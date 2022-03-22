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
    ALLOW = 267,
    CURRENT_CLASS = 268,
    MUTABLE = 269,
    DESCRIPTOR = 270,
    MAKE_READ_ONLY = 271,
    IMPLEMENT = 272,
    IF = 273,
    UNLESS = 274,
    ELSIF = 275,
    ELSE = 276,
    FOR = 277,
    WHILE = 278,
    LAST = 279,
    NEXT = 280,
    SWITCH = 281,
    CASE = 282,
    DEFAULT = 283,
    BREAK = 284,
    EVAL = 285,
    NAME = 286,
    VAR_NAME = 287,
    CONSTANT = 288,
    EXCEPTION_VAR = 289,
    UNDEF = 290,
    VOID = 291,
    BYTE = 292,
    SHORT = 293,
    INT = 294,
    LONG = 295,
    FLOAT = 296,
    DOUBLE = 297,
    STRING = 298,
    OBJECT = 299,
    ELEMENT = 300,
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
    RETURN = 311,
    WEAKEN = 312,
    DIE = 313,
    WARN = 314,
    PRINT = 315,
    CURRENT_CLASS_NAME = 316,
    UNWEAKEN = 317,
    ASSIGN = 318,
    SPECIAL_ASSIGN = 319,
    LOGICAL_OR = 320,
    LOGICAL_AND = 321,
    BIT_OR = 322,
    BIT_XOR = 323,
    BIT_AND = 324,
    NUMEQ = 325,
    NUMNE = 326,
    STREQ = 327,
    STRNE = 328,
    NUMGT = 329,
    NUMGE = 330,
    NUMLT = 331,
    NUMLE = 332,
    STRGT = 333,
    STRGE = 334,
    STRLT = 335,
    STRLE = 336,
    ISA = 337,
    NUMERIC_CMP = 338,
    STRING_CMP = 339,
    SHIFT = 340,
    DIVIDE = 341,
    DIVIDE_UNSIGNED_INT = 342,
    DIVIDE_UNSIGNED_LONG = 343,
    REMAINDER = 344,
    REMAINDER_UNSIGNED_INT = 345,
    REMAINDER_UNSIGNED_LONG = 346,
    LOGICAL_NOT = 347,
    BIT_NOT = 348,
    CREATE_REF = 349,
    DEREF = 350,
    PLUS = 351,
    MINUS = 352,
    CONVERT = 353,
    SCALAR = 354,
    STRING_LENGTH = 355,
    ISWEAK = 356,
    REFCNT = 357,
    REFOP = 358,
    DUMP = 359,
    NEW_STRING_LEN = 360,
    IS_READ_ONLY = 361,
    COPY = 362,
    HAS_IMPLEMENT = 363,
    INC = 364,
    DEC = 365,
    ARROW = 366
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED  */
