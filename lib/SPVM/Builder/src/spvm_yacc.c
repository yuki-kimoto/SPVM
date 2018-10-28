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
     RETURN = 283,
     WEAKEN = 284,
     CROAK = 285,
     NEW = 286,
     OUTER = 287,
     UNDEF = 288,
     VOID = 289,
     BYTE = 290,
     SHORT = 291,
     INT = 292,
     LONG = 293,
     FLOAT = 294,
     DOUBLE = 295,
     STRING = 296,
     OBJECT = 297,
     AMPERSAND = 298,
     SPECIAL_ASSIGN = 299,
     ASSIGN = 300,
     OR = 301,
     AND = 302,
     BIT_XOR = 303,
     BIT_OR = 304,
     BIT_AND = 305,
     REL = 306,
     SHIFT = 307,
     REMAINDER = 308,
     DIVIDE = 309,
     MULTIPLY = 310,
     ISA = 311,
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
#define RETURN 283
#define WEAKEN 284
#define CROAK 285
#define NEW 286
#define OUTER 287
#define UNDEF 288
#define VOID 289
#define BYTE 290
#define SHORT 291
#define INT 292
#define LONG 293
#define FLOAT 294
#define DOUBLE 295
#define STRING 296
#define OBJECT 297
#define AMPERSAND 298
#define SPECIAL_ASSIGN 299
#define ASSIGN 300
#define OR 301
#define AND 302
#define BIT_XOR 303
#define BIT_OR 304
#define BIT_AND 305
#define REL 306
#define SHIFT 307
#define REMAINDER 308
#define DIVIDE 309
#define MULTIPLY 310
#define ISA 311
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
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1730

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  79
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  196
/* YYNRULES -- Number of states.  */
#define YYNSTATES  376

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
      71,    69,     2,    53,    77,    54,    55,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    74,    76,
       2,     2,     2,     2,    61,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    72,     2,    78,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    73,     2,    75,    60,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    56,    57,
      58,    59,    62,    63,    64,    65,    66,    67,    68,    70
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    13,    17,    23,
      26,    31,    35,    36,    38,    41,    43,    45,    47,    49,
      52,    54,    58,    61,    65,    66,    68,    72,    75,    77,
      79,    83,    88,    95,   105,   115,   124,   136,   137,   139,
     141,   145,   149,   152,   154,   158,   162,   163,   165,   168,
     170,   171,   173,   176,   178,   180,   182,   184,   186,   188,
     190,   192,   194,   196,   199,   202,   204,   214,   220,   226,
     230,   233,   240,   247,   248,   251,   258,   262,   265,   267,
     269,   271,   274,   276,   279,   281,   283,   284,   286,   288,
     290,   292,   294,   298,   300,   302,   304,   306,   308,   310,
     312,   314,   316,   318,   320,   322,   324,   326,   328,   330,
     332,   336,   342,   345,   349,   351,   354,   357,   360,   363,
     366,   369,   372,   376,   380,   384,   388,   392,   396,   400,
     404,   408,   412,   416,   420,   424,   427,   430,   436,   438,
     440,   442,   446,   451,   457,   462,   467,   472,   479,   483,
     490,   494,   500,   506,   511,   516,   519,   522,   525,   530,
     534,   540,   543,   548,   551,   556,   560,   564,   568,   572,
     575,   580,   583,   589,   591,   593,   595,   597,   599,   601,
     603,   605,   607,   609,   611,   613,   615,   617,   620,   624,
     628,   631,   636,   641,   643,   645,   647
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      80,     0,    -1,    81,    -1,    -1,    82,    -1,    82,    83,
      -1,    83,    -1,     3,   144,    85,    -1,     3,   144,    74,
     103,    85,    -1,     3,    85,    -1,     3,    74,   103,    85,
      -1,    73,    86,    75,    -1,    -1,    87,    -1,    87,    88,
      -1,    88,    -1,    96,    -1,    97,    -1,    90,    -1,    95,
      76,    -1,    89,    -1,    10,   144,    76,    -1,     7,    91,
      -1,    73,    92,    75,    -1,    -1,    93,    -1,    93,    77,
      94,    -1,    93,    77,    -1,    94,    -1,    25,    -1,    25,
      45,    27,    -1,     6,   142,    74,   143,    -1,     4,   150,
      74,   103,   143,    76,    -1,   103,     5,   151,    74,   149,
      71,    99,    69,   116,    -1,   103,     5,   151,    74,   149,
      71,    99,    69,    76,    -1,   103,     5,    74,   149,    71,
      99,    69,   116,    -1,    72,   100,    78,   103,     5,    74,
     149,    71,    99,    69,   116,    -1,    -1,   100,    -1,   102,
      -1,   102,    77,   100,    -1,   100,    77,   101,    -1,   100,
      77,    -1,   101,    -1,   142,    74,   143,    -1,   142,    74,
       9,    -1,    -1,   104,    -1,   104,    11,    -1,    11,    -1,
      -1,   106,    -1,   106,   107,    -1,   107,    -1,   108,    -1,
     114,    -1,   109,    -1,   110,    -1,   116,    -1,   111,    -1,
     112,    -1,   113,    -1,   117,    -1,   121,    76,    -1,   118,
      76,    -1,    76,    -1,    17,    71,   120,    76,   120,    76,
     120,    69,   116,    -1,    18,    71,   120,    69,   116,    -1,
      21,    71,   121,    69,   116,    -1,    22,   121,    74,    -1,
      23,    74,    -1,    13,    71,   120,    69,   116,   115,    -1,
      14,    71,   120,    69,   116,   115,    -1,    -1,    16,   116,
      -1,    15,    71,   120,    69,   116,   115,    -1,    73,   105,
      75,    -1,    24,   116,    -1,    19,    -1,    20,    -1,    28,
      -1,    28,   121,    -1,    30,    -1,    30,   121,    -1,   133,
      -1,   134,    -1,    -1,   122,    -1,   121,    -1,   138,    -1,
     140,    -1,   139,    -1,    71,   120,    69,    -1,   142,    -1,
      27,    -1,    33,    -1,   131,    -1,   132,    -1,   130,    -1,
     129,    -1,   127,    -1,   128,    -1,   135,    -1,   141,    -1,
     125,    -1,   123,    -1,   137,    -1,   136,    -1,   126,    -1,
     124,    -1,   122,    77,   121,    -1,   122,    77,    71,   122,
      69,    -1,   122,    77,    -1,    71,   122,    69,    -1,   121,
      -1,    53,   121,    -1,    54,   121,    -1,    60,   121,    -1,
      68,   121,    -1,   121,    68,    -1,    67,   121,    -1,   121,
      67,    -1,   121,    53,   121,    -1,   121,    54,   121,    -1,
     121,    55,   121,    -1,   121,    58,   121,    -1,   121,    57,
     121,    -1,   121,    56,   121,    -1,   121,    48,   121,    -1,
     121,    43,   121,    -1,   121,    49,   121,    -1,   121,    52,
     121,    -1,    71,   121,    69,    -1,   121,    45,   121,    -1,
     121,    44,   121,    -1,    31,   144,    -1,    31,   148,    -1,
      31,   146,    73,   119,    75,    -1,    84,    -1,    97,    -1,
      98,    -1,    72,   119,    78,    -1,    71,   143,    69,   121,
      -1,   121,    70,    72,   121,    78,    -1,   130,    72,   121,
      78,    -1,   132,    72,   121,    78,    -1,   151,    71,   119,
      69,    -1,   144,    70,   151,    71,   119,    69,    -1,   144,
      70,   151,    -1,   121,    70,   151,    71,   119,    69,    -1,
     121,    70,   151,    -1,   121,    70,    71,   119,    69,    -1,
     121,    70,    73,   150,    75,    -1,   132,    73,   150,    75,
      -1,   130,    73,   150,    75,    -1,    29,   132,    -1,    29,
     130,    -1,    61,   121,    -1,    61,    73,   121,    75,    -1,
      65,    61,   121,    -1,    65,    61,    73,   121,    75,    -1,
      62,   142,    -1,    62,    73,   142,    75,    -1,    63,   142,
      -1,    63,    73,   142,    75,    -1,   121,    51,   121,    -1,
     120,    59,   143,    -1,   120,    46,   120,    -1,   120,    47,
     120,    -1,    66,   120,    -1,     8,   142,    74,   143,    -1,
       8,   142,    -1,     8,   142,    74,    32,   143,    -1,    26,
      -1,   144,    -1,   146,    -1,   147,    -1,   145,    -1,    25,
      -1,    35,    -1,    36,    -1,    37,    -1,    38,    -1,    39,
      -1,    40,    -1,    42,    -1,    41,    -1,   144,    43,    -1,
     144,    72,    78,    -1,   146,    72,    78,    -1,    12,   146,
      -1,   144,    72,   121,    78,    -1,   146,    72,   121,    78,
      -1,   143,    -1,    34,    -1,    25,    -1,    25,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    67,    67,    75,    78,    91,   105,   108,   112,   118,
     122,   128,   137,   140,   152,   166,   169,   170,   171,   172,
     173,   176,   182,   188,   197,   200,   213,   227,   231,   234,
     238,   244,   250,   256,   260,   266,   270,   276,   279,   290,
     298,   317,   331,   335,   338,   344,   355,   358,   371,   385,
     389,   392,   405,   419,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   433,   437,   441,   447,   453,   459,   465,
     471,   474,   485,   499,   502,   506,   512,   520,   526,   527,
     528,   531,   535,   539,   543,   544,   548,   551,   564,   565,
     566,   567,   568,   574,   575,   579,   580,   581,   582,   583,
     584,   585,   586,   587,   588,   589,   590,   591,   592,   593,
     596,   610,   635,   639,   643,   649,   654,   659,   665,   670,
     675,   680,   687,   692,   697,   701,   705,   709,   713,   717,
     721,   725,   729,   735,   739,   745,   749,   753,   757,   764,
     783,   804,   811,   818,   822,   826,   832,   836,   840,   845,
     849,   854,   861,   865,   869,   875,   881,   887,   892,   897,
     902,   909,   913,   919,   924,   931,   937,   943,   947,   951,
     957,   961,   965,   971,   977,   978,   979,   980,   983,   987,
     993,   999,  1005,  1011,  1017,  1023,  1029,  1037,  1043,  1047,
    1053,  1059,  1063,  1069,  1070,  1075,  1076
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
  "EVAL", "NAME", "VAR_NAME", "CONSTANT", "RETURN", "WEAKEN", "CROAK",
  "NEW", "OUTER", "UNDEF", "VOID", "BYTE", "SHORT", "INT", "LONG", "FLOAT",
  "DOUBLE", "STRING", "OBJECT", "AMPERSAND", "SPECIAL_ASSIGN", "ASSIGN",
  "OR", "AND", "BIT_XOR", "BIT_OR", "BIT_AND", "REL", "SHIFT", "'+'",
  "'-'", "'.'", "REMAINDER", "DIVIDE", "MULTIPLY", "ISA", "'~'", "'@'",
  "DEREF", "REF", "UMINUS", "SCALAR", "NOT", "DEC", "INC", "')'", "ARROW",
  "'('", "'['", "'{'", "':'", "'}'", "';'", "','", "']'", "$accept",
  "grammar", "opt_packages", "packages", "package", "anon_package",
  "package_block", "opt_declarations", "declarations", "declaration",
  "use", "enumeration", "enumeration_block", "opt_enumeration_values",
  "enumeration_values", "enumeration_value", "our", "has", "sub",
  "anon_sub", "opt_args", "args", "arg", "invocant", "opt_descriptors",
  "descriptors", "opt_statements", "statements", "statement",
  "normal_statement", "for_statement", "while_statement",
  "switch_statement", "case_statement", "default_statement",
  "if_statement", "else_statement", "block", "eval_block", "expression",
  "opt_normal_terms", "term", "normal_term", "normal_terms", "unop",
  "incdec", "binop", "assign", "new", "array_init", "convert_type",
  "array_access", "call_sub", "field_access", "weaken_field",
  "weaken_array_element", "array_length", "deref", "ref", "relative_term",
  "isa", "logical_term", "my_var", "var", "type", "basic_type", "ref_type",
  "array_type", "const_array_type", "array_type_with_length",
  "type_or_void", "field_name", "sub_name", 0
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
     305,   306,   307,    43,    45,    46,   308,   309,   310,   311,
     126,    64,   312,   313,   314,   315,   316,   317,   318,    41,
     319,    40,    91,   123,    58,   125,    59,    44,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    79,    80,    81,    81,    82,    82,    83,    83,    84,
      84,    85,    86,    86,    87,    87,    88,    88,    88,    88,
      88,    89,    90,    91,    92,    92,    93,    93,    93,    94,
      94,    95,    96,    97,    97,    98,    98,    99,    99,    99,
      99,   100,   100,   100,   101,   102,   103,   103,   104,   104,
     105,   105,   106,   106,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   108,   108,   108,   109,   110,   111,   112,
     113,   114,   114,   115,   115,   115,   116,   117,   118,   118,
     118,   118,   118,   118,   118,   118,   119,   119,   120,   120,
     120,   120,   120,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     122,   122,   122,   122,   122,   123,   123,   123,   124,   124,
     124,   124,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   126,   126,   127,   127,   127,   127,   127,
     127,   128,   129,   130,   130,   130,   131,   131,   131,   131,
     131,   131,   132,   132,   132,   133,   134,   135,   135,   135,
     135,   136,   136,   137,   137,   138,   139,   140,   140,   140,
     141,   141,   141,   142,   143,   143,   143,   143,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   145,   146,   146,
     147,   148,   148,   149,   149,   150,   151
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     3,     5,     2,
       4,     3,     0,     1,     2,     1,     1,     1,     1,     2,
       1,     3,     2,     3,     0,     1,     3,     2,     1,     1,
       3,     4,     6,     9,     9,     8,    11,     0,     1,     1,
       3,     3,     2,     1,     3,     3,     0,     1,     2,     1,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     1,     9,     5,     5,     3,
       2,     6,     6,     0,     2,     6,     3,     2,     1,     1,
       1,     2,     1,     2,     1,     1,     0,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     5,     2,     3,     1,     2,     2,     2,     2,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     5,     1,     1,
       1,     3,     4,     5,     4,     4,     4,     6,     3,     6,
       3,     5,     5,     4,     4,     2,     2,     2,     4,     3,
       5,     2,     4,     2,     4,     3,     3,     3,     3,     2,
       4,     2,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     3,
       2,     4,     4,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     2,     4,     6,   178,   179,   180,   181,
     182,   183,   184,   186,   185,     0,     1,     5,    12,    46,
       7,     0,     0,     0,     0,    49,     0,    13,    15,    20,
      18,     0,    16,    17,     0,    47,     0,   195,     0,   173,
       0,    24,    22,     0,    11,    14,    19,     0,    48,     8,
      46,     0,    29,     0,    25,    28,    21,   196,     0,     0,
       0,    31,   174,   177,   175,   176,     0,    23,    27,     0,
       0,     0,   190,   187,     0,     0,    30,    26,   194,   193,
       0,    32,   188,   189,    37,     0,    38,    43,    39,     0,
       0,    42,     0,     0,    46,    34,    33,    41,     0,    40,
      45,    44,     0,     0,     0,     0,     0,     0,    78,    79,
       0,    46,     0,     0,   178,    94,    46,    46,    46,     0,
      95,    46,    46,    46,    46,     0,     0,     0,    46,    46,
      46,    46,    65,   138,   139,   140,     0,     0,    46,    53,
      54,    56,    57,    59,    60,    61,    55,    58,    62,     0,
       0,   105,   109,   104,   108,   100,   101,    99,    98,    96,
      97,    84,    85,   102,   107,   106,   103,    93,     0,     0,
       0,    46,     9,   171,    46,    46,    46,    46,    46,     0,
      70,    77,    81,     0,    98,    97,    83,   135,     0,   136,
     115,   116,   117,    46,   157,     0,   161,     0,   163,    46,
     120,   118,     0,     0,   174,    46,     0,     0,   114,    87,
      93,     0,    76,    52,    64,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    46,   121,   119,     0,
      63,    46,     0,    46,     0,     0,    46,     0,     0,    46,
      46,     0,    88,    89,    91,    90,     0,     0,     0,     0,
      69,    46,    46,    46,     0,     0,     0,    46,   159,   132,
      46,   114,     0,    46,   141,   112,     0,   129,   134,   133,
     128,   130,   131,   122,   123,   124,   127,   126,   125,    46,
      46,     0,   150,     0,     0,     0,     0,   148,     0,    10,
       0,   170,   169,     0,    88,    46,    46,     0,     0,    46,
       0,    46,     0,     0,     0,     0,     0,   158,   162,   164,
       0,   142,   113,     0,    46,   110,     0,     0,     0,     0,
      46,   144,   154,   145,   153,    46,   146,   172,    92,   167,
     168,   166,    73,   165,    73,     0,    67,    68,   191,   192,
     137,   160,     0,     0,    37,   151,   143,   152,     0,     0,
       0,     0,    71,    72,    46,     0,   111,     0,   149,   147,
      46,    74,     0,     0,     0,     0,     0,    37,    35,     0,
      66,     0,    73,     0,    75,    36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,   133,    20,    26,    27,    28,
      29,    30,    42,    53,    54,    55,    31,    32,   134,   135,
      85,    86,    87,    88,   136,    35,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   352,   147,   148,   149,
     207,   241,   242,   209,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   243,
     244,   245,   166,   167,   203,   168,    63,    64,    65,   189,
      80,    38,   169
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -316
static const yytype_int16 yypact[] =
{
      32,   352,    38,  -316,    32,  -316,  -316,  -316,  -316,  -316,
    -316,  -316,  -316,  -316,  -316,   -27,  -316,  -316,   524,    31,
    -316,    48,    30,     2,   352,  -316,    11,   524,  -316,  -316,
    -316,    15,  -316,  -316,    89,    90,    24,  -316,    35,  -316,
      41,    81,  -316,    46,  -316,  -316,  -316,   100,  -316,  -316,
      31,   542,    72,    58,    62,  -316,  -316,  -316,    69,   542,
     352,  -316,   -10,  -316,    84,  -316,   126,  -316,    81,   232,
      99,    98,    84,  -316,   125,   127,  -316,  -316,  -316,  -316,
     106,  -316,  -316,  -316,    30,   137,   131,  -316,   132,   136,
      12,    30,    30,   143,   599,  -316,  -316,  -316,   138,   131,
    -316,  -316,    54,    30,   150,   151,   154,   155,  -316,  -316,
     163,  1371,   140,   162,   165,  -316,   731,  1371,   779,   352,
    -316,  1371,  1371,  1371,   893,    -4,     4,   177,  1371,  1371,
    1091,   437,  -316,  -316,  -316,  -316,   235,   171,   665,  -316,
    -316,  -316,  -316,  -316,  -316,  -316,  -316,  -316,  -316,   174,
     308,  -316,  -316,  -316,  -316,  -316,  -316,  -316,    92,  -316,
      94,  -316,  -316,  -316,  -316,  -316,  -316,  -316,   182,   176,
     542,    31,  -316,   180,  1139,  1139,  1139,  1139,  1371,  1513,
    -316,  -316,  1653,  1653,   -24,    86,  1653,   179,   119,  -316,
      44,    44,    44,  1371,    44,    30,  -316,    30,  -316,   959,
      56,    56,  1569,   187,   -19,  1205,   117,   183,  1653,   178,
     138,   -13,  -316,  -316,  -316,  1371,  1371,  1371,  1371,  1371,
    1371,  1371,  1371,  1371,  1371,  1371,  1371,  -316,  -316,    -7,
    -316,  1371,    48,  1371,    48,   100,  1253,    24,   417,  1139,
    1025,    34,  1597,  -316,  -316,  -316,    61,    37,    85,  1625,
    -316,   485,   533,   827,  1457,   184,   185,  1371,    44,  -316,
    1371,  1569,   -38,    31,  -316,  1323,   232,   315,  1653,  1653,
     315,   315,  1660,   130,   130,   130,    44,    44,    44,  1253,
    1371,    48,   191,    93,   188,   175,   201,   207,   189,  -316,
     542,  -316,  -316,   286,  1541,  1139,  1139,   542,   162,  1371,
     162,  1139,   162,   162,   272,  1401,   205,  -316,  -316,  -316,
    1485,    -3,  -316,   276,  1205,  1653,   212,   215,  1429,   210,
    1253,  -316,  -316,  -316,  -316,  1253,  -316,  -316,  -316,   -18,
     228,  -316,   186,  1653,   186,    43,  -316,  -316,  -316,  -316,
    -316,  -316,   214,   -32,    30,  -316,  -316,  -316,   221,   222,
     223,   162,  -316,  -316,  1139,   232,  -316,   224,  -316,  -316,
    1139,  -316,   378,   229,   162,   496,   162,    30,  -316,   162,
    -316,   226,   186,   162,  -316,  -316
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -316,  -316,  -316,  -316,   297,  -316,   -30,  -316,  -316,   280,
    -316,  -316,  -316,  -316,  -316,   240,  -316,  -316,    16,  -316,
    -312,   -71,   227,  -316,   -14,  -316,  -316,  -316,   193,  -316,
    -316,  -316,  -316,  -316,  -316,  -316,  -315,   -87,  -316,  -316,
    -225,  -161,   181,  -198,  -316,  -316,  -316,  -316,  -316,  -316,
    -316,   197,  -316,   217,  -316,  -316,  -316,  -316,  -316,  -316,
    -316,  -316,  -316,   -21,   -49,    -1,  -316,   -43,  -316,  -316,
    -257,  -207,   -39
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -197
static const yytype_int16 yytable[] =
{
      15,    40,    61,    96,    34,    36,    49,   262,    58,   316,
      70,   288,    57,    34,   246,   247,   248,    72,    57,   353,
      79,    99,    39,    43,    73,   284,   181,   286,   306,   296,
      39,   312,   357,    73,    33,     1,    59,   356,    16,   265,
     215,   297,    25,    33,   101,   265,    18,    19,   231,   232,
      62,   235,  -156,    74,   317,   371,    39,   374,    62,    71,
     206,   266,    74,    89,   279,   280,   281,   229,    62,   195,
      98,    98,   172,    37,   319,    41,   188,   197,   292,   293,
     295,   296,   173,   295,   296,    94,    44,   215,    95,   295,
     296,    46,    62,   297,    47,   348,   297,    18,   363,   215,
     349,    48,   297,   298,   196,   198,    52,   295,   296,    50,
     210,   227,   228,   301,   229,    51,   343,    66,   187,   354,
     297,   101,    56,  -197,  -197,    57,   229,    18,   171,   204,
     300,   295,   296,    67,   329,   330,   215,   216,   217,    68,
     335,   218,   219,    69,   297,   220,   221,   222,   223,   224,
     225,   226,   100,    76,   302,    60,    75,   237,   233,   234,
     227,   228,  -155,   229,   231,   232,   233,   234,     6,    62,
      74,   321,    58,   215,   255,    81,   256,    84,     7,     8,
       9,    10,    11,    12,    13,    14,   224,   225,   226,   291,
     282,   252,   253,   362,    91,   263,   287,   227,   228,   365,
     229,   350,   351,    82,   204,    83,    90,   289,    91,    92,
      93,   332,   170,   334,   180,   336,   337,    79,   215,   216,
     217,   174,   175,   218,   219,   176,   177,   220,   221,   222,
     223,   224,   225,   226,   178,    94,  -196,    62,   199,   204,
     211,   327,   227,   228,    60,   229,   212,   236,   331,   313,
     214,   251,   235,   323,   238,   265,   260,     6,   326,   308,
     309,   264,   320,   322,   361,    62,    78,     7,     8,     9,
      10,    11,    12,    13,    14,   150,   324,   368,   325,   370,
     340,   342,   372,   344,   345,   347,   375,   297,   355,    62,
     358,   359,   179,   364,   360,   373,    62,   182,   183,   186,
     367,    17,   190,   191,   192,   194,    79,    45,    77,   200,
     201,   202,   208,   204,   184,   215,   216,   217,    97,   150,
     218,   219,     0,    89,   220,   221,   222,   223,   224,   225,
     226,   213,   295,   296,   185,     0,     0,     0,     0,   227,
     228,     0,   229,     0,     0,   297,    89,     0,     0,     0,
     338,   215,   216,   217,    62,   328,   218,   219,   215,   249,
     220,   221,   222,   223,   224,   225,   226,   220,   221,   222,
     223,   224,   225,   226,   254,   227,   228,     6,   229,     0,
     258,     0,   227,   228,   230,   229,   261,     7,     8,     9,
      10,    11,    12,    13,    14,     0,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,     0,     0,
       0,     0,   283,     0,   285,     0,     0,   208,     0,     0,
       0,   294,     0,     0,   295,   296,     0,     0,     0,    60,
       0,     0,   304,   305,   208,     0,     0,   297,   310,     0,
     102,   311,     6,     0,     0,   103,   315,   366,    25,   290,
       0,     0,     7,     8,     9,    10,    11,    12,    13,    14,
     208,   318,   114,    39,   115,     0,     0,     0,   119,     0,
     120,     0,     7,     8,     9,    10,    11,    12,    13,    14,
     333,     0,     0,     0,     0,     0,     0,     0,   102,     0,
     121,   122,     0,   103,     0,   261,    25,   123,   124,   125,
     126,   208,   127,     0,   128,   129,   208,     0,   205,   131,
     114,    39,   115,     0,     0,   -86,   119,     0,   120,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    21,   -46,
      22,    23,     0,     0,    24,    25,   102,     0,   121,   122,
       0,   103,   295,   296,    25,   123,   124,   125,   126,     0,
     127,     0,   128,   129,    60,   297,   130,   131,   114,    39,
     115,     0,     0,    82,   119,   369,   120,     6,     7,     8,
       9,    10,    11,    12,    13,    14,     0,     7,     8,     9,
      10,    11,    12,    13,    14,     0,   121,   122,     0,     0,
       0,     0,     0,   123,   124,   125,   126,     0,   127,     0,
     128,   129,   102,     0,   130,   131,     0,   103,     0,     0,
      25,    83,   104,   105,     0,     0,   106,   107,   108,   109,
     110,   111,   112,   113,   114,    39,   115,   116,   117,   118,
     119,     0,   120,     0,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   121,   122,     0,     0,     0,     0,     0,   123,
     124,   125,   126,     0,   127,     0,   128,   129,   102,     0,
     130,   131,    94,   103,   -50,   132,    25,     0,   104,   105,
       0,     0,   106,   107,   108,   109,   110,   111,   112,   113,
     114,    39,   115,   116,   117,   118,   119,     0,   120,     0,
       7,     8,     9,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   121,   122,
       0,     0,     0,     0,     0,   123,   124,   125,   126,     0,
     127,     0,   128,   129,   102,     0,   130,   131,    94,   103,
     -51,   132,    25,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   114,    39,   115,     0,
       0,     0,   119,     0,   120,     0,     7,     8,     9,    10,
      11,    12,    13,    14,     0,     0,     0,     0,     0,     0,
       0,     0,   102,     0,   121,   122,     0,   103,     0,     0,
      25,   123,   124,   125,   126,     0,   127,     0,   128,   129,
       0,     0,   130,   131,   114,    39,   115,   -80,     0,     0,
     119,     0,   120,     0,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     0,     0,     0,     0,     0,     0,     0,
     102,     0,   121,   122,     0,   103,     0,     0,    25,   123,
     124,   125,   126,     0,   127,     0,   128,   129,     0,     0,
     130,   131,   114,    39,   115,   -82,     0,     0,   119,     0,
     120,     0,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     121,   122,     0,     0,     0,     0,     0,   123,   124,   125,
     126,     0,   127,     0,   128,   129,   102,     0,   205,   131,
       0,   103,   -86,     0,    25,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   114,    39,
     115,     0,     0,     0,   119,     0,   120,     0,     7,     8,
       9,    10,    11,    12,    13,    14,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   121,   122,     0,     0,
       0,     0,     0,   123,   124,   125,   126,     0,   127,     0,
     128,   129,   102,     0,   130,   131,   193,   103,     0,     0,
      25,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   114,    39,   115,     0,     0,     0,
     119,     0,   120,     0,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   121,   122,     0,     0,     0,     0,     0,   123,
     124,   125,   126,     0,   127,     0,   128,   129,   102,     0,
     130,   131,   257,   103,     0,     0,    25,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     114,    39,   115,     0,     0,     0,   119,     0,   120,     0,
       7,     8,     9,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   121,   122,
       0,     0,     0,     0,     0,   123,   124,   125,   126,     0,
     127,   239,   128,   129,   102,     0,   240,   131,     0,   103,
       0,     0,    25,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   114,    39,   115,     0,
       0,     0,   119,     0,   120,     0,     7,     8,     9,    10,
      11,    12,    13,    14,     0,     0,     0,     0,     0,     0,
       0,     0,   102,     0,   121,   122,     0,   103,     0,     0,
      25,   123,   124,   125,   126,     0,   127,     0,   128,   129,
       0,     0,   130,   131,   114,    39,   115,     0,     0,     0,
     119,     0,   120,     0,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   121,   122,     0,     0,     0,     0,     0,   123,
     124,   125,   126,     0,   127,   239,   128,   129,   102,     0,
     240,   131,     0,   103,     0,     0,    25,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     114,    39,   115,     0,     0,     0,   119,     0,   120,     0,
       7,     8,     9,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,     0,     0,     0,   102,     0,   121,   122,
       0,   103,     0,     0,    25,   123,   124,   125,   126,     0,
     127,     0,   128,   129,     0,     0,   205,   131,   114,    39,
     115,     0,     0,     0,   119,     0,   120,     0,     7,     8,
       9,    10,    11,    12,    13,    14,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   121,   122,     0,     0,
       0,     0,     0,   123,   124,   125,   126,     0,   127,     0,
     128,   129,   -86,     0,   205,   131,   102,     0,   -46,     0,
       0,   103,     0,     0,    25,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   114,    39,
     115,     0,     0,     0,   119,     0,   120,     0,     7,     8,
       9,    10,    11,    12,    13,    14,     0,     0,     0,     0,
       0,     0,     0,     0,   102,     0,   121,   122,     0,   103,
       0,     0,    25,   123,   124,   125,   126,     0,   127,     0,
     128,   129,     0,     0,   314,   131,   114,    39,   115,     0,
       0,     0,   119,     0,   120,     0,     7,     8,     9,    10,
      11,    12,    13,    14,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   121,   122,     0,     0,     0,     0,
       0,   123,   124,   125,   126,     0,   127,     0,   128,   129,
       0,     0,   130,   131,   215,   216,   217,     0,     0,   218,
     219,     0,     0,   220,   221,   222,   223,   224,   225,   226,
       0,     0,     0,     0,     0,     0,     0,     0,   227,   228,
       0,   229,   215,   216,   217,     0,     0,   218,   219,   339,
       0,   220,   221,   222,   223,   224,   225,   226,     0,     0,
       0,     0,     0,     0,     0,     0,   227,   228,     0,   229,
     215,   216,   217,     0,     0,   218,   219,   346,     0,   220,
     221,   222,   223,   224,   225,   226,     0,     0,     0,     0,
       0,     0,     0,     0,   227,   228,     0,   229,   215,   216,
     217,     0,   307,   218,   219,     0,     0,   220,   221,   222,
     223,   224,   225,   226,     0,     0,     0,     0,     0,     0,
       0,     0,   227,   228,     0,   229,   215,   216,   217,     0,
     341,   218,   219,     0,     0,   220,   221,   222,   223,   224,
     225,   226,     0,     0,     0,     0,     0,     0,     0,     0,
     227,   228,     0,   229,   215,   216,   217,   250,     0,   218,
     219,     0,   299,   220,   221,   222,   223,   224,   225,   226,
       0,     0,     0,     0,     0,     0,     0,     0,   227,   228,
     259,   229,   215,   216,   217,     0,     0,   218,   219,     0,
       0,   220,   221,   222,   223,   224,   225,   226,     0,     0,
       0,     0,     0,     0,     0,     0,   227,   228,   259,   229,
     215,   216,   217,     0,     0,   218,   219,     0,   299,   220,
     221,   222,   223,   224,   225,   226,     0,     0,     0,     0,
       0,     0,     0,     0,   227,   228,     0,   229,   215,   216,
     217,     0,     0,   218,   219,     0,     0,   220,   221,   222,
     223,   224,   225,   226,     0,     0,     0,     0,     0,     0,
       0,     0,   227,   228,   303,   229,   215,   216,   217,     0,
       0,   218,   219,   215,     0,   220,   221,   222,   223,   224,
     225,   226,     0,   221,   222,   223,   224,   225,   226,     0,
     227,   228,     0,   229,     0,     0,     0,   227,   228,     0,
     229
};

static const yytype_int16 yycheck[] =
{
       1,    22,    51,    90,    18,    19,    36,   205,    47,   266,
      59,   236,    25,    27,   175,   176,   177,    60,    25,   334,
      69,    92,    26,    24,    43,   232,   113,   234,   253,    47,
      26,    69,   344,    43,    18,     3,    50,    69,     0,    77,
      43,    59,    11,    27,    93,    77,    73,    74,    72,    73,
      51,    70,    76,    72,   279,   367,    26,   372,    59,    60,
     131,    74,    72,    84,    71,    72,    73,    70,    69,    73,
      91,    92,   102,    25,   281,    73,   119,    73,   239,   240,
      46,    47,   103,    46,    47,    73,    75,    43,    76,    46,
      47,    76,    93,    59,     5,   320,    59,    73,   355,    43,
     325,    11,    59,    69,   125,   126,    25,    46,    47,    74,
     131,    67,    68,    76,    70,    74,   314,    45,   119,    76,
      59,   170,    76,    67,    68,    25,    70,    73,    74,   130,
      69,    46,    47,    75,   295,   296,    43,    44,    45,    77,
     301,    48,    49,    74,    59,    52,    53,    54,    55,    56,
      57,    58,     9,    27,    69,    12,    72,   171,    72,    73,
      67,    68,    76,    70,    72,    73,    72,    73,    25,   170,
      72,    78,   211,    43,   195,    76,   197,    71,    35,    36,
      37,    38,    39,    40,    41,    42,    56,    57,    58,   238,
     229,    72,    73,   354,    77,    78,   235,    67,    68,   360,
      70,    15,    16,    78,   205,    78,    69,   237,    77,    77,
      74,   298,    74,   300,    74,   302,   303,   266,    43,    44,
      45,    71,    71,    48,    49,    71,    71,    52,    53,    54,
      55,    56,    57,    58,    71,    73,    71,   238,    61,   240,
       5,   290,    67,    68,    12,    70,    75,    71,   297,   263,
      76,    72,    70,    78,    74,    77,    69,    25,    69,    75,
      75,    78,    71,    75,   351,   266,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    94,    75,   364,    71,   366,
      75,     5,   369,    71,    69,    75,   373,    59,    74,   290,
      69,    69,   111,    69,    71,    69,   297,   116,   117,   118,
      71,     4,   121,   122,   123,   124,   355,    27,    68,   128,
     129,   130,   131,   314,   117,    43,    44,    45,    91,   138,
      48,    49,    -1,   344,    52,    53,    54,    55,    56,    57,
      58,   138,    46,    47,   117,    -1,    -1,    -1,    -1,    67,
      68,    -1,    70,    -1,    -1,    59,   367,    -1,    -1,    -1,
      78,    43,    44,    45,   355,    69,    48,    49,    43,   178,
      52,    53,    54,    55,    56,    57,    58,    52,    53,    54,
      55,    56,    57,    58,   193,    67,    68,    25,    70,    -1,
     199,    -1,    67,    68,    76,    70,   205,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,    -1,    -1,
      -1,    -1,   231,    -1,   233,    -1,    -1,   236,    -1,    -1,
      -1,   240,    -1,    -1,    46,    47,    -1,    -1,    -1,    12,
      -1,    -1,   251,   252,   253,    -1,    -1,    59,   257,    -1,
       3,   260,    25,    -1,    -1,     8,   265,    69,    11,    32,
      -1,    -1,    35,    36,    37,    38,    39,    40,    41,    42,
     279,   280,    25,    26,    27,    -1,    -1,    -1,    31,    -1,
      33,    -1,    35,    36,    37,    38,    39,    40,    41,    42,
     299,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,
      53,    54,    -1,     8,    -1,   314,    11,    60,    61,    62,
      63,   320,    65,    -1,    67,    68,   325,    -1,    71,    72,
      25,    26,    27,    -1,    -1,    78,    31,    -1,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,     4,     5,
       6,     7,    -1,    -1,    10,    11,     3,    -1,    53,    54,
      -1,     8,    46,    47,    11,    60,    61,    62,    63,    -1,
      65,    -1,    67,    68,    12,    59,    71,    72,    25,    26,
      27,    -1,    -1,    78,    31,    69,    33,    25,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    53,    54,    -1,    -1,
      -1,    -1,    -1,    60,    61,    62,    63,    -1,    65,    -1,
      67,    68,     3,    -1,    71,    72,    -1,     8,    -1,    -1,
      11,    78,    13,    14,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    33,    -1,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    -1,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    -1,    65,    -1,    67,    68,     3,    -1,
      71,    72,    73,     8,    75,    76,    11,    -1,    13,    14,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    -1,
      65,    -1,    67,    68,     3,    -1,    71,    72,    73,     8,
      75,    76,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    25,    26,    27,    -1,
      -1,    -1,    31,    -1,    33,    -1,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,    -1,    53,    54,    -1,     8,    -1,    -1,
      11,    60,    61,    62,    63,    -1,    65,    -1,    67,    68,
      -1,    -1,    71,    72,    25,    26,    27,    76,    -1,    -1,
      31,    -1,    33,    -1,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    -1,    53,    54,    -1,     8,    -1,    -1,    11,    60,
      61,    62,    63,    -1,    65,    -1,    67,    68,    -1,    -1,
      71,    72,    25,    26,    27,    76,    -1,    -1,    31,    -1,
      33,    -1,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    54,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,
      63,    -1,    65,    -1,    67,    68,     3,    -1,    71,    72,
      -1,     8,    75,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,    26,
      27,    -1,    -1,    -1,    31,    -1,    33,    -1,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    -1,    -1,
      -1,    -1,    -1,    60,    61,    62,    63,    -1,    65,    -1,
      67,    68,     3,    -1,    71,    72,    73,     8,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    25,    26,    27,    -1,    -1,    -1,
      31,    -1,    33,    -1,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    -1,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    -1,    65,    -1,    67,    68,     3,    -1,
      71,    72,    73,     8,    -1,    -1,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    26,    27,    -1,    -1,    -1,    31,    -1,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    -1,
      65,    66,    67,    68,     3,    -1,    71,    72,    -1,     8,
      -1,    -1,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    25,    26,    27,    -1,
      -1,    -1,    31,    -1,    33,    -1,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,    -1,    53,    54,    -1,     8,    -1,    -1,
      11,    60,    61,    62,    63,    -1,    65,    -1,    67,    68,
      -1,    -1,    71,    72,    25,    26,    27,    -1,    -1,    -1,
      31,    -1,    33,    -1,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    -1,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    -1,    65,    66,    67,    68,     3,    -1,
      71,    72,    -1,     8,    -1,    -1,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    26,    27,    -1,    -1,    -1,    31,    -1,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    53,    54,
      -1,     8,    -1,    -1,    11,    60,    61,    62,    63,    -1,
      65,    -1,    67,    68,    -1,    -1,    71,    72,    25,    26,
      27,    -1,    -1,    -1,    31,    -1,    33,    -1,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    -1,    -1,
      -1,    -1,    -1,    60,    61,    62,    63,    -1,    65,    -1,
      67,    68,    69,    -1,    71,    72,     3,    -1,     5,    -1,
      -1,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,    26,
      27,    -1,    -1,    -1,    31,    -1,    33,    -1,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    -1,    53,    54,    -1,     8,
      -1,    -1,    11,    60,    61,    62,    63,    -1,    65,    -1,
      67,    68,    -1,    -1,    71,    72,    25,    26,    27,    -1,
      -1,    -1,    31,    -1,    33,    -1,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    54,    -1,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    -1,    65,    -1,    67,    68,
      -1,    -1,    71,    72,    43,    44,    45,    -1,    -1,    48,
      49,    -1,    -1,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,
      -1,    70,    43,    44,    45,    -1,    -1,    48,    49,    78,
      -1,    52,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    -1,    70,
      43,    44,    45,    -1,    -1,    48,    49,    78,    -1,    52,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    68,    -1,    70,    43,    44,
      45,    -1,    75,    48,    49,    -1,    -1,    52,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    68,    -1,    70,    43,    44,    45,    -1,
      75,    48,    49,    -1,    -1,    52,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    68,    -1,    70,    43,    44,    45,    74,    -1,    48,
      49,    -1,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    43,    44,    45,    -1,    -1,    48,    49,    -1,
      -1,    52,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,
      43,    44,    45,    -1,    -1,    48,    49,    -1,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    68,    -1,    70,    43,    44,
      45,    -1,    -1,    48,    49,    -1,    -1,    52,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    68,    69,    70,    43,    44,    45,    -1,
      -1,    48,    49,    43,    -1,    52,    53,    54,    55,    56,
      57,    58,    -1,    53,    54,    55,    56,    57,    58,    -1,
      67,    68,    -1,    70,    -1,    -1,    -1,    67,    68,    -1,
      70
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    80,    81,    82,    83,    25,    35,    36,    37,
      38,    39,    40,    41,    42,   144,     0,    83,    73,    74,
      85,     4,     6,     7,    10,    11,    86,    87,    88,    89,
      90,    95,    96,    97,   103,   104,   103,    25,   150,    26,
     142,    73,    91,   144,    75,    88,    76,     5,    11,    85,
      74,    74,    25,    92,    93,    94,    76,    25,   151,   103,
      12,   143,   144,   145,   146,   147,    45,    75,    77,    74,
     143,   144,   146,    43,    72,    72,    27,    94,    34,   143,
     149,    76,    78,    78,    71,    99,   100,   101,   102,   142,
      69,    77,    77,    74,    73,    76,   116,   101,   142,   100,
       9,   143,     3,     8,    13,    14,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    27,    28,    29,    30,    31,
      33,    53,    54,    60,    61,    62,    63,    65,    67,    68,
      71,    72,    76,    84,    97,    98,   103,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   116,   117,   118,
     121,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   141,   142,   144,   151,
      74,    74,    85,   142,    71,    71,    71,    71,    71,   121,
      74,   116,   121,   121,   130,   132,   121,   144,   146,   148,
     121,   121,   121,    73,   121,    73,   142,    73,   142,    61,
     121,   121,   121,   143,   144,    71,   100,   119,   121,   122,
     142,     5,    75,   107,    76,    43,    44,    45,    48,    49,
      52,    53,    54,    55,    56,    57,    58,    67,    68,    70,
      76,    72,    73,    72,    73,    70,    71,   103,    74,    66,
      71,   120,   121,   138,   139,   140,   120,   120,   120,   121,
      74,    72,    72,    73,   121,   142,   142,    73,   121,    69,
      69,   121,   122,    78,    78,    77,    74,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,    71,
      72,    73,   151,   121,   150,   121,   150,   151,   119,    85,
      32,   143,   120,   120,   121,    46,    47,    59,    69,    51,
      69,    76,    69,    69,   121,   121,   119,    75,    75,    75,
     121,   121,    69,   103,    71,   121,   149,   119,   121,   150,
      71,    78,    75,    78,    75,    71,    69,   143,    69,   120,
     120,   143,   116,   121,   116,   120,   116,   116,    78,    78,
      75,    75,     5,   122,    71,    69,    78,    75,   119,   119,
      15,    16,   115,   115,    76,    74,    69,    99,    69,    69,
      71,   116,   120,   149,    69,   120,    69,    71,   116,    69,
     116,    99,   116,    69,   115,   116
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
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (2)].opval), NULL, (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 10:
#line 123 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (4)].opval), NULL, (yyvsp[(4) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 11:
#line 129 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_class_block;
    ;}
    break;

  case 12:
#line 137 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 13:
#line 141 "yacc/spvm_yacc.y"
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

  case 14:
#line 153 "yacc/spvm_yacc.y"
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
#line 177 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 22:
#line 183 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 23:
#line 189 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_enum_block;
    ;}
    break;

  case 24:
#line 197 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 25:
#line 201 "yacc/spvm_yacc.y"
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

  case 26:
#line 214 "yacc/spvm_yacc.y"
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

  case 27:
#line 228 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 29:
#line 235 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 30:
#line 239 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 31:
#line 245 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_our(compiler, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 32:
#line 251 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_has(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(2) - (6)].opval), (yyvsp[(4) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 33:
#line 257 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (9)].opval), (yyvsp[(3) - (9)].opval), (yyvsp[(5) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(1) - (9)].opval), (yyvsp[(9) - (9)].opval), NULL);
     ;}
    break;

  case 34:
#line 261 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (9)].opval), (yyvsp[(3) - (9)].opval), (yyvsp[(5) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(1) - (9)].opval), NULL, NULL);
     ;}
    break;

  case 35:
#line 267 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (8)].opval), NULL, (yyvsp[(4) - (8)].opval), (yyvsp[(6) - (8)].opval), (yyvsp[(1) - (8)].opval), (yyvsp[(8) - (8)].opval), NULL);
     ;}
    break;

  case 36:
#line 271 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(5) - (11)].opval), NULL, (yyvsp[(7) - (11)].opval), (yyvsp[(9) - (11)].opval), (yyvsp[(4) - (11)].opval), (yyvsp[(11) - (11)].opval), (yyvsp[(2) - (11)].opval));
     ;}
    break;

  case 37:
#line 276 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 38:
#line 280 "yacc/spvm_yacc.y"
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

  case 39:
#line 291 "yacc/spvm_yacc.y"
    {
       // Add invocant to arguments
       SPVM_OP* op_args = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
       SPVM_OP_insert_child(compiler, op_args, op_args->last, (yyvsp[(1) - (1)].opval));
       
       (yyval.opval) = op_args;
    ;}
    break;

  case 40:
#line 299 "yacc/spvm_yacc.y"
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

  case 41:
#line 318 "yacc/spvm_yacc.y"
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

  case 42:
#line 332 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 44:
#line 339 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 45:
#line 345 "yacc/spvm_yacc.y"
    {
      SPVM_TYPE* type = SPVM_TYPE_new(compiler);
      type->is_self = 1;
      SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, (yyvsp[(3) - (3)].opval)->file, (yyvsp[(3) - (3)].opval)->line);
      
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), op_type);
    ;}
    break;

  case 46:
#line 355 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 47:
#line 359 "yacc/spvm_yacc.y"
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

  case 48:
#line 372 "yacc/spvm_yacc.y"
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

  case 50:
#line 389 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 51:
#line 393 "yacc/spvm_yacc.y"
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

  case 52:
#line 406 "yacc/spvm_yacc.y"
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

  case 63:
#line 434 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 64:
#line 438 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 65:
#line 442 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 66:
#line 448 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[(1) - (9)].opval), (yyvsp[(3) - (9)].opval), (yyvsp[(5) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(9) - (9)].opval));
    ;}
    break;

  case 67:
#line 454 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 68:
#line 460 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 69:
#line 466 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 71:
#line 475 "yacc/spvm_yacc.y"
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
#line 486 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (6)].opval)->file, (yyvsp[(1) - (6)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    ;}
    break;

  case 73:
#line 499 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 74:
#line 503 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (2)].opval);
    ;}
    break;

  case 75:
#line 507 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
    ;}
    break;

  case 76:
#line 513 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_block;
    ;}
    break;

  case 77:
#line 521 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 80:
#line 528 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 81:
#line 532 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 82:
#line 536 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 83:
#line 540 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 86:
#line 548 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 87:
#line 552 "yacc/spvm_yacc.y"
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

  case 92:
#line 569 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 94:
#line 576 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_constant(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 110:
#line 597 "yacc/spvm_yacc.y"
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
#line 611 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (5)].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[(1) - (5)].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (5)].opval)->file, (yyvsp[(1) - (5)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (5)].opval));
      }
      
      if ((yyvsp[(4) - (5)].opval)->id == SPVM_OP_C_ID_LIST) {
        SPVM_OP* op_term = (yyvsp[(4) - (5)].opval)->first;
        while ((op_term = SPVM_OP_sibling(compiler, op_term))) {
          SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term);
          SPVM_OP_insert_child(compiler, op_list, op_list->last, op_term);
          op_term = op_stab;
        }
      }
      else {
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(4) - (5)].opval));
      }
      
      (yyval.opval) = op_list;
    ;}
    break;

  case 112:
#line 636 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 113:
#line 640 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 114:
#line 644 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (1)].opval);
    ;}
    break;

  case 115:
#line 650 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 116:
#line 655 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEGATE, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op_negate, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 117:
#line 660 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unop(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 118:
#line 666 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_incdec(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 119:
#line 671 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_incdec(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 120:
#line 676 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_incdec(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 121:
#line 681 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_incdec(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 122:
#line 688 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 123:
#line 693 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 124:
#line 698 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_concat(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 125:
#line 702 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 126:
#line 706 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 127:
#line 710 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 128:
#line 714 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 129:
#line 718 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 130:
#line 722 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 131:
#line 726 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 132:
#line 730 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 133:
#line 736 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 134:
#line 740 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_special_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 135:
#line 746 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 136:
#line 750 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 137:
#line 754 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 138:
#line 758 "yacc/spvm_yacc.y"
    {
      // New
      SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);

      (yyval.opval) = SPVM_OP_build_new(compiler, op_new, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 139:
#line 765 "yacc/spvm_yacc.y"
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
      
      (yyval.opval) = SPVM_OP_build_new(compiler, op_new, op_package, NULL);
    ;}
    break;

  case 140:
#line 784 "yacc/spvm_yacc.y"
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
      
      (yyval.opval) = SPVM_OP_build_new(compiler, op_new, op_package, NULL);
    ;}
    break;

  case 141:
#line 805 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 142:
#line 812 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, (yyvsp[(2) - (4)].opval)->file, (yyvsp[(2) - (4)].opval)->line);
      (yyval.opval) = SPVM_OP_build_convert(compiler, op_convert, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 143:
#line 819 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 144:
#line 823 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 145:
#line 827 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 146:
#line 833 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, NULL, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 147:
#line 837 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 148:
#line 841 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_normal_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_normal_terms);
    ;}
    break;

  case 149:
#line 846 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 150:
#line 850 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_normal_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_normal_terms);
    ;}
    break;

  case 151:
#line 855 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[(2) - (5)].opval)->file, (yyvsp[(2) - (5)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (5)].opval), op_sub_name, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 152:
#line 862 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 153:
#line 866 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 154:
#line 870 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 155:
#line 876 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 156:
#line 882 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_weaken_array_element(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 157:
#line 888 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 158:
#line 893 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 159:
#line 898 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 160:
#line 903 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 161:
#line 910 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_deref(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 162:
#line 914 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_deref(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 163:
#line 920 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_ref(compiler, op_ref, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 164:
#line 925 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, (yyvsp[(1) - (4)].opval)->file, (yyvsp[(1) - (4)].opval)->line);
      (yyval.opval) = SPVM_OP_build_ref(compiler, op_ref, (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 165:
#line 932 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 166:
#line 938 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 167:
#line 944 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_or(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 168:
#line 948 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_and(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 169:
#line 952 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_not(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 170:
#line 958 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval), 0);
    ;}
    break;

  case 171:
#line 962 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL, 0);
    ;}
    break;

  case 172:
#line 966 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(5) - (5)].opval), 1);
    ;}
    break;

  case 173:
#line 972 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 178:
#line 984 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 179:
#line 988 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_byte_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 180:
#line 994 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_short_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 181:
#line 1000 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 182:
#line 1006 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_long_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 183:
#line 1012 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_float_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 184:
#line 1018 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_double_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 185:
#line 1024 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_any_object_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 186:
#line 1030 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_string_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 187:
#line 1038 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 188:
#line 1044 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 189:
#line 1048 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 190:
#line 1054 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_const_array_type(compiler, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 191:
#line 1060 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 192:
#line 1064 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 194:
#line 1071 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3339 "spvm_yacc.tab.c"
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


#line 1078 "yacc/spvm_yacc.y"


