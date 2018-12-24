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
     SPECIAL_ASSIGN = 304,
     ASSIGN = 305,
     COND_OR = 306,
     COND_AND = 307,
     BIT_XOR = 308,
     BIT_OR = 309,
     STRNE = 310,
     STREQ = 311,
     NUMNE = 312,
     NUMEQ = 313,
     ISA = 314,
     STRLE = 315,
     STRLT = 316,
     STRGE = 317,
     STRGT = 318,
     NUMLE = 319,
     NUMLT = 320,
     NUMGE = 321,
     NUMGT = 322,
     SHIFT = 323,
     REMAINDER = 324,
     DIVIDE = 325,
     MULTIPLY = 326,
     CAST = 327,
     NEW = 328,
     REQUIRE = 329,
     MINUS = 330,
     PLUS = 331,
     LENGTH = 332,
     DEREF = 333,
     REF = 334,
     SCALAR = 335,
     BIT_NOT = 336,
     COND_NOT = 337,
     DEC = 338,
     INC = 339,
     ARROW = 340
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
#define SPECIAL_ASSIGN 304
#define ASSIGN 305
#define COND_OR 306
#define COND_AND 307
#define BIT_XOR 308
#define BIT_OR 309
#define STRNE 310
#define STREQ 311
#define NUMNE 312
#define NUMEQ 313
#define ISA 314
#define STRLE 315
#define STRLT 316
#define STRGE 317
#define STRGT 318
#define NUMLE 319
#define NUMLT 320
#define NUMGE 321
#define NUMGT 322
#define SHIFT 323
#define REMAINDER 324
#define DIVIDE 325
#define MULTIPLY 326
#define CAST 327
#define NEW 328
#define REQUIRE 329
#define MINUS 330
#define PLUS 331
#define LENGTH 332
#define DEREF 333
#define REF 334
#define SCALAR 335
#define BIT_NOT 336
#define COND_NOT 337
#define DEC 338
#define INC 339
#define ARROW 340




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
#line 299 "spvm_yacc.tab.c"

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
#define YYLAST   1729

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  100
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  76
/* YYNRULES -- Number of rules.  */
#define YYNRULES  211
/* YYNRULES -- Number of states.  */
#define YYNSTATES  408

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   340

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    55,     2,
      93,    97,     2,    70,    98,    71,    72,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    94,    96,
       2,     2,     2,     2,    76,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    91,     2,    99,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    92,     2,    95,     2,     2,     2,     2,
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
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    73,    74,    75,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90
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
     220,   224,   227,   231,   234,   237,   239,   249,   255,   261,
     265,   268,   274,   281,   288,   289,   292,   299,   303,   306,
     307,   309,   311,   313,   315,   317,   319,   321,   323,   325,
     327,   329,   331,   333,   335,   337,   339,   341,   343,   345,
     347,   349,   351,   353,   357,   359,   363,   366,   368,   371,
     374,   377,   380,   383,   386,   389,   393,   397,   401,   405,
     409,   413,   417,   421,   425,   429,   433,   437,   440,   443,
     449,   451,   455,   458,   462,   468,   473,   478,   483,   490,
     494,   501,   505,   511,   517,   522,   527,   530,   533,   536,
     541,   545,   551,   554,   557,   560,   565,   569,   573,   577,
     581,   585,   589,   593,   597,   601,   605,   609,   613,   617,
     621,   625,   628,   632,   637,   640,   642,   644,   646,   648,
     650,   652,   654,   656,   658,   660,   662,   664,   666,   668,
     671,   675,   679,   684,   689,   691,   693,   695,   697,   698,
     700,   704
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     101,     0,    -1,   102,    -1,    -1,   103,    -1,   103,   104,
      -1,   104,    -1,     3,   167,   105,    -1,     3,   167,    94,
     126,   105,    -1,    92,   106,    95,    -1,    -1,   107,    -1,
     107,   108,    -1,   108,    -1,   118,    -1,   119,    -1,   112,
      -1,   117,    96,    -1,   110,    -1,   109,    -1,    44,   139,
      -1,    10,   167,    96,    -1,    10,   167,    93,   174,    97,
      96,    -1,    79,   167,    -1,     7,   113,    -1,    92,   114,
      95,    -1,    -1,   115,    -1,   115,    98,   116,    -1,   115,
      98,    -1,   116,    -1,   173,    -1,   173,    50,    26,    -1,
       6,    27,    94,   126,   166,    -1,     4,   172,    94,   126,
     166,    96,    -1,   126,     5,   173,    94,   171,    93,   121,
     124,    97,   139,    -1,   126,     5,   173,    94,   171,    93,
     121,   124,    97,    96,    -1,   126,     5,    94,   171,    93,
     121,   124,    97,   139,    -1,    91,   122,    99,   126,     5,
      94,   171,    93,   121,   124,    97,   139,    -1,    -1,   122,
      -1,   125,    -1,   125,    98,   122,    -1,   122,    98,   123,
      -1,   123,    -1,   164,    94,   166,    -1,    -1,    39,    -1,
     164,    94,     9,    -1,    -1,   127,    -1,   127,    11,    -1,
      11,    -1,    -1,   129,    -1,   129,   130,    -1,   130,    -1,
     137,    -1,   131,    -1,   132,    -1,   139,    -1,   133,    -1,
     134,    -1,   135,    -1,   140,    -1,   136,    -1,   143,    96,
      -1,    18,    96,    -1,    19,    96,    -1,    45,    96,    -1,
      45,   143,    96,    -1,    47,    96,    -1,    47,   143,    96,
      -1,   156,    96,    -1,   157,    96,    -1,    96,    -1,    16,
      93,   142,    96,   142,    96,   142,    97,   139,    -1,    17,
      93,   142,    97,   139,    -1,    20,    93,   143,    97,   139,
      -1,    21,   143,    94,    -1,    22,    94,    -1,    12,    93,
     111,    97,   139,    -1,    12,    93,   142,    97,   139,   138,
      -1,    13,    93,   142,    97,   139,   138,    -1,    -1,    15,
     139,    -1,    14,    93,   142,    97,   139,   138,    -1,    92,
     128,    95,    -1,    23,   139,    -1,    -1,   144,    -1,   143,
      -1,   162,    -1,   164,    -1,    28,    -1,   165,    -1,    26,
      -1,    29,    -1,   154,    -1,   155,    -1,   153,    -1,   151,
      -1,   149,    -1,   150,    -1,   158,    -1,   159,    -1,   163,
      -1,   147,    -1,   145,    -1,   161,    -1,   160,    -1,   148,
      -1,   146,    -1,    93,   143,    97,    -1,    48,    -1,   144,
      98,   143,    -1,   144,    98,    -1,   143,    -1,    70,   143,
      -1,    71,   143,    -1,    86,   143,    -1,    89,   143,    -1,
     143,    89,    -1,    88,   143,    -1,   143,    88,    -1,   143,
      70,   143,    -1,   143,    71,   143,    -1,   143,    72,   143,
      -1,   143,    75,   143,    -1,   143,    74,   143,    -1,   143,
      73,   143,    -1,   143,    53,   143,    -1,   143,    55,   143,
      -1,   143,    54,   143,    -1,   143,    69,   143,    -1,   143,
      50,   143,    -1,   143,    49,   143,    -1,    78,   167,    -1,
      78,   170,    -1,    78,   169,    92,   141,    95,    -1,   120,
      -1,    91,   141,    99,    -1,   152,   143,    -1,    93,   166,
      97,    -1,   143,    90,    91,   143,    99,    -1,   153,    91,
     143,    99,    -1,   155,    91,   143,    99,    -1,    24,    93,
     141,    97,    -1,   167,    90,   173,    93,   141,    97,    -1,
     167,    90,   173,    -1,   143,    90,   173,    93,   141,    97,
      -1,   143,    90,   173,    -1,   143,    90,    93,   141,    97,
      -1,   143,    90,    92,   172,    95,    -1,   155,    92,   172,
      95,    -1,   153,    92,   172,    95,    -1,    46,   155,    -1,
      46,   153,    -1,    76,   143,    -1,    76,    92,   143,    95,
      -1,    85,    76,   143,    -1,    85,    76,    92,   143,    95,
      -1,    82,   143,    -1,    83,   164,    -1,    84,   164,    -1,
      84,    92,   164,    95,    -1,   143,    59,   143,    -1,   143,
      58,   143,    -1,   143,    68,   143,    -1,   143,    67,   143,
      -1,   143,    66,   143,    -1,   143,    65,   143,    -1,   143,
      57,   143,    -1,   143,    56,   143,    -1,   143,    64,   143,
      -1,   143,    63,   143,    -1,   143,    62,   143,    -1,   143,
      61,   143,    -1,   142,    60,   166,    -1,   142,    51,   142,
      -1,   142,    52,   142,    -1,    87,   142,    -1,    93,   162,
      97,    -1,     8,   164,    94,   166,    -1,     8,   164,    -1,
      25,    -1,    27,    -1,   167,    -1,   169,    -1,   168,    -1,
      24,    -1,    31,    -1,    32,    -1,    33,    -1,    34,    -1,
      35,    -1,    36,    -1,    38,    -1,    37,    -1,   167,    55,
      -1,   167,    91,    99,    -1,   169,    91,    99,    -1,   167,
      91,   143,    99,    -1,   169,    91,   143,    99,    -1,   166,
      -1,    30,    -1,    24,    -1,    24,    -1,    -1,   175,    -1,
     175,    98,   173,    -1,   173,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    65,    65,    73,    76,    89,   103,   106,   110,   116,
     125,   128,   140,   154,   157,   158,   159,   160,   161,   162,
     165,   174,   178,   184,   191,   197,   206,   209,   222,   236,
     240,   243,   247,   253,   259,   265,   269,   275,   279,   295,
     298,   309,   317,   336,   350,   353,   360,   363,   366,   377,
     380,   393,   407,   411,   414,   427,   441,   444,   445,   446,
     447,   448,   449,   450,   451,   452,   453,   457,   458,   459,
     463,   467,   471,   475,   476,   477,   483,   489,   495,   501,
     507,   510,   518,   529,   543,   546,   550,   556,   564,   571,
     574,   587,   588,   591,   592,   593,   594,   595,   596,   597,
     598,   599,   600,   601,   602,   603,   604,   605,   606,   607,
     608,   609,   610,   611,   615,   618,   632,   636,   642,   647,
     652,   658,   663,   668,   673,   680,   685,   690,   694,   698,
     702,   706,   710,   715,   719,   725,   729,   735,   739,   743,
     747,   770,   777,   784,   790,   794,   798,   804,   808,   812,
     817,   821,   826,   832,   836,   840,   846,   852,   858,   863,
     868,   873,   880,   885,   891,   896,   903,   907,   911,   915,
     919,   923,   927,   931,   935,   939,   943,   947,   951,   955,
     959,   963,   967,   973,   977,   983,   989,   995,   996,   997,
    1000,  1004,  1010,  1016,  1022,  1028,  1034,  1040,  1046,  1054,
    1060,  1064,  1070,  1074,  1080,  1081,  1087,  1090,  1094,  1097,
    1110,  1124
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
  "RETURN", "WEAKEN", "CROAK", "CURRENT_PACKAGE", "SPECIAL_ASSIGN",
  "ASSIGN", "COND_OR", "COND_AND", "BIT_XOR", "BIT_OR", "'&'", "STRNE",
  "STREQ", "NUMNE", "NUMEQ", "ISA", "STRLE", "STRLT", "STRGE", "STRGT",
  "NUMLE", "NUMLT", "NUMGE", "NUMGT", "SHIFT", "'+'", "'-'", "'.'",
  "REMAINDER", "DIVIDE", "MULTIPLY", "'@'", "CAST", "NEW", "REQUIRE",
  "MINUS", "PLUS", "LENGTH", "DEREF", "REF", "SCALAR", "BIT_NOT",
  "COND_NOT", "DEC", "INC", "ARROW", "'['", "'{'", "'('", "':'", "'}'",
  "';'", "')'", "','", "']'", "$accept", "grammar", "opt_packages",
  "packages", "package", "package_block", "opt_declarations",
  "declarations", "declaration", "begin_block", "use", "require",
  "enumeration", "enumeration_block", "opt_enumeration_values",
  "enumeration_values", "enumeration_value", "our", "has", "sub",
  "anon_sub", "opt_args", "args", "arg", "opt_vaarg", "invocant",
  "opt_descriptors", "descriptors", "opt_statements", "statements",
  "statement", "for_statement", "while_statement", "switch_statement",
  "case_statement", "default_statement", "if_require_statement",
  "if_statement", "else_statement", "block", "eval_block",
  "opt_expression_terms", "term", "expression_term", "expression_terms",
  "unop", "incdec", "binop", "assign", "new", "array_init", "convert_type",
  "convert", "array_access", "call_sub", "field_access", "weaken_field",
  "weaken_array_element", "array_length", "string_length", "deref", "ref",
  "condition_term", "my_var", "var", "package_var_access", "type",
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
     305,   306,   307,   308,   309,    38,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
      43,    45,    46,   324,   325,   326,    64,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,    91,   123,    40,    58,   125,    59,    41,    44,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   100,   101,   102,   102,   103,   103,   104,   104,   105,
     106,   106,   107,   107,   108,   108,   108,   108,   108,   108,
     109,   110,   110,   111,   112,   113,   114,   114,   115,   115,
     115,   116,   116,   117,   118,   119,   119,   120,   120,   121,
     121,   121,   121,   122,   122,   123,   124,   124,   125,   126,
     126,   127,   127,   128,   128,   129,   129,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   131,   132,   133,   134,
     135,   136,   137,   137,   138,   138,   138,   139,   140,   141,
     141,   142,   142,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   144,   144,   144,   145,   145,
     145,   146,   146,   146,   146,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   148,   148,   149,   149,   149,
     149,   150,   151,   152,   153,   153,   153,   154,   154,   154,
     154,   154,   154,   155,   155,   155,   156,   157,   158,   158,
     158,   158,   159,   160,   161,   161,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   163,   163,   164,   165,   166,   166,   166,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   168,
     169,   169,   170,   170,   171,   171,   172,   173,   174,   174,
     175,   175
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
       3,     2,     3,     2,     2,     1,     9,     5,     5,     3,
       2,     5,     6,     6,     0,     2,     6,     3,     2,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     3,     2,     1,     2,     2,
       2,     2,     2,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     5,
       1,     3,     2,     3,     5,     4,     4,     4,     6,     3,
       6,     3,     5,     5,     4,     4,     2,     2,     2,     4,
       3,     5,     2,     2,     2,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     3,     4,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     3,     4,     4,     1,     1,     1,     1,     0,     1,
       3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     2,     4,     6,   190,   191,   192,   193,
     194,   195,   196,   198,   197,     0,     1,     5,    10,    49,
       7,     0,     0,     0,     0,    52,     0,     0,    11,    13,
      19,    18,    16,     0,    14,    15,     0,    50,     0,   206,
       0,     0,    26,    24,     0,    49,    20,     9,    12,    17,
       0,    51,     8,    49,    49,   207,     0,    27,    30,    31,
     208,    21,     0,     0,     0,     0,     0,     0,     0,     0,
      49,     0,     0,   190,   185,    96,   186,    94,    97,    49,
      49,    49,   114,    49,    49,    49,     0,    49,     0,     0,
       0,    49,    49,    49,    49,    49,    75,   140,     0,     0,
      49,    56,    58,    59,    61,    62,    63,    65,    57,    60,
      64,     0,   108,   112,   107,   111,   102,   103,   101,    49,
     100,    98,    99,     0,     0,   104,   105,   110,   109,   106,
      93,    95,     0,     0,     0,     0,    25,    29,     0,   211,
       0,   209,   184,    49,    49,    49,    49,    67,    68,    49,
       0,    80,    88,    49,    69,     0,     0,   100,    99,    71,
       0,   118,   119,    49,   158,   137,     0,   138,   162,   163,
       0,   164,    49,   120,   123,   121,     0,    44,     0,   117,
      90,    93,     0,     0,   187,   189,   188,     0,    87,    55,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,   124,   122,     0,    66,   142,    49,     0,    49,
       0,    73,    74,     0,     0,     0,   187,    33,    28,    32,
       0,     0,     0,     0,    49,    49,     0,     0,    91,    92,
       0,     0,     0,     0,    79,     0,    70,    72,     0,    49,
      49,    49,     0,    49,   160,     0,    49,   141,   116,     0,
     113,   143,   199,     0,     0,     0,   136,   135,   131,   133,
     132,   134,   125,   126,   127,   130,   129,   128,    49,     0,
      49,   151,     0,     0,     0,     0,   149,   205,   204,     0,
      34,    22,   210,   183,    23,   181,     0,    91,    92,     0,
      49,    49,     0,     0,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,     0,    49,     0,     0,
     147,   159,   200,     0,   201,     0,     0,   165,     0,    43,
       0,     0,   115,    45,     0,     0,     0,     0,    49,   145,
     155,   146,   154,    49,    39,   182,    81,   179,   180,   178,
      84,   173,   172,   167,   166,   177,   176,   175,   174,   171,
     170,   169,   168,    84,     0,    77,    78,   202,   203,   139,
     161,     0,    39,   144,   153,   152,     0,     0,    46,    40,
      41,     0,     0,     0,    82,    83,    49,     0,    46,   150,
     148,    47,     0,     0,     0,    49,    85,     0,     0,     0,
       0,    42,    48,     0,     0,    39,     0,    36,    35,     0,
      76,    46,    37,    84,     0,    86,     0,    38
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    20,    27,    28,    29,    30,
      31,   226,    32,    43,    56,    57,    58,    33,    34,    35,
      97,   368,   369,   177,   382,   370,    98,    37,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   374,   109,
     110,   178,   227,   228,   180,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   229,   129,   130,   131,   278,   132,   185,   186,
     167,   279,    40,    59,   140,   141
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -354
static const yytype_int16 yypact[] =
{
      24,   469,    20,  -354,    24,  -354,  -354,  -354,  -354,  -354,
    -354,  -354,  -354,  -354,  -354,   -56,  -354,  -354,   245,    30,
    -354,    28,    43,   -33,   469,  -354,   -20,   -14,   245,  -354,
    -354,  -354,  -354,    -6,  -354,  -354,    86,   105,    35,  -354,
      77,    79,   136,  -354,   -61,   705,  -354,  -354,  -354,  -354,
     136,  -354,  -354,    30,    30,  -354,    81,    83,  -354,   124,
     136,  -354,   157,    90,    95,    96,   100,   101,   107,   103,
    1328,   111,   -20,   108,  -354,  -354,  -354,  -354,  -354,   822,
    1328,   901,  -354,  1328,  1328,  1182,   469,  1328,   157,    -8,
     128,  1328,  1328,  1328,    29,  1328,  -354,  -354,   218,   146,
     791,  -354,  -354,  -354,  -354,  -354,  -354,  -354,  -354,  -354,
    -354,   892,  -354,  -354,  -354,  -354,  -354,  -354,  -354,  1328,
      17,  -354,    32,   144,   149,  -354,  -354,  -354,  -354,  -354,
    -354,  -354,   142,   152,   469,   469,  -354,   136,   227,  -354,
     168,   169,   172,  1098,  1213,  1213,  1213,  -354,  -354,  1328,
    1570,  -354,  -354,   618,  -354,  1460,  1639,   -70,    48,  -354,
    1488,    13,    13,  1328,    13,   178,    45,  -354,    13,  -354,
     157,  -354,  1297,    13,    66,    66,    59,  -354,   171,  1639,
     174,   185,  1402,   183,    87,  -354,   191,   192,  -354,  -354,
    1328,  1328,  1328,  1328,  1328,  1328,  1328,  1328,  1328,  1328,
    1328,  1328,  -354,  -354,   -13,  -354,    13,  1328,    28,  1328,
      28,  -354,  -354,   136,   325,   189,   -22,  -354,  -354,  -354,
     194,   136,   469,   469,  1213,  1213,   190,   -21,  1612,  -354,
      -9,   177,    22,  1431,  -354,   196,  -354,  -354,  1516,   508,
     539,  1019,   193,  1328,    13,   157,    30,  -354,   988,   469,
    -354,  -354,  -354,   198,   199,   325,  1639,  1639,   188,   188,
     321,   409,   278,   278,   278,    13,    13,    13,  1328,    28,
     618,   202,    76,   204,   137,   205,   208,  -354,  -354,   210,
    -354,  -354,  -354,  -354,  -354,  -354,   110,  1373,   207,   -20,
    1213,  1213,   469,   -20,  1328,  1328,  1328,  1328,  1328,  1328,
    1328,  1328,  1328,  1328,  1328,  1328,   -20,  1213,   -20,   -20,
    -354,  -354,  -354,   145,  -354,   387,   213,  -354,  1543,  -354,
     185,   307,  1639,  -354,   222,   609,   221,   225,   618,  -354,
    -354,  -354,  -354,   618,   157,  -354,  -354,    23,   264,  -354,
     153,  1639,  1639,  1639,  1639,  1639,  1639,  1639,  1639,  1639,
    1639,  1639,  1639,   153,   179,  -354,  -354,  -354,  -354,  -354,
    -354,   231,   157,  -354,  -354,  -354,   230,   233,   289,   234,
     235,   237,   241,   -20,  -354,  -354,  1213,   325,   289,  -354,
    -354,  -354,   247,   157,   305,  1213,  -354,    44,   253,   250,
      -3,   234,  -354,    46,   -20,   157,   -20,  -354,  -354,   -20,
    -354,   289,  -354,   153,   257,  -354,   -20,  -354
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -354,  -354,  -354,  -354,   346,   326,  -354,  -354,   342,  -354,
    -354,  -354,  -354,  -354,  -354,  -354,   236,  -354,  -354,  -354,
    -354,  -349,   -91,   127,  -353,  -354,    -4,  -354,  -354,  -354,
     277,  -354,  -354,  -354,  -354,  -354,  -354,  -354,  -335,   -25,
    -354,  -149,  -138,   226,  -354,  -354,  -354,  -354,  -354,  -354,
    -354,  -354,  -354,   298,  -354,   300,  -354,  -354,  -354,  -354,
    -354,  -354,   159,  -354,   -60,  -354,   -90,    -1,  -354,   296,
    -354,  -239,  -198,   -41,  -354,  -354
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -158
static const yytype_int16 yytable[] =
{
      15,    46,   142,   176,   235,   183,   230,   231,   232,   133,
     273,    55,   275,   378,    36,    38,   324,    74,   375,   139,
      16,   207,   208,    44,    36,   389,  -157,     1,   169,   171,
     290,   291,    60,   252,   181,    61,    18,    62,    19,   292,
      25,    25,   290,   291,   215,   217,   401,   152,   404,   134,
     135,   292,    39,    73,    74,    75,    76,    77,    78,    42,
       7,     8,     9,    10,    11,    12,    13,    14,   405,   253,
      41,   326,    45,   290,   291,   291,   293,    82,   268,   269,
     270,    47,   292,   292,   170,   165,   285,   286,   306,    45,
      49,    50,   316,   397,   184,   290,   291,   290,   291,    83,
      84,   202,   203,   204,   292,    85,   292,    86,   207,   208,
     242,    87,    88,    89,    90,    91,    51,    92,    93,   308,
      94,   327,    95,   209,   210,   190,   191,    18,   -89,   192,
     193,   194,   283,   216,   216,   183,   240,   241,   388,   209,
     210,   394,   252,   399,  -156,   195,   196,   197,   198,   199,
     200,   201,   337,   338,  -158,  -158,   204,   245,   246,   323,
      55,   290,   291,   271,   202,   203,   204,   372,   373,   354,
     292,    53,   276,    54,   138,   329,   136,   213,   253,   366,
     282,   137,    74,   143,   367,   320,   190,   191,   144,   145,
     192,   193,   194,   146,   190,   191,   149,   147,   192,   193,
     194,   153,   339,   148,   172,   151,   195,   196,   197,   198,
     199,   200,   201,   216,   195,   196,   197,   198,   199,   200,
     201,   216,   284,   187,   184,   202,   203,   204,   290,   291,
     290,   291,   213,   202,   203,   204,   331,   292,   387,   292,
     211,   188,   321,   194,   357,   212,   214,   393,   216,    21,
     -49,    22,    23,   219,   216,    24,    25,   195,   196,   197,
     198,   199,   200,   201,   336,   220,   222,   221,   340,   239,
     247,   111,   248,   307,   371,   376,   202,   203,   204,   249,
     251,   353,   254,   355,   356,   280,   255,   289,   317,    26,
     281,   216,   391,   310,   323,   328,   150,   312,   314,   330,
     332,   333,   371,   334,   335,   155,   156,   160,   359,   161,
     162,   164,   361,   168,   392,   362,   364,   173,   174,   175,
     179,   182,   365,   320,   292,   377,   111,   379,   381,     6,
     380,   384,   245,   383,   385,   371,     7,     8,     9,    10,
      11,    12,    13,    14,   390,   206,   395,   396,   386,     6,
      17,   199,   200,   201,   406,   277,     7,     8,     9,    10,
      11,    12,    13,    14,    52,   398,   202,   203,   204,   400,
      48,   402,   319,   218,   403,   233,   216,   189,   157,   179,
     158,   407,   166,   216,   288,     0,     0,     0,     0,   238,
     195,   196,   197,   198,   199,   200,   201,     0,   244,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   202,
     203,   204,     0,     0,     0,     0,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,     0,     0,
       0,     0,     0,   272,     0,   274,   190,   191,     0,     0,
     192,   193,   194,     0,     0,     0,     0,     0,     0,     0,
       0,   287,     0,     0,     0,     0,   195,   196,   197,   198,
     199,   200,   201,     0,     0,   313,   315,   179,     0,   318,
       0,     0,     0,     0,   322,   202,   203,   204,     0,   196,
     197,   198,   199,   200,   201,     0,   358,     0,     0,     0,
       0,     0,     0,     6,   325,     0,   179,   202,   203,   204,
       7,     8,     9,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,     0,     0,     0,    62,     0,     0,    25,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,    73,    74,    75,    76,    77,    78,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    62,     0,     0,
      25,     0,     0,     0,   179,     0,    82,     0,     0,   179,
       0,     0,     0,    73,    74,    75,    76,    77,    78,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    83,    84,
       0,     0,     0,     0,    85,     0,    86,    82,     0,     0,
      87,    88,    89,    90,    91,     0,    92,    93,     0,    94,
       0,    95,     0,     0,     0,     0,     0,   312,     0,    83,
      84,     0,     0,     0,     0,    85,     0,    86,     0,     0,
       0,    87,    88,    89,    90,    91,    62,    92,    93,    25,
      94,     0,    95,     0,     0,     0,     0,     0,   314,     0,
       0,     0,    73,    74,    75,    76,    77,    78,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,   190,   191,
       0,     0,   192,   193,   194,     0,    82,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   195,   196,
     197,   198,   199,   200,   201,     0,     0,     0,    83,    84,
       0,     0,     0,     0,    85,     0,    86,   202,   203,   204,
      87,    88,    89,    90,    91,     0,    92,    93,   363,    94,
       0,    95,     0,    62,     0,   -89,    25,    63,    64,     0,
       0,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,     0,     7,     8,     9,    10,
      11,    12,    13,    14,     0,     0,     0,     0,     0,     0,
      79,    80,    81,    82,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    83,    84,     0,     0,     0,
       0,    85,     0,    86,     0,     0,     0,    87,    88,    89,
      90,    91,     0,    92,    93,     0,    94,    45,    95,    62,
     -53,    96,    25,    63,    64,     0,     0,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,     0,     7,     8,     9,    10,    11,    12,    13,    14,
      62,     0,     0,    25,     0,     0,    79,    80,    81,    82,
       0,     0,     0,     0,     0,     0,    73,    74,    75,    76,
      77,    78,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    83,    84,     0,     0,     0,     0,    85,     0,    86,
      82,     0,     0,    87,    88,    89,    90,    91,     0,    92,
      93,     0,    94,    45,    95,     0,   -54,    96,     0,     0,
       0,     0,    83,    84,     0,     0,     0,     0,    85,     0,
      86,     0,     0,     0,    87,    88,    89,    90,    91,    62,
      92,    93,    25,    94,     0,    95,     0,     0,   154,     0,
       0,     0,     0,     0,     0,    73,    74,    75,    76,    77,
      78,     0,     7,     8,     9,    10,    11,    12,    13,    14,
       0,   190,   191,     0,     0,   192,   193,   194,     0,    82,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   195,   196,   197,   198,   199,   200,   201,     0,     0,
       0,    83,    84,     0,     0,     0,     0,    85,     0,    86,
     202,   203,   204,    87,    88,    89,    90,    91,   205,    92,
      93,     0,    94,   -49,    95,     0,    62,   159,     0,    25,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    73,    74,    75,    76,    77,    78,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    62,     0,     0,
      25,     0,     0,     0,     0,     0,    82,     0,     0,     0,
       0,     0,     0,    73,    74,    75,    76,    77,    78,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    83,    84,
       0,     0,     0,     0,    85,     0,    86,    82,     0,     0,
      87,    88,    89,    90,    91,     0,    92,    93,     0,    94,
       0,    95,     0,     0,     0,     0,     0,     0,     0,    83,
      84,     0,     0,     0,     0,    85,     0,    86,     0,     0,
       0,    87,    88,    89,    90,    91,    62,    92,    93,    25,
      94,     0,    95,     0,   -89,     0,     0,     0,     0,     0,
       0,     0,    73,    74,    75,    76,    77,    78,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    82,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    83,    84,
       0,     0,     0,     0,    85,     0,    86,   223,     0,     0,
      87,    88,    89,    90,    91,   224,    92,    93,     0,    94,
      62,   225,     0,    25,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    73,    74,    75,    76,
      77,    78,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    62,     0,     0,    25,     0,     0,     0,     0,     0,
      82,     0,     0,     0,     0,     0,     0,    73,    74,    75,
      76,    77,    78,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    83,    84,     0,     0,     0,     0,    85,     0,
      86,    82,     0,     0,    87,    88,    89,    90,    91,     0,
      92,    93,     0,    94,   163,    95,     0,     0,     0,     0,
       0,     0,     0,    83,    84,     0,     0,     0,     0,    85,
       0,    86,     0,     0,     0,    87,    88,    89,    90,    91,
     224,    92,    93,     0,    94,    62,   225,     0,    25,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    73,    74,    75,    76,    77,    78,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    62,     0,     0,    25,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
       0,     0,    73,    74,    75,    76,    77,    78,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    83,    84,     0,
       0,     0,     0,    85,     0,    86,    82,     0,     0,    87,
      88,    89,    90,    91,     0,    92,    93,     0,    94,   243,
      95,     0,     0,     0,     0,     0,     0,     0,    83,    84,
       0,     0,     0,     0,    85,     0,    86,     0,     0,     0,
      87,    88,    89,    90,    91,     0,    92,    93,     0,    94,
       0,    95,   190,   191,     0,     0,   192,   193,   194,   294,
     295,   296,   297,     0,   298,   299,   300,   301,   302,   303,
     304,   305,   195,   196,   197,   198,   199,   200,   201,     0,
       0,   190,   191,     0,     0,   192,   193,   194,     0,     0,
       0,   202,   203,   204,     0,     0,     0,     0,     0,     0,
     250,   195,   196,   197,   198,   199,   200,   201,     0,     0,
     190,   191,     0,     0,   192,   193,   194,     0,     0,     0,
     202,   203,   204,     0,     0,     0,     0,     0,     0,   250,
     195,   196,   197,   198,   199,   200,   201,     0,     0,   190,
     191,     0,     0,   192,   193,   194,     0,     0,     0,   202,
     203,   204,     0,     0,     0,     0,     0,     0,   309,   195,
     196,   197,   198,   199,   200,   201,     0,   190,   191,     0,
       0,   192,   193,   194,     0,     0,     0,     0,   202,   203,
     204,     0,     0,     0,     0,     0,   236,   195,   196,   197,
     198,   199,   200,   201,     0,   190,   191,     0,     0,   192,
     193,   194,     0,     0,     0,     0,   202,   203,   204,     0,
       0,     0,     0,     0,   237,   195,   196,   197,   198,   199,
     200,   201,   190,   191,     0,     0,   192,   193,   194,     0,
       0,     0,     0,     0,   202,   203,   204,     0,     0,     0,
       0,   311,   195,   196,   197,   198,   199,   200,   201,   190,
     191,     0,     0,   192,   193,   194,     0,     0,     0,     0,
       0,   202,   203,   204,     0,     0,     0,     0,   360,   195,
     196,   197,   198,   199,   200,   201,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   202,   203,
     204,   190,   191,     0,   234,   192,   193,   194,   294,   295,
     296,   297,     0,   298,   299,   300,   301,   302,   303,   304,
     305,   195,   196,   197,   198,   199,   200,   201,   190,   191,
       0,     0,   192,   193,   194,     0,     0,     0,     0,     0,
     202,   203,   204,     0,     0,     0,     0,     0,   195,   196,
     197,   198,   199,   200,   201,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   202,   203,   204
};

static const yytype_int16 yycheck[] =
{
       1,    26,    62,    94,   153,    95,   144,   145,   146,    50,
     208,    24,   210,   362,    18,    19,   255,    25,   353,    60,
       0,    91,    92,    24,    28,   378,    96,     3,    88,    89,
      51,    52,    93,    55,    94,    96,    92,     8,    94,    60,
      11,    11,    51,    52,   134,   135,   395,    72,   401,    53,
      54,    60,    24,    24,    25,    26,    27,    28,    29,    92,
      31,    32,    33,    34,    35,    36,    37,    38,   403,    91,
      27,   269,    92,    51,    52,    52,    97,    48,    91,    92,
      93,    95,    60,    60,    92,    86,   224,   225,    97,    92,
      96,     5,   241,    96,    95,    51,    52,    51,    52,    70,
      71,    88,    89,    90,    60,    76,    60,    78,    91,    92,
     170,    82,    83,    84,    85,    86,    11,    88,    89,    97,
      91,   270,    93,    91,    92,    49,    50,    92,    99,    53,
      54,    55,   222,   134,   135,   225,    91,    92,   377,    91,
      92,    97,    55,    97,    96,    69,    70,    71,    72,    73,
      74,    75,   290,   291,    88,    89,    90,    98,    99,   249,
      24,    51,    52,   204,    88,    89,    90,    14,    15,   307,
      60,    94,   213,    94,    50,    99,    95,    90,    91,   328,
     221,    98,    25,    93,   333,   245,    49,    50,    93,    93,
      53,    54,    55,    93,    49,    50,    93,    96,    53,    54,
      55,    93,   292,    96,    76,    94,    69,    70,    71,    72,
      73,    74,    75,   214,    69,    70,    71,    72,    73,    74,
      75,   222,   223,     5,   225,    88,    89,    90,    51,    52,
      51,    52,    90,    88,    89,    90,    99,    60,   376,    60,
      96,    95,   246,    55,    99,    96,    94,   385,   249,     4,
       5,     6,     7,    26,   255,    10,    11,    69,    70,    71,
      72,    73,    74,    75,   289,    97,    94,    98,   293,    91,
      99,    45,    98,    96,   334,    96,    88,    89,    90,    94,
      97,   306,    91,   308,   309,    96,    94,    97,    95,    44,
      96,   292,   383,    97,   384,    93,    70,    99,    99,    95,
      95,    93,   362,    93,    97,    79,    80,    81,    95,    83,
      84,    85,     5,    87,     9,    93,    95,    91,    92,    93,
      94,    95,    97,   383,    60,    94,   100,    97,    39,    24,
      97,    94,    98,    98,    93,   395,    31,    32,    33,    34,
      35,    36,    37,    38,    97,   119,    93,    97,   373,    24,
       4,    73,    74,    75,    97,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    38,   390,    88,    89,    90,   394,
      28,   396,   245,   137,   399,   149,   377,   100,    80,   153,
      80,   406,    86,   384,   225,    -1,    -1,    -1,    -1,   163,
      69,    70,    71,    72,    73,    74,    75,    -1,   172,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    -1,    -1,    -1,    -1,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,    -1,    -1,
      -1,    -1,    -1,   207,    -1,   209,    49,    50,    -1,    -1,
      53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   225,    -1,    -1,    -1,    -1,    69,    70,    71,    72,
      73,    74,    75,    -1,    -1,   239,   240,   241,    -1,   243,
      -1,    -1,    -1,    -1,   248,    88,    89,    90,    -1,    70,
      71,    72,    73,    74,    75,    -1,    99,    -1,    -1,    -1,
      -1,    -1,    -1,    24,   268,    -1,   270,    88,    89,    90,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,    -1,    11,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,    24,    25,    26,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,     8,    -1,    -1,
      11,    -1,    -1,    -1,   328,    -1,    48,    -1,    -1,   333,
      -1,    -1,    -1,    24,    25,    26,    27,    28,    29,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    70,    71,
      -1,    -1,    -1,    -1,    76,    -1,    78,    48,    -1,    -1,
      82,    83,    84,    85,    86,    -1,    88,    89,    -1,    91,
      -1,    93,    -1,    -1,    -1,    -1,    -1,    99,    -1,    70,
      71,    -1,    -1,    -1,    -1,    76,    -1,    78,    -1,    -1,
      -1,    82,    83,    84,    85,    86,     8,    88,    89,    11,
      91,    -1,    93,    -1,    -1,    -1,    -1,    -1,    99,    -1,
      -1,    -1,    24,    25,    26,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    49,    50,
      -1,    -1,    53,    54,    55,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    70,
      71,    72,    73,    74,    75,    -1,    -1,    -1,    70,    71,
      -1,    -1,    -1,    -1,    76,    -1,    78,    88,    89,    90,
      82,    83,    84,    85,    86,    -1,    88,    89,    99,    91,
      -1,    93,    -1,     8,    -1,    97,    11,    12,    13,    -1,
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    -1,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    -1,    -1,    -1,
      -1,    76,    -1,    78,    -1,    -1,    -1,    82,    83,    84,
      85,    86,    -1,    88,    89,    -1,    91,    92,    93,     8,
      95,    96,    11,    12,    13,    -1,    -1,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    -1,    31,    32,    33,    34,    35,    36,    37,    38,
       8,    -1,    -1,    11,    -1,    -1,    45,    46,    47,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,    27,
      28,    29,    -1,    31,    32,    33,    34,    35,    36,    37,
      38,    70,    71,    -1,    -1,    -1,    -1,    76,    -1,    78,
      48,    -1,    -1,    82,    83,    84,    85,    86,    -1,    88,
      89,    -1,    91,    92,    93,    -1,    95,    96,    -1,    -1,
      -1,    -1,    70,    71,    -1,    -1,    -1,    -1,    76,    -1,
      78,    -1,    -1,    -1,    82,    83,    84,    85,    86,     8,
      88,    89,    11,    91,    -1,    93,    -1,    -1,    96,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    25,    26,    27,    28,
      29,    -1,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    49,    50,    -1,    -1,    53,    54,    55,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    70,    71,    72,    73,    74,    75,    -1,    -1,
      -1,    70,    71,    -1,    -1,    -1,    -1,    76,    -1,    78,
      88,    89,    90,    82,    83,    84,    85,    86,    96,    88,
      89,    -1,    91,     5,    93,    -1,     8,    96,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    25,    26,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,     8,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    25,    26,    27,    28,    29,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    70,    71,
      -1,    -1,    -1,    -1,    76,    -1,    78,    48,    -1,    -1,
      82,    83,    84,    85,    86,    -1,    88,    89,    -1,    91,
      -1,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      71,    -1,    -1,    -1,    -1,    76,    -1,    78,    -1,    -1,
      -1,    82,    83,    84,    85,    86,     8,    88,    89,    11,
      91,    -1,    93,    -1,    95,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    25,    26,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,
      -1,    -1,    -1,    -1,    76,    -1,    78,    79,    -1,    -1,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    91,
       8,    93,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,    27,
      28,    29,    -1,    31,    32,    33,    34,    35,    36,    37,
      38,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,
      27,    28,    29,    -1,    31,    32,    33,    34,    35,    36,
      37,    38,    70,    71,    -1,    -1,    -1,    -1,    76,    -1,
      78,    48,    -1,    -1,    82,    83,    84,    85,    86,    -1,
      88,    89,    -1,    91,    92,    93,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    -1,    -1,    -1,    -1,    76,
      -1,    78,    -1,    -1,    -1,    82,    83,    84,    85,    86,
      87,    88,    89,    -1,    91,     8,    93,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    25,    26,    27,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,     8,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    25,    26,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    70,    71,    -1,
      -1,    -1,    -1,    76,    -1,    78,    48,    -1,    -1,    82,
      83,    84,    85,    86,    -1,    88,    89,    -1,    91,    92,
      93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,
      -1,    -1,    -1,    -1,    76,    -1,    78,    -1,    -1,    -1,
      82,    83,    84,    85,    86,    -1,    88,    89,    -1,    91,
      -1,    93,    49,    50,    -1,    -1,    53,    54,    55,    56,
      57,    58,    59,    -1,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    -1,
      -1,    49,    50,    -1,    -1,    53,    54,    55,    -1,    -1,
      -1,    88,    89,    90,    -1,    -1,    -1,    -1,    -1,    -1,
      97,    69,    70,    71,    72,    73,    74,    75,    -1,    -1,
      49,    50,    -1,    -1,    53,    54,    55,    -1,    -1,    -1,
      88,    89,    90,    -1,    -1,    -1,    -1,    -1,    -1,    97,
      69,    70,    71,    72,    73,    74,    75,    -1,    -1,    49,
      50,    -1,    -1,    53,    54,    55,    -1,    -1,    -1,    88,
      89,    90,    -1,    -1,    -1,    -1,    -1,    -1,    97,    69,
      70,    71,    72,    73,    74,    75,    -1,    49,    50,    -1,
      -1,    53,    54,    55,    -1,    -1,    -1,    -1,    88,    89,
      90,    -1,    -1,    -1,    -1,    -1,    96,    69,    70,    71,
      72,    73,    74,    75,    -1,    49,    50,    -1,    -1,    53,
      54,    55,    -1,    -1,    -1,    -1,    88,    89,    90,    -1,
      -1,    -1,    -1,    -1,    96,    69,    70,    71,    72,    73,
      74,    75,    49,    50,    -1,    -1,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    -1,    -1,    -1,
      -1,    95,    69,    70,    71,    72,    73,    74,    75,    49,
      50,    -1,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,
      -1,    88,    89,    90,    -1,    -1,    -1,    -1,    95,    69,
      70,    71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    49,    50,    -1,    94,    53,    54,    55,    56,    57,
      58,    59,    -1,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    49,    50,
      -1,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    -1,    -1,    -1,    -1,    -1,    69,    70,
      71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,   101,   102,   103,   104,    24,    31,    32,    33,
      34,    35,    36,    37,    38,   167,     0,   104,    92,    94,
     105,     4,     6,     7,    10,    11,    44,   106,   107,   108,
     109,   110,   112,   117,   118,   119,   126,   127,   126,    24,
     172,    27,    92,   113,   167,    92,   139,    95,   108,    96,
       5,    11,   105,    94,    94,    24,   114,   115,   116,   173,
      93,    96,     8,    12,    13,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    45,
      46,    47,    48,    70,    71,    76,    78,    82,    83,    84,
      85,    86,    88,    89,    91,    93,    96,   120,   126,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   139,
     140,   143,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   163,
     164,   165,   167,   173,   126,   126,    95,    98,    50,   173,
     174,   175,   164,    93,    93,    93,    93,    96,    96,    93,
     143,    94,   139,    93,    96,   143,   143,   153,   155,    96,
     143,   143,   143,    92,   143,   167,   169,   170,   143,   164,
      92,   164,    76,   143,   143,   143,   122,   123,   141,   143,
     144,   164,   143,   166,   167,   168,   169,     5,    95,   130,
      49,    50,    53,    54,    55,    69,    70,    71,    72,    73,
      74,    75,    88,    89,    90,    96,   143,    91,    92,    91,
      92,    96,    96,    90,    94,   166,   167,   166,   116,    26,
      97,    98,    94,    79,    87,    93,   111,   142,   143,   162,
     142,   142,   142,   143,    94,   141,    96,    96,   143,    91,
      91,    92,   164,    92,   143,    98,    99,    99,    98,    94,
      97,    97,    55,    91,    91,    94,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,    91,    92,
      93,   173,   143,   172,   143,   172,   173,    30,   166,   171,
      96,    96,   173,   166,   167,   142,   142,   143,   162,    97,
      51,    52,    60,    97,    56,    57,    58,    59,    61,    62,
      63,    64,    65,    66,    67,    68,    97,    96,    97,    97,
      97,    95,    99,   143,    99,   143,   141,    95,   143,   123,
     164,   126,   143,   166,   171,   143,   172,   141,    93,    99,
      95,    99,    95,    93,    93,    97,   139,   142,   142,   166,
     139,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   139,   142,   139,   139,    99,    99,    95,
      95,     5,    93,    99,    95,    97,   141,   141,   121,   122,
     125,   164,    14,    15,   138,   138,    96,    94,   121,    97,
      97,    39,   124,    98,    94,    93,   139,   142,   171,   124,
      97,   122,     9,   142,    97,    93,    97,    96,   139,    97,
     139,   121,   139,   139,   124,   138,    97,   139
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
#line 66 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_grammar(compiler, (yyvsp[(1) - (1)].opval));
      compiler->op_grammar = (yyval.opval);
    ;}
    break;

  case 3:
#line 73 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 4:
#line 77 "yacc/spvm_yacc.y"
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
#line 90 "yacc/spvm_yacc.y"
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
#line 107 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval), (yyvsp[(3) - (3)].opval), NULL);
    ;}
    break;

  case 8:
#line 111 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(5) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 9:
#line 117 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_class_block;
    ;}
    break;

  case 10:
#line 125 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 11:
#line 129 "yacc/spvm_yacc.y"
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
#line 141 "yacc/spvm_yacc.y"
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
#line 166 "yacc/spvm_yacc.y"
    { 
      SPVM_OP* op_sub = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUB, compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "BEGIN", compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_void_type = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_sub(compiler, op_sub, op_sub_name, op_void_type, NULL, NULL, (yyvsp[(2) - (2)].opval), NULL, NULL, 1);
    ;}
    break;

  case 21:
#line 175 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval), NULL, 0);
    ;}
    break;

  case 22:
#line 179 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(2) - (6)].opval), (yyvsp[(4) - (6)].opval), 0);
    ;}
    break;

  case 23:
#line 185 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_use(compiler, op_use, (yyvsp[(2) - (2)].opval), NULL, 1);
    ;}
    break;

  case 24:
#line 192 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 25:
#line 198 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_enum_block;
    ;}
    break;

  case 26:
#line 206 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 27:
#line 210 "yacc/spvm_yacc.y"
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
#line 223 "yacc/spvm_yacc.y"
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
#line 237 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 31:
#line 244 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 32:
#line 248 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 33:
#line 254 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_our(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(4) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 34:
#line 260 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_has(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(2) - (6)].opval), (yyvsp[(4) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 35:
#line 266 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (10)].opval), (yyvsp[(3) - (10)].opval), (yyvsp[(5) - (10)].opval), (yyvsp[(7) - (10)].opval), (yyvsp[(1) - (10)].opval), (yyvsp[(10) - (10)].opval), NULL, (yyvsp[(8) - (10)].opval), 0);
     ;}
    break;

  case 36:
#line 270 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (10)].opval), (yyvsp[(3) - (10)].opval), (yyvsp[(5) - (10)].opval), (yyvsp[(7) - (10)].opval), (yyvsp[(1) - (10)].opval), NULL, NULL, (yyvsp[(8) - (10)].opval), 0);
     ;}
    break;

  case 37:
#line 276 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (9)].opval), NULL, (yyvsp[(4) - (9)].opval), (yyvsp[(6) - (9)].opval), (yyvsp[(1) - (9)].opval), (yyvsp[(9) - (9)].opval), NULL, (yyvsp[(7) - (9)].opval), 0);
     ;}
    break;

  case 38:
#line 280 "yacc/spvm_yacc.y"
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
#line 295 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 40:
#line 299 "yacc/spvm_yacc.y"
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
#line 310 "yacc/spvm_yacc.y"
    {
       // Add invocant to arguments
       SPVM_OP* op_args = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
       SPVM_OP_insert_child(compiler, op_args, op_args->last, (yyvsp[(1) - (1)].opval));
       
       (yyval.opval) = op_args;
    ;}
    break;

  case 42:
#line 318 "yacc/spvm_yacc.y"
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
#line 337 "yacc/spvm_yacc.y"
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
#line 354 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 46:
#line 360 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = NULL;
    ;}
    break;

  case 48:
#line 367 "yacc/spvm_yacc.y"
    {
      SPVM_TYPE* type = SPVM_TYPE_new(compiler);
      type->is_self = 1;
      SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, (yyvsp[(3) - (3)].opval)->file, (yyvsp[(3) - (3)].opval)->line);
      
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), op_type);
    ;}
    break;

  case 49:
#line 377 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 50:
#line 381 "yacc/spvm_yacc.y"
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
#line 394 "yacc/spvm_yacc.y"
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
#line 411 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 54:
#line 415 "yacc/spvm_yacc.y"
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
#line 428 "yacc/spvm_yacc.y"
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
#line 454 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 69:
#line 460 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (2)].opval), NULL);
    ;}
    break;

  case 70:
#line 464 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 71:
#line 468 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (2)].opval), NULL);
    ;}
    break;

  case 72:
#line 472 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 75:
#line 478 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 76:
#line 484 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[(1) - (9)].opval), (yyvsp[(3) - (9)].opval), (yyvsp[(5) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(9) - (9)].opval));
    ;}
    break;

  case 77:
#line 490 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 78:
#line 496 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 79:
#line 502 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 81:
#line 511 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->cur_file, compiler->cur_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 82:
#line 519 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (6)].opval)->file, (yyvsp[(1) - (6)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    ;}
    break;

  case 83:
#line 530 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (6)].opval)->file, (yyvsp[(1) - (6)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    ;}
    break;

  case 84:
#line 543 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 85:
#line 547 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (2)].opval);
    ;}
    break;

  case 86:
#line 551 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
    ;}
    break;

  case 87:
#line 557 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_block;
    ;}
    break;

  case 88:
#line 565 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 89:
#line 571 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 90:
#line 575 "yacc/spvm_yacc.y"
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

  case 113:
#line 612 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_single_parenthes_term(compiler, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 115:
#line 619 "yacc/spvm_yacc.y"
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

  case 116:
#line 633 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 117:
#line 637 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (1)].opval);
    ;}
    break;

  case 118:
#line 643 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 119:
#line 648 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEGATE, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op_negate, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 120:
#line 653 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unop(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 121:
#line 659 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_incdec(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 122:
#line 664 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_incdec(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 123:
#line 669 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_incdec(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 124:
#line 674 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_incdec(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 125:
#line 681 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 126:
#line 686 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 127:
#line 691 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_concat(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 128:
#line 695 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 129:
#line 699 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 130:
#line 703 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 131:
#line 707 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 132:
#line 711 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BIT_AND, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 133:
#line 716 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 134:
#line 720 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 135:
#line 726 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 136:
#line 730 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_special_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 137:
#line 736 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 138:
#line 740 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 139:
#line 744 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 140:
#line 748 "yacc/spvm_yacc.y"
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

  case 141:
#line 771 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 142:
#line 778 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_convert(compiler, op_convert, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 143:
#line 785 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 144:
#line 791 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 145:
#line 795 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 146:
#line 799 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 147:
#line 805 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, NULL, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 148:
#line 809 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 149:
#line 813 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_expression_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_expression_terms);
    ;}
    break;

  case 150:
#line 818 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 151:
#line 822 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_expression_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_expression_terms);
    ;}
    break;

  case 152:
#line 827 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[(2) - (5)].opval)->file, (yyvsp[(2) - (5)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (5)].opval), op_sub_name, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 153:
#line 833 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 154:
#line 837 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 155:
#line 841 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 156:
#line 847 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 157:
#line 853 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_weaken_array_element(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 158:
#line 859 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 159:
#line 864 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 160:
#line 869 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 161:
#line 874 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 162:
#line 881 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_string_length(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 163:
#line 886 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_deref(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 164:
#line 892 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_ref(compiler, op_ref, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 165:
#line 897 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, (yyvsp[(1) - (4)].opval)->file, (yyvsp[(1) - (4)].opval)->line);
      (yyval.opval) = SPVM_OP_build_ref(compiler, op_ref, (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 166:
#line 904 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 167:
#line 908 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 168:
#line 912 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 169:
#line 916 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 170:
#line 920 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 171:
#line 924 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 172:
#line 928 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 173:
#line 932 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 174:
#line 936 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 175:
#line 940 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 176:
#line 944 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 177:
#line 948 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 178:
#line 952 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 179:
#line 956 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_or(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 180:
#line 960 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_and(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 181:
#line 964 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_not(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 182:
#line 968 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_single_parenthes_term(compiler, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 183:
#line 974 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 184:
#line 978 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 185:
#line 984 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 186:
#line 990 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package_var_access(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 190:
#line 1001 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 191:
#line 1005 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_byte_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 192:
#line 1011 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_short_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 193:
#line 1017 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 194:
#line 1023 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_long_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 195:
#line 1029 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_float_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 196:
#line 1035 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_double_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 197:
#line 1041 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_any_object_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 198:
#line 1047 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_string_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 199:
#line 1055 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 200:
#line 1061 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 201:
#line 1065 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 202:
#line 1071 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 203:
#line 1075 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 205:
#line 1082 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 208:
#line 1094 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 209:
#line 1098 "yacc/spvm_yacc.y"
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

  case 210:
#line 1111 "yacc/spvm_yacc.y"
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
#line 3478 "spvm_yacc.tab.c"
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


#line 1126 "yacc/spvm_yacc.y"


