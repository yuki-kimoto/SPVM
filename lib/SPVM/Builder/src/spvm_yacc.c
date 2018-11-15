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
     CONST = 267,
     IF = 268,
     UNLESS = 269,
     ELSIF = 270,
     ELSE = 271,
     FOR = 272,
     WHILE = 273,
     LAST = 274,
     NEXT = 275,
     SWITCH = 276,
     CASE = 277,
     DEFAULT = 278,
     EVAL = 279,
     NAME = 280,
     VAR_NAME = 281,
     CONSTANT = 282,
     PACKAGE_VAR_NAME = 283,
     MAYBE_SUB_NAME = 284,
     RETURN = 285,
     WEAKEN = 286,
     CROAK = 287,
     NEW = 288,
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
     AMPERSAND = 299,
     DOT3 = 300,
     SPECIAL_ASSIGN = 301,
     ASSIGN = 302,
     OR = 303,
     AND = 304,
     BIT_XOR = 305,
     BIT_OR = 306,
     BIT_AND = 307,
     REL = 308,
     SHIFT = 309,
     REMAINDER = 310,
     DIVIDE = 311,
     MULTIPLY = 312,
     ISA = 313,
     DEREF = 314,
     REF = 315,
     UMINUS = 316,
     SCALAR = 317,
     NOT = 318,
     DEC = 319,
     INC = 320,
     ARROW = 321
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
#define CONST 267
#define IF 268
#define UNLESS 269
#define ELSIF 270
#define ELSE 271
#define FOR 272
#define WHILE 273
#define LAST 274
#define NEXT 275
#define SWITCH 276
#define CASE 277
#define DEFAULT 278
#define EVAL 279
#define NAME 280
#define VAR_NAME 281
#define CONSTANT 282
#define PACKAGE_VAR_NAME 283
#define MAYBE_SUB_NAME 284
#define RETURN 285
#define WEAKEN 286
#define CROAK 287
#define NEW 288
#define UNDEF 289
#define VOID 290
#define BYTE 291
#define SHORT 292
#define INT 293
#define LONG 294
#define FLOAT 295
#define DOUBLE 296
#define STRING 297
#define OBJECT 298
#define AMPERSAND 299
#define DOT3 300
#define SPECIAL_ASSIGN 301
#define ASSIGN 302
#define OR 303
#define AND 304
#define BIT_XOR 305
#define BIT_OR 306
#define BIT_AND 307
#define REL 308
#define SHIFT 309
#define REMAINDER 310
#define DIVIDE 311
#define MULTIPLY 312
#define ISA 313
#define DEREF 314
#define REF 315
#define UMINUS 316
#define SCALAR 317
#define NOT 318
#define DEC 319
#define INC 320
#define ARROW 321




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
#line 261 "spvm_yacc.tab.c"

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
#define YYLAST   1644

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  193
/* YYNRULES -- Number of states.  */
#define YYNSTATES  366

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   321

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      73,    71,     2,    55,    79,    56,    57,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    76,    78,
       2,     2,     2,     2,    63,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    74,     2,    80,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    75,     2,    77,    62,     2,     2,     2,
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
      58,    59,    60,    61,    64,    65,    66,    67,    68,    69,
      70,    72
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    13,    17,    23,
      27,    28,    30,    33,    35,    37,    39,    41,    44,    46,
      50,    53,    57,    58,    60,    64,    67,    69,    71,    75,
      81,    88,    99,   110,   120,   133,   134,   136,   138,   142,
     146,   148,   152,   153,   155,   159,   160,   162,   165,   167,
     168,   170,   173,   175,   177,   179,   181,   183,   185,   187,
     189,   191,   193,   196,   199,   201,   211,   217,   223,   227,
     230,   237,   244,   245,   248,   255,   259,   262,   264,   266,
     268,   271,   273,   276,   278,   280,   281,   283,   285,   287,
     289,   291,   295,   297,   299,   301,   303,   305,   307,   309,
     311,   313,   315,   317,   319,   321,   323,   325,   327,   329,
     331,   335,   338,   340,   343,   346,   349,   352,   355,   358,
     361,   365,   369,   373,   377,   381,   385,   389,   393,   397,
     401,   405,   409,   413,   416,   419,   425,   427,   431,   436,
     442,   447,   452,   457,   464,   468,   475,   479,   485,   491,
     496,   501,   504,   507,   510,   515,   519,   525,   528,   531,
     536,   540,   544,   548,   552,   555,   560,   563,   565,   567,
     569,   571,   573,   575,   577,   579,   581,   583,   585,   587,
     589,   591,   593,   596,   600,   604,   607,   612,   617,   619,
     621,   623,   625,   627
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      82,     0,    -1,    83,    -1,    -1,    84,    -1,    84,    85,
      -1,    85,    -1,     3,   147,    86,    -1,     3,   147,    76,
     105,    86,    -1,    75,    87,    77,    -1,    -1,    88,    -1,
      88,    89,    -1,    89,    -1,    97,    -1,    98,    -1,    91,
      -1,    96,    78,    -1,    90,    -1,    10,   147,    78,    -1,
       7,    92,    -1,    75,    93,    77,    -1,    -1,    94,    -1,
      94,    79,    95,    -1,    94,    79,    -1,    95,    -1,    25,
      -1,    25,    47,    27,    -1,     6,    28,    76,   105,   146,
      -1,     4,   153,    76,   105,   146,    78,    -1,   105,     5,
     154,    76,   152,    73,   100,   103,    71,   118,    -1,   105,
       5,   154,    76,   152,    73,   100,   103,    71,    78,    -1,
     105,     5,    76,   152,    73,   100,   103,    71,   118,    -1,
      74,   101,    80,   105,     5,    76,   152,    73,   100,   103,
      71,   118,    -1,    -1,   101,    -1,   104,    -1,   104,    79,
     101,    -1,   101,    79,   102,    -1,   102,    -1,   144,    76,
     146,    -1,    -1,    45,    -1,   144,    76,     9,    -1,    -1,
     106,    -1,   106,    11,    -1,    11,    -1,    -1,   108,    -1,
     108,   109,    -1,   109,    -1,   110,    -1,   116,    -1,   111,
      -1,   112,    -1,   118,    -1,   113,    -1,   114,    -1,   115,
      -1,   119,    -1,   123,    78,    -1,   120,    78,    -1,    78,
      -1,    17,    73,   122,    78,   122,    78,   122,    71,   118,
      -1,    18,    73,   122,    71,   118,    -1,    21,    73,   123,
      71,   118,    -1,    22,   123,    76,    -1,    23,    76,    -1,
      13,    73,   122,    71,   118,   117,    -1,    14,    73,   122,
      71,   118,   117,    -1,    -1,    16,   118,    -1,    15,    73,
     122,    71,   118,   117,    -1,    75,   107,    77,    -1,    24,
     118,    -1,    19,    -1,    20,    -1,    30,    -1,    30,   123,
      -1,    32,    -1,    32,   123,    -1,   135,    -1,   136,    -1,
      -1,   124,    -1,   123,    -1,   140,    -1,   142,    -1,   141,
      -1,    73,   122,    71,    -1,   144,    -1,   145,    -1,    27,
      -1,    34,    -1,   133,    -1,   134,    -1,   132,    -1,   131,
      -1,   129,    -1,   130,    -1,   137,    -1,   143,    -1,   127,
      -1,   125,    -1,   139,    -1,   138,    -1,   128,    -1,   126,
      -1,   124,    79,   123,    -1,   124,    79,    -1,   123,    -1,
      55,   123,    -1,    56,   123,    -1,    62,   123,    -1,    70,
     123,    -1,   123,    70,    -1,    69,   123,    -1,   123,    69,
      -1,   123,    55,   123,    -1,   123,    56,   123,    -1,   123,
      57,   123,    -1,   123,    60,   123,    -1,   123,    59,   123,
      -1,   123,    58,   123,    -1,   123,    50,   123,    -1,   123,
      44,   123,    -1,   123,    51,   123,    -1,   123,    54,   123,
      -1,    73,   123,    71,    -1,   123,    47,   123,    -1,   123,
      46,   123,    -1,    33,   147,    -1,    33,   151,    -1,    33,
     149,    75,   121,    77,    -1,    99,    -1,    74,   121,    80,
      -1,    73,   146,    71,   123,    -1,   123,    72,    74,   123,
      80,    -1,   132,    74,   123,    80,    -1,   134,    74,   123,
      80,    -1,   154,    73,   121,    71,    -1,   147,    72,   154,
      73,   121,    71,    -1,   147,    72,   154,    -1,   123,    72,
     154,    73,   121,    71,    -1,   123,    72,   154,    -1,   123,
      72,    73,   121,    71,    -1,   123,    72,    75,   153,    77,
      -1,   134,    75,   153,    77,    -1,   132,    75,   153,    77,
      -1,    31,   134,    -1,    31,   132,    -1,    63,   123,    -1,
      63,    75,   123,    77,    -1,    67,    63,   123,    -1,    67,
      63,    75,   123,    77,    -1,    64,   144,    -1,    65,   144,
      -1,    65,    75,   144,    77,    -1,   123,    53,   123,    -1,
     122,    61,   146,    -1,   122,    48,   122,    -1,   122,    49,
     122,    -1,    68,   122,    -1,     8,   144,    76,   146,    -1,
       8,   144,    -1,    26,    -1,    28,    -1,   147,    -1,   149,
      -1,   150,    -1,   148,    -1,    25,    -1,    36,    -1,    37,
      -1,    38,    -1,    39,    -1,    40,    -1,    41,    -1,    43,
      -1,    42,    -1,   147,    44,    -1,   147,    74,    80,    -1,
     149,    74,    80,    -1,    12,   149,    -1,   147,    74,   123,
      80,    -1,   149,    74,   123,    80,    -1,   146,    -1,    35,
      -1,    25,    -1,    29,    -1,    25,    -1,    29,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    68,    68,    76,    79,    92,   106,   109,   113,   119,
     128,   131,   143,   157,   160,   161,   162,   163,   164,   167,
     173,   179,   188,   191,   204,   218,   222,   225,   229,   235,
     241,   247,   251,   257,   261,   277,   280,   291,   299,   318,
     332,   335,   342,   345,   348,   359,   362,   375,   389,   393,
     396,   409,   423,   426,   427,   428,   429,   430,   431,   432,
     433,   434,   437,   441,   445,   451,   457,   463,   469,   475,
     478,   489,   503,   506,   510,   516,   524,   530,   531,   532,
     535,   539,   543,   547,   548,   552,   555,   568,   569,   570,
     571,   572,   578,   579,   580,   584,   585,   586,   587,   588,
     589,   590,   591,   592,   593,   594,   595,   596,   597,   598,
     601,   615,   619,   625,   630,   635,   641,   646,   651,   656,
     663,   668,   673,   677,   681,   685,   689,   693,   697,   701,
     705,   711,   715,   721,   725,   729,   733,   756,   763,   770,
     774,   778,   784,   788,   792,   797,   801,   806,   813,   817,
     821,   827,   833,   839,   844,   849,   854,   861,   867,   872,
     879,   885,   891,   895,   899,   905,   909,   915,   921,   927,
     928,   929,   930,   933,   937,   943,   949,   955,   961,   967,
     973,   979,   987,   993,   997,  1003,  1009,  1013,  1019,  1020,
    1026,  1027,  1030,  1031
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PACKAGE", "HAS", "SUB", "OUR", "ENUM",
  "MY", "SELF", "USE", "DESCRIPTOR", "CONST", "IF", "UNLESS", "ELSIF",
  "ELSE", "FOR", "WHILE", "LAST", "NEXT", "SWITCH", "CASE", "DEFAULT",
  "EVAL", "NAME", "VAR_NAME", "CONSTANT", "PACKAGE_VAR_NAME",
  "MAYBE_SUB_NAME", "RETURN", "WEAKEN", "CROAK", "NEW", "UNDEF", "VOID",
  "BYTE", "SHORT", "INT", "LONG", "FLOAT", "DOUBLE", "STRING", "OBJECT",
  "AMPERSAND", "DOT3", "SPECIAL_ASSIGN", "ASSIGN", "OR", "AND", "BIT_XOR",
  "BIT_OR", "BIT_AND", "REL", "SHIFT", "'+'", "'-'", "'.'", "REMAINDER",
  "DIVIDE", "MULTIPLY", "ISA", "'~'", "'@'", "DEREF", "REF", "UMINUS",
  "SCALAR", "NOT", "DEC", "INC", "')'", "ARROW", "'('", "'['", "'{'",
  "':'", "'}'", "';'", "','", "']'", "$accept", "grammar", "opt_packages",
  "packages", "package", "package_block", "opt_declarations",
  "declarations", "declaration", "use", "enumeration", "enumeration_block",
  "opt_enumeration_values", "enumeration_values", "enumeration_value",
  "our", "has", "sub", "anon_sub", "opt_args", "args", "arg", "opt_vaarg",
  "invocant", "opt_descriptors", "descriptors", "opt_statements",
  "statements", "statement", "normal_statement", "for_statement",
  "while_statement", "switch_statement", "case_statement",
  "default_statement", "if_statement", "else_statement", "block",
  "eval_block", "expression", "opt_normal_terms", "term", "normal_term",
  "normal_terms", "unop", "incdec", "binop", "assign", "new", "array_init",
  "convert_type", "array_access", "call_sub", "field_access",
  "weaken_field", "weaken_array_element", "array_length", "deref", "ref",
  "relative_term", "isa", "logical_term", "my_var", "var",
  "package_var_access", "type", "basic_type", "ref_type", "array_type",
  "const_array_type", "array_type_with_length", "type_or_void",
  "field_name", "sub_name", 0
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
     305,   306,   307,   308,   309,    43,    45,    46,   310,   311,
     312,   313,   126,    64,   314,   315,   316,   317,   318,   319,
     320,    41,   321,    40,    91,   123,    58,   125,    59,    44,
      93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    83,    83,    84,    84,    85,    85,    86,
      87,    87,    88,    88,    89,    89,    89,    89,    89,    90,
      91,    92,    93,    93,    94,    94,    94,    95,    95,    96,
      97,    98,    98,    99,    99,   100,   100,   100,   100,   101,
     101,   102,   103,   103,   104,   105,   105,   106,   106,   107,
     107,   108,   108,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   110,   110,   110,   111,   112,   113,   114,   115,
     116,   116,   117,   117,   117,   118,   119,   120,   120,   120,
     120,   120,   120,   120,   120,   121,   121,   122,   122,   122,
     122,   122,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     124,   124,   124,   125,   125,   125,   126,   126,   126,   126,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   128,   128,   129,   129,   129,   129,   130,   131,   132,
     132,   132,   133,   133,   133,   133,   133,   133,   134,   134,
     134,   135,   136,   137,   137,   137,   137,   138,   139,   139,
     140,   141,   142,   142,   142,   143,   143,   144,   145,   146,
     146,   146,   146,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   148,   149,   149,   150,   151,   151,   152,   152,
     153,   153,   154,   154
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     3,     5,     3,
       0,     1,     2,     1,     1,     1,     1,     2,     1,     3,
       2,     3,     0,     1,     3,     2,     1,     1,     3,     5,
       6,    10,    10,     9,    12,     0,     1,     1,     3,     3,
       1,     3,     0,     1,     3,     0,     1,     2,     1,     0,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     1,     9,     5,     5,     3,     2,
       6,     6,     0,     2,     6,     3,     2,     1,     1,     1,
       2,     1,     2,     1,     1,     0,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     1,     2,     2,     2,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     5,     1,     3,     4,     5,
       4,     4,     4,     6,     3,     6,     3,     5,     5,     4,
       4,     2,     2,     2,     4,     3,     5,     2,     2,     4,
       3,     3,     3,     3,     2,     4,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     3,     2,     4,     4,     1,     1,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     2,     4,     6,   173,   174,   175,   176,
     177,   178,   179,   181,   180,     0,     1,     5,    10,    45,
       7,     0,     0,     0,     0,    48,     0,    11,    13,    18,
      16,     0,    14,    15,     0,    46,     0,   190,   191,     0,
       0,    22,    20,     0,     9,    12,    17,     0,    47,     8,
      45,    45,    27,     0,    23,    26,    19,   192,   193,     0,
       0,     0,     0,    21,    25,     0,     0,     0,   169,   172,
     170,   171,    29,    28,    24,   189,   188,     0,     0,   185,
      30,   182,     0,     0,    35,   183,   184,   167,    42,    36,
      40,    37,     0,    43,     0,     0,     0,     0,     0,    39,
       0,    38,    44,    41,    45,    32,    31,     0,     0,     0,
       0,     0,     0,    77,    78,     0,    45,     0,     0,   173,
      94,   168,    45,    45,    45,     0,    95,    45,    45,    45,
      45,     0,     0,     0,    45,    45,    45,    45,    64,   136,
       0,     0,    45,    52,    53,    55,    56,    58,    59,    60,
      54,    57,    61,     0,     0,   105,   109,   104,   108,   100,
     101,    99,    98,    96,    97,    83,    84,   102,   107,   106,
     103,    92,    93,     0,     0,   166,    45,    45,    45,    45,
      45,     0,    69,    76,    80,     0,    98,    97,    82,   133,
       0,   134,   113,   114,   115,    45,   153,   157,     0,   158,
      45,   118,   116,     0,     0,   169,     0,     0,   112,    86,
      92,     0,    75,    51,    63,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,   119,   117,     0,
      62,    45,     0,    45,     0,     0,    45,     0,    45,    45,
       0,    87,    88,    90,    89,     0,     0,     0,     0,    68,
      45,    45,    45,     0,     0,    45,   155,   130,    45,    45,
     137,   111,     0,   127,   132,   131,   126,   128,   129,   120,
     121,   122,   125,   124,   123,    45,    45,     0,   146,     0,
       0,     0,     0,   144,     0,   165,   164,     0,    87,    45,
      45,     0,     0,    45,     0,    45,     0,     0,     0,     0,
       0,   154,   159,     0,   138,     0,   110,     0,     0,     0,
       0,    45,   140,   150,   141,   149,    45,   142,    91,   162,
     163,   161,    72,   160,    72,     0,    66,    67,   186,   187,
     135,   156,     0,    35,   147,   139,   148,     0,     0,     0,
       0,    70,    71,    45,     0,    42,   145,   143,    45,    73,
       0,     0,     0,     0,     0,    35,     0,     0,    65,    42,
      33,    72,     0,    74,     0,    34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    20,    26,    27,    28,    29,
      30,    42,    53,    54,    55,    31,    32,    33,   139,    88,
      89,    90,    94,    91,   140,    35,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   341,   151,   152,   153,
     207,   240,   241,   209,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   242,
     243,   244,   170,   171,   172,    76,   173,    69,    70,    71,
     191,    77,    39,   174
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -319
static const yytype_int16 yypact[] =
{
      28,   293,    56,  -319,    28,  -319,  -319,  -319,  -319,  -319,
    -319,  -319,  -319,  -319,  -319,    38,  -319,  -319,   347,    26,
    -319,    37,    42,     3,   293,  -319,    18,   347,  -319,  -319,
    -319,    10,  -319,  -319,    99,    96,    25,  -319,  -319,    34,
      36,   113,  -319,    65,  -319,  -319,  -319,    50,  -319,  -319,
      26,    26,   104,    79,    87,  -319,  -319,  -319,  -319,   106,
     255,   255,   153,  -319,   113,   216,   293,   109,    -2,  -319,
     118,  -319,  -319,  -319,  -319,  -319,  -319,   122,   125,   118,
    -319,  -319,   117,   121,   178,  -319,  -319,  -319,   176,   127,
    -319,   148,   163,  -319,   158,   178,   178,    80,   -46,  -319,
     164,   127,  -319,  -319,   498,  -319,  -319,   255,   178,   162,
     169,   171,   172,  -319,  -319,   174,  1197,   173,   189,   175,
    -319,  -319,   626,  1197,   686,   293,  -319,  1197,  1197,  1197,
     863,   178,   -12,   205,  1197,  1197,  1047,   334,  -319,  -319,
     266,   196,   566,  -319,  -319,  -319,  -319,  -319,  -319,  -319,
    -319,  -319,  -319,   197,  1336,  -319,  -319,  -319,  -319,  -319,
    -319,  -319,    51,  -319,    57,  -319,  -319,  -319,  -319,  -319,
    -319,  -319,  -319,   202,   203,   201,  1097,  1097,  1097,  1097,
    1197,  1423,  -319,  -319,  1564,  1564,    16,    83,  1564,   207,
      94,  -319,    29,    29,    29,  1197,    29,  -319,   178,  -319,
     923,    39,    39,  1479,   208,    -5,   135,   206,  1564,   204,
     164,   209,  -319,  -319,  -319,  1197,  1197,  1197,  1197,  1197,
    1197,  1197,  1197,  1197,  1197,  1197,  1197,  -319,  -319,    11,
    -319,  1197,    37,  1197,    37,    50,  1147,   255,  1097,   983,
      32,  1508,  -319,  -319,  -319,    81,   -28,   123,  1535,  -319,
     384,   434,   746,  1365,   210,  1197,    29,  -319,  1197,    26,
    -319,   813,   216,   119,  1564,  1564,   119,   119,  1572,    95,
      95,    95,    29,    29,    29,  1147,  1197,    37,   226,    90,
     223,  1228,   224,   229,   211,  -319,  -319,   159,  1450,  1097,
    1097,   255,   189,  1197,   189,  1097,   189,   189,  1255,  1282,
     239,  -319,  -319,  1394,   -25,   298,  1564,   244,   248,  1309,
     246,  1147,  -319,  -319,  -319,  -319,  1147,  -319,  -319,    -3,
     260,  -319,   218,  1564,   218,    -4,  -319,  -319,  -319,  -319,
    -319,  -319,   250,   178,  -319,  -319,  -319,   253,   256,   264,
     189,  -319,  -319,  1097,   216,   176,  -319,  -319,  1097,  -319,
     161,   265,   275,   217,   189,   178,   189,   189,  -319,   176,
    -319,   218,   277,  -319,   189,  -319
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -319,  -319,  -319,  -319,   345,   319,  -319,  -319,   329,  -319,
    -319,  -319,  -319,  -319,   302,  -319,  -319,  -319,  -319,  -303,
     -86,   274,  -318,  -319,   -16,  -319,  -319,  -319,   236,  -319,
    -319,  -319,  -319,  -319,  -319,  -319,  -306,   -94,  -319,  -319,
    -214,  -162,    89,  -319,  -319,  -319,  -319,  -319,  -319,  -319,
    -319,   257,  -319,   258,  -319,  -319,  -319,  -319,  -319,  -319,
    -319,  -319,  -319,   -83,  -319,   -54,    -1,  -319,   -57,  -319,
    -319,  -257,  -206,   -39
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -193
static const yytype_int16 yytable[] =
{
      15,    92,    34,    36,   106,   307,    67,    72,    59,    79,
     101,    34,   100,   100,    87,   245,   246,   247,   342,   215,
     289,   290,   284,    43,   183,   175,   280,   352,   282,   104,
     345,     1,   105,   291,    60,    61,    57,    25,   300,    81,
      58,   362,    81,   103,   289,   290,   290,   229,   197,   199,
     295,   206,   359,   103,   210,   363,    16,   291,   291,    68,
      68,   308,    37,   198,    68,    78,    38,   235,   190,    82,
      40,   310,    82,   215,   343,    57,   286,   287,    41,    58,
     289,   290,   204,   215,   275,   276,   277,   351,    46,   102,
     231,   232,    66,   291,  -152,    44,    68,   337,   227,   228,
      18,   229,   338,   292,    47,     6,    68,    48,  -193,  -193,
      50,   229,    51,    18,    19,   254,     7,     8,     9,    10,
      11,    12,    13,    14,   189,   231,   232,   319,   320,   289,
     290,   233,   234,   325,   215,   205,   216,   217,    52,   215,
     218,   219,   291,    56,   220,   221,   222,   223,   224,   225,
     226,    62,   294,   224,   225,   226,    63,   233,   234,   227,
     228,  -151,   229,   215,   227,   228,    64,   229,   251,   252,
     312,   289,   290,   220,   221,   222,   223,   224,   225,   226,
      73,   350,    65,   285,   291,   204,   353,    80,   227,   228,
     278,   229,    83,   154,   296,    84,   283,    85,   322,    82,
     324,    86,   326,   327,    87,   181,    95,   289,   290,   289,
     290,   184,   185,   188,    95,   259,   192,   193,   194,   196,
     291,    93,   291,   201,   202,   203,   208,    96,    66,    98,
     318,   154,   354,   339,   340,   176,    68,   321,   205,    97,
     107,     6,   177,   305,   178,   179,   349,   180,  -192,   182,
      92,    75,     7,     8,     9,    10,    11,    12,    13,    14,
     358,    68,   360,   361,   104,   289,   290,    66,   200,   248,
     365,   211,    92,   212,   235,   214,   236,   237,   291,   258,
       6,   250,   317,   261,   253,   262,   260,   302,   357,   256,
      68,     7,     8,     9,    10,    11,    12,    13,    14,   311,
     313,   315,   316,   332,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   330,   333,     6,   334,
     279,   291,   281,   336,   346,   208,   344,   347,   288,     7,
       8,     9,    10,    11,    12,    13,    14,   348,   355,   298,
     299,   208,   108,    68,   303,    25,   356,   304,   364,    17,
     306,    21,   -45,    22,    23,    49,    45,    24,    25,   119,
      87,   120,   121,    58,   208,   309,    74,   125,   126,    99,
       7,     8,     9,    10,    11,    12,    13,    14,   213,     0,
     186,   187,   323,     0,     0,     0,     0,     0,     0,   127,
     128,     0,   108,     0,     0,    25,   129,   130,   131,   132,
     208,   133,     0,   134,   135,   208,     0,   136,   137,   119,
      87,   120,   121,    58,   -85,     0,     0,   125,   126,     0,
       7,     8,     9,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   127,
     128,     0,   108,     0,     0,    25,   129,   130,   131,   132,
       0,   133,     0,   134,   135,     0,     0,   136,   137,   119,
      87,   120,   121,    58,    85,     0,     0,   125,   126,     0,
       7,     8,     9,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   127,
     128,     0,     0,     0,     0,     0,   129,   130,   131,   132,
       0,   133,     0,   134,   135,     0,   108,   136,   137,    25,
       0,   109,   110,     0,    86,   111,   112,   113,   114,   115,
     116,   117,   118,   119,    87,   120,   121,    58,   122,   123,
     124,   125,   126,     0,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   127,   128,     0,     0,     0,     0,     0,
     129,   130,   131,   132,     0,   133,     0,   134,   135,     0,
       0,   136,   137,   104,   108,   -49,   138,    25,     0,   109,
     110,     0,     0,   111,   112,   113,   114,   115,   116,   117,
     118,   119,    87,   120,   121,    58,   122,   123,   124,   125,
     126,     0,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   127,   128,     0,     0,     0,     0,     0,   129,   130,
     131,   132,     0,   133,   108,   134,   135,    25,     0,   136,
     137,   104,     0,   -50,   138,     0,     0,     0,     0,     0,
       0,   119,    87,   120,   121,    58,     0,     0,     0,   125,
     126,     0,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   127,   128,     0,     0,     0,     0,     0,   129,   130,
     131,   132,     0,   133,   108,   134,   135,    25,     0,   136,
     137,     0,     0,     0,   -79,     0,     0,     0,     0,     0,
       0,   119,    87,   120,   121,    58,     0,     0,     0,   125,
     126,     0,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   127,   128,     0,     0,     0,     0,     0,   129,   130,
     131,   132,     0,   133,   108,   134,   135,    25,     0,   136,
     137,     0,     0,     0,   -81,     0,     0,     0,     0,     0,
       0,   119,    87,   120,   121,    58,     0,     0,     0,   125,
     126,     0,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   127,   128,     0,     0,     0,     0,     0,   129,   130,
     131,   132,     0,   133,     0,   134,   135,     0,   -45,   136,
     137,   108,     0,   -85,    25,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   119,    87,
     120,   121,    58,     0,     0,     0,   125,   126,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   127,   128,
       0,   108,     0,     0,    25,   129,   130,   131,   132,     0,
     133,     0,   134,   135,     0,     0,   136,   137,   119,    87,
     120,   121,    58,     0,     0,     0,   125,   126,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   127,   128,
       0,     0,     0,     0,     0,   129,   130,   131,   132,     0,
     133,   108,   134,   135,    25,     0,   136,   137,   195,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   119,    87,
     120,   121,    58,     0,     0,     0,   125,   126,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   127,   128,
       0,     0,     0,     0,     0,   129,   130,   131,   132,     0,
     133,   108,   134,   135,    25,    66,   136,   137,   255,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   119,    87,
     120,   121,    58,     0,     0,     0,   125,   126,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   127,   128,
       0,     0,     0,     0,     0,   129,   130,   131,   132,     0,
     133,   238,   134,   135,     0,   108,   239,   137,    25,    66,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   119,    87,   120,   121,    58,     0,     0,     0,
     125,   126,     0,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   127,   128,     0,   108,     0,     0,    25,   129,
     130,   131,   132,     0,   133,     0,   134,   135,     0,     0,
     136,   137,   119,    87,   120,   121,    58,     0,     0,     0,
     125,   126,     0,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   127,   128,     0,   108,     0,     0,    25,   129,
     130,   131,   132,     0,   133,   238,   134,   135,     0,     0,
     239,   137,   119,    87,   120,   121,    58,     0,     0,     0,
     125,   126,     0,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   127,   128,     0,   108,     0,     0,    25,   129,
     130,   131,   132,     0,   133,     0,   134,   135,   -85,     0,
     136,   137,   119,    87,   120,   121,    58,     0,     0,     0,
     125,   126,     0,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   127,   128,     0,     0,     0,     0,     0,   129,
     130,   131,   132,     0,   133,     0,   134,   135,     0,     0,
     136,   137,   215,     0,   216,   217,     0,     0,   218,   219,
       0,     0,   220,   221,   222,   223,   224,   225,   226,     0,
       0,     0,     0,     0,     0,     0,     0,   227,   228,   215,
     229,   216,   217,     0,     0,   218,   219,     0,   314,   220,
     221,   222,   223,   224,   225,   226,     0,     0,     0,     0,
       0,     0,     0,     0,   227,   228,   215,   229,   216,   217,
       0,     0,   218,   219,     0,   328,   220,   221,   222,   223,
     224,   225,   226,     0,     0,     0,     0,     0,     0,     0,
       0,   227,   228,   215,   229,   216,   217,     0,     0,   218,
     219,     0,   329,   220,   221,   222,   223,   224,   225,   226,
       0,     0,     0,     0,     0,     0,     0,     0,   227,   228,
     215,   229,   216,   217,     0,     0,   218,   219,     0,   335,
     220,   221,   222,   223,   224,   225,   226,     0,     0,     0,
       0,     0,     0,     0,     0,   227,   228,     0,   229,   215,
       0,   216,   217,     0,   230,   218,   219,     0,     0,   220,
     221,   222,   223,   224,   225,   226,     0,     0,     0,     0,
       0,     0,     0,     0,   227,   228,     0,   229,   215,     0,
     216,   217,   301,     0,   218,   219,     0,     0,   220,   221,
     222,   223,   224,   225,   226,     0,     0,     0,     0,     0,
       0,     0,     0,   227,   228,     0,   229,   215,     0,   216,
     217,   331,     0,   218,   219,     0,     0,   220,   221,   222,
     223,   224,   225,   226,     0,     0,     0,     0,     0,     0,
       0,     0,   227,   228,   215,   229,   216,   217,     0,   249,
     218,   219,     0,   293,   220,   221,   222,   223,   224,   225,
     226,     0,     0,     0,     0,     0,     0,     0,     0,   227,
     228,   257,   229,   215,     0,   216,   217,     0,     0,   218,
     219,     0,     0,   220,   221,   222,   223,   224,   225,   226,
       0,     0,     0,     0,     0,     0,     0,     0,   227,   228,
     257,   229,   215,     0,   216,   217,     0,     0,   218,   219,
       0,   293,   220,   221,   222,   223,   224,   225,   226,     0,
       0,     0,     0,     0,     0,     0,     0,   227,   228,   215,
     229,   216,   217,     0,     0,   218,   219,     0,     0,   220,
     221,   222,   223,   224,   225,   226,     0,     0,     0,     0,
       0,     0,     0,     0,   227,   228,   297,   229,   215,     0,
     216,   217,     0,     0,   218,   219,   215,     0,   220,   221,
     222,   223,   224,   225,   226,     0,     0,   221,   222,   223,
     224,   225,   226,   227,   228,     0,   229,     0,     0,     0,
       0,   227,   228,     0,   229
};

static const yytype_int16 yycheck[] =
{
       1,    84,    18,    19,    98,   262,    60,    61,    47,    66,
      96,    27,    95,    96,    26,   177,   178,   179,   324,    44,
      48,    49,   236,    24,   118,   108,   232,   345,   234,    75,
     333,     3,    78,    61,    50,    51,    25,    11,   252,    44,
      29,   359,    44,    97,    48,    49,    49,    72,   131,   132,
      78,   137,   355,   107,   137,   361,     0,    61,    61,    60,
      61,   275,    25,    75,    65,    66,    29,    72,   125,    74,
      28,   277,    74,    44,    78,    25,   238,   239,    75,    29,
      48,    49,   136,    44,    73,    74,    75,   344,    78,     9,
      74,    75,    12,    61,    78,    77,    97,   311,    69,    70,
      75,    72,   316,    71,     5,    25,   107,    11,    69,    70,
      76,    72,    76,    75,    76,   198,    36,    37,    38,    39,
      40,    41,    42,    43,   125,    74,    75,   289,   290,    48,
      49,    74,    75,   295,    44,   136,    46,    47,    25,    44,
      50,    51,    61,    78,    54,    55,    56,    57,    58,    59,
      60,    47,    71,    58,    59,    60,    77,    74,    75,    69,
      70,    78,    72,    44,    69,    70,    79,    72,    74,    75,
      80,    48,    49,    54,    55,    56,    57,    58,    59,    60,
      27,   343,    76,   237,    61,   239,   348,    78,    69,    70,
     229,    72,    74,   104,    71,    73,   235,    80,   292,    74,
     294,    80,   296,   297,    26,   116,    79,    48,    49,    48,
      49,   122,   123,   124,    79,    80,   127,   128,   129,   130,
      61,    45,    61,   134,   135,   136,   137,    79,    12,    71,
      71,   142,    71,    15,    16,    73,   237,   291,   239,    76,
      76,    25,    73,   259,    73,    73,   340,    73,    73,    76,
     333,    35,    36,    37,    38,    39,    40,    41,    42,    43,
     354,   262,   356,   357,    75,    48,    49,    12,    63,   180,
     364,     5,   355,    77,    72,    78,    73,    76,    61,    71,
      25,    74,    71,    79,   195,    76,    80,    77,    71,   200,
     291,    36,    37,    38,    39,    40,    41,    42,    43,    73,
      77,    77,    73,     5,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,    77,    73,    25,    71,
     231,    61,   233,    77,    71,   236,    76,    71,   239,    36,
      37,    38,    39,    40,    41,    42,    43,    73,    73,   250,
     251,   252,     8,   344,   255,    11,    71,   258,    71,     4,
     261,     4,     5,     6,     7,    36,    27,    10,    11,    25,
      26,    27,    28,    29,   275,   276,    64,    33,    34,    95,
      36,    37,    38,    39,    40,    41,    42,    43,   142,    -1,
     123,   123,   293,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    -1,     8,    -1,    -1,    11,    62,    63,    64,    65,
     311,    67,    -1,    69,    70,   316,    -1,    73,    74,    25,
      26,    27,    28,    29,    80,    -1,    -1,    33,    34,    -1,
      36,    37,    38,    39,    40,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    -1,     8,    -1,    -1,    11,    62,    63,    64,    65,
      -1,    67,    -1,    69,    70,    -1,    -1,    73,    74,    25,
      26,    27,    28,    29,    80,    -1,    -1,    33,    34,    -1,
      36,    37,    38,    39,    40,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,
      -1,    67,    -1,    69,    70,    -1,     8,    73,    74,    11,
      -1,    13,    14,    -1,    80,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    -1,    36,    37,    38,    39,    40,    41,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    -1,
      62,    63,    64,    65,    -1,    67,    -1,    69,    70,    -1,
      -1,    73,    74,    75,     8,    77,    78,    11,    -1,    13,
      14,    -1,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    36,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    56,    -1,    -1,    -1,    -1,    -1,    62,    63,
      64,    65,    -1,    67,     8,    69,    70,    11,    -1,    73,
      74,    75,    -1,    77,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    25,    26,    27,    28,    29,    -1,    -1,    -1,    33,
      34,    -1,    36,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    56,    -1,    -1,    -1,    -1,    -1,    62,    63,
      64,    65,    -1,    67,     8,    69,    70,    11,    -1,    73,
      74,    -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    25,    26,    27,    28,    29,    -1,    -1,    -1,    33,
      34,    -1,    36,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    56,    -1,    -1,    -1,    -1,    -1,    62,    63,
      64,    65,    -1,    67,     8,    69,    70,    11,    -1,    73,
      74,    -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    25,    26,    27,    28,    29,    -1,    -1,    -1,    33,
      34,    -1,    36,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    56,    -1,    -1,    -1,    -1,    -1,    62,    63,
      64,    65,    -1,    67,    -1,    69,    70,    -1,     5,    73,
      74,     8,    -1,    77,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,    26,
      27,    28,    29,    -1,    -1,    -1,    33,    34,    -1,    36,
      37,    38,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      -1,     8,    -1,    -1,    11,    62,    63,    64,    65,    -1,
      67,    -1,    69,    70,    -1,    -1,    73,    74,    25,    26,
      27,    28,    29,    -1,    -1,    -1,    33,    34,    -1,    36,
      37,    38,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    -1,
      67,     8,    69,    70,    11,    -1,    73,    74,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,    26,
      27,    28,    29,    -1,    -1,    -1,    33,    34,    -1,    36,
      37,    38,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    -1,
      67,     8,    69,    70,    11,    12,    73,    74,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,    26,
      27,    28,    29,    -1,    -1,    -1,    33,    34,    -1,    36,
      37,    38,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    -1,
      67,    68,    69,    70,    -1,     8,    73,    74,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    26,    27,    28,    29,    -1,    -1,    -1,
      33,    34,    -1,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    -1,     8,    -1,    -1,    11,    62,
      63,    64,    65,    -1,    67,    -1,    69,    70,    -1,    -1,
      73,    74,    25,    26,    27,    28,    29,    -1,    -1,    -1,
      33,    34,    -1,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    -1,     8,    -1,    -1,    11,    62,
      63,    64,    65,    -1,    67,    68,    69,    70,    -1,    -1,
      73,    74,    25,    26,    27,    28,    29,    -1,    -1,    -1,
      33,    34,    -1,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    -1,     8,    -1,    -1,    11,    62,
      63,    64,    65,    -1,    67,    -1,    69,    70,    71,    -1,
      73,    74,    25,    26,    27,    28,    29,    -1,    -1,    -1,
      33,    34,    -1,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    -1,    62,
      63,    64,    65,    -1,    67,    -1,    69,    70,    -1,    -1,
      73,    74,    44,    -1,    46,    47,    -1,    -1,    50,    51,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    70,    44,
      72,    46,    47,    -1,    -1,    50,    51,    -1,    80,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    70,    44,    72,    46,    47,
      -1,    -1,    50,    51,    -1,    80,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    70,    44,    72,    46,    47,    -1,    -1,    50,
      51,    -1,    80,    54,    55,    56,    57,    58,    59,    60,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    70,
      44,    72,    46,    47,    -1,    -1,    50,    51,    -1,    80,
      54,    55,    56,    57,    58,    59,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    70,    -1,    72,    44,
      -1,    46,    47,    -1,    78,    50,    51,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    70,    -1,    72,    44,    -1,
      46,    47,    77,    -1,    50,    51,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    70,    -1,    72,    44,    -1,    46,
      47,    77,    -1,    50,    51,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    69,    70,    44,    72,    46,    47,    -1,    76,
      50,    51,    -1,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      70,    71,    72,    44,    -1,    46,    47,    -1,    -1,    50,
      51,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    70,
      71,    72,    44,    -1,    46,    47,    -1,    -1,    50,    51,
      -1,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    70,    44,
      72,    46,    47,    -1,    -1,    50,    51,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    70,    71,    72,    44,    -1,
      46,    47,    -1,    -1,    50,    51,    44,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    55,    56,    57,
      58,    59,    60,    69,    70,    -1,    72,    -1,    -1,    -1,
      -1,    69,    70,    -1,    72
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    82,    83,    84,    85,    25,    36,    37,    38,
      39,    40,    41,    42,    43,   147,     0,    85,    75,    76,
      86,     4,     6,     7,    10,    11,    87,    88,    89,    90,
      91,    96,    97,    98,   105,   106,   105,    25,    29,   153,
      28,    75,    92,   147,    77,    89,    78,     5,    11,    86,
      76,    76,    25,    93,    94,    95,    78,    25,    29,   154,
     105,   105,    47,    77,    79,    76,    12,   146,   147,   148,
     149,   150,   146,    27,    95,    35,   146,   152,   147,   149,
      78,    44,    74,    74,    73,    80,    80,    26,   100,   101,
     102,   104,   144,    45,   103,    79,    79,    76,    71,   102,
     144,   101,     9,   146,    75,    78,   118,    76,     8,    13,
      14,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      27,    28,    30,    31,    32,    33,    34,    55,    56,    62,
      63,    64,    65,    67,    69,    70,    73,    74,    78,    99,
     105,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   118,   119,   120,   123,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     143,   144,   145,   147,   154,   144,    73,    73,    73,    73,
      73,   123,    76,   118,   123,   123,   132,   134,   123,   147,
     149,   151,   123,   123,   123,    75,   123,   144,    75,   144,
      63,   123,   123,   123,   146,   147,   101,   121,   123,   124,
     144,     5,    77,   109,    78,    44,    46,    47,    50,    51,
      54,    55,    56,    57,    58,    59,    60,    69,    70,    72,
      78,    74,    75,    74,    75,    72,    73,    76,    68,    73,
     122,   123,   140,   141,   142,   122,   122,   122,   123,    76,
      74,    74,    75,   123,   144,    75,   123,    71,    71,    80,
      80,    79,    76,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,    73,    74,    75,   154,   123,
     153,   123,   153,   154,   121,   146,   122,   122,   123,    48,
      49,    61,    71,    53,    71,    78,    71,    71,   123,   123,
     121,    77,    77,   123,   123,   105,   123,   152,   121,   123,
     153,    73,    80,    77,    80,    77,    73,    71,    71,   122,
     122,   146,   118,   123,   118,   122,   118,   118,    80,    80,
      77,    77,     5,    73,    71,    80,    77,   121,   121,    15,
      16,   117,   117,    78,    76,   100,    71,    71,    73,   118,
     122,   152,   103,   122,    71,    73,    71,    71,   118,   100,
     118,   118,   103,   117,    71,   118
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
#line 69 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_grammar(compiler, (yyvsp[(1) - (1)].opval));
      compiler->op_grammar = (yyval.opval);
    ;}
    break;

  case 3:
#line 76 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 4:
#line 80 "yacc/spvm_yacc.y"
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
#line 93 "yacc/spvm_yacc.y"
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
#line 110 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval), (yyvsp[(3) - (3)].opval), NULL);
    ;}
    break;

  case 8:
#line 114 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(5) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 9:
#line 120 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_class_block;
    ;}
    break;

  case 10:
#line 128 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 11:
#line 132 "yacc/spvm_yacc.y"
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
#line 144 "yacc/spvm_yacc.y"
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

  case 19:
#line 168 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 20:
#line 174 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 21:
#line 180 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_enum_block;
    ;}
    break;

  case 22:
#line 188 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 23:
#line 192 "yacc/spvm_yacc.y"
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

  case 24:
#line 205 "yacc/spvm_yacc.y"
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

  case 25:
#line 219 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 27:
#line 226 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 28:
#line 230 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 29:
#line 236 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_our(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(4) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 30:
#line 242 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_has(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(2) - (6)].opval), (yyvsp[(4) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 31:
#line 248 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (10)].opval), (yyvsp[(3) - (10)].opval), (yyvsp[(5) - (10)].opval), (yyvsp[(7) - (10)].opval), (yyvsp[(1) - (10)].opval), (yyvsp[(10) - (10)].opval), NULL, (yyvsp[(8) - (10)].opval));
     ;}
    break;

  case 32:
#line 252 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (10)].opval), (yyvsp[(3) - (10)].opval), (yyvsp[(5) - (10)].opval), (yyvsp[(7) - (10)].opval), (yyvsp[(1) - (10)].opval), NULL, NULL, (yyvsp[(8) - (10)].opval));
     ;}
    break;

  case 33:
#line 258 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (9)].opval), NULL, (yyvsp[(4) - (9)].opval), (yyvsp[(6) - (9)].opval), (yyvsp[(1) - (9)].opval), (yyvsp[(9) - (9)].opval), NULL, (yyvsp[(7) - (9)].opval));
     ;}
    break;

  case 34:
#line 262 "yacc/spvm_yacc.y"
    {
       SPVM_OP* op_list_args;
       if ((yyvsp[(2) - (12)].opval)->id == SPVM_OP_C_ID_LIST) {
         op_list_args = (yyvsp[(2) - (12)].opval);
       }
       else {
         op_list_args = SPVM_OP_new_op_list(compiler, (yyvsp[(2) - (12)].opval)->file, (yyvsp[(2) - (12)].opval)->line);
         SPVM_OP_insert_child(compiler, op_list_args, op_list_args->last, (yyvsp[(2) - (12)].opval));
       }
       
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(5) - (12)].opval), NULL, (yyvsp[(7) - (12)].opval), (yyvsp[(9) - (12)].opval), (yyvsp[(4) - (12)].opval), (yyvsp[(12) - (12)].opval), op_list_args, (yyvsp[(10) - (12)].opval));
     ;}
    break;

  case 35:
#line 277 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 36:
#line 281 "yacc/spvm_yacc.y"
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

  case 37:
#line 292 "yacc/spvm_yacc.y"
    {
       // Add invocant to arguments
       SPVM_OP* op_args = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
       SPVM_OP_insert_child(compiler, op_args, op_args->last, (yyvsp[(1) - (1)].opval));
       
       (yyval.opval) = op_args;
    ;}
    break;

  case 38:
#line 300 "yacc/spvm_yacc.y"
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

  case 39:
#line 319 "yacc/spvm_yacc.y"
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

  case 41:
#line 336 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 42:
#line 342 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = NULL;
    ;}
    break;

  case 44:
#line 349 "yacc/spvm_yacc.y"
    {
      SPVM_TYPE* type = SPVM_TYPE_new(compiler);
      type->is_self = 1;
      SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, (yyvsp[(3) - (3)].opval)->file, (yyvsp[(3) - (3)].opval)->line);
      
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), op_type);
    ;}
    break;

  case 45:
#line 359 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 46:
#line 363 "yacc/spvm_yacc.y"
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

  case 47:
#line 376 "yacc/spvm_yacc.y"
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

  case 49:
#line 393 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 50:
#line 397 "yacc/spvm_yacc.y"
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
#line 410 "yacc/spvm_yacc.y"
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

  case 62:
#line 438 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 63:
#line 442 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 64:
#line 446 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 65:
#line 452 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[(1) - (9)].opval), (yyvsp[(3) - (9)].opval), (yyvsp[(5) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(9) - (9)].opval));
    ;}
    break;

  case 66:
#line 458 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 67:
#line 464 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 68:
#line 470 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 70:
#line 479 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (6)].opval)->file, (yyvsp[(1) - (6)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    ;}
    break;

  case 71:
#line 490 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (6)].opval)->file, (yyvsp[(1) - (6)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    ;}
    break;

  case 72:
#line 503 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 73:
#line 507 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (2)].opval);
    ;}
    break;

  case 74:
#line 511 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
    ;}
    break;

  case 75:
#line 517 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_block;
    ;}
    break;

  case 76:
#line 525 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 79:
#line 532 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 80:
#line 536 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 81:
#line 540 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 82:
#line 544 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 85:
#line 552 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 86:
#line 556 "yacc/spvm_yacc.y"
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

  case 91:
#line 573 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 94:
#line 581 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_constant(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 110:
#line 602 "yacc/spvm_yacc.y"
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

  case 111:
#line 616 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 112:
#line 620 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (1)].opval);
    ;}
    break;

  case 113:
#line 626 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 114:
#line 631 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEGATE, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op_negate, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 115:
#line 636 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unop(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 116:
#line 642 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_incdec(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 117:
#line 647 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_incdec(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 118:
#line 652 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_incdec(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 119:
#line 657 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_incdec(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 120:
#line 664 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 121:
#line 669 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 122:
#line 674 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_concat(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 123:
#line 678 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 124:
#line 682 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 125:
#line 686 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 126:
#line 690 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 127:
#line 694 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 128:
#line 698 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 129:
#line 702 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 130:
#line 706 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 131:
#line 712 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 132:
#line 716 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_special_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 133:
#line 722 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 134:
#line 726 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 135:
#line 730 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 136:
#line 734 "yacc/spvm_yacc.y"
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

  case 137:
#line 757 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 138:
#line 764 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, (yyvsp[(2) - (4)].opval)->file, (yyvsp[(2) - (4)].opval)->line);
      (yyval.opval) = SPVM_OP_build_convert(compiler, op_convert, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 139:
#line 771 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 140:
#line 775 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 141:
#line 779 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 142:
#line 785 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, NULL, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 143:
#line 789 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 144:
#line 793 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_normal_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_normal_terms);
    ;}
    break;

  case 145:
#line 798 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 146:
#line 802 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_normal_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_normal_terms);
    ;}
    break;

  case 147:
#line 807 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[(2) - (5)].opval)->file, (yyvsp[(2) - (5)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (5)].opval), op_sub_name, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 148:
#line 814 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 149:
#line 818 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 150:
#line 822 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 151:
#line 828 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 152:
#line 834 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_weaken_array_element(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 153:
#line 840 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 154:
#line 845 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 155:
#line 850 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 156:
#line 855 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 157:
#line 862 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_deref(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 158:
#line 868 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_ref(compiler, op_ref, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 159:
#line 873 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, (yyvsp[(1) - (4)].opval)->file, (yyvsp[(1) - (4)].opval)->line);
      (yyval.opval) = SPVM_OP_build_ref(compiler, op_ref, (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 160:
#line 880 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 161:
#line 886 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 162:
#line 892 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_or(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 163:
#line 896 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_and(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 164:
#line 900 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_not(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 165:
#line 906 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 166:
#line 910 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 167:
#line 916 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 168:
#line 922 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package_var_access(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 173:
#line 934 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 174:
#line 938 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_byte_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 175:
#line 944 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_short_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 176:
#line 950 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 177:
#line 956 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_long_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 178:
#line 962 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_float_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 179:
#line 968 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_double_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 180:
#line 974 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_any_object_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 181:
#line 980 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_string_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 182:
#line 988 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 183:
#line 994 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 184:
#line 998 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 185:
#line 1004 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_const_array_type(compiler, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 186:
#line 1010 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 187:
#line 1014 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 189:
#line 1021 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3247 "spvm_yacc.tab.c"
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


#line 1033 "yacc/spvm_yacc.y"


