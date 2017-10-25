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
     NEW = 269,
     SET = 270,
     GET = 271,
     OUR = 272,
     LAST = 273,
     NEXT = 274,
     NAME = 275,
     VAR = 276,
     CONSTANT = 277,
     ENUM = 278,
     DESCRIPTOR = 279,
     CORETYPE = 280,
     UNDEF = 281,
     CROAK = 282,
     PACKAGE_VAR = 283,
     SWITCH = 284,
     CASE = 285,
     DEFAULT = 286,
     VOID = 287,
     EVAL = 288,
     EXCEPTION_VAR = 289,
     BYTE = 290,
     SHORT = 291,
     INT = 292,
     LONG = 293,
     FLOAT = 294,
     DOUBLE = 295,
     STRING = 296,
     WEAKEN = 297,
     SPECIAL_ASSIGN = 298,
     ASSIGN = 299,
     OR = 300,
     AND = 301,
     BIT_XOR = 302,
     BIT_OR = 303,
     BIT_AND = 304,
     REL = 305,
     SHIFT = 306,
     REMAINDER = 307,
     DIVIDE = 308,
     MULTIPLY = 309,
     UMINUS = 310,
     ARRAY_LENGTH = 311,
     NOT = 312,
     DEC = 313,
     INC = 314,
     ARROW = 315
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
#define NEW 269
#define SET 270
#define GET 271
#define OUR 272
#define LAST 273
#define NEXT 274
#define NAME 275
#define VAR 276
#define CONSTANT 277
#define ENUM 278
#define DESCRIPTOR 279
#define CORETYPE 280
#define UNDEF 281
#define CROAK 282
#define PACKAGE_VAR 283
#define SWITCH 284
#define CASE 285
#define DEFAULT 286
#define VOID 287
#define EVAL 288
#define EXCEPTION_VAR 289
#define BYTE 290
#define SHORT 291
#define INT 292
#define LONG 293
#define FLOAT 294
#define DOUBLE 295
#define STRING 296
#define WEAKEN 297
#define SPECIAL_ASSIGN 298
#define ASSIGN 299
#define OR 300
#define AND 301
#define BIT_XOR 302
#define BIT_OR 303
#define BIT_AND 304
#define REL 305
#define SHIFT 306
#define REMAINDER 307
#define DIVIDE 308
#define MULTIPLY 309
#define UMINUS 310
#define ARRAY_LENGTH 311
#define NOT 312
#define DEC 313
#define INC 314
#define ARROW 315




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
#line 246 "spvm_yacc.tab.c"

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
#define YYLAST   966

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  175
/* YYNRULES -- Number of states.  */
#define YYNSTATES  309

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   315

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      67,    66,     2,    53,    71,    54,    55,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    72,    43,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    68,     2,    73,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    69,     2,    70,    59,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    56,    57,    58,
      60,    61,    62,    63,    64,    65
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    13,    15,    17,
      21,    25,    26,    28,    31,    33,    35,    37,    39,    42,
      45,    48,    52,    56,    57,    59,    63,    66,    68,    70,
      74,    75,    77,    80,    82,    84,    86,    88,    90,    92,
      94,    96,    98,   100,   104,   107,   110,   112,   114,   116,
     125,   131,   137,   141,   144,   151,   152,   155,   162,   169,
     179,   189,   192,   195,   198,   203,   206,   211,   213,   215,
     217,   220,   222,   225,   229,   233,   237,   239,   240,   242,
     246,   249,   251,   252,   254,   258,   261,   263,   266,   271,
     273,   275,   277,   279,   281,   283,   285,   287,   289,   291,
     293,   295,   297,   299,   302,   305,   310,   316,   321,   326,
     329,   332,   335,   338,   341,   344,   347,   350,   353,   357,
     361,   365,   369,   373,   377,   381,   385,   389,   393,   397,
     403,   407,   411,   415,   419,   423,   427,   431,   435,   439,
     445,   451,   456,   461,   466,   473,   477,   478,   480,   484,
     487,   489,   493,   494,   496,   500,   503,   505,   507,   509,
     511,   513,   515,   517,   519,   521,   523,   527,   531,   536,
     541,   543,   545,   547,   549,   551
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      75,     0,    -1,    76,    -1,    -1,    77,    -1,    77,    78,
      -1,    78,    -1,    79,    -1,    80,    -1,    13,   137,    43,
      -1,     6,   137,    84,    -1,    -1,    82,    -1,    82,    83,
      -1,    83,    -1,   102,    -1,   103,    -1,   106,    -1,   104,
      43,    -1,   105,    43,    -1,   108,    43,    -1,    69,    81,
      70,    -1,    69,    86,    70,    -1,    -1,    87,    -1,    87,
      71,    88,    -1,    87,    71,    -1,    88,    -1,    20,    -1,
      20,    45,    22,    -1,    -1,    90,    -1,    90,    91,    -1,
      91,    -1,    93,    -1,   100,    -1,    95,    -1,    96,    -1,
      92,    -1,    97,    -1,    98,    -1,    99,    -1,   138,    -1,
      69,    89,    70,    -1,   115,    43,    -1,   109,    43,    -1,
      43,    -1,   115,    -1,   109,    -1,    11,    67,    93,   115,
      43,    94,    66,    92,    -1,    12,    67,   115,    66,    92,
      -1,    29,    67,   115,    66,    92,    -1,    30,   115,    72,
      -1,    31,    72,    -1,     7,    67,   115,    66,    92,   101,
      -1,    -1,     9,    92,    -1,     8,    67,   115,    66,    92,
     101,    -1,     4,   135,    72,   128,   130,    43,    -1,     5,
     136,    67,   125,    66,    72,   128,   134,    92,    -1,     5,
     136,    67,   125,    66,    72,   128,   134,    43,    -1,    15,
     112,    -1,    16,   112,    -1,    23,    85,    -1,     3,    21,
      72,   130,    -1,     3,    21,    -1,    17,    21,    72,   130,
      -1,    18,    -1,    19,    -1,    10,    -1,    10,   115,    -1,
      27,    -1,    27,   115,    -1,   118,    45,   115,    -1,   123,
      45,   115,    -1,    34,    45,   115,    -1,   119,    -1,    -1,
     111,    -1,   111,    71,   115,    -1,   111,    71,    -1,   115,
      -1,    -1,   113,    -1,   113,    71,    20,    -1,   113,    71,
      -1,    20,    -1,    61,   115,    -1,    61,    69,   115,    70,
      -1,    21,    -1,    28,    -1,    34,    -1,    22,    -1,    26,
      -1,   124,    -1,   118,    -1,   120,    -1,   121,    -1,   123,
      -1,   117,    -1,   116,    -1,   114,    -1,   107,    -1,    14,
     131,    -1,    14,   133,    -1,    67,   130,    66,   115,    -1,
     115,    65,    69,   135,    70,    -1,   118,    69,   135,    70,
      -1,   123,    69,   135,    70,    -1,    42,   118,    -1,    53,
     115,    -1,    54,   115,    -1,    64,   115,    -1,   115,    64,
      -1,    63,   115,    -1,   115,    63,    -1,    59,   115,    -1,
      62,   115,    -1,   115,    53,   115,    -1,   115,    54,   115,
      -1,   115,    55,   115,    -1,   115,    58,   115,    -1,   115,
      57,   115,    -1,   115,    56,   115,    -1,   115,    48,   115,
      -1,   115,    50,   115,    -1,   115,    49,   115,    -1,   115,
      52,   115,    -1,   115,    51,   115,    -1,   107,    45,    68,
     110,    73,    -1,   107,    45,   122,    -1,   107,    45,   115,
      -1,    21,    45,   115,    -1,    21,    44,   115,    -1,    28,
      45,   115,    -1,    28,    44,   115,    -1,    67,   115,    66,
      -1,   115,    46,   115,    -1,   115,    47,   115,    -1,    14,
     132,    69,   110,    70,    -1,   115,    65,    68,   115,    73,
      -1,   123,    68,   115,    73,    -1,   118,    68,   115,    73,
      -1,   136,    67,   110,    66,    -1,   115,    65,   136,    67,
     110,    66,    -1,   115,    65,   136,    -1,    -1,   126,    -1,
     126,    71,   127,    -1,   126,    71,    -1,   127,    -1,    21,
      72,   130,    -1,    -1,   129,    -1,   129,    71,    24,    -1,
     129,    71,    -1,    24,    -1,   131,    -1,   132,    -1,    20,
      -1,    35,    -1,    36,    -1,    37,    -1,    38,    -1,    39,
      -1,    40,    -1,   131,    68,    73,    -1,   132,    68,    73,
      -1,   131,    68,   115,    73,    -1,   132,    68,   115,    73,
      -1,   130,    -1,    32,    -1,    20,    -1,    20,    -1,    20,
      -1,    33,    92,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    51,    51,    63,    66,    79,    93,    96,    97,   100,
     106,   116,   119,   131,   145,   148,   149,   150,   151,   152,
     153,   156,   164,   173,   176,   189,   203,   207,   210,   214,
     221,   224,   237,   251,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   265,   273,   279,   280,   286,   292,   295,
     301,   307,   313,   319,   322,   336,   339,   343,   349,   355,
     359,   365,   371,   377,   383,   387,   393,   399,   400,   401,
     404,   408,   412,   416,   420,   424,   428,   432,   435,   448,
     462,   466,   470,   473,   486,   500,   504,   507,   511,   517,
     518,   519,   520,   524,   525,   526,   527,   528,   529,   530,
     531,   532,   533,   536,   540,   546,   552,   556,   560,   566,
     572,   577,   582,   587,   592,   597,   602,   606,   612,   617,
     622,   626,   630,   634,   638,   642,   646,   650,   654,   658,
     662,   666,   670,   674,   678,   682,   686,   690,   694,   700,
     706,   710,   714,   720,   724,   728,   735,   738,   751,   765,
     769,   772,   779,   782,   795,   809,   813,   816,   817,   820,
     824,   828,   832,   836,   840,   844,   850,   854,   860,   864,
     870,   871,   876,   877,   878,   881
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MY", "HAS", "SUB", "PACKAGE", "IF",
  "ELSIF", "ELSE", "RETURN", "FOR", "WHILE", "USE", "NEW", "SET", "GET",
  "OUR", "LAST", "NEXT", "NAME", "VAR", "CONSTANT", "ENUM", "DESCRIPTOR",
  "CORETYPE", "UNDEF", "CROAK", "PACKAGE_VAR", "SWITCH", "CASE", "DEFAULT",
  "VOID", "EVAL", "EXCEPTION_VAR", "BYTE", "SHORT", "INT", "LONG", "FLOAT",
  "DOUBLE", "STRING", "WEAKEN", "';'", "SPECIAL_ASSIGN", "ASSIGN", "OR",
  "AND", "BIT_XOR", "BIT_OR", "BIT_AND", "REL", "SHIFT", "'+'", "'-'",
  "'.'", "REMAINDER", "DIVIDE", "MULTIPLY", "'~'", "UMINUS",
  "ARRAY_LENGTH", "NOT", "DEC", "INC", "ARROW", "')'", "'('", "'['", "'{'",
  "'}'", "','", "':'", "']'", "$accept", "grammar",
  "opt_declarations_in_grammar", "declarations_in_grammar",
  "declaration_in_grammar", "use", "package",
  "opt_declarations_in_package", "declarations_in_package",
  "declaration_in_package", "package_block", "enumeration_block",
  "opt_enumeration_values", "enumeration_values", "enumeration_value",
  "opt_statements", "statements", "statement", "block", "normal_statement",
  "normal_statement_for_end", "for_statement", "while_statement",
  "switch_statement", "case_statement", "default_statement",
  "if_statement", "else_statement", "field", "sub", "setters", "getters",
  "enumeration", "my_var", "our_var", "expression", "opt_terms", "terms",
  "opt_names", "names", "array_length", "term", "new_object",
  "convert_type", "call_field", "weaken_field", "unop", "binop",
  "array_init", "array_elem", "call_sub", "opt_args", "args", "arg",
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,    59,   298,   299,   300,   301,   302,   303,
     304,   305,   306,    43,    45,    46,   307,   308,   309,   126,
     310,   311,   312,   313,   314,   315,    41,    40,    91,   123,
     125,    44,    58,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    76,    76,    77,    77,    78,    78,    79,
      80,    81,    81,    82,    82,    83,    83,    83,    83,    83,
      83,    84,    85,    86,    86,    87,    87,    87,    88,    88,
      89,    89,    90,    90,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    92,    93,    93,    93,    94,    94,    95,
      96,    97,    98,    99,   100,   101,   101,   101,   102,   103,
     103,   104,   105,   106,   107,   107,   108,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   110,   110,   111,
     111,   111,   112,   112,   113,   113,   113,   114,   114,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   116,   116,   117,   118,   118,   118,   119,
     120,   120,   120,   120,   120,   120,   120,   120,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   122,
     123,   123,   123,   124,   124,   124,   125,   125,   126,   126,
     126,   127,   128,   128,   129,   129,   129,   130,   130,   131,
     131,   131,   131,   131,   131,   131,   132,   132,   133,   133,
     134,   134,   135,   136,   137,   138
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     1,     3,
       3,     0,     1,     2,     1,     1,     1,     1,     2,     2,
       2,     3,     3,     0,     1,     3,     2,     1,     1,     3,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     2,     2,     1,     1,     1,     8,
       5,     5,     3,     2,     6,     0,     2,     6,     6,     9,
       9,     2,     2,     2,     4,     2,     4,     1,     1,     1,
       2,     1,     2,     3,     3,     3,     1,     0,     1,     3,
       2,     1,     0,     1,     3,     2,     1,     2,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     4,     5,     4,     4,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     5,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     5,
       5,     4,     4,     4,     6,     3,     0,     1,     3,     2,
       1,     3,     0,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     4,     4,
       1,     1,     1,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     0,     2,     4,     6,     7,     8,   174,
       0,     0,     1,     5,    11,    10,     9,     0,     0,    82,
      82,     0,     0,     0,    12,    14,    15,    16,     0,     0,
      17,     0,   172,     0,   173,     0,    86,    61,    83,    62,
       0,    23,    63,    21,    13,    18,    19,    20,   152,   146,
      85,     0,    28,     0,    24,    27,   156,     0,   153,     0,
       0,   147,   150,    84,   159,   160,   161,   162,   163,   164,
     165,    66,   157,   158,     0,    22,    26,     0,   155,     0,
       0,   149,     0,     0,    29,    25,    58,   154,   151,   152,
     148,   166,   167,     0,   171,   170,     0,    60,    30,    59,
       0,     0,    69,     0,     0,     0,    67,    68,    89,    92,
      93,    71,    90,     0,     0,     0,     0,    91,     0,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    31,
      33,    38,    34,    36,    37,    39,    40,    41,    35,   102,
       0,   101,     0,   100,    99,    95,    76,    96,    97,    98,
      94,     0,    42,    65,     0,    91,    70,    95,    98,     0,
       0,   103,     0,   104,     0,     0,    72,     0,     0,     0,
       0,    53,   175,     0,     0,    95,   110,   111,   116,     0,
      87,   117,   114,   112,   159,     0,     0,    43,    32,     0,
      45,    44,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   115,   113,     0,     0,     0,
       0,     0,     0,     0,    77,     0,     0,     0,     0,     0,
       0,   133,   132,   135,   134,     0,    52,    75,     0,   136,
       0,     0,    77,   131,   130,   137,   138,   124,   126,   125,
     128,   127,   118,   119,   120,   123,   122,   121,     0,     0,
     145,    73,     0,     0,    74,     0,     0,     0,    78,    81,
      64,     0,     0,     0,     0,     0,     0,    88,   105,     0,
       0,     0,     0,    77,   142,   107,   141,   108,   143,    80,
      55,     0,    50,   168,   169,    51,    77,   129,   140,   106,
       0,    79,     0,     0,    54,     0,    48,    47,     0,   144,
       0,    56,     0,   139,     0,    49,     0,    55,    57
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,     8,    23,    24,    25,
      15,    42,    53,    54,    55,   128,   129,   130,   131,   132,
     295,   133,   134,   135,   136,   137,   138,   294,    26,    27,
      28,    29,    30,   139,    31,   140,   257,   258,    37,    38,
     141,   259,   143,   144,   157,   146,   147,   148,   234,   158,
     150,    60,    61,    62,    57,    58,    71,    72,    73,   163,
      96,    33,   151,    10,   152
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -226
static const yytype_int16 yypact[] =
{
       6,    -2,    -2,    36,  -226,     6,  -226,  -226,  -226,  -226,
     -31,     0,  -226,  -226,   140,  -226,  -226,    20,    40,    49,
      49,    35,     4,    43,   140,  -226,  -226,  -226,    32,    73,
    -226,    74,  -226,    46,  -226,    54,  -226,  -226,    53,  -226,
      55,   105,  -226,  -226,  -226,  -226,  -226,  -226,   102,   107,
     121,   268,    97,    79,    72,  -226,  -226,   268,    82,    78,
      92,    88,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,
    -226,  -226,    93,    94,   142,  -226,   105,   123,   144,   268,
     100,   107,    96,    98,  -226,  -226,  -226,  -226,  -226,   102,
    -226,  -226,  -226,    99,  -226,  -226,   -34,  -226,   256,  -226,
     153,   108,   543,   109,   110,   268,  -226,  -226,     5,  -226,
    -226,   543,     8,   111,   543,   120,   112,   138,   543,  -226,
     543,   543,   543,   308,   543,   543,   543,   381,   125,   256,
    -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,   155,
     158,  -226,   701,  -226,  -226,   -23,  -226,  -226,  -226,   -14,
    -226,   131,  -226,   130,   543,  -226,   849,    -3,     9,   436,
     543,   136,   139,  -226,   543,   543,   849,   543,   543,   543,
     649,  -226,  -226,   543,   849,   -27,    26,    26,    26,   543,
      26,    26,    45,    45,   141,   744,   143,  -226,  -226,   329,
    -226,  -226,   543,   543,   543,   543,   543,   543,   543,   543,
     543,   543,   543,   543,   543,  -226,  -226,   -10,   543,   543,
      20,   543,   543,    20,   543,   268,   765,   543,   786,   126,
     191,   849,   849,   849,   849,   807,  -226,   849,   676,  -226,
     543,   268,   543,   849,  -226,   868,   886,   373,   373,   484,
     901,   418,    23,    23,    23,    26,    26,    26,   543,    20,
     147,   849,   183,   145,   849,   535,   146,   152,   149,   849,
    -226,   112,   724,   112,   565,   593,   112,  -226,  -226,    15,
     148,   621,   154,   543,  -226,  -226,  -226,  -226,  -226,   543,
      85,   491,  -226,  -226,  -226,  -226,   543,  -226,  -226,  -226,
     156,   849,   159,   112,  -226,   157,  -226,   849,   172,  -226,
     543,  -226,   112,  -226,   828,  -226,   112,    85,  -226
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -226,  -226,  -226,  -226,   222,  -226,  -226,  -226,  -226,   204,
    -226,  -226,  -226,  -226,   167,  -226,  -226,   122,   -96,    90,
    -226,  -226,  -226,  -226,  -226,  -226,  -226,   -50,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,   -21,  -225,  -226,   241,  -226,
    -226,   -97,  -226,  -226,   -85,  -226,  -226,  -226,  -226,   -95,
    -226,  -226,  -226,   181,   176,  -226,   -42,  -101,   -99,  -226,
    -226,  -202,   -16,   267,  -226
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -174
static const yytype_int16 yytable[] =
{
      99,   142,    35,   149,   161,   156,   162,   270,   253,    97,
      34,   256,     1,   145,   166,    77,  -109,   170,     9,     2,
     172,   174,   208,   176,   177,   178,   180,   181,   182,   183,
     185,   211,   142,   175,   149,    98,    12,    88,    14,  -109,
      32,   209,   210,    16,   145,   209,   210,   272,   290,   164,
     165,    95,   167,   168,   212,   213,    40,   216,   248,   249,
      34,   298,   142,   218,   149,   209,   210,   221,   222,    36,
     223,   224,   225,    41,   145,    45,   227,   212,   213,   202,
     203,   204,   228,   220,   286,   186,   205,   206,   207,   205,
     206,   207,   233,   292,   293,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,  -174,  -174,
     207,   251,   252,    43,   254,   255,    46,    47,    48,    64,
     262,    49,   264,   265,    50,    52,    56,    51,    59,   100,
     161,    94,   269,   268,    65,    66,    67,    68,    69,    70,
     105,    63,    74,    76,    17,    18,    34,   108,   109,    75,
      79,   271,   110,    78,   112,    19,    20,    21,    80,    81,
     155,    82,    83,    22,    84,   280,    86,   282,    87,    91,
     285,    92,    89,   260,   153,   154,   159,   160,   169,   120,
     121,    98,   291,   173,   297,   122,   149,   123,   124,   125,
     126,   250,   171,   127,   100,   187,   145,   301,   214,    91,
     189,   190,   215,   304,   219,   105,   305,   220,  -173,   230,
     307,    34,   108,   109,   273,   275,   277,   110,   278,   112,
     279,   287,   299,   302,   289,   155,   300,    13,    44,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   303,    85,   120,   121,   205,   206,   207,   217,
     122,   188,   123,   124,   125,   126,   274,   308,   127,   100,
     296,    39,    90,   101,    92,    93,   102,   103,   104,    11,
     105,     0,     0,     0,   106,   107,    34,   108,   109,     0,
       0,     0,   110,   111,   112,   113,   114,   115,    64,   116,
     117,     0,     0,     0,     0,     0,     0,     0,   118,   119,
       0,     0,     0,    65,    66,    67,    68,    69,    70,   120,
     121,   100,     0,     0,     0,   122,     0,   123,   124,   125,
     126,     0,   105,   127,     0,    98,     0,     0,    34,   108,
     109,     0,   100,     0,   110,     0,   112,     0,     0,     0,
       0,     0,   155,   231,     0,     0,     0,     0,     0,    34,
     108,   109,     0,     0,     0,   110,     0,   112,     0,     0,
       0,   120,   121,   155,     0,     0,     0,   122,     0,   123,
     124,   125,   126,     0,     0,   127,     0,   179,     0,     0,
       0,     0,   120,   121,   100,     0,     0,     0,   122,     0,
     123,   124,   125,   126,     0,   105,   127,   232,     0,     0,
       0,   184,   108,   109,     0,     0,     0,   110,     0,   112,
       0,     0,     0,     0,     0,   155,    65,    66,    67,    68,
      69,    70,     0,   196,   197,   198,   199,   200,   201,   202,
     203,   204,     0,     0,   120,   121,   205,   206,   207,   100,
     122,     0,   123,   124,   125,   126,   102,     0,   127,     0,
     105,     0,     0,     0,   106,   107,    34,   108,   109,     0,
       0,     0,   110,   111,   112,     0,     0,     0,     0,     0,
     117,   199,   200,   201,   202,   203,   204,     0,   118,   119,
       0,   205,   206,   207,     0,     0,     0,     0,     0,   120,
     121,     0,     0,     0,   100,   122,     0,   123,   124,   125,
     126,   102,     0,   127,     0,   105,     0,     0,     0,   106,
     107,    34,   108,   109,     0,     0,     0,   110,   111,   112,
       0,     0,     0,     0,     0,   117,     0,     0,     0,     0,
       0,     0,     0,   118,     0,   197,   198,   199,   200,   201,
     202,   203,   204,     0,   120,   121,   100,   205,   206,   207,
     122,     0,   123,   124,   125,   126,     0,   105,   127,     0,
       0,     0,     0,    34,   108,   109,     0,     0,     0,   110,
       0,   112,     0,     0,     0,     0,     0,   155,     0,     0,
       0,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,     0,     0,   120,   121,   205,   206,
     207,     0,   122,     0,   123,   124,   125,   126,   276,     0,
     127,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,     0,     0,     0,     0,   205,   206,
     207,     0,     0,     0,     0,     0,     0,     0,   283,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,     0,     0,     0,     0,   205,   206,   207,     0,
       0,     0,     0,     0,     0,     0,   284,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
       0,     0,     0,     0,   205,   206,   207,     0,     0,     0,
       0,     0,     0,     0,   288,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,     0,     0,
       0,     0,   205,   206,   207,     0,     0,     0,     0,     0,
       0,   226,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,     0,     0,     0,     0,   205,
     206,   207,     0,     0,   191,     0,   267,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
       0,     0,     0,     0,   205,   206,   207,   281,     0,     0,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,     0,     0,     0,     0,   205,   206,   207,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,     0,     0,     0,     0,   205,   206,   207,
     229,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,     0,     0,     0,     0,   205,   206,
     207,   261,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,     0,     0,     0,     0,   205,
     206,   207,   263,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,     0,     0,     0,     0,
     205,   206,   207,   266,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,     0,     0,     0,
       0,   205,   206,   207,   306,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,     0,     0,
       0,     0,   205,   206,   207,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,     0,     0,     0,
       0,   205,   206,   207,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,     0,     0,     0,     0,   205,
     206,   207,  -174,   198,   199,   200,   201,   202,   203,   204,
       0,     0,     0,     0,   205,   206,   207
};

static const yytype_int16 yycheck[] =
{
      96,    98,    18,    98,   105,   102,   105,   232,   210,    43,
      20,   213,     6,    98,   111,    57,    43,   114,    20,    13,
     116,   118,    45,   120,   121,   122,   123,   124,   125,   126,
     127,    45,   129,   118,   129,    69,     0,    79,    69,    66,
      20,    68,    69,    43,   129,    68,    69,   249,   273,    44,
      45,    93,    44,    45,    68,    69,    21,   154,    68,    69,
      20,   286,   159,   160,   159,    68,    69,   164,   165,    20,
     167,   168,   169,    69,   159,    43,   173,    68,    69,    56,
      57,    58,   179,    68,    69,   127,    63,    64,    65,    63,
      64,    65,   189,     8,     9,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,    63,    64,
      65,   208,   209,    70,   211,   212,    43,    43,    72,    20,
     217,    67,   219,   220,    71,    20,    24,    72,    21,     3,
     231,    32,   231,   230,    35,    36,    37,    38,    39,    40,
      14,    20,    45,    71,     4,     5,    20,    21,    22,    70,
      72,   248,    26,    71,    28,    15,    16,    17,    66,    71,
      34,    68,    68,    23,    22,   261,    43,   263,    24,    73,
     266,    73,    72,   215,    21,    67,    67,    67,    67,    53,
      54,    69,   279,    45,   281,    59,   281,    61,    62,    63,
      64,   207,    72,    67,     3,    70,   281,   293,    67,    73,
      45,    43,    72,   300,    68,    14,   302,    68,    67,    66,
     306,    20,    21,    22,    67,    70,    70,    26,    66,    28,
      71,    73,    66,    66,    70,    34,    67,     5,    24,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    70,    76,    53,    54,    63,    64,    65,   159,
      59,   129,    61,    62,    63,    64,    73,   307,    67,     3,
     281,    20,    81,     7,    73,    89,    10,    11,    12,     2,
      14,    -1,    -1,    -1,    18,    19,    20,    21,    22,    -1,
      -1,    -1,    26,    27,    28,    29,    30,    31,    20,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,
      -1,    -1,    -1,    35,    36,    37,    38,    39,    40,    53,
      54,     3,    -1,    -1,    -1,    59,    -1,    61,    62,    63,
      64,    -1,    14,    67,    -1,    69,    -1,    -1,    20,    21,
      22,    -1,     3,    -1,    26,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    34,    14,    -1,    -1,    -1,    -1,    -1,    20,
      21,    22,    -1,    -1,    -1,    26,    -1,    28,    -1,    -1,
      -1,    53,    54,    34,    -1,    -1,    -1,    59,    -1,    61,
      62,    63,    64,    -1,    -1,    67,    -1,    69,    -1,    -1,
      -1,    -1,    53,    54,     3,    -1,    -1,    -1,    59,    -1,
      61,    62,    63,    64,    -1,    14,    67,    68,    -1,    -1,
      -1,    20,    21,    22,    -1,    -1,    -1,    26,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,
      39,    40,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    -1,    53,    54,    63,    64,    65,     3,
      59,    -1,    61,    62,    63,    64,    10,    -1,    67,    -1,
      14,    -1,    -1,    -1,    18,    19,    20,    21,    22,    -1,
      -1,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      34,    53,    54,    55,    56,    57,    58,    -1,    42,    43,
      -1,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,    53,
      54,    -1,    -1,    -1,     3,    59,    -1,    61,    62,    63,
      64,    10,    -1,    67,    -1,    14,    -1,    -1,    -1,    18,
      19,    20,    21,    22,    -1,    -1,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    42,    -1,    51,    52,    53,    54,    55,
      56,    57,    58,    -1,    53,    54,     3,    63,    64,    65,
      59,    -1,    61,    62,    63,    64,    -1,    14,    67,    -1,
      -1,    -1,    -1,    20,    21,    22,    -1,    -1,    -1,    26,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,
      -1,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    -1,    -1,    53,    54,    63,    64,
      65,    -1,    59,    -1,    61,    62,    63,    64,    73,    -1,
      67,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    63,    64,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    63,    64,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    63,    64,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,    63,
      64,    65,    -1,    -1,    43,    -1,    70,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    63,    64,    65,    43,    -1,    -1,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,    63,    64,    65,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,    63,    64,    65,
      66,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    63,    64,    65,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    63,    64,    65,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,    63,
      64,    65,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    63,    64,    65
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    13,    75,    76,    77,    78,    79,    80,    20,
     137,   137,     0,    78,    69,    84,    43,     4,     5,    15,
      16,    17,    23,    81,    82,    83,   102,   103,   104,   105,
     106,   108,    20,   135,    20,   136,    20,   112,   113,   112,
      21,    69,    85,    70,    83,    43,    43,    43,    72,    67,
      71,    72,    20,    86,    87,    88,    24,   128,   129,    21,
     125,   126,   127,    20,    20,    35,    36,    37,    38,    39,
      40,   130,   131,   132,    45,    70,    71,   130,    71,    72,
      66,    71,    68,    68,    22,    88,    43,    24,   130,    72,
     127,    73,    73,   128,    32,   130,   134,    43,    69,    92,
       3,     7,    10,    11,    12,    14,    18,    19,    21,    22,
      26,    27,    28,    29,    30,    31,    33,    34,    42,    43,
      53,    54,    59,    61,    62,    63,    64,    67,    89,    90,
      91,    92,    93,    95,    96,    97,    98,    99,   100,   107,
     109,   114,   115,   116,   117,   118,   119,   120,   121,   123,
     124,   136,   138,    21,    67,    34,   115,   118,   123,    67,
      67,   131,   132,   133,    44,    45,   115,    44,    45,    67,
     115,    72,    92,    45,   115,   118,   115,   115,   115,    69,
     115,   115,   115,   115,    20,   115,   130,    70,    91,    45,
      43,    43,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    63,    64,    65,    45,    68,
      69,    45,    68,    69,    67,    72,   115,    93,   115,    68,
      68,   115,   115,   115,   115,   115,    72,   115,   115,    66,
      66,    14,    68,   115,   122,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,    68,    69,
     136,   115,   115,   135,   115,   115,   135,   110,   111,   115,
     130,    66,   115,    66,   115,   115,    66,    70,   115,   132,
     110,   115,   135,    67,    73,    70,    73,    70,    66,    71,
      92,    43,    92,    73,    73,    92,    69,    73,    73,    70,
     110,   115,     8,     9,   101,    94,   109,   115,   110,    66,
      67,    92,    66,    70,   115,    92,    66,    92,   101
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
#line 63 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 4:
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
#line 101 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 10:
#line 107 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval), (yyvsp[(3) - (3)].opval));
      if (compiler->fatal_error) {
        YYABORT;
      }
    ;}
    break;

  case 11:
#line 116 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 12:
#line 120 "yacc/spvm_yacc.y"
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

  case 13:
#line 132 "yacc/spvm_yacc.y"
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

  case 21:
#line 157 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CLASS_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_class_block;
    ;}
    break;

  case 22:
#line 165 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ENUM_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_enum_block;
    ;}
    break;

  case 23:
#line 173 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 24:
#line 177 "yacc/spvm_yacc.y"
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

  case 25:
#line 190 "yacc/spvm_yacc.y"
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

  case 26:
#line 204 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 28:
#line 211 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 29:
#line 215 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 30:
#line 221 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 31:
#line 225 "yacc/spvm_yacc.y"
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
#line 238 "yacc/spvm_yacc.y"
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
#line 266 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_code_block = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_code_block, op_code_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_code_block;
    ;}
    break;

  case 44:
#line 274 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_pop = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POP, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      SPVM_OP_insert_child(compiler, op_pop, op_pop->last, (yyvsp[(1) - (2)].opval));
      (yyval.opval) = op_pop;
    ;}
    break;

  case 46:
#line 281 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
    ;}
    break;

  case 47:
#line 287 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_pop = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POP, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      SPVM_OP_insert_child(compiler, op_pop, op_pop->last, (yyvsp[(1) - (1)].opval));
      (yyval.opval) = op_pop;
    ;}
    break;

  case 49:
#line 296 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[(1) - (8)].opval), (yyvsp[(3) - (8)].opval), (yyvsp[(4) - (8)].opval), (yyvsp[(6) - (8)].opval), (yyvsp[(8) - (8)].opval));
    ;}
    break;

  case 50:
#line 302 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 51:
#line 308 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 52:
#line 314 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 54:
#line 323 "yacc/spvm_yacc.y"
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
#line 336 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 56:
#line 340 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (2)].opval);
    ;}
    break;

  case 57:
#line 344 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
    ;}
    break;

  case 58:
#line 350 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(2) - (6)].opval), (yyvsp[(4) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 59:
#line 356 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(1) - (9)].opval), (yyvsp[(2) - (9)].opval), (yyvsp[(4) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(8) - (9)].opval), (yyvsp[(9) - (9)].opval));
     ;}
    break;

  case 60:
#line 360 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(1) - (9)].opval), (yyvsp[(2) - (9)].opval), (yyvsp[(4) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(8) - (9)].opval), NULL);
     ;}
    break;

  case 61:
#line 366 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_setters(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 62:
#line 372 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_getters(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 63:
#line 378 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 64:
#line 384 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my_var(compiler, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 65:
#line 388 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my_var(compiler, (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 66:
#line 394 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_our(compiler, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 69:
#line 401 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 70:
#line 405 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 71:
#line 409 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 72:
#line 413 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 73:
#line 417 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 74:
#line 421 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 75:
#line 425 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 77:
#line 432 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 78:
#line 436 "yacc/spvm_yacc.y"
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

  case 79:
#line 449 "yacc/spvm_yacc.y"
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

  case 80:
#line 463 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval)
    ;}
    break;

  case 82:
#line 470 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 83:
#line 474 "yacc/spvm_yacc.y"
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

  case 84:
#line 487 "yacc/spvm_yacc.y"
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

  case 85:
#line 501 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval)
    ;}
    break;

  case 87:
#line 508 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_length(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 88:
#line 512 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_length(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 92:
#line 521 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_constant(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 103:
#line 537 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new_object(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 104:
#line 541 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new_object(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 105:
#line 547 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_convert_type(compiler, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 106:
#line 553 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_field(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 107:
#line 557 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_field(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 108:
#line 561 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_field(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 109:
#line 567 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 110:
#line 573 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_PLUS, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 111:
#line 578 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NEGATE, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op_negate, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 112:
#line 583 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_PRE_INC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 113:
#line 588 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POST_INC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 114:
#line 593 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_PRE_DEC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 115:
#line 598 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POST_DEC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 116:
#line 603 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unop(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 117:
#line 607 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_not(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 118:
#line 613 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ADD, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 119:
#line 618 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_SUBTRACT, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 120:
#line 623 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_concat_string(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 121:
#line 627 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 122:
#line 631 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 123:
#line 635 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 124:
#line 639 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 125:
#line 643 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 126:
#line 647 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 127:
#line 651 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 128:
#line 655 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 129:
#line 659 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (5)].opval), (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 130:
#line 663 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 131:
#line 667 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 132:
#line 671 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 133:
#line 675 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 134:
#line 679 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 135:
#line 683 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 136:
#line 687 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 137:
#line 691 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_or(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 138:
#line 695 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_and(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 139:
#line 701 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_init2(compiler, (yyvsp[(2) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 140:
#line 707 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_elem(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 141:
#line 711 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_elem(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 142:
#line 715 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_elem(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 143:
#line 721 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, (yyvsp[(1) - (4)].opval)->file, (yyvsp[(1) - (4)].opval)->line), (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 144:
#line 725 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 145:
#line 729 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_terms);
    ;}
    break;

  case 146:
#line 735 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 147:
#line 739 "yacc/spvm_yacc.y"
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

  case 148:
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

  case 149:
#line 766 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 151:
#line 773 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my_var(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 152:
#line 779 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 153:
#line 783 "yacc/spvm_yacc.y"
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

  case 154:
#line 796 "yacc/spvm_yacc.y"
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

  case 155:
#line 810 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 159:
#line 821 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_name(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 160:
#line 825 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_byte(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 161:
#line 829 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_short(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 162:
#line 833 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_int(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 163:
#line 837 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_long(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 164:
#line 841 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_float(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 165:
#line 845 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_double(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 166:
#line 851 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_array(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 167:
#line 855 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_array(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 168:
#line 861 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_array(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 169:
#line 865 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_type_array(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 171:
#line 872 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_void(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 175:
#line 882 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2922 "spvm_yacc.tab.c"
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


#line 886 "yacc/spvm_yacc.y"


