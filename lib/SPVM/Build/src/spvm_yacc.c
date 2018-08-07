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
     OUR = 270,
     SELF = 271,
     CONST = 272,
     LAST = 273,
     NEXT = 274,
     NAME = 275,
     CONSTANT = 276,
     ENUM = 277,
     DESCRIPTOR = 278,
     CORETYPE = 279,
     CROAK = 280,
     VAR_NAME = 281,
     INTERFACE = 282,
     ISA = 283,
     SWITCH = 284,
     CASE = 285,
     DEFAULT = 286,
     EVAL = 287,
     WEAKEN = 288,
     PRECOMPILE = 289,
     BACKSLASH = 290,
     UNDEF = 291,
     VOID = 292,
     BYTE = 293,
     SHORT = 294,
     INT = 295,
     LONG = 296,
     FLOAT = 297,
     DOUBLE = 298,
     STRING = 299,
     OBJECT = 300,
     AMPERSAND = 301,
     SPECIAL_ASSIGN = 302,
     ASSIGN = 303,
     OR = 304,
     AND = 305,
     BIT_XOR = 306,
     BIT_OR = 307,
     BIT_AND = 308,
     REL = 309,
     SHIFT = 310,
     REMAINDER = 311,
     DIVIDE = 312,
     MULTIPLY = 313,
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
#define OUR 270
#define SELF 271
#define CONST 272
#define LAST 273
#define NEXT 274
#define NAME 275
#define CONSTANT 276
#define ENUM 277
#define DESCRIPTOR 278
#define CORETYPE 279
#define CROAK 280
#define VAR_NAME 281
#define INTERFACE 282
#define ISA 283
#define SWITCH 284
#define CASE 285
#define DEFAULT 286
#define EVAL 287
#define WEAKEN 288
#define PRECOMPILE 289
#define BACKSLASH 290
#define UNDEF 291
#define VOID 292
#define BYTE 293
#define SHORT 294
#define INT 295
#define LONG 296
#define FLOAT 297
#define DOUBLE 298
#define STRING 299
#define OBJECT 300
#define AMPERSAND 301
#define SPECIAL_ASSIGN 302
#define ASSIGN 303
#define OR 304
#define AND 305
#define BIT_XOR 306
#define BIT_OR 307
#define BIT_AND 308
#define REL 309
#define SHIFT 310
#define REMAINDER 311
#define DIVIDE 312
#define MULTIPLY 313
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
#line 260 "spvm_yacc.tab.c"

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
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1344

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  196
/* YYNRULES -- Number of states.  */
#define YYNSTATES  363

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
      74,    72,     2,    57,    78,    58,    59,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    79,    47,
       2,     2,     2,     2,    64,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    75,     2,    80,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    76,     2,    77,    63,     2,     2,     2,
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
      45,    46,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    60,    61,    62,    65,    66,    67,    68,    69,    70,
      71,    73
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    13,    15,    19,
      24,    28,    29,    31,    34,    36,    38,    40,    42,    45,
      47,    49,    53,    57,    58,    60,    64,    67,    69,    71,
      75,    76,    78,    81,    83,    85,    87,    89,    91,    93,
      95,    97,    99,   101,   105,   108,   111,   113,   123,   129,
     135,   139,   142,   149,   150,   153,   160,   167,   177,   187,
     196,   205,   208,   213,   216,   221,   222,   224,   228,   232,
     235,   237,   239,   243,   246,   251,   255,   261,   264,   269,
     272,   277,   279,   281,   283,   285,   289,   291,   293,   295,
     297,   299,   301,   303,   305,   307,   309,   311,   313,   315,
     317,   319,   321,   323,   325,   328,   330,   333,   337,   341,
     343,   347,   350,   353,   359,   361,   363,   367,   372,   378,
     383,   388,   391,   394,   397,   400,   403,   406,   409,   412,
     416,   420,   424,   428,   432,   436,   440,   444,   448,   452,
     456,   460,   464,   468,   472,   476,   480,   484,   487,   493,
     498,   503,   508,   515,   519,   526,   530,   536,   537,   539,
     541,   545,   549,   552,   554,   558,   562,   563,   566,   567,
     569,   572,   574,   576,   578,   580,   582,   584,   586,   588,
     590,   592,   594,   596,   598,   600,   603,   607,   611,   614,
     619,   624,   626,   628,   630,   632,   634
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      82,     0,    -1,    83,    -1,    -1,    84,    -1,    84,    85,
      -1,    85,    -1,    87,    -1,    13,   144,    47,    -1,     6,
     144,   140,    92,    -1,     6,   140,    92,    -1,    -1,    90,
      -1,    90,    91,    -1,    91,    -1,   109,    -1,   110,    -1,
     112,    -1,   114,    47,    -1,    86,    -1,   111,    -1,    76,
      89,    77,    -1,    76,    94,    77,    -1,    -1,    95,    -1,
      95,    78,    96,    -1,    95,    78,    -1,    96,    -1,    20,
      -1,    20,    49,    21,    -1,    -1,    98,    -1,    98,    99,
      -1,    99,    -1,   101,    -1,   107,    -1,   102,    -1,   103,
      -1,   100,    -1,   104,    -1,   105,    -1,   106,    -1,   153,
      -1,    76,    97,    77,    -1,   122,    47,    -1,   123,    47,
      -1,    47,    -1,    11,    74,   121,    47,   121,    47,   121,
      72,   100,    -1,    12,    74,   121,    72,   100,    -1,    29,
      74,   122,    72,   100,    -1,    30,   122,    79,    -1,    31,
      79,    -1,     7,    74,   121,    72,   100,   108,    -1,    -1,
       9,   100,    -1,     8,    74,   121,    72,   100,   108,    -1,
       4,   150,    79,   141,   143,    47,    -1,   141,     5,   151,
      79,   149,    74,   136,    72,   100,    -1,   141,     5,   151,
      79,   149,    74,   136,    72,    47,    -1,   141,     5,    79,
     149,    74,   136,    72,   100,    -1,   141,     5,    79,   149,
      74,   136,    72,    47,    -1,    22,    93,    -1,     3,   152,
      79,   143,    -1,     3,   152,    -1,    15,   152,    79,   143,
      -1,    -1,   116,    -1,   116,    78,   122,    -1,   116,    78,
     117,    -1,   116,    78,    -1,   117,    -1,   122,    -1,    74,
     116,    72,    -1,    64,   122,    -1,    64,    76,   122,    77,
      -1,    68,    64,   122,    -1,    68,    64,    76,   122,    77,
      -1,    65,   152,    -1,    65,    76,   152,    77,    -1,    35,
     152,    -1,    35,    76,   152,    77,    -1,   122,    -1,   132,
      -1,   133,    -1,   124,    -1,    74,   121,    72,    -1,   152,
      -1,    21,    -1,    36,    -1,   135,    -1,   128,    -1,   134,
      -1,   127,    -1,   125,    -1,   126,    -1,   118,    -1,   113,
      -1,   131,    -1,   130,    -1,   120,    -1,   119,    -1,    18,
      -1,    19,    -1,    10,    -1,    10,   122,    -1,    25,    -1,
      25,   122,    -1,   128,    49,   122,    -1,   134,    49,   122,
      -1,   129,    -1,   121,    28,   143,    -1,    14,   144,    -1,
      14,   148,    -1,    14,   146,    76,   115,    77,    -1,    88,
      -1,   111,    -1,    75,   115,    80,    -1,    74,   143,    72,
     122,    -1,   122,    73,    76,   150,    77,    -1,   128,    76,
     150,    77,    -1,   134,    76,   150,    77,    -1,    33,   128,
      -1,    57,   122,    -1,    58,   122,    -1,    71,   122,    -1,
     122,    71,    -1,    70,   122,    -1,   122,    70,    -1,    63,
     122,    -1,   122,    57,   122,    -1,   122,    58,   122,    -1,
     122,    59,   122,    -1,   122,    62,   122,    -1,   122,    61,
     122,    -1,   122,    60,   122,    -1,   122,    52,   122,    -1,
     122,    46,   122,    -1,   122,    53,   122,    -1,   122,    56,
     122,    -1,   113,    49,   122,    -1,   152,    49,   122,    -1,
     152,    48,   122,    -1,    74,   122,    72,    -1,   119,    49,
     122,    -1,   122,    55,   122,    -1,   121,    50,   121,    -1,
     121,    51,   121,    -1,    69,   121,    -1,   122,    73,    75,
     122,    80,    -1,   134,    75,   122,    80,    -1,   128,    75,
     122,    80,    -1,   151,    74,   115,    72,    -1,   144,    73,
     151,    74,   115,    72,    -1,   144,    73,   151,    -1,   122,
      73,   151,    74,   115,    72,    -1,   122,    73,   151,    -1,
     122,    73,    74,   115,    72,    -1,    -1,   137,    -1,   139,
      -1,   139,    78,   137,    -1,   137,    78,   138,    -1,   137,
      78,    -1,   138,    -1,   152,    79,   143,    -1,   152,    79,
      16,    -1,    -1,    79,   142,    -1,    -1,   142,    -1,   142,
      23,    -1,    23,    -1,   144,    -1,   146,    -1,   147,    -1,
     145,    -1,    20,    -1,    38,    -1,    39,    -1,    40,    -1,
      41,    -1,    42,    -1,    43,    -1,    45,    -1,    44,    -1,
      46,   144,    -1,   144,    75,    80,    -1,   146,    75,    80,
      -1,    17,   146,    -1,   144,    75,   122,    80,    -1,   146,
      75,   122,    80,    -1,   143,    -1,    37,    -1,    20,    -1,
      20,    -1,    26,    -1,    32,   100,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    54,    54,    63,    66,    79,    93,    96,    99,   105,
     111,   118,   121,   133,   147,   150,   151,   152,   153,   154,
     155,   158,   166,   175,   178,   191,   205,   209,   212,   216,
     223,   226,   239,   253,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   267,   275,   276,   277,   283,   289,   295,
     301,   307,   310,   324,   327,   331,   337,   343,   347,   353,
     358,   365,   371,   375,   381,   388,   391,   404,   418,   443,
     447,   451,   457,   463,   468,   473,   478,   485,   489,   495,
     500,   507,   508,   509,   510,   511,   517,   518,   522,   523,
     524,   525,   526,   527,   528,   529,   530,   531,   532,   533,
     534,   537,   538,   539,   542,   546,   550,   554,   558,   562,
     565,   571,   575,   579,   583,   590,   611,   618,   625,   629,
     633,   639,   645,   650,   655,   660,   665,   670,   675,   681,
     686,   691,   695,   699,   703,   707,   711,   715,   719,   723,
     727,   731,   735,   739,   745,   751,   755,   759,   765,   769,
     773,   779,   783,   787,   792,   796,   801,   809,   812,   823,
     831,   850,   864,   868,   871,   877,   884,   887,   901,   904,
     917,   931,   934,   935,   936,   937,   940,   944,   951,   958,
     965,   972,   979,   986,   993,  1002,  1008,  1012,  1018,  1024,
    1028,  1035,  1036,  1041,  1042,  1045,  1051
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MY", "HAS", "SUB", "PACKAGE", "IF",
  "ELSIF", "ELSE", "RETURN", "FOR", "WHILE", "USE", "NEW", "OUR", "SELF",
  "CONST", "LAST", "NEXT", "NAME", "CONSTANT", "ENUM", "DESCRIPTOR",
  "CORETYPE", "CROAK", "VAR_NAME", "INTERFACE", "ISA", "SWITCH", "CASE",
  "DEFAULT", "EVAL", "WEAKEN", "PRECOMPILE", "BACKSLASH", "UNDEF", "VOID",
  "BYTE", "SHORT", "INT", "LONG", "FLOAT", "DOUBLE", "STRING", "OBJECT",
  "AMPERSAND", "';'", "SPECIAL_ASSIGN", "ASSIGN", "OR", "AND", "BIT_XOR",
  "BIT_OR", "BIT_AND", "REL", "SHIFT", "'+'", "'-'", "'.'", "REMAINDER",
  "DIVIDE", "MULTIPLY", "'~'", "'@'", "DEREF", "REF", "UMINUS", "SCALAR",
  "NOT", "DEC", "INC", "')'", "ARROW", "'('", "'['", "'{'", "'}'", "','",
  "':'", "']'", "$accept", "grammar", "opt_declarations_in_grammar",
  "declarations_in_grammar", "declaration_in_grammar", "use", "package",
  "anon_package", "opt_declarations_in_package", "declarations_in_package",
  "declaration_in_package", "package_block", "enumeration_block",
  "opt_enumeration_values", "enumeration_values", "enumeration_value",
  "opt_statements", "statements", "statement", "block", "normal_statement",
  "for_statement", "while_statement", "switch_statement", "case_statement",
  "default_statement", "if_statement", "else_statement", "field", "sub",
  "anon_sub", "enumeration", "my_var", "package_var",
  "opt_assignable_terms", "assignable_terms", "list_assignable_terms",
  "array_length", "deref", "ref", "term", "assignable_term", "expression",
  "isa", "new_object", "array_init", "convert_type", "field_access",
  "weaken_field", "unop", "binop", "relative_term", "logical_term",
  "array_access", "call_sub", "opt_args", "args", "arg", "invocant",
  "opt_colon_descriptors", "opt_descriptors", "descriptors", "type",
  "basic_type", "ref_type", "array_type", "const_array_type",
  "array_type_with_length", "type_or_void", "field_name", "sub_name",
  "var", "eval_block", 0
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
     295,   296,   297,   298,   299,   300,   301,    59,   302,   303,
     304,   305,   306,   307,   308,   309,   310,    43,    45,    46,
     311,   312,   313,   126,    64,   314,   315,   316,   317,   318,
     319,   320,    41,   321,    40,    91,   123,   125,    44,    58,
      93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    83,    83,    84,    84,    85,    86,    87,
      88,    89,    89,    90,    90,    91,    91,    91,    91,    91,
      91,    92,    93,    94,    94,    95,    95,    95,    96,    96,
      97,    97,    98,    98,    99,    99,    99,    99,    99,    99,
      99,    99,    99,   100,   101,   101,   101,   102,   103,   104,
     105,   106,   107,   108,   108,   108,   109,   110,   110,   111,
     111,   112,   113,   113,   114,   115,   115,   116,   116,   116,
     116,   116,   117,   118,   118,   118,   118,   119,   119,   120,
     120,   121,   121,   121,   121,   121,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     124,   125,   125,   125,   125,   125,   126,   127,   128,   128,
     128,   129,   130,   130,   130,   130,   130,   130,   130,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   132,   133,   133,   133,   134,   134,
     134,   135,   135,   135,   135,   135,   135,   136,   136,   136,
     136,   137,   137,   137,   138,   139,   140,   140,   141,   141,
     142,   142,   143,   143,   143,   143,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   145,   146,   146,   147,   148,
     148,   149,   149,   150,   151,   152,   153
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     3,     4,
       3,     0,     1,     2,     1,     1,     1,     1,     2,     1,
       1,     3,     3,     0,     1,     3,     2,     1,     1,     3,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     2,     2,     1,     9,     5,     5,
       3,     2,     6,     0,     2,     6,     6,     9,     9,     8,
       8,     2,     4,     2,     4,     0,     1,     3,     3,     2,
       1,     1,     3,     2,     4,     3,     5,     2,     4,     2,
       4,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     2,     3,     3,     1,
       3,     2,     2,     5,     1,     1,     3,     4,     5,     4,
       4,     2,     2,     2,     2,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     5,     4,
       4,     4,     6,     3,     6,     3,     5,     0,     1,     1,
       3,     3,     2,     1,     3,     3,     0,     2,     0,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     3,     2,     4,
       4,     1,     1,     1,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     2,     4,     6,     7,   176,   177,   178,
     179,   180,   181,   182,   184,   183,   166,     1,     5,     0,
       0,   171,   167,    11,     9,   170,     0,     0,     0,     0,
      19,     0,    12,    14,    15,    16,    20,    17,     0,     0,
     169,   193,     0,     0,   195,     0,    23,    61,    21,    13,
      18,     0,   168,     8,     0,    28,     0,    24,    27,   194,
       0,     0,     0,     0,     0,    64,   172,   175,   173,   174,
       0,    22,    26,   192,   191,     0,     0,     0,     0,   188,
     185,     0,     0,    29,    25,   157,     0,    56,   186,   187,
       0,   158,   163,   159,     0,   157,     0,   162,     0,     0,
       0,    60,    30,    59,   161,     0,   160,   165,   164,     0,
       0,   166,     0,   103,     0,     0,     0,   101,   102,   176,
      87,   105,     0,   168,     0,     0,   168,     0,    88,    46,
     168,   168,   168,   168,     0,     0,   168,   168,   168,    65,
     114,     0,    31,    33,    38,    34,    36,    37,    39,    40,
      41,    35,   115,    96,    95,   100,    99,     0,     0,    93,
      94,    92,    90,   109,    98,    97,    91,    89,     0,     0,
       0,    86,    42,     0,    58,    57,    63,     0,   168,   104,
      90,    91,   168,   168,   111,     0,   112,   106,   168,     0,
      51,   196,     0,    90,     0,    79,   122,   123,   128,   168,
      73,     0,    77,   168,   126,   124,     0,     0,   172,   168,
       0,    66,    70,    71,    43,    32,   168,   168,   168,    44,
     168,   168,   168,   168,   168,   168,   168,   168,   168,   127,
     125,     0,    45,   168,   168,     0,   168,   168,     0,     0,
       0,    65,   168,   168,     0,    10,   168,   168,     0,    81,
      84,    82,    83,     0,     0,   168,   168,    65,     0,    50,
       0,     0,     0,   168,    75,   142,   168,     0,    71,   116,
      69,   139,   143,   136,   135,   137,   138,   129,   130,   131,
     134,   133,   132,    65,   168,     0,   155,   107,     0,     0,
     108,     0,     0,   153,     0,   141,   140,    62,   147,     0,
      81,     0,   168,   168,     0,   168,   168,     0,     0,     0,
       0,     0,    80,    74,    78,     0,   117,    72,    68,    67,
       0,     0,     0,    65,   150,   119,   149,   120,    65,   151,
      85,   110,   145,   146,    53,   144,     0,    48,   189,   190,
     113,    49,    76,   156,   148,   118,     0,     0,     0,     0,
      52,   168,   154,   152,   168,    54,     0,     0,     0,     0,
      47,    53,    55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    30,     6,   140,    31,    32,
      33,    24,    47,    56,    57,    58,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   350,    34,    35,
     152,    37,   153,    38,   210,   211,   212,   154,   155,   156,
     248,   249,   158,   250,   159,   160,   161,   180,   163,   164,
     165,   251,   252,   181,   167,    90,    91,    92,    93,    20,
     168,    40,   207,   169,    67,    68,    69,   186,    75,    42,
     170,   171,   172
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -235
static const yytype_int16 yypact[] =
{
       9,   562,    90,  -235,     9,  -235,  -235,  -235,  -235,  -235,
    -235,  -235,  -235,  -235,  -235,  -235,   -29,  -235,  -235,    25,
       6,  -235,    76,   243,  -235,  -235,    94,   562,   100,    60,
    -235,    79,   243,  -235,  -235,  -235,  -235,  -235,   112,   156,
      76,  -235,    84,   119,  -235,    98,   154,  -235,  -235,  -235,
    -235,   -15,    25,  -235,   328,   132,   110,   115,  -235,  -235,
     393,   121,   328,   562,   562,  -235,   126,  -235,   127,  -235,
     182,  -235,   154,  -235,  -235,   130,   393,   158,   126,   127,
    -235,   135,   144,  -235,  -235,   100,   136,  -235,  -235,  -235,
     134,   150,  -235,   151,   160,   100,    36,   100,   100,     0,
     170,  -235,   459,  -235,  -235,   166,   150,  -235,  -235,    41,
     100,   -29,   159,   793,   163,   176,   562,  -235,  -235,   178,
    -235,   793,   179,   955,   180,   168,   955,    -7,  -235,  -235,
     955,   955,   955,   505,     3,   193,   955,   955,   684,   839,
    -235,   153,   459,  -235,  -235,  -235,  -235,  -235,  -235,  -235,
    -235,  -235,  -235,   211,  -235,   213,  -235,  1148,   220,  -235,
    -235,  -235,   -24,  -235,  -235,  -235,    31,  -235,   266,   208,
     209,    71,  -235,   328,  -235,  -235,   203,     6,   885,  1236,
      48,    95,   885,   885,   212,   104,  -235,  1236,   955,  1053,
    -235,  -235,  1236,    11,   100,  -235,    59,    59,    59,   955,
      59,   100,  -235,   551,    87,    87,  1170,   218,   -42,   747,
     204,   214,  -235,  1236,  -235,  -235,   955,   955,   955,  -235,
     955,   955,   955,   955,   955,   955,   955,   955,   955,  -235,
    -235,    -9,  -235,   955,   955,    94,   955,   955,    94,   217,
     271,   839,   955,   955,   328,  -235,   885,   614,   -16,  1192,
    -235,  -235,  -235,    99,     4,   320,   383,   839,  1214,  -235,
     221,  1081,   224,   955,    59,  -235,   955,    38,  1170,  -235,
     839,  1236,  1236,  1254,  1254,  1254,  1271,   165,   165,   165,
      59,    59,    59,   839,   955,    94,   223,  1236,    82,   225,
    1236,   161,   226,   230,   233,  1236,  1236,  -235,   278,    46,
    1126,   328,   885,   885,   168,   955,   885,   168,   975,  1001,
     234,   168,  -235,  -235,  -235,  1103,   -37,  -235,  -235,  1236,
     238,  1027,   235,   839,  -235,  -235,  -235,  -235,   839,  -235,
    -235,  -235,    80,   278,   189,  1236,   117,  -235,  -235,  -235,
    -235,  -235,  -235,  -235,  -235,  -235,   241,   242,   245,   168,
    -235,   885,  -235,  -235,   885,  -235,    50,    53,   168,   168,
    -235,   189,  -235
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -235,  -235,  -235,  -235,   312,  -235,  -235,  -235,  -235,  -235,
     285,   143,  -235,  -235,  -235,   249,  -235,  -235,   183,   -95,
    -235,  -235,  -235,  -235,  -235,  -235,  -235,   -34,  -235,  -235,
     -10,  -235,  -235,  -235,  -234,   120,    54,  -235,  -235,  -235,
    -155,    52,  -235,  -235,  -235,  -235,  -235,   -31,  -235,  -235,
    -235,  -235,  -235,   -65,  -235,   236,   232,   231,  -235,   222,
      61,   313,   -52,    -1,  -235,   -59,  -235,  -235,   261,  -217,
     -45,   -25,  -235
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -195
static const yytype_int16 yytable[] =
{
      16,   103,    65,    45,    79,    59,    61,   294,    74,   218,
      77,    59,   301,    36,   175,     1,   107,    63,   289,    44,
       7,   292,    36,   310,    74,   233,    43,   253,   254,    44,
     191,   240,   301,    81,   302,   303,   231,   166,     8,     9,
      10,    11,    12,    13,    14,    15,    64,   108,    21,   320,
      19,   234,   235,    66,   302,   303,   304,   185,  -121,    66,
      94,    66,    78,    80,    60,   283,   284,   285,   322,   194,
      94,   162,   105,   105,   301,    66,   307,   166,   301,   201,
     236,   301,    23,   101,    39,   176,   234,   235,   174,   346,
      17,   298,   299,    39,   347,   193,   302,   303,    66,    25,
     302,   303,   195,   302,   303,   218,   237,   238,   301,   202,
     317,   162,   102,    62,    41,   184,   270,   102,   330,   242,
     243,   108,   358,   234,   235,   359,    44,   301,   218,   229,
     230,   303,   231,   218,   220,   221,    46,   208,   222,   223,
     224,   225,   226,   227,   228,   301,   306,   332,   333,   302,
     303,   336,   229,   230,   157,   231,    48,  -195,  -195,    50,
     231,    51,   324,    52,   351,   179,    53,   302,   303,   260,
     237,   238,    66,   187,    55,   189,   262,    54,   192,   256,
     257,    70,   196,   197,   198,   200,   286,    71,   204,   205,
     206,   213,   297,    72,   157,   293,   356,   348,   349,   357,
      76,    81,    82,    83,    85,    87,    96,   218,   208,   334,
      95,   218,   337,   220,   221,    88,   341,   222,   223,   224,
     225,   226,   227,   228,    89,   226,   227,   228,    97,    98,
     214,   229,   230,   178,   231,   229,   230,   182,   231,    99,
     258,   326,   109,    66,   102,   173,   208,    26,  -168,   331,
     183,   261,  -194,   188,   355,   264,    27,   203,    28,   190,
     216,   268,   217,   360,   361,    29,    21,   232,   271,   272,
     273,   239,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   240,   244,   241,   269,   287,   288,   255,   290,   291,
     266,    59,   270,   213,   295,   296,    60,   323,   312,   300,
      66,   314,   325,   327,   328,   329,   301,   308,   309,   213,
     343,   340,   345,   352,   353,   315,    18,    49,   316,   354,
     245,    84,   319,   110,   318,   215,   111,   362,   104,   267,
     106,   100,    22,   177,   116,   213,   321,    86,     0,     0,
     119,   120,     0,    21,     0,    63,    44,     0,     7,     0,
       0,     0,     0,     0,     0,   127,   128,   335,     8,     9,
      10,    11,    12,    13,    14,    15,     8,     9,    10,    11,
      12,    13,    14,    15,    64,   213,     0,   130,   131,     0,
     213,     0,     0,   132,   133,   134,   110,     0,   135,   111,
     136,   137,     0,     0,   138,   139,     0,   116,     0,     0,
      88,     0,     0,   119,   120,     0,    21,     0,     0,    44,
      63,     0,     0,     7,     0,     0,     0,     0,   127,   128,
       0,     8,     9,    10,    11,    12,    13,    14,    15,     0,
      73,     8,     9,    10,    11,    12,    13,    14,    15,    64,
     130,   131,     0,     0,     0,     0,   132,   133,   134,     0,
       0,   135,     0,   136,   137,     0,     0,   138,   139,     0,
       0,     0,   110,    89,  -168,   111,   112,     0,     0,   113,
     114,   115,     0,   116,     0,     0,     0,   117,   118,   119,
     120,     0,    21,     0,   121,    44,     0,     0,   122,   123,
     124,   125,   126,     0,   127,   128,     0,     8,     9,    10,
      11,    12,    13,    14,    15,     0,   129,     0,   110,     0,
       0,   111,     0,     0,     0,     0,   130,   131,     0,   116,
       0,     0,   132,   133,   134,   119,   120,   135,    21,   136,
     137,    44,     0,   138,   139,   102,     0,     0,     0,     0,
     127,   128,     0,     8,     9,    10,    11,    12,    13,    14,
      15,     0,     0,     0,   110,     0,     0,   111,     0,     0,
       0,     0,   130,   131,     0,   116,     0,     0,   132,   133,
     134,   119,   120,   135,    21,   136,   137,    44,     0,   138,
     139,   199,     7,     0,     0,     0,   127,   128,     0,     8,
       9,    10,    11,    12,    13,    14,    15,     0,     0,     0,
       8,     9,    10,    11,    12,    13,    14,    15,   130,   131,
       0,     0,     0,     0,   132,   133,   134,   110,     0,   135,
     111,   136,   137,     0,     0,   138,   139,   263,   116,     0,
       0,    63,     0,     0,   119,   120,     0,    21,     0,     0,
      44,     0,     0,     0,     0,     0,     0,     0,     0,   127,
     128,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      64,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   130,   131,     0,     0,     0,     0,   132,   133,   134,
       0,     0,   135,   246,   136,   137,     0,   110,   247,   139,
     111,     0,     0,     0,     0,     0,     0,     0,   116,     0,
       0,    63,     0,     0,   119,   120,     0,    21,     0,     0,
      44,     0,     0,     0,     0,     0,     0,     0,     0,   127,
     128,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      64,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   130,   131,     0,     0,     0,     0,   132,   133,   134,
     110,     0,   135,   111,   136,   137,     0,     0,   138,   139,
       0,   116,     0,     0,    63,     0,     0,   119,   120,     0,
      21,     0,     0,    44,     0,     0,     0,     0,     0,     0,
       0,     0,   127,   128,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    64,     0,     0,   110,     0,  -168,   111,
       0,     0,     0,     0,   130,   131,     0,   116,     0,     0,
     132,   133,   134,   119,   120,   135,    21,   136,   137,    44,
       0,   209,   139,     0,     0,     0,     0,     0,   127,   128,
       0,     8,     9,    10,    11,    12,    13,    14,    15,     0,
       0,     0,   110,     0,  -168,   111,     0,     0,     0,     0,
     130,   131,     0,   116,     0,     0,   132,   133,   134,   119,
     120,   135,    21,   136,   137,    44,     0,   138,   139,     0,
       0,     0,     0,     0,   127,   128,     0,     8,     9,    10,
      11,    12,    13,    14,    15,     0,     0,     0,   110,     0,
       0,   111,     0,     0,     0,     0,   130,   131,     0,   116,
       0,     0,   132,   133,   134,   119,   120,   135,    21,   136,
     137,    44,     0,   209,   139,     0,     0,     0,     0,     0,
     127,   128,     0,     8,     9,    10,    11,    12,    13,    14,
      15,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   130,   131,     0,     0,     0,     0,   132,   133,
     134,     0,     0,   135,   246,   136,   137,     0,   110,   247,
     139,   111,     0,     0,     0,     0,     0,     0,     0,   116,
       0,     0,     0,     0,     0,   119,   120,     0,    21,     0,
       0,    44,     0,     0,     0,     0,     0,     0,     0,     0,
     127,   128,     0,     8,     9,    10,    11,    12,    13,    14,
      15,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   130,   131,     0,     0,     0,     0,   132,   133,
     134,   218,     0,   135,     0,   136,   137,   220,   221,   138,
     139,   222,   223,   224,   225,   226,   227,   228,     0,     0,
       0,     0,     0,     0,     0,   229,   230,   218,   231,     0,
       0,     0,     0,   220,   221,   338,     0,   222,   223,   224,
     225,   226,   227,   228,     0,     0,     0,     0,     0,     0,
       0,   229,   230,   218,   231,     0,     0,     0,     0,   220,
     221,   339,     0,   222,   223,   224,   225,   226,   227,   228,
       0,     0,     0,     0,     0,     0,     0,   229,   230,   218,
     231,     0,     0,     0,     0,   220,   221,   344,     0,   222,
     223,   224,   225,   226,   227,   228,     0,     0,     0,     0,
       0,     0,     0,   229,   230,     0,   231,   218,     0,     0,
       0,     0,   259,   220,   221,     0,     0,   222,   223,   224,
     225,   226,   227,   228,     0,     0,     0,     0,     0,   218,
       0,   229,   230,     0,   231,   220,   221,     0,   313,   222,
     223,   224,   225,   226,   227,   228,     0,     0,     0,     0,
       0,     0,   218,   229,   230,     0,   231,     0,   220,   221,
     342,   305,   222,   223,   224,   225,   226,   227,   228,     0,
       0,     0,     0,     0,   218,   219,   229,   230,   265,   231,
     220,   221,     0,     0,   222,   223,   224,   225,   226,   227,
     228,     0,     0,     0,     0,     0,   218,     0,   229,   230,
       0,   231,   220,   221,     0,     0,   222,   223,   224,   225,
     226,   227,   228,     0,     0,     0,     0,     0,   218,     0,
     229,   230,   265,   231,   220,   221,     0,   305,   222,   223,
     224,   225,   226,   227,   228,     0,     0,     0,     0,     0,
     218,     0,   229,   230,     0,   231,   220,   221,     0,     0,
     222,   223,   224,   225,   226,   227,   228,     0,     0,     0,
       0,     0,   218,     0,   229,   230,   311,   231,   220,   221,
       0,     0,   222,   223,   224,   225,   226,   227,   228,     0,
     218,     0,     0,     0,     0,     0,   229,   230,     0,   231,
     222,   223,   224,   225,   226,   227,   228,   218,     0,     0,
       0,     0,     0,     0,   229,   230,     0,   231,   223,   224,
     225,   226,   227,   228,     0,     0,     0,     0,     0,     0,
       0,   229,   230,     0,   231
};

static const yytype_int16 yycheck[] =
{
       1,    96,    54,    28,    63,    20,    51,   241,    60,    46,
      62,    20,    28,    23,   109,     6,    16,    17,   235,    26,
      20,   238,    32,   257,    76,    49,    27,   182,   183,    26,
     125,    73,    28,    75,    50,    51,    73,   102,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    99,    23,   283,
      79,    75,    76,    54,    50,    51,    72,   116,    47,    60,
      85,    62,    63,    64,    79,    74,    75,    76,   285,    76,
      95,   102,    97,    98,    28,    76,    72,   142,    28,    76,
      49,    28,    76,    47,    23,   110,    75,    76,    47,   323,
       0,   246,   247,    32,   328,   126,    50,    51,    99,    23,
      50,    51,   127,    50,    51,    46,    75,    76,    28,   134,
      72,   142,    76,    52,    20,   116,    78,    76,    72,    48,
      49,   173,    72,    75,    76,    72,    26,    28,    46,    70,
      71,    51,    73,    46,    52,    53,    76,   138,    56,    57,
      58,    59,    60,    61,    62,    28,    47,   302,   303,    50,
      51,   306,    70,    71,   102,    73,    77,    70,    71,    47,
      73,     5,    80,    79,    47,   113,    47,    50,    51,   194,
      75,    76,   173,   121,    20,   123,   201,    79,   126,    75,
      76,    49,   130,   131,   132,   133,   231,    77,   136,   137,
     138,   139,   244,    78,   142,   240,   351,     8,     9,   354,
      79,    75,    75,    21,    74,    47,    72,    46,   209,   304,
      74,    46,   307,    52,    53,    80,   311,    56,    57,    58,
      59,    60,    61,    62,    80,    60,    61,    62,    78,    78,
      77,    70,    71,    74,    73,    70,    71,    74,    73,    79,
     188,    80,    72,   244,    76,    79,   247,     4,     5,   301,
      74,   199,    74,    74,   349,   203,    13,    64,    15,    79,
      49,   209,    49,   358,   359,    22,    23,    47,   216,   217,
     218,     5,   220,   221,   222,   223,   224,   225,   226,   227,
     228,    73,    79,    74,    80,   233,   234,    75,   236,   237,
      72,    20,    78,   241,   242,   243,    79,    74,    77,   247,
     301,    77,    77,    77,    74,    72,    28,   255,   256,   257,
      72,    77,    77,    72,    72,   263,     4,    32,   266,    74,
     177,    72,   270,     3,   270,   142,     6,   361,    97,   209,
      98,    95,    19,   111,    14,   283,   284,    76,    -1,    -1,
      20,    21,    -1,    23,    -1,    17,    26,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,   305,    38,    39,
      40,    41,    42,    43,    44,    45,    38,    39,    40,    41,
      42,    43,    44,    45,    46,   323,    -1,    57,    58,    -1,
     328,    -1,    -1,    63,    64,    65,     3,    -1,    68,     6,
      70,    71,    -1,    -1,    74,    75,    -1,    14,    -1,    -1,
      80,    -1,    -1,    20,    21,    -1,    23,    -1,    -1,    26,
      17,    -1,    -1,    20,    -1,    -1,    -1,    -1,    35,    36,
      -1,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      57,    58,    -1,    -1,    -1,    -1,    63,    64,    65,    -1,
      -1,    68,    -1,    70,    71,    -1,    -1,    74,    75,    -1,
      -1,    -1,     3,    80,     5,     6,     7,    -1,    -1,    10,
      11,    12,    -1,    14,    -1,    -1,    -1,    18,    19,    20,
      21,    -1,    23,    -1,    25,    26,    -1,    -1,    29,    30,
      31,    32,    33,    -1,    35,    36,    -1,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    47,    -1,     3,    -1,
      -1,     6,    -1,    -1,    -1,    -1,    57,    58,    -1,    14,
      -1,    -1,    63,    64,    65,    20,    21,    68,    23,    70,
      71,    26,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,
      35,    36,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,     3,    -1,    -1,     6,    -1,    -1,
      -1,    -1,    57,    58,    -1,    14,    -1,    -1,    63,    64,
      65,    20,    21,    68,    23,    70,    71,    26,    -1,    74,
      75,    76,    20,    -1,    -1,    -1,    35,    36,    -1,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    44,    45,    57,    58,
      -1,    -1,    -1,    -1,    63,    64,    65,     3,    -1,    68,
       6,    70,    71,    -1,    -1,    74,    75,    76,    14,    -1,
      -1,    17,    -1,    -1,    20,    21,    -1,    23,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    57,    58,    -1,    -1,    -1,    -1,    63,    64,    65,
      -1,    -1,    68,    69,    70,    71,    -1,     3,    74,    75,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    14,    -1,
      -1,    17,    -1,    -1,    20,    21,    -1,    23,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    57,    58,    -1,    -1,    -1,    -1,    63,    64,    65,
       3,    -1,    68,     6,    70,    71,    -1,    -1,    74,    75,
      -1,    14,    -1,    -1,    17,    -1,    -1,    20,    21,    -1,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    -1,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    -1,    -1,     3,    -1,     5,     6,
      -1,    -1,    -1,    -1,    57,    58,    -1,    14,    -1,    -1,
      63,    64,    65,    20,    21,    68,    23,    70,    71,    26,
      -1,    74,    75,    -1,    -1,    -1,    -1,    -1,    35,    36,
      -1,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      -1,    -1,     3,    -1,     5,     6,    -1,    -1,    -1,    -1,
      57,    58,    -1,    14,    -1,    -1,    63,    64,    65,    20,
      21,    68,    23,    70,    71,    26,    -1,    74,    75,    -1,
      -1,    -1,    -1,    -1,    35,    36,    -1,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    -1,    -1,     3,    -1,
      -1,     6,    -1,    -1,    -1,    -1,    57,    58,    -1,    14,
      -1,    -1,    63,    64,    65,    20,    21,    68,    23,    70,
      71,    26,    -1,    74,    75,    -1,    -1,    -1,    -1,    -1,
      35,    36,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    58,    -1,    -1,    -1,    -1,    63,    64,
      65,    -1,    -1,    68,    69,    70,    71,    -1,     3,    74,
      75,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    14,
      -1,    -1,    -1,    -1,    -1,    20,    21,    -1,    23,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    36,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    58,    -1,    -1,    -1,    -1,    63,    64,
      65,    46,    -1,    68,    -1,    70,    71,    52,    53,    74,
      75,    56,    57,    58,    59,    60,    61,    62,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    46,    73,    -1,
      -1,    -1,    -1,    52,    53,    80,    -1,    56,    57,    58,
      59,    60,    61,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    46,    73,    -1,    -1,    -1,    -1,    52,
      53,    80,    -1,    56,    57,    58,    59,    60,    61,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    46,
      73,    -1,    -1,    -1,    -1,    52,    53,    80,    -1,    56,
      57,    58,    59,    60,    61,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    -1,    73,    46,    -1,    -1,
      -1,    -1,    79,    52,    53,    -1,    -1,    56,    57,    58,
      59,    60,    61,    62,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    70,    71,    -1,    73,    52,    53,    -1,    77,    56,
      57,    58,    59,    60,    61,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    70,    71,    -1,    73,    -1,    52,    53,
      77,    55,    56,    57,    58,    59,    60,    61,    62,    -1,
      -1,    -1,    -1,    -1,    46,    47,    70,    71,    72,    73,
      52,    53,    -1,    -1,    56,    57,    58,    59,    60,    61,
      62,    -1,    -1,    -1,    -1,    -1,    46,    -1,    70,    71,
      -1,    73,    52,    53,    -1,    -1,    56,    57,    58,    59,
      60,    61,    62,    -1,    -1,    -1,    -1,    -1,    46,    -1,
      70,    71,    72,    73,    52,    53,    -1,    55,    56,    57,
      58,    59,    60,    61,    62,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    70,    71,    -1,    73,    52,    53,    -1,    -1,
      56,    57,    58,    59,    60,    61,    62,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    70,    71,    72,    73,    52,    53,
      -1,    -1,    56,    57,    58,    59,    60,    61,    62,    -1,
      46,    -1,    -1,    -1,    -1,    -1,    70,    71,    -1,    73,
      56,    57,    58,    59,    60,    61,    62,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    -1,    73,    57,    58,
      59,    60,    61,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    -1,    73
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    82,    83,    84,    85,    87,    20,    38,    39,
      40,    41,    42,    43,    44,    45,   144,     0,    85,    79,
     140,    23,   142,    76,    92,    23,     4,    13,    15,    22,
      86,    89,    90,    91,   109,   110,   111,   112,   114,   141,
     142,    20,   150,   144,    26,   152,    76,    93,    77,    91,
      47,     5,    79,    47,    79,    20,    94,    95,    96,    20,
      79,   151,   141,    17,    46,   143,   144,   145,   146,   147,
      49,    77,    78,    37,   143,   149,    79,   143,   144,   146,
     144,    75,    75,    21,    96,    74,   149,    47,    80,    80,
     136,   137,   138,   139,   152,    74,    72,    78,    78,    79,
     136,    47,    76,   100,   138,   152,   137,    16,   143,    72,
       3,     6,     7,    10,    11,    12,    14,    18,    19,    20,
      21,    25,    29,    30,    31,    32,    33,    35,    36,    47,
      57,    58,    63,    64,    65,    68,    70,    71,    74,    75,
      88,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   111,   113,   118,   119,   120,   122,   123,   125,
     126,   127,   128,   129,   130,   131,   134,   135,   141,   144,
     151,   152,   153,    79,    47,   100,   152,   140,    74,   122,
     128,   134,    74,    74,   144,   146,   148,   122,    74,   122,
      79,   100,   122,   128,    76,   152,   122,   122,   122,    76,
     122,    76,   152,    64,   122,   122,   122,   143,   144,    74,
     115,   116,   117,   122,    77,    99,    49,    49,    46,    47,
      52,    53,    56,    57,    58,    59,    60,    61,    62,    70,
      71,    73,    47,    49,    75,    76,    49,    75,    76,     5,
      73,    74,    48,    49,    79,    92,    69,    74,   121,   122,
     124,   132,   133,   121,   121,    75,    75,    76,   122,    79,
     152,   122,   152,    76,   122,    72,    72,   116,   122,    80,
      78,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,    74,    75,    76,   151,   122,   122,   150,
     122,   122,   150,   151,   115,   122,   122,   143,   121,   121,
     122,    28,    50,    51,    72,    55,    47,    72,   122,   122,
     115,    72,    77,    77,    77,   122,   122,    72,   117,   122,
     115,   122,   150,    74,    80,    77,    80,    77,    74,    72,
      72,   143,   121,   121,   100,   122,   121,   100,    80,    80,
      77,   100,    77,    72,    80,    77,   115,   115,     8,     9,
     108,    47,    72,    72,    74,   100,   121,   121,    72,    72,
     100,   100,   108
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
#line 55 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_grammar(compiler, (yyvsp[(1) - (1)].opval));

      compiler->op_grammar = (yyval.opval);
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
#line 80 "yacc/spvm_yacc.y"
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

  case 8:
#line 100 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 9:
#line 106 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 10:
#line 112 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (3)].opval), NULL, (yyvsp[(3) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 11:
#line 118 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 12:
#line 122 "yacc/spvm_yacc.y"
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

  case 13:
#line 134 "yacc/spvm_yacc.y"
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
#line 159 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_class_block;
    ;}
    break;

  case 22:
#line 167 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_enum_block;
    ;}
    break;

  case 23:
#line 175 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 24:
#line 179 "yacc/spvm_yacc.y"
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

  case 25:
#line 192 "yacc/spvm_yacc.y"
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

  case 26:
#line 206 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 28:
#line 213 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 29:
#line 217 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 30:
#line 223 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 31:
#line 227 "yacc/spvm_yacc.y"
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

  case 32:
#line 240 "yacc/spvm_yacc.y"
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

  case 43:
#line 268 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_block;
    ;}
    break;

  case 46:
#line 278 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
    ;}
    break;

  case 47:
#line 284 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[(1) - (9)].opval), (yyvsp[(3) - (9)].opval), (yyvsp[(5) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(9) - (9)].opval));
    ;}
    break;

  case 48:
#line 290 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 49:
#line 296 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 50:
#line 302 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 52:
#line 311 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (6)].opval)->file, (yyvsp[(1) - (6)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    ;}
    break;

  case 53:
#line 324 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 54:
#line 328 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (2)].opval);
    ;}
    break;

  case 55:
#line 332 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
    ;}
    break;

  case 56:
#line 338 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(2) - (6)].opval), (yyvsp[(4) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 57:
#line 344 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (9)].opval), (yyvsp[(3) - (9)].opval), (yyvsp[(5) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(1) - (9)].opval), (yyvsp[(9) - (9)].opval));
     ;}
    break;

  case 58:
#line 348 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (9)].opval), (yyvsp[(3) - (9)].opval), (yyvsp[(5) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(1) - (9)].opval), NULL);
     ;}
    break;

  case 59:
#line 354 "yacc/spvm_yacc.y"
    {
       SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[(2) - (8)].opval)->file, (yyvsp[(2) - (8)].opval)->line);
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (8)].opval), op_sub_name, (yyvsp[(4) - (8)].opval), (yyvsp[(6) - (8)].opval), (yyvsp[(1) - (8)].opval), (yyvsp[(8) - (8)].opval));
     ;}
    break;

  case 60:
#line 359 "yacc/spvm_yacc.y"
    {
       SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[(2) - (8)].opval)->file, (yyvsp[(2) - (8)].opval)->line);
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (8)].opval), op_sub_name, (yyvsp[(4) - (8)].opval), (yyvsp[(6) - (8)].opval), (yyvsp[(1) - (8)].opval), NULL);
     ;}
    break;

  case 61:
#line 366 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 62:
#line 372 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 63:
#line 376 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 64:
#line 382 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package_var(compiler, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 65:
#line 388 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 66:
#line 392 "yacc/spvm_yacc.y"
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

  case 67:
#line 405 "yacc/spvm_yacc.y"
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

  case 68:
#line 419 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (3)].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[(1) - (3)].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (3)].opval));
      }
      
      if ((yyvsp[(3) - (3)].opval)->id == SPVM_OP_C_ID_LIST) {
        SPVM_OP* op_term = (yyvsp[(3) - (3)].opval)->first;
        while ((op_term = SPVM_OP_sibling(compiler, op_term))) {
          SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term);
          SPVM_OP_insert_child(compiler, op_list, op_list->last, op_term);
          op_term = op_stab;
        }
      }
      else {
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(3) - (3)].opval));
      }
      
      (yyval.opval) = op_list;
    ;}
    break;

  case 69:
#line 444 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 70:
#line 448 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (1)].opval);
    ;}
    break;

  case 71:
#line 452 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (1)].opval);
    ;}
    break;

  case 72:
#line 458 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 73:
#line 464 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 74:
#line 469 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 75:
#line 474 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 76:
#line 479 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 77:
#line 486 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_deref(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 78:
#line 490 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_deref(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 79:
#line 496 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_ref(compiler, op_ref, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 80:
#line 501 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, (yyvsp[(1) - (4)].opval)->file, (yyvsp[(1) - (4)].opval)->line);
      (yyval.opval) = SPVM_OP_build_ref(compiler, op_ref, (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 85:
#line 512 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 87:
#line 519 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_constant(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 103:
#line 539 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 104:
#line 543 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 105:
#line 547 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 106:
#line 551 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 107:
#line 555 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 108:
#line 559 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 110:
#line 566 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 111:
#line 572 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new_object(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 112:
#line 576 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new_object(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 113:
#line 580 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new_object(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 114:
#line 584 "yacc/spvm_yacc.y"
    {
      // New
      SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);

      (yyval.opval) = SPVM_OP_build_new_object(compiler, op_new, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 115:
#line 591 "yacc/spvm_yacc.y"
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
      
      // New
      SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = SPVM_OP_build_new_object(compiler, op_new, op_package, NULL);
    ;}
    break;

  case 116:
#line 612 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 117:
#line 619 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, (yyvsp[(2) - (4)].opval)->file, (yyvsp[(2) - (4)].opval)->line);
      (yyval.opval) = SPVM_OP_build_convert(compiler, op_convert, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 118:
#line 626 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 119:
#line 630 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 120:
#line 634 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 121:
#line 640 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 122:
#line 646 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 123:
#line 651 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEGATE, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op_negate, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 124:
#line 656 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 125:
#line 661 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 126:
#line 666 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 127:
#line 671 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 128:
#line 676 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unop(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 129:
#line 682 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 130:
#line 687 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 131:
#line 692 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_concat(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 132:
#line 696 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 133:
#line 700 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 134:
#line 704 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 135:
#line 708 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 136:
#line 712 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 137:
#line 716 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 138:
#line 720 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 139:
#line 724 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 140:
#line 728 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 141:
#line 732 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 142:
#line 736 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 143:
#line 740 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 144:
#line 746 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 145:
#line 752 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_or(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 146:
#line 756 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_and(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 147:
#line 760 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_not(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 148:
#line 766 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 149:
#line 770 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 150:
#line 774 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 151:
#line 780 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, NULL, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 152:
#line 784 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 153:
#line 788 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_assignable_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_assignable_terms);
    ;}
    break;

  case 154:
#line 793 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 155:
#line 797 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_assignable_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_assignable_terms);
    ;}
    break;

  case 156:
#line 802 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[(2) - (5)].opval)->file, (yyvsp[(2) - (5)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (5)].opval), op_sub_name, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 157:
#line 809 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 158:
#line 813 "yacc/spvm_yacc.y"
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

  case 159:
#line 824 "yacc/spvm_yacc.y"
    {
       // Add invocant to arguments
       SPVM_OP* op_args = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
       SPVM_OP_insert_child(compiler, op_args, op_args->last, (yyvsp[(1) - (1)].opval));
       
       (yyval.opval) = op_args;
    ;}
    break;

  case 160:
#line 832 "yacc/spvm_yacc.y"
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

  case 161:
#line 851 "yacc/spvm_yacc.y"
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

  case 162:
#line 865 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 164:
#line 872 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 165:
#line 878 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 166:
#line 884 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 167:
#line 888 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(2) - (2)].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[(2) - (2)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(2) - (2)].opval));
        (yyval.opval) = op_list;
      }
    ;}
    break;

  case 168:
#line 901 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 169:
#line 905 "yacc/spvm_yacc.y"
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

  case 170:
#line 918 "yacc/spvm_yacc.y"
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

  case 176:
#line 941 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 177:
#line 945 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_byte_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 178:
#line 952 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_short_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 179:
#line 959 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_int_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 180:
#line 966 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_long_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 181:
#line 973 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_float_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 182:
#line 980 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_double_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 183:
#line 987 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_object_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 184:
#line 994 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_string_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 185:
#line 1003 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 186:
#line 1009 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 187:
#line 1013 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 188:
#line 1019 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_const_array_type(compiler, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 189:
#line 1025 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 190:
#line 1029 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 192:
#line 1037 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_void(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 195:
#line 1046 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 196:
#line 1052 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3250 "spvm_yacc.tab.c"
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


#line 1056 "yacc/spvm_yacc.y"


