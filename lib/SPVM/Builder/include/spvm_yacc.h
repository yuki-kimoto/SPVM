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
    TRUE = 295,
    FALSE = 296,
    DOT3 = 297,
    FATCAMMA = 298,
    RW = 299,
    RO = 300,
    WO = 301,
    INIT = 302,
    NEW = 303,
    RETURN = 304,
    WEAKEN = 305,
    DIE = 306,
    WARN = 307,
    PRINT = 308,
    CURRENT_CLASS = 309,
    UNWEAKEN = 310,
    ASSIGN = 311,
    SPECIAL_ASSIGN = 312,
    LOGICAL_OR = 313,
    LOGICAL_AND = 314,
    BIT_OR = 315,
    BIT_XOR = 316,
    NUMEQ = 317,
    NUMNE = 318,
    STREQ = 319,
    STRNE = 320,
    NUMGT = 321,
    NUMGE = 322,
    NUMLT = 323,
    NUMLE = 324,
    STRGT = 325,
    STRGE = 326,
    STRLT = 327,
    STRLE = 328,
    ISA = 329,
    NUMERIC_CMP = 330,
    STRING_CMP = 331,
    SHIFT = 332,
    MULTIPLY = 333,
    DIVIDE = 334,
    REMAINDER = 335,
    LOGICAL_NOT = 336,
    BIT_NOT = 337,
    CREATE_REF = 338,
    DEREF = 339,
    PLUS = 340,
    MINUS = 341,
    CONVERT = 342,
    SCALAR = 343,
    STRING_LENGTH = 344,
    ISWEAK = 345,
    REFCNT = 346,
    REFOP = 347,
    DUMP = 348,
    INC = 349,
    DEC = 350,
    ARROW = 351
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED  */
