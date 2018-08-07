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
     OUR = 262,
     SELF = 263,
     IF = 264,
     ELSIF = 265,
     ELSE = 266,
     FOR = 267,
     WHILE = 268,
     LAST = 269,
     NEXT = 270,
     NAME = 271,
     VAR_NAME = 272,
     CONSTANT = 273,
     ENUM = 274,
     CORETYPE = 275,
     SWITCH = 276,
     CASE = 277,
     DEFAULT = 278,
     EVAL = 279,
     UNDEF = 280,
     VOID = 281,
     BYTE = 282,
     SHORT = 283,
     INT = 284,
     LONG = 285,
     FLOAT = 286,
     DOUBLE = 287,
     STRING = 288,
     OBJECT = 289,
     RETURN = 290,
     USE = 291,
     NEW = 292,
     CONST = 293,
     AMPERSAND = 294,
     DESCRIPTOR = 295,
     WEAKEN = 296,
     CROAK = 297,
     SPECIAL_ASSIGN = 298,
     ASSIGN = 299,
     OR = 300,
     AND = 301,
     BIT_XOR = 302,
     BIT_OR = 303,
     BIT_AND = 304,
     REL = 305,
     SHIFT = 306,
     REMAINDER = 307,
     DIVIDE = 308,
     MULTIPLY = 309,
     ISA = 310,
     DEREF = 311,
     REF = 312,
     UMINUS = 313,
     SCALAR = 314,
     NOT = 315,
     DEC = 316,
     INC = 317,
     ARROW = 318
   };
#endif
/* Tokens.  */
#define MY 258
#define HAS 259
#define SUB 260
#define PACKAGE 261
#define OUR 262
#define SELF 263
#define IF 264
#define ELSIF 265
#define ELSE 266
#define FOR 267
#define WHILE 268
#define LAST 269
#define NEXT 270
#define NAME 271
#define VAR_NAME 272
#define CONSTANT 273
#define ENUM 274
#define CORETYPE 275
#define SWITCH 276
#define CASE 277
#define DEFAULT 278
#define EVAL 279
#define UNDEF 280
#define VOID 281
#define BYTE 282
#define SHORT 283
#define INT 284
#define LONG 285
#define FLOAT 286
#define DOUBLE 287
#define STRING 288
#define OBJECT 289
#define RETURN 290
#define USE 291
#define NEW 292
#define CONST 293
#define AMPERSAND 294
#define DESCRIPTOR 295
#define WEAKEN 296
#define CROAK 297
#define SPECIAL_ASSIGN 298
#define ASSIGN 299
#define OR 300
#define AND 301
#define BIT_XOR 302
#define BIT_OR 303
#define BIT_AND 304
#define REL 305
#define SHIFT 306
#define REMAINDER 307
#define DIVIDE 308
#define MULTIPLY 309
#define ISA 310
#define DEREF 311
#define REF 312
#define UMINUS 313
#define SCALAR 314
#define NOT 315
#define DEC 316
#define INC 317
#define ARROW 318




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



