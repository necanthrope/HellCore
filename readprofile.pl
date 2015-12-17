#!/usr/bin/perl -w


#   ----- readprofile.pl <profile log>
#
#
#   yes this is a horrible gross pile of perl, but I didn't realize I'd 
#   want to ever show it to anyone, let alone add it to cvs, but I guess
#   I should.
#
#   sorry it's such a mess. :(   -- Seraph
#

use strict;

my $filename = shift;
if (!$filename) {
  print "Usage: $0 <profile log>\n";
  exit 1;
}

open (PRO, "<", $filename) or die $?;
$/ = "\n";

my $lastsec = 0;
my $do_print = 0;

  my %ok_transitions = (
	'start_execution' => [qw(call return end_execution)],
	'end_execution'   => [qw(start_execution)],
	'newtask'         => [qw(start_execution)],
	'call'		  => [qw(call return end_execution)],
	'return'	  => [qw(call return end_execution)],
  );

my %stacks;
my %calls;
my %verbs;
my %returns;
my %times;
my %puretimes;
my %stacktimes;
my %pauses;

sub diff_ns {
	my ($a, $b) = @_;

	my $secs = $b->[0] - $a->[0];
	if ($secs) {
		return ($secs * 1000000000 + (1000000000 - $a->[1]) + $b->[1]);
	} else {
		return ($b->[1] - $a->[1]);
	}
}

sub f2s
{
    my $frame = shift;
    return join ("", "  ", $frame->{verb}, " ", $frame->{time}[0], ".", $frame->{time}[1], " (",
	$frame->{context}, ")");
}

while (<PRO>) {
  chomp;

  my ($taskid, $forkid, $context, $vloc, $verbname, $this, $retval) = split(/,/);
  my $cputime;

  ($cputime, $taskid) = split (/: /, $taskid);
  my ($cpu_s, $cpu_ns) = split(/\./, $cputime);
  $cpu_s =~ s/^\+ //;

  if ($forkid ne "MAIN") {
    $taskid = $taskid . "." . $forkid;
  }

  $verbname = (split (/ /, $verbname))[0];

  $this = "" if ($this eq $vloc);

  # deal with stack etc
  my ($stack, $stacktop);

  if (exists($stacks{$taskid})) {
    $stack = $stacks{$taskid};
    $stacktop = $stack->[$#$stack];
  } else {
    $stacks{$taskid} = [];
    $stack = $stacks{$taskid};
  }

 
  my $objverb = "$vloc:$verbname";
  my $thistime = [ $cpu_s, $cpu_ns ];
  my $frame = { "verb" => $objverb, "time" => $thistime, "context" => $context };

  if ($context eq "newtask" && defined($stacktop)) {
	warn "task ID re-use";
	my $newtaskid = $taskid . "A";
	print STDERR "$taskid: moving to $newtaskid\n";
	$stacks{$newtaskid} = $stacks{$taskid};
	$stacks{$taskid} = [];
	$stack = $stacks{$taskid};
	$stacktimes{$newtaskid} = delete($stacktimes{$taskid});
	$stacktop = undef;
  }

  if (defined($stacktop) &&
	!(grep { $_ eq $context } @{$ok_transitions{$stacktop->{context}}}) ) {
	print STDERR "$taskid: $context after $stacktop->{context} -- disallowed\n";
	print STDERR "  top of stack: ", f2s($stacktop), "\n";
	print STDERR "  new frame:    ", f2s($frame), "\n";
	die;
  }


  if ($context eq "end_execution") {
	# allowed after: start, call, return
	# followed by:   start

	if (exists($stacktimes{$taskid})) {
	  # from previous start/call/return, we were running this verb.

	  my $start_time = $stacktimes{$taskid};
	  my $elapsed_ns = diff_ns($start_time, $thistime);
	  $puretimes{$objverb} += $elapsed_ns / 1000.0;
	} else {
	  print STDERR f2s($frame), "\n";
	  print STDERR "end_execution out of nowhere for $taskid";
	}
	$stacktimes{$taskid} = $thistime;
	$pauses{$objverb}++;
	push @$stack, $frame;

  } elsif ($context eq "start_execution") {
	# allowed after: newtask, end, NULL
	# followed by:   call, return, end

	if (!defined($stacktop)) {
		push @$stack, $frame;
	} elsif ($stacktop->{context} eq "newtask") {
		# ok, no problem, pop newtask and put this on
		pop @$stack;
		push @$stack, $frame;
	} else {
		# this is a return from suspend, pop suspend
		pop @$stack;
                my $elapsed_ns = diff_ns( $stacktop->{time}, $thistime );

		# iterate through stack and reduce times
		foreach my $prev_frame (@$stack) {
			$times{$prev_frame->{verb}} -= ($elapsed_ns / 1000.0);
		}
	}
	$stacktimes{$taskid} = $thistime;

  } elsif ($context eq "call") {
	# allowed after: start, call, return
	# followed by:   end, call, return

	push @$stack, $frame;

	if (defined($stacktop)) {
		$calls{$stacktop->{verb}}{$objverb}++;
		$verbs{$objverb}++;

	# halt execution of caller, add total time
	my $caller_stop_time = $stacktimes{$taskid};
	my $caller_total_time = diff_ns( $caller_stop_time, $thistime );
	$puretimes{$stacktop->{verb}} += $caller_total_time / 1000.0;
	}

	# begin execution of callee
	$stacktimes{$taskid} = $thistime;

  } elsif ($context eq "return") {
	# allowed after: start, call, return
	# followed by:   end, call, return

	my $caller;

	if (!defined($stacktop)) {
		# nothing
	} elsif ($stacktop->{verb} ne $objverb) {
		# try to find call

		my @savedstack = @$stack;
		my $n_jump = 0;

		print "$taskid: saving stack and searching for original call...\n";
		while (@$stack) {
			my $searchframe = pop @$stack;
			print "  popped ", $searchframe->{verb}, " from stack\n";
			$n_jump++;
			if ($searchframe->{verb} eq $objverb) {
				print "  found caller, jumped $n_jump frames\n";
				$caller = $searchframe;
			}
		}
		if (!defined($caller)) {
			print "  couldn't find caller anywhere in stack, restoring and continuing\n";
			@$stack = @savedstack;
		}

	} else {
		$caller = pop @$stack;
	}

        if (defined($caller) && $caller->{context} eq "newtask") {
                print STDERR "$taskid: return after newtask\n";
                die;
        }

        if (defined($caller)) {
	  my $elapsed_ns = diff_ns( $caller->{time}, $thistime );
	  $times{$objverb} += ($elapsed_ns / 1000.0);
	  
	  # halt execution of this
	  my $previous_start_time = $stacktimes{$taskid};
	  my $total_execution_time = diff_ns( $previous_start_time, $thistime );
	  $puretimes{$objverb} += $total_execution_time / 1000.0;

	  # begin execution of caller
	  $stacktimes{$taskid} = $thistime;
        }
	$returns{$objverb}{$retval}++ if defined($retval);
        
  } elsif ($context eq "newtask") {
	if (@$stack) {
		print STDERR "$taskid: caller shouldn't exist for new task\n";
	}
	push @$stack, $frame;

  } else {
	die "unknown context $context";
  }


  if ($lastsec ne $cpu_s) {
	$lastsec = $cpu_s;
	print "$cpu_s.000..\n";
  }
} # end while

my %avgtimes;
foreach my $objverb (keys(%verbs)) {
   next unless exists($puretimes{$objverb});

   my $runtime = $puretimes{$objverb};
   $avgtimes{$objverb} = $runtime / $verbs{$objverb};
}


my $titlefmt = "%-50s %10s\n";

my @counts;
foreach my $caller (keys(%calls)) {
   foreach my $callee (keys(%{$calls{$caller}})) {
	my $str = "$caller -> $callee";
	push @counts, [ $str, $calls{$caller}->{$callee} ];
   }
}

@counts = (sort { $b->[1] <=> $a->[1] } @counts)[1..50];

printf $titlefmt, "top 50 caller/callee combinations", "count";
foreach my $c (@counts) {
   last unless $c;
   printf "%-50s %10d\n", @$c;
}

print "\n";

@counts = ();

foreach my $verb (keys(%verbs)) {
        push @counts, [ $verb, $verbs{$verb} ];
}

@counts = (sort { $b->[1] <=> $a->[1] } @counts)[1..50];

printf $titlefmt, "top 50 called verbs", "count";
foreach my $c (@counts) {
   last unless $c;
   printf "%-50s %10d\n", @$c;
}

print "\n";

@counts = ();

foreach my $verb (keys(%returns)) {
   foreach my $value (keys(%{$returns{$verb}})) {
        my $str = "$verb => $value";
        push @counts, [ $str, $returns{$verb}->{$value} ];
   }
}

@counts = (sort { $b->[1] <=> $a->[1] } @counts)[1..50];

printf $titlefmt, "top 50 returned values", "count";
foreach my $c (@counts) {
   last unless $c;
   printf "%-50s %10d\n", @$c;
}

print "\n";



@counts = ();

foreach my $verb (keys(%times)) {
   push @counts, [ $verb, $times{$verb} ];
}

@counts = (sort { $b->[1] <=> $a->[1] } @counts)[1..50];

printf $titlefmt, "top 50 verbs by cumulative time (inc callees)", "usec";
foreach my $c (@counts) {
   last unless $c;
   printf "%-50s %10d\n", @$c;
}
print "\n";


@counts = ();

foreach my $verb (keys(%puretimes)) {
   push @counts, [ $verb, $puretimes{$verb} ];
}

@counts = (sort { $b->[1] <=> $a->[1] } @counts)[1..50];

printf $titlefmt, "top 50 verbs by in-verb time (exc callees)", "usec";
foreach my $c (@counts) {
   last unless $c;
   printf "%-50s %10d\n", @$c;
}
print "\n";


@counts = ();

foreach my $verb (keys(%avgtimes)) {
   push @counts, [ $verb, $avgtimes{$verb} ];
}

@counts = (sort { $b->[1] <=> $a->[1] } @counts)[1..50];

printf $titlefmt, "top 50 verbs by average execution time (exc callees)", "usec";
foreach my $c (@counts) {
   last unless $c;
   printf "%-50s %10d\n", @$c;
}
print "\n";



@counts = ();

foreach my $verb (keys(%pauses)) {
   push @counts, [ $verb, $pauses{$verb} ];
}

@counts = (sort { $b->[1] <=> $a->[1] } @counts)[1..50];

printf $titlefmt, "top 50 verbs by # of suspends", "count";
foreach my $c (@counts) {
   last unless $c;
   printf "%-50s %10d\n", @$c;
}

exit;

#
# $Id: readprofile.pl,v 1.3 2009/10/11 18:32:31 blacklite Exp $
#
# $Log: readprofile.pl,v $
# Revision 1.3  2009/10/11 18:32:31  blacklite
# ignore end_exec out of nowhere and no retvals
#
# Revision 1.2  2009/09/29 20:45:33  blacklite
# add arg, calc average execution time
#
# Revision 1.1  2009/07/25 03:21:59  blacklite
# add profiling when PROFILE_VERBS is defined, spits info out to a profile log
# (specify with -p). I may still be missing some spots but this seems to give
# usable info right now.
#
#

