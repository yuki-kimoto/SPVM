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
     ELSIF = 269,
     ELSE = 270,
     FOR = 271,
     WHILE = 272,
     LAST = 273,
     NEXT = 274,
     SWITCH = 275,
     CASE = 276,
     DEFAULT = 277,
     EVAL = 278,
     NAME = 279,
     VAR_NAME = 280,
     CONSTANT = 281,
     RETURN = 282,
     WEAKEN = 283,
     CROAK = 284,
     NEW = 285,
     UNDEF = 286,
     VOID = 287,
     BYTE = 288,
     SHORT = 289,
     INT = 290,
     LONG = 291,
     FLOAT = 292,
     DOUBLE = 293,
     STRING = 294,
     OBJECT = 295,
     AMPERSAND = 296,
     SPECIAL_ASSIGN = 297,
     ASSIGN = 298,
     OR = 299,
     AND = 300,
     BIT_XOR = 301,
     BIT_OR = 302,
     BIT_AND = 303,
     REL = 304,
     SHIFT = 305,
     REMAINDER = 306,
     DIVIDE = 307,
     MULTIPLY = 308,
     ISA = 309,
     DEREF = 310,
     REF = 311,
     UMINUS = 312,
     SCALAR = 313,
     NOT = 314,
     DEC = 315,
     INC = 316,
     ARROW = 317
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
#define ELSIF 269
#define ELSE 270
#define FOR 271
#define WHILE 272
#define LAST 273
#define NEXT 274
#define SWITCH 275
#define CASE 276
#define DEFAULT 277
#define EVAL 278
#define NAME 279
#define VAR_NAME 280
#define CONSTANT 281
#define RETURN 282
#define WEAKEN 283
#define CROAK 284
#define NEW 285
#define UNDEF 286
#define VOID 287
#define BYTE 288
#define SHORT 289
#define INT 290
#define LONG 291
#define FLOAT 292
#define DOUBLE 293
#define STRING 294
#define OBJECT 295
#define AMPERSAND 296
#define SPECIAL_ASSIGN 297
#define ASSIGN 298
#define OR 299
#define AND 300
#define BIT_XOR 301
#define BIT_OR 302
#define BIT_AND 303
#define REL 304
#define SHIFT 305
#define REMAINDER 306
#define DIVIDE 307
#define MULTIPLY 308
#define ISA 309
#define DEREF 310
#define REF 311
#define UMINUS 312
#define SCALAR 313
#define NOT 314
#define DEC 315
#define INC 316
#define ARROW 317




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
#line 252 "spvm_yacc.tab.c"

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
#define YYLAST   1451

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  70
/* YYNRULES -- Number of rules.  */
#define YYNRULES  194
/* YYNRULES -- Number of states.  */
#define YYNSTATES  365

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   317

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      69,    67,     2,    51,    75,    52,    53,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    73,    72,
       2,     2,     2,     2,    59,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    70,     2,    76,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    71,     2,    74,    58,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    54,    55,    56,    57,
      60,    61,    62,    63,    64,    65,    66,    68
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    13,    17,    21,
      27,    30,    35,    36,    38,    41,    43,    45,    47,    49,
      52,    54,    56,    60,    64,    65,    67,    71,    74,    76,
      78,    82,    83,    85,    88,    90,    92,    94,    96,    98,
     100,   102,   104,   106,   108,   112,   115,   118,   120,   130,
     136,   142,   146,   149,   156,   157,   160,   167,   174,   184,
     194,   203,   212,   215,   220,   223,   228,   229,   231,   235,
     241,   244,   248,   250,   253,   258,   262,   268,   271,   276,
     279,   284,   286,   288,   290,   292,   296,   298,   300,   302,
     304,   306,   308,   310,   312,   314,   316,   318,   320,   322,
     324,   326,   328,   330,   332,   335,   337,   340,   344,   348,
     350,   354,   357,   360,   366,   368,   370,   374,   379,   385,
     390,   395,   398,   401,   404,   407,   410,   413,   416,   419,
     423,   427,   431,   435,   439,   443,   447,   451,   455,   459,
     463,   467,   471,   475,   479,   483,   487,   491,   494,   500,
     505,   510,   515,   522,   526,   533,   537,   543,   544,   546,
     548,   552,   556,   559,   561,   565,   569,   570,   572,   575,
     577,   579,   581,   583,   585,   587,   589,   591,   593,   595,
     597,   599,   601,   603,   606,   610,   614,   617,   622,   627,
     629,   631,   633,   635,   637
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      78,     0,    -1,    79,    -1,    -1,    80,    -1,    80,    82,
      -1,    82,    -1,    10,   137,    72,    -1,     3,   137,    87,
      -1,     3,   137,    73,   134,    87,    -1,     3,    87,    -1,
       3,    73,   134,    87,    -1,    -1,    85,    -1,    85,    86,
      -1,    86,    -1,   104,    -1,   105,    -1,   107,    -1,   109,
      72,    -1,    81,    -1,   106,    -1,    71,    84,    74,    -1,
      71,    89,    74,    -1,    -1,    90,    -1,    90,    75,    91,
      -1,    90,    75,    -1,    91,    -1,    24,    -1,    24,    43,
      26,    -1,    -1,    93,    -1,    93,    94,    -1,    94,    -1,
      96,    -1,   102,    -1,    97,    -1,    98,    -1,    95,    -1,
      99,    -1,   100,    -1,   101,    -1,   146,    -1,    71,    92,
      74,    -1,   116,    72,    -1,   117,    72,    -1,    72,    -1,
      16,    69,   115,    72,   115,    72,   115,    67,    95,    -1,
      17,    69,   115,    67,    95,    -1,    20,    69,   116,    67,
      95,    -1,    21,   116,    73,    -1,    22,    73,    -1,    13,
      69,   115,    67,    95,   103,    -1,    -1,    15,    95,    -1,
      14,    69,   115,    67,    95,   103,    -1,     4,   143,    73,
     134,   136,    72,    -1,   134,     5,   144,    73,   142,    69,
     130,    67,    95,    -1,   134,     5,   144,    73,   142,    69,
     130,    67,    72,    -1,   134,     5,    73,   142,    69,   130,
      67,    95,    -1,   134,     5,    73,   142,    69,   130,    67,
      72,    -1,     7,    88,    -1,     8,   145,    73,   136,    -1,
       8,   145,    -1,     6,   145,    73,   136,    -1,    -1,   111,
      -1,   111,    75,   116,    -1,   111,    75,    69,   111,    67,
      -1,   111,    75,    -1,    69,   111,    67,    -1,   116,    -1,
      59,   116,    -1,    59,    71,   116,    74,    -1,    63,    59,
     116,    -1,    63,    59,    71,   116,    74,    -1,    60,   145,
      -1,    60,    71,   145,    74,    -1,    61,   145,    -1,    61,
      71,   145,    74,    -1,   116,    -1,   126,    -1,   127,    -1,
     118,    -1,    69,   115,    67,    -1,   145,    -1,    26,    -1,
      31,    -1,   129,    -1,   122,    -1,   128,    -1,   121,    -1,
     119,    -1,   120,    -1,   112,    -1,   108,    -1,   125,    -1,
     124,    -1,   114,    -1,   113,    -1,    18,    -1,    19,    -1,
      27,    -1,    27,   116,    -1,    29,    -1,    29,   116,    -1,
     122,    43,   116,    -1,   128,    43,   116,    -1,   123,    -1,
     115,    57,   136,    -1,    30,   137,    -1,    30,   141,    -1,
      30,   139,    71,   110,    74,    -1,    83,    -1,   106,    -1,
      70,   110,    76,    -1,    69,   136,    67,   116,    -1,   116,
      68,    71,   143,    74,    -1,   122,    71,   143,    74,    -1,
     128,    71,   143,    74,    -1,    28,   122,    -1,    51,   116,
      -1,    52,   116,    -1,    66,   116,    -1,   116,    66,    -1,
      65,   116,    -1,   116,    65,    -1,    58,   116,    -1,   116,
      51,   116,    -1,   116,    52,   116,    -1,   116,    53,   116,
      -1,   116,    56,   116,    -1,   116,    55,   116,    -1,   116,
      54,   116,    -1,   116,    46,   116,    -1,   116,    41,   116,
      -1,   116,    47,   116,    -1,   116,    50,   116,    -1,   108,
      43,   116,    -1,   145,    43,   116,    -1,   145,    42,   116,
      -1,    69,   116,    67,    -1,   113,    43,   116,    -1,   116,
      49,   116,    -1,   115,    44,   115,    -1,   115,    45,   115,
      -1,    64,   115,    -1,   116,    68,    70,   116,    76,    -1,
     128,    70,   116,    76,    -1,   122,    70,   116,    76,    -1,
     144,    69,   110,    67,    -1,   137,    68,   144,    69,   110,
      67,    -1,   137,    68,   144,    -1,   116,    68,   144,    69,
     110,    67,    -1,   116,    68,   144,    -1,   116,    68,    69,
     110,    67,    -1,    -1,   131,    -1,   133,    -1,   133,    75,
     131,    -1,   131,    75,   132,    -1,   131,    75,    -1,   132,
      -1,   145,    73,   136,    -1,   145,    73,     9,    -1,    -1,
     135,    -1,   135,    11,    -1,    11,    -1,   137,    -1,   139,
      -1,   140,    -1,   138,    -1,    24,    -1,    33,    -1,    34,
      -1,    35,    -1,    36,    -1,    37,    -1,    38,    -1,    40,
      -1,    39,    -1,    41,   137,    -1,   137,    70,    76,    -1,
     139,    70,    76,    -1,    12,   139,    -1,   137,    70,   116,
      76,    -1,   139,    70,   116,    76,    -1,   136,    -1,    32,
      -1,    24,    -1,    24,    -1,    25,    -1,    23,    95,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    67,    67,    76,    79,    92,   106,   109,   115,   119,
     125,   129,   136,   139,   151,   165,   168,   169,   170,   171,
     172,   173,   176,   184,   193,   196,   209,   223,   227,   230,
     234,   241,   244,   257,   271,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   285,   293,   297,   301,   307,   313,
     319,   325,   331,   334,   348,   351,   355,   361,   367,   371,
     377,   382,   389,   395,   399,   405,   412,   415,   428,   442,
     467,   471,   475,   481,   486,   491,   496,   503,   507,   513,
     518,   525,   526,   527,   528,   529,   535,   536,   540,   541,
     542,   543,   544,   545,   546,   547,   548,   549,   550,   551,
     552,   555,   556,   557,   560,   564,   568,   572,   576,   580,
     583,   589,   593,   597,   601,   608,   629,   636,   643,   647,
     651,   657,   663,   668,   673,   678,   683,   688,   693,   699,
     704,   709,   713,   717,   721,   725,   729,   733,   737,   741,
     745,   749,   753,   757,   763,   769,   773,   777,   783,   787,
     791,   797,   801,   805,   810,   814,   819,   827,   830,   841,
     849,   868,   882,   886,   889,   895,   902,   905,   918,   932,
     935,   936,   937,   938,   941,   945,   952,   959,   966,   973,
     980,   987,   994,  1003,  1009,  1013,  1019,  1025,  1029,  1036,
    1037,  1042,  1043,  1046,  1052
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PACKAGE", "HAS", "SUB", "OUR", "ENUM",
  "MY", "SELF", "USE", "DESCRIPTOR", "CONST", "IF", "ELSIF", "ELSE", "FOR",
  "WHILE", "LAST", "NEXT", "SWITCH", "CASE", "DEFAULT", "EVAL", "NAME",
  "VAR_NAME", "CONSTANT", "RETURN", "WEAKEN", "CROAK", "NEW", "UNDEF",
  "VOID", "BYTE", "SHORT", "INT", "LONG", "FLOAT", "DOUBLE", "STRING",
  "OBJECT", "AMPERSAND", "SPECIAL_ASSIGN", "ASSIGN", "OR", "AND",
  "BIT_XOR", "BIT_OR", "BIT_AND", "REL", "SHIFT", "'+'", "'-'", "'.'",
  "REMAINDER", "DIVIDE", "MULTIPLY", "ISA", "'~'", "'@'", "DEREF", "REF",
  "UMINUS", "SCALAR", "NOT", "DEC", "INC", "')'", "ARROW", "'('", "'['",
  "'{'", "';'", "':'", "'}'", "','", "']'", "$accept", "grammar",
  "opt_packages", "packages", "use", "package", "anon_package",
  "opt_declarations", "declarations", "declaration", "package_block",
  "enumeration_block", "opt_enumeration_values", "enumeration_values",
  "enumeration_value", "opt_statements", "statements", "statement",
  "block", "normal_statement", "for_statement", "while_statement",
  "switch_statement", "case_statement", "default_statement",
  "if_statement", "else_statement", "has", "sub", "anon_sub",
  "enumeration", "my_var", "package_var", "opt_assignable_terms",
  "assignable_terms", "array_length", "deref", "ref", "term",
  "assignable_term", "expression", "isa", "new", "array_init",
  "convert_type", "field_access", "weaken_field", "unop", "binop",
  "relative_term", "logical_term", "array_access", "call_sub", "opt_args",
  "args", "arg", "invocant", "opt_descriptors", "descriptors", "type",
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,    43,    45,    46,   306,   307,   308,   309,   126,    64,
     310,   311,   312,   313,   314,   315,   316,    41,   317,    40,
      91,   123,    59,    58,   125,    44,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    77,    78,    79,    79,    80,    80,    81,    82,    82,
      83,    83,    84,    84,    85,    85,    86,    86,    86,    86,
      86,    86,    87,    88,    89,    89,    90,    90,    90,    91,
      91,    92,    92,    93,    93,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    95,    96,    96,    96,    97,    98,
      99,   100,   101,   102,   103,   103,   103,   104,   105,   105,
     106,   106,   107,   108,   108,   109,   110,   110,   111,   111,
     111,   111,   111,   112,   112,   112,   112,   113,   113,   114,
     114,   115,   115,   115,   115,   115,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     118,   119,   119,   119,   119,   119,   120,   121,   122,   122,
     122,   123,   124,   124,   124,   124,   124,   124,   124,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   126,   127,   127,   127,   128,   128,
     128,   129,   129,   129,   129,   129,   129,   130,   130,   130,
     130,   131,   131,   131,   132,   133,   134,   134,   135,   135,
     136,   136,   136,   136,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   138,   139,   139,   140,   141,   141,   142,
     142,   143,   144,   145,   146
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     3,     3,     5,
       2,     4,     0,     1,     2,     1,     1,     1,     1,     2,
       1,     1,     3,     3,     0,     1,     3,     2,     1,     1,
       3,     0,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     2,     2,     1,     9,     5,
       5,     3,     2,     6,     0,     2,     6,     6,     9,     9,
       8,     8,     2,     4,     2,     4,     0,     1,     3,     5,
       2,     3,     1,     2,     4,     3,     5,     2,     4,     2,
       4,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     2,     3,     3,     1,
       3,     2,     2,     5,     1,     1,     3,     4,     5,     4,
       4,     2,     2,     2,     2,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     5,     4,
       4,     4,     6,     3,     6,     3,     5,     0,     1,     1,
       3,     3,     2,     1,     3,     3,     0,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     3,     2,     4,     4,     1,
       1,     1,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     2,     4,     6,   174,   175,   176,   177,
     178,   179,   180,   182,   181,     0,     1,     5,    12,   166,
       8,     0,     0,     0,     0,   169,    20,     0,    13,    15,
      16,    17,    21,    18,     0,     0,   167,     0,   191,     0,
     193,     0,    24,    62,     0,    22,    14,    19,     0,   168,
       9,   166,     0,    29,     0,    25,    28,     7,   192,     0,
       0,     0,     0,     0,    65,   170,   173,   171,   172,     0,
      23,    27,   190,   189,     0,     0,     0,     0,   186,   183,
       0,     0,    30,    26,   157,     0,    57,   184,   185,     0,
     158,   163,   159,     0,   157,     0,   162,     0,     0,     0,
      31,    61,    60,   161,     0,   160,   165,   164,     0,     0,
       0,     0,     0,     0,   101,   102,     0,   166,     0,     0,
     174,    87,   103,   166,   105,     0,    88,   166,   166,   166,
     166,     0,     0,     0,   166,   166,   166,    66,    47,   114,
       0,    32,    34,    39,    35,    37,    38,    40,    41,    42,
      36,   115,    96,    95,   100,    99,     0,     0,    93,    94,
      92,    90,   109,    98,    97,    91,    89,     0,     0,     0,
      86,    43,     0,    59,    58,   166,    10,    64,   166,   166,
     166,   166,     0,    90,    91,    52,   194,   104,     0,    90,
     106,   111,     0,   112,   122,   123,   128,   166,    73,     0,
      77,     0,    79,   166,   126,   124,     0,     0,   170,   166,
       0,    67,    72,    44,    33,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   127,   125,     0,
      45,    46,   166,   166,     0,   166,   166,     0,     0,     0,
      66,   166,   166,     0,     0,   166,   166,     0,    81,    84,
      82,    83,     0,     0,     0,    51,   166,   166,    66,     0,
       0,     0,   166,    75,   142,   166,     0,    72,   116,    70,
     139,   143,   136,   135,   137,   138,   129,   130,   131,   134,
     133,   132,    66,   166,     0,   155,   107,     0,     0,   108,
       0,     0,   153,     0,   141,   140,    11,    63,   147,     0,
      81,   166,   166,     0,     0,   166,   166,     0,     0,     0,
       0,     0,    74,    78,    80,     0,   117,    71,   166,    68,
       0,     0,     0,    66,   150,   119,   149,   120,    66,   151,
      85,   145,   146,   110,    54,   144,     0,    49,    50,   187,
     188,   113,    76,     0,   156,   148,   118,     0,     0,     0,
       0,    53,   166,    69,   154,   152,   166,    55,     0,     0,
       0,     0,    48,    54,    56
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    26,     5,   139,    27,    28,    29,
      20,    43,    54,    55,    56,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   351,    30,    31,   151,
      33,   152,    34,   210,   211,   153,   154,   155,   247,   248,
     157,   249,   158,   159,   160,   183,   162,   163,   164,   250,
     251,   184,   166,    89,    90,    91,    92,   167,    36,   207,
     168,    66,    67,    68,   193,    74,    39,   169,   170,   171
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -230
static const yytype_int16 yypact[] =
{
      27,   544,    34,  -230,    27,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,   -38,  -230,  -230,   115,    33,
    -230,    62,    43,    56,   544,  -230,  -230,    57,   115,  -230,
    -230,  -230,  -230,  -230,    35,   131,   133,    76,  -230,    81,
    -230,    85,   125,  -230,    98,  -230,  -230,  -230,   -17,  -230,
    -230,    33,   444,   136,   119,   121,  -230,  -230,  -230,   480,
     126,   444,   544,   544,  -230,   124,  -230,   139,  -230,   191,
    -230,   125,  -230,  -230,   155,   480,   153,   124,   139,  -230,
     152,   156,  -230,  -230,    43,   160,  -230,  -230,  -230,   164,
     158,  -230,   161,   162,    43,   -34,    43,    43,   310,   172,
     371,  -230,  -230,  -230,   167,   158,  -230,  -230,     8,    25,
      43,   173,   175,   182,  -230,  -230,   183,  1024,   180,   184,
     188,  -230,   760,  1024,   760,   544,  -230,  1024,  1024,  1024,
     436,   -12,    -8,   199,  1024,  1024,   628,   828,  -230,  -230,
     185,   371,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,   218,  -230,   222,  -230,  1237,   207,  -230,  -230,
    -230,   -25,  -230,  -230,  -230,     5,  -230,   275,   213,   215,
      30,  -230,   444,  -230,  -230,    33,  -230,   209,   892,   892,
     892,  1024,  1209,    20,    90,  -230,  -230,  1357,  1357,    13,
    1357,   216,    96,  -230,    91,    91,    91,  1024,    91,    43,
    -230,    43,  -230,   500,   107,   107,  1288,   220,    44,   692,
     219,   210,  1357,  -230,  -230,  1024,  1024,  1024,  1024,  1024,
    1024,  1024,  1024,  1024,  1024,  1024,  1024,  -230,  -230,     0,
    -230,  -230,  1024,  1024,    62,  1024,  1024,    62,   221,   267,
     828,  1024,  1024,    76,   444,   892,   564,   159,  1311,  -230,
    -230,  -230,     9,   193,  1334,  -230,   238,   302,   828,  1157,
     226,   232,  1024,    91,  -230,  1024,   -39,  1288,  -230,   960,
    1357,  1357,  1364,  1364,  1364,  1383,   488,   488,   488,    91,
      91,    91,   828,  1024,    62,   223,  1357,    87,   235,  1357,
    1045,   237,   243,   248,  1357,  1357,  -230,  -230,  -230,   313,
    1265,   892,   892,   444,   184,  1024,   892,   184,   184,  1073,
    1101,   242,  -230,  -230,  -230,  1183,    36,  -230,   692,  1357,
     251,  1129,   246,   828,  -230,  -230,  -230,  -230,   828,  -230,
    -230,   -30,   264,  -230,   163,  1357,    73,  -230,  -230,  -230,
    -230,  -230,  -230,   -28,  -230,  -230,  -230,   256,   257,   260,
     184,  -230,   892,  -230,  -230,  -230,   892,  -230,   368,   465,
     184,   184,  -230,   163,  -230
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -230,  -230,  -230,  -230,  -230,   321,  -230,  -230,  -230,   303,
     -31,  -230,  -230,  -230,   259,  -230,  -230,   211,   -94,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,    -7,  -230,  -230,     3,
    -230,  -230,  -230,  -218,  -207,  -230,  -230,  -230,  -137,   -35,
    -230,  -230,  -230,  -230,  -230,   -91,  -230,  -230,  -230,  -230,
    -230,   -84,  -230,   261,   262,   268,  -230,     1,  -230,   -49,
      -1,  -230,   -58,  -230,  -230,   291,  -229,   -37,    19,  -230
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -193
static const yytype_int16 yytable[] =
{
      15,   102,   266,    64,    78,   288,    50,    58,   291,   161,
      73,    60,    76,    40,   174,   302,   165,    40,   232,    35,
      37,    32,   293,    44,    58,   186,    73,   303,   317,    35,
       1,    32,   189,    18,    16,    19,   269,   100,   101,   353,
     311,    41,   252,   253,    25,   233,   234,   269,   235,   107,
     161,    65,    61,   301,   302,   322,    59,   165,    65,   199,
      65,    77,    79,   201,   320,   156,   303,   192,    40,   282,
     283,   284,   241,   242,    65,   236,   237,   217,   176,   100,
     173,   306,   182,   233,   234,  -121,    38,   187,   188,   190,
     233,   234,   194,   195,   196,   198,    18,    65,   175,   204,
     205,   206,   212,    93,   229,   347,   156,    47,   298,   299,
     348,   343,   239,    93,    80,   104,   104,   301,   302,    21,
    -166,    22,    23,   107,   191,    24,    25,    42,   217,   177,
     303,    45,   217,   218,   219,   208,    48,   220,   221,   222,
     223,   224,   225,   226,    49,   352,   254,    18,   217,    53,
     200,   202,   227,   228,    51,   229,   227,   228,    52,   229,
     236,   237,   259,   324,   331,   332,   257,   258,   263,   336,
      57,    65,  -193,  -193,   267,   229,   243,   349,   350,    69,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   285,    70,    80,   297,    71,   286,   287,    75,
     289,   290,   292,   301,   302,   212,   294,   295,   208,    81,
     334,   300,   296,   337,   338,   358,   303,    82,   260,   359,
     261,   309,   310,   212,    84,    86,   304,   315,    87,    94,
     316,    95,    88,    96,   319,    98,    97,   301,   302,   108,
     172,   109,   178,    65,   179,   208,   110,   212,   321,    25,
     303,   180,   181,   185,   333,   100,   357,  -192,   203,   213,
     307,   215,   120,    40,   121,   216,   362,   363,   125,   126,
     335,     7,     8,     9,    10,    11,    12,    13,    14,   231,
     238,   239,   244,   267,   240,   269,   256,   265,   212,   127,
     128,    58,   323,   212,    59,   268,   129,   130,   131,   132,
     313,   133,    65,   134,   135,   109,   314,   136,   137,   325,
     110,   327,   328,    25,    87,   329,   341,   208,   344,   106,
     346,   303,    62,   354,   355,    17,   120,    40,   121,   356,
      83,    46,   125,   126,     6,     7,     8,     9,    10,    11,
      12,    13,    14,     7,     8,     9,    10,    11,    12,    13,
      14,    63,   214,   127,   128,    99,   364,   301,   302,   105,
     129,   130,   131,   132,   103,   133,    85,   134,   135,     0,
     303,   136,   137,     0,   109,     0,  -166,     0,    88,   110,
     330,     0,    25,     0,   111,     0,     0,   112,   113,   114,
     115,   116,   117,   118,   119,   120,    40,   121,   122,   123,
     124,   125,   126,     0,     7,     8,     9,    10,    11,    12,
      13,    14,   301,   302,     0,     0,     0,     0,     0,     0,
       0,     0,   127,   128,     0,   303,     0,     0,     0,   129,
     130,   131,   132,     0,   133,   360,   134,   135,     0,   109,
     136,   137,   100,   138,   110,     0,     0,    25,     0,     0,
       0,     0,     0,     0,     0,     0,    62,     0,     0,     0,
     120,    40,   121,     0,     0,     0,   125,   126,     6,     7,
       8,     9,    10,    11,    12,    13,    14,     7,     8,     9,
      10,    11,    12,    13,    14,    63,     0,   127,   128,     0,
       0,     0,    62,     0,   129,   130,   131,   132,     0,   133,
       0,   134,   135,   109,     6,   136,   137,   197,   110,   301,
     302,    25,    72,     7,     8,     9,    10,    11,    12,    13,
      14,    63,   303,     0,   120,    40,   121,     0,     0,   217,
     125,   126,   361,     7,     8,     9,    10,    11,    12,    13,
      14,     0,   224,   225,   226,     0,     0,     0,     0,     0,
       0,   127,   128,   227,   228,     0,   229,     0,   129,   130,
     131,   132,     0,   133,     0,   134,   135,   109,     6,   136,
     137,   262,   110,     0,     0,    25,    62,     7,     8,     9,
      10,    11,    12,    13,    14,     0,     0,     0,   120,    40,
     121,     0,     0,     0,   125,   126,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    63,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   127,   128,     0,     0,     0,
       0,     0,   129,   130,   131,   132,     0,   133,   245,   134,
     135,   109,     0,   246,   137,     0,   110,     0,     0,    25,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   120,    40,   121,     0,     0,     0,   125,   126,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    63,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   127,
     128,     0,     0,     0,     0,     0,   129,   130,   131,   132,
       0,   133,     0,   134,   135,   109,     0,   136,   137,     0,
     110,     0,     0,    25,    62,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   120,    40,   121,     0,
       0,     0,   125,   126,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    63,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   127,   128,     0,     0,     0,     0,     0,
     129,   130,   131,   132,     0,   133,     0,   134,   135,     0,
       0,   209,   137,   109,     0,  -166,     0,     0,   110,     0,
       0,    25,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   120,    40,   121,     0,     0,     0,
     125,   126,     0,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   127,   128,     0,     0,     0,     0,     0,   129,   130,
     131,   132,     0,   133,     0,   134,   135,     0,     0,   136,
     137,   109,     0,  -166,     0,     0,   110,     0,     0,    25,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   120,    40,   121,     0,     0,     0,   125,   126,
       0,     7,     8,     9,    10,    11,    12,    13,    14,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   127,
     128,     0,     0,     0,     0,     0,   129,   130,   131,   132,
       0,   133,     0,   134,   135,   109,     0,   209,   137,     0,
     110,     0,     0,    25,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   120,    40,   121,     0,
       0,     0,   125,   126,     0,     7,     8,     9,    10,    11,
      12,    13,    14,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   127,   128,     0,     0,     0,     0,     0,
     129,   130,   131,   132,     0,   133,   245,   134,   135,     0,
       0,   246,   137,   109,     0,  -166,     0,     0,   110,     0,
       0,    25,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   120,    40,   121,     0,     0,     0,
     125,   126,     0,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   127,   128,     0,     0,     0,     0,     0,   129,   130,
     131,   132,     0,   133,     0,   134,   135,   109,     0,   318,
     137,     0,   110,     0,     0,    25,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   120,    40,
     121,     0,     0,     0,   125,   126,     0,     7,     8,     9,
      10,    11,    12,    13,    14,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   127,   128,     0,     0,     0,
       0,     0,   129,   130,   131,   132,   217,   133,     0,   134,
     135,   218,   219,   136,   137,   220,   221,   222,   223,   224,
     225,   226,     0,     0,     0,     0,     0,     0,     0,     0,
     227,   228,     0,   229,   217,     0,     0,     0,     0,   218,
     219,   326,     0,   220,   221,   222,   223,   224,   225,   226,
       0,     0,     0,     0,     0,     0,     0,     0,   227,   228,
       0,   229,   217,     0,     0,     0,     0,   218,   219,   339,
       0,   220,   221,   222,   223,   224,   225,   226,     0,     0,
       0,     0,     0,     0,     0,     0,   227,   228,     0,   229,
     217,     0,     0,     0,     0,   218,   219,   340,     0,   220,
     221,   222,   223,   224,   225,   226,     0,     0,     0,     0,
       0,     0,     0,     0,   227,   228,     0,   229,   217,     0,
       0,     0,     0,   218,   219,   345,     0,   220,   221,   222,
     223,   224,   225,   226,     0,     0,     0,     0,     0,     0,
       0,     0,   227,   228,   217,   229,     0,     0,     0,   218,
     219,   312,     0,   220,   221,   222,   223,   224,   225,   226,
       0,     0,     0,     0,     0,     0,     0,     0,   227,   228,
     217,   229,     0,     0,     0,   218,   219,   342,     0,   220,
     221,   222,   223,   224,   225,   226,     0,     0,     0,     0,
       0,     0,     0,     0,   227,   228,     0,   229,   217,     0,
       0,     0,   255,   218,   219,     0,     0,   220,   221,   222,
     223,   224,   225,   226,     0,     0,     0,     0,     0,     0,
       0,     0,   227,   228,     0,   229,   217,     0,     0,   230,
       0,   218,   219,     0,   305,   220,   221,   222,   223,   224,
     225,   226,     0,     0,     0,     0,     0,     0,     0,   217,
     227,   228,   264,   229,   218,   219,     0,     0,   220,   221,
     222,   223,   224,   225,   226,     0,     0,     0,     0,     0,
       0,     0,   217,   227,   228,   264,   229,   218,   219,     0,
     305,   220,   221,   222,   223,   224,   225,   226,     0,     0,
       0,     0,     0,     0,     0,   217,   227,   228,     0,   229,
     218,   219,     0,     0,   220,   221,   222,   223,   224,   225,
     226,     0,     0,     0,     0,     0,     0,     0,   217,   227,
     228,   308,   229,   218,   219,   217,     0,   220,   221,   222,
     223,   224,   225,   226,   220,   221,   222,   223,   224,   225,
     226,     0,   227,   228,   217,   229,     0,     0,     0,   227,
     228,     0,   229,     0,   221,   222,   223,   224,   225,   226,
       0,     0,     0,     0,     0,     0,     0,     0,   227,   228,
       0,   229
};

static const yytype_int16 yycheck[] =
{
       1,    95,   209,    52,    62,   234,    37,    24,   237,   100,
      59,    48,    61,    25,   108,    45,   100,    25,    43,    18,
      19,    18,   240,    24,    24,   119,    75,    57,    67,    28,
       3,    28,   123,    71,     0,    73,    75,    71,    72,    67,
     258,    22,   179,   180,    11,    70,    71,    75,    43,    98,
     141,    52,    51,    44,    45,   284,    73,   141,    59,    71,
      61,    62,    63,    71,   282,   100,    57,   125,    25,    69,
      70,    71,    42,    43,    75,    70,    71,    41,   109,    71,
      72,    72,   117,    70,    71,    72,    24,   122,   123,   124,
      70,    71,   127,   128,   129,   130,    71,    98,    73,   134,
     135,   136,   137,    84,    68,   323,   141,    72,   245,   246,
     328,   318,    68,    94,    70,    96,    97,    44,    45,     4,
       5,     6,     7,   172,   125,    10,    11,    71,    41,   110,
      57,    74,    41,    46,    47,   136,     5,    50,    51,    52,
      53,    54,    55,    56,    11,    72,   181,    71,    41,    24,
     131,   132,    65,    66,    73,    68,    65,    66,    73,    68,
      70,    71,   197,    76,   301,   302,    70,    71,   203,   306,
      72,   172,    65,    66,   209,    68,   175,    14,    15,    43,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   229,    74,    70,   244,    75,   232,   233,    73,
     235,   236,   239,    44,    45,   240,   241,   242,   209,    70,
     304,   246,   243,   307,   308,   352,    57,    26,   199,   356,
     201,   256,   257,   258,    69,    72,    67,   262,    76,    69,
     265,    67,    76,    75,   269,    73,    75,    44,    45,    67,
      73,     3,    69,   244,    69,   246,     8,   282,   283,    11,
      57,    69,    69,    73,   303,    71,   350,    69,    59,    74,
      67,    43,    24,    25,    26,    43,   360,   361,    30,    31,
     305,    33,    34,    35,    36,    37,    38,    39,    40,    72,
       5,    68,    73,   318,    69,    75,    70,    67,   323,    51,
      52,    24,    69,   328,    73,    76,    58,    59,    60,    61,
      74,    63,   303,    65,    66,     3,    74,    69,    70,    74,
       8,    74,    69,    11,    76,    67,    74,   318,    67,     9,
      74,    57,    12,    67,    67,     4,    24,    25,    26,    69,
      71,    28,    30,    31,    24,    33,    34,    35,    36,    37,
      38,    39,    40,    33,    34,    35,    36,    37,    38,    39,
      40,    41,   141,    51,    52,    94,   363,    44,    45,    97,
      58,    59,    60,    61,    96,    63,    75,    65,    66,    -1,
      57,    69,    70,    -1,     3,    -1,     5,    -1,    76,     8,
      67,    -1,    11,    -1,    13,    -1,    -1,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    52,    -1,    57,    -1,    -1,    -1,    58,
      59,    60,    61,    -1,    63,    67,    65,    66,    -1,     3,
      69,    70,    71,    72,     8,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    24,    33,
      34,    35,    36,    37,    38,    39,    40,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    -1,    51,    52,    -1,
      -1,    -1,    12,    -1,    58,    59,    60,    61,    -1,    63,
      -1,    65,    66,     3,    24,    69,    70,    71,     8,    44,
      45,    11,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    57,    -1,    24,    25,    26,    -1,    -1,    41,
      30,    31,    67,    33,    34,    35,    36,    37,    38,    39,
      40,    -1,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    52,    65,    66,    -1,    68,    -1,    58,    59,
      60,    61,    -1,    63,    -1,    65,    66,     3,    24,    69,
      70,    71,     8,    -1,    -1,    11,    12,    33,    34,    35,
      36,    37,    38,    39,    40,    -1,    -1,    -1,    24,    25,
      26,    -1,    -1,    -1,    30,    31,    -1,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    -1,
      -1,    -1,    58,    59,    60,    61,    -1,    63,    64,    65,
      66,     3,    -1,    69,    70,    -1,     8,    -1,    -1,    11,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,
      52,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,
      -1,    63,    -1,    65,    66,     3,    -1,    69,    70,    -1,
       8,    -1,    -1,    11,    12,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,
      58,    59,    60,    61,    -1,    63,    -1,    65,    66,    -1,
      -1,    69,    70,     3,    -1,     5,    -1,    -1,     8,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    -1,    63,    -1,    65,    66,    -1,    -1,    69,
      70,     3,    -1,     5,    -1,    -1,     8,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,
      52,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,
      -1,    63,    -1,    65,    66,     3,    -1,    69,    70,    -1,
       8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,
      58,    59,    60,    61,    -1,    63,    64,    65,    66,    -1,
      -1,    69,    70,     3,    -1,     5,    -1,    -1,     8,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    -1,    63,    -1,    65,    66,     3,    -1,    69,
      70,    -1,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,
      26,    -1,    -1,    -1,    30,    31,    -1,    33,    34,    35,
      36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    -1,
      -1,    -1,    58,    59,    60,    61,    41,    63,    -1,    65,
      66,    46,    47,    69,    70,    50,    51,    52,    53,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    -1,    68,    41,    -1,    -1,    -1,    -1,    46,
      47,    76,    -1,    50,    51,    52,    53,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      -1,    68,    41,    -1,    -1,    -1,    -1,    46,    47,    76,
      -1,    50,    51,    52,    53,    54,    55,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    -1,    68,
      41,    -1,    -1,    -1,    -1,    46,    47,    76,    -1,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    -1,    68,    41,    -1,
      -1,    -1,    -1,    46,    47,    76,    -1,    50,    51,    52,
      53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    41,    68,    -1,    -1,    -1,    46,
      47,    74,    -1,    50,    51,    52,    53,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      41,    68,    -1,    -1,    -1,    46,    47,    74,    -1,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    -1,    68,    41,    -1,
      -1,    -1,    73,    46,    47,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    -1,    68,    41,    -1,    -1,    72,
      -1,    46,    47,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      65,    66,    67,    68,    46,    47,    -1,    -1,    50,    51,
      52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    65,    66,    67,    68,    46,    47,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    65,    66,    -1,    68,
      46,    47,    -1,    -1,    50,    51,    52,    53,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    65,
      66,    67,    68,    46,    47,    41,    -1,    50,    51,    52,
      53,    54,    55,    56,    50,    51,    52,    53,    54,    55,
      56,    -1,    65,    66,    41,    68,    -1,    -1,    -1,    65,
      66,    -1,    68,    -1,    51,    52,    53,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      -1,    68
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    78,    79,    80,    82,    24,    33,    34,    35,
      36,    37,    38,    39,    40,   137,     0,    82,    71,    73,
      87,     4,     6,     7,    10,    11,    81,    84,    85,    86,
     104,   105,   106,   107,   109,   134,   135,   134,    24,   143,
      25,   145,    71,    88,   137,    74,    86,    72,     5,    11,
      87,    73,    73,    24,    89,    90,    91,    72,    24,    73,
     144,   134,    12,    41,   136,   137,   138,   139,   140,    43,
      74,    75,    32,   136,   142,    73,   136,   137,   139,   137,
      70,    70,    26,    91,    69,   142,    72,    76,    76,   130,
     131,   132,   133,   145,    69,    67,    75,    75,    73,   130,
      71,    72,    95,   132,   145,   131,     9,   136,    67,     3,
       8,    13,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    26,    27,    28,    29,    30,    31,    51,    52,    58,
      59,    60,    61,    63,    65,    66,    69,    70,    72,    83,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   106,   108,   112,   113,   114,   116,   117,   119,   120,
     121,   122,   123,   124,   125,   128,   129,   134,   137,   144,
     145,   146,    73,    72,    95,    73,    87,   145,    69,    69,
      69,    69,   116,   122,   128,    73,    95,   116,   116,   122,
     116,   137,   139,   141,   116,   116,   116,    71,   116,    71,
     145,    71,   145,    59,   116,   116,   116,   136,   137,    69,
     110,   111,   116,    74,    94,    43,    43,    41,    46,    47,
      50,    51,    52,    53,    54,    55,    56,    65,    66,    68,
      72,    72,    43,    70,    71,    43,    70,    71,     5,    68,
      69,    42,    43,   134,    73,    64,    69,   115,   116,   118,
     126,   127,   115,   115,   116,    73,    70,    70,    71,   116,
     145,   145,    71,   116,    67,    67,   111,   116,    76,    75,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,    69,    70,    71,   144,   116,   116,   143,   116,
     116,   143,   144,   110,   116,   116,    87,   136,   115,   115,
     116,    44,    45,    57,    67,    49,    72,    67,    67,   116,
     116,   110,    74,    74,    74,   116,   116,    67,    69,   116,
     110,   116,   143,    69,    76,    74,    76,    74,    69,    67,
      67,   115,   115,   136,    95,   116,   115,    95,    95,    76,
      76,    74,    74,   111,    67,    76,    74,   110,   110,    14,
      15,   103,    72,    67,    67,    67,    69,    95,   115,   115,
      67,    67,    95,    95,   103
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
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 8:
#line 116 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval), (yyvsp[(3) - (3)].opval), NULL);
    ;}
    break;

  case 9:
#line 120 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(5) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 10:
#line 126 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (2)].opval), NULL, (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 11:
#line 130 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (4)].opval), NULL, (yyvsp[(4) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 12:
#line 136 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 13:
#line 140 "yacc/spvm_yacc.y"
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
#line 152 "yacc/spvm_yacc.y"
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

  case 22:
#line 177 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_class_block;
    ;}
    break;

  case 23:
#line 185 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_enum_block;
    ;}
    break;

  case 24:
#line 193 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 25:
#line 197 "yacc/spvm_yacc.y"
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
#line 210 "yacc/spvm_yacc.y"
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
#line 224 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 29:
#line 231 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 30:
#line 235 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 31:
#line 241 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 32:
#line 245 "yacc/spvm_yacc.y"
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

  case 33:
#line 258 "yacc/spvm_yacc.y"
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

  case 44:
#line 286 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_block;
    ;}
    break;

  case 45:
#line 294 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 46:
#line 298 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 47:
#line 302 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 48:
#line 308 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[(1) - (9)].opval), (yyvsp[(3) - (9)].opval), (yyvsp[(5) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(9) - (9)].opval));
    ;}
    break;

  case 49:
#line 314 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 50:
#line 320 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 51:
#line 326 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 53:
#line 335 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (6)].opval)->file, (yyvsp[(1) - (6)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    ;}
    break;

  case 54:
#line 348 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 55:
#line 352 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (2)].opval);
    ;}
    break;

  case 56:
#line 356 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
    ;}
    break;

  case 57:
#line 362 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_has(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(2) - (6)].opval), (yyvsp[(4) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 58:
#line 368 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (9)].opval), (yyvsp[(3) - (9)].opval), (yyvsp[(5) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(1) - (9)].opval), (yyvsp[(9) - (9)].opval));
     ;}
    break;

  case 59:
#line 372 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (9)].opval), (yyvsp[(3) - (9)].opval), (yyvsp[(5) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(1) - (9)].opval), NULL);
     ;}
    break;

  case 60:
#line 378 "yacc/spvm_yacc.y"
    {
       SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[(2) - (8)].opval)->file, (yyvsp[(2) - (8)].opval)->line);
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (8)].opval), op_sub_name, (yyvsp[(4) - (8)].opval), (yyvsp[(6) - (8)].opval), (yyvsp[(1) - (8)].opval), (yyvsp[(8) - (8)].opval));
     ;}
    break;

  case 61:
#line 383 "yacc/spvm_yacc.y"
    {
       SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[(2) - (8)].opval)->file, (yyvsp[(2) - (8)].opval)->line);
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (8)].opval), op_sub_name, (yyvsp[(4) - (8)].opval), (yyvsp[(6) - (8)].opval), (yyvsp[(1) - (8)].opval), NULL);
     ;}
    break;

  case 62:
#line 390 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 63:
#line 396 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 64:
#line 400 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 65:
#line 406 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package_var(compiler, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 66:
#line 412 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 67:
#line 416 "yacc/spvm_yacc.y"
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

  case 68:
#line 429 "yacc/spvm_yacc.y"
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

  case 69:
#line 443 "yacc/spvm_yacc.y"
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

  case 70:
#line 468 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 71:
#line 472 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 72:
#line 476 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (1)].opval);
    ;}
    break;

  case 73:
#line 482 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 74:
#line 487 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 75:
#line 492 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 76:
#line 497 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 77:
#line 504 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_deref(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 78:
#line 508 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_deref(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 79:
#line 514 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_ref(compiler, op_ref, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 80:
#line 519 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, (yyvsp[(1) - (4)].opval)->file, (yyvsp[(1) - (4)].opval)->line);
      (yyval.opval) = SPVM_OP_build_ref(compiler, op_ref, (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 85:
#line 530 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 87:
#line 537 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_constant(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 103:
#line 557 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 104:
#line 561 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 105:
#line 565 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 106:
#line 569 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 107:
#line 573 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 108:
#line 577 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 110:
#line 584 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 111:
#line 590 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 112:
#line 594 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 113:
#line 598 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 114:
#line 602 "yacc/spvm_yacc.y"
    {
      // New
      SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);

      (yyval.opval) = SPVM_OP_build_new(compiler, op_new, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 115:
#line 609 "yacc/spvm_yacc.y"
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

  case 116:
#line 630 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 117:
#line 637 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, (yyvsp[(2) - (4)].opval)->file, (yyvsp[(2) - (4)].opval)->line);
      (yyval.opval) = SPVM_OP_build_convert(compiler, op_convert, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 118:
#line 644 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 119:
#line 648 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 120:
#line 652 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 121:
#line 658 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 122:
#line 664 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 123:
#line 669 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEGATE, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op_negate, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 124:
#line 674 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 125:
#line 679 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 126:
#line 684 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 127:
#line 689 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unop(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 128:
#line 694 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unop(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 129:
#line 700 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 130:
#line 705 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binop(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 131:
#line 710 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_concat(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 132:
#line 714 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 133:
#line 718 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 134:
#line 722 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 135:
#line 726 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 136:
#line 730 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 137:
#line 734 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 138:
#line 738 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 139:
#line 742 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 140:
#line 746 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 141:
#line 750 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 142:
#line 754 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 143:
#line 758 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 144:
#line 764 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binop(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 145:
#line 770 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_or(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 146:
#line 774 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_and(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 147:
#line 778 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_not(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 148:
#line 784 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 149:
#line 788 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 150:
#line 792 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 151:
#line 798 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, NULL, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 152:
#line 802 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 153:
#line 806 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_assignable_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_assignable_terms);
    ;}
    break;

  case 154:
#line 811 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 155:
#line 815 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_assignable_terms = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_assignable_terms);
    ;}
    break;

  case 156:
#line 820 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[(2) - (5)].opval)->file, (yyvsp[(2) - (5)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (5)].opval), op_sub_name, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 157:
#line 827 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 158:
#line 831 "yacc/spvm_yacc.y"
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
#line 842 "yacc/spvm_yacc.y"
    {
       // Add invocant to arguments
       SPVM_OP* op_args = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
       SPVM_OP_insert_child(compiler, op_args, op_args->last, (yyvsp[(1) - (1)].opval));
       
       (yyval.opval) = op_args;
    ;}
    break;

  case 160:
#line 850 "yacc/spvm_yacc.y"
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
#line 869 "yacc/spvm_yacc.y"
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
#line 883 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 164:
#line 890 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 165:
#line 896 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 166:
#line 902 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 167:
#line 906 "yacc/spvm_yacc.y"
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
#line 919 "yacc/spvm_yacc.y"
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

  case 174:
#line 942 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 175:
#line 946 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_byte_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 176:
#line 953 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_short_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 177:
#line 960 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_int_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 178:
#line 967 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_long_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 179:
#line 974 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_float_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 180:
#line 981 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_double_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 181:
#line 988 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_object_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 182:
#line 995 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      op_type->uv.type = SPVM_TYPE_create_string_type(compiler);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 183:
#line 1004 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 184:
#line 1010 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 185:
#line 1014 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 186:
#line 1020 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_const_array_type(compiler, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 187:
#line 1026 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 188:
#line 1030 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 190:
#line 1038 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_void(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 193:
#line 1047 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 194:
#line 1053 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3258 "spvm_yacc.tab.c"
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


#line 1057 "yacc/spvm_yacc.y"


