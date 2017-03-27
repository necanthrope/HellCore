/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "parser.y"

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

/*************************************************************************/
/* NOTE: If you add an #include here, make sure you properly update the  */
/*       parser.o dependency line in the Makefile.			 */
/*************************************************************************/

#include "my-ctype.h"
#include "my-math.h"
#include "my-stdlib.h"
#include "my-string.h"

#include "ast.h"
#include "code_gen.h" 
#include "config.h"
#include "functions.h"
#include "keywords.h"
#include "list.h"
#include "log.h"
#include "numbers.h"
#include "opcode.h"
#include "parser.h"
#include "program.h"
#include "storage.h"
#include "streams.h"
#include "structures.h"
#include "sym_table.h"
#include "utils.h"
#include "version.h" 

static Stmt    	       *prog_start;
static int		dollars_ok;
static DB_Version	language_version;

static void	error(const char *, const char *);
static void	warning(const char *, const char *);
static int	find_id(char *name);
static void	yyerror(const char *s);
static int	yylex(void);
static Scatter *scatter_from_arglist(Arg_List *);
static Scatter *add_scatter_item(Scatter *, Scatter *);
static void	vet_scatter(Scatter *);
static void	push_loop_name(const char *);
static void	pop_loop_name(void);
static void	suspend_loop_scope(void);
static void	resume_loop_scope(void);

enum loop_exit_kind { LOOP_BREAK, LOOP_CONTINUE };

static void	check_loop_name(const char *, enum loop_exit_kind);


/* Line 268 of yacc.c  */
#line 140 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     tINTEGER = 258,
     tOBJECT = 259,
     tFLOAT = 260,
     tSTRING = 261,
     tID = 262,
     tERROR = 263,
     tIF = 264,
     tELSE = 265,
     tELSEIF = 266,
     tENDIF = 267,
     tFOR = 268,
     tIN = 269,
     tENDFOR = 270,
     tRETURN = 271,
     tYIELD = 272,
     tFORK = 273,
     tENDFORK = 274,
     tWHILE = 275,
     tENDWHILE = 276,
     tTRY = 277,
     tENDTRY = 278,
     tEXCEPT = 279,
     tFINALLY = 280,
     tANY = 281,
     tBREAK = 282,
     tCONTINUE = 283,
     tTO = 284,
     tARROW = 285,
     tHASHARROW = 286,
     tAND = 287,
     tOR = 288,
     tGE = 289,
     tLE = 290,
     tNE = 291,
     tEQ = 292,
     tUNARYMINUS = 293
   };
#endif
/* Tokens.  */
#define tINTEGER 258
#define tOBJECT 259
#define tFLOAT 260
#define tSTRING 261
#define tID 262
#define tERROR 263
#define tIF 264
#define tELSE 265
#define tELSEIF 266
#define tENDIF 267
#define tFOR 268
#define tIN 269
#define tENDFOR 270
#define tRETURN 271
#define tYIELD 272
#define tFORK 273
#define tENDFORK 274
#define tWHILE 275
#define tENDWHILE 276
#define tTRY 277
#define tENDTRY 278
#define tEXCEPT 279
#define tFINALLY 280
#define tANY 281
#define tBREAK 282
#define tCONTINUE 283
#define tTO 284
#define tARROW 285
#define tHASHARROW 286
#define tAND 287
#define tOR 288
#define tGE 289
#define tLE 290
#define tNE 291
#define tEQ 292
#define tUNARYMINUS 293




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 69 "parser.y"

  Stmt	       *stmt;
  Expr	       *expr;
  int		integer;
  Objid		object;
  double       *real;
  char	       *string;
  enum error	error;
  Arg_List     *args;
  Cond_Arm     *arm;
  Except_Arm   *except;
  Scatter      *scatter;



/* Line 293 of yacc.c  */
#line 268 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 280 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1701

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  101
/* YYNRULES -- Number of states.  */
#define YYNSTATES  231

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,     2,    54,    47,     2,    62,
      55,    56,    45,    43,    64,    44,    51,    46,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    52,    58,
      37,    31,    38,    33,    63,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    53,     2,    57,    48,     2,    61,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    59,    34,    60,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    32,    35,    36,    39,
      40,    41,    42,    50
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    18,    19,    29,    30,
      42,    43,    51,    52,    61,    62,    70,    71,    80,    83,
      86,    90,    93,    97,   101,   104,   108,   111,   113,   118,
     124,   125,   132,   133,   136,   139,   140,   145,   151,   152,
     154,   156,   158,   160,   162,   164,   166,   169,   173,   179,
     186,   192,   201,   207,   215,   217,   221,   227,   232,   236,
     240,   244,   248,   252,   256,   260,   264,   268,   272,   276,
     280,   284,   288,   292,   295,   298,   302,   306,   310,   316,
     323,   324,   326,   328,   329,   332,   333,   335,   336,   338,
     340,   343,   347,   352,   356,   362,   366,   370,   374,   379,
     381,   384
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      66,     0,    -1,    67,    -1,    -1,    67,    68,    -1,     9,
      55,    81,    56,    67,    75,    76,    12,    -1,    -1,    13,
       7,    14,    55,    81,    56,    69,    67,    15,    -1,    -1,
      13,     7,    14,    53,    81,    29,    81,    57,    70,    67,
      15,    -1,    -1,    20,    55,    81,    56,    71,    67,    21,
      -1,    -1,    20,     7,    55,    81,    56,    72,    67,    21,
      -1,    -1,    18,    55,    81,    56,    73,    67,    19,    -1,
      -1,    18,     7,    55,    81,    56,    74,    67,    19,    -1,
      81,    58,    -1,    27,    58,    -1,    27,     7,    58,    -1,
      28,    58,    -1,    28,     7,    58,    -1,    16,    81,    58,
      -1,    16,    58,    -1,    17,    81,    58,    -1,    17,    58,
      -1,    58,    -1,    22,    67,    77,    23,    -1,    22,    67,
      25,    67,    23,    -1,    -1,    75,    11,    55,    81,    56,
      67,    -1,    -1,    10,    67,    -1,    24,    79,    -1,    -1,
      77,    24,    78,    79,    -1,    80,    55,    83,    56,    67,
      -1,    -1,     7,    -1,     3,    -1,     5,    -1,     6,    -1,
       4,    -1,     8,    -1,     7,    -1,    54,     7,    -1,    81,
      51,     7,    -1,    81,    51,    55,    81,    56,    -1,    81,
      52,     7,    55,    85,    56,    -1,    54,     7,    55,    85,
      56,    -1,    81,    52,    55,    81,    56,    55,    85,    56,
      -1,    81,    53,    82,    81,    57,    -1,    81,    53,    82,
      81,    29,    81,    57,    -1,    54,    -1,    81,    31,    81,
      -1,    59,    89,    60,    31,    81,    -1,     7,    55,    85,
      56,    -1,    81,    43,    81,    -1,    81,    44,    81,    -1,
      81,    45,    81,    -1,    81,    46,    81,    -1,    81,    47,
      81,    -1,    81,    48,    81,    -1,    81,    35,    81,    -1,
      81,    36,    81,    -1,    81,    42,    81,    -1,    81,    41,
      81,    -1,    81,    37,    81,    -1,    81,    40,    81,    -1,
      81,    38,    81,    -1,    81,    39,    81,    -1,    81,    14,
      81,    -1,    44,    81,    -1,    49,    81,    -1,    55,    81,
      56,    -1,    59,    85,    60,    -1,    53,    86,    57,    -1,
      81,    33,    81,    34,    81,    -1,    61,    81,    49,    83,
      84,    62,    -1,    -1,    26,    -1,    87,    -1,    -1,    30,
      81,    -1,    -1,    87,    -1,    -1,    88,    -1,    81,    -1,
      63,    81,    -1,    87,    64,    81,    -1,    87,    64,    63,
      81,    -1,    81,    32,    81,    -1,    88,    64,    81,    32,
      81,    -1,    87,    64,    90,    -1,    89,    64,    90,    -1,
      89,    64,     7,    -1,    89,    64,    63,     7,    -1,    90,
      -1,    33,     7,    -1,    33,     7,    31,    81,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   114,   114,   120,   121,   136,   145,   144,   157,   156,
     170,   169,   182,   181,   194,   193,   206,   205,   217,   222,
     228,   234,   240,   246,   251,   256,   261,   266,   268,   274,
     284,   285,   303,   304,   309,   312,   311,   337,   342,   343,
     347,   352,   357,   362,   367,   372,   377,   386,   393,   397,
     404,   413,   417,   422,   430,   436,   458,   466,   487,   491,
     495,   499,   503,   507,   511,   515,   519,   523,   527,   531,
     535,   539,   543,   547,   568,   573,   575,   580,   585,   592,
     603,   606,   608,   613,   614,   619,   620,   626,   627,   632,
     634,   636,   650,   667,   672,   690,   699,   703,   708,   713,
     718,   722
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "tINTEGER", "tOBJECT", "tFLOAT",
  "tSTRING", "tID", "tERROR", "tIF", "tELSE", "tELSEIF", "tENDIF", "tFOR",
  "tIN", "tENDFOR", "tRETURN", "tYIELD", "tFORK", "tENDFORK", "tWHILE",
  "tENDWHILE", "tTRY", "tENDTRY", "tEXCEPT", "tFINALLY", "tANY", "tBREAK",
  "tCONTINUE", "tTO", "tARROW", "'='", "tHASHARROW", "'?'", "'|'", "tAND",
  "tOR", "'<'", "'>'", "tGE", "tLE", "tNE", "tEQ", "'+'", "'-'", "'*'",
  "'/'", "'%'", "'^'", "'!'", "tUNARYMINUS", "'.'", "':'", "'['", "'$'",
  "'('", "')'", "']'", "';'", "'{'", "'}'", "'`'", "'\\''", "'@'", "','",
  "$accept", "program", "statements", "statement", "$@1", "$@2", "$@3",
  "$@4", "$@5", "$@6", "elseifs", "elsepart", "excepts", "$@7", "except",
  "opt_id", "expr", "dollars_up", "codes", "default", "arglist",
  "hashlist", "ne_arglist", "ne_hashlist", "scatter", "scatter_item", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,    61,   286,    63,   124,   287,   288,    60,    62,   289,
     290,   291,   292,    43,    45,    42,    47,    37,    94,    33,
     293,    46,    58,    91,    36,    40,    41,    93,    59,   123,
     125,    96,    39,    64,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    65,    66,    67,    67,    68,    69,    68,    70,    68,
      71,    68,    72,    68,    73,    68,    74,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      75,    75,    76,    76,    77,    78,    77,    79,    80,    80,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      82,    83,    83,    84,    84,    85,    85,    86,    86,    87,
      87,    87,    87,    88,    88,    89,    89,    89,    89,    89,
      90,    90
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     8,     0,     9,     0,    11,
       0,     7,     0,     8,     0,     7,     0,     8,     2,     2,
       3,     2,     3,     3,     2,     3,     2,     1,     4,     5,
       0,     6,     0,     2,     2,     0,     4,     5,     0,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     5,     6,
       5,     8,     5,     7,     1,     3,     5,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     3,     3,     3,     5,     6,
       0,     1,     1,     0,     2,     0,     1,     0,     1,     1,
       2,     3,     4,     3,     5,     3,     3,     3,     4,     1,
       2,     4
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,    40,    43,    41,    42,    45,    44,
       0,     0,     0,     0,     0,     0,     3,     0,     0,     0,
       0,    87,    54,     0,    27,    85,     0,     4,     0,    85,
       0,     0,    24,     0,    26,     0,     0,     0,     0,     0,
       0,     0,    19,     0,    21,    73,    74,     0,     0,    88,
      46,     0,     0,     0,    89,     0,    86,     0,    99,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
      18,     0,    86,     0,     0,    23,    25,     0,     0,     0,
       0,    38,     3,     0,    20,    22,     0,    77,     0,    85,
      75,   100,    90,    76,     0,     0,     0,     0,    72,    55,
       0,    64,    65,    68,    70,    71,    69,    67,    66,    58,
      59,    60,    61,    62,    63,    47,     0,     0,     0,     0,
      57,     0,     3,     0,     0,     0,    14,     0,    10,    39,
      34,     0,     0,    28,    35,    93,     0,     0,     0,     0,
      91,    95,     0,    97,     0,    96,    81,    83,    82,     0,
       0,    85,     0,     0,    30,     0,     0,    16,     3,    12,
       3,     0,    29,    38,     0,    50,   101,    92,    56,    98,
       0,     0,    78,    48,     0,     0,     0,    52,    32,     0,
       6,     3,     0,     3,     0,     0,    36,    94,    84,    79,
      49,    85,     0,     3,     0,     0,     0,     3,     0,    15,
       0,    11,     3,     0,    53,    33,     0,     5,     8,     0,
      17,    13,    37,    51,     0,     3,     7,     3,     0,    31,
       9
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    27,   207,   225,   170,   193,   168,   191,
     188,   205,    93,   173,   140,   141,    28,   129,   157,   181,
      55,    48,    82,    49,    57,    58
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -61
static const yytype_int16 yypact[] =
{
     -61,    27,   772,   -61,   -61,   -61,   -61,   -61,   -39,   -61,
      -6,    32,   798,   831,    -4,    18,   -61,    16,    17,   447,
     447,   447,    43,   447,   -61,   106,   447,   -61,   860,   226,
     447,    58,   -61,   895,   -61,   930,    14,   447,    22,   447,
     300,    31,   -61,    35,   -61,   -44,   -44,  1420,    26,    28,
      39,  1070,    88,   447,  1596,    37,    40,   -54,   -61,  1455,
     447,   447,   447,   447,   447,   447,   447,   447,   447,   447,
     447,   447,   447,   447,   447,   447,   447,    23,    25,   -61,
     -61,    42,    41,  1105,   -27,   -61,   -61,   447,  1140,   447,
    1175,   108,   -61,    24,   -61,   -61,   447,   -61,   447,   226,
     -61,    86,  1596,   -61,   194,    91,     7,   210,   -10,  1596,
    1491,  1648,  1648,   -10,   -10,   -10,   -10,   -10,   -10,    55,
      55,    34,    34,    34,    34,   -61,   447,    64,   447,   447,
     -61,   287,   -61,   447,   447,  1210,   -61,  1245,   -61,   -61,
     -61,    69,   359,   -61,   -61,  1596,  1526,    71,   447,   447,
    1596,   -61,   447,   -61,   121,   -61,   -61,    99,    41,   447,
    1280,   226,  1315,   965,   772,  1561,  1350,   -61,   -61,   -61,
     -61,   210,   -61,   108,   447,   -61,  1596,  1596,  1596,   -61,
     447,    68,  1631,   -61,    75,    77,   447,   -61,     9,   447,
     -61,   -61,   418,   -61,   477,    78,   -61,  1596,  1596,   -61,
     -61,   226,  1000,   -61,    80,   124,  1035,   -61,   536,   -61,
     595,   -61,   -61,    81,   -61,   772,   447,   -61,   -61,   654,
     -61,   -61,   772,   -61,  1385,   -61,   -61,   -61,   713,   772,
     -61
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -61,   -61,   -16,   -61,   -61,   -61,   -61,   -61,   -61,   -61,
     -61,   -61,   -61,   -61,   -35,   -61,    -8,   -61,   -29,   -61,
     -28,   -61,   -23,   -61,   -61,   -60
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
      40,    81,    56,    36,    33,    35,   105,    77,    78,    79,
     106,    45,    46,    47,   153,    51,    29,    54,    59,   203,
     204,    54,    83,    41,    43,    38,   133,     3,   134,    88,
     125,    90,   127,    71,    72,    73,    74,    75,    76,    31,
      52,    77,    78,    79,   151,   102,   155,   143,   144,    30,
      50,    37,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,    87,
     154,   147,    84,    39,    42,    44,   142,    89,   126,   135,
     128,   137,    76,    97,   158,    77,    78,    79,   145,    94,
     146,    54,    98,    95,    99,   101,   150,   103,   130,    54,
      73,    74,    75,    76,   104,   131,    77,    78,    79,     4,
       5,     6,     7,     8,     9,   139,   164,   148,   160,   161,
     162,   163,   152,   150,   171,   165,   166,   175,   179,   180,
     199,   200,   201,   184,   212,   216,   217,   223,   196,    52,
     176,   177,   195,     0,   178,     0,     0,     0,   158,     0,
      19,   182,   192,    54,   194,    20,     0,     0,     0,    21,
      22,    23,     0,    54,     0,    25,   197,    26,     0,    53,
       0,     0,   198,   213,     0,   208,     0,   210,   202,     0,
       0,   206,     0,     0,     0,     0,     0,   215,     0,     0,
       0,   219,     0,    54,     0,     0,   222,     4,     5,     6,
       7,     8,     9,     0,     0,     0,     0,     0,   224,   228,
       0,   229,     0,     4,     5,     6,     7,     8,     9,     0,
       0,     0,     0,     0,     0,     0,     0,    52,     0,     4,
       5,     6,     7,     8,     9,     0,   156,     0,    19,     0,
       0,     0,     0,    20,     0,     0,     0,    21,    22,    23,
       0,     0,     0,    25,    19,    26,     0,   149,     0,    20,
       0,     0,     0,    21,    22,    23,     0,     0,     0,    25,
      19,    26,     0,    53,     0,    20,     0,     0,     0,    21,
      22,    23,     0,     0,     0,    25,     0,    26,     0,    53,
       4,     5,     6,     7,     8,     9,     0,     0,     0,     0,
       0,     0,     0,     4,     5,     6,     7,     8,     9,    10,
       0,     0,     0,    11,     0,     0,    12,    13,    14,     0,
      15,     0,    16,     0,    91,    92,     0,    17,    18,     0,
       0,    19,     0,     0,     0,     0,    20,     0,     0,     0,
      21,    22,    23,     0,    19,     0,    25,     0,    26,    20,
     149,     0,     0,    21,    22,    23,     0,     0,    24,    25,
       0,    26,     4,     5,     6,     7,     8,     9,    10,     0,
       0,     0,    11,     0,     0,    12,    13,    14,     0,    15,
       0,    16,   172,     0,     0,     0,    17,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,     0,     0,     0,     0,    20,     0,
       0,     0,    21,    22,    23,     0,     0,    24,    25,     0,
      26,     4,     5,     6,     7,     8,     9,    10,     0,     0,
       0,    11,     0,     0,    12,    13,    14,   209,    15,     0,
      16,     0,     0,     0,     0,    17,    18,     0,     0,     0,
       4,     5,     6,     7,     8,     9,     0,     0,     0,     0,
       0,     0,    19,     0,     0,     0,     0,    20,     0,     0,
       0,    21,    22,    23,     0,     0,    24,    25,     0,    26,
       4,     5,     6,     7,     8,     9,    10,     0,     0,     0,
      11,    19,     0,    12,    13,    14,    20,    15,   211,    16,
      21,    22,    23,     0,    17,    18,    25,     0,    26,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    19,     0,     0,     0,     0,    20,     0,     0,     0,
      21,    22,    23,     0,     0,    24,    25,     0,    26,     4,
       5,     6,     7,     8,     9,    10,     0,     0,     0,    11,
       0,     0,    12,    13,    14,   220,    15,     0,    16,     0,
       0,     0,     0,    17,    18,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      19,     0,     0,     0,     0,    20,     0,     0,     0,    21,
      22,    23,     0,     0,    24,    25,     0,    26,     4,     5,
       6,     7,     8,     9,    10,     0,     0,     0,    11,     0,
       0,    12,    13,    14,     0,    15,   221,    16,     0,     0,
       0,     0,    17,    18,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    19,
       0,     0,     0,     0,    20,     0,     0,     0,    21,    22,
      23,     0,     0,    24,    25,     0,    26,     4,     5,     6,
       7,     8,     9,    10,     0,     0,     0,    11,     0,   226,
      12,    13,    14,     0,    15,     0,    16,     0,     0,     0,
       0,    17,    18,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    19,     0,
       0,     0,     0,    20,     0,     0,     0,    21,    22,    23,
       0,     0,    24,    25,     0,    26,     4,     5,     6,     7,
       8,     9,    10,     0,     0,     0,    11,     0,   230,    12,
      13,    14,     0,    15,     0,    16,     0,     0,     0,     0,
      17,    18,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    19,     0,     0,
       0,     0,    20,     0,     0,     0,    21,    22,    23,     0,
       0,    24,    25,     0,    26,     4,     5,     6,     7,     8,
       9,    10,     0,     0,     0,    11,     0,     0,    12,    13,
      14,     0,    15,     0,    16,     0,     0,     0,     0,    17,
      18,     4,     5,     6,     7,     8,     9,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    19,     0,     0,     0,
       0,    20,     0,     0,     0,    21,    22,    23,     0,     0,
      24,    25,     0,    26,     4,     5,     6,     7,     8,     9,
       0,     0,    19,     0,     0,     0,     0,    20,     0,     0,
       0,    21,    22,    23,     0,     0,    32,    25,     0,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    60,    19,     0,     0,     0,     0,
      20,     0,     0,     0,    21,    22,    23,     0,     0,    34,
      25,    61,    26,    62,     0,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    60,
       0,    77,    78,    79,     0,     0,     0,     0,    80,     0,
       0,     0,     0,     0,     0,     0,    61,     0,    62,     0,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    60,     0,    77,    78,    79,     0,
       0,     0,     0,    85,     0,     0,     0,     0,     0,     0,
       0,    61,     0,    62,     0,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    60,
       0,    77,    78,    79,     0,     0,     0,     0,    86,     0,
       0,     0,     0,     0,   186,     0,    61,     0,    62,     0,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    60,     0,    77,    78,    79,     0,
       0,     0,   187,     0,     0,     0,     0,     0,     0,     0,
       0,    61,     0,    62,     0,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    60,
       0,    77,    78,    79,     0,     0,     0,   214,     0,     0,
       0,     0,     0,     0,     0,     0,    61,     0,    62,     0,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    60,     0,    77,    78,    79,     0,
       0,     0,   218,     0,     0,     0,     0,     0,     0,     0,
       0,    61,     0,    62,     0,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    60,
       0,    77,    78,    79,     0,     0,   100,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,     0,    62,     0,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    60,     0,    77,    78,    79,     0,
       0,   132,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,     0,    62,     0,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    60,
       0,    77,    78,    79,     0,     0,   136,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,     0,    62,     0,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    60,     0,    77,    78,    79,     0,
       0,   138,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,     0,    62,     0,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    60,
       0,    77,    78,    79,     0,     0,   167,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,     0,    62,     0,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    60,     0,    77,    78,    79,     0,
       0,   169,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,     0,    62,     0,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    60,
       0,    77,    78,    79,     0,     0,   183,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,     0,    62,     0,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    60,     0,    77,    78,    79,     0,
       0,   185,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,     0,    62,     0,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    60,
       0,    77,    78,    79,     0,     0,   190,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,     0,    62,     0,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    60,     0,    77,    78,    79,     0,
       0,   227,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    96,    62,     0,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    60,
       0,    77,    78,    79,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,     0,    62,     0,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,   107,    60,    77,    78,    79,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    61,     0,    62,   159,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      60,     0,    77,    78,    79,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    61,   174,    62,
       0,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    60,     0,    77,    78,    79,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     189,     0,    61,     0,    62,     0,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      60,     0,    77,    78,    79,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    61,     0,    62,
       0,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    60,     0,    77,    78,    79,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    60,     0,    -1,     0,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
       0,     0,    77,    78,    79,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,     0,     0,    77,
      78,    79
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-61))

#define yytable_value_is_error(yytable_value) \
  ((yytable_value) == (-1))

static const yytype_int16 yycheck[] =
{
      16,    29,    25,     7,    12,    13,    60,    51,    52,    53,
      64,    19,    20,    21,     7,    23,    55,    25,    26,    10,
      11,    29,    30,     7,     7,     7,    53,     0,    55,    37,
       7,    39,     7,    43,    44,    45,    46,    47,    48,     7,
      33,    51,    52,    53,   104,    53,   106,    23,    24,    55,
       7,    55,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    55,
      63,    99,    14,    55,    58,    58,    92,    55,    55,    87,
      55,    89,    48,    57,   107,    51,    52,    53,    96,    58,
      98,    99,    64,    58,    55,     7,   104,    60,    56,   107,
      45,    46,    47,    48,    64,    64,    51,    52,    53,     3,
       4,     5,     6,     7,     8,     7,   132,    31,   126,    55,
     128,   129,    31,   131,    55,   133,   134,    56,     7,    30,
      62,    56,    55,   161,    56,    55,    12,    56,   173,    33,
     148,   149,   171,    -1,   152,    -1,    -1,    -1,   171,    -1,
      44,   159,   168,   161,   170,    49,    -1,    -1,    -1,    53,
      54,    55,    -1,   171,    -1,    59,   174,    61,    -1,    63,
      -1,    -1,   180,   201,    -1,   191,    -1,   193,   186,    -1,
      -1,   189,    -1,    -1,    -1,    -1,    -1,   203,    -1,    -1,
      -1,   207,    -1,   201,    -1,    -1,   212,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,   216,   225,
      -1,   227,    -1,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,     3,
       4,     5,     6,     7,     8,    -1,    26,    -1,    44,    -1,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    53,    54,    55,
      -1,    -1,    -1,    59,    44,    61,    -1,    63,    -1,    49,
      -1,    -1,    -1,    53,    54,    55,    -1,    -1,    -1,    59,
      44,    61,    -1,    63,    -1,    49,    -1,    -1,    -1,    53,
      54,    55,    -1,    -1,    -1,    59,    -1,    61,    -1,    63,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      -1,    -1,    -1,    13,    -1,    -1,    16,    17,    18,    -1,
      20,    -1,    22,    -1,    24,    25,    -1,    27,    28,    -1,
      -1,    44,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,
      53,    54,    55,    -1,    44,    -1,    59,    -1,    61,    49,
      63,    -1,    -1,    53,    54,    55,    -1,    -1,    58,    59,
      -1,    61,     3,     4,     5,     6,     7,     8,     9,    -1,
      -1,    -1,    13,    -1,    -1,    16,    17,    18,    -1,    20,
      -1,    22,    23,    -1,    -1,    -1,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,    49,    -1,
      -1,    -1,    53,    54,    55,    -1,    -1,    58,    59,    -1,
      61,     3,     4,     5,     6,     7,     8,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    17,    18,    19,    20,    -1,
      22,    -1,    -1,    -1,    -1,    27,    28,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    -1,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    53,    54,    55,    -1,    -1,    58,    59,    -1,    61,
       3,     4,     5,     6,     7,     8,     9,    -1,    -1,    -1,
      13,    44,    -1,    16,    17,    18,    49,    20,    21,    22,
      53,    54,    55,    -1,    27,    28,    59,    -1,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,
      53,    54,    55,    -1,    -1,    58,    59,    -1,    61,     3,
       4,     5,     6,     7,     8,     9,    -1,    -1,    -1,    13,
      -1,    -1,    16,    17,    18,    19,    20,    -1,    22,    -1,
      -1,    -1,    -1,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    53,
      54,    55,    -1,    -1,    58,    59,    -1,    61,     3,     4,
       5,     6,     7,     8,     9,    -1,    -1,    -1,    13,    -1,
      -1,    16,    17,    18,    -1,    20,    21,    22,    -1,    -1,
      -1,    -1,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    53,    54,
      55,    -1,    -1,    58,    59,    -1,    61,     3,     4,     5,
       6,     7,     8,     9,    -1,    -1,    -1,    13,    -1,    15,
      16,    17,    18,    -1,    20,    -1,    22,    -1,    -1,    -1,
      -1,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    53,    54,    55,
      -1,    -1,    58,    59,    -1,    61,     3,     4,     5,     6,
       7,     8,     9,    -1,    -1,    -1,    13,    -1,    15,    16,
      17,    18,    -1,    20,    -1,    22,    -1,    -1,    -1,    -1,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    53,    54,    55,    -1,
      -1,    58,    59,    -1,    61,     3,     4,     5,     6,     7,
       8,     9,    -1,    -1,    -1,    13,    -1,    -1,    16,    17,
      18,    -1,    20,    -1,    22,    -1,    -1,    -1,    -1,    27,
      28,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    53,    54,    55,    -1,    -1,
      58,    59,    -1,    61,     3,     4,     5,     6,     7,     8,
      -1,    -1,    44,    -1,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    53,    54,    55,    -1,    -1,    58,    59,    -1,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    14,    44,    -1,    -1,    -1,    -1,
      49,    -1,    -1,    -1,    53,    54,    55,    -1,    -1,    58,
      59,    31,    61,    33,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    14,
      -1,    51,    52,    53,    -1,    -1,    -1,    -1,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    14,    -1,    51,    52,    53,    -1,
      -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    33,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    14,
      -1,    51,    52,    53,    -1,    -1,    -1,    -1,    58,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    31,    -1,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    14,    -1,    51,    52,    53,    -1,
      -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    33,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    14,
      -1,    51,    52,    53,    -1,    -1,    -1,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    14,    -1,    51,    52,    53,    -1,
      -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    33,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    14,
      -1,    51,    52,    53,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    14,    -1,    51,    52,    53,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    33,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    14,
      -1,    51,    52,    53,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    14,    -1,    51,    52,    53,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    33,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    14,
      -1,    51,    52,    53,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    14,    -1,    51,    52,    53,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    33,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    14,
      -1,    51,    52,    53,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    14,    -1,    51,    52,    53,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    33,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    14,
      -1,    51,    52,    53,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    14,    -1,    51,    52,    53,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    14,
      -1,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    14,    51,    52,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      14,    -1,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    14,    -1,    51,    52,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      29,    -1,    31,    -1,    33,    -1,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      14,    -1,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    14,    -1,    51,    52,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    14,    -1,    33,    -1,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      -1,    -1,    51,    52,    53,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    -1,    -1,    51,
      52,    53
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    66,    67,     0,     3,     4,     5,     6,     7,     8,
       9,    13,    16,    17,    18,    20,    22,    27,    28,    44,
      49,    53,    54,    55,    58,    59,    61,    68,    81,    55,
      55,     7,    58,    81,    58,    81,     7,    55,     7,    55,
      67,     7,    58,     7,    58,    81,    81,    81,    86,    88,
       7,    81,    33,    63,    81,    85,    87,    89,    90,    81,
      14,    31,    33,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    51,    52,    53,
      58,    85,    87,    81,    14,    58,    58,    55,    81,    55,
      81,    24,    25,    77,    58,    58,    32,    57,    64,    55,
      56,     7,    81,    60,    64,    60,    64,    49,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,     7,    55,     7,    55,    82,
      56,    64,    56,    53,    55,    81,    56,    81,    56,     7,
      79,    80,    67,    23,    24,    81,    81,    85,    31,    63,
      81,    90,    31,     7,    63,    90,    26,    83,    87,    34,
      81,    55,    81,    81,    67,    81,    81,    56,    73,    56,
      71,    55,    23,    78,    32,    56,    81,    81,    81,     7,
      30,    84,    81,    56,    85,    56,    29,    57,    75,    29,
      56,    74,    67,    72,    67,    83,    79,    81,    81,    62,
      56,    55,    81,    10,    11,    76,    81,    69,    67,    19,
      67,    21,    56,    85,    57,    67,    55,    12,    57,    67,
      19,    21,    67,    56,    81,    70,    15,    56,    67,    67,
      15
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 115 "parser.y"
    { prog_start = (yyvsp[(1) - (1)].stmt); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 120 "parser.y"
    { (yyval.stmt) = 0; }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 122 "parser.y"
    {
		    if ((yyvsp[(1) - (2)].stmt)) {
			Stmt *tmp = (yyvsp[(1) - (2)].stmt);
			
			while (tmp->next)
			    tmp = tmp->next;
			tmp->next = (yyvsp[(2) - (2)].stmt);
			(yyval.stmt) = (yyvsp[(1) - (2)].stmt);
		    } else
			(yyval.stmt) = (yyvsp[(2) - (2)].stmt);
		}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 137 "parser.y"
    {

		    (yyval.stmt) = alloc_stmt(STMT_COND);
		    (yyval.stmt)->s.cond.arms = alloc_cond_arm((yyvsp[(3) - (8)].expr), (yyvsp[(5) - (8)].stmt));
		    (yyval.stmt)->s.cond.arms->next = (yyvsp[(6) - (8)].arm);
		    (yyval.stmt)->s.cond.otherwise = (yyvsp[(7) - (8)].stmt);
		}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 145 "parser.y"
    {
		    push_loop_name((yyvsp[(2) - (6)].string));
		}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 149 "parser.y"
    {
		    (yyval.stmt) = alloc_stmt(STMT_LIST);
		    (yyval.stmt)->s.list.id = find_id((yyvsp[(2) - (9)].string));
		    (yyval.stmt)->s.list.expr = (yyvsp[(5) - (9)].expr);
		    (yyval.stmt)->s.list.body = (yyvsp[(8) - (9)].stmt);
		    pop_loop_name();
		}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 157 "parser.y"
    {
		    push_loop_name((yyvsp[(2) - (8)].string));
		}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 161 "parser.y"
    {
		    (yyval.stmt) = alloc_stmt(STMT_RANGE);
		    (yyval.stmt)->s.range.id = find_id((yyvsp[(2) - (11)].string));
		    (yyval.stmt)->s.range.from = (yyvsp[(5) - (11)].expr);
		    (yyval.stmt)->s.range.to = (yyvsp[(7) - (11)].expr);
		    (yyval.stmt)->s.range.body = (yyvsp[(10) - (11)].stmt);
		    pop_loop_name();
		}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 170 "parser.y"
    {
		    push_loop_name(0);
		}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 174 "parser.y"
    {
		    (yyval.stmt) = alloc_stmt(STMT_WHILE);
		    (yyval.stmt)->s.loop.id = -1;
		    (yyval.stmt)->s.loop.condition = (yyvsp[(3) - (7)].expr);
		    (yyval.stmt)->s.loop.body = (yyvsp[(6) - (7)].stmt);
		    pop_loop_name();
		}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 182 "parser.y"
    {
		    push_loop_name((yyvsp[(2) - (5)].string));
		}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 186 "parser.y"
    {
		    (yyval.stmt) = alloc_stmt(STMT_WHILE);
		    (yyval.stmt)->s.loop.id = find_id((yyvsp[(2) - (8)].string));
		    (yyval.stmt)->s.loop.condition = (yyvsp[(4) - (8)].expr);
		    (yyval.stmt)->s.loop.body = (yyvsp[(7) - (8)].stmt);
		    pop_loop_name();
		}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 194 "parser.y"
    {
		    suspend_loop_scope();
		}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 198 "parser.y"
    {
		    (yyval.stmt) = alloc_stmt(STMT_FORK);
		    (yyval.stmt)->s.fork.id = -1;
		    (yyval.stmt)->s.fork.time = (yyvsp[(3) - (7)].expr);
		    (yyval.stmt)->s.fork.body = (yyvsp[(6) - (7)].stmt);
		    resume_loop_scope();
		}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 206 "parser.y"
    {
		    suspend_loop_scope();
		}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 210 "parser.y"
    {
		    (yyval.stmt) = alloc_stmt(STMT_FORK);
		    (yyval.stmt)->s.fork.id = find_id((yyvsp[(2) - (8)].string));
		    (yyval.stmt)->s.fork.time = (yyvsp[(4) - (8)].expr);
		    (yyval.stmt)->s.fork.body = (yyvsp[(7) - (8)].stmt);
		    resume_loop_scope();
		}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 218 "parser.y"
    {
		    (yyval.stmt) = alloc_stmt(STMT_EXPR);
		    (yyval.stmt)->s.expr = (yyvsp[(1) - (2)].expr);
		}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 223 "parser.y"
    {
		    check_loop_name(0, LOOP_BREAK);
		    (yyval.stmt) = alloc_stmt(STMT_BREAK);
		    (yyval.stmt)->s.exit = -1;
		}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 229 "parser.y"
    {
		    check_loop_name((yyvsp[(2) - (3)].string), LOOP_BREAK);
		    (yyval.stmt) = alloc_stmt(STMT_BREAK);
		    (yyval.stmt)->s.exit = find_id((yyvsp[(2) - (3)].string));
		}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 235 "parser.y"
    {
		    check_loop_name(0, LOOP_CONTINUE);
		    (yyval.stmt) = alloc_stmt(STMT_CONTINUE);
		    (yyval.stmt)->s.exit = -1;
		}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 241 "parser.y"
    {
		    check_loop_name((yyvsp[(2) - (3)].string), LOOP_CONTINUE);
		    (yyval.stmt) = alloc_stmt(STMT_CONTINUE);
		    (yyval.stmt)->s.exit = find_id((yyvsp[(2) - (3)].string));
		}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 247 "parser.y"
    {
		    (yyval.stmt) = alloc_stmt(STMT_RETURN);
		    (yyval.stmt)->s.expr = (yyvsp[(2) - (3)].expr);
		}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 252 "parser.y"
    {
		    (yyval.stmt) = alloc_stmt(STMT_RETURN);
		    (yyval.stmt)->s.expr = 0;
		}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 257 "parser.y"
    {
		    (yyval.stmt) = alloc_stmt(STMT_YIELD);
		    (yyval.stmt)->s.expr = (yyvsp[(2) - (3)].expr);
		}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 262 "parser.y"
    {
		    (yyval.stmt) = alloc_stmt(STMT_YIELD);
		    (yyval.stmt)->s.expr = 0;
		}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 267 "parser.y"
    { (yyval.stmt) = 0; }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 269 "parser.y"
    {
		    (yyval.stmt) = alloc_stmt(STMT_TRY_EXCEPT);
		    (yyval.stmt)->s.catch.body = (yyvsp[(2) - (4)].stmt);
		    (yyval.stmt)->s.catch.excepts = (yyvsp[(3) - (4)].except);
		}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 275 "parser.y"
    {
		    (yyval.stmt) = alloc_stmt(STMT_TRY_FINALLY);
		    (yyval.stmt)->s.finally.body = (yyvsp[(2) - (5)].stmt);
		    (yyval.stmt)->s.finally.handler = (yyvsp[(4) - (5)].stmt);
		}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 284 "parser.y"
    { (yyval.arm) = 0; }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 286 "parser.y"
    {
		    Cond_Arm *this_arm = alloc_cond_arm((yyvsp[(4) - (6)].expr), (yyvsp[(6) - (6)].stmt));
		    
		    if ((yyvsp[(1) - (6)].arm)) {
		        Cond_Arm *tmp = (yyvsp[(1) - (6)].arm);

			while (tmp->next)
			    tmp = tmp->next;
			tmp->next = this_arm;
			(yyval.arm) = (yyvsp[(1) - (6)].arm);
		    } else
			(yyval.arm) = this_arm;
		}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 303 "parser.y"
    { (yyval.stmt) = 0; }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 305 "parser.y"
    { (yyval.stmt) = (yyvsp[(2) - (2)].stmt); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 310 "parser.y"
    { (yyval.except) = (yyvsp[(2) - (2)].except); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 312 "parser.y"
    {
		    Except_Arm *tmp = (yyvsp[(1) - (2)].except);
		    int		count = 1;
		    
		    while (tmp->next) {
			tmp = tmp->next;
			count++;
		    }
		    if (!tmp->codes)
			yyerror("Unreachable EXCEPT clause");
		    else if (count > 255)
			yyerror("Too many EXCEPT clauses (max. 255)");
		}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 326 "parser.y"
    {
		    Except_Arm *tmp = (yyvsp[(1) - (4)].except);
		    
		    while (tmp->next)
			tmp = tmp->next;

		    tmp->next = (yyvsp[(4) - (4)].except);
		    (yyval.except) = (yyvsp[(1) - (4)].except);
		}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 338 "parser.y"
    { (yyval.except) = alloc_except((yyvsp[(1) - (5)].string) ? find_id((yyvsp[(1) - (5)].string)) : -1, (yyvsp[(3) - (5)].args), (yyvsp[(5) - (5)].stmt)); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 342 "parser.y"
    { (yyval.string) = 0; }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 344 "parser.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 348 "parser.y"
    {
		    (yyval.expr) = alloc_var(TYPE_INT);
		    (yyval.expr)->e.var.v.num = (yyvsp[(1) - (1)].integer);
		}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 353 "parser.y"
    {
		    (yyval.expr) = alloc_var(TYPE_FLOAT);
		    (yyval.expr)->e.var.v.fnum = (yyvsp[(1) - (1)].real);
		}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 358 "parser.y"
    {
		    (yyval.expr) = alloc_var(TYPE_STR);
		    (yyval.expr)->e.var.v.str = (yyvsp[(1) - (1)].string);
		}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 363 "parser.y"
    {
		    (yyval.expr) = alloc_var(TYPE_OBJ);
		    (yyval.expr)->e.var.v.obj = (yyvsp[(1) - (1)].object);
		}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 368 "parser.y"
    {
		    (yyval.expr) = alloc_var(TYPE_ERR);
		    (yyval.expr)->e.var.v.err = (yyvsp[(1) - (1)].error);
		}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 373 "parser.y"
    {
		    (yyval.expr) = alloc_expr(EXPR_ID);
		    (yyval.expr)->e.id = find_id((yyvsp[(1) - (1)].string));
		}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 378 "parser.y"
    {
		    /* Treat $foo like #0.("foo") */
		    Expr *obj = alloc_var(TYPE_OBJ);
		    Expr *prop = alloc_var(TYPE_STR);
		    obj->e.var.v.obj = 0;
		    prop->e.var.v.str = (yyvsp[(2) - (2)].string);
		    (yyval.expr) = alloc_binary(EXPR_PROP, obj, prop);
		}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 387 "parser.y"
    {
		    /* Treat foo.bar like foo.("bar") for simplicity */
		    Expr *prop = alloc_var(TYPE_STR);
		    prop->e.var.v.str = (yyvsp[(3) - (3)].string);
		    (yyval.expr) = alloc_binary(EXPR_PROP, (yyvsp[(1) - (3)].expr), prop);
		}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 394 "parser.y"
    {
		    (yyval.expr) = alloc_binary(EXPR_PROP, (yyvsp[(1) - (5)].expr), (yyvsp[(4) - (5)].expr));
		}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 398 "parser.y"
    {
		    /* treat foo:bar(args) like foo:("bar")(args) */
		    Expr *verb = alloc_var(TYPE_STR);
		    verb->e.var.v.str = (yyvsp[(3) - (6)].string);
		    (yyval.expr) = alloc_verb((yyvsp[(1) - (6)].expr), verb, (yyvsp[(5) - (6)].args));
		}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 405 "parser.y"
    {
		    /* treat $bar(args) like #0:("bar")(args) */
		    Expr *obj = alloc_var(TYPE_OBJ);
		    Expr *verb = alloc_var(TYPE_STR);
		    obj->e.var.v.obj = 0;
		    verb->e.var.v.str = (yyvsp[(2) - (5)].string);
		    (yyval.expr) = alloc_verb(obj, verb, (yyvsp[(4) - (5)].args));
		}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 414 "parser.y"
    {
		    (yyval.expr) = alloc_verb((yyvsp[(1) - (8)].expr), (yyvsp[(4) - (8)].expr), (yyvsp[(7) - (8)].args));
		}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 418 "parser.y"
    {
		    dollars_ok--;
		    (yyval.expr) = alloc_binary(EXPR_INDEX, (yyvsp[(1) - (5)].expr), (yyvsp[(4) - (5)].expr));
		}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 423 "parser.y"
    {
		    dollars_ok--;
		    (yyval.expr) = alloc_expr(EXPR_RANGE);
		    (yyval.expr)->e.range.base = (yyvsp[(1) - (7)].expr);
		    (yyval.expr)->e.range.from = (yyvsp[(4) - (7)].expr);
		    (yyval.expr)->e.range.to = (yyvsp[(6) - (7)].expr);
		}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 431 "parser.y"
    {
		    if (!dollars_ok)
			yyerror("Illegal context for `$' expression.");
		    (yyval.expr) = alloc_expr(EXPR_LENGTH);
		}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 437 "parser.y"
    {
		    Expr *e = (yyvsp[(1) - (3)].expr);

		    if (e->kind == EXPR_LIST) {
			e->kind = EXPR_SCATTER;
			if (e->e.list) {
			    e->e.scatter = scatter_from_arglist(e->e.list);
			    vet_scatter(e->e.scatter);
			} else
			    yyerror("Empty list in scattering assignment.");
		    } else {
			if (e->kind == EXPR_RANGE)
			    e = e->e.range.base;
			while (e->kind == EXPR_INDEX)
			    e = e->e.bin.lhs;
			if (e->kind != EXPR_ID  &&  e->kind != EXPR_PROP)
			    yyerror("Illegal expression on left side of"
				    " assignment.");
		    }
		    (yyval.expr) = alloc_binary(EXPR_ASGN, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
	        }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 459 "parser.y"
    {
		    Expr       *e = alloc_expr(EXPR_SCATTER);

		    e->e.scatter = (yyvsp[(2) - (5)].scatter);
		    vet_scatter((yyvsp[(2) - (5)].scatter));
		    (yyval.expr) = alloc_binary(EXPR_ASGN, e, (yyvsp[(5) - (5)].expr));
		}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 467 "parser.y"
    {
		    unsigned f_no;

		    (yyval.expr) = alloc_expr(EXPR_CALL);
		    if ((f_no = number_func_by_name((yyvsp[(1) - (4)].string))) == FUNC_NOT_FOUND) {
			/* Replace with call_function("$1", @args) */
			Expr	       *fname = alloc_var(TYPE_STR);
			Arg_List       *a = alloc_arg_list(ARG_NORMAL, fname);

			fname->e.var.v.str = (yyvsp[(1) - (4)].string);
			a->next = (yyvsp[(3) - (4)].args);
			warning("Unknown built-in function: ", (yyvsp[(1) - (4)].string));
			(yyval.expr)->e.call.func = number_func_by_name("call_function");
			(yyval.expr)->e.call.args = a;
		    } else {
			(yyval.expr)->e.call.func = f_no;
			(yyval.expr)->e.call.args = (yyvsp[(3) - (4)].args);
			dealloc_string((yyvsp[(1) - (4)].string));
		    }
		}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 488 "parser.y"
    {
		    (yyval.expr) = alloc_binary(EXPR_PLUS, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
		}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 492 "parser.y"
    {
		    (yyval.expr) = alloc_binary(EXPR_MINUS, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
		}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 496 "parser.y"
    {
		    (yyval.expr) = alloc_binary(EXPR_TIMES, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
		}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 500 "parser.y"
    {
		    (yyval.expr) = alloc_binary(EXPR_DIVIDE, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
		}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 504 "parser.y"
    {
		    (yyval.expr) = alloc_binary(EXPR_MOD, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
		}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 508 "parser.y"
    {
		    (yyval.expr) = alloc_binary(EXPR_EXP, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
		}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 512 "parser.y"
    {
		    (yyval.expr) = alloc_binary(EXPR_AND, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
		}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 516 "parser.y"
    {
		    (yyval.expr) = alloc_binary(EXPR_OR, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
		}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 520 "parser.y"
    {
		    (yyval.expr) = alloc_binary(EXPR_EQ, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
		}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 524 "parser.y"
    {
		    (yyval.expr) = alloc_binary(EXPR_NE, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
		}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 528 "parser.y"
    {
		    (yyval.expr) = alloc_binary(EXPR_LT, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
		}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 532 "parser.y"
    {
		    (yyval.expr) = alloc_binary(EXPR_LE, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
		}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 536 "parser.y"
    {
		    (yyval.expr) = alloc_binary(EXPR_GT, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
		}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 540 "parser.y"
    {
		    (yyval.expr) = alloc_binary(EXPR_GE, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
		}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 544 "parser.y"
    {
		    (yyval.expr) = alloc_binary(EXPR_IN, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
		}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 548 "parser.y"
    {
		    if ((yyvsp[(2) - (2)].expr)->kind == EXPR_VAR
			&& ((yyvsp[(2) - (2)].expr)->e.var.type == TYPE_INT
			    || (yyvsp[(2) - (2)].expr)->e.var.type == TYPE_FLOAT)) {
			switch ((yyvsp[(2) - (2)].expr)->e.var.type) {
			  case TYPE_INT:
			    (yyvsp[(2) - (2)].expr)->e.var.v.num = -(yyvsp[(2) - (2)].expr)->e.var.v.num;
			    break;
			  case TYPE_FLOAT:
			    *((yyvsp[(2) - (2)].expr)->e.var.v.fnum) = - (*((yyvsp[(2) - (2)].expr)->e.var.v.fnum));
			    break;
			  default:
			    break;
			}
		        (yyval.expr) = (yyvsp[(2) - (2)].expr);
		    } else {
			(yyval.expr) = alloc_expr(EXPR_NEGATE);
			(yyval.expr)->e.expr = (yyvsp[(2) - (2)].expr);
		    }
		}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 569 "parser.y"
    {
		    (yyval.expr) = alloc_expr(EXPR_NOT);
		    (yyval.expr)->e.expr = (yyvsp[(2) - (2)].expr);
		}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 574 "parser.y"
    { (yyval.expr) = (yyvsp[(2) - (3)].expr); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 576 "parser.y"
    {
		    (yyval.expr) = alloc_expr(EXPR_LIST);
		    (yyval.expr)->e.list = (yyvsp[(2) - (3)].args);
		}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 581 "parser.y"
    {
		    (yyval.expr) = alloc_expr(EXPR_HASH);
		    (yyval.expr)->e.list = (yyvsp[(2) - (3)].args);
		}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 586 "parser.y"
    {
		    (yyval.expr) = alloc_expr(EXPR_COND);
		    (yyval.expr)->e.cond.condition = (yyvsp[(1) - (5)].expr);
		    (yyval.expr)->e.cond.consequent = (yyvsp[(3) - (5)].expr);
		    (yyval.expr)->e.cond.alternate = (yyvsp[(5) - (5)].expr);
		}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 593 "parser.y"
    {
		    (yyval.expr) = alloc_expr(EXPR_CATCH);
		    (yyval.expr)->e.catch.try = (yyvsp[(2) - (6)].expr);
		    (yyval.expr)->e.catch.codes = (yyvsp[(4) - (6)].args);
		    (yyval.expr)->e.catch.except = (yyvsp[(5) - (6)].expr);
		}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 603 "parser.y"
    { dollars_ok++; }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 607 "parser.y"
    { (yyval.args) = 0; }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 609 "parser.y"
    { (yyval.args) = (yyvsp[(1) - (1)].args); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 613 "parser.y"
    { (yyval.expr) = 0; }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 615 "parser.y"
    { (yyval.expr) = (yyvsp[(2) - (2)].expr); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 619 "parser.y"
    { (yyval.args) = 0; }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 621 "parser.y"
    { (yyval.args) = (yyvsp[(1) - (1)].args); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 626 "parser.y"
    { (yyval.args) = 0; }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 628 "parser.y"
    { (yyval.args) = (yyvsp[(1) - (1)].args); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 633 "parser.y"
    { (yyval.args) = alloc_arg_list(ARG_NORMAL, (yyvsp[(1) - (1)].expr)); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 635 "parser.y"
    { (yyval.args) = alloc_arg_list(ARG_SPLICE, (yyvsp[(2) - (2)].expr)); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 637 "parser.y"
    {
		    Arg_List *this_arg = alloc_arg_list(ARG_NORMAL, (yyvsp[(3) - (3)].expr));

		    if ((yyvsp[(1) - (3)].args)) {
			Arg_List *tmp = (yyvsp[(1) - (3)].args);

			while (tmp->next)
			    tmp = tmp->next;
			tmp->next = this_arg;
			(yyval.args) = (yyvsp[(1) - (3)].args);
		    } else
			(yyval.args) = this_arg;
		}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 651 "parser.y"
    {
		    Arg_List *this_arg = alloc_arg_list(ARG_SPLICE, (yyvsp[(4) - (4)].expr));

		    if ((yyvsp[(1) - (4)].args)) {
			Arg_List *tmp = (yyvsp[(1) - (4)].args);

			while (tmp->next)
			    tmp = tmp->next;
			tmp->next = this_arg;
			(yyval.args) = (yyvsp[(1) - (4)].args);
		    } else
			(yyval.args) = this_arg;
		}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 668 "parser.y"
    {
		Expr *e = alloc_binary(EXPR_HASHENTRY, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
		(yyval.args) = alloc_arg_list(ARG_NORMAL, e);
	    }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 673 "parser.y"
    {
		Expr *e = alloc_binary(EXPR_HASHENTRY, (yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].expr));
		Arg_List *this_arg = alloc_arg_list(ARG_NORMAL, e);

		if ((yyvsp[(1) - (5)].args)) {
		    Arg_List *tmp = (yyvsp[(1) - (5)].args);

		    while (tmp->next)
			tmp = tmp->next;
		    tmp->next = this_arg;
		    (yyval.args) = (yyvsp[(1) - (5)].args);
		} else
		     (yyval.args) = this_arg;
	    }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 691 "parser.y"
    {
		    Scatter    *sc = scatter_from_arglist((yyvsp[(1) - (3)].args));

		    if (sc)
			(yyval.scatter) = add_scatter_item(sc, (yyvsp[(3) - (3)].scatter));
		    else
			(yyval.scatter) = (yyvsp[(3) - (3)].scatter);
		}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 700 "parser.y"
    {
		    (yyval.scatter) = add_scatter_item((yyvsp[(1) - (3)].scatter), (yyvsp[(3) - (3)].scatter));
		}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 704 "parser.y"
    {
		    (yyval.scatter) = add_scatter_item((yyvsp[(1) - (3)].scatter), alloc_scatter(SCAT_REQUIRED,
							    find_id((yyvsp[(3) - (3)].string)), 0));
		}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 709 "parser.y"
    {
		    (yyval.scatter) = add_scatter_item((yyvsp[(1) - (4)].scatter), alloc_scatter(SCAT_REST,
							    find_id((yyvsp[(4) - (4)].string)), 0));
		}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 714 "parser.y"
    {   (yyval.scatter) = (yyvsp[(1) - (1)].scatter);  }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 719 "parser.y"
    {
		    (yyval.scatter) = alloc_scatter(SCAT_OPTIONAL, find_id((yyvsp[(2) - (2)].string)), 0);
		}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 723 "parser.y"
    {
		    (yyval.scatter) = alloc_scatter(SCAT_OPTIONAL, find_id((yyvsp[(2) - (4)].string)), (yyvsp[(4) - (4)].expr));
		}
    break;



/* Line 1806 of yacc.c  */
#line 3067 "y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 728 "parser.y"


static int		lineno, nerrors, must_rename_keywords;
static Parser_Client	client;
static void	       *client_data;
static Names	       *local_names;

static int
find_id(char *name)
{
    int slot = find_or_add_name(&local_names, name);

    dealloc_string(name);
    return slot;
}

static void
yyerror(const char *s)
{
    error(s, 0);
}

static const char *
fmt_error(const char *s, const char *t)
{
    static Stream      *str = 0;

    if (str == 0)
	str = new_stream(100);
    if (t)
	stream_printf(str, "Line %d:  %s%s", lineno, s, t);
    else
	stream_printf(str, "Line %d:  %s", lineno, s);
    return reset_stream(str);
}

static void
error(const char *s, const char *t)
{
    nerrors++;
    (*(client.error))(client_data, fmt_error(s, t));
}

static void
warning(const char *s, const char *t)
{
    if (client.warning)
	(*(client.warning))(client_data, fmt_error(s, t));
    else
	error(s, t);
}

static int unget_buffer[5], unget_count;

static int
lex_getc(void)
{
    if (unget_count > 0)
	return unget_buffer[--unget_count];
    else
	return (*(client.getch))(client_data);
}

static void
lex_ungetc(int c)
{
    unget_buffer[unget_count++] = c;
}

static int
follow(int expect, int ifyes, int ifno)     /* look ahead for >=, etc. */
{
    int c = lex_getc();

    if (c == expect)
        return ifyes;
    lex_ungetc(c);
    return ifno;
}

static Stream  *token_stream = 0;

static int
yylex(void)
{
    int		c;

    reset_stream(token_stream);

start_over:

    do {
	c = lex_getc();
	if (c == '\n') lineno++;
    } while (isspace(c));

    if (c == '/') {
	c = lex_getc();
	if (c == '*') {
	    for (;;) {
		c = lex_getc();
		if (c == '*') {
		    c = lex_getc();
		    if (c == '/')
			goto start_over;
		}
		if (c == EOF) {
		    yyerror("End of program while in a comment");
		    return c;
		}
	    }
	} else {
	    lex_ungetc(c);
	    return '/';
	}
    }

    if (c == '#') {
	int            negative = 0;
	Objid          oid = 0;

	c = lex_getc();
	if (c == '-') {
	    negative = 1;
	    c = lex_getc();
	}
	if (!isdigit(c)) {
	    yyerror("Malformed object number");
	    lex_ungetc(c);
	    return 0;
	}
	do {
	    oid = oid * 10 + (c - '0');
	    c = lex_getc();
	} while (isdigit(c));
	lex_ungetc(c);

	yylval.object = negative ? -oid : oid;
	return tOBJECT;
    }

    if (isdigit(c) || (c == '.'  &&  language_version >= DBV_Float)) {
	int	n = 0;
	int	type = tINTEGER;

	while (isdigit(c)) {
	    n = n * 10 + (c - '0');
	    stream_add_char(token_stream, c);
	    c = lex_getc();
	}

	if (language_version >= DBV_Float && c == '.') {
	    /* maybe floating-point (but maybe `..') */
	    int cc;

	    lex_ungetc(cc = lex_getc()); /* peek ahead */
	    if (isdigit(cc)) {	/* definitely floating-point */
		type = tFLOAT;
		do {
		    stream_add_char(token_stream, c);
		    c = lex_getc();
		} while (isdigit(c));
	    } else if (stream_length(token_stream) == 0)
		/* no digits before or after `.'; not a number at all */
		goto normal_dot;
	    else if (cc != '.') {
		/* Some digits before dot, not `..' */
		type = tFLOAT;
		stream_add_char(token_stream, c);
		c = lex_getc();
	    }
	}

	if (language_version >= DBV_Float && (c == 'e' || c == 'E')) {
	    /* better be an exponent */
	    type = tFLOAT;
	    stream_add_char(token_stream, c);
	    c = lex_getc();
	    if (c == '+' || c == '-') {
		stream_add_char(token_stream, c);
		c = lex_getc();
	    }
	    if (!isdigit(c)) {
		yyerror("Malformed floating-point literal");
		lex_ungetc(c);
		return 0;
	    }
	    do {
		stream_add_char(token_stream, c);
		c = lex_getc();
	    } while (isdigit(c));
	}
	
	lex_ungetc(c);

	if (type == tINTEGER)
	    yylval.integer = n;
	else {
	    double	d;
	    
	    d = strtod(reset_stream(token_stream), 0);
	    if (!IS_REAL(d)) {
		yyerror("Floating-point literal out of range");
		d = 0.0;
	    }
	    yylval.real = alloc_float(d);
	}
	return type;
    }
    
    if (isalpha(c) || c == '_') {
	char	       *buf;
	Keyword	       *k;

	stream_add_char(token_stream, c);
	while (isalnum(c = lex_getc()) || c == '_')
	    stream_add_char(token_stream, c);
	lex_ungetc(c);
	buf = reset_stream(token_stream);

	k = find_keyword(buf);
	if (k) {
	    if (k->version <= language_version) {
		int	t = k->token;

		if (t == tERROR)
		    yylval.error = k->error;
		return t;
	    } else {		/* New keyword being used as an identifier */
		if (!must_rename_keywords)
		    warning("Renaming old use of new keyword: ", buf);
		must_rename_keywords = 1;
	    }
	}
	
	yylval.string = alloc_string(buf);
	return tID;
    }

    if (c == '"') {
	while(1) {
	    c = lex_getc();
	    if (c == '"')
		break;
	    if (c == '\\')
		c = lex_getc();
	    if (c == '\n' || c == EOF) {
		yyerror("Missing quote");
		break;
	    }
	    stream_add_char(token_stream, c);
	}
	yylval.string = alloc_string(reset_stream(token_stream));
	return tSTRING;
    }

    switch(c) {
      case '>':         return follow('=', tGE, '>');
      case '<':         return follow('=', tLE, '<');
      case '=':         return ((c = follow('=', tEQ, 0))
				? c
				: follow('>', tARROW, '='));
      case '!':         return follow('=', tNE, '!');
      case '|':         return follow('|', tOR, '|');
      case '&':         return follow('&', tAND, '&');
      case '-':         return follow('>', tHASHARROW, '-');
      normal_dot:
      case '.':		return follow('.', tTO, '.');
      default:          return c;
    }
}

static Scatter *
add_scatter_item(Scatter *first, Scatter *last)
{
    Scatter    *tmp = first;

    while (tmp->next)
	tmp = tmp->next;
    tmp->next = last;

    return first;
}

static Scatter *
scatter_from_arglist(Arg_List *a)
{
    Scatter    *sc = 0, **scp;
    Arg_List   *anext;

    for (scp = &sc; a; a = anext, scp = &((*scp)->next)) {
	if (a->expr->kind == EXPR_ID) {
	    *scp = alloc_scatter(a->kind == ARG_NORMAL ? SCAT_REQUIRED
						       : SCAT_REST,
				 a->expr->e.id, 0);
	    anext = a->next;
	    dealloc_node(a->expr);
	    dealloc_node(a);
	} else {
	    yyerror("Scattering assignment targets must be simple variables.");
	    return 0;
	}
    }

    return sc;
}

static void
vet_scatter(Scatter *sc)
{
    int	seen_rest = 0, count = 0;

    for (; sc; sc = sc->next) {
	if (sc->kind == SCAT_REST) {
	    if (seen_rest)
		yyerror("More than one `@' target in scattering assignment.");
	    else
		seen_rest = 1;
	}
	count++;
    }

    if (count > 255)
	yyerror("Too many targets in scattering assignment.");
}

struct loop_entry {
    struct loop_entry  *next;
    const char	       *name;
    int			is_barrier;
};

static struct loop_entry *loop_stack;

static void
push_loop_name(const char *name)
{
    struct loop_entry  *entry = mymalloc(sizeof(struct loop_entry), M_AST);

    entry->next = loop_stack;
    entry->name = (name ? str_dup(name) : 0);
    entry->is_barrier = 0;
    loop_stack = entry;
}

static void
pop_loop_name(void)
{
    if (!loop_stack)
	errlog("PARSER: Empty loop stack in POP_LOOP_NAME!\n");
    else if (loop_stack->is_barrier)
	errlog("PARSER: Tried to pop loop-scope barrier!\n");
    else {
	struct loop_entry      *entry = loop_stack;

	loop_stack = loop_stack->next;
	if (entry->name)
	    free_str(entry->name);
	myfree(entry, M_AST);
    }
}

static void
suspend_loop_scope(void)
{
    struct loop_entry  *entry = mymalloc(sizeof(struct loop_entry), M_AST);

    entry->next = loop_stack;
    entry->name = 0;
    entry->is_barrier = 1;
    loop_stack = entry;
}

static void
resume_loop_scope(void)
{
    if (!loop_stack)
	errlog("PARSER: Empty loop stack in RESUME_LOOP_SCOPE!\n");
    else if (!loop_stack->is_barrier)
	errlog("PARSER: Tried to resume non-loop-scope barrier!\n");
    else {
	struct loop_entry      *entry = loop_stack;

	loop_stack = loop_stack->next;
	myfree(entry, M_AST);
    }
}

static void
check_loop_name(const char *name, enum loop_exit_kind kind)
{
    struct loop_entry  *entry;

    if (!name) {
	if (!loop_stack  ||  loop_stack->is_barrier) {
	    if (kind == LOOP_BREAK)
		yyerror("No enclosing loop for `break' statement");
	    else
		yyerror("No enclosing loop for `continue' statement");
	}
	return;
    }
    
    for (entry = loop_stack; entry && !entry->is_barrier; entry = entry->next)
	if (entry->name  &&  mystrcasecmp(entry->name, name) == 0)
	    return;

    if (kind == LOOP_BREAK)
	error("Invalid loop name in `break' statement: ", name);
    else
	error("Invalid loop name in `continue' statement: ", name);
}

Program *
parse_program(DB_Version version, Parser_Client c, void *data)
{
    extern int	yyparse();
    Program    *prog;
    
    if (token_stream == 0)
	token_stream = new_stream(1024);
    unget_count = 0;
    nerrors = 0;
    must_rename_keywords = 0;
    lineno = 1;
    client = c;
    client_data = data;
    local_names = new_builtin_names(version);
    dollars_ok = 0;
    loop_stack = 0;
    language_version = version;
    
    begin_code_allocation();
    yyparse();
    end_code_allocation(nerrors > 0);
    if (loop_stack) {
	if (nerrors == 0)
	    errlog("PARSER: Non-empty loop-scope stack!\n");
	while (loop_stack) {
	    struct loop_entry *entry = loop_stack;

	    loop_stack = loop_stack->next;
	    if (entry->name)
		free_str(entry->name);
	    myfree(entry, M_AST);
	}
    }
    
    if (nerrors == 0) {
	if (must_rename_keywords) {
	    /* One or more new keywords were used as identifiers in this code,
	     * possibly as local variable names (but maybe only as property or
	     * verb names).  Such local variables must be renamed to avoid a
	     * conflict in the new world.  We just add underscores to the end
	     * until it stops conflicting with any other local variable.
	     */
	    unsigned i;

	    for (i = first_user_slot(version); i < local_names->size; i++) {
		const char	*name = local_names->names[i];
	    
		if (find_keyword(name)) { /* Got one... */
		    stream_add_string(token_stream, name);
		    do {
			stream_add_char(token_stream, '_');
		    } while (find_name(local_names,
				       stream_contents(token_stream)) >= 0);
		    free_str(name);
		    local_names->names[i] =
			str_dup(reset_stream(token_stream));
		}
	    }
	}

	prog = generate_code(prog_start, version);
	prog->num_var_names = local_names->size;
	prog->var_names = local_names->names;

	myfree(local_names, M_NAMES);
	free_stmt(prog_start);

	return prog;
    } else {
	free_names(local_names);
	return 0;
    }
}

struct parser_state {
    Var		code;		/* a list of strings */
    int		cur_string;	/* which string? */
    int		cur_char;	/* which character in that string? */
    Var		errors;		/* a list of strings */
};

static void
my_error(void *data, const char *msg)
{
    struct parser_state	*state = (struct parser_state *) data;
    Var			v;
    
    v.type = TYPE_STR;
    v.v.str = str_dup(msg);
    state->errors = listappend(state->errors, v);
}

static int
my_getc(void *data)
{
    struct parser_state	*state = (struct parser_state *) data;
    Var			code;
    char		c;
    
    code = state->code;
    if (task_timed_out  ||  state->cur_string > code.v.list[0].v.num)
	return EOF;
    else if (!(c = code.v.list[state->cur_string].v.str[state->cur_char])) {
	state->cur_string++;
	state->cur_char = 0;
	return '\n';
    } else {
	state->cur_char++;
	return c;
    }
}

static Parser_Client list_parser_client = { my_error, 0, my_getc };

Program *
parse_list_as_program(Var code, Var *errors)
{
    struct parser_state	state;
    Program	       *program;
    
    state.code = code;
    state.cur_string = 1;
    state.cur_char = 0;
    state.errors = new_list(0);
    program = parse_program(current_version, list_parser_client, &state);
    *errors = state.errors;

    return program;
}

char rcsid_parser[] = "$Id: parser.y,v 1.5 2009/03/27 21:29:34 blacklite Exp $";

/* 
 * $Log: parser.y,v $
 * Revision 1.5  2009/03/27 21:29:34  blacklite
 * add optional arg to yield statement -- should have been checked in earlier with other yield changes
 *
 * Revision 1.4  2009/03/08 12:41:31  blacklite
 * Added HASH data type, yield keyword, MEMORY_TRACE, vfscanf(),
 * extra myrealloc() and memcpy() tricks for lists, Valgrind
 * support for str_intern.c, etc. See ChangeLog.txt.
 *
 * Revision 1.3  2007/09/12 07:33:29  spunky
 * This is a working version of the current HellMOO server
 *
 * Revision 1.2  1998/12/14 13:18:45  nop
 * Merge UNSAFE_OPTS (ref fixups); fix Log tag placement to fit CVS whims
 *
 * Revision 1.1.1.1  1997/03/03 03:45:02  nop
 * LambdaMOO 1.8.0p5
 *
 * Revision 2.11  1996/05/12  21:28:37  pavel
 * Removed non-backward-compatible parse error for negating a non-numeric
 * literal.  Made certain aspects of floating-point literal parsing be
 * language-version-dependent, to maintain backward compatibility with DBs
 * written by pre-float servers.  Release 1.8.0p5.
 *
 * Revision 2.10  1996/04/19  01:26:38  pavel
 * Fixed potential memory smash when `$' expression occurs in an illegal
 * context.  Release 1.8.0p4.
 *
 * Revision 2.9  1996/03/10  01:08:01  pavel
 * Removed bogus `call_function("foo", ...)' --> `foo(...)' conversion.
 * Fixed line numbers of renamed-variable warnings.  Release 1.8.0.
 *
 * Revision 2.8  1996/02/18  23:14:54  pavel
 * Liberalized parsing of floating-point numbers to accept `3.' and `3.e1'.
 * Changed parsing to replace call_function("foo", @args) with foo(@args) if
 * foo is a known function.  Release 1.8.0beta3.
 *
 * Revision 2.7  1996/02/11  00:46:01  pavel
 * Liberalized parsing of floating-point literals to accept `.02' and the
 * like.  Fixed a bug where `1E6' and the like would be parsed as an integer.
 * Release 1.8.0beta2.
 *
 * Revision 2.6  1996/02/08  06:32:48  pavel
 * Added support for floating-point literals, exponentiation expression, named
 * WHILE loops, and BREAK and CONTINUE statements.  Generalized support for
 * version-dependent compilation.  Renamed TYPE_NUM to TYPE_INT.  Removed use
 * of ungetch() method on Parser_Client.  Updated copyright notice for 1996.
 * Release 1.8.0beta1.
 *
 * Revision 2.5  1996/01/16  07:17:05  pavel
 * Add support for scattering assignment.  Release 1.8.0alpha6.
 *
 * Revision 2.4  1996/01/11  07:50:49  pavel
 * Added missing #include "my-string.h".  Release 1.8.0alpha5.
 *
 * Revision 2.3  1995/12/31  00:09:40  pavel
 * Removed unused tokens tRAISE and tFORLIST (huh?).  Added `$' expression.
 * Release 1.8.0alpha4.
 *
 * Revision 2.2  1995/12/28  00:43:25  pavel
 * Added some support for MOO-compilation warnings.  Changed `unknown built-in
 * function' error into a warning with recovery.  Changed identifier-renaming
 * log message into a warning.  Release 1.8.0alpha3.
 *
 * Revision 2.1  1995/12/11  08:01:26  pavel
 * Added support for `$foo(...)' syntax.  Release 1.8.0alpha2.
 *
 * Revision 2.0  1995/11/30  04:48:11  pavel
 * New baseline version, corresponding to release 1.8.0alpha1.
 *
 * Revision 1.13  1992/10/23  23:03:47  pavel
 * Added copyright notice.
 *
 * Revision 1.12  1992/10/23  22:21:43  pavel
 * Eliminated all uses of the useless macro NULL.
 *
 * Revision 1.11  1992/10/21  03:02:35  pavel
 * Converted to use new automatic configuration system.
 *
 * Revision 1.10  1992/08/31  22:25:51  pjames
 * Changed some `char *'s to `const char *'
 * 
 * Revision 1.9  1992/08/28  23:18:38  pjames
 * Added ASGN_RANGE parsing code.  Fixed tiny memory leak.
 * 
 * Revision 1.8  1992/08/28  16:16:52  pjames
 * Changed `ak_dealloc_string()' to `free_str()'.
 * 
 * Revision 1.7  1992/08/12  01:49:58  pjames
 * Negative literals are now accepted (instead of negated positive literals).
 * 
 * Revision 1.6  1992/08/10  16:55:59  pjames
 * Updated #includes.
 * 
 * Revision 1.5  1992/07/30  21:22:08  pjames
 * Removed max_stack calculations (moved to vector.c).
 * 
 * Revision 1.4  1992/07/29  18:05:12  pjames
 * $$ no longer = NULL when there is an illegal left hand side of an
 * expression.
 * 
 * Revision 1.3  1992/07/27  18:12:41  pjames
 * Changed name of ct_env to var_names and const_env to literals.
 * Modified call to vectorize to use new argument format.
 * Assignment statements now check left hand side properly for allowable
 * expressions, and now frees memory from reused expressions.
 * 
 * Revision 1.2  1992/07/21  00:05:16  pavel
 * Added rcsid_<filename-root> declaration to hold the RCS ident. string.
 * 
 * Revision 1.1  1992/07/20  23:23:12  pavel
 * Initial RCS-controlled version.
 */

