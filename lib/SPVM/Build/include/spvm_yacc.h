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
     CONST = 272,
     LAST = 273,
     NEXT = 274,
     NAME = 275,
     CONSTANT = 276,
     ENUM = 277,
     DESCRIPTOR = 278,
     CORETYPE = 279,
     CROAK = 280,
     VAR_NAME = 281,
     INTERFACE = 282,
     ISA = 283,
     SWITCH = 284,
     CASE = 285,
     DEFAULT = 286,
     EVAL = 287,
     WEAKEN = 288,
     PRECOMPILE = 289,
     DEREF = 290,
     BACKSLASH = 291,
     UNDEF = 292,
     VOID = 293,
     BYTE = 294,
     SHORT = 295,
     INT = 296,
     LONG = 297,
     FLOAT = 298,
     DOUBLE = 299,
     STRING = 300,
     OBJECT = 301,
     AMPERSAND = 302,
     SPECIAL_ASSIGN = 303,
     ASSIGN = 304,
     OR = 305,
     AND = 306,
     BIT_XOR = 307,
     BIT_OR = 308,
     BIT_AND = 309,
     REL = 310,
     SHIFT = 311,
     REMAINDER = 312,
     DIVIDE = 313,
     MULTIPLY = 314,
     UMINUS = 315,
     SCALAR = 316,
     NOT = 317,
     DEC = 318,
     INC = 319,
     ARROW = 320
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
#define CONST 272
#define LAST 273
#define NEXT 274
#define NAME 275
#define CONSTANT 276
#define ENUM 277
#define DESCRIPTOR 278
#define CORETYPE 279
#define CROAK 280
#define VAR_NAME 281
#define INTERFACE 282
#define ISA 283
#define SWITCH 284
#define CASE 285
#define DEFAULT 286
#define EVAL 287
#define WEAKEN 288
#define PRECOMPILE 289
#define DEREF 290
#define BACKSLASH 291
#define UNDEF 292
#define VOID 293
#define BYTE 294
#define SHORT 295
#define INT 296
#define LONG 297
#define FLOAT 298
#define DOUBLE 299
#define STRING 300
#define OBJECT 301
#define AMPERSAND 302
#define SPECIAL_ASSIGN 303
#define ASSIGN 304
#define OR 305
#define AND 306
#define BIT_XOR 307
#define BIT_OR 308
#define BIT_AND 309
#define REL 310
#define SHIFT 311
#define REMAINDER 312
#define DIVIDE 313
#define MULTIPLY 314
#define UMINUS 315
#define SCALAR 316
#define NOT 317
#define DEC 318
#define INC 319
#define ARROW 320




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



