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

#ifndef YY_SPVM_YY_LIB_SPVM_BUILDER_INCLUDE_SPVM_YACC_H_INCLUDED
# define YY_SPVM_YY_LIB_SPVM_BUILDER_INCLUDE_SPVM_YACC_H_INCLUDED
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
    OUTMOST_CLASS = 269,
    MUTABLE = 270,
    ATTRIBUTE = 271,
    MAKE_READ_ONLY = 272,
    INTERFACE = 273,
    EVAL_ERROR_ID = 274,
    ARGS_WIDTH = 275,
    VERSION_DECL = 276,
    VERSION_FROM = 277,
    IF = 278,
    UNLESS = 279,
    ELSIF = 280,
    ELSE = 281,
    FOR = 282,
    WHILE = 283,
    LAST = 284,
    NEXT = 285,
    SWITCH = 286,
    CASE = 287,
    DEFAULT = 288,
    BREAK = 289,
    EVAL = 290,
    SYMBOL_NAME = 291,
    VAR_NAME = 292,
    CONSTANT = 293,
    EXCEPTION_VAR = 294,
    UNDEF = 295,
    VOID = 296,
    BYTE = 297,
    SHORT = 298,
    INT = 299,
    LONG = 300,
    FLOAT = 301,
    DOUBLE = 302,
    STRING = 303,
    OBJECT = 304,
    TRUE = 305,
    FALSE = 306,
    END_OF_FILE = 307,
    FATCAMMA = 308,
    RW = 309,
    RO = 310,
    WO = 311,
    INIT = 312,
    NEW = 313,
    OF = 314,
    BASIC_TYPE_ID = 315,
    EXTENDS = 316,
    SUPER = 317,
    RETURN = 318,
    WEAKEN = 319,
    DIE = 320,
    WARN = 321,
    PRINT = 322,
    SAY = 323,
    OUTMOST_CLASS_NAME = 324,
    UNWEAKEN = 325,
    ASSIGN = 326,
    SPECIAL_ASSIGN = 327,
    LOGICAL_OR = 328,
    LOGICAL_AND = 329,
    BIT_OR = 330,
    BIT_XOR = 331,
    BIT_AND = 332,
    NUMEQ = 333,
    NUMNE = 334,
    STREQ = 335,
    STRNE = 336,
    NUMGT = 337,
    NUMGE = 338,
    NUMLT = 339,
    NUMLE = 340,
    STRGT = 341,
    STRGE = 342,
    STRLT = 343,
    STRLE = 344,
    ISA = 345,
    ISA_ERROR = 346,
    IS_TYPE = 347,
    IS_ERROR = 348,
    IS_COMPILE_TYPE = 349,
    NUMERIC_CMP = 350,
    STRING_CMP = 351,
    CAN = 352,
    SHIFT = 353,
    DIVIDE = 354,
    DIVIDE_UNSIGNED_INT = 355,
    DIVIDE_UNSIGNED_LONG = 356,
    MODULO = 357,
    MODULO_UNSIGNED_INT = 358,
    MODULO_UNSIGNED_LONG = 359,
    LOGICAL_NOT = 360,
    BIT_NOT = 361,
    REFERENCE = 362,
    DEREFERENCE = 363,
    PLUS = 364,
    MINUS = 365,
    CONVERT = 366,
    SCALAR = 367,
    STRING_LENGTH = 368,
    ISWEAK = 369,
    TYPE_NAME = 370,
    COMPILE_TYPE_NAME = 371,
    DUMP = 372,
    NEW_STRING_LEN = 373,
    IS_READ_ONLY = 374,
    COPY = 375,
    INC = 376,
    DEC = 377,
    ARROW = 378
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_LIB_SPVM_BUILDER_INCLUDE_SPVM_YACC_H_INCLUDED  */
