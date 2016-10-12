
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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

/* Line 1676 of yacc.c  */
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



/* Line 1676 of yacc.c  */
#line 144 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


