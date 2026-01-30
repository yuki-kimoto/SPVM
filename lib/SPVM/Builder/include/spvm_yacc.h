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
    BREAK_POINT = 294,
    SYMBOL_NAME = 295,
    VAR_NAME = 296,
    CONSTANT = 297,
    EXCEPTION_VAR = 298,
    COPY_FIELDS = 299,
    EXISTS = 300,
    DELETE = 301,
    UNDEF = 302,
    VOID = 303,
    BYTE = 304,
    SHORT = 305,
    INT = 306,
    LONG = 307,
    FLOAT = 308,
    DOUBLE = 309,
    STRING = 310,
    OBJECT = 311,
    ELEMENT = 312,
    TRUE = 313,
    FALSE = 314,
    END_OF_FILE = 315,
    RW = 316,
    RO = 317,
    WO = 318,
    INIT = 319,
    NEW = 320,
    OF = 321,
    BASIC_TYPE_ID = 322,
    EXTENDS = 323,
    SUPER = 324,
    SET_LENGTH = 325,
    SET_CAPACITY = 326,
    RETURN = 327,
    WEAKEN = 328,
    DIE = 329,
    WARN = 330,
    WARN_LEVEL = 331,
    DIAG = 332,
    PRINT = 333,
    SAY = 334,
    STDERR = 335,
    OUTMOST_CLASS_NAME = 336,
    UNWEAKEN = 337,
    ENABLE_OPTIONS = 338,
    DISABLE_OPTIONS = 339,
    FATCAMMA = 340,
    ASSIGN = 341,
    SPECIAL_ASSIGN = 342,
    LOGICAL_OR = 343,
    DEFINED_OR = 344,
    LOGICAL_AND = 345,
    BIT_OR = 346,
    BIT_XOR = 347,
    BIT_AND = 348,
    NUMEQ = 349,
    NUMNE = 350,
    STREQ = 351,
    STRNE = 352,
    NUMGT = 353,
    NUMGE = 354,
    NUMLT = 355,
    NUMLE = 356,
    STRGT = 357,
    STRGE = 358,
    STRLT = 359,
    STRLE = 360,
    ISA = 361,
    ISA_ERROR = 362,
    IS_TYPE = 363,
    IS_ERROR = 364,
    IS_COMPILE_TYPE = 365,
    NUMERIC_CMP = 366,
    STRING_CMP = 367,
    CAN = 368,
    SHIFT = 369,
    DIVIDE = 370,
    DIVIDE_UNSIGNED_INT = 371,
    DIVIDE_UNSIGNED_LONG = 372,
    MODULO = 373,
    MODULO_UNSIGNED_INT = 374,
    MODULO_UNSIGNED_LONG = 375,
    LOGICAL_NOT = 376,
    BIT_NOT = 377,
    REFERENCE = 378,
    DEREFERENCE = 379,
    PLUS = 380,
    MINUS = 381,
    CONVERT = 382,
    SCALAR = 383,
    STRING_LENGTH = 384,
    ISWEAK = 385,
    TYPE_NAME = 386,
    COMPILE_TYPE_NAME = 387,
    DUMP = 388,
    NEW_STRING_LEN = 389,
    IS_READ_ONLY = 390,
    IS_FIXED_LENGTH = 391,
    COPY = 392,
    ADDRESS = 393,
    IS_OPTIONS = 394,
    CAPACITY = 395,
    CALLER = 396,
    INC = 397,
    DEC = 398,
    ARROW = 399
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_LIB_SPVM_BUILDER_INCLUDE_SPVM_YACC_H_INCLUDED  */
