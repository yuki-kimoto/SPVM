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
     REQUIRE = 266,
     ALLOW = 267,
     DESCRIPTOR = 268,
     IF = 269,
     UNLESS = 270,
     ELSIF = 271,
     ELSE = 272,
     FOR = 273,
     WHILE = 274,
     LAST = 275,
     NEXT = 276,
     SWITCH = 277,
     CASE = 278,
     DEFAULT = 279,
     EVAL = 280,
     NAME = 281,
     VAR_NAME = 282,
     CONSTANT = 283,
     EXCEPTION_VAR = 284,
     UNDEF = 285,
     VOID = 286,
     BYTE = 287,
     SHORT = 288,
     INT = 289,
     LONG = 290,
     FLOAT = 291,
     DOUBLE = 292,
     STRING = 293,
     OBJECT = 294,
     DOT3 = 295,
     FATCAMMA = 296,
     RW = 297,
     RO = 298,
     WO = 299,
     BEGIN = 300,
     NEW = 301,
     RETURN = 302,
     WEAKEN = 303,
     DIE = 304,
     CURRENT_PACKAGE = 305,
     UNWEAKEN = 306,
     SPECIAL_ASSIGN = 307,
     ASSIGN = 308,
     LOGICAL_OR = 309,
     LOGICAL_AND = 310,
     BIT_XOR = 311,
     BIT_OR = 312,
     STRNE = 313,
     STREQ = 314,
     NUMNE = 315,
     NUMEQ = 316,
     ISA = 317,
     STRLE = 318,
     STRLT = 319,
     STRGE = 320,
     STRGT = 321,
     NUMLE = 322,
     NUMLT = 323,
     NUMGE = 324,
     NUMGT = 325,
     SHIFT = 326,
     REMAINDER = 327,
     DIVIDE = 328,
     MULTIPLY = 329,
     REFCNT = 330,
     ISWEAK = 331,
     LENGTH = 332,
     SCALAR = 333,
     CONVERT = 334,
     MINUS = 335,
     PLUS = 336,
     DEREF = 337,
     REF = 338,
     BIT_NOT = 339,
     LOGICAL_NOT = 340,
     DEC = 341,
     INC = 342,
     ARROW = 343
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
#define REQUIRE 266
#define ALLOW 267
#define DESCRIPTOR 268
#define IF 269
#define UNLESS 270
#define ELSIF 271
#define ELSE 272
#define FOR 273
#define WHILE 274
#define LAST 275
#define NEXT 276
#define SWITCH 277
#define CASE 278
#define DEFAULT 279
#define EVAL 280
#define NAME 281
#define VAR_NAME 282
#define CONSTANT 283
#define EXCEPTION_VAR 284
#define UNDEF 285
#define VOID 286
#define BYTE 287
#define SHORT 288
#define INT 289
#define LONG 290
#define FLOAT 291
#define DOUBLE 292
#define STRING 293
#define OBJECT 294
#define DOT3 295
#define FATCAMMA 296
#define RW 297
#define RO 298
#define WO 299
#define BEGIN 300
#define NEW 301
#define RETURN 302
#define WEAKEN 303
#define DIE 304
#define CURRENT_PACKAGE 305
#define UNWEAKEN 306
#define SPECIAL_ASSIGN 307
#define ASSIGN 308
#define LOGICAL_OR 309
#define LOGICAL_AND 310
#define BIT_XOR 311
#define BIT_OR 312
#define STRNE 313
#define STREQ 314
#define NUMNE 315
#define NUMEQ 316
#define ISA 317
#define STRLE 318
#define STRLT 319
#define STRGE 320
#define STRGT 321
#define NUMLE 322
#define NUMLT 323
#define NUMGE 324
#define NUMGT 325
#define SHIFT 326
#define REMAINDER 327
#define DIVIDE 328
#define MULTIPLY 329
#define REFCNT 330
#define ISWEAK 331
#define LENGTH 332
#define SCALAR 333
#define CONVERT 334
#define MINUS 335
#define PLUS 336
#define DEREF 337
#define REF 338
#define BIT_NOT 339
#define LOGICAL_NOT 340
#define DEC 341
#define INC 342
#define ARROW 343




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
#line 305 "spvm_yacc.tab.c"

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
#define YYLAST   2566

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  103
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  83
/* YYNRULES -- Number of rules.  */
#define YYNRULES  222
/* YYNRULES -- Number of states.  */
#define YYNSTATES  430

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   343

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    61,     2,
      54,   100,     2,    76,   101,    77,    78,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    97,    99,
       2,     2,     2,     2,    82,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    51,     2,   102,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    53,     2,    98,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    52,    55,    56,    57,
      58,    59,    60,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    79,    80,    81,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    13,    17,    23,
      27,    28,    30,    33,    35,    37,    39,    41,    44,    46,
      48,    50,    53,    57,    64,    67,    71,    74,    78,    79,
      81,    85,    88,    90,    92,    96,   102,   109,   120,   131,
     141,   154,   155,   157,   159,   163,   167,   169,   173,   174,
     176,   180,   181,   183,   186,   188,   189,   191,   194,   196,
     198,   200,   202,   204,   206,   208,   210,   212,   214,   217,
     220,   223,   226,   230,   233,   237,   240,   243,   245,   255,
     261,   267,   271,   276,   279,   281,   286,   290,   294,   297,
     303,   310,   317,   318,   321,   328,   332,   336,   337,   339,
     340,   342,   344,   346,   348,   350,   352,   354,   356,   358,
     360,   362,   364,   366,   368,   370,   372,   374,   376,   378,
     380,   382,   384,   388,   390,   392,   394,   396,   398,   400,
     403,   407,   410,   412,   415,   418,   421,   424,   427,   430,
     433,   437,   441,   445,   449,   453,   457,   461,   465,   469,
     473,   477,   481,   485,   489,   493,   497,   501,   505,   509,
     513,   517,   521,   525,   529,   533,   536,   540,   544,   547,
     550,   552,   556,   561,   567,   572,   577,   582,   589,   593,
     600,   604,   610,   616,   621,   626,   633,   640,   647,   650,
     655,   659,   665,   668,   671,   674,   679,   682,   684,   686,
     688,   690,   692,   694,   696,   698,   700,   702,   704,   706,
     708,   711,   715,   719,   724,   729,   731,   733,   735,   737,
     738,   740,   744
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     104,     0,    -1,   105,    -1,    -1,   106,    -1,   106,   107,
      -1,   107,    -1,     3,   177,   108,    -1,     3,   177,    97,
     130,   108,    -1,    53,   109,    98,    -1,    -1,   110,    -1,
     110,   111,    -1,   111,    -1,   122,    -1,   123,    -1,   116,
      -1,   121,    99,    -1,   113,    -1,   115,    -1,   112,    -1,
      45,   145,    -1,    10,   177,    99,    -1,    10,   177,    54,
     184,   100,    99,    -1,    11,   177,    -1,    12,   177,    99,
      -1,     7,   117,    -1,    53,   118,    98,    -1,    -1,   119,
      -1,   119,   101,   120,    -1,   119,   101,    -1,   120,    -1,
     183,    -1,   183,    56,    28,    -1,     6,    27,    97,   130,
     176,    -1,     4,   182,    97,   130,   176,    99,    -1,   130,
       5,   183,    97,   181,    54,   125,   128,   100,   145,    -1,
     130,     5,   183,    97,   181,    54,   125,   128,   100,    99,
      -1,   130,     5,    97,   181,    54,   125,   128,   100,   145,
      -1,    51,   126,   102,   130,     5,    97,   181,    54,   125,
     128,   100,   145,    -1,    -1,   126,    -1,   129,    -1,   129,
     101,   126,    -1,   126,   101,   127,    -1,   127,    -1,   175,
      97,   176,    -1,    -1,    40,    -1,   175,    97,     9,    -1,
      -1,   131,    -1,   131,    13,    -1,    13,    -1,    -1,   133,
      -1,   133,   134,    -1,   134,    -1,   143,    -1,   135,    -1,
     136,    -1,   145,    -1,   137,    -1,   140,    -1,   141,    -1,
     146,    -1,   142,    -1,   149,    99,    -1,    20,    99,    -1,
      21,    99,    -1,    47,    99,    -1,    47,   149,    99,    -1,
      49,    99,    -1,    49,   149,    99,    -1,   167,    99,    -1,
     168,    99,    -1,    99,    -1,    18,    54,   148,    99,   149,
      99,   148,   100,   145,    -1,    19,    54,   149,   100,   145,
      -1,    22,    54,   149,   100,   138,    -1,    53,   139,    98,
      -1,    53,   139,   141,    98,    -1,   139,   140,    -1,   140,
      -1,    23,   149,    97,   145,    -1,    23,   149,    97,    -1,
      24,    97,   145,    -1,    24,    97,    -1,    14,    54,   114,
     100,   145,    -1,    14,    54,   149,   100,   145,   144,    -1,
      15,    54,   149,   100,   145,   144,    -1,    -1,    17,   145,
      -1,    16,    54,   149,   100,   145,   144,    -1,    53,   132,
      98,    -1,    25,   145,    99,    -1,    -1,   151,    -1,    -1,
     149,    -1,   175,    -1,    29,    -1,    28,    -1,    30,    -1,
     165,    -1,   166,    -1,   164,    -1,   163,    -1,   161,    -1,
     162,    -1,   170,    -1,   171,    -1,   150,    -1,   174,    -1,
     155,    -1,   152,    -1,   173,    -1,   172,    -1,   160,    -1,
     153,    -1,   154,    -1,    54,   151,   100,    -1,    50,    -1,
     169,    -1,   156,    -1,   157,    -1,   158,    -1,   159,    -1,
      83,   175,    -1,   151,   101,   149,    -1,   151,   101,    -1,
     149,    -1,    76,   149,    -1,    77,   149,    -1,    92,   149,
      -1,    95,   149,    -1,   149,    95,    -1,    94,   149,    -1,
     149,    94,    -1,   149,    76,   149,    -1,   149,    77,   149,
      -1,   149,    81,   149,    -1,   149,    80,   149,    -1,   149,
      79,   149,    -1,   149,    59,   149,    -1,   149,    61,   149,
      -1,   149,    60,   149,    -1,   149,    75,   149,    -1,   149,
      78,   149,    -1,   149,    65,   149,    -1,   149,    64,   149,
      -1,   149,    74,   149,    -1,   149,    73,   149,    -1,   149,
      72,   149,    -1,   149,    71,   149,    -1,   149,    63,   149,
      -1,   149,    62,   149,    -1,   149,    70,   149,    -1,   149,
      69,   149,    -1,   149,    68,   149,    -1,   149,    67,   149,
      -1,   149,    66,   176,    -1,   149,    57,   149,    -1,   149,
      58,   149,    -1,    93,   149,    -1,   149,    56,   149,    -1,
     149,    55,   149,    -1,    46,   177,    -1,    46,   180,    -1,
     124,    -1,    51,   147,   102,    -1,    54,   176,   100,   149,
      -1,   149,    96,    51,   149,   102,    -1,   164,    51,   149,
     102,    -1,   166,    51,   149,   102,    -1,    26,    54,   147,
     100,    -1,   177,    96,   183,    54,   147,   100,    -1,   177,
      96,   183,    -1,   149,    96,   183,    54,   147,   100,    -1,
     149,    96,   183,    -1,   149,    96,    54,   147,   100,    -1,
     149,    96,    53,   182,    98,    -1,   166,    53,   182,    98,
      -1,   164,    53,   182,    98,    -1,    48,   175,    96,    53,
     182,    98,    -1,    52,   175,    96,    53,   182,    98,    -1,
      84,   175,    96,    53,   182,    98,    -1,    82,   149,    -1,
      82,    53,   149,    98,    -1,    86,    82,   149,    -1,    86,
      82,    53,   149,    98,    -1,    85,   149,    -1,    90,   175,
      -1,    91,   175,    -1,     8,   175,    97,   176,    -1,     8,
     175,    -1,    27,    -1,   177,    -1,   179,    -1,   178,    -1,
      26,    -1,    32,    -1,    33,    -1,    34,    -1,    35,    -1,
      36,    -1,    37,    -1,    39,    -1,    38,    -1,   177,    61,
      -1,   177,    51,   102,    -1,   179,    51,   102,    -1,   177,
      51,   149,   102,    -1,   179,    51,   149,   102,    -1,   176,
      -1,    31,    -1,    26,    -1,    26,    -1,    -1,   185,    -1,
     185,   101,   183,    -1,   183,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    64,    64,    72,    75,    88,   102,   105,   109,   115,
     124,   127,   139,   153,   156,   157,   158,   159,   160,   161,
     162,   165,   174,   178,   184,   191,   198,   204,   213,   216,
     229,   243,   247,   250,   254,   260,   266,   272,   276,   282,
     286,   302,   305,   316,   324,   343,   357,   360,   367,   370,
     373,   384,   387,   400,   414,   418,   421,   434,   448,   451,
     452,   453,   454,   455,   456,   457,   458,   459,   460,   464,
     465,   466,   470,   474,   478,   482,   483,   484,   490,   496,
     502,   508,   514,   522,   536,   542,   546,   553,   557,   564,
     572,   583,   597,   600,   604,   610,   618,   625,   628,   642,
     645,   648,   649,   650,   651,   652,   653,   654,   655,   656,
     657,   658,   659,   660,   661,   662,   663,   664,   665,   666,
     667,   668,   669,   685,   686,   687,   688,   689,   690,   693,
     699,   713,   717,   723,   728,   733,   739,   744,   751,   756,
     763,   768,   773,   777,   781,   785,   789,   794,   798,   802,
     808,   812,   816,   820,   824,   828,   834,   838,   842,   846,
     850,   854,   860,   866,   870,   874,   880,   884,   890,   894,
     898,   921,   928,   935,   939,   943,   949,   953,   957,   962,
     966,   971,   977,   981,   985,   991,   998,  1005,  1012,  1017,
    1022,  1027,  1034,  1040,  1046,  1053,  1057,  1063,  1069,  1070,
    1071,  1074,  1078,  1084,  1090,  1096,  1102,  1108,  1114,  1120,
    1128,  1134,  1138,  1144,  1148,  1154,  1155,  1161,  1164,  1168,
    1171,  1184,  1198
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PACKAGE", "HAS", "SUB", "OUR", "ENUM",
  "MY", "SELF", "USE", "REQUIRE", "ALLOW", "DESCRIPTOR", "IF", "UNLESS",
  "ELSIF", "ELSE", "FOR", "WHILE", "LAST", "NEXT", "SWITCH", "CASE",
  "DEFAULT", "EVAL", "NAME", "VAR_NAME", "CONSTANT", "EXCEPTION_VAR",
  "UNDEF", "VOID", "BYTE", "SHORT", "INT", "LONG", "FLOAT", "DOUBLE",
  "STRING", "OBJECT", "DOT3", "FATCAMMA", "RW", "RO", "WO", "BEGIN", "NEW",
  "RETURN", "WEAKEN", "DIE", "CURRENT_PACKAGE", "'['", "UNWEAKEN", "'{'",
  "'('", "SPECIAL_ASSIGN", "ASSIGN", "LOGICAL_OR", "LOGICAL_AND",
  "BIT_XOR", "BIT_OR", "'&'", "STRNE", "STREQ", "NUMNE", "NUMEQ", "ISA",
  "STRLE", "STRLT", "STRGE", "STRGT", "NUMLE", "NUMLT", "NUMGE", "NUMGT",
  "SHIFT", "'+'", "'-'", "'.'", "REMAINDER", "DIVIDE", "MULTIPLY", "'@'",
  "REFCNT", "ISWEAK", "LENGTH", "SCALAR", "CONVERT", "MINUS", "PLUS",
  "DEREF", "REF", "BIT_NOT", "LOGICAL_NOT", "DEC", "INC", "ARROW", "':'",
  "'}'", "';'", "')'", "','", "']'", "$accept", "grammar", "opt_packages",
  "packages", "package", "package_block", "opt_declarations",
  "declarations", "declaration", "begin_block", "use", "require", "allow",
  "enumeration", "enumeration_block", "opt_enumeration_values",
  "enumeration_values", "enumeration_value", "our", "has", "sub",
  "anon_sub", "opt_args", "args", "arg", "opt_vaarg", "invocant",
  "opt_descriptors", "descriptors", "opt_statements", "statements",
  "statement", "for_statement", "while_statement", "switch_statement",
  "switch_block", "case_statements", "case_statement", "default_statement",
  "if_require_statement", "if_statement", "else_statement", "block",
  "eval_block", "opt_expressions", "opt_expression", "expression",
  "refcnt", "expressions", "unary_op", "inc", "dec", "binary_op",
  "num_comparison_op", "str_comparison_op", "isa", "logical_op", "assign",
  "new", "array_init", "convert", "array_access", "call_sub",
  "field_access", "weaken_field", "unweaken_field", "isweak_field",
  "array_length", "string_length", "deref", "ref", "my_var", "var", "type",
  "basic_type", "ref_type", "array_type", "array_type_with_length",
  "type_or_void", "field_name", "sub_name", "opt_sub_names", "sub_names", 0
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
     305,    91,   306,   123,    40,   307,   308,   309,   310,   311,
     312,    38,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,    43,    45,    46,   327,
     328,   329,    64,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,    58,   125,    59,
      41,    44,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   103,   104,   105,   105,   106,   106,   107,   107,   108,
     109,   109,   110,   110,   111,   111,   111,   111,   111,   111,
     111,   112,   113,   113,   114,   115,   116,   117,   118,   118,
     119,   119,   119,   120,   120,   121,   122,   123,   123,   124,
     124,   125,   125,   125,   125,   126,   126,   127,   128,   128,
     129,   130,   130,   131,   131,   132,   132,   133,   133,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   135,   136,
     137,   138,   138,   139,   139,   140,   140,   141,   141,   142,
     143,   143,   144,   144,   144,   145,   146,   147,   147,   148,
     148,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   150,
     151,   151,   151,   152,   152,   152,   153,   153,   154,   154,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     156,   156,   156,   156,   156,   156,   157,   157,   157,   157,
     157,   157,   158,   159,   159,   159,   160,   160,   161,   161,
     161,   162,   163,   164,   164,   164,   165,   165,   165,   165,
     165,   165,   166,   166,   166,   167,   168,   169,   170,   170,
     170,   170,   171,   172,   173,   174,   174,   175,   176,   176,
     176,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     178,   179,   179,   180,   180,   181,   181,   182,   183,   184,
     184,   185,   185
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     3,     5,     3,
       0,     1,     2,     1,     1,     1,     1,     2,     1,     1,
       1,     2,     3,     6,     2,     3,     2,     3,     0,     1,
       3,     2,     1,     1,     3,     5,     6,    10,    10,     9,
      12,     0,     1,     1,     3,     3,     1,     3,     0,     1,
       3,     0,     1,     2,     1,     0,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       2,     2,     3,     2,     3,     2,     2,     1,     9,     5,
       5,     3,     4,     2,     1,     4,     3,     3,     2,     5,
       6,     6,     0,     2,     6,     3,     3,     0,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     2,
       3,     2,     1,     2,     2,     2,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     2,     2,
       1,     3,     4,     5,     4,     4,     4,     6,     3,     6,
       3,     5,     5,     4,     4,     6,     6,     6,     2,     4,
       3,     5,     2,     2,     2,     4,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     3,     3,     4,     4,     1,     1,     1,     1,     0,
       1,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     2,     4,     6,   201,   202,   203,   204,
     205,   206,   207,   209,   208,     0,     1,     5,    10,    51,
       7,     0,     0,     0,     0,     0,    54,     0,     0,    11,
      13,    20,    18,    19,    16,     0,    14,    15,     0,    52,
       0,   217,     0,     0,    28,    26,     0,     0,    51,    21,
       9,    12,    17,     0,    53,     8,    51,    51,   218,     0,
      29,    32,    33,   219,    22,    25,     0,     0,     0,     0,
       0,     0,     0,     0,    51,     0,     0,   201,   197,   103,
     102,   104,     0,    51,     0,    51,   123,    51,     0,    51,
      51,    51,    51,     0,     0,    51,     0,     0,     0,    51,
      51,    51,    51,    77,   170,     0,     0,    51,    58,    60,
      61,    63,    64,    65,    67,    59,    62,    66,     0,   113,
     116,   120,   121,   115,   125,   126,   127,   128,   119,   109,
     110,   108,   107,   105,   106,     0,     0,   124,   111,   112,
     118,   117,   114,   101,     0,     0,     0,     0,    27,    31,
       0,   222,     0,   220,   196,    51,    51,    51,    51,    69,
      70,    51,     0,    88,     0,    51,   168,     0,   169,    71,
       0,     0,    73,     0,     0,    46,     0,   132,    98,   101,
       0,     0,     0,   198,   200,   199,   133,   134,    51,   188,
     129,     0,   192,    51,   193,   194,   135,   165,   138,   136,
       0,    95,    57,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,     0,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
     139,   137,     0,    68,    51,     0,    51,     0,    75,    76,
       0,     0,     0,   198,    35,    30,    34,     0,     0,     0,
       0,     0,     0,     0,     0,   100,     0,     0,    86,    87,
      96,     0,    51,    51,    72,     0,    74,     0,    51,   171,
     131,     0,     0,   122,    51,     0,   210,     0,     0,     0,
      51,   190,     0,   167,   166,   163,   164,   145,   147,   146,
     157,   156,   151,   150,   162,   161,   160,   159,   158,   155,
     154,   153,   152,   148,   140,   141,   149,   144,   143,   142,
      51,     0,    51,   180,     0,     0,     0,     0,   178,   216,
     215,     0,    36,    23,   221,   195,    24,     0,     0,     0,
      51,     0,     0,    85,   176,   211,     0,   212,     0,     0,
      45,     0,     0,   130,    47,     0,   172,   189,     0,     0,
       0,     0,     0,     0,    51,   174,   184,   175,   183,    51,
      41,    89,    92,    92,     0,    79,     0,    80,   213,   214,
       0,     0,     0,     0,   191,    41,   173,   182,   181,     0,
       0,    48,    42,    43,     0,     0,     0,    90,    91,    51,
       0,    84,   185,     0,   186,   187,    48,   179,   177,    49,
       0,     0,     0,    51,    93,     0,    81,    83,     0,     0,
       0,     0,    44,    50,     0,     0,    82,    41,     0,    38,
      37,     0,    78,    48,    39,    92,     0,    94,     0,    40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    20,    28,    29,    30,    31,
      32,   251,    33,    34,    45,    59,    60,    61,    35,    36,
      37,   104,   381,   382,   175,   400,   383,   105,    39,   106,
     107,   108,   109,   110,   111,   367,   390,   112,   113,   114,
     115,   387,   116,   117,   176,   254,   177,   119,   178,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   320,   144,   184,   185,   168,   321,    42,
      62,   152,   153
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -376
static const yytype_int16 yypact[] =
{
      34,   240,    41,  -376,    34,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,  -376,  -376,   -26,  -376,  -376,    63,    40,
    -376,    38,    51,    30,   240,   240,  -376,    37,    16,    63,
    -376,  -376,  -376,  -376,  -376,    10,  -376,  -376,   112,   109,
      70,  -376,    32,    33,   102,  -376,   -36,    45,   777,  -376,
    -376,  -376,  -376,   102,  -376,  -376,    40,    40,  -376,    39,
      53,  -376,    83,   102,  -376,  -376,   120,    98,   101,   103,
     115,    86,    88,   136,  1573,    95,    37,   139,  -376,  -376,
    -376,  -376,   240,   953,   120,  1041,  -376,   337,   120,  1573,
    1573,  1573,  1309,   120,   120,  1573,   113,   120,   120,  1573,
    1573,  1573,  1573,  -376,  -376,   191,    99,   865,  -376,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  2084,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,    31,  -376,    67,   100,   105,  -376,  -376,  -376,
    -376,  -376,  -376,  -376,   104,   110,   240,   240,  -376,   102,
     173,  -376,   106,   107,   114,  1397,  1573,  1129,  1573,  -376,
    -376,  1573,  2352,    37,   116,   601,   158,   161,  -376,  -376,
    2129,   118,  -376,  2174,   -68,  -376,   117,  2395,   119,   124,
     126,    -5,   123,   -31,  -376,   165,    -2,    -2,  1573,    -2,
    -376,   128,    -2,  1485,  -376,  -376,    -2,    -2,    11,    11,
     129,  -376,  -376,  1573,  1573,  1573,  1573,  1573,  1573,  1573,
    1573,  1573,  1573,  1573,   240,  1573,  1573,  1573,  1573,  1573,
    1573,  1573,  1573,  1573,  1573,  1573,  1573,  1573,  1573,  1573,
    -376,  -376,    26,  -376,  1573,    38,  1573,    38,  -376,  -376,
     102,   225,   131,   -12,  -376,  -376,  -376,   132,   102,   240,
     240,   127,  1854,  1900,   133,  2395,  1946,  1992,    37,  -376,
    -376,   134,   425,   513,  -376,   175,  -376,   120,    40,  -376,
    1221,   240,   183,  -376,  1573,   135,  -376,   137,  2264,   185,
    1573,    -2,   225,  2395,  2395,  2434,   257,  2470,  2470,   418,
     506,   506,   506,   506,  -376,   594,   594,   594,   594,   594,
     594,   594,   594,    55,    46,    46,    46,    -2,    -2,    -2,
    1573,    38,   601,   187,  1614,   144,  1662,   145,   190,  -376,
    -376,   192,  -376,  -376,  -376,  -376,  -376,    37,    37,    37,
    1573,    37,   194,  -376,  -376,  -376,  1710,  -376,  1758,    38,
    -376,   124,   245,  2395,  -376,    38,    -2,  -376,    38,  2308,
     198,  1806,   147,   153,   601,  -376,  -376,  -376,  -376,   601,
     120,  -376,    43,    43,  2219,  -376,   231,  -376,  -376,  -376,
     169,   171,   182,   184,  -376,   120,  -376,  -376,  -376,   186,
     188,   229,   170,   189,   195,   230,    37,  -376,  -376,   689,
      -9,  -376,  -376,   225,  -376,  -376,   229,  -376,  -376,  -376,
     193,   120,    65,  1573,  -376,   196,  -376,  -376,   197,   233,
     199,   -41,   170,  -376,  2038,    37,  -376,   120,    37,  -376,
    -376,    37,  -376,   229,  -376,    43,   200,  -376,    37,  -376
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -376,  -376,  -376,  -376,   279,   249,  -376,  -376,   262,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,   148,  -376,  -376,
    -376,  -376,  -356,   -86,    27,  -375,  -376,   -13,  -376,  -376,
    -376,   201,  -376,  -376,  -376,  -376,  -376,  -324,   -89,  -376,
    -376,  -353,   -25,  -376,  -156,   -84,   -45,  -376,   218,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,   -62,   -61,    -1,  -376,   227,  -376,  -274,  -224,
     -46,  -376,  -376
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -100
static const yytype_int16 yytable[] =
{
      15,   174,    49,   118,   154,    38,    40,   145,   350,   261,
     388,   315,    48,   317,    74,    75,    38,   151,    63,   396,
     275,   410,   171,    46,    47,   179,   180,    18,   182,   162,
     276,   190,   191,   267,   268,   194,   195,     1,   170,   275,
     173,    16,   391,   146,   147,   186,   187,   189,   426,   276,
     192,   164,    58,    26,   196,   197,   198,   199,   419,   385,
     386,   423,   118,    64,    41,   240,   407,    21,   -51,    22,
      23,    19,   427,    24,   413,    25,    26,   310,    43,   311,
     312,   166,   234,    44,   235,   242,   244,   352,   183,   406,
      48,     6,   230,   231,   232,   273,   270,     7,     8,     9,
      10,    11,    12,    13,    14,  -100,  -100,   232,    27,    52,
     252,   253,   255,   256,    50,   370,   257,    53,   236,   409,
     237,   372,    54,    18,   373,   227,   228,   229,    58,    56,
      57,   224,   225,   226,   227,   228,   229,   148,   259,   150,
     230,   231,   232,   278,    65,   243,   243,    78,   281,   230,
     231,   232,   155,   294,   149,   156,   353,   157,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   158,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   159,   313,   160,   325,   314,
     161,   316,   163,   165,   318,   193,   200,   201,   379,   238,
     240,   246,   324,   380,   239,   341,   247,   241,   248,   262,
     344,   249,   263,   243,   265,   260,   277,   336,   338,   269,
     270,   271,   272,   274,   279,   343,   282,   327,   339,   346,
     322,   323,   330,   333,   334,   349,   345,   335,   348,   337,
     243,   354,   356,   358,   359,   377,   360,   366,   243,   326,
     371,     6,   375,   378,    74,   342,   319,     7,     8,     9,
      10,    11,    12,    13,    14,   351,     6,   392,   393,   399,
     243,   267,     7,     8,     9,    10,    11,    12,    13,    14,
     394,   243,   395,    17,   403,   364,   397,   417,   398,    55,
     401,    51,   402,   411,   340,   416,   415,   245,   384,   418,
     428,   408,   361,   362,   363,   405,   365,   181,   202,   167,
       0,     0,     0,   384,     0,   412,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   341,
       0,   344,     0,     0,   255,    66,     0,     0,     0,     0,
      26,   230,   231,   232,     0,   384,     0,     0,   414,     0,
       0,   404,     0,    77,    78,    79,    80,    81,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,     0,    82,     0,     0,   420,    86,    87,     0,
     422,    89,   243,   424,     0,     0,   425,     0,     0,     0,
       0,   243,     0,   429,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    90,    91,     0,     0,     0,     0,    92,
      93,    94,    95,    96,     0,     0,     0,    97,    98,    99,
     100,   101,   102,    66,     0,     0,     0,     0,    26,   -97,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    77,    78,    79,    80,    81,     0,     7,     8,     9,
      10,    11,    12,    13,    14,     0,     0,     0,     0,     0,
       0,    82,     0,     0,     0,    86,    87,     0,     0,    89,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
       0,    90,    91,     0,     0,     0,     0,    92,    93,    94,
      95,    96,   230,   231,   232,    97,    98,    99,   100,   101,
     102,    66,     0,     0,     0,     0,    26,   335,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    77,
      78,    79,    80,    81,     0,     7,     8,     9,    10,    11,
      12,    13,    14,     0,     0,     0,     0,     0,     0,    82,
       0,     0,     0,    86,    87,     0,     0,    89,  -100,  -100,
    -100,  -100,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,     0,    90,
      91,     0,     0,     0,     0,    92,    93,    94,    95,    96,
     230,   231,   232,    97,    98,    99,   100,   101,   102,    66,
       0,     0,     0,     0,    26,   337,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    77,    78,    79,
      80,    81,     0,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,     0,    82,     0,     0,
       0,    86,    87,     0,     0,    89,     0,     0,     0,     0,
    -100,  -100,  -100,  -100,  -100,  -100,  -100,  -100,  -100,   223,
     224,   225,   226,   227,   228,   229,     0,    90,    91,     0,
       0,     0,     0,    92,    93,    94,    95,    96,   230,   231,
     232,    97,    98,    99,   100,   101,   102,    66,     0,     0,
       0,   -97,    26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    77,    78,    79,    80,    81,
       0,     7,     8,     9,    10,    11,    12,    13,    14,     0,
       0,     0,     0,     0,     0,    82,     0,     0,     0,    86,
      87,     0,     0,    89,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    90,    91,     0,     0,     0,
       0,    92,    93,    94,    95,    96,     0,     0,     0,    97,
      98,    99,   100,   101,   102,    66,     0,     0,     0,   -99,
      26,    67,    68,     0,     0,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,     0,    82,    83,    84,    85,    86,    87,    88,
      48,    89,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    90,    91,     0,     0,     0,     0,    92,
      93,    94,    95,    96,     0,     0,     0,    97,    98,    99,
     100,   101,   102,    66,     0,   -55,   103,     0,    26,    67,
      68,     0,     0,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,     0,     7,     8,     9,
      10,    11,    12,    13,    14,     0,     0,     0,     0,     0,
       0,    82,    83,    84,    85,    86,    87,    88,    48,    89,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    90,    91,     0,     0,     0,     0,    92,    93,    94,
      95,    96,     0,     0,     0,    97,    98,    99,   100,   101,
     102,    66,     0,   -56,   103,     0,    26,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    77,
      78,    79,    80,    81,     0,     7,     8,     9,    10,    11,
      12,    13,    14,     0,     0,     0,     0,     0,     0,    82,
       0,     0,     0,    86,    87,     0,     0,    89,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    90,
      91,     0,     0,     0,     0,    92,    93,    94,    95,    96,
       0,     0,     0,    97,    98,    99,   100,   101,   102,    66,
       0,     0,   169,     0,    26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    77,    78,    79,
      80,    81,     0,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,     0,    82,     0,     0,
       0,    86,    87,     0,     0,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    90,    91,     0,
       0,     0,     0,    92,    93,    94,    95,    96,     0,     0,
       0,    97,    98,    99,   100,   101,   102,    66,     0,     0,
     172,     0,    26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    77,    78,    79,    80,    81,
       0,     7,     8,     9,    10,    11,    12,    13,    14,     0,
       0,     0,     0,     0,     0,    82,     0,     0,     0,    86,
      87,     0,     0,    89,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    90,    91,     0,     0,     0,
       0,    92,    93,    94,    95,    96,     0,     0,     0,    97,
      98,    99,   100,   101,   102,     0,   -51,     0,   -99,    66,
       0,     0,     0,     0,    26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    77,    78,    79,
      80,    81,     0,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,     0,    82,     0,     0,
       0,    86,    87,     0,     0,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    90,    91,     0,
       0,     0,     0,    92,    93,    94,    95,    96,     0,     0,
       0,    97,    98,    99,   100,   101,   102,    66,     0,     0,
       0,     0,    26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    77,    78,    79,    80,    81,
       0,     7,     8,     9,    10,    11,    12,    13,    14,     0,
       0,     0,     0,     0,     0,    82,     0,     0,     0,    86,
      87,     0,   188,    89,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    90,    91,     0,     0,     0,
       0,    92,    93,    94,    95,    96,     0,     0,     0,    97,
      98,    99,   100,   101,   102,    66,     0,     0,   250,     0,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    77,    78,    79,    80,    81,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,     0,    82,     0,     0,     0,    86,    87,     0,
       0,    89,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    90,    91,     0,     0,     0,     0,    92,
      93,    94,    95,    96,     0,     0,     0,    97,    98,    99,
     100,   101,   102,    66,     0,     0,     0,     0,    26,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    77,    78,    79,    80,    81,     0,     7,     8,     9,
      10,    11,    12,    13,    14,     0,     0,     0,     0,     0,
       0,    82,     0,     0,     0,    86,    87,     0,   280,    89,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    90,    91,     0,     0,     0,     0,    92,    93,    94,
      95,    96,     0,     0,     0,    97,    98,    99,   100,   101,
     102,    66,     0,     0,     0,     0,    26,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    77,
      78,    79,    80,    81,     0,     7,     8,     9,    10,    11,
      12,    13,    14,     0,     0,     0,     0,     0,     0,    82,
       0,     0,     0,    86,    87,     0,     0,    89,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    90,
      91,     0,     0,     0,     0,    92,    93,    94,    95,    96,
       0,     0,     0,    97,    98,    99,   100,   101,   102,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   230,   231,
     232,     0,     0,     0,     0,     0,   355,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   230,   231,   232,     0,
       0,     0,     0,     0,   357,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   230,   231,   232,     0,     0,     0,
       0,     0,   368,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   230,   231,   232,     0,     0,     0,     0,     0,
     369,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     230,   231,   232,     0,     0,     0,     0,     0,   376,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   230,   231,
     232,     0,     0,     0,   328,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   230,   231,   232,     0,     0,     0,
     329,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     230,   231,   232,     0,     0,     0,   331,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   230,   231,   232,     0,
       0,     0,   332,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   230,   231,   232,     0,     0,     0,   421,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   230,   231,
     232,     0,     0,   233,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   230,   231,   232,     0,     0,   264,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   230,   231,
     232,     0,     0,   266,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   230,   231,   232,     0,     0,   389,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   230,   231,
     232,     0,   347,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   230,   231,   232,     0,   374,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   230,   231,   232,   258,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   230,
     231,   232,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   230,   231,
     232,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   230,   231,   232
};

static const yytype_int16 yycheck[] =
{
       1,    87,    27,    48,    66,    18,    19,    53,   282,   165,
     363,   235,    53,   237,    23,    24,    29,    63,    54,   375,
      51,   396,    84,    24,    25,    87,    88,    53,    89,    74,
      61,    93,    94,   101,   102,    97,    98,     3,    83,    51,
      85,     0,   366,    56,    57,    90,    91,    92,   423,    61,
      95,    76,    26,    13,    99,   100,   101,   102,    99,    16,
      17,   417,   107,    99,    26,    96,   390,     4,     5,     6,
       7,    97,   425,    10,     9,    12,    13,    51,    27,    53,
      54,    82,    51,    53,    53,   146,   147,   311,    89,    98,
      53,    26,    94,    95,    96,   100,   101,    32,    33,    34,
      35,    36,    37,    38,    39,    94,    95,    96,    45,    99,
     155,   156,   157,   158,    98,   339,   161,     5,    51,   393,
      53,   345,    13,    53,   348,    79,    80,    81,    26,    97,
      97,    76,    77,    78,    79,    80,    81,    98,   163,    56,
      94,    95,    96,   188,    99,   146,   147,    27,   193,    94,
      95,    96,    54,   214,   101,    54,   312,    54,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,    54,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,    99,   232,    99,   249,   234,
      54,   236,    97,    54,   240,    82,     5,    98,   354,    99,
      96,    28,   248,   359,    99,   267,   100,    97,   101,    51,
     271,    97,    51,   214,    96,    99,    51,   262,   263,   102,
     101,    97,    96,   100,    96,   270,    97,   100,    53,   274,
      99,    99,    99,   258,   100,   280,    53,   102,    53,   102,
     241,    54,    98,    98,    54,    98,    54,    53,   249,   250,
       5,    26,    54,   100,    23,   268,    31,    32,    33,    34,
      35,    36,    37,    38,    39,   310,    26,    98,    97,    40,
     271,   101,    32,    33,    34,    35,    36,    37,    38,    39,
      98,   282,    98,     4,    54,   330,   100,    54,   100,    40,
     101,    29,    97,   100,   267,    98,   100,   149,   360,   100,
     100,   390,   327,   328,   329,   389,   331,    89,   107,    82,
      -1,    -1,    -1,   375,    -1,   401,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,   401,
      -1,   402,    -1,    -1,   389,     8,    -1,    -1,    -1,    -1,
      13,    94,    95,    96,    -1,   417,    -1,    -1,   403,    -1,
      -1,   386,    -1,    26,    27,    28,    29,    30,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,   411,    50,    51,    -1,
     415,    54,   393,   418,    -1,    -1,   421,    -1,    -1,    -1,
      -1,   402,    -1,   428,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    -1,    -1,    -1,    -1,    82,
      83,    84,    85,    86,    -1,    -1,    -1,    90,    91,    92,
      93,    94,    95,     8,    -1,    -1,    -1,    -1,    13,   102,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    27,    28,    29,    30,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    -1,    50,    51,    -1,    -1,    54,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      -1,    76,    77,    -1,    -1,    -1,    -1,    82,    83,    84,
      85,    86,    94,    95,    96,    90,    91,    92,    93,    94,
      95,     8,    -1,    -1,    -1,    -1,    13,   102,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      27,    28,    29,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    -1,    50,    51,    -1,    -1,    54,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    -1,    76,
      77,    -1,    -1,    -1,    -1,    82,    83,    84,    85,    86,
      94,    95,    96,    90,    91,    92,    93,    94,    95,     8,
      -1,    -1,    -1,    -1,    13,   102,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,    30,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      -1,    50,    51,    -1,    -1,    54,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    -1,    76,    77,    -1,
      -1,    -1,    -1,    82,    83,    84,    85,    86,    94,    95,
      96,    90,    91,    92,    93,    94,    95,     8,    -1,    -1,
      -1,   100,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    29,    30,
      -1,    32,    33,    34,    35,    36,    37,    38,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    50,
      51,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    77,    -1,    -1,    -1,
      -1,    82,    83,    84,    85,    86,    -1,    -1,    -1,    90,
      91,    92,    93,    94,    95,     8,    -1,    -1,    -1,   100,
      13,    14,    15,    -1,    -1,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    -1,    -1,    -1,    -1,    82,
      83,    84,    85,    86,    -1,    -1,    -1,    90,    91,    92,
      93,    94,    95,     8,    -1,    98,    99,    -1,    13,    14,
      15,    -1,    -1,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    77,    -1,    -1,    -1,    -1,    82,    83,    84,
      85,    86,    -1,    -1,    -1,    90,    91,    92,    93,    94,
      95,     8,    -1,    98,    99,    -1,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      27,    28,    29,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    -1,    50,    51,    -1,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      77,    -1,    -1,    -1,    -1,    82,    83,    84,    85,    86,
      -1,    -1,    -1,    90,    91,    92,    93,    94,    95,     8,
      -1,    -1,    99,    -1,    13,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,    30,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      -1,    50,    51,    -1,    -1,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    -1,
      -1,    -1,    -1,    82,    83,    84,    85,    86,    -1,    -1,
      -1,    90,    91,    92,    93,    94,    95,     8,    -1,    -1,
      99,    -1,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    29,    30,
      -1,    32,    33,    34,    35,    36,    37,    38,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    50,
      51,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    77,    -1,    -1,    -1,
      -1,    82,    83,    84,    85,    86,    -1,    -1,    -1,    90,
      91,    92,    93,    94,    95,    -1,     5,    -1,    99,     8,
      -1,    -1,    -1,    -1,    13,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,    30,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      -1,    50,    51,    -1,    -1,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    -1,
      -1,    -1,    -1,    82,    83,    84,    85,    86,    -1,    -1,
      -1,    90,    91,    92,    93,    94,    95,     8,    -1,    -1,
      -1,    -1,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    29,    30,
      -1,    32,    33,    34,    35,    36,    37,    38,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    50,
      51,    -1,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    77,    -1,    -1,    -1,
      -1,    82,    83,    84,    85,    86,    -1,    -1,    -1,    90,
      91,    92,    93,    94,    95,     8,    -1,    -1,    11,    -1,
      13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    27,    28,    29,    30,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    -1,    50,    51,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    -1,    -1,    -1,    -1,    82,
      83,    84,    85,    86,    -1,    -1,    -1,    90,    91,    92,
      93,    94,    95,     8,    -1,    -1,    -1,    -1,    13,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    27,    28,    29,    30,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    -1,    50,    51,    -1,    53,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    77,    -1,    -1,    -1,    -1,    82,    83,    84,
      85,    86,    -1,    -1,    -1,    90,    91,    92,    93,    94,
      95,     8,    -1,    -1,    -1,    -1,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      27,    28,    29,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    -1,    50,    51,    -1,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      77,    -1,    -1,    -1,    -1,    82,    83,    84,    85,    86,
      -1,    -1,    -1,    90,    91,    92,    93,    94,    95,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    95,
      96,    -1,    -1,    -1,    -1,    -1,   102,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    94,    95,    96,    -1,
      -1,    -1,    -1,    -1,   102,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    94,    95,    96,    -1,    -1,    -1,
      -1,    -1,   102,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    94,    95,    96,    -1,    -1,    -1,    -1,    -1,
     102,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      94,    95,    96,    -1,    -1,    -1,    -1,    -1,   102,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    95,
      96,    -1,    -1,    -1,   100,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    94,    95,    96,    -1,    -1,    -1,
     100,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      94,    95,    96,    -1,    -1,    -1,   100,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    94,    95,    96,    -1,
      -1,    -1,   100,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    94,    95,    96,    -1,    -1,    -1,   100,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    95,
      96,    -1,    -1,    99,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    94,    95,    96,    -1,    -1,    99,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    95,
      96,    -1,    -1,    99,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    94,    95,    96,    -1,    -1,    99,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    95,
      96,    -1,    98,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    94,    95,    96,    -1,    98,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    94,    95,    96,    97,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,
      95,    96,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    95,
      96,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    94,    95,    96
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,   104,   105,   106,   107,    26,    32,    33,    34,
      35,    36,    37,    38,    39,   177,     0,   107,    53,    97,
     108,     4,     6,     7,    10,    12,    13,    45,   109,   110,
     111,   112,   113,   115,   116,   121,   122,   123,   130,   131,
     130,    26,   182,    27,    53,   117,   177,   177,    53,   145,
      98,   111,    99,     5,    13,   108,    97,    97,    26,   118,
     119,   120,   183,    54,    99,    99,     8,    14,    15,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    46,    47,    48,    49,    50,    51,    52,    54,
      76,    77,    82,    83,    84,    85,    86,    90,    91,    92,
      93,    94,    95,    99,   124,   130,   132,   133,   134,   135,
     136,   137,   140,   141,   142,   143,   145,   146,   149,   150,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   177,   183,   130,   130,    98,   101,
      56,   183,   184,   185,   175,    54,    54,    54,    54,    99,
      99,    54,   149,    97,   145,    54,   177,   179,   180,    99,
     149,   175,    99,   149,   126,   127,   147,   149,   151,   175,
     175,   151,   176,   177,   178,   179,   149,   149,    53,   149,
     175,   175,   149,    82,   175,   175,   149,   149,   149,   149,
       5,    98,   134,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      94,    95,    96,    99,    51,    53,    51,    53,    99,    99,
      96,    97,   176,   177,   176,   120,    28,   100,   101,    97,
      11,   114,   149,   149,   148,   149,   149,   149,    97,   145,
      99,   147,    51,    51,    99,    96,    99,   101,   102,   102,
     101,    97,    96,   100,   100,    51,    61,    51,   149,    96,
      53,   149,    97,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   176,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
      51,    53,    54,   183,   149,   182,   149,   182,   183,    31,
     176,   181,    99,    99,   183,   176,   177,   100,   100,   100,
      99,   100,   100,   145,   100,   102,   149,   102,   149,    53,
     127,   175,   130,   149,   176,    53,   149,    98,    53,   149,
     181,   149,   182,   147,    54,   102,    98,   102,    98,    54,
      54,   145,   145,   145,   149,   145,    53,   138,   102,   102,
     182,     5,   182,   182,    98,    54,   102,    98,   100,   147,
     147,   125,   126,   129,   175,    16,    17,   144,   144,    99,
     139,   140,    98,    97,    98,    98,   125,   100,   100,    40,
     128,   101,    97,    54,   145,   148,    98,   140,   141,   181,
     128,   100,   126,     9,   149,   100,    98,    54,   100,    99,
     145,   100,   145,   125,   145,   145,   128,   144,   100,   145
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
#line 65 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_grammar(compiler, (yyvsp[(1) - (1)].opval));
      compiler->op_grammar = (yyval.opval);
    ;}
    break;

  case 3:
#line 72 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 4:
#line 76 "yacc/spvm_yacc.y"
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
#line 89 "yacc/spvm_yacc.y"
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
#line 106 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval), (yyvsp[(3) - (3)].opval), NULL);
    ;}
    break;

  case 8:
#line 110 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(5) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 9:
#line 116 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_class_block;
    ;}
    break;

  case 10:
#line 124 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 11:
#line 128 "yacc/spvm_yacc.y"
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
#line 140 "yacc/spvm_yacc.y"
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

  case 21:
#line 166 "yacc/spvm_yacc.y"
    { 
      SPVM_OP* op_sub = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUB, compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "BEGIN", compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_void_type = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_sub(compiler, op_sub, op_sub_name, op_void_type, NULL, NULL, (yyvsp[(2) - (2)].opval), NULL, NULL, 1);
    ;}
    break;

  case 22:
#line 175 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval), NULL, 0);
    ;}
    break;

  case 23:
#line 179 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(2) - (6)].opval), (yyvsp[(4) - (6)].opval), 0);
    ;}
    break;

  case 24:
#line 185 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_use(compiler, op_use, (yyvsp[(2) - (2)].opval), NULL, 1);
    ;}
    break;

  case 25:
#line 192 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_allow(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 26:
#line 199 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 27:
#line 205 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_enum_block;
    ;}
    break;

  case 28:
#line 213 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 29:
#line 217 "yacc/spvm_yacc.y"
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

  case 30:
#line 230 "yacc/spvm_yacc.y"
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

  case 31:
#line 244 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 33:
#line 251 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 34:
#line 255 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 35:
#line 261 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_our(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(4) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 36:
#line 267 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_has(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(2) - (6)].opval), (yyvsp[(4) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 37:
#line 273 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (10)].opval), (yyvsp[(3) - (10)].opval), (yyvsp[(5) - (10)].opval), (yyvsp[(7) - (10)].opval), (yyvsp[(1) - (10)].opval), (yyvsp[(10) - (10)].opval), NULL, (yyvsp[(8) - (10)].opval), 0);
     ;}
    break;

  case 38:
#line 277 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (10)].opval), (yyvsp[(3) - (10)].opval), (yyvsp[(5) - (10)].opval), (yyvsp[(7) - (10)].opval), (yyvsp[(1) - (10)].opval), NULL, NULL, (yyvsp[(8) - (10)].opval), 0);
     ;}
    break;

  case 39:
#line 283 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (9)].opval), NULL, (yyvsp[(4) - (9)].opval), (yyvsp[(6) - (9)].opval), (yyvsp[(1) - (9)].opval), (yyvsp[(9) - (9)].opval), NULL, (yyvsp[(7) - (9)].opval), 0);
     ;}
    break;

  case 40:
#line 287 "yacc/spvm_yacc.y"
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

  case 41:
#line 302 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 42:
#line 306 "yacc/spvm_yacc.y"
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

  case 43:
#line 317 "yacc/spvm_yacc.y"
    {
       // Add invocant to arguments
       SPVM_OP* op_args = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
       SPVM_OP_insert_child(compiler, op_args, op_args->last, (yyvsp[(1) - (1)].opval));
       
       (yyval.opval) = op_args;
    ;}
    break;

  case 44:
#line 325 "yacc/spvm_yacc.y"
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

  case 45:
#line 344 "yacc/spvm_yacc.y"
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

  case 47:
#line 361 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 48:
#line 367 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = NULL;
    ;}
    break;

  case 50:
#line 374 "yacc/spvm_yacc.y"
    {
      SPVM_TYPE* type = SPVM_TYPE_new(compiler);
      type->is_self = 1;
      SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, (yyvsp[(3) - (3)].opval)->file, (yyvsp[(3) - (3)].opval)->line);
      
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), op_type);
    ;}
    break;

  case 51:
#line 384 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 52:
#line 388 "yacc/spvm_yacc.y"
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

  case 53:
#line 401 "yacc/spvm_yacc.y"
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

  case 55:
#line 418 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 56:
#line 422 "yacc/spvm_yacc.y"
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

  case 57:
#line 435 "yacc/spvm_yacc.y"
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

  case 68:
#line 461 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_expression_statement(compiler, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 71:
#line 467 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (2)].opval), NULL);
    ;}
    break;

  case 72:
#line 471 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 73:
#line 475 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[(1) - (2)].opval), NULL);
    ;}
    break;

  case 74:
#line 479 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 77:
#line 485 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 78:
#line 491 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[(1) - (9)].opval), (yyvsp[(3) - (9)].opval), (yyvsp[(5) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(9) - (9)].opval));
    ;}
    break;

  case 79:
#line 497 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 80:
#line 503 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 81:
#line 509 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->cur_file, compiler->cur_line);
      op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[(2) - (3)].opval), NULL);
    ;}
    break;

  case 82:
#line 515 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->cur_file, compiler->cur_line);
      op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[(2) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 83:
#line 523 "yacc/spvm_yacc.y"
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

  case 84:
#line 537 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (1)].opval);
    ;}
    break;

  case 85:
#line 543 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 86:
#line 547 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval), op_block);
    ;}
    break;

  case 87:
#line 554 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 88:
#line 558 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[(1) - (2)].opval), op_block);
    ;}
    break;

  case 89:
#line 565 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->cur_file, compiler->cur_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 90:
#line 573 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (6)].opval)->file, (yyvsp[(1) - (6)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    ;}
    break;

  case 91:
#line 584 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (6)].opval)->file, (yyvsp[(1) - (6)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    ;}
    break;

  case 92:
#line 597 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 93:
#line 601 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (2)].opval);
    ;}
    break;

  case 94:
#line 605 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
    ;}
    break;

  case 95:
#line 611 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_block;
    ;}
    break;

  case 96:
#line 619 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 97:
#line 625 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 98:
#line 629 "yacc/spvm_yacc.y"
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

  case 99:
#line 642 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 122:
#line 670 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(2) - (3)].opval)->id == SPVM_OP_C_ID_LIST) {
        SPVM_OP* op_expression = (yyvsp[(2) - (3)].opval)->first;
        SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, compiler->cur_file, compiler->cur_line);
        while ((op_expression = SPVM_OP_sibling(compiler, op_expression))) {
          SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_expression);
          SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_expression);
          op_expression = op_stab;
        }
        (yyval.opval) = op_sequence;
      }
      else {
        (yyval.opval) = (yyvsp[(2) - (3)].opval);
      }
    ;}
    break;

  case 129:
#line 694 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_refcnt(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 130:
#line 700 "yacc/spvm_yacc.y"
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

  case 131:
#line 714 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 132:
#line 718 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (1)].opval);
    ;}
    break;

  case 133:
#line 724 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 134:
#line 729 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MINUS, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, op_negate, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 135:
#line 734 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 136:
#line 740 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 137:
#line 745 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 138:
#line 752 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 139:
#line 757 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 140:
#line 764 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 141:
#line 769 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 142:
#line 774 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 143:
#line 778 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 144:
#line 782 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 145:
#line 786 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 146:
#line 790 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BIT_AND, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 147:
#line 795 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 148:
#line 799 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 149:
#line 803 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_concat(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 150:
#line 809 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 151:
#line 813 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 152:
#line 817 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 153:
#line 821 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 154:
#line 825 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 155:
#line 829 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 156:
#line 835 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 157:
#line 839 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 158:
#line 843 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 159:
#line 847 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 160:
#line 851 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 161:
#line 855 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 162:
#line 861 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 163:
#line 867 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_or(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 164:
#line 871 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_and(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 165:
#line 875 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_not(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 166:
#line 881 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 167:
#line 885 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_special_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 168:
#line 891 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 169:
#line 895 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 170:
#line 899 "yacc/spvm_yacc.y"
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

  case 171:
#line 922 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 172:
#line 929 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, (yyvsp[(2) - (4)].opval)->file, (yyvsp[(2) - (4)].opval)->line);
      (yyval.opval) = SPVM_OP_build_convert(compiler, op_convert, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 173:
#line 936 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 174:
#line 940 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 175:
#line 944 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 176:
#line 950 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, NULL, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 177:
#line 954 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 178:
#line 958 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_expressions = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_expressions);
    ;}
    break;

  case 179:
#line 963 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 180:
#line 967 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_expressions = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_expressions);
    ;}
    break;

  case 181:
#line 972 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[(2) - (5)].opval)->file, (yyvsp[(2) - (5)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (5)].opval), op_sub_name, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 182:
#line 978 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 183:
#line 982 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 184:
#line 986 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 185:
#line 992 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, (yyvsp[(2) - (6)].opval), (yyvsp[(5) - (6)].opval));
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[(1) - (6)].opval), op_field_access);
    ;}
    break;

  case 186:
#line 999 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, (yyvsp[(2) - (6)].opval), (yyvsp[(5) - (6)].opval));
      (yyval.opval) = SPVM_OP_build_unweaken_field(compiler, (yyvsp[(1) - (6)].opval), op_field_access);
    ;}
    break;

  case 187:
#line 1006 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, (yyvsp[(2) - (6)].opval), (yyvsp[(5) - (6)].opval));
      (yyval.opval) = SPVM_OP_build_isweak_field(compiler, (yyvsp[(1) - (6)].opval), op_field_access);
    ;}
    break;

  case 188:
#line 1013 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 189:
#line 1018 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 190:
#line 1023 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 191:
#line 1028 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 192:
#line 1035 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_string_length(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 193:
#line 1041 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_deref(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 194:
#line 1047 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_ref(compiler, op_ref, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 195:
#line 1054 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 196:
#line 1058 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 197:
#line 1064 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 201:
#line 1075 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 202:
#line 1079 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_byte_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 203:
#line 1085 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_short_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 204:
#line 1091 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 205:
#line 1097 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_long_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 206:
#line 1103 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_float_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 207:
#line 1109 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_double_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 208:
#line 1115 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_any_object_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 209:
#line 1121 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_string_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 210:
#line 1129 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 211:
#line 1135 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 212:
#line 1139 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 213:
#line 1145 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 214:
#line 1149 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 216:
#line 1156 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 219:
#line 1168 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 220:
#line 1172 "yacc/spvm_yacc.y"
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

  case 221:
#line 1185 "yacc/spvm_yacc.y"
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
#line 3742 "spvm_yacc.tab.c"
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


#line 1200 "yacc/spvm_yacc.y"


