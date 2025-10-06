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
    MAKE_FIXED_LENGTH = 275,
    INTERFACE = 276,
    EVAL_ERROR_ID = 277,
    ARGS_WIDTH = 278,
    VERSION_DECL = 279,
    VERSION_FROM = 280,
    IF = 281,
    UNLESS = 282,
    ELSIF = 283,
    ELSE = 284,
    FOR = 285,
    WHILE = 286,
    LAST = 287,
    NEXT = 288,
    SWITCH = 289,
    CASE = 290,
    DEFAULT = 291,
    BREAK = 292,
    EVAL = 293,
    SYMBOL_NAME = 294,
    VAR_NAME = 295,
    CONSTANT = 296,
    EXCEPTION_VAR = 297,
    COPY_FIELDS = 298,
    EXISTS = 299,
    DELETE = 300,
    UNDEF = 301,
    VOID = 302,
    BYTE = 303,
    SHORT = 304,
    INT = 305,
    LONG = 306,
    FLOAT = 307,
    DOUBLE = 308,
    STRING = 309,
    OBJECT = 310,
    ELEMENT = 311,
    TRUE = 312,
    FALSE = 313,
    END_OF_FILE = 314,
    RW = 315,
    RO = 316,
    WO = 317,
    INIT = 318,
    NEW = 319,
    OF = 320,
    BASIC_TYPE_ID = 321,
    EXTENDS = 322,
    SUPER = 323,
    SET_LENGTH = 324,
    SET_CAPACITY = 325,
    RETURN = 326,
    WEAKEN = 327,
    DIE = 328,
    WARN = 329,
    PRINT = 330,
    SAY = 331,
    OUTMOST_CLASS_NAME = 332,
    UNWEAKEN = 333,
    ENABLE_OPTIONS = 334,
    DISABLE_OPTIONS = 335,
    FATCAMMA = 336,
    ASSIGN = 337,
    SPECIAL_ASSIGN = 338,
    LOGICAL_OR = 339,
    DEFINED_OR = 340,
    LOGICAL_AND = 341,
    BIT_OR = 342,
    BIT_XOR = 343,
    BIT_AND = 344,
    NUMEQ = 345,
    NUMNE = 346,
    STREQ = 347,
    STRNE = 348,
    NUMGT = 349,
    NUMGE = 350,
    NUMLT = 351,
    NUMLE = 352,
    STRGT = 353,
    STRGE = 354,
    STRLT = 355,
    STRLE = 356,
    ISA = 357,
    ISA_ERROR = 358,
    IS_TYPE = 359,
    IS_ERROR = 360,
    IS_COMPILE_TYPE = 361,
    NUMERIC_CMP = 362,
    STRING_CMP = 363,
    CAN = 364,
    SHIFT = 365,
    DIVIDE = 366,
    DIVIDE_UNSIGNED_INT = 367,
    DIVIDE_UNSIGNED_LONG = 368,
    MODULO = 369,
    MODULO_UNSIGNED_INT = 370,
    MODULO_UNSIGNED_LONG = 371,
    LOGICAL_NOT = 372,
    BIT_NOT = 373,
    REFERENCE = 374,
    DEREFERENCE = 375,
    PLUS = 376,
    MINUS = 377,
    CONVERT = 378,
    SCALAR = 379,
    STRING_LENGTH = 380,
    ISWEAK = 381,
    TYPE_NAME = 382,
    COMPILE_TYPE_NAME = 383,
    DUMP = 384,
    NEW_STRING_LEN = 385,
    IS_READ_ONLY = 386,
    IS_FIXED_LENGTH = 387,
    COPY = 388,
    ADDRESS = 389,
    IS_OPTIONS = 390,
    CAPACITY = 391,
    INC = 392,
    DEC = 393,
    ARROW = 394
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_LIB_SPVM_BUILDER_INCLUDE_SPVM_YACC_H_INCLUDED  */
