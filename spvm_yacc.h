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
     MY = 258,
     HAS = 259,
     SUB = 260,
     PACKAGE = 261,
     IF = 262,
     ELSIF = 263,
     ELSE = 264,
     RETURN = 265,
     FOR = 266,
     WHILE = 267,
     USE = 268,
     NEW = 269,
     OUR = 270,
     SELF = 271,
     CLASS = 272,
     STRING_EQ = 273,
     STRING_NE = 274,
     STRING_GT = 275,
     STRING_GE = 276,
     STRING_LT = 277,
     STRING_LE = 278,
     LAST = 279,
     NEXT = 280,
     NAME = 281,
     CONSTANT = 282,
     ENUM = 283,
     DESCRIPTOR = 284,
     CORETYPE = 285,
     UNDEF = 286,
     CROAK = 287,
     VAR_NAME = 288,
     INTERFACE = 289,
     REF = 290,
     ISA = 291,
     SWITCH = 292,
     CASE = 293,
     DEFAULT = 294,
     VOID = 295,
     EVAL = 296,
     BYTE = 297,
     SHORT = 298,
     INT = 299,
     LONG = 300,
     FLOAT = 301,
     DOUBLE = 302,
     STRING = 303,
     WEAKEN = 304,
     SPECIAL_ASSIGN = 305,
     ASSIGN = 306,
     OR = 307,
     AND = 308,
     BIT_XOR = 309,
     BIT_OR = 310,
     BIT_AND = 311,
     REL = 312,
     SHIFT = 313,
     REMAINDER = 314,
     DIVIDE = 315,
     MULTIPLY = 316,
     UMINUS = 317,
     ARRAY_LENGTH = 318,
     NOT = 319,
     DEC = 320,
     INC = 321,
     ARROW = 322
   };
#endif
/* Tokens.  */
#define MY 258
#define HAS 259
#define SUB 260
#define PACKAGE 261
#define IF 262
#define ELSIF 263
#define ELSE 264
#define RETURN 265
#define FOR 266
#define WHILE 267
#define USE 268
#define NEW 269
#define OUR 270
#define SELF 271
#define CLASS 272
#define STRING_EQ 273
#define STRING_NE 274
#define STRING_GT 275
#define STRING_GE 276
#define STRING_LT 277
#define STRING_LE 278
#define LAST 279
#define NEXT 280
#define NAME 281
#define CONSTANT 282
#define ENUM 283
#define DESCRIPTOR 284
#define CORETYPE 285
#define UNDEF 286
#define CROAK 287
#define VAR_NAME 288
#define INTERFACE 289
#define REF 290
#define ISA 291
#define SWITCH 292
#define CASE 293
#define DEFAULT 294
#define VOID 295
#define EVAL 296
#define BYTE 297
#define SHORT 298
#define INT 299
#define LONG 300
#define FLOAT 301
#define DOUBLE 302
#define STRING 303
#define WEAKEN 304
#define SPECIAL_ASSIGN 305
#define ASSIGN 306
#define OR 307
#define AND 308
#define BIT_XOR 309
#define BIT_OR 310
#define BIT_AND 311
#define REL 312
#define SHIFT 313
#define REMAINDER 314
#define DIVIDE 315
#define MULTIPLY 316
#define UMINUS 317
#define ARRAY_LENGTH 318
#define NOT 319
#define DEC 320
#define INC 321
#define ARROW 322




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



