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
     MY = 258,
     HAS = 259,
     SUB = 260,
     PACKAGE = 261,
     IF = 262,
     ELSIF = 263,
     ELSE = 264,
     RETURN = 265,
     FOR = 266,
     WHILE = 267,
     USE = 268,
     MALLOC = 269,
     LAST = 270,
     NEXT = 271,
     NAME = 272,
     VAR = 273,
     CONSTANT = 274,
     ENUM = 275,
     DESCRIPTOR = 276,
     CORETYPE = 277,
     UNDEF = 278,
     DIE = 279,
     SWITCH = 280,
     CASE = 281,
     DEFAULT = 282,
     VOID = 283,
     TRY = 284,
     CATCH = 285,
     ASSIGN = 286,
     OR = 287,
     AND = 288,
     BIT_XOR = 289,
     BIT_OR = 290,
     BIT_AND = 291,
     REL = 292,
     SHIFT = 293,
     REMAINDER = 294,
     DIVIDE = 295,
     MULTIPLY = 296,
     UMINUS = 297,
     ARRAY_LENGTH = 298,
     NOT = 299,
     DEC = 300,
     INC = 301,
     ARROW = 302
   };
#endif
/* Tokens.  */
#define MY 258
#define HAS 259
#define SUB 260
#define PACKAGE 261
#define IF 262
#define ELSIF 263
#define ELSE 264
#define RETURN 265
#define FOR 266
#define WHILE 267
#define USE 268
#define MALLOC 269
#define LAST 270
#define NEXT 271
#define NAME 272
#define VAR 273
#define CONSTANT 274
#define ENUM 275
#define DESCRIPTOR 276
#define CORETYPE 277
#define UNDEF 278
#define DIE 279
#define SWITCH 280
#define CASE 281
#define DEFAULT 282
#define VOID 283
#define TRY 284
#define CATCH 285
#define ASSIGN 286
#define OR 287
#define AND 288
#define BIT_XOR 289
#define BIT_OR 290
#define BIT_AND 291
#define REL 292
#define SHIFT 293
#define REMAINDER 294
#define DIVIDE 295
#define MULTIPLY 296
#define UMINUS 297
#define ARRAY_LENGTH 298
#define NOT 299
#define DEC 300
#define INC 301
#define ARROW 302




/* Copy the first part of user declarations.  */
#line 5 "yacc/spvm_yacc.y"

  #include <stdio.h>
  
  #include "spvm_compiler.h"
  #include "spvm_yacc_util.h"
  #include "spvm_toke.h"
  #include "spvm_op.h"
  #include "spvm_dumper.h"
  #include "spvm_constant.h"


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
#line 219 "spvm_yacc.tab.c"

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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   743

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  142
/* YYNRULES -- Number of states.  */
#define YYNSTATES  265

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      53,    52,     2,    40,    57,    41,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    58,    31,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    54,     2,    59,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    55,     2,    56,    45,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    32,    33,    34,    35,
      36,    37,    38,    39,    42,    43,    44,    46,    47,    48,
      49,    50,    51
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    13,    15,    17,
      21,    25,    26,    28,    31,    33,    35,    37,    39,    43,
      47,    48,    50,    54,    56,    58,    62,    63,    65,    68,
      70,    72,    74,    76,    78,    80,    82,    84,    86,    88,
      92,    95,    98,   100,   109,   115,   121,   125,   128,   135,
     136,   139,   146,   152,   162,   172,   175,   180,   183,   190,
     195,   197,   199,   201,   204,   207,   209,   210,   212,   216,
     218,   221,   226,   227,   229,   231,   233,   235,   237,   239,
     241,   243,   245,   247,   249,   251,   254,   257,   262,   268,
     273,   278,   281,   284,   287,   290,   293,   296,   299,   302,
     306,   310,   314,   318,   322,   326,   330,   334,   338,   342,
     346,   350,   354,   358,   364,   369,   374,   379,   386,   390,
     397,   401,   402,   404,   408,   410,   414,   415,   417,   421,
     423,   425,   427,   429,   433,   437,   442,   447,   449,   451,
     453,   455,   457
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      61,     0,    -1,    62,    -1,    -1,    63,    -1,    63,    64,
      -1,    64,    -1,    65,    -1,    66,    -1,    13,   116,    31,
      -1,     6,   116,    70,    -1,    -1,    68,    -1,    68,    69,
      -1,    69,    -1,    87,    -1,    88,    -1,    89,    -1,    55,
      67,    56,    -1,    55,    72,    56,    -1,    -1,    73,    -1,
      73,    57,    74,    -1,    74,    -1,    17,    -1,    17,    32,
      19,    -1,    -1,    76,    -1,    76,    77,    -1,    77,    -1,
      79,    -1,    85,    -1,    80,    -1,    81,    -1,    78,    -1,
      82,    -1,    83,    -1,    84,    -1,   117,    -1,    55,    75,
      56,    -1,    96,    31,    -1,    91,    31,    -1,    31,    -1,
      11,    53,    79,    96,    31,    95,    52,    78,    -1,    12,
      53,    96,    52,    78,    -1,    25,    53,    96,    52,    78,
      -1,    26,    96,    58,    -1,    27,    58,    -1,     7,    53,
      96,    52,    78,    86,    -1,    -1,     9,    78,    -1,     8,
      53,    96,    52,    78,    86,    -1,     4,   114,    58,   109,
      31,    -1,     5,   115,    53,   104,    52,    58,   107,   113,
      78,    -1,     5,   115,    53,   104,    52,    58,   107,   113,
      31,    -1,    20,    71,    -1,     3,    18,    58,   109,    -1,
       3,    18,    -1,     3,    18,    58,   109,    32,    96,    -1,
       3,    18,    32,    96,    -1,    15,    -1,    16,    -1,    10,
      -1,    10,    96,    -1,    24,    96,    -1,    90,    -1,    -1,
      93,    -1,    93,    57,    96,    -1,    96,    -1,    47,    96,
      -1,    47,    55,    96,    56,    -1,    -1,    96,    -1,    18,
      -1,    19,    -1,    23,    -1,   103,    -1,    99,    -1,   100,
      -1,   101,    -1,   102,    -1,    98,    -1,    97,    -1,    94,
      -1,    14,   110,    -1,    14,   112,    -1,    53,   109,    52,
      96,    -1,    96,    51,    55,   114,    56,    -1,    99,    55,
     114,    56,    -1,   102,    55,   114,    56,    -1,    40,    96,
      -1,    41,    96,    -1,    50,    96,    -1,    96,    50,    -1,
      49,    96,    -1,    96,    49,    -1,    45,    96,    -1,    48,
      96,    -1,    96,    40,    96,    -1,    96,    41,    96,    -1,
      96,    44,    96,    -1,    96,    43,    96,    -1,    96,    42,
      96,    -1,    96,    35,    96,    -1,    96,    37,    96,    -1,
      96,    36,    96,    -1,    96,    39,    96,    -1,    96,    38,
      96,    -1,    96,    32,    96,    -1,    53,    96,    52,    -1,
      96,    33,    96,    -1,    96,    34,    96,    -1,    96,    51,
      54,    96,    59,    -1,   102,    54,    96,    59,    -1,    99,
      54,    96,    59,    -1,   115,    53,    92,    52,    -1,    96,
      51,   115,    53,    92,    52,    -1,    96,    51,   115,    -1,
     116,    51,   115,    53,    92,    52,    -1,   116,    51,   115,
      -1,    -1,   105,    -1,   105,    57,   106,    -1,   106,    -1,
      18,    58,   109,    -1,    -1,   108,    -1,   108,    57,    21,
      -1,    21,    -1,   110,    -1,   111,    -1,    17,    -1,   110,
      54,    59,    -1,   111,    54,    59,    -1,   110,    54,    96,
      59,    -1,   111,    54,    96,    59,    -1,   109,    -1,    28,
      -1,    17,    -1,    17,    -1,    17,    -1,    29,    78,    30,
      53,    18,    52,    78,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    50,    50,    62,    65,    77,    81,    84,    85,    88,
      94,   104,   107,   119,   123,   126,   127,   128,   131,   138,
     146,   149,   161,   165,   168,   173,   182,   185,   197,   201,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   215,
     222,   227,   228,   234,   240,   246,   252,   258,   261,   268,
     271,   276,   282,   288,   292,   297,   303,   307,   311,   315,
     321,   322,   323,   326,   330,   334,   338,   341,   353,   357,
     360,   364,   370,   373,   376,   377,   378,   379,   380,   381,
     382,   383,   384,   385,   386,   389,   393,   399,   405,   409,
     413,   419,   424,   429,   434,   439,   444,   449,   453,   459,
     464,   469,   473,   477,   481,   485,   489,   493,   497,   501,
     505,   509,   513,   519,   523,   527,   533,   537,   541,   546,
     550,   558,   561,   573,   577,   580,   587,   590,   602,   606,
     609,   610,   614,   620,   624,   630,   634,   640,   641,   643,
     644,   645,   648
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MY", "HAS", "SUB", "PACKAGE", "IF",
  "ELSIF", "ELSE", "RETURN", "FOR", "WHILE", "USE", "MALLOC", "LAST",
  "NEXT", "NAME", "VAR", "CONSTANT", "ENUM", "DESCRIPTOR", "CORETYPE",
  "UNDEF", "DIE", "SWITCH", "CASE", "DEFAULT", "VOID", "TRY", "CATCH",
  "';'", "ASSIGN", "OR", "AND", "BIT_XOR", "BIT_OR", "BIT_AND", "REL",
  "SHIFT", "'+'", "'-'", "REMAINDER", "DIVIDE", "MULTIPLY", "'~'",
  "UMINUS", "ARRAY_LENGTH", "NOT", "DEC", "INC", "ARROW", "')'", "'('",
  "'['", "'{'", "'}'", "','", "':'", "']'", "$accept", "grammar",
  "opt_declarations_in_grammar", "declarations_in_grammar",
  "declaration_in_grammar", "use", "package",
  "opt_declarations_in_package", "declarations_in_package",
  "declaration_in_package", "package_block", "enumeration_block",
  "opt_enumeration_values", "enumeration_values", "enumeration_value",
  "opt_statements", "statements", "statement", "block", "normal_statement",
  "for_statement", "while_statement", "switch_statement", "case_statement",
  "default_statement", "if_statement", "else_statement", "field", "sub",
  "enumeration", "my", "expression", "opt_terms", "terms", "array_length",
  "opt_term", "term", "new_object", "convert_type", "call_field", "unop",
  "binop", "array_elem", "call_sub", "opt_args", "args", "arg",
  "opt_descriptors", "descriptors", "type", "type_name", "type_array",
  "type_array_with_length", "type_or_void", "field_name", "sub_name",
  "package_name", "try_catch", 0
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
     285,    59,   286,   287,   288,   289,   290,   291,   292,   293,
      43,    45,   294,   295,   296,   126,   297,   298,   299,   300,
     301,   302,    41,    40,    91,   123,   125,    44,    58,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    61,    62,    62,    63,    63,    64,    64,    65,
      66,    67,    67,    68,    68,    69,    69,    69,    70,    71,
      72,    72,    73,    73,    74,    74,    75,    75,    76,    76,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    78,
      79,    79,    79,    80,    81,    82,    83,    84,    85,    86,
      86,    86,    87,    88,    88,    89,    90,    90,    90,    90,
      91,    91,    91,    91,    91,    91,    92,    92,    93,    93,
      94,    94,    95,    95,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    97,    97,    98,    99,    99,
      99,   100,   100,   100,   100,   100,   100,   100,   100,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   102,   102,   102,   103,   103,   103,   103,
     103,   104,   104,   105,   105,   106,   107,   107,   108,   108,
     109,   109,   110,   111,   111,   112,   112,   113,   113,   114,
     115,   116,   117
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     1,     3,
       3,     0,     1,     2,     1,     1,     1,     1,     3,     3,
       0,     1,     3,     1,     1,     3,     0,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     1,     8,     5,     5,     3,     2,     6,     0,
       2,     6,     5,     9,     9,     2,     4,     2,     6,     4,
       1,     1,     1,     2,     2,     1,     0,     1,     3,     1,
       2,     4,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     4,     5,     4,
       4,     2,     2,     2,     2,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     5,     4,     4,     4,     6,     3,     6,
       3,     0,     1,     3,     1,     3,     0,     1,     3,     1,
       1,     1,     1,     3,     3,     4,     4,     1,     1,     1,
       1,     1,     7
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     0,     2,     4,     6,     7,     8,   141,
       0,     0,     1,     5,    11,    10,     9,     0,     0,     0,
       0,    12,    14,    15,    16,    17,   139,     0,   140,     0,
      20,    55,    18,    13,     0,   121,    24,     0,    21,    23,
     132,     0,   130,   131,     0,     0,   122,   124,     0,    19,
       0,    52,     0,     0,     0,     0,     0,    25,    22,   133,
     134,   125,   126,   123,   129,     0,   127,   138,   137,     0,
       0,    54,    26,    53,   128,     0,     0,    62,     0,     0,
       0,    60,    61,   140,    74,    75,    76,     0,     0,     0,
       0,     0,    42,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27,    29,    34,    30,    32,    33,    35,    36,
      37,    31,    65,     0,    84,     0,    83,    82,    78,    79,
      80,    81,    77,     0,     0,    38,    57,     0,    63,     0,
       0,    85,     0,    86,    64,     0,     0,    47,     0,    91,
      92,    97,     0,    70,    98,    95,    93,   132,     0,     0,
      39,    28,    41,    40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    96,    94,     0,
       0,     0,     0,     0,    66,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    46,     0,     0,   110,     0,   109,
     111,   112,   104,   106,   105,   108,   107,    99,   100,   103,
     102,   101,     0,     0,   118,     0,     0,     0,     0,     0,
      67,    69,   120,    59,    56,     0,     0,     0,     0,     0,
       0,     0,    71,    87,     0,     0,    66,   115,    89,   114,
      90,   116,     0,    66,     0,    49,    72,    44,   135,   136,
      45,     0,   113,    88,     0,    68,     0,    58,     0,     0,
      48,     0,    73,     0,   117,   119,     0,    50,     0,   142,
       0,    43,     0,    49,    51
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,     8,    20,    21,    22,
      15,    31,    37,    38,    39,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   250,    23,    24,    25,
     112,   113,   209,   210,   114,   251,   115,   116,   117,   118,
     119,   120,   121,   122,    45,    46,    47,    65,    66,    41,
      42,    43,   133,    69,    27,   123,   124,   125
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -213
static const yytype_int16 yypact[] =
{
       5,    -2,    -2,    20,  -213,     5,  -213,  -213,  -213,  -213,
     -23,     4,  -213,  -213,    50,  -213,  -213,    22,    36,   -18,
       0,    50,  -213,  -213,  -213,  -213,  -213,     6,  -213,    18,
      41,  -213,  -213,  -213,    57,    83,    71,    49,    51,  -213,
    -213,    76,    56,    75,    72,    79,    78,  -213,   114,  -213,
      41,  -213,    82,    85,    57,    84,    83,  -213,  -213,  -213,
    -213,  -213,   115,  -213,  -213,   -12,    88,  -213,  -213,   -22,
     119,  -213,   180,  -213,  -213,   129,    96,   244,    97,   100,
      57,  -213,  -213,   103,  -213,  -213,  -213,   244,   102,   244,
      99,   104,  -213,   244,   244,   244,   233,   244,   244,   244,
     281,   116,   180,  -213,  -213,  -213,  -213,  -213,  -213,  -213,
    -213,  -213,  -213,   140,  -213,   468,  -213,  -213,    -5,  -213,
    -213,    25,  -213,   121,   124,  -213,   -24,   244,   614,    28,
     244,   122,   123,  -213,   614,   244,   415,  -213,   148,    12,
      12,    12,   244,    12,    12,    48,    48,   -41,   488,   130,
    -213,  -213,  -213,  -213,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,  -213,  -213,   -14,
     244,    22,   244,    22,   244,    36,   244,    57,   509,   244,
     530,   120,   196,   551,  -213,   128,   442,  -213,   244,   614,
     632,   649,   664,   664,   678,   692,    73,    77,    77,    12,
      12,    12,   244,    22,   132,   274,   144,   303,   145,   136,
     151,   614,   149,   614,   184,   104,   573,   104,   331,   359,
     104,   194,  -213,  -213,   387,   161,   244,  -213,  -213,  -213,
    -213,  -213,   244,   244,   244,    58,   244,  -213,  -213,  -213,
    -213,   166,  -213,  -213,   170,   614,   171,   614,   173,   104,
    -213,   172,   614,   104,  -213,  -213,   244,  -213,   104,  -213,
     593,  -213,   104,    58,  -213
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -213,  -213,  -213,  -213,   226,  -213,  -213,  -213,  -213,   211,
    -213,  -213,  -213,  -213,   188,  -213,  -213,   137,   -69,   105,
    -213,  -213,  -213,  -213,  -213,  -213,   -21,  -213,  -213,  -213,
    -213,  -213,  -212,  -213,  -213,  -213,   -70,  -213,  -213,  -213,
    -213,  -213,  -213,  -213,  -213,  -213,   192,  -213,  -213,   -52,
     160,   174,  -213,  -213,  -167,   -17,    81,  -213
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -142
static const yytype_int16 yytable[] =
{
      73,    29,    61,    28,   206,    40,   208,   128,   176,    71,
    -141,     1,  -140,    68,   244,     9,    67,   134,     2,   136,
      12,   246,   138,   139,   140,   141,   143,   144,   145,   146,
     148,    75,    14,    72,   177,    16,   225,    30,    77,    26,
     202,   203,    80,    81,    82,    83,    84,    85,   149,   170,
     171,    86,    87,    28,    17,    18,    32,   178,    36,    92,
     180,   167,   168,   169,    34,   183,   248,   249,    93,    94,
      19,    35,   186,    95,    40,    96,    97,    98,    99,   172,
     173,   100,    10,    11,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,  -142,  -142,   169,
     205,    44,   207,    48,   211,    49,   213,    51,    50,   216,
      52,   218,   219,   162,   163,   164,   165,   166,   223,   164,
     165,   166,   167,   168,   169,   214,   167,   168,   169,    53,
      54,    55,   224,    57,    80,    56,    64,    83,    84,    85,
      74,    59,    62,    86,    60,    70,   235,   126,   237,   127,
     129,   240,   204,   130,  -141,   135,   211,   137,   212,    72,
      93,    94,   245,   211,   247,    95,   252,    96,    97,    98,
      99,   152,   150,   100,   174,   175,   181,   182,   185,    59,
     257,   221,   188,    75,   259,   226,   260,    76,   231,   261,
      77,    78,    79,   263,    80,    81,    82,    83,    84,    85,
     228,   230,   233,    86,    87,    88,    89,    90,   232,    91,
      80,    92,   241,    83,    84,    85,   234,   243,   253,    86,
      93,    94,   254,   255,   258,    95,   256,    96,    97,    98,
      99,    13,    33,   100,   179,    72,    93,    94,    58,   151,
     131,    95,   264,    96,    97,    98,    99,    80,    63,   100,
      83,    84,    85,     0,   132,    60,    86,     0,    80,     0,
       0,    83,    84,    85,     0,     0,     0,    86,     0,     0,
       0,     0,     0,    93,    94,     0,     0,     0,    95,     0,
      96,    97,    98,    99,    93,    94,   100,     0,   142,    95,
       0,    96,    97,    98,    99,    80,     0,   100,   147,    84,
      85,     0,     0,     0,    86,     0,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,     0,
       0,    93,    94,   167,   168,   169,    95,     0,    96,    97,
      98,    99,     0,   227,   100,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,     0,     0,
       0,     0,   167,   168,   169,     0,     0,     0,     0,     0,
       0,     0,   229,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,     0,     0,     0,     0,
     167,   168,   169,     0,     0,     0,     0,     0,     0,     0,
     238,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,     0,     0,     0,     0,   167,   168,
     169,     0,     0,     0,     0,     0,     0,     0,   239,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,     0,     0,     0,     0,   167,   168,   169,     0,
       0,     0,     0,     0,     0,     0,   242,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
       0,     0,     0,     0,   167,   168,   169,     0,     0,     0,
       0,     0,     0,   184,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,     0,     0,     0,
       0,   167,   168,   169,     0,     0,     0,     0,   222,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,     0,     0,     0,     0,   167,   168,   169,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,     0,     0,     0,     0,   167,   168,   169,
     187,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,     0,     0,     0,     0,   167,   168,
     169,   215,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,     0,     0,     0,     0,   167,
     168,   169,   217,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,     0,     0,     0,     0,
     167,   168,   169,   220,   236,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,     0,     0,
       0,     0,   167,   168,   169,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,     0,     0,
       0,     0,   167,   168,   169,   262,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,     0,
       0,     0,     0,   167,   168,   169,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,     0,     0,     0,
       0,   167,   168,   169,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,     0,     0,     0,     0,   167,   168,
     169,   159,   160,   161,   162,   163,   164,   165,   166,     0,
       0,     0,     0,   167,   168,   169,   160,   161,   162,   163,
     164,   165,   166,     0,     0,     0,     0,   167,   168,   169,
    -142,   161,   162,   163,   164,   165,   166,     0,     0,     0,
       0,   167,   168,   169
};

static const yytype_int16 yycheck[] =
{
      69,    18,    54,    17,   171,    17,   173,    77,    32,    31,
      51,     6,    53,    65,   226,    17,    28,    87,    13,    89,
       0,   233,    91,    93,    94,    95,    96,    97,    98,    99,
     100,     3,    55,    55,    58,    31,   203,    55,    10,    17,
      54,    55,    14,    15,    16,    17,    18,    19,   100,    54,
      55,    23,    24,    17,     4,     5,    56,   127,    17,    31,
     130,    49,    50,    51,    58,   135,     8,     9,    40,    41,
      20,    53,   142,    45,    17,    47,    48,    49,    50,    54,
      55,    53,     1,     2,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,    49,    50,    51,
     170,    18,   172,    32,   174,    56,   176,    31,    57,   179,
      54,   181,   182,    40,    41,    42,    43,    44,   188,    42,
      43,    44,    49,    50,    51,   177,    49,    50,    51,    54,
      58,    52,   202,    19,    14,    57,    21,    17,    18,    19,
      21,    59,    58,    23,    59,    57,   215,    18,   217,    53,
      53,   220,   169,    53,    51,    53,   226,    58,   175,    55,
      40,    41,   232,   233,   234,    45,   236,    47,    48,    49,
      50,    31,    56,    53,    53,    51,    54,    54,    30,    59,
     249,    53,    52,     3,   253,    53,   256,     7,    52,   258,
      10,    11,    12,   262,    14,    15,    16,    17,    18,    19,
      56,    56,    53,    23,    24,    25,    26,    27,    57,    29,
      14,    31,    18,    17,    18,    19,    32,    56,    52,    23,
      40,    41,    52,    52,    52,    45,    53,    47,    48,    49,
      50,     5,    21,    53,   129,    55,    40,    41,    50,   102,
      80,    45,   263,    47,    48,    49,    50,    14,    56,    53,
      17,    18,    19,    -1,    80,    59,    23,    -1,    14,    -1,
      -1,    17,    18,    19,    -1,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    40,    41,    -1,    -1,    -1,    45,    -1,
      47,    48,    49,    50,    40,    41,    53,    -1,    55,    45,
      -1,    47,    48,    49,    50,    14,    -1,    53,    17,    18,
      19,    -1,    -1,    -1,    23,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    40,    41,    49,    50,    51,    45,    -1,    47,    48,
      49,    50,    -1,    59,    53,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    59,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      49,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,    50,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    49,    50,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    49,    50,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    49,    50,    51,    -1,    -1,    -1,    -1,    56,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    49,    50,    51,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    49,    50,    51,
      52,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,    50,
      51,    52,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,
      50,    51,    52,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      49,    50,    51,    52,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    49,    50,    51,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    49,    50,    51,    52,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    49,    50,    51,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    49,    50,    51,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,    50,
      51,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    49,    50,    51,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    49,    50,    51,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    49,    50,    51
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    13,    61,    62,    63,    64,    65,    66,    17,
     116,   116,     0,    64,    55,    70,    31,     4,     5,    20,
      67,    68,    69,    87,    88,    89,    17,   114,    17,   115,
      55,    71,    56,    69,    58,    53,    17,    72,    73,    74,
      17,   109,   110,   111,    18,   104,   105,   106,    32,    56,
      57,    31,    54,    54,    58,    52,    57,    19,    74,    59,
      59,   109,    58,   106,    21,   107,   108,    28,   109,   113,
      57,    31,    55,    78,    21,     3,     7,    10,    11,    12,
      14,    15,    16,    17,    18,    19,    23,    24,    25,    26,
      27,    29,    31,    40,    41,    45,    47,    48,    49,    50,
      53,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    90,    91,    94,    96,    97,    98,    99,   100,
     101,   102,   103,   115,   116,   117,    18,    53,    96,    53,
      53,   110,   111,   112,    96,    53,    96,    58,    78,    96,
      96,    96,    55,    96,    96,    96,    96,    17,    96,   109,
      56,    77,    31,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    49,    50,    51,
      54,    55,    54,    55,    53,    51,    32,    58,    96,    79,
      96,    54,    54,    96,    58,    30,    96,    52,    52,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    54,    55,   115,    96,   114,    96,   114,    92,
      93,    96,   115,    96,   109,    52,    96,    52,    96,    96,
      52,    53,    56,    96,    96,   114,    53,    59,    56,    59,
      56,    52,    57,    53,    32,    78,    31,    78,    59,    59,
      78,    18,    59,    56,    92,    96,    92,    96,     8,     9,
      86,    95,    96,    52,    52,    52,    53,    78,    52,    78,
      96,    78,    52,    78,    86
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
#line 51 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_grammar(compiler, (yyvsp[(1) - (1)].opval));

      // Syntax error
      if (compiler->error_count) {
        YYABORT;
      }
    ;}
    break;

  case 3:
#line 62 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    ;}
    break;

  case 4:
#line 66 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->code == SPVM_OP_C_CODE_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_sibling_splice(compiler, (yyval.opval), (yyval.opval)->first, 0, (yyvsp[(1) - (1)].opval));
      }
    ;}
    break;

  case 5:
#line 78 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_append_elem(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
    ;}
    break;

  case 9:
#line 89 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 10:
#line 95 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval), (yyvsp[(3) - (3)].opval));
      if (compiler->fatal_error) {
        YYABORT;
      }
    ;}
    break;

  case 11:
#line 104 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    ;}
    break;

  case 12:
#line 108 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->code == SPVM_OP_C_CODE_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_sibling_splice(compiler, (yyval.opval), (yyval.opval)->first, 0, (yyvsp[(1) - (1)].opval));
      }
    ;}
    break;

  case 13:
#line 120 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_append_elem(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
    ;}
    break;

  case 18:
#line 132 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CLASS_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_sibling_splice(compiler, (yyval.opval), NULL, 0, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 19:
#line 139 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ENUM_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_sibling_splice(compiler, (yyval.opval), NULL, 0, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 20:
#line 146 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    ;}
    break;

  case 21:
#line 150 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->code == SPVM_OP_C_CODE_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_sibling_splice(compiler, (yyval.opval), (yyval.opval)->first, 0, (yyvsp[(1) - (1)].opval));
      }
    ;}
    break;

  case 22:
#line 162 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_append_elem(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
    ;}
    break;

  case 24:
#line 169 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ENUMERATION_VALUE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      SPVM_OP_sibling_splice(compiler, (yyval.opval), NULL, 0, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 25:
#line 174 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ENUMERATION_VALUE, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_sibling_splice(compiler, (yyval.opval), NULL, 0, (yyvsp[(1) - (3)].opval));
      SPVM_OP_sibling_splice(compiler, (yyval.opval), (yyvsp[(1) - (3)].opval), 0, (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 26:
#line 182 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    ;}
    break;

  case 27:
#line 186 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->code == SPVM_OP_C_CODE_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_sibling_splice(compiler, (yyval.opval), (yyval.opval)->first, 0, (yyvsp[(1) - (1)].opval));
      }
    ;}
    break;

  case 28:
#line 198 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_append_elem(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
    ;}
    break;

  case 39:
#line 216 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_sibling_splice(compiler, (yyval.opval), NULL, 0, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 40:
#line 223 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POP, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      SPVM_OP_sibling_splice(compiler, (yyval.opval), NULL, 0, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 42:
#line 229 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
    ;}
    break;

  case 43:
#line 235 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[(1) - (8)].opval), (yyvsp[(3) - (8)].opval), (yyvsp[(4) - (8)].opval), (yyvsp[(6) - (8)].opval), (yyvsp[(8) - (8)].opval));
    ;}
    break;

  case 44:
#line 241 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 45:
#line 247 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 46:
#line 253 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 48:
#line 262 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
    ;}
    break;

  case 49:
#line 268 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, compiler->cur_module_path, compiler->cur_line);
    ;}
    break;

  case 50:
#line 272 "yacc/spvm_yacc.y"
    {
      (yyvsp[(2) - (2)].opval)->flag |= SPVM_OP_C_FLAG_BLOCK_ELSE;
      (yyval.opval) = (yyvsp[(2) - (2)].opval);
    ;}
    break;

  case 51:
#line 277 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
    ;}
    break;

  case 52:
#line 283 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 53:
#line 289 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(1) - (9)].opval), (yyvsp[(2) - (9)].opval), (yyvsp[(4) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(8) - (9)].opval), (yyvsp[(9) - (9)].opval));
     ;}
    break;

  case 54:
#line 293 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(1) - (9)].opval), (yyvsp[(2) - (9)].opval), (yyvsp[(4) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(8) - (9)].opval), NULL);
     ;}
    break;

  case 55:
#line 298 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 56:
#line 304 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my_var(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval), NULL);
    ;}
    break;

  case 57:
#line 308 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my_var(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL, NULL);
    ;}
    break;

  case 58:
#line 312 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my_var(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(2) - (6)].opval), (yyvsp[(4) - (6)].opval), (yyvsp[(6) - (6)].opval));
    ;}
    break;

  case 59:
#line 316 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my_var(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval), NULL, (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 62:
#line 323 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 63:
#line 327 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 64:
#line 331 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 66:
#line 338 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    ;}
    break;

  case 67:
#line 342 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->code == SPVM_OP_C_CODE_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_sibling_splice(compiler, (yyval.opval), (yyval.opval)->first, 0, (yyvsp[(1) - (1)].opval));
      }
    ;}
    break;

  case 68:
#line 354 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_append_elem(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
    ;}
    break;

  case 70:
#line 361 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_length(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 71:
#line 365 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_length(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 72:
#line 370 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, compiler->cur_module_path, compiler->cur_line);
    ;}
    break;

  case 85:
#line 390 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_malloc_object(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 86:
#line 394 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_malloc_object(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 87:
#line 400 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_convert_type(compiler, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 88:
#line 406 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_field(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 89:
#line 410 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_field(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 90:
#line 414 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_field(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 91:
#line 420 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_PLUS, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 92:
#line 425 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NEGATE, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 93:
#line 430 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_PRE_INC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 94:
#line 435 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POST_INC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 95:
#line 440 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_PRE_DEC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 96:
#line 445 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POST_DEC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 97:
#line 450 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unop(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 98:
#line 454 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unop(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 99:
#line 460 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ADD, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 100:
#line 465 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_SUBTRACT, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 101:
#line 470 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 102:
#line 474 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 103:
#line 478 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 104:
#line 482 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 105:
#line 486 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 106:
#line 490 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 107:
#line 494 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 108:
#line 498 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 109:
#line 502 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 110:
#line 506 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 111:
#line 510 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 112:
#line 514 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 113:
#line 520 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_elem(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 114:
#line 524 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_elem(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 115:
#line 528 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_elem(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 116:
#line 534 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, (yyvsp[(1) - (4)].opval)->file, (yyvsp[(1) - (4)].opval)->line), (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 117:
#line 538 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 118:
#line 542 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_terms);
    ;}
    break;

  case 119:
#line 547 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 120:
#line 551 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_terms);
    ;}
    break;

  case 121:
#line 558 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    ;}
    break;

  case 122:
#line 562 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->code == SPVM_OP_C_CODE_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_sibling_splice(compiler, (yyval.opval), (yyval.opval)->first, 0, (yyvsp[(1) - (1)].opval));
      }
    ;}
    break;

  case 123:
#line 574 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_append_elem(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
    ;}
    break;

  case 125:
#line 581 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my_var(compiler, SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_MY_VAR, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), NULL);
    ;}
    break;

  case 126:
#line 587 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    ;}
    break;

  case 127:
#line 591 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->code == SPVM_OP_C_CODE_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_sibling_splice(compiler, (yyval.opval), (yyval.opval)->first, 0, (yyvsp[(1) - (1)].opval));
      }
    ;}
    break;

  case 128:
#line 603 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_append_elem(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
    ;}
    break;

  case 132:
#line 615 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_name(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 133:
#line 621 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_array(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 134:
#line 625 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_array(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 135:
#line 631 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_array(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 136:
#line 635 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_array(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 142:
#line 649 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_try_catch(compiler, (yyvsp[(1) - (7)].opval), (yyvsp[(2) - (7)].opval), (yyvsp[(3) - (7)].opval), (yyvsp[(5) - (7)].opval), (yyvsp[(7) - (7)].opval));
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2512 "spvm_yacc.tab.c"
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


#line 653 "yacc/spvm_yacc.y"



