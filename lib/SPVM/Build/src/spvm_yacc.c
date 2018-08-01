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
     DEREF = 290,
     BACKSLASH = 291,
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
     AMPERSAND = 302,
     SPECIAL_ASSIGN = 303,
     ASSIGN = 304,
     OR = 305,
     AND = 306,
     BIT_XOR = 307,
     BIT_OR = 308,
     BIT_AND = 309,
     REL = 310,
     SHIFT = 311,
     REMAINDER = 312,
     DIVIDE = 313,
     MULTIPLY = 314,
     UMINUS = 315,
     SCALAR = 316,
     NOT = 317,
     DEC = 318,
     INC = 319,
     ARROW = 320
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
#define DEREF 290
#define BACKSLASH 291
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
#define AMPERSAND 302
#define SPECIAL_ASSIGN 303
#define ASSIGN 304
#define OR 305
#define AND 306
#define BIT_XOR 307
#define BIT_OR 308
#define BIT_AND 309
#define REL 310
#define SHIFT 311
#define REMAINDER 312
#define DIVIDE 313
#define MULTIPLY 314
#define UMINUS 315
#define SCALAR 316
#define NOT 317
#define DEC 318
#define INC 319
#define ARROW 320




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
#line 258 "spvm_yacc.tab.c"

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
#define YYLAST   1483

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  198
/* YYNRULES -- Number of states.  */
#define YYNSTATES  364

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   320

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      73,    71,     2,    58,    77,    59,    60,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    78,    48,
       2,     2,     2,     2,    65,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    74,     2,    79,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    75,     2,    76,    64,     2,     2,     2,
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
      45,    46,    47,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    61,    62,    63,    66,    67,    68,    69,    70,
      72
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
     267,   272,   275,   280,   282,   284,   286,   288,   292,   294,
     296,   298,   300,   302,   304,   306,   308,   310,   312,   314,
     316,   318,   320,   322,   324,   326,   328,   331,   333,   336,
     340,   344,   346,   350,   353,   356,   362,   364,   366,   370,
     375,   381,   386,   391,   394,   397,   400,   403,   406,   409,
     412,   415,   419,   423,   427,   431,   435,   439,   443,   447,
     451,   455,   459,   463,   467,   471,   475,   479,   483,   487,
     490,   496,   501,   506,   511,   518,   522,   529,   533,   539,
     540,   542,   544,   548,   552,   555,   557,   561,   565,   566,
     569,   570,   572,   575,   577,   579,   581,   583,   585,   587,
     589,   591,   593,   595,   597,   599,   601,   603,   606,   610,
     614,   617,   622,   627,   629,   631,   633,   635,   637
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      81,     0,    -1,    82,    -1,    -1,    83,    -1,    83,    84,
      -1,    84,    -1,    86,    -1,    13,   144,    48,    -1,     6,
     144,   140,    91,    -1,     6,   140,    91,    -1,    -1,    89,
      -1,    89,    90,    -1,    90,    -1,   109,    -1,   110,    -1,
     112,    -1,   114,    48,    -1,    85,    -1,   111,    -1,    75,
      88,    76,    -1,    75,    93,    76,    -1,    -1,    94,    -1,
      94,    77,    95,    -1,    94,    77,    -1,    95,    -1,    20,
      -1,    20,    50,    21,    -1,    -1,    97,    -1,    97,    98,
      -1,    98,    -1,   100,    -1,   107,    -1,   102,    -1,   103,
      -1,    99,    -1,   104,    -1,   105,    -1,   106,    -1,   153,
      -1,    75,    96,    76,    -1,   122,    48,    -1,   123,    48,
      -1,    48,    -1,   122,    -1,   123,    -1,    11,    73,   100,
     121,    48,   101,    71,    99,    -1,    12,    73,   121,    71,
      99,    -1,    29,    73,   122,    71,    99,    -1,    30,   122,
      78,    -1,    31,    78,    -1,     7,    73,   121,    71,    99,
     108,    -1,    -1,     9,    99,    -1,     8,    73,   121,    71,
      99,   108,    -1,     4,   150,    78,   141,   143,    48,    -1,
     141,     5,   151,    78,   149,    73,   136,    71,    99,    -1,
     141,     5,   151,    78,   149,    73,   136,    71,    48,    -1,
     141,     5,    78,   149,    73,   136,    71,    99,    -1,   141,
       5,    78,   149,    73,   136,    71,    48,    -1,    22,    92,
      -1,     3,   152,    78,   143,    -1,     3,   152,    -1,    15,
     152,    78,   143,    -1,    -1,   116,    -1,   116,    77,   122,
      -1,   116,    77,   117,    -1,   116,    77,    -1,   117,    -1,
     122,    -1,    73,   116,    71,    -1,    65,   122,    -1,    65,
      75,   122,    76,    -1,    67,    65,   122,    -1,    67,    65,
      75,   122,    76,    -1,    35,   152,    -1,    35,    75,   152,
      76,    -1,    36,   152,    -1,    36,    75,   152,    76,    -1,
     122,    -1,   132,    -1,   133,    -1,   124,    -1,    73,   121,
      71,    -1,   152,    -1,    21,    -1,    37,    -1,   135,    -1,
     128,    -1,   134,    -1,   127,    -1,   125,    -1,   126,    -1,
     118,    -1,   113,    -1,   131,    -1,   130,    -1,   120,    -1,
     119,    -1,    18,    -1,    19,    -1,    10,    -1,    10,   122,
      -1,    25,    -1,    25,   122,    -1,   128,    50,   122,    -1,
     134,    50,   122,    -1,   129,    -1,   121,    28,   143,    -1,
      14,   144,    -1,    14,   148,    -1,    14,   146,    75,   115,
      76,    -1,    87,    -1,   111,    -1,    74,   115,    79,    -1,
      73,   143,    71,   122,    -1,   122,    72,    75,   150,    76,
      -1,   128,    75,   150,    76,    -1,   134,    75,   150,    76,
      -1,    33,   128,    -1,    58,   122,    -1,    59,   122,    -1,
      70,   122,    -1,   122,    70,    -1,    69,   122,    -1,   122,
      69,    -1,    64,   122,    -1,   122,    58,   122,    -1,   122,
      59,   122,    -1,   122,    60,   122,    -1,   122,    63,   122,
      -1,   122,    62,   122,    -1,   122,    61,   122,    -1,   122,
      53,   122,    -1,   122,    47,   122,    -1,   122,    54,   122,
      -1,   122,    57,   122,    -1,   113,    50,   122,    -1,   152,
      50,   122,    -1,   152,    49,   122,    -1,    73,   122,    71,
      -1,   119,    50,   122,    -1,   122,    56,   122,    -1,   121,
      51,   121,    -1,   121,    52,   121,    -1,    68,   121,    -1,
     122,    72,    74,   122,    79,    -1,   134,    74,   122,    79,
      -1,   128,    74,   122,    79,    -1,   151,    73,   115,    71,
      -1,   144,    72,   151,    73,   115,    71,    -1,   144,    72,
     151,    -1,   122,    72,   151,    73,   115,    71,    -1,   122,
      72,   151,    -1,   122,    72,    73,   115,    71,    -1,    -1,
     137,    -1,   139,    -1,   139,    77,   137,    -1,   137,    77,
     138,    -1,   137,    77,    -1,   138,    -1,   152,    78,   143,
      -1,   152,    78,    16,    -1,    -1,    78,   142,    -1,    -1,
     142,    -1,   142,    23,    -1,    23,    -1,   144,    -1,   146,
      -1,   147,    -1,   145,    -1,    20,    -1,    39,    -1,    40,
      -1,    41,    -1,    42,    -1,    43,    -1,    44,    -1,    46,
      -1,    45,    -1,    47,   144,    -1,   144,    74,    79,    -1,
     146,    74,    79,    -1,    17,   146,    -1,   144,    74,   122,
      79,    -1,   146,    74,   122,    79,    -1,   143,    -1,    38,
      -1,    20,    -1,    20,    -1,    26,    -1,    32,    99,    -1
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
     493,   499,   504,   511,   512,   513,   514,   515,   521,   522,
     526,   527,   528,   529,   530,   531,   532,   533,   534,   535,
     536,   537,   538,   541,   542,   543,   546,   550,   554,   558,
     562,   566,   569,   575,   579,   583,   587,   594,   615,   622,
     629,   633,   637,   643,   649,   654,   659,   664,   669,   674,
     679,   685,   690,   695,   699,   703,   707,   711,   715,   719,
     723,   727,   731,   735,   739,   743,   749,   755,   759,   763,
     769,   773,   777,   783,   787,   791,   796,   800,   805,   813,
     816,   827,   835,   854,   868,   872,   875,   881,   888,   891,
     905,   908,   921,   935,   938,   939,   940,   941,   944,   948,
     955,   962,   969,   976,   983,   990,   997,  1006,  1012,  1016,
    1022,  1028,  1032,  1039,  1040,  1045,  1046,  1049,  1055
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
  "DEFAULT", "EVAL", "WEAKEN", "PRECOMPILE", "DEREF", "BACKSLASH", "UNDEF",
  "VOID", "BYTE", "SHORT", "INT", "LONG", "FLOAT", "DOUBLE", "STRING",
  "OBJECT", "AMPERSAND", "';'", "SPECIAL_ASSIGN", "ASSIGN", "OR", "AND",
  "BIT_XOR", "BIT_OR", "BIT_AND", "REL", "SHIFT", "'+'", "'-'", "'.'",
  "REMAINDER", "DIVIDE", "MULTIPLY", "'~'", "'@'", "UMINUS", "SCALAR",
  "NOT", "DEC", "INC", "')'", "ARROW", "'('", "'['", "'{'", "'}'", "','",
  "':'", "']'", "$accept", "grammar", "opt_declarations_in_grammar",
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
  "ref", "term", "assignable_term", "expression", "isa", "new_object",
  "array_init", "convert_type", "field_access", "weaken_field", "unop",
  "binop", "relative_term", "logical_term", "array_access", "call_sub",
  "opt_args", "args", "arg", "invocant", "opt_colon_descriptors",
  "opt_descriptors", "descriptors", "type", "basic_type", "ref_type",
  "array_type", "const_array_type", "array_type_with_length",
  "type_or_void", "field_name", "sub_name", "var", "eval_block", 0
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
     295,   296,   297,   298,   299,   300,   301,   302,    59,   303,
     304,   305,   306,   307,   308,   309,   310,   311,    43,    45,
      46,   312,   313,   314,   126,    64,   315,   316,   317,   318,
     319,    41,   320,    40,    91,   123,   125,    44,    58,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    80,    81,    82,    82,    83,    83,    84,    85,    86,
      87,    88,    88,    89,    89,    90,    90,    90,    90,    90,
      90,    91,    92,    93,    93,    94,    94,    94,    95,    95,
      96,    96,    97,    97,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    99,   100,   100,   100,   101,   101,   102,
     103,   104,   105,   106,   107,   108,   108,   108,   109,   110,
     110,   111,   111,   112,   113,   113,   114,   115,   115,   116,
     116,   116,   116,   116,   117,   118,   118,   118,   118,   119,
     119,   120,   120,   121,   121,   121,   121,   121,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   124,   125,   125,   125,   125,   125,   126,   127,
     128,   128,   128,   129,   130,   130,   130,   130,   130,   130,
     130,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   132,   133,   133,   133,
     134,   134,   134,   135,   135,   135,   135,   135,   135,   136,
     136,   136,   136,   137,   137,   137,   138,   139,   140,   140,
     141,   141,   142,   142,   143,   143,   143,   143,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   145,   146,   146,
     147,   148,   148,   149,   149,   150,   151,   152,   153
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
       4,     2,     4,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     3,
       3,     1,     3,     2,     2,     5,     1,     1,     3,     4,
       5,     4,     4,     2,     2,     2,     2,     2,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       5,     4,     4,     4,     6,     3,     6,     3,     5,     0,
       1,     1,     3,     3,     2,     1,     3,     3,     0,     2,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     3,
       2,     4,     4,     1,     1,     1,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     2,     4,     6,     7,   178,   179,   180,
     181,   182,   183,   184,   186,   185,   168,     1,     5,     0,
       0,   173,   169,    11,     9,   172,     0,     0,     0,     0,
      19,     0,    12,    14,    15,    16,    20,    17,     0,     0,
     171,   195,     0,     0,   197,     0,    23,    63,    21,    13,
      18,     0,   170,     8,     0,    28,     0,    24,    27,   196,
       0,     0,     0,     0,     0,    66,   174,   177,   175,   176,
       0,    22,    26,   194,   193,     0,     0,     0,     0,   190,
     187,     0,     0,    29,    25,   159,     0,    58,   188,   189,
       0,   160,   165,   161,     0,   159,     0,   164,     0,     0,
       0,    62,    30,    61,   163,     0,   162,   167,   166,     0,
       0,   168,     0,   105,     0,     0,     0,   103,   104,   178,
      89,   107,     0,   170,     0,     0,   170,     0,     0,    90,
      46,   170,   170,   170,   170,     0,   170,   170,   170,    67,
     116,     0,    31,    33,    38,    34,    36,    37,    39,    40,
      41,    35,   117,    98,    97,   102,   101,     0,     0,    95,
      96,    94,    92,   111,   100,    99,    93,    91,     0,     0,
       0,    88,    42,     0,    60,    59,    65,     0,   170,   106,
      92,    93,   170,   170,   113,     0,   114,   108,   170,     0,
      53,   198,     0,    92,     0,    79,     0,    81,   124,   125,
     130,   170,    75,   170,   128,   126,     0,     0,   174,   170,
       0,    68,    72,    73,    43,    32,   170,   170,   170,    44,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   129,
     127,     0,    45,   170,   170,     0,   170,   170,     0,     0,
       0,    67,   170,   170,     0,    10,   170,   170,     0,    83,
      86,    84,    85,   170,     0,   170,   170,    67,     0,    52,
       0,     0,     0,   170,    77,   144,   170,     0,    73,   118,
      71,   141,   145,   138,   137,   139,   140,   131,   132,   133,
     136,   135,   134,    67,   170,     0,   157,   109,     0,     0,
     110,     0,     0,   155,     0,   143,   142,    64,   149,     0,
      83,     0,   170,   170,     0,   170,     0,     0,     0,     0,
       0,     0,    80,    82,    76,     0,   119,    74,    70,    69,
       0,     0,     0,    67,   152,   121,   151,   122,    67,   153,
      87,   112,   147,   148,    55,   146,   170,    50,   191,   192,
     115,    51,    78,   158,   150,   120,     0,     0,     0,     0,
      54,     0,    47,    48,   156,   154,   170,    56,     0,     0,
      49,     0,    55,    57
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    30,     6,   140,    31,    32,
      33,    24,    47,    56,    57,    58,   141,   142,   143,   144,
     145,   351,   146,   147,   148,   149,   150,   151,   350,    34,
      35,   152,    37,   153,    38,   210,   211,   212,   154,   155,
     156,   248,   249,   158,   250,   159,   160,   161,   180,   163,
     164,   165,   251,   252,   181,   167,    90,    91,    92,    93,
      20,   168,    40,   207,   169,    67,    68,    69,   186,    75,
      42,   170,   171,   172
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -233
static const yytype_int16 yypact[] =
{
      15,   666,    37,  -233,    15,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,   -26,  -233,  -233,    26,
     -19,  -233,    55,   237,  -233,  -233,    48,   666,    64,    12,
    -233,    30,   237,  -233,  -233,  -233,  -233,  -233,    62,   122,
      55,  -233,    73,    81,  -233,    82,   113,  -233,  -233,  -233,
    -233,    -7,    26,  -233,   591,    89,    91,    92,  -233,  -233,
     536,    90,   591,   666,   666,  -233,    96,  -233,    97,  -233,
     153,  -233,   113,  -233,  -233,   103,   536,   129,    96,    97,
    -233,   101,   102,  -233,  -233,    64,   109,  -233,  -233,  -233,
     124,   116,  -233,   120,   121,    64,   -30,    64,    64,   402,
     130,  -233,   469,  -233,  -233,   125,   116,  -233,  -233,   -29,
      64,   -26,   131,   977,   132,   133,   666,  -233,  -233,   137,
    -233,   977,   138,  1148,   146,   127,  1148,    -3,     2,  -233,
    -233,  1148,  1148,  1148,   526,   150,  1148,  1148,   855,  1034,
    -233,   149,   469,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,   176,  -233,   177,  -233,  1331,   180,  -233,
    -233,  -233,    42,  -233,  -233,  -233,    68,  -233,   226,   161,
     162,    45,  -233,   591,  -233,  -233,   158,   -19,  1091,  1411,
     -41,    49,   656,  1091,   170,    61,  -233,  1411,  1148,  1244,
    -233,  -233,  1411,   -33,    64,  -233,    64,  -233,    35,    35,
      35,  1148,    35,   583,    83,    83,  1351,   174,    14,   920,
     168,   171,  -233,  1411,  -233,  -233,  1148,  1148,  1148,  -233,
    1148,  1148,  1148,  1148,  1148,  1148,  1148,  1148,  1148,  -233,
    -233,    -9,  -233,  1148,  1148,    48,  1148,  1148,    48,   173,
     236,  1034,  1148,  1148,   591,  -233,  1091,   786,   -16,  1371,
    -233,  -233,  -233,  1091,    22,   325,   394,  1034,  1391,  -233,
     181,   182,  1270,  1148,    35,  -233,  1148,   -55,  1351,  -233,
    1034,  1411,  1411,   712,   712,   712,   777,    50,    50,    50,
      35,    35,    35,  1034,  1148,    48,   189,  1411,    87,   188,
    1411,   160,   191,   192,   200,  1411,  1411,  -233,   253,    29,
    1311,   591,  1091,  1091,   127,  1148,   110,   127,  1172,  1196,
     206,   127,  -233,  -233,  -233,  1290,   -18,  -233,  -233,  1411,
     212,  1220,   208,  1034,  -233,  -233,  -233,  -233,  1034,  -233,
    -233,  -233,    51,   253,   155,  1411,   721,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,   216,   219,   218,   127,
    -233,   221,  1411,  -233,  -233,  -233,  1091,  -233,   127,    57,
    -233,   127,   155,  -233
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -233,  -233,  -233,  -233,   292,  -233,  -233,  -233,  -233,  -233,
     265,   126,  -233,  -233,  -233,   229,  -233,  -233,   156,   -95,
     123,  -233,  -233,  -233,  -233,  -233,  -233,  -233,   -60,  -233,
    -233,    16,  -233,  -233,  -233,  -232,    95,    36,  -233,  -233,
    -233,  -177,    52,   -25,  -233,  -233,  -233,  -233,   -99,  -233,
    -233,  -233,  -233,  -233,   -98,  -233,   215,   214,   217,  -233,
     202,     8,   297,   -52,    -1,  -233,   -58,  -233,  -233,   241,
    -218,   -44,     4,  -233
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -197
static const yytype_int16 yytable[] =
{
      16,   103,    65,   162,   166,    79,   254,    61,    74,   294,
      77,    59,   301,    59,   175,  -123,   317,   289,   101,   174,
     292,     1,   270,    44,    74,   310,    43,   193,    44,   218,
     191,    39,    45,   234,   235,   302,   303,    17,  -123,    36,
      39,   234,   235,   162,   166,   102,   102,   108,    36,    21,
     301,   320,    19,    66,   231,   304,    23,   301,   185,    66,
      62,    66,    78,    80,   283,   284,   285,   322,    41,   298,
     299,    60,   194,   302,   303,    66,   306,   196,    25,   301,
     302,   303,   218,   162,   166,   301,   240,    46,    81,    94,
      44,   346,   233,   307,   242,   243,   347,   218,    66,    94,
     330,   105,   105,   303,   229,   230,    48,   231,   302,   303,
      50,   226,   227,   228,   176,   184,   234,   235,   236,   229,
     230,   108,   231,   237,   238,   332,   333,    51,   361,    53,
     218,   195,   197,    55,   218,   256,   257,   208,   301,    70,
     220,   221,   237,   238,   222,   223,   224,   225,   226,   227,
     228,    52,  -197,  -197,   157,   231,   229,   230,   336,   231,
      54,   302,   303,   348,   349,   179,   324,    71,    76,    72,
      81,    82,    66,   187,    83,   189,    85,    87,   192,   359,
      88,    89,    95,   198,   199,   200,   202,   286,   204,   205,
     206,   213,   297,    97,   157,    96,   293,    98,   260,    99,
     261,   109,   102,   173,   178,   182,   183,   218,   208,   334,
    -196,   188,   337,   220,   221,   203,   341,   222,   223,   224,
     225,   226,   227,   228,   190,   214,   216,   217,   232,   229,
     230,   239,   231,   240,   157,   241,   244,   162,   166,   326,
     258,    26,  -170,    66,   255,   266,   208,   269,   270,   331,
      27,    60,    28,   262,   357,   264,    59,   312,   313,    29,
      21,   268,   323,   360,   325,   328,   362,   327,   271,   272,
     273,   329,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   301,   340,   343,   345,   287,   288,   354,   290,   291,
     355,   356,   358,   213,   295,   296,    18,    49,   215,   300,
      66,    84,   363,   245,   267,   253,   318,   308,   309,   213,
     100,   353,   106,   177,   104,   315,    22,    86,   316,     0,
       0,     0,   319,     0,     0,     0,     0,     0,   110,     0,
       0,   111,     0,     0,     0,   213,   321,     0,     0,   116,
       0,     0,     0,     0,     0,   119,   120,     0,    21,     0,
       0,    44,     0,     0,     0,     0,     0,   335,     0,     0,
     127,   128,   129,     0,     8,     9,    10,    11,    12,    13,
      14,    15,     0,     0,     0,   213,     0,     0,     0,     0,
     213,     0,     0,   131,   132,     0,     0,     0,   352,   133,
     134,     0,   135,     0,   136,   137,     0,   110,   138,   139,
     111,     0,     0,     0,    88,     0,     0,     0,   116,     0,
       0,     0,     0,     0,   119,   120,     0,    21,   107,    63,
      44,     0,     7,     0,     0,     0,     0,     0,     0,   127,
     128,   129,     0,     8,     9,    10,    11,    12,    13,    14,
      15,     8,     9,    10,    11,    12,    13,    14,    15,    64,
       0,     0,   131,   132,     0,     0,     0,     0,   133,   134,
       0,   135,     0,   136,   137,     0,     0,   138,   139,     0,
       0,     0,   110,    89,  -170,   111,   112,     0,     0,   113,
     114,   115,     0,   116,     0,     0,     0,   117,   118,   119,
     120,     0,    21,     0,   121,    44,     0,     0,   122,   123,
     124,   125,   126,     0,   127,   128,   129,     0,     8,     9,
      10,    11,    12,    13,    14,    15,     0,   130,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   131,   132,   110,
       0,     0,   111,   133,   134,     0,   135,     0,   136,   137,
     116,     0,   138,   139,   102,     0,   119,   120,     0,    21,
       0,     0,    44,    63,     0,     0,     7,     0,     0,     0,
       0,   127,   128,   129,     0,     8,     9,    10,    11,    12,
      13,    14,    15,     0,    73,     8,     9,    10,    11,    12,
      13,    14,    15,    64,   131,   132,   110,     0,     0,   111,
     133,   134,     0,   135,     0,   136,   137,   116,     0,   138,
     139,   201,     0,   119,   120,     0,    21,     0,    63,    44,
       0,     7,     0,     0,     0,     0,     0,     0,   127,   128,
     129,     0,     8,     9,    10,    11,    12,    13,    14,    15,
       8,     9,    10,    11,    12,    13,    14,    15,    64,     0,
       0,   131,   132,     0,     0,     0,     0,   133,   134,     0,
     135,     0,   136,   137,     0,     0,   138,   139,   263,   110,
       0,     0,   111,     0,     0,     0,   113,     0,     0,     0,
     116,     0,     0,     0,   117,   118,   119,   120,     0,    21,
       0,   121,    44,     0,     0,     0,     7,     0,     0,   126,
       0,   127,   128,   129,     0,     8,     9,    10,    11,    12,
      13,    14,    15,     0,   130,     8,     9,    10,    11,    12,
      13,    14,    15,     0,   131,   132,     0,     0,     0,     0,
     133,   134,     0,   135,   110,   136,   137,   111,     0,   138,
     139,   113,     0,     0,     0,   116,     0,     0,     0,   117,
     118,   119,   120,     0,    21,     0,   121,    44,     0,     0,
       0,     0,     0,     0,   126,     0,   127,   128,   129,   218,
       8,     9,    10,    11,    12,    13,    14,    15,     0,   222,
     223,   224,   225,   226,   227,   228,     0,     0,     0,   131,
     132,   229,   230,     0,   231,   133,   134,     0,   135,   110,
     136,   137,   111,     0,   138,   139,     0,     0,     0,     0,
     116,     0,     0,    63,     0,     0,   119,   120,     0,    21,
       0,     0,    44,     0,     0,     0,     0,     0,     0,     0,
       0,   127,   128,   129,   218,     8,     9,    10,    11,    12,
      13,    14,    15,    64,     0,   223,   224,   225,   226,   227,
     228,     0,     0,     0,   131,   132,   229,   230,     0,   231,
     133,   134,     0,   135,   246,   136,   137,     0,   110,   247,
     139,   111,     0,     0,     0,     0,     0,     0,     0,   116,
       0,     0,    63,     0,     0,   119,   120,     0,    21,     0,
       0,    44,     0,     0,     0,     0,     0,     0,     0,     0,
     127,   128,   129,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    64,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   131,   132,     0,     0,     0,     0,   133,
     134,     0,   135,   110,   136,   137,   111,     0,   138,   139,
       0,     0,     0,     0,   116,     0,     0,    63,     0,     0,
     119,   120,     0,    21,     0,     0,    44,     0,     0,     0,
       0,     0,     0,     0,     0,   127,   128,   129,     0,     8,
       9,    10,    11,    12,    13,    14,    15,    64,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   131,   132,
     110,     0,  -170,   111,   133,   134,     0,   135,     0,   136,
     137,   116,     0,   209,   139,     0,     0,   119,   120,     0,
      21,     0,     0,    44,     0,     0,     0,     0,     0,     0,
       0,     0,   127,   128,   129,     0,     8,     9,    10,    11,
      12,    13,    14,    15,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   131,   132,   110,     0,  -170,
     111,   133,   134,     0,   135,     0,   136,   137,   116,     0,
     138,   139,     0,     0,   119,   120,     0,    21,     0,     0,
      44,     0,     0,     0,     0,     0,     0,     0,     0,   127,
     128,   129,     0,     8,     9,    10,    11,    12,    13,    14,
      15,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   131,   132,   110,     0,     0,   111,   133,   134,
       0,   135,     0,   136,   137,   116,     0,   209,   139,     0,
       0,   119,   120,     0,    21,     0,     0,    44,     0,     0,
       0,     0,     0,     0,     0,     0,   127,   128,   129,     0,
       8,     9,    10,    11,    12,    13,    14,    15,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   131,
     132,   110,     0,     0,   111,   133,   134,     0,   135,   246,
     136,   137,   116,     0,   247,   139,     0,     0,   119,   120,
       0,    21,     0,     0,    44,     0,     0,     0,     0,     0,
       0,     0,     0,   127,   128,   129,     0,     8,     9,    10,
      11,    12,    13,    14,    15,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   131,   132,     0,     0,
       0,     0,   133,   134,     0,   135,     0,   136,   137,   218,
       0,   138,   139,     0,     0,   220,   221,     0,     0,   222,
     223,   224,   225,   226,   227,   228,     0,     0,     0,     0,
       0,   229,   230,   218,   231,     0,     0,     0,     0,   220,
     221,   338,     0,   222,   223,   224,   225,   226,   227,   228,
       0,     0,     0,     0,     0,   229,   230,   218,   231,     0,
       0,     0,     0,   220,   221,   339,     0,   222,   223,   224,
     225,   226,   227,   228,     0,     0,     0,     0,     0,   229,
     230,   218,   231,     0,     0,     0,     0,   220,   221,   344,
       0,   222,   223,   224,   225,   226,   227,   228,     0,     0,
       0,     0,     0,   229,   230,     0,   231,   218,     0,     0,
       0,     0,   259,   220,   221,     0,     0,   222,   223,   224,
     225,   226,   227,   228,     0,     0,     0,   218,     0,   229,
     230,     0,   231,   220,   221,     0,   314,   222,   223,   224,
     225,   226,   227,   228,     0,     0,     0,     0,   218,   229,
     230,     0,   231,     0,   220,   221,   342,   305,   222,   223,
     224,   225,   226,   227,   228,     0,     0,     0,   218,   219,
     229,   230,   265,   231,   220,   221,     0,     0,   222,   223,
     224,   225,   226,   227,   228,     0,     0,     0,   218,     0,
     229,   230,     0,   231,   220,   221,     0,     0,   222,   223,
     224,   225,   226,   227,   228,     0,     0,     0,   218,     0,
     229,   230,   265,   231,   220,   221,     0,   305,   222,   223,
     224,   225,   226,   227,   228,     0,     0,     0,   218,     0,
     229,   230,     0,   231,   220,   221,     0,     0,   222,   223,
     224,   225,   226,   227,   228,     0,     0,     0,   218,     0,
     229,   230,   311,   231,   220,   221,     0,     0,   222,   223,
     224,   225,   226,   227,   228,     0,     0,     0,     0,     0,
     229,   230,     0,   231
};

static const yytype_int16 yycheck[] =
{
       1,    96,    54,   102,   102,    63,   183,    51,    60,   241,
      62,    20,    28,    20,   109,    48,    71,   235,    48,    48,
     238,     6,    77,    26,    76,   257,    27,   126,    26,    47,
     125,    23,    28,    74,    75,    51,    52,     0,    71,    23,
      32,    74,    75,   142,   142,    75,    75,    99,    32,    23,
      28,   283,    78,    54,    72,    71,    75,    28,   116,    60,
      52,    62,    63,    64,    73,    74,    75,   285,    20,   246,
     247,    78,    75,    51,    52,    76,   253,    75,    23,    28,
      51,    52,    47,   182,   182,    28,    72,    75,    74,    85,
      26,   323,    50,    71,    49,    50,   328,    47,    99,    95,
      71,    97,    98,    52,    69,    70,    76,    72,    51,    52,
      48,    61,    62,    63,   110,   116,    74,    75,    50,    69,
      70,   173,    72,    74,    75,   302,   303,     5,    71,    48,
      47,   127,   128,    20,    47,    74,    75,   138,    28,    50,
      53,    54,    74,    75,    57,    58,    59,    60,    61,    62,
      63,    78,    69,    70,   102,    72,    69,    70,    48,    72,
      78,    51,    52,     8,     9,   113,    79,    76,    78,    77,
      74,    74,   173,   121,    21,   123,    73,    48,   126,   356,
      79,    79,    73,   131,   132,   133,   134,   231,   136,   137,
     138,   139,   244,    77,   142,    71,   240,    77,   194,    78,
     196,    71,    75,    78,    73,    73,    73,    47,   209,   304,
      73,    73,   307,    53,    54,    65,   311,    57,    58,    59,
      60,    61,    62,    63,    78,    76,    50,    50,    48,    69,
      70,     5,    72,    72,   182,    73,    78,   336,   336,    79,
     188,     4,     5,   244,    74,    71,   247,    79,    77,   301,
      13,    78,    15,   201,   349,   203,    20,    76,    76,    22,
      23,   209,    73,   358,    76,    73,   361,    76,   216,   217,
     218,    71,   220,   221,   222,   223,   224,   225,   226,   227,
     228,    28,    76,    71,    76,   233,   234,    71,   236,   237,
      71,    73,    71,   241,   242,   243,     4,    32,   142,   247,
     301,    72,   362,   177,   209,   182,   270,   255,   256,   257,
      95,   336,    98,   111,    97,   263,    19,    76,   266,    -1,
      -1,    -1,   270,    -1,    -1,    -1,    -1,    -1,     3,    -1,
      -1,     6,    -1,    -1,    -1,   283,   284,    -1,    -1,    14,
      -1,    -1,    -1,    -1,    -1,    20,    21,    -1,    23,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,   305,    -1,    -1,
      35,    36,    37,    -1,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    -1,    -1,   323,    -1,    -1,    -1,    -1,
     328,    -1,    -1,    58,    59,    -1,    -1,    -1,   336,    64,
      65,    -1,    67,    -1,    69,    70,    -1,     3,    73,    74,
       6,    -1,    -1,    -1,    79,    -1,    -1,    -1,    14,    -1,
      -1,    -1,    -1,    -1,    20,    21,    -1,    23,    16,    17,
      26,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36,    37,    -1,    39,    40,    41,    42,    43,    44,    45,
      46,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    -1,    58,    59,    -1,    -1,    -1,    -1,    64,    65,
      -1,    67,    -1,    69,    70,    -1,    -1,    73,    74,    -1,
      -1,    -1,     3,    79,     5,     6,     7,    -1,    -1,    10,
      11,    12,    -1,    14,    -1,    -1,    -1,    18,    19,    20,
      21,    -1,    23,    -1,    25,    26,    -1,    -1,    29,    30,
      31,    32,    33,    -1,    35,    36,    37,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,     3,
      -1,    -1,     6,    64,    65,    -1,    67,    -1,    69,    70,
      14,    -1,    73,    74,    75,    -1,    20,    21,    -1,    23,
      -1,    -1,    26,    17,    -1,    -1,    20,    -1,    -1,    -1,
      -1,    35,    36,    37,    -1,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    58,    59,     3,    -1,    -1,     6,
      64,    65,    -1,    67,    -1,    69,    70,    14,    -1,    73,
      74,    75,    -1,    20,    21,    -1,    23,    -1,    17,    26,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,
      37,    -1,    39,    40,    41,    42,    43,    44,    45,    46,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      -1,    58,    59,    -1,    -1,    -1,    -1,    64,    65,    -1,
      67,    -1,    69,    70,    -1,    -1,    73,    74,    75,     3,
      -1,    -1,     6,    -1,    -1,    -1,    10,    -1,    -1,    -1,
      14,    -1,    -1,    -1,    18,    19,    20,    21,    -1,    23,
      -1,    25,    26,    -1,    -1,    -1,    20,    -1,    -1,    33,
      -1,    35,    36,    37,    -1,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    48,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    58,    59,    -1,    -1,    -1,    -1,
      64,    65,    -1,    67,     3,    69,    70,     6,    -1,    73,
      74,    10,    -1,    -1,    -1,    14,    -1,    -1,    -1,    18,
      19,    20,    21,    -1,    23,    -1,    25,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    -1,    35,    36,    37,    47,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    57,
      58,    59,    60,    61,    62,    63,    -1,    -1,    -1,    58,
      59,    69,    70,    -1,    72,    64,    65,    -1,    67,     3,
      69,    70,     6,    -1,    73,    74,    -1,    -1,    -1,    -1,
      14,    -1,    -1,    17,    -1,    -1,    20,    21,    -1,    23,
      -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    47,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    58,    59,    60,    61,    62,
      63,    -1,    -1,    -1,    58,    59,    69,    70,    -1,    72,
      64,    65,    -1,    67,    68,    69,    70,    -1,     3,    73,
      74,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    14,
      -1,    -1,    17,    -1,    -1,    20,    21,    -1,    23,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    36,    37,    -1,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    -1,    -1,    -1,    -1,    64,
      65,    -1,    67,     3,    69,    70,     6,    -1,    73,    74,
      -1,    -1,    -1,    -1,    14,    -1,    -1,    17,    -1,    -1,
      20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    -1,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,
       3,    -1,     5,     6,    64,    65,    -1,    67,    -1,    69,
      70,    14,    -1,    73,    74,    -1,    -1,    20,    21,    -1,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    58,    59,     3,    -1,     5,
       6,    64,    65,    -1,    67,    -1,    69,    70,    14,    -1,
      73,    74,    -1,    -1,    20,    21,    -1,    23,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36,    37,    -1,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    58,    59,     3,    -1,    -1,     6,    64,    65,
      -1,    67,    -1,    69,    70,    14,    -1,    73,    74,    -1,
      -1,    20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,    -1,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      59,     3,    -1,    -1,     6,    64,    65,    -1,    67,    68,
      69,    70,    14,    -1,    73,    74,    -1,    -1,    20,    21,
      -1,    23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    36,    37,    -1,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    58,    59,    -1,    -1,
      -1,    -1,    64,    65,    -1,    67,    -1,    69,    70,    47,
      -1,    73,    74,    -1,    -1,    53,    54,    -1,    -1,    57,
      58,    59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,
      -1,    69,    70,    47,    72,    -1,    -1,    -1,    -1,    53,
      54,    79,    -1,    57,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    -1,    -1,    69,    70,    47,    72,    -1,
      -1,    -1,    -1,    53,    54,    79,    -1,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,    69,
      70,    47,    72,    -1,    -1,    -1,    -1,    53,    54,    79,
      -1,    57,    58,    59,    60,    61,    62,    63,    -1,    -1,
      -1,    -1,    -1,    69,    70,    -1,    72,    47,    -1,    -1,
      -1,    -1,    78,    53,    54,    -1,    -1,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    47,    -1,    69,
      70,    -1,    72,    53,    54,    -1,    76,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    47,    69,
      70,    -1,    72,    -1,    53,    54,    76,    56,    57,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    47,    48,
      69,    70,    71,    72,    53,    54,    -1,    -1,    57,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    47,    -1,
      69,    70,    -1,    72,    53,    54,    -1,    -1,    57,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    47,    -1,
      69,    70,    71,    72,    53,    54,    -1,    56,    57,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    47,    -1,
      69,    70,    -1,    72,    53,    54,    -1,    -1,    57,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    47,    -1,
      69,    70,    71,    72,    53,    54,    -1,    -1,    57,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,
      69,    70,    -1,    72
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    81,    82,    83,    84,    86,    20,    39,    40,
      41,    42,    43,    44,    45,    46,   144,     0,    84,    78,
     140,    23,   142,    75,    91,    23,     4,    13,    15,    22,
      85,    88,    89,    90,   109,   110,   111,   112,   114,   141,
     142,    20,   150,   144,    26,   152,    75,    92,    76,    90,
      48,     5,    78,    48,    78,    20,    93,    94,    95,    20,
      78,   151,   141,    17,    47,   143,   144,   145,   146,   147,
      50,    76,    77,    38,   143,   149,    78,   143,   144,   146,
     144,    74,    74,    21,    95,    73,   149,    48,    79,    79,
     136,   137,   138,   139,   152,    73,    71,    77,    77,    78,
     136,    48,    75,    99,   138,   152,   137,    16,   143,    71,
       3,     6,     7,    10,    11,    12,    14,    18,    19,    20,
      21,    25,    29,    30,    31,    32,    33,    35,    36,    37,
      48,    58,    59,    64,    65,    67,    69,    70,    73,    74,
      87,    96,    97,    98,    99,   100,   102,   103,   104,   105,
     106,   107,   111,   113,   118,   119,   120,   122,   123,   125,
     126,   127,   128,   129,   130,   131,   134,   135,   141,   144,
     151,   152,   153,    78,    48,    99,   152,   140,    73,   122,
     128,   134,    73,    73,   144,   146,   148,   122,    73,   122,
      78,    99,   122,   128,    75,   152,    75,   152,   122,   122,
     122,    75,   122,    65,   122,   122,   122,   143,   144,    73,
     115,   116,   117,   122,    76,    98,    50,    50,    47,    48,
      53,    54,    57,    58,    59,    60,    61,    62,    63,    69,
      70,    72,    48,    50,    74,    75,    50,    74,    75,     5,
      72,    73,    49,    50,    78,    91,    68,    73,   121,   122,
     124,   132,   133,   100,   121,    74,    74,    75,   122,    78,
     152,   152,   122,    75,   122,    71,    71,   116,   122,    79,
      77,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,    73,    74,    75,   151,   122,   122,   150,
     122,   122,   150,   151,   115,   122,   122,   143,   121,   121,
     122,    28,    51,    52,    71,    56,   121,    71,   122,   122,
     115,    71,    76,    76,    76,   122,   122,    71,   117,   122,
     115,   122,   150,    73,    79,    76,    79,    76,    73,    71,
      71,   143,   121,   121,    99,   122,    48,    99,    79,    79,
      76,    99,    76,    71,    79,    76,   115,   115,     8,     9,
     108,   101,   122,   123,    71,    71,    73,    99,    71,   121,
      99,    71,    99,   108
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

  case 81:
#line 500 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_ref(compiler, op_ref, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 82:
#line 505 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, (yyvsp[(1) - (4)].opval)->file, (yyvsp[(1) - (4)].opval)->line);
      (yyval.opval) = SPVM_OP_build_ref(compiler, op_ref, (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 87:
#line 516 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 89:
#line 523 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_constant(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 105:
#line 543 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 106:
#line 547 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 107:
#line 551 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 108:
#line 555 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 109:
#line 559 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 110:
#line 563 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 112:
#line 570 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 113:
#line 576 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new_object(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 114:
#line 580 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new_object(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 115:
#line 584 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new_object(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 116:
#line 588 "yacc/spvm_yacc.y"
    {
      // New
      SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);

      (yyval.opval) = SPVM_OP_build_new_object(compiler, op_new, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 117:
#line 595 "yacc/spvm_yacc.y"
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

  case 118:
#line 616 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 119:
#line 623 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, (yyvsp[(2) - (4)].opval)->file, (yyvsp[(2) - (4)].opval)->line);
      (yyval.opval) = SPVM_OP_build_convert(compiler, op_convert, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 120:
#line 630 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 121:
#line 634 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 122:
#line 638 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 123:
#line 644 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 124:
#line 650 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 125:
#line 655 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEGATE, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op_negate, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 126:
#line 660 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 127:
#line 665 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 128:
#line 670 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 129:
#line 675 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 130:
#line 680 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unop(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 131:
#line 686 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 132:
#line 691 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 133:
#line 696 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_concat(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 134:
#line 700 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 135:
#line 704 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 136:
#line 708 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 137:
#line 712 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 138:
#line 716 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 139:
#line 720 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 140:
#line 724 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 141:
#line 728 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 142:
#line 732 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 143:
#line 736 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 144:
#line 740 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 145:
#line 744 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 146:
#line 750 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 147:
#line 756 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_or(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 148:
#line 760 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_and(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 149:
#line 764 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_not(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 150:
#line 770 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 151:
#line 774 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 152:
#line 778 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 153:
#line 784 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, NULL, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 154:
#line 788 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 155:
#line 792 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_assignable_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_assignable_terms);
    ;}
    break;

  case 156:
#line 797 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 157:
#line 801 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_assignable_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_assignable_terms);
    ;}
    break;

  case 158:
#line 806 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[(2) - (5)].opval)->file, (yyvsp[(2) - (5)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (5)].opval), op_sub_name, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 159:
#line 813 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 160:
#line 817 "yacc/spvm_yacc.y"
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

  case 161:
#line 828 "yacc/spvm_yacc.y"
    {
       // Add invocant to arguments
       SPVM_OP* op_args = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
       SPVM_OP_insert_child(compiler, op_args, op_args->last, (yyvsp[(1) - (1)].opval));
       
       (yyval.opval) = op_args;
    ;}
    break;

  case 162:
#line 836 "yacc/spvm_yacc.y"
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

  case 163:
#line 855 "yacc/spvm_yacc.y"
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

  case 164:
#line 869 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 166:
#line 876 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 167:
#line 882 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 168:
#line 888 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 169:
#line 892 "yacc/spvm_yacc.y"
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

  case 170:
#line 905 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 171:
#line 909 "yacc/spvm_yacc.y"
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

  case 172:
#line 922 "yacc/spvm_yacc.y"
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

  case 178:
#line 945 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 179:
#line 949 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_byte_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 180:
#line 956 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_short_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 181:
#line 963 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_int_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 182:
#line 970 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_long_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 183:
#line 977 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_float_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 184:
#line 984 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_double_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 185:
#line 991 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_object_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 186:
#line 998 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_string_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 187:
#line 1007 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 188:
#line 1013 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 189:
#line 1017 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 190:
#line 1023 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_const_array_type(compiler, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 191:
#line 1029 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 192:
#line 1033 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 194:
#line 1041 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_void(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 197:
#line 1050 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 198:
#line 1056 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3275 "spvm_yacc.tab.c"
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


#line 1060 "yacc/spvm_yacc.y"


