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
    END_OF_FILE = 300,
    DOT3 = 301,
    FATCAMMA = 302,
    RW = 303,
    RO = 304,
    WO = 305,
    INIT = 306,
    NEW = 307,
    RETURN = 308,
    WEAKEN = 309,
    DIE = 310,
    WARN = 311,
    PRINT = 312,
    CURRENT_CLASS_NAME = 313,
    UNWEAKEN = 314,
    ASSIGN = 315,
    SPECIAL_ASSIGN = 316,
    LOGICAL_OR = 317,
    LOGICAL_AND = 318,
    BIT_OR = 319,
    BIT_XOR = 320,
    BIT_AND = 321,
    NUMEQ = 322,
    NUMNE = 323,
    STREQ = 324,
    STRNE = 325,
    NUMGT = 326,
    NUMGE = 327,
    NUMLT = 328,
    NUMLE = 329,
    STRGT = 330,
    STRGE = 331,
    STRLT = 332,
    STRLE = 333,
    ISA = 334,
    NUMERIC_CMP = 335,
    STRING_CMP = 336,
    SHIFT = 337,
    DIVIDE = 338,
    DIVIDE_UINT = 339,
    DIVIDE_ULONG = 340,
    REMAINDER = 341,
    REMAINDER_UINT = 342,
    REMAINDER_ULONG = 343,
    LOGICAL_NOT = 344,
    BIT_NOT = 345,
    CREATE_REF = 346,
    DEREF = 347,
    PLUS = 348,
    MINUS = 349,
    CONVERT = 350,
    SCALAR = 351,
    STRING_LENGTH = 352,
    ISWEAK = 353,
    REFCNT = 354,
    REFOP = 355,
    DUMP = 356,
    INC = 357,
    DEC = 358,
    ARROW = 359
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED  */
