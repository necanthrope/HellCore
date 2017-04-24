# HellCore
Source code for the HellCore project, a fork of LambdaMOO.

## Dependencies:

* autoconf
* automake
* bison
* gcc
* gperf
* libstdc++
* make
* sed

If you are unable to build despite having working and recent versions of these
installed, please file a bug report on this repository.

## README

This is an attempt at making a hellcore MOO database. Started from HellMOO, I
deleted tons of Hell-specific objects and verbs. I might have deleted useful
stuff, I more than likely left references to useless/deleted props/objects all
over the place.

Before you start the server, read the section on building it.

To start it, you can run
```shell
./restart hellcore
```

You can also start it with something like this:
```shell
./moo -l moo.log hellcore.db hell.db.test 7777
```

```
(./moo -l <logfile> <original DB> <new DB> <port>)
```

You should be able to login with 'connect Wizard', then change your password.

### Building

Simply run
```shell
./build.sh
```

The moo binary will be located as `src/moo`.

If you are familiar with the standard Linux/Unix build process, you can instead
run
```shell
./autogen.sh && ./configure && make
```

### USE AT YOUR OWN RISK. I DENY RESPONSIBILITY FOR:
* Spontaneous hairy nose
* Micropenis
* Liver vs pancreas internal war
* Making baby Jesus retch
* Getting on the No-Fly list
* Lizard people living under the Appalachian Mountains following you around

Cheers,

Senso/Dionysus, Necanthrope, diatomic.ge
