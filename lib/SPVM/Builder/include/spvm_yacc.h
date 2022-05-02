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
    IF = 274,
    UNLESS = 275,
    ELSIF = 276,
    ELSE = 277,
    FOR = 278,
    WHILE = 279,
    LAST = 280,
    NEXT = 281,
    SWITCH = 282,
    CASE = 283,
    DEFAULT = 284,
    BREAK = 285,
    EVAL = 286,
    NAME = 287,
    VAR_NAME = 288,
    CONSTANT = 289,
    EXCEPTION_VAR = 290,
    UNDEF = 291,
    VOID = 292,
    BYTE = 293,
    SHORT = 294,
    INT = 295,
    LONG = 296,
    FLOAT = 297,
    DOUBLE = 298,
    STRING = 299,
    OBJECT = 300,
    TRUE = 301,
    FALSE = 302,
    END_OF_FILE = 303,
    DOT3 = 304,
    FATCAMMA = 305,
    RW = 306,
    RO = 307,
    WO = 308,
    INIT = 309,
    NEW = 310,
    OF = 311,
    RETURN = 312,
    WEAKEN = 313,
    DIE = 314,
    WARN = 315,
    PRINT = 316,
    CURRENT_CLASS_NAME = 317,
    UNWEAKEN = 318,
    ASSIGN = 319,
    SPECIAL_ASSIGN = 320,
    LOGICAL_OR = 321,
    LOGICAL_AND = 322,
    BIT_OR = 323,
    BIT_XOR = 324,
    BIT_AND = 325,
    NUMEQ = 326,
    NUMNE = 327,
    STREQ = 328,
    STRNE = 329,
    NUMGT = 330,
    NUMGE = 331,
    NUMLT = 332,
    NUMLE = 333,
    STRGT = 334,
    STRGE = 335,
    STRLT = 336,
    STRLE = 337,
    ISA = 338,
    NUMERIC_CMP = 339,
    STRING_CMP = 340,
    SHIFT = 341,
    DIVIDE = 342,
    DIVIDE_UNSIGNED_INT = 343,
    DIVIDE_UNSIGNED_LONG = 344,
    REMAINDER = 345,
    REMAINDER_UNSIGNED_INT = 346,
    REMAINDER_UNSIGNED_LONG = 347,
    LOGICAL_NOT = 348,
    BIT_NOT = 349,
    CREATE_REF = 350,
    DEREF = 351,
    PLUS = 352,
    MINUS = 353,
    CONVERT = 354,
    SCALAR = 355,
    STRING_LENGTH = 356,
    ISWEAK = 357,
    REFCNT = 358,
    REFOP = 359,
    DUMP = 360,
    NEW_STRING_LEN = 361,
    IS_READ_ONLY = 362,
    COPY = 363,
    HAS_IMPLEMENT = 364,
    INC = 365,
    DEC = 366,
    ARROW = 367
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED  */
