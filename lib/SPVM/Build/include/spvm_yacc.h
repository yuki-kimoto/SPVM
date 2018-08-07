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
     CONSTANT = 272,
     ENUM = 273,
     DESCRIPTOR = 274,
     CORETYPE = 275,
     CROAK = 276,
     VAR_NAME = 277,
     INTERFACE = 278,
     ISA = 279,
     SWITCH = 280,
     CASE = 281,
     DEFAULT = 282,
     EVAL = 283,
     WEAKEN = 284,
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
     RETURN = 295,
     USE = 296,
     NEW = 297,
     CONST = 298,
     AMPERSAND = 299,
     SPECIAL_ASSIGN = 300,
     ASSIGN = 301,
     OR = 302,
     AND = 303,
     BIT_XOR = 304,
     BIT_OR = 305,
     BIT_AND = 306,
     REL = 307,
     SHIFT = 308,
     REMAINDER = 309,
     DIVIDE = 310,
     MULTIPLY = 311,
     DEREF = 312,
     REF = 313,
     UMINUS = 314,
     SCALAR = 315,
     NOT = 316,
     DEC = 317,
     INC = 318,
     ARROW = 319
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
#define CONSTANT 272
#define ENUM 273
#define DESCRIPTOR 274
#define CORETYPE 275
#define CROAK 276
#define VAR_NAME 277
#define INTERFACE 278
#define ISA 279
#define SWITCH 280
#define CASE 281
#define DEFAULT 282
#define EVAL 283
#define WEAKEN 284
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
#define RETURN 295
#define USE 296
#define NEW 297
#define CONST 298
#define AMPERSAND 299
#define SPECIAL_ASSIGN 300
#define ASSIGN 301
#define OR 302
#define AND 303
#define BIT_XOR 304
#define BIT_OR 305
#define BIT_AND 306
#define REL 307
#define SHIFT 308
#define REMAINDER 309
#define DIVIDE 310
#define MULTIPLY 311
#define DEREF 312
#define REF 313
#define UMINUS 314
#define SCALAR 315
#define NOT 316
#define DEC 317
#define INC 318
#define ARROW 319




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



