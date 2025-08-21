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
    EXISTS = 298,
    DELETE = 299,
    UNDEF = 300,
    VOID = 301,
    BYTE = 302,
    SHORT = 303,
    INT = 304,
    LONG = 305,
    FLOAT = 306,
    DOUBLE = 307,
    STRING = 308,
    OBJECT = 309,
    TRUE = 310,
    FALSE = 311,
    END_OF_FILE = 312,
    RW = 313,
    RO = 314,
    WO = 315,
    INIT = 316,
    NEW = 317,
    OF = 318,
    BASIC_TYPE_ID = 319,
    EXTENDS = 320,
    SUPER = 321,
    RETURN = 322,
    WEAKEN = 323,
    DIE = 324,
    WARN = 325,
    PRINT = 326,
    SAY = 327,
    OUTMOST_CLASS_NAME = 328,
    UNWEAKEN = 329,
    ENABLE_OPTIONS = 330,
    DISABLE_OPTIONS = 331,
    FATCAMMA = 332,
    ASSIGN = 333,
    SPECIAL_ASSIGN = 334,
    LOGICAL_OR = 335,
    DEFINED_OR = 336,
    LOGICAL_AND = 337,
    BIT_OR = 338,
    BIT_XOR = 339,
    BIT_AND = 340,
    NUMEQ = 341,
    NUMNE = 342,
    STREQ = 343,
    STRNE = 344,
    NUMGT = 345,
    NUMGE = 346,
    NUMLT = 347,
    NUMLE = 348,
    STRGT = 349,
    STRGE = 350,
    STRLT = 351,
    STRLE = 352,
    ISA = 353,
    ISA_ERROR = 354,
    IS_TYPE = 355,
    IS_ERROR = 356,
    IS_COMPILE_TYPE = 357,
    NUMERIC_CMP = 358,
    STRING_CMP = 359,
    CAN = 360,
    SHIFT = 361,
    DIVIDE = 362,
    DIVIDE_UNSIGNED_INT = 363,
    DIVIDE_UNSIGNED_LONG = 364,
    MODULO = 365,
    MODULO_UNSIGNED_INT = 366,
    MODULO_UNSIGNED_LONG = 367,
    LOGICAL_NOT = 368,
    BIT_NOT = 369,
    REFERENCE = 370,
    DEREFERENCE = 371,
    PLUS = 372,
    MINUS = 373,
    CONVERT = 374,
    SCALAR = 375,
    STRING_LENGTH = 376,
    ISWEAK = 377,
    TYPE_NAME = 378,
    COMPILE_TYPE_NAME = 379,
    DUMP = 380,
    NEW_STRING_LEN = 381,
    IS_READ_ONLY = 382,
    COPY = 383,
    ADDRESS = 384,
    IS_OPTIONS = 385,
    INC = 386,
    DEC = 387,
    ARROW = 388
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_LIB_SPVM_BUILDER_INCLUDE_SPVM_YACC_H_INCLUDED  */
