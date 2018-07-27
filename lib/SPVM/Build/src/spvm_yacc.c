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
     REF = 283,
     ISA = 284,
     SWITCH = 285,
     CASE = 286,
     DEFAULT = 287,
     EVAL = 288,
     WEAKEN = 289,
     PRECOMPILE = 290,
     DEREF = 291,
     UNDEF = 292,
     VOID = 293,
     BYTE = 294,
     SHORT = 295,
     INT = 296,
     LONG = 297,
     FLOAT = 298,
     DOUBLE = 299,
     STRING = 300,
     OBJECT = 301,
     BYTE_REF = 302,
     SHORT_REF = 303,
     INT_REF = 304,
     LONG_REF = 305,
     FLOAT_REF = 306,
     DOUBLE_REF = 307,
     SPECIAL_ASSIGN = 308,
     ASSIGN = 309,
     OR = 310,
     AND = 311,
     BIT_XOR = 312,
     BIT_OR = 313,
     BIT_AND = 314,
     REL = 315,
     SHIFT = 316,
     REMAINDER = 317,
     DIVIDE = 318,
     MULTIPLY = 319,
     UMINUS = 320,
     SCALAR = 321,
     NOT = 322,
     DEC = 323,
     INC = 324,
     ARROW = 325
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
#define REF 283
#define ISA 284
#define SWITCH 285
#define CASE 286
#define DEFAULT 287
#define EVAL 288
#define WEAKEN 289
#define PRECOMPILE 290
#define DEREF 291
#define UNDEF 292
#define VOID 293
#define BYTE 294
#define SHORT 295
#define INT 296
#define LONG 297
#define FLOAT 298
#define DOUBLE 299
#define STRING 300
#define OBJECT 301
#define BYTE_REF 302
#define SHORT_REF 303
#define INT_REF 304
#define LONG_REF 305
#define FLOAT_REF 306
#define DOUBLE_REF 307
#define SPECIAL_ASSIGN 308
#define ASSIGN 309
#define OR 310
#define AND 311
#define BIT_XOR 312
#define BIT_OR 313
#define BIT_AND 314
#define REL 315
#define SHIFT 316
#define REMAINDER 317
#define DIVIDE 318
#define MULTIPLY 319
#define UMINUS 320
#define SCALAR 321
#define NOT 322
#define DEC 323
#define INC 324
#define ARROW 325




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
#line 268 "spvm_yacc.tab.c"

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
#define YYLAST   1349

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  72
/* YYNRULES -- Number of rules.  */
#define YYNRULES  194
/* YYNRULES -- Number of states.  */
#define YYNSTATES  358

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   325

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      78,    76,     2,    63,    82,    64,    65,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    83,    53,
       2,     2,     2,     2,    70,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    79,     2,    84,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    80,     2,    81,    69,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    66,    67,    68,
      71,    72,    73,    74,    75,    77
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
      95,    97,    99,   101,   105,   108,   111,   113,   115,   117,
     126,   132,   138,   142,   145,   152,   153,   156,   163,   170,
     180,   190,   199,   208,   211,   216,   219,   224,   225,   227,
     231,   235,   238,   240,   242,   246,   249,   254,   258,   264,
     267,   272,   274,   276,   278,   280,   284,   286,   288,   290,
     292,   294,   296,   298,   300,   302,   304,   306,   308,   310,
     312,   314,   316,   318,   321,   323,   326,   330,   334,   336,
     340,   343,   346,   352,   354,   356,   360,   365,   371,   376,
     381,   384,   387,   390,   393,   396,   399,   402,   405,   409,
     413,   417,   421,   425,   429,   433,   437,   441,   445,   449,
     453,   457,   461,   465,   469,   473,   476,   482,   487,   492,
     497,   504,   508,   515,   519,   525,   526,   528,   530,   534,
     538,   541,   543,   547,   551,   552,   555,   556,   558,   561,
     563,   565,   567,   569,   571,   573,   575,   577,   579,   581,
     583,   585,   587,   591,   595,   598,   603,   608,   610,   612,
     614,   616,   618,   621,   626
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      86,     0,    -1,    87,    -1,    -1,    88,    -1,    88,    89,
      -1,    89,    -1,    91,    -1,    13,   148,    53,    -1,     6,
     148,   144,    96,    -1,     6,   144,    96,    -1,    -1,    94,
      -1,    94,    95,    -1,    95,    -1,   114,    -1,   115,    -1,
     117,    -1,   119,    53,    -1,    90,    -1,   116,    -1,    80,
      93,    81,    -1,    80,    98,    81,    -1,    -1,    99,    -1,
      99,    82,   100,    -1,    99,    82,    -1,   100,    -1,    20,
      -1,    20,    55,    21,    -1,    -1,   102,    -1,   102,   103,
      -1,   103,    -1,   105,    -1,   112,    -1,   107,    -1,   108,
      -1,   104,    -1,   109,    -1,   110,    -1,   111,    -1,   156,
      -1,    80,   101,    81,    -1,   126,    53,    -1,   127,    53,
      -1,    53,    -1,   126,    -1,   127,    -1,    11,    78,   105,
     125,    53,   106,    76,   104,    -1,    12,    78,   125,    76,
     104,    -1,    30,    78,   126,    76,   104,    -1,    31,   126,
      83,    -1,    32,    83,    -1,     7,    78,   125,    76,   104,
     113,    -1,    -1,     9,   104,    -1,     8,    78,   125,    76,
     104,   113,    -1,     4,   153,    83,   145,   147,    53,    -1,
     145,     5,   154,    83,   152,    78,   140,    76,   104,    -1,
     145,     5,   154,    83,   152,    78,   140,    76,    53,    -1,
     145,     5,    83,   152,    78,   140,    76,   104,    -1,   145,
       5,    83,   152,    78,   140,    76,    53,    -1,    22,    97,
      -1,     3,   155,    83,   147,    -1,     3,   155,    -1,    15,
     155,    83,   147,    -1,    -1,   121,    -1,   121,    82,   126,
      -1,   121,    82,   122,    -1,   121,    82,    -1,   122,    -1,
     126,    -1,    78,   121,    76,    -1,    70,   126,    -1,    70,
      80,   126,    81,    -1,    72,    70,   126,    -1,    72,    70,
      80,   126,    81,    -1,    36,   155,    -1,    36,    80,   155,
      81,    -1,   126,    -1,   136,    -1,   137,    -1,   128,    -1,
      78,   125,    76,    -1,   155,    -1,    21,    -1,    37,    -1,
     139,    -1,   132,    -1,   138,    -1,   131,    -1,   129,    -1,
     130,    -1,   123,    -1,   118,    -1,   135,    -1,   134,    -1,
     124,    -1,    18,    -1,    19,    -1,    10,    -1,    10,   126,
      -1,    25,    -1,    25,   126,    -1,   132,    55,   126,    -1,
     138,    55,   126,    -1,   133,    -1,   125,    29,   147,    -1,
      14,   148,    -1,    14,   151,    -1,    14,   149,    80,   120,
      81,    -1,    92,    -1,   116,    -1,    79,   120,    84,    -1,
      78,   147,    76,   126,    -1,   126,    77,    80,   153,    81,
      -1,   132,    80,   153,    81,    -1,   138,    80,   153,    81,
      -1,    34,   132,    -1,    63,   126,    -1,    64,   126,    -1,
      75,   126,    -1,   126,    75,    -1,    74,   126,    -1,   126,
      74,    -1,    69,   126,    -1,   126,    63,   126,    -1,   126,
      64,   126,    -1,   126,    65,   126,    -1,   126,    68,   126,
      -1,   126,    67,   126,    -1,   126,    66,   126,    -1,   126,
      58,   126,    -1,   126,    60,   126,    -1,   126,    59,   126,
      -1,   126,    62,   126,    -1,   118,    55,   126,    -1,   155,
      55,   126,    -1,   155,    54,   126,    -1,    78,   126,    76,
      -1,   126,    61,   126,    -1,   125,    56,   125,    -1,   125,
      57,   125,    -1,    73,   125,    -1,   126,    77,    79,   126,
      84,    -1,   138,    79,   126,    84,    -1,   132,    79,   126,
      84,    -1,   154,    78,   120,    76,    -1,   148,    77,   154,
      78,   120,    76,    -1,   148,    77,   154,    -1,   126,    77,
     154,    78,   120,    76,    -1,   126,    77,   154,    -1,   126,
      77,    78,   120,    76,    -1,    -1,   141,    -1,   143,    -1,
     143,    82,   141,    -1,   141,    82,   142,    -1,   141,    82,
      -1,   142,    -1,   155,    83,   147,    -1,   155,    83,    16,
      -1,    -1,    83,   146,    -1,    -1,   146,    -1,   146,    23,
      -1,    23,    -1,   148,    -1,   149,    -1,   150,    -1,    20,
      -1,    39,    -1,    40,    -1,    41,    -1,    42,    -1,    43,
      -1,    44,    -1,    46,    -1,    45,    -1,   148,    79,    84,
      -1,   149,    79,    84,    -1,    17,   149,    -1,   148,    79,
     126,    84,    -1,   149,    79,   126,    84,    -1,   147,    -1,
      38,    -1,    20,    -1,    20,    -1,    26,    -1,    28,   155,
      -1,    28,    80,   155,    81,    -1,    33,   104,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    54,    54,    63,    66,    79,    93,    96,    99,   105,
     111,   118,   121,   133,   147,   150,   151,   152,   153,   154,
     155,   158,   166,   175,   178,   191,   205,   209,   212,   216,
     223,   226,   239,   253,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   267,   275,   276,   277,   283,   284,   287,
     293,   299,   305,   311,   314,   328,   331,   335,   341,   347,
     351,   357,   362,   369,   375,   379,   385,   392,   395,   408,
     422,   447,   451,   455,   461,   467,   472,   477,   482,   489,
     493,   499,   500,   501,   502,   503,   509,   510,   514,   515,
     516,   517,   518,   519,   520,   521,   522,   523,   524,   525,
     528,   529,   530,   533,   537,   541,   545,   549,   553,   556,
     562,   566,   570,   574,   581,   602,   609,   616,   620,   624,
     630,   636,   641,   646,   651,   656,   661,   666,   672,   677,
     682,   686,   690,   694,   698,   702,   706,   710,   714,   718,
     722,   726,   732,   738,   742,   746,   752,   756,   760,   766,
     770,   774,   779,   783,   788,   796,   799,   810,   818,   837,
     851,   855,   858,   864,   871,   874,   888,   891,   904,   918,
     921,   922,   923,   926,   930,   937,   944,   951,   958,   965,
     972,   979,   988,   992,   998,  1004,  1008,  1015,  1016,  1021,
    1022,  1025,  1029,  1033,  1039
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
  "CORETYPE", "CROAK", "VAR_NAME", "INTERFACE", "REF", "ISA", "SWITCH",
  "CASE", "DEFAULT", "EVAL", "WEAKEN", "PRECOMPILE", "DEREF", "UNDEF",
  "VOID", "BYTE", "SHORT", "INT", "LONG", "FLOAT", "DOUBLE", "STRING",
  "OBJECT", "BYTE_REF", "SHORT_REF", "INT_REF", "LONG_REF", "FLOAT_REF",
  "DOUBLE_REF", "';'", "SPECIAL_ASSIGN", "ASSIGN", "OR", "AND", "BIT_XOR",
  "BIT_OR", "BIT_AND", "REL", "SHIFT", "'+'", "'-'", "'.'", "REMAINDER",
  "DIVIDE", "MULTIPLY", "'~'", "'@'", "UMINUS", "SCALAR", "NOT", "DEC",
  "INC", "')'", "ARROW", "'('", "'['", "'{'", "'}'", "','", "':'", "']'",
  "$accept", "grammar", "opt_declarations_in_grammar",
  "declarations_in_grammar", "declaration_in_grammar", "use", "package",
  "anon_package", "opt_declarations_in_package", "declarations_in_package",
  "declaration_in_package", "package_block", "enumeration_block",
  "opt_enumeration_values", "enumeration_values", "enumeration_value",
  "opt_statements", "statements", "statement", "block", "normal_statement",
  "normal_statement_for_end", "for_statement", "while_statement",
  "switch_statement", "case_statement", "default_statement",
  "if_statement", "else_statement", "field", "sub", "anon_sub",
  "enumeration", "my_var", "package_var", "opt_assignable_terms",
  "assignable_terms", "list_assignable_terms", "array_length", "deref",
  "term", "assignable_term", "expression", "isa", "new_object",
  "array_init", "convert_type", "field_access", "weaken_field", "unop",
  "binop", "relative_term", "logical_term", "array_access", "call_sub",
  "opt_args", "args", "arg", "invocant", "opt_colon_descriptors",
  "opt_descriptors", "descriptors", "type", "basic_type", "array_type",
  "const_array_type", "array_type_with_length", "type_or_void",
  "field_name", "sub_name", "var", "eval_block", 0
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
     305,   306,   307,    59,   308,   309,   310,   311,   312,   313,
     314,   315,   316,    43,    45,    46,   317,   318,   319,   126,
      64,   320,   321,   322,   323,   324,    41,   325,    40,    91,
     123,   125,    44,    58,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    87,    87,    88,    88,    89,    90,    91,
      92,    93,    93,    94,    94,    95,    95,    95,    95,    95,
      95,    96,    97,    98,    98,    99,    99,    99,   100,   100,
     101,   101,   102,   102,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   104,   105,   105,   105,   106,   106,   107,
     108,   109,   110,   111,   112,   113,   113,   113,   114,   115,
     115,   116,   116,   117,   118,   118,   119,   120,   120,   121,
     121,   121,   121,   121,   122,   123,   123,   123,   123,   124,
     124,   125,   125,   125,   125,   125,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   128,
     129,   129,   129,   129,   129,   130,   131,   132,   132,   132,
     133,   134,   134,   134,   134,   134,   134,   134,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   136,   137,   137,   137,   138,   138,   138,   139,
     139,   139,   139,   139,   139,   140,   140,   140,   140,   141,
     141,   141,   142,   143,   144,   144,   145,   145,   146,   146,
     147,   147,   147,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   149,   149,   150,   151,   151,   152,   152,   153,
     154,   155,   155,   155,   156
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     3,     4,
       3,     0,     1,     2,     1,     1,     1,     1,     2,     1,
       1,     3,     3,     0,     1,     3,     2,     1,     1,     3,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     2,     2,     1,     1,     1,     8,
       5,     5,     3,     2,     6,     0,     2,     6,     6,     9,
       9,     8,     8,     2,     4,     2,     4,     0,     1,     3,
       3,     2,     1,     1,     3,     2,     4,     3,     5,     2,
       4,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     2,     3,     3,     1,     3,
       2,     2,     5,     1,     1,     3,     4,     5,     4,     4,
       2,     2,     2,     2,     2,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     5,     4,     4,     4,
       6,     3,     6,     3,     5,     0,     1,     1,     3,     3,
       2,     1,     3,     3,     0,     2,     0,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     2,     4,     4,     1,     1,     1,
       1,     1,     2,     4,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     2,     4,     6,     7,   173,   174,   175,
     176,   177,   178,   179,   181,   180,   164,     1,     5,     0,
       0,   169,   165,    11,     9,   168,     0,     0,     0,     0,
      19,     0,    12,    14,    15,    16,    20,    17,     0,     0,
     167,   189,     0,     0,   191,     0,     0,    23,    63,    21,
      13,    18,     0,   166,     8,     0,   192,     0,    28,     0,
      24,    27,   190,     0,     0,     0,     0,     0,    66,   170,
     171,   172,     0,    22,    26,   188,   187,     0,     0,     0,
     193,     0,   184,     0,     0,    29,    25,   155,     0,    58,
     182,   183,     0,   156,   161,   157,     0,   155,     0,   160,
       0,     0,     0,    62,    30,    61,   159,     0,   158,   163,
     162,     0,     0,   164,     0,   102,     0,     0,     0,   100,
     101,   173,    87,   104,     0,   166,     0,     0,   166,     0,
      88,    46,   166,   166,   166,   166,     0,   166,   166,   166,
      67,   113,     0,    31,    33,    38,    34,    36,    37,    39,
      40,    41,    35,   114,    96,    95,    99,     0,     0,    93,
      94,    92,    90,   108,    98,    97,    91,    89,     0,     0,
       0,    86,    42,     0,    60,    59,    65,     0,   166,   103,
      90,    91,   166,   166,   110,     0,   111,   105,   166,     0,
      53,   194,     0,    90,     0,    79,   121,   122,   127,   166,
      75,   166,   125,   123,     0,     0,   170,   166,     0,    68,
      72,    73,    43,    32,   166,    44,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   126,   124,     0,    45,
     166,   166,     0,   166,   166,     0,     0,     0,    67,   166,
     166,     0,    10,   166,   166,     0,    81,    84,    82,    83,
     166,     0,   166,   166,    67,     0,    52,     0,     0,   166,
      77,   141,   166,     0,    73,   115,    71,   138,   134,   136,
     135,   137,   128,   129,   130,   133,   132,   131,    67,   166,
       0,   153,   106,     0,     0,   107,     0,     0,   151,     0,
     140,   139,    64,   145,     0,    81,     0,   166,   166,     0,
     166,     0,     0,     0,     0,     0,     0,    80,    76,     0,
     116,    74,    70,    69,     0,     0,     0,    67,   148,   118,
     147,   119,    67,   149,    85,   109,   143,   144,    55,   142,
     166,    50,   185,   186,   112,    51,    78,   154,   146,   117,
       0,     0,     0,     0,    54,     0,    47,    48,   152,   150,
     166,    56,     0,     0,    49,     0,    55,    57
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    30,     6,   141,    31,    32,
      33,    24,    48,    59,    60,    61,   142,   143,   144,   145,
     146,   345,   147,   148,   149,   150,   151,   152,   344,    34,
      35,   153,    37,   154,    38,   208,   209,   210,   155,   156,
     245,   246,   158,   247,   159,   160,   161,   180,   163,   164,
     165,   248,   249,   181,   167,    92,    93,    94,    95,    20,
     168,    40,   205,   169,    70,    71,   186,    77,    42,   170,
     171,   172
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -221
static const yytype_int16 yypact[] =
{
      41,   208,    16,  -221,    41,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,  -221,  -221,  -221,  -221,   -54,  -221,  -221,    38,
      -4,  -221,    57,   140,  -221,  -221,    96,   208,    10,    39,
    -221,    40,   140,  -221,  -221,  -221,  -221,  -221,    81,   132,
      57,  -221,    63,    98,  -221,    -8,    71,   141,  -221,  -221,
    -221,  -221,   -16,    38,  -221,    10,  -221,   582,   112,    87,
      88,  -221,  -221,   329,    86,   582,    90,   208,  -221,    95,
     108,  -221,   167,  -221,   141,  -221,  -221,   113,   329,   143,
    -221,    95,   108,   116,   117,  -221,  -221,    10,   126,  -221,
    -221,  -221,   131,   128,  -221,   133,   125,    10,   -21,    10,
      10,   270,   138,  -221,   399,  -221,  -221,   136,   128,  -221,
    -221,    -5,    10,   -54,   142,   744,   144,   145,   208,  -221,
    -221,   146,  -221,   744,   148,   998,   147,   152,   998,    -7,
    -221,  -221,   998,   998,   998,   444,   157,   998,   998,   789,
     834,  -221,   135,   399,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,  -221,  -221,   178,  -221,  -221,  1161,   181,  -221,
    -221,  -221,    35,  -221,  -221,  -221,    53,  -221,   230,   159,
     161,   -15,  -221,   582,  -221,  -221,   162,    -4,   879,  1241,
      32,    45,   567,   879,   163,    70,  -221,  1241,   998,  1135,
    -221,  -221,  1241,    60,    10,  -221,   -25,   -25,   -25,   998,
     -25,   489,    82,    82,   870,   168,   -24,   953,   172,   175,
    -221,  1241,  -221,  -221,   998,  -221,   998,   998,   998,   998,
     998,   998,   998,   998,   998,   998,  -221,  -221,    -9,  -221,
     998,   998,    96,   998,   998,    96,   179,   241,   834,   998,
     998,   582,  -221,   879,   682,   -22,   989,  -221,  -221,  -221,
     879,    29,   257,   319,   834,  1221,  -221,   186,  1181,   998,
     -25,  -221,   998,   -45,   870,  -221,   834,  1241,  1257,  1257,
     667,  1272,   198,   198,   198,   -25,   -25,   -25,   834,   998,
      96,   190,  1241,  1020,   188,  1241,  1043,   189,   196,   203,
    1241,  1241,  -221,   253,    50,   480,   582,   879,   879,   152,
     998,    74,   152,  1066,  1089,   207,   152,  -221,  -221,  1201,
     214,  -221,  -221,  1241,   216,  1112,   223,   834,  -221,  -221,
    -221,  -221,   834,  -221,  -221,  -221,   -12,   253,   156,  1241,
     637,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
     229,   231,   206,   152,  -221,   232,  1241,  -221,  -221,  -221,
     879,  -221,   152,    72,  -221,   152,   156,  -221
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -221,  -221,  -221,  -221,   302,  -221,  -221,  -221,  -221,  -221,
     285,   151,  -221,  -221,  -221,   244,  -221,  -221,   176,   -97,
     155,  -221,  -221,  -221,  -221,  -221,  -221,  -221,   -33,  -221,
    -221,     1,  -221,  -221,  -221,  -213,   123,    58,  -221,  -221,
    -155,   -41,     4,  -221,  -221,  -221,  -221,  -101,  -221,  -221,
    -221,  -221,  -221,   -99,  -221,   246,   238,   245,  -221,   235,
     -10,   331,   -55,    -1,   -61,  -221,  -221,   273,  -220,   -43,
      23,  -221
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -191
static const yytype_int16 yytable[] =
{
      16,   105,    68,   162,    62,   166,    82,   296,    76,    64,
      79,    62,   284,    39,   175,   287,    17,   296,    44,    44,
      45,    45,    39,    76,    36,   289,    43,   193,   251,    19,
     191,   311,   103,    36,   297,   298,    44,   266,    45,   239,
     240,   305,   162,    65,   166,   298,   110,     1,   174,   226,
     227,    46,   228,   237,   299,    83,    69,   185,   296,   104,
     316,    21,    69,   157,    69,   314,    81,    63,    56,   278,
     279,   280,    55,   194,   179,   104,    23,    69,    66,   296,
      25,   162,   187,   166,   189,   297,   298,   192,   293,   294,
     230,   196,   197,   198,   200,   301,   202,   203,   204,   211,
      69,   296,   157,   296,   340,   302,   297,   298,   233,   341,
      96,   231,   232,  -120,   231,   232,    41,   184,   110,    47,
      96,    49,   107,   107,   234,   235,   324,   330,   297,   298,
     297,   298,   234,   235,    51,   176,  -120,    52,   206,   231,
     232,   157,   326,   327,    26,  -166,    53,   255,   355,   253,
     254,    54,   195,    27,    57,    28,  -191,  -191,   258,   228,
     260,    58,    29,    21,   342,   343,   264,    72,    73,    78,
      74,    80,    69,   267,    83,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   281,   292,    84,    85,   282,
     283,    87,   285,   286,   288,   353,    89,   211,   290,   291,
      90,    91,   328,   295,    97,   331,   206,    98,   101,   335,
      99,   303,   304,   211,   111,   100,   212,   257,   309,   173,
     178,   310,   182,   183,  -190,   313,   188,   201,     7,   162,
     190,   166,   104,   214,   229,   236,   237,   211,   315,   238,
      69,   325,   252,   206,   262,   241,   351,     8,     9,    10,
      11,    12,    13,    14,    15,   354,   265,   266,   356,   329,
     112,    62,    63,   113,   223,   224,   225,   307,   317,   319,
     321,   118,   226,   227,   322,   228,   211,   121,   122,   323,
      21,   211,   296,    44,   350,    45,   109,    67,   334,   346,
       7,   228,   337,   129,   130,    69,     8,     9,    10,    11,
      12,    13,    14,    15,   339,   348,    18,   349,   352,     8,
       9,    10,    11,    12,    13,    14,    15,    50,    86,   213,
     132,   133,   112,   357,   312,   113,   134,   135,   242,   136,
     263,   137,   138,   118,   347,   139,   140,   250,   108,   121,
     122,    90,    21,   102,   106,    44,    67,    45,   177,     7,
      22,    88,     0,     0,     0,   129,   130,     0,     8,     9,
      10,    11,    12,    13,    14,    15,     0,    75,     8,     9,
      10,    11,    12,    13,    14,    15,     0,     0,     0,     0,
       0,     0,   132,   133,     0,     0,     0,     0,   134,   135,
       0,   136,     0,   137,   138,     0,     0,   139,   140,     0,
       0,     0,   112,    91,  -166,   113,   114,     0,     0,   115,
     116,   117,     0,   118,     0,     0,     0,   119,   120,   121,
     122,     0,    21,     0,   123,    44,     0,    45,     0,   124,
     125,   126,   127,   128,     0,   129,   130,     0,     8,     9,
      10,    11,    12,    13,    14,    15,     0,   112,     0,     0,
     113,     0,   131,     0,     0,     0,     0,     0,   118,     0,
       0,     0,   132,   133,   121,   122,     0,    21,   134,   135,
      44,   136,    45,   137,   138,     0,     0,   139,   140,   104,
     129,   130,     0,     8,     9,    10,    11,    12,    13,    14,
      15,     0,   112,     0,     0,   113,     0,     0,     0,     0,
       0,     0,     0,   118,     0,     0,     0,   132,   133,   121,
     122,     0,    21,   134,   135,    44,   136,    45,   137,   138,
       0,     0,   139,   140,   199,   129,   130,     0,     8,     9,
      10,    11,    12,    13,    14,    15,     0,     0,   216,   217,
     218,   300,   219,   220,   221,   222,   223,   224,   225,     0,
       0,     0,   132,   133,   226,   227,   261,   228,   134,   135,
       0,   136,     0,   137,   138,     0,     0,   139,   140,   259,
     112,     0,     0,   113,     0,     0,     0,   115,     0,     0,
       0,   118,     0,     0,     0,   119,   120,   121,   122,     0,
      21,     0,   123,    44,     0,    45,     0,     0,     0,    67,
       0,   128,     7,   129,   130,     0,     8,     9,    10,    11,
      12,    13,    14,    15,     0,     0,     0,     0,     0,     0,
     131,     8,     9,    10,    11,    12,    13,    14,    15,     0,
     132,   133,     0,     0,     0,     0,   134,   135,     0,   136,
     112,   137,   138,   113,     0,   139,   140,   115,     0,     0,
       0,   118,     0,     0,     0,   119,   120,   121,   122,     0,
      21,     0,   123,    44,     0,    45,     0,     0,     0,     0,
       0,   128,     0,   129,   130,     0,     8,     9,    10,    11,
      12,    13,    14,    15,     0,   112,     0,     0,   113,     0,
       0,     0,     0,     0,     0,     0,   118,     0,     0,    67,
     132,   133,   121,   122,     0,    21,   134,   135,    44,   136,
      45,   137,   138,     0,     0,   139,   140,     0,   129,   130,
       0,     8,     9,    10,    11,    12,    13,    14,    15,   219,
     220,   221,   222,   223,   224,   225,     0,     0,     0,     0,
       0,   226,   227,     0,   228,   132,   133,   112,     0,  -166,
     113,   134,   135,     0,   136,   243,   137,   138,   118,     0,
     244,   140,     0,     0,   121,   122,     0,    21,     0,     0,
      44,     0,    45,     0,     0,     0,     0,     0,     0,     0,
     129,   130,     0,     8,     9,    10,    11,    12,    13,    14,
      15,     0,   112,     0,     0,   113,     0,     0,     0,     0,
       0,     0,     0,   118,     0,     0,    67,   132,   133,   121,
     122,     0,    21,   134,   135,    44,   136,    45,   137,   138,
       0,     0,   139,   140,     0,   129,   130,     0,     8,     9,
      10,    11,    12,    13,    14,    15,     0,   112,     0,  -166,
     113,     0,     0,     0,     0,     0,     0,     0,   118,     0,
       0,     0,   132,   133,   121,   122,     0,    21,   134,   135,
      44,   136,    45,   137,   138,     0,     0,   139,   140,     0,
     129,   130,     0,     8,     9,    10,    11,    12,    13,    14,
      15,     0,   112,     0,     0,   113,     0,     0,     0,     0,
       0,     0,     0,   118,     0,     0,     0,   132,   133,   121,
     122,     0,    21,   134,   135,    44,   136,    45,   137,   138,
       0,     0,   207,   140,     0,   129,   130,     0,     8,     9,
      10,    11,    12,    13,    14,    15,     0,     0,   216,   217,
     218,     0,   219,   220,   221,   222,   223,   224,   225,     0,
       0,     0,   132,   133,   226,   227,   261,   228,   134,   135,
       0,   136,   243,   137,   138,     0,   112,   244,   140,   113,
       0,     0,     0,     0,     0,     0,     0,   118,     0,     0,
      67,     0,     0,   121,   122,     0,    21,     0,     0,    44,
       0,    45,     0,     0,     0,     0,     0,     0,     0,   129,
     130,     0,     8,     9,    10,    11,    12,    13,    14,    15,
       0,   112,     0,     0,   113,     0,     0,     0,     0,     0,
       0,     0,   118,     0,     0,     0,   132,   133,   121,   122,
       0,    21,   134,   135,    44,   136,    45,   137,   138,     0,
       0,   207,   140,     0,   129,   130,     0,     8,     9,    10,
      11,    12,    13,    14,    15,     0,     0,   216,   217,   218,
     300,   219,   220,   221,   222,   223,   224,   225,     0,     0,
       0,   132,   133,   226,   227,     0,   228,   134,   135,     0,
     136,     0,   137,   138,     0,     0,   139,   140,   216,   217,
     218,     0,   219,   220,   221,   222,   223,   224,   225,     0,
       0,     0,     0,     0,   226,   227,     0,   228,     0,     0,
       0,   216,   217,   218,   318,   219,   220,   221,   222,   223,
     224,   225,     0,     0,     0,     0,     0,   226,   227,     0,
     228,     0,     0,     0,   216,   217,   218,   320,   219,   220,
     221,   222,   223,   224,   225,     0,     0,     0,     0,     0,
     226,   227,     0,   228,     0,     0,     0,   216,   217,   218,
     332,   219,   220,   221,   222,   223,   224,   225,     0,     0,
       0,     0,     0,   226,   227,     0,   228,     0,     0,     0,
     216,   217,   218,   333,   219,   220,   221,   222,   223,   224,
     225,     0,     0,     0,     0,     0,   226,   227,     0,   228,
       0,     0,     0,   216,   217,   218,   338,   219,   220,   221,
     222,   223,   224,   225,     0,     0,     0,     0,     0,   226,
     227,     0,   228,     0,   215,     0,     0,     0,   256,   216,
     217,   218,     0,   219,   220,   221,   222,   223,   224,   225,
       0,     0,     0,     0,     0,   226,   227,     0,   228,   216,
     217,   218,     0,   219,   220,   221,   222,   223,   224,   225,
       0,     0,     0,     0,     0,   226,   227,     0,   228,   216,
     217,   218,   308,   219,   220,   221,   222,   223,   224,   225,
       0,     0,     0,     0,     0,   226,   227,     0,   228,   216,
     217,   218,   336,   219,   220,   221,   222,   223,   224,   225,
       0,     0,     0,     0,     0,   226,   227,   306,   228,   216,
     217,   218,     0,   219,   220,   221,   222,   223,   224,   225,
       0,     0,     0,     0,     0,   226,   227,   218,   228,   219,
     220,   221,   222,   223,   224,   225,     0,     0,     0,     0,
       0,   226,   227,     0,   228,   220,   221,   222,   223,   224,
     225,     0,     0,     0,     0,     0,   226,   227,     0,   228
};

static const yytype_int16 yycheck[] =
{
       1,    98,    57,   104,    20,   104,    67,    29,    63,    52,
      65,    20,   232,    23,   111,   235,     0,    29,    26,    26,
      28,    28,    32,    78,    23,   238,    27,   128,   183,    83,
     127,    76,    53,    32,    56,    57,    26,    82,    28,    54,
      55,   254,   143,    53,   143,    57,   101,     6,    53,    74,
      75,    28,    77,    77,    76,    79,    57,   118,    29,    80,
     280,    23,    63,   104,    65,   278,    67,    83,    45,    78,
      79,    80,    80,    80,   115,    80,    80,    78,    55,    29,
      23,   182,   123,   182,   125,    56,    57,   128,   243,   244,
      55,   132,   133,   134,   135,   250,   137,   138,   139,   140,
     101,    29,   143,    29,   317,    76,    56,    57,    55,   322,
      87,    79,    80,    53,    79,    80,    20,   118,   173,    80,
      97,    81,    99,   100,    79,    80,    76,    53,    56,    57,
      56,    57,    79,    80,    53,   112,    76,     5,   139,    79,
      80,   182,   297,   298,     4,     5,    83,   188,    76,    79,
      80,    53,   129,    13,    83,    15,    74,    75,   199,    77,
     201,    20,    22,    23,     8,     9,   207,    55,    81,    83,
      82,    81,   173,   214,    79,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   228,   241,    79,    21,   230,
     231,    78,   233,   234,   237,   350,    53,   238,   239,   240,
      84,    84,   299,   244,    78,   302,   207,    76,    83,   306,
      82,   252,   253,   254,    76,    82,    81,   194,   259,    83,
      78,   262,    78,    78,    78,   266,    78,    70,    20,   330,
      83,   330,    80,    55,    53,     5,    77,   278,   279,    78,
     241,   296,    79,   244,    76,    83,   343,    39,    40,    41,
      42,    43,    44,    45,    46,   352,    84,    82,   355,   300,
       3,    20,    83,     6,    66,    67,    68,    81,    78,    81,
      81,    14,    74,    75,    78,    77,   317,    20,    21,    76,
      23,   322,    29,    26,    78,    28,    16,    17,    81,   330,
      20,    77,    76,    36,    37,   296,    39,    40,    41,    42,
      43,    44,    45,    46,    81,    76,     4,    76,    76,    39,
      40,    41,    42,    43,    44,    45,    46,    32,    74,   143,
      63,    64,     3,   356,   266,     6,    69,    70,   177,    72,
     207,    74,    75,    14,   330,    78,    79,   182,   100,    20,
      21,    84,    23,    97,    99,    26,    17,    28,   113,    20,
      19,    78,    -1,    -1,    -1,    36,    37,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    -1,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    64,    -1,    -1,    -1,    -1,    69,    70,
      -1,    72,    -1,    74,    75,    -1,    -1,    78,    79,    -1,
      -1,    -1,     3,    84,     5,     6,     7,    -1,    -1,    10,
      11,    12,    -1,    14,    -1,    -1,    -1,    18,    19,    20,
      21,    -1,    23,    -1,    25,    26,    -1,    28,    -1,    30,
      31,    32,    33,    34,    -1,    36,    37,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    -1,     3,    -1,    -1,
       6,    -1,    53,    -1,    -1,    -1,    -1,    -1,    14,    -1,
      -1,    -1,    63,    64,    20,    21,    -1,    23,    69,    70,
      26,    72,    28,    74,    75,    -1,    -1,    78,    79,    80,
      36,    37,    -1,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    14,    -1,    -1,    -1,    63,    64,    20,
      21,    -1,    23,    69,    70,    26,    72,    28,    74,    75,
      -1,    -1,    78,    79,    80,    36,    37,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    -1,    -1,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    -1,
      -1,    -1,    63,    64,    74,    75,    76,    77,    69,    70,
      -1,    72,    -1,    74,    75,    -1,    -1,    78,    79,    80,
       3,    -1,    -1,     6,    -1,    -1,    -1,    10,    -1,    -1,
      -1,    14,    -1,    -1,    -1,    18,    19,    20,    21,    -1,
      23,    -1,    25,    26,    -1,    28,    -1,    -1,    -1,    17,
      -1,    34,    20,    36,    37,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      63,    64,    -1,    -1,    -1,    -1,    69,    70,    -1,    72,
       3,    74,    75,     6,    -1,    78,    79,    10,    -1,    -1,
      -1,    14,    -1,    -1,    -1,    18,    19,    20,    21,    -1,
      23,    -1,    25,    26,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    34,    -1,    36,    37,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    -1,     3,    -1,    -1,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    14,    -1,    -1,    17,
      63,    64,    20,    21,    -1,    23,    69,    70,    26,    72,
      28,    74,    75,    -1,    -1,    78,    79,    -1,    36,    37,
      -1,    39,    40,    41,    42,    43,    44,    45,    46,    62,
      63,    64,    65,    66,    67,    68,    -1,    -1,    -1,    -1,
      -1,    74,    75,    -1,    77,    63,    64,     3,    -1,     5,
       6,    69,    70,    -1,    72,    73,    74,    75,    14,    -1,
      78,    79,    -1,    -1,    20,    21,    -1,    23,    -1,    -1,
      26,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    37,    -1,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    14,    -1,    -1,    17,    63,    64,    20,
      21,    -1,    23,    69,    70,    26,    72,    28,    74,    75,
      -1,    -1,    78,    79,    -1,    36,    37,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    -1,     3,    -1,     5,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    14,    -1,
      -1,    -1,    63,    64,    20,    21,    -1,    23,    69,    70,
      26,    72,    28,    74,    75,    -1,    -1,    78,    79,    -1,
      36,    37,    -1,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    14,    -1,    -1,    -1,    63,    64,    20,
      21,    -1,    23,    69,    70,    26,    72,    28,    74,    75,
      -1,    -1,    78,    79,    -1,    36,    37,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    -1,    -1,    58,    59,
      60,    -1,    62,    63,    64,    65,    66,    67,    68,    -1,
      -1,    -1,    63,    64,    74,    75,    76,    77,    69,    70,
      -1,    72,    73,    74,    75,    -1,     3,    78,    79,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    14,    -1,    -1,
      17,    -1,    -1,    20,    21,    -1,    23,    -1,    -1,    26,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      37,    -1,    39,    40,    41,    42,    43,    44,    45,    46,
      -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    14,    -1,    -1,    -1,    63,    64,    20,    21,
      -1,    23,    69,    70,    26,    72,    28,    74,    75,    -1,
      -1,    78,    79,    -1,    36,    37,    -1,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    -1,    -1,
      -1,    63,    64,    74,    75,    -1,    77,    69,    70,    -1,
      72,    -1,    74,    75,    -1,    -1,    78,    79,    58,    59,
      60,    -1,    62,    63,    64,    65,    66,    67,    68,    -1,
      -1,    -1,    -1,    -1,    74,    75,    -1,    77,    -1,    -1,
      -1,    58,    59,    60,    84,    62,    63,    64,    65,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    74,    75,    -1,
      77,    -1,    -1,    -1,    58,    59,    60,    84,    62,    63,
      64,    65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,
      74,    75,    -1,    77,    -1,    -1,    -1,    58,    59,    60,
      84,    62,    63,    64,    65,    66,    67,    68,    -1,    -1,
      -1,    -1,    -1,    74,    75,    -1,    77,    -1,    -1,    -1,
      58,    59,    60,    84,    62,    63,    64,    65,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,    74,    75,    -1,    77,
      -1,    -1,    -1,    58,    59,    60,    84,    62,    63,    64,
      65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,    74,
      75,    -1,    77,    -1,    53,    -1,    -1,    -1,    83,    58,
      59,    60,    -1,    62,    63,    64,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    74,    75,    -1,    77,    58,
      59,    60,    -1,    62,    63,    64,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    74,    75,    -1,    77,    58,
      59,    60,    81,    62,    63,    64,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    74,    75,    -1,    77,    58,
      59,    60,    81,    62,    63,    64,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    74,    75,    76,    77,    58,
      59,    60,    -1,    62,    63,    64,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    74,    75,    60,    77,    62,
      63,    64,    65,    66,    67,    68,    -1,    -1,    -1,    -1,
      -1,    74,    75,    -1,    77,    63,    64,    65,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,    74,    75,    -1,    77
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    86,    87,    88,    89,    91,    20,    39,    40,
      41,    42,    43,    44,    45,    46,   148,     0,    89,    83,
     144,    23,   146,    80,    96,    23,     4,    13,    15,    22,
      90,    93,    94,    95,   114,   115,   116,   117,   119,   145,
     146,    20,   153,   148,    26,    28,   155,    80,    97,    81,
      95,    53,     5,    83,    53,    80,   155,    83,    20,    98,
      99,   100,    20,    83,   154,   145,   155,    17,   147,   148,
     149,   150,    55,    81,    82,    38,   147,   152,    83,   147,
      81,   148,   149,    79,    79,    21,   100,    78,   152,    53,
      84,    84,   140,   141,   142,   143,   155,    78,    76,    82,
      82,    83,   140,    53,    80,   104,   142,   155,   141,    16,
     147,    76,     3,     6,     7,    10,    11,    12,    14,    18,
      19,    20,    21,    25,    30,    31,    32,    33,    34,    36,
      37,    53,    63,    64,    69,    70,    72,    74,    75,    78,
      79,    92,   101,   102,   103,   104,   105,   107,   108,   109,
     110,   111,   112,   116,   118,   123,   124,   126,   127,   129,
     130,   131,   132,   133,   134,   135,   138,   139,   145,   148,
     154,   155,   156,    83,    53,   104,   155,   144,    78,   126,
     132,   138,    78,    78,   148,   149,   151,   126,    78,   126,
      83,   104,   126,   132,    80,   155,   126,   126,   126,    80,
     126,    70,   126,   126,   126,   147,   148,    78,   120,   121,
     122,   126,    81,   103,    55,    53,    58,    59,    60,    62,
      63,    64,    65,    66,    67,    68,    74,    75,    77,    53,
      55,    79,    80,    55,    79,    80,     5,    77,    78,    54,
      55,    83,    96,    73,    78,   125,   126,   128,   136,   137,
     105,   125,    79,    79,    80,   126,    83,   155,   126,    80,
     126,    76,    76,   121,   126,    84,    82,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,    78,    79,
      80,   154,   126,   126,   153,   126,   126,   153,   154,   120,
     126,   126,   147,   125,   125,   126,    29,    56,    57,    76,
      61,   125,    76,   126,   126,   120,    76,    81,    81,   126,
     126,    76,   122,   126,   120,   126,   153,    78,    84,    81,
      84,    81,    78,    76,    76,   147,   125,   125,   104,   126,
      53,   104,    84,    84,    81,   104,    81,    76,    84,    81,
     120,   120,     8,     9,   113,   106,   126,   127,    76,    76,
      78,   104,    76,   125,   104,    76,   104,   113
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

  case 49:
#line 288 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[(1) - (8)].opval), (yyvsp[(3) - (8)].opval), (yyvsp[(4) - (8)].opval), (yyvsp[(6) - (8)].opval), (yyvsp[(8) - (8)].opval));
    ;}
    break;

  case 50:
#line 294 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 51:
#line 300 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 52:
#line 306 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 54:
#line 315 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (6)].opval)->file, (yyvsp[(1) - (6)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    ;}
    break;

  case 55:
#line 328 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 56:
#line 332 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (2)].opval);
    ;}
    break;

  case 57:
#line 336 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
    ;}
    break;

  case 58:
#line 342 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(2) - (6)].opval), (yyvsp[(4) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 59:
#line 348 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (9)].opval), (yyvsp[(3) - (9)].opval), (yyvsp[(5) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(1) - (9)].opval), (yyvsp[(9) - (9)].opval));
     ;}
    break;

  case 60:
#line 352 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (9)].opval), (yyvsp[(3) - (9)].opval), (yyvsp[(5) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(1) - (9)].opval), NULL);
     ;}
    break;

  case 61:
#line 358 "yacc/spvm_yacc.y"
    {
       SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[(2) - (8)].opval)->file, (yyvsp[(2) - (8)].opval)->line);
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (8)].opval), op_sub_name, (yyvsp[(4) - (8)].opval), (yyvsp[(6) - (8)].opval), (yyvsp[(1) - (8)].opval), (yyvsp[(8) - (8)].opval));
     ;}
    break;

  case 62:
#line 363 "yacc/spvm_yacc.y"
    {
       SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[(2) - (8)].opval)->file, (yyvsp[(2) - (8)].opval)->line);
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (8)].opval), op_sub_name, (yyvsp[(4) - (8)].opval), (yyvsp[(6) - (8)].opval), (yyvsp[(1) - (8)].opval), NULL);
     ;}
    break;

  case 63:
#line 370 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 64:
#line 376 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 65:
#line 380 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 66:
#line 386 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package_var(compiler, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 67:
#line 392 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 68:
#line 396 "yacc/spvm_yacc.y"
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

  case 69:
#line 409 "yacc/spvm_yacc.y"
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

  case 70:
#line 423 "yacc/spvm_yacc.y"
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

  case 71:
#line 448 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 72:
#line 452 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (1)].opval);
    ;}
    break;

  case 73:
#line 456 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (1)].opval);
    ;}
    break;

  case 74:
#line 462 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 75:
#line 468 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 76:
#line 473 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 77:
#line 478 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 78:
#line 483 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 79:
#line 490 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_deref(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 80:
#line 494 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_deref(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 85:
#line 504 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 87:
#line 511 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_constant(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 102:
#line 530 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 103:
#line 534 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 104:
#line 538 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 105:
#line 542 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 106:
#line 546 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 107:
#line 550 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 109:
#line 557 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 110:
#line 563 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new_object(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 111:
#line 567 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new_object(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 112:
#line 571 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new_object(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 113:
#line 575 "yacc/spvm_yacc.y"
    {
      // New
      SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);

      (yyval.opval) = SPVM_OP_build_new_object(compiler, op_new, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 114:
#line 582 "yacc/spvm_yacc.y"
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

  case 115:
#line 603 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 116:
#line 610 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, (yyvsp[(2) - (4)].opval)->file, (yyvsp[(2) - (4)].opval)->line);
      (yyval.opval) = SPVM_OP_build_convert(compiler, op_convert, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 117:
#line 617 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 118:
#line 621 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 119:
#line 625 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 120:
#line 631 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 121:
#line 637 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 122:
#line 642 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEGATE, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op_negate, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 123:
#line 647 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 124:
#line 652 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 125:
#line 657 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 126:
#line 662 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 127:
#line 667 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unop(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 128:
#line 673 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 129:
#line 678 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 130:
#line 683 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_concat(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 131:
#line 687 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 132:
#line 691 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 133:
#line 695 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 134:
#line 699 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 135:
#line 703 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 136:
#line 707 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 137:
#line 711 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 138:
#line 715 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 139:
#line 719 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 140:
#line 723 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 141:
#line 727 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 142:
#line 733 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 143:
#line 739 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_or(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 144:
#line 743 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_and(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 145:
#line 747 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_not(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 146:
#line 753 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 147:
#line 757 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 148:
#line 761 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 149:
#line 767 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, NULL, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 150:
#line 771 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 151:
#line 775 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_assignable_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_assignable_terms);
    ;}
    break;

  case 152:
#line 780 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 153:
#line 784 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_assignable_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_assignable_terms);
    ;}
    break;

  case 154:
#line 789 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[(2) - (5)].opval)->file, (yyvsp[(2) - (5)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (5)].opval), op_sub_name, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 155:
#line 796 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 156:
#line 800 "yacc/spvm_yacc.y"
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

  case 157:
#line 811 "yacc/spvm_yacc.y"
    {
       // Add invocant to arguments
       SPVM_OP* op_args = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
       SPVM_OP_insert_child(compiler, op_args, op_args->last, (yyvsp[(1) - (1)].opval));
       
       (yyval.opval) = op_args;
    ;}
    break;

  case 158:
#line 819 "yacc/spvm_yacc.y"
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

  case 159:
#line 838 "yacc/spvm_yacc.y"
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

  case 160:
#line 852 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 162:
#line 859 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 163:
#line 865 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 164:
#line 871 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 165:
#line 875 "yacc/spvm_yacc.y"
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

  case 166:
#line 888 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 167:
#line 892 "yacc/spvm_yacc.y"
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

  case 168:
#line 905 "yacc/spvm_yacc.y"
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

  case 173:
#line 927 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 174:
#line 931 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_byte_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 175:
#line 938 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_short_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 176:
#line 945 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_int_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 177:
#line 952 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_long_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 178:
#line 959 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_float_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 179:
#line 966 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_double_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 180:
#line 973 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_object_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 181:
#line 980 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_string_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 182:
#line 989 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 183:
#line 993 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 184:
#line 999 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_const_array_type(compiler, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 185:
#line 1005 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 186:
#line 1009 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 188:
#line 1017 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_void(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 191:
#line 1026 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 192:
#line 1030 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_ref_var(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 193:
#line 1034 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_ref_var(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 194:
#line 1040 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3239 "spvm_yacc.tab.c"
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


#line 1044 "yacc/spvm_yacc.y"


