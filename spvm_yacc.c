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
#define EVAL 284
#define EXCEPTION_VAR 285
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
#define YYLAST   900

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  146
/* YYNRULES -- Number of states.  */
#define YYNSTATES  269

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
      92,    95,    98,   100,   102,   104,   113,   119,   125,   129,
     132,   139,   140,   143,   150,   156,   166,   176,   179,   184,
     187,   189,   191,   193,   196,   198,   201,   205,   209,   213,
     214,   216,   220,   222,   225,   230,   232,   234,   236,   238,
     240,   242,   244,   246,   248,   250,   252,   254,   256,   259,
     262,   267,   273,   278,   283,   286,   289,   292,   295,   298,
     301,   304,   307,   311,   315,   319,   323,   327,   331,   335,
     339,   343,   347,   351,   355,   359,   363,   367,   373,   378,
     383,   388,   395,   399,   406,   410,   411,   413,   417,   419,
     423,   424,   426,   430,   432,   434,   436,   438,   442,   446,
     451,   456,   458,   460,   462,   464,   466
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      61,     0,    -1,    62,    -1,    -1,    63,    -1,    63,    64,
      -1,    64,    -1,    65,    -1,    66,    -1,    13,   116,    31,
      -1,     6,   116,    70,    -1,    -1,    68,    -1,    68,    69,
      -1,    69,    -1,    88,    -1,    89,    -1,    90,    -1,    55,
      67,    56,    -1,    55,    72,    56,    -1,    -1,    73,    -1,
      73,    57,    74,    -1,    74,    -1,    17,    -1,    17,    32,
      19,    -1,    -1,    76,    -1,    76,    77,    -1,    77,    -1,
      79,    -1,    86,    -1,    81,    -1,    82,    -1,    78,    -1,
      83,    -1,    84,    -1,    85,    -1,   117,    -1,    55,    75,
      56,    -1,    96,    31,    -1,    92,    31,    -1,    31,    -1,
      96,    -1,    92,    -1,    11,    53,    79,    96,    31,    80,
      52,    78,    -1,    12,    53,    96,    52,    78,    -1,    25,
      53,    96,    52,    78,    -1,    26,    96,    58,    -1,    27,
      58,    -1,     7,    53,    96,    52,    78,    87,    -1,    -1,
       9,    78,    -1,     8,    53,    96,    52,    78,    87,    -1,
       4,   114,    58,   109,    31,    -1,     5,   115,    53,   104,
      52,    58,   107,   113,    78,    -1,     5,   115,    53,   104,
      52,    58,   107,   113,    31,    -1,    20,    71,    -1,     3,
      18,    58,   109,    -1,     3,    18,    -1,    15,    -1,    16,
      -1,    10,    -1,    10,    96,    -1,    24,    -1,    24,    96,
      -1,    99,    32,    96,    -1,   102,    32,    96,    -1,    30,
      32,    96,    -1,    -1,    94,    -1,    94,    57,    96,    -1,
      96,    -1,    47,    96,    -1,    47,    55,    96,    56,    -1,
      18,    -1,    30,    -1,    19,    -1,    23,    -1,   103,    -1,
      99,    -1,   100,    -1,   101,    -1,   102,    -1,    98,    -1,
      97,    -1,    95,    -1,    91,    -1,    14,   110,    -1,    14,
     112,    -1,    53,   109,    52,    96,    -1,    96,    51,    55,
     114,    56,    -1,    99,    55,   114,    56,    -1,   102,    55,
     114,    56,    -1,    40,    96,    -1,    41,    96,    -1,    50,
      96,    -1,    96,    50,    -1,    49,    96,    -1,    96,    49,
      -1,    45,    96,    -1,    48,    96,    -1,    96,    40,    96,
      -1,    96,    41,    96,    -1,    96,    44,    96,    -1,    96,
      43,    96,    -1,    96,    42,    96,    -1,    96,    35,    96,
      -1,    96,    37,    96,    -1,    96,    36,    96,    -1,    96,
      39,    96,    -1,    96,    38,    96,    -1,    91,    32,    96,
      -1,    18,    32,    96,    -1,    53,    96,    52,    -1,    96,
      33,    96,    -1,    96,    34,    96,    -1,    96,    51,    54,
      96,    59,    -1,   102,    54,    96,    59,    -1,    99,    54,
      96,    59,    -1,   115,    53,    93,    52,    -1,    96,    51,
     115,    53,    93,    52,    -1,    96,    51,   115,    -1,   116,
      51,   115,    53,    93,    52,    -1,   116,    51,   115,    -1,
      -1,   105,    -1,   105,    57,   106,    -1,   106,    -1,    18,
      58,   109,    -1,    -1,   108,    -1,   108,    57,    21,    -1,
      21,    -1,   110,    -1,   111,    -1,    17,    -1,   110,    54,
      59,    -1,   111,    54,    59,    -1,   110,    54,    96,    59,
      -1,   111,    54,    96,    59,    -1,   109,    -1,    28,    -1,
      17,    -1,    17,    -1,    17,    -1,    29,    78,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    50,    50,    62,    65,    78,    92,    95,    96,    99,
     105,   115,   118,   130,   134,   137,   138,   139,   142,   149,
     157,   160,   172,   176,   179,   184,   193,   196,   208,   212,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   226,
     233,   238,   239,   245,   250,   253,   259,   265,   271,   277,
     280,   294,   297,   301,   307,   313,   317,   322,   328,   332,
     338,   339,   340,   343,   347,   351,   355,   359,   363,   370,
     373,   385,   389,   392,   396,   402,   403,   404,   408,   409,
     410,   411,   412,   413,   414,   415,   416,   417,   420,   424,
     430,   436,   440,   444,   450,   455,   473,   478,   483,   488,
     493,   497,   503,   508,   513,   517,   521,   525,   529,   533,
     537,   541,   545,   549,   553,   557,   561,   567,   571,   575,
     581,   585,   589,   594,   598,   606,   609,   621,   625,   628,
     635,   638,   650,   654,   657,   658,   662,   668,   672,   678,
     682,   688,   689,   691,   692,   693,   696
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
  "BIT_AND", "REL", "SHIFT", "'+'", "'-'", "REMAINDER", "DIVIDE",
  "MULTIPLY", "'~'", "UMINUS", "ARRAY_LENGTH", "NOT", "DEC", "INC",
  "ARROW", "')'", "'('", "'['", "'{'", "'}'", "','", "':'", "']'",
  "$accept", "grammar", "opt_declarations_in_grammar",
  "declarations_in_grammar", "declaration_in_grammar", "use", "package",
  "opt_declarations_in_package", "declarations_in_package",
  "declaration_in_package", "package_block", "enumeration_block",
  "opt_enumeration_values", "enumeration_values", "enumeration_value",
  "opt_statements", "statements", "statement", "block", "normal_statement",
  "normal_statement_for_end", "for_statement", "while_statement",
  "switch_statement", "case_statement", "default_statement",
  "if_statement", "else_statement", "field", "sub", "enumeration",
  "my_var", "expression", "opt_terms", "terms", "array_length", "term",
  "new_object", "convert_type", "call_field", "unop", "binop",
  "array_elem", "call_sub", "opt_args", "args", "arg", "opt_descriptors",
  "descriptors", "type", "type_name", "type_array",
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
      79,    79,    79,    80,    80,    81,    82,    83,    84,    85,
      86,    87,    87,    87,    88,    89,    89,    90,    91,    91,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    93,
      93,    94,    94,    95,    95,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    97,    97,
      98,    99,    99,    99,   100,   100,   100,   100,   100,   100,
     100,   100,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   102,   102,   102,
     103,   103,   103,   103,   103,   104,   104,   105,   105,   106,
     107,   107,   108,   108,   109,   109,   110,   111,   111,   112,
     112,   113,   113,   114,   115,   116,   117
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     1,     3,
       3,     0,     1,     2,     1,     1,     1,     1,     3,     3,
       0,     1,     3,     1,     1,     3,     0,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     1,     1,     1,     8,     5,     5,     3,     2,
       6,     0,     2,     6,     5,     9,     9,     2,     4,     2,
       1,     1,     1,     2,     1,     2,     3,     3,     3,     0,
       1,     3,     1,     2,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       4,     5,     4,     4,     2,     2,     2,     2,     2,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     5,     4,     4,
       4,     6,     3,     6,     3,     0,     1,     3,     1,     3,
       0,     1,     3,     1,     1,     1,     1,     3,     3,     4,
       4,     1,     1,     1,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     0,     2,     4,     6,     7,     8,   145,
       0,     0,     1,     5,    11,    10,     9,     0,     0,     0,
       0,    12,    14,    15,    16,    17,   143,     0,   144,     0,
      20,    57,    18,    13,     0,   125,    24,     0,    21,    23,
     136,     0,   134,   135,     0,     0,   126,   128,     0,    19,
       0,    54,     0,     0,     0,     0,     0,    25,    22,   137,
     138,   129,   130,   127,   133,     0,   131,   142,   141,     0,
       0,    56,    26,    55,   132,     0,     0,    62,     0,     0,
       0,    60,    61,   144,    75,    77,    78,    64,     0,     0,
       0,     0,    76,    42,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    27,    29,    34,    30,    32,    33,    35,
      36,    37,    31,    87,     0,    86,     0,    85,    84,    80,
      81,    82,    83,    79,     0,     0,    38,    59,     0,    76,
      63,    80,    83,     0,     0,    88,     0,    89,     0,    65,
       0,     0,    49,   146,     0,    94,    95,   100,     0,    73,
     101,    98,    96,   136,     0,     0,    39,    28,     0,    41,
      40,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    99,    97,     0,     0,     0,     0,     0,
       0,     0,    69,     0,     0,     0,     0,     0,     0,     0,
     113,     0,    48,    68,     0,   114,     0,   112,   115,   116,
     107,   109,   108,   111,   110,   102,   103,   106,   105,   104,
       0,     0,   122,    66,     0,     0,    67,     0,     0,     0,
      70,    72,   124,    58,     0,     0,     0,     0,     0,     0,
      74,    90,     0,     0,    69,   119,    92,   118,    93,   120,
       0,    69,    51,     0,    46,   139,   140,    47,   117,    91,
       0,    71,     0,     0,     0,    50,     0,    44,    43,   121,
     123,     0,    52,     0,     0,    45,     0,    51,    53
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,     8,    20,    21,    22,
      15,    31,    37,    38,    39,   102,   103,   104,   105,   106,
     256,   107,   108,   109,   110,   111,   112,   255,    23,    24,
      25,   113,   114,   219,   220,   115,   116,   117,   118,   131,
     120,   121,   132,   123,    45,    46,    47,    65,    66,    41,
      42,    43,   137,    69,    27,   124,   125,   126
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -196
static const yytype_int16 yypact[] =
{
      39,    -6,    -6,    14,  -196,    39,  -196,  -196,  -196,  -196,
     -35,     3,  -196,  -196,    33,  -196,  -196,    47,    51,    17,
      22,    33,  -196,  -196,  -196,  -196,  -196,    21,  -196,    27,
      67,  -196,  -196,  -196,    68,    70,    54,    46,    50,  -196,
    -196,    58,    49,    56,    55,    52,    57,  -196,    93,  -196,
      67,  -196,    65,    72,    68,    75,    70,  -196,  -196,  -196,
    -196,  -196,    95,  -196,  -196,    -9,    77,  -196,  -196,   -24,
     105,  -196,   259,  -196,  -196,   109,    82,   428,    83,    84,
      68,  -196,  -196,    87,   116,  -196,  -196,   428,    96,   428,
      92,   101,   119,  -196,   428,   428,   428,   299,   428,   428,
     428,   468,   106,   259,  -196,  -196,  -196,  -196,  -196,  -196,
    -196,  -196,  -196,   127,   130,  -196,   674,  -196,  -196,   -22,
    -196,  -196,   -11,  -196,   111,   114,  -196,   113,   428,  -196,
     814,    -7,    -4,   347,   428,   120,   123,  -196,   428,   814,
     428,   624,  -196,  -196,   428,     5,     5,     5,   428,     5,
       5,     9,     9,   -36,   714,   115,  -196,  -196,   428,  -196,
    -196,   428,   428,   428,   428,   428,   428,   428,   428,   428,
     428,   428,   428,  -196,  -196,   -14,   428,   428,    47,   428,
     428,    47,   428,    51,    68,   734,   428,   754,   165,   208,
     814,   774,  -196,   814,   650,  -196,   428,   814,   832,   849,
     103,   103,   201,   292,    79,    32,    32,     5,     5,     5,
     428,    47,   125,   814,   489,   117,   814,   516,   124,   129,
     132,   814,   133,  -196,   101,   695,   101,   543,   570,   101,
    -196,  -196,   597,   131,   428,  -196,  -196,  -196,  -196,  -196,
     428,   428,    53,   388,  -196,  -196,  -196,  -196,  -196,  -196,
     139,   814,   140,   143,   101,  -196,   141,  -196,   814,  -196,
    -196,   428,  -196,   101,   794,  -196,   101,    53,  -196
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -196,  -196,  -196,  -196,   193,  -196,  -196,  -196,  -196,   178,
    -196,  -196,  -196,  -196,   150,  -196,  -196,    98,   -69,    71,
    -196,  -196,  -196,  -196,  -196,  -196,  -196,   -65,  -196,  -196,
    -196,  -196,   -40,  -195,  -196,  -196,   -71,  -196,  -196,   -68,
    -196,  -196,   -67,  -196,  -196,  -196,   151,  -196,  -196,   -52,
     128,   136,  -196,  -196,  -169,   -17,    69,  -196
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -146
static const yytype_int16 yytable[] =
{
      73,    29,    61,    28,   119,   122,   130,    71,    40,   215,
     176,     9,   218,    68,    12,  -145,   139,  -144,   141,    67,
      14,   179,   143,   145,   146,   147,   149,   150,   151,   152,
     154,    72,   177,   178,    16,   119,   122,    17,    18,   250,
     210,   211,   233,   180,   181,     1,   252,   177,   178,   155,
     180,   181,     2,    19,   173,   174,   175,   185,  -146,  -146,
     175,   253,   254,   187,    26,   119,   122,   190,    28,   191,
      10,    11,    30,   193,   170,   171,   172,   194,    32,    34,
      35,   173,   174,   175,    36,    40,    48,   197,    44,    51,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,    49,    52,    55,   213,   214,    50,   216,   217,
      53,   221,    57,    54,    56,   225,    64,   227,   228,   168,
     169,   170,   171,   172,    59,   231,    74,   127,   173,   174,
     175,    60,   223,    62,    70,   128,   133,   134,  -145,   232,
     165,   166,   167,   168,   169,   170,   171,   172,   138,   140,
     142,   144,   173,   174,   175,   242,    72,   244,   212,   158,
     247,   159,   156,   221,   182,   183,   222,   196,    75,   251,
     221,   184,   258,   236,   188,   119,   122,   189,   234,    80,
     238,   239,    83,    84,    85,   262,   241,   249,    86,   240,
     264,   259,   260,   263,   265,   129,   261,   267,    13,    33,
      58,   157,   268,   257,   186,    94,    95,    63,   135,     0,
      96,    75,    97,    98,    99,   100,   136,     0,   101,     0,
       0,     0,    80,     0,    59,    83,    84,    85,     0,     0,
       0,    86,     0,     0,     0,     0,     0,     0,   129,   166,
     167,   168,   169,   170,   171,   172,     0,     0,    94,    95,
     173,   174,   175,    96,     0,    97,    98,    99,   100,     0,
       0,   101,    75,     0,     0,     0,    76,    60,     0,    77,
      78,    79,     0,    80,    81,    82,    83,    84,    85,     0,
       0,     0,    86,    87,    88,    89,    90,     0,    91,    92,
      93,     0,     0,     0,     0,     0,     0,     0,     0,    94,
      95,     0,    75,     0,    96,     0,    97,    98,    99,   100,
       0,     0,   101,    80,    72,     0,    83,    84,    85,     0,
       0,     0,    86,     0,     0,     0,     0,     0,     0,   129,
    -146,   167,   168,   169,   170,   171,   172,     0,     0,    94,
      95,   173,   174,   175,    96,     0,    97,    98,    99,   100,
      75,     0,   101,     0,   148,     0,     0,    77,     0,     0,
       0,    80,    81,    82,    83,    84,    85,     0,     0,     0,
      86,    87,     0,     0,     0,     0,     0,    92,    93,     0,
       0,     0,     0,     0,     0,     0,     0,    94,    95,     0,
       0,    75,    96,     0,    97,    98,    99,   100,    77,     0,
     101,     0,    80,    81,    82,    83,    84,    85,     0,     0,
       0,    86,    87,     0,     0,     0,     0,     0,    92,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    94,    95,
       0,    75,     0,    96,     0,    97,    98,    99,   100,     0,
       0,   101,    80,     0,     0,    83,    84,    85,     0,     0,
       0,    86,     0,     0,     0,     0,     0,     0,   129,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    94,    95,
       0,    75,     0,    96,     0,    97,    98,    99,   100,     0,
       0,   101,    80,     0,     0,   153,    84,    85,     0,     0,
       0,    86,     0,     0,     0,     0,     0,     0,   129,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    94,    95,
       0,     0,     0,    96,     0,    97,    98,    99,   100,     0,
       0,   101,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,     0,     0,     0,     0,   173,   174,
     175,     0,     0,     0,     0,     0,     0,     0,   235,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,     0,     0,   173,   174,   175,     0,     0,
       0,     0,     0,     0,     0,   237,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,     0,     0,
       0,     0,   173,   174,   175,     0,     0,     0,     0,     0,
       0,     0,   245,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,     0,     0,     0,     0,   173,
     174,   175,     0,     0,     0,     0,     0,     0,     0,   246,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,     0,     0,     0,     0,   173,   174,   175,     0,
       0,     0,     0,     0,     0,     0,   248,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,     0,     0,   173,   174,   175,     0,     0,     0,     0,
       0,     0,   192,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,     0,     0,     0,     0,   173,
     174,   175,     0,     0,     0,   160,   230,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,     0,     0,   173,   174,   175,   243,     0,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
       0,     0,     0,     0,   173,   174,   175,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,     0,     0,   173,   174,   175,   195,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,     0,     0,   173,   174,   175,   224,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,     0,     0,   173,   174,   175,   226,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,     0,     0,   173,   174,   175,   229,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,     0,     0,   173,   174,   175,   266,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,     0,     0,   173,   174,   175,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,     0,     0,     0,
       0,   173,   174,   175,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,     0,     0,     0,     0,   173,   174,
     175
};

static const yytype_int16 yycheck[] =
{
      69,    18,    54,    17,    72,    72,    77,    31,    17,   178,
      32,    17,   181,    65,     0,    51,    87,    53,    89,    28,
      55,    32,    91,    94,    95,    96,    97,    98,    99,   100,
     101,    55,    54,    55,    31,   103,   103,     4,     5,   234,
      54,    55,   211,    54,    55,     6,   241,    54,    55,   101,
      54,    55,    13,    20,    49,    50,    51,   128,    49,    50,
      51,     8,     9,   134,    17,   133,   133,   138,    17,   140,
       1,     2,    55,   144,    42,    43,    44,   148,    56,    58,
      53,    49,    50,    51,    17,    17,    32,   158,    18,    31,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,    56,    54,    52,   176,   177,    57,   179,   180,
      54,   182,    19,    58,    57,   186,    21,   188,   189,    40,
      41,    42,    43,    44,    59,   196,    21,    18,    49,    50,
      51,    59,   184,    58,    57,    53,    53,    53,    51,   210,
      37,    38,    39,    40,    41,    42,    43,    44,    32,    53,
      58,    32,    49,    50,    51,   224,    55,   226,   175,    32,
     229,    31,    56,   234,    53,    51,   183,    52,     3,   240,
     241,    58,   243,    56,    54,   243,   243,    54,    53,    14,
      56,    52,    17,    18,    19,   254,    53,    56,    23,    57,
     261,    52,    52,    52,   263,    30,    53,   266,     5,    21,
      50,   103,   267,   243,   133,    40,    41,    56,    80,    -1,
      45,     3,    47,    48,    49,    50,    80,    -1,    53,    -1,
      -1,    -1,    14,    -1,    59,    17,    18,    19,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    40,    41,
      49,    50,    51,    45,    -1,    47,    48,    49,    50,    -1,
      -1,    53,     3,    -1,    -1,    -1,     7,    59,    -1,    10,
      11,    12,    -1,    14,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    23,    24,    25,    26,    27,    -1,    29,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      41,    -1,     3,    -1,    45,    -1,    47,    48,    49,    50,
      -1,    -1,    53,    14,    55,    -1,    17,    18,    19,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    40,
      41,    49,    50,    51,    45,    -1,    47,    48,    49,    50,
       3,    -1,    53,    -1,    55,    -1,    -1,    10,    -1,    -1,
      -1,    14,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    -1,
      -1,     3,    45,    -1,    47,    48,    49,    50,    10,    -1,
      53,    -1,    14,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,
      -1,     3,    -1,    45,    -1,    47,    48,    49,    50,    -1,
      -1,    53,    14,    -1,    -1,    17,    18,    19,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,
      -1,     3,    -1,    45,    -1,    47,    48,    49,    50,    -1,
      -1,    53,    14,    -1,    -1,    17,    18,    19,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,
      -1,    -1,    -1,    45,    -1,    47,    48,    49,    50,    -1,
      -1,    53,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,    50,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    49,    50,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    59,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,
      50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    49,    50,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    49,    50,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    58,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,
      50,    51,    -1,    -1,    -1,    31,    56,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    49,    50,    51,    31,    -1,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    49,    50,    51,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    49,    50,    51,    52,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    49,    50,    51,    52,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    49,    50,    51,    52,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    49,    50,    51,    52,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    49,    50,    51,    52,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    49,    50,    51,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    49,    50,    51,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,    50,
      51
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    13,    61,    62,    63,    64,    65,    66,    17,
     116,   116,     0,    64,    55,    70,    31,     4,     5,    20,
      67,    68,    69,    88,    89,    90,    17,   114,    17,   115,
      55,    71,    56,    69,    58,    53,    17,    72,    73,    74,
      17,   109,   110,   111,    18,   104,   105,   106,    32,    56,
      57,    31,    54,    54,    58,    52,    57,    19,    74,    59,
      59,   109,    58,   106,    21,   107,   108,    28,   109,   113,
      57,    31,    55,    78,    21,     3,     7,    10,    11,    12,
      14,    15,    16,    17,    18,    19,    23,    24,    25,    26,
      27,    29,    30,    31,    40,    41,    45,    47,    48,    49,
      50,    53,    75,    76,    77,    78,    79,    81,    82,    83,
      84,    85,    86,    91,    92,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   115,   116,   117,    18,    53,    30,
      96,    99,   102,    53,    53,   110,   111,   112,    32,    96,
      53,    96,    58,    78,    32,    96,    96,    96,    55,    96,
      96,    96,    96,    17,    96,   109,    56,    77,    32,    31,
      31,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    49,    50,    51,    32,    54,    55,    32,
      54,    55,    53,    51,    58,    96,    79,    96,    54,    54,
      96,    96,    58,    96,    96,    52,    52,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      54,    55,   115,    96,    96,   114,    96,    96,   114,    93,
      94,    96,   115,   109,    52,    96,    52,    96,    96,    52,
      56,    96,    96,   114,    53,    59,    56,    59,    56,    52,
      57,    53,    78,    31,    78,    59,    59,    78,    59,    56,
      93,    96,    93,     8,     9,    87,    80,    92,    96,    52,
      52,    53,    78,    52,    96,    78,    52,    78,    87
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
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 4:
#line 66 "yacc/spvm_yacc.y"
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
#line 79 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (2)].opval)->code == SPVM_OP_C_CODE_LIST) {
        op_list = (yyvsp[(1) - (2)].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->file);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (2)].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(2) - (2)].opval));
      
      (yyval.opval) = op_list;
    ;}
    break;

  case 9:
#line 100 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 10:
#line 106 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval), (yyvsp[(3) - (3)].opval));
      if (compiler->fatal_error) {
        YYABORT;
      }
    ;}
    break;

  case 11:
#line 115 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 12:
#line 119 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->code == SPVM_OP_C_CODE_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, (yyval.opval), (yyval.opval)->first, (yyvsp[(1) - (1)].opval));
      }
    ;}
    break;

  case 13:
#line 131 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_append_elem(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
    ;}
    break;

  case 18:
#line 143 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CLASS_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, (yyval.opval), NULL, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 19:
#line 150 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ENUM_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, (yyval.opval), NULL, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 20:
#line 157 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 21:
#line 161 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->code == SPVM_OP_C_CODE_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, (yyval.opval), (yyval.opval)->first, (yyvsp[(1) - (1)].opval));
      }
    ;}
    break;

  case 22:
#line 173 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_append_elem(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
    ;}
    break;

  case 24:
#line 180 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ENUMERATION_VALUE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      SPVM_OP_insert_child(compiler, (yyval.opval), NULL, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 25:
#line 185 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ENUMERATION_VALUE, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, (yyval.opval), NULL, (yyvsp[(1) - (3)].opval));
      SPVM_OP_insert_child(compiler, (yyval.opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 26:
#line 193 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 27:
#line 197 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->code == SPVM_OP_C_CODE_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, (yyval.opval), (yyval.opval)->first, (yyvsp[(1) - (1)].opval));
      }
    ;}
    break;

  case 28:
#line 209 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_append_elem(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
    ;}
    break;

  case 39:
#line 227 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, (yyval.opval), NULL, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 40:
#line 234 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POP, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      SPVM_OP_insert_child(compiler, (yyval.opval), NULL, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 42:
#line 240 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
    ;}
    break;

  case 43:
#line 246 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POP, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      SPVM_OP_insert_child(compiler, (yyval.opval), NULL, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 45:
#line 254 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[(1) - (8)].opval), (yyvsp[(3) - (8)].opval), (yyvsp[(4) - (8)].opval), (yyvsp[(6) - (8)].opval), (yyvsp[(8) - (8)].opval));
    ;}
    break;

  case 46:
#line 260 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 47:
#line 266 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 48:
#line 272 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 50:
#line 281 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, (yyvsp[(1) - (6)].opval)->file, (yyvsp[(1) - (6)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    ;}
    break;

  case 51:
#line 294 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 52:
#line 298 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (2)].opval);
    ;}
    break;

  case 53:
#line 302 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
    ;}
    break;

  case 54:
#line 308 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 55:
#line 314 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(1) - (9)].opval), (yyvsp[(2) - (9)].opval), (yyvsp[(4) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(8) - (9)].opval), (yyvsp[(9) - (9)].opval));
     ;}
    break;

  case 56:
#line 318 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(1) - (9)].opval), (yyvsp[(2) - (9)].opval), (yyvsp[(4) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(8) - (9)].opval), NULL);
     ;}
    break;

  case 57:
#line 323 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 58:
#line 329 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my_var(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 59:
#line 333 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my_var(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 62:
#line 340 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 63:
#line 344 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 64:
#line 348 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 65:
#line 352 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 66:
#line 356 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assignop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 67:
#line 360 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assignop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 68:
#line 364 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assignop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 69:
#line 370 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 70:
#line 374 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->code == SPVM_OP_C_CODE_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, (yyval.opval), (yyval.opval)->first, (yyvsp[(1) - (1)].opval));
      }
    ;}
    break;

  case 71:
#line 386 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_append_elem(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
    ;}
    break;

  case 73:
#line 393 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_length(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 74:
#line 397 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_length(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 77:
#line 405 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_constant(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 88:
#line 421 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_malloc_object(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 89:
#line 425 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_malloc_object(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 90:
#line 431 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_convert_type(compiler, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 91:
#line 437 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_field(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 92:
#line 441 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_field(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 93:
#line 445 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_field(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 94:
#line 451 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_PLUS, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 95:
#line 456 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(2) - (2)].opval)->code == SPVM_OP_C_CODE_CONSTANT) {
        SPVM_CONSTANT* constant = (yyvsp[(2) - (2)].opval)->uv.constant;
        if (constant->code == SPVM_CONSTANT_C_CODE_INT || constant->code == SPVM_CONSTANT_C_CODE_LONG) {
          constant->sign = 1;
          (yyval.opval) = (yyvsp[(2) - (2)].opval);
        }
        else {
          SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NEGATE, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
          (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
        }
      }
      else {
        SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NEGATE, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
        (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
      }
    ;}
    break;

  case 96:
#line 474 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_PRE_INC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 97:
#line 479 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POST_INC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 98:
#line 484 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_PRE_DEC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 99:
#line 489 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POST_DEC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 100:
#line 494 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unop(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 101:
#line 498 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unop(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 102:
#line 504 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ADD, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 103:
#line 509 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_SUBTRACT, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 104:
#line 514 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 105:
#line 518 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 106:
#line 522 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 107:
#line 526 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 108:
#line 530 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 109:
#line 534 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 110:
#line 538 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 111:
#line 542 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 112:
#line 546 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assignop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 113:
#line 550 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assignop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 114:
#line 554 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 115:
#line 558 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 116:
#line 562 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 117:
#line 568 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_elem(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 118:
#line 572 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_elem(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 119:
#line 576 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_elem(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 120:
#line 582 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, (yyvsp[(1) - (4)].opval)->file, (yyvsp[(1) - (4)].opval)->line), (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 121:
#line 586 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 122:
#line 590 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_terms);
    ;}
    break;

  case 123:
#line 595 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 124:
#line 599 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_terms);
    ;}
    break;

  case 125:
#line 606 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 126:
#line 610 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->code == SPVM_OP_C_CODE_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, (yyval.opval), (yyval.opval)->first, (yyvsp[(1) - (1)].opval));
      }
    ;}
    break;

  case 127:
#line 622 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_append_elem(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
    ;}
    break;

  case 129:
#line 629 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my_var(compiler, SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_MY, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 130:
#line 635 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 131:
#line 639 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->code == SPVM_OP_C_CODE_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, (yyval.opval), (yyval.opval)->first, (yyvsp[(1) - (1)].opval));
      }
    ;}
    break;

  case 132:
#line 651 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_append_elem(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
    ;}
    break;

  case 136:
#line 663 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_name(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 137:
#line 669 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_array(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 138:
#line 673 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_array(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 139:
#line 679 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_array(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 140:
#line 683 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_array(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 146:
#line 697 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2604 "spvm_yacc.tab.c"
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


#line 701 "yacc/spvm_yacc.y"



