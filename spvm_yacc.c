
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         SPVM_yyparse
#define yylex           SPVM_yylex
#define yyerror         SPVM_yyerror
#define yylval          SPVM_yylval
#define yychar          SPVM_yychar
#define yydebug         SPVM_yydebug
#define yynerrs         SPVM_yynerrs


/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 5 "yacc/spvm_yacc.y"

  #include <stdio.h>
  
  #include "spvm_compiler.h"
  #include "spvm_yacc_util.h"
  #include "spvm_toke.h"
  #include "spvm_op.h"
  #include "spvm_dumper.h"
  #include "spvm_constant.h"
  #include "spvm_type.h"


/* Line 189 of yacc.c  */
#line 94 "spvm_yacc.tab.c"

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
     EVAL = 284,
     EXCEPTION_VAR = 285,
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



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 182 "spvm_yacc.tab.c"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   931

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  60
/* YYNRULES -- Number of rules.  */
#define YYNRULES  153
/* YYNRULES -- Number of states.  */
#define YYNSTATES  284

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
      55,    54,     2,    42,    59,    43,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    60,    31,
      38,     2,    39,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    56,     2,    61,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    57,     2,    58,    47,     2,     2,     2,
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
      36,    37,    40,    41,    44,    45,    46,    48,    49,    50,
      51,    52,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    13,    15,    17,
      21,    26,    30,    34,    36,    40,    41,    43,    46,    48,
      50,    52,    54,    58,    62,    63,    65,    69,    71,    73,
      77,    78,    80,    83,    85,    87,    89,    91,    93,    95,
      97,    99,   101,   103,   107,   110,   113,   115,   117,   119,
     128,   134,   140,   144,   147,   154,   155,   158,   165,   171,
     181,   191,   194,   199,   202,   204,   206,   208,   211,   213,
     216,   220,   224,   228,   229,   231,   235,   237,   240,   245,
     247,   249,   251,   253,   255,   257,   259,   261,   263,   265,
     267,   269,   271,   274,   277,   282,   288,   293,   298,   301,
     304,   307,   310,   313,   316,   319,   322,   326,   330,   334,
     338,   342,   346,   350,   354,   358,   362,   366,   370,   376,
     380,   384,   388,   392,   396,   402,   407,   412,   417,   424,
     428,   435,   439,   440,   442,   446,   448,   452,   453,   455,
     459,   461,   463,   465,   467,   471,   475,   480,   485,   487,
     489,   491,   493,   495
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      63,     0,    -1,    64,    -1,    -1,    65,    -1,    65,    66,
      -1,    66,    -1,    67,    -1,    70,    -1,    13,   120,    31,
      -1,    13,   120,    68,    31,    -1,    57,    69,    58,    -1,
      69,    59,   113,    -1,   113,    -1,     6,   120,    74,    -1,
      -1,    72,    -1,    72,    73,    -1,    73,    -1,    92,    -1,
      93,    -1,    94,    -1,    57,    71,    58,    -1,    57,    76,
      58,    -1,    -1,    77,    -1,    77,    59,    78,    -1,    78,
      -1,    17,    -1,    17,    32,   100,    -1,    -1,    80,    -1,
      80,    81,    -1,    81,    -1,    83,    -1,    90,    -1,    85,
      -1,    86,    -1,    82,    -1,    87,    -1,    88,    -1,    89,
      -1,   121,    -1,    57,    79,    58,    -1,   100,    31,    -1,
      96,    31,    -1,    31,    -1,   100,    -1,    96,    -1,    11,
      55,    83,   100,    31,    84,    54,    82,    -1,    12,    55,
     100,    54,    82,    -1,    25,    55,   100,    54,    82,    -1,
      26,   100,    60,    -1,    27,    60,    -1,     7,    55,   100,
      54,    82,    91,    -1,    -1,     9,    82,    -1,     8,    55,
     100,    54,    82,    91,    -1,     4,   118,    60,   113,    31,
      -1,     5,   119,    55,   108,    54,    60,   111,   117,    82,
      -1,     5,   119,    55,   108,    54,    60,   111,   117,    31,
      -1,    20,    75,    -1,     3,    18,    60,   113,    -1,     3,
      18,    -1,    15,    -1,    16,    -1,    10,    -1,    10,   100,
      -1,    24,    -1,    24,   100,    -1,   103,    32,   100,    -1,
     106,    32,   100,    -1,    30,    32,   100,    -1,    -1,    98,
      -1,    98,    59,   100,    -1,   100,    -1,    49,   100,    -1,
      49,    57,   100,    58,    -1,    18,    -1,    30,    -1,    19,
      -1,    23,    -1,   107,    -1,   103,    -1,   104,    -1,   105,
      -1,   106,    -1,   102,    -1,   101,    -1,    99,    -1,    95,
      -1,    14,   114,    -1,    14,   116,    -1,    55,   113,    54,
     100,    -1,   100,    53,    57,   118,    58,    -1,   103,    57,
     118,    58,    -1,   106,    57,   118,    58,    -1,    42,   100,
      -1,    43,   100,    -1,    52,   100,    -1,   100,    52,    -1,
      51,   100,    -1,   100,    51,    -1,    47,   100,    -1,    50,
     100,    -1,   100,    42,   100,    -1,   100,    43,   100,    -1,
     100,    46,   100,    -1,   100,    45,   100,    -1,   100,    44,
     100,    -1,   100,    35,   100,    -1,   100,    37,   100,    -1,
     100,    36,   100,    -1,   100,    41,   100,    -1,   100,    40,
     100,    -1,   100,    38,   100,    -1,   100,    39,   100,    -1,
      95,    32,    56,    97,    61,    -1,    95,    32,   100,    -1,
      18,    32,   100,    -1,    55,   100,    54,    -1,   100,    33,
     100,    -1,   100,    34,   100,    -1,   100,    53,    56,   100,
      61,    -1,   106,    56,   100,    61,    -1,   103,    56,   100,
      61,    -1,   119,    55,    97,    54,    -1,   100,    53,   119,
      55,    97,    54,    -1,   100,    53,   119,    -1,   120,    53,
     119,    55,    97,    54,    -1,   120,    53,   119,    -1,    -1,
     109,    -1,   109,    59,   110,    -1,   110,    -1,    18,    60,
     113,    -1,    -1,   112,    -1,   112,    59,    21,    -1,    21,
      -1,   114,    -1,   115,    -1,    17,    -1,   114,    56,    61,
      -1,   115,    56,    61,    -1,   114,    56,   100,    61,    -1,
     115,    56,   100,    61,    -1,   113,    -1,    28,    -1,    17,
      -1,    17,    -1,    17,    -1,    29,    82,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    51,    51,    63,    66,    79,    93,    96,    97,   100,
     104,   110,   113,   127,   130,   140,   143,   155,   169,   172,
     173,   174,   177,   185,   194,   197,   210,   224,   227,   233,
     243,   246,   259,   273,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   287,   295,   301,   302,   308,   314,   317,
     323,   329,   335,   341,   344,   358,   361,   365,   371,   377,
     381,   386,   392,   396,   402,   403,   404,   407,   411,   415,
     419,   423,   427,   434,   437,   450,   464,   467,   471,   477,
     478,   479,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   495,   499,   505,   511,   515,   519,   525,   530,
     548,   553,   558,   563,   568,   572,   578,   583,   588,   592,
     596,   600,   604,   608,   612,   616,   620,   625,   630,   634,
     638,   642,   646,   650,   656,   660,   664,   670,   674,   678,
     683,   687,   695,   698,   711,   725,   728,   735,   738,   751,
     765,   768,   769,   772,   778,   782,   788,   792,   798,   799,
     802,   803,   804,   807
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
  "UNDEF", "DIE", "SWITCH", "CASE", "DEFAULT", "VOID", "EVAL",
  "EXCEPTION_VAR", "';'", "ASSIGN", "OR", "AND", "BIT_XOR", "BIT_OR",
  "BIT_AND", "'<'", "'>'", "REL", "SHIFT", "'+'", "'-'", "REMAINDER",
  "DIVIDE", "MULTIPLY", "'~'", "UMINUS", "ARRAY_LENGTH", "NOT", "DEC",
  "INC", "ARROW", "')'", "'('", "'['", "'{'", "'}'", "','", "':'", "']'",
  "$accept", "grammar", "opt_declarations_in_grammar",
  "declarations_in_grammar", "declaration_in_grammar", "use",
  "template_args", "types", "package", "opt_declarations_in_package",
  "declarations_in_package", "declaration_in_package", "package_block",
  "enumeration_block", "opt_enumeration_values", "enumeration_values",
  "enumeration_value", "opt_statements", "statements", "statement",
  "block", "normal_statement", "normal_statement_for_end", "for_statement",
  "while_statement", "switch_statement", "case_statement",
  "default_statement", "if_statement", "else_statement", "field", "sub",
  "enumeration", "my_var", "expression", "opt_terms", "terms",
  "array_length", "term", "new_object", "convert_type", "call_field",
  "unop", "binop", "array_elem", "call_sub", "opt_args", "args", "arg",
  "opt_descriptors", "descriptors", "type", "type_name", "type_array",
  "type_array_with_length", "type_or_void", "field_name", "sub_name",
  "package_name", "eval_block", 0
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
     285,    59,   286,   287,   288,   289,   290,   291,    60,    62,
     292,   293,    43,    45,   294,   295,   296,   126,   297,   298,
     299,   300,   301,   302,    41,    40,    91,   123,   125,    44,
      58,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    62,    63,    64,    64,    65,    65,    66,    66,    67,
      67,    68,    69,    69,    70,    71,    71,    72,    72,    73,
      73,    73,    74,    75,    76,    76,    77,    77,    78,    78,
      79,    79,    80,    80,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    82,    83,    83,    83,    84,    84,    85,
      86,    87,    88,    89,    90,    91,    91,    91,    92,    93,
      93,    94,    95,    95,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    97,    97,    98,    98,    99,    99,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   101,   101,   102,   103,   103,   103,   104,   104,
     104,   104,   104,   104,   104,   104,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   106,   106,   106,   107,   107,   107,
     107,   107,   108,   108,   109,   109,   110,   111,   111,   112,
     112,   113,   113,   114,   115,   115,   116,   116,   117,   117,
     118,   119,   120,   121
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     1,     3,
       4,     3,     3,     1,     3,     0,     1,     2,     1,     1,
       1,     1,     3,     3,     0,     1,     3,     1,     1,     3,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     2,     2,     1,     1,     1,     8,
       5,     5,     3,     2,     6,     0,     2,     6,     5,     9,
       9,     2,     4,     2,     1,     1,     1,     2,     1,     2,
       3,     3,     3,     0,     1,     3,     1,     2,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     4,     5,     4,     4,     2,     2,
       2,     2,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     5,     3,
       3,     3,     3,     3,     5,     4,     4,     4,     6,     3,
       6,     3,     0,     1,     3,     1,     3,     0,     1,     3,
       1,     1,     1,     1,     3,     3,     4,     4,     1,     1,
       1,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     0,     2,     4,     6,     7,     8,   152,
       0,     0,     1,     5,    15,    14,     9,     0,     0,     0,
       0,     0,     0,    16,    18,    19,    20,    21,   143,     0,
      13,   141,   142,    10,   150,     0,   151,     0,    24,    61,
      22,    17,    11,     0,     0,     0,     0,   132,    28,     0,
      25,    27,    12,   144,   145,     0,     0,     0,   133,   135,
       0,    23,     0,    58,     0,     0,     0,     0,     0,   151,
      79,    81,    82,    80,     0,     0,     0,     0,     0,     0,
       0,     0,    91,    90,    29,    89,    88,    84,    85,    86,
      87,    83,     0,     0,    26,   136,   137,   134,    63,    92,
       0,    93,     0,    98,    99,   104,     0,    77,   105,   102,
     100,   143,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     101,     0,     0,     0,     0,     0,    73,     0,   140,     0,
     138,     0,     0,     0,   120,     0,   121,     0,    73,   119,
     122,   123,   111,   113,   112,   116,   117,   115,   114,   106,
     107,   110,   109,   108,     0,     0,   129,     0,     0,     0,
       0,     0,    74,    76,   131,   149,   148,     0,     0,    62,
       0,     0,    78,    94,     0,     0,     0,    73,   126,    96,
     125,    97,   127,     0,    73,    60,    30,    59,   139,   146,
     147,   118,   124,    95,     0,    75,     0,     0,    66,     0,
       0,    64,    65,    68,     0,     0,     0,     0,    80,    46,
       0,    31,    33,    38,    34,    36,    37,    39,    40,    41,
      35,     0,     0,    84,    87,    42,   128,   130,     0,    67,
       0,     0,    69,     0,     0,    53,   153,     0,    43,    32,
      45,    44,     0,     0,     0,     0,     0,     0,    52,    72,
      70,    71,     0,     0,     0,     0,    55,     0,    50,    51,
       0,     0,    54,     0,    48,    47,     0,    56,     0,     0,
      49,     0,    55,    57
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,    18,    29,     8,    22,
      23,    24,    15,    39,    49,    50,    51,   220,   221,   222,
     223,   224,   273,   225,   226,   227,   228,   229,   230,   272,
      25,    26,    27,    82,   231,   171,   172,    83,   173,    85,
      86,    87,    88,    89,    90,    91,    57,    58,    59,   139,
     140,    30,    31,    32,   101,   177,    35,    92,    93,   235
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -192
static const yytype_int16 yypact[] =
{
      20,    -7,    -7,    34,  -192,    20,  -192,  -192,  -192,  -192,
     -18,   -29,  -192,  -192,    18,  -192,  -192,    54,    14,    56,
      58,    31,    -8,    18,  -192,  -192,  -192,  -192,  -192,    -6,
    -192,    41,    44,  -192,  -192,    30,  -192,    60,    92,  -192,
    -192,  -192,  -192,    54,    50,    55,    54,    99,    87,    62,
      63,  -192,  -192,  -192,  -192,    96,    68,    69,    70,  -192,
     388,  -192,    92,  -192,    54,    71,    99,   114,    54,    81,
     103,  -192,  -192,  -192,   388,   388,   388,   242,   388,   388,
     388,   430,   109,  -192,   806,  -192,  -192,    39,  -192,  -192,
      46,  -192,    88,    89,  -192,  -192,   123,  -192,    91,   104,
     108,  -192,   388,    28,    28,    28,   388,    28,    28,    33,
      33,   -28,   696,   111,   284,   388,   388,   388,   388,   388,
     388,   388,   388,   388,   388,   388,   388,   388,   388,  -192,
    -192,    -9,   388,    56,   388,    56,   388,    58,  -192,    12,
      93,    54,   107,   171,   806,   626,  -192,   388,   388,   806,
     826,   845,   862,   862,   423,   878,   878,   878,   266,    94,
      94,    28,    28,    28,   388,    56,   115,   453,   105,   482,
     113,   118,   110,   806,   120,  -192,  -192,   -22,   145,  -192,
     511,   540,  -192,  -192,   106,   569,   119,   388,  -192,  -192,
    -192,  -192,  -192,   388,   388,  -192,   224,  -192,  -192,  -192,
    -192,  -192,  -192,  -192,   122,   806,   125,   127,   388,   129,
     131,  -192,  -192,   388,   136,   388,   137,   116,   164,  -192,
     140,   224,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,
    -192,   168,   652,   -20,    37,  -192,  -192,  -192,   388,   806,
     327,   388,   806,   388,   598,  -192,  -192,   388,  -192,  -192,
    -192,  -192,   388,   388,   718,   388,   740,   762,  -192,   806,
     806,   806,   116,   675,   116,   116,    98,   370,  -192,  -192,
     147,   116,  -192,   146,  -192,   806,   388,  -192,   116,   784,
    -192,   116,    98,  -192
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -192,  -192,  -192,  -192,   198,  -192,  -192,  -192,  -192,  -192,
    -192,   181,  -192,  -192,  -192,  -192,   143,  -192,  -192,   -15,
    -173,   -32,  -192,  -192,  -192,  -192,  -192,  -192,  -192,   -73,
    -192,  -192,  -192,  -192,   -57,  -117,  -192,  -192,   -60,  -192,
    -192,  -191,  -192,  -192,  -189,  -192,  -192,  -192,   149,  -192,
    -192,   -40,   144,   151,  -192,  -192,  -122,   -19,   112,  -192
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -153
static const yytype_int16 yytable[] =
{
      84,    37,    16,    52,   197,   233,    55,   234,    36,   195,
       9,   168,   252,   170,   103,   104,   105,   107,   108,   109,
     110,   112,    19,    20,    95,  -152,     1,  -151,    17,    28,
     233,   184,   234,     2,    12,   196,   132,   133,    21,    14,
     175,   113,   144,   186,   246,    33,   145,   164,   165,   233,
      40,   234,    42,    43,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   253,
     204,    28,   167,    34,   169,    36,   233,   206,   234,   129,
     130,   131,   180,   181,  -153,  -153,   131,   183,    38,   266,
      46,   268,   269,   134,   135,   132,   133,    44,   277,   176,
      45,   179,   134,   135,   185,   280,   270,   271,   282,    48,
      67,    53,   166,    10,    11,    47,    54,    56,   174,    60,
      61,    68,    62,    65,    69,    70,    71,    63,    64,    66,
      72,    96,    98,   205,  -152,   102,   232,    73,   126,   127,
     128,   114,   137,   136,   138,   129,   130,   131,   239,    74,
      75,   141,   178,   242,    76,   244,    77,    78,    79,    80,
     142,   232,    81,   189,   143,   147,   198,   201,    53,   193,
     187,   191,   192,   196,    67,   194,   236,   203,   254,   237,
     232,   256,   238,   257,   240,    68,   241,   259,    69,    70,
      71,   243,   260,   261,    72,   263,   247,   245,   248,   250,
     278,    73,   276,    13,    41,    94,   249,   275,   255,   283,
     274,     0,    99,    74,    75,    97,   279,     0,    76,   100,
      77,    78,    79,    80,     0,     0,    81,    67,     0,     0,
       0,   207,    54,     0,   208,   209,   210,     0,    68,   211,
     212,    69,    70,    71,     0,    67,     0,    72,   213,   214,
     215,   216,     0,   217,   218,   219,    68,     0,     0,    69,
      70,    71,     0,     0,     0,    72,    74,    75,     0,     0,
       0,    76,    73,    77,    78,    79,    80,     0,     0,    81,
       0,   196,     0,     0,    74,    75,     0,    67,     0,    76,
       0,    77,    78,    79,    80,     0,     0,    81,    68,   106,
       0,    69,    70,    71,     0,     0,     0,    72,   124,   125,
     126,   127,   128,     0,    73,     0,     0,   129,   130,   131,
       0,     0,     0,     0,     0,     0,    74,    75,     0,     0,
      67,    76,     0,    77,    78,    79,    80,   208,     0,    81,
     148,    68,   211,   212,    69,    70,    71,     0,     0,     0,
      72,   213,     0,     0,     0,     0,     0,   218,   219,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    74,
      75,     0,     0,    67,    76,     0,    77,    78,    79,    80,
     208,     0,    81,     0,    68,   211,   212,    69,    70,    71,
       0,    67,     0,    72,   213,     0,     0,     0,     0,     0,
     218,     0,    68,     0,     0,    69,    70,    71,     0,     0,
       0,    72,    74,    75,     0,     0,     0,    76,    73,    77,
      78,    79,    80,     0,     0,    81,     0,     0,     0,     0,
      74,    75,     0,    67,     0,    76,     0,    77,    78,    79,
      80,     0,     0,    81,    68,     0,     0,   111,    70,    71,
       0,     0,     0,    72,     0,     0,     0,     0,     0,     0,
      73,   120,   121,   122,   123,   124,   125,   126,   127,   128,
       0,     0,    74,    75,   129,   130,   131,    76,     0,    77,
      78,    79,    80,     0,     0,    81,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
       0,     0,     0,     0,   129,   130,   131,     0,     0,     0,
       0,     0,     0,     0,   188,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,     0,
       0,     0,     0,   129,   130,   131,     0,     0,     0,     0,
       0,     0,     0,   190,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,     0,     0,
       0,     0,   129,   130,   131,     0,     0,     0,     0,     0,
       0,     0,   199,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,     0,     0,     0,
       0,   129,   130,   131,     0,     0,     0,     0,     0,     0,
       0,   200,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,     0,     0,     0,     0,
     129,   130,   131,     0,     0,     0,     0,     0,     0,     0,
     202,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,     0,     0,     0,     0,   129,
     130,   131,     0,     0,     0,     0,     0,     0,   258,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,     0,     0,     0,     0,   129,   130,   131,
       0,     0,     0,   251,   182,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,     0,
       0,     0,     0,   129,   130,   131,   267,     0,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,     0,     0,     0,     0,   129,   130,   131,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,     0,     0,     0,     0,   129,   130,   131,
     146,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,     0,     0,     0,     0,   129,
     130,   131,   262,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,     0,     0,     0,
       0,   129,   130,   131,   264,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,     0,
       0,     0,     0,   129,   130,   131,   265,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,     0,     0,     0,     0,   129,   130,   131,   281,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,     0,     0,     0,     0,   129,   130,   131,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,     0,     0,     0,     0,   129,   130,   131,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,     0,     0,     0,     0,   129,   130,   131,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,     0,
       0,     0,     0,   129,   130,   131,  -153,  -153,  -153,   123,
     124,   125,   126,   127,   128,     0,     0,     0,     0,   129,
     130,   131
};

static const yytype_int16 yycheck[] =
{
      60,    20,    31,    43,   177,   196,    46,   196,    17,    31,
      17,   133,    32,   135,    74,    75,    76,    77,    78,    79,
      80,    81,     4,     5,    64,    53,     6,    55,    57,    17,
     221,   148,   221,    13,     0,    57,    56,    57,    20,    57,
      28,    81,   102,   165,   217,    31,   106,    56,    57,   240,
      58,   240,    58,    59,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,    32,
     187,    17,   132,    17,   134,    17,   267,   194,   267,    51,
      52,    53,   142,   143,    51,    52,    53,   147,    57,   262,
      60,   264,   265,    56,    57,    56,    57,    56,   271,   139,
      56,   141,    56,    57,   164,   278,     8,     9,   281,    17,
       3,    61,   131,     1,     2,    55,    61,    18,   137,    32,
      58,    14,    59,    54,    17,    18,    19,    31,    60,    59,
      23,    60,    18,   193,    53,    32,   196,    30,    44,    45,
      46,    32,    53,    55,    21,    51,    52,    53,   208,    42,
      43,    60,    59,   213,    47,   215,    49,    50,    51,    52,
      56,   221,    55,    58,    56,    54,    21,    61,    61,    59,
      55,    58,    54,    57,     3,    55,    54,    58,   238,    54,
     240,   241,    55,   243,    55,    14,    55,   247,    17,    18,
      19,    55,   252,   253,    23,   255,    32,    60,    58,    31,
      54,    30,    55,     5,    23,    62,   221,   267,   240,   282,
     267,    -1,    68,    42,    43,    66,   276,    -1,    47,    68,
      49,    50,    51,    52,    -1,    -1,    55,     3,    -1,    -1,
      -1,     7,    61,    -1,    10,    11,    12,    -1,    14,    15,
      16,    17,    18,    19,    -1,     3,    -1,    23,    24,    25,
      26,    27,    -1,    29,    30,    31,    14,    -1,    -1,    17,
      18,    19,    -1,    -1,    -1,    23,    42,    43,    -1,    -1,
      -1,    47,    30,    49,    50,    51,    52,    -1,    -1,    55,
      -1,    57,    -1,    -1,    42,    43,    -1,     3,    -1,    47,
      -1,    49,    50,    51,    52,    -1,    -1,    55,    14,    57,
      -1,    17,    18,    19,    -1,    -1,    -1,    23,    42,    43,
      44,    45,    46,    -1,    30,    -1,    -1,    51,    52,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,    -1,
       3,    47,    -1,    49,    50,    51,    52,    10,    -1,    55,
      56,    14,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,     3,    47,    -1,    49,    50,    51,    52,
      10,    -1,    55,    -1,    14,    15,    16,    17,    18,    19,
      -1,     3,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    14,    -1,    -1,    17,    18,    19,    -1,    -1,
      -1,    23,    42,    43,    -1,    -1,    -1,    47,    30,    49,
      50,    51,    52,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      42,    43,    -1,     3,    -1,    47,    -1,    49,    50,    51,
      52,    -1,    -1,    55,    14,    -1,    -1,    17,    18,    19,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      -1,    -1,    42,    43,    51,    52,    53,    47,    -1,    49,
      50,    51,    52,    -1,    -1,    55,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    51,    52,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    51,    52,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    61,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      51,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    51,
      52,    53,    -1,    -1,    -1,    -1,    -1,    -1,    60,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    51,    52,    53,
      -1,    -1,    -1,    31,    58,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    51,    52,    53,    31,    -1,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    51,    52,    53,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    51,    52,    53,
      54,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    51,
      52,    53,    54,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    51,    52,    53,    54,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    51,    52,    53,    54,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    51,    52,    53,    54,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    51,    52,    53,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    51,    52,    53,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    51,    52,    53,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    51,    52,    53,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    51,
      52,    53
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    13,    63,    64,    65,    66,    67,    70,    17,
     120,   120,     0,    66,    57,    74,    31,    57,    68,     4,
       5,    20,    71,    72,    73,    92,    93,    94,    17,    69,
     113,   114,   115,    31,    17,   118,    17,   119,    57,    75,
      58,    73,    58,    59,    56,    56,    60,    55,    17,    76,
      77,    78,   113,    61,    61,   113,    18,   108,   109,   110,
      32,    58,    59,    31,    60,    54,    59,     3,    14,    17,
      18,    19,    23,    30,    42,    43,    47,    49,    50,    51,
      52,    55,    95,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   119,   120,    78,   113,    60,   110,    18,   114,
     115,   116,    32,   100,   100,   100,    57,   100,   100,   100,
     100,    17,   100,   113,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    51,
      52,    53,    56,    57,    56,    57,    55,    53,    21,   111,
     112,    60,    56,    56,   100,   100,    54,    54,    56,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,    56,    57,   119,   100,   118,   100,
     118,    97,    98,   100,   119,    28,   113,   117,    59,   113,
     100,   100,    58,   100,    97,   100,   118,    55,    61,    58,
      61,    58,    54,    59,    55,    31,    57,    82,    21,    61,
      61,    61,    61,    58,    97,   100,    97,     7,    10,    11,
      12,    15,    16,    24,    25,    26,    27,    29,    30,    31,
      79,    80,    81,    82,    83,    85,    86,    87,    88,    89,
      90,    96,   100,   103,   106,   121,    54,    54,    55,   100,
      55,    55,   100,    55,   100,    60,    82,    32,    58,    81,
      31,    31,    32,    32,   100,    83,   100,   100,    60,   100,
     100,   100,    54,   100,    54,    54,    82,    31,    82,    82,
       8,     9,    91,    84,    96,   100,    55,    82,    54,   100,
      82,    54,    82,    91
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , compiler);
      YYFPRINTF (stderr, "\n");
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





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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

/* Line 1455 of yacc.c  */
#line 52 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_grammar(compiler, (yyvsp[(1) - (1)].opval));

      // Syntax error
      if (compiler->error_count) {
        YYABORT;
      }
    ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 63 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 67 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->code == SPVM_OP_C_CODE_LIST) {
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

/* Line 1455 of yacc.c  */
#line 80 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (2)].opval)->code == SPVM_OP_C_CODE_LIST) {
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

  case 9:

/* Line 1455 of yacc.c  */
#line 101 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 105 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval));
    ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 114 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (3)].opval)->code == SPVM_OP_C_CODE_LIST) {
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

  case 14:

/* Line 1455 of yacc.c  */
#line 131 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval), (yyvsp[(3) - (3)].opval));
      if (compiler->fatal_error) {
        YYABORT;
      }
    ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 140 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 144 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->code == SPVM_OP_C_CODE_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, (yyval.opval), (yyval.opval)->last, (yyvsp[(1) - (1)].opval));
      }
    ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 156 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (2)].opval)->code == SPVM_OP_C_CODE_LIST) {
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

  case 22:

/* Line 1455 of yacc.c  */
#line 178 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CLASS_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_class_block;
    ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 186 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ENUM_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_enum_block;
    ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 194 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 198 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->code == SPVM_OP_C_CODE_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (1)].opval));
        (yyval.opval) = op_list;
      }
    ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 211 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (3)].opval)->code == SPVM_OP_C_CODE_LIST) {
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

  case 28:

/* Line 1455 of yacc.c  */
#line 228 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_enumeration_value = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ENUMERATION_VALUE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      SPVM_OP_insert_child(compiler, op_enumeration_value, op_enumeration_value->last, (yyvsp[(1) - (1)].opval));
      (yyval.opval) = op_enumeration_value;
    ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 234 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_enumeration_value = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ENUMERATION_VALUE, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_enumeration_value, op_enumeration_value->last, (yyvsp[(1) - (3)].opval));
      SPVM_OP_insert_child(compiler, op_enumeration_value, op_enumeration_value->last, (yyvsp[(3) - (3)].opval));
      (yyval.opval) = op_enumeration_value;
    ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 243 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 247 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->code == SPVM_OP_C_CODE_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (1)].opval));
        (yyval.opval) = op_list;
      }
    ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 260 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (2)].opval)->code == SPVM_OP_C_CODE_LIST) {
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

  case 43:

/* Line 1455 of yacc.c  */
#line 288 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_code_block = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_code_block, op_code_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_code_block;
    ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 296 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_pop = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POP, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      SPVM_OP_insert_child(compiler, op_pop, op_pop->last, (yyvsp[(1) - (2)].opval));
      (yyval.opval) = op_pop;
    ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 303 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
    ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 309 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_pop = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POP, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      SPVM_OP_insert_child(compiler, op_pop, op_pop->last, (yyvsp[(1) - (1)].opval));
      (yyval.opval) = op_pop;
    ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 318 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[(1) - (8)].opval), (yyvsp[(3) - (8)].opval), (yyvsp[(4) - (8)].opval), (yyvsp[(6) - (8)].opval), (yyvsp[(8) - (8)].opval));
    ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 324 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 330 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 336 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 345 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, (yyvsp[(1) - (6)].opval)->file, (yyvsp[(1) - (6)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 358 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 362 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (2)].opval);
    ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 366 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
    ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 372 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 378 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(1) - (9)].opval), (yyvsp[(2) - (9)].opval), (yyvsp[(4) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(8) - (9)].opval), (yyvsp[(9) - (9)].opval));
     ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 382 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(1) - (9)].opval), (yyvsp[(2) - (9)].opval), (yyvsp[(4) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(8) - (9)].opval), NULL);
     ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 387 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 393 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my_var(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 397 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my_var(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 404 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 408 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 412 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 416 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 420 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assignop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 424 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assignop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 428 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assignop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 434 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 438 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->code == SPVM_OP_C_CODE_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (1)].opval));
        (yyval.opval) = op_list;
      }
    ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 451 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (3)].opval)->code == SPVM_OP_C_CODE_LIST) {
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

  case 77:

/* Line 1455 of yacc.c  */
#line 468 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_length(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 472 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_length(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 480 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_constant(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 496 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_malloc_object(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 500 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_malloc_object(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 506 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_convert_type(compiler, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 512 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_field(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 516 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_field(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 520 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_field(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 526 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_PLUS, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 531 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(2) - (2)].opval)->code == SPVM_OP_C_CODE_CONSTANT) {
        SPVM_OP* op_constant = (yyvsp[(2) - (2)].opval);
        SPVM_CONSTANT* constant = op_constant->uv.constant;
        if (constant->sign) {
          constant->sign = 0;
        }
        else {
          constant->sign = 1;
        }
        (yyval.opval) = op_constant;
      }
      else {
        SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NEGATE, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
        (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
      }
    ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 549 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_PRE_INC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 554 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POST_INC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 559 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_PRE_DEC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 564 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POST_DEC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 569 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unop(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 573 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unop(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 579 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ADD, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 584 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_SUBTRACT, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 589 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 593 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 597 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 601 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 605 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 609 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 613 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 617 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 621 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_LT);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 626 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_GT);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 631 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assignop(compiler, (yyvsp[(2) - (5)].opval), (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 635 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assignop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 639 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assignop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 643 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 647 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 651 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 657 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_elem(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 661 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_elem(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 665 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_elem(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 671 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, (yyvsp[(1) - (4)].opval)->file, (yyvsp[(1) - (4)].opval)->line), (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 675 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 679 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_terms);
    ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 684 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 688 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_terms);
    ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 695 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 699 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->code == SPVM_OP_C_CODE_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (1)].opval));
        (yyval.opval) = op_list;
      }
    ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 712 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (3)].opval)->code == SPVM_OP_C_CODE_LIST) {
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

  case 136:

/* Line 1455 of yacc.c  */
#line 729 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my_var(compiler, SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_MY, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 735 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 739 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->code == SPVM_OP_C_CODE_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->first, (yyvsp[(1) - (1)].opval));
        (yyval.opval) = op_list;
      }
    ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 752 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (3)].opval)->code == SPVM_OP_C_CODE_LIST) {
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

  case 143:

/* Line 1455 of yacc.c  */
#line 773 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_name(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 779 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_array(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 783 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_array(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 789 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_array(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 793 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_array(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 808 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;



/* Line 1455 of yacc.c  */
#line 2913 "spvm_yacc.tab.c"
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
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (compiler, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
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



/* Line 1675 of yacc.c  */
#line 812 "yacc/spvm_yacc.y"


