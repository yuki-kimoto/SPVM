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
     DESCRIPTOR = 267,
     IF = 268,
     UNLESS = 269,
     ELSIF = 270,
     ELSE = 271,
     FOR = 272,
     WHILE = 273,
     LAST = 274,
     NEXT = 275,
     SWITCH = 276,
     CASE = 277,
     DEFAULT = 278,
     EVAL = 279,
     NAME = 280,
     VAR_NAME = 281,
     CONSTANT = 282,
     PACKAGE_VAR_NAME = 283,
     EXCEPTION_VAR = 284,
     UNDEF = 285,
     VOID = 286,
     BYTE = 287,
     SHORT = 288,
     INT = 289,
     LONG = 290,
     FLOAT = 291,
     DOUBLE = 292,
     STRING = 293,
     OBJECT = 294,
     DOT3 = 295,
     FATCAMMA = 296,
     RW = 297,
     RO = 298,
     WO = 299,
     BEGIN = 300,
     NEW = 301,
     RETURN = 302,
     WEAKEN = 303,
     CROAK = 304,
     CURRENT_PACKAGE = 305,
     UNWEAKEN = 306,
     ISWEAK = 307,
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
     LENGTH = 331,
     SCALAR = 332,
     CONVERT = 333,
     MINUS = 334,
     PLUS = 335,
     DEREF = 336,
     REF = 337,
     BIT_NOT = 338,
     LOGICAL_NOT = 339,
     DEC = 340,
     INC = 341,
     ARROW = 342
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
#define DESCRIPTOR 267
#define IF 268
#define UNLESS 269
#define ELSIF 270
#define ELSE 271
#define FOR 272
#define WHILE 273
#define LAST 274
#define NEXT 275
#define SWITCH 276
#define CASE 277
#define DEFAULT 278
#define EVAL 279
#define NAME 280
#define VAR_NAME 281
#define CONSTANT 282
#define PACKAGE_VAR_NAME 283
#define EXCEPTION_VAR 284
#define UNDEF 285
#define VOID 286
#define BYTE 287
#define SHORT 288
#define INT 289
#define LONG 290
#define FLOAT 291
#define DOUBLE 292
#define STRING 293
#define OBJECT 294
#define DOT3 295
#define FATCAMMA 296
#define RW 297
#define RO 298
#define WO 299
#define BEGIN 300
#define NEW 301
#define RETURN 302
#define WEAKEN 303
#define CROAK 304
#define CURRENT_PACKAGE 305
#define UNWEAKEN 306
#define ISWEAK 307
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
#define LENGTH 331
#define SCALAR 332
#define CONVERT 333
#define MINUS 334
#define PLUS 335
#define DEREF 336
#define REF 337
#define BIT_NOT 338
#define LOGICAL_NOT 339
#define DEC 340
#define INC 341
#define ARROW 342




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



