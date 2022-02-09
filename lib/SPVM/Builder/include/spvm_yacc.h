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
    IF = 272,
    UNLESS = 273,
    ELSIF = 274,
    ELSE = 275,
    FOR = 276,
    WHILE = 277,
    LAST = 278,
    NEXT = 279,
    SWITCH = 280,
    CASE = 281,
    DEFAULT = 282,
    BREAK = 283,
    EVAL = 284,
    NAME = 285,
    VAR_NAME = 286,
    CONSTANT = 287,
    EXCEPTION_VAR = 288,
    UNDEF = 289,
    VOID = 290,
    BYTE = 291,
    SHORT = 292,
    INT = 293,
    LONG = 294,
    FLOAT = 295,
    DOUBLE = 296,
    STRING = 297,
    OBJECT = 298,
    TRUE = 299,
    FALSE = 300,
    END_OF_FILE = 301,
    DOT3 = 302,
    FATCAMMA = 303,
    RW = 304,
    RO = 305,
    WO = 306,
    INIT = 307,
    NEW = 308,
    RETURN = 309,
    WEAKEN = 310,
    DIE = 311,
    WARN = 312,
    PRINT = 313,
    CURRENT_CLASS_NAME = 314,
    UNWEAKEN = 315,
    ASSIGN = 316,
    SPECIAL_ASSIGN = 317,
    LOGICAL_OR = 318,
    LOGICAL_AND = 319,
    BIT_OR = 320,
    BIT_XOR = 321,
    BIT_AND = 322,
    NUMEQ = 323,
    NUMNE = 324,
    STREQ = 325,
    STRNE = 326,
    NUMGT = 327,
    NUMGE = 328,
    NUMLT = 329,
    NUMLE = 330,
    STRGT = 331,
    STRGE = 332,
    STRLT = 333,
    STRLE = 334,
    ISA = 335,
    NUMERIC_CMP = 336,
    STRING_CMP = 337,
    SHIFT = 338,
    DIVIDE = 339,
    DIVIDE_UNSIGNED_INT = 340,
    DIVIDE_UNSIGNED_LONG = 341,
    REMAINDER = 342,
    REMAINDER_UNSIGNED_INT = 343,
    REMAINDER_UNSIGNED_LONG = 344,
    LOGICAL_NOT = 345,
    BIT_NOT = 346,
    CREATE_REF = 347,
    DEREF = 348,
    PLUS = 349,
    MINUS = 350,
    CONVERT = 351,
    SCALAR = 352,
    STRING_LENGTH = 353,
    ISWEAK = 354,
    REFCNT = 355,
    REFOP = 356,
    DUMP = 357,
    NEW_STRING_LEN = 358,
    IS_READ_ONLY = 359,
    INC = 360,
    DEC = 361,
    ARROW = 362
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED  */
