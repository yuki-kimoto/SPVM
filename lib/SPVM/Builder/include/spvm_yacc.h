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
     INIT = 301,
     NEW = 302,
     RETURN = 303,
     WEAKEN = 304,
     DIE = 305,
     WARN = 306,
     PRINT = 307,
     CURRENT_PACKAGE = 308,
     UNWEAKEN = 309,
     SPECIAL_ASSIGN = 310,
     ASSIGN = 311,
     LOGICAL_OR = 312,
     LOGICAL_AND = 313,
     BIT_XOR = 314,
     BIT_OR = 315,
     STRNE = 316,
     STREQ = 317,
     NUMNE = 318,
     NUMEQ = 319,
     ISA = 320,
     STRLE = 321,
     STRLT = 322,
     STRGE = 323,
     STRGT = 324,
     NUMLE = 325,
     NUMLT = 326,
     NUMGE = 327,
     NUMGT = 328,
     SHIFT = 329,
     REMAINDER = 330,
     DIVIDE = 331,
     MULTIPLY = 332,
     SPACE_SHIP = 333,
     REFOP = 334,
     REFCNT = 335,
     ISWEAK = 336,
     LENGTH = 337,
     SCALAR = 338,
     CONVERT = 339,
     MINUS = 340,
     PLUS = 341,
     DEREF = 342,
     CREATE_REF = 343,
     BIT_NOT = 344,
     LOGICAL_NOT = 345,
     DEC = 346,
     INC = 347,
     ARROW = 348
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
#define INIT 301
#define NEW 302
#define RETURN 303
#define WEAKEN 304
#define DIE 305
#define WARN 306
#define PRINT 307
#define CURRENT_PACKAGE 308
#define UNWEAKEN 309
#define SPECIAL_ASSIGN 310
#define ASSIGN 311
#define LOGICAL_OR 312
#define LOGICAL_AND 313
#define BIT_XOR 314
#define BIT_OR 315
#define STRNE 316
#define STREQ 317
#define NUMNE 318
#define NUMEQ 319
#define ISA 320
#define STRLE 321
#define STRLT 322
#define STRGE 323
#define STRGT 324
#define NUMLE 325
#define NUMLT 326
#define NUMGE 327
#define NUMGT 328
#define SHIFT 329
#define REMAINDER 330
#define DIVIDE 331
#define MULTIPLY 332
#define SPACE_SHIP 333
#define REFOP 334
#define REFCNT 335
#define ISWEAK 336
#define LENGTH 337
#define SCALAR 338
#define CONVERT 339
#define MINUS 340
#define PLUS 341
#define DEREF 342
#define CREATE_REF 343
#define BIT_NOT 344
#define LOGICAL_NOT 345
#define DEC 346
#define INC 347
#define ARROW 348




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



