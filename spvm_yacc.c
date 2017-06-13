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
#define YYLAST   698

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  137
/* YYNRULES -- Number of states.  */
#define YYNSTATES  250

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
     218,   221,   222,   224,   226,   228,   230,   232,   234,   236,
     238,   240,   242,   244,   246,   249,   252,   257,   262,   265,
     268,   271,   274,   277,   280,   283,   286,   290,   294,   298,
     302,   306,   310,   314,   318,   322,   326,   330,   334,   338,
     342,   347,   352,   359,   363,   370,   374,   375,   377,   381,
     383,   387,   388,   390,   394,   396,   398,   400,   402,   410,
     414,   418,   423,   428,   430,   432,   434,   436
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      61,     0,    -1,    62,    -1,    -1,    63,    -1,    63,    64,
      -1,    64,    -1,    65,    -1,    66,    -1,    13,   117,    31,
      -1,     6,   117,    70,    -1,    -1,    68,    -1,    68,    69,
      -1,    69,    -1,    87,    -1,    88,    -1,    89,    -1,    55,
      67,    56,    -1,    55,    72,    56,    -1,    -1,    73,    -1,
      73,    57,    74,    -1,    74,    -1,    17,    -1,    17,    32,
      19,    -1,    -1,    76,    -1,    76,    77,    -1,    77,    -1,
      79,    -1,    85,    -1,    80,    -1,    81,    -1,    78,    -1,
      82,    -1,    83,    -1,    84,    -1,   111,    -1,    55,    75,
      56,    -1,    96,    31,    -1,    91,    31,    -1,    31,    -1,
      11,    53,    79,    96,    31,    95,    52,    78,    -1,    12,
      53,    96,    52,    78,    -1,    25,    53,    96,    52,    78,
      -1,    26,    96,    58,    -1,    27,    58,    -1,     7,    53,
      96,    52,    78,    86,    -1,    -1,     9,    78,    -1,     8,
      53,    96,    52,    78,    86,    -1,     4,   115,    58,   109,
      31,    -1,     5,   116,    53,   104,    52,    58,   107,   114,
      78,    -1,     5,   116,    53,   104,    52,    58,   107,   114,
      31,    -1,    20,    71,    -1,     3,    18,    58,   109,    -1,
       3,    18,    -1,     3,    18,    58,   109,    32,    96,    -1,
       3,    18,    32,    96,    -1,    15,    -1,    16,    -1,    10,
      -1,    10,    96,    -1,    24,    96,    -1,    90,    -1,    -1,
      93,    -1,    93,    57,    96,    -1,    96,    -1,    47,    96,
      -1,    -1,    96,    -1,    18,    -1,    19,    -1,    23,    -1,
     103,    -1,    99,    -1,   100,    -1,   101,    -1,   102,    -1,
      98,    -1,    97,    -1,    94,    -1,    14,   110,    -1,    14,
     113,    -1,    53,   109,    52,    96,    -1,    96,    55,   115,
      56,    -1,    40,    96,    -1,    41,    96,    -1,    50,    96,
      -1,    96,    50,    -1,    49,    96,    -1,    96,    49,    -1,
      45,    96,    -1,    48,    96,    -1,    96,    40,    96,    -1,
      96,    41,    96,    -1,    96,    44,    96,    -1,    96,    43,
      96,    -1,    96,    42,    96,    -1,    96,    35,    96,    -1,
      96,    37,    96,    -1,    96,    36,    96,    -1,    96,    39,
      96,    -1,    96,    38,    96,    -1,    96,    32,    96,    -1,
      53,    96,    52,    -1,    96,    33,    96,    -1,    96,    34,
      96,    -1,    96,    54,    96,    59,    -1,   116,    53,    92,
      52,    -1,    96,    51,   116,    53,    92,    52,    -1,    96,
      51,   116,    -1,   117,    51,   116,    53,    92,    52,    -1,
     117,    51,   116,    -1,    -1,   105,    -1,   105,    57,   106,
      -1,   106,    -1,    18,    58,   109,    -1,    -1,   108,    -1,
     108,    57,    21,    -1,    21,    -1,   110,    -1,   112,    -1,
      17,    -1,    29,    78,    30,    53,    18,    52,    78,    -1,
     110,    54,    59,    -1,   112,    54,    59,    -1,   110,    54,
      96,    59,    -1,   112,    54,    96,    59,    -1,   109,    -1,
      28,    -1,    17,    -1,    17,    -1,    17,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    50,    50,    68,    71,    83,    87,    90,    91,    94,
     100,   110,   113,   125,   129,   132,   133,   134,   137,   144,
     152,   155,   167,   171,   174,   179,   188,   191,   203,   207,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   221,
     228,   233,   234,   240,   246,   252,   258,   264,   267,   274,
     277,   282,   288,   294,   298,   303,   309,   313,   317,   321,
     327,   331,   335,   338,   342,   346,   350,   353,   365,   369,
     372,   379,   382,   385,   386,   387,   388,   389,   390,   391,
     392,   393,   394,   395,   398,   402,   408,   414,   420,   425,
     430,   435,   440,   445,   450,   454,   460,   465,   470,   474,
     478,   482,   486,   490,   494,   498,   502,   506,   510,   514,
     520,   526,   530,   534,   539,   543,   551,   554,   566,   570,
     573,   580,   583,   595,   599,   602,   603,   607,   613,   619,
     623,   629,   633,   639,   640,   642,   643,   644
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
  "opt_descriptors", "descriptors", "type", "type_name", "try_catch",
  "type_array", "type_array_with_length", "type_or_void", "field_name",
  "sub_name", "package_name", 0
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
      94,    95,    95,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    97,    97,    98,    99,   100,   100,
     100,   100,   100,   100,   100,   100,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     102,   103,   103,   103,   103,   103,   104,   104,   105,   105,
     106,   107,   107,   108,   108,   109,   109,   110,   111,   112,
     112,   113,   113,   114,   114,   115,   116,   117
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
       2,     0,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     4,     4,     2,     2,
       2,     2,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     4,     6,     3,     6,     3,     0,     1,     3,     1,
       3,     0,     1,     3,     1,     1,     1,     1,     7,     3,
       3,     4,     4,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     0,     2,     4,     6,     7,     8,   137,
       0,     0,     1,     5,    11,    10,     9,     0,     0,     0,
       0,    12,    14,    15,    16,    17,   135,     0,   136,     0,
      20,    55,    18,    13,     0,   116,    24,     0,    21,    23,
     127,     0,   125,   126,     0,     0,   117,   119,     0,    19,
       0,    52,     0,     0,     0,     0,     0,    25,    22,   129,
     130,   120,   121,   118,   124,     0,   122,   134,   133,     0,
       0,    54,    26,    53,   123,     0,     0,    62,     0,     0,
       0,    60,    61,   136,    73,    74,    75,     0,     0,     0,
       0,     0,    42,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27,    29,    34,    30,    32,    33,    35,    36,
      37,    31,    65,     0,    83,     0,    82,    81,    77,    78,
      79,    80,    76,    38,     0,     0,    57,     0,    63,     0,
       0,    84,     0,    85,    64,     0,     0,    47,     0,    88,
      89,    94,    70,    95,    92,    90,   127,     0,     0,    39,
      28,    41,    40,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    93,    91,     0,     0,
       0,    66,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    46,     0,   107,     0,   106,   108,   109,   101,   103,
     102,   105,   104,    96,    97,   100,    99,    98,   113,     0,
       0,     0,    67,    69,   115,    59,    56,     0,     0,     0,
       0,     0,     0,     0,    86,    66,   110,    87,   111,     0,
      66,     0,    49,    71,    44,   131,   132,    45,     0,     0,
      68,     0,    58,     0,     0,    48,     0,    72,     0,   112,
     114,     0,    50,     0,   128,     0,    43,     0,    49,    51
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,     8,    20,    21,    22,
      15,    31,    37,    38,    39,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   235,    23,    24,    25,
     112,   113,   201,   202,   114,   236,   115,   116,   117,   118,
     119,   120,   121,   122,    45,    46,    47,    65,    66,    41,
      42,   123,    43,   133,    69,    27,   124,   125
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -201
static const yytype_int16 yypact[] =
{
       0,    -1,    -1,    21,  -201,     0,  -201,  -201,  -201,  -201,
      -7,    20,  -201,  -201,    29,  -201,  -201,    47,    56,    19,
      22,    29,  -201,  -201,  -201,  -201,  -201,    24,  -201,    43,
      62,  -201,  -201,  -201,    80,    82,    66,    46,    48,  -201,
    -201,    73,    53,    59,    67,    72,    63,  -201,   107,  -201,
      62,  -201,    71,    75,    80,    69,    82,  -201,  -201,  -201,
    -201,  -201,   108,  -201,  -201,    18,    78,  -201,  -201,   -13,
     115,  -201,   165,  -201,  -201,   121,    88,   224,    89,    91,
      80,  -201,  -201,    95,  -201,  -201,  -201,   224,    94,   224,
      90,   102,  -201,   224,   224,   224,   224,   224,   224,   224,
     261,   104,   165,  -201,  -201,  -201,  -201,  -201,  -201,  -201,
    -201,  -201,  -201,   127,  -201,   395,  -201,  -201,  -201,  -201,
    -201,  -201,  -201,  -201,   113,   119,   -21,   224,   564,   213,
     224,   131,   132,  -201,   564,   224,   367,  -201,   157,    61,
      61,    61,    61,    61,    68,    68,    -8,   444,   141,  -201,
    -201,  -201,  -201,   224,   224,   224,   224,   224,   224,   224,
     224,   224,   224,   224,   224,   224,  -201,  -201,    56,   224,
      47,   224,    56,   224,    80,   468,   224,   492,    -9,   114,
     516,  -201,   142,  -201,   224,   564,   586,   607,   249,   249,
     625,   643,    12,    26,    26,    61,    61,    61,   144,   283,
     143,   146,   145,   564,   147,   564,   169,   102,   420,   102,
     311,   339,   102,   185,   -51,   224,  -201,  -201,  -201,   224,
     224,   224,    50,   224,  -201,  -201,  -201,  -201,   152,   155,
     564,   156,   564,   158,   102,  -201,   167,   564,   102,  -201,
    -201,   224,  -201,   102,  -201,   540,  -201,   102,    50,  -201
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -201,  -201,  -201,  -201,   204,  -201,  -201,  -201,  -201,   196,
    -201,  -201,  -201,  -201,   171,  -201,  -201,   120,   -69,    96,
    -201,  -201,  -201,  -201,  -201,  -201,   -24,  -201,  -201,  -201,
    -201,  -201,  -200,  -201,  -201,  -201,   -70,  -201,  -201,  -201,
    -201,  -201,  -201,  -201,  -201,  -201,   170,  -201,  -201,   -53,
     153,  -201,   154,  -201,  -201,    65,   -16,    70
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -138
static const yytype_int16 yytable[] =
{
      73,    61,    29,   169,   170,    80,     1,   128,    83,    84,
      85,   173,    68,     2,    86,   229,     9,   134,    71,   136,
     231,    12,   138,   139,   140,   141,   142,   143,   144,   145,
     147,    93,    94,    17,    18,    40,    95,   174,    96,    97,
      98,    99,    72,  -137,   100,  -136,    67,   148,    14,    19,
      59,    16,   161,   162,   163,   164,   165,   175,   233,   234,
     177,   166,   167,   168,    26,   180,   169,   170,   163,   164,
     165,    10,    11,    28,    30,   166,   167,   168,    32,    36,
     169,   170,    34,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,    35,    40,    48,   199,
      44,   203,    49,   205,    51,    50,   208,    52,   210,   211,
     166,   167,   168,    53,   214,   169,   170,  -138,  -138,   168,
      56,   206,   169,   170,    55,    54,    57,    62,    80,    64,
      59,    83,    84,    85,    60,    70,    74,    86,   222,   126,
     224,   127,   129,   227,   130,   203,  -137,   135,   137,   230,
     203,   232,   198,   237,    93,    94,   204,    72,   151,    95,
     149,    96,    97,    98,    99,   242,   171,   100,    75,   244,
     172,   245,    76,    60,   246,    77,    78,    79,   248,    80,
      81,    82,    83,    84,    85,   178,   179,   182,    86,    87,
      88,    89,    90,   184,    91,   213,    92,   215,   218,   217,
     220,   221,   219,   228,   238,    93,    94,   239,   240,    13,
      95,   241,    96,    97,    98,    99,    75,    33,   100,   243,
      72,    58,   150,    77,   249,   176,    63,    80,    81,    82,
      83,    84,    85,   131,   132,   200,    86,    87,    80,     0,
       0,    83,    84,    85,    92,     0,     0,    86,     0,     0,
       0,     0,     0,    93,    94,     0,     0,     0,    95,     0,
      96,    97,    98,    99,    93,    94,   100,     0,     0,    95,
       0,    96,    97,    98,    99,    80,     0,   100,   146,    84,
      85,     0,     0,     0,    86,     0,   158,   159,   160,   161,
     162,   163,   164,   165,     0,     0,     0,     0,   166,   167,
     168,    93,    94,   169,   170,     0,    95,     0,    96,    97,
      98,    99,     0,     0,   100,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,     0,     0,
       0,     0,   166,   167,   168,     0,     0,   169,   170,     0,
       0,     0,   216,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,     0,     0,     0,     0,
     166,   167,   168,     0,     0,   169,   170,     0,     0,     0,
     225,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,     0,     0,     0,     0,   166,   167,
     168,     0,     0,   169,   170,     0,     0,     0,   226,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,     0,     0,     0,     0,   166,   167,   168,     0,
       0,   169,   170,     0,     0,   181,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
       0,     0,     0,     0,   166,   167,   168,     0,     0,   169,
     170,   223,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,     0,     0,     0,     0,   166,
     167,   168,     0,     0,   169,   170,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,     0,
       0,     0,     0,   166,   167,   168,   183,     0,   169,   170,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,     0,     0,     0,     0,   166,   167,   168,
     207,     0,   169,   170,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,     0,     0,     0,
       0,   166,   167,   168,   209,     0,   169,   170,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,     0,     0,     0,     0,   166,   167,   168,   212,     0,
     169,   170,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,     0,     0,     0,     0,   166,
     167,   168,   247,     0,   169,   170,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,     0,
       0,     0,     0,   166,   167,   168,     0,     0,   169,   170,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,     0,     0,     0,     0,   166,   167,   168,     0,     0,
     169,   170,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,     0,     0,     0,     0,   166,   167,   168,     0,
       0,   169,   170,   159,   160,   161,   162,   163,   164,   165,
       0,     0,     0,     0,   166,   167,   168,     0,     0,   169,
     170,  -138,   160,   161,   162,   163,   164,   165,     0,     0,
       0,     0,   166,   167,   168,     0,     0,   169,   170
};

static const yytype_int16 yycheck[] =
{
      69,    54,    18,    54,    55,    14,     6,    77,    17,    18,
      19,    32,    65,    13,    23,   215,    17,    87,    31,    89,
     220,     0,    91,    93,    94,    95,    96,    97,    98,    99,
     100,    40,    41,     4,     5,    17,    45,    58,    47,    48,
      49,    50,    55,    51,    53,    53,    28,   100,    55,    20,
      59,    31,    40,    41,    42,    43,    44,   127,     8,     9,
     130,    49,    50,    51,    17,   135,    54,    55,    42,    43,
      44,     1,     2,    17,    55,    49,    50,    51,    56,    17,
      54,    55,    58,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,    53,    17,    32,   169,
      18,   171,    56,   173,    31,    57,   176,    54,   178,   179,
      49,    50,    51,    54,   184,    54,    55,    49,    50,    51,
      57,   174,    54,    55,    52,    58,    19,    58,    14,    21,
      59,    17,    18,    19,    59,    57,    21,    23,   207,    18,
     209,    53,    53,   212,    53,   215,    51,    53,    58,   219,
     220,   221,   168,   223,    40,    41,   172,    55,    31,    45,
      56,    47,    48,    49,    50,   234,    53,    53,     3,   238,
      51,   241,     7,    59,   243,    10,    11,    12,   247,    14,
      15,    16,    17,    18,    19,    54,    54,    30,    23,    24,
      25,    26,    27,    52,    29,    53,    31,    53,    52,    56,
      53,    32,    57,    18,    52,    40,    41,    52,    52,     5,
      45,    53,    47,    48,    49,    50,     3,    21,    53,    52,
      55,    50,   102,    10,   248,   129,    56,    14,    15,    16,
      17,    18,    19,    80,    80,   170,    23,    24,    14,    -1,
      -1,    17,    18,    19,    31,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    40,    41,    -1,    -1,    -1,    45,    -1,
      47,    48,    49,    50,    40,    41,    53,    -1,    -1,    45,
      -1,    47,    48,    49,    50,    14,    -1,    53,    17,    18,
      19,    -1,    -1,    -1,    23,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,    50,
      51,    40,    41,    54,    55,    -1,    45,    -1,    47,    48,
      49,    50,    -1,    -1,    53,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    49,    50,    51,    -1,    -1,    54,    55,    -1,
      -1,    -1,    59,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      49,    50,    51,    -1,    -1,    54,    55,    -1,    -1,    -1,
      59,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,    50,
      51,    -1,    -1,    54,    55,    -1,    -1,    -1,    59,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    49,    50,    51,    -1,
      -1,    54,    55,    -1,    -1,    58,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    49,    50,    51,    -1,    -1,    54,
      55,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,
      50,    51,    -1,    -1,    54,    55,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    49,    50,    51,    52,    -1,    54,    55,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    49,    50,    51,
      52,    -1,    54,    55,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    49,    50,    51,    52,    -1,    54,    55,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    49,    50,    51,    52,    -1,
      54,    55,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,
      50,    51,    52,    -1,    54,    55,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    49,    50,    51,    -1,    -1,    54,    55,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    49,    50,    51,    -1,    -1,
      54,    55,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    49,    50,    51,    -1,
      -1,    54,    55,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    49,    50,    51,    -1,    -1,    54,
      55,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    49,    50,    51,    -1,    -1,    54,    55
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    13,    61,    62,    63,    64,    65,    66,    17,
     117,   117,     0,    64,    55,    70,    31,     4,     5,    20,
      67,    68,    69,    87,    88,    89,    17,   115,    17,   116,
      55,    71,    56,    69,    58,    53,    17,    72,    73,    74,
      17,   109,   110,   112,    18,   104,   105,   106,    32,    56,
      57,    31,    54,    54,    58,    52,    57,    19,    74,    59,
      59,   109,    58,   106,    21,   107,   108,    28,   109,   114,
      57,    31,    55,    78,    21,     3,     7,    10,    11,    12,
      14,    15,    16,    17,    18,    19,    23,    24,    25,    26,
      27,    29,    31,    40,    41,    45,    47,    48,    49,    50,
      53,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    90,    91,    94,    96,    97,    98,    99,   100,
     101,   102,   103,   111,   116,   117,    18,    53,    96,    53,
      53,   110,   112,   113,    96,    53,    96,    58,    78,    96,
      96,    96,    96,    96,    96,    96,    17,    96,   109,    56,
      77,    31,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    49,    50,    51,    54,
      55,    53,    51,    32,    58,    96,    79,    96,    54,    54,
      96,    58,    30,    52,    52,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,   116,    96,
     115,    92,    93,    96,   116,    96,   109,    52,    96,    52,
      96,    96,    52,    53,    96,    53,    59,    56,    52,    57,
      53,    32,    78,    31,    78,    59,    59,    78,    18,    92,
      96,    92,    96,     8,     9,    86,    95,    96,    52,    52,
      52,    53,    78,    52,    78,    96,    78,    52,    78,    86
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
      else {
#ifdef DEBUG
        // Dump spvm information
        SPVM_DUMPER_dump_spvm(compiler);
#endif
      }
    ;}
    break;

  case 3:
#line 68 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    ;}
    break;

  case 4:
#line 72 "yacc/spvm_yacc.y"
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
#line 84 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_append_elem(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
    ;}
    break;

  case 9:
#line 95 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 10:
#line 101 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval), (yyvsp[(3) - (3)].opval));
      if (compiler->fatal_error) {
        YYABORT;
      }
    ;}
    break;

  case 11:
#line 110 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    ;}
    break;

  case 12:
#line 114 "yacc/spvm_yacc.y"
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
#line 126 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_append_elem(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
    ;}
    break;

  case 18:
#line 138 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CLASS_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_sibling_splice(compiler, (yyval.opval), NULL, 0, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 19:
#line 145 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ENUM_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_sibling_splice(compiler, (yyval.opval), NULL, 0, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 20:
#line 152 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    ;}
    break;

  case 21:
#line 156 "yacc/spvm_yacc.y"
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
#line 168 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_append_elem(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
    ;}
    break;

  case 24:
#line 175 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ENUMERATION_VALUE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      SPVM_OP_sibling_splice(compiler, (yyval.opval), NULL, 0, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 25:
#line 180 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ENUMERATION_VALUE, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_sibling_splice(compiler, (yyval.opval), NULL, 0, (yyvsp[(1) - (3)].opval));
      SPVM_OP_sibling_splice(compiler, (yyval.opval), (yyvsp[(1) - (3)].opval), 0, (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 26:
#line 188 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    ;}
    break;

  case 27:
#line 192 "yacc/spvm_yacc.y"
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
#line 204 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_append_elem(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
    ;}
    break;

  case 39:
#line 222 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_sibling_splice(compiler, (yyval.opval), NULL, 0, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 40:
#line 229 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POP, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      SPVM_OP_sibling_splice(compiler, (yyval.opval), NULL, 0, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 42:
#line 235 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
    ;}
    break;

  case 43:
#line 241 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[(1) - (8)].opval), (yyvsp[(3) - (8)].opval), (yyvsp[(4) - (8)].opval), (yyvsp[(6) - (8)].opval), (yyvsp[(8) - (8)].opval));
    ;}
    break;

  case 44:
#line 247 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 45:
#line 253 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 46:
#line 259 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 48:
#line 268 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
    ;}
    break;

  case 49:
#line 274 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, compiler->cur_module_path, compiler->cur_line);
    ;}
    break;

  case 50:
#line 278 "yacc/spvm_yacc.y"
    {
      (yyvsp[(2) - (2)].opval)->flag |= SPVM_OP_C_FLAG_BLOCK_ELSE;
      (yyval.opval) = (yyvsp[(2) - (2)].opval);
    ;}
    break;

  case 51:
#line 283 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
    ;}
    break;

  case 52:
#line 289 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 53:
#line 295 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(1) - (9)].opval), (yyvsp[(2) - (9)].opval), (yyvsp[(4) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(8) - (9)].opval), (yyvsp[(9) - (9)].opval));
     ;}
    break;

  case 54:
#line 299 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(1) - (9)].opval), (yyvsp[(2) - (9)].opval), (yyvsp[(4) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(8) - (9)].opval), NULL);
     ;}
    break;

  case 55:
#line 304 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 56:
#line 310 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my_var(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval), NULL);
    ;}
    break;

  case 57:
#line 314 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my_var(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL, NULL);
    ;}
    break;

  case 58:
#line 318 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my_var(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(2) - (6)].opval), (yyvsp[(4) - (6)].opval), (yyvsp[(6) - (6)].opval));
    ;}
    break;

  case 59:
#line 322 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my_var(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval), NULL, (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 60:
#line 328 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_last(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 61:
#line 332 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_next(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 62:
#line 335 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 63:
#line 339 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 64:
#line 343 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 66:
#line 350 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    ;}
    break;

  case 67:
#line 354 "yacc/spvm_yacc.y"
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
#line 366 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_append_elem(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
    ;}
    break;

  case 70:
#line 373 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_length(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 71:
#line 379 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, compiler->cur_module_path, compiler->cur_line);
    ;}
    break;

  case 84:
#line 399 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_malloc_object(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 85:
#line 403 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_malloc_object(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 86:
#line 409 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_convert_type(compiler, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 87:
#line 415 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_field(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 88:
#line 421 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_PLUS, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 89:
#line 426 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NEGATE, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 90:
#line 431 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_PRE_INC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 91:
#line 436 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POST_INC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 92:
#line 441 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_PRE_DEC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 93:
#line 446 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POST_DEC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 94:
#line 451 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unop(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 95:
#line 455 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unop(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 96:
#line 461 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ADD, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 97:
#line 466 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_SUBTRACT, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 98:
#line 471 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 99:
#line 475 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 100:
#line 479 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 101:
#line 483 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 102:
#line 487 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 103:
#line 491 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 104:
#line 495 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 105:
#line 499 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 106:
#line 503 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 107:
#line 507 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 108:
#line 511 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 109:
#line 515 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 110:
#line 521 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_elem(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 111:
#line 527 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, (yyvsp[(1) - (4)].opval)->file, (yyvsp[(1) - (4)].opval)->line), (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 112:
#line 531 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 113:
#line 535 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_terms);
    ;}
    break;

  case 114:
#line 540 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 115:
#line 544 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_terms);
    ;}
    break;

  case 116:
#line 551 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    ;}
    break;

  case 117:
#line 555 "yacc/spvm_yacc.y"
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

  case 118:
#line 567 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_append_elem(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
    ;}
    break;

  case 120:
#line 574 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my_var(compiler, SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_MY_VAR, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), NULL);
    ;}
    break;

  case 121:
#line 580 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    ;}
    break;

  case 122:
#line 584 "yacc/spvm_yacc.y"
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
#line 596 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_append_elem(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
    ;}
    break;

  case 127:
#line 608 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_name(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 128:
#line 614 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_try_catch(compiler, (yyvsp[(1) - (7)].opval), (yyvsp[(2) - (7)].opval), (yyvsp[(3) - (7)].opval), (yyvsp[(5) - (7)].opval), (yyvsp[(7) - (7)].opval));
    ;}
    break;

  case 129:
#line 620 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_array(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 130:
#line 624 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_array(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 131:
#line 630 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_array(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 132:
#line 634 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_array(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2474 "spvm_yacc.tab.c"
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


#line 646 "yacc/spvm_yacc.y"



