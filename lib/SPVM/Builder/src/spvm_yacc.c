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
    MAKE_FIXED_LENGTH = 275,
    INTERFACE = 276,
    EVAL_ERROR_ID = 277,
    ARGS_WIDTH = 278,
    VERSION_DECL = 279,
    VERSION_FROM = 280,
    IF = 281,
    UNLESS = 282,
    ELSIF = 283,
    ELSE = 284,
    FOR = 285,
    WHILE = 286,
    LAST = 287,
    NEXT = 288,
    SWITCH = 289,
    CASE = 290,
    DEFAULT = 291,
    BREAK = 292,
    EVAL = 293,
    SYMBOL_NAME = 294,
    VAR_NAME = 295,
    CONSTANT = 296,
    EXCEPTION_VAR = 297,
    COPY_FIELDS = 298,
    EXISTS = 299,
    DELETE = 300,
    UNDEF = 301,
    VOID = 302,
    BYTE = 303,
    SHORT = 304,
    INT = 305,
    LONG = 306,
    FLOAT = 307,
    DOUBLE = 308,
    STRING = 309,
    OBJECT = 310,
    ELEMENT = 311,
    TRUE = 312,
    FALSE = 313,
    END_OF_FILE = 314,
    RW = 315,
    RO = 316,
    WO = 317,
    INIT = 318,
    NEW = 319,
    OF = 320,
    BASIC_TYPE_ID = 321,
    EXTENDS = 322,
    SUPER = 323,
    SET_LENGTH = 324,
    SET_CAPACITY = 325,
    RETURN = 326,
    WEAKEN = 327,
    DIE = 328,
    WARN = 329,
    WARN_LEVEL = 330,
    DIAG = 331,
    PRINT = 332,
    SAY = 333,
    STDERR = 334,
    OUTMOST_CLASS_NAME = 335,
    UNWEAKEN = 336,
    ENABLE_OPTIONS = 337,
    DISABLE_OPTIONS = 338,
    FATCAMMA = 339,
    ASSIGN = 340,
    SPECIAL_ASSIGN = 341,
    LOGICAL_OR = 342,
    DEFINED_OR = 343,
    LOGICAL_AND = 344,
    BIT_OR = 345,
    BIT_XOR = 346,
    BIT_AND = 347,
    NUMEQ = 348,
    NUMNE = 349,
    STREQ = 350,
    STRNE = 351,
    NUMGT = 352,
    NUMGE = 353,
    NUMLT = 354,
    NUMLE = 355,
    STRGT = 356,
    STRGE = 357,
    STRLT = 358,
    STRLE = 359,
    ISA = 360,
    ISA_ERROR = 361,
    IS_TYPE = 362,
    IS_ERROR = 363,
    IS_COMPILE_TYPE = 364,
    NUMERIC_CMP = 365,
    STRING_CMP = 366,
    CAN = 367,
    SHIFT = 368,
    DIVIDE = 369,
    DIVIDE_UNSIGNED_INT = 370,
    DIVIDE_UNSIGNED_LONG = 371,
    MODULO = 372,
    MODULO_UNSIGNED_INT = 373,
    MODULO_UNSIGNED_LONG = 374,
    LOGICAL_NOT = 375,
    BIT_NOT = 376,
    REFERENCE = 377,
    DEREFERENCE = 378,
    PLUS = 379,
    MINUS = 380,
    CONVERT = 381,
    SCALAR = 382,
    STRING_LENGTH = 383,
    ISWEAK = 384,
    TYPE_NAME = 385,
    COMPILE_TYPE_NAME = 386,
    DUMP = 387,
    NEW_STRING_LEN = 388,
    IS_READ_ONLY = 389,
    IS_FIXED_LENGTH = 390,
    COPY = 391,
    ADDRESS = 392,
    IS_OPTIONS = 393,
    CAPACITY = 394,
    CALLER = 395,
    INC = 396,
    DEC = 397,
    ARROW = 398
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_LIB_SPVM_BUILDER_INCLUDE_SPVM_YACC_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 277 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:358  */

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
#define YYFINAL  229
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   7246

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  159
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  109
/* YYNRULES -- Number of rules.  */
#define YYNRULES  338
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  678

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   398

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
     153,   152,   120,   117,    84,   118,   119,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    89,   157,
       2,     2,     2,    88,   129,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   154,     2,   156,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   155,     2,   158,     2,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    85,
      86,    87,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   121,
     122,   123,   124,   125,   126,   127,   128,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    82,    82,    85,    88,    91,    94,    95,    98,    99,
     100,   101,   102,   108,   114,   120,   124,   130,   136,   142,
     148,   154,   160,   165,   173,   179,   183,   187,   194,   198,
     204,   205,   209,   213,   220,   223,   236,   250,   253,   257,
     261,   265,   269,   276,   279,   283,   286,   292,   301,   304,
     316,   330,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   346,   352,   358,   364,   372,   373,   380,
     388,   395,   401,   407,   413,   422,   425,   438,   452,   453,
     456,   460,   466,   472,   479,   482,   485,   494,   497,   500,
     506,   511,   515,   523,   527,   531,   535,   541,   545,   563,
     566,   579,   593,   594,   597,   601,   607,   621,   622,   625,
     629,   633,   639,   648,   651,   664,   678,   682,   685,   698,
     712,   715,   716,   717,   718,   719,   720,   721,   722,   723,
     724,   725,   726,   727,   728,   732,   736,   737,   741,   742,
     746,   749,   753,   757,   761,   765,   771,   772,   773,   777,
     781,   785,   789,   790,   791,   795,   799,   803,   807,   808,
     809,   813,   819,   825,   829,   835,   841,   847,   852,   860,
     863,   876,   890,   896,   900,   906,   910,   916,   922,   929,
     939,   953,   956,   960,   967,   975,   981,   985,   991,   998,
    1001,  1015,  1018,  1021,  1022,  1023,  1024,  1025,  1026,  1027,
    1028,  1029,  1030,  1034,  1038,  1039,  1040,  1041,  1042,  1043,
    1044,  1045,  1046,  1050,  1051,  1052,  1053,  1054,  1055,  1056,
    1057,  1058,  1059,  1062,  1078,  1091,  1105,  1109,  1115,  1120,
    1125,  1129,  1133,  1137,  1141,  1145,  1149,  1153,  1157,  1161,
    1165,  1169,  1170,  1174,  1178,  1184,  1189,  1194,  1199,  1206,
    1211,  1218,  1223,  1230,  1231,  1232,  1233,  1234,  1235,  1238,
    1243,  1248,  1253,  1257,  1261,  1265,  1269,  1273,  1279,  1286,
    1290,  1294,  1298,  1304,  1308,  1312,  1316,  1320,  1324,  1328,
    1332,  1336,  1340,  1344,  1348,  1352,  1356,  1362,  1368,  1372,
    1376,  1382,  1388,  1392,  1396,  1400,  1404,  1410,  1415,  1422,
    1426,  1432,  1436,  1442,  1446,  1452,  1458,  1464,  1470,  1479,
    1484,  1490,  1495,  1501,  1506,  1512,  1520,  1525,  1530,  1535,
    1542,  1547,  1552,  1557,  1564,  1569,  1574,  1579,  1586,  1594,
    1602,  1610,  1614,  1620,  1626,  1632,  1640,  1648,  1652
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CLASS", "HAS", "GET", "SET", "METHOD",
  "OUR", "ENUM", "MY", "USE", "AS", "REQUIRE", "ALIAS", "ALLOW",
  "OUTMOST_CLASS", "MUTABLE", "ATTRIBUTE", "MAKE_READ_ONLY",
  "MAKE_FIXED_LENGTH", "INTERFACE", "EVAL_ERROR_ID", "ARGS_WIDTH",
  "VERSION_DECL", "VERSION_FROM", "IF", "UNLESS", "ELSIF", "ELSE", "FOR",
  "WHILE", "LAST", "NEXT", "SWITCH", "CASE", "DEFAULT", "BREAK", "EVAL",
  "SYMBOL_NAME", "VAR_NAME", "CONSTANT", "EXCEPTION_VAR", "COPY_FIELDS",
  "EXISTS", "DELETE", "UNDEF", "VOID", "BYTE", "SHORT", "INT", "LONG",
  "FLOAT", "DOUBLE", "STRING", "OBJECT", "ELEMENT", "TRUE", "FALSE",
  "END_OF_FILE", "RW", "RO", "WO", "INIT", "NEW", "OF", "BASIC_TYPE_ID",
  "EXTENDS", "SUPER", "SET_LENGTH", "SET_CAPACITY", "RETURN", "WEAKEN",
  "DIE", "WARN", "WARN_LEVEL", "DIAG", "PRINT", "SAY", "STDERR",
  "OUTMOST_CLASS_NAME", "UNWEAKEN", "ENABLE_OPTIONS", "DISABLE_OPTIONS",
  "','", "FATCAMMA", "ASSIGN", "SPECIAL_ASSIGN", "'?'", "':'",
  "LOGICAL_OR", "DEFINED_OR", "LOGICAL_AND", "BIT_OR", "BIT_XOR",
  "BIT_AND", "NUMEQ", "NUMNE", "STREQ", "STRNE", "NUMGT", "NUMGE", "NUMLT",
  "NUMLE", "STRGT", "STRGE", "STRLT", "STRLE", "ISA", "ISA_ERROR",
  "IS_TYPE", "IS_ERROR", "IS_COMPILE_TYPE", "NUMERIC_CMP", "STRING_CMP",
  "CAN", "SHIFT", "'+'", "'-'", "'.'", "'*'", "DIVIDE",
  "DIVIDE_UNSIGNED_INT", "DIVIDE_UNSIGNED_LONG", "MODULO",
  "MODULO_UNSIGNED_INT", "MODULO_UNSIGNED_LONG", "LOGICAL_NOT", "BIT_NOT",
  "'@'", "REFERENCE", "DEREFERENCE", "PLUS", "MINUS", "CONVERT", "SCALAR",
  "STRING_LENGTH", "ISWEAK", "TYPE_NAME", "COMPILE_TYPE_NAME", "DUMP",
  "NEW_STRING_LEN", "IS_READ_ONLY", "IS_FIXED_LENGTH", "COPY", "ADDRESS",
  "IS_OPTIONS", "CAPACITY", "CALLER", "INC", "DEC", "ARROW", "')'", "'('",
  "'['", "'{'", "']'", "';'", "'}'", "$accept", "grammar", "field_name",
  "method_name", "class_name", "runtime_type", "type", "union_type",
  "generic_type", "basic_type", "ref_type", "array_type",
  "array_type_with_length", "return_type", "opt_classes", "classes",
  "class", "opt_basic_type", "opt_extends", "class_block",
  "opt_definitions", "definitions", "definition", "init_statement",
  "version_decl", "version_from", "use_without_alias", "use", "require",
  "class_alias", "allow", "interface", "enumeration", "enumeration_block",
  "opt_enumeration_items", "enumeration_items", "enumeration_item", "our",
  "has", "opt_getter", "getter", "opt_setter", "setter", "method",
  "anon_method", "opt_args", "args", "arg", "anon_method_fields",
  "anon_method_field", "opt_attributes", "attributes", "opt_statements",
  "statements", "statement", "die", "void_return_operator",
  "for_statement", "foreach_statement", "while_statement",
  "switch_statement", "switch_block", "opt_case_statements",
  "case_statements", "case_statement", "default_statement",
  "if_require_statement", "if_statement", "else_statement", "block",
  "eval_block", "var_decl", "var", "opt_operators", "opt_operator",
  "operator", "sequential", "operators", "unary_operator", "array_length",
  "inc", "dec", "binary_operator", "arithmetic_operator",
  "ternary_operator", "bit_operator", "comparison_operator",
  "string_concatenation", "logical_operator", "defined_or", "type_check",
  "type_cast", "can", "assign", "new", "array_init", "call_method",
  "array_element_access", "field_access", "hash_value_access",
  "weaken_field", "unweaken_field", "isweak_field", "warn", "warn_level",
  "copy_fields", "exists", "delete", "caller", YY_NULLPTR
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
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,    44,   339,   340,   341,    63,    58,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,   363,   364,   365,   366,   367,   368,    43,    45,    46,
      42,   369,   370,   371,   372,   373,   374,   375,   376,    64,
     377,   378,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   389,   390,   391,   392,   393,   394,   395,   396,
     397,   398,    41,    40,    91,   123,    93,    59,   125
};
# endif

#define YYPACT_NINF -549

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-549)))

#define YYTABLE_NINF -333

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-333)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     946,   187,    25,   187,    33,  -549,  4118,  4118,  -549,  -549,
     -73,   -60,    11,   -57,   -71,   -37,   -12,  4118,    19,   -22,
     -11,  -549,  -549,  -549,  -549,  4118,    25,    25,  -549,  -549,
    -549,  -549,  -549,  -549,  -549,  -549,  -549,  -549,  -549,   187,
     217,    -1,    18,  2276,    25,  2418,  2560,  4118,  3267,  3408,
    -549,    25,  4118,  4118,  4118,  4118,  4118,  4118,  4259,  4118,
      25,    -3,  4118,    25,  4118,  4118,  4118,  4118,  4118,  4118,
    4118,  4118,  4118,  4118,  2082,  4118,  4118,  3549,   696,  1345,
    -549,   168,    38,  -549,   946,  -549,  -549,  -549,   184,   205,
     166,  1197,  -549,    67,    71,  -549,  -549,  -549,  -549,  -549,
    -549,  -549,  -549,  -549,  -549,  -549,  -549,  5235,  -549,  -549,
    -549,  -549,  -549,  -549,  -549,  -549,  -549,  -549,  -549,  -549,
    -549,  -549,  -549,  -549,  -549,  -549,  -549,  -549,  -100,   -25,
       7,  -549,  -549,  -549,  -549,  -549,  -549,  -549,  -549,  -549,
    -549,   162,   141,    76,    78,  1784,  6918,  6918,  3695,  4118,
    2702,    90,  4118,  -549,  -549,  4118,  6786,   -11,  -549,  1494,
    -549,  5777,    93,    97,   -67,    95,  -549,   217,  -549,   160,
    -549,  -549,   -14,  -549,   103,  4118,  4118,  -549,  5303,    99,
    2134,  5845,  6918,  5913,  4118,  6918,  4118,  6918,   107,  6918,
    6918,    34,    34,    34,    34,  1784,    34,    34,  -549,  4400,
      34,   113,    34,    34,    34,    34,    34,    34,    34,    34,
      34,    34,    34,    37,    37,   -45,   -29,  6918,   -34,   234,
     -53,  -549,   185,   129,   202,  -549,   131,  5235,   -47,  -549,
     248,  -549,   203,  -549,  -549,  -549,  -549,  -549,  4118,  4118,
    4118,  4118,  4118,  4118,  4118,  4118,  4118,  4118,  4118,  4118,
    4118,  4118,  4118,  4118,  4118,  4118,  4118,  4118,  4118,   187,
     187,   187,   187,   217,  4118,  4118,    42,  4118,  4118,  4118,
    4118,  4118,  4118,  4118,  4118,  4118,  4118,  4118,  -549,  -549,
     -21,  -549,  4118,  4541,  4118,  4541,  4118,  4541,   187,   -42,
     217,  -549,  3836,   187,   139,  6183,  6250,   147,  6918,   176,
    6317,  6384,   -11,  -549,  4118,   154,   155,   194,  2844,  2985,
     160,   217,   217,  -549,   158,   159,  5981,  6049,  -549,   161,
    6918,  4118,  4118,  6918,  6918,   163,  4752,  1784,    34,   164,
    4118,  1643,  -549,  -549,   228,    60,   302,   302,  -549,  1933,
    -549,  -549,  -549,   169,   126,  6918,  6918,  6852,   260,   260,
    1045,  7039,  7039,   441,  7095,  7095,  7095,  7095,    96,    96,
      96,    96,    96,    96,    96,    96,  -549,   -35,  -549,  -549,
    -549,  -549,    96,    96,  -549,  -549,   177,   157,   157,   157,
      34,    34,    34,    34,    34,    34,    34,  3126,  4118,  4541,
     170,  5371,   173,   171,  4821,  5438,   172,  4890,  5505,   174,
    4959,  -549,   302,     8,   262,   272,   160,   182,  -549,   -11,
     -11,   -11,  2702,  4682,   -11,   180,  -549,  6117,   234,   234,
     218,  -549,  5572,  -549,  5639,  -549,   160,  4118,  4118,   234,
    6918,  6918,   234,  -549,  5028,   234,    34,   183,   254,  6918,
     302,  -549,   185,   332,   217,  3836,  -549,   186,   160,   188,
    4118,   -31,   190,  5706,   189,  5097,  3836,  -549,  -549,  -549,
    -549,  -549,  -549,  -549,  -549,  -549,    -7,   234,   303,   187,
     187,   187,   187,   304,   187,   -11,   191,    74,  -549,  -549,
    -549,  -549,  -549,  -549,  -549,  -549,  -549,  -549,  -549,   193,
    -549,   146,  -549,  -549,  -549,   317,   165,   165,   231,  1784,
    6451,  -549,   313,  -549,   217,   232,   236,  -549,  -549,  -549,
    6518,  6585,   237,   239,  -549,   240,  4118,  4118,   217,   300,
     -30,   247,   244,    25,  6982,  -549,  -549,  -549,  -549,  -549,
     249,   343,   344,   315,   316,    15,   394,   250,   255,   256,
     257,  -549,  -549,  -549,  -549,     5,   261,   -11,   264,   -11,
    -549,  -549,  3977,  5166,   -11,   -16,   313,  -549,   160,  -549,
    -549,  -549,  -549,  -549,  -549,  -549,  6652,   -27,   126,  4118,
    -549,  -549,   263,   334,  -549,   330,  -549,  -549,  -549,   302,
     302,   381,   381,  -549,  -549,  -549,  -549,   126,   333,   248,
    -549,  -549,  4118,  -549,   269,   271,  -549,  -549,   266,  -549,
    -549,  4118,   273,  6918,   -11,    25,   217,   217,   217,  -549,
     268,   274,   275,   126,   346,   276,   345,  -549,  6719,   -11,
     -11,  -549,  6918,    25,  -549,  -549,    52,    23,    23,  -549,
    -549,    25,   277,   392,  -549,   248,   -11,  -549,  -549,   283,
    4118,   -11,   430,  -549,   430,   285,    25,  -549,  -549,   165,
     -11,  6918,  -549,   -51,  -549,  -549,   281,     1,   287,  -549,
    -549,   126,    25,  -549,  -549,  -549,  -549,    35,   288,   290,
    -549,  -549,    25,   -11,   291,  -549,   -11,  -549
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      34,    43,     0,     0,     0,   116,   113,   113,   200,   201,
       0,     0,     0,     0,     0,     0,     0,   113,     0,     0,
       0,    15,   188,   195,   194,   113,     0,     0,   196,    16,
      17,    18,    19,    20,    21,    23,    22,   202,   203,     0,
       0,     0,     0,   113,     0,   113,   113,   113,   113,   113,
     204,     0,   113,   113,   113,   113,   113,   113,   113,   113,
       0,     0,   113,     0,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   337,   113,   113,   113,   113,   113,
     139,     0,     0,     2,    35,    37,   140,   305,     0,   114,
       0,   118,   120,     0,     0,   122,   123,   124,   126,   127,
     128,   130,   121,   125,   129,   199,   193,     0,   220,   205,
     241,   209,   210,   206,   253,   207,   254,   255,   256,   257,
     258,   211,   197,   213,   208,   198,   214,   219,   215,   216,
     217,   152,   153,   218,   146,   147,   158,   221,   159,   222,
      44,    45,   187,     0,   310,   113,   154,   155,   113,   113,
     113,     0,   113,   131,   132,   113,     0,   176,   133,   113,
     185,     0,     0,     0,   303,     0,   304,     0,     8,   212,
      10,    11,     6,     9,     7,   113,   113,   134,     0,     0,
     113,   141,   331,     0,   113,   148,   113,   150,     0,   156,
     157,   228,   229,   290,   230,   113,   245,   236,   235,   113,
     233,     0,   231,   232,   234,   237,   239,   240,   238,   242,
     243,   244,   338,   249,   251,     0,     6,   227,     0,     0,
       0,   108,   193,     0,   190,   308,     0,   227,     0,     1,
       0,    36,     0,   115,    42,   119,   136,   138,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,     0,
       0,     0,     0,     0,   113,   113,     0,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   250,   252,
       0,   137,   113,   113,   113,   113,   113,   113,     0,     0,
       0,    66,   113,     0,     0,     0,     0,     0,   192,     0,
       0,     0,   174,   175,   113,     0,     0,     0,   113,   113,
      12,     0,     0,    24,     0,     0,     0,     0,   135,     0,
     143,   113,   113,   149,   151,     0,   227,   113,   247,     0,
     113,   226,   223,     3,     0,   107,   113,   113,   306,   226,
     184,   307,     4,   312,     0,   301,   302,     0,   288,   291,
     289,   271,   269,   270,   273,   274,   280,   281,   275,   276,
     277,   278,   282,   283,   284,   285,   292,     6,   293,   294,
     295,   296,   279,   286,   300,   299,   272,   259,   260,   287,
     261,   262,   263,   264,   265,   266,   267,   113,   113,   113,
     314,     0,     3,     0,     0,     0,     0,     0,     0,     0,
       0,    46,   113,   113,     0,     0,   186,     0,    69,     0,
       0,     0,   113,   113,     0,     0,   173,     0,     0,     0,
       0,    25,     0,    26,     0,    13,    14,   113,   113,     0,
     145,   333,     0,   246,   227,     0,   297,     0,     0,   225,
     113,   106,     0,     0,     0,   113,    31,    32,    30,     0,
     113,     0,     0,     0,     0,     0,   113,   317,   321,   325,
     318,   322,   326,   319,   323,   327,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   113,    51,    58,
      52,    53,    67,    54,    55,    56,    57,    59,    60,     0,
      62,     0,    40,    38,   309,   177,   181,   181,     0,   113,
       0,   165,   169,   166,     0,     0,     0,    27,    28,    29,
       0,     0,     0,     0,   248,     0,   113,   113,     0,     0,
     111,     0,     0,    99,   268,   298,   315,   316,   320,   324,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    63,    47,    50,    61,     0,     0,     0,     0,     0,
     179,   180,   113,   227,     0,     0,   170,   172,   334,   335,
     336,   160,   161,   328,   329,   330,     0,   109,     0,   113,
     311,    33,     0,   100,   103,     0,   313,    41,    39,   113,
     113,     0,     0,    71,    72,    64,    65,     0,     0,    75,
      73,   178,   113,   182,     0,     0,   163,   167,     0,   171,
     224,   113,     0,   112,     0,   102,     0,     0,     0,     5,
       0,     0,     0,     0,    80,     0,    76,    79,     0,     0,
       0,   168,   110,    99,    97,   101,   104,    84,    84,    68,
      70,    99,     0,     0,    74,    78,     0,   162,   164,     0,
     113,     0,    87,    85,    87,     0,    99,    81,    77,   181,
       0,   105,    86,     0,    83,    88,     0,     0,     0,   183,
      98,     0,     0,    89,    82,    96,    95,     0,    92,     0,
      94,    93,     0,     0,     0,    90,     0,    91
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -549,  -549,  -272,  -220,  -142,  -192,   -36,  -549,  -549,     0,
    -549,   406,  -549,  -534,  -549,  -549,   362,  -549,  -549,   -19,
    -549,  -549,   -28,  -549,  -549,  -549,  -368,  -549,  -549,  -549,
    -549,  -549,  -549,  -549,  -549,  -549,  -187,  -549,  -549,  -178,
    -549,  -193,  -549,  -549,  -549,  -495,  -549,  -548,  -549,   117,
    -328,  -549,   -49,  -549,   363,  -549,  -549,  -549,  -549,  -549,
    -549,  -549,  -549,  -549,  -459,  -102,  -549,   124,  -480,   -18,
    -549,   444,    -2,  -286,  -398,   620,  -549,   -72,  -549,  -549,
    -549,  -549,  -549,  -549,  -549,  -549,  -549,  -549,  -549,  -549,
    -549,  -549,  -549,  -549,  -549,  -549,  -549,  -549,  -549,  -549,
    -549,  -549,  -549,  -549,  -549,  -549,  -549,  -549,  -549
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    81,   334,   614,   610,   168,   448,   170,   171,    82,
     173,   174,   166,   449,    83,    84,    85,   141,   289,   405,
     476,   477,   478,   479,   480,   481,    86,   483,   294,   484,
     485,   486,   487,   590,   615,   616,   617,   488,   489,   642,
     643,   654,   655,   490,    87,   572,   573,   574,   220,   221,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,   503,   555,   556,    99,   100,   101,   102,   550,   103,
     104,   105,   106,   223,   297,   217,   108,   224,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     142,   140,   160,   143,   169,   218,   407,   228,   443,   444,
     343,   393,   467,   396,   498,   399,   468,   551,   342,   469,
      18,     2,   470,   471,   162,   163,     5,   581,   641,   472,
     226,   335,   473,   474,   602,   482,   312,   339,   661,   164,
     172,   215,   179,   557,   342,   180,   375,   402,   311,   188,
     331,   312,   307,   612,   282,   283,   569,   625,   198,   601,
     390,   201,   311,   311,   219,    22,   311,   366,   368,   369,
     370,   475,   144,   228,   466,   491,   222,   216,   467,   632,
     148,   342,   468,   374,   307,   469,   153,   308,   470,   471,
     307,   313,     5,   149,   587,   472,   152,   599,   473,   474,
      22,   452,   662,   336,   159,   307,   313,   330,   157,   482,
     226,   341,   518,   403,   669,   404,   311,   454,   332,   314,
     154,   525,   230,   228,   674,   314,   199,   668,   639,   284,
     285,   310,   387,   388,   389,   158,   645,   475,   640,   303,
     314,   155,   597,   167,   159,   311,   505,   506,   403,   491,
     531,   658,   175,   545,   594,   546,   159,   512,   665,   521,
     513,   286,   287,   515,   150,    21,   -48,   172,   229,   659,
     530,   176,   291,   446,    29,    30,    31,    32,    33,    34,
      35,    36,   447,   278,   279,   280,  -333,  -333,   280,   230,
     159,   232,   670,   548,   549,   533,  -333,  -333,  -333,  -333,
    -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,
    -333,  -333,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   233,   236,   234,    21,   371,   237,   288,
     290,   292,   -49,   291,   167,    29,    30,    31,    32,    33,
      34,    35,    36,   299,   305,   278,   279,   280,   306,   309,
     319,   607,   608,   311,   406,   228,    21,   315,   325,   367,
     367,   367,   367,   172,   329,    29,    30,    31,    32,    33,
      34,    35,    36,   333,   337,   425,   426,   271,   272,   273,
     274,   275,   276,   277,   416,   338,   339,   342,   401,   340,
     172,   409,   344,   408,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   412,   413,   278,   279,   280,   418,
     419,   172,   172,   420,   421,   423,   429,   440,   432,   435,
       5,   492,   445,   456,   -15,   588,   278,   279,   280,   458,
     461,   493,   464,   442,   494,   502,   516,   507,   517,   519,
     522,   523,   526,   534,   172,   539,   547,   528,    17,   542,
     544,   451,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   216,   552,   568,
     559,   495,   496,   497,   560,   563,   501,   564,   565,   570,
     571,   576,   577,   578,   579,   580,   582,   583,   520,   278,
     279,   280,   584,   585,   586,   604,   589,   592,   605,   606,
     609,   619,   613,   620,   621,   629,   623,   228,   631,   635,
     646,   630,   633,   647,   634,   650,   653,   657,   664,   667,
     611,   672,   673,   676,   172,   165,   231,   532,   648,   543,
     644,   656,   441,   598,   235,   438,   151,   541,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   558,   535,
     536,   537,   538,     0,   540,     0,     0,     0,     0,     0,
       0,     0,   567,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   172,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   172,     0,
       0,   575,     0,     0,     0,     0,     0,     0,     0,   591,
       0,   593,     0,     0,     0,     0,   596,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   172,     0,
     626,   627,   628,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   624,   172,     0,     0,
     278,   279,   280,     0,     0,     0,     0,     0,     0,     0,
       0,   637,   638,   575,     0,     0,   172,   172,   172,     0,
       0,     0,     0,   172,     0,     0,     0,     0,   649,     0,
     107,   575,     0,   652,     0,     0,   146,   147,     0,   575,
       0,     0,   660,     0,     0,   663,     0,   156,     0,   666,
       0,     0,     0,     0,   575,   161,     0,     0,     0,   671,
       0,     0,     0,     0,     0,   675,     0,     0,   677,     0,
     575,   172,     0,   178,     0,   181,   182,   183,   185,   187,
     575,     0,   189,   190,   191,   192,   193,   194,   196,   197,
       0,     0,   200,     0,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,     0,     0,   227,
     219,     0,     0,     0,   107,     0,     2,     0,     0,     0,
       0,   107,     4,     0,     5,     0,     0,     0,     8,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    21,    22,    23,    24,     0,
      26,     0,    28,     0,    29,    30,    31,    32,    33,    34,
      35,    36,     0,    37,    38,     0,     0,     0,     0,     0,
      39,     0,    40,     0,     0,     0,     0,     0,   295,   296,
     298,     0,   300,     0,     0,   301,    50,     0,     0,   107,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   316,   317,     0,     0,     0,
     320,     0,     0,     0,   323,     0,   324,     0,     0,     0,
       0,     0,     0,    54,    55,   326,     0,     0,     0,   328,
       0,     0,     0,    56,    57,    58,    59,    60,     0,     0,
       0,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,     0,     0,    77,
      78,   145,  -189,     0,     0,     0,     0,     0,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,     0,
       0,     0,     0,     0,   372,   373,     0,   376,   377,   378,
     379,   380,   381,   382,   383,   384,   385,   386,     0,     0,
       0,     0,   391,   394,   395,   397,   398,   400,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   417,     0,     0,     0,   422,   424,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   430,   431,     0,     0,     0,     0,   434,     0,     1,
     436,   439,     0,  -113,     0,     0,     2,     3,     0,   439,
       0,     0,     4,     0,     5,     6,     7,     0,     8,     9,
       0,     0,    10,    11,     0,     0,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,     0,    29,    30,    31,    32,    33,    34,
      35,    36,     0,    37,    38,  -117,     0,     0,   453,   455,
      39,     0,    40,     0,     0,    41,    42,    43,    44,    45,
      46,    47,     0,    48,    49,     0,    50,    51,    52,    53,
       0,     0,   298,   500,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   510,   511,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    54,    55,     0,     0,     0,     0,     0,
     524,     0,     0,    56,    57,    58,    59,    60,     0,     0,
       0,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,     0,     0,    77,
      78,    79,     0,    80,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   553,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   295,   566,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   298,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   603,
       0,     0,     0,     0,   278,   279,   280,     0,     0,     0,
       0,     0,     0,     0,  -113,     0,     0,     2,     3,     0,
       0,     0,   618,     4,     0,     5,     6,     7,     0,     8,
       9,   622,     0,    10,    11,     0,     0,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,     0,    29,    30,    31,    32,    33,
      34,    35,    36,     0,    37,    38,     0,     0,     0,     0,
     651,    39,     0,    40,     0,     0,    41,    42,    43,    44,
      45,    46,    47,     0,    48,    49,     0,    50,    51,    52,
      53,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    54,    55,     0,     0,     0,     0,
       0,     0,     0,     0,    56,    57,    58,    59,    60,     0,
       0,     0,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,     0,     0,
      77,    78,    79,     0,    80,     2,     3,     0,     0,     0,
       0,     4,     0,     5,     6,     7,     0,     8,     9,     0,
       0,    10,    11,     0,     0,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,     0,    29,    30,    31,    32,    33,    34,    35,
      36,     0,    37,    38,     0,     0,     0,     0,     0,    39,
       0,    40,     0,     0,    41,    42,    43,    44,    45,    46,
      47,     0,    48,    49,     0,    50,    51,    52,    53,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    54,    55,     0,     0,     0,     0,     0,     0,
       0,     0,    56,    57,    58,    59,    60,     0,     0,     0,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,     0,     0,    77,    78,
      79,     0,    80,   225,     2,     3,     0,     0,     0,     0,
       4,     0,     5,     6,     7,     0,     8,     9,     0,     0,
      10,    11,     0,     0,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,     0,    29,    30,    31,    32,    33,    34,    35,    36,
       0,    37,    38,     0,     0,     0,     0,     0,    39,     0,
      40,     0,     0,    41,    42,    43,    44,    45,    46,    47,
       0,    48,    49,     0,    50,    51,    52,    53,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    54,    55,     0,     0,     0,     0,     0,     0,     0,
       0,    56,    57,    58,    59,    60,     0,     0,     0,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,     0,     0,    77,    78,    79,
    -113,    80,  -117,     2,     0,     0,     0,     0,     0,     4,
       0,     5,     0,     0,     0,     8,     9,     0,     0,   437,
      11,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,    22,    23,    24,     0,    26,     0,    28,
       0,    29,    30,    31,    32,    33,    34,    35,    36,     0,
      37,    38,     0,     0,     0,     0,     0,    39,     0,    40,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    50,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      54,    55,     0,     0,     0,     0,     0,     0,     0,     0,
      56,    57,    58,    59,    60,     0,     0,     0,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,     2,     0,    77,    78,   145,     0,
       4,     0,     5,     0,     0,     0,     8,     9,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,    22,    23,    24,     0,    26,     0,
      28,     0,    29,    30,    31,    32,    33,    34,    35,    36,
       0,    37,    38,     0,     0,     0,     0,     0,    39,     0,
      40,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    54,    55,     0,     0,     0,     0,     0,     0,     0,
       0,    56,    57,    58,    59,    60,     0,     0,     0,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,     0,     0,    77,    78,   145,
    -113,     0,   225,     2,     0,     0,     0,     0,     0,     4,
       0,     5,     0,     0,     0,     8,     9,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,    22,    23,    24,     0,    26,     0,    28,
       0,    29,    30,    31,    32,    33,    34,    35,    36,     0,
      37,    38,     0,     0,     0,     0,     0,    39,     0,    40,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    50,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      54,    55,     0,     0,     0,     0,     0,     0,     0,     0,
      56,    57,    58,    59,    60,     0,     0,     0,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,     0,     0,    77,    78,   145,  -113,
       0,     0,     2,     0,     0,     0,     0,     0,     4,     0,
       5,     0,     0,     0,     8,     9,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    21,    22,    23,    24,     0,    26,     0,    28,     0,
      29,    30,    31,    32,    33,    34,    35,    36,     0,    37,
      38,     0,     0,     0,     2,     0,    39,     0,    40,     0,
       4,     0,     5,     0,     0,     0,     8,     9,     0,     0,
       0,     0,    50,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,    22,    23,    24,     0,    26,     0,
      28,     0,    29,    30,    31,    32,    33,    34,    35,    36,
       0,    37,    38,     0,     0,     0,     0,     0,    39,     0,
      40,     0,     0,     0,     0,     0,     0,     0,     0,    56,
      57,    58,    59,    60,    50,     0,     0,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,     0,     0,    77,    78,   145,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    54,    55,     0,     0,     0,     0,     0,     0,     0,
       0,    56,    57,    58,    59,    60,     0,     0,     0,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,   230,     2,    77,    78,   145,
       0,  -144,     4,     0,     5,     0,     0,     0,     8,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    21,    22,    23,    24,     0,
      26,     0,    28,     0,    29,    30,    31,    32,    33,    34,
      35,    36,     0,    37,    38,     0,     0,     0,     0,     0,
      39,     0,    40,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    54,    55,     0,     0,     0,     0,     0,
       0,     0,     0,    56,    57,    58,    59,    60,     0,     0,
       0,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,     0,     2,    77,
      78,   145,     0,   177,     4,     0,     5,     0,     0,     0,
       8,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,    22,    23,
      24,     0,    26,     0,    28,     0,    29,    30,    31,    32,
      33,    34,    35,    36,     0,    37,    38,     0,     0,     0,
       0,     0,    39,     0,    40,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    54,    55,     0,     0,     0,
       0,     0,     0,     0,     0,    56,    57,    58,    59,    60,
       0,     0,     0,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,     0,
       2,    77,    78,   145,     0,  -142,     4,     0,     5,     0,
       0,     0,     8,     9,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    21,
      22,    23,    24,     0,    26,     0,    28,     0,    29,    30,
      31,    32,    33,    34,    35,    36,     0,    37,    38,     0,
       0,     0,     0,     0,    39,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    54,    55,     0,
       0,     0,     0,     0,     0,     0,     0,    56,    57,    58,
      59,    60,     0,     0,     0,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,     0,     2,    77,    78,   145,     0,  -332,     4,     0,
       5,     0,     0,     0,     8,     9,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    21,    22,    23,    24,     0,    26,     0,    28,     0,
      29,    30,    31,    32,    33,    34,    35,    36,     0,    37,
      38,     0,     0,     0,     0,     0,    39,     0,    40,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    54,
      55,     0,     0,     0,     0,     0,     0,     0,     0,    56,
      57,    58,    59,    60,     0,     0,     0,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,     0,     2,    77,    78,   145,     0,  -191,
       4,     0,     5,     0,     0,     0,     8,     9,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,    22,    23,    24,     0,    26,     0,
      28,     0,    29,    30,    31,    32,    33,    34,    35,    36,
       0,    37,    38,     0,     0,     0,     0,     0,    39,     0,
      40,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    54,    55,     0,     0,     0,     0,     0,     0,     0,
       0,    56,    57,    58,    59,    60,     0,     0,     0,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,     2,     0,    77,    78,   145,
     421,     4,     0,     5,     0,     0,     0,     8,     9,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,    22,    23,    24,     0,    26,
       0,    28,     0,    29,    30,    31,    32,    33,    34,    35,
      36,     0,    37,    38,     0,     0,     0,     0,     0,    39,
       0,    40,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    50,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    54,    55,     0,     0,     0,     0,     0,     0,
       0,     0,    56,    57,    58,    59,    60,     0,     0,     0,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,     2,     0,    77,    78,
     145,   423,     4,   167,     5,     0,     0,     0,     8,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    21,    22,    23,    24,     0,
      26,     0,    28,     0,    29,    30,    31,    32,    33,    34,
      35,    36,     0,    37,    38,     0,     0,     0,     0,     0,
      39,     0,    40,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    54,    55,     0,     0,     0,     0,     0,
       0,     0,     0,    56,    57,    58,    59,    60,     0,     0,
       0,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,     2,  -189,    77,
      78,   145,     0,     4,     0,     5,     0,     0,     0,     8,
       9,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,    22,    23,    24,
       0,    26,     0,    28,     0,    29,    30,    31,    32,    33,
      34,    35,    36,     0,    37,    38,     0,     0,     0,     0,
       0,    39,     0,    40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   184,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    54,    55,     0,     0,     0,     0,
       0,     0,     0,     0,    56,    57,    58,    59,    60,     0,
       0,     0,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,     2,     0,
      77,    78,   145,     0,     4,     0,     5,     0,     0,     0,
       8,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,    22,    23,
      24,     0,    26,     0,    28,     0,    29,    30,    31,    32,
      33,    34,    35,    36,     0,    37,    38,     0,     0,     0,
       0,     0,    39,     0,    40,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   186,    50,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    54,    55,     0,     0,     0,
       0,     0,     0,     0,     0,    56,    57,    58,    59,    60,
       0,     0,     0,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,     2,
       0,    77,    78,   145,     0,     4,   167,     5,     0,     0,
       0,     8,     9,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,    22,
      23,    24,     0,    26,     0,    28,     0,    29,    30,    31,
      32,    33,    34,    35,    36,     0,    37,    38,     0,     0,
       0,     0,     0,    39,     0,    40,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    50,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    54,    55,     0,     0,
       0,     0,     0,     0,     0,     0,    56,    57,    58,    59,
      60,     0,     0,     0,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
       0,     0,    77,    78,   145,     2,     0,     0,   293,     0,
       0,     4,     0,     5,     0,     0,     0,     8,     9,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,    22,    23,    24,     0,    26,
       0,    28,     0,    29,    30,    31,    32,    33,    34,    35,
      36,     0,    37,    38,     0,     0,     0,     0,     0,    39,
       0,    40,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    50,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    54,    55,     0,     0,     0,     0,     0,     0,
       0,     0,    56,    57,    58,    59,    60,     0,     0,     0,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,     2,     0,    77,    78,
     145,     0,     4,     0,     5,     0,     0,     0,     8,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    21,    22,    23,    24,     0,
      26,     0,    28,     0,    29,    30,    31,    32,    33,    34,
      35,    36,     0,    37,    38,     0,     0,     0,     0,     0,
      39,     0,    40,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    54,    55,     0,     0,     0,     0,     0,
       0,     0,     0,    56,    57,    58,    59,    60,     0,     0,
       0,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,     2,  -189,    77,
      78,   145,     0,     4,     0,     5,     0,     0,     0,     8,
       9,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,    22,    23,    24,
       0,    26,     0,    28,     0,    29,    30,    31,    32,    33,
      34,    35,    36,     0,    37,    38,     0,     0,     0,     0,
       0,    39,     0,    40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    54,    55,     0,     0,     0,     0,
       0,     0,     0,     0,    56,    57,    58,    59,    60,     0,
       0,     0,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,     2,  -191,
      77,    78,   145,     0,     4,     0,     5,     0,     0,     0,
       8,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,    22,    23,
      24,     0,    26,     0,    28,     0,    29,    30,    31,    32,
      33,    34,    35,    36,     0,    37,    38,     0,     0,     0,
       0,     0,    39,     0,    40,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    54,    55,     0,     0,     0,
       0,     0,     0,     0,     0,    56,    57,    58,    59,    60,
       0,     0,     0,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,     2,
       0,    77,    78,   145,     0,     4,     0,     5,     0,     0,
       0,     8,     9,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,    22,
      23,    24,     0,    26,     0,    28,     0,    29,    30,    31,
      32,    33,    34,    35,    36,     0,    37,    38,     0,     0,
       0,     0,     0,    39,     0,    40,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    50,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    54,    55,     0,     0,
       0,     0,     0,     0,     0,     0,    56,    57,    58,    59,
      60,     0,     0,     0,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
       2,     0,    77,    78,   195,     0,     4,     0,     5,     0,
       0,     0,     8,     9,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    21,
      22,    23,    24,     0,    26,     0,    28,     0,    29,    30,
      31,    32,    33,    34,    35,    36,     0,    37,    38,     0,
       0,     0,     0,     0,    39,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    54,    55,     0,
       0,     0,     0,     0,     0,     0,     0,    56,    57,    58,
      59,    60,     0,     0,     0,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,     2,     0,    77,    78,   327,     0,     4,     0,     5,
       0,     0,     0,     8,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     392,    22,    23,    24,     0,    26,     0,    28,     0,    29,
      30,    31,    32,    33,    34,    35,    36,     0,    37,    38,
       0,     0,     0,     0,     0,    39,     0,    40,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    50,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    54,    55,
       0,     0,     0,     0,     0,     0,     0,     0,    56,    57,
      58,    59,    60,     0,     0,     0,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,     2,     0,    77,    78,   145,     0,     4,     0,
       5,     0,     0,     0,     8,     9,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    21,    22,    23,    24,     0,    26,     0,    28,     0,
      29,    30,    31,    32,    33,    34,    35,    36,     0,    37,
      38,     0,     0,     0,     0,     0,    39,     0,    40,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    54,
      55,     0,     0,     0,     0,     0,     0,     0,     0,    56,
      57,    58,    59,    60,     0,     0,     0,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,     0,     0,    77,    78,   499,   238,   239,
     240,     0,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   278,   279,   280,     0,     0,     0,   238,   239,   240,
     433,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     278,   279,   280,     0,     0,     0,   238,   239,   240,   459,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   278,
     279,   280,     0,     0,     0,   238,   239,   240,   462,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   278,   279,
     280,     0,     0,     0,   238,   239,   240,   465,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   278,   279,   280,
       0,     0,     0,   238,   239,   240,   514,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   278,   279,   280,     0,
       0,     0,   238,   239,   240,   529,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   278,   279,   280,     0,     0,
       0,   238,   239,   240,   595,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   278,   279,   280,     0,     0,   238,
     239,   240,   281,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   278,   279,   280,     0,     0,   238,   239,   240,
     318,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     278,   279,   280,     0,   238,   239,   240,   457,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   278,   279,   280,
       0,   238,   239,   240,   460,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   278,   279,   280,     0,   238,   239,
     240,   463,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   278,   279,   280,     0,   238,   239,   240,   508,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   278,   279,
     280,     0,   238,   239,   240,   509,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   278,   279,   280,     0,     0,
       0,   304,   527,   238,   239,   240,     0,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   278,   279,   280,   321,
       0,   238,   239,   240,     0,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   278,   279,   280,   322,     0,   238,
     239,   240,     0,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   278,   279,   280,   427,     0,   238,   239,   240,
       0,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     278,   279,   280,   428,     0,   238,   239,   240,     0,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   278,   279,
     280,   504,     0,   238,   239,   240,     0,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   278,   279,   280,   238,
     239,   240,     0,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   278,   279,   280,   410,   238,   239,   240,     0,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   278,
     279,   280,   411,   238,   239,   240,     0,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   278,   279,   280,   414,
     238,   239,   240,     0,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   278,   279,   280,   415,   238,   239,   240,
       0,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     278,   279,   280,   554,   238,   239,   240,     0,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   278,   279,   280,
     561,   238,   239,   240,     0,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   278,   279,   280,   562,   238,   239,
     240,     0,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   278,   279,   280,   600,   238,   239,   240,     0,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   278,   279,
     280,   636,   238,   239,   240,   302,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   278,   279,   280,   238,   239,
     240,   450,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   278,   279,   280,   238,   239,   240,     0,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   278,   279,   280,
     240,     0,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   278,   279,   280,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   278,   279,
     280,  -333,  -333,  -333,  -333,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   278,   279,   280
};

static const yytype_int16 yycheck[] =
{
       2,     1,    20,     3,    40,    77,   292,    79,   336,   337,
     230,   283,     4,   285,   412,   287,     8,   497,    39,    11,
      36,    10,    14,    15,    26,    27,    18,    12,     5,    21,
      79,    84,    24,    25,   568,   403,    65,    84,    89,    39,
      40,    77,    44,   502,    39,    45,   266,    89,    93,    51,
      84,    65,   119,   587,   154,   155,    86,   605,    60,    86,
     280,    63,    93,    93,     4,    40,    93,   259,   260,   261,
     262,    63,    39,   145,   402,   403,    78,    77,     4,   613,
     153,    39,     8,    41,   119,    11,   157,   154,    14,    15,
     119,   120,    18,   153,    89,    21,   153,   556,    24,    25,
      40,   387,   153,   156,   155,   119,   120,   152,    89,   477,
     159,   158,   440,   155,   662,   157,    93,   389,   152,   154,
     157,   152,   151,   195,   672,   154,   129,   661,   623,   154,
     155,   167,   153,   154,   155,   157,   631,    63,    86,   157,
     154,   153,   158,    17,   155,    93,   418,   419,   155,   477,
     157,   646,   153,     7,   552,     9,   155,   429,   157,   445,
     432,   154,   155,   435,   153,    39,   158,   167,     0,   649,
     456,   153,   157,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,   149,   150,   151,   149,   150,   151,   151,
     155,     7,   157,    28,    29,   467,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,    18,   157,    59,    39,   263,   157,    67,
      89,   153,   158,   157,    17,    48,    49,    50,    51,    52,
      53,    54,    55,   153,   151,   149,   150,   151,   151,   154,
     151,   579,   580,    93,   290,   327,    39,   154,   151,   259,
     260,   261,   262,   263,   151,    48,    49,    50,    51,    52,
      53,    54,    55,    39,    89,   311,   312,   120,   121,   122,
     123,   124,   125,   126,   302,   156,    84,    39,   288,   158,
     290,   152,    89,   293,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   157,   129,   149,   150,   151,   155,
     155,   311,   312,   119,   156,   156,   155,    89,   155,   155,
      18,    59,   153,   153,   151,   545,   149,   150,   151,   158,
     158,    59,   158,   335,   152,   155,   153,   119,    84,     7,
     154,   153,   152,    40,   344,    41,    29,   158,    35,   158,
     157,   387,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   387,   157,    89,
     158,   409,   410,   411,   158,   158,   414,   158,   158,   152,
     156,   152,    59,    59,    89,    89,    12,   157,   444,   149,
     150,   151,   157,   157,   157,   152,   155,   153,    84,    89,
      39,   152,    89,   152,   158,   157,   153,   499,   153,    84,
     153,   157,    86,    41,   158,   152,     6,   152,   157,   152,
     582,   153,   152,   152,   444,    39,    84,   466,   635,   477,
     628,   644,   335,   555,    91,   331,    12,   475,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   504,   469,
     470,   471,   472,    -1,   474,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   518,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   504,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   518,    -1,
      -1,   523,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   547,
      -1,   549,    -1,    -1,    -1,    -1,   554,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   568,    -1,
     606,   607,   608,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   604,   587,    -1,    -1,
     149,   150,   151,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   619,   620,   605,    -1,    -1,   606,   607,   608,    -1,
      -1,    -1,    -1,   613,    -1,    -1,    -1,    -1,   636,    -1,
       0,   623,    -1,   641,    -1,    -1,     6,     7,    -1,   631,
      -1,    -1,   650,    -1,    -1,   653,    -1,    17,    -1,   657,
      -1,    -1,    -1,    -1,   646,    25,    -1,    -1,    -1,   667,
      -1,    -1,    -1,    -1,    -1,   673,    -1,    -1,   676,    -1,
     662,   661,    -1,    43,    -1,    45,    46,    47,    48,    49,
     672,    -1,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    62,    -1,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    -1,    -1,    79,
       4,    -1,    -1,    -1,    84,    -1,    10,    -1,    -1,    -1,
      -1,    91,    16,    -1,    18,    -1,    -1,    -1,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    40,    41,    42,    -1,
      44,    -1,    46,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    -1,    57,    58,    -1,    -1,    -1,    -1,    -1,
      64,    -1,    66,    -1,    -1,    -1,    -1,    -1,   148,   149,
     150,    -1,   152,    -1,    -1,   155,    80,    -1,    -1,   159,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   175,   176,    -1,    -1,    -1,
     180,    -1,    -1,    -1,   184,    -1,   186,    -1,    -1,    -1,
      -1,    -1,    -1,   117,   118,   195,    -1,    -1,    -1,   199,
      -1,    -1,    -1,   127,   128,   129,   130,   131,    -1,    -1,
      -1,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,    -1,    -1,   153,
     154,   155,   156,    -1,    -1,    -1,    -1,    -1,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,    -1,
      -1,    -1,    -1,    -1,   264,   265,    -1,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,    -1,    -1,
      -1,    -1,   282,   283,   284,   285,   286,   287,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   304,    -1,    -1,    -1,   308,   309,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   321,   322,    -1,    -1,    -1,    -1,   327,    -1,     3,
     330,   331,    -1,     7,    -1,    -1,    10,    11,    -1,   339,
      -1,    -1,    16,    -1,    18,    19,    20,    -1,    22,    23,
      -1,    -1,    26,    27,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    -1,    57,    58,    59,    -1,    -1,   388,   389,
      64,    -1,    66,    -1,    -1,    69,    70,    71,    72,    73,
      74,    75,    -1,    77,    78,    -1,    80,    81,    82,    83,
      -1,    -1,   412,   413,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   427,   428,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   117,   118,    -1,    -1,    -1,    -1,    -1,
     450,    -1,    -1,   127,   128,   129,   130,   131,    -1,    -1,
      -1,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,    -1,    -1,   153,
     154,   155,    -1,   157,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   499,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   516,   517,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   552,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   569,
      -1,    -1,    -1,    -1,   149,   150,   151,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     7,    -1,    -1,    10,    11,    -1,
      -1,    -1,   592,    16,    -1,    18,    19,    20,    -1,    22,
      23,   601,    -1,    26,    27,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    -1,    57,    58,    -1,    -1,    -1,    -1,
     640,    64,    -1,    66,    -1,    -1,    69,    70,    71,    72,
      73,    74,    75,    -1,    77,    78,    -1,    80,    81,    82,
      83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   117,   118,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   127,   128,   129,   130,   131,    -1,
      -1,    -1,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,    -1,    -1,
     153,   154,   155,    -1,   157,    10,    11,    -1,    -1,    -1,
      -1,    16,    -1,    18,    19,    20,    -1,    22,    23,    -1,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    -1,    57,    58,    -1,    -1,    -1,    -1,    -1,    64,
      -1,    66,    -1,    -1,    69,    70,    71,    72,    73,    74,
      75,    -1,    77,    78,    -1,    80,    81,    82,    83,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   117,   118,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   127,   128,   129,   130,   131,    -1,    -1,    -1,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,    -1,    -1,   153,   154,
     155,    -1,   157,   158,    10,    11,    -1,    -1,    -1,    -1,
      16,    -1,    18,    19,    20,    -1,    22,    23,    -1,    -1,
      26,    27,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      -1,    57,    58,    -1,    -1,    -1,    -1,    -1,    64,    -1,
      66,    -1,    -1,    69,    70,    71,    72,    73,    74,    75,
      -1,    77,    78,    -1,    80,    81,    82,    83,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   117,   118,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   127,   128,   129,   130,   131,    -1,    -1,    -1,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,    -1,    -1,   153,   154,   155,
       7,   157,   158,    10,    -1,    -1,    -1,    -1,    -1,    16,
      -1,    18,    -1,    -1,    -1,    22,    23,    -1,    -1,    26,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    40,    41,    42,    -1,    44,    -1,    46,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    -1,
      57,    58,    -1,    -1,    -1,    -1,    -1,    64,    -1,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     117,   118,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     127,   128,   129,   130,   131,    -1,    -1,    -1,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,    10,    -1,   153,   154,   155,    -1,
      16,    -1,    18,    -1,    -1,    -1,    22,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    40,    41,    42,    -1,    44,    -1,
      46,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      -1,    57,    58,    -1,    -1,    -1,    -1,    -1,    64,    -1,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   117,   118,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   127,   128,   129,   130,   131,    -1,    -1,    -1,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,    -1,    -1,   153,   154,   155,
       7,    -1,   158,    10,    -1,    -1,    -1,    -1,    -1,    16,
      -1,    18,    -1,    -1,    -1,    22,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    40,    41,    42,    -1,    44,    -1,    46,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    -1,
      57,    58,    -1,    -1,    -1,    -1,    -1,    64,    -1,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     117,   118,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     127,   128,   129,   130,   131,    -1,    -1,    -1,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,    -1,    -1,   153,   154,   155,     7,
      -1,    -1,    10,    -1,    -1,    -1,    -1,    -1,    16,    -1,
      18,    -1,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    40,    41,    42,    -1,    44,    -1,    46,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    -1,    57,
      58,    -1,    -1,    -1,    10,    -1,    64,    -1,    66,    -1,
      16,    -1,    18,    -1,    -1,    -1,    22,    23,    -1,    -1,
      -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    40,    41,    42,    -1,    44,    -1,
      46,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      -1,    57,    58,    -1,    -1,    -1,    -1,    -1,    64,    -1,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   127,
     128,   129,   130,   131,    80,    -1,    -1,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,    -1,    -1,   153,   154,   155,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   117,   118,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   127,   128,   129,   130,   131,    -1,    -1,    -1,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,    10,   153,   154,   155,
      -1,   157,    16,    -1,    18,    -1,    -1,    -1,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    40,    41,    42,    -1,
      44,    -1,    46,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    -1,    57,    58,    -1,    -1,    -1,    -1,    -1,
      64,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   117,   118,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   127,   128,   129,   130,   131,    -1,    -1,
      -1,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,    -1,    10,   153,
     154,   155,    -1,   157,    16,    -1,    18,    -1,    -1,    -1,
      22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    41,
      42,    -1,    44,    -1,    46,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    -1,    57,    58,    -1,    -1,    -1,
      -1,    -1,    64,    -1,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   117,   118,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   127,   128,   129,   130,   131,
      -1,    -1,    -1,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,    -1,
      10,   153,   154,   155,    -1,   157,    16,    -1,    18,    -1,
      -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      40,    41,    42,    -1,    44,    -1,    46,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    -1,    57,    58,    -1,
      -1,    -1,    -1,    -1,    64,    -1,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   127,   128,   129,
     130,   131,    -1,    -1,    -1,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,    -1,    10,   153,   154,   155,    -1,   157,    16,    -1,
      18,    -1,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    40,    41,    42,    -1,    44,    -1,    46,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    -1,    57,
      58,    -1,    -1,    -1,    -1,    -1,    64,    -1,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,
     118,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   127,
     128,   129,   130,   131,    -1,    -1,    -1,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,    -1,    10,   153,   154,   155,    -1,   157,
      16,    -1,    18,    -1,    -1,    -1,    22,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    40,    41,    42,    -1,    44,    -1,
      46,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      -1,    57,    58,    -1,    -1,    -1,    -1,    -1,    64,    -1,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   117,   118,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   127,   128,   129,   130,   131,    -1,    -1,    -1,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,    10,    -1,   153,   154,   155,
     156,    16,    -1,    18,    -1,    -1,    -1,    22,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    40,    41,    42,    -1,    44,
      -1,    46,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    -1,    57,    58,    -1,    -1,    -1,    -1,    -1,    64,
      -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   117,   118,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   127,   128,   129,   130,   131,    -1,    -1,    -1,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,    10,    -1,   153,   154,
     155,   156,    16,    17,    18,    -1,    -1,    -1,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    40,    41,    42,    -1,
      44,    -1,    46,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    -1,    57,    58,    -1,    -1,    -1,    -1,    -1,
      64,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   117,   118,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   127,   128,   129,   130,   131,    -1,    -1,
      -1,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,    10,   152,   153,
     154,   155,    -1,    16,    -1,    18,    -1,    -1,    -1,    22,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      -1,    44,    -1,    46,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    -1,    57,    58,    -1,    -1,    -1,    -1,
      -1,    64,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   117,   118,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   127,   128,   129,   130,   131,    -1,
      -1,    -1,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,    10,    -1,
     153,   154,   155,    -1,    16,    -1,    18,    -1,    -1,    -1,
      22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    41,
      42,    -1,    44,    -1,    46,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    -1,    57,    58,    -1,    -1,    -1,
      -1,    -1,    64,    -1,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   117,   118,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   127,   128,   129,   130,   131,
      -1,    -1,    -1,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,    10,
      -1,   153,   154,   155,    -1,    16,    17,    18,    -1,    -1,
      -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,
      41,    42,    -1,    44,    -1,    46,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    -1,    57,    58,    -1,    -1,
      -1,    -1,    -1,    64,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   117,   118,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   127,   128,   129,   130,
     131,    -1,    -1,    -1,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
      -1,    -1,   153,   154,   155,    10,    -1,    -1,    13,    -1,
      -1,    16,    -1,    18,    -1,    -1,    -1,    22,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    40,    41,    42,    -1,    44,
      -1,    46,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    -1,    57,    58,    -1,    -1,    -1,    -1,    -1,    64,
      -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   117,   118,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   127,   128,   129,   130,   131,    -1,    -1,    -1,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,    10,    -1,   153,   154,
     155,    -1,    16,    -1,    18,    -1,    -1,    -1,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    40,    41,    42,    -1,
      44,    -1,    46,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    -1,    57,    58,    -1,    -1,    -1,    -1,    -1,
      64,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   117,   118,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   127,   128,   129,   130,   131,    -1,    -1,
      -1,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,    10,   152,   153,
     154,   155,    -1,    16,    -1,    18,    -1,    -1,    -1,    22,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      -1,    44,    -1,    46,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    -1,    57,    58,    -1,    -1,    -1,    -1,
      -1,    64,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   117,   118,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   127,   128,   129,   130,   131,    -1,
      -1,    -1,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,    10,   152,
     153,   154,   155,    -1,    16,    -1,    18,    -1,    -1,    -1,
      22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    41,
      42,    -1,    44,    -1,    46,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    -1,    57,    58,    -1,    -1,    -1,
      -1,    -1,    64,    -1,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   117,   118,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   127,   128,   129,   130,   131,
      -1,    -1,    -1,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,    10,
      -1,   153,   154,   155,    -1,    16,    -1,    18,    -1,    -1,
      -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,
      41,    42,    -1,    44,    -1,    46,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    -1,    57,    58,    -1,    -1,
      -1,    -1,    -1,    64,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   117,   118,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   127,   128,   129,   130,
     131,    -1,    -1,    -1,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
      10,    -1,   153,   154,   155,    -1,    16,    -1,    18,    -1,
      -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      40,    41,    42,    -1,    44,    -1,    46,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    -1,    57,    58,    -1,
      -1,    -1,    -1,    -1,    64,    -1,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   127,   128,   129,
     130,   131,    -1,    -1,    -1,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,    10,    -1,   153,   154,   155,    -1,    16,    -1,    18,
      -1,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    40,    41,    42,    -1,    44,    -1,    46,    -1,    48,
      49,    50,    51,    52,    53,    54,    55,    -1,    57,    58,
      -1,    -1,    -1,    -1,    -1,    64,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   127,   128,
     129,   130,   131,    -1,    -1,    -1,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,    10,    -1,   153,   154,   155,    -1,    16,    -1,
      18,    -1,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    40,    41,    42,    -1,    44,    -1,    46,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    -1,    57,
      58,    -1,    -1,    -1,    -1,    -1,    64,    -1,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,
     118,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   127,
     128,   129,   130,   131,    -1,    -1,    -1,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,    -1,    -1,   153,   154,   155,    86,    87,
      88,    -1,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   149,   150,   151,    -1,    -1,    -1,    86,    87,    88,
     158,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     149,   150,   151,    -1,    -1,    -1,    86,    87,    88,   158,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,
     150,   151,    -1,    -1,    -1,    86,    87,    88,   158,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,
     151,    -1,    -1,    -1,    86,    87,    88,   158,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,   151,
      -1,    -1,    -1,    86,    87,    88,   158,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   149,   150,   151,    -1,
      -1,    -1,    86,    87,    88,   158,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   149,   150,   151,    -1,    -1,
      -1,    86,    87,    88,   158,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   149,   150,   151,    -1,    -1,    86,
      87,    88,   157,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   149,   150,   151,    -1,    -1,    86,    87,    88,
     157,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     149,   150,   151,    -1,    86,    87,    88,   156,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,   151,
      -1,    86,    87,    88,   156,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   149,   150,   151,    -1,    86,    87,
      88,   156,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   149,   150,   151,    -1,    86,    87,    88,   156,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,
     151,    -1,    86,    87,    88,   156,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   149,   150,   151,    -1,    -1,
      -1,    84,   156,    86,    87,    88,    -1,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   149,   150,   151,    84,
      -1,    86,    87,    88,    -1,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   149,   150,   151,    84,    -1,    86,
      87,    88,    -1,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   149,   150,   151,    84,    -1,    86,    87,    88,
      -1,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     149,   150,   151,    84,    -1,    86,    87,    88,    -1,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,
     151,    84,    -1,    86,    87,    88,    -1,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   149,   150,   151,    86,
      87,    88,    -1,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   149,   150,   151,   152,    86,    87,    88,    -1,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,
     150,   151,   152,    86,    87,    88,    -1,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   149,   150,   151,   152,
      86,    87,    88,    -1,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   149,   150,   151,   152,    86,    87,    88,
      -1,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     149,   150,   151,   152,    86,    87,    88,    -1,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,   151,
     152,    86,    87,    88,    -1,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   149,   150,   151,   152,    86,    87,
      88,    -1,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   149,   150,   151,   152,    86,    87,    88,    -1,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,
     151,   152,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   149,   150,   151,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   149,   150,   151,    86,    87,    88,    -1,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,   151,
      88,    -1,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   149,   150,   151,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,
     151,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   149,   150,   151
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,    10,    11,    16,    18,    19,    20,    22,    23,
      26,    27,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    48,
      49,    50,    51,    52,    53,    54,    55,    57,    58,    64,
      66,    69,    70,    71,    72,    73,    74,    75,    77,    78,
      80,    81,    82,    83,   117,   118,   127,   128,   129,   130,
     131,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   153,   154,   155,
     157,   160,   168,   173,   174,   175,   185,   203,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   223,
     224,   225,   226,   228,   229,   230,   231,   234,   235,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     168,   176,   231,   168,    39,   155,   234,   234,   153,   153,
     153,   230,   153,   157,   157,   153,   234,    89,   157,   155,
     228,   234,   231,   231,   168,   170,   171,    17,   164,   165,
     166,   167,   168,   169,   170,   153,   153,   157,   234,   231,
     168,   234,   234,   234,    79,   234,    79,   234,   231,   234,
     234,   234,   234,   234,   234,   155,   234,   234,   231,   129,
     234,   231,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   165,   168,   234,   236,     4,
     207,   208,   231,   232,   236,   158,   211,   234,   236,     0,
     151,   175,     7,    18,    59,   213,   157,   157,    86,    87,
      88,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   149,   150,
     151,   157,   154,   155,   154,   155,   154,   155,    67,   177,
      89,   157,   153,    13,   187,   234,   234,   233,   234,   153,
     234,   234,    89,   228,    84,   151,   151,   119,   154,   154,
     165,    93,    65,   120,   154,   154,   234,   234,   157,   151,
     234,    84,    84,   234,   234,   151,   234,   155,   234,   151,
     152,    84,   152,    39,   161,    84,   156,    89,   156,    84,
     158,   158,    39,   162,    89,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   164,   168,   164,   164,
     164,   165,   234,   234,    41,   162,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   153,   154,   155,
     162,   234,    39,   161,   234,   234,   161,   234,   234,   161,
     234,   168,    89,   155,   157,   178,   165,   232,   168,   152,
     152,   152,   157,   129,   152,   152,   228,   234,   155,   155,
     119,   156,   234,   156,   234,   165,   165,    84,    84,   155,
     234,   234,   155,   158,   234,   155,   234,    26,   226,   234,
      89,   208,   231,   209,   209,   153,    47,    56,   165,   172,
      89,   165,   232,   234,   161,   234,   153,   156,   158,   158,
     156,   158,   158,   156,   158,   158,   209,     4,     8,    11,
      14,    15,    21,    24,    25,    63,   179,   180,   181,   182,
     183,   184,   185,   186,   188,   189,   190,   191,   196,   197,
     202,   209,    59,    59,   152,   228,   228,   228,   233,   155,
     234,   228,   155,   220,    84,   161,   161,   119,   156,   156,
     234,   234,   161,   161,   158,   161,   153,    84,   209,     7,
     165,   232,   154,   153,   234,   152,   152,   156,   158,   158,
     232,   157,   178,   161,    40,   168,   168,   168,   168,    41,
     168,   228,   158,   181,   157,     7,     9,    29,    28,    29,
     227,   227,   157,   234,   152,   221,   222,   223,   165,   158,
     158,   152,   152,   158,   158,   158,   234,   165,    89,    86,
     152,   156,   204,   205,   206,   231,   152,    59,    59,    89,
      89,    12,    12,   157,   157,   157,   157,    89,   162,   155,
     192,   228,   153,   228,   233,   158,   228,   158,   224,   223,
     152,    86,   172,   234,   152,    84,    89,   209,   209,    39,
     163,   163,   172,    89,   162,   193,   194,   195,   234,   152,
     152,   158,   234,   153,   228,   206,   165,   165,   165,   157,
     157,   153,   172,    86,   158,    84,   152,   228,   228,   204,
      86,     5,   198,   199,   198,   204,   153,    41,   195,   228,
     152,   234,   228,     6,   200,   201,   200,   152,   204,   227,
     228,    89,   153,   228,   157,   157,   228,   152,   172,   206,
     157,   228,   153,   152,   206,   228,   152,   228
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   159,   160,   161,   162,   163,   164,   164,   165,   165,
     165,   165,   165,   166,   167,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   169,   170,   170,   170,   171,   171,
     172,   172,   172,   172,   173,   173,   174,   174,   175,   175,
     175,   175,   175,   176,   176,   177,   177,   178,   179,   179,
     180,   180,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   182,   183,   184,   185,   186,   186,   187,
     188,   189,   190,   191,   192,   193,   193,   194,   194,   194,
     195,   195,   196,   197,   198,   198,   199,   200,   200,   201,
     201,   201,   201,   202,   202,   202,   202,   203,   203,   204,
     204,   205,   205,   205,   206,   206,   207,   207,   207,   208,
     208,   208,   208,   209,   209,   210,   210,   211,   211,   212,
     212,   213,   213,   213,   213,   213,   213,   213,   213,   213,
     213,   213,   213,   213,   213,   213,   213,   213,   213,   213,
     213,   214,   214,   214,   214,   214,   215,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   215,   215,   215,   215,
     215,   215,   216,   217,   217,   218,   219,   220,   220,   221,
     221,   222,   222,   223,   223,   224,   224,   225,   225,   226,
     226,   227,   227,   227,   228,   229,   230,   230,   231,   232,
     232,   233,   233,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   235,   235,   236,   236,   236,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   238,   238,   238,   238,   239,
     239,   240,   240,   241,   241,   241,   241,   241,   241,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   243,   244,
     244,   244,   244,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   246,   247,   247,
     247,   248,   249,   249,   249,   249,   249,   250,   250,   251,
     251,   252,   252,   253,   253,   253,   254,   254,   254,   255,
     255,   255,   255,   255,   255,   255,   256,   256,   256,   256,
     257,   257,   257,   257,   258,   258,   258,   258,   259,   260,
     261,   262,   262,   263,   264,   265,   266,   267,   267
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     3,     3,     4,     4,     4,
       1,     1,     1,     3,     0,     1,     2,     1,     5,     7,
       5,     7,     2,     0,     1,     0,     2,     3,     0,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     2,     3,     3,     3,     1,     5,     2,
       5,     3,     3,     3,     3,     0,     1,     3,     2,     1,
       1,     3,     8,     7,     0,     1,     2,     0,     1,     2,
       5,     7,     3,     9,     9,     8,     8,     8,    11,     0,
       1,     3,     2,     1,     3,     5,     3,     2,     1,     5,
       7,     4,     6,     0,     1,     2,     1,     0,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     3,     2,     2,     2,     1,
       1,     2,     1,     3,     2,     4,     1,     1,     2,     3,
       2,     3,     1,     1,     2,     2,     2,     2,     1,     1,
       6,     6,     9,     7,     9,     5,     5,     3,     4,     0,
       1,     2,     1,     4,     3,     3,     2,     5,     7,     6,
       6,     0,     2,     6,     3,     2,     4,     2,     1,     0,
       1,     0,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     7,     3,     2,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     1,     2,     2,     2,     2,     4,     3,     5,     2,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     5,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     3,     3,     3,     3,     3,     3,     4,     5,     3,
       3,     3,     3,     2,     2,     1,     3,     3,     2,     5,
       2,     6,     3,     6,     3,     5,     5,     4,     4,     4,
       5,     4,     4,     4,     5,     4,     4,     4,     6,     6,
       6,     2,     1,     4,     6,     6,     6,     1,     2
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
        case 12:
#line 103 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_mutable_type(compiler, (yyvsp[0].opval));
    }
#line 3196 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 13:
#line 109 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_union_type(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3204 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 14:
#line 115 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_generic_type(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3212 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 15:
#line 121 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[0].opval));
    }
#line 3220 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 16:
#line 125 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_byte_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3230 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 17:
#line 131 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_short_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3240 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 18:
#line 137 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3250 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 19:
#line 143 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_long_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3260 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 20:
#line 149 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_float_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3270 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 21:
#line 155 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_double_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3280 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 22:
#line 161 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_any_object_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = op_type;
    }
#line 3289 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 23:
#line 166 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_string_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3299 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 24:
#line 174 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[-1].opval));
    }
#line 3307 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 25:
#line 180 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-2].opval), NULL, 0);
    }
#line 3315 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 26:
#line 184 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-2].opval), NULL, 0);
    }
#line 3323 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 27:
#line 188 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), NULL, 1);
    }
#line 3332 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 28:
#line 195 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval), 0);
    }
#line 3340 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 29:
#line 199 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval), 0);
    }
#line 3348 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 31:
#line 206 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_void_type(compiler, compiler->current_file, compiler->current_line);
    }
#line 3356 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 32:
#line 210 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_element_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
    }
#line 3364 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 33:
#line 214 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_element_array_type(compiler, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
    }
#line 3372 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 34:
#line 220 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3380 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 35:
#line 224 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3395 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 36:
#line 237 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3413 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 38:
#line 254 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), NULL, (yyvsp[-2].opval));
    }
#line 3421 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 39:
#line 258 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[-4].opval));
    }
#line 3429 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 40:
#line 262 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), NULL, NULL, (yyvsp[-2].opval));
    }
#line 3437 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 41:
#line 266 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), NULL, (yyvsp[-2].opval), (yyvsp[-4].opval));
    }
#line 3445 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 42:
#line 270 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_anon_class_from_statements(compiler, (yyvsp[-1].opval));
    }
#line 3453 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 43:
#line 276 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 3461 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 45:
#line 283 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 3469 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 46:
#line 287 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_extends(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3477 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 47:
#line 293 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_class_block;
    }
#line 3487 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 48:
#line 301 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3495 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 49:
#line 305 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[0].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
        SPVM_OP_insert_child(compiler, (yyval.opval), (yyval.opval)->last, (yyvsp[0].opval));
      }
    }
#line 3509 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 50:
#line 317 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3527 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 63:
#line 347 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    { 
      (yyval.opval) = SPVM_OP_build_init_statement(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3535 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 64:
#line 353 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_version_decl(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3543 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 65:
#line 359 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_version_from(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3551 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 66:
#line 365 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      int32_t is_require = 0;
      SPVM_OP* op_name_class_alias = NULL;
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), op_name_class_alias, is_require);
    }
#line 3561 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 68:
#line 374 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      int32_t is_require = 0;
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), is_require);
    }
#line 3570 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 69:
#line 381 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, compiler->current_file, compiler->current_line);
      int32_t is_require = 1;
      (yyval.opval) = SPVM_OP_build_use(compiler, op_use, (yyvsp[0].opval), NULL, is_require);
    }
#line 3580 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 70:
#line 389 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_alias(compiler, op_use, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3589 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 71:
#line 396 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_allow(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3597 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 72:
#line 402 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_interface_statement(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3605 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 73:
#line 408 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), (yyvsp[-2].opval));
    }
#line 3613 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 74:
#line 414 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_enum_block;
    }
#line 3623 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 75:
#line 422 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3631 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 76:
#line 426 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3646 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 77:
#line 439 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3664 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 80:
#line 457 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_item(compiler, (yyvsp[0].opval), NULL);
    }
#line 3672 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 81:
#line 461 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_item(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3680 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 82:
#line 467 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class_var(compiler, (yyvsp[-7].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3688 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 83:
#line 473 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_field(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3696 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 84:
#line 479 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 3704 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 86:
#line 486 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_return_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      SPVM_OP* op_arg = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_accessor(compiler, (yyvsp[-1].opval), op_arg, (yyvsp[0].opval), op_return_type);
    }
#line 3714 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 87:
#line 494 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 3722 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 89:
#line 501 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_return_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      SPVM_OP* op_arg = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_accessor(compiler, (yyvsp[-1].opval), op_arg, (yyvsp[0].opval), op_return_type);
    }
#line 3732 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 90:
#line 507 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_return_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_accessor(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval), op_return_type);
    }
#line 3741 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 91:
#line 512 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_accessor(compiler, (yyvsp[-6].opval), (yyvsp[-2].opval), (yyvsp[0].opval), (yyvsp[-4].opval));
    }
#line 3749 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 92:
#line 516 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_arg = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      SPVM_OP* op_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_accessor(compiler, (yyvsp[-2].opval), op_arg, op_block, (yyvsp[0].opval));
    }
#line 3759 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 93:
#line 524 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-8].opval), (yyvsp[0].opval));
     }
#line 3767 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 94:
#line 528 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-8].opval), NULL);
     }
#line 3775 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 95:
#line 532 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-6].opval), NULL, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-7].opval), (yyvsp[0].opval));
     }
#line 3783 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 96:
#line 536 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-6].opval), NULL, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-7].opval), NULL);
     }
#line 3791 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 97:
#line 542 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-6].opval), NULL, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-7].opval), (yyvsp[0].opval));
     }
#line 3799 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 98:
#line 546 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3818 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 99:
#line 563 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3826 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 100:
#line 567 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3841 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 101:
#line 580 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3859 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 104:
#line 598 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[-2].opval), (yyvsp[0].opval), NULL, NULL);
    }
#line 3867 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 105:
#line 602 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), NULL, (yyvsp[0].opval));
    }
#line 3875 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 106:
#line 608 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3893 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 109:
#line 626 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_anon_method_field(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 3901 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 110:
#line 630 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_anon_method_field(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3909 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 111:
#line 634 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_FIELD, (yyvsp[-3].opval)->file, (yyvsp[-3].opval)->line);
      
      (yyval.opval) = SPVM_OP_build_anon_method_field(compiler, op_field, NULL, (yyvsp[-1].opval), (yyvsp[0].opval), (yyvsp[-3].opval));
    }
#line 3919 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 112:
#line 640 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_FIELD, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      
      (yyval.opval) = SPVM_OP_build_anon_method_field(compiler, op_field, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3929 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 113:
#line 648 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3937 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 114:
#line 652 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3952 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 115:
#line 665 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3970 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 117:
#line 682 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3978 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 118:
#line 686 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3993 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 119:
#line 699 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 4011 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 134:
#line 729 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[-1].opval), NULL);
    }
#line 4019 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 135:
#line 733 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 4027 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 137:
#line 738 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_operator_statement(compiler, (yyvsp[-1].opval));
    }
#line 4035 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 139:
#line 743 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
#line 4043 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 141:
#line 750 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 4051 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 142:
#line 754 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[0].opval), NULL, NULL);
    }
#line 4059 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 143:
#line 758 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-2].opval), (yyvsp[0].opval), (yyvsp[-1].opval));
    }
#line 4067 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 144:
#line 762 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-1].opval), NULL, (yyvsp[0].opval));
    }
#line 4075 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 145:
#line 766 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-3].opval), (yyvsp[0].opval), (yyvsp[-2].opval));
    }
#line 4083 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 148:
#line 774 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_print(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), 0);
    }
#line 4091 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 149:
#line 778 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_print(compiler, (yyvsp[-2].opval), (yyvsp[0].opval), 1);
    }
#line 4099 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 150:
#line 782 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_print(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), 0);
    }
#line 4107 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 151:
#line 786 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_print(compiler, (yyvsp[-2].opval), (yyvsp[0].opval), 1);
    }
#line 4115 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 154:
#line 792 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_make_read_only(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4123 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 155:
#line 796 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_make_fixed_length(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4131 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 156:
#line 800 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enable_options(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4139 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 157:
#line 804 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_disable_options(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4147 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 160:
#line 810 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4155 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 161:
#line 814 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4163 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 162:
#line 820 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[-8].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4171 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 163:
#line 826 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_foreach_statement(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4179 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 164:
#line 830 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_foreach_statement(compiler, (yyvsp[-8].opval), (yyvsp[-7].opval), (yyvsp[-3].opval), (yyvsp[0].opval));
    }
#line 4187 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 165:
#line 836 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4195 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 166:
#line 842 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4203 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 167:
#line 848 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[-1].opval), NULL);
    }
#line 4212 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 168:
#line 853 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 4221 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 169:
#line 860 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 4229 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 170:
#line 864 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 4244 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 171:
#line 877 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 4262 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 172:
#line 891 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 4270 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 173:
#line 897 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4278 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 174:
#line 901 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), NULL);
    }
#line 4286 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 175:
#line 907 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4294 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 176:
#line 911 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[-1].opval), NULL);
    }
#line 4302 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 177:
#line 917 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->current_file, compiler->current_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[-2].opval), (yyvsp[0].opval), NULL);
    }
#line 4312 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 178:
#line 923 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->current_file, compiler->current_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4322 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 179:
#line 930 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval), 0);
      
      // condition part has own scope
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    }
#line 4336 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 180:
#line 940 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      op_if = SPVM_OP_build_if_statement(compiler, op_if, (yyvsp[-3].opval), (yyvsp[0].opval), (yyvsp[-1].opval), 0);
      
      // condition part has own scope
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    }
#line 4351 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 181:
#line 953 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
#line 4359 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 182:
#line 957 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 4367 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 183:
#line 961 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, op_if, (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval), 0);
    }
#line 4376 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 184:
#line 968 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_block;
    }
#line 4386 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 185:
#line 976 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4394 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 186:
#line 982 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var_decl(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval), NULL);
    }
#line 4402 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 187:
#line 986 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var_decl(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL, NULL);
    }
#line 4410 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 188:
#line 992 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[0].opval));
    }
#line 4418 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 189:
#line 998 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 4426 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1002 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 4441 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1015 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
#line 4449 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1031 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_true(compiler, (yyvsp[0].opval));
    }
#line 4457 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1035 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_false(compiler, (yyvsp[0].opval));
    }
#line 4465 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1047 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_basic_type_id(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4473 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1063 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 4493 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1079 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_operator = (yyvsp[-5].opval)->first;
      SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, compiler->current_file, compiler->current_line);
      
      SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, (yyvsp[-5].opval));
      SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, (yyvsp[-3].opval));
      SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, (yyvsp[-1].opval));
      
      (yyval.opval) = op_sequence;
    }
#line 4508 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1092 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 4526 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1106 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[-1].opval);
    }
#line 4534 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1110 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 4542 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1116 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, operator, (yyvsp[0].opval));
    }
#line 4551 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1121 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MINUS, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, op_negate, (yyvsp[0].opval));
    }
#line 4560 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1126 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4568 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1130 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4576 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1134 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4584 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1138 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4592 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1142 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4600 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1146 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op_var(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4608 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1150 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op_var(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4616 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1154 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4624 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1158 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4632 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1162 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4640 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1166 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4648 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1171 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4656 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1175 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4664 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1179 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4672 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1185 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[0].opval));
    }
#line 4681 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1190 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[-1].opval));
    }
#line 4690 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1195 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[0].opval));
    }
#line 4699 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1200 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[-1].opval));
    }
#line 4708 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1207 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, operator, (yyvsp[0].opval));
    }
#line 4717 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1212 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, operator, (yyvsp[-1].opval));
    }
#line 4726 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1219 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, operator, (yyvsp[0].opval));
    }
#line 4735 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1224 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, operator, (yyvsp[-1].opval));
    }
#line 4744 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1239 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, operator, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4753 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1244 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, operator, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4762 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1249 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MULTIPLY, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, operator, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4771 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1254 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4779 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1258 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4787 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1262 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4795 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1266 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4803 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1270 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4811 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1274 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4819 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1280 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* ternary_op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TERNARY_OP, (yyvsp[-4].opval)->file, (yyvsp[-4].opval)->line);
      (yyval.opval) = SPVM_OP_build_ternary_op(compiler, ternary_op, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4828 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1287 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4836 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1291 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4844 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1295 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4852 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1299 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4860 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1305 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4868 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1309 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4876 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 275:
#line 1313 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4884 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1317 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4892 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1321 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4900 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1325 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4908 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1329 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4916 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 280:
#line 1333 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4924 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1337 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4932 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1341 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4940 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1345 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4948 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 284:
#line 1349 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4956 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1353 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4964 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1357 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4972 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 287:
#line 1363 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4980 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1369 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_logical_or(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4988 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 289:
#line 1373 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_logical_and(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4996 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1377 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_logical_not(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 5004 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 291:
#line 1383 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_defined_or(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 5012 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 292:
#line 1389 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_type_check(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 5020 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1393 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_type_check(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 5028 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 294:
#line 1397 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_type_check(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 5036 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 295:
#line 1401 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_type_check(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 5044 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 296:
#line 1405 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_type_check(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 5052 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 297:
#line 1411 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type_cast = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      (yyval.opval) = SPVM_OP_build_type_cast(compiler, op_type_cast, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 5061 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 298:
#line 1416 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type_cast = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_type_cast(compiler, op_type_cast, (yyvsp[-1].opval), (yyvsp[-4].opval));
    }
#line 5070 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 299:
#line 1423 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_can(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 5078 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 300:
#line 1427 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_can(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 5086 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 301:
#line 1433 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 5094 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 302:
#line 1437 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_special_assign(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 5102 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 303:
#line 1443 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 5110 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 304:
#line 1447 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_length = (yyvsp[0].opval)->last;
      SPVM_OP_cut_op(compiler, (yyvsp[0].opval)->last);
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), op_length);
    }
#line 5120 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 305:
#line 1453 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_anon_method(compiler, (yyvsp[0].opval));
    }
#line 5128 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 306:
#line 1459 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->current_file, compiler->current_line);
      int32_t is_key_values = 0;
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[-1].opval), is_key_values);
    }
#line 5138 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 307:
#line 1465 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->current_file, compiler->current_line);
      int32_t is_key_values = 1;
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[-1].opval), is_key_values);
    }
#line 5148 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 308:
#line 1471 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->current_file, compiler->current_line);
      int32_t is_key_values = 1;
      SPVM_OP* op_list_elements = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, op_list_elements, is_key_values);
    }
#line 5159 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 309:
#line 1480 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 5168 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 310:
#line 1485 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, (yyvsp[-1].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-1].opval), (yyvsp[0].opval), op_operators);
    }
#line 5178 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 311:
#line 1491 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 5187 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 312:
#line 1496 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-2].opval), (yyvsp[0].opval), op_operators);
    }
#line 5197 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 313:
#line 1502 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 5206 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 314:
#line 1507 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-2].opval), (yyvsp[0].opval), op_operators);
    }
#line 5216 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 315:
#line 1513 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_method_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[-3].opval)->file, (yyvsp[-3].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-4].opval), op_method_name, (yyvsp[-1].opval));
    }
#line 5226 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 316:
#line 1521 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_element_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_ELEMENT_ACCESS, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_element_access(compiler, op_array_element_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 5235 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 317:
#line 1526 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_element_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_ELEMENT_ACCESS, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_element_access(compiler, op_array_element_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 5244 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 318:
#line 1531 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_element_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_ELEMENT_ACCESS, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_element_access(compiler, op_array_element_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 5253 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 319:
#line 1536 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_element_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_ELEMENT_ACCESS, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_element_access(compiler, op_array_element_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 5262 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 320:
#line 1543 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 5271 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 321:
#line 1548 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 5280 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 322:
#line 1553 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 5289 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 323:
#line 1558 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 5298 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 324:
#line 1565 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_hash_value_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_HASH_VALUE_ACCESS, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op_hash_value_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 5307 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 325:
#line 1570 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_hash_value_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_HASH_VALUE_ACCESS, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op_hash_value_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 5316 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 326:
#line 1575 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_hash_value_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_HASH_VALUE_ACCESS, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op_hash_value_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 5325 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 327:
#line 1580 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_hash_value_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_HASH_VALUE_ACCESS, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op_hash_value_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 5334 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 328:
#line 1587 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 5344 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 329:
#line 1595 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_unweaken_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 5354 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 330:
#line 1603 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_isweak_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 5364 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 331:
#line 1611 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_warn(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 5372 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 332:
#line 1615 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_warn(compiler, (yyvsp[0].opval), NULL);
    }
#line 5380 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 333:
#line 1621 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_warn_level(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 5388 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 334:
#line 1627 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_copy_fields(compiler, (yyvsp[-5].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 5396 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 335:
#line 1633 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_exists(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 5406 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 336:
#line 1641 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_delete(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 5416 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 337:
#line 1649 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_caller(compiler, (yyvsp[0].opval), NULL);
    }
#line 5424 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 338:
#line 1653 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_caller(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 5432 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;


#line 5436 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
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
#line 1657 "yacc/spvm_yacc.y" /* yacc.c:1906  */

