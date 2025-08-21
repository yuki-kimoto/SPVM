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
    UNDEF = 299,
    VOID = 300,
    BYTE = 301,
    SHORT = 302,
    INT = 303,
    LONG = 304,
    FLOAT = 305,
    DOUBLE = 306,
    STRING = 307,
    OBJECT = 308,
    TRUE = 309,
    FALSE = 310,
    END_OF_FILE = 311,
    RW = 312,
    RO = 313,
    WO = 314,
    INIT = 315,
    NEW = 316,
    OF = 317,
    BASIC_TYPE_ID = 318,
    EXTENDS = 319,
    SUPER = 320,
    RETURN = 321,
    WEAKEN = 322,
    DIE = 323,
    WARN = 324,
    PRINT = 325,
    SAY = 326,
    OUTMOST_CLASS_NAME = 327,
    UNWEAKEN = 328,
    ENABLE_OPTIONS = 329,
    DISABLE_OPTIONS = 330,
    FATCAMMA = 331,
    ASSIGN = 332,
    SPECIAL_ASSIGN = 333,
    LOGICAL_OR = 334,
    DEFINED_OR = 335,
    LOGICAL_AND = 336,
    BIT_OR = 337,
    BIT_XOR = 338,
    BIT_AND = 339,
    NUMEQ = 340,
    NUMNE = 341,
    STREQ = 342,
    STRNE = 343,
    NUMGT = 344,
    NUMGE = 345,
    NUMLT = 346,
    NUMLE = 347,
    STRGT = 348,
    STRGE = 349,
    STRLT = 350,
    STRLE = 351,
    ISA = 352,
    ISA_ERROR = 353,
    IS_TYPE = 354,
    IS_ERROR = 355,
    IS_COMPILE_TYPE = 356,
    NUMERIC_CMP = 357,
    STRING_CMP = 358,
    CAN = 359,
    SHIFT = 360,
    DIVIDE = 361,
    DIVIDE_UNSIGNED_INT = 362,
    DIVIDE_UNSIGNED_LONG = 363,
    MODULO = 364,
    MODULO_UNSIGNED_INT = 365,
    MODULO_UNSIGNED_LONG = 366,
    LOGICAL_NOT = 367,
    BIT_NOT = 368,
    REFERENCE = 369,
    DEREFERENCE = 370,
    PLUS = 371,
    MINUS = 372,
    CONVERT = 373,
    SCALAR = 374,
    STRING_LENGTH = 375,
    ISWEAK = 376,
    TYPE_NAME = 377,
    COMPILE_TYPE_NAME = 378,
    DUMP = 379,
    NEW_STRING_LEN = 380,
    IS_READ_ONLY = 381,
    COPY = 382,
    ADDRESS = 383,
    IS_OPTIONS = 384,
    INC = 385,
    DEC = 386,
    ARROW = 387
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_LIB_SPVM_BUILDER_INCLUDE_SPVM_YACC_H_INCLUDED  */
