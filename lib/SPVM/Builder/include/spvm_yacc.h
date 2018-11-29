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
     MAYBE_SUB_NAME = 283,
     EXCEPTION_VAR = 284,
     RETURN = 285,
     WEAKEN = 286,
     CROAK = 287,
     NEW = 288,
     UNDEF = 289,
     VOID = 290,
     BYTE = 291,
     SHORT = 292,
     INT = 293,
     LONG = 294,
     FLOAT = 295,
     DOUBLE = 296,
     STRING = 297,
     OBJECT = 298,
     AMPERSAND = 299,
     DOT3 = 300,
     LENGTH = 301,
     FATCAMMA = 302,
     RW = 303,
     RO = 304,
     WO = 305,
     BEGIN = 306,
     SPECIAL_ASSIGN = 307,
     ASSIGN = 308,
     OR = 309,
     AND = 310,
     BIT_XOR = 311,
     BIT_OR = 312,
     BIT_AND = 313,
     REL = 314,
     SHIFT = 315,
     REMAINDER = 316,
     DIVIDE = 317,
     MULTIPLY = 318,
     ISA = 319,
     DEREF = 320,
     REF = 321,
     UMINUS = 322,
     SCALAR = 323,
     NOT = 324,
     DEC = 325,
     INC = 326,
     ARROW = 327
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
#define MAYBE_SUB_NAME 283
#define EXCEPTION_VAR 284
#define RETURN 285
#define WEAKEN 286
#define CROAK 287
#define NEW 288
#define UNDEF 289
#define VOID 290
#define BYTE 291
#define SHORT 292
#define INT 293
#define LONG 294
#define FLOAT 295
#define DOUBLE 296
#define STRING 297
#define OBJECT 298
#define AMPERSAND 299
#define DOT3 300
#define LENGTH 301
#define FATCAMMA 302
#define RW 303
#define RO 304
#define WO 305
#define BEGIN 306
#define SPECIAL_ASSIGN 307
#define ASSIGN 308
#define OR 309
#define AND 310
#define BIT_XOR 311
#define BIT_OR 312
#define BIT_AND 313
#define REL 314
#define SHIFT 315
#define REMAINDER 316
#define DIVIDE 317
#define MULTIPLY 318
#define ISA 319
#define DEREF 320
#define REF 321
#define UMINUS 322
#define SCALAR 323
#define NOT 324
#define DEC 325
#define INC 326
#define ARROW 327




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



