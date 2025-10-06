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
    RETURN = 324,
    WEAKEN = 325,
    DIE = 326,
    WARN = 327,
    PRINT = 328,
    SAY = 329,
    OUTMOST_CLASS_NAME = 330,
    UNWEAKEN = 331,
    ENABLE_OPTIONS = 332,
    DISABLE_OPTIONS = 333,
    FATCAMMA = 334,
    ASSIGN = 335,
    SPECIAL_ASSIGN = 336,
    LOGICAL_OR = 337,
    DEFINED_OR = 338,
    LOGICAL_AND = 339,
    BIT_OR = 340,
    BIT_XOR = 341,
    BIT_AND = 342,
    NUMEQ = 343,
    NUMNE = 344,
    STREQ = 345,
    STRNE = 346,
    NUMGT = 347,
    NUMGE = 348,
    NUMLT = 349,
    NUMLE = 350,
    STRGT = 351,
    STRGE = 352,
    STRLT = 353,
    STRLE = 354,
    ISA = 355,
    ISA_ERROR = 356,
    IS_TYPE = 357,
    IS_ERROR = 358,
    IS_COMPILE_TYPE = 359,
    NUMERIC_CMP = 360,
    STRING_CMP = 361,
    CAN = 362,
    SHIFT = 363,
    DIVIDE = 364,
    DIVIDE_UNSIGNED_INT = 365,
    DIVIDE_UNSIGNED_LONG = 366,
    MODULO = 367,
    MODULO_UNSIGNED_INT = 368,
    MODULO_UNSIGNED_LONG = 369,
    LOGICAL_NOT = 370,
    BIT_NOT = 371,
    REFERENCE = 372,
    DEREFERENCE = 373,
    PLUS = 374,
    MINUS = 375,
    CONVERT = 376,
    SCALAR = 377,
    STRING_LENGTH = 378,
    ISWEAK = 379,
    TYPE_NAME = 380,
    COMPILE_TYPE_NAME = 381,
    DUMP = 382,
    NEW_STRING_LEN = 383,
    IS_READ_ONLY = 384,
    IS_FIXED_LENGTH = 385,
    COPY = 386,
    ADDRESS = 387,
    IS_OPTIONS = 388,
    INC = 389,
    DEC = 390,
    ARROW = 391
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_LIB_SPVM_BUILDER_INCLUDE_SPVM_YACC_H_INCLUDED  */
