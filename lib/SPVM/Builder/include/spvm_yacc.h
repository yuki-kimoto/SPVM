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

#ifndef YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED
# define YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED
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
    CURRENT_CLASS = 269,
    MUTABLE = 270,
    DESCRIPTOR = 271,
    MAKE_READ_ONLY = 272,
    INTERFACE = 273,
    ERROR_CODE = 274,
    ERROR = 275,
    IF = 276,
    UNLESS = 277,
    ELSIF = 278,
    ELSE = 279,
    FOR = 280,
    WHILE = 281,
    LAST = 282,
    NEXT = 283,
    SWITCH = 284,
    CASE = 285,
    DEFAULT = 286,
    BREAK = 287,
    EVAL = 288,
    SYMBOL_NAME = 289,
    VAR_NAME = 290,
    CONSTANT = 291,
    EXCEPTION_VAR = 292,
    UNDEF = 293,
    VOID = 294,
    BYTE = 295,
    SHORT = 296,
    INT = 297,
    LONG = 298,
    FLOAT = 299,
    DOUBLE = 300,
    STRING = 301,
    OBJECT = 302,
    TRUE = 303,
    FALSE = 304,
    END_OF_FILE = 305,
    DOT3 = 306,
    FATCAMMA = 307,
    RW = 308,
    RO = 309,
    WO = 310,
    INIT = 311,
    NEW = 312,
    OF = 313,
    CLASS_ID = 314,
    RETURN = 315,
    WEAKEN = 316,
    DIE = 317,
    WARN = 318,
    PRINT = 319,
    CURRENT_CLASS_NAME = 320,
    UNWEAKEN = 321,
    ASSIGN = 322,
    SPECIAL_ASSIGN = 323,
    LOGICAL_OR = 324,
    LOGICAL_AND = 325,
    BIT_OR = 326,
    BIT_XOR = 327,
    BIT_AND = 328,
    NUMEQ = 329,
    NUMNE = 330,
    STREQ = 331,
    STRNE = 332,
    NUMGT = 333,
    NUMGE = 334,
    NUMLT = 335,
    NUMLE = 336,
    STRGT = 337,
    STRGE = 338,
    STRLT = 339,
    STRLE = 340,
    ISA = 341,
    NUMERIC_CMP = 342,
    STRING_CMP = 343,
    SHIFT = 344,
    DIVIDE = 345,
    DIVIDE_UNSIGNED_INT = 346,
    DIVIDE_UNSIGNED_LONG = 347,
    REMAINDER = 348,
    REMAINDER_UNSIGNED_INT = 349,
    REMAINDER_UNSIGNED_LONG = 350,
    LOGICAL_NOT = 351,
    BIT_NOT = 352,
    CREATE_REF = 353,
    DEREF = 354,
    PLUS = 355,
    MINUS = 356,
    CONVERT = 357,
    SCALAR = 358,
    STRING_LENGTH = 359,
    ISWEAK = 360,
    REFCNT = 361,
    REFOP = 362,
    DUMP = 363,
    NEW_STRING_LEN = 364,
    IS_READ_ONLY = 365,
    COPY = 366,
    HAS_IMPL = 367,
    SET_ERROR_CODE = 368,
    INC = 369,
    DEC = 370,
    ARROW = 371
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED  */
