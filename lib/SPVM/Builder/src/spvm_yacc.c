/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         SPVM_yyparse
#define yylex           SPVM_yylex
#define yyerror         SPVM_yyerror
#define yydebug         SPVM_yydebug
#define yynerrs         SPVM_yynerrs


/* Copy the first part of user declarations.  */
#line 8 "yacc/spvm_yacc.y" /* yacc.c:339  */

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
  #include "spvm_attribute.h"
  #include "spvm_string.h"

#line 88 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "spvm_yacc.h".  */
#ifndef YY_SPVM_YY_LIB_SPVM_BUILDER_INCLUDE_SPVM_YACC_H_INCLUDED
# define YY_SPVM_YY_LIB_SPVM_BUILDER_INCLUDE_SPVM_YACC_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int SPVM_yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CLASS = 258,
    HAS = 259,
    METHOD = 260,
    OUR = 261,
    ENUM = 262,
    MY = 263,
    USE = 264,
    AS = 265,
    REQUIRE = 266,
    ALIAS = 267,
    ALLOW = 268,
    CURRENT_CLASS = 269,
    MUTABLE = 270,
    ATTRIBUTE = 271,
    MAKE_READ_ONLY = 272,
    INTERFACE = 273,
    EVAL_ERROR_ID = 274,
    ARGS_WIDTH = 275,
    VERSION_DECL = 276,
    IF = 277,
    UNLESS = 278,
    ELSIF = 279,
    ELSE = 280,
    FOR = 281,
    WHILE = 282,
    LAST = 283,
    NEXT = 284,
    SWITCH = 285,
    CASE = 286,
    DEFAULT = 287,
    BREAK = 288,
    EVAL = 289,
    SYMBOL_NAME = 290,
    VAR_NAME = 291,
    CONSTANT = 292,
    EXCEPTION_VAR = 293,
    UNDEF = 294,
    VOID = 295,
    BYTE = 296,
    SHORT = 297,
    INT = 298,
    LONG = 299,
    FLOAT = 300,
    DOUBLE = 301,
    STRING = 302,
    OBJECT = 303,
    TRUE = 304,
    FALSE = 305,
    END_OF_FILE = 306,
    FATCAMMA = 307,
    RW = 308,
    RO = 309,
    WO = 310,
    INIT = 311,
    NEW = 312,
    OF = 313,
    BASIC_TYPE_ID = 314,
    EXTENDS = 315,
    SUPER = 316,
    RETURN = 317,
    WEAKEN = 318,
    DIE = 319,
    WARN = 320,
    PRINT = 321,
    SAY = 322,
    CURRENT_CLASS_NAME = 323,
    UNWEAKEN = 324,
    ASSIGN = 325,
    SPECIAL_ASSIGN = 326,
    LOGICAL_OR = 327,
    LOGICAL_AND = 328,
    BIT_OR = 329,
    BIT_XOR = 330,
    BIT_AND = 331,
    NUMEQ = 332,
    NUMNE = 333,
    STREQ = 334,
    STRNE = 335,
    NUMGT = 336,
    NUMGE = 337,
    NUMLT = 338,
    NUMLE = 339,
    STRGT = 340,
    STRGE = 341,
    STRLT = 342,
    STRLE = 343,
    ISA = 344,
    ISA_ERROR = 345,
    IS_TYPE = 346,
    IS_ERROR = 347,
    IS_COMPILE_TYPE = 348,
    NUMERIC_CMP = 349,
    STRING_CMP = 350,
    CAN = 351,
    SHIFT = 352,
    DIVIDE = 353,
    DIVIDE_UNSIGNED_INT = 354,
    DIVIDE_UNSIGNED_LONG = 355,
    MODULO = 356,
    MODULO_UNSIGNED_INT = 357,
    MODULO_UNSIGNED_LONG = 358,
    LOGICAL_NOT = 359,
    BIT_NOT = 360,
    CREATE_REF = 361,
    DEREF = 362,
    PLUS = 363,
    MINUS = 364,
    CONVERT = 365,
    SCALAR = 366,
    STRING_LENGTH = 367,
    ISWEAK = 368,
    REFCNT = 369,
    TYPE_NAME = 370,
    COMPILE_TYPE_NAME = 371,
    DUMP = 372,
    NEW_STRING_LEN = 373,
    IS_READ_ONLY = 374,
    COPY = 375,
    INC = 376,
    DEC = 377,
    ARROW = 378
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_LIB_SPVM_BUILDER_INCLUDE_SPVM_YACC_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 257 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   4943

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  138
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  97
/* YYNRULES -- Number of rules.  */
#define YYNRULES  289
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  559

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   378

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      72,   136,   104,   101,   135,   102,   103,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   132,   133,
       2,     2,     2,     2,   113,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    70,     2,   137,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    71,     2,   134,     2,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   105,   106,   107,   108,   109,   110,   111,
     112,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    70,    70,    74,    77,    90,   104,   107,   111,   115,
     119,   126,   129,   133,   136,   142,   151,   154,   166,   180,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     195,   201,   207,   213,   220,   228,   235,   241,   247,   253,
     262,   265,   278,   292,   293,   296,   300,   306,   312,   318,
     322,   326,   330,   336,   342,   360,   363,   376,   390,   391,
     394,   398,   404,   418,   419,   422,   426,   430,   439,   442,
     455,   469,   473,   476,   489,   503,   506,   507,   508,   509,
     510,   511,   512,   513,   514,   515,   516,   517,   518,   519,
     523,   527,   531,   532,   536,   539,   543,   547,   551,   555,
     561,   562,   566,   570,   571,   572,   578,   582,   588,   594,
     598,   604,   610,   616,   622,   631,   634,   647,   661,   667,
     671,   677,   681,   687,   693,   700,   711,   725,   728,   732,
     738,   746,   753,   756,   770,   773,   776,   777,   778,   779,
     780,   781,   782,   783,   784,   785,   786,   787,   788,   789,
     790,   791,   792,   793,   809,   810,   811,   812,   813,   814,
     815,   816,   817,   821,   825,   826,   827,   831,   832,   835,
     849,   853,   859,   864,   869,   873,   877,   881,   885,   889,
     893,   897,   901,   905,   909,   915,   920,   927,   932,   939,
     944,   949,   954,   958,   962,   966,   970,   974,   978,   982,
     986,   990,   994,  1000,  1004,  1008,  1012,  1016,  1020,  1024,
    1028,  1032,  1036,  1040,  1044,  1048,  1052,  1058,  1064,  1070,
    1076,  1082,  1088,  1092,  1096,  1102,  1106,  1112,  1116,  1122,
    1128,  1134,  1140,  1149,  1154,  1161,  1166,  1172,  1177,  1183,
    1188,  1194,  1202,  1207,  1212,  1219,  1224,  1229,  1237,  1245,
    1253,  1261,  1265,  1271,  1276,  1281,  1286,  1293,  1297,  1303,
    1309,  1310,  1315,  1316,  1317,  1320,  1323,  1327,  1333,  1339,
    1345,  1351,  1357,  1363,  1368,  1376,  1382,  1386,  1392,  1396,
    1402,  1403,  1410,  1413,  1416,  1422,  1436,  1442,  1445,  1448
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CLASS", "HAS", "METHOD", "OUR", "ENUM",
  "MY", "USE", "AS", "REQUIRE", "ALIAS", "ALLOW", "CURRENT_CLASS",
  "MUTABLE", "ATTRIBUTE", "MAKE_READ_ONLY", "INTERFACE", "EVAL_ERROR_ID",
  "ARGS_WIDTH", "VERSION_DECL", "IF", "UNLESS", "ELSIF", "ELSE", "FOR",
  "WHILE", "LAST", "NEXT", "SWITCH", "CASE", "DEFAULT", "BREAK", "EVAL",
  "SYMBOL_NAME", "VAR_NAME", "CONSTANT", "EXCEPTION_VAR", "UNDEF", "VOID",
  "BYTE", "SHORT", "INT", "LONG", "FLOAT", "DOUBLE", "STRING", "OBJECT",
  "TRUE", "FALSE", "END_OF_FILE", "FATCAMMA", "RW", "RO", "WO", "INIT",
  "NEW", "OF", "BASIC_TYPE_ID", "EXTENDS", "SUPER", "RETURN", "WEAKEN",
  "DIE", "WARN", "PRINT", "SAY", "CURRENT_CLASS_NAME", "UNWEAKEN", "'['",
  "'{'", "'('", "ASSIGN", "SPECIAL_ASSIGN", "LOGICAL_OR", "LOGICAL_AND",
  "BIT_OR", "BIT_XOR", "BIT_AND", "NUMEQ", "NUMNE", "STREQ", "STRNE",
  "NUMGT", "NUMGE", "NUMLT", "NUMLE", "STRGT", "STRGE", "STRLT", "STRLE",
  "ISA", "ISA_ERROR", "IS_TYPE", "IS_ERROR", "IS_COMPILE_TYPE",
  "NUMERIC_CMP", "STRING_CMP", "CAN", "SHIFT", "'+'", "'-'", "'.'", "'*'",
  "DIVIDE", "DIVIDE_UNSIGNED_INT", "DIVIDE_UNSIGNED_LONG", "MODULO",
  "MODULO_UNSIGNED_INT", "MODULO_UNSIGNED_LONG", "LOGICAL_NOT", "BIT_NOT",
  "'@'", "CREATE_REF", "DEREF", "PLUS", "MINUS", "CONVERT", "SCALAR",
  "STRING_LENGTH", "ISWEAK", "REFCNT", "TYPE_NAME", "COMPILE_TYPE_NAME",
  "DUMP", "NEW_STRING_LEN", "IS_READ_ONLY", "COPY", "INC", "DEC", "ARROW",
  "':'", "';'", "'}'", "','", "')'", "']'", "$accept", "grammar",
  "opt_classes", "classes", "class", "opt_class_type", "opt_extends",
  "class_block", "opt_definitions", "definitions", "definition",
  "init_block", "version_decl", "use", "require", "alias", "allow",
  "interface", "enumeration", "enumeration_block",
  "opt_enumeration_values", "enumeration_values", "enumeration_value",
  "our", "has", "method", "anon_method", "opt_args", "args", "arg",
  "has_for_anon_list", "has_for_anon", "opt_attributes", "attributes",
  "opt_statements", "statements", "statement", "die",
  "void_return_operator", "warn", "for_statement", "foreach_statement",
  "while_statement", "switch_statement", "switch_block",
  "opt_case_statements", "case_statements", "case_statement",
  "default_statement", "if_require_statement", "if_statement",
  "else_statement", "block", "eval_block", "opt_operators", "opt_operator",
  "operator", "operators", "unary_operator", "inc", "dec",
  "binary_operator", "comparison_operator", "isa", "isa_error", "is_type",
  "is_error", "is_compile_type", "logical_operator", "assign", "new",
  "array_init", "convert", "call_method", "array_access", "field_access",
  "weaken_field", "unweaken_field", "isweak_field", "can", "array_length",
  "var_decl", "var", "qualified_type", "type", "class_type", "basic_type",
  "ref_type", "array_type", "array_type_with_length", "return_type",
  "opt_type_comment", "type_comment", "union_type", "field_name",
  "method_name", "alias_name", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
      91,   123,    40,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,    43,    45,    46,    42,   353,   354,   355,   356,   357,
     358,   359,   360,    64,   361,   362,   363,   364,   365,   366,
     367,   368,   369,   370,   371,   372,   373,   374,   375,   376,
     377,   378,    58,    59,   125,    44,    41,    93
};
# endif

#define YYPACT_NINF -455

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-455)))

#define YYTABLE_NINF -135

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-135)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      63,   302,    39,  -455,    63,  -455,  -455,  -455,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,     9,  -455,  -455,  -455,  -455,
     302,   -49,  -455,    52,    61,    34,    47,    67,    70,   302,
     302,   302,  -455,   302,    76,    48,   -11,   108,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,  -455,  -455,   -15,  -455,    21,
     109,   -46,  -455,  -455,  -455,    -4,    -2,     4,   121,    -1,
       0,     3,  1389,  -455,  -455,  -455,  -455,   -16,    68,  -455,
      83,    87,    61,    61,   105,  -455,   105,  -455,  -455,  -455,
     106,   111,  2868,  -455,  -455,    69,    72,    16,    77,    17,
      18,    89,  2868,    30,    32,    48,  -455,  -455,  -455,  -455,
    -455,  -455,   302,   302,  1881,   106,  2004,  2127,  2868,  2868,
    -455,   106,   648,  1512,  2622,  2868,  2868,  2868,  2868,  2991,
    2868,   106,    50,  2868,   106,  2868,  2868,  2868,  2868,  2868,
    2868,  2868,  2868,  2868,  -455,  -455,   162,    35,  1635,  -455,
      33,    38,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,
    -455,  -455,  -455,  4253,  -455,  -455,  -455,  -455,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,
     -25,    -8,  -455,  -455,  -455,  -455,  -455,  -455,  -455,    37,
    -455,   112,    40,   138,  -455,  -455,  -455,   210,   210,  -455,
      41,    42,    44,   107,  1758,  4496,  2745,  2868,  2250,   113,
    2868,  -455,  -455,  2868,  4436,    48,  -455,  -455,   110,   117,
    -455,  -455,   -33,  -455,   120,  -455,  4314,    60,  4004,  2373,
     -37,  4496,  4496,  4496,    71,    67,   -99,  -455,    46,  4496,
      43,    49,  -455,  4253,   -53,   302,   -36,    56,  -455,   -81,
     -81,   -81,   -81,  1758,   -81,   -81,  -455,  3114,   -81,    73,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -34,   -34,    66,
    -455,  -455,  -455,  -455,  2868,  2868,  2868,  2868,  2868,  2868,
    2868,  2868,  2868,  2868,  2868,  2868,  2868,  2868,  2868,  2868,
    2868,  2868,  2868,   302,   302,   302,   302,   302,  2868,  2868,
      22,  2868,  2868,  2868,  2868,  2868,  2868,  2868,  2868,  2868,
    2868,  2868,  -455,  -455,     8,  -455,  2868,    67,  2868,    67,
     138,  -455,   141,   128,   112,    74,    78,  -455,   130,   141,
     141,  -455,  -455,   210,  1143,   302,    65,  3620,  3684,    79,
    4496,    93,  3748,  3812,    48,  -455,   772,   896,    81,  -455,
      84,  -455,   136,  2868,  4496,   140,    82,    36,    61,  -455,
    2499,    61,  -455,  -455,  -455,  2868,  4067,  1758,   -81,   144,
     112,  4496,  4496,  4552,  4607,  4660,  4660,  4712,  4764,  4764,
    4764,  4764,  4812,  4812,  4812,  4812,  4812,  4812,  4812,  4812,
    -455,  -455,  -455,  -455,  -455,  4812,  4812,  -455,  -455,   161,
     203,   203,   203,   -81,   -81,   -81,   -81,   -81,   -81,   -81,
    2868,    67,  1020,   148,  3295,    88,  3360,    90,   151,   302,
    -455,  -455,   106,   154,  -455,   138,   190,  -455,    95,   141,
      96,  -455,    48,    48,    48,  2868,  3237,    48,   160,  -455,
    -455,  3425,  -455,  3490,    67,  4496,    67,    61,  -455,    49,
     228,  4496,   210,   -81,  -455,  4129,    67,   163,  3555,   100,
     101,   102,  1143,  -455,  -455,  -455,  -455,  1143,  -455,   164,
     103,   124,  -455,   114,   106,  -455,  -455,  -455,  -455,  -455,
     215,    85,    85,  4375,  1758,  3876,  -455,   212,  -455,  -455,
    -455,   126,   127,   210,   115,   141,  -455,   139,   106,  -455,
    -455,  -455,  -455,   142,   143,   302,   -44,   106,   210,   145,
      48,   176,    48,  -455,  -455,  1266,  4191,    48,   -12,   212,
    -455,  -455,  -455,   141,   112,  -455,  -455,   146,  -455,  -455,
    -455,  -455,  -455,  -455,   141,   -42,  -455,  2868,  -455,   147,
     157,  -455,  -455,   166,  -455,   199,   202,    48,   207,  -455,
    -455,  3940,    48,    48,  -455,  2868,   106,  -455,  2868,    48,
    -455,  -455,  4496,   158,  4496,    85,    48,  -455,  -455
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       3,    11,     0,     2,     4,     6,   266,   267,   268,   269,
     270,   271,   272,   274,   273,    13,    12,   265,     1,     5,
       0,     0,    14,    68,    68,     0,     0,     0,     0,     0,
       0,     0,    71,     0,     0,     0,     0,    68,    19,    25,
      20,    21,    22,    23,    24,    26,    27,     0,    29,     0,
      69,     0,     9,     7,   287,     0,     0,     0,     0,     0,
       0,     0,    68,    30,    15,    18,    28,     0,     0,    70,
       0,     0,    68,    68,     0,    32,     0,    36,    37,    31,
       0,     0,    68,   167,   168,     0,     0,     0,     0,     0,
       0,     0,    68,     0,     0,     0,   259,   138,   137,   139,
     162,   163,     0,     0,    68,     0,    68,    68,    68,    68,
     154,     0,    68,    68,    68,    68,    68,    68,    68,    68,
      68,     0,     0,    68,     0,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    93,   229,     0,     0,    68,    75,
       0,     0,   100,    77,    78,    79,    81,    82,    83,    85,
      76,    80,    84,     0,   148,   151,   152,   149,   156,   157,
     158,   159,   160,   161,   165,   150,   144,   145,   143,   140,
     142,   141,   103,   104,   155,   164,   146,   147,   136,     0,
     288,     0,     0,    40,    38,    10,     8,     0,     0,   289,
       0,     0,   258,   236,    68,   105,    68,    68,    68,     0,
      68,    86,    87,    68,     0,   122,    88,   131,   227,     0,
     228,   166,   262,   264,   263,    89,     0,     0,    95,    68,
     262,   106,   101,   102,     0,     0,     0,    64,     0,   171,
     133,   136,   232,   171,     0,     0,     0,     0,   260,   172,
     173,   224,   174,    68,   253,   181,   180,    68,   178,     0,
     175,   176,   177,   179,   182,   184,   183,   185,   187,     0,
     130,    74,    94,    92,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,     0,     0,     0,     0,     0,    68,    68,
       0,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,   186,   188,     0,    91,    68,     0,    68,     0,
       0,   281,   282,     0,     0,     0,    41,    44,    45,   282,
     282,    33,    35,     0,    68,     0,     0,     0,     0,     0,
     135,     0,     0,     0,   120,   121,    68,    68,     0,   275,
       0,    90,     0,    68,    97,     0,     0,    63,    68,   230,
     170,    68,   231,   261,   153,    68,   171,    68,   255,     0,
       0,   225,   226,   222,   223,   200,   198,   199,   203,   204,
     210,   211,   205,   206,   207,   208,   212,   213,   214,   215,
     217,   218,   219,   220,   221,   209,   216,   252,   251,   201,
     189,   190,   202,   191,   192,   193,   194,   195,   196,   197,
      68,     0,    68,   240,     0,     0,     0,     0,   238,     0,
     280,   283,    55,     0,    39,    43,     0,    48,     0,   282,
       0,    34,     0,     0,     0,    68,    68,     0,     0,   119,
     276,     0,   277,     0,     0,    99,     0,    68,    62,     0,
       0,   169,     0,   233,   254,   171,     0,     0,     0,     0,
       0,     0,    68,   243,   247,   244,   246,    68,   286,   284,
       0,    56,    59,     0,    55,    42,    46,    47,   257,   235,
     123,   127,   127,     0,    68,     0,   111,   115,   112,   278,
     279,     0,     0,     0,     0,   282,   256,     0,    55,   242,
     245,   241,   234,     0,     0,     0,     0,    58,     0,     0,
       0,     0,     0,   125,   126,    68,   171,     0,     0,   116,
     118,   248,   249,   282,     0,    67,   250,     0,   239,   237,
     285,    52,    51,    57,   282,     0,   124,    68,   128,     0,
       0,   109,   113,     0,   117,    65,     0,     0,    60,    50,
      49,     0,     0,     0,   114,    68,    55,    53,    68,     0,
     108,   110,    66,     0,    61,   127,     0,   129,    54
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -455,  -455,  -455,  -455,   271,  -455,  -455,   225,  -455,  -455,
     258,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,
    -455,  -455,  -119,  -455,  -455,  -455,  -455,  -441,  -455,  -200,
    -455,   -45,   -20,  -455,  -455,  -455,   165,  -455,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,  -455,  -455,  -433,  -210,  -455,
    -455,  -454,   -35,  -455,  -309,  -204,   322,  -108,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,
    -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,  -455,
    -455,   217,   -70,  -113,   -90,  -455,     1,  -455,   204,  -455,
    -305,  -308,  -455,  -455,  -217,   -60,   229
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    15,    21,    26,    36,    37,
      38,    39,    40,    41,   326,    42,    43,    44,    45,   184,
     315,   316,   317,    46,    47,    48,   135,   460,   461,   462,
     226,   227,   136,    50,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   478,   508,   509,   147,   148,   149,
     150,   503,   151,   152,   228,   329,   229,   230,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   312,   238,    16,   179,   213,   214,   210,
     313,   410,   411,   459,    55,   318,   190
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      63,   237,    17,    49,    51,   234,   236,   182,   346,   413,
     192,   417,   418,   211,    74,   420,   219,    49,   504,   180,
      93,    22,    23,   499,    80,    23,    67,    62,    68,    62,
      57,    58,    59,   338,    60,   217,   347,   338,   348,    18,
     225,   224,   231,   180,   510,   306,   307,   517,   302,   303,
     304,   246,   187,   188,   249,   447,    27,   180,    28,   387,
     207,    29,   308,   309,    30,    31,     1,   339,    32,    20,
      33,   339,    96,    34,   319,   320,   534,    32,   400,   401,
     402,   352,   350,    24,    25,    52,   234,    70,   198,   521,
     405,   539,   407,   450,   310,  -135,  -135,   304,    53,   350,
     354,   557,    54,   208,   212,   553,    56,   220,    35,   501,
     502,   468,    27,    61,    28,   220,   181,    29,    66,    62,
      30,    31,   532,    64,    32,    69,    33,   235,    72,    34,
      73,    76,    77,    78,   185,   234,    79,    75,   186,   183,
     189,   196,    96,   493,   197,   353,   193,     6,   494,   200,
     201,   202,   311,     7,     8,     9,    10,    11,    12,    13,
      14,   203,   205,   247,    35,   206,   262,   259,   310,   260,
     335,   263,   314,   180,   321,   322,   323,   515,   350,   324,
     336,   351,   212,   349,   449,   331,   -16,   337,   212,   212,
     340,   342,   355,   380,   381,   382,   383,   384,   360,   409,
     412,   422,   345,   416,   359,   535,   426,   434,   414,   536,
     419,   436,   425,   415,   437,   446,   538,   481,   430,   482,
     452,   432,   454,   457,   456,   235,   464,   466,   467,   487,
     388,   477,   469,   484,   490,   488,   212,   491,   492,   496,
     500,   495,   -17,    92,   403,     6,   498,   514,   527,   234,
     408,     7,     8,     9,    10,    11,    12,    13,    14,   497,
     511,   512,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   545,   516,   546,    19,    71,   439,   518,   519,
     548,   525,   537,   542,   212,   212,   212,   212,   212,   451,
     302,   303,   304,   543,   556,    65,   465,   523,   533,   429,
     544,   529,   438,   261,   199,   191,   209,   295,   296,   297,
     298,   299,   300,   301,     0,   212,     0,     0,     0,   458,
       0,     0,     0,     0,   212,     0,   421,     0,   440,   485,
       0,   442,   302,   303,   304,     0,     0,     6,     0,     0,
       0,     0,   463,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   212,     0,     0,     0,     0,   234,     0,     0,     0,
     513,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   153,   524,     0,   470,   471,   472,
       0,     0,   476,     0,   463,     0,     0,     0,     0,     0,
       0,     0,     0,   220,   195,   520,     0,     0,     0,     0,
     212,     0,     0,     0,   204,     0,     0,   483,   463,     0,
       0,     0,     0,     0,     0,     0,   216,   463,   218,   221,
     222,   223,     0,     0,     0,   233,     0,   239,   240,   241,
     242,   244,   245,   212,     0,   248,     0,   250,   251,   252,
     253,   254,   255,   256,   257,   258,     0,     0,     0,     0,
     153,   522,     0,     0,     0,   526,     0,   528,     0,     0,
       0,     0,   531,     0,     0,     0,   463,     0,     0,     0,
       0,     0,     0,     0,   212,     0,     0,     0,     0,     0,
     540,     0,     0,     0,     0,     0,   212,     0,     0,   212,
       0,     0,   547,     0,     0,     0,     0,   550,   551,     0,
       0,     0,     0,     0,   555,   212,     0,     0,   327,   328,
     330,   558,   332,     0,     0,   333,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   344,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   356,     0,     0,     0,   358,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,     0,     0,     0,     0,     0,
     385,   386,     0,   389,   390,   391,   392,   393,   394,   395,
     396,   397,   398,   399,     0,     0,     0,     0,   404,     0,
     406,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   225,     0,     0,     0,    80,     0,   431,   433,
       0,     0,    81,     0,    32,   435,     0,    83,    84,     0,
       0,     0,   441,     0,     0,     0,     0,   443,     0,   445,
       0,     0,     0,     6,    96,    97,    98,    99,     0,     7,
       8,     9,    10,    11,    12,    13,    14,   100,   101,     0,
       0,     0,     0,     0,     0,   102,     0,   103,     0,     0,
       0,     0,     0,     0,     0,     0,   110,     0,   112,   194,
     114,     0,   448,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   473,   475,   115,
     116,     0,     0,     0,     0,     0,     0,     0,     0,   117,
     118,   119,   120,   121,     0,     0,     0,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,     0,
      80,     0,     0,     0,     0,  -132,    81,     0,    32,     0,
       0,    83,    84,     0,     0,     0,   506,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6,    96,    97,
      98,    99,     0,     7,     8,     9,    10,    11,    12,    13,
      14,   100,   101,     0,     0,     0,     0,   330,     0,   102,
       0,   103,     0,     0,     0,     0,     0,     0,     0,     0,
     110,     0,   112,   194,   114,     0,     0,     0,     0,   541,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   552,     0,     0,
     554,     0,     0,   115,   116,     0,     0,     0,     0,     0,
       0,     0,     0,   117,   118,   119,   120,   121,     0,     0,
       0,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,     0,    80,     0,     0,     0,     0,   430,
      81,     0,    32,     0,     0,    83,    84,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,    96,    97,    98,    99,     0,     7,     8,     9,
      10,    11,    12,    13,    14,   100,   101,     0,     0,     0,
       0,     0,     0,   102,     0,   103,     0,     0,     0,     0,
       0,     0,     0,     0,   110,     0,   112,   194,   114,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,   116,     0,
       0,     0,     0,     0,     0,     0,     0,   117,   118,   119,
     120,   121,     0,     0,     0,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,     0,    80,     0,
       0,     0,     0,   432,    81,   235,    32,     0,     0,    83,
      84,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,    96,    97,    98,    99,
       0,     7,     8,     9,    10,    11,    12,    13,    14,   100,
     101,     0,     0,     0,     0,     0,     0,   102,     0,   103,
       0,     0,     0,     0,     0,     0,     0,     0,   110,     0,
     112,   194,   114,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   115,   116,     0,     0,     0,     0,     0,     0,     0,
       0,   117,   118,   119,   120,   121,     0,     0,     0,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,    80,     0,     0,     0,     0,  -132,    81,     0,    32,
       0,     0,    83,    84,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     6,    96,
      97,    98,    99,     0,     7,     8,     9,    10,    11,    12,
      13,    14,   100,   101,     0,     0,     0,     0,     0,     0,
     102,     0,   103,     0,     0,     0,     0,     0,     0,     0,
       0,   110,     0,   112,   194,   114,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   115,   116,     0,     0,     0,     0,
       0,     0,     0,     0,   117,   118,   119,   120,   121,     0,
       0,     0,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,    80,     0,     0,     0,     0,  -132,
      81,     0,    32,     0,     0,    83,    84,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,    96,    97,    98,    99,     0,     7,     8,     9,
      10,    11,    12,    13,    14,   100,   101,     0,     0,     0,
       0,     0,     0,   102,     0,   103,     0,     0,     0,     0,
       0,     0,     0,     0,   110,     0,   112,   194,   114,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,   116,     0,
       0,     0,     0,     0,     0,     0,     0,   117,   118,   119,
     120,   121,     0,     0,     0,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,    80,     0,     0,
       0,     0,  -134,    81,     0,    32,    82,     0,    83,    84,
       0,    85,    86,     0,     0,    87,    88,    89,    90,    91,
      92,    93,    94,    95,     6,    96,    97,    98,    99,     0,
       7,     8,     9,    10,    11,    12,    13,    14,   100,   101,
       0,     0,     0,     0,     0,     0,   102,     0,   103,     0,
       0,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     115,   116,     0,     0,     0,     0,     0,     0,     0,     0,
     117,   118,   119,   120,   121,     0,     0,     0,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
      80,     0,   134,   -72,     0,     0,    81,     0,    32,    82,
       0,    83,    84,     0,    85,    86,     0,     0,    87,    88,
      89,    90,    91,    92,    93,    94,    95,     6,    96,    97,
      98,    99,     0,     7,     8,     9,    10,    11,    12,    13,
      14,   100,   101,     0,     0,     0,     0,     0,     0,   102,
       0,   103,     0,     0,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   115,   116,     0,     0,     0,     0,     0,
       0,     0,     0,   117,   118,   119,   120,   121,     0,     0,
       0,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,    80,     0,   134,   232,     0,     0,    81,
       0,    32,    82,     0,    83,    84,     0,    85,    86,     0,
       0,    87,    88,    89,    90,    91,    92,    93,    94,    95,
       6,    96,    97,    98,    99,     0,     7,     8,     9,    10,
      11,    12,    13,    14,   100,   101,     0,     0,     0,     0,
       0,     0,   102,     0,   103,     0,     0,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   115,   116,     0,     0,
       0,     0,     0,     0,     0,     0,   117,   118,   119,   120,
     121,     0,     0,     0,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,    80,     0,   134,   -73,
       0,     0,    81,     0,    32,     0,     0,    83,    84,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,    96,    97,    98,    99,     0,     7,
       8,     9,    10,    11,    12,    13,    14,   100,   101,     0,
       0,     0,     0,     0,     0,   102,     0,   103,     0,     0,
       0,     0,     0,     0,     0,     0,   110,     0,   112,   194,
     114,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   115,
     116,     0,     0,     0,     0,     0,     0,     0,     0,   117,
     118,   119,   120,   121,     0,     0,     0,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,    80,
       0,     0,   232,     0,     0,    81,     0,    32,     0,     0,
      83,    84,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,    96,    97,    98,
      99,     0,     7,     8,     9,    10,    11,    12,    13,    14,
     100,   101,     0,     0,     0,     0,     0,     0,   102,     0,
     103,     0,     0,     0,     0,     0,     0,     0,     0,   110,
       0,   112,   194,   114,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   115,   116,     0,     0,     0,     0,     0,     0,
       0,     0,   117,   118,   119,   120,   121,     0,     0,     0,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,    80,     0,   215,     0,     0,     0,    81,     0,
      32,     0,     0,    83,    84,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
      96,    97,    98,    99,     0,     7,     8,     9,    10,    11,
      12,    13,    14,   100,   101,     0,     0,     0,     0,     0,
       0,   102,     0,   103,     0,     0,     0,     0,     0,     0,
       0,     0,   110,     0,   112,   194,   114,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   115,   116,     0,     0,     0,
       0,     0,     0,     0,     0,   117,   118,   119,   120,   121,
       0,     0,     0,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,    80,     0,   -96,     0,     0,
       0,    81,     0,    32,     0,     0,    83,    84,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     6,    96,    97,    98,    99,     0,     7,     8,
       9,    10,    11,    12,    13,    14,   100,   101,     0,     0,
       0,     0,     0,     0,   102,     0,   103,     0,     0,     0,
       0,     0,     0,     0,     0,   110,     0,   112,   194,   114,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   115,   116,
       0,     0,     0,     0,     0,     0,     0,     0,   117,   118,
     119,   120,   121,     0,     0,     0,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,    80,     0,
    -107,     0,     0,     0,    81,     0,    32,     0,     0,    83,
      84,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,    96,    97,    98,    99,
       0,     7,     8,     9,    10,    11,    12,    13,    14,   100,
     101,     0,     0,     0,     0,     0,     0,   102,     0,   103,
       0,     0,     0,     0,     0,     0,     0,     0,   110,     0,
     112,   194,   114,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   115,   116,     0,     0,     0,     0,     0,     0,     0,
       0,   117,   118,   119,   120,   121,     0,     0,     0,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,    80,     0,  -134,     0,     0,     0,    81,     0,    32,
       0,     0,    83,    84,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     6,    96,
      97,    98,    99,     0,     7,     8,     9,    10,    11,    12,
      13,    14,   100,   101,     0,     0,     0,     0,     0,     0,
     102,     0,   103,     0,     0,     0,     0,     0,     0,     0,
       0,   110,     0,   112,   194,   114,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   115,   116,     0,     0,     0,     0,
       0,     0,     0,     0,   117,   118,   119,   120,   121,     0,
       0,     0,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   -68,     0,   -98,    80,     0,     0,
       0,     0,     0,    81,     0,    32,     0,     0,    83,    84,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,    96,    97,    98,    99,     0,
       7,     8,     9,    10,    11,    12,    13,    14,   100,   101,
       0,     0,     0,     0,     0,     0,   102,     0,   103,     0,
       0,     0,     0,     0,     0,     0,     0,   110,     0,   112,
     194,   114,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     115,   116,     0,     0,     0,     0,     0,     0,     0,     0,
     117,   118,   119,   120,   121,     0,     0,     0,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
      80,     0,     0,     0,     0,     0,    81,   235,    32,     0,
       0,    83,    84,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6,    96,    97,
      98,    99,     0,     7,     8,     9,    10,    11,    12,    13,
      14,   100,   101,     0,     0,     0,     0,     0,     0,   102,
       0,   103,     0,     0,     0,     0,     0,     0,     0,     0,
     110,     0,   112,   194,   114,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   115,   116,     0,     0,     0,     0,     0,
       0,     0,     0,   117,   118,   119,   120,   121,     0,     0,
       0,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,    80,     0,     0,   325,     0,     0,    81,
       0,    32,     0,     0,    83,    84,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       6,    96,    97,    98,    99,     0,     7,     8,     9,    10,
      11,    12,    13,    14,   100,   101,     0,     0,     0,     0,
       0,     0,   102,     0,   103,     0,     0,     0,     0,     0,
       0,     0,     0,   110,     0,   112,   194,   114,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   115,   116,     0,     0,
       0,     0,     0,     0,     0,     0,   117,   118,   119,   120,
     121,     0,     0,     0,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,    80,     0,     0,     0,
       0,     0,    81,     0,    32,     0,     0,    83,    84,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,    96,    97,    98,    99,     0,     7,
       8,     9,    10,    11,    12,    13,    14,   100,   101,     0,
       0,     0,     0,     0,     0,   102,     0,   103,     0,     0,
       0,     0,     0,     0,     0,     0,   110,     0,   112,   194,
     114,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   115,
     116,     0,     0,     0,     0,     0,     0,     0,     0,   117,
     118,   119,   120,   121,     0,     0,     0,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,    80,
       0,     0,     0,     0,     0,    81,     0,    32,     0,     0,
      83,    84,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,    96,    97,    98,
      99,     0,     7,     8,     9,    10,    11,    12,    13,    14,
     100,   101,     0,     0,     0,     0,     0,     0,   102,     0,
     103,     0,     0,     0,     0,     0,     0,     0,     0,   110,
       0,   112,   243,   114,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   115,   116,     0,     0,     0,     0,     0,     0,
       0,     0,   117,   118,   119,   120,   121,     0,     0,     0,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,    80,     0,     0,     0,     0,     0,    81,     0,
      32,     0,     0,    83,    84,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
      96,    97,    98,    99,     0,     7,     8,     9,    10,    11,
      12,    13,    14,   100,   101,     0,     0,     0,     0,     0,
       0,   102,     0,   103,     0,     0,     0,     0,     0,     0,
       0,     0,   110,     0,   112,   357,   114,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   115,   116,     0,     0,     0,
       0,     0,     0,     0,     0,   117,   118,   119,   120,   121,
       0,     0,     0,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,    80,     0,     0,     0,     0,
       0,    81,     0,    32,     0,     0,    83,    84,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     6,    96,    97,    98,    99,     0,     7,     8,
       9,    10,    11,    12,    13,    14,   100,   101,     0,     0,
       0,     0,     0,     0,   102,     0,   103,     0,     0,     0,
       0,     0,     0,     0,     0,   110,     0,   112,   474,   114,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   115,   116,
       0,     0,     0,     0,     0,     0,     0,     0,   117,   118,
     119,   120,   121,     0,     0,     0,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   302,   303,   304,     0,     0,     0,
       0,     0,   453,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   302,
     303,   304,     0,     0,     0,     0,     0,   455,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   302,   303,   304,     0,     0,     0,
       0,     0,   479,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   302,
     303,   304,     0,     0,     0,     0,     0,   480,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   302,   303,   304,     0,     0,     0,
       0,     0,   489,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   302,
     303,   304,     0,     0,     0,     0,   423,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   302,   303,   304,     0,     0,     0,     0,
     424,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   302,   303,   304,
       0,     0,     0,     0,   427,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   302,   303,   304,     0,     0,     0,     0,   428,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   302,   303,   304,     0,     0,
       0,     0,   507,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   302,
     303,   304,     0,     0,     0,     0,   549,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   302,   303,   304,     0,     0,     0,   343,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   302,   303,   304,     0,
       0,   444,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   302,   303,
     304,     0,     0,   486,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     302,   303,   304,     0,     0,   530,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   302,   303,   304,     0,   305,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   302,   303,   304,     0,   341,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   302,   303,   304,     0,   505,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   302,   303,   304,   334,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   302,   303,   304,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   302,   303,   304,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   302,   303,   304,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   302,
     303,   304,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   302,   303,   304,  -135,  -135,  -135,  -135,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   302,   303,   304,  -135,  -135,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,  -135,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   302,   303,   304
};

static const yytype_int16 yycheck[] =
{
      35,   114,     1,    23,    24,   113,   114,    67,   225,   314,
      80,   319,   320,   103,    10,   324,   106,    37,   472,    35,
      32,    20,    71,   464,     8,    71,     5,    71,     7,    71,
      29,    30,    31,    70,    33,   105,   135,    70,   137,     0,
       4,   111,   112,    35,   477,    70,    71,   488,   129,   130,
     131,   121,    72,    73,   124,   360,     4,    35,     6,    37,
      95,     9,    70,    71,    12,    13,     3,   104,    16,    60,
      18,   104,    36,    21,   187,   188,   509,    16,    70,    71,
      72,   134,   135,   132,   133,    51,   194,   133,    72,   133,
     307,   133,   309,   402,   131,   129,   130,   131,    51,   135,
     136,   555,    35,   102,   103,   546,    36,   106,    56,    24,
      25,   419,     4,    37,     6,   114,   132,     9,   133,    71,
      12,    13,   134,   134,    16,    16,    18,    15,   132,    21,
     132,    10,   133,   133,    51,   243,   133,   133,    51,    71,
      35,    72,    36,   452,    72,   235,    35,    35,   457,    72,
     133,   133,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    72,   132,   113,    56,   133,   133,     5,   131,   134,
     205,   133,   132,    35,   133,   133,   132,   485,   135,    72,
      70,   132,   181,   137,   401,    72,   134,    70,   187,   188,
      70,   131,   136,   283,   284,   285,   286,   287,   132,    58,
      72,   136,   131,    73,   131,   513,   113,    71,   134,   514,
     323,    71,   133,   135,   132,    71,   524,   434,   137,   436,
      72,   137,   134,    72,   134,    15,    72,    37,   133,   446,
     290,    71,   136,     5,   134,    72,   235,   136,   136,   136,
      25,    77,   134,    31,   304,    35,   132,   132,    72,   357,
     310,    41,    42,    43,    44,    45,    46,    47,    48,   135,
     134,   134,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,    73,   134,    72,     4,    51,   347,   136,   136,
      73,   136,   136,   136,   283,   284,   285,   286,   287,   402,
     129,   130,   131,   136,   136,    37,   415,   497,   508,   334,
     134,   505,   347,   138,    87,    76,   102,   104,   105,   106,
     107,   108,   109,   110,    -1,   314,    -1,    -1,    -1,   409,
      -1,    -1,    -1,    -1,   323,    -1,   325,    -1,   348,   442,
      -1,   351,   129,   130,   131,    -1,    -1,    35,    -1,    -1,
      -1,    -1,   412,    41,    42,    43,    44,    45,    46,    47,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   360,    -1,    -1,    -1,    -1,   474,    -1,    -1,    -1,
     483,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,   498,    -1,   422,   423,   424,
      -1,    -1,   427,    -1,   464,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   402,    82,   495,    -1,    -1,    -1,    -1,
     409,    -1,    -1,    -1,    92,    -1,    -1,   437,   488,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   104,   497,   106,   107,
     108,   109,    -1,    -1,    -1,   113,    -1,   115,   116,   117,
     118,   119,   120,   442,    -1,   123,    -1,   125,   126,   127,
     128,   129,   130,   131,   132,   133,    -1,    -1,    -1,    -1,
     138,   496,    -1,    -1,    -1,   500,    -1,   502,    -1,    -1,
      -1,    -1,   507,    -1,    -1,    -1,   546,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   483,    -1,    -1,    -1,    -1,    -1,
     525,    -1,    -1,    -1,    -1,    -1,   495,    -1,    -1,   498,
      -1,    -1,   537,    -1,    -1,    -1,    -1,   542,   543,    -1,
      -1,    -1,    -1,    -1,   549,   514,    -1,    -1,   196,   197,
     198,   556,   200,    -1,    -1,   203,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   219,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   243,    -1,    -1,    -1,   247,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,    -1,    -1,    -1,    -1,    -1,
     288,   289,    -1,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,    -1,    -1,    -1,    -1,   306,    -1,
     308,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     4,    -1,    -1,    -1,     8,    -1,   336,   337,
      -1,    -1,    14,    -1,    16,   343,    -1,    19,    20,    -1,
      -1,    -1,   350,    -1,    -1,    -1,    -1,   355,    -1,   357,
      -1,    -1,    -1,    35,    36,    37,    38,    39,    -1,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    -1,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    70,    71,
      72,    -1,   400,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   425,   426,   101,
     102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   111,
     112,   113,   114,   115,    -1,    -1,    -1,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,    -1,
       8,    -1,    -1,    -1,    -1,   137,    14,    -1,    16,    -1,
      -1,    19,    20,    -1,    -1,    -1,   474,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,
      38,    39,    -1,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    -1,    -1,    -1,    -1,   505,    -1,    57,
      -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    -1,    70,    71,    72,    -1,    -1,    -1,    -1,   527,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   545,    -1,    -1,
     548,    -1,    -1,   101,   102,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   111,   112,   113,   114,   115,    -1,    -1,
      -1,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,    -1,     8,    -1,    -1,    -1,    -1,   137,
      14,    -1,    16,    -1,    -1,    19,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    -1,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    -1,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    -1,    70,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   111,   112,   113,
     114,   115,    -1,    -1,    -1,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,    -1,     8,    -1,
      -1,    -1,    -1,   137,    14,    15,    16,    -1,    -1,    19,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      -1,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,    59,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,   102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   111,   112,   113,   114,   115,    -1,    -1,    -1,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,     8,    -1,    -1,    -1,    -1,   136,    14,    -1,    16,
      -1,    -1,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,
      37,    38,    39,    -1,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      57,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    -1,    70,    71,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   101,   102,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   111,   112,   113,   114,   115,    -1,
      -1,    -1,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,     8,    -1,    -1,    -1,    -1,   136,
      14,    -1,    16,    -1,    -1,    19,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    -1,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    -1,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    -1,    70,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   111,   112,   113,
     114,   115,    -1,    -1,    -1,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,     8,    -1,    -1,
      -1,    -1,   136,    14,    -1,    16,    17,    -1,    19,    20,
      -1,    22,    23,    -1,    -1,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    -1,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,    59,    -1,
      -1,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     101,   102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     111,   112,   113,   114,   115,    -1,    -1,    -1,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
       8,    -1,   133,   134,    -1,    -1,    14,    -1,    16,    17,
      -1,    19,    20,    -1,    22,    23,    -1,    -1,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    -1,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    -1,    -1,    -1,    -1,    -1,    -1,    57,
      -1,    59,    -1,    -1,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,   102,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   111,   112,   113,   114,   115,    -1,    -1,
      -1,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,     8,    -1,   133,   134,    -1,    -1,    14,
      -1,    16,    17,    -1,    19,    20,    -1,    22,    23,    -1,
      -1,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    -1,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    -1,    59,    -1,    -1,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   101,   102,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   111,   112,   113,   114,
     115,    -1,    -1,    -1,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,     8,    -1,   133,   134,
      -1,    -1,    14,    -1,    16,    -1,    -1,    19,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    36,    37,    38,    39,    -1,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    -1,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    70,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
     102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   111,
     112,   113,   114,   115,    -1,    -1,    -1,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,     8,
      -1,    -1,   134,    -1,    -1,    14,    -1,    16,    -1,    -1,
      19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,
      39,    -1,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   101,   102,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   111,   112,   113,   114,   115,    -1,    -1,    -1,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,     8,    -1,   133,    -1,    -1,    -1,    14,    -1,
      16,    -1,    -1,    19,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    39,    -1,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    57,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    -1,    70,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,   102,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   111,   112,   113,   114,   115,
      -1,    -1,    -1,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,     8,    -1,   133,    -1,    -1,
      -1,    14,    -1,    16,    -1,    -1,    19,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    39,    -1,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    57,    -1,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    -1,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   111,   112,
     113,   114,   115,    -1,    -1,    -1,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,     8,    -1,
     133,    -1,    -1,    -1,    14,    -1,    16,    -1,    -1,    19,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      -1,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,    59,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,   102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   111,   112,   113,   114,   115,    -1,    -1,    -1,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,     8,    -1,   133,    -1,    -1,    -1,    14,    -1,    16,
      -1,    -1,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,
      37,    38,    39,    -1,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      57,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    -1,    70,    71,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   101,   102,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   111,   112,   113,   114,   115,    -1,
      -1,    -1,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,     5,    -1,   133,     8,    -1,    -1,
      -1,    -1,    -1,    14,    -1,    16,    -1,    -1,    19,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,    -1,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    70,
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     101,   102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     111,   112,   113,   114,   115,    -1,    -1,    -1,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
       8,    -1,    -1,    -1,    -1,    -1,    14,    15,    16,    -1,
      -1,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,
      38,    39,    -1,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    -1,    -1,    -1,    -1,    -1,    -1,    57,
      -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,   102,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   111,   112,   113,   114,   115,    -1,    -1,
      -1,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,     8,    -1,    -1,    11,    -1,    -1,    14,
      -1,    16,    -1,    -1,    19,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    36,    37,    38,    39,    -1,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    -1,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    -1,    70,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   101,   102,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   111,   112,   113,   114,
     115,    -1,    -1,    -1,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,     8,    -1,    -1,    -1,
      -1,    -1,    14,    -1,    16,    -1,    -1,    19,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    36,    37,    38,    39,    -1,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    -1,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    70,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
     102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   111,
     112,   113,   114,   115,    -1,    -1,    -1,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,     8,
      -1,    -1,    -1,    -1,    -1,    14,    -1,    16,    -1,    -1,
      19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,
      39,    -1,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   101,   102,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   111,   112,   113,   114,   115,    -1,    -1,    -1,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,     8,    -1,    -1,    -1,    -1,    -1,    14,    -1,
      16,    -1,    -1,    19,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    39,    -1,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    57,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    -1,    70,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,   102,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   111,   112,   113,   114,   115,
      -1,    -1,    -1,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,     8,    -1,    -1,    -1,    -1,
      -1,    14,    -1,    16,    -1,    -1,    19,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    39,    -1,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    57,    -1,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    -1,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   111,   112,
     113,   114,   115,    -1,    -1,    -1,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   129,   130,   131,    -1,    -1,    -1,
      -1,    -1,   137,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,
     130,   131,    -1,    -1,    -1,    -1,    -1,   137,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   129,   130,   131,    -1,    -1,    -1,
      -1,    -1,   137,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,
     130,   131,    -1,    -1,    -1,    -1,    -1,   137,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   129,   130,   131,    -1,    -1,    -1,
      -1,    -1,   137,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,
     130,   131,    -1,    -1,    -1,    -1,   136,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   129,   130,   131,    -1,    -1,    -1,    -1,
     136,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,   130,   131,
      -1,    -1,    -1,    -1,   136,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   129,   130,   131,    -1,    -1,    -1,    -1,   136,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   129,   130,   131,    -1,    -1,
      -1,    -1,   136,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,
     130,   131,    -1,    -1,    -1,    -1,   136,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   129,   130,   131,    -1,    -1,    -1,   135,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   129,   130,   131,    -1,
      -1,   134,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,   130,
     131,    -1,    -1,   134,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     129,   130,   131,    -1,    -1,   134,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   129,   130,   131,    -1,   133,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   129,   130,   131,    -1,   133,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   129,   130,   131,    -1,   133,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   129,   130,   131,   132,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   129,   130,   131,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   129,   130,   131,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   129,   130,   131,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,
     130,   131,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   129,   130,   131,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   129,   130,   131,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   129,   130,   131
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,   139,   140,   141,   142,    35,    41,    42,    43,
      44,    45,    46,    47,    48,   143,   223,   224,     0,   142,
      60,   144,   224,    71,   132,   133,   145,     4,     6,     9,
      12,    13,    16,    18,    21,    56,   146,   147,   148,   149,
     150,   151,   153,   154,   155,   156,   161,   162,   163,   170,
     171,   170,    51,    51,    35,   232,    36,   224,   224,   224,
     224,    37,    71,   190,   134,   148,   133,     5,     7,    16,
     133,   145,   132,   132,    10,   133,    10,   133,   133,   133,
       8,    14,    17,    19,    20,    22,    23,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    36,    37,    38,    39,
      49,    50,    57,    59,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,   101,   102,   111,   112,   113,
     114,   115,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   133,   164,   170,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   185,   186,   187,
     188,   190,   191,   194,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   224,
      35,   132,   233,    71,   157,    51,    51,   170,   170,    35,
     234,   234,   220,    35,    71,   194,    72,    72,    72,   219,
      72,   133,   133,    72,   194,   132,   133,   190,   224,   226,
     227,   222,   224,   225,   226,   133,   194,   220,   194,   222,
     224,   194,   194,   194,   220,     4,   168,   169,   192,   194,
     195,   220,   134,   194,   195,    15,   195,   221,   222,   194,
     194,   194,   194,    71,   194,   194,   220,   113,   194,   220,
     194,   194,   194,   194,   194,   194,   194,   194,   194,     5,
     134,   174,   133,   133,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   129,   130,   131,   133,    70,    71,    70,    71,
     131,    40,   221,   228,   132,   158,   159,   160,   233,   221,
     221,   133,   133,   132,    72,    11,   152,   194,   194,   193,
     194,    72,   194,   194,   132,   190,    70,    70,    70,   104,
      70,   133,   131,   135,   194,   131,   232,   135,   137,   137,
     135,   132,   134,   222,   136,   136,   194,    71,   194,   131,
     132,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     222,   222,   222,   222,   222,   194,   194,    37,   233,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
      70,    71,    72,   233,   194,   232,   194,   232,   233,    58,
     229,   230,    72,   228,   134,   135,    73,   229,   229,   221,
     192,   224,   136,   136,   136,   133,   113,   136,   136,   190,
     137,   194,   137,   194,    71,   194,    71,   132,   169,   220,
     170,   194,   170,   194,   134,   194,    71,   228,   194,   232,
     192,   221,    72,   137,   134,   137,   134,    72,   222,   231,
     165,   166,   167,   220,    72,   160,    37,   133,   229,   136,
     190,   190,   190,   194,    71,   194,   190,    71,   182,   137,
     137,   232,   232,   170,     5,   221,   134,   232,    72,   137,
     134,   136,   136,   192,   192,    77,   136,   135,   132,   165,
      25,    24,    25,   189,   189,   133,   194,   136,   183,   184,
     185,   134,   134,   221,   132,   229,   134,   165,   136,   136,
     222,   133,   190,   167,   221,   136,   190,    72,   190,   193,
     134,   190,   134,   186,   185,   229,   228,   136,   229,   133,
     190,   194,   136,   136,   134,    73,    72,   190,    73,   136,
     190,   190,   194,   165,   194,   190,   136,   189,   190
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   138,   139,   140,   140,   141,   141,   142,   142,   142,
     142,   143,   143,   144,   144,   145,   146,   146,   147,   147,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     149,   150,   151,   151,   152,   153,   154,   155,   156,   157,
     158,   158,   159,   159,   159,   160,   160,   161,   162,   163,
     163,   163,   163,   164,   164,   165,   165,   166,   166,   166,
     167,   167,   168,   168,   168,   169,   169,   169,   170,   170,
     171,   171,   172,   172,   173,   173,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   175,   175,   175,   175,   175,
     176,   176,   176,   176,   176,   176,   177,   177,   178,   179,
     179,   180,   181,   182,   182,   183,   183,   184,   184,   185,
     185,   186,   186,   187,   187,   188,   188,   189,   189,   189,
     190,   191,   192,   192,   193,   193,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   195,
     195,   195,   196,   196,   196,   196,   196,   196,   196,   196,
     196,   196,   196,   196,   196,   197,   197,   198,   198,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   200,   200,   200,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   201,   202,   203,
     204,   205,   206,   206,   206,   207,   207,   208,   208,   208,
     209,   209,   209,   210,   210,   211,   211,   211,   211,   211,
     211,   211,   212,   212,   212,   213,   213,   213,   214,   215,
     216,   217,   217,   218,   218,   218,   218,   219,   219,   220,
     221,   221,   222,   222,   222,   223,   224,   224,   224,   224,
     224,   224,   224,   224,   224,   225,   226,   226,   227,   227,
     228,   228,   229,   229,   230,   231,   231,   232,   233,   234
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     5,     7,     5,
       7,     0,     1,     0,     2,     3,     0,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       2,     3,     3,     5,     2,     5,     3,     3,     3,     3,
       0,     1,     3,     2,     1,     1,     3,     7,     6,     9,
       9,     8,     8,     8,    11,     0,     1,     3,     2,     1,
       4,     6,     3,     2,     1,     6,     8,     5,     0,     1,
       2,     1,     0,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       3,     2,     2,     1,     2,     2,     1,     3,     2,     4,
       1,     2,     2,     1,     1,     2,     2,     1,     9,     7,
       9,     5,     5,     3,     4,     0,     1,     2,     1,     4,
       3,     3,     2,     5,     7,     6,     6,     0,     2,     6,
       3,     2,     0,     1,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     3,
       2,     1,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     3,     3,     2,     2,     1,
       3,     3,     2,     4,     5,     5,     2,     6,     3,     6,
       3,     5,     5,     4,     4,     5,     4,     4,     6,     6,
       6,     3,     3,     2,     4,     3,     5,     5,     2,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     3,     4,     4,
       2,     1,     0,     1,     2,     3,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (compiler, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, compiler); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, SPVM_COMPILER* compiler)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (compiler);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, SPVM_COMPILER* compiler)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, compiler);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, SPVM_COMPILER* compiler)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              , compiler);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, compiler); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, SPVM_COMPILER* compiler)
{
  YYUSE (yyvaluep);
  YYUSE (compiler);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (SPVM_COMPILER* compiler)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, compiler);
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 74 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 2651 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 4:
#line 78 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[0].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[0].opval));
        (yyval.opval) = op_list;
      }
    }
#line 2666 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 5:
#line 91 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_list;
      if ((yyvsp[-1].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[-1].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[-1].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[0].opval));
      
      (yyval.opval) = op_list;
    }
#line 2684 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 7:
#line 108 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), NULL, (yyvsp[-2].opval));
    }
#line 2692 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 8:
#line 112 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[-4].opval));
    }
#line 2700 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 9:
#line 116 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), NULL, NULL, (yyvsp[-2].opval));
    }
#line 2708 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 10:
#line 120 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), NULL, (yyvsp[-2].opval), (yyvsp[-4].opval));
    }
#line 2716 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 11:
#line 126 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 2724 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 13:
#line 133 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 2732 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 14:
#line 137 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_extends(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 2740 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 15:
#line 143 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_class_block;
    }
#line 2750 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 16:
#line 151 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 2758 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 17:
#line 155 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[0].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
        SPVM_OP_insert_child(compiler, (yyval.opval), (yyval.opval)->last, (yyvsp[0].opval));
      }
    }
#line 2772 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 18:
#line 167 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_list;
      if ((yyvsp[-1].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[-1].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[-1].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[0].opval));
      
      (yyval.opval) = op_list;
    }
#line 2790 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 30:
#line 196 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    { 
      (yyval.opval) = SPVM_OP_build_init_block(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 2798 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 31:
#line 202 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_version_decl(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2806 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 32:
#line 208 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      int32_t is_require = 0;
      SPVM_OP* op_name_alias = NULL;
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), op_name_alias, is_require);
    }
#line 2816 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 33:
#line 214 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      int32_t is_require = 0;
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), is_require);
    }
#line 2825 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 34:
#line 221 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, compiler->current_file, compiler->current_line);
      int32_t is_require = 1;
      (yyval.opval) = SPVM_OP_build_use(compiler, op_use, (yyvsp[0].opval), NULL, is_require);
    }
#line 2835 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 35:
#line 229 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_alias(compiler, op_use, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 2844 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 36:
#line 236 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_allow(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2852 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 37:
#line 242 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_implement(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2860 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 38:
#line 248 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_definition(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), (yyvsp[-2].opval));
    }
#line 2868 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 39:
#line 254 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_enum_block;
    }
#line 2878 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 40:
#line 262 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 2886 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 41:
#line 266 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[0].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[0].opval));
        (yyval.opval) = op_list;
      }
    }
#line 2901 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 42:
#line 279 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_list;
      if ((yyvsp[-2].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[-2].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[-2].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[0].opval));
      
      (yyval.opval) = op_list;
    }
#line 2919 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 45:
#line 297 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[0].opval), NULL);
    }
#line 2927 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 46:
#line 301 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2935 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 47:
#line 307 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class_var_definition(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-2].opval));
    }
#line 2943 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 48:
#line 313 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_field_definition(compiler, (yyvsp[-5].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2951 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 49:
#line 319 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method_definition(compiler, (yyvsp[-7].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-8].opval), (yyvsp[0].opval), NULL, 0, 0);
     }
#line 2959 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 50:
#line 323 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method_definition(compiler, (yyvsp[-7].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-8].opval), NULL, NULL, 0, 0);
     }
#line 2967 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 51:
#line 327 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method_definition(compiler, (yyvsp[-6].opval), NULL, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-7].opval), (yyvsp[0].opval), NULL, 0, 0);
     }
#line 2975 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 52:
#line 331 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method_definition(compiler, (yyvsp[-6].opval), NULL, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-7].opval), NULL, NULL, 0, 0);
     }
#line 2983 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 53:
#line 337 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t is_init = 0;
       int32_t is_anon = 1;
       (yyval.opval) = SPVM_OP_build_method_definition(compiler, (yyvsp[-6].opval), NULL, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-7].opval), (yyvsp[0].opval), NULL, is_init, is_anon);
     }
#line 2993 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 54:
#line 343 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       SPVM_OP* op_list_args;
       if ((yyvsp[-9].opval)->id == SPVM_OP_C_ID_LIST) {
         op_list_args = (yyvsp[-9].opval);
       }
       else {
         op_list_args = SPVM_OP_new_op_list(compiler, (yyvsp[-9].opval)->file, (yyvsp[-9].opval)->line);
         SPVM_OP_insert_child(compiler, op_list_args, op_list_args->last, (yyvsp[-9].opval));
       }
       
       int32_t is_init = 0;
       int32_t is_anon = 1;
       (yyval.opval) = SPVM_OP_build_method_definition(compiler, (yyvsp[-6].opval), NULL, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-7].opval), (yyvsp[0].opval), op_list_args, is_init, is_anon);
     }
#line 3012 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 55:
#line 360 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3020 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 56:
#line 364 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[0].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[0].opval));
        (yyval.opval) = op_list;
      }
    }
#line 3035 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 57:
#line 377 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_list;
      if ((yyvsp[-2].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[-2].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[-2].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[0].opval));
      
      (yyval.opval) = op_list;
    }
#line 3053 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 60:
#line 395 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval), NULL, NULL);
    }
#line 3061 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 61:
#line 399 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), NULL, (yyvsp[0].opval));
    }
#line 3069 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 62:
#line 405 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_list;
      if ((yyvsp[-2].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[-2].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[-2].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[0].opval));
      
      (yyval.opval) = op_list;
    }
#line 3087 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 65:
#line 423 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_anon_method_field_definition(compiler, (yyvsp[-5].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-1].opval), NULL);
    }
#line 3095 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 66:
#line 427 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_anon_method_field_definition(compiler, (yyvsp[-7].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[0].opval));
    }
#line 3103 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 67:
#line 431 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_FIELD, (yyvsp[-4].opval)->file, (yyvsp[-4].opval)->line);
      
      (yyval.opval) = SPVM_OP_build_anon_method_field_definition(compiler, op_field, NULL, (yyvsp[-2].opval), (yyvsp[-1].opval), (yyvsp[-4].opval));
    }
#line 3113 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 68:
#line 439 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3121 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 69:
#line 443 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[0].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[0].opval));
        (yyval.opval) = op_list;
      }
    }
#line 3136 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 70:
#line 456 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_list;
      if ((yyvsp[-1].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[-1].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[-1].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[0].opval));
      
      (yyval.opval) = op_list;
    }
#line 3154 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 72:
#line 473 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3162 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 73:
#line 477 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[0].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[0].opval));
        (yyval.opval) = op_list;
      }
    }
#line 3177 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 74:
#line 490 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_list;
      if ((yyvsp[-1].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[-1].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[-1].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[0].opval));
      
      (yyval.opval) = op_list;
    }
#line 3195 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 89:
#line 520 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[-1].opval), NULL);
    }
#line 3203 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 90:
#line 524 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3211 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 91:
#line 528 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_operator_statement(compiler, (yyvsp[-1].opval));
    }
#line 3219 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 93:
#line 533 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
#line 3227 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 95:
#line 540 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 3235 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 96:
#line 544 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[0].opval), NULL, NULL);
    }
#line 3243 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 97:
#line 548 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-2].opval), (yyvsp[0].opval), (yyvsp[-1].opval));
    }
#line 3251 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 98:
#line 552 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-1].opval), NULL, (yyvsp[0].opval));
    }
#line 3259 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 99:
#line 556 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-3].opval), (yyvsp[0].opval), (yyvsp[-2].opval));
    }
#line 3267 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 101:
#line 563 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_print(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3275 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 102:
#line 567 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_print(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3283 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 105:
#line 573 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_make_read_only(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3291 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 106:
#line 579 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_warn(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3299 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 107:
#line 583 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_warn(compiler, (yyvsp[0].opval), NULL);
    }
#line 3307 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 108:
#line 589 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[-8].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3315 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 109:
#line 595 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_foreach_statement(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3323 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 110:
#line 599 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_foreach_statement(compiler, (yyvsp[-8].opval), (yyvsp[-7].opval), (yyvsp[-3].opval), (yyvsp[0].opval));
    }
#line 3331 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 111:
#line 605 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3339 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 112:
#line 611 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3347 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 113:
#line 617 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->current_file, compiler->current_line);
      op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[-1].opval), NULL);
    }
#line 3357 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 114:
#line 623 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->current_file, compiler->current_line);
      op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3367 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 115:
#line 631 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3375 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 116:
#line 635 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[0].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[0].opval));
        (yyval.opval) = op_list;
      }
    }
#line 3390 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 117:
#line 648 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_list;
      if ((yyvsp[-1].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[-1].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[-1].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[0].opval));
      
      (yyval.opval) = op_list;
    }
#line 3408 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 118:
#line 662 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 3416 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 119:
#line 668 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3424 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 120:
#line 672 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), NULL);
    }
#line 3432 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 121:
#line 678 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3440 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 122:
#line 682 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[-1].opval), NULL);
    }
#line 3448 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 123:
#line 688 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->current_file, compiler->current_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[-2].opval), (yyvsp[0].opval), NULL);
    }
#line 3458 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 124:
#line 694 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->current_file, compiler->current_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3468 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 125:
#line 701 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval), 0);
      
      // if is wraped with block to allow the following syntax
      //  if (var_decl $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    }
#line 3483 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 126:
#line 712 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval), 0);
      
      // if is wraped with block to allow the following syntax
      //  if (var_decl $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    }
#line 3498 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 127:
#line 725 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
#line 3506 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 128:
#line 729 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 3514 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 129:
#line 733 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval), 0);
    }
#line 3522 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 130:
#line 739 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_block;
    }
#line 3532 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 131:
#line 747 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3540 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 132:
#line 753 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3548 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 133:
#line 757 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[0].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[0].opval));
        (yyval.opval) = op_list;
      }
    }
#line 3563 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 134:
#line 770 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
#line 3571 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 153:
#line 794 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      if ((yyvsp[-1].opval)->id == SPVM_OP_C_ID_LIST) {
        SPVM_OP* op_operator = (yyvsp[-1].opval)->first;
        SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, compiler->current_file, compiler->current_line);
        while ((op_operator = SPVM_OP_sibling(compiler, op_operator))) {
          SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_operator);
          SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_operator);
          op_operator = op_stab;
        }
        (yyval.opval) = op_sequence;
      }
      else {
        (yyval.opval) = (yyvsp[-1].opval);
      }
    }
#line 3591 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 162:
#line 818 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_true(compiler, (yyvsp[0].opval));
    }
#line 3599 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 163:
#line 822 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_false(compiler, (yyvsp[0].opval));
    }
#line 3607 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 166:
#line 828 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_basic_type_id(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3615 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 169:
#line 836 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_list;
      if ((yyvsp[-2].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[-2].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[-2].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[0].opval));
      
      (yyval.opval) = op_list;
    }
#line 3633 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 170:
#line 850 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[-1].opval);
    }
#line 3641 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 171:
#line 854 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 3649 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 172:
#line 860 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, operator, (yyvsp[0].opval));
    }
#line 3658 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 173:
#line 865 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MINUS, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, op_negate, (yyvsp[0].opval));
    }
#line 3667 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 174:
#line 870 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3675 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 175:
#line 874 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op_var(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3683 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 176:
#line 878 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3691 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 177:
#line 882 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3699 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 178:
#line 886 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3707 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 179:
#line 890 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3715 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 180:
#line 894 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op_var(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3723 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 181:
#line 898 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op_var(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3731 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 182:
#line 902 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3739 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 183:
#line 906 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3747 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 184:
#line 910 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3755 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 185:
#line 916 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, operator, (yyvsp[0].opval));
    }
#line 3764 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 186:
#line 921 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, operator, (yyvsp[-1].opval));
    }
#line 3773 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 187:
#line 928 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, operator, (yyvsp[0].opval));
    }
#line 3782 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 188:
#line 933 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, operator, (yyvsp[-1].opval));
    }
#line 3791 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 189:
#line 940 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, operator, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3800 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 190:
#line 945 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, operator, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3809 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 191:
#line 950 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MULTIPLY, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, operator, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3818 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 192:
#line 955 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3826 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 193:
#line 959 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3834 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 194:
#line 963 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3842 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 195:
#line 967 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3850 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 196:
#line 971 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3858 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 197:
#line 975 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3866 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 198:
#line 979 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3874 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 199:
#line 983 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3882 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 200:
#line 987 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3890 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 201:
#line 991 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3898 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 202:
#line 995 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3906 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1001 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3914 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1005 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3922 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1009 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3930 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1013 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3938 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1017 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3946 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1021 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3954 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1025 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3962 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1029 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3970 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1033 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3978 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1037 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3986 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1041 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3994 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1045 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4002 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1049 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4010 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1053 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4018 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1059 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4026 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1065 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_isa_error(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4034 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1071 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_is_type(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4042 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1077 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_is_error(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4050 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1083 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_is_compile_type(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4058 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1089 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_logical_or(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4066 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1093 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_logical_and(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4074 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1097 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_logical_not(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4082 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1103 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4090 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1107 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_special_assign(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4098 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1113 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 4106 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1117 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_length = (yyvsp[0].opval)->last;
      SPVM_OP_cut_op(compiler, (yyvsp[0].opval)->last);
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), op_length);
    }
#line 4116 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1123 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_anon_method(compiler, (yyvsp[0].opval));
    }
#line 4124 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1129 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->current_file, compiler->current_line);
      int32_t is_key_values = 0;
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[-1].opval), is_key_values);
    }
#line 4134 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1135 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->current_file, compiler->current_line);
      int32_t is_key_values = 1;
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[-1].opval), is_key_values);
    }
#line 4144 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1141 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->current_file, compiler->current_line);
      int32_t is_key_values = 1;
      SPVM_OP* op_list_elements = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, op_list_elements, is_key_values);
    }
#line 4155 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1150 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      (yyval.opval) = SPVM_OP_build_type_cast(compiler, op_convert, (yyvsp[-2].opval), (yyvsp[0].opval), NULL);
    }
#line 4164 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1155 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_type_cast(compiler, op_convert, (yyvsp[-1].opval), (yyvsp[-4].opval), NULL);
    }
#line 4173 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1162 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4182 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1167 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, (yyvsp[-1].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-1].opval), (yyvsp[0].opval), op_operators);
    }
#line 4192 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1173 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4201 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1178 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-2].opval), (yyvsp[0].opval), op_operators);
    }
#line 4211 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1184 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4220 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1189 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-2].opval), (yyvsp[0].opval), op_operators);
    }
#line 4230 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1195 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_method_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[-3].opval)->file, (yyvsp[-3].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-4].opval), op_method_name, (yyvsp[-1].opval));
    }
#line 4240 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1203 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_ACCESS, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_access(compiler, op_array_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 4249 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1208 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_ACCESS, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_access(compiler, op_array_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4258 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1213 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_ACCESS, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_access(compiler, op_array_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4267 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1220 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 4276 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1225 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4285 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1230 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_access = (yyvsp[-3].opval);
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_field_access(compiler, op_field_access, op_array_access, (yyvsp[-1].opval));
    }
#line 4295 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1238 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 4305 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1246 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_unweaken_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 4315 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1254 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_isweak_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 4325 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1262 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_can(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4333 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1266 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_can(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4341 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1272 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[0].opval));
    }
#line 4350 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1277 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[-1].opval));
    }
#line 4359 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1282 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[0].opval));
    }
#line 4368 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1287 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[-1].opval));
    }
#line 4377 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1294 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var_decl(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), NULL);
    }
#line 4385 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1298 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var_decl(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL, NULL);
    }
#line 4393 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1304 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[0].opval));
    }
#line 4401 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1310 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
    (yyval.opval) = SPVM_OP_build_mutable_type(compiler, (yyvsp[0].opval));
  }
#line 4409 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1324 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[0].opval));
    }
#line 4417 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1328 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_byte_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 4427 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1334 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_short_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 4437 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1340 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 4447 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1346 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_long_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 4457 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1352 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_float_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 4467 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1358 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_double_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 4477 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1364 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_any_object_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = op_type;
    }
#line 4486 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1369 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_string_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 4496 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 275:
#line 1377 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[-1].opval));
    }
#line 4504 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1383 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-2].opval), NULL);
    }
#line 4512 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1387 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-2].opval), NULL);
    }
#line 4520 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1393 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4528 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1397 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4536 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1404 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_void_type(compiler, compiler->current_file, compiler->current_line);
    }
#line 4544 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1410 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
#line 4552 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 284:
#line 1417 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 4560 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1423 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_list;
      if ((yyvsp[-2].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[-2].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[-2].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[0].opval));
      
      (yyval.opval) = op_list;
    }
#line 4578 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1437 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 4586 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;


#line 4590 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (compiler, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (compiler, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, compiler);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 1450 "yacc/spvm_yacc.y" /* yacc.c:1906  */

