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
     LAST = 270,
     NEXT = 271,
     NAME = 272,
     VAR = 273,
     CONSTANT = 274,
     ENUM = 275,
     DESCRIPTOR = 276,
     CORETYPE = 277,
     UNDEF = 278,
     CROAK = 279,
     SWITCH = 280,
     CASE = 281,
     DEFAULT = 282,
     VOID = 283,
     EVAL = 284,
     EXCEPTION_VAR = 285,
     BYTE = 286,
     SHORT = 287,
     INT = 288,
     LONG = 289,
     FLOAT = 290,
     DOUBLE = 291,
     STRING = 292,
     WEAKEN = 293,
     SPECIAL_ASSIGN = 294,
     ASSIGN = 295,
     OR = 296,
     AND = 297,
     BIT_XOR = 298,
     BIT_OR = 299,
     BIT_AND = 300,
     REL = 301,
     SHIFT = 302,
     REMAINDER = 303,
     DIVIDE = 304,
     MULTIPLY = 305,
     UMINUS = 306,
     ARRAY_LENGTH = 307,
     NOT = 308,
     DEC = 309,
     INC = 310,
     ARROW = 311
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
#define LAST 270
#define NEXT 271
#define NAME 272
#define VAR 273
#define CONSTANT 274
#define ENUM 275
#define DESCRIPTOR 276
#define CORETYPE 277
#define UNDEF 278
#define CROAK 279
#define SWITCH 280
#define CASE 281
#define DEFAULT 282
#define VOID 283
#define EVAL 284
#define EXCEPTION_VAR 285
#define BYTE 286
#define SHORT 287
#define INT 288
#define LONG 289
#define FLOAT 290
#define DOUBLE 291
#define STRING 292
#define WEAKEN 293
#define SPECIAL_ASSIGN 294
#define ASSIGN 295
#define OR 296
#define AND 297
#define BIT_XOR 298
#define BIT_OR 299
#define BIT_AND 300
#define REL 301
#define SHIFT 302
#define REMAINDER 303
#define DIVIDE 304
#define MULTIPLY 305
#define UMINUS 306
#define ARRAY_LENGTH 307
#define NOT 308
#define DEC 309
#define INC 310
#define ARROW 311




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



