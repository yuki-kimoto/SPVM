/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED
# define YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int SPVM_yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CLASS = 258,
    HAS = 259,
    METHOD = 260,
    OUR = 261,
    ENUM = 262,
    MY = 263,
    USE = 264,
    REQUIRE = 265,
    ALLOW = 266,
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
    BREAK = 279,
    EVAL = 280,
    NAME = 281,
    VAR_NAME = 282,
    CONSTANT = 283,
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
    INIT = 300,
    NEW = 301,
    RETURN = 302,
    WEAKEN = 303,
    DIE = 304,
    WARN = 305,
    PRINT = 306,
    CURRENT_CLASS = 307,
    UNWEAKEN = 308,
    ASSIGN = 309,
    SPECIAL_ASSIGN = 310,
    LOGICAL_OR = 311,
    LOGICAL_AND = 312,
    BIT_OR = 313,
    BIT_XOR = 314,
    NUMEQ = 315,
    NUMNE = 316,
    STREQ = 317,
    STRNE = 318,
    NUMGT = 319,
    NUMGE = 320,
    NUMLT = 321,
    NUMLE = 322,
    STRGT = 323,
    STRGE = 324,
    STRLT = 325,
    STRLE = 326,
    ISA = 327,
    NUMERIC_CMP = 328,
    STRING_CMP = 329,
    SHIFT = 330,
    MULTIPLY = 331,
    DIVIDE = 332,
    REMAINDER = 333,
    LOGICAL_NOT = 334,
    BIT_NOT = 335,
    CREATE_REF = 336,
    DEREF = 337,
    PLUS = 338,
    MINUS = 339,
    CONVERT = 340,
    SCALAR = 341,
    STRING_LENGTH = 342,
    ISWEAK = 343,
    REFCNT = 344,
    REFOP = 345,
    DUMP = 346,
    INC = 347,
    DEC = 348,
    ARROW = 349
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED  */
