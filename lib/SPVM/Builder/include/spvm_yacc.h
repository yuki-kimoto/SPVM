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
    EVAL_ERROR_NAME = 278,
    ARGS_WIDTH = 279,
    VERSION_DECL = 280,
    VERSION_FROM = 281,
    IF = 282,
    UNLESS = 283,
    ELSIF = 284,
    ELSE = 285,
    FOR = 286,
    WHILE = 287,
    LAST = 288,
    NEXT = 289,
    SWITCH = 290,
    CASE = 291,
    DEFAULT = 292,
    BREAK = 293,
    EVAL = 294,
    BREAK_POINT = 295,
    SYMBOL_NAME = 296,
    VAR_NAME = 297,
    CONSTANT = 298,
    EXCEPTION_VAR = 299,
    COPY_FIELDS = 300,
    EXISTS = 301,
    DELETE = 302,
    UNDEF = 303,
    VOID = 304,
    BYTE = 305,
    SHORT = 306,
    INT = 307,
    LONG = 308,
    FLOAT = 309,
    DOUBLE = 310,
    STRING = 311,
    OBJECT = 312,
    ELEMENT = 313,
    TRUE = 314,
    FALSE = 315,
    END_OF_FILE = 316,
    RW = 317,
    RO = 318,
    WO = 319,
    INIT = 320,
    END = 321,
    NEW = 322,
    OF = 323,
    BASIC_TYPE_ID = 324,
    EXTENDS = 325,
    SUPER = 326,
    SET_LENGTH = 327,
    SET_CAPACITY = 328,
    RETURN = 329,
    WEAKEN = 330,
    DIE = 331,
    WARN = 332,
    WARN_LEVEL = 333,
    DIAG = 334,
    PRINT = 335,
    SAY = 336,
    STDERR = 337,
    OUTMOST_CLASS_NAME = 338,
    UNWEAKEN = 339,
    ENABLE_OPTIONS = 340,
    DISABLE_OPTIONS = 341,
    FATCAMMA = 342,
    ASSIGN = 343,
    SPECIAL_ASSIGN = 344,
    LOGICAL_OR = 345,
    DEFINED_OR = 346,
    LOGICAL_AND = 347,
    BIT_OR = 348,
    BIT_XOR = 349,
    BIT_AND = 350,
    NUMEQ = 351,
    NUMNE = 352,
    STREQ = 353,
    STRNE = 354,
    NUMGT = 355,
    NUMGE = 356,
    NUMLT = 357,
    NUMLE = 358,
    STRGT = 359,
    STRGE = 360,
    STRLT = 361,
    STRLE = 362,
    ISA = 363,
    ISA_ERROR = 364,
    IS_TYPE = 365,
    IS_ERROR = 366,
    IS_COMPILE_TYPE = 367,
    NUMERIC_CMP = 368,
    STRING_CMP = 369,
    CAN = 370,
    SHIFT = 371,
    DIVIDE = 372,
    DIVIDE_UNSIGNED_INT = 373,
    DIVIDE_UNSIGNED_LONG = 374,
    MODULO = 375,
    MODULO_UNSIGNED_INT = 376,
    MODULO_UNSIGNED_LONG = 377,
    LOGICAL_NOT = 378,
    BIT_NOT = 379,
    REFERENCE = 380,
    DEREFERENCE = 381,
    PLUS = 382,
    MINUS = 383,
    CONVERT = 384,
    SCALAR = 385,
    STRING_LENGTH = 386,
    ISWEAK = 387,
    TYPE_NAME = 388,
    COMPILE_TYPE_NAME = 389,
    DUMP = 390,
    NEW_STRING_LEN = 391,
    IS_READ_ONLY = 392,
    IS_FIXED_LENGTH = 393,
    COPY = 394,
    ADDRESS = 395,
    IS_OPTIONS = 396,
    CAPACITY = 397,
    CALLER = 398,
    INC = 399,
    DEC = 400,
    ARROW = 401
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_LIB_SPVM_BUILDER_INCLUDE_SPVM_YACC_H_INCLUDED  */
