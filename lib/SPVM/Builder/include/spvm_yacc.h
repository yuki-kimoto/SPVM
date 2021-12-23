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
    CURRENT_CLASS = 267,
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
    TRUE = 296,
    FALSE = 297,
    DOT3 = 298,
    FATCAMMA = 299,
    RW = 300,
    RO = 301,
    WO = 302,
    INIT = 303,
    NEW = 304,
    RETURN = 305,
    WEAKEN = 306,
    DIE = 307,
    WARN = 308,
    PRINT = 309,
    CURRENT_CLASS_NAME = 310,
    UNWEAKEN = 311,
    ASSIGN = 312,
    SPECIAL_ASSIGN = 313,
    LOGICAL_OR = 314,
    LOGICAL_AND = 315,
    BIT_OR = 316,
    BIT_XOR = 317,
    NUMEQ = 318,
    NUMNE = 319,
    STREQ = 320,
    STRNE = 321,
    NUMGT = 322,
    NUMGE = 323,
    NUMLT = 324,
    NUMLE = 325,
    STRGT = 326,
    STRGE = 327,
    STRLT = 328,
    STRLE = 329,
    ISA = 330,
    NUMERIC_CMP = 331,
    STRING_CMP = 332,
    SHIFT = 333,
    MULTIPLY = 334,
    DIVIDE = 335,
    REMAINDER = 336,
    LOGICAL_NOT = 337,
    BIT_NOT = 338,
    CREATE_REF = 339,
    DEREF = 340,
    PLUS = 341,
    MINUS = 342,
    CONVERT = 343,
    SCALAR = 344,
    STRING_LENGTH = 345,
    ISWEAK = 346,
    REFCNT = 347,
    REFOP = 348,
    DUMP = 349,
    INC = 350,
    DEC = 351,
    ARROW = 352
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED  */
