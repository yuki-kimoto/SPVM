/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse SPVM_yyparse
#define yylex   SPVM_yylex
#define yyerror SPVM_yyerror
#define yylval  SPVM_yylval
#define yychar  SPVM_yychar
#define yydebug SPVM_yydebug
#define yynerrs SPVM_yynerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PACKAGE = 258,
     HAS = 259,
     SUB = 260,
     OUR = 261,
     ENUM = 262,
     MY = 263,
     SELF = 264,
     USE = 265,
     DESCRIPTOR = 266,
     IF = 267,
     UNLESS = 268,
     ELSIF = 269,
     ELSE = 270,
     FOR = 271,
     WHILE = 272,
     LAST = 273,
     NEXT = 274,
     SWITCH = 275,
     CASE = 276,
     DEFAULT = 277,
     EVAL = 278,
     NAME = 279,
     VAR_NAME = 280,
     CONSTANT = 281,
     PACKAGE_VAR_NAME = 282,
     EXCEPTION_VAR = 283,
     UNDEF = 284,
     VOID = 285,
     BYTE = 286,
     SHORT = 287,
     INT = 288,
     LONG = 289,
     FLOAT = 290,
     DOUBLE = 291,
     STRING = 292,
     OBJECT = 293,
     DOT3 = 294,
     FATCAMMA = 295,
     RW = 296,
     RO = 297,
     WO = 298,
     BEGIN = 299,
     RETURN = 300,
     WEAKEN = 301,
     CROAK = 302,
     CURRENT_PACKAGE = 303,
     UNWEAKEN = 304,
     ISWEAK = 305,
     SPECIAL_ASSIGN = 306,
     ASSIGN = 307,
     LOGICAL_OR = 308,
     LOGICAL_AND = 309,
     BIT_XOR = 310,
     BIT_OR = 311,
     STRNE = 312,
     STREQ = 313,
     NUMNE = 314,
     NUMEQ = 315,
     ISA = 316,
     STRLE = 317,
     STRLT = 318,
     STRGE = 319,
     STRGT = 320,
     NUMLE = 321,
     NUMLT = 322,
     NUMGE = 323,
     NUMGT = 324,
     REQUIRE = 325,
     LENGTH = 326,
     SCALAR = 327,
     SHIFT = 328,
     REMAINDER = 329,
     DIVIDE = 330,
     MULTIPLY = 331,
     CAST = 332,
     MINUS = 333,
     PLUS = 334,
     DEREF = 335,
     REF = 336,
     BIT_NOT = 337,
     LOGICAL_NOT = 338,
     DEC = 339,
     INC = 340,
     NEW = 341,
     ARROW = 342
   };
#endif
/* Tokens.  */
#define PACKAGE 258
#define HAS 259
#define SUB 260
#define OUR 261
#define ENUM 262
#define MY 263
#define SELF 264
#define USE 265
#define DESCRIPTOR 266
#define IF 267
#define UNLESS 268
#define ELSIF 269
#define ELSE 270
#define FOR 271
#define WHILE 272
#define LAST 273
#define NEXT 274
#define SWITCH 275
#define CASE 276
#define DEFAULT 277
#define EVAL 278
#define NAME 279
#define VAR_NAME 280
#define CONSTANT 281
#define PACKAGE_VAR_NAME 282
#define EXCEPTION_VAR 283
#define UNDEF 284
#define VOID 285
#define BYTE 286
#define SHORT 287
#define INT 288
#define LONG 289
#define FLOAT 290
#define DOUBLE 291
#define STRING 292
#define OBJECT 293
#define DOT3 294
#define FATCAMMA 295
#define RW 296
#define RO 297
#define WO 298
#define BEGIN 299
#define RETURN 300
#define WEAKEN 301
#define CROAK 302
#define CURRENT_PACKAGE 303
#define UNWEAKEN 304
#define ISWEAK 305
#define SPECIAL_ASSIGN 306
#define ASSIGN 307
#define LOGICAL_OR 308
#define LOGICAL_AND 309
#define BIT_XOR 310
#define BIT_OR 311
#define STRNE 312
#define STREQ 313
#define NUMNE 314
#define NUMEQ 315
#define ISA 316
#define STRLE 317
#define STRLT 318
#define STRGE 319
#define STRGT 320
#define NUMLE 321
#define NUMLT 322
#define NUMGE 323
#define NUMGT 324
#define REQUIRE 325
#define LENGTH 326
#define SCALAR 327
#define SHIFT 328
#define REMAINDER 329
#define DIVIDE 330
#define MULTIPLY 331
#define CAST 332
#define MINUS 333
#define PLUS 334
#define DEREF 335
#define REF 336
#define BIT_NOT 337
#define LOGICAL_NOT 338
#define DEC 339
#define INC 340
#define NEW 341
#define ARROW 342




/* Copy the first part of user declarations.  */
#line 5 "yacc/spvm_yacc.y"

  #include <stdio.h>
  
  #include "spvm_compiler.h"
  #include "spvm_yacc_util.h"
  #include "spvm_toke.h"
  #include "spvm_op.h"
  #include "spvm_dumper.h"
  #include "spvm_constant.h"
  #include "spvm_type.h"
  #include "spvm_block.h"
  #include "spvm_list.h"
  #include "spvm_package.h"


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 303 "spvm_yacc.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1742

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  102
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  87
/* YYNRULES -- Number of rules.  */
#define YYNRULES  226
/* YYNRULES -- Number of states.  */
#define YYNSTATES  426

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   342

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    57,     2,
      95,    99,     2,    75,   100,    76,    77,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    96,    98,
       2,     2,     2,     2,    81,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    93,     2,   101,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    94,     2,    97,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    78,
      79,    80,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    13,    17,    23,
      27,    28,    30,    33,    35,    37,    39,    41,    44,    46,
      48,    51,    55,    62,    65,    68,    72,    73,    75,    79,
      82,    84,    86,    90,    96,   103,   114,   125,   135,   148,
     149,   151,   153,   157,   161,   163,   167,   168,   170,   174,
     175,   177,   180,   182,   183,   185,   188,   190,   192,   194,
     196,   198,   200,   202,   204,   206,   208,   211,   214,   217,
     220,   224,   227,   231,   234,   237,   240,   243,   246,   249,
     251,   261,   267,   273,   277,   280,   286,   293,   300,   301,
     304,   311,   315,   318,   319,   321,   323,   325,   326,   328,
     330,   332,   334,   336,   338,   340,   342,   344,   346,   348,
     350,   352,   354,   356,   358,   360,   362,   364,   366,   368,
     370,   374,   376,   380,   383,   385,   388,   391,   394,   397,
     400,   403,   406,   410,   414,   418,   422,   426,   430,   434,
     438,   442,   446,   448,   450,   454,   456,   458,   460,   464,
     468,   472,   476,   480,   484,   488,   492,   496,   500,   504,
     508,   512,   516,   520,   523,   527,   531,   534,   537,   539,
     543,   546,   550,   556,   561,   566,   571,   578,   582,   589,
     593,   599,   605,   610,   615,   618,   621,   624,   627,   630,
     633,   636,   641,   645,   651,   654,   657,   660,   665,   670,
     673,   675,   677,   679,   681,   683,   685,   687,   689,   691,
     693,   695,   697,   699,   701,   704,   708,   712,   717,   722,
     724,   726,   728,   730,   731,   733,   737
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     103,     0,    -1,   104,    -1,    -1,   105,    -1,   105,   106,
      -1,   106,    -1,     3,   180,   107,    -1,     3,   180,    96,
     128,   107,    -1,    94,   108,    97,    -1,    -1,   109,    -1,
     109,   110,    -1,   110,    -1,   120,    -1,   121,    -1,   114,
      -1,   119,    98,    -1,   112,    -1,   111,    -1,    44,   141,
      -1,    10,   180,    98,    -1,    10,   180,    95,   187,    99,
      98,    -1,    71,   180,    -1,     7,   115,    -1,    94,   116,
      97,    -1,    -1,   117,    -1,   117,   100,   118,    -1,   117,
     100,    -1,   118,    -1,   186,    -1,   186,    52,    26,    -1,
       6,    27,    96,   128,   179,    -1,     4,   185,    96,   128,
     179,    98,    -1,   128,     5,   186,    96,   184,    95,   123,
     126,    99,   141,    -1,   128,     5,   186,    96,   184,    95,
     123,   126,    99,    98,    -1,   128,     5,    96,   184,    95,
     123,   126,    99,   141,    -1,    93,   124,   101,   128,     5,
      96,   184,    95,   123,   126,    99,   141,    -1,    -1,   124,
      -1,   127,    -1,   127,   100,   124,    -1,   124,   100,   125,
      -1,   125,    -1,   177,    96,   179,    -1,    -1,    39,    -1,
     177,    96,     9,    -1,    -1,   129,    -1,   129,    11,    -1,
      11,    -1,    -1,   131,    -1,   131,   132,    -1,   132,    -1,
     139,    -1,   133,    -1,   134,    -1,   141,    -1,   135,    -1,
     136,    -1,   137,    -1,   142,    -1,   138,    -1,   146,    98,
      -1,    18,    98,    -1,    19,    98,    -1,    45,    98,    -1,
      45,   146,    98,    -1,    47,    98,    -1,    47,   146,    98,
      -1,   166,    98,    -1,   167,    98,    -1,   168,    98,    -1,
     169,    98,    -1,   170,    98,    -1,   171,    98,    -1,    98,
      -1,    16,    95,   145,    98,   144,    98,   145,    99,   141,
      -1,    17,    95,   144,    99,   141,    -1,    20,    95,   146,
      99,   141,    -1,    21,   146,    96,    -1,    22,    96,    -1,
      12,    95,   113,    99,   141,    -1,    12,    95,   144,    99,
     141,   140,    -1,    13,    95,   144,    99,   141,   140,    -1,
      -1,    15,   141,    -1,    14,    95,   144,    99,   141,   140,
      -1,    94,   130,    97,    -1,    23,   141,    -1,    -1,   147,
      -1,   146,    -1,   152,    -1,    -1,   146,    -1,   177,    -1,
      28,    -1,   178,    -1,    26,    -1,    29,    -1,   164,    -1,
     165,    -1,   163,    -1,   161,    -1,   159,    -1,   160,    -1,
     172,    -1,   173,    -1,   176,    -1,   151,    -1,   148,    -1,
     175,    -1,   174,    -1,   158,    -1,   149,    -1,   150,    -1,
      95,   147,    99,    -1,    48,    -1,   147,   100,   146,    -1,
     147,   100,    -1,   146,    -1,    75,   146,    -1,    76,   146,
      -1,    87,   146,    -1,    90,   146,    -1,   146,    90,    -1,
      89,   146,    -1,   146,    89,    -1,   146,    75,   146,    -1,
     146,    76,   146,    -1,   146,    80,   146,    -1,   146,    79,
     146,    -1,   146,    78,   146,    -1,   146,    55,   146,    -1,
     146,    57,   146,    -1,   146,    56,   146,    -1,   146,    74,
     146,    -1,   146,    77,   146,    -1,   153,    -1,   157,    -1,
      95,   152,    99,    -1,   154,    -1,   155,    -1,   156,    -1,
     146,    61,   146,    -1,   146,    60,   146,    -1,   146,    70,
     146,    -1,   146,    69,   146,    -1,   146,    68,   146,    -1,
     146,    67,   146,    -1,   146,    59,   146,    -1,   146,    58,
     146,    -1,   146,    66,   146,    -1,   146,    65,   146,    -1,
     146,    64,   146,    -1,   146,    63,   146,    -1,   146,    62,
     179,    -1,   144,    53,   144,    -1,   144,    54,   144,    -1,
      88,   144,    -1,   146,    52,   146,    -1,   146,    51,   146,
      -1,    91,   180,    -1,    91,   183,    -1,   122,    -1,    93,
     143,   101,    -1,   162,   146,    -1,    95,   179,    99,    -1,
     146,    92,    93,   146,   101,    -1,   163,    93,   146,   101,
      -1,   165,    93,   146,   101,    -1,    24,    95,   143,    99,
      -1,   180,    92,   186,    95,   143,    99,    -1,   180,    92,
     186,    -1,   146,    92,   186,    95,   143,    99,    -1,   146,
      92,   186,    -1,   146,    92,    95,   143,    99,    -1,   146,
      92,    94,   185,    97,    -1,   165,    94,   185,    97,    -1,
     163,    94,   185,    97,    -1,    46,   165,    -1,    46,   163,
      -1,    49,   165,    -1,    49,   163,    -1,    50,   165,    -1,
      50,   163,    -1,    81,   146,    -1,    81,    94,   146,    97,
      -1,    73,    81,   146,    -1,    73,    81,    94,   146,    97,
      -1,    72,   146,    -1,    85,   177,    -1,    86,   177,    -1,
      86,    94,   177,    97,    -1,     8,   177,    96,   179,    -1,
       8,   177,    -1,    25,    -1,    27,    -1,   180,    -1,   182,
      -1,   181,    -1,    24,    -1,    31,    -1,    32,    -1,    33,
      -1,    34,    -1,    35,    -1,    36,    -1,    38,    -1,    37,
      -1,   180,    57,    -1,   180,    93,   101,    -1,   182,    93,
     101,    -1,   180,    93,   146,   101,    -1,   182,    93,   146,
     101,    -1,   179,    -1,    30,    -1,    24,    -1,    24,    -1,
      -1,   188,    -1,   188,   100,   186,    -1,   186,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    67,    67,    75,    78,    91,   105,   108,   112,   118,
     127,   130,   142,   156,   159,   160,   161,   162,   163,   164,
     167,   176,   180,   186,   193,   199,   208,   211,   224,   238,
     242,   245,   249,   255,   261,   267,   271,   277,   281,   297,
     300,   311,   319,   338,   352,   355,   362,   365,   368,   379,
     382,   395,   409,   413,   416,   429,   443,   446,   447,   448,
     449,   450,   451,   452,   453,   454,   455,   461,   462,   463,
     467,   471,   475,   479,   480,   481,   482,   483,   484,   485,
     491,   497,   503,   509,   515,   518,   526,   537,   551,   554,
     558,   564,   572,   579,   582,   595,   596,   600,   603,   606,
     607,   608,   609,   610,   611,   612,   613,   614,   615,   616,
     617,   618,   619,   620,   621,   622,   623,   624,   625,   626,
     627,   643,   646,   660,   664,   670,   675,   680,   686,   691,
     698,   703,   710,   715,   720,   724,   728,   732,   736,   741,
     745,   749,   755,   756,   757,   763,   764,   765,   768,   772,
     776,   780,   784,   788,   794,   798,   802,   806,   810,   814,
     820,   826,   830,   834,   840,   844,   850,   854,   858,   881,
     888,   895,   901,   905,   909,   915,   919,   923,   928,   932,
     937,   943,   947,   951,   957,   963,   969,   975,   981,   987,
     993,   998,  1003,  1008,  1015,  1020,  1026,  1031,  1038,  1042,
    1048,  1054,  1060,  1061,  1062,  1065,  1069,  1075,  1081,  1087,
    1093,  1099,  1105,  1111,  1119,  1125,  1129,  1135,  1139,  1145,
    1146,  1152,  1155,  1159,  1162,  1175,  1189
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PACKAGE", "HAS", "SUB", "OUR", "ENUM",
  "MY", "SELF", "USE", "DESCRIPTOR", "IF", "UNLESS", "ELSIF", "ELSE",
  "FOR", "WHILE", "LAST", "NEXT", "SWITCH", "CASE", "DEFAULT", "EVAL",
  "NAME", "VAR_NAME", "CONSTANT", "PACKAGE_VAR_NAME", "EXCEPTION_VAR",
  "UNDEF", "VOID", "BYTE", "SHORT", "INT", "LONG", "FLOAT", "DOUBLE",
  "STRING", "OBJECT", "DOT3", "FATCAMMA", "RW", "RO", "WO", "BEGIN",
  "RETURN", "WEAKEN", "CROAK", "CURRENT_PACKAGE", "UNWEAKEN", "ISWEAK",
  "SPECIAL_ASSIGN", "ASSIGN", "LOGICAL_OR", "LOGICAL_AND", "BIT_XOR",
  "BIT_OR", "'&'", "STRNE", "STREQ", "NUMNE", "NUMEQ", "ISA", "STRLE",
  "STRLT", "STRGE", "STRGT", "NUMLE", "NUMLT", "NUMGE", "NUMGT", "REQUIRE",
  "LENGTH", "SCALAR", "SHIFT", "'+'", "'-'", "'.'", "REMAINDER", "DIVIDE",
  "MULTIPLY", "'@'", "CAST", "MINUS", "PLUS", "DEREF", "REF", "BIT_NOT",
  "LOGICAL_NOT", "DEC", "INC", "NEW", "ARROW", "'['", "'{'", "'('", "':'",
  "'}'", "';'", "')'", "','", "']'", "$accept", "grammar", "opt_packages",
  "packages", "package", "package_block", "opt_declarations",
  "declarations", "declaration", "begin_block", "use", "require",
  "enumeration", "enumeration_block", "opt_enumeration_values",
  "enumeration_values", "enumeration_value", "our", "has", "sub",
  "anon_sub", "opt_args", "args", "arg", "opt_vaarg", "invocant",
  "opt_descriptors", "descriptors", "opt_statements", "statements",
  "statement", "for_statement", "while_statement", "switch_statement",
  "case_statement", "default_statement", "if_require_statement",
  "if_statement", "else_statement", "block", "eval_block",
  "opt_expressions", "term", "opt_expression", "expression", "expressions",
  "unary_op", "inc", "dec", "binary_op", "condition", "comparison_op",
  "num_comparison_op", "str_comparison_op", "isa", "logical_op", "assign",
  "new", "array_init", "convert_type", "convert", "array_access",
  "call_sub", "field_access", "weaken_field", "weaken_array_element",
  "unweaken_field", "unweaken_array_element", "isweak_field",
  "isweak_array_element", "array_length", "string_length", "deref", "ref",
  "my_var", "var", "package_var_access", "type", "basic_type", "ref_type",
  "array_type", "array_type_with_length", "type_or_void", "field_name",
  "sub_name", "opt_sub_names", "sub_names", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,    38,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,    43,    45,    46,   329,   330,
     331,    64,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,    91,   123,    40,    58,   125,    59,    41,
      44,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   102,   103,   104,   104,   105,   105,   106,   106,   107,
     108,   108,   109,   109,   110,   110,   110,   110,   110,   110,
     111,   112,   112,   113,   114,   115,   116,   116,   117,   117,
     117,   118,   118,   119,   120,   121,   121,   122,   122,   123,
     123,   123,   123,   124,   124,   125,   126,   126,   127,   128,
     128,   129,   129,   130,   130,   131,   131,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     133,   134,   135,   136,   137,   138,   139,   139,   140,   140,
     140,   141,   142,   143,   143,   144,   144,   145,   145,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   147,   147,   147,   148,   148,   148,   149,   149,
     150,   150,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   152,   152,   152,   153,   153,   153,   154,   154,
     154,   154,   154,   154,   155,   155,   155,   155,   155,   155,
     156,   157,   157,   157,   158,   158,   159,   159,   159,   160,
     161,   162,   163,   163,   163,   164,   164,   164,   164,   164,
     164,   165,   165,   165,   166,   167,   168,   169,   170,   171,
     172,   172,   172,   172,   173,   174,   175,   175,   176,   176,
     177,   178,   179,   179,   179,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   181,   182,   182,   183,   183,   184,
     184,   185,   186,   187,   187,   188,   188
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     3,     5,     3,
       0,     1,     2,     1,     1,     1,     1,     2,     1,     1,
       2,     3,     6,     2,     2,     3,     0,     1,     3,     2,
       1,     1,     3,     5,     6,    10,    10,     9,    12,     0,
       1,     1,     3,     3,     1,     3,     0,     1,     3,     0,
       1,     2,     1,     0,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       3,     2,     3,     2,     2,     2,     2,     2,     2,     1,
       9,     5,     5,     3,     2,     5,     6,     6,     0,     2,
       6,     3,     2,     0,     1,     1,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     3,     2,     1,     2,     2,     2,     2,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     1,     3,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     3,     2,     2,     1,     3,
       2,     3,     5,     4,     4,     4,     6,     3,     6,     3,
       5,     5,     4,     4,     2,     2,     2,     2,     2,     2,
       2,     4,     3,     5,     2,     2,     2,     4,     4,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     3,     3,     4,     4,     1,
       1,     1,     1,     0,     1,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     2,     4,     6,   205,   206,   207,   208,
     209,   210,   211,   213,   212,     0,     1,     5,    10,    49,
       7,     0,     0,     0,     0,    52,     0,     0,    11,    13,
      19,    18,    16,     0,    14,    15,     0,    50,     0,   221,
       0,     0,    26,    24,     0,    49,    20,     9,    12,    17,
       0,    51,     8,    49,    49,   222,     0,    27,    30,    31,
     223,    21,     0,     0,     0,     0,     0,     0,     0,     0,
      49,     0,     0,   205,   200,   102,   201,   100,   103,    49,
      49,    49,   121,    49,    49,    49,     0,    49,    49,    49,
       0,     0,    49,    49,    49,     0,    49,    49,    79,   168,
       0,     0,    49,    56,    58,    59,    61,    62,    63,    65,
      57,    60,    64,     0,   114,   118,   119,   113,   117,   108,
     109,   107,    49,   106,   104,   105,     0,     0,     0,     0,
       0,     0,   110,   111,   116,   115,   112,    99,   101,     0,
       0,     0,     0,    25,    29,     0,   226,     0,   224,   199,
      49,    49,    49,    49,    67,    68,    49,     0,    84,    92,
      49,    69,     0,     0,   106,   105,    71,     0,   106,   105,
     106,   105,   194,    49,   125,   126,    49,   190,   195,     0,
     196,   127,   130,   128,   166,     0,   167,     0,    44,     0,
     124,    94,    99,     0,     0,   202,   204,   203,     0,    91,
      55,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,   131,   129,     0,    66,   170,    49,     0,
      49,     0,    73,    74,    75,    76,    77,    78,     0,     0,
       0,   202,    33,    28,    32,     0,     0,     0,     0,    49,
      49,     0,     0,    95,    96,   142,   145,   146,   147,   143,
       0,     0,    98,     0,     0,    83,     0,    70,    72,    49,
     192,     0,     0,    49,    49,     0,    49,   169,   123,     0,
     120,   171,   214,     0,     0,     0,   165,   164,   137,   139,
     138,   140,   132,   133,   141,   136,   135,   134,    49,     0,
      49,   179,     0,     0,     0,     0,   177,   220,   219,     0,
      34,    22,   225,   198,    23,   163,     0,    95,    96,     0,
      49,    49,     0,    49,    49,    49,    49,     0,    49,    49,
      49,    49,    49,    49,    49,    49,     0,    49,     0,     0,
     175,     0,   191,   197,   215,     0,   216,     0,    43,     0,
       0,   122,    45,     0,     0,     0,     0,    49,   173,   183,
     174,   182,    49,    39,   144,    85,   161,   162,    88,   155,
     154,   149,   148,   160,   159,   158,   157,   156,   153,   152,
     151,   150,    88,     0,    81,    82,   193,   217,   218,     0,
      39,   172,   181,   180,     0,     0,    46,    40,    41,     0,
       0,     0,    86,    87,    49,     0,    46,   178,   176,    47,
       0,     0,     0,    49,    89,     0,     0,     0,     0,    42,
      48,     0,     0,    39,     0,    36,    35,     0,    80,    46,
      37,    88,     0,    90,     0,    38
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    20,    27,    28,    29,    30,
      31,   241,    32,    43,    56,    57,    58,    33,    34,    35,
      99,   386,   387,   188,   400,   388,   100,    37,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   392,   111,
     112,   189,   242,   251,   243,   191,   114,   115,   116,   117,
     244,   245,   246,   247,   248,   249,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   298,   139,   196,
     197,   186,   299,    40,    59,   147,   148
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -370
static const yytype_int16 yypact[] =
{
      56,   325,    70,  -370,    56,  -370,  -370,  -370,  -370,  -370,
    -370,  -370,  -370,  -370,  -370,    22,  -370,  -370,    95,    78,
    -370,    49,    68,    13,   325,  -370,    23,    -4,    95,  -370,
    -370,  -370,  -370,    25,  -370,  -370,   132,   146,    76,  -370,
      47,    84,   150,  -370,   -74,   732,  -370,  -370,  -370,  -370,
     150,  -370,  -370,    78,    78,  -370,    90,   101,  -370,   152,
     150,  -370,   196,   128,   130,   136,   137,   129,   135,   140,
    1294,   142,    23,   161,  -370,  -370,  -370,  -370,  -370,   851,
    1294,   937,  -370,  1294,  1294,  1294,   171,  1294,  1294,  1160,
     196,   -10,  1294,  1294,  1294,   325,   439,  1294,  -370,  -370,
     255,   168,   820,  -370,  -370,  -370,  -370,  -370,  -370,  -370,
    -370,  -370,  -370,  1458,  -370,  -370,  -370,  -370,  -370,  -370,
    -370,  -370,  1294,   -48,  -370,    55,   172,   173,   187,   188,
     190,   191,  -370,  -370,  -370,  -370,  -370,  -370,  -370,   198,
     195,   325,   325,  -370,   150,   268,  -370,   197,   199,   201,
    1088,  1191,   968,  1191,  -370,  -370,  1294,  1578,  -370,  -370,
     127,  -370,  1488,  1650,   -22,    10,  -370,  1518,    79,    85,
      88,   100,   429,  1263,    99,    99,  1294,    99,  -370,   196,
    -370,    99,   117,   117,   202,   205,  -370,    66,  -370,   204,
    1650,   200,   206,    97,   207,   -18,  -370,   214,   212,  -370,
    -370,  1294,  1294,  1294,  1294,  1294,  1294,  1294,  1294,  1294,
    1294,  1294,  1294,  -370,  -370,   -14,  -370,    99,  1294,    49,
    1294,    49,  -370,  -370,  -370,  -370,  -370,  -370,   150,   245,
     213,   -35,  -370,  -370,  -370,   216,   150,   325,   325,  1191,
    1191,   218,   -36,  1620,  -370,  -370,  -370,  -370,  -370,  -370,
     -34,   220,  1650,   -16,  1428,  -370,   222,  -370,  -370,  1294,
      99,   365,   226,   525,   557,   196,    78,  -370,  1057,   325,
    -370,  -370,  -370,   211,   223,   245,  1650,  1650,   258,   258,
     429,   696,    42,    42,    42,    99,    99,    99,  1294,    49,
     127,   224,   -23,   228,    35,   230,   233,  -370,  -370,   234,
    -370,  -370,  -370,  -370,  -370,  -370,   157,  1398,   232,    23,
    1191,  1191,    23,  1294,  1294,  1294,  1294,   325,  1294,  1294,
    1294,  1294,  1294,  1294,  1294,  1294,    23,  1191,    23,    23,
    -370,  1548,  -370,  -370,  -370,   608,  -370,  1321,  -370,   206,
     308,  1650,  -370,   244,  1351,   243,   246,   127,  -370,  -370,
    -370,  -370,   127,   196,  -370,  -370,   288,  -370,   215,  1650,
    1650,  1650,  1650,  -370,  1650,  1650,  1650,  1650,  1650,  1650,
    1650,  1650,   215,   -13,  -370,  -370,  -370,  -370,  -370,   248,
     196,  -370,  -370,  -370,   252,   253,   315,   264,   265,   259,
     272,    23,  -370,  -370,   643,   245,   315,  -370,  -370,  -370,
     269,   196,   210,  1191,  -370,   270,   275,   285,   -30,   264,
    -370,   -11,    23,   196,    23,  -370,  -370,    23,  -370,   315,
    -370,   215,   286,  -370,    23,  -370
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -370,  -370,  -370,  -370,   382,   353,  -370,  -370,   367,  -370,
    -370,  -370,  -370,  -370,  -370,  -370,   249,  -370,  -370,  -370,
    -370,  -336,   -91,   131,  -369,  -370,     7,  -370,  -370,  -370,
     295,  -370,  -370,  -370,  -370,  -370,  -370,  -370,  -359,   -25,
    -370,  -157,  -142,     4,   170,   -90,  -370,  -370,  -370,  -370,
     160,  -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,
    -370,    46,  -370,    62,  -370,  -370,  -370,  -370,  -370,  -370,
    -370,  -370,  -370,  -370,  -370,   -60,  -370,   -93,    -1,  -370,
     307,  -370,  -267,  -207,   -44,  -370,  -370
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -190
static const yytype_int16 yytable[] =
{
      15,    46,   149,   256,   194,   187,   140,   193,   343,   250,
      55,   253,   293,   393,   295,    74,   146,   310,   311,   310,
     311,    60,   272,    44,    61,    36,    38,   407,   201,   202,
     178,   180,   203,   204,   205,    36,   192,   310,   311,   272,
     310,   311,   310,   311,   396,   218,   219,   159,   230,   232,
     422,   206,   207,   208,   209,   210,   211,   212,   273,     1,
     141,   142,   423,   312,    45,   326,   213,   214,   415,   215,
      16,   218,   219,    39,   228,   273,  -185,   419,   348,   288,
     289,   290,   345,   328,   179,   394,   201,   202,   417,    25,
     203,   204,   205,    47,   184,    41,   195,   305,   306,    21,
     -49,    22,    23,   220,   221,    24,    25,    42,  -184,   206,
     207,   208,   209,   210,   211,   212,    18,    45,    19,   262,
     210,   211,   212,    49,   213,   214,   164,   215,   406,   168,
     170,   213,   214,   346,   215,    62,   350,    50,    25,    26,
     231,   231,   165,    53,   303,   169,   171,   194,   220,   221,
     193,    73,    74,    75,    76,    77,    78,    51,     7,     8,
       9,    10,    11,    12,    13,    14,   265,   266,   356,   357,
      18,   291,   218,   219,    55,    82,   342,  -187,   220,   221,
      54,   218,   219,  -186,   296,   373,  -189,   143,   213,   214,
     384,   215,   302,   220,   221,   385,   270,   268,  -188,    85,
      86,   144,    87,    88,   145,   339,  -190,  -190,    89,   215,
     310,   311,    90,    91,    92,   113,    93,    94,    95,   410,
      96,    74,    97,   150,   363,   151,   -93,   154,   231,   390,
     391,   152,   153,   155,     6,   156,   231,   304,   158,   195,
     157,     7,     8,     9,    10,    11,    12,    13,    14,   162,
     163,   167,   173,   163,   163,   172,   160,   174,   175,   177,
     198,   411,   181,   182,   183,   199,   190,   190,   231,     6,
     222,   223,   113,   340,   231,   297,     7,     8,     9,    10,
      11,    12,    13,    14,   355,   224,   225,   358,   226,   227,
     228,   229,   217,   389,   234,   263,   235,   237,   264,   236,
     268,   372,   269,   374,   375,   267,   271,   274,   275,   342,
     409,   300,   334,   379,   301,   205,   231,   309,   327,   347,
     389,   330,   252,   333,   336,   349,   254,   351,   352,   353,
     190,   354,   206,   207,   208,   209,   210,   211,   212,   380,
     382,   339,   311,   260,   395,   383,   261,   213,   214,     6,
     215,   397,   398,   389,   399,   402,     7,     8,     9,    10,
      11,    12,    13,    14,   265,   401,   404,   403,   408,   412,
     413,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   416,   414,   424,    17,   418,   292,   420,
     294,    52,   421,   233,   231,    48,   338,   200,   405,   425,
     308,   231,   185,     0,     0,     0,     0,     0,     0,     0,
     307,     0,     0,     0,     0,     0,   201,   202,     0,     0,
     203,   204,   205,     0,     0,     0,     0,     0,     0,   331,
       0,     0,     0,   335,   337,     0,     0,     0,   341,   206,
     207,   208,   209,   210,   211,   212,     0,    62,     0,     0,
      25,     0,     0,     0,   213,   214,     0,   215,   344,     0,
     190,     0,   332,    73,    74,    75,    76,    77,    78,     0,
       7,     8,     9,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,   359,   360,   361,   362,    82,   364,   365,
     366,   367,   368,   369,   370,   371,     0,     0,     0,     0,
       0,     0,     0,   206,   207,   208,   209,   210,   211,   212,
       0,    85,    86,     0,    87,    88,     0,   190,   213,   214,
      89,   215,   190,     0,    90,    91,    92,     0,    93,    94,
      95,     0,    96,    62,    97,     0,    25,     0,     0,     0,
     -93,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      74,    75,    76,    77,    78,     0,     7,     8,     9,    10,
      11,    12,    13,    14,   252,    62,     0,     0,    25,     0,
       0,     0,     0,    82,     0,     0,     0,     0,     0,     0,
       0,    73,    74,    75,    76,    77,    78,     0,     7,     8,
       9,    10,    11,    12,    13,    14,     0,    85,    86,     0,
      87,    88,     0,     0,     0,    82,    89,     0,     0,     0,
      90,    91,    92,     0,    93,    94,    95,     0,    96,     0,
      97,     0,     0,     0,     0,     0,   334,     0,     0,    85,
      86,     0,    87,    88,     0,     0,     0,     0,    89,     0,
       0,     0,    90,    91,    92,     0,    93,    94,    95,     0,
      96,    62,    97,     0,    25,     0,     0,     0,   336,   201,
     202,     0,     0,   203,   204,   205,     0,    73,    74,    75,
      76,    77,    78,     0,     7,     8,     9,    10,    11,    12,
      13,    14,   206,   207,   208,   209,   210,   211,   212,     0,
       0,    82,     0,     0,     0,     0,     0,   213,   214,     0,
     215,     0,     0,     0,     0,     0,     0,     0,     0,   377,
       0,     0,     0,     0,     0,    85,    86,     0,    87,    88,
       0,     0,     0,     0,    89,     0,     0,     0,    90,    91,
      92,     0,    93,    94,    95,     0,    96,     0,    97,     0,
      62,     0,   -97,    25,    63,    64,     0,     0,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,     0,     7,     8,     9,    10,    11,    12,    13,
      14,   207,   208,   209,   210,   211,   212,    79,    80,    81,
      82,    83,    84,     0,     0,   213,   214,     0,   215,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    85,    86,     0,    87,    88,     0,
       0,     0,     0,    89,     0,     0,     0,    90,    91,    92,
       0,    93,    94,    95,     0,    96,    45,    97,    62,   -53,
      98,    25,    63,    64,     0,     0,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    62,
       0,     0,    25,     0,     0,    79,    80,    81,    82,    83,
      84,     0,     0,     0,     0,    73,    74,    75,    76,    77,
      78,     0,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,    85,    86,     0,    87,    88,     0,     0,    82,
       0,    89,     0,     0,     0,    90,    91,    92,     0,    93,
      94,    95,     0,    96,    45,    97,     0,   -54,    98,     0,
       0,     0,     0,    85,    86,     0,    87,    88,     0,     0,
       0,     0,    89,     0,     0,     0,    90,    91,    92,     0,
      93,    94,    95,     0,    96,    62,    97,     0,    25,   161,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    73,    74,    75,    76,    77,    78,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    62,     0,     0,    25,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
       0,     0,    73,    74,    75,    76,    77,    78,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,    85,
      86,     0,    87,    88,     0,     0,    82,     0,    89,     0,
       0,     0,    90,    91,    92,     0,    93,    94,    95,     0,
      96,     0,    97,     0,     0,   166,     0,     0,     0,     0,
      85,    86,     0,    87,    88,     0,     0,     0,     0,    89,
       0,     0,     0,    90,    91,    92,     0,    93,    94,    95,
       0,    96,   -49,    97,     0,    62,   -97,     0,    25,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    73,    74,    75,    76,    77,    78,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    62,     0,     0,    25,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
       0,     0,    73,    74,    75,    76,    77,    78,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,    85,
      86,     0,    87,    88,     0,     0,    82,     0,    89,     0,
       0,     0,    90,    91,    92,     0,    93,    94,    95,     0,
      96,     0,    97,     0,     0,     0,     0,     0,     0,   238,
      85,    86,     0,    87,    88,     0,     0,     0,    62,    89,
       0,    25,     0,    90,    91,    92,   239,    93,    94,    95,
       0,    96,     0,   240,    73,    74,    75,    76,    77,    78,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    62,
       0,     0,    25,     0,     0,     0,     0,     0,    82,     0,
       0,     0,     0,     0,     0,    73,    74,    75,    76,    77,
      78,     0,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,    85,    86,     0,    87,    88,     0,     0,    82,
       0,    89,     0,     0,     0,    90,    91,    92,     0,    93,
      94,    95,     0,    96,   176,    97,     0,     0,     0,     0,
       0,     0,     0,    85,    86,     0,    87,    88,     0,     0,
       0,    62,    89,     0,    25,     0,    90,    91,    92,   239,
      93,    94,    95,     0,    96,     0,   240,    73,    74,    75,
      76,    77,    78,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    62,     0,     0,    25,     0,     0,     0,     0,
       0,    82,     0,     0,     0,     0,     0,     0,    73,    74,
      75,    76,    77,    78,     0,     7,     8,     9,    10,    11,
      12,    13,    14,     0,     0,    85,    86,     0,    87,    88,
       0,     0,    82,     0,    89,     0,     0,     0,    90,    91,
      92,     0,    93,    94,    95,     0,    96,   259,    97,     0,
       0,     0,     0,     0,     0,     0,    85,    86,     0,    87,
      88,     0,   201,   202,     0,    89,   203,   204,   205,    90,
      91,    92,     0,    93,    94,    95,     0,    96,     0,    97,
       0,     0,     0,     0,     0,   206,   207,   208,   209,   210,
     211,   212,   201,   202,     0,     0,   203,   204,   205,     0,
     213,   214,     0,   215,     0,     0,     0,     0,     0,     0,
       0,     0,   378,     0,     0,   206,   207,   208,   209,   210,
     211,   212,     0,     0,     0,     0,     0,     0,     0,     0,
     213,   214,     0,   215,     0,     0,     0,     0,     0,   201,
     202,     0,   381,   203,   204,   205,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,     0,
       0,     0,   206,   207,   208,   209,   210,   211,   212,   201,
     202,     0,     0,   203,   204,   205,     0,   213,   214,     0,
     215,     0,     0,     0,     0,     0,     0,  -124,  -124,     0,
       0,     0,   206,   207,   208,   209,   210,   211,   212,   201,
     202,     0,     0,   203,   204,   205,     0,   213,   214,     0,
     215,     0,     0,     0,     0,     0,     0,   329,     0,     0,
       0,     0,   206,   207,   208,   209,   210,   211,   212,   201,
     202,     0,     0,   203,   204,   205,     0,   213,   214,     0,
     215,     0,     0,     0,     0,     0,   216,     0,     0,     0,
       0,     0,   206,   207,   208,   209,   210,   211,   212,   201,
     202,     0,     0,   203,   204,   205,     0,   213,   214,     0,
     215,     0,     0,     0,     0,     0,   257,     0,     0,     0,
       0,     0,   206,   207,   208,   209,   210,   211,   212,   201,
     202,     0,     0,   203,   204,   205,     0,   213,   214,     0,
     215,     0,     0,     0,     0,     0,   258,     0,     0,     0,
       0,     0,   206,   207,   208,   209,   210,   211,   212,   201,
     202,     0,     0,   203,   204,   205,     0,   213,   214,     0,
     215,     0,     0,     0,     0,   376,     0,     0,     0,     0,
       0,     0,   206,   207,   208,   209,   210,   211,   212,     0,
       0,     0,     0,     0,     0,     0,     0,   213,   214,     0,
     215,   201,   202,     0,   255,   203,   204,   205,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,     0,     0,     0,   206,   207,   208,   209,   210,   211,
     212,   201,   202,     0,     0,   203,   204,   205,     0,   213,
     214,     0,   215,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   206,   207,   208,   209,   210,   211,
     212,     0,     0,     0,     0,     0,     0,     0,     0,   213,
     214,     0,   215
};

static const yytype_int16 yycheck[] =
{
       1,    26,    62,   160,    97,    96,    50,    97,   275,   151,
      24,   153,   219,   372,   221,    25,    60,    53,    54,    53,
      54,    95,    57,    24,    98,    18,    19,   396,    51,    52,
      90,    91,    55,    56,    57,    28,    96,    53,    54,    57,
      53,    54,    53,    54,   380,    93,    94,    72,   141,   142,
     419,    74,    75,    76,    77,    78,    79,    80,    93,     3,
      53,    54,   421,    99,    94,    99,    89,    90,    98,    92,
       0,    93,    94,    24,    92,    93,    98,   413,   101,    93,
      94,    95,   289,    99,    94,    98,    51,    52,    99,    11,
      55,    56,    57,    97,    95,    27,    97,   239,   240,     4,
       5,     6,     7,    93,    94,    10,    11,    94,    98,    74,
      75,    76,    77,    78,    79,    80,    94,    94,    96,   179,
      78,    79,    80,    98,    89,    90,    80,    92,   395,    83,
      84,    89,    90,   290,    92,     8,   101,     5,    11,    44,
     141,   142,    80,    96,   237,    83,    84,   240,    93,    94,
     240,    24,    25,    26,    27,    28,    29,    11,    31,    32,
      33,    34,    35,    36,    37,    38,   100,   101,   310,   311,
      94,   215,    93,    94,    24,    48,   269,    98,    93,    94,
      96,    93,    94,    98,   228,   327,    98,    97,    89,    90,
     347,    92,   236,    93,    94,   352,    99,   100,    98,    72,
      73,   100,    75,    76,    52,   265,    89,    90,    81,    92,
      53,    54,    85,    86,    87,    45,    89,    90,    91,     9,
      93,    25,    95,    95,   317,    95,    99,    98,   229,    14,
      15,    95,    95,    98,    24,    95,   237,   238,    96,   240,
      70,    31,    32,    33,    34,    35,    36,    37,    38,    79,
      80,    81,    81,    83,    84,    85,    95,    87,    88,    89,
       5,   403,    92,    93,    94,    97,    96,    97,   269,    24,
      98,    98,   102,   266,   275,    30,    31,    32,    33,    34,
      35,    36,    37,    38,   309,    98,    98,   312,    98,    98,
      92,    96,   122,   353,    26,    93,    99,    96,    93,   100,
     100,   326,    96,   328,   329,   101,    99,    93,    96,   402,
     401,    98,   101,     5,    98,    57,   317,    99,    98,    95,
     380,    99,   152,    97,   101,    97,   156,    97,    95,    95,
     160,    99,    74,    75,    76,    77,    78,    79,    80,    95,
      97,   401,    54,   173,    96,    99,   176,    89,    90,    24,
      92,    99,    99,   413,    39,    96,    31,    32,    33,    34,
      35,    36,    37,    38,   100,   100,   391,    95,    99,    99,
      95,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   408,    99,    99,     4,   412,   218,   414,
     220,    38,   417,   144,   395,    28,   265,   102,   394,   424,
     240,   402,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     240,    -1,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,
      55,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,   259,
      -1,    -1,    -1,   263,   264,    -1,    -1,    -1,   268,    74,
      75,    76,    77,    78,    79,    80,    -1,     8,    -1,    -1,
      11,    -1,    -1,    -1,    89,    90,    -1,    92,   288,    -1,
     290,    -1,    97,    24,    25,    26,    27,    28,    29,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,   313,   314,   315,   316,    48,   318,   319,
     320,   321,   322,   323,   324,   325,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    75,    76,    77,    78,    79,    80,
      -1,    72,    73,    -1,    75,    76,    -1,   347,    89,    90,
      81,    92,   352,    -1,    85,    86,    87,    -1,    89,    90,
      91,    -1,    93,     8,    95,    -1,    11,    -1,    -1,    -1,
     101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      25,    26,    27,    28,    29,    -1,    31,    32,    33,    34,
      35,    36,    37,    38,   394,     8,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    25,    26,    27,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    72,    73,    -1,
      75,    76,    -1,    -1,    -1,    48,    81,    -1,    -1,    -1,
      85,    86,    87,    -1,    89,    90,    91,    -1,    93,    -1,
      95,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    72,
      73,    -1,    75,    76,    -1,    -1,    -1,    -1,    81,    -1,
      -1,    -1,    85,    86,    87,    -1,    89,    90,    91,    -1,
      93,     8,    95,    -1,    11,    -1,    -1,    -1,   101,    51,
      52,    -1,    -1,    55,    56,    57,    -1,    24,    25,    26,
      27,    28,    29,    -1,    31,    32,    33,    34,    35,    36,
      37,    38,    74,    75,    76,    77,    78,    79,    80,    -1,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    89,    90,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
      -1,    -1,    -1,    -1,    -1,    72,    73,    -1,    75,    76,
      -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,    85,    86,
      87,    -1,    89,    90,    91,    -1,    93,    -1,    95,    -1,
       8,    -1,    99,    11,    12,    13,    -1,    -1,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    -1,    31,    32,    33,    34,    35,    36,    37,
      38,    75,    76,    77,    78,    79,    80,    45,    46,    47,
      48,    49,    50,    -1,    -1,    89,    90,    -1,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    -1,    75,    76,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    85,    86,    87,
      -1,    89,    90,    91,    -1,    93,    94,    95,     8,    97,
      98,    11,    12,    13,    -1,    -1,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    31,    32,    33,    34,    35,    36,    37,    38,     8,
      -1,    -1,    11,    -1,    -1,    45,    46,    47,    48,    49,
      50,    -1,    -1,    -1,    -1,    24,    25,    26,    27,    28,
      29,    -1,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    72,    73,    -1,    75,    76,    -1,    -1,    48,
      -1,    81,    -1,    -1,    -1,    85,    86,    87,    -1,    89,
      90,    91,    -1,    93,    94,    95,    -1,    97,    98,    -1,
      -1,    -1,    -1,    72,    73,    -1,    75,    76,    -1,    -1,
      -1,    -1,    81,    -1,    -1,    -1,    85,    86,    87,    -1,
      89,    90,    91,    -1,    93,     8,    95,    -1,    11,    98,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    25,    26,    27,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,     8,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    25,    26,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    72,
      73,    -1,    75,    76,    -1,    -1,    48,    -1,    81,    -1,
      -1,    -1,    85,    86,    87,    -1,    89,    90,    91,    -1,
      93,    -1,    95,    -1,    -1,    98,    -1,    -1,    -1,    -1,
      72,    73,    -1,    75,    76,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    -1,    85,    86,    87,    -1,    89,    90,    91,
      -1,    93,     5,    95,    -1,     8,    98,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    25,    26,    27,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,     8,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    25,    26,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    72,
      73,    -1,    75,    76,    -1,    -1,    48,    -1,    81,    -1,
      -1,    -1,    85,    86,    87,    -1,    89,    90,    91,    -1,
      93,    -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      72,    73,    -1,    75,    76,    -1,    -1,    -1,     8,    81,
      -1,    11,    -1,    85,    86,    87,    88,    89,    90,    91,
      -1,    93,    -1,    95,    24,    25,    26,    27,    28,    29,
      -1,    31,    32,    33,    34,    35,    36,    37,    38,     8,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    25,    26,    27,    28,
      29,    -1,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    72,    73,    -1,    75,    76,    -1,    -1,    48,
      -1,    81,    -1,    -1,    -1,    85,    86,    87,    -1,    89,
      90,    91,    -1,    93,    94,    95,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    -1,    75,    76,    -1,    -1,
      -1,     8,    81,    -1,    11,    -1,    85,    86,    87,    88,
      89,    90,    91,    -1,    93,    -1,    95,    24,    25,    26,
      27,    28,    29,    -1,    31,    32,    33,    34,    35,    36,
      37,    38,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,
      26,    27,    28,    29,    -1,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    72,    73,    -1,    75,    76,
      -1,    -1,    48,    -1,    81,    -1,    -1,    -1,    85,    86,
      87,    -1,    89,    90,    91,    -1,    93,    94,    95,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    -1,    75,
      76,    -1,    51,    52,    -1,    81,    55,    56,    57,    85,
      86,    87,    -1,    89,    90,    91,    -1,    93,    -1,    95,
      -1,    -1,    -1,    -1,    -1,    74,    75,    76,    77,    78,
      79,    80,    51,    52,    -1,    -1,    55,    56,    57,    -1,
      89,    90,    -1,    92,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   101,    -1,    -1,    74,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    90,    -1,    92,    -1,    -1,    -1,    -1,    -1,    51,
      52,    -1,   101,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    -1,
      -1,    -1,    74,    75,    76,    77,    78,    79,    80,    51,
      52,    -1,    -1,    55,    56,    57,    -1,    89,    90,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    -1,    99,   100,    -1,
      -1,    -1,    74,    75,    76,    77,    78,    79,    80,    51,
      52,    -1,    -1,    55,    56,    57,    -1,    89,    90,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    -1,    99,    -1,    -1,
      -1,    -1,    74,    75,    76,    77,    78,    79,    80,    51,
      52,    -1,    -1,    55,    56,    57,    -1,    89,    90,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,
      -1,    -1,    74,    75,    76,    77,    78,    79,    80,    51,
      52,    -1,    -1,    55,    56,    57,    -1,    89,    90,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,
      -1,    -1,    74,    75,    76,    77,    78,    79,    80,    51,
      52,    -1,    -1,    55,    56,    57,    -1,    89,    90,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,
      -1,    -1,    74,    75,    76,    77,    78,    79,    80,    51,
      52,    -1,    -1,    55,    56,    57,    -1,    89,    90,    -1,
      92,    -1,    -1,    -1,    -1,    97,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    75,    76,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    -1,
      92,    51,    52,    -1,    96,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    74,    75,    76,    77,    78,    79,
      80,    51,    52,    -1,    -1,    55,    56,    57,    -1,    89,
      90,    -1,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    75,    76,    77,    78,    79,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      90,    -1,    92
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,   103,   104,   105,   106,    24,    31,    32,    33,
      34,    35,    36,    37,    38,   180,     0,   106,    94,    96,
     107,     4,     6,     7,    10,    11,    44,   108,   109,   110,
     111,   112,   114,   119,   120,   121,   128,   129,   128,    24,
     185,    27,    94,   115,   180,    94,   141,    97,   110,    98,
       5,    11,   107,    96,    96,    24,   116,   117,   118,   186,
      95,    98,     8,    12,    13,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    45,
      46,    47,    48,    49,    50,    72,    73,    75,    76,    81,
      85,    86,    87,    89,    90,    91,    93,    95,    98,   122,
     128,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   141,   142,   146,   148,   149,   150,   151,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   180,
     186,   128,   128,    97,   100,    52,   186,   187,   188,   177,
      95,    95,    95,    95,    98,    98,    95,   146,    96,   141,
      95,    98,   146,   146,   163,   165,    98,   146,   163,   165,
     163,   165,   146,    81,   146,   146,    94,   146,   177,    94,
     177,   146,   146,   146,   180,   182,   183,   124,   125,   143,
     146,   147,   177,   147,   179,   180,   181,   182,     5,    97,
     132,    51,    52,    55,    56,    57,    74,    75,    76,    77,
      78,    79,    80,    89,    90,    92,    98,   146,    93,    94,
      93,    94,    98,    98,    98,    98,    98,    98,    92,    96,
     179,   180,   179,   118,    26,    99,   100,    96,    71,    88,
      95,   113,   144,   146,   152,   153,   154,   155,   156,   157,
     144,   145,   146,   144,   146,    96,   143,    98,    98,    94,
     146,   146,   177,    93,    93,   100,   101,   101,   100,    96,
      99,    99,    57,    93,    93,    96,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,    93,    94,
      95,   186,   146,   185,   146,   185,   186,    30,   179,   184,
      98,    98,   186,   179,   180,   144,   144,   146,   152,    99,
      53,    54,    99,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    99,    98,    99,    99,
      99,   146,    97,    97,   101,   146,   101,   146,   125,   177,
     128,   146,   179,   184,   146,   185,   143,    95,   101,    97,
     101,    97,    95,    95,    99,   141,   144,   144,   141,   146,
     146,   146,   146,   179,   146,   146,   146,   146,   146,   146,
     146,   146,   141,   144,   141,   141,    97,   101,   101,     5,
      95,   101,    97,    99,   143,   143,   123,   124,   127,   177,
      14,    15,   140,   140,    98,    96,   123,    99,    99,    39,
     126,   100,    96,    95,   141,   145,   184,   126,    99,   124,
       9,   144,    99,    95,    99,    98,   141,    99,   141,   123,
     141,   141,   126,   140,    99,   141
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (compiler, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, compiler)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, compiler); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, SPVM_COMPILER* compiler)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, compiler)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    SPVM_COMPILER* compiler;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (compiler);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, SPVM_COMPILER* compiler)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, compiler)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    SPVM_COMPILER* compiler;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, compiler);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, SPVM_COMPILER* compiler)
#else
static void
yy_reduce_print (yyvsp, yyrule, compiler)
    YYSTYPE *yyvsp;
    int yyrule;
    SPVM_COMPILER* compiler;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , compiler);
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, compiler); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, SPVM_COMPILER* compiler)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, compiler)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    SPVM_COMPILER* compiler;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (compiler);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (SPVM_COMPILER* compiler);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (SPVM_COMPILER* compiler)
#else
int
yyparse (compiler)
    SPVM_COMPILER* compiler;
#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 68 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_grammar(compiler, (yyvsp[(1) - (1)].opval));
      compiler->op_grammar = (yyval.opval);
    ;}
    break;

  case 3:
#line 75 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 4:
#line 79 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (1)].opval));
        (yyval.opval) = op_list;
      }
    ;}
    break;

  case 5:
#line 92 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (2)].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[(1) - (2)].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (2)].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(2) - (2)].opval));
      
      (yyval.opval) = op_list;
    ;}
    break;

  case 7:
#line 109 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval), (yyvsp[(3) - (3)].opval), NULL);
    ;}
    break;

  case 8:
#line 113 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(5) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 9:
#line 119 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_class_block;
    ;}
    break;

  case 10:
#line 127 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 11:
#line 131 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, (yyval.opval), (yyval.opval)->last, (yyvsp[(1) - (1)].opval));
      }
    ;}
    break;

  case 12:
#line 143 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (2)].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[(1) - (2)].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (2)].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(2) - (2)].opval));
      
      (yyval.opval) = op_list;
    ;}
    break;

  case 20:
#line 168 "yacc/spvm_yacc.y"
    { 
      SPVM_OP* op_sub = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUB, compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "BEGIN", compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_void_type = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_sub(compiler, op_sub, op_sub_name, op_void_type, NULL, NULL, (yyvsp[(2) - (2)].opval), NULL, NULL, 1);
    ;}
    break;

  case 21:
#line 177 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval), NULL, 0);
    ;}
    break;

  case 22:
#line 181 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(2) - (6)].opval), (yyvsp[(4) - (6)].opval), 0);
    ;}
    break;

  case 23:
#line 187 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_use(compiler, op_use, (yyvsp[(2) - (2)].opval), NULL, 1);
    ;}
    break;

  case 24:
#line 194 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 25:
#line 200 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_enum_block;
    ;}
    break;

  case 26:
#line 208 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 27:
#line 212 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (1)].opval));
        (yyval.opval) = op_list;
      }
    ;}
    break;

  case 28:
#line 225 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (3)].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[(1) - (3)].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (3)].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(3) - (3)].opval));
      
      (yyval.opval) = op_list;
    ;}
    break;

  case 29:
#line 239 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 31:
#line 246 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 32:
#line 250 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 33:
#line 256 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_our(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(4) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 34:
#line 262 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_has(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(2) - (6)].opval), (yyvsp[(4) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 35:
#line 268 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (10)].opval), (yyvsp[(3) - (10)].opval), (yyvsp[(5) - (10)].opval), (yyvsp[(7) - (10)].opval), (yyvsp[(1) - (10)].opval), (yyvsp[(10) - (10)].opval), NULL, (yyvsp[(8) - (10)].opval), 0);
     ;}
    break;

  case 36:
#line 272 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (10)].opval), (yyvsp[(3) - (10)].opval), (yyvsp[(5) - (10)].opval), (yyvsp[(7) - (10)].opval), (yyvsp[(1) - (10)].opval), NULL, NULL, (yyvsp[(8) - (10)].opval), 0);
     ;}
    break;

  case 37:
#line 278 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (9)].opval), NULL, (yyvsp[(4) - (9)].opval), (yyvsp[(6) - (9)].opval), (yyvsp[(1) - (9)].opval), (yyvsp[(9) - (9)].opval), NULL, (yyvsp[(7) - (9)].opval), 0);
     ;}
    break;

  case 38:
#line 282 "yacc/spvm_yacc.y"
    {
       SPVM_OP* op_list_args;
       if ((yyvsp[(2) - (12)].opval)->id == SPVM_OP_C_ID_LIST) {
         op_list_args = (yyvsp[(2) - (12)].opval);
       }
       else {
         op_list_args = SPVM_OP_new_op_list(compiler, (yyvsp[(2) - (12)].opval)->file, (yyvsp[(2) - (12)].opval)->line);
         SPVM_OP_insert_child(compiler, op_list_args, op_list_args->last, (yyvsp[(2) - (12)].opval));
       }
       
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(5) - (12)].opval), NULL, (yyvsp[(7) - (12)].opval), (yyvsp[(9) - (12)].opval), (yyvsp[(4) - (12)].opval), (yyvsp[(12) - (12)].opval), op_list_args, (yyvsp[(10) - (12)].opval), 0);
     ;}
    break;

  case 39:
#line 297 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 40:
#line 301 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (1)].opval));
        (yyval.opval) = op_list;
      }
    ;}
    break;

  case 41:
#line 312 "yacc/spvm_yacc.y"
    {
       // Add invocant to arguments
       SPVM_OP* op_args = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
       SPVM_OP_insert_child(compiler, op_args, op_args->last, (yyvsp[(1) - (1)].opval));
       
       (yyval.opval) = op_args;
    ;}
    break;

  case 42:
#line 320 "yacc/spvm_yacc.y"
    {
      // Add invocant to arguments
      SPVM_OP* op_args;
      if ((yyvsp[(3) - (3)].opval)->id == SPVM_OP_C_ID_LIST) {
        op_args = (yyvsp[(3) - (3)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(3) - (3)].opval));
        op_args = op_list;
      }
      
      SPVM_OP_insert_child(compiler, op_args, op_args->first, (yyvsp[(1) - (3)].opval));
       
      (yyval.opval) = op_args;
    ;}
    break;

  case 43:
#line 339 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (3)].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[(1) - (3)].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (3)].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(3) - (3)].opval));
      
      (yyval.opval) = op_list;
    ;}
    break;

  case 45:
#line 356 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 46:
#line 362 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = NULL;
    ;}
    break;

  case 48:
#line 369 "yacc/spvm_yacc.y"
    {
      SPVM_TYPE* type = SPVM_TYPE_new(compiler);
      type->is_self = 1;
      SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, (yyvsp[(3) - (3)].opval)->file, (yyvsp[(3) - (3)].opval)->line);
      
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), op_type);
    ;}
    break;

  case 49:
#line 379 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 50:
#line 383 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (1)].opval));
        (yyval.opval) = op_list;
      }
    ;}
    break;

  case 51:
#line 396 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (2)].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[(1) - (2)].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (2)].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(2) - (2)].opval));
      
      (yyval.opval) = op_list;
    ;}
    break;

  case 53:
#line 413 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 54:
#line 417 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (1)].opval));
        (yyval.opval) = op_list;
      }
    ;}
    break;

  case 55:
#line 430 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (2)].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[(1) - (2)].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (2)].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(2) - (2)].opval));
      
      (yyval.opval) = op_list;
    ;}
    break;

  case 66:
#line 456 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_expression_statement = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_EXPRESSION_STATEMENT, compiler->cur_file, compiler->cur_line);
      SPVM_OP_insert_child(compiler, op_expression_statement, op_expression_statement->last, (yyvsp[(1) - (2)].opval));
      (yyval.opval) = op_expression_statement;
    ;}
    break;

  case 69:
#line 464 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (2)].opval), NULL);
    ;}
    break;

  case 70:
#line 468 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 71:
#line 472 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (2)].opval), NULL);
    ;}
    break;

  case 72:
#line 476 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 79:
#line 486 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 80:
#line 492 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[(1) - (9)].opval), (yyvsp[(3) - (9)].opval), (yyvsp[(5) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(9) - (9)].opval));
    ;}
    break;

  case 81:
#line 498 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 82:
#line 504 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 83:
#line 510 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 85:
#line 519 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->cur_file, compiler->cur_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 86:
#line 527 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (6)].opval)->file, (yyvsp[(1) - (6)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    ;}
    break;

  case 87:
#line 538 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (6)].opval)->file, (yyvsp[(1) - (6)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    ;}
    break;

  case 88:
#line 551 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 89:
#line 555 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (2)].opval);
    ;}
    break;

  case 90:
#line 559 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
    ;}
    break;

  case 91:
#line 565 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_block;
    ;}
    break;

  case 92:
#line 573 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 93:
#line 579 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 94:
#line 583 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (1)].opval));
        (yyval.opval) = op_list;
      }
    ;}
    break;

  case 97:
#line 600 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 120:
#line 628 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(2) - (3)].opval)->id == SPVM_OP_C_ID_LIST) {
			  SPVM_OP* op_term = (yyvsp[(2) - (3)].opval)->first;
	      SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, compiler->cur_file, compiler->cur_line);
			  while ((op_term = SPVM_OP_sibling(compiler, op_term))) {
			    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term);
  	      SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_term);
  	      op_term = op_stab;
			  }
			  (yyval.opval) = op_sequence;
      }
      else {
        (yyval.opval) = (yyvsp[(2) - (3)].opval);
      }
    ;}
    break;

  case 122:
#line 647 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (3)].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[(1) - (3)].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (3)].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(3) - (3)].opval));
      
      (yyval.opval) = op_list;
    ;}
    break;

  case 123:
#line 661 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 124:
#line 665 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (1)].opval);
    ;}
    break;

  case 125:
#line 671 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 126:
#line 676 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MINUS, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, op_negate, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 127:
#line 681 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 128:
#line 687 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 129:
#line 692 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 130:
#line 699 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 131:
#line 704 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 132:
#line 711 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 133:
#line 716 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 134:
#line 721 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 135:
#line 725 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 136:
#line 729 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 137:
#line 733 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 138:
#line 737 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BIT_AND, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 139:
#line 742 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 140:
#line 746 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 141:
#line 750 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_concat(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 144:
#line 758 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 148:
#line 769 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 149:
#line 773 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 150:
#line 777 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 151:
#line 781 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 152:
#line 785 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 153:
#line 789 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 154:
#line 795 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 155:
#line 799 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 156:
#line 803 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 157:
#line 807 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 158:
#line 811 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 159:
#line 815 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 160:
#line 821 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 161:
#line 827 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_or(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 162:
#line 831 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_and(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 163:
#line 835 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_not(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 164:
#line 841 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 165:
#line 845 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_special_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 166:
#line 851 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 167:
#line 855 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 168:
#line 859 "yacc/spvm_yacc.y"
    {
      // Package
      SPVM_OP* op_package = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PACKAGE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      // Create class block
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      SPVM_OP* op_list_declarations = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP_insert_child(compiler, op_list_declarations, op_list_declarations->last, (yyvsp[(1) - (1)].opval));
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, op_list_declarations);
      
      // Build package
      SPVM_OP_build_package(compiler, op_package, NULL, op_class_block, NULL);

      // Type
      SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, op_package->uv.package->op_type->uv.type, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      // New
      SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      (yyval.opval) = SPVM_OP_build_new(compiler, op_new, op_type, NULL);
    ;}
    break;

  case 169:
#line 882 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 170:
#line 889 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_convert(compiler, op_convert, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 171:
#line 896 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 172:
#line 902 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 173:
#line 906 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 174:
#line 910 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 175:
#line 916 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, NULL, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 176:
#line 920 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 177:
#line 924 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_expressions = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_expressions);
    ;}
    break;

  case 178:
#line 929 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 179:
#line 933 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_expressions = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_expressions);
    ;}
    break;

  case 180:
#line 938 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[(2) - (5)].opval)->file, (yyvsp[(2) - (5)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (5)].opval), op_sub_name, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 181:
#line 944 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 182:
#line 948 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 183:
#line 952 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 184:
#line 958 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 185:
#line 964 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_weaken_array_element(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 186:
#line 970 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 187:
#line 976 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_weaken_array_element(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 188:
#line 982 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 189:
#line 988 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_weaken_array_element(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 190:
#line 994 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 191:
#line 999 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 192:
#line 1004 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 193:
#line 1009 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 194:
#line 1016 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_string_length(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 195:
#line 1021 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_deref(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 196:
#line 1027 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_ref(compiler, op_ref, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 197:
#line 1032 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, (yyvsp[(1) - (4)].opval)->file, (yyvsp[(1) - (4)].opval)->line);
      (yyval.opval) = SPVM_OP_build_ref(compiler, op_ref, (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 198:
#line 1039 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 199:
#line 1043 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 200:
#line 1049 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 201:
#line 1055 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package_var_access(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 205:
#line 1066 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 206:
#line 1070 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_byte_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 207:
#line 1076 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_short_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 208:
#line 1082 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 209:
#line 1088 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_long_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 210:
#line 1094 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_float_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 211:
#line 1100 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_double_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 212:
#line 1106 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_any_object_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 213:
#line 1112 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_string_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 214:
#line 1120 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 215:
#line 1126 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 216:
#line 1130 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 217:
#line 1136 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 218:
#line 1140 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 220:
#line 1147 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 223:
#line 1159 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 224:
#line 1163 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (1)].opval));
        (yyval.opval) = op_list;
      }
    ;}
    break;

  case 225:
#line 1176 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (3)].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[(1) - (3)].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (3)].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(3) - (3)].opval));
      
      (yyval.opval) = op_list;
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3547 "spvm_yacc.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (compiler, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (compiler, yymsg);
	  }
	else
	  {
	    yyerror (compiler, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, compiler);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, compiler);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (compiler, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, compiler);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, compiler);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 1191 "yacc/spvm_yacc.y"


