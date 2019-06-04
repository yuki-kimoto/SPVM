/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     PACKAGE = 258,
     HAS = 259,
     SUB = 260,
     OUR = 261,
     ENUM = 262,
     MY = 263,
     SELF = 264,
     USE = 265,
     REQUIRE = 266,
     ALLOW = 267,
     DESCRIPTOR = 268,
     IF = 269,
     UNLESS = 270,
     ELSIF = 271,
     ELSE = 272,
     FOR = 273,
     WHILE = 274,
     LAST = 275,
     NEXT = 276,
     SWITCH = 277,
     CASE = 278,
     DEFAULT = 279,
     BREAK = 280,
     EVAL = 281,
     NAME = 282,
     VAR_NAME = 283,
     CONSTANT = 284,
     EXCEPTION_VAR = 285,
     UNDEF = 286,
     VOID = 287,
     BYTE = 288,
     SHORT = 289,
     INT = 290,
     LONG = 291,
     FLOAT = 292,
     DOUBLE = 293,
     STRING = 294,
     OBJECT = 295,
     DOT3 = 296,
     FATCAMMA = 297,
     RW = 298,
     RO = 299,
     WO = 300,
     BEGIN = 301,
     NEW = 302,
     RETURN = 303,
     WEAKEN = 304,
     DIE = 305,
     CURRENT_PACKAGE = 306,
     UNWEAKEN = 307,
     SPECIAL_ASSIGN = 308,
     ASSIGN = 309,
     LOGICAL_OR = 310,
     LOGICAL_AND = 311,
     BIT_XOR = 312,
     BIT_OR = 313,
     STRNE = 314,
     STREQ = 315,
     NUMNE = 316,
     NUMEQ = 317,
     ISA = 318,
     STRLE = 319,
     STRLT = 320,
     STRGE = 321,
     STRGT = 322,
     NUMLE = 323,
     NUMLT = 324,
     NUMGE = 325,
     NUMGT = 326,
     SHIFT = 327,
     REMAINDER = 328,
     DIVIDE = 329,
     MULTIPLY = 330,
     REFCNT = 331,
     ISWEAK = 332,
     LENGTH = 333,
     SCALAR = 334,
     CONVERT = 335,
     MINUS = 336,
     PLUS = 337,
     DEREF = 338,
     REF = 339,
     BIT_NOT = 340,
     LOGICAL_NOT = 341,
     DEC = 342,
     INC = 343,
     ARROW = 344
   };
#endif
/* Tokens.  */
#define PACKAGE 258
#define HAS 259
#define SUB 260
#define OUR 261
#define ENUM 262
#define MY 263
#define SELF 264
#define USE 265
#define REQUIRE 266
#define ALLOW 267
#define DESCRIPTOR 268
#define IF 269
#define UNLESS 270
#define ELSIF 271
#define ELSE 272
#define FOR 273
#define WHILE 274
#define LAST 275
#define NEXT 276
#define SWITCH 277
#define CASE 278
#define DEFAULT 279
#define BREAK 280
#define EVAL 281
#define NAME 282
#define VAR_NAME 283
#define CONSTANT 284
#define EXCEPTION_VAR 285
#define UNDEF 286
#define VOID 287
#define BYTE 288
#define SHORT 289
#define INT 290
#define LONG 291
#define FLOAT 292
#define DOUBLE 293
#define STRING 294
#define OBJECT 295
#define DOT3 296
#define FATCAMMA 297
#define RW 298
#define RO 299
#define WO 300
#define BEGIN 301
#define NEW 302
#define RETURN 303
#define WEAKEN 304
#define DIE 305
#define CURRENT_PACKAGE 306
#define UNWEAKEN 307
#define SPECIAL_ASSIGN 308
#define ASSIGN 309
#define LOGICAL_OR 310
#define LOGICAL_AND 311
#define BIT_XOR 312
#define BIT_OR 313
#define STRNE 314
#define STREQ 315
#define NUMNE 316
#define NUMEQ 317
#define ISA 318
#define STRLE 319
#define STRLT 320
#define STRGE 321
#define STRGT 322
#define NUMLE 323
#define NUMLT 324
#define NUMGE 325
#define NUMGT 326
#define SHIFT 327
#define REMAINDER 328
#define DIVIDE 329
#define MULTIPLY 330
#define REFCNT 331
#define ISWEAK 332
#define LENGTH 333
#define SCALAR 334
#define CONVERT 335
#define MINUS 336
#define PLUS 337
#define DEREF 338
#define REF 339
#define BIT_NOT 340
#define LOGICAL_NOT 341
#define DEC 342
#define INC 343
#define ARROW 344




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



