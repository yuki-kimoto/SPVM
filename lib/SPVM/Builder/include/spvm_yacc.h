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
    END = 320,
    NEW = 321,
    OF = 322,
    BASIC_TYPE_ID = 323,
    EXTENDS = 324,
    SUPER = 325,
    SET_LENGTH = 326,
    SET_CAPACITY = 327,
    RETURN = 328,
    WEAKEN = 329,
    DIE = 330,
    WARN = 331,
    WARN_LEVEL = 332,
    DIAG = 333,
    PRINT = 334,
    SAY = 335,
    STDERR = 336,
    OUTMOST_CLASS_NAME = 337,
    UNWEAKEN = 338,
    ENABLE_OPTIONS = 339,
    DISABLE_OPTIONS = 340,
    FATCAMMA = 341,
    ASSIGN = 342,
    SPECIAL_ASSIGN = 343,
    LOGICAL_OR = 344,
    DEFINED_OR = 345,
    LOGICAL_AND = 346,
    BIT_OR = 347,
    BIT_XOR = 348,
    BIT_AND = 349,
    NUMEQ = 350,
    NUMNE = 351,
    STREQ = 352,
    STRNE = 353,
    NUMGT = 354,
    NUMGE = 355,
    NUMLT = 356,
    NUMLE = 357,
    STRGT = 358,
    STRGE = 359,
    STRLT = 360,
    STRLE = 361,
    ISA = 362,
    ISA_ERROR = 363,
    IS_TYPE = 364,
    IS_ERROR = 365,
    IS_COMPILE_TYPE = 366,
    NUMERIC_CMP = 367,
    STRING_CMP = 368,
    CAN = 369,
    SHIFT = 370,
    DIVIDE = 371,
    DIVIDE_UNSIGNED_INT = 372,
    DIVIDE_UNSIGNED_LONG = 373,
    MODULO = 374,
    MODULO_UNSIGNED_INT = 375,
    MODULO_UNSIGNED_LONG = 376,
    LOGICAL_NOT = 377,
    BIT_NOT = 378,
    REFERENCE = 379,
    DEREFERENCE = 380,
    PLUS = 381,
    MINUS = 382,
    CONVERT = 383,
    SCALAR = 384,
    STRING_LENGTH = 385,
    ISWEAK = 386,
    TYPE_NAME = 387,
    COMPILE_TYPE_NAME = 388,
    DUMP = 389,
    NEW_STRING_LEN = 390,
    IS_READ_ONLY = 391,
    IS_FIXED_LENGTH = 392,
    COPY = 393,
    ADDRESS = 394,
    IS_OPTIONS = 395,
    CAPACITY = 396,
    CALLER = 397,
    INC = 398,
    DEC = 399,
    ARROW = 400
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_LIB_SPVM_BUILDER_INCLUDE_SPVM_YACC_H_INCLUDED  */
