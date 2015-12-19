# HellCore
Source code for the HellCore project, a fork of LambdaMOO.

## Known dependencies:
* libstdc++
* gperf

## README

This is an attempt at making a hellcore MOO database. Started from HellMOO, I
deleted tons of Hell-specific objects and verbs. I might have deleted useful
stuff, I more than likely left references to useless/deleted props/objects all
over the place.

To start it, you will need to run something like this:
> ./moo -l moo.log hellcore.db hell.db.test 7777
> (./moo -l <logfile> <original DB> <new DB> <port>)

or just:

> ./restart hellcore

You should be able to login with 'connect Wizard', then change your password.

### Building

FOR UNICODE BRANCH ONLY:

run this commands before running make:
> yacc -d parser.y

Simply change to the src directory, and type 'make'.  This should build the moo binary.

### USE AT YOUR OWN RISK. I DENY RESPONSIBILITY FOR:
* Spontaneous hairy nose
* Micropenis
* Liver vs pancreas internal war
* Making baby Jesus retch
* Getting on the No-Fly list
* Lizard people living under the Appalachian Mountains following you around

Cheers,

Senso/Dionysus, Necanthrope

