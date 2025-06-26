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
    COPY_FIELDS = 295,
    UNDEF = 296,
    VOID = 297,
    BYTE = 298,
    SHORT = 299,
    INT = 300,
    LONG = 301,
    FLOAT = 302,
    DOUBLE = 303,
    STRING = 304,
    OBJECT = 305,
    TRUE = 306,
    FALSE = 307,
    END_OF_FILE = 308,
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
    ENABLE_OPTIONS = 326,
    DISABLE_OPTIONS = 327,
    FATCAMMA = 328,
    ASSIGN = 329,
    SPECIAL_ASSIGN = 330,
    LOGICAL_OR = 331,
    DEFINED_OR = 332,
    LOGICAL_AND = 333,
    BIT_OR = 334,
    BIT_XOR = 335,
    BIT_AND = 336,
    NUMEQ = 337,
    NUMNE = 338,
    STREQ = 339,
    STRNE = 340,
    NUMGT = 341,
    NUMGE = 342,
    NUMLT = 343,
    NUMLE = 344,
    STRGT = 345,
    STRGE = 346,
    STRLT = 347,
    STRLE = 348,
    ISA = 349,
    ISA_ERROR = 350,
    IS_TYPE = 351,
    IS_ERROR = 352,
    IS_COMPILE_TYPE = 353,
    NUMERIC_CMP = 354,
    STRING_CMP = 355,
    CAN = 356,
    SHIFT = 357,
    DIVIDE = 358,
    DIVIDE_UNSIGNED_INT = 359,
    DIVIDE_UNSIGNED_LONG = 360,
    MODULO = 361,
    MODULO_UNSIGNED_INT = 362,
    MODULO_UNSIGNED_LONG = 363,
    LOGICAL_NOT = 364,
    BIT_NOT = 365,
    REFERENCE = 366,
    DEREFERENCE = 367,
    PLUS = 368,
    MINUS = 369,
    CONVERT = 370,
    SCALAR = 371,
    STRING_LENGTH = 372,
    ISWEAK = 373,
    TYPE_NAME = 374,
    COMPILE_TYPE_NAME = 375,
    DUMP = 376,
    NEW_STRING_LEN = 377,
    IS_READ_ONLY = 378,
    COPY = 379,
    ADDRESS = 380,
    IS_OPTIONS = 381,
    INC = 382,
    DEC = 383,
    ARROW = 384
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_LIB_SPVM_BUILDER_INCLUDE_SPVM_YACC_H_INCLUDED  */
