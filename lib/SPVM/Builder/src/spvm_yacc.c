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
     AMPERSAND = 294,
     DOT3 = 295,
     FATCAMMA = 296,
     RW = 297,
     RO = 298,
     WO = 299,
     BEGIN = 300,
     REQUIRE = 301,
     RETURN = 302,
     WEAKEN = 303,
     CROAK = 304,
     NEW = 305,
     CURRENT_PACKAGE = 306,
     SPECIAL_ASSIGN = 307,
     ASSIGN = 308,
     OR = 309,
     AND = 310,
     BIT_XOR = 311,
     BIT_OR = 312,
     BIT_AND = 313,
     REL = 314,
     SHIFT = 315,
     REMAINDER = 316,
     DIVIDE = 317,
     MULTIPLY = 318,
     ISA = 319,
     LENGTH = 320,
     DEREF = 321,
     REF = 322,
     UMINUS = 323,
     SCALAR = 324,
     NOT = 325,
     DEC = 326,
     INC = 327,
     ARROW = 328
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
#define AMPERSAND 294
#define DOT3 295
#define FATCAMMA 296
#define RW 297
#define RO 298
#define WO 299
#define BEGIN 300
#define REQUIRE 301
#define RETURN 302
#define WEAKEN 303
#define CROAK 304
#define NEW 305
#define CURRENT_PACKAGE 306
#define SPECIAL_ASSIGN 307
#define ASSIGN 308
#define OR 309
#define AND 310
#define BIT_XOR 311
#define BIT_OR 312
#define BIT_AND 313
#define REL 314
#define SHIFT 315
#define REMAINDER 316
#define DIVIDE 317
#define MULTIPLY 318
#define ISA 319
#define LENGTH 320
#define DEREF 321
#define REF 322
#define UMINUS 323
#define SCALAR 324
#define NOT 325
#define DEC 326
#define INC 327
#define ARROW 328




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
#line 275 "spvm_yacc.tab.c"

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
#define YYLAST   1792

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  76
/* YYNRULES -- Number of rules.  */
#define YYNRULES  201
/* YYNRULES -- Number of states.  */
#define YYNSTATES  388

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   328

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      80,    78,     2,    61,    86,    62,    63,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    83,    85,
       2,     2,     2,     2,    69,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    81,     2,    87,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    82,     2,    84,    68,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    64,    65,    66,    67,
      70,    71,    72,    73,    74,    75,    76,    77,    79
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
     347,   349,   351,   353,   355,   359,   361,   365,   368,   370,
     373,   376,   379,   382,   385,   388,   391,   395,   399,   403,
     407,   411,   415,   419,   423,   427,   431,   435,   439,   442,
     445,   451,   453,   457,   462,   468,   473,   478,   483,   490,
     494,   501,   505,   511,   517,   522,   527,   530,   533,   536,
     541,   545,   551,   554,   557,   560,   565,   569,   573,   577,
     581,   585,   588,   592,   597,   600,   602,   604,   606,   608,
     610,   612,   614,   616,   618,   620,   622,   624,   626,   628,
     631,   635,   639,   644,   649,   651,   653,   655,   657,   658,
     660,   664
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      89,     0,    -1,    90,    -1,    -1,    91,    -1,    91,    92,
      -1,    92,    -1,     3,   155,    93,    -1,     3,   155,    83,
     114,    93,    -1,    82,    94,    84,    -1,    -1,    95,    -1,
      95,    96,    -1,    96,    -1,   106,    -1,   107,    -1,   100,
      -1,   105,    85,    -1,    98,    -1,    97,    -1,    45,   127,
      -1,    10,   155,    85,    -1,    10,   155,    80,   162,    78,
      85,    -1,    46,   155,    -1,     7,   101,    -1,    82,   102,
      84,    -1,    -1,   103,    -1,   103,    86,   104,    -1,   103,
      86,    -1,   104,    -1,   161,    -1,   161,    53,    26,    -1,
       6,    27,    83,   114,   154,    -1,     4,   160,    83,   114,
     154,    85,    -1,   114,     5,   161,    83,   159,    80,   109,
     112,    78,   127,    -1,   114,     5,   161,    83,   159,    80,
     109,   112,    78,    85,    -1,   114,     5,    83,   159,    80,
     109,   112,    78,   127,    -1,    81,   110,    87,   114,     5,
      83,   159,    80,   109,   112,    78,   127,    -1,    -1,   110,
      -1,   113,    -1,   113,    86,   110,    -1,   110,    86,   111,
      -1,   111,    -1,   152,    83,   154,    -1,    -1,    40,    -1,
     152,    83,     9,    -1,    -1,   115,    -1,   115,    11,    -1,
      11,    -1,    -1,   117,    -1,   117,   118,    -1,   118,    -1,
     125,    -1,   119,    -1,   120,    -1,   127,    -1,   121,    -1,
     122,    -1,   123,    -1,   128,    -1,   124,    -1,   131,    85,
      -1,    18,    85,    -1,    19,    85,    -1,    47,    85,    -1,
      47,   131,    85,    -1,    49,    85,    -1,    49,   131,    85,
      -1,   143,    85,    -1,   144,    85,    -1,    85,    -1,    16,
      80,   130,    85,   130,    85,   130,    78,   127,    -1,    17,
      80,   130,    78,   127,    -1,    20,    80,   131,    78,   127,
      -1,    21,   131,    83,    -1,    22,    83,    -1,    12,    80,
      99,    78,   127,    -1,    12,    80,   130,    78,   127,   126,
      -1,    13,    80,   130,    78,   127,   126,    -1,    -1,    15,
     127,    -1,    14,    80,   130,    78,   127,   126,    -1,    82,
     116,    84,    -1,    23,   127,    -1,    -1,   132,    -1,   131,
      -1,   149,    -1,   150,    -1,   152,    -1,    28,    -1,   153,
      -1,    26,    -1,    29,    -1,   141,    -1,   142,    -1,   140,
      -1,   139,    -1,   137,    -1,   138,    -1,   145,    -1,   146,
      -1,   151,    -1,   135,    -1,   133,    -1,   148,    -1,   147,
      -1,   136,    -1,   134,    -1,    80,   131,    78,    -1,    51,
      -1,   132,    86,   131,    -1,   132,    86,    -1,   131,    -1,
      61,   131,    -1,    62,   131,    -1,    68,   131,    -1,    77,
     131,    -1,   131,    77,    -1,    76,   131,    -1,   131,    76,
      -1,   131,    61,   131,    -1,   131,    62,   131,    -1,   131,
      63,   131,    -1,   131,    66,   131,    -1,   131,    65,   131,
      -1,   131,    64,   131,    -1,   131,    56,   131,    -1,   131,
      39,   131,    -1,   131,    57,   131,    -1,   131,    60,   131,
      -1,   131,    53,   131,    -1,   131,    52,   131,    -1,    50,
     155,    -1,    50,   158,    -1,    50,   157,    82,   129,    84,
      -1,   108,    -1,    81,   129,    87,    -1,    80,   154,    78,
     131,    -1,   131,    79,    81,   131,    87,    -1,   140,    81,
     131,    87,    -1,   142,    81,   131,    87,    -1,    24,    80,
     129,    78,    -1,   155,    79,   161,    80,   129,    78,    -1,
     155,    79,   161,    -1,   131,    79,   161,    80,   129,    78,
      -1,   131,    79,   161,    -1,   131,    79,    80,   129,    78,
      -1,   131,    79,    82,   160,    84,    -1,   142,    82,   160,
      84,    -1,   140,    82,   160,    84,    -1,    48,   142,    -1,
      48,   140,    -1,    69,   131,    -1,    69,    82,   131,    84,
      -1,    74,    69,   131,    -1,    74,    69,    82,   131,    84,
      -1,    70,   131,    -1,    71,   152,    -1,    72,   152,    -1,
      72,    82,   152,    84,    -1,   131,    59,   131,    -1,   130,
      67,   154,    -1,    80,   149,    78,    -1,   130,    54,   130,
      -1,   130,    55,   130,    -1,    75,   130,    -1,    80,   150,
      78,    -1,     8,   152,    83,   154,    -1,     8,   152,    -1,
      25,    -1,    27,    -1,   155,    -1,   157,    -1,   156,    -1,
      24,    -1,    31,    -1,    32,    -1,    33,    -1,    34,    -1,
      35,    -1,    36,    -1,    38,    -1,    37,    -1,   155,    39,
      -1,   155,    81,    87,    -1,   157,    81,    87,    -1,   155,
      81,   131,    87,    -1,   157,    81,   131,    87,    -1,   154,
      -1,    30,    -1,    24,    -1,    24,    -1,    -1,   163,    -1,
     163,    86,   161,    -1,   161,    -1
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
     449,   450,   451,   452,   453,   454,   455,   459,   460,   461,
     465,   469,   473,   477,   478,   479,   485,   491,   497,   503,
     509,   512,   520,   531,   545,   548,   552,   558,   566,   573,
     576,   589,   590,   591,   594,   595,   596,   597,   598,   599,
     600,   601,   602,   603,   604,   605,   606,   607,   608,   609,
     610,   611,   612,   613,   614,   618,   621,   635,   639,   645,
     650,   655,   661,   666,   671,   676,   683,   688,   693,   697,
     701,   705,   709,   713,   717,   721,   727,   731,   737,   741,
     745,   749,   772,   779,   786,   790,   794,   800,   804,   808,
     813,   817,   822,   828,   832,   836,   842,   848,   854,   859,
     864,   869,   876,   881,   887,   892,   899,   903,   907,   913,
     917,   921,   925,   931,   935,   941,   947,   953,   954,   955,
     958,   962,   968,   974,   980,   986,   992,   998,  1004,  1012,
    1018,  1022,  1028,  1032,  1038,  1039,  1045,  1048,  1052,  1055,
    1068,  1082
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
  "STRING", "OBJECT", "AMPERSAND", "DOT3", "FATCAMMA", "RW", "RO", "WO",
  "BEGIN", "REQUIRE", "RETURN", "WEAKEN", "CROAK", "NEW",
  "CURRENT_PACKAGE", "SPECIAL_ASSIGN", "ASSIGN", "OR", "AND", "BIT_XOR",
  "BIT_OR", "BIT_AND", "REL", "SHIFT", "'+'", "'-'", "'.'", "REMAINDER",
  "DIVIDE", "MULTIPLY", "ISA", "'~'", "'@'", "LENGTH", "DEREF", "REF",
  "UMINUS", "SCALAR", "NOT", "DEC", "INC", "')'", "ARROW", "'('", "'['",
  "'{'", "':'", "'}'", "';'", "','", "']'", "$accept", "grammar",
  "opt_packages", "packages", "package", "package_block",
  "opt_declarations", "declarations", "declaration", "begin_block", "use",
  "require", "enumeration", "enumeration_block", "opt_enumeration_values",
  "enumeration_values", "enumeration_value", "our", "has", "sub",
  "anon_sub", "opt_args", "args", "arg", "opt_vaarg", "invocant",
  "opt_descriptors", "descriptors", "opt_statements", "statements",
  "statement", "for_statement", "while_statement", "switch_statement",
  "case_statement", "default_statement", "if_require_statement",
  "if_statement", "else_statement", "block", "eval_block",
  "opt_normal_terms", "term", "normal_term", "normal_terms", "unop",
  "incdec", "binop", "assign", "new", "array_init", "convert_type",
  "array_access", "call_sub", "field_access", "weaken_field",
  "weaken_array_element", "array_length", "string_length", "deref", "ref",
  "relative_term", "logical_term", "my_var", "var", "package_var_access",
  "type", "basic_type", "ref_type", "array_type", "array_type_with_length",
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,    43,    45,    46,   316,   317,   318,   319,   126,    64,
     320,   321,   322,   323,   324,   325,   326,   327,    41,   328,
      40,    91,   123,    58,   125,    59,    44,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    88,    89,    90,    90,    91,    91,    92,    92,    93,
      94,    94,    95,    95,    96,    96,    96,    96,    96,    96,
      97,    98,    98,    99,   100,   101,   102,   102,   103,   103,
     103,   104,   104,   105,   106,   107,   107,   108,   108,   109,
     109,   109,   109,   110,   110,   111,   112,   112,   113,   114,
     114,   115,   115,   116,   116,   117,   117,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   119,   120,   121,   122,
     123,   124,   125,   125,   126,   126,   126,   127,   128,   129,
     129,   130,   130,   130,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   132,   132,   132,   133,
     133,   133,   134,   134,   134,   134,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   136,   136,   137,   137,
     137,   137,   138,   139,   140,   140,   140,   141,   141,   141,
     141,   141,   141,   142,   142,   142,   143,   144,   145,   145,
     145,   145,   146,   147,   148,   148,   149,   149,   149,   150,
     150,   150,   150,   151,   151,   152,   153,   154,   154,   154,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   156,
     157,   157,   158,   158,   159,   159,   160,   161,   162,   162,
     163,   163
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
       1,     1,     1,     1,     3,     1,     3,     2,     1,     2,
       2,     2,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       5,     1,     3,     4,     5,     4,     4,     4,     6,     3,
       6,     3,     5,     5,     4,     4,     2,     2,     2,     4,
       3,     5,     2,     2,     2,     4,     3,     3,     3,     3,
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
       3,     0,     0,     2,     4,     6,   180,   181,   182,   183,
     184,   185,   186,   188,   187,     0,     1,     5,    10,    49,
       7,     0,     0,     0,     0,    52,     0,     0,    11,    13,
      19,    18,    16,     0,    14,    15,     0,    50,     0,   196,
       0,     0,    26,    24,     0,    49,    20,     9,    12,    17,
       0,    51,     8,    49,    49,   197,     0,    27,    30,    31,
     198,    21,     0,     0,     0,     0,     0,     0,     0,     0,
      49,     0,     0,   180,   175,    97,   176,    95,    98,    49,
      49,    49,     0,   115,    49,    49,    49,    49,    49,     0,
       0,     0,    49,    49,    49,    49,    75,   141,     0,     0,
      49,    56,    58,    59,    61,    62,    63,    65,    57,    60,
      64,     0,   109,   113,   108,   112,   103,   104,   102,   101,
      99,   100,     0,     0,   105,   106,   111,   110,   107,    94,
      96,     0,     0,     0,     0,    25,    29,     0,   201,     0,
     199,   174,    49,    49,    49,    49,    67,    68,    49,     0,
      80,    88,    49,    69,     0,     0,   101,   100,    71,     0,
     138,     0,   139,   119,   120,   121,    49,   158,   162,   163,
       0,   164,    49,   124,   122,     0,     0,   177,   179,   178,
       0,    44,     0,   118,    90,    94,     0,    87,    55,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,   125,   123,     0,    66,    49,     0,    49,     0,    73,
      74,     0,     0,     0,   177,    33,    28,    32,     0,     0,
       0,     0,    49,    49,     0,     0,    91,    92,    93,     0,
       0,     0,     0,    79,     0,    70,    72,    49,    49,    49,
       0,     0,    49,   160,   114,    49,   189,     0,     0,     0,
      49,   142,   117,     0,     0,   133,   137,   136,   132,   134,
     135,   126,   127,   128,   131,   130,   129,    49,    49,     0,
     151,     0,     0,     0,     0,   149,   195,   194,     0,    34,
      22,   200,   173,    23,   171,     0,    91,    92,    93,     0,
      49,    49,     0,     0,    49,     0,    49,     0,     0,   147,
     190,     0,   191,     0,     0,   159,   165,     0,   143,    43,
       0,     0,   116,    45,     0,     0,     0,     0,    49,   145,
     155,   146,   154,    49,    39,   168,   172,    81,   169,   170,
     167,    84,   166,    84,     0,    77,    78,   192,   193,   140,
     161,     0,    39,   152,   144,   153,     0,     0,    46,    40,
      41,     0,     0,     0,    82,    83,    49,     0,    46,   150,
     148,    47,     0,     0,     0,    49,    85,     0,     0,     0,
       0,    42,    48,     0,     0,    39,     0,    36,    35,     0,
      76,    46,    37,    84,     0,    86,     0,    38
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    20,    27,    28,    29,    30,
      31,   224,    32,    43,    56,    57,    58,    33,    34,    35,
      97,   348,   349,   181,   362,   350,    98,    37,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   354,   109,
     110,   182,   225,   226,   184,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   227,   228,   128,   129,   130,   277,   131,   178,   179,
     162,   278,    40,    59,   139,   140
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -343
static const yytype_int16 yypact[] =
{
       8,   364,    32,  -343,     8,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,  -343,  -343,  -343,   -64,  -343,  -343,   140,    31,
    -343,    39,    49,   -27,   364,  -343,    -4,    24,   140,  -343,
    -343,  -343,  -343,    -2,  -343,  -343,    82,    81,    14,  -343,
      37,    65,   104,  -343,   -63,   553,  -343,  -343,  -343,  -343,
     104,  -343,  -343,    31,    31,  -343,    68,    86,  -343,   124,
     104,  -343,   114,    99,   102,   103,   106,   115,   128,   108,
    1317,   101,    -4,   119,  -343,  -343,  -343,  -343,  -343,   695,
    1317,   762,   364,  -343,  1317,  1317,  1317,   970,  1317,   114,
     -10,   152,  1317,  1317,  1317,   342,  -343,  -343,   224,   146,
     628,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,    38,  -343,  -343,  -343,  -343,  -343,  -343,  -343,   -44,
    -343,    53,   148,   154,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,   158,   161,   364,   364,  -343,   104,   215,  -343,   168,
     164,   171,  1104,  1175,  1175,  1175,  -343,  -343,  1317,  1573,
    -343,  -343,  1246,  -343,  1455,  1713,   -61,    28,  -343,  1485,
     170,    56,  -343,    45,    45,    45,  1317,    45,    45,  -343,
     114,  -343,  1037,    50,    50,  1629,   178,     1,  -343,   180,
      55,  -343,   172,  1713,   176,   184,   186,  -343,  -343,  1317,
    1317,  1317,  1317,  1317,  1317,  1317,  1317,  1317,  1317,  1317,
    1317,  -343,  -343,   -11,  -343,  1317,    39,  1317,    39,  -343,
    -343,   104,   431,   191,   -35,  -343,  -343,  -343,   192,   104,
     364,   364,  1175,  1175,   185,   111,  1657,  -343,  -343,   150,
      64,   188,  1685,  -343,   200,  -343,  -343,   409,   476,   829,
    1515,   195,  1317,    45,  -343,  1317,  -343,   194,   198,   114,
      31,  -343,   903,   364,   431,   131,  1713,  1713,   131,   131,
     256,   159,   159,   159,    45,    45,    45,  1246,  1317,    39,
     206,   236,   196,  1343,   210,   223,  -343,  -343,   225,  -343,
    -343,  -343,  -343,  -343,  -343,    12,  1601,   212,   228,    -4,
    1175,  1175,   364,    -4,  1317,    -4,  1175,    -4,    -4,  -343,
    -343,  1371,  -343,  1399,   226,  -343,  -343,  1544,    -6,  -343,
     184,   302,  1713,  -343,   229,   230,  1427,   227,  1246,  -343,
    -343,  -343,  -343,  1246,   114,  -343,  -343,  -343,    19,   257,
    -343,   153,  1713,   153,   160,  -343,  -343,  -343,  -343,  -343,
    -343,   242,   114,  -343,  -343,  -343,   248,   249,   290,   245,
     258,   251,   266,    -4,  -343,  -343,  1175,   431,   290,  -343,
    -343,  -343,   269,   114,   305,  1175,  -343,   193,   268,   274,
       3,   245,  -343,   327,    -4,   114,    -4,  -343,  -343,    -4,
    -343,   290,  -343,   153,   277,  -343,    -4,  -343
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -343,  -343,  -343,  -343,   353,   320,  -343,  -343,   331,  -343,
    -343,  -343,  -343,  -343,  -343,  -343,   247,  -343,  -343,  -343,
    -343,  -334,   -89,   113,  -342,  -343,     7,  -343,  -343,  -343,
     260,  -343,  -343,  -343,  -343,  -343,  -343,  -343,  -321,   -25,
    -343,  -142,  -116,   -36,  -343,  -343,  -343,  -343,  -343,  -343,
    -343,  -343,   284,  -343,   285,  -343,  -343,  -343,  -343,  -343,
    -343,   149,   162,  -343,   -59,  -343,   -80,    -1,  -343,   304,
    -343,  -252,  -201,    15,  -343,  -343
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -158
static const yytype_int16 yytable[] =
{
      15,    46,   314,   141,   246,   272,   180,   274,   358,   111,
     234,     1,   355,    55,   176,    74,   369,    60,    18,    19,
     205,   206,    61,    44,  -157,    36,    38,   229,   230,   231,
     169,   171,    16,   189,   149,    36,   185,   205,   206,   384,
     246,   381,    25,   154,   155,   159,   247,   151,   163,   164,
     165,   167,   168,   213,   215,    42,   173,   174,   175,   183,
     133,   134,   385,    39,   111,   132,   290,   291,   317,   267,
     268,   269,   170,   203,   291,   138,    41,   189,    45,   292,
     211,   160,   247,    49,   189,    45,   292,    50,   377,   189,
     190,   191,    51,   177,   192,   193,    18,   304,   194,   195,
     196,   197,   198,   199,   200,   368,   284,   285,    47,   207,
     208,   241,   232,  -156,   201,   202,   183,   203,   290,   291,
      53,   201,   202,   204,   203,   315,  -158,  -158,    55,   203,
     240,   292,   214,   214,   207,   208,   243,   238,   239,    74,
     282,   249,   250,   176,    21,   -49,    22,    23,    54,   296,
      24,    25,   135,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   290,   291,   352,   353,   271,
     189,   273,   136,   313,   328,   329,   346,   137,   292,   142,
     334,   347,   143,   144,   150,    26,   145,   286,   148,   293,
     310,   194,   195,   196,   197,   198,   199,   200,   189,   152,
     146,   301,   303,   183,   290,   291,   307,   201,   202,   308,
     203,   214,   330,   147,   290,   291,   312,   292,   270,   214,
     283,   172,   177,   198,   199,   200,   275,   292,   295,   186,
     187,   183,   316,   209,   281,   201,   202,   211,   203,   210,
     367,   217,   290,   291,   212,   356,   218,   290,   291,   373,
     219,   237,   214,   214,   220,   292,   245,   311,   332,   251,
     292,   248,   252,   289,   327,   351,   297,   253,   331,   254,
     333,   374,   335,   336,   371,   189,   279,   280,   299,   306,
     320,   300,   183,   351,   313,   302,   318,   183,   190,   191,
     325,   214,   192,   193,   322,   189,   194,   195,   196,   197,
     198,   199,   200,   323,   310,   324,   326,   341,   343,   342,
     339,   345,   201,   202,   372,   203,   351,   195,   196,   197,
     198,   199,   200,   319,   292,   357,   359,   360,   366,     6,
     361,   249,   201,   202,   364,   203,     7,     8,     9,    10,
      11,    12,    13,    14,   363,   378,   365,   370,   375,   380,
      62,   382,   376,    25,   383,   386,   214,    17,    52,    48,
     188,   387,   309,   214,   156,   157,    73,    74,    75,    76,
      77,    78,   287,     7,     8,     9,    10,    11,    12,    13,
      14,   290,   291,   216,     0,   288,   161,     0,     6,     0,
       0,     0,    82,    83,   292,     7,     8,     9,    10,    11,
      12,    13,    14,    84,    85,   379,     0,     0,     0,     0,
      86,    87,    88,    89,    90,     0,    91,    62,    92,    93,
      25,     0,    94,    95,     0,     0,     0,     0,     0,   -89,
       0,     0,     0,    73,    74,    75,    76,    77,    78,     0,
       7,     8,     9,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,     0,     0,     6,     0,     0,     0,    82,
      83,   276,     7,     8,     9,    10,    11,    12,    13,    14,
      84,    85,     0,     0,     0,     0,     0,    86,    87,    88,
      89,    90,     0,    91,    62,    92,    93,    25,     0,    94,
      95,     0,     0,     0,     0,     0,   300,     0,     0,     0,
      73,    74,    75,    76,    77,    78,     0,     7,     8,     9,
      10,    11,    12,    13,    14,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    82,    83,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    84,    85,     0,
       0,     0,     0,     0,    86,    87,    88,    89,    90,     0,
      91,     0,    92,    93,     0,     0,    94,    95,     0,     0,
       0,    62,     0,   302,    25,    63,    64,     0,     0,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,     0,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     0,     0,     0,     0,     0,     0,     0,
      79,    80,    81,    82,    83,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    84,    85,     0,     0,     0,     0,
       0,    86,    87,    88,    89,    90,     0,    91,     0,    92,
      93,     0,     0,    94,    95,    45,    62,   -53,    96,    25,
      63,    64,     0,     0,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,     0,     0,     0,    79,    80,    81,    82,    83,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    84,
      85,     0,     0,     0,     0,     0,    86,    87,    88,    89,
      90,     0,    91,    62,    92,    93,    25,     0,    94,    95,
      45,     0,   -54,    96,     0,     0,     0,     0,     0,    73,
      74,    75,    76,    77,    78,     0,     7,     8,     9,    10,
      11,    12,    13,    14,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    82,    83,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    84,    85,     0,     0,
       0,     0,     0,    86,    87,    88,    89,    90,     0,    91,
      62,    92,    93,    25,     0,    94,    95,     0,     0,     0,
     153,     0,     0,     0,     0,     0,    73,    74,    75,    76,
      77,    78,     0,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    82,    83,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    84,    85,     0,     0,     0,     0,     0,
      86,    87,    88,    89,    90,     0,    91,    62,    92,    93,
      25,     0,    94,    95,     0,     0,     0,   158,     0,     0,
       0,     0,     0,    73,    74,    75,    76,    77,    78,     0,
       7,     8,     9,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    82,
      83,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      84,    85,     0,     0,     0,     0,     0,    86,    87,    88,
      89,    90,     0,    91,     0,    92,    93,     0,   -49,    94,
      95,    62,     0,   -89,    25,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    73,    74,    75,
      76,    77,    78,     0,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    82,    83,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    84,    85,     0,     0,     0,     0,
       0,    86,    87,    88,    89,    90,     0,    91,    62,    92,
      93,    25,     0,    94,    95,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    73,    74,    75,    76,    77,    78,
       0,     7,     8,     9,    10,    11,    12,    13,    14,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      82,    83,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    84,    85,     0,     0,     0,     0,     0,    86,    87,
      88,    89,    90,     0,    91,    62,    92,    93,    25,     0,
      94,    95,   166,     0,     0,     0,     0,     0,     0,     0,
       0,    73,    74,    75,    76,    77,    78,     0,     7,     8,
       9,    10,    11,    12,    13,    14,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    82,    83,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    84,    85,
       0,     0,     0,     0,     0,    86,    87,    88,    89,    90,
       0,    91,    62,    92,    93,    25,     0,    94,    95,   242,
       0,     0,     0,     0,     0,     0,     0,     0,    73,    74,
      75,    76,    77,    78,     0,     7,     8,     9,    10,    11,
      12,    13,    14,     0,     0,     0,     0,     0,     0,     0,
     221,     0,     0,     0,    82,    83,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    84,    85,     0,     0,     0,
       0,     0,    86,    87,    88,    89,    90,     0,    91,   222,
      92,    93,     0,    62,   223,    95,    25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      74,    75,    76,    77,    78,     0,     7,     8,     9,    10,
      11,    12,    13,    14,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    82,    83,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    84,    85,     0,     0,
       0,     0,     0,    86,    87,    88,    89,    90,     0,    91,
     222,    92,    93,     0,    62,   223,    95,    25,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      73,    74,    75,    76,    77,    78,     0,     7,     8,     9,
      10,    11,    12,    13,    14,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    82,    83,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    84,    85,     0,
       0,     0,     0,     0,    86,    87,    88,    89,    90,     0,
      91,     0,    92,    93,   -89,    62,    94,    95,    25,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    73,    74,    75,    76,    77,    78,     0,     7,     8,
       9,    10,    11,    12,    13,    14,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    82,    83,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    84,    85,
       0,     0,   189,     0,     0,    86,    87,    88,    89,    90,
       0,    91,     0,    92,    93,   190,   191,    94,    95,   192,
     193,     0,     0,   194,   195,   196,   197,   198,   199,   200,
     189,     0,     0,     0,     0,     0,     0,     0,     0,   201,
     202,     0,   203,   190,   191,     0,     0,   192,   193,     0,
     321,   194,   195,   196,   197,   198,   199,   200,   189,     0,
       0,     0,     0,     0,     0,     0,     0,   201,   202,     0,
     203,   190,   191,     0,     0,   192,   193,     0,   337,   194,
     195,   196,   197,   198,   199,   200,   189,     0,     0,     0,
       0,     0,     0,     0,     0,   201,   202,     0,   203,   190,
     191,     0,     0,   192,   193,     0,   338,   194,   195,   196,
     197,   198,   199,   200,   189,     0,     0,     0,     0,     0,
       0,     0,     0,   201,   202,     0,   203,   190,   191,     0,
       0,   192,   193,     0,   344,   194,   195,   196,   197,   198,
     199,   200,     0,     0,   189,     0,     0,     0,     0,     0,
       0,   201,   202,     0,   203,     0,     0,   190,   191,     0,
     235,   192,   193,     0,     0,   194,   195,   196,   197,   198,
     199,   200,     0,     0,   189,     0,     0,     0,     0,     0,
       0,   201,   202,     0,   203,     0,     0,   190,   191,     0,
     236,   192,   193,     0,     0,   194,   195,   196,   197,   198,
     199,   200,     0,   189,     0,     0,     0,     0,     0,     0,
       0,   201,   202,     0,   203,     0,   190,   191,     0,   305,
     192,   193,     0,     0,   194,   195,   196,   197,   198,   199,
     200,     0,   189,     0,     0,     0,     0,     0,     0,     0,
     201,   202,     0,   203,     0,   190,   191,     0,   340,   192,
     193,     0,     0,   194,   195,   196,   197,   198,   199,   200,
     189,     0,     0,     0,     0,     0,     0,     0,     0,   201,
     202,     0,   203,   190,   191,     0,   233,   192,   193,     0,
     294,   194,   195,   196,   197,   198,   199,   200,   189,     0,
       0,     0,     0,     0,     0,     0,     0,   201,   202,   244,
     203,   190,   191,     0,     0,   192,   193,     0,     0,   194,
     195,   196,   197,   198,   199,   200,   189,     0,     0,     0,
       0,     0,     0,     0,     0,   201,   202,   244,   203,   190,
     191,     0,     0,   192,   193,     0,   294,   194,   195,   196,
     197,   198,   199,   200,   189,     0,     0,     0,     0,     0,
       0,     0,     0,   201,   202,     0,   203,   190,   191,     0,
       0,   192,   193,     0,     0,   194,   195,   196,   197,   198,
     199,   200,   189,     0,     0,     0,     0,     0,     0,     0,
       0,   201,   202,   298,   203,   190,   191,     0,     0,   192,
     193,     0,     0,   194,   195,   196,   197,   198,   199,   200,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   201,
     202,     0,   203
};

static const yytype_int16 yycheck[] =
{
       1,    26,   254,    62,    39,   206,    95,   208,   342,    45,
     152,     3,   333,    24,    94,    25,   358,    80,    82,    83,
      81,    82,    85,    24,    85,    18,    19,   143,   144,   145,
      89,    90,     0,    39,    70,    28,    95,    81,    82,   381,
      39,   375,    11,    79,    80,    81,    81,    72,    84,    85,
      86,    87,    88,   133,   134,    82,    92,    93,    94,    95,
      53,    54,   383,    24,   100,    50,    54,    55,   269,    80,
      81,    82,    82,    79,    55,    60,    27,    39,    82,    67,
      79,    82,    81,    85,    39,    82,    67,     5,    85,    39,
      52,    53,    11,    94,    56,    57,    82,   239,    60,    61,
      62,    63,    64,    65,    66,   357,   222,   223,    84,    81,
      82,   170,   148,    85,    76,    77,   152,    79,    54,    55,
      83,    76,    77,    85,    79,   267,    76,    77,    24,    79,
     166,    67,   133,   134,    81,    82,   172,    81,    82,    25,
     220,    86,    87,   223,     4,     5,     6,     7,    83,    85,
      10,    11,    84,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,    54,    55,    14,    15,   205,
      39,   207,    86,   253,   290,   291,   318,    53,    67,    80,
     296,   323,    80,    80,    83,    45,    80,   223,    80,    78,
     249,    60,    61,    62,    63,    64,    65,    66,    39,    80,
      85,   237,   238,   239,    54,    55,   242,    76,    77,   245,
      79,   212,   292,    85,    54,    55,   252,    67,   203,   220,
     221,    69,   223,    64,    65,    66,   211,    67,    78,     5,
      84,   267,   268,    85,   219,    76,    77,    79,    79,    85,
     356,    26,    54,    55,    83,    85,    78,    54,    55,   365,
      86,    81,   253,   254,    83,    67,    78,   250,   294,    87,
      67,    81,    86,    78,   289,   324,    78,    83,   293,    83,
     295,    78,   297,   298,   363,    39,    85,    85,    78,    84,
      84,    87,   318,   342,   364,    87,    80,   323,    52,    53,
      78,   292,    56,    57,    84,    39,    60,    61,    62,    63,
      64,    65,    66,    80,   363,    80,    78,     5,    78,    80,
      84,    84,    76,    77,     9,    79,   375,    61,    62,    63,
      64,    65,    66,    87,    67,    83,    78,    78,   353,    24,
      40,    86,    76,    77,    83,    79,    31,    32,    33,    34,
      35,    36,    37,    38,    86,   370,    80,    78,    80,   374,
       8,   376,    78,    11,   379,    78,   357,     4,    38,    28,
     100,   386,   249,   364,    80,    80,    24,    25,    26,    27,
      28,    29,   223,    31,    32,    33,    34,    35,    36,    37,
      38,    54,    55,   136,    -1,   223,    82,    -1,    24,    -1,
      -1,    -1,    50,    51,    67,    31,    32,    33,    34,    35,
      36,    37,    38,    61,    62,    78,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    -1,    74,     8,    76,    77,
      11,    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,    87,
      -1,    -1,    -1,    24,    25,    26,    27,    28,    29,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    50,
      51,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      61,    62,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    -1,    74,     8,    76,    77,    11,    -1,    80,
      81,    -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,    -1,
      24,    25,    26,    27,    28,    29,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    -1,
      74,    -1,    76,    77,    -1,    -1,    80,    81,    -1,    -1,
      -1,     8,    -1,    87,    11,    12,    13,    -1,    -1,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    -1,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    -1,    74,    -1,    76,
      77,    -1,    -1,    80,    81,    82,     8,    84,    85,    11,
      12,    13,    -1,    -1,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    49,    50,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      62,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    -1,    74,     8,    76,    77,    11,    -1,    80,    81,
      82,    -1,    84,    85,    -1,    -1,    -1,    -1,    -1,    24,
      25,    26,    27,    28,    29,    -1,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    -1,    74,
       8,    76,    77,    11,    -1,    80,    81,    -1,    -1,    -1,
      85,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,    27,
      28,    29,    -1,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    62,    -1,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    -1,    74,     8,    76,    77,
      11,    -1,    80,    81,    -1,    -1,    -1,    85,    -1,    -1,
      -1,    -1,    -1,    24,    25,    26,    27,    28,    29,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    62,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    -1,    74,    -1,    76,    77,    -1,     5,    80,
      81,     8,    -1,    84,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,
      27,    28,    29,    -1,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    -1,    74,     8,    76,
      77,    11,    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    25,    26,    27,    28,    29,
      -1,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    62,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    -1,    74,     8,    76,    77,    11,    -1,
      80,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    25,    26,    27,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      -1,    74,     8,    76,    77,    11,    -1,    80,    81,    82,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,
      26,    27,    28,    29,    -1,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    -1,    50,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    -1,    74,    75,
      76,    77,    -1,     8,    80,    81,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      25,    26,    27,    28,    29,    -1,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    -1,    74,
      75,    76,    77,    -1,     8,    80,    81,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    25,    26,    27,    28,    29,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    -1,
      74,    -1,    76,    77,    78,     8,    80,    81,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    25,    26,    27,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,
      -1,    -1,    39,    -1,    -1,    68,    69,    70,    71,    72,
      -1,    74,    -1,    76,    77,    52,    53,    80,    81,    56,
      57,    -1,    -1,    60,    61,    62,    63,    64,    65,    66,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      77,    -1,    79,    52,    53,    -1,    -1,    56,    57,    -1,
      87,    60,    61,    62,    63,    64,    65,    66,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    -1,
      79,    52,    53,    -1,    -1,    56,    57,    -1,    87,    60,
      61,    62,    63,    64,    65,    66,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    77,    -1,    79,    52,
      53,    -1,    -1,    56,    57,    -1,    87,    60,    61,    62,
      63,    64,    65,    66,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    -1,    79,    52,    53,    -1,
      -1,    56,    57,    -1,    87,    60,    61,    62,    63,    64,
      65,    66,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    77,    -1,    79,    -1,    -1,    52,    53,    -1,
      85,    56,    57,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    77,    -1,    79,    -1,    -1,    52,    53,    -1,
      85,    56,    57,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    77,    -1,    79,    -1,    52,    53,    -1,    84,
      56,    57,    -1,    -1,    60,    61,    62,    63,    64,    65,
      66,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    77,    -1,    79,    -1,    52,    53,    -1,    84,    56,
      57,    -1,    -1,    60,    61,    62,    63,    64,    65,    66,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      77,    -1,    79,    52,    53,    -1,    83,    56,    57,    -1,
      59,    60,    61,    62,    63,    64,    65,    66,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,
      79,    52,    53,    -1,    -1,    56,    57,    -1,    -1,    60,
      61,    62,    63,    64,    65,    66,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    77,    78,    79,    52,
      53,    -1,    -1,    56,    57,    -1,    59,    60,    61,    62,
      63,    64,    65,    66,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    -1,    79,    52,    53,    -1,
      -1,    56,    57,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    77,    78,    79,    52,    53,    -1,    -1,    56,
      57,    -1,    -1,    60,    61,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      77,    -1,    79
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    89,    90,    91,    92,    24,    31,    32,    33,
      34,    35,    36,    37,    38,   155,     0,    92,    82,    83,
      93,     4,     6,     7,    10,    11,    45,    94,    95,    96,
      97,    98,   100,   105,   106,   107,   114,   115,   114,    24,
     160,    27,    82,   101,   155,    82,   127,    84,    96,    85,
       5,    11,    93,    83,    83,    24,   102,   103,   104,   161,
      80,    85,     8,    12,    13,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    47,
      48,    49,    50,    51,    61,    62,    68,    69,    70,    71,
      72,    74,    76,    77,    80,    81,    85,   108,   114,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   127,
     128,   131,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   151,   152,
     153,   155,   161,   114,   114,    84,    86,    53,   161,   162,
     163,   152,    80,    80,    80,    80,    85,    85,    80,   131,
      83,   127,    80,    85,   131,   131,   140,   142,    85,   131,
     155,   157,   158,   131,   131,   131,    82,   131,   131,   152,
      82,   152,    69,   131,   131,   131,   154,   155,   156,   157,
     110,   111,   129,   131,   132,   152,     5,    84,   118,    39,
      52,    53,    56,    57,    60,    61,    62,    63,    64,    65,
      66,    76,    77,    79,    85,    81,    82,    81,    82,    85,
      85,    79,    83,   154,   155,   154,   104,    26,    78,    86,
      83,    46,    75,    80,    99,   130,   131,   149,   150,   130,
     130,   130,   131,    83,   129,    85,    85,    81,    81,    82,
     131,   152,    82,   131,    78,    78,    39,    81,    81,    86,
      87,    87,    86,    83,    83,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,    80,    81,    82,
     161,   131,   160,   131,   160,   161,    30,   154,   159,    85,
      85,   161,   154,   155,   130,   130,   131,   149,   150,    78,
      54,    55,    67,    78,    59,    78,    85,    78,    78,    78,
      87,   131,    87,   131,   129,    84,    84,   131,   131,   111,
     152,   114,   131,   154,   159,   129,   131,   160,    80,    87,
      84,    87,    84,    80,    80,    78,    78,   127,   130,   130,
     154,   127,   131,   127,   130,   127,   127,    87,    87,    84,
      84,     5,    80,    78,    87,    84,   129,   129,   109,   110,
     113,   152,    14,    15,   126,   126,    85,    83,   109,    78,
      78,    40,   112,    86,    83,    80,   127,   130,   159,   112,
      78,   110,     9,   130,    78,    80,    78,    85,   127,    78,
     127,   109,   127,   127,   112,   126,    78,   127
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
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 69:
#line 462 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (2)].opval), NULL);
    ;}
    break;

  case 70:
#line 466 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 71:
#line 470 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (2)].opval), NULL);
    ;}
    break;

  case 72:
#line 474 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 75:
#line 480 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 76:
#line 486 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[(1) - (9)].opval), (yyvsp[(3) - (9)].opval), (yyvsp[(5) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(9) - (9)].opval));
    ;}
    break;

  case 77:
#line 492 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 78:
#line 498 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 79:
#line 504 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 81:
#line 513 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->cur_file, compiler->cur_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 82:
#line 521 "yacc/spvm_yacc.y"
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
#line 532 "yacc/spvm_yacc.y"
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
#line 545 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 85:
#line 549 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (2)].opval);
    ;}
    break;

  case 86:
#line 553 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
    ;}
    break;

  case 87:
#line 559 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_block;
    ;}
    break;

  case 88:
#line 567 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 89:
#line 573 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 90:
#line 577 "yacc/spvm_yacc.y"
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

  case 114:
#line 615 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_single_parenthes_term(compiler, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 116:
#line 622 "yacc/spvm_yacc.y"
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

  case 117:
#line 636 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 118:
#line 640 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (1)].opval);
    ;}
    break;

  case 119:
#line 646 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 120:
#line 651 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEGATE, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op_negate, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 121:
#line 656 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unop(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 122:
#line 662 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_incdec(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 123:
#line 667 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_incdec(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 124:
#line 672 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_incdec(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 125:
#line 677 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_incdec(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 126:
#line 684 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 127:
#line 689 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 128:
#line 694 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_concat(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 129:
#line 698 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 130:
#line 702 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 131:
#line 706 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 132:
#line 710 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 133:
#line 714 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 134:
#line 718 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 135:
#line 722 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 136:
#line 728 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 137:
#line 732 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_special_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 138:
#line 738 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 139:
#line 742 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 140:
#line 746 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 141:
#line 750 "yacc/spvm_yacc.y"
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

  case 142:
#line 773 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 143:
#line 780 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, (yyvsp[(2) - (4)].opval)->file, (yyvsp[(2) - (4)].opval)->line);
      (yyval.opval) = SPVM_OP_build_convert(compiler, op_convert, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 144:
#line 787 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 145:
#line 791 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 146:
#line 795 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 147:
#line 801 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, NULL, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 148:
#line 805 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 149:
#line 809 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_normal_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_normal_terms);
    ;}
    break;

  case 150:
#line 814 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 151:
#line 818 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_normal_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_normal_terms);
    ;}
    break;

  case 152:
#line 823 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[(2) - (5)].opval)->file, (yyvsp[(2) - (5)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (5)].opval), op_sub_name, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 153:
#line 829 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 154:
#line 833 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 155:
#line 837 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 156:
#line 843 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 157:
#line 849 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_weaken_array_element(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 158:
#line 855 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 159:
#line 860 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 160:
#line 865 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 161:
#line 870 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 162:
#line 877 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_string_length(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 163:
#line 882 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_deref(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 164:
#line 888 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_ref(compiler, op_ref, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 165:
#line 893 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, (yyvsp[(1) - (4)].opval)->file, (yyvsp[(1) - (4)].opval)->line);
      (yyval.opval) = SPVM_OP_build_ref(compiler, op_ref, (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 166:
#line 900 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 167:
#line 904 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 168:
#line 908 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_single_parenthes_term(compiler, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 169:
#line 914 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_or(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 170:
#line 918 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_and(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 171:
#line 922 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_not(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 172:
#line 926 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_single_parenthes_term(compiler, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 173:
#line 932 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 174:
#line 936 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 175:
#line 942 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 176:
#line 948 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package_var_access(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 180:
#line 959 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 181:
#line 963 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_byte_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 182:
#line 969 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_short_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 183:
#line 975 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 184:
#line 981 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_long_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 185:
#line 987 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_float_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 186:
#line 993 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_double_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 187:
#line 999 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_any_object_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 188:
#line 1005 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_string_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 189:
#line 1013 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 190:
#line 1019 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 191:
#line 1023 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 192:
#line 1029 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 193:
#line 1033 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 195:
#line 1040 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 198:
#line 1052 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 199:
#line 1056 "yacc/spvm_yacc.y"
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

  case 200:
#line 1069 "yacc/spvm_yacc.y"
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
#line 3371 "spvm_yacc.tab.c"
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


#line 1084 "yacc/spvm_yacc.y"


