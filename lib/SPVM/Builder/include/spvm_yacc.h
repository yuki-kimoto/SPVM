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
    GET = 260,
    SET = 261,
    METHOD = 262,
    OUR = 263,
    ENUM = 264,
    MY = 265,
    USE = 266,
    AS = 267,
    REQUIRE = 268,
    ALIAS = 269,
    ALLOW = 270,
    OUTMOST_CLASS = 271,
    MUTABLE = 272,
    ATTRIBUTE = 273,
    MAKE_READ_ONLY = 274,
    INTERFACE = 275,
    EVAL_ERROR_ID = 276,
    ARGS_WIDTH = 277,
    VERSION_DECL = 278,
    VERSION_FROM = 279,
    IF = 280,
    UNLESS = 281,
    ELSIF = 282,
    ELSE = 283,
    FOR = 284,
    WHILE = 285,
    LAST = 286,
    NEXT = 287,
    SWITCH = 288,
    CASE = 289,
    DEFAULT = 290,
    BREAK = 291,
    EVAL = 292,
    SYMBOL_NAME = 293,
    VAR_NAME = 294,
    CONSTANT = 295,
    EXCEPTION_VAR = 296,
    COPY_FIELDS = 297,
    UNDEF = 298,
    VOID = 299,
    BYTE = 300,
    SHORT = 301,
    INT = 302,
    LONG = 303,
    FLOAT = 304,
    DOUBLE = 305,
    STRING = 306,
    OBJECT = 307,
    TRUE = 308,
    FALSE = 309,
    END_OF_FILE = 310,
    RW = 311,
    RO = 312,
    WO = 313,
    INIT = 314,
    NEW = 315,
    OF = 316,
    BASIC_TYPE_ID = 317,
    EXTENDS = 318,
    SUPER = 319,
    RETURN = 320,
    WEAKEN = 321,
    DIE = 322,
    WARN = 323,
    PRINT = 324,
    SAY = 325,
    OUTMOST_CLASS_NAME = 326,
    UNWEAKEN = 327,
    ENABLE_OPTIONS = 328,
    DISABLE_OPTIONS = 329,
    FATCAMMA = 330,
    ASSIGN = 331,
    SPECIAL_ASSIGN = 332,
    LOGICAL_OR = 333,
    DEFINED_OR = 334,
    LOGICAL_AND = 335,
    BIT_OR = 336,
    BIT_XOR = 337,
    BIT_AND = 338,
    NUMEQ = 339,
    NUMNE = 340,
    STREQ = 341,
    STRNE = 342,
    NUMGT = 343,
    NUMGE = 344,
    NUMLT = 345,
    NUMLE = 346,
    STRGT = 347,
    STRGE = 348,
    STRLT = 349,
    STRLE = 350,
    ISA = 351,
    ISA_ERROR = 352,
    IS_TYPE = 353,
    IS_ERROR = 354,
    IS_COMPILE_TYPE = 355,
    NUMERIC_CMP = 356,
    STRING_CMP = 357,
    CAN = 358,
    SHIFT = 359,
    DIVIDE = 360,
    DIVIDE_UNSIGNED_INT = 361,
    DIVIDE_UNSIGNED_LONG = 362,
    MODULO = 363,
    MODULO_UNSIGNED_INT = 364,
    MODULO_UNSIGNED_LONG = 365,
    LOGICAL_NOT = 366,
    BIT_NOT = 367,
    REFERENCE = 368,
    DEREFERENCE = 369,
    PLUS = 370,
    MINUS = 371,
    CONVERT = 372,
    SCALAR = 373,
    STRING_LENGTH = 374,
    ISWEAK = 375,
    TYPE_NAME = 376,
    COMPILE_TYPE_NAME = 377,
    DUMP = 378,
    NEW_STRING_LEN = 379,
    IS_READ_ONLY = 380,
    COPY = 381,
    ADDRESS = 382,
    IS_OPTIONS = 383,
    INC = 384,
    DEC = 385,
    ARROW = 386
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_LIB_SPVM_BUILDER_INCLUDE_SPVM_YACC_H_INCLUDED  */
