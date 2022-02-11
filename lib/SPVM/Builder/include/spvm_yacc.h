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
    COMPATIBLE = 272,
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
    TRUE = 300,
    FALSE = 301,
    END_OF_FILE = 302,
    DOT3 = 303,
    FATCAMMA = 304,
    RW = 305,
    RO = 306,
    WO = 307,
    INIT = 308,
    NEW = 309,
    RETURN = 310,
    WEAKEN = 311,
    DIE = 312,
    WARN = 313,
    PRINT = 314,
    CURRENT_CLASS_NAME = 315,
    UNWEAKEN = 316,
    ASSIGN = 317,
    SPECIAL_ASSIGN = 318,
    LOGICAL_OR = 319,
    LOGICAL_AND = 320,
    BIT_OR = 321,
    BIT_XOR = 322,
    BIT_AND = 323,
    NUMEQ = 324,
    NUMNE = 325,
    STREQ = 326,
    STRNE = 327,
    NUMGT = 328,
    NUMGE = 329,
    NUMLT = 330,
    NUMLE = 331,
    STRGT = 332,
    STRGE = 333,
    STRLT = 334,
    STRLE = 335,
    ISA = 336,
    NUMERIC_CMP = 337,
    STRING_CMP = 338,
    SHIFT = 339,
    DIVIDE = 340,
    DIVIDE_UNSIGNED_INT = 341,
    DIVIDE_UNSIGNED_LONG = 342,
    REMAINDER = 343,
    REMAINDER_UNSIGNED_INT = 344,
    REMAINDER_UNSIGNED_LONG = 345,
    LOGICAL_NOT = 346,
    BIT_NOT = 347,
    CREATE_REF = 348,
    DEREF = 349,
    PLUS = 350,
    MINUS = 351,
    CONVERT = 352,
    SCALAR = 353,
    STRING_LENGTH = 354,
    ISWEAK = 355,
    REFCNT = 356,
    REFOP = 357,
    DUMP = 358,
    NEW_STRING_LEN = 359,
    IS_READ_ONLY = 360,
    COPY = 361,
    INC = 362,
    DEC = 363,
    ARROW = 364
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED  */
