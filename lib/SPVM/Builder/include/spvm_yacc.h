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
     DESCRIPTOR = 266,
     IF = 267,
     UNLESS = 268,
     ELSIF = 269,
     ELSE = 270,
     FOR = 271,
     WHILE = 272,
     LAST = 273,
     NEXT = 274,
     SWITCH = 275,
     CASE = 276,
     DEFAULT = 277,
     EVAL = 278,
     NAME = 279,
     VAR_NAME = 280,
     CONSTANT = 281,
     PACKAGE_VAR_NAME = 282,
     EXCEPTION_VAR = 283,
     UNDEF = 284,
     VOID = 285,
     BYTE = 286,
     SHORT = 287,
     INT = 288,
     LONG = 289,
     FLOAT = 290,
     DOUBLE = 291,
     STRING = 292,
     OBJECT = 293,
     DOT3 = 294,
     FATCAMMA = 295,
     RW = 296,
     RO = 297,
     WO = 298,
     BEGIN = 299,
     RETURN = 300,
     WEAKEN = 301,
     CROAK = 302,
     CURRENT_PACKAGE = 303,
     UNWEAKEN = 304,
     ISWEAK = 305,
     SPECIAL_ASSIGN = 306,
     ASSIGN = 307,
     LOGICAL_OR = 308,
     LOGICAL_AND = 309,
     BIT_XOR = 310,
     BIT_OR = 311,
     STRNE = 312,
     STREQ = 313,
     NUMNE = 314,
     NUMEQ = 315,
     ISA = 316,
     STRLE = 317,
     STRLT = 318,
     STRGE = 319,
     STRGT = 320,
     NUMLE = 321,
     NUMLT = 322,
     NUMGE = 323,
     NUMGT = 324,
     REQUIRE = 325,
     LENGTH = 326,
     SCALAR = 327,
     SHIFT = 328,
     REMAINDER = 329,
     DIVIDE = 330,
     MULTIPLY = 331,
     CAST = 332,
     MINUS = 333,
     PLUS = 334,
     DEREF = 335,
     REF = 336,
     BIT_NOT = 337,
     LOGICAL_NOT = 338,
     DEC = 339,
     INC = 340,
     NEW = 341,
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
#define DESCRIPTOR 266
#define IF 267
#define UNLESS 268
#define ELSIF 269
#define ELSE 270
#define FOR 271
#define WHILE 272
#define LAST 273
#define NEXT 274
#define SWITCH 275
#define CASE 276
#define DEFAULT 277
#define EVAL 278
#define NAME 279
#define VAR_NAME 280
#define CONSTANT 281
#define PACKAGE_VAR_NAME 282
#define EXCEPTION_VAR 283
#define UNDEF 284
#define VOID 285
#define BYTE 286
#define SHORT 287
#define INT 288
#define LONG 289
#define FLOAT 290
#define DOUBLE 291
#define STRING 292
#define OBJECT 293
#define DOT3 294
#define FATCAMMA 295
#define RW 296
#define RO 297
#define WO 298
#define BEGIN 299
#define RETURN 300
#define WEAKEN 301
#define CROAK 302
#define CURRENT_PACKAGE 303
#define UNWEAKEN 304
#define ISWEAK 305
#define SPECIAL_ASSIGN 306
#define ASSIGN 307
#define LOGICAL_OR 308
#define LOGICAL_AND 309
#define BIT_XOR 310
#define BIT_OR 311
#define STRNE 312
#define STREQ 313
#define NUMNE 314
#define NUMEQ 315
#define ISA 316
#define STRLE 317
#define STRLT 318
#define STRGE 319
#define STRGT 320
#define NUMLE 321
#define NUMLT 322
#define NUMGE 323
#define NUMGT 324
#define REQUIRE 325
#define LENGTH 326
#define SCALAR 327
#define SHIFT 328
#define REMAINDER 329
#define DIVIDE 330
#define MULTIPLY 331
#define CAST 332
#define MINUS 333
#define PLUS 334
#define DEREF 335
#define REF 336
#define BIT_NOT 337
#define LOGICAL_NOT 338
#define DEC 339
#define INC 340
#define NEW 341
#define ARROW 342




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



