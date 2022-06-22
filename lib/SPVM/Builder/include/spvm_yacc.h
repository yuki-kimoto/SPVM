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
    ALIAS = 267,
    ALLOW = 268,
    CURRENT_CLASS = 269,
    MUTABLE = 270,
    DESCRIPTOR = 271,
    MAKE_READ_ONLY = 272,
    INTERFACE = 273,
    ERROR_CODE = 274,
    ERROR = 275,
    IF = 276,
    UNLESS = 277,
    ELSIF = 278,
    ELSE = 279,
    FOR = 280,
    WHILE = 281,
    LAST = 282,
    NEXT = 283,
    SWITCH = 284,
    CASE = 285,
    DEFAULT = 286,
    BREAK = 287,
    EVAL = 288,
    SYMBOL_NAME = 289,
    VAR_NAME = 290,
    CONSTANT = 291,
    EXCEPTION_VAR = 292,
    UNDEF = 293,
    VOID = 294,
    BYTE = 295,
    SHORT = 296,
    INT = 297,
    LONG = 298,
    FLOAT = 299,
    DOUBLE = 300,
    STRING = 301,
    OBJECT = 302,
    TRUE = 303,
    FALSE = 304,
    END_OF_FILE = 305,
    DOT3 = 306,
    FATCAMMA = 307,
    RW = 308,
    RO = 309,
    WO = 310,
    INIT = 311,
    NEW = 312,
    OF = 313,
    CLASS_ID = 314,
    EXTENDS = 315,
    SUPER = 316,
    RETURN = 317,
    WEAKEN = 318,
    DIE = 319,
    WARN = 320,
    PRINT = 321,
    CURRENT_CLASS_NAME = 322,
    UNWEAKEN = 323,
    ASSIGN = 324,
    SPECIAL_ASSIGN = 325,
    LOGICAL_OR = 326,
    LOGICAL_AND = 327,
    BIT_OR = 328,
    BIT_XOR = 329,
    BIT_AND = 330,
    NUMEQ = 331,
    NUMNE = 332,
    STREQ = 333,
    STRNE = 334,
    NUMGT = 335,
    NUMGE = 336,
    NUMLT = 337,
    NUMLE = 338,
    STRGT = 339,
    STRGE = 340,
    STRLT = 341,
    STRLE = 342,
    ISA = 343,
    NUMERIC_CMP = 344,
    STRING_CMP = 345,
    SHIFT = 346,
    DIVIDE = 347,
    DIVIDE_UNSIGNED_INT = 348,
    DIVIDE_UNSIGNED_LONG = 349,
    REMAINDER = 350,
    REMAINDER_UNSIGNED_INT = 351,
    REMAINDER_UNSIGNED_LONG = 352,
    LOGICAL_NOT = 353,
    BIT_NOT = 354,
    CREATE_REF = 355,
    DEREF = 356,
    PLUS = 357,
    MINUS = 358,
    CONVERT = 359,
    SCALAR = 360,
    STRING_LENGTH = 361,
    ISWEAK = 362,
    REFCNT = 363,
    REFOP = 364,
    DUMP = 365,
    NEW_STRING_LEN = 366,
    IS_READ_ONLY = 367,
    COPY = 368,
    HAS_IMPL = 369,
    SET_ERROR_CODE = 370,
    INC = 371,
    DEC = 372,
    ARROW = 373
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED  */
