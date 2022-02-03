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
    AS = 265,
    REQUIRE = 266,
    ALLOW = 267,
    CURRENT_CLASS = 268,
    MUTABLE = 269,
    DESCRIPTOR = 270,
    IF = 271,
    UNLESS = 272,
    ELSIF = 273,
    ELSE = 274,
    FOR = 275,
    WHILE = 276,
    LAST = 277,
    NEXT = 278,
    SWITCH = 279,
    CASE = 280,
    DEFAULT = 281,
    BREAK = 282,
    EVAL = 283,
    NAME = 284,
    VAR_NAME = 285,
    CONSTANT = 286,
    EXCEPTION_VAR = 287,
    UNDEF = 288,
    VOID = 289,
    BYTE = 290,
    SHORT = 291,
    INT = 292,
    LONG = 293,
    FLOAT = 294,
    DOUBLE = 295,
    STRING = 296,
    OBJECT = 297,
    TRUE = 298,
    FALSE = 299,
    DOT3 = 300,
    FATCAMMA = 301,
    RW = 302,
    RO = 303,
    WO = 304,
    INIT = 305,
    NEW = 306,
    RETURN = 307,
    WEAKEN = 308,
    DIE = 309,
    WARN = 310,
    PRINT = 311,
    CURRENT_CLASS_NAME = 312,
    UNWEAKEN = 313,
    ASSIGN = 314,
    SPECIAL_ASSIGN = 315,
    LOGICAL_OR = 316,
    LOGICAL_AND = 317,
    BIT_OR = 318,
    BIT_XOR = 319,
    BIT_AND = 320,
    NUMEQ = 321,
    NUMNE = 322,
    STREQ = 323,
    STRNE = 324,
    NUMGT = 325,
    NUMGE = 326,
    NUMLT = 327,
    NUMLE = 328,
    STRGT = 329,
    STRGE = 330,
    STRLT = 331,
    STRLE = 332,
    ISA = 333,
    NUMERIC_CMP = 334,
    STRING_CMP = 335,
    SHIFT = 336,
    DIVIDE = 337,
    REMAINDER = 338,
    LOGICAL_NOT = 339,
    BIT_NOT = 340,
    CREATE_REF = 341,
    DEREF = 342,
    PLUS = 343,
    MINUS = 344,
    CONVERT = 345,
    SCALAR = 346,
    STRING_LENGTH = 347,
    ISWEAK = 348,
    REFCNT = 349,
    REFOP = 350,
    DUMP = 351,
    INC = 352,
    DEC = 353,
    ARROW = 354
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED  */
