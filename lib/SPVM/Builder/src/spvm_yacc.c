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
    GET = 260,
    SET = 261,
    METHOD = 262,
    OUR = 263,
    ENUM = 264,
    MY = 265,
    USE = 266,
    AS = 267,
    REQUIRE = 268,
    ALIAS = 269,
    ALLOW = 270,
    OUTMOST_CLASS = 271,
    MUTABLE = 272,
    ATTRIBUTE = 273,
    MAKE_READ_ONLY = 274,
    INTERFACE = 275,
    EVAL_ERROR_ID = 276,
    ARGS_WIDTH = 277,
    VERSION_DECL = 278,
    VERSION_FROM = 279,
    IF = 280,
    UNLESS = 281,
    ELSIF = 282,
    ELSE = 283,
    FOR = 284,
    WHILE = 285,
    LAST = 286,
    NEXT = 287,
    SWITCH = 288,
    CASE = 289,
    DEFAULT = 290,
    BREAK = 291,
    EVAL = 292,
    SYMBOL_NAME = 293,
    VAR_NAME = 294,
    CONSTANT = 295,
    EXCEPTION_VAR = 296,
    COPY_FIELDS = 297,
    UNDEF = 298,
    VOID = 299,
    BYTE = 300,
    SHORT = 301,
    INT = 302,
    LONG = 303,
    FLOAT = 304,
    DOUBLE = 305,
    STRING = 306,
    OBJECT = 307,
    TRUE = 308,
    FALSE = 309,
    END_OF_FILE = 310,
    RW = 311,
    RO = 312,
    WO = 313,
    INIT = 314,
    NEW = 315,
    OF = 316,
    BASIC_TYPE_ID = 317,
    EXTENDS = 318,
    SUPER = 319,
    RETURN = 320,
    WEAKEN = 321,
    DIE = 322,
    WARN = 323,
    PRINT = 324,
    SAY = 325,
    OUTMOST_CLASS_NAME = 326,
    UNWEAKEN = 327,
    ENABLE_OPTIONS = 328,
    DISABLE_OPTIONS = 329,
    FATCAMMA = 330,
    ASSIGN = 331,
    SPECIAL_ASSIGN = 332,
    LOGICAL_OR = 333,
    DEFINED_OR = 334,
    LOGICAL_AND = 335,
    BIT_OR = 336,
    BIT_XOR = 337,
    BIT_AND = 338,
    NUMEQ = 339,
    NUMNE = 340,
    STREQ = 341,
    STRNE = 342,
    NUMGT = 343,
    NUMGE = 344,
    NUMLT = 345,
    NUMLE = 346,
    STRGT = 347,
    STRGE = 348,
    STRLT = 349,
    STRLE = 350,
    ISA = 351,
    ISA_ERROR = 352,
    IS_TYPE = 353,
    IS_ERROR = 354,
    IS_COMPILE_TYPE = 355,
    NUMERIC_CMP = 356,
    STRING_CMP = 357,
    CAN = 358,
    SHIFT = 359,
    DIVIDE = 360,
    DIVIDE_UNSIGNED_INT = 361,
    DIVIDE_UNSIGNED_LONG = 362,
    MODULO = 363,
    MODULO_UNSIGNED_INT = 364,
    MODULO_UNSIGNED_LONG = 365,
    LOGICAL_NOT = 366,
    BIT_NOT = 367,
    REFERENCE = 368,
    DEREFERENCE = 369,
    PLUS = 370,
    MINUS = 371,
    CONVERT = 372,
    SCALAR = 373,
    STRING_LENGTH = 374,
    ISWEAK = 375,
    TYPE_NAME = 376,
    COMPILE_TYPE_NAME = 377,
    DUMP = 378,
    NEW_STRING_LEN = 379,
    IS_READ_ONLY = 380,
    COPY = 381,
    ADDRESS = 382,
    IS_OPTIONS = 383,
    INC = 384,
    DEC = 385,
    ARROW = 386
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_LIB_SPVM_BUILDER_INCLUDE_SPVM_YACC_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 265 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:358  */

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
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   4768

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  147
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  105
/* YYNRULES -- Number of rules.  */
#define YYNRULES  309
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  597

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   386

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
     141,   140,   111,   108,    75,   109,   110,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    80,   145,
       2,     2,     2,    79,   120,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   142,     2,   144,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   143,     2,   146,     2,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      76,    77,    78,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     112,   113,   114,   115,   116,   117,   118,   119,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    82,    82,    85,    88,    91,    94,    95,   100,   101,
     102,   105,   109,   115,   121,   127,   133,   139,   145,   150,
     158,   164,   168,   174,   178,   184,   185,   192,   195,   198,
     199,   202,   208,   222,   229,   232,   245,   259,   262,   266,
     270,   274,   281,   284,   288,   291,   297,   306,   309,   321,
     335,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   351,   357,   363,   369,   375,   382,   390,   397,
     403,   409,   415,   424,   427,   440,   454,   455,   458,   462,
     468,   474,   479,   481,   484,   486,   488,   491,   494,   498,
     502,   506,   512,   516,   534,   537,   550,   564,   565,   568,
     572,   578,   592,   593,   596,   600,   604,   610,   619,   622,
     635,   649,   653,   656,   669,   683,   686,   687,   688,   689,
     690,   691,   692,   693,   694,   695,   696,   697,   698,   699,
     703,   707,   708,   712,   713,   719,   723,   727,   731,   735,
     741,   742,   746,   750,   751,   752,   756,   760,   764,   767,
     773,   777,   783,   789,   795,   800,   808,   811,   824,   838,
     844,   848,   854,   858,   864,   870,   877,   887,   901,   904,
     908,   915,   923,   929,   933,   939,   946,   949,   963,   966,
     969,   970,   971,   972,   973,   974,   975,   976,   977,   978,
     982,   986,   987,   988,   989,   990,   991,   992,   993,   994,
     998,   999,  1000,  1001,  1002,  1003,  1004,  1007,  1023,  1036,
    1050,  1054,  1060,  1065,  1070,  1074,  1078,  1082,  1086,  1090,
    1094,  1098,  1102,  1106,  1110,  1111,  1115,  1121,  1126,  1131,
    1136,  1143,  1148,  1155,  1160,  1167,  1168,  1169,  1170,  1171,
    1172,  1175,  1180,  1185,  1190,  1194,  1198,  1202,  1206,  1210,
    1216,  1223,  1227,  1231,  1235,  1241,  1245,  1249,  1253,  1257,
    1261,  1265,  1269,  1273,  1277,  1281,  1285,  1289,  1293,  1299,
    1305,  1309,  1313,  1319,  1325,  1329,  1333,  1337,  1341,  1347,
    1352,  1359,  1363,  1369,  1373,  1379,  1383,  1389,  1395,  1401,
    1407,  1416,  1421,  1427,  1432,  1438,  1443,  1449,  1457,  1462,
    1467,  1474,  1479,  1484,  1492,  1500,  1508,  1516,  1520,  1526
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CLASS", "HAS", "GET", "SET", "METHOD",
  "OUR", "ENUM", "MY", "USE", "AS", "REQUIRE", "ALIAS", "ALLOW",
  "OUTMOST_CLASS", "MUTABLE", "ATTRIBUTE", "MAKE_READ_ONLY", "INTERFACE",
  "EVAL_ERROR_ID", "ARGS_WIDTH", "VERSION_DECL", "VERSION_FROM", "IF",
  "UNLESS", "ELSIF", "ELSE", "FOR", "WHILE", "LAST", "NEXT", "SWITCH",
  "CASE", "DEFAULT", "BREAK", "EVAL", "SYMBOL_NAME", "VAR_NAME",
  "CONSTANT", "EXCEPTION_VAR", "COPY_FIELDS", "UNDEF", "VOID", "BYTE",
  "SHORT", "INT", "LONG", "FLOAT", "DOUBLE", "STRING", "OBJECT", "TRUE",
  "FALSE", "END_OF_FILE", "RW", "RO", "WO", "INIT", "NEW", "OF",
  "BASIC_TYPE_ID", "EXTENDS", "SUPER", "RETURN", "WEAKEN", "DIE", "WARN",
  "PRINT", "SAY", "OUTMOST_CLASS_NAME", "UNWEAKEN", "ENABLE_OPTIONS",
  "DISABLE_OPTIONS", "','", "FATCAMMA", "ASSIGN", "SPECIAL_ASSIGN", "'?'",
  "':'", "LOGICAL_OR", "DEFINED_OR", "LOGICAL_AND", "BIT_OR", "BIT_XOR",
  "BIT_AND", "NUMEQ", "NUMNE", "STREQ", "STRNE", "NUMGT", "NUMGE", "NUMLT",
  "NUMLE", "STRGT", "STRGE", "STRLT", "STRLE", "ISA", "ISA_ERROR",
  "IS_TYPE", "IS_ERROR", "IS_COMPILE_TYPE", "NUMERIC_CMP", "STRING_CMP",
  "CAN", "SHIFT", "'+'", "'-'", "'.'", "'*'", "DIVIDE",
  "DIVIDE_UNSIGNED_INT", "DIVIDE_UNSIGNED_LONG", "MODULO",
  "MODULO_UNSIGNED_INT", "MODULO_UNSIGNED_LONG", "LOGICAL_NOT", "BIT_NOT",
  "'@'", "REFERENCE", "DEREFERENCE", "PLUS", "MINUS", "CONVERT", "SCALAR",
  "STRING_LENGTH", "ISWEAK", "TYPE_NAME", "COMPILE_TYPE_NAME", "DUMP",
  "NEW_STRING_LEN", "IS_READ_ONLY", "COPY", "ADDRESS", "IS_OPTIONS", "INC",
  "DEC", "ARROW", "')'", "'('", "'['", "'{'", "']'", "';'", "'}'",
  "$accept", "grammar", "field_name", "method_name", "class_name",
  "qualified_type", "type", "basic_type", "ref_type", "array_type",
  "array_type_with_length", "return_type", "opt_type_comments",
  "type_comments", "type_comment", "union_type", "opt_classes", "classes",
  "class", "opt_basic_type", "opt_extends", "class_block",
  "opt_definitions", "definitions", "definition", "init_statement",
  "version_decl", "version_from", "use", "require", "class_alias", "allow",
  "interface", "enumeration", "enumeration_block", "opt_enumeration_items",
  "enumeration_items", "enumeration_item", "our", "has", "opt_getter",
  "getter", "opt_setter", "setter", "method", "anon_method", "opt_args",
  "args", "arg", "anon_method_fields", "anon_method_field",
  "opt_attributes", "attributes", "opt_statements", "statements",
  "statement", "die", "void_return_operator", "for_statement",
  "foreach_statement", "while_statement", "switch_statement",
  "switch_block", "opt_case_statements", "case_statements",
  "case_statement", "default_statement", "if_require_statement",
  "if_statement", "else_statement", "block", "eval_block", "var_decl",
  "var", "opt_operators", "opt_operator", "operator", "sequential",
  "operators", "unary_operator", "array_length", "inc", "dec",
  "binary_operator", "arithmetic_operator", "ternary_operator",
  "bit_operator", "comparison_operator", "string_concatenation",
  "logical_operator", "defined_or", "type_check", "type_cast", "can",
  "assign", "new", "array_init", "call_method", "array_access",
  "field_access", "weaken_field", "unweaken_field", "isweak_field", "warn",
  "copy_fields", YY_NULLPTR
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
     325,   326,   327,   328,   329,    44,   330,   331,   332,    63,
      58,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,    43,    45,
      46,    42,   360,   361,   362,   363,   364,   365,   366,   367,
      64,   368,   369,   370,   371,   372,   373,   374,   375,   376,
     377,   378,   379,   380,   381,   382,   383,   384,   385,   386,
      41,    40,    91,   123,    93,    59,   125
};
# endif

#define YYPACT_NINF -488

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-488)))

#define YYTABLE_NINF -309

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-309)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      18,   218,    50,  -488,    18,  -488,  -488,  -488,  -488,  -488,
    -488,  -488,  -488,  -488,  -488,  -488,    -9,  -488,  -488,   218,
     -63,  -488,    44,    80,    12,    28,  -488,   -97,    52,    47,
      62,   218,   218,   218,   218,    56,   218,   -41,   -31,   106,
    -488,  -488,  -488,  -488,  -488,  -488,  -488,  -488,  -488,  -488,
     -29,  -488,    38,  -488,  -488,    63,    68,  -488,  -488,    45,
      48,    -3,   115,   -11,    -8,    -7,     1,   881,  -488,  -488,
    -488,  -488,   -28,     4,  -488,  -488,    44,    44,    97,  -488,
      97,  -488,  -488,  -488,  -488,   119,    98,  2644,  -488,  -488,
      19,    21,     3,    23,    14,    31,    26,  2644,    65,    32,
     -41,  -488,  -488,  -488,  2644,  -488,  -488,  -488,   218,   218,
    1513,   119,  1643,  1688,  2644,  2644,  -488,   119,  2644,  2644,
    2644,  2644,  2644,  2644,  2689,  2644,   119,    43,  2644,   119,
    2644,  2644,  2644,  2644,  2644,  2644,  2644,  2644,  2644,  2644,
    2296,   687,  1015,  -488,    40,  -488,   173,    35,  1149,  -488,
      37,    39,  -488,  -488,  -488,  -488,  -488,  -488,  -488,  -488,
    -488,  -488,  -488,  -488,  3128,  -488,  -488,  -488,  -488,  -488,
    -488,  -488,  -488,  -488,  -488,  -488,  -488,  -488,  -488,  -488,
    -488,  -488,  -488,  -488,  -488,  -113,   -85,  -488,  -488,  -488,
    -488,  -488,  -488,   105,   103,   147,  -488,   171,   171,  -488,
      41,    42,   109,    51,  1331,  4349,  2341,  2644,  1818,    58,
    2644,  -488,  -488,  2644,  4223,   -41,  -488,  -488,  3582,    70,
      71,  -488,  -488,   -76,  -488,    72,  -488,  3193,    61,  1863,
     -74,  3647,  4349,  4349,  4349,    76,  4349,  4349,   -99,   -99,
     -99,   -99,  1331,   -99,   -99,  -488,  2818,   -99,    85,   -99,
     -99,   -99,   -99,   -99,   -99,   -99,   -99,   -95,   -95,   218,
      88,   129,  4349,   -53,    47,   -52,  -488,   111,    66,   150,
    -488,  3128,   -60,   147,   162,  -488,  -488,  -488,  -488,  2644,
    2644,  2644,  2644,  2644,  2644,  2644,  2644,  2644,  2644,  2644,
    2644,  2644,  2644,  2644,  2644,  2644,  2644,  2644,  2644,  2644,
     218,   218,   218,   218,   171,  2644,  2644,    15,  2644,  2644,
    2644,  2644,  2644,  2644,  2644,  2644,  2644,  2644,  2644,  -488,
    -488,   -10,  -488,  2644,    47,  2644,    47,  -488,  -488,    89,
     105,   166,    99,   169,  -488,   241,   102,  -488,  -488,   171,
    2470,   218,   108,  3775,  3839,   104,  4349,   130,  3903,  3967,
     -41,  -488,  2644,  1993,  2038,  -488,   107,   110,  -488,   114,
    4349,  2644,   131,  2930,  1331,   -99,   132,   129,  2644,   218,
    -488,   129,  -488,  1286,  -488,   178,    22,    44,    44,  -488,
    1468,  -488,   112,   105,  4349,  4349,  4286,  4467,  4467,  4523,
    2153,  2153,  4576,  4629,  4629,  4629,  4629,   251,   251,   251,
     251,   251,   251,   251,   251,  -488,  -488,  -488,  -488,  -488,
     251,   251,  -488,  -488,   123,    57,    57,    57,   -99,   -99,
     -99,   -99,   -99,   -99,   -99,  2167,  2644,    47,   135,  3258,
     126,  3322,   127,   119,   136,   238,  -488,   147,   -41,   273,
    -488,  -488,  -488,   140,  -488,   -41,   -41,   -41,  1818,  2863,
     -41,   138,  -488,  3712,  -488,  3386,  -488,  3450,    47,  4349,
      47,  -488,  2996,    47,  -488,   -99,  -488,   198,  -488,   142,
     209,  4349,    44,  -488,   111,   278,   171,  2470,   145,  2644,
     148,   149,  3514,   144,  2470,  -488,  -488,  -488,  -488,   151,
     217,  -488,   213,   119,  -488,  -488,  -488,   -41,  -488,  -488,
    -488,   266,    49,    49,   152,  1331,  4031,  -488,   261,  -488,
     218,  -488,  -488,   153,   159,  -488,   160,   218,  2644,  2644,
     171,   216,   221,   167,   119,  4410,  -488,  -488,  -488,  -488,
     168,   -72,   119,   171,   170,  -488,   -41,   174,   -41,  -488,
    -488,  2515,  3062,   -41,   -27,   261,  -488,  -488,  -488,  -488,
    -488,  -488,  4095,   232,   105,  2644,  -488,   172,  -488,  -488,
    -488,  -488,   234,   -46,  -488,  2644,  -488,   176,   177,  -488,
    -488,   175,  -488,  -488,  2644,   179,  4349,   -41,  2644,  -488,
    -488,  4159,   -41,   -41,  -488,  4349,   119,  -488,  4349,   -41,
    -488,  -488,   182,    49,   -41,  -488,  -488
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      34,    42,     0,     2,    35,    37,    11,    12,    13,    14,
      15,    16,    17,    19,    18,    43,    44,     1,    36,     0,
       0,    45,   108,   108,     0,     0,   111,     0,   109,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   108,
      50,    57,    51,    52,    53,    54,    55,    56,    58,    59,
       0,    61,     0,    40,    38,     0,     0,   110,     3,     0,
       0,     0,     0,     0,     0,     0,     0,   108,    62,    46,
      49,    60,     0,     0,    41,    39,   108,   108,     0,    65,
       0,    69,    70,    63,    64,     0,     0,   108,   187,   188,
       0,     0,     0,     0,     0,     0,     0,   108,     0,     0,
       0,   175,   182,   181,   108,   183,   189,   190,     0,     0,
     108,     0,   108,   108,   108,   108,   191,     0,   108,   108,
     108,   108,   108,   108,   108,   108,     0,     0,   108,     0,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   134,     0,   287,     0,     0,   108,   115,
       0,     0,   117,   118,   119,   121,   122,   123,   125,   116,
     120,   124,   186,   180,     0,   206,   192,   224,   196,   197,
     193,   235,   194,   236,   237,   238,   239,   240,   198,   184,
     200,   195,   185,   201,   205,   202,   203,   143,   144,   204,
     140,   148,     4,     0,     0,    73,    71,     0,     0,     5,
       0,     0,   174,   292,   108,   145,   108,   108,   108,     0,
     108,   126,   127,   108,     0,   163,   128,   172,     0,   285,
       0,   286,   199,     8,    10,     9,   129,     0,     0,   108,
       8,   135,   307,   141,   142,     0,   146,   147,   212,   213,
     272,   214,   108,   227,   220,   219,   108,   217,     0,   215,
     216,   218,   221,   223,   222,   225,   226,   231,   233,     0,
       0,    27,   211,     0,     0,     0,   103,   180,     0,   177,
     290,   211,     0,     0,     0,   171,   114,   131,   133,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
       0,     0,     0,     0,     0,   108,   108,     0,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   232,
     234,     0,   132,   108,     0,   108,     0,    26,    25,     0,
       0,    78,     0,    74,    77,    82,     0,    66,    68,     0,
     108,     0,     0,     0,     0,     0,   179,     0,     0,     0,
     161,   162,   108,   108,   108,    20,     0,     0,   130,     0,
     137,   108,     0,   211,   108,   229,     0,    27,   108,     0,
       6,    28,    30,   210,   207,     0,   102,   108,   108,   288,
     210,   289,   294,     0,   283,   284,     0,   270,   273,   271,
     253,   251,   252,   255,   256,   262,   263,   257,   258,   259,
     260,   264,   265,   266,   267,   274,   275,   276,   277,   278,
     261,   268,   282,   281,   254,   241,   242,   269,   243,   244,
     245,   246,   247,   248,   249,   108,   108,     0,   296,     0,
       0,     0,     0,    94,     0,     0,    72,    76,     0,    85,
      83,    80,   173,     0,    67,     0,     0,     0,   108,   108,
       0,     0,   160,     0,    21,     0,    22,     0,     0,   139,
       0,   228,   211,     0,     7,   279,    33,    31,    29,     0,
       0,   209,   108,   101,     0,     0,     0,   108,     0,   108,
       0,     0,     0,     0,   108,   299,   303,   300,   302,     0,
      95,    98,     0,    94,    79,    75,    84,     0,    81,    86,
     291,   164,   168,   168,     0,   108,     0,   152,   156,   153,
       0,    23,    24,     0,     0,   230,     0,     0,   108,   108,
       0,     0,   106,     0,    94,   250,   280,   297,   298,   301,
       0,     0,    97,     0,     0,    87,     0,     0,     0,   166,
     167,   108,   211,     0,     0,   157,   159,   309,   304,   305,
     306,    32,     0,   104,     0,   108,   293,     0,   295,    91,
      90,    96,    99,     0,   165,   108,   169,     0,     0,   150,
     154,     0,   158,   208,   108,     0,   107,     0,   108,    89,
      88,     0,     0,     0,   155,   105,    94,    92,   100,     0,
     149,   151,     0,   168,     0,   170,    93
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -488,  -488,  -252,   -66,   239,  -138,   -98,     0,  -488,   206,
    -488,  -327,   -49,  -488,   -48,  -488,  -488,  -488,   320,  -488,
    -488,   298,  -488,  -488,   287,  -488,  -488,  -488,  -488,  -488,
    -488,  -488,  -488,  -488,  -488,  -488,  -488,  -110,  -488,  -488,
    -488,  -488,  -488,  -488,  -488,  -488,  -473,  -488,  -204,  -488,
     -47,     2,  -488,  -488,  -488,   183,  -488,  -488,  -488,  -488,
    -488,  -488,  -488,  -488,  -488,  -481,  -212,  -488,   -40,  -487,
     -37,  -488,   242,   -36,  -336,  -430,   331,  -488,  -135,  -488,
    -488,  -488,  -488,  -488,  -488,  -488,  -488,  -488,  -488,  -488,
    -488,  -488,  -488,  -488,  -488,  -488,  -488,  -488,  -488,  -488,
    -488,  -488,  -488,  -488,  -488
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    59,   331,   200,   328,   261,   144,   224,   225,
     221,   329,   370,   371,   372,   467,     3,     4,     5,    16,
      20,    25,    38,    39,    40,    41,    42,    43,    44,   342,
      45,    46,    47,    48,   196,   332,   333,   334,    49,    50,
     439,   440,   498,   499,    51,   145,   489,   490,   491,   265,
     266,   146,    28,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   509,   544,   545,   156,   157,   158,   159,   539,
     160,   161,   162,   163,   268,   345,   262,   165,   269,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      68,    15,   260,   434,   443,   263,   194,   272,    98,    78,
     192,   222,   375,    85,   229,   380,   540,    22,   504,    21,
     534,     1,   373,   376,    27,    52,   264,   546,   192,   323,
     324,    61,    62,    63,    64,   355,    66,   355,   319,   320,
     321,    52,  -309,  -309,   321,    72,    23,    73,    55,   202,
      17,   557,   193,   192,    19,   412,   478,   325,   326,   335,
     336,   101,    26,   217,   572,   273,   356,    53,   356,   272,
      57,    67,   430,   559,   432,   228,   537,   538,   197,   198,
      23,   235,    24,    54,    29,    58,   381,   374,    30,   481,
     245,    31,   377,   248,    32,    33,    65,    67,    26,   579,
      34,    60,    67,    35,    36,   267,   595,   272,   219,   223,
      29,   567,   230,   592,    30,    69,    71,    31,    74,   570,
      32,    33,   259,    75,    26,    76,    34,    80,    77,    35,
      36,   425,   426,   427,    81,   199,   203,    82,    83,    37,
     230,   523,    79,     6,   208,   215,    84,   195,   530,   327,
       7,     8,     9,    10,    11,    12,    13,    14,   101,   211,
     206,   367,   207,   246,   210,    37,   409,   213,   312,   313,
     314,   315,   316,   317,   318,   483,   212,   216,   351,   273,
     274,   275,   277,   330,   278,   192,   337,   338,   259,   339,
     369,   378,   340,   223,   319,   320,   321,   223,   223,   347,
     359,   442,   405,   406,   407,   408,   513,   382,   514,     6,
     379,   516,   353,   354,   357,   362,     7,     8,     9,    10,
      11,    12,    13,    14,   366,   380,   -47,   575,   368,   272,
     433,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   413,   383,   435,   437,   436,   438,   441,   445,   448,
     449,   454,   -48,   477,   456,   428,     6,   458,   472,   223,
     319,   320,   321,     7,     8,     9,    10,    11,    12,    13,
      14,   466,   486,   488,   460,   463,   484,   493,   494,   497,
     500,   508,   517,   518,   519,   521,   524,   480,   526,   527,
     529,   531,   532,   533,   536,    97,   554,   541,   555,   548,
     223,   223,   223,   223,   223,   549,   550,   556,   558,   574,
     563,   578,   577,   452,   220,   565,   582,   583,   464,   201,
     586,   584,   594,   468,    18,    56,    70,   495,   561,   473,
     223,   276,   571,   470,   209,     0,     0,     0,   522,   223,
     474,   444,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   223,
     272,     0,     0,     0,     0,     0,     0,     0,     0,   475,
     476,     0,   553,   223,     0,     0,     0,     0,   319,   320,
     321,     0,     0,     0,     0,   562,     0,   492,   164,     0,
       0,   496,     0,     0,     0,     0,     0,     0,   501,   502,
     503,     0,   547,   507,     0,     0,     0,     0,   205,   551,
       0,     0,     0,     0,     0,   230,     0,     0,   214,     0,
       0,     0,     0,     0,     0,   218,     0,     0,     0,     0,
       0,   227,     0,   231,   232,   233,   234,     0,     0,   236,
     237,   238,   239,   240,   241,   243,   244,   492,     0,   247,
     535,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,     0,     0,   271,   520,     0,   223,     0,     0,   164,
       0,     0,     0,     0,     0,     0,     0,     0,   492,     0,
       0,     0,     0,     0,   560,     0,   492,     0,     0,   564,
       0,   566,     0,     0,     0,     0,   569,     0,     0,     0,
     223,     0,     0,     0,     0,     0,     0,   223,     0,     0,
     223,     0,     0,     0,     0,     0,   580,     0,     0,     0,
       0,     0,     0,   223,     0,     0,     0,   343,   344,   346,
     587,   348,     0,     0,   349,   590,   591,     0,     0,     0,
     492,     0,   593,     0,   223,     0,     0,   596,     0,     0,
     360,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   363,     0,     0,     0,   365,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     384,   385,   386,   387,   388,   389,   390,   391,   392,   393,
     394,   395,   396,   397,   398,   399,   400,   401,   402,   403,
     404,     0,     0,     0,     0,     0,   410,   411,     0,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
       0,     0,     0,     0,   429,     0,   431,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   453,   455,   457,     0,     0,     0,     0,
       0,   264,   459,     0,     0,   462,     0,    85,     0,   465,
       0,     0,     0,    86,   471,    26,     0,     0,    88,    89,
       0,   471,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,   101,   102,   103,     0,
     105,     0,     7,     8,     9,    10,    11,    12,    13,    14,
     106,   107,     0,     0,     0,     0,     0,   108,     0,   109,
       0,     0,     0,     0,     0,     0,     0,   482,   116,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   346,
     506,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   120,   121,     0,     0,     0,
       0,     0,     0,     0,     0,   122,   123,   124,   125,   126,
     525,     0,     0,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,     0,     0,   140,   141,
     204,  -176,     0,     0,     0,     0,   542,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   343,
     552,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   346,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   576,     0,     0,     0,
       0,    85,     0,     0,     0,     0,   581,    86,     0,    26,
      87,     0,    88,    89,     0,   585,    90,    91,     0,   588,
      92,    93,    94,    95,    96,    97,    98,    99,   100,     6,
     101,   102,   103,   104,   105,     0,     7,     8,     9,    10,
      11,    12,    13,    14,   106,   107,     0,     0,     0,     0,
       0,   108,     0,   109,     0,     0,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   120,
     121,     0,     0,     0,     0,     0,     0,     0,     0,   122,
     123,   124,   125,   126,     0,     0,     0,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
       0,     0,   140,   141,   142,    85,   143,  -112,     0,     0,
       0,    86,     0,    26,    87,     0,    88,    89,     0,     0,
      90,    91,     0,     0,    92,    93,    94,    95,    96,    97,
      98,    99,   100,     6,   101,   102,   103,   104,   105,     0,
       7,     8,     9,    10,    11,    12,    13,    14,   106,   107,
       0,     0,     0,     0,     0,   108,     0,   109,     0,     0,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   120,   121,     0,     0,     0,     0,     0,
       0,     0,     0,   122,   123,   124,   125,   126,     0,     0,
       0,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,     0,     0,   140,   141,   142,    85,
     143,   270,     0,     0,     0,    86,     0,    26,    87,     0,
      88,    89,     0,     0,    90,    91,     0,     0,    92,    93,
      94,    95,    96,    97,    98,    99,   100,     6,   101,   102,
     103,   104,   105,     0,     7,     8,     9,    10,    11,    12,
      13,    14,   106,   107,     0,     0,     0,     0,     0,   108,
       0,   109,     0,     0,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   120,   121,     0,
       0,     0,     0,     0,     0,     0,     0,   122,   123,   124,
     125,   126,     0,     0,     0,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,     0,     0,
     140,   141,   142,  -108,   143,  -113,    85,     0,     0,     0,
       0,     0,    86,     0,    26,     0,     0,    88,    89,     0,
       0,   469,    91,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,   101,   102,   103,     0,   105,
       0,     7,     8,     9,    10,    11,    12,    13,    14,   106,
     107,    85,     0,     0,     0,     0,   108,    86,   109,    26,
       0,     0,    88,    89,     0,     0,     0,   116,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
     101,   102,   103,     0,   105,     0,     7,     8,     9,    10,
      11,    12,    13,    14,   106,   107,     0,     0,     0,     0,
       0,   108,     0,   109,   120,   121,     0,     0,     0,     0,
       0,     0,   116,     0,   122,   123,   124,   125,   126,     0,
       0,     0,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,     0,     0,   140,   141,   204,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   120,
     121,     0,     0,     0,     0,     0,     0,     0,     0,   122,
     123,   124,   125,   126,     0,     0,     0,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
       0,     0,   140,   141,   204,  -108,     0,   270,    85,     0,
       0,     0,     0,     0,    86,     0,    26,     0,     0,    88,
      89,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,   101,   102,   103,
       0,   105,     0,     7,     8,     9,    10,    11,    12,    13,
      14,   106,   107,    85,     0,     0,     0,     0,   108,    86,
     109,    26,     0,     0,    88,    89,     0,     0,     0,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,   101,   102,   103,     0,   105,     0,     7,     8,
       9,    10,    11,    12,    13,    14,   106,   107,     0,     0,
       0,     0,     0,   108,     0,   109,   120,   121,     0,     0,
       0,     0,     0,     0,   116,     0,   122,   123,   124,   125,
     126,     0,     0,     0,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,     0,     0,   140,
     141,   204,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   120,   121,     0,     0,     0,     0,     0,     0,     0,
       0,   122,   123,   124,   125,   126,     0,     0,     0,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,     0,    85,   140,   141,   204,     0,   226,    86,
       0,    26,     0,     0,    88,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,   101,   102,   103,     0,   105,     0,     7,     8,
       9,    10,    11,    12,    13,    14,   106,   107,    85,     0,
       0,     0,     0,   108,    86,   109,    26,     0,     0,    88,
      89,     0,     0,     0,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,   101,   102,   103,
       0,   105,     0,     7,     8,     9,    10,    11,    12,    13,
      14,   106,   107,     0,     0,     0,     0,     0,   108,     0,
     109,   120,   121,     0,     0,     0,     0,     0,     0,   116,
       0,   122,   123,   124,   125,   126,     0,     0,     0,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,     0,     0,   140,   141,   204,     0,  -136,     0,
       0,     0,     0,     0,     0,     0,   120,   121,     0,     0,
       0,     0,     0,     0,     0,     0,   122,   123,   124,   125,
     126,     0,     0,     0,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,     0,    85,   140,
     141,   204,     0,  -308,    86,     0,    26,     0,     0,    88,
      89,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,   101,   102,   103,
       0,   105,     0,     7,     8,     9,    10,    11,    12,    13,
      14,   106,   107,    85,     0,     0,     0,     0,   108,    86,
     109,    26,     0,     0,    88,    89,     0,     0,     0,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,   101,   102,   103,     0,   105,     0,     7,     8,
       9,    10,    11,    12,    13,    14,   106,   107,     0,     0,
       0,     0,     0,   108,     0,   109,   120,   121,     0,     0,
       0,     0,     0,     0,   116,     0,   122,   123,   124,   125,
     126,     0,     0,     0,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,     0,     0,   140,
     141,   204,     0,  -178,     0,     0,     0,     0,     0,     0,
       0,   120,   121,     0,     0,     0,     0,     0,     0,     0,
       0,   122,   123,   124,   125,   126,     0,     0,     0,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,     0,    85,   140,   141,   204,     0,  -138,    86,
       0,    26,     0,     0,    88,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,   101,   102,   103,     0,   105,     0,     7,     8,
       9,    10,    11,    12,    13,    14,   106,   107,    85,     0,
       0,     0,     0,   108,    86,   109,    26,     0,     0,    88,
      89,     0,     0,     0,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,   101,   102,   103,
       0,   105,     0,     7,     8,     9,    10,    11,    12,    13,
      14,   106,   107,     0,     0,     0,     0,     0,   108,     0,
     109,   120,   121,     0,     0,     0,     0,     0,     0,   116,
       0,   122,   123,   124,   125,   126,     0,     0,     0,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,     0,     0,   140,   141,   204,   454,     0,     0,
       0,     0,     0,     0,     0,     0,   120,   121,     0,     0,
       0,     0,     0,     0,     0,     0,   122,   123,   124,   125,
     126,     0,     0,     0,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,    85,     0,   140,
     141,   204,   456,    86,   259,    26,     0,     0,    88,    89,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,   101,   102,   103,     0,
     105,     0,     7,     8,     9,    10,    11,    12,    13,    14,
     106,   107,     0,     0,     0,     0,     0,   108,     0,   109,
       0,     0,     0,     0,     0,     0,     0,     0,   116,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,     0,     0,     0,     0,   120,   121,     0,     0,     0,
       0,     0,     0,     0,     0,   122,   123,   124,   125,   126,
     319,   320,   321,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,    85,  -176,   140,   141,
     204,     0,    86,   259,    26,     0,     0,    88,    89,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,   101,   102,   103,     0,   105,
       0,     7,     8,     9,    10,    11,    12,    13,    14,   106,
     107,    85,     0,     0,   341,     0,   108,    86,   109,    26,
       0,     0,    88,    89,     0,     0,     0,   116,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
     101,   102,   103,     0,   105,     0,     7,     8,     9,    10,
      11,    12,    13,    14,   106,   107,     0,     0,     0,     0,
       0,   108,     0,   109,   120,   121,     0,     0,     0,     0,
       0,     0,   116,     0,   122,   123,   124,   125,   126,     0,
       0,     0,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,     0,     0,   140,   141,   204,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   120,
     121,     0,     0,     0,     0,     0,     0,     0,     0,   122,
     123,   124,   125,   126,     0,     0,     0,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
      85,     0,   140,   141,   204,     0,    86,     0,    26,     0,
       0,    88,    89,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     6,   101,
     102,   103,     0,   105,     0,     7,     8,     9,    10,    11,
      12,    13,    14,   106,   107,    85,     0,     0,     0,     0,
     108,    86,   109,    26,     0,     0,    88,    89,     0,     0,
       0,   116,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,   101,   102,   103,     0,   105,     0,
       7,     8,     9,    10,    11,    12,    13,    14,   106,   107,
       0,     0,     0,     0,     0,   108,     0,   109,   120,   121,
       0,     0,     0,     0,     0,     0,   116,     0,   122,   123,
     124,   125,   126,     0,     0,     0,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,     0,
    -176,   140,   141,   204,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   120,   121,     0,     0,     0,     0,     0,
       0,     0,     0,   122,   123,   124,   125,   126,     0,     0,
       0,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,    85,  -178,   140,   141,   204,     0,
      86,     0,    26,     0,     0,    88,    89,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     6,   101,   102,   103,     0,   105,     0,     7,
       8,     9,    10,    11,    12,    13,    14,   106,   107,    85,
       0,     0,     0,     0,   108,    86,   109,    26,     0,     0,
      88,    89,     0,     0,     0,   116,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6,   101,   102,
     103,     0,   105,     0,     7,     8,     9,    10,    11,    12,
      13,    14,   106,   107,     0,     0,     0,     0,     0,   108,
       0,   109,   120,   121,     0,     0,     0,     0,     0,     0,
     116,     0,   122,   123,   124,   125,   126,     0,     0,     0,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,     0,     0,   140,   141,   204,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   120,   121,     0,
       0,     0,     0,     0,     0,     0,     0,   122,   123,   124,
     125,   126,     0,     0,     0,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,    85,     0,
     140,   141,   242,     0,    86,     0,    26,     0,     0,    88,
      89,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,   101,   102,   103,
       0,   105,     0,     7,     8,     9,    10,    11,    12,    13,
      14,   106,   107,    85,     0,     0,     0,     0,   108,    86,
     109,    26,     0,     0,    88,    89,     0,     0,     0,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,   101,   102,   103,     0,   105,     0,     7,     8,
       9,    10,    11,    12,    13,    14,   106,   107,     0,     0,
       0,     0,     0,   108,     0,   109,   120,   121,     0,     0,
       0,     0,     0,     0,   116,     0,   122,   123,   124,   125,
     126,     0,     0,     0,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,     0,     0,   140,
     141,   364,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   120,   121,     0,     0,     0,     0,     0,     0,     0,
       0,   122,   123,   124,   125,   126,     0,     0,     0,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,     0,     0,   140,   141,   505,   279,   280,   281,
       0,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   319,   320,   321,
       0,     0,     0,   279,   280,   281,   461,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   319,   320,   321,     0,     0,     0,   279,
     280,   281,   515,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   319,
     320,   321,     0,     0,     0,   279,   280,   281,   568,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   319,   320,   321,     0,     0,
     279,   280,   281,   322,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     319,   320,   321,     0,     0,   279,   280,   281,   358,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   319,   320,   321,     0,   279,
     280,   281,   485,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   319,
     320,   321,     0,   279,   280,   281,   487,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   319,   320,   321,     0,   279,   280,   281,
     511,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   319,   320,   321,
       0,   279,   280,   281,   512,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   319,   320,   321,     0,     0,     0,   352,   528,   279,
     280,   281,     0,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   319,
     320,   321,   361,     0,   279,   280,   281,     0,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   319,   320,   321,   510,     0,   279,
     280,   281,     0,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   319,
     320,   321,   279,   280,   281,     0,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   319,   320,   321,   446,   279,   280,   281,     0,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   319,   320,   321,   447,
     279,   280,   281,     0,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     319,   320,   321,   450,   279,   280,   281,     0,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   319,   320,   321,   451,   279,   280,
     281,     0,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   319,   320,
     321,   543,   279,   280,   281,     0,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   319,   320,   321,   573,   279,   280,   281,     0,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   319,   320,   321,   589,
     279,   280,   281,   350,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     319,   320,   321,   279,   280,   281,   479,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   319,   320,   321,   279,   280,   281,     0,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   319,   320,   321,   281,
       0,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   319,   320,   321,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   319,   320,   321,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     319,   320,   321,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   319,   320,   321,  -309,  -309,  -309,  -309,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   319,   320,   321
};

static const yytype_int16 yycheck[] =
{
      37,     1,   140,   330,   340,   140,    72,   142,    35,    12,
      38,   109,   264,    10,   112,    75,   503,    80,   448,    19,
     493,     3,    75,    75,    22,    23,     4,   508,    38,   142,
     143,    31,    32,    33,    34,   111,    36,   111,   137,   138,
     139,    39,   137,   138,   139,     7,   143,     9,   145,    85,
       0,   524,    80,    38,    63,    40,   383,   142,   143,   197,
     198,    39,    18,   100,   545,   139,   142,    55,   142,   204,
      18,   143,   324,   145,   326,   111,    27,    28,    76,    77,
     143,   117,   145,    55,     4,    38,   146,   140,     8,   425,
     126,    11,   144,   129,    14,    15,    40,   143,    18,   145,
      20,    39,   143,    23,    24,   141,   593,   242,   108,   109,
       4,   541,   112,   586,     8,   146,   145,    11,    55,   146,
      14,    15,    17,    55,    18,    80,    20,    12,    80,    23,
      24,   141,   142,   143,   145,    38,    38,   145,   145,    59,
     140,   477,   145,    38,   141,    80,   145,   143,   484,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    39,   145,
     141,   259,   141,   120,   141,    59,   304,   141,   111,   112,
     113,   114,   115,   116,   117,   427,   145,   145,   215,   139,
       7,   146,   145,    80,   145,    38,   145,   145,    17,    80,
      61,    80,   141,   193,   137,   138,   139,   197,   198,   141,
     139,   339,   300,   301,   302,   303,   458,   273,   460,    38,
     144,   463,   142,   142,   142,   139,    45,    46,    47,    48,
      49,    50,    51,    52,   139,    75,   146,   554,   140,   364,
     141,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   307,    80,    77,    75,   146,     5,   145,   140,   145,
     120,   144,   146,   141,   144,   321,    38,   143,    80,   259,
     137,   138,   139,    45,    46,    47,    48,    49,    50,    51,
      52,   369,   146,   146,   143,   143,   141,   141,    40,     6,
     140,   143,    84,   141,    75,     7,   141,   425,   140,   140,
     146,   140,    75,    80,    28,    34,    80,   145,    77,   146,
     300,   301,   302,   303,   304,   146,   146,   140,   140,    77,
     140,    77,   140,   350,   108,   141,   140,   140,   367,    80,
     141,   146,   140,   371,     4,    27,    39,   437,   532,   376,
     330,   148,   544,   373,    92,    -1,    -1,    -1,   476,   339,
     376,   341,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   369,
     505,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   377,
     378,    -1,   520,   383,    -1,    -1,    -1,    -1,   137,   138,
     139,    -1,    -1,    -1,    -1,   533,    -1,   433,    67,    -1,
      -1,   438,    -1,    -1,    -1,    -1,    -1,    -1,   445,   446,
     447,    -1,   510,   450,    -1,    -1,    -1,    -1,    87,   517,
      -1,    -1,    -1,    -1,    -1,   425,    -1,    -1,    97,    -1,
      -1,    -1,    -1,    -1,    -1,   104,    -1,    -1,    -1,    -1,
      -1,   110,    -1,   112,   113,   114,   115,    -1,    -1,   118,
     119,   120,   121,   122,   123,   124,   125,   493,    -1,   128,
     497,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,    -1,    -1,   142,   472,    -1,   476,    -1,    -1,   148,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   524,    -1,
      -1,    -1,    -1,    -1,   531,    -1,   532,    -1,    -1,   536,
      -1,   538,    -1,    -1,    -1,    -1,   543,    -1,    -1,    -1,
     510,    -1,    -1,    -1,    -1,    -1,    -1,   517,    -1,    -1,
     520,    -1,    -1,    -1,    -1,    -1,   563,    -1,    -1,    -1,
      -1,    -1,    -1,   533,    -1,    -1,    -1,   206,   207,   208,
     577,   210,    -1,    -1,   213,   582,   583,    -1,    -1,    -1,
     586,    -1,   589,    -1,   554,    -1,    -1,   594,    -1,    -1,
     229,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   242,    -1,    -1,    -1,   246,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,    -1,    -1,    -1,    -1,    -1,   305,   306,    -1,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
      -1,    -1,    -1,    -1,   323,    -1,   325,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   352,   353,   354,    -1,    -1,    -1,    -1,
      -1,     4,   361,    -1,    -1,   364,    -1,    10,    -1,   368,
      -1,    -1,    -1,    16,   373,    18,    -1,    -1,    21,    22,
      -1,   380,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,
      43,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    -1,    -1,    -1,    -1,    -1,    60,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   426,    71,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   448,
     449,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   108,   109,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   118,   119,   120,   121,   122,
     479,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,    -1,    -1,   141,   142,
     143,   144,    -1,    -1,    -1,    -1,   505,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   518,
     519,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   541,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   555,    -1,    -1,    -1,
      -1,    10,    -1,    -1,    -1,    -1,   565,    16,    -1,    18,
      19,    -1,    21,    22,    -1,   574,    25,    26,    -1,   578,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    -1,    -1,    -1,    -1,
      -1,    60,    -1,    62,    -1,    -1,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,
     119,   120,   121,   122,    -1,    -1,    -1,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
      -1,    -1,   141,   142,   143,    10,   145,   146,    -1,    -1,
      -1,    16,    -1,    18,    19,    -1,    21,    22,    -1,    -1,
      25,    26,    -1,    -1,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      -1,    -1,    -1,    -1,    -1,    60,    -1,    62,    -1,    -1,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   108,   109,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   118,   119,   120,   121,   122,    -1,    -1,
      -1,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,    -1,    -1,   141,   142,   143,    10,
     145,   146,    -1,    -1,    -1,    16,    -1,    18,    19,    -1,
      21,    22,    -1,    -1,    25,    26,    -1,    -1,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,    60,
      -1,    62,    -1,    -1,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,   109,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,   119,   120,
     121,   122,    -1,    -1,    -1,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,    -1,    -1,
     141,   142,   143,     7,   145,   146,    10,    -1,    -1,    -1,
      -1,    -1,    16,    -1,    18,    -1,    -1,    21,    22,    -1,
      -1,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    10,    -1,    -1,    -1,    -1,    60,    16,    62,    18,
      -1,    -1,    21,    22,    -1,    -1,    -1,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    -1,    43,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    -1,    -1,    -1,    -1,
      -1,    60,    -1,    62,   108,   109,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    -1,   118,   119,   120,   121,   122,    -1,
      -1,    -1,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,    -1,    -1,   141,   142,   143,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,
     119,   120,   121,   122,    -1,    -1,    -1,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
      -1,    -1,   141,   142,   143,     7,    -1,   146,    10,    -1,
      -1,    -1,    -1,    -1,    16,    -1,    18,    -1,    -1,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      -1,    43,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    10,    -1,    -1,    -1,    -1,    60,    16,
      62,    18,    -1,    -1,    21,    22,    -1,    -1,    -1,    71,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    41,    -1,    43,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    -1,    -1,
      -1,    -1,    -1,    60,    -1,    62,   108,   109,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    -1,   118,   119,   120,   121,
     122,    -1,    -1,    -1,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,    -1,    -1,   141,
     142,   143,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   118,   119,   120,   121,   122,    -1,    -1,    -1,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,    -1,    10,   141,   142,   143,    -1,   145,    16,
      -1,    18,    -1,    -1,    21,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    41,    -1,    43,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    10,    -1,
      -1,    -1,    -1,    60,    16,    62,    18,    -1,    -1,    21,
      22,    -1,    -1,    -1,    71,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      -1,    43,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    -1,    -1,    -1,    -1,    -1,    60,    -1,
      62,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      -1,   118,   119,   120,   121,   122,    -1,    -1,    -1,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,    -1,    -1,   141,   142,   143,    -1,   145,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,   109,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   118,   119,   120,   121,
     122,    -1,    -1,    -1,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,    -1,    10,   141,
     142,   143,    -1,   145,    16,    -1,    18,    -1,    -1,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      -1,    43,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    10,    -1,    -1,    -1,    -1,    60,    16,
      62,    18,    -1,    -1,    21,    22,    -1,    -1,    -1,    71,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    41,    -1,    43,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    -1,    -1,
      -1,    -1,    -1,    60,    -1,    62,   108,   109,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    -1,   118,   119,   120,   121,
     122,    -1,    -1,    -1,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,    -1,    -1,   141,
     142,   143,    -1,   145,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   118,   119,   120,   121,   122,    -1,    -1,    -1,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,    -1,    10,   141,   142,   143,    -1,   145,    16,
      -1,    18,    -1,    -1,    21,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    41,    -1,    43,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    10,    -1,
      -1,    -1,    -1,    60,    16,    62,    18,    -1,    -1,    21,
      22,    -1,    -1,    -1,    71,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      -1,    43,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    -1,    -1,    -1,    -1,    -1,    60,    -1,
      62,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      -1,   118,   119,   120,   121,   122,    -1,    -1,    -1,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,    -1,    -1,   141,   142,   143,   144,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,   109,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   118,   119,   120,   121,
     122,    -1,    -1,    -1,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,    10,    -1,   141,
     142,   143,   144,    16,    17,    18,    -1,    -1,    21,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,
      43,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    -1,    -1,    -1,    -1,    -1,    60,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,    -1,    -1,    -1,    -1,   108,   109,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   118,   119,   120,   121,   122,
     137,   138,   139,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,    10,   140,   141,   142,
     143,    -1,    16,    17,    18,    -1,    -1,    21,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    10,    -1,    -1,    13,    -1,    60,    16,    62,    18,
      -1,    -1,    21,    22,    -1,    -1,    -1,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    -1,    43,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    -1,    -1,    -1,    -1,
      -1,    60,    -1,    62,   108,   109,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    -1,   118,   119,   120,   121,   122,    -1,
      -1,    -1,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,    -1,    -1,   141,   142,   143,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,
     119,   120,   121,   122,    -1,    -1,    -1,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
      10,    -1,   141,   142,   143,    -1,    16,    -1,    18,    -1,
      -1,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    -1,    43,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    10,    -1,    -1,    -1,    -1,
      60,    16,    62,    18,    -1,    -1,    21,    22,    -1,    -1,
      -1,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      -1,    -1,    -1,    -1,    -1,    60,    -1,    62,   108,   109,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,   118,   119,
     120,   121,   122,    -1,    -1,    -1,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,    -1,
     140,   141,   142,   143,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   108,   109,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   118,   119,   120,   121,   122,    -1,    -1,
      -1,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,    10,   140,   141,   142,   143,    -1,
      16,    -1,    18,    -1,    -1,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    41,    -1,    43,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    10,
      -1,    -1,    -1,    -1,    60,    16,    62,    18,    -1,    -1,
      21,    22,    -1,    -1,    -1,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,
      41,    -1,    43,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,    60,
      -1,    62,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    -1,   118,   119,   120,   121,   122,    -1,    -1,    -1,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,    -1,    -1,   141,   142,   143,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,   109,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,   119,   120,
     121,   122,    -1,    -1,    -1,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,    10,    -1,
     141,   142,   143,    -1,    16,    -1,    18,    -1,    -1,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      -1,    43,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    10,    -1,    -1,    -1,    -1,    60,    16,
      62,    18,    -1,    -1,    21,    22,    -1,    -1,    -1,    71,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    41,    -1,    43,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    -1,    -1,
      -1,    -1,    -1,    60,    -1,    62,   108,   109,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    -1,   118,   119,   120,   121,
     122,    -1,    -1,    -1,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,    -1,    -1,   141,
     142,   143,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   118,   119,   120,   121,   122,    -1,    -1,    -1,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,    -1,    -1,   141,   142,   143,    77,    78,    79,
      -1,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   137,   138,   139,
      -1,    -1,    -1,    77,    78,    79,   146,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   137,   138,   139,    -1,    -1,    -1,    77,
      78,    79,   146,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   137,
     138,   139,    -1,    -1,    -1,    77,    78,    79,   146,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   137,   138,   139,    -1,    -1,
      77,    78,    79,   145,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     137,   138,   139,    -1,    -1,    77,    78,    79,   145,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   137,   138,   139,    -1,    77,
      78,    79,   144,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   137,
     138,   139,    -1,    77,    78,    79,   144,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   137,   138,   139,    -1,    77,    78,    79,
     144,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   137,   138,   139,
      -1,    77,    78,    79,   144,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   137,   138,   139,    -1,    -1,    -1,    75,   144,    77,
      78,    79,    -1,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   137,
     138,   139,    75,    -1,    77,    78,    79,    -1,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   137,   138,   139,    75,    -1,    77,
      78,    79,    -1,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   137,
     138,   139,    77,    78,    79,    -1,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   137,   138,   139,   140,    77,    78,    79,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   137,   138,   139,   140,
      77,    78,    79,    -1,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     137,   138,   139,   140,    77,    78,    79,    -1,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   137,   138,   139,   140,    77,    78,
      79,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   137,   138,
     139,   140,    77,    78,    79,    -1,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   137,   138,   139,   140,    77,    78,    79,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   137,   138,   139,   140,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     137,   138,   139,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   137,   138,   139,    77,    78,    79,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   137,   138,   139,    79,
      -1,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   137,   138,   139,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   137,   138,   139,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     137,   138,   139,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   137,   138,   139,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   137,   138,   139
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,   148,   163,   164,   165,    38,    45,    46,    47,
      48,    49,    50,    51,    52,   154,   166,     0,   165,    63,
     167,   154,    80,   143,   145,   168,    18,   198,   199,     4,
       8,    11,    14,    15,    20,    23,    24,    59,   169,   170,
     171,   172,   173,   174,   175,   177,   178,   179,   180,   185,
     186,   191,   198,    55,    55,   145,   168,    18,    38,   149,
      39,   154,   154,   154,   154,    40,   154,   143,   217,   146,
     171,   145,     7,     9,    55,    55,    80,    80,    12,   145,
      12,   145,   145,   145,   145,    10,    16,    19,    21,    22,
      25,    26,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    39,    40,    41,    42,    43,    53,    54,    60,    62,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
     108,   109,   118,   119,   120,   121,   122,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     141,   142,   143,   145,   154,   192,   198,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   212,   213,   214,   215,
     217,   218,   219,   220,   223,   224,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,    38,    80,   150,   143,   181,   198,   198,    38,
     151,   151,   220,    38,   143,   223,   141,   141,   141,   219,
     141,   145,   145,   141,   223,    80,   145,   217,   223,   154,
     156,   157,   153,   154,   155,   156,   145,   223,   220,   153,
     154,   223,   223,   223,   223,   220,   223,   223,   223,   223,
     223,   223,   143,   223,   223,   220,   120,   223,   220,   223,
     223,   223,   223,   223,   223,   223,   223,   223,   223,    17,
     152,   153,   223,   225,     4,   196,   197,   220,   221,   225,
     146,   223,   225,   139,     7,   146,   202,   145,   145,    77,
      78,    79,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   137,
     138,   139,   145,   142,   143,   142,   143,    44,   152,   158,
      80,   150,   182,   183,   184,   152,   152,   145,   145,    80,
     141,    13,   176,   223,   223,   222,   223,   141,   223,   223,
      80,   217,    75,   142,   142,   111,   142,   142,   145,   139,
     223,    75,   139,   223,   143,   223,   139,   153,   140,    61,
     159,   160,   161,    75,   140,   149,    75,   144,    80,   144,
      75,   146,   150,    80,   223,   223,   223,   223,   223,   223,
     223,   223,   223,   223,   223,   223,   223,   223,   223,   223,
     223,   223,   223,   223,   223,   153,   153,   153,   153,   152,
     223,   223,    40,   150,   223,   223,   223,   223,   223,   223,
     223,   223,   223,   223,   223,   141,   142,   143,   150,   223,
     149,   223,   149,   141,   158,    77,   146,    75,     5,   187,
     188,   145,   152,   221,   154,   140,   140,   140,   145,   120,
     140,   140,   217,   223,   144,   223,   144,   223,   143,   223,
     143,   146,   223,   143,   159,   223,   153,   162,   161,    25,
     215,   223,    80,   197,   220,   198,   198,   141,   158,    80,
     152,   221,   223,   149,   141,   144,   146,   144,   146,   193,
     194,   195,   220,   141,    40,   184,   217,     6,   189,   190,
     140,   217,   217,   217,   222,   143,   223,   217,   143,   209,
      75,   144,   144,   149,   149,   146,   149,    84,   141,    75,
     198,     7,   152,   221,   141,   223,   140,   140,   144,   146,
     221,   140,    75,    80,   193,   217,    28,    27,    28,   216,
     216,   145,   223,   140,   210,   211,   212,   153,   146,   146,
     146,   153,   223,   152,    80,    77,   140,   193,   140,   145,
     217,   195,   152,   140,   217,   141,   217,   222,   146,   217,
     146,   213,   212,   140,    77,   158,   223,   140,    77,   145,
     217,   223,   140,   140,   146,   223,   141,   217,   223,   140,
     217,   217,   193,   217,   140,   216,   217
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   147,   148,   149,   150,   151,   152,   152,   153,   153,
     153,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     155,   156,   156,   157,   157,   158,   158,   159,   159,   160,
     160,   161,   162,   162,   163,   163,   164,   164,   165,   165,
     165,   165,   166,   166,   167,   167,   168,   169,   169,   170,
     170,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   172,   173,   174,   175,   175,   176,   177,   178,
     179,   180,   181,   182,   182,   183,   183,   183,   184,   184,
     185,   186,   187,   187,   188,   189,   189,   190,   191,   191,
     191,   191,   192,   192,   193,   193,   194,   194,   194,   195,
     195,   196,   196,   196,   197,   197,   197,   197,   198,   198,
     199,   199,   200,   200,   201,   201,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   203,   203,   203,   203,   203,
     204,   204,   204,   204,   204,   204,   204,   204,   204,   205,
     206,   206,   207,   208,   209,   209,   210,   210,   211,   211,
     212,   212,   213,   213,   214,   214,   215,   215,   216,   216,
     216,   217,   218,   219,   219,   220,   221,   221,   222,   222,
     223,   223,   223,   223,   223,   223,   223,   223,   223,   223,
     223,   223,   223,   223,   223,   223,   223,   223,   223,   223,
     223,   223,   223,   223,   223,   223,   223,   224,   224,   225,
     225,   225,   226,   226,   226,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   226,   226,   227,   227,   227,
     227,   228,   228,   229,   229,   230,   230,   230,   230,   230,
     230,   231,   231,   231,   231,   231,   231,   231,   231,   231,
     232,   233,   233,   233,   233,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   235,
     236,   236,   236,   237,   238,   238,   238,   238,   238,   239,
     239,   240,   240,   241,   241,   242,   242,   242,   243,   243,
     243,   244,   244,   244,   244,   244,   244,   244,   245,   245,
     245,   246,   246,   246,   247,   248,   249,   250,   250,   251
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     2,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     3,     3,     4,     4,     1,     1,     0,     1,     2,
       1,     2,     3,     1,     0,     1,     2,     1,     5,     7,
       5,     7,     0,     1,     0,     2,     3,     0,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     3,     3,     3,     5,     2,     5,     3,
       3,     3,     3,     0,     1,     3,     2,     1,     1,     3,
       6,     7,     0,     1,     2,     0,     1,     2,     9,     9,
       8,     8,     8,    11,     0,     1,     3,     2,     1,     3,
       5,     3,     2,     1,     5,     7,     4,     6,     0,     1,
       2,     1,     0,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       3,     2,     2,     2,     1,     2,     1,     3,     2,     4,
       1,     2,     2,     1,     1,     2,     2,     2,     1,     9,
       7,     9,     5,     5,     3,     4,     0,     1,     2,     1,
       4,     3,     3,     2,     5,     7,     6,     6,     0,     2,
       6,     3,     2,     4,     2,     1,     0,     1,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     3,     7,     3,
       2,     1,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     1,     2,     2,     2,     4,     3,
       5,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       5,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     3,     3,     3,     3,     3,     3,     4,
       5,     3,     3,     3,     3,     2,     2,     1,     3,     3,
       2,     5,     2,     6,     3,     6,     3,     5,     5,     4,
       4,     5,     4,     4,     6,     6,     6,     2,     1,     6
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
        case 7:
#line 95 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
    (yyval.opval) = SPVM_OP_build_mutable_type(compiler, (yyvsp[-1].opval));
  }
#line 2650 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 11:
#line 106 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[0].opval));
    }
#line 2658 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 12:
#line 110 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_byte_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2668 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 13:
#line 116 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_short_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2678 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 14:
#line 122 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2688 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 15:
#line 128 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_long_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2698 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 16:
#line 134 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_float_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2708 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 17:
#line 140 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_double_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2718 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 18:
#line 146 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_any_object_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = op_type;
    }
#line 2727 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 19:
#line 151 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_string_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2737 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 20:
#line 159 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[-1].opval));
    }
#line 2745 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 21:
#line 165 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-2].opval), NULL);
    }
#line 2753 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 22:
#line 169 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-2].opval), NULL);
    }
#line 2761 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 23:
#line 175 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 2769 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 24:
#line 179 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 2777 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 26:
#line 186 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_void_type(compiler, compiler->current_file, compiler->current_line);
    }
#line 2785 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 27:
#line 192 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
#line 2793 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 31:
#line 203 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 2801 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 32:
#line 209 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2819 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 33:
#line 223 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 2827 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 34:
#line 229 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 2835 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 35:
#line 233 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2850 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 36:
#line 246 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2868 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 38:
#line 263 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), NULL, (yyvsp[-2].opval));
    }
#line 2876 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 39:
#line 267 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[-4].opval));
    }
#line 2884 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 40:
#line 271 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), NULL, NULL, (yyvsp[-2].opval));
    }
#line 2892 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 41:
#line 275 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), NULL, (yyvsp[-2].opval), (yyvsp[-4].opval));
    }
#line 2900 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 42:
#line 281 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 2908 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 44:
#line 288 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 2916 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 45:
#line 292 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_extends(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 2924 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 46:
#line 298 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_class_block;
    }
#line 2934 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 47:
#line 306 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 2942 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 48:
#line 310 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[0].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
        SPVM_OP_insert_child(compiler, (yyval.opval), (yyval.opval)->last, (yyvsp[0].opval));
      }
    }
#line 2956 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 49:
#line 322 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2974 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 62:
#line 352 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    { 
      (yyval.opval) = SPVM_OP_build_init_statement(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 2982 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 63:
#line 358 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_version_decl(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2990 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 64:
#line 364 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_version_from(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2998 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 65:
#line 370 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      int32_t is_require = 0;
      SPVM_OP* op_name_class_alias = NULL;
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), op_name_class_alias, is_require);
    }
#line 3008 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 66:
#line 376 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      int32_t is_require = 0;
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), is_require);
    }
#line 3017 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 67:
#line 383 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, compiler->current_file, compiler->current_line);
      int32_t is_require = 1;
      (yyval.opval) = SPVM_OP_build_use(compiler, op_use, (yyvsp[0].opval), NULL, is_require);
    }
#line 3027 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 68:
#line 391 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_alias(compiler, op_use, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3036 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 69:
#line 398 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_allow(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3044 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 70:
#line 404 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_interface_statement(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3052 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 71:
#line 410 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), (yyvsp[-2].opval));
    }
#line 3060 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 72:
#line 416 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_enum_block;
    }
#line 3070 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 73:
#line 424 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3078 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 74:
#line 428 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3093 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 75:
#line 441 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3111 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 78:
#line 459 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_item(compiler, (yyvsp[0].opval), NULL);
    }
#line 3119 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 79:
#line 463 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_item(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3127 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 80:
#line 469 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class_var(compiler, (yyvsp[-5].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3135 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 81:
#line 475 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_field(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-2].opval));
    }
#line 3143 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 88:
#line 495 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-8].opval), (yyvsp[0].opval));
     }
#line 3151 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 89:
#line 499 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-8].opval), NULL);
     }
#line 3159 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 90:
#line 503 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-6].opval), NULL, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-7].opval), (yyvsp[0].opval));
     }
#line 3167 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 91:
#line 507 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-6].opval), NULL, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-7].opval), NULL);
     }
#line 3175 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 92:
#line 513 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-6].opval), NULL, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-7].opval), (yyvsp[0].opval));
     }
#line 3183 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 93:
#line 517 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       SPVM_OP* op_anon_method_fields;
       if ((yyvsp[-9].opval)->id == SPVM_OP_C_ID_LIST) {
         op_anon_method_fields = (yyvsp[-9].opval);
       }
       else {
         op_anon_method_fields = SPVM_OP_new_op_list(compiler, (yyvsp[-9].opval)->file, (yyvsp[-9].opval)->line);
         SPVM_OP_insert_child(compiler, op_anon_method_fields, op_anon_method_fields->last, (yyvsp[-9].opval));
       }
       
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-6].opval), NULL, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-7].opval), (yyvsp[0].opval));
       
       SPVM_OP_attach_anon_method_fields(compiler, (yyval.opval), op_anon_method_fields);
     }
#line 3202 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 94:
#line 534 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3210 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 95:
#line 538 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3225 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 96:
#line 551 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3243 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 99:
#line 569 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[-2].opval), (yyvsp[0].opval), NULL, NULL);
    }
#line 3251 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 100:
#line 573 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), NULL, (yyvsp[0].opval));
    }
#line 3259 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 101:
#line 579 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3277 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 104:
#line 597 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_anon_method_field(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 3285 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 105:
#line 601 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_anon_method_field(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3293 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 106:
#line 605 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_FIELD, (yyvsp[-3].opval)->file, (yyvsp[-3].opval)->line);
      
      (yyval.opval) = SPVM_OP_build_anon_method_field(compiler, op_field, NULL, (yyvsp[-1].opval), (yyvsp[0].opval), (yyvsp[-3].opval));
    }
#line 3303 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 107:
#line 611 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_FIELD, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      
      (yyval.opval) = SPVM_OP_build_anon_method_field(compiler, op_field, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3313 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 108:
#line 619 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3321 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 109:
#line 623 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3336 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 110:
#line 636 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3354 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 112:
#line 653 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3362 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 113:
#line 657 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3377 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 114:
#line 670 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3395 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 129:
#line 700 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[-1].opval), NULL);
    }
#line 3403 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 130:
#line 704 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3411 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 132:
#line 709 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_operator_statement(compiler, (yyvsp[-1].opval));
    }
#line 3419 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 134:
#line 714 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
#line 3427 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 135:
#line 720 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 3435 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 136:
#line 724 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[0].opval), NULL, NULL);
    }
#line 3443 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 137:
#line 728 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-2].opval), (yyvsp[0].opval), (yyvsp[-1].opval));
    }
#line 3451 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 138:
#line 732 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-1].opval), NULL, (yyvsp[0].opval));
    }
#line 3459 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 139:
#line 736 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-3].opval), (yyvsp[0].opval), (yyvsp[-2].opval));
    }
#line 3467 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 141:
#line 743 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_print(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3475 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 142:
#line 747 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_print(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3483 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 145:
#line 753 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_make_read_only(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3491 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 146:
#line 757 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enable_options(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3499 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 147:
#line 761 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_disable_options(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3507 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 149:
#line 768 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[-8].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3515 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 150:
#line 774 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_foreach_statement(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3523 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 151:
#line 778 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_foreach_statement(compiler, (yyvsp[-8].opval), (yyvsp[-7].opval), (yyvsp[-3].opval), (yyvsp[0].opval));
    }
#line 3531 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 152:
#line 784 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3539 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 153:
#line 790 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3547 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 154:
#line 796 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[-1].opval), NULL);
    }
#line 3556 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 155:
#line 801 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3565 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 156:
#line 808 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3573 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 157:
#line 812 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3588 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 158:
#line 825 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3606 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 159:
#line 839 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 3614 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 160:
#line 845 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3622 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 161:
#line 849 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), NULL);
    }
#line 3630 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 162:
#line 855 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3638 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 163:
#line 859 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[-1].opval), NULL);
    }
#line 3646 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 164:
#line 865 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->current_file, compiler->current_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[-2].opval), (yyvsp[0].opval), NULL);
    }
#line 3656 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 165:
#line 871 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->current_file, compiler->current_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3666 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 166:
#line 878 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval), 0);
      
      // condition part has own scope
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    }
#line 3680 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 167:
#line 888 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      op_if = SPVM_OP_build_if_statement(compiler, op_if, (yyvsp[-3].opval), (yyvsp[0].opval), (yyvsp[-1].opval), 0);
      
      // condition part has own scope
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    }
#line 3695 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 168:
#line 901 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
#line 3703 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 169:
#line 905 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 3711 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 170:
#line 909 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, op_if, (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval), 0);
    }
#line 3720 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 171:
#line 916 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_block;
    }
#line 3730 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 172:
#line 924 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3738 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 173:
#line 930 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var_decl(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval), NULL);
    }
#line 3746 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 174:
#line 934 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var_decl(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL, NULL);
    }
#line 3754 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 175:
#line 940 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[0].opval));
    }
#line 3762 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 176:
#line 946 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3770 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 177:
#line 950 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3785 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 178:
#line 963 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
#line 3793 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 189:
#line 979 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_true(compiler, (yyvsp[0].opval));
    }
#line 3801 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 190:
#line 983 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_false(compiler, (yyvsp[0].opval));
    }
#line 3809 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 199:
#line 995 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_basic_type_id(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3817 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1008 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3837 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1024 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_operator = (yyvsp[-5].opval)->first;
      SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, compiler->current_file, compiler->current_line);
      
      SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, (yyvsp[-5].opval));
      SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, (yyvsp[-3].opval));
      SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, (yyvsp[-1].opval));
      
      (yyval.opval) = op_sequence;
    }
#line 3852 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1037 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3870 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1051 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[-1].opval);
    }
#line 3878 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1055 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 3886 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1061 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, operator, (yyvsp[0].opval));
    }
#line 3895 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1066 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MINUS, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, op_negate, (yyvsp[0].opval));
    }
#line 3904 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1071 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3912 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1075 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3920 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1079 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3928 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1083 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3936 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1087 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3944 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1091 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op_var(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3952 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1095 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op_var(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3960 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1099 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3968 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1103 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3976 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1107 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3984 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1112 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3992 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1116 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4000 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1122 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[0].opval));
    }
#line 4009 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1127 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[-1].opval));
    }
#line 4018 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1132 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[0].opval));
    }
#line 4027 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1137 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[-1].opval));
    }
#line 4036 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1144 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, operator, (yyvsp[0].opval));
    }
#line 4045 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1149 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, operator, (yyvsp[-1].opval));
    }
#line 4054 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1156 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, operator, (yyvsp[0].opval));
    }
#line 4063 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1161 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, operator, (yyvsp[-1].opval));
    }
#line 4072 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1176 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, operator, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4081 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1181 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, operator, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4090 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1186 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MULTIPLY, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, operator, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4099 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1191 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4107 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1195 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4115 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1199 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4123 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1203 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4131 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1207 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4139 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1211 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4147 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1217 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* ternary_op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TERNARY_OP, (yyvsp[-4].opval)->file, (yyvsp[-4].opval)->line);
      (yyval.opval) = SPVM_OP_build_ternary_op(compiler, ternary_op, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4156 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1224 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4164 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1228 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4172 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1232 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4180 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1236 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4188 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1242 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4196 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1246 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4204 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1250 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4212 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1254 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4220 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1258 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4228 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1262 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4236 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1266 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4244 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1270 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4252 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1274 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4260 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1278 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4268 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1282 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4276 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1286 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4284 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1290 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4292 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1294 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4300 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1300 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4308 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1306 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_logical_or(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4316 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1310 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_logical_and(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4324 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1314 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_logical_not(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4332 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1320 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_defined_or(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4340 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1326 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_type_check(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4348 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 275:
#line 1330 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_type_check(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4356 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1334 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_type_check(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4364 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1338 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_type_check(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4372 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1342 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_type_check(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4380 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1348 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type_cast = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      (yyval.opval) = SPVM_OP_build_type_cast(compiler, op_type_cast, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4389 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 280:
#line 1353 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type_cast = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_type_cast(compiler, op_type_cast, (yyvsp[-1].opval), (yyvsp[-4].opval));
    }
#line 4398 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1360 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_can(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4406 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1364 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_can(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4414 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1370 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4422 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 284:
#line 1374 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_special_assign(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4430 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1380 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 4438 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1384 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_length = (yyvsp[0].opval)->last;
      SPVM_OP_cut_op(compiler, (yyvsp[0].opval)->last);
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), op_length);
    }
#line 4448 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 287:
#line 1390 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_anon_method(compiler, (yyvsp[0].opval));
    }
#line 4456 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1396 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->current_file, compiler->current_line);
      int32_t is_key_values = 0;
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[-1].opval), is_key_values);
    }
#line 4466 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 289:
#line 1402 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->current_file, compiler->current_line);
      int32_t is_key_values = 1;
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[-1].opval), is_key_values);
    }
#line 4476 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1408 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->current_file, compiler->current_line);
      int32_t is_key_values = 1;
      SPVM_OP* op_list_elements = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, op_list_elements, is_key_values);
    }
#line 4487 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 291:
#line 1417 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4496 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 292:
#line 1422 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, (yyvsp[-1].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-1].opval), (yyvsp[0].opval), op_operators);
    }
#line 4506 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1428 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4515 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 294:
#line 1433 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-2].opval), (yyvsp[0].opval), op_operators);
    }
#line 4525 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 295:
#line 1439 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4534 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 296:
#line 1444 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-2].opval), (yyvsp[0].opval), op_operators);
    }
#line 4544 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 297:
#line 1450 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_method_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[-3].opval)->file, (yyvsp[-3].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-4].opval), op_method_name, (yyvsp[-1].opval));
    }
#line 4554 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 298:
#line 1458 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ELEMENT_ACCESS, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_element_access(compiler, op_array_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 4563 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 299:
#line 1463 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ELEMENT_ACCESS, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_element_access(compiler, op_array_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4572 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 300:
#line 1468 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ELEMENT_ACCESS, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_element_access(compiler, op_array_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4581 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 301:
#line 1475 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 4590 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 302:
#line 1480 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4599 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 303:
#line 1485 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_access = (yyvsp[-3].opval);
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_field_access(compiler, op_field_access, op_array_access, (yyvsp[-1].opval));
    }
#line 4609 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 304:
#line 1493 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 4619 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 305:
#line 1501 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_unweaken_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 4629 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 306:
#line 1509 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_isweak_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 4639 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 307:
#line 1517 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_warn(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4647 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 308:
#line 1521 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_warn(compiler, (yyvsp[0].opval), NULL);
    }
#line 4655 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 309:
#line 1527 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_copy_fields(compiler, (yyvsp[-5].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4663 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;


#line 4667 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
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
#line 1531 "yacc/spvm_yacc.y" /* yacc.c:1906  */

