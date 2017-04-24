# This file is used to generate the configure script.
# To build it, run autogen.sh in this directory.

# Make changes in configure.ac, not configure.


# The minimum autoconf version required to rebuild the configure script.
# (This is only needed on developer machines, and should be set to the lowest
# possible version.)
AC_PREREQ([2.64])


# Package name, version, bug report address, tarball name (default), and URL.
# NOTE: The HellCore version should be set here, not elsewhere.
AC_INIT([HellCore],
        [1.10.4],
        [https://github.com/necanthrope/HellCore],
        ,
        [https://github.com/necanthrope/HellCore])


# Initialize automake.
# foreign:      Tell automake not to expect the standard GNU files (NEWS,
#               AUTHORS, etc.), and not to error when it doesn't find them.
AM_INIT_AUTOMAKE([foreign])

# By default, just show what's being compiled while building, rather than the
# whole command.
# (This can be overridden by passing --disable-silent-rules to configure, or by
# running 'make V=1 [target]'.)
AM_SILENT_RULES([yes])


# This should be the relative path to a unique file in the project.
# (It's just used as a sanity check for the configure script to make sure it's
# looking in the right place.)
# If the file is renamed, moved, or deleted, adjust this line to refer to
# another uniquely named file.
AC_CONFIG_SRCDIR([src/db_verbs.c])



# These are the files we want configure to substitute values.
# For example, Makefile.in (generated automatically by automake) becomes
# Makefile.
AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/version.c])


# Check for necessary programs.

# Make sure we have a working C compiler.
AC_PROG_CC

# Make sure we have a working yacc/bison/lex compiler.
# (If a compiler isn't available but the yacc/bison/lex files are already
# compiled (e.g. as in a source tarbal), this will fail safely and set the
# timestamps as if they were compiled.)
# (The first line is so automake knows to handle yacc/bison/lex, and the second
# makes autoconf look for a yacc/bison/lex compiler.)
AM_PROG_LEX
AC_PROG_YACC

# Check if we have gperf.
# (This will follow the same fail-safe behavior as noted above for
# yacc/bison/lex.)
AM_MISSING_PROG([GPERF], [gperf])

# Find a valid sed.
AC_PROG_SED



# Check for necessary libraries and headers.

# Link the math library.
AC_SEARCH_LIBS([atan2], [m])


# Link the crypt library.
AC_SEARCH_LIBS([crypt], [crypt])


# Generate the configure script.
# (There probably shouldn't be any autoconf things after this.)
AC_OUTPUT
