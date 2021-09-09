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
    CURRENT_CLASS = 308,
    UNWEAKEN = 309,
    ASSIGN = 310,
    SPECIAL_ASSIGN = 311,
    LOGICAL_OR = 312,
    LOGICAL_AND = 313,
    BIT_OR = 314,
    BIT_XOR = 315,
    NUMEQ = 316,
    NUMNE = 317,
    STREQ = 318,
    STRNE = 319,
    NUMGT = 320,
    NUMGE = 321,
    NUMLT = 322,
    NUMLE = 323,
    STRGT = 324,
    STRGE = 325,
    STRLT = 326,
    STRLE = 327,
    ISA = 328,
    NUMERIC_CMP = 329,
    STRING_CMP = 330,
    SHIFT = 331,
    MULTIPLY = 332,
    DIVIDE = 333,
    REMAINDER = 334,
    LOGICAL_NOT = 335,
    BIT_NOT = 336,
    CREATE_REF = 337,
    DEREF = 338,
    PLUS = 339,
    MINUS = 340,
    CONVERT = 341,
    SCALAR = 342,
    STRING_LENGTH = 343,
    ISWEAK = 344,
    REFCNT = 345,
    REFOP = 346,
    DUMP = 347,
    INC = 348,
    DEC = 349,
    ARROW = 350
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED  */
