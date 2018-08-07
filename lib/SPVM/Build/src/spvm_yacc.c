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
     OUR = 262,
     SELF = 263,
     IF = 264,
     ELSIF = 265,
     ELSE = 266,
     FOR = 267,
     WHILE = 268,
     LAST = 269,
     NEXT = 270,
     NAME = 271,
     CONSTANT = 272,
     ENUM = 273,
     DESCRIPTOR = 274,
     CORETYPE = 275,
     CROAK = 276,
     VAR_NAME = 277,
     INTERFACE = 278,
     ISA = 279,
     SWITCH = 280,
     CASE = 281,
     DEFAULT = 282,
     EVAL = 283,
     WEAKEN = 284,
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
     RETURN = 295,
     USE = 296,
     NEW = 297,
     CONST = 298,
     AMPERSAND = 299,
     SPECIAL_ASSIGN = 300,
     ASSIGN = 301,
     OR = 302,
     AND = 303,
     BIT_XOR = 304,
     BIT_OR = 305,
     BIT_AND = 306,
     REL = 307,
     SHIFT = 308,
     REMAINDER = 309,
     DIVIDE = 310,
     MULTIPLY = 311,
     DEREF = 312,
     REF = 313,
     UMINUS = 314,
     SCALAR = 315,
     NOT = 316,
     DEC = 317,
     INC = 318,
     ARROW = 319
   };
#endif
/* Tokens.  */
#define MY 258
#define HAS 259
#define SUB 260
#define PACKAGE 261
#define OUR 262
#define SELF 263
#define IF 264
#define ELSIF 265
#define ELSE 266
#define FOR 267
#define WHILE 268
#define LAST 269
#define NEXT 270
#define NAME 271
#define CONSTANT 272
#define ENUM 273
#define DESCRIPTOR 274
#define CORETYPE 275
#define CROAK 276
#define VAR_NAME 277
#define INTERFACE 278
#define ISA 279
#define SWITCH 280
#define CASE 281
#define DEFAULT 282
#define EVAL 283
#define WEAKEN 284
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
#define RETURN 295
#define USE 296
#define NEW 297
#define CONST 298
#define AMPERSAND 299
#define SPECIAL_ASSIGN 300
#define ASSIGN 301
#define OR 302
#define AND 303
#define BIT_XOR 304
#define BIT_OR 305
#define BIT_AND 306
#define REL 307
#define SHIFT 308
#define REMAINDER 309
#define DIVIDE 310
#define MULTIPLY 311
#define DEREF 312
#define REF 313
#define UMINUS 314
#define SCALAR 315
#define NOT 316
#define DEC 317
#define INC 318
#define ARROW 319




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
#line 256 "spvm_yacc.tab.c"

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
#define YYLAST   1449

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  79
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  196
/* YYNRULES -- Number of states.  */
#define YYNSTATES  363

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   319

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      72,    70,     2,    55,    76,    56,    57,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    77,    45,
       2,     2,     2,     2,    62,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    73,     2,    78,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    74,     2,    75,    61,     2,     2,     2,
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
      46,    47,    48,    49,    50,    51,    52,    53,    54,    58,
      59,    60,    63,    64,    65,    66,    67,    68,    69,    71
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
      80,     0,    -1,    81,    -1,    -1,    82,    -1,    82,    83,
      -1,    83,    -1,    85,    -1,    41,   142,    45,    -1,     6,
     142,   138,    90,    -1,     6,   138,    90,    -1,    -1,    88,
      -1,    88,    89,    -1,    89,    -1,   107,    -1,   108,    -1,
     110,    -1,   112,    45,    -1,    84,    -1,   109,    -1,    74,
      87,    75,    -1,    74,    92,    75,    -1,    -1,    93,    -1,
      93,    76,    94,    -1,    93,    76,    -1,    94,    -1,    16,
      -1,    16,    47,    17,    -1,    -1,    96,    -1,    96,    97,
      -1,    97,    -1,    99,    -1,   105,    -1,   100,    -1,   101,
      -1,    98,    -1,   102,    -1,   103,    -1,   104,    -1,   151,
      -1,    74,    95,    75,    -1,   120,    45,    -1,   121,    45,
      -1,    45,    -1,    12,    72,   119,    45,   119,    45,   119,
      70,    98,    -1,    13,    72,   119,    70,    98,    -1,    25,
      72,   120,    70,    98,    -1,    26,   120,    77,    -1,    27,
      77,    -1,     9,    72,   119,    70,    98,   106,    -1,    -1,
      11,    98,    -1,    10,    72,   119,    70,    98,   106,    -1,
       4,   148,    77,   139,   141,    45,    -1,   139,     5,   149,
      77,   147,    72,   134,    70,    98,    -1,   139,     5,   149,
      77,   147,    72,   134,    70,    45,    -1,   139,     5,    77,
     147,    72,   134,    70,    98,    -1,   139,     5,    77,   147,
      72,   134,    70,    45,    -1,    18,    91,    -1,     3,   150,
      77,   141,    -1,     3,   150,    -1,     7,   150,    77,   141,
      -1,    -1,   114,    -1,   114,    76,   120,    -1,   114,    76,
     115,    -1,   114,    76,    -1,   115,    -1,   120,    -1,    72,
     114,    70,    -1,    62,   120,    -1,    62,    74,   120,    75,
      -1,    66,    62,   120,    -1,    66,    62,    74,   120,    75,
      -1,    63,   150,    -1,    63,    74,   150,    75,    -1,    64,
     150,    -1,    64,    74,   150,    75,    -1,   120,    -1,   130,
      -1,   131,    -1,   122,    -1,    72,   119,    70,    -1,   150,
      -1,    17,    -1,    30,    -1,   133,    -1,   126,    -1,   132,
      -1,   125,    -1,   123,    -1,   124,    -1,   116,    -1,   111,
      -1,   129,    -1,   128,    -1,   118,    -1,   117,    -1,    14,
      -1,    15,    -1,    40,    -1,    40,   120,    -1,    21,    -1,
      21,   120,    -1,   126,    47,   120,    -1,   132,    47,   120,
      -1,   127,    -1,   119,    24,   141,    -1,    42,   142,    -1,
      42,   146,    -1,    42,   144,    74,   113,    75,    -1,    86,
      -1,   109,    -1,    73,   113,    78,    -1,    72,   141,    70,
     120,    -1,   120,    71,    74,   148,    75,    -1,   126,    74,
     148,    75,    -1,   132,    74,   148,    75,    -1,    29,   126,
      -1,    55,   120,    -1,    56,   120,    -1,    69,   120,    -1,
     120,    69,    -1,    68,   120,    -1,   120,    68,    -1,    61,
     120,    -1,   120,    55,   120,    -1,   120,    56,   120,    -1,
     120,    57,   120,    -1,   120,    60,   120,    -1,   120,    59,
     120,    -1,   120,    58,   120,    -1,   120,    50,   120,    -1,
     120,    44,   120,    -1,   120,    51,   120,    -1,   120,    54,
     120,    -1,   111,    47,   120,    -1,   150,    47,   120,    -1,
     150,    46,   120,    -1,    72,   120,    70,    -1,   117,    47,
     120,    -1,   120,    53,   120,    -1,   119,    48,   119,    -1,
     119,    49,   119,    -1,    67,   119,    -1,   120,    71,    73,
     120,    78,    -1,   132,    73,   120,    78,    -1,   126,    73,
     120,    78,    -1,   149,    72,   113,    70,    -1,   142,    71,
     149,    72,   113,    70,    -1,   142,    71,   149,    -1,   120,
      71,   149,    72,   113,    70,    -1,   120,    71,   149,    -1,
     120,    71,    72,   113,    70,    -1,    -1,   135,    -1,   137,
      -1,   137,    76,   135,    -1,   135,    76,   136,    -1,   135,
      76,    -1,   136,    -1,   150,    77,   141,    -1,   150,    77,
       8,    -1,    -1,    77,   140,    -1,    -1,   140,    -1,   140,
      19,    -1,    19,    -1,   142,    -1,   144,    -1,   145,    -1,
     143,    -1,    16,    -1,    32,    -1,    33,    -1,    34,    -1,
      35,    -1,    36,    -1,    37,    -1,    39,    -1,    38,    -1,
      44,   142,    -1,   142,    73,    78,    -1,   144,    73,    78,
      -1,    43,   144,    -1,   142,    73,   120,    78,    -1,   144,
      73,   120,    78,    -1,   141,    -1,    31,    -1,    16,    -1,
      16,    -1,    22,    -1,    28,    98,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    56,    56,    65,    68,    81,    95,    98,   101,   107,
     113,   120,   123,   135,   149,   152,   153,   154,   155,   156,
     157,   160,   168,   177,   180,   193,   207,   211,   214,   218,
     225,   228,   241,   255,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   269,   277,   278,   279,   285,   291,   297,
     303,   309,   312,   326,   329,   333,   339,   345,   349,   355,
     360,   367,   373,   377,   383,   390,   393,   406,   420,   445,
     449,   453,   459,   465,   470,   475,   480,   487,   491,   497,
     502,   509,   510,   511,   512,   513,   519,   520,   524,   525,
     526,   527,   528,   529,   530,   531,   532,   533,   534,   535,
     536,   539,   540,   541,   544,   548,   552,   556,   560,   564,
     567,   573,   577,   581,   585,   592,   613,   620,   627,   631,
     635,   641,   647,   652,   657,   662,   667,   672,   677,   683,
     688,   693,   697,   701,   705,   709,   713,   717,   721,   725,
     729,   733,   737,   741,   747,   753,   757,   761,   767,   771,
     775,   781,   785,   789,   794,   798,   803,   811,   814,   825,
     833,   852,   866,   870,   873,   879,   886,   889,   903,   906,
     919,   933,   936,   937,   938,   939,   942,   946,   953,   960,
     967,   974,   981,   988,   995,  1004,  1010,  1014,  1020,  1026,
    1030,  1037,  1038,  1043,  1044,  1047,  1053
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MY", "HAS", "SUB", "PACKAGE", "OUR",
  "SELF", "IF", "ELSIF", "ELSE", "FOR", "WHILE", "LAST", "NEXT", "NAME",
  "CONSTANT", "ENUM", "DESCRIPTOR", "CORETYPE", "CROAK", "VAR_NAME",
  "INTERFACE", "ISA", "SWITCH", "CASE", "DEFAULT", "EVAL", "WEAKEN",
  "UNDEF", "VOID", "BYTE", "SHORT", "INT", "LONG", "FLOAT", "DOUBLE",
  "STRING", "OBJECT", "RETURN", "USE", "NEW", "CONST", "AMPERSAND", "';'",
  "SPECIAL_ASSIGN", "ASSIGN", "OR", "AND", "BIT_XOR", "BIT_OR", "BIT_AND",
  "REL", "SHIFT", "'+'", "'-'", "'.'", "REMAINDER", "DIVIDE", "MULTIPLY",
  "'~'", "'@'", "DEREF", "REF", "UMINUS", "SCALAR", "NOT", "DEC", "INC",
  "')'", "ARROW", "'('", "'['", "'{'", "'}'", "','", "':'", "']'",
  "$accept", "grammar", "opt_declarations_in_grammar",
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
     295,   296,   297,   298,   299,    59,   300,   301,   302,   303,
     304,   305,   306,   307,   308,    43,    45,    46,   309,   310,
     311,   126,    64,   312,   313,   314,   315,   316,   317,   318,
      41,   319,    40,    91,   123,   125,    44,    58,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    79,    80,    81,    81,    82,    82,    83,    84,    85,
      86,    87,    87,    88,    88,    89,    89,    89,    89,    89,
      89,    90,    91,    92,    92,    93,    93,    93,    94,    94,
      95,    95,    96,    96,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    98,    99,    99,    99,   100,   101,   102,
     103,   104,   105,   106,   106,   106,   107,   108,   108,   109,
     109,   110,   111,   111,   112,   113,   113,   114,   114,   114,
     114,   114,   115,   116,   116,   116,   116,   117,   117,   118,
     118,   119,   119,   119,   119,   119,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     122,   123,   123,   123,   123,   123,   124,   125,   126,   126,
     126,   127,   128,   128,   128,   128,   128,   128,   128,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   130,   131,   131,   131,   132,   132,
     132,   133,   133,   133,   133,   133,   133,   134,   134,   134,
     134,   135,   135,   135,   136,   137,   138,   138,   139,   139,
     140,   140,   141,   141,   141,   141,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   143,   144,   144,   145,   146,
     146,   147,   147,   148,   149,   150,   151
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
     169,   193,     0,   195,     0,    23,    61,     0,    21,    13,
      18,     0,   168,     0,    28,     0,    24,    27,     8,   194,
       0,     0,     0,     0,     0,    64,   172,   175,   173,   174,
       0,    22,    26,   192,   191,     0,     0,     0,     0,   188,
     185,     0,     0,    29,    25,   157,     0,    56,   186,   187,
       0,   158,   163,   159,     0,   157,     0,   162,     0,     0,
       0,    60,    30,    59,   161,     0,   160,   165,   164,     0,
       0,   166,     0,     0,     0,   101,   102,   176,    87,   105,
       0,   168,     0,     0,   168,    88,   103,     0,    46,   168,
     168,   168,   168,     0,     0,     0,   168,   168,   168,    65,
     114,     0,    31,    33,    38,    34,    36,    37,    39,    40,
      41,    35,   115,    96,    95,   100,    99,     0,     0,    93,
      94,    92,    90,   109,    98,    97,    91,    89,     0,     0,
       0,    86,    42,     0,    58,    57,    63,     0,   168,   168,
     168,   106,    90,    91,   168,     0,    51,   196,     0,    90,
     104,   111,     0,   112,   122,   123,   128,   168,    73,     0,
      77,     0,    79,   168,   126,   124,     0,     0,   172,   168,
       0,    66,    70,    71,    43,    32,   168,   168,   168,    44,
     168,   168,   168,   168,   168,   168,   168,   168,   168,   127,
     125,     0,    45,   168,   168,     0,   168,   168,     0,     0,
       0,    65,   168,   168,     0,    10,   168,   168,     0,    81,
      84,    82,    83,     0,     0,     0,    50,   168,   168,    65,
       0,     0,     0,   168,    75,   142,   168,     0,    71,   116,
      69,   139,   143,   136,   135,   137,   138,   129,   130,   131,
     134,   133,   132,    65,   168,     0,   155,   107,     0,     0,
     108,     0,     0,   153,     0,   141,   140,    62,   147,     0,
      81,     0,   168,   168,     0,   168,   168,     0,     0,     0,
       0,     0,    74,    78,    80,     0,   117,    72,    68,    67,
       0,     0,     0,    65,   150,   119,   149,   120,    65,   151,
      85,   110,   145,   146,    53,   144,     0,    48,    49,   189,
     190,   113,    76,   156,   148,   118,     0,     0,     0,     0,
      52,   168,   154,   152,   168,    54,     0,     0,     0,     0,
      47,    53,    55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    30,     6,   140,    31,    32,
      33,    24,    46,    55,    56,    57,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   350,    34,    35,
     152,    37,   153,    38,   210,   211,   212,   154,   155,   156,
     248,   249,   158,   250,   159,   160,   161,   182,   163,   164,
     165,   251,   252,   183,   167,    90,    91,    92,    93,    20,
     168,    40,   207,   169,    67,    68,    69,   193,    75,    42,
     170,   171,   172
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -239
static const yytype_int16 yypact[] =
{
      19,   312,    41,  -239,    19,  -239,  -239,  -239,  -239,  -239,
    -239,  -239,  -239,  -239,  -239,  -239,   -33,  -239,  -239,    30,
     -21,  -239,    77,    82,  -239,  -239,    83,    85,    39,   312,
    -239,    58,    82,  -239,  -239,  -239,  -239,  -239,    91,   142,
      77,  -239,    71,  -239,    75,   139,  -239,   111,  -239,  -239,
    -239,    -3,    30,   437,   112,    93,    84,  -239,  -239,  -239,
     251,    92,   437,   312,   312,  -239,   101,  -239,   109,  -239,
     169,  -239,   139,  -239,  -239,   115,   251,   143,   101,   109,
    -239,   113,   116,  -239,  -239,    85,   117,  -239,  -239,  -239,
     120,   119,  -239,   121,   122,    85,   -28,    85,    85,   106,
     126,  -239,   493,  -239,  -239,   123,   119,  -239,  -239,   -26,
      85,   -33,   129,   130,   133,  -239,  -239,   137,  -239,   888,
     140,  1091,   134,   144,  1091,  -239,   888,   312,  -239,  1091,
    1091,  1091,   557,    -8,     4,   145,  1091,  1091,   753,   959,
    -239,   146,   493,  -239,  -239,  -239,  -239,  -239,  -239,  -239,
    -239,  -239,  -239,   172,  -239,   176,  -239,  1290,   179,  -239,
    -239,  -239,    46,  -239,  -239,  -239,    80,  -239,   224,   159,
     164,    48,  -239,   437,  -239,  -239,   154,   -21,  1023,  1023,
    1023,  1378,    29,    32,  1091,  1195,  -239,  -239,  1378,   -23,
    1378,   166,    38,  -239,   102,   102,   102,  1091,   102,    85,
    -239,    85,  -239,   621,   135,   135,  1312,   174,   -34,   817,
     167,   175,  -239,  1378,  -239,  -239,  1091,  1091,  1091,  -239,
    1091,  1091,  1091,  1091,  1091,  1091,  1091,  1091,  1091,  -239,
    -239,    -4,  -239,  1091,  1091,    83,  1091,  1091,    83,   165,
     232,   959,  1091,  1091,   437,  -239,  1023,   685,   -13,  1334,
    -239,  -239,  -239,    86,    -6,  1356,  -239,   354,   422,   959,
    1223,   177,   181,  1091,   102,  -239,  1091,   -43,  1312,  -239,
     959,  1378,  1378,   843,   843,   843,   911,   377,   377,   377,
     102,   102,   102,   959,  1091,    83,   178,  1378,   107,   191,
    1378,   203,   193,   197,   200,  1378,  1378,  -239,   249,     6,
    1268,   437,  1023,  1023,   144,  1091,  1023,   144,   144,  1117,
    1143,   201,  -239,  -239,  -239,  1245,    47,  -239,  -239,  1378,
     205,  1169,   202,   959,  -239,  -239,  -239,  -239,   959,  -239,
    -239,  -239,    16,   249,   114,  1378,   192,  -239,  -239,  -239,
    -239,  -239,  -239,  -239,  -239,  -239,   208,   209,   219,   144,
    -239,  1023,  -239,  -239,  1023,  -239,    34,    60,   144,   144,
    -239,   114,  -239
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -239,  -239,  -239,  -239,   288,  -239,  -239,  -239,  -239,  -239,
     264,   124,  -239,  -239,  -239,   225,  -239,  -239,   156,   -94,
    -239,  -239,  -239,  -239,  -239,  -239,  -239,   -59,  -239,  -239,
       0,  -239,  -239,  -239,  -238,    94,    36,  -239,  -239,  -239,
    -174,    96,  -239,  -239,  -239,  -239,  -239,   -86,  -239,  -239,
    -239,  -239,  -239,   -82,  -239,   212,   206,   211,  -239,   198,
      65,   291,   -52,    -1,  -239,   -56,  -239,  -239,   235,  -204,
     -47,   -18,  -239
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -195
static const yytype_int16 yytable[] =
{
      16,    65,   103,   294,    61,   253,   254,    79,    74,    44,
      77,   301,    59,    59,    43,   175,   162,   101,   301,   174,
     166,   311,  -121,    36,    74,     1,    43,   317,    47,   187,
     301,   289,    36,   270,   292,   302,   303,   240,   189,    81,
     301,    17,   302,   303,    19,   320,   102,   108,   102,    21,
     234,   235,    66,    23,   302,   303,   162,   304,   301,    66,
     166,    66,    78,    80,   307,   303,   199,    94,   283,   284,
     285,   192,   298,   299,    60,    66,   330,    94,   201,   105,
     105,   322,   302,   303,   301,   346,    26,  -168,    39,    27,
     347,   218,   176,   233,   242,   243,    25,    39,    66,    41,
      28,    21,   234,   235,   358,   237,   238,    43,   302,   303,
     301,   258,   259,    45,   107,   200,   202,    62,   231,   234,
     235,   108,     7,    29,   348,   349,   191,   236,   332,   333,
     359,   306,   336,    48,   302,   303,    50,   208,     8,     9,
      10,    11,    12,    13,    14,    15,   218,    51,    52,    63,
      64,   218,    53,   237,   238,    54,    58,   220,   221,    70,
      72,   222,   223,   224,   225,   226,   227,   228,    71,    76,
     229,   230,    66,   231,    81,   229,   230,   356,   231,   218,
     357,   261,    82,   262,   286,   324,    83,    85,    87,    95,
      96,    88,   297,   293,    89,    97,   109,    98,   157,    99,
     173,   178,   179,  -195,  -195,   180,   231,   203,   208,  -194,
     334,   186,   184,   337,   338,   181,   301,   185,   102,   216,
     188,   214,   190,   217,   232,   194,   195,   196,   198,   239,
     240,   244,   204,   205,   206,   213,   241,   351,   157,   257,
     302,   303,    60,    66,   266,   269,   208,   218,    59,   331,
     323,   270,   313,   220,   221,   355,   314,   222,   223,   224,
     225,   226,   227,   228,   360,   361,   325,     7,   327,   328,
     329,   229,   230,   301,   231,   343,   341,   345,   352,   353,
     255,   326,    73,     8,     9,    10,    11,    12,    13,    14,
      15,   354,    18,   260,    63,    64,    49,    84,   215,   264,
      66,   245,   362,   267,   106,   268,   318,   100,   104,   177,
      22,    86,   271,   272,   273,     0,   274,   275,   276,   277,
     278,   279,   280,   281,   282,     0,     0,     0,     7,   287,
     288,     0,   290,   291,     0,     0,     0,   213,   295,   296,
       0,     0,     0,   300,     8,     9,    10,    11,    12,    13,
      14,    15,     0,   309,   310,   213,     0,   110,     0,   315,
     111,     0,   316,     0,     0,     0,   319,     0,     0,     0,
     117,   118,     0,    21,     0,     0,    43,     0,     0,   213,
     321,     0,     0,     0,   125,     0,     8,     9,    10,    11,
      12,    13,    14,    15,     0,     0,   127,     0,     0,     0,
       0,   335,     0,     0,     0,     0,     0,     0,     0,   129,
     130,     0,     0,     0,     0,   131,   132,   133,   134,   213,
     135,   218,   136,   137,   213,   110,   138,   139,   111,     0,
       0,     0,    88,     0,     0,   226,   227,   228,   117,   118,
       0,    21,     0,     0,    43,   229,   230,     0,   231,     0,
       0,     0,   125,     7,     8,     9,    10,    11,    12,    13,
      14,    15,     0,     0,   127,     0,     0,     0,     0,     8,
       9,    10,    11,    12,    13,    14,    15,   129,   130,     0,
      63,    64,     0,   131,   132,   133,   134,     0,   135,     0,
     136,   137,     0,     0,   138,   139,   110,     0,  -168,   111,
      89,     0,   112,     0,     0,   113,   114,   115,   116,   117,
     118,     0,    21,     0,   119,    43,     0,     0,   120,   121,
     122,   123,   124,   125,     0,     8,     9,    10,    11,    12,
      13,    14,    15,   126,     0,   127,     0,     0,   128,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   129,   130,
       0,     0,     0,     0,   131,   132,   133,   134,     0,   135,
     110,   136,   137,   111,     0,   138,   139,   102,     0,     0,
       0,     0,     0,   117,   118,     0,    21,     0,     0,    43,
       0,     0,     0,     0,     0,     0,     0,   125,     0,     8,
       9,    10,    11,    12,    13,    14,    15,     0,     0,   127,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   129,   130,     0,     0,     0,     0,   131,   132,
     133,   134,     0,   135,   110,   136,   137,   111,     0,   138,
     139,   197,     0,     0,     0,     0,     0,   117,   118,     0,
      21,     0,     0,    43,     0,     0,     0,     0,     0,     0,
       0,   125,     0,     8,     9,    10,    11,    12,    13,    14,
      15,     0,     0,   127,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   129,   130,     0,     0,
       0,     0,   131,   132,   133,   134,     0,   135,   110,   136,
     137,   111,     0,   138,   139,   263,     0,     0,     0,     0,
       0,   117,   118,     0,    21,     0,     0,    43,     0,     0,
       0,     0,     0,     0,     0,   125,     0,     8,     9,    10,
      11,    12,    13,    14,    15,     0,     0,   127,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     129,   130,     0,     0,     0,     0,   131,   132,   133,   134,
       0,   135,   246,   136,   137,     0,   110,   247,   139,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   117,
     118,     0,    21,     0,     0,    43,     0,     0,     0,     0,
       0,     0,     0,   125,     0,     8,     9,    10,    11,    12,
      13,    14,    15,     0,     0,   127,    63,    64,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   129,   130,
       0,     0,     0,     0,   131,   132,   133,   134,     0,   135,
     110,   136,   137,   111,     0,   138,   139,     0,     0,     0,
       0,     0,     0,   117,   118,     0,    21,     0,     0,    43,
       0,     0,     0,     0,     0,     0,     0,   125,     0,     8,
       9,    10,    11,    12,    13,    14,    15,     0,     0,   127,
      63,    64,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   129,   130,     0,     0,     0,     0,   131,   132,
     133,   134,     0,   135,     0,   136,   137,   218,     0,   209,
     139,   110,     0,  -168,   111,     0,     0,   222,   223,   224,
     225,   226,   227,   228,   117,   118,     0,    21,     0,     0,
      43,   229,   230,     0,   231,     0,     0,     0,   125,     0,
       8,     9,    10,    11,    12,    13,    14,    15,     0,     0,
     127,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   129,   130,     0,     0,     0,     0,   131,
     132,   133,   134,     0,   135,   218,   136,   137,     0,     0,
     138,   139,   110,     0,  -168,   111,   223,   224,   225,   226,
     227,   228,     0,     0,     0,   117,   118,     0,    21,   229,
     230,    43,   231,     0,     0,     0,     0,     0,     0,   125,
       0,     8,     9,    10,    11,    12,    13,    14,    15,     0,
       0,   127,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   129,   130,     0,     0,     0,     0,
     131,   132,   133,   134,     0,   135,   110,   136,   137,   111,
       0,   209,   139,     0,     0,     0,     0,     0,     0,   117,
     118,     0,    21,     0,     0,    43,     0,     0,     0,     0,
       0,     0,     0,   125,     0,     8,     9,    10,    11,    12,
      13,    14,    15,     0,     0,   127,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   129,   130,
       0,     0,     0,     0,   131,   132,   133,   134,     0,   135,
     246,   136,   137,     0,   110,   247,   139,   111,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   117,   118,     0,
      21,     0,     0,    43,     0,     0,     0,     0,     0,     0,
       0,   125,     0,     8,     9,    10,    11,    12,    13,    14,
      15,     0,     0,   127,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   129,   130,     0,     0,
       0,     0,   131,   132,   133,   134,     0,   135,     0,   136,
     137,   218,     0,   138,   139,     0,     0,   220,   221,     0,
       0,   222,   223,   224,   225,   226,   227,   228,     0,     0,
       0,     0,     0,     0,     0,   229,   230,   218,   231,     0,
       0,     0,     0,   220,   221,   339,     0,   222,   223,   224,
     225,   226,   227,   228,     0,     0,     0,     0,     0,     0,
       0,   229,   230,   218,   231,     0,     0,     0,     0,   220,
     221,   340,     0,   222,   223,   224,   225,   226,   227,   228,
       0,     0,     0,     0,     0,     0,     0,   229,   230,   218,
     231,     0,     0,     0,     0,   220,   221,   344,     0,   222,
     223,   224,   225,   226,   227,   228,     0,     0,     0,     0,
       0,     0,     0,   229,   230,     0,   231,   218,     0,     0,
       0,     0,   256,   220,   221,     0,     0,   222,   223,   224,
     225,   226,   227,   228,     0,     0,     0,     0,     0,   218,
       0,   229,   230,     0,   231,   220,   221,     0,   312,   222,
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
       0,     0,   218,     0,   229,   230,   308,   231,   220,   221,
       0,     0,   222,   223,   224,   225,   226,   227,   228,     0,
       0,     0,     0,     0,     0,     0,   229,   230,     0,   231
};

static const yytype_int16 yycheck[] =
{
       1,    53,    96,   241,    51,   179,   180,    63,    60,    27,
      62,    24,    16,    16,    22,   109,   102,    45,    24,    45,
     102,   259,    45,    23,    76,     6,    22,    70,    29,   123,
      24,   235,    32,    76,   238,    48,    49,    71,   124,    73,
      24,     0,    48,    49,    77,   283,    74,    99,    74,    19,
      73,    74,    53,    74,    48,    49,   142,    70,    24,    60,
     142,    62,    63,    64,    70,    49,    74,    85,    72,    73,
      74,   127,   246,   247,    77,    76,    70,    95,    74,    97,
      98,   285,    48,    49,    24,   323,     4,     5,    23,     7,
     328,    44,   110,    47,    46,    47,    19,    32,    99,    16,
      18,    19,    73,    74,    70,    73,    74,    22,    48,    49,
      24,    73,    74,    74,     8,   133,   134,    52,    71,    73,
      74,   173,    16,    41,    10,    11,   127,    47,   302,   303,
      70,    45,   306,    75,    48,    49,    45,   138,    32,    33,
      34,    35,    36,    37,    38,    39,    44,     5,    77,    43,
      44,    44,    77,    73,    74,    16,    45,    50,    51,    47,
      76,    54,    55,    56,    57,    58,    59,    60,    75,    77,
      68,    69,   173,    71,    73,    68,    69,   351,    71,    44,
     354,   199,    73,   201,   231,    78,    17,    72,    45,    72,
      70,    78,   244,   240,    78,    76,    70,    76,   102,    77,
      77,    72,    72,    68,    69,    72,    71,    62,   209,    72,
     304,    77,    72,   307,   308,   119,    24,   121,    74,    47,
     124,    75,   126,    47,    45,   129,   130,   131,   132,     5,
      71,    77,   136,   137,   138,   139,    72,    45,   142,    73,
      48,    49,    77,   244,    70,    78,   247,    44,    16,   301,
      72,    76,    75,    50,    51,   349,    75,    54,    55,    56,
      57,    58,    59,    60,   358,   359,    75,    16,    75,    72,
      70,    68,    69,    24,    71,    70,    75,    75,    70,    70,
     184,    78,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    72,     4,   197,    43,    44,    32,    72,   142,   203,
     301,   177,   361,   209,    98,   209,   270,    95,    97,   111,
      19,    76,   216,   217,   218,    -1,   220,   221,   222,   223,
     224,   225,   226,   227,   228,    -1,    -1,    -1,    16,   233,
     234,    -1,   236,   237,    -1,    -1,    -1,   241,   242,   243,
      -1,    -1,    -1,   247,    32,    33,    34,    35,    36,    37,
      38,    39,    -1,   257,   258,   259,    -1,     3,    -1,   263,
       6,    -1,   266,    -1,    -1,    -1,   270,    -1,    -1,    -1,
      16,    17,    -1,    19,    -1,    -1,    22,    -1,    -1,   283,
     284,    -1,    -1,    -1,    30,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    -1,    -1,    42,    -1,    -1,    -1,
      -1,   305,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    -1,    -1,    -1,    -1,    61,    62,    63,    64,   323,
      66,    44,    68,    69,   328,     3,    72,    73,     6,    -1,
      -1,    -1,    78,    -1,    -1,    58,    59,    60,    16,    17,
      -1,    19,    -1,    -1,    22,    68,    69,    -1,    71,    -1,
      -1,    -1,    30,    16,    32,    33,    34,    35,    36,    37,
      38,    39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    55,    56,    -1,
      43,    44,    -1,    61,    62,    63,    64,    -1,    66,    -1,
      68,    69,    -1,    -1,    72,    73,     3,    -1,     5,     6,
      78,    -1,     9,    -1,    -1,    12,    13,    14,    15,    16,
      17,    -1,    19,    -1,    21,    22,    -1,    -1,    25,    26,
      27,    28,    29,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    -1,    42,    -1,    -1,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      -1,    -1,    -1,    -1,    61,    62,    63,    64,    -1,    66,
       3,    68,    69,     6,    -1,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    19,    -1,    -1,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    61,    62,
      63,    64,    -1,    66,     3,    68,    69,     6,    -1,    72,
      73,    74,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      19,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    -1,    -1,
      -1,    -1,    61,    62,    63,    64,    -1,    66,     3,    68,
      69,     6,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    19,    -1,    -1,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    -1,    -1,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    56,    -1,    -1,    -1,    -1,    61,    62,    63,    64,
      -1,    66,    67,    68,    69,    -1,     3,    72,    73,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,
      17,    -1,    19,    -1,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    -1,    -1,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      -1,    -1,    -1,    -1,    61,    62,    63,    64,    -1,    66,
       3,    68,    69,     6,    -1,    72,    73,    -1,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    19,    -1,    -1,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    61,    62,
      63,    64,    -1,    66,    -1,    68,    69,    44,    -1,    72,
      73,     3,    -1,     5,     6,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    16,    17,    -1,    19,    -1,    -1,
      22,    68,    69,    -1,    71,    -1,    -1,    -1,    30,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    -1,    -1,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    61,
      62,    63,    64,    -1,    66,    44,    68,    69,    -1,    -1,
      72,    73,     3,    -1,     5,     6,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    16,    17,    -1,    19,    68,
      69,    22,    71,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    32,    33,    34,    35,    36,    37,    38,    39,    -1,
      -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    56,    -1,    -1,    -1,    -1,
      61,    62,    63,    64,    -1,    66,     3,    68,    69,     6,
      -1,    72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    16,
      17,    -1,    19,    -1,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    -1,    -1,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      -1,    -1,    -1,    -1,    61,    62,    63,    64,    -1,    66,
      67,    68,    69,    -1,     3,    72,    73,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      19,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    -1,    -1,
      -1,    -1,    61,    62,    63,    64,    -1,    66,    -1,    68,
      69,    44,    -1,    72,    73,    -1,    -1,    50,    51,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    44,    71,    -1,
      -1,    -1,    -1,    50,    51,    78,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    44,    71,    -1,    -1,    -1,    -1,    50,
      51,    78,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    44,
      71,    -1,    -1,    -1,    -1,    50,    51,    78,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    -1,    71,    44,    -1,    -1,
      -1,    -1,    77,    50,    51,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    68,    69,    -1,    71,    50,    51,    -1,    75,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    68,    69,    -1,    71,    -1,    50,    51,
      75,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    -1,    -1,    -1,    44,    45,    68,    69,    70,    71,
      50,    51,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    -1,    -1,    -1,    -1,    -1,    44,    -1,    68,    69,
      -1,    71,    50,    51,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    -1,    44,    -1,
      68,    69,    70,    71,    50,    51,    -1,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,
      44,    -1,    68,    69,    -1,    71,    50,    51,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    -1,    -1,    -1,
      -1,    -1,    44,    -1,    68,    69,    70,    71,    50,    51,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    -1,    71
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    80,    81,    82,    83,    85,    16,    32,    33,
      34,    35,    36,    37,    38,    39,   142,     0,    83,    77,
     138,    19,   140,    74,    90,    19,     4,     7,    18,    41,
      84,    87,    88,    89,   107,   108,   109,   110,   112,   139,
     140,    16,   148,    22,   150,    74,    91,   142,    75,    89,
      45,     5,    77,    77,    16,    92,    93,    94,    45,    16,
      77,   149,   139,    43,    44,   141,   142,   143,   144,   145,
      47,    75,    76,    31,   141,   147,    77,   141,   142,   144,
     142,    73,    73,    17,    94,    72,   147,    45,    78,    78,
     134,   135,   136,   137,   150,    72,    70,    76,    76,    77,
     134,    45,    74,    98,   136,   150,   135,     8,   141,    70,
       3,     6,     9,    12,    13,    14,    15,    16,    17,    21,
      25,    26,    27,    28,    29,    30,    40,    42,    45,    55,
      56,    61,    62,    63,    64,    66,    68,    69,    72,    73,
      86,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   109,   111,   116,   117,   118,   120,   121,   123,
     124,   125,   126,   127,   128,   129,   132,   133,   139,   142,
     149,   150,   151,    77,    45,    98,   150,   138,    72,    72,
      72,   120,   126,   132,    72,   120,    77,    98,   120,   126,
     120,   142,   144,   146,   120,   120,   120,    74,   120,    74,
     150,    74,   150,    62,   120,   120,   120,   141,   142,    72,
     113,   114,   115,   120,    75,    97,    47,    47,    44,    45,
      50,    51,    54,    55,    56,    57,    58,    59,    60,    68,
      69,    71,    45,    47,    73,    74,    47,    73,    74,     5,
      71,    72,    46,    47,    77,    90,    67,    72,   119,   120,
     122,   130,   131,   119,   119,   120,    77,    73,    73,    74,
     120,   150,   150,    74,   120,    70,    70,   114,   120,    78,
      76,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,    72,    73,    74,   149,   120,   120,   148,
     120,   120,   148,   149,   113,   120,   120,   141,   119,   119,
     120,    24,    48,    49,    70,    53,    45,    70,    70,   120,
     120,   113,    75,    75,    75,   120,   120,    70,   115,   120,
     113,   120,   148,    72,    78,    75,    78,    75,    72,    70,
      70,   141,   119,   119,    98,   120,   119,    98,    98,    78,
      78,    75,    75,    70,    78,    75,   113,   113,    10,    11,
     106,    45,    70,    70,    72,    98,   119,   119,    70,    70,
      98,    98,   106
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
#line 57 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_grammar(compiler, (yyvsp[(1) - (1)].opval));

      compiler->op_grammar = (yyval.opval);
    ;}
    break;

  case 3:
#line 65 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 4:
#line 69 "yacc/spvm_yacc.y"
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
#line 82 "yacc/spvm_yacc.y"
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
#line 102 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 9:
#line 108 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 10:
#line 114 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (3)].opval), NULL, (yyvsp[(3) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 11:
#line 120 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 12:
#line 124 "yacc/spvm_yacc.y"
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
#line 136 "yacc/spvm_yacc.y"
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
#line 161 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_class_block;
    ;}
    break;

  case 22:
#line 169 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_enum_block;
    ;}
    break;

  case 23:
#line 177 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 24:
#line 181 "yacc/spvm_yacc.y"
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
#line 194 "yacc/spvm_yacc.y"
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
#line 208 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 28:
#line 215 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 29:
#line 219 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 30:
#line 225 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 31:
#line 229 "yacc/spvm_yacc.y"
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
#line 242 "yacc/spvm_yacc.y"
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
#line 270 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_block;
    ;}
    break;

  case 46:
#line 280 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
    ;}
    break;

  case 47:
#line 286 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[(1) - (9)].opval), (yyvsp[(3) - (9)].opval), (yyvsp[(5) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(9) - (9)].opval));
    ;}
    break;

  case 48:
#line 292 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 49:
#line 298 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 50:
#line 304 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 52:
#line 313 "yacc/spvm_yacc.y"
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
#line 326 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 54:
#line 330 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (2)].opval);
    ;}
    break;

  case 55:
#line 334 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
    ;}
    break;

  case 56:
#line 340 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(2) - (6)].opval), (yyvsp[(4) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 57:
#line 346 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (9)].opval), (yyvsp[(3) - (9)].opval), (yyvsp[(5) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(1) - (9)].opval), (yyvsp[(9) - (9)].opval));
     ;}
    break;

  case 58:
#line 350 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (9)].opval), (yyvsp[(3) - (9)].opval), (yyvsp[(5) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(1) - (9)].opval), NULL);
     ;}
    break;

  case 59:
#line 356 "yacc/spvm_yacc.y"
    {
       SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[(2) - (8)].opval)->file, (yyvsp[(2) - (8)].opval)->line);
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (8)].opval), op_sub_name, (yyvsp[(4) - (8)].opval), (yyvsp[(6) - (8)].opval), (yyvsp[(1) - (8)].opval), (yyvsp[(8) - (8)].opval));
     ;}
    break;

  case 60:
#line 361 "yacc/spvm_yacc.y"
    {
       SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[(2) - (8)].opval)->file, (yyvsp[(2) - (8)].opval)->line);
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (8)].opval), op_sub_name, (yyvsp[(4) - (8)].opval), (yyvsp[(6) - (8)].opval), (yyvsp[(1) - (8)].opval), NULL);
     ;}
    break;

  case 61:
#line 368 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 62:
#line 374 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 63:
#line 378 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 64:
#line 384 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package_var(compiler, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 65:
#line 390 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 66:
#line 394 "yacc/spvm_yacc.y"
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
#line 407 "yacc/spvm_yacc.y"
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
#line 421 "yacc/spvm_yacc.y"
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
#line 446 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 70:
#line 450 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (1)].opval);
    ;}
    break;

  case 71:
#line 454 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (1)].opval);
    ;}
    break;

  case 72:
#line 460 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 73:
#line 466 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 74:
#line 471 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 75:
#line 476 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 76:
#line 481 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 77:
#line 488 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_deref(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 78:
#line 492 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_deref(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 79:
#line 498 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_ref(compiler, op_ref, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 80:
#line 503 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, (yyvsp[(1) - (4)].opval)->file, (yyvsp[(1) - (4)].opval)->line);
      (yyval.opval) = SPVM_OP_build_ref(compiler, op_ref, (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 85:
#line 514 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 87:
#line 521 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_constant(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 103:
#line 541 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 104:
#line 545 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 105:
#line 549 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 106:
#line 553 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 107:
#line 557 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 108:
#line 561 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 110:
#line 568 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 111:
#line 574 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new_object(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 112:
#line 578 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new_object(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 113:
#line 582 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new_object(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 114:
#line 586 "yacc/spvm_yacc.y"
    {
      // New
      SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);

      (yyval.opval) = SPVM_OP_build_new_object(compiler, op_new, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 115:
#line 593 "yacc/spvm_yacc.y"
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
#line 614 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 117:
#line 621 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, (yyvsp[(2) - (4)].opval)->file, (yyvsp[(2) - (4)].opval)->line);
      (yyval.opval) = SPVM_OP_build_convert(compiler, op_convert, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 118:
#line 628 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 119:
#line 632 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 120:
#line 636 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 121:
#line 642 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 122:
#line 648 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 123:
#line 653 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEGATE, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op_negate, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 124:
#line 658 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 125:
#line 663 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 126:
#line 668 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 127:
#line 673 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 128:
#line 678 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unop(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 129:
#line 684 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 130:
#line 689 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 131:
#line 694 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_concat(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 132:
#line 698 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 133:
#line 702 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 134:
#line 706 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 135:
#line 710 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 136:
#line 714 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 137:
#line 718 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 138:
#line 722 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 139:
#line 726 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 140:
#line 730 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 141:
#line 734 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 142:
#line 738 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 143:
#line 742 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 144:
#line 748 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 145:
#line 754 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_or(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 146:
#line 758 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_and(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 147:
#line 762 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_not(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 148:
#line 768 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 149:
#line 772 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 150:
#line 776 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 151:
#line 782 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, NULL, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 152:
#line 786 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 153:
#line 790 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_assignable_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_assignable_terms);
    ;}
    break;

  case 154:
#line 795 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 155:
#line 799 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_assignable_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_assignable_terms);
    ;}
    break;

  case 156:
#line 804 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[(2) - (5)].opval)->file, (yyvsp[(2) - (5)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (5)].opval), op_sub_name, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 157:
#line 811 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 158:
#line 815 "yacc/spvm_yacc.y"
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
#line 826 "yacc/spvm_yacc.y"
    {
       // Add invocant to arguments
       SPVM_OP* op_args = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
       SPVM_OP_insert_child(compiler, op_args, op_args->last, (yyvsp[(1) - (1)].opval));
       
       (yyval.opval) = op_args;
    ;}
    break;

  case 160:
#line 834 "yacc/spvm_yacc.y"
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
#line 853 "yacc/spvm_yacc.y"
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
#line 867 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 164:
#line 874 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 165:
#line 880 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 166:
#line 886 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 167:
#line 890 "yacc/spvm_yacc.y"
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
#line 903 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 169:
#line 907 "yacc/spvm_yacc.y"
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
#line 920 "yacc/spvm_yacc.y"
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
#line 943 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 177:
#line 947 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_byte_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 178:
#line 954 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_short_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 179:
#line 961 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_int_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 180:
#line 968 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_long_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 181:
#line 975 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_float_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 182:
#line 982 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_double_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 183:
#line 989 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_object_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 184:
#line 996 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_string_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 185:
#line 1005 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 186:
#line 1011 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 187:
#line 1015 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 188:
#line 1021 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_const_array_type(compiler, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 189:
#line 1027 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 190:
#line 1031 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 192:
#line 1039 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_void(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 195:
#line 1048 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 196:
#line 1054 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3264 "spvm_yacc.tab.c"
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


#line 1058 "yacc/spvm_yacc.y"


