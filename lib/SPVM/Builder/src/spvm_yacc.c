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
    EXISTS = 298,
    DELETE = 299,
    UNDEF = 300,
    VOID = 301,
    BYTE = 302,
    SHORT = 303,
    INT = 304,
    LONG = 305,
    FLOAT = 306,
    DOUBLE = 307,
    STRING = 308,
    OBJECT = 309,
    ELEMENT = 310,
    TRUE = 311,
    FALSE = 312,
    END_OF_FILE = 313,
    RW = 314,
    RO = 315,
    WO = 316,
    INIT = 317,
    NEW = 318,
    OF = 319,
    BASIC_TYPE_ID = 320,
    EXTENDS = 321,
    SUPER = 322,
    RETURN = 323,
    WEAKEN = 324,
    DIE = 325,
    WARN = 326,
    PRINT = 327,
    SAY = 328,
    OUTMOST_CLASS_NAME = 329,
    UNWEAKEN = 330,
    ENABLE_OPTIONS = 331,
    DISABLE_OPTIONS = 332,
    FATCAMMA = 333,
    ASSIGN = 334,
    SPECIAL_ASSIGN = 335,
    LOGICAL_OR = 336,
    DEFINED_OR = 337,
    LOGICAL_AND = 338,
    BIT_OR = 339,
    BIT_XOR = 340,
    BIT_AND = 341,
    NUMEQ = 342,
    NUMNE = 343,
    STREQ = 344,
    STRNE = 345,
    NUMGT = 346,
    NUMGE = 347,
    NUMLT = 348,
    NUMLE = 349,
    STRGT = 350,
    STRGE = 351,
    STRLT = 352,
    STRLE = 353,
    ISA = 354,
    ISA_ERROR = 355,
    IS_TYPE = 356,
    IS_ERROR = 357,
    IS_COMPILE_TYPE = 358,
    NUMERIC_CMP = 359,
    STRING_CMP = 360,
    CAN = 361,
    SHIFT = 362,
    DIVIDE = 363,
    DIVIDE_UNSIGNED_INT = 364,
    DIVIDE_UNSIGNED_LONG = 365,
    MODULO = 366,
    MODULO_UNSIGNED_INT = 367,
    MODULO_UNSIGNED_LONG = 368,
    LOGICAL_NOT = 369,
    BIT_NOT = 370,
    REFERENCE = 371,
    DEREFERENCE = 372,
    PLUS = 373,
    MINUS = 374,
    CONVERT = 375,
    SCALAR = 376,
    STRING_LENGTH = 377,
    ISWEAK = 378,
    TYPE_NAME = 379,
    COMPILE_TYPE_NAME = 380,
    DUMP = 381,
    NEW_STRING_LEN = 382,
    IS_READ_ONLY = 383,
    COPY = 384,
    ADDRESS = 385,
    IS_OPTIONS = 386,
    INC = 387,
    DEC = 388,
    ARROW = 389
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_LIB_SPVM_BUILDER_INCLUDE_SPVM_YACC_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 268 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:358  */

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
#define YYLAST   5512

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  150
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  107
/* YYNRULES -- Number of rules.  */
#define YYNRULES  318
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  627

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   389

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
     144,   143,   114,   111,    78,   112,   113,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    83,   148,
       2,     2,     2,    82,   123,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   145,     2,   147,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   146,     2,   149,     2,     2,     2,     2,
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
      75,    76,    77,    79,    80,    81,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   115,   116,   117,   118,   119,   120,   121,
     122,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    82,    82,    85,    88,    91,    94,    95,   101,   102,
     103,   106,   110,   116,   122,   128,   134,   140,   146,   151,
     157,   164,   170,   174,   178,   185,   189,   195,   196,   203,
     206,   209,   210,   213,   219,   233,   240,   243,   256,   270,
     273,   277,   281,   285,   292,   295,   299,   302,   308,   317,
     320,   332,   346,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   362,   368,   374,   380,   386,   393,
     401,   408,   414,   420,   426,   435,   438,   451,   465,   466,
     469,   473,   479,   485,   492,   495,   498,   507,   510,   513,
     519,   524,   528,   536,   540,   544,   548,   554,   558,   576,
     579,   592,   606,   607,   610,   614,   620,   634,   635,   638,
     642,   646,   652,   661,   664,   677,   691,   695,   698,   711,
     725,   728,   729,   730,   731,   732,   733,   734,   735,   736,
     737,   738,   739,   740,   741,   745,   749,   750,   754,   755,
     761,   765,   769,   773,   777,   783,   784,   788,   792,   793,
     794,   798,   802,   806,   807,   810,   816,   820,   826,   832,
     838,   843,   851,   854,   867,   881,   887,   891,   897,   901,
     907,   913,   920,   930,   944,   947,   951,   958,   966,   972,
     976,   982,   989,   992,  1006,  1009,  1012,  1013,  1014,  1015,
    1016,  1017,  1018,  1019,  1020,  1021,  1025,  1029,  1030,  1031,
    1032,  1033,  1034,  1035,  1036,  1037,  1041,  1042,  1043,  1044,
    1045,  1046,  1047,  1048,  1051,  1067,  1080,  1094,  1098,  1104,
    1109,  1114,  1118,  1122,  1126,  1130,  1134,  1138,  1142,  1146,
    1150,  1154,  1155,  1159,  1165,  1170,  1175,  1180,  1187,  1192,
    1199,  1204,  1211,  1212,  1213,  1214,  1215,  1216,  1219,  1224,
    1229,  1234,  1238,  1242,  1246,  1250,  1254,  1260,  1267,  1271,
    1275,  1279,  1285,  1289,  1293,  1297,  1301,  1305,  1309,  1313,
    1317,  1321,  1325,  1329,  1333,  1337,  1343,  1349,  1353,  1357,
    1363,  1369,  1373,  1377,  1381,  1385,  1391,  1396,  1403,  1407,
    1413,  1417,  1423,  1427,  1433,  1439,  1445,  1451,  1460,  1465,
    1471,  1476,  1482,  1487,  1493,  1501,  1506,  1511,  1518,  1523,
    1528,  1536,  1544,  1552,  1560,  1564,  1570,  1576,  1584
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
  "CONSTANT", "EXCEPTION_VAR", "COPY_FIELDS", "EXISTS", "DELETE", "UNDEF",
  "VOID", "BYTE", "SHORT", "INT", "LONG", "FLOAT", "DOUBLE", "STRING",
  "OBJECT", "ELEMENT", "TRUE", "FALSE", "END_OF_FILE", "RW", "RO", "WO",
  "INIT", "NEW", "OF", "BASIC_TYPE_ID", "EXTENDS", "SUPER", "RETURN",
  "WEAKEN", "DIE", "WARN", "PRINT", "SAY", "OUTMOST_CLASS_NAME",
  "UNWEAKEN", "ENABLE_OPTIONS", "DISABLE_OPTIONS", "','", "FATCAMMA",
  "ASSIGN", "SPECIAL_ASSIGN", "'?'", "':'", "LOGICAL_OR", "DEFINED_OR",
  "LOGICAL_AND", "BIT_OR", "BIT_XOR", "BIT_AND", "NUMEQ", "NUMNE", "STREQ",
  "STRNE", "NUMGT", "NUMGE", "NUMLT", "NUMLE", "STRGT", "STRGE", "STRLT",
  "STRLE", "ISA", "ISA_ERROR", "IS_TYPE", "IS_ERROR", "IS_COMPILE_TYPE",
  "NUMERIC_CMP", "STRING_CMP", "CAN", "SHIFT", "'+'", "'-'", "'.'", "'*'",
  "DIVIDE", "DIVIDE_UNSIGNED_INT", "DIVIDE_UNSIGNED_LONG", "MODULO",
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
  "copy_fields", "exists", "delete", YY_NULLPTR
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
     325,   326,   327,   328,   329,   330,   331,   332,    44,   333,
     334,   335,    63,    58,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,    43,    45,    46,    42,   363,   364,   365,   366,   367,
     368,   369,   370,    64,   371,   372,   373,   374,   375,   376,
     377,   378,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   389,    41,    40,    91,   123,    93,    59,   125
};
# endif

#define YYPACT_NINF -531

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-531)))

#define YYTABLE_NINF -316

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-316)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      22,   198,    31,  -531,    22,  -531,  -531,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,   -27,  -531,  -531,
     198,   -55,  -531,    32,    34,     4,    11,  -531,   -69,    54,
      56,    64,   198,   198,   198,   198,    78,   198,   -20,   -28,
     105,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,
    -531,   -21,  -531,    80,  -531,  -531,    76,    84,  -531,  -531,
      63,    65,    -4,   135,     3,     5,     6,     7,   902,  -531,
    -531,  -531,  -531,   -12,    10,  -531,  -531,    32,    32,   111,
    -531,   111,  -531,  -531,  -531,  -531,   113,   120,  3314,  -531,
    -531,    16,    17,     1,    18,    15,    20,    21,  3314,    81,
      23,   -20,  -531,  -531,  -531,  3314,   113,   113,  -531,  -531,
    -531,   198,   198,  1720,   113,  1853,  1986,  3314,  3314,  -531,
     113,  3314,  3314,  3314,  3314,  3314,  3314,  3446,  3314,   113,
      43,  3314,   113,  3314,  3314,  3314,  3314,  3314,  3314,  3314,
    3314,  3314,  3314,  2781,   694,  1039,  -531,    28,  -531,   165,
      25,  1176,  -531,    27,    29,  -531,  -531,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,  3975,  -531,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -102,   -90,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,   221,    93,
     140,  -531,   142,   142,  -531,    33,    36,    96,    41,  1448,
    5196,  2918,  3314,  2119,    42,  3314,  -531,  -531,  3314,  5070,
     -20,  -531,  -531,  4429,    45,    57,   -60,    55,  -531,  -531,
     -67,  -531,    59,  -531,  4040,    72,  2252,    -9,  4494,  5196,
    5196,  5196,    75,  5196,  5196,   -40,   -40,   -40,   -40,  1448,
     -40,   -40,  -531,  3578,   -40,    77,   -40,   -40,   -40,   -40,
     -40,   -40,   -40,   -40,   -34,   -34,   198,    58,   141,  5196,
     -51,    56,   -57,  -531,   123,    60,   143,  -531,  3975,   -61,
     140,   137,  -531,  -531,  -531,  -531,  3314,  3314,  3314,  3314,
    3314,  3314,  3314,  3314,  3314,  3314,  3314,  3314,  3314,  3314,
    3314,  3314,  3314,  3314,  3314,  3314,  3314,   198,   198,   198,
     198,   142,  3314,  3314,    97,  3314,  3314,  3314,  3314,  3314,
    3314,  3314,  3314,  3314,  3314,  3314,  -531,  -531,   -14,  -531,
    3314,    56,  3314,    56,  -531,  -531,    79,   221,   145,    82,
     148,  -531,   223,   223,  -531,  -531,   142,  3050,   198,    86,
    4622,  4686,    85,  5196,   107,  4750,  4814,   -20,  -531,  3314,
      88,    91,   119,  2385,  2517,  -531,    92,    94,  -531,    98,
    5196,  3314,   109,  3777,  1448,   -40,   110,   141,  3314,   198,
    -531,   141,  -531,  1316,  -531,   157,    37,    32,    32,  -531,
    1588,  -531,   114,   221,  5196,  5196,  5133,  5314,  5314,  5370,
    1302,  1302,  1434,  1574,  1574,  1574,  1574,   888,   888,   888,
     888,   888,   888,   888,   888,  -531,  -531,  -531,  -531,  -531,
     888,   888,  -531,  -531,   172,   184,   184,   184,   -40,   -40,
     -40,   -40,   -40,   -40,   -40,  2649,  3314,    56,   116,  4105,
     112,  4169,   115,   113,   118,   225,  -531,   140,   -20,   257,
    -531,   257,  -531,   134,  -531,   -20,   -20,   -20,  2119,  3710,
     -20,   132,  -531,  4559,    56,    56,   166,  -531,  4233,  -531,
    4297,    56,  5196,    56,  -531,  3843,    56,  -531,   -40,  -531,
     193,  -531,   149,   203,  5196,    32,  -531,   123,   287,   142,
    3050,   151,  3314,   153,   162,  4361,   167,  3050,  -531,  -531,
    -531,  -531,   163,   237,  -531,   234,   113,  -531,  -531,  -531,
     -47,  -531,  -531,   170,  -531,   292,    53,    53,   173,  1448,
    4878,  -531,   288,  -531,   198,   174,   178,  -531,  -531,  -531,
     179,   180,  -531,   181,   198,  3314,  3314,   142,   248,   252,
     190,   113,  5257,  -531,  -531,  -531,  -531,   191,    -8,   113,
     142,   192,   221,   113,  -531,  -531,   -20,   194,   -20,  -531,
    -531,  3182,  3909,   -20,   -25,   288,  -531,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,  4942,   256,   221,  3314,  -531,   196,
    -531,  -531,  -531,  -531,   261,    -7,   199,   201,  -531,  3314,
    -531,   202,   204,  -531,  -531,   200,  -531,  -531,  3314,   206,
    5196,   -20,  3314,  -531,  -531,   113,   -20,  5006,   -20,   -20,
    -531,  5196,   113,  -531,  5196,   209,  -531,   -20,  -531,  -531,
     210,   -20,    53,   -20,  -531,  -531,  -531
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      36,    44,     0,     2,    37,    39,    11,    12,    13,    14,
      15,    16,    17,    19,    18,    20,    45,    46,     1,    38,
       0,     0,    47,   113,   113,     0,     0,   116,     0,   114,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     113,    52,    59,    53,    54,    55,    56,    57,    58,    60,
      61,     0,    63,     0,    42,    40,     0,     0,   115,     3,
       0,     0,     0,     0,     0,     0,     0,     0,   113,    64,
      48,    51,    62,     0,     0,    43,    41,   113,   113,     0,
      67,     0,    71,    72,    65,    66,     0,     0,   113,   193,
     194,     0,     0,     0,     0,     0,     0,     0,   113,     0,
       0,     0,   181,   188,   187,   113,     0,     0,   189,   195,
     196,     0,     0,   113,     0,   113,   113,   113,   113,   197,
       0,   113,   113,   113,   113,   113,   113,   113,   113,     0,
       0,   113,     0,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   139,     0,   294,     0,
       0,   113,   120,     0,     0,   122,   123,   124,   126,   127,
     128,   130,   121,   125,   129,   192,   186,     0,   212,   198,
     231,   202,   203,   199,   242,   200,   243,   244,   245,   246,
     247,   204,   190,   206,   201,   191,   207,   211,   208,   209,
     148,   149,   210,   145,   153,   213,   154,     4,     0,     0,
      75,    73,     0,     0,     5,     0,     0,   180,   299,   113,
     150,   113,   113,   113,     0,   113,   131,   132,   113,     0,
     169,   133,   178,     0,     0,     0,   292,     0,   293,   205,
       8,    10,     9,   134,     0,     0,   113,     8,   140,   314,
     146,   147,     0,   151,   152,   219,   220,   279,   221,   113,
     234,   227,   226,   113,   224,     0,   222,   223,   225,   228,
     230,   229,   232,   233,   238,   240,     0,     0,    29,   218,
       0,     0,     0,   108,   186,     0,   183,   297,   218,     0,
       0,     0,   177,   119,   136,   138,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,     0,     0,     0,
       0,     0,   113,   113,     0,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   239,   241,     0,   137,
     113,     0,   113,     0,    28,    27,     0,     0,    80,     0,
      76,    79,    84,    84,    68,    70,     0,   113,     0,     0,
       0,     0,     0,   185,     0,     0,     0,   167,   168,   113,
       0,     0,     0,   113,   113,    21,     0,     0,   135,     0,
     142,   113,     0,   218,   113,   236,     0,    29,   113,     0,
       6,    30,    32,   217,   214,     0,   107,   113,   113,   295,
     217,   296,   301,     0,   290,   291,     0,   277,   280,   278,
     260,   258,   259,   262,   263,   269,   270,   264,   265,   266,
     267,   271,   272,   273,   274,   281,   282,   283,   284,   285,
     268,   275,   289,   288,   261,   248,   249,   276,   250,   251,
     252,   253,   254,   255,   256,   113,   113,     0,   303,     0,
       0,     0,     0,    99,     0,     0,    74,    78,     0,    87,
      85,    87,   179,     0,    69,     0,     0,     0,   113,   113,
       0,     0,   166,     0,     0,     0,     0,    22,     0,    23,
       0,     0,   144,     0,   235,   218,     0,     7,   286,    35,
      33,    31,     0,     0,   216,   113,   106,     0,     0,     0,
     113,     0,   113,     0,     0,     0,     0,   113,   306,   310,
     307,   309,     0,   100,   103,     0,    99,    81,    77,    86,
       0,    83,    88,     0,   298,   170,   174,   174,     0,   113,
       0,   158,   162,   159,     0,     0,     0,    24,    25,    26,
       0,     0,   237,     0,     0,   113,   113,     0,     0,   111,
       0,    99,   257,   287,   304,   305,   308,     0,     0,   102,
       0,     0,     0,     0,    89,    82,     0,     0,     0,   172,
     173,   113,   218,     0,     0,   163,   165,   316,   317,   318,
     311,   312,   313,    34,     0,   109,     0,   113,   300,     0,
     302,    96,    95,   101,   104,     0,    92,     0,   171,   113,
     175,     0,     0,   156,   160,     0,   164,   215,   113,     0,
     112,     0,   113,    94,    93,     0,     0,     0,     0,     0,
     161,   110,    99,    97,   105,     0,    90,     0,   155,   157,
       0,     0,   174,     0,    91,   176,    98
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -531,  -531,  -249,   -71,   273,  -138,   -97,     0,  -531,   231,
    -531,  -334,   -22,  -531,   -24,  -531,  -531,  -531,   352,  -531,
    -531,   330,  -531,  -531,   319,  -531,  -531,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,   -87,  -531,  -531,
      19,  -531,   -88,  -531,  -531,  -531,  -490,  -531,  -530,  -531,
     -19,   -11,  -531,  -531,  -531,   213,  -531,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,  -531,  -492,  -203,  -531,   -18,  -508,
     -38,  -531,   275,   -46,  -340,  -444,   328,  -531,  -139,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,  -531
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    60,   338,   205,   335,   268,   147,   231,   232,
     228,   336,   380,   381,   382,   480,     3,     4,     5,    17,
      21,    26,    39,    40,    41,    42,    43,    44,    45,   349,
      46,    47,    48,    49,   201,   339,   340,   341,    50,    51,
     449,   450,   511,   512,    52,   148,   502,   503,   504,   272,
     273,   149,    29,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   523,   564,   565,   159,   160,   161,   162,   559,
     163,   164,   165,   166,   275,   352,   269,   168,   276,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      69,    16,   199,   444,   270,   267,   279,   453,    79,   560,
      99,    86,    28,    53,   518,   229,   551,   390,   236,   583,
      22,   386,   385,   587,   197,     1,   197,   383,    23,    53,
     566,    18,    62,    63,    64,    65,   552,    67,    30,    20,
     207,   271,    31,   330,   331,    32,   362,   365,    33,    34,
      27,   579,    27,   362,    35,   332,   333,    36,    37,   491,
     224,   225,    54,   222,   342,   343,   202,   203,   235,    55,
     279,   198,    58,   596,   242,   615,   102,    24,   366,    56,
     557,   558,   440,   252,   442,   363,   255,    73,   391,    74,
     387,    24,   384,    25,    59,   494,    38,   553,   274,    68,
     326,   327,   328,    61,   362,   365,  -316,  -316,   328,    30,
     279,   226,   230,    31,   625,   237,    32,   591,    66,    33,
      34,    70,   620,    27,   594,    35,    68,    72,    36,    37,
     435,   436,   437,   280,    75,   197,   366,   422,    68,    68,
     581,   603,    76,   237,    80,   213,    77,    81,    78,   204,
     540,    82,   102,    83,    84,    85,   200,   547,   208,   266,
     211,   212,   215,   216,   220,   218,   253,    38,   217,   377,
     280,   221,   281,   419,   282,   284,   337,   285,   197,   346,
       6,   344,   358,   -49,   345,   347,   354,   360,   496,     7,
       8,     9,    10,    11,    12,    13,    14,    15,   230,   361,
     364,   378,   230,   230,   367,   379,   388,   389,   452,   392,
     415,   416,   417,   418,   369,   525,   526,   372,   586,   376,
     393,   390,   530,   443,   531,   445,   447,   533,   448,   455,
     459,   446,   466,   458,   464,   279,     6,   465,   266,   467,
     485,   469,   599,   423,   471,     7,     8,     9,    10,    11,
      12,    13,    14,    15,   -50,   473,   476,   438,   490,     6,
     497,   499,   506,   510,   501,   507,   230,   334,     7,     8,
       9,    10,    11,    12,    13,    14,    15,   514,   522,   527,
     534,   536,   479,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   535,   538,   541,   543,   493,   319,   320,
     321,   322,   323,   324,   325,   544,   548,   230,   230,   230,
     230,   230,   326,   327,   328,   549,   546,   550,   555,   462,
     556,   561,    98,   568,   326,   327,   328,   569,   570,   571,
     572,   576,   577,   578,   580,   585,   598,   230,   589,   601,
     487,   602,   227,   605,   606,   608,   230,   609,   454,   610,
     612,   539,   621,   623,   206,   477,    19,   481,    57,    71,
     508,   595,   451,   513,   283,   483,     0,   486,   214,     0,
       0,     0,     0,     0,     0,     0,   488,   489,     0,   230,
     279,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   230,     0,     0,   167,   505,     0,   575,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     509,     0,   584,     0,     0,     0,   210,   515,   516,   517,
       0,     0,   521,     0,     0,     0,   219,   567,     0,     0,
       0,     0,     0,   223,     0,   237,     0,   573,     0,     0,
       0,   234,     0,   238,   239,   240,   241,     0,     0,   243,
     244,   245,   246,   247,   248,   250,   251,     0,     0,   254,
     505,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,     0,   554,   278,   537,     0,     0,     0,     0,   167,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   230,
       0,     0,     0,     0,     0,   505,     0,     0,     0,     0,
       0,     0,     0,   505,     0,     0,     0,   505,     0,     0,
     582,     0,     0,     0,     0,     0,     0,     0,   588,     0,
     590,     0,     0,     0,   230,   593,     0,     0,     0,     0,
       0,     0,     0,     0,   230,     0,     0,   230,     0,   350,
     351,   353,     0,   355,     0,     0,   356,   604,     0,     0,
     230,     0,   230,     0,     0,     0,     0,     0,     0,   505,
       0,     0,     0,   613,   370,     0,   505,     0,   616,     0,
     618,   619,     0,     0,     0,     0,   230,   373,     0,   622,
       0,   375,     0,   624,     0,   626,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   394,   395,   396,   397,   398,   399,
     400,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,   414,     0,     0,     0,     0,     0,
     420,   421,     0,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   433,   434,     0,     0,     0,     0,   439,     0,
     441,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   463,     0,     0,
       0,   468,   470,     0,     0,     0,     0,     0,   271,   472,
       0,     0,   475,     0,    86,     0,   478,     0,     0,     0,
      87,   484,    27,     0,     0,    89,    90,     0,   484,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     6,   102,   103,   104,     0,   106,     0,   108,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    15,
     109,   110,     0,     0,     0,     0,     0,   111,     0,   112,
       0,     0,     0,     0,   495,     0,     0,     0,   119,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   353,   520,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   123,   124,     0,     0,     0,
       0,     0,     0,     0,     0,   125,   126,   127,   128,   129,
     542,     0,     0,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,     0,     0,   143,   144,
     209,  -182,     0,     0,     0,     0,     0,   562,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   350,   574,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   353,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   600,     0,     0,     0,     0,
       0,     0,    86,     0,     0,     0,     0,   607,    87,     0,
      27,    88,     0,    89,    90,     0,   611,    91,    92,     0,
     614,    93,    94,    95,    96,    97,    98,    99,   100,   101,
       6,   102,   103,   104,   105,   106,   107,   108,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    15,   109,   110,
       0,     0,     0,     0,     0,   111,     0,   112,     0,     0,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
       0,     0,  -316,  -316,  -316,  -316,  -316,  -316,  -316,  -316,
    -316,  -316,  -316,  -316,  -316,  -316,  -316,  -316,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,     0,
       0,     0,     0,   123,   124,     0,     0,     0,     0,     0,
       0,     0,     0,   125,   126,   127,   128,   129,   326,   327,
     328,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,     0,     0,   143,   144,   145,    86,
     146,  -117,     0,     0,     0,    87,     0,    27,    88,     0,
      89,    90,     0,     0,    91,    92,     0,     0,    93,    94,
      95,    96,    97,    98,    99,   100,   101,     6,   102,   103,
     104,   105,   106,   107,   108,     0,     7,     8,     9,    10,
      11,    12,    13,    14,    15,   109,   110,     0,     0,     0,
       0,     0,   111,     0,   112,     0,     0,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     123,   124,     0,     0,     0,     0,     0,     0,     0,     0,
     125,   126,   127,   128,   129,     0,     0,     0,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,     0,     0,   143,   144,   145,    86,   146,   277,     0,
       0,     0,    87,     0,    27,    88,     0,    89,    90,     0,
       0,    91,    92,     0,     0,    93,    94,    95,    96,    97,
      98,    99,   100,   101,     6,   102,   103,   104,   105,   106,
     107,   108,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,   109,   110,     0,     0,     0,     0,     0,   111,
       0,   112,     0,     0,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   123,   124,     0,
       0,     0,     0,     0,     0,     0,     0,   125,   126,   127,
     128,   129,     0,     0,     0,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,     0,     0,
     143,   144,   145,  -113,   146,  -118,    86,     0,     0,     0,
       0,     0,    87,     0,    27,     0,     0,    89,    90,     0,
       0,   482,    92,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,   102,   103,   104,     0,   106,
       0,   108,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,   109,   110,     0,     0,     0,     0,     0,   111,
       0,   112,     0,     0,     0,     0,     0,     0,     0,     0,
     119,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,     0,     0,     0,     0,   123,   124,     0,
       0,     0,     0,     0,     0,     0,     0,   125,   126,   127,
     128,   129,   326,   327,   328,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,    86,     0,
     143,   144,   209,     0,    87,     0,    27,     0,     0,    89,
      90,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,   102,   103,   104,
       0,   106,     0,   108,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    15,   109,   110,     0,     0,     0,     0,
       0,   111,     0,   112,     0,     0,     0,     0,     0,     0,
       0,     0,   119,     0,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,     0,     0,     0,     0,   123,
     124,     0,     0,     0,     0,     0,     0,     0,     0,   125,
     126,   127,   128,   129,   326,   327,   328,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
       0,     0,   143,   144,   209,  -113,     0,   277,    86,     0,
       0,     0,     0,     0,    87,     0,    27,     0,     0,    89,
      90,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,   102,   103,   104,
       0,   106,     0,   108,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    15,   109,   110,     0,     0,     0,     0,
       0,   111,     0,   112,     0,     0,     0,     0,     0,     0,
       0,     0,   119,     0,  -316,  -316,  -316,  -316,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,     0,     0,     0,     0,   123,
     124,     0,     0,     0,     0,     0,     0,     0,     0,   125,
     126,   127,   128,   129,   326,   327,   328,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
      86,     0,   143,   144,   209,     0,    87,     0,    27,     0,
       0,    89,    90,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     6,   102,
     103,   104,     0,   106,     0,   108,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    15,   109,   110,     0,     0,
       0,     0,     0,   111,     0,   112,     0,     0,     0,     0,
       0,     0,     0,     0,   119,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   123,   124,     0,     0,     0,     0,     0,     0,     0,
       0,   125,   126,   127,   128,   129,     0,     0,     0,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,     0,    86,   143,   144,   209,     0,   233,    87,
       0,    27,     0,     0,    89,    90,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,   102,   103,   104,     0,   106,     0,   108,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    15,   109,
     110,     0,     0,     0,     0,     0,   111,     0,   112,     0,
       0,     0,     0,     0,     0,     0,     0,   119,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   123,   124,     0,     0,     0,     0,
       0,     0,     0,     0,   125,   126,   127,   128,   129,     0,
       0,     0,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,     0,    86,   143,   144,   209,
       0,  -141,    87,     0,    27,     0,     0,    89,    90,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,   102,   103,   104,     0,   106,
       0,   108,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,   109,   110,     0,     0,     0,     0,     0,   111,
       0,   112,     0,     0,     0,     0,     0,     0,     0,     0,
     119,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   123,   124,     0,
       0,     0,     0,     0,     0,     0,     0,   125,   126,   127,
     128,   129,     0,     0,     0,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,     0,    86,
     143,   144,   209,     0,  -315,    87,     0,    27,     0,     0,
      89,    90,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6,   102,   103,
     104,     0,   106,     0,   108,     0,     7,     8,     9,    10,
      11,    12,    13,    14,    15,   109,   110,     0,     0,     0,
       0,     0,   111,     0,   112,     0,     0,     0,     0,     0,
       0,     0,     0,   119,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     123,   124,     0,     0,     0,     0,     0,     0,     0,     0,
     125,   126,   127,   128,   129,     0,     0,     0,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,     0,    86,   143,   144,   209,     0,  -184,    87,     0,
      27,     0,     0,    89,    90,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       6,   102,   103,   104,     0,   106,     0,   108,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    15,   109,   110,
       0,     0,     0,     0,     0,   111,     0,   112,     0,     0,
       0,     0,     0,     0,     0,     0,   119,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   123,   124,     0,     0,     0,     0,     0,
       0,     0,     0,   125,   126,   127,   128,   129,     0,     0,
       0,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,     0,    86,   143,   144,   209,     0,
    -143,    87,     0,    27,     0,     0,    89,    90,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,   102,   103,   104,     0,   106,     0,
     108,     0,     7,     8,     9,    10,    11,    12,    13,    14,
      15,   109,   110,     0,     0,     0,     0,     0,   111,     0,
     112,     0,     0,     0,     0,     0,     0,     0,     0,   119,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   123,   124,     0,     0,
       0,     0,     0,     0,     0,     0,   125,   126,   127,   128,
     129,     0,     0,     0,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,    86,     0,   143,
     144,   209,   467,    87,     0,    27,     0,     0,    89,    90,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,   102,   103,   104,     0,
     106,     0,   108,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    15,   109,   110,     0,     0,     0,     0,     0,
     111,     0,   112,     0,     0,     0,     0,     0,     0,     0,
       0,   119,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   123,   124,
       0,     0,     0,     0,     0,     0,     0,     0,   125,   126,
     127,   128,   129,     0,     0,     0,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,    86,
       0,   143,   144,   209,   469,    87,   266,    27,     0,     0,
      89,    90,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6,   102,   103,
     104,     0,   106,     0,   108,     0,     7,     8,     9,    10,
      11,    12,    13,    14,    15,   109,   110,     0,     0,     0,
       0,     0,   111,     0,   112,     0,     0,     0,     0,     0,
       0,     0,     0,   119,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     123,   124,     0,     0,     0,     0,     0,     0,     0,     0,
     125,   126,   127,   128,   129,     0,     0,     0,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,    86,  -182,   143,   144,   209,     0,    87,   266,    27,
       0,     0,    89,    90,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
     102,   103,   104,     0,   106,     0,   108,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    15,   109,   110,     0,
       0,     0,     0,     0,   111,     0,   112,     0,     0,     0,
       0,     0,     0,     0,     0,   119,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   123,   124,     0,     0,     0,     0,     0,     0,
       0,     0,   125,   126,   127,   128,   129,     0,     0,     0,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,     0,     0,   143,   144,   209,    86,     0,
       0,   348,     0,     0,    87,     0,    27,     0,     0,    89,
      90,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,   102,   103,   104,
       0,   106,     0,   108,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    15,   109,   110,     0,     0,     0,     0,
       0,   111,     0,   112,     0,     0,     0,     0,     0,     0,
       0,     0,   119,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   123,
     124,     0,     0,     0,     0,     0,     0,     0,     0,   125,
     126,   127,   128,   129,     0,     0,     0,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
      86,     0,   143,   144,   209,     0,    87,     0,    27,     0,
       0,    89,    90,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     6,   102,
     103,   104,     0,   106,     0,   108,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    15,   109,   110,     0,     0,
       0,     0,     0,   111,     0,   112,     0,     0,     0,     0,
       0,     0,     0,     0,   119,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   123,   124,     0,     0,     0,     0,     0,     0,     0,
       0,   125,   126,   127,   128,   129,     0,     0,     0,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,    86,  -182,   143,   144,   209,     0,    87,     0,
      27,     0,     0,    89,    90,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       6,   102,   103,   104,     0,   106,     0,   108,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    15,   109,   110,
       0,     0,     0,     0,     0,   111,     0,   112,     0,     0,
       0,     0,     0,     0,     0,     0,   119,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   123,   124,     0,     0,     0,     0,     0,
       0,     0,     0,   125,   126,   127,   128,   129,     0,     0,
       0,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,    86,  -184,   143,   144,   209,     0,
      87,     0,    27,     0,     0,    89,    90,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     6,   102,   103,   104,     0,   106,     0,   108,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    15,
     109,   110,     0,     0,     0,     0,     0,   111,     0,   112,
       0,     0,     0,     0,     0,     0,     0,     0,   119,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   123,   124,     0,     0,     0,
       0,     0,     0,     0,     0,   125,   126,   127,   128,   129,
       0,     0,     0,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,    86,     0,   143,   144,
     209,     0,    87,     0,    27,     0,     0,    89,    90,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,   102,   103,   104,     0,   106,
       0,   108,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,   109,   110,     0,     0,     0,     0,     0,   111,
       0,   112,     0,     0,     0,     0,     0,     0,     0,     0,
     119,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   123,   124,     0,
       0,     0,     0,     0,     0,     0,     0,   125,   126,   127,
     128,   129,     0,     0,     0,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,    86,     0,
     143,   144,   249,     0,    87,     0,    27,     0,     0,    89,
      90,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,   102,   103,   104,
       0,   106,     0,   108,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    15,   109,   110,     0,     0,     0,     0,
       0,   111,     0,   112,     0,     0,     0,     0,     0,     0,
       0,     0,   119,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   123,
     124,     0,     0,     0,     0,     0,     0,     0,     0,   125,
     126,   127,   128,   129,     0,     0,     0,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
      86,     0,   143,   144,   374,     0,    87,     0,    27,     0,
       0,    89,    90,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     6,   102,
     103,   104,     0,   106,     0,   108,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    15,   109,   110,     0,     0,
       0,     0,     0,   111,     0,   112,     0,     0,     0,     0,
       0,     0,     0,     0,   119,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   123,   124,     0,     0,     0,     0,     0,     0,     0,
       0,   125,   126,   127,   128,   129,     0,     0,     0,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,     0,     0,   143,   144,   519,   286,   287,   288,
       0,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   326,   327,   328,
       0,     0,     0,   286,   287,   288,   474,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   326,   327,   328,     0,     0,     0,   286,
     287,   288,   532,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   326,
     327,   328,     0,     0,     0,   286,   287,   288,   592,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   326,   327,   328,     0,     0,
     286,   287,   288,   329,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     326,   327,   328,     0,     0,   286,   287,   288,   368,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   326,   327,   328,     0,   286,
     287,   288,   498,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   326,
     327,   328,     0,   286,   287,   288,   500,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   326,   327,   328,     0,   286,   287,   288,
     528,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   326,   327,   328,
       0,   286,   287,   288,   529,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   326,   327,   328,     0,     0,     0,   359,   545,   286,
     287,   288,     0,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   326,
     327,   328,   371,     0,   286,   287,   288,     0,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   326,   327,   328,   524,     0,   286,
     287,   288,     0,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   326,
     327,   328,   286,   287,   288,     0,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   326,   327,   328,   456,   286,   287,   288,     0,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   326,   327,   328,   457,
     286,   287,   288,     0,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     326,   327,   328,   460,   286,   287,   288,     0,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   326,   327,   328,   461,   286,   287,
     288,     0,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   326,   327,
     328,   563,   286,   287,   288,     0,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   326,   327,   328,   597,   286,   287,   288,     0,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   326,   327,   328,   617,
     286,   287,   288,   357,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     326,   327,   328,   286,   287,   288,   492,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   326,   327,   328,   286,   287,   288,     0,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   326,   327,   328,   288,
       0,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   326,   327,   328,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   326,   327,   328,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     326,   327,   328
};

static const yytype_int16 yycheck[] =
{
      38,     1,    73,   337,   143,   143,   145,   347,    12,   517,
      35,    10,    23,    24,   458,   112,   506,    78,   115,   549,
      20,    78,   271,   553,    38,     3,    38,    78,    83,    40,
     522,     0,    32,    33,    34,    35,    83,    37,     4,    66,
      86,     4,     8,   145,   146,    11,   113,   114,    14,    15,
      18,   541,    18,   113,    20,   145,   146,    23,    24,   393,
     106,   107,    58,   101,   202,   203,    77,    78,   114,    58,
     209,    83,    18,   565,   120,   605,    39,   146,   145,   148,
      27,    28,   331,   129,   333,   145,   132,     7,   149,     9,
     147,   146,   143,   148,    38,   435,    62,   144,   144,   146,
     140,   141,   142,    39,   113,   114,   140,   141,   142,     4,
     249,   111,   112,     8,   622,   115,    11,   561,    40,    14,
      15,   149,   612,    18,   149,    20,   146,   148,    23,    24,
     144,   145,   146,   142,    58,    38,   145,    40,   146,   146,
     148,   148,    58,   143,   148,   144,    83,    12,    83,    38,
     490,   148,    39,   148,   148,   148,   146,   497,    38,    17,
     144,   144,   144,   148,    83,   144,   123,    62,   148,   266,
     142,   148,     7,   311,   149,   148,    83,   148,    38,    83,
      38,   148,   220,   149,   148,   144,   144,   142,   437,    47,
      48,    49,    50,    51,    52,    53,    54,    55,   198,   142,
     145,   143,   202,   203,   145,    64,    83,   147,   346,   280,
     307,   308,   309,   310,   142,   464,   465,   142,   552,   142,
      83,    78,   471,   144,   473,    80,    78,   476,     5,   143,
     123,   149,   113,   148,   146,   374,    38,   146,    17,   147,
      83,   147,   576,   314,   146,    47,    48,    49,    50,    51,
      52,    53,    54,    55,   149,   146,   146,   328,   144,    38,
     144,   149,   144,     6,   149,    40,   266,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,   143,   146,   113,
      87,    78,   379,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   144,     7,   144,   143,   435,   114,   115,
     116,   117,   118,   119,   120,   143,   143,   307,   308,   309,
     310,   311,   140,   141,   142,    78,   149,    83,   148,   357,
      28,   148,    34,   149,   140,   141,   142,   149,   149,   149,
     149,    83,    80,   143,   143,   143,    80,   337,   144,   143,
     386,    80,   111,   144,   143,   143,   346,   143,   348,   149,
     144,   489,   143,   143,    81,   377,     4,   381,    28,    40,
     447,   564,   343,   451,   151,   383,    -1,   386,    93,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   387,   388,    -1,   379,
     519,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   393,    -1,    -1,    68,   443,    -1,   537,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     448,    -1,   550,    -1,    -1,    -1,    88,   455,   456,   457,
      -1,    -1,   460,    -1,    -1,    -1,    98,   524,    -1,    -1,
      -1,    -1,    -1,   105,    -1,   435,    -1,   534,    -1,    -1,
      -1,   113,    -1,   115,   116,   117,   118,    -1,    -1,   121,
     122,   123,   124,   125,   126,   127,   128,    -1,    -1,   131,
     506,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,    -1,   510,   145,   485,    -1,    -1,    -1,    -1,   151,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   489,
      -1,    -1,    -1,    -1,    -1,   541,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   549,    -1,    -1,    -1,   553,    -1,    -1,
     548,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   556,    -1,
     558,    -1,    -1,    -1,   524,   563,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   534,    -1,    -1,   537,    -1,   211,
     212,   213,    -1,   215,    -1,    -1,   218,   585,    -1,    -1,
     550,    -1,   552,    -1,    -1,    -1,    -1,    -1,    -1,   605,
      -1,    -1,    -1,   601,   236,    -1,   612,    -1,   606,    -1,
     608,   609,    -1,    -1,    -1,    -1,   576,   249,    -1,   617,
      -1,   253,    -1,   621,    -1,   623,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,    -1,    -1,    -1,    -1,    -1,
     312,   313,    -1,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,    -1,    -1,    -1,    -1,   330,    -1,
     332,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   359,    -1,    -1,
      -1,   363,   364,    -1,    -1,    -1,    -1,    -1,     4,   371,
      -1,    -1,   374,    -1,    10,    -1,   378,    -1,    -1,    -1,
      16,   383,    18,    -1,    -1,    21,    22,    -1,   390,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    41,    -1,    43,    -1,    45,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    -1,    -1,    -1,    -1,    63,    -1,    65,
      -1,    -1,    -1,    -1,   436,    -1,    -1,    -1,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   458,   459,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   111,   112,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   121,   122,   123,   124,   125,
     492,    -1,    -1,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,    -1,    -1,   144,   145,
     146,   147,    -1,    -1,    -1,    -1,    -1,   519,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   535,   536,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   561,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   577,    -1,    -1,    -1,    -1,
      -1,    -1,    10,    -1,    -1,    -1,    -1,   589,    16,    -1,
      18,    19,    -1,    21,    22,    -1,   598,    25,    26,    -1,
     602,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    -1,    -1,    -1,    -1,    63,    -1,    65,    -1,    -1,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      -1,    -1,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,    -1,
      -1,    -1,    -1,   111,   112,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   121,   122,   123,   124,   125,   140,   141,
     142,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,    -1,    -1,   144,   145,   146,    10,
     148,   149,    -1,    -1,    -1,    16,    -1,    18,    19,    -1,
      21,    22,    -1,    -1,    25,    26,    -1,    -1,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    -1,    -1,
      -1,    -1,    63,    -1,    65,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     111,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     121,   122,   123,   124,   125,    -1,    -1,    -1,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,    -1,    -1,   144,   145,   146,    10,   148,   149,    -1,
      -1,    -1,    16,    -1,    18,    19,    -1,    21,    22,    -1,
      -1,    25,    26,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,    63,
      -1,    65,    -1,    -1,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   111,   112,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,   122,   123,
     124,   125,    -1,    -1,    -1,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,    -1,    -1,
     144,   145,   146,     7,   148,   149,    10,    -1,    -1,    -1,
      -1,    -1,    16,    -1,    18,    -1,    -1,    21,    22,    -1,
      -1,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,
      -1,    45,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,    63,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,    -1,    -1,    -1,    -1,   111,   112,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,   122,   123,
     124,   125,   140,   141,   142,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,    10,    -1,
     144,   145,   146,    -1,    16,    -1,    18,    -1,    -1,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      -1,    43,    -1,    45,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    -1,    -1,    -1,
      -1,    63,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    -1,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,    -1,    -1,    -1,    -1,   111,
     112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,
     122,   123,   124,   125,   140,   141,   142,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
      -1,    -1,   144,   145,   146,     7,    -1,   149,    10,    -1,
      -1,    -1,    -1,    -1,    16,    -1,    18,    -1,    -1,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      -1,    43,    -1,    45,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    -1,    -1,    -1,
      -1,    63,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    -1,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,    -1,    -1,    -1,    -1,   111,
     112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,
     122,   123,   124,   125,   140,   141,   142,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
      10,    -1,   144,   145,   146,    -1,    16,    -1,    18,    -1,
      -1,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    -1,    43,    -1,    45,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    -1,
      -1,    -1,    -1,    63,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   111,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   121,   122,   123,   124,   125,    -1,    -1,    -1,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,    -1,    10,   144,   145,   146,    -1,   148,    16,
      -1,    18,    -1,    -1,    21,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    41,    -1,    43,    -1,    45,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    -1,    -1,    -1,    -1,    63,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   111,   112,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   121,   122,   123,   124,   125,    -1,
      -1,    -1,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,    -1,    10,   144,   145,   146,
      -1,   148,    16,    -1,    18,    -1,    -1,    21,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,
      -1,    45,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,    63,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   111,   112,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,   122,   123,
     124,   125,    -1,    -1,    -1,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,    -1,    10,
     144,   145,   146,    -1,   148,    16,    -1,    18,    -1,    -1,
      21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,
      41,    -1,    43,    -1,    45,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    -1,    -1,
      -1,    -1,    63,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     111,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     121,   122,   123,   124,   125,    -1,    -1,    -1,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,    -1,    10,   144,   145,   146,    -1,   148,    16,    -1,
      18,    -1,    -1,    21,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    41,    -1,    43,    -1,    45,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    -1,    -1,    -1,    -1,    63,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   111,   112,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   121,   122,   123,   124,   125,    -1,    -1,
      -1,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,    -1,    10,   144,   145,   146,    -1,
     148,    16,    -1,    18,    -1,    -1,    21,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,    -1,
      45,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    -1,    -1,    -1,    -1,    63,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   111,   112,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   121,   122,   123,   124,
     125,    -1,    -1,    -1,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,    10,    -1,   144,
     145,   146,   147,    16,    -1,    18,    -1,    -1,    21,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,
      43,    -1,    45,    -1,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,
      63,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   111,   112,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,   122,
     123,   124,   125,    -1,    -1,    -1,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,    10,
      -1,   144,   145,   146,   147,    16,    17,    18,    -1,    -1,
      21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,
      41,    -1,    43,    -1,    45,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    -1,    -1,
      -1,    -1,    63,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     111,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     121,   122,   123,   124,   125,    -1,    -1,    -1,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,    10,   143,   144,   145,   146,    -1,    16,    17,    18,
      -1,    -1,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    -1,    43,    -1,    45,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    63,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   111,   112,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   121,   122,   123,   124,   125,    -1,    -1,    -1,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,    -1,    -1,   144,   145,   146,    10,    -1,
      -1,    13,    -1,    -1,    16,    -1,    18,    -1,    -1,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      -1,    43,    -1,    45,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    -1,    -1,    -1,
      -1,    63,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   111,
     112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,
     122,   123,   124,   125,    -1,    -1,    -1,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
      10,    -1,   144,   145,   146,    -1,    16,    -1,    18,    -1,
      -1,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    -1,    43,    -1,    45,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    -1,
      -1,    -1,    -1,    63,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   111,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   121,   122,   123,   124,   125,    -1,    -1,    -1,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,    10,   143,   144,   145,   146,    -1,    16,    -1,
      18,    -1,    -1,    21,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    41,    -1,    43,    -1,    45,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    -1,    -1,    -1,    -1,    63,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   111,   112,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   121,   122,   123,   124,   125,    -1,    -1,
      -1,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,    10,   143,   144,   145,   146,    -1,
      16,    -1,    18,    -1,    -1,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    41,    -1,    43,    -1,    45,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    -1,    -1,    -1,    -1,    63,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   111,   112,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   121,   122,   123,   124,   125,
      -1,    -1,    -1,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,    10,    -1,   144,   145,
     146,    -1,    16,    -1,    18,    -1,    -1,    21,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,
      -1,    45,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,    63,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   111,   112,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,   122,   123,
     124,   125,    -1,    -1,    -1,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,    10,    -1,
     144,   145,   146,    -1,    16,    -1,    18,    -1,    -1,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      -1,    43,    -1,    45,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    -1,    -1,    -1,
      -1,    63,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   111,
     112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,
     122,   123,   124,   125,    -1,    -1,    -1,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
      10,    -1,   144,   145,   146,    -1,    16,    -1,    18,    -1,
      -1,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    -1,    43,    -1,    45,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    -1,
      -1,    -1,    -1,    63,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   111,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   121,   122,   123,   124,   125,    -1,    -1,    -1,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,    -1,    -1,   144,   145,   146,    80,    81,    82,
      -1,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,   141,   142,
      -1,    -1,    -1,    80,    81,    82,   149,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   140,   141,   142,    -1,    -1,    -1,    80,
      81,    82,   149,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,
     141,   142,    -1,    -1,    -1,    80,    81,    82,   149,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   140,   141,   142,    -1,    -1,
      80,    81,    82,   148,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     140,   141,   142,    -1,    -1,    80,    81,    82,   148,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   140,   141,   142,    -1,    80,
      81,    82,   147,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,
     141,   142,    -1,    80,    81,    82,   147,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   140,   141,   142,    -1,    80,    81,    82,
     147,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,   141,   142,
      -1,    80,    81,    82,   147,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   140,   141,   142,    -1,    -1,    -1,    78,   147,    80,
      81,    82,    -1,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,
     141,   142,    78,    -1,    80,    81,    82,    -1,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   140,   141,   142,    78,    -1,    80,
      81,    82,    -1,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,
     141,   142,    80,    81,    82,    -1,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   140,   141,   142,   143,    80,    81,    82,    -1,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   140,   141,   142,   143,
      80,    81,    82,    -1,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     140,   141,   142,   143,    80,    81,    82,    -1,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   140,   141,   142,   143,    80,    81,
      82,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,   141,
     142,   143,    80,    81,    82,    -1,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   140,   141,   142,   143,    80,    81,    82,    -1,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   140,   141,   142,   143,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     140,   141,   142,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   140,   141,   142,    80,    81,    82,    -1,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   140,   141,   142,    82,
      -1,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,   141,   142,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   140,   141,   142,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     140,   141,   142
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,   151,   166,   167,   168,    38,    47,    48,    49,
      50,    51,    52,    53,    54,    55,   157,   169,     0,   168,
      66,   170,   157,    83,   146,   148,   171,    18,   201,   202,
       4,     8,    11,    14,    15,    20,    23,    24,    62,   172,
     173,   174,   175,   176,   177,   178,   180,   181,   182,   183,
     188,   189,   194,   201,    58,    58,   148,   171,    18,    38,
     152,    39,   157,   157,   157,   157,    40,   157,   146,   220,
     149,   174,   148,     7,     9,    58,    58,    83,    83,    12,
     148,    12,   148,   148,   148,   148,    10,    16,    19,    21,
      22,    25,    26,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    39,    40,    41,    42,    43,    44,    45,    56,
      57,    63,    65,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,   111,   112,   121,   122,   123,   124,   125,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   144,   145,   146,   148,   157,   195,   201,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   215,
     216,   217,   218,   220,   221,   222,   223,   226,   227,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,    38,    83,   153,
     146,   184,   201,   201,    38,   154,   154,   223,    38,   146,
     226,   144,   144,   144,   222,   144,   148,   148,   144,   226,
      83,   148,   220,   226,   223,   223,   157,   159,   160,   156,
     157,   158,   159,   148,   226,   223,   156,   157,   226,   226,
     226,   226,   223,   226,   226,   226,   226,   226,   226,   146,
     226,   226,   223,   123,   226,   223,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   226,    17,   155,   156,   226,
     228,     4,   199,   200,   223,   224,   228,   149,   226,   228,
     142,     7,   149,   205,   148,   148,    80,    81,    82,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   140,   141,   142,   148,
     145,   146,   145,   146,    46,   155,   161,    83,   153,   185,
     186,   187,   155,   155,   148,   148,    83,   144,    13,   179,
     226,   226,   225,   226,   144,   226,   226,    83,   220,    78,
     142,   142,   113,   145,   145,   114,   145,   145,   148,   142,
     226,    78,   142,   226,   146,   226,   142,   156,   143,    64,
     162,   163,   164,    78,   143,   152,    78,   147,    83,   147,
      78,   149,   153,    83,   226,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   156,   156,   156,   156,   155,
     226,   226,    40,   153,   226,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   144,   145,   146,   153,   226,
     152,   226,   152,   144,   161,    80,   149,    78,     5,   190,
     191,   190,   155,   224,   157,   143,   143,   143,   148,   123,
     143,   143,   220,   226,   146,   146,   113,   147,   226,   147,
     226,   146,   226,   146,   149,   226,   146,   162,   226,   156,
     165,   164,    25,   218,   226,    83,   200,   223,   201,   201,
     144,   161,    83,   155,   224,   226,   152,   144,   147,   149,
     147,   149,   196,   197,   198,   223,   144,    40,   187,   220,
       6,   192,   193,   192,   143,   220,   220,   220,   225,   146,
     226,   220,   146,   212,    78,   152,   152,   113,   147,   147,
     152,   152,   149,   152,    87,   144,    78,   201,     7,   155,
     224,   144,   226,   143,   143,   147,   149,   224,   143,    78,
      83,   196,    83,   144,   220,   148,    28,    27,    28,   219,
     219,   148,   226,   143,   213,   214,   215,   156,   149,   149,
     149,   149,   149,   156,   226,   155,    83,    80,   143,   196,
     143,   148,   220,   198,   155,   143,   161,   198,   220,   144,
     220,   225,   149,   220,   149,   216,   215,   143,    80,   161,
     226,   143,    80,   148,   220,   144,   143,   226,   143,   143,
     149,   226,   144,   220,   226,   198,   220,   143,   220,   220,
     196,   143,   220,   143,   220,   219,   220
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   150,   151,   152,   153,   154,   155,   155,   156,   156,
     156,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   158,   159,   159,   159,   160,   160,   161,   161,   162,
     162,   163,   163,   164,   165,   165,   166,   166,   167,   167,
     168,   168,   168,   168,   169,   169,   170,   170,   171,   172,
     172,   173,   173,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   175,   176,   177,   178,   178,   179,
     180,   181,   182,   183,   184,   185,   185,   186,   186,   186,
     187,   187,   188,   189,   190,   190,   191,   192,   192,   193,
     193,   193,   193,   194,   194,   194,   194,   195,   195,   196,
     196,   197,   197,   197,   198,   198,   199,   199,   199,   200,
     200,   200,   200,   201,   201,   202,   202,   203,   203,   204,
     204,   205,   205,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   205,
     206,   206,   206,   206,   206,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   208,   209,   209,   210,   211,
     212,   212,   213,   213,   214,   214,   215,   215,   216,   216,
     217,   217,   218,   218,   219,   219,   219,   220,   221,   222,
     222,   223,   224,   224,   225,   225,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   227,   227,   228,   228,   228,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   230,   230,   230,   230,   231,   231,
     232,   232,   233,   233,   233,   233,   233,   233,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   235,   236,   236,
     236,   236,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   238,   239,   239,   239,
     240,   241,   241,   241,   241,   241,   242,   242,   243,   243,
     244,   244,   245,   245,   245,   246,   246,   246,   247,   247,
     247,   247,   247,   247,   247,   248,   248,   248,   249,   249,
     249,   250,   251,   252,   253,   253,   254,   255,   256
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     2,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     3,     3,     4,     4,     4,     1,     1,     0,
       1,     2,     1,     2,     3,     1,     0,     1,     2,     1,
       5,     7,     5,     7,     0,     1,     0,     2,     3,     0,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     3,     3,     3,     5,     2,
       5,     3,     3,     3,     3,     0,     1,     3,     2,     1,
       1,     3,     8,     7,     0,     1,     2,     0,     1,     2,
       5,     7,     3,     9,     9,     8,     8,     8,    11,     0,
       1,     3,     2,     1,     3,     5,     3,     2,     1,     5,
       7,     4,     6,     0,     1,     2,     1,     0,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     3,     2,     2,     2,     1,
       2,     1,     3,     2,     4,     1,     2,     2,     1,     1,
       2,     2,     2,     1,     1,     9,     7,     9,     5,     5,
       3,     4,     0,     1,     2,     1,     4,     3,     3,     2,
       5,     7,     6,     6,     0,     2,     6,     3,     2,     4,
       2,     1,     0,     1,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     7,     3,     2,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     1,     2,     2,     2,     4,     3,     5,     2,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     5,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       3,     3,     3,     3,     3,     3,     4,     5,     3,     3,
       3,     3,     2,     2,     1,     3,     3,     2,     5,     2,
       6,     3,     6,     3,     5,     5,     4,     4,     5,     4,
       4,     6,     6,     6,     2,     1,     6,     6,     6
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
#line 96 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_mutable_type(compiler, (yyvsp[-1].opval));
    }
#line 2815 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 11:
#line 107 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[0].opval));
    }
#line 2823 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 12:
#line 111 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_byte_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2833 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 13:
#line 117 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_short_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2843 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 14:
#line 123 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2853 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 15:
#line 129 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_long_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2863 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 16:
#line 135 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_float_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2873 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 17:
#line 141 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_double_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2883 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 18:
#line 147 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_any_object_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = op_type;
    }
#line 2892 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 19:
#line 152 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_string_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2902 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 20:
#line 158 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_any_object_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = op_type;
    }
#line 2911 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 21:
#line 165 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[-1].opval));
    }
#line 2919 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 22:
#line 171 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-2].opval), NULL, 0);
    }
#line 2927 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 23:
#line 175 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-2].opval), NULL, 0);
    }
#line 2935 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 24:
#line 179 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), NULL, 1);
    }
#line 2944 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 25:
#line 186 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval), 0);
    }
#line 2952 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 26:
#line 190 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval), 0);
    }
#line 2960 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 28:
#line 197 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_void_type(compiler, compiler->current_file, compiler->current_line);
    }
#line 2968 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 29:
#line 203 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
#line 2976 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 33:
#line 214 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 2984 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 34:
#line 220 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3002 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 35:
#line 234 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 3010 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 36:
#line 240 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3018 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 37:
#line 244 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3033 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 38:
#line 257 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3051 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 40:
#line 274 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), NULL, (yyvsp[-2].opval));
    }
#line 3059 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 41:
#line 278 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[-4].opval));
    }
#line 3067 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 42:
#line 282 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), NULL, NULL, (yyvsp[-2].opval));
    }
#line 3075 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 43:
#line 286 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), NULL, (yyvsp[-2].opval), (yyvsp[-4].opval));
    }
#line 3083 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 44:
#line 292 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 3091 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 46:
#line 299 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 3099 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 47:
#line 303 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_extends(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3107 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 48:
#line 309 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_class_block;
    }
#line 3117 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 49:
#line 317 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3125 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 50:
#line 321 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[0].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
        SPVM_OP_insert_child(compiler, (yyval.opval), (yyval.opval)->last, (yyvsp[0].opval));
      }
    }
#line 3139 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 51:
#line 333 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3157 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 64:
#line 363 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    { 
      (yyval.opval) = SPVM_OP_build_init_statement(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3165 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 65:
#line 369 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_version_decl(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3173 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 66:
#line 375 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_version_from(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3181 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 67:
#line 381 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      int32_t is_require = 0;
      SPVM_OP* op_name_class_alias = NULL;
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), op_name_class_alias, is_require);
    }
#line 3191 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 68:
#line 387 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      int32_t is_require = 0;
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), is_require);
    }
#line 3200 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 69:
#line 394 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, compiler->current_file, compiler->current_line);
      int32_t is_require = 1;
      (yyval.opval) = SPVM_OP_build_use(compiler, op_use, (yyvsp[0].opval), NULL, is_require);
    }
#line 3210 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 70:
#line 402 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_alias(compiler, op_use, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3219 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 71:
#line 409 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_allow(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3227 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 72:
#line 415 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_interface_statement(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3235 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 73:
#line 421 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), (yyvsp[-2].opval));
    }
#line 3243 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 74:
#line 427 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_enum_block;
    }
#line 3253 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 75:
#line 435 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3261 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 76:
#line 439 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3276 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 77:
#line 452 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3294 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 80:
#line 470 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_item(compiler, (yyvsp[0].opval), NULL);
    }
#line 3302 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 81:
#line 474 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_item(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3310 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 82:
#line 480 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class_var(compiler, (yyvsp[-7].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3318 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 83:
#line 486 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_field(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3326 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 84:
#line 492 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 3334 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 86:
#line 499 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_return_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      SPVM_OP* op_arg = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_accessor(compiler, (yyvsp[-1].opval), op_arg, (yyvsp[0].opval), op_return_type);
    }
#line 3344 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 87:
#line 507 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 3352 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 89:
#line 514 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_return_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      SPVM_OP* op_arg = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_accessor(compiler, (yyvsp[-1].opval), op_arg, (yyvsp[0].opval), op_return_type);
    }
#line 3362 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 90:
#line 520 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_return_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_accessor(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval), op_return_type);
    }
#line 3371 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 91:
#line 525 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_accessor(compiler, (yyvsp[-6].opval), (yyvsp[-2].opval), (yyvsp[0].opval), (yyvsp[-4].opval));
    }
#line 3379 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 92:
#line 529 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_arg = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      SPVM_OP* op_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_accessor(compiler, (yyvsp[-2].opval), op_arg, op_block, (yyvsp[0].opval));
    }
#line 3389 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 93:
#line 537 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-8].opval), (yyvsp[0].opval));
     }
#line 3397 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 94:
#line 541 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-8].opval), NULL);
     }
#line 3405 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 95:
#line 545 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-6].opval), NULL, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-7].opval), (yyvsp[0].opval));
     }
#line 3413 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 96:
#line 549 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-6].opval), NULL, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-7].opval), NULL);
     }
#line 3421 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 97:
#line 555 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-6].opval), NULL, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-7].opval), (yyvsp[0].opval));
     }
#line 3429 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 98:
#line 559 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3448 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 99:
#line 576 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3456 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 100:
#line 580 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3471 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 101:
#line 593 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3489 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 104:
#line 611 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[-2].opval), (yyvsp[0].opval), NULL, NULL);
    }
#line 3497 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 105:
#line 615 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), NULL, (yyvsp[0].opval));
    }
#line 3505 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 106:
#line 621 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3523 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 109:
#line 639 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_anon_method_field(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 3531 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 110:
#line 643 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_anon_method_field(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3539 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 111:
#line 647 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_FIELD, (yyvsp[-3].opval)->file, (yyvsp[-3].opval)->line);
      
      (yyval.opval) = SPVM_OP_build_anon_method_field(compiler, op_field, NULL, (yyvsp[-1].opval), (yyvsp[0].opval), (yyvsp[-3].opval));
    }
#line 3549 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 112:
#line 653 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_FIELD, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      
      (yyval.opval) = SPVM_OP_build_anon_method_field(compiler, op_field, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3559 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 113:
#line 661 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3567 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 114:
#line 665 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3582 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 115:
#line 678 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3600 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 117:
#line 695 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3608 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 118:
#line 699 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3623 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 119:
#line 712 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3641 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 134:
#line 742 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[-1].opval), NULL);
    }
#line 3649 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 135:
#line 746 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3657 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 137:
#line 751 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_operator_statement(compiler, (yyvsp[-1].opval));
    }
#line 3665 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 139:
#line 756 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
#line 3673 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 140:
#line 762 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 3681 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 141:
#line 766 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[0].opval), NULL, NULL);
    }
#line 3689 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 142:
#line 770 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-2].opval), (yyvsp[0].opval), (yyvsp[-1].opval));
    }
#line 3697 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 143:
#line 774 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-1].opval), NULL, (yyvsp[0].opval));
    }
#line 3705 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 144:
#line 778 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-3].opval), (yyvsp[0].opval), (yyvsp[-2].opval));
    }
#line 3713 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 146:
#line 785 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_print(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3721 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 147:
#line 789 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_print(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3729 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 150:
#line 795 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_make_read_only(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3737 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 151:
#line 799 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enable_options(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3745 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 152:
#line 803 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_disable_options(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3753 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 155:
#line 811 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[-8].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3761 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 156:
#line 817 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_foreach_statement(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3769 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 157:
#line 821 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_foreach_statement(compiler, (yyvsp[-8].opval), (yyvsp[-7].opval), (yyvsp[-3].opval), (yyvsp[0].opval));
    }
#line 3777 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 158:
#line 827 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3785 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 159:
#line 833 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3793 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 160:
#line 839 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[-1].opval), NULL);
    }
#line 3802 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 161:
#line 844 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3811 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 162:
#line 851 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3819 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 163:
#line 855 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3834 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 164:
#line 868 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3852 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 165:
#line 882 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 3860 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 166:
#line 888 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3868 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 167:
#line 892 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), NULL);
    }
#line 3876 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 168:
#line 898 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3884 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 169:
#line 902 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[-1].opval), NULL);
    }
#line 3892 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 170:
#line 908 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->current_file, compiler->current_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[-2].opval), (yyvsp[0].opval), NULL);
    }
#line 3902 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 171:
#line 914 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->current_file, compiler->current_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3912 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 172:
#line 921 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval), 0);
      
      // condition part has own scope
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    }
#line 3926 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 173:
#line 931 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      op_if = SPVM_OP_build_if_statement(compiler, op_if, (yyvsp[-3].opval), (yyvsp[0].opval), (yyvsp[-1].opval), 0);
      
      // condition part has own scope
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    }
#line 3941 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 174:
#line 944 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
#line 3949 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 175:
#line 948 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 3957 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 176:
#line 952 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, op_if, (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval), 0);
    }
#line 3966 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 177:
#line 959 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_block;
    }
#line 3976 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 178:
#line 967 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3984 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 179:
#line 973 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var_decl(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval), NULL);
    }
#line 3992 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 180:
#line 977 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var_decl(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL, NULL);
    }
#line 4000 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 181:
#line 983 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[0].opval));
    }
#line 4008 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 182:
#line 989 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 4016 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 183:
#line 993 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 4031 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1006 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
#line 4039 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1022 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_true(compiler, (yyvsp[0].opval));
    }
#line 4047 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1026 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_false(compiler, (yyvsp[0].opval));
    }
#line 4055 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1038 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_basic_type_id(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4063 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1052 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 4083 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1068 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_operator = (yyvsp[-5].opval)->first;
      SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, compiler->current_file, compiler->current_line);
      
      SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, (yyvsp[-5].opval));
      SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, (yyvsp[-3].opval));
      SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, (yyvsp[-1].opval));
      
      (yyval.opval) = op_sequence;
    }
#line 4098 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1081 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 4116 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1095 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[-1].opval);
    }
#line 4124 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1099 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 4132 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1105 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, operator, (yyvsp[0].opval));
    }
#line 4141 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1110 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MINUS, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, op_negate, (yyvsp[0].opval));
    }
#line 4150 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1115 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4158 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1119 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4166 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1123 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4174 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1127 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4182 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1131 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4190 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1135 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op_var(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4198 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1139 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op_var(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4206 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1143 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4214 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1147 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4222 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1151 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4230 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1156 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4238 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1160 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4246 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1166 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[0].opval));
    }
#line 4255 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1171 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[-1].opval));
    }
#line 4264 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1176 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[0].opval));
    }
#line 4273 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1181 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[-1].opval));
    }
#line 4282 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1188 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, operator, (yyvsp[0].opval));
    }
#line 4291 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1193 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, operator, (yyvsp[-1].opval));
    }
#line 4300 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1200 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, operator, (yyvsp[0].opval));
    }
#line 4309 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1205 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, operator, (yyvsp[-1].opval));
    }
#line 4318 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1220 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, operator, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4327 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1225 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, operator, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4336 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1230 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MULTIPLY, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, operator, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4345 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1235 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4353 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1239 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4361 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1243 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4369 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1247 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4377 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1251 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4385 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1255 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4393 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1261 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* ternary_op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TERNARY_OP, (yyvsp[-4].opval)->file, (yyvsp[-4].opval)->line);
      (yyval.opval) = SPVM_OP_build_ternary_op(compiler, ternary_op, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4402 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1268 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4410 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1272 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4418 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1276 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4426 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1280 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4434 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1286 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4442 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1290 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4450 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1294 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4458 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1298 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4466 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1302 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4474 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1306 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4482 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1310 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4490 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1314 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4498 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1318 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4506 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1322 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4514 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1326 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4522 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1330 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4530 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1334 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4538 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 275:
#line 1338 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4546 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1344 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4554 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1350 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_logical_or(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4562 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1354 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_logical_and(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4570 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1358 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_logical_not(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4578 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 280:
#line 1364 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_defined_or(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4586 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1370 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_type_check(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4594 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1374 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_type_check(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4602 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1378 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_type_check(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4610 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 284:
#line 1382 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_type_check(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4618 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1386 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_type_check(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4626 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1392 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type_cast = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      (yyval.opval) = SPVM_OP_build_type_cast(compiler, op_type_cast, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4635 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 287:
#line 1397 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type_cast = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_type_cast(compiler, op_type_cast, (yyvsp[-1].opval), (yyvsp[-4].opval));
    }
#line 4644 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1404 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_can(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4652 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 289:
#line 1408 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_can(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4660 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1414 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4668 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 291:
#line 1418 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_special_assign(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4676 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 292:
#line 1424 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 4684 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1428 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_length = (yyvsp[0].opval)->last;
      SPVM_OP_cut_op(compiler, (yyvsp[0].opval)->last);
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), op_length);
    }
#line 4694 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 294:
#line 1434 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_anon_method(compiler, (yyvsp[0].opval));
    }
#line 4702 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 295:
#line 1440 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->current_file, compiler->current_line);
      int32_t is_key_values = 0;
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[-1].opval), is_key_values);
    }
#line 4712 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 296:
#line 1446 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->current_file, compiler->current_line);
      int32_t is_key_values = 1;
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[-1].opval), is_key_values);
    }
#line 4722 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 297:
#line 1452 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->current_file, compiler->current_line);
      int32_t is_key_values = 1;
      SPVM_OP* op_list_elements = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, op_list_elements, is_key_values);
    }
#line 4733 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 298:
#line 1461 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4742 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 299:
#line 1466 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, (yyvsp[-1].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-1].opval), (yyvsp[0].opval), op_operators);
    }
#line 4752 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 300:
#line 1472 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4761 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 301:
#line 1477 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-2].opval), (yyvsp[0].opval), op_operators);
    }
#line 4771 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 302:
#line 1483 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4780 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 303:
#line 1488 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-2].opval), (yyvsp[0].opval), op_operators);
    }
#line 4790 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 304:
#line 1494 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_method_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[-3].opval)->file, (yyvsp[-3].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-4].opval), op_method_name, (yyvsp[-1].opval));
    }
#line 4800 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 305:
#line 1502 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ELEMENT_ACCESS, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_element_access(compiler, op_array_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 4809 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 306:
#line 1507 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ELEMENT_ACCESS, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_element_access(compiler, op_array_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4818 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 307:
#line 1512 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ELEMENT_ACCESS, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_element_access(compiler, op_array_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4827 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 308:
#line 1519 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 4836 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 309:
#line 1524 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4845 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 310:
#line 1529 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_access = (yyvsp[-3].opval);
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_field_access(compiler, op_field_access, op_array_access, (yyvsp[-1].opval));
    }
#line 4855 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 311:
#line 1537 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 4865 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 312:
#line 1545 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_unweaken_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 4875 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 313:
#line 1553 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_isweak_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 4885 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 314:
#line 1561 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_warn(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4893 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 315:
#line 1565 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_warn(compiler, (yyvsp[0].opval), NULL);
    }
#line 4901 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 316:
#line 1571 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_copy_fields(compiler, (yyvsp[-5].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4909 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 317:
#line 1577 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_exists(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 4919 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 318:
#line 1585 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_delete(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 4929 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;


#line 4933 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
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
#line 1591 "yacc/spvm_yacc.y" /* yacc.c:1906  */

