/* C code produced by gperf version 3.0.4 */

/* Command-line: gperf -aCIptT -k'1,3,$' keywords.gperf  */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 1 "keywords.gperf"
	/* -*- C -*- */

/******************************************************************************
  Copyright (c) 1992, 1995, 1996 Xerox Corporation.  All rights reserved.
  Portions of this code were written by Stephen White, aka ghond.
  Use and copying of this software and preparation of derivative works based
  upon this software are permitted.  Any distribution of this software or
  derivative works must comply with all applicable United States export
  control laws.  This software is made available AS IS, and Xerox Corporation
  makes no warranty about the software, its performance or its conformity to
  any specification.  Any person obtaining a copy of this software is requested
  to send their name and post office or electronic mail address to:
    Pavel Curtis
    Xerox PARC
    3333 Coyote Hill Rd.
    Palo Alto, CA 94304
    Pavel@Xerox.Com
 *****************************************************************************/

#include "my-string.h"

#include "config.h"
#include "keywords.h"
#include "tokens.h"
#include "utils.h"

/**/

#include <string.h>

#define TOTAL_KEYWORDS 36
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 9
#define MIN_HASH_VALUE 3
#define MAX_HASH_VALUE 51
/* maximum key range = 49, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (str, len)
     register const char *str;
     register unsigned int len;
{
  static const unsigned char asso_values[] =
    {
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52,  0, 52, 20,  0,  0,
       0,  5, 52, 35, 52, 52, 52, 10, 20, 52,
      25, 35, 25, 45, 30, 52, 20, 52, 52,  0,
      52, 52, 52, 52, 52, 52, 52, 52, 10, 15,
       0,  0,  5, 52, 52, 15, 52,  0, 52, 52,
       0, 52, 52, 52,  5,  5, 10, 52, 52,  0,
      52,  0, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

#ifdef __GNUC__
__inline
#if defined __GNUC_STDC_INLINE__ || defined __GNUC_GNU_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct keyword *
in_word_set (str, len)
     register const char *str;
     register unsigned int len;
{
  static const struct keyword wordlist[] =
    {
      {""}, {""}, {""},
#line 48 "keywords.gperf"
      {"ANY",		DBV_Exceptions, tANY},
      {""},
#line 67 "keywords.gperf"
      {"yield",		DBV_Hash, tYIELD},
#line 47 "keywords.gperf"
      {"endtry",		DBV_Exceptions, tENDTRY},
#line 40 "keywords.gperf"
      {"endfork",	DBV_Prehistory, tENDFORK},
#line 43 "keywords.gperf"
      {"endwhile",	DBV_Prehistory, tENDWHILE},
#line 33 "keywords.gperf"
      {"else",		DBV_Prehistory, tELSE},
#line 35 "keywords.gperf"
      {"endif",		DBV_Prehistory, tENDIF},
#line 38 "keywords.gperf"
      {"endfor",		DBV_Prehistory, tENDFOR},
#line 46 "keywords.gperf"
      {"finally",	DBV_Exceptions, tFINALLY},
#line 44 "keywords.gperf"
      {"try",		DBV_Exceptions, tTRY},
#line 39 "keywords.gperf"
      {"fork",		DBV_Prehistory, tFORK},
#line 49 "keywords.gperf"
      {"break",		DBV_BreakCont, tBREAK},
#line 34 "keywords.gperf"
      {"elseif",		DBV_Prehistory, tELSEIF},
#line 37 "keywords.gperf"
      {"in",		DBV_Prehistory, tIN},
#line 36 "keywords.gperf"
      {"for",		DBV_Prehistory, tFOR},
      {""},
#line 42 "keywords.gperf"
      {"while",		DBV_Prehistory, tWHILE},
#line 41 "keywords.gperf"
      {"return",		DBV_Prehistory, tRETURN},
#line 32 "keywords.gperf"
      {"if",		DBV_Prehistory, tIF},
#line 50 "keywords.gperf"
      {"continue",	DBV_BreakCont, tCONTINUE},
      {""},
#line 53 "keywords.gperf"
      {"E_DIV",		DBV_Prehistory, tERROR,	E_DIV},
#line 51 "keywords.gperf"
      {"E_NONE",		DBV_Prehistory, tERROR,	E_NONE},
#line 57 "keywords.gperf"
      {"E_VARNF",	DBV_Prehistory, tERROR,	E_VARNF},
#line 56 "keywords.gperf"
      {"E_VERBNF",	DBV_Prehistory, tERROR,	E_VERBNF},
      {""}, {""},
#line 45 "keywords.gperf"
      {"except",		DBV_Exceptions, tEXCEPT},
#line 61 "keywords.gperf"
      {"E_RANGE",	DBV_Prehistory, tERROR,	E_RANGE},
#line 55 "keywords.gperf"
      {"E_PROPNF",	DBV_Prehistory, tERROR,	E_PROPNF},
#line 59 "keywords.gperf"
      {"E_RECMOVE",	DBV_Prehistory, tERROR,	E_RECMOVE},
      {""},
#line 52 "keywords.gperf"
      {"E_TYPE",		DBV_Prehistory, tERROR,	E_TYPE},
#line 66 "keywords.gperf"
      {"E_FLOAT",	DBV_Float,	tERROR,	E_FLOAT},
#line 60 "keywords.gperf"
      {"E_MAXREC",	DBV_Prehistory, tERROR,	E_MAXREC},
      {""}, {""},
#line 54 "keywords.gperf"
      {"E_PERM",		DBV_Prehistory, tERROR,	E_PERM},
#line 65 "keywords.gperf"
      {"E_QUOTA",	DBV_Prehistory, tERROR,	E_QUOTA},
#line 58 "keywords.gperf"
      {"E_INVIND",	DBV_Prehistory, tERROR,	E_INVIND},
      {""}, {""},
#line 63 "keywords.gperf"
      {"E_NACC",		DBV_Prehistory, tERROR,	E_NACC},
      {""},
#line 64 "keywords.gperf"
      {"E_INVARG",	DBV_Prehistory, tERROR,	E_INVARG},
      {""}, {""},
#line 62 "keywords.gperf"
      {"E_ARGS",		DBV_Prehistory, tERROR,	E_ARGS}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].name;

          if (*str == *s && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}
#line 68 "keywords.gperf"


const struct keyword *
find_keyword(const char *word)
{
    return in_word_set(word, strlen(word));
}

char rcsid_keywords[] = "$Id: keywords.gperf,v 1.4 2009/03/08 12:41:31 blacklite Exp $";

/* $Log: keywords.gperf,v $
/* Revision 1.4  2009/03/08 12:41:31  blacklite
/* Added HASH data type, yield keyword, MEMORY_TRACE, vfscanf(),
/* extra myrealloc() and memcpy() tricks for lists, Valgrind
/* support for str_intern.c, etc. See ChangeLog.txt.
/*
/* Revision 1.3  2007/09/12 07:33:29  spunky
/* This is a working version of the current HellMOO server
/*
/* Revision 1.1.1.1  1997/03/03 03:45:02  nop
/* LambdaMOO 1.8.0p5
/*
 * Revision 2.2  1996/02/08  06:33:21  pavel
 * Added `break', `continue', and E_FLOAT.  Updated copyright notice for 1996.
 * Release 1.8.0beta1.
 *
 * Revision 2.1  1995/12/11  08:15:42  pavel
 * Added #include "tokens.h" removed from keywords.h.  Release 1.8.0alpha2.
 *
 * Revision 2.0  1995/11/30  05:02:56  pavel
 * New baseline version, corresponding to release 1.8.0alpha1.
 *
 * Revision 1.1  1995/11/30  05:01:47  pavel
 * Initial revision
 */
