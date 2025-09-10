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
    TRUE = 310,
    FALSE = 311,
    END_OF_FILE = 312,
    RW = 313,
    RO = 314,
    WO = 315,
    INIT = 316,
    NEW = 317,
    OF = 318,
    BASIC_TYPE_ID = 319,
    EXTENDS = 320,
    SUPER = 321,
    RETURN = 322,
    WEAKEN = 323,
    DIE = 324,
    WARN = 325,
    PRINT = 326,
    SAY = 327,
    OUTMOST_CLASS_NAME = 328,
    UNWEAKEN = 329,
    ENABLE_OPTIONS = 330,
    DISABLE_OPTIONS = 331,
    FATCAMMA = 332,
    ASSIGN = 333,
    SPECIAL_ASSIGN = 334,
    LOGICAL_OR = 335,
    DEFINED_OR = 336,
    LOGICAL_AND = 337,
    BIT_OR = 338,
    BIT_XOR = 339,
    BIT_AND = 340,
    NUMEQ = 341,
    NUMNE = 342,
    STREQ = 343,
    STRNE = 344,
    NUMGT = 345,
    NUMGE = 346,
    NUMLT = 347,
    NUMLE = 348,
    STRGT = 349,
    STRGE = 350,
    STRLT = 351,
    STRLE = 352,
    ISA = 353,
    ISA_ERROR = 354,
    IS_TYPE = 355,
    IS_ERROR = 356,
    IS_COMPILE_TYPE = 357,
    NUMERIC_CMP = 358,
    STRING_CMP = 359,
    CAN = 360,
    SHIFT = 361,
    DIVIDE = 362,
    DIVIDE_UNSIGNED_INT = 363,
    DIVIDE_UNSIGNED_LONG = 364,
    MODULO = 365,
    MODULO_UNSIGNED_INT = 366,
    MODULO_UNSIGNED_LONG = 367,
    LOGICAL_NOT = 368,
    BIT_NOT = 369,
    REFERENCE = 370,
    DEREFERENCE = 371,
    PLUS = 372,
    MINUS = 373,
    CONVERT = 374,
    SCALAR = 375,
    STRING_LENGTH = 376,
    ISWEAK = 377,
    TYPE_NAME = 378,
    COMPILE_TYPE_NAME = 379,
    DUMP = 380,
    NEW_STRING_LEN = 381,
    IS_READ_ONLY = 382,
    COPY = 383,
    ADDRESS = 384,
    IS_OPTIONS = 385,
    INC = 386,
    DEC = 387,
    ARROW = 388
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_LIB_SPVM_BUILDER_INCLUDE_SPVM_YACC_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 267 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:358  */

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
#define YYLAST   4624

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  149
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  107
/* YYNRULES -- Number of rules.  */
#define YYNRULES  317
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  626

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   388

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
     143,   142,   113,   110,    77,   111,   112,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    82,   147,
       2,     2,     2,    81,   122,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   144,     2,   146,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   145,     2,   148,     2,     2,     2,     2,
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
      75,    76,    78,    79,    80,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   114,   115,   116,   117,   118,   119,   120,   121,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    82,    82,    85,    88,    91,    94,    95,   101,   102,
     103,   106,   110,   116,   122,   128,   134,   140,   146,   151,
     159,   165,   169,   173,   180,   184,   190,   191,   198,   201,
     204,   205,   208,   214,   228,   235,   238,   251,   265,   268,
     272,   276,   280,   287,   290,   294,   297,   303,   312,   315,
     327,   341,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   357,   363,   369,   375,   381,   388,   396,
     403,   409,   415,   421,   430,   433,   446,   460,   461,   464,
     468,   474,   480,   487,   490,   493,   502,   505,   508,   514,
     519,   523,   531,   535,   539,   543,   549,   553,   571,   574,
     587,   601,   602,   605,   609,   615,   629,   630,   633,   637,
     641,   647,   656,   659,   672,   686,   690,   693,   706,   720,
     723,   724,   725,   726,   727,   728,   729,   730,   731,   732,
     733,   734,   735,   736,   740,   744,   745,   749,   750,   756,
     760,   764,   768,   772,   778,   779,   783,   787,   788,   789,
     793,   797,   801,   802,   805,   811,   815,   821,   827,   833,
     838,   846,   849,   862,   876,   882,   886,   892,   896,   902,
     908,   915,   925,   939,   942,   946,   953,   961,   967,   971,
     977,   984,   987,  1001,  1004,  1007,  1008,  1009,  1010,  1011,
    1012,  1013,  1014,  1015,  1016,  1020,  1024,  1025,  1026,  1027,
    1028,  1029,  1030,  1031,  1032,  1036,  1037,  1038,  1039,  1040,
    1041,  1042,  1043,  1046,  1062,  1075,  1089,  1093,  1099,  1104,
    1109,  1113,  1117,  1121,  1125,  1129,  1133,  1137,  1141,  1145,
    1149,  1150,  1154,  1160,  1165,  1170,  1175,  1182,  1187,  1194,
    1199,  1206,  1207,  1208,  1209,  1210,  1211,  1214,  1219,  1224,
    1229,  1233,  1237,  1241,  1245,  1249,  1255,  1262,  1266,  1270,
    1274,  1280,  1284,  1288,  1292,  1296,  1300,  1304,  1308,  1312,
    1316,  1320,  1324,  1328,  1332,  1338,  1344,  1348,  1352,  1358,
    1364,  1368,  1372,  1376,  1380,  1386,  1391,  1398,  1402,  1408,
    1412,  1418,  1422,  1428,  1434,  1440,  1446,  1455,  1460,  1466,
    1471,  1477,  1482,  1488,  1496,  1501,  1506,  1513,  1518,  1523,
    1531,  1539,  1547,  1555,  1559,  1565,  1571,  1579
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
  "OBJECT", "TRUE", "FALSE", "END_OF_FILE", "RW", "RO", "WO", "INIT",
  "NEW", "OF", "BASIC_TYPE_ID", "EXTENDS", "SUPER", "RETURN", "WEAKEN",
  "DIE", "WARN", "PRINT", "SAY", "OUTMOST_CLASS_NAME", "UNWEAKEN",
  "ENABLE_OPTIONS", "DISABLE_OPTIONS", "','", "FATCAMMA", "ASSIGN",
  "SPECIAL_ASSIGN", "'?'", "':'", "LOGICAL_OR", "DEFINED_OR",
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
     325,   326,   327,   328,   329,   330,   331,    44,   332,   333,
     334,    63,    58,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
      43,    45,    46,    42,   362,   363,   364,   365,   366,   367,
     368,   369,    64,   370,   371,   372,   373,   374,   375,   376,
     377,   378,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   388,    41,    40,    91,   123,    93,    59,   125
};
# endif

#define YYPACT_NINF -514

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-514)))

#define YYTABLE_NINF -315

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-315)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      21,   251,    35,  -514,    21,  -514,  -514,  -514,  -514,  -514,
    -514,  -514,  -514,  -514,  -514,  -514,   -10,  -514,  -514,   251,
     -61,  -514,    10,   338,   -11,    47,  -514,  -120,    23,    36,
      25,   251,   251,   251,   251,    72,   251,   -20,   -14,   371,
    -514,  -514,  -514,  -514,  -514,  -514,  -514,  -514,  -514,  -514,
     -18,  -514,    40,  -514,  -514,    81,    84,  -514,  -514,    55,
      65,    -7,   137,    11,    14,    24,    37,   687,  -514,  -514,
    -514,  -514,   -22,    12,  -514,  -514,    10,    10,   148,  -514,
     148,  -514,  -514,  -514,  -514,   149,   151,  2455,  -514,  -514,
      44,    48,    -4,    49,    46,    51,    52,  2455,   112,    53,
     -20,  -514,  -514,  -514,  2455,   149,   149,  -514,  -514,  -514,
     251,   251,  1343,   149,  1475,  1528,  2455,  2455,  -514,   149,
    2455,  2455,  2455,  2455,  2455,  2455,  2586,  2455,   149,    74,
    2455,   149,  2455,  2455,  2455,  2455,  2455,  2455,  2455,  2455,
    2455,  2455,  2082,   556,   823,  -514,    58,  -514,   197,    60,
     959,  -514,    66,    76,  -514,  -514,  -514,  -514,  -514,  -514,
    -514,  -514,  -514,  -514,  -514,  -514,  3035,  -514,  -514,  -514,
    -514,  -514,  -514,  -514,  -514,  -514,  -514,  -514,  -514,  -514,
    -514,  -514,  -514,  -514,  -514,  -514,  -514,     7,     9,  -514,
    -514,  -514,  -514,  -514,  -514,  -514,  -514,   168,   142,   187,
    -514,   126,   126,  -514,    79,    82,   145,    85,  1151,  4256,
    2218,  2455,  1660,    87,  2455,  -514,  -514,  2455,  4130,   -20,
    -514,  -514,  3489,    90,    91,     6,    89,  -514,  -514,    19,
    -514,    92,  -514,  3100,    93,  1713,    15,  3554,  4256,  4256,
    4256,    94,  4256,  4256,  -102,  -102,  -102,  -102,  1151,  -102,
    -102,  -514,  2639,  -102,    96,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,  -102,   -96,   -96,   251,    97,   198,  4256,   -59,
      36,   -48,  -514,   180,   118,   203,  -514,  3035,   -51,   187,
     200,  -514,  -514,  -514,  -514,  2455,  2455,  2455,  2455,  2455,
    2455,  2455,  2455,  2455,  2455,  2455,  2455,  2455,  2455,  2455,
    2455,  2455,  2455,  2455,  2455,  2455,   251,   251,   251,   251,
     126,  2455,  2455,    28,  2455,  2455,  2455,  2455,  2455,  2455,
    2455,  2455,  2455,  2455,  2455,  -514,  -514,   -28,  -514,  2455,
      36,  2455,    36,  -514,  -514,   140,   168,   206,   143,   211,
    -514,   285,   285,  -514,  -514,   126,  2271,   251,   153,  3682,
    3746,   146,  4256,   174,  3810,  3874,   -20,  -514,  2455,   167,
     171,   208,  1845,  1898,  -514,   176,   178,  -514,   182,  4256,
    2455,   184,  2837,  1151,  -102,   185,   198,  2455,   251,  -514,
     198,  -514,  1098,  -514,   249,    26,    10,    10,  -514,  1290,
    -514,   190,   168,  4256,  4256,  4193,  4374,  4374,  4430,   542,
     542,  2756,  4483,  4483,  4483,  4483,   673,   673,   673,   673,
     673,   673,   673,   673,  -514,  -514,  -514,  -514,  -514,   673,
     673,  -514,  -514,   337,   366,   366,   366,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,  2029,  2455,    36,   191,  3165,   192,
    3229,   193,   149,   195,   295,  -514,   187,   -20,   333,  -514,
     333,  -514,   201,  -514,   -20,   -20,   -20,  1660,  2770,   -20,
     205,  -514,  3619,    36,    36,   239,  -514,  3293,  -514,  3357,
      36,  4256,    36,  -514,  2903,    36,  -514,  -102,  -514,   268,
    -514,   212,   280,  4256,    10,  -514,   180,   352,   126,  2271,
     217,  2455,   221,   222,  3421,   218,  2271,  -514,  -514,  -514,
    -514,   223,   292,  -514,   288,   149,  -514,  -514,  -514,   -42,
    -514,  -514,   224,  -514,   344,    80,    80,   226,  1151,  3938,
    -514,   340,  -514,   251,   228,   229,  -514,  -514,  -514,   232,
     233,  -514,   236,   251,  2455,  2455,   126,   305,   309,   255,
     149,  4317,  -514,  -514,  -514,  -514,   256,   -12,   149,   126,
     258,   168,   149,  -514,  -514,   -20,   250,   -20,  -514,  -514,
    2402,  2969,   -20,   -24,   340,  -514,  -514,  -514,  -514,  -514,
    -514,  -514,  -514,  4002,   322,   168,  2455,  -514,   261,  -514,
    -514,  -514,  -514,   325,    -1,   262,   264,  -514,  2455,  -514,
     265,   266,  -514,  -514,   263,  -514,  -514,  2455,   271,  4256,
     -20,  2455,  -514,  -514,   149,   -20,  4066,   -20,   -20,  -514,
    4256,   149,  -514,  4256,   273,  -514,   -20,  -514,  -514,   274,
     -20,    80,   -20,  -514,  -514,  -514
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      35,    43,     0,     2,    36,    38,    11,    12,    13,    14,
      15,    16,    17,    19,    18,    44,    45,     1,    37,     0,
       0,    46,   112,   112,     0,     0,   115,     0,   113,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
      51,    58,    52,    53,    54,    55,    56,    57,    59,    60,
       0,    62,     0,    41,    39,     0,     0,   114,     3,     0,
       0,     0,     0,     0,     0,     0,     0,   112,    63,    47,
      50,    61,     0,     0,    42,    40,   112,   112,     0,    66,
       0,    70,    71,    64,    65,     0,     0,   112,   192,   193,
       0,     0,     0,     0,     0,     0,     0,   112,     0,     0,
       0,   180,   187,   186,   112,     0,     0,   188,   194,   195,
       0,     0,   112,     0,   112,   112,   112,   112,   196,     0,
     112,   112,   112,   112,   112,   112,   112,   112,     0,     0,
     112,     0,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   138,     0,   293,     0,     0,
     112,   119,     0,     0,   121,   122,   123,   125,   126,   127,
     129,   120,   124,   128,   191,   185,     0,   211,   197,   230,
     201,   202,   198,   241,   199,   242,   243,   244,   245,   246,
     203,   189,   205,   200,   190,   206,   210,   207,   208,   147,
     148,   209,   144,   152,   212,   153,     4,     0,     0,    74,
      72,     0,     0,     5,     0,     0,   179,   298,   112,   149,
     112,   112,   112,     0,   112,   130,   131,   112,     0,   168,
     132,   177,     0,     0,     0,   291,     0,   292,   204,     8,
      10,     9,   133,     0,     0,   112,     8,   139,   313,   145,
     146,     0,   150,   151,   218,   219,   278,   220,   112,   233,
     226,   225,   112,   223,     0,   221,   222,   224,   227,   229,
     228,   231,   232,   237,   239,     0,     0,    28,   217,     0,
       0,     0,   107,   185,     0,   182,   296,   217,     0,     0,
       0,   176,   118,   135,   137,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,     0,     0,     0,     0,
       0,   112,   112,     0,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   238,   240,     0,   136,   112,
       0,   112,     0,    27,    26,     0,     0,    79,     0,    75,
      78,    83,    83,    67,    69,     0,   112,     0,     0,     0,
       0,     0,   184,     0,     0,     0,   166,   167,   112,     0,
       0,     0,   112,   112,    20,     0,     0,   134,     0,   141,
     112,     0,   217,   112,   235,     0,    28,   112,     0,     6,
      29,    31,   216,   213,     0,   106,   112,   112,   294,   216,
     295,   300,     0,   289,   290,     0,   276,   279,   277,   259,
     257,   258,   261,   262,   268,   269,   263,   264,   265,   266,
     270,   271,   272,   273,   280,   281,   282,   283,   284,   267,
     274,   288,   287,   260,   247,   248,   275,   249,   250,   251,
     252,   253,   254,   255,   112,   112,     0,   302,     0,     0,
       0,     0,    98,     0,     0,    73,    77,     0,    86,    84,
      86,   178,     0,    68,     0,     0,     0,   112,   112,     0,
       0,   165,     0,     0,     0,     0,    21,     0,    22,     0,
       0,   143,     0,   234,   217,     0,     7,   285,    34,    32,
      30,     0,     0,   215,   112,   105,     0,     0,     0,   112,
       0,   112,     0,     0,     0,     0,   112,   305,   309,   306,
     308,     0,    99,   102,     0,    98,    80,    76,    85,     0,
      82,    87,     0,   297,   169,   173,   173,     0,   112,     0,
     157,   161,   158,     0,     0,     0,    23,    24,    25,     0,
       0,   236,     0,     0,   112,   112,     0,     0,   110,     0,
      98,   256,   286,   303,   304,   307,     0,     0,   101,     0,
       0,     0,     0,    88,    81,     0,     0,     0,   171,   172,
     112,   217,     0,     0,   162,   164,   315,   316,   317,   310,
     311,   312,    33,     0,   108,     0,   112,   299,     0,   301,
      95,    94,   100,   103,     0,    91,     0,   170,   112,   174,
       0,     0,   155,   159,     0,   163,   214,   112,     0,   111,
       0,   112,    93,    92,     0,     0,     0,     0,     0,   160,
     109,    98,    96,   104,     0,    89,     0,   154,   156,     0,
       0,   173,     0,    90,   175,    97
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -514,  -514,  -149,   -16,   341,  -140,   -97,     0,  -514,   310,
    -514,  -283,    54,  -514,    43,  -514,  -514,  -514,   420,  -514,
    -514,   398,  -514,  -514,   388,  -514,  -514,  -514,  -514,  -514,
    -514,  -514,  -514,  -514,  -514,  -514,  -514,   -17,  -514,  -514,
      86,  -514,   -15,  -514,  -514,  -514,  -492,  -514,  -498,  -514,
      56,   -19,  -514,  -514,  -514,   281,  -514,  -514,  -514,  -514,
    -514,  -514,  -514,  -514,  -514,  -513,  -130,  -514,    57,  -501,
     -37,  -514,   345,    17,  -334,  -434,   -45,  -514,  -135,  -514,
    -514,  -514,  -514,  -514,  -514,  -514,  -514,  -514,  -514,  -514,
    -514,  -514,  -514,  -514,  -514,  -514,  -514,  -514,  -514,  -514,
    -514,  -514,  -514,  -514,  -514,  -514,  -514
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    59,   337,   204,   334,   267,   146,   230,   231,
     227,   335,   379,   380,   381,   479,     3,     4,     5,    16,
      20,    25,    38,    39,    40,    41,    42,    43,    44,   348,
      45,    46,    47,    48,   200,   338,   339,   340,    49,    50,
     448,   449,   510,   511,    51,   147,   501,   502,   503,   271,
     272,   148,    28,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   522,   563,   564,   158,   159,   160,   161,   558,
     162,   163,   164,   165,   274,   351,   268,   167,   275,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      68,    15,   266,    27,    52,    78,    85,   269,   565,   278,
     196,    98,   452,   550,   228,   559,   196,   235,   382,    21,
      52,    22,   166,   517,     1,    23,   389,    55,    26,   385,
     270,    61,    62,    63,    64,    17,    66,   325,   326,   327,
     551,    57,   209,  -315,  -315,   327,    53,    72,   578,    73,
     582,   595,   218,   443,   586,    19,   198,   201,   202,   222,
     197,   341,   342,   221,    60,   101,   196,   233,   421,   237,
     238,   239,   240,   278,    58,   242,   243,   244,   245,   246,
     247,   249,   250,   383,    23,   253,    24,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   390,   386,   277,
     493,   552,   206,    67,    54,   166,   614,   556,   557,   490,
     225,   229,    65,   278,   236,   434,   435,   436,   361,   619,
     624,   384,   223,   224,   593,    67,   590,   361,   364,    71,
     234,   361,   364,    67,    69,   580,   241,    76,    74,   212,
      79,    75,   236,   265,    67,   251,   602,    77,   254,    80,
     362,   329,   330,   331,   332,   539,   279,   199,    81,   365,
     273,    82,   546,   365,     6,   349,   350,   352,   376,   354,
     418,    83,   355,     7,     8,     9,    10,    11,    12,    13,
      14,   439,   357,   441,    84,   265,   203,   210,   101,   207,
     369,   211,   214,   215,   219,   217,   252,   229,   216,   279,
     220,   229,   229,   372,   280,   451,     6,   374,   281,   414,
     415,   416,   417,   283,   333,     7,     8,     9,    10,    11,
      12,    13,    14,   284,   336,   196,   343,   345,   346,   344,
     353,   359,   360,   363,   368,   371,   366,   375,   278,   377,
     393,   394,   395,   396,   397,   398,   399,   400,   401,   402,
     403,   404,   405,   406,   407,   408,   409,   410,   411,   412,
     413,   378,   387,   391,   388,   229,   419,   420,   585,   423,
     424,   425,   426,   427,   428,   429,   430,   431,   432,   433,
     389,   478,   392,   442,   438,   444,   440,   495,   446,     6,
     447,   445,   598,   457,   492,   454,   458,   422,     7,     8,
       9,    10,    11,    12,    13,    14,   229,   229,   229,   229,
     229,   437,   463,   462,   524,   525,   464,   467,   469,   461,
     465,   529,   466,   530,   468,   471,   532,   470,   474,   472,
     475,   484,   477,   489,   496,   506,   229,   483,   505,   509,
     498,   500,    29,   513,   483,   229,    30,   453,   538,    31,
     521,   526,    32,    33,   533,   534,    26,   535,    34,   537,
     540,    35,    36,   542,   543,   547,   545,   487,   488,   548,
     549,   554,   555,   560,    97,    29,   567,   568,   229,    30,
     569,   570,    31,   278,   571,    32,    33,   575,   576,    26,
     494,    34,   229,   588,    35,    36,   574,   577,   579,    37,
     584,   597,   486,   600,   601,   604,   605,   607,   608,   583,
     508,   609,   352,   519,   611,   620,   622,   514,   515,   516,
     226,   205,   520,   480,    18,    56,   566,    70,   450,   507,
     476,   282,    37,   594,   236,   512,   572,   213,     0,   482,
       0,   485,     0,     0,     0,     0,   541,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,     0,     0,   504,
       0,     0,     0,     0,     0,   536,     0,     0,     0,     0,
       0,     0,   553,   561,     0,     0,   325,   326,   327,   318,
     319,   320,   321,   322,   323,   324,   -48,     0,   229,   349,
     573,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   325,   326,   327,     0,     0,
     581,     0,     0,     0,     0,   352,     0,     0,   587,   -49,
     589,     0,   504,   229,     0,   592,     0,     0,     0,     0,
       0,   599,     0,   229,     0,     0,   229,     0,     0,     0,
       0,     0,     0,   606,     0,     0,     0,   603,     0,   229,
       0,   229,   610,     0,     0,     0,   613,   504,     0,     0,
     270,     0,     0,   612,     0,   504,    85,     0,   615,   504,
     617,   618,    86,     0,    26,   229,     0,    88,    89,   621,
       0,     0,     0,   623,     0,   625,     0,     0,     0,     0,
       0,     0,     0,     0,     6,   101,   102,   103,     0,   105,
       0,   107,     0,     7,     8,     9,    10,    11,    12,    13,
      14,   108,   109,     0,     0,     0,     0,     0,   110,     0,
     111,   504,     0,     0,     0,     0,     0,     0,   504,   118,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,     0,     0,     0,     0,   122,   123,     0,     0,
       0,     0,     0,     0,     0,     0,   124,   125,   126,   127,
     128,   325,   326,   327,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,    85,     0,   142,
     143,   208,  -181,    86,     0,    26,    87,     0,    88,    89,
       0,     0,    90,    91,     0,     0,    92,    93,    94,    95,
      96,    97,    98,    99,   100,     6,   101,   102,   103,   104,
     105,   106,   107,     0,     7,     8,     9,    10,    11,    12,
      13,    14,   108,   109,     0,     0,     0,     0,     0,   110,
       0,   111,     0,     0,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,     0,     0,  -315,  -315,  -315,  -315,
    -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,
    -315,  -315,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,     0,     0,     0,     0,   122,   123,     0,
       0,     0,     0,     0,     0,     0,     0,   124,   125,   126,
     127,   128,   325,   326,   327,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,     0,     0,
     142,   143,   144,    85,   145,  -116,     0,     0,     0,    86,
       0,    26,    87,     0,    88,    89,     0,     0,    90,    91,
       0,     0,    92,    93,    94,    95,    96,    97,    98,    99,
     100,     6,   101,   102,   103,   104,   105,   106,   107,     0,
       7,     8,     9,    10,    11,    12,    13,    14,   108,   109,
       0,     0,     0,     0,     0,   110,     0,   111,     0,     0,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   122,   123,     0,     0,     0,     0,     0,
       0,     0,     0,   124,   125,   126,   127,   128,     0,     0,
       0,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,     0,     0,   142,   143,   144,    85,
     145,   276,     0,     0,     0,    86,     0,    26,    87,     0,
      88,    89,     0,     0,    90,    91,     0,     0,    92,    93,
      94,    95,    96,    97,    98,    99,   100,     6,   101,   102,
     103,   104,   105,   106,   107,     0,     7,     8,     9,    10,
      11,    12,    13,    14,   108,   109,     0,     0,     0,     0,
       0,   110,     0,   111,     0,     0,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   122,
     123,     0,     0,     0,     0,     0,     0,     0,     0,   124,
     125,   126,   127,   128,     0,     0,     0,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
       0,     0,   142,   143,   144,  -112,   145,  -117,    85,     0,
       0,     0,     0,     0,    86,     0,    26,     0,     0,    88,
      89,     0,     0,   481,    91,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,   101,   102,   103,
       0,   105,     0,   107,     0,     7,     8,     9,    10,    11,
      12,    13,    14,   108,   109,     0,     0,     0,     0,     0,
     110,    85,   111,     0,     0,     0,     0,    86,     0,    26,
       0,   118,    88,    89,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
     101,   102,   103,     0,   105,     0,   107,     0,     7,     8,
       9,    10,    11,    12,    13,    14,   108,   109,   122,   123,
       0,     0,     0,   110,     0,   111,     0,     0,   124,   125,
     126,   127,   128,     0,   118,     0,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,     0,
       0,   142,   143,   208,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   122,   123,     0,     0,     0,     0,     0,     0,     0,
       0,   124,   125,   126,   127,   128,     0,     0,     0,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,     0,     0,   142,   143,   208,  -112,     0,   276,
      85,     0,     0,     0,     0,     0,    86,     0,    26,     0,
       0,    88,    89,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     6,   101,
     102,   103,     0,   105,     0,   107,     0,     7,     8,     9,
      10,    11,    12,    13,    14,   108,   109,     0,     0,     0,
       0,     0,   110,    85,   111,     0,     0,     0,     0,    86,
       0,    26,     0,   118,    88,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,   101,   102,   103,     0,   105,     0,   107,     0,
       7,     8,     9,    10,    11,    12,    13,    14,   108,   109,
     122,   123,     0,     0,     0,   110,     0,   111,     0,     0,
     124,   125,   126,   127,   128,     0,   118,     0,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,     0,     0,   142,   143,   208,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   122,   123,     0,     0,     0,     0,     0,
       0,     0,     0,   124,   125,   126,   127,   128,     0,     0,
       0,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,     0,    85,   142,   143,   208,     0,
     232,    86,     0,    26,     0,     0,    88,    89,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,   101,   102,   103,     0,   105,     0,
     107,     0,     7,     8,     9,    10,    11,    12,    13,    14,
     108,   109,     0,     0,     0,     0,     0,   110,    85,   111,
       0,     0,     0,     0,    86,     0,    26,     0,   118,    88,
      89,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,   101,   102,   103,
       0,   105,     0,   107,     0,     7,     8,     9,    10,    11,
      12,    13,    14,   108,   109,   122,   123,     0,     0,     0,
     110,     0,   111,     0,     0,   124,   125,   126,   127,   128,
       0,   118,     0,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,     0,     0,   142,   143,
     208,     0,  -140,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   122,   123,
       0,     0,     0,     0,     0,     0,     0,     0,   124,   125,
     126,   127,   128,     0,     0,     0,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,     0,
      85,   142,   143,   208,     0,  -314,    86,     0,    26,     0,
       0,    88,    89,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     6,   101,
     102,   103,     0,   105,     0,   107,     0,     7,     8,     9,
      10,    11,    12,    13,    14,   108,   109,     0,     0,     0,
       0,     0,   110,    85,   111,     0,     0,     0,     0,    86,
       0,    26,     0,   118,    88,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,   101,   102,   103,     0,   105,     0,   107,     0,
       7,     8,     9,    10,    11,    12,    13,    14,   108,   109,
     122,   123,     0,     0,     0,   110,     0,   111,     0,     0,
     124,   125,   126,   127,   128,     0,   118,     0,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,     0,     0,   142,   143,   208,     0,  -183,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   122,   123,     0,     0,     0,     0,     0,
       0,     0,     0,   124,   125,   126,   127,   128,     0,     0,
       0,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,     0,    85,   142,   143,   208,     0,
    -142,    86,     0,    26,     0,     0,    88,    89,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,   101,   102,   103,     0,   105,     0,
     107,     0,     7,     8,     9,    10,    11,    12,    13,    14,
     108,   109,     0,     0,     0,     0,     0,   110,    85,   111,
       0,     0,     0,     0,    86,     0,    26,     0,   118,    88,
      89,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,   101,   102,   103,
       0,   105,     0,   107,     0,     7,     8,     9,    10,    11,
      12,    13,    14,   108,   109,   122,   123,     0,     0,     0,
     110,     0,   111,     0,     0,   124,   125,   126,   127,   128,
       0,   118,     0,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,     0,     0,   142,   143,
     208,   466,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   122,   123,
       0,     0,     0,     0,     0,     0,     0,     0,   124,   125,
     126,   127,   128,     0,     0,     0,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,    85,
       0,   142,   143,   208,   468,    86,   265,    26,     0,     0,
      88,    89,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6,   101,   102,
     103,     0,   105,     0,   107,     0,     7,     8,     9,    10,
      11,    12,    13,    14,   108,   109,     0,     0,     0,     0,
       0,   110,    85,   111,     0,     0,     0,     0,    86,   265,
      26,     0,   118,    88,    89,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       6,   101,   102,   103,     0,   105,     0,   107,     0,     7,
       8,     9,    10,    11,    12,    13,    14,   108,   109,   122,
     123,     0,     0,     0,   110,     0,   111,     0,     0,   124,
     125,   126,   127,   128,     0,   118,     0,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
       0,  -181,   142,   143,   208,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   122,   123,     0,     0,     0,     0,     0,     0,
       0,     0,   124,   125,   126,   127,   128,     0,     0,     0,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,     0,     0,   142,   143,   208,    85,     0,
       0,   347,     0,     0,    86,     0,    26,     0,     0,    88,
      89,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,   101,   102,   103,
       0,   105,     0,   107,     0,     7,     8,     9,    10,    11,
      12,    13,    14,   108,   109,     0,     0,     0,     0,     0,
     110,    85,   111,     0,     0,     0,     0,    86,     0,    26,
       0,   118,    88,    89,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
     101,   102,   103,     0,   105,     0,   107,     0,     7,     8,
       9,    10,    11,    12,    13,    14,   108,   109,   122,   123,
       0,     0,     0,   110,     0,   111,     0,     0,   124,   125,
     126,   127,   128,     0,   118,     0,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,     0,
       0,   142,   143,   208,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   122,   123,     0,     0,     0,     0,     0,     0,     0,
       0,   124,   125,   126,   127,   128,     0,     0,     0,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,    85,  -181,   142,   143,   208,     0,    86,     0,
      26,     0,     0,    88,    89,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       6,   101,   102,   103,     0,   105,     0,   107,     0,     7,
       8,     9,    10,    11,    12,    13,    14,   108,   109,     0,
       0,     0,     0,     0,   110,    85,   111,     0,     0,     0,
       0,    86,     0,    26,     0,   118,    88,    89,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,   101,   102,   103,     0,   105,     0,
     107,     0,     7,     8,     9,    10,    11,    12,    13,    14,
     108,   109,   122,   123,     0,     0,     0,   110,     0,   111,
       0,     0,   124,   125,   126,   127,   128,     0,   118,     0,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,     0,  -183,   142,   143,   208,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   122,   123,     0,     0,     0,
       0,     0,     0,     0,     0,   124,   125,   126,   127,   128,
       0,     0,     0,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,    85,     0,   142,   143,
     208,     0,    86,     0,    26,     0,     0,    88,    89,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,   101,   102,   103,     0,   105,
       0,   107,     0,     7,     8,     9,    10,    11,    12,    13,
      14,   108,   109,     0,     0,     0,     0,     0,   110,    85,
     111,     0,     0,     0,     0,    86,     0,    26,     0,   118,
      88,    89,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6,   101,   102,
     103,     0,   105,     0,   107,     0,     7,     8,     9,    10,
      11,    12,    13,    14,   108,   109,   122,   123,     0,     0,
       0,   110,     0,   111,     0,     0,   124,   125,   126,   127,
     128,     0,   118,     0,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,     0,     0,   142,
     143,   248,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   122,
     123,     0,     0,     0,     0,     0,     0,     0,     0,   124,
     125,   126,   127,   128,     0,     0,     0,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
      85,     0,   142,   143,   373,     0,    86,     0,    26,     0,
       0,    88,    89,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     6,   101,
     102,   103,     0,   105,     0,   107,     0,     7,     8,     9,
      10,    11,    12,    13,    14,   108,   109,     0,     0,     0,
       0,     0,   110,     0,   111,     0,     0,     0,     0,     0,
       0,     0,     0,   118,     0,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,     0,     0,     0,     0,
     122,   123,     0,     0,     0,     0,     0,     0,     0,     0,
     124,   125,   126,   127,   128,   325,   326,   327,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,     0,     0,   142,   143,   518,   285,   286,   287,     0,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   325,   326,   327,     0,
       0,     0,   285,   286,   287,   473,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   325,   326,   327,     0,     0,     0,   285,   286,
     287,   531,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   325,   326,
     327,     0,     0,     0,   285,   286,   287,   591,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   325,   326,   327,     0,     0,   285,
     286,   287,   328,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   325,
     326,   327,     0,     0,   285,   286,   287,   367,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   325,   326,   327,     0,   285,   286,
     287,   497,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   325,   326,
     327,     0,   285,   286,   287,   499,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   325,   326,   327,     0,   285,   286,   287,   527,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   325,   326,   327,     0,
     285,   286,   287,   528,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     325,   326,   327,     0,     0,     0,   358,   544,   285,   286,
     287,     0,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   325,   326,
     327,   370,     0,   285,   286,   287,     0,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   325,   326,   327,   523,     0,   285,   286,
     287,     0,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   325,   326,
     327,   285,   286,   287,     0,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   325,   326,   327,   455,   285,   286,   287,     0,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   325,   326,   327,   456,   285,
     286,   287,     0,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   325,
     326,   327,   459,   285,   286,   287,     0,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   325,   326,   327,   460,   285,   286,   287,
       0,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   325,   326,   327,
     562,   285,   286,   287,     0,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   325,   326,   327,   596,   285,   286,   287,     0,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   325,   326,   327,   616,   285,
     286,   287,   356,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   325,
     326,   327,   285,   286,   287,   491,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   325,   326,   327,   285,   286,   287,     0,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   325,   326,   327,   287,     0,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   325,   326,   327,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   325,   326,   327,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   325,
     326,   327,  -315,  -315,  -315,  -315,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   325,   326,   327
};

static const yytype_int16 yycheck[] =
{
      37,     1,   142,    22,    23,    12,    10,   142,   521,   144,
      38,    35,   346,   505,   111,   516,    38,   114,    77,    19,
      39,    82,    67,   457,     3,   145,    77,   147,    18,    77,
       4,    31,    32,    33,    34,     0,    36,   139,   140,   141,
      82,    18,    87,   139,   140,   141,    57,     7,   540,     9,
     548,   564,    97,   336,   552,    65,    72,    76,    77,   104,
      82,   201,   202,   100,    39,    39,    38,   112,    40,   114,
     115,   116,   117,   208,    38,   120,   121,   122,   123,   124,
     125,   126,   127,   142,   145,   130,   147,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   148,   146,   144,
     434,   143,    85,   145,    57,   150,   604,    27,    28,   392,
     110,   111,    40,   248,   114,   143,   144,   145,   112,   611,
     621,   270,   105,   106,   148,   145,   560,   112,   113,   147,
     113,   112,   113,   145,   148,   147,   119,    82,    57,   143,
     147,    57,   142,    17,   145,   128,   147,    82,   131,    12,
     144,   144,   145,   144,   145,   489,   141,   145,   147,   144,
     143,   147,   496,   144,    38,   210,   211,   212,   265,   214,
     310,   147,   217,    47,    48,    49,    50,    51,    52,    53,
      54,   330,   219,   332,   147,    17,    38,   143,    39,    38,
     235,   143,   143,   147,    82,   143,   122,   197,   147,   141,
     147,   201,   202,   248,     7,   345,    38,   252,   148,   306,
     307,   308,   309,   147,    46,    47,    48,    49,    50,    51,
      52,    53,    54,   147,    82,    38,   147,    82,   143,   147,
     143,   141,   141,   144,   141,   141,   144,   141,   373,   142,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,    63,    82,   279,   146,   265,   311,   312,   551,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
      77,   378,    82,   143,   329,    79,   331,   436,    77,    38,
       5,   148,   575,   147,   434,   142,   122,   313,    47,    48,
      49,    50,    51,    52,    53,    54,   306,   307,   308,   309,
     310,   327,   145,   358,   463,   464,   145,   362,   363,   356,
     112,   470,   146,   472,   146,   370,   475,   145,   373,   145,
     145,    82,   377,   143,   143,    40,   336,   382,   143,     6,
     148,   148,     4,   142,   389,   345,     8,   347,   488,    11,
     145,   112,    14,    15,    86,   143,    18,    77,    20,     7,
     143,    23,    24,   142,   142,   142,   148,   386,   387,    77,
      82,   147,    28,   147,    34,     4,   148,   148,   378,     8,
     148,   148,    11,   518,   148,    14,    15,    82,    79,    18,
     435,    20,   392,   143,    23,    24,   536,   142,   142,    61,
     142,    79,   385,   142,    79,   143,   142,   142,   142,   549,
     447,   148,   457,   458,   143,   142,   142,   454,   455,   456,
     110,    80,   459,   380,     4,    27,   523,    39,   342,   446,
     376,   150,    61,   563,   434,   450,   533,    92,    -1,   382,
      -1,   385,    -1,    -1,    -1,    -1,   491,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,    -1,    -1,   442,
      -1,    -1,    -1,    -1,    -1,   484,    -1,    -1,    -1,    -1,
      -1,    -1,   509,   518,    -1,    -1,   139,   140,   141,   113,
     114,   115,   116,   117,   118,   119,   148,    -1,   488,   534,
     535,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   139,   140,   141,    -1,    -1,
     547,    -1,    -1,    -1,    -1,   560,    -1,    -1,   555,   148,
     557,    -1,   505,   523,    -1,   562,    -1,    -1,    -1,    -1,
      -1,   576,    -1,   533,    -1,    -1,   536,    -1,    -1,    -1,
      -1,    -1,    -1,   588,    -1,    -1,    -1,   584,    -1,   549,
      -1,   551,   597,    -1,    -1,    -1,   601,   540,    -1,    -1,
       4,    -1,    -1,   600,    -1,   548,    10,    -1,   605,   552,
     607,   608,    16,    -1,    18,   575,    -1,    21,    22,   616,
      -1,    -1,    -1,   620,    -1,   622,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,
      -1,    45,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    62,    -1,
      64,   604,    -1,    -1,    -1,    -1,    -1,    -1,   611,    73,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,    -1,    -1,    -1,    -1,   110,   111,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   120,   121,   122,   123,
     124,   139,   140,   141,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,    10,    -1,   143,
     144,   145,   146,    16,    -1,    18,    19,    -1,    21,    22,
      -1,    -1,    25,    26,    -1,    -1,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,    62,
      -1,    64,    -1,    -1,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    -1,    -1,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,    -1,    -1,    -1,    -1,   110,   111,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,   121,   122,
     123,   124,   139,   140,   141,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,    -1,    -1,
     143,   144,   145,    10,   147,   148,    -1,    -1,    -1,    16,
      -1,    18,    19,    -1,    21,    22,    -1,    -1,    25,    26,
      -1,    -1,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    62,    -1,    64,    -1,    -1,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   110,   111,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   120,   121,   122,   123,   124,    -1,    -1,
      -1,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,    -1,    -1,   143,   144,   145,    10,
     147,   148,    -1,    -1,    -1,    16,    -1,    18,    19,    -1,
      21,    22,    -1,    -1,    25,    26,    -1,    -1,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    62,    -1,    64,    -1,    -1,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,
     111,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,
     121,   122,   123,   124,    -1,    -1,    -1,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
      -1,    -1,   143,   144,   145,     7,   147,   148,    10,    -1,
      -1,    -1,    -1,    -1,    16,    -1,    18,    -1,    -1,    21,
      22,    -1,    -1,    25,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      -1,    43,    -1,    45,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
      62,    10,    64,    -1,    -1,    -1,    -1,    16,    -1,    18,
      -1,    73,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    -1,    43,    -1,    45,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,   110,   111,
      -1,    -1,    -1,    62,    -1,    64,    -1,    -1,   120,   121,
     122,   123,   124,    -1,    73,    -1,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,    -1,
      -1,   143,   144,   145,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   110,   111,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   120,   121,   122,   123,   124,    -1,    -1,    -1,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,    -1,    -1,   143,   144,   145,     7,    -1,   148,
      10,    -1,    -1,    -1,    -1,    -1,    16,    -1,    18,    -1,
      -1,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    -1,    43,    -1,    45,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    -1,    -1,
      -1,    -1,    62,    10,    64,    -1,    -1,    -1,    -1,    16,
      -1,    18,    -1,    73,    21,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    41,    -1,    43,    -1,    45,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
     110,   111,    -1,    -1,    -1,    62,    -1,    64,    -1,    -1,
     120,   121,   122,   123,   124,    -1,    73,    -1,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,    -1,    -1,   143,   144,   145,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   110,   111,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   120,   121,   122,   123,   124,    -1,    -1,
      -1,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,    -1,    10,   143,   144,   145,    -1,
     147,    16,    -1,    18,    -1,    -1,    21,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,    -1,
      45,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    62,    10,    64,
      -1,    -1,    -1,    -1,    16,    -1,    18,    -1,    73,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      -1,    43,    -1,    45,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,   110,   111,    -1,    -1,    -1,
      62,    -1,    64,    -1,    -1,   120,   121,   122,   123,   124,
      -1,    73,    -1,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,    -1,    -1,   143,   144,
     145,    -1,   147,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,   111,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,   121,
     122,   123,   124,    -1,    -1,    -1,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,    -1,
      10,   143,   144,   145,    -1,   147,    16,    -1,    18,    -1,
      -1,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    -1,    43,    -1,    45,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    -1,    -1,
      -1,    -1,    62,    10,    64,    -1,    -1,    -1,    -1,    16,
      -1,    18,    -1,    73,    21,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    41,    -1,    43,    -1,    45,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
     110,   111,    -1,    -1,    -1,    62,    -1,    64,    -1,    -1,
     120,   121,   122,   123,   124,    -1,    73,    -1,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,    -1,    -1,   143,   144,   145,    -1,   147,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   110,   111,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   120,   121,   122,   123,   124,    -1,    -1,
      -1,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,    -1,    10,   143,   144,   145,    -1,
     147,    16,    -1,    18,    -1,    -1,    21,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,    -1,
      45,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    62,    10,    64,
      -1,    -1,    -1,    -1,    16,    -1,    18,    -1,    73,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      -1,    43,    -1,    45,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,   110,   111,    -1,    -1,    -1,
      62,    -1,    64,    -1,    -1,   120,   121,   122,   123,   124,
      -1,    73,    -1,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,    -1,    -1,   143,   144,
     145,   146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,   111,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,   121,
     122,   123,   124,    -1,    -1,    -1,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,    10,
      -1,   143,   144,   145,   146,    16,    17,    18,    -1,    -1,
      21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,
      41,    -1,    43,    -1,    45,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    62,    10,    64,    -1,    -1,    -1,    -1,    16,    17,
      18,    -1,    73,    21,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    41,    -1,    43,    -1,    45,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,   110,
     111,    -1,    -1,    -1,    62,    -1,    64,    -1,    -1,   120,
     121,   122,   123,   124,    -1,    73,    -1,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
      -1,   142,   143,   144,   145,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   110,   111,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   120,   121,   122,   123,   124,    -1,    -1,    -1,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,    -1,    -1,   143,   144,   145,    10,    -1,
      -1,    13,    -1,    -1,    16,    -1,    18,    -1,    -1,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      -1,    43,    -1,    45,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
      62,    10,    64,    -1,    -1,    -1,    -1,    16,    -1,    18,
      -1,    73,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    -1,    43,    -1,    45,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,   110,   111,
      -1,    -1,    -1,    62,    -1,    64,    -1,    -1,   120,   121,
     122,   123,   124,    -1,    73,    -1,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,    -1,
      -1,   143,   144,   145,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   110,   111,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   120,   121,   122,   123,   124,    -1,    -1,    -1,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,    10,   142,   143,   144,   145,    -1,    16,    -1,
      18,    -1,    -1,    21,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    41,    -1,    43,    -1,    45,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    -1,
      -1,    -1,    -1,    -1,    62,    10,    64,    -1,    -1,    -1,
      -1,    16,    -1,    18,    -1,    73,    21,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,    -1,
      45,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,   110,   111,    -1,    -1,    -1,    62,    -1,    64,
      -1,    -1,   120,   121,   122,   123,   124,    -1,    73,    -1,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,    -1,   142,   143,   144,   145,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   110,   111,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   120,   121,   122,   123,   124,
      -1,    -1,    -1,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,    10,    -1,   143,   144,
     145,    -1,    16,    -1,    18,    -1,    -1,    21,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,
      -1,    45,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    62,    10,
      64,    -1,    -1,    -1,    -1,    16,    -1,    18,    -1,    73,
      21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,
      41,    -1,    43,    -1,    45,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,   110,   111,    -1,    -1,
      -1,    62,    -1,    64,    -1,    -1,   120,   121,   122,   123,
     124,    -1,    73,    -1,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,    -1,    -1,   143,
     144,   145,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,
     111,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,
     121,   122,   123,   124,    -1,    -1,    -1,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
      10,    -1,   143,   144,   145,    -1,    16,    -1,    18,    -1,
      -1,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    -1,    43,    -1,    45,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    -1,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,    -1,    -1,    -1,    -1,
     110,   111,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     120,   121,   122,   123,   124,   139,   140,   141,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,    -1,    -1,   143,   144,   145,    79,    80,    81,    -1,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   139,   140,   141,    -1,
      -1,    -1,    79,    80,    81,   148,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   139,   140,   141,    -1,    -1,    -1,    79,    80,
      81,   148,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,   140,
     141,    -1,    -1,    -1,    79,    80,    81,   148,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   139,   140,   141,    -1,    -1,    79,
      80,    81,   147,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,
     140,   141,    -1,    -1,    79,    80,    81,   147,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   139,   140,   141,    -1,    79,    80,
      81,   146,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,   140,
     141,    -1,    79,    80,    81,   146,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   139,   140,   141,    -1,    79,    80,    81,   146,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   139,   140,   141,    -1,
      79,    80,    81,   146,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     139,   140,   141,    -1,    -1,    -1,    77,   146,    79,    80,
      81,    -1,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,   140,
     141,    77,    -1,    79,    80,    81,    -1,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   139,   140,   141,    77,    -1,    79,    80,
      81,    -1,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,   140,
     141,    79,    80,    81,    -1,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   139,   140,   141,   142,    79,    80,    81,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   139,   140,   141,   142,    79,
      80,    81,    -1,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,
     140,   141,   142,    79,    80,    81,    -1,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   139,   140,   141,   142,    79,    80,    81,
      -1,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,   140,   141,
     142,    79,    80,    81,    -1,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   139,   140,   141,   142,    79,    80,    81,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   139,   140,   141,   142,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,
     140,   141,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   139,   140,   141,    79,    80,    81,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   139,   140,   141,    81,    -1,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   139,   140,   141,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   139,   140,   141,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,
     140,   141,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   139,   140,   141
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,   150,   165,   166,   167,    38,    47,    48,    49,
      50,    51,    52,    53,    54,   156,   168,     0,   167,    65,
     169,   156,    82,   145,   147,   170,    18,   200,   201,     4,
       8,    11,    14,    15,    20,    23,    24,    61,   171,   172,
     173,   174,   175,   176,   177,   179,   180,   181,   182,   187,
     188,   193,   200,    57,    57,   147,   170,    18,    38,   151,
      39,   156,   156,   156,   156,    40,   156,   145,   219,   148,
     173,   147,     7,     9,    57,    57,    82,    82,    12,   147,
      12,   147,   147,   147,   147,    10,    16,    19,    21,    22,
      25,    26,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    39,    40,    41,    42,    43,    44,    45,    55,    56,
      62,    64,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,   110,   111,   120,   121,   122,   123,   124,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   143,   144,   145,   147,   156,   194,   200,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   214,   215,
     216,   217,   219,   220,   221,   222,   225,   226,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,    38,    82,   152,   145,
     183,   200,   200,    38,   153,   153,   222,    38,   145,   225,
     143,   143,   143,   221,   143,   147,   147,   143,   225,    82,
     147,   219,   225,   222,   222,   156,   158,   159,   155,   156,
     157,   158,   147,   225,   222,   155,   156,   225,   225,   225,
     225,   222,   225,   225,   225,   225,   225,   225,   145,   225,
     225,   222,   122,   225,   222,   225,   225,   225,   225,   225,
     225,   225,   225,   225,   225,    17,   154,   155,   225,   227,
       4,   198,   199,   222,   223,   227,   148,   225,   227,   141,
       7,   148,   204,   147,   147,    79,    80,    81,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   139,   140,   141,   147,   144,
     145,   144,   145,    46,   154,   160,    82,   152,   184,   185,
     186,   154,   154,   147,   147,    82,   143,    13,   178,   225,
     225,   224,   225,   143,   225,   225,    82,   219,    77,   141,
     141,   112,   144,   144,   113,   144,   144,   147,   141,   225,
      77,   141,   225,   145,   225,   141,   155,   142,    63,   161,
     162,   163,    77,   142,   151,    77,   146,    82,   146,    77,
     148,   152,    82,   225,   225,   225,   225,   225,   225,   225,
     225,   225,   225,   225,   225,   225,   225,   225,   225,   225,
     225,   225,   225,   225,   155,   155,   155,   155,   154,   225,
     225,    40,   152,   225,   225,   225,   225,   225,   225,   225,
     225,   225,   225,   225,   143,   144,   145,   152,   225,   151,
     225,   151,   143,   160,    79,   148,    77,     5,   189,   190,
     189,   154,   223,   156,   142,   142,   142,   147,   122,   142,
     142,   219,   225,   145,   145,   112,   146,   225,   146,   225,
     145,   225,   145,   148,   225,   145,   161,   225,   155,   164,
     163,    25,   217,   225,    82,   199,   222,   200,   200,   143,
     160,    82,   154,   223,   225,   151,   143,   146,   148,   146,
     148,   195,   196,   197,   222,   143,    40,   186,   219,     6,
     191,   192,   191,   142,   219,   219,   219,   224,   145,   225,
     219,   145,   211,    77,   151,   151,   112,   146,   146,   151,
     151,   148,   151,    86,   143,    77,   200,     7,   154,   223,
     143,   225,   142,   142,   146,   148,   223,   142,    77,    82,
     195,    82,   143,   219,   147,    28,    27,    28,   218,   218,
     147,   225,   142,   212,   213,   214,   155,   148,   148,   148,
     148,   148,   155,   225,   154,    82,    79,   142,   195,   142,
     147,   219,   197,   154,   142,   160,   197,   219,   143,   219,
     224,   148,   219,   148,   215,   214,   142,    79,   160,   225,
     142,    79,   147,   219,   143,   142,   225,   142,   142,   148,
     225,   143,   219,   225,   197,   219,   142,   219,   219,   195,
     142,   219,   142,   219,   218,   219
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   149,   150,   151,   152,   153,   154,   154,   155,   155,
     155,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     157,   158,   158,   158,   159,   159,   160,   160,   161,   161,
     162,   162,   163,   164,   164,   165,   165,   166,   166,   167,
     167,   167,   167,   168,   168,   169,   169,   170,   171,   171,
     172,   172,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   174,   175,   176,   177,   177,   178,   179,
     180,   181,   182,   183,   184,   184,   185,   185,   185,   186,
     186,   187,   188,   189,   189,   190,   191,   191,   192,   192,
     192,   192,   193,   193,   193,   193,   194,   194,   195,   195,
     196,   196,   196,   197,   197,   198,   198,   198,   199,   199,
     199,   199,   200,   200,   201,   201,   202,   202,   203,   203,
     204,   204,   204,   204,   204,   204,   204,   204,   204,   204,
     204,   204,   204,   204,   204,   204,   204,   204,   204,   205,
     205,   205,   205,   205,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   207,   208,   208,   209,   210,   211,
     211,   212,   212,   213,   213,   214,   214,   215,   215,   216,
     216,   217,   217,   218,   218,   218,   219,   220,   221,   221,
     222,   223,   223,   224,   224,   225,   225,   225,   225,   225,
     225,   225,   225,   225,   225,   225,   225,   225,   225,   225,
     225,   225,   225,   225,   225,   225,   225,   225,   225,   225,
     225,   225,   225,   226,   226,   227,   227,   227,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   229,   229,   229,   229,   230,   230,   231,
     231,   232,   232,   232,   232,   232,   232,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   234,   235,   235,   235,
     235,   236,   236,   236,   236,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   237,   238,   238,   238,   239,
     240,   240,   240,   240,   240,   241,   241,   242,   242,   243,
     243,   244,   244,   244,   245,   245,   245,   246,   246,   246,
     246,   246,   246,   246,   247,   247,   247,   248,   248,   248,
     249,   250,   251,   252,   252,   253,   254,   255
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     2,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     3,     3,     4,     4,     4,     1,     1,     0,     1,
       2,     1,     2,     3,     1,     0,     1,     2,     1,     5,
       7,     5,     7,     0,     1,     0,     2,     3,     0,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     2,     3,     3,     3,     5,     2,     5,
       3,     3,     3,     3,     0,     1,     3,     2,     1,     1,
       3,     8,     7,     0,     1,     2,     0,     1,     2,     5,
       7,     3,     9,     9,     8,     8,     8,    11,     0,     1,
       3,     2,     1,     3,     5,     3,     2,     1,     5,     7,
       4,     6,     0,     1,     2,     1,     0,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     2,     3,     2,     2,     2,     1,     2,
       1,     3,     2,     4,     1,     2,     2,     1,     1,     2,
       2,     2,     1,     1,     9,     7,     9,     5,     5,     3,
       4,     0,     1,     2,     1,     4,     3,     3,     2,     5,
       7,     6,     6,     0,     2,     6,     3,     2,     4,     2,
       1,     0,     1,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     7,     3,     2,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       1,     2,     2,     2,     4,     3,     5,     2,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     5,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     3,     4,     5,     3,     3,     3,
       3,     2,     2,     1,     3,     3,     2,     5,     2,     6,
       3,     6,     3,     5,     5,     4,     4,     5,     4,     4,
       6,     6,     6,     2,     1,     6,     6,     6
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
#line 2636 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 11:
#line 107 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[0].opval));
    }
#line 2644 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 12:
#line 111 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_byte_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2654 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 13:
#line 117 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_short_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2664 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 14:
#line 123 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2674 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 15:
#line 129 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_long_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2684 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 16:
#line 135 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_float_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2694 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 17:
#line 141 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_double_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2704 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 18:
#line 147 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_any_object_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = op_type;
    }
#line 2713 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 19:
#line 152 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_string_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 2723 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 20:
#line 160 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[-1].opval));
    }
#line 2731 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 21:
#line 166 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-2].opval), NULL, 0);
    }
#line 2739 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 22:
#line 170 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-2].opval), NULL, 0);
    }
#line 2747 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 23:
#line 174 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), NULL, 1);
    }
#line 2756 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 24:
#line 181 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval), 0);
    }
#line 2764 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 25:
#line 185 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval), 0);
    }
#line 2772 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 27:
#line 192 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_void_type(compiler, compiler->current_file, compiler->current_line);
    }
#line 2780 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 28:
#line 198 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
#line 2788 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 32:
#line 209 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 2796 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 33:
#line 215 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2814 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 34:
#line 229 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 2822 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 35:
#line 235 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 2830 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 36:
#line 239 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2845 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 37:
#line 252 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2863 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 39:
#line 269 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), NULL, (yyvsp[-2].opval));
    }
#line 2871 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 40:
#line 273 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[-4].opval));
    }
#line 2879 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 41:
#line 277 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), NULL, NULL, (yyvsp[-2].opval));
    }
#line 2887 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 42:
#line 281 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), NULL, (yyvsp[-2].opval), (yyvsp[-4].opval));
    }
#line 2895 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 43:
#line 287 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 2903 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 45:
#line 294 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 2911 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 46:
#line 298 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_extends(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 2919 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 47:
#line 304 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_class_block;
    }
#line 2929 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 48:
#line 312 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 2937 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 49:
#line 316 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[0].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
        SPVM_OP_insert_child(compiler, (yyval.opval), (yyval.opval)->last, (yyvsp[0].opval));
      }
    }
#line 2951 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 50:
#line 328 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2969 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 63:
#line 358 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    { 
      (yyval.opval) = SPVM_OP_build_init_statement(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 2977 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 64:
#line 364 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_version_decl(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2985 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 65:
#line 370 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_version_from(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2993 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 66:
#line 376 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      int32_t is_require = 0;
      SPVM_OP* op_name_class_alias = NULL;
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), op_name_class_alias, is_require);
    }
#line 3003 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 67:
#line 382 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      int32_t is_require = 0;
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), is_require);
    }
#line 3012 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 68:
#line 389 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, compiler->current_file, compiler->current_line);
      int32_t is_require = 1;
      (yyval.opval) = SPVM_OP_build_use(compiler, op_use, (yyvsp[0].opval), NULL, is_require);
    }
#line 3022 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 69:
#line 397 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_alias(compiler, op_use, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3031 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 70:
#line 404 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_allow(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3039 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 71:
#line 410 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_interface_statement(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3047 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 72:
#line 416 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), (yyvsp[-2].opval));
    }
#line 3055 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 73:
#line 422 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_enum_block;
    }
#line 3065 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 74:
#line 430 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3073 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 75:
#line 434 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3088 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 76:
#line 447 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3106 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 79:
#line 465 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_item(compiler, (yyvsp[0].opval), NULL);
    }
#line 3114 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 80:
#line 469 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_item(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3122 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 81:
#line 475 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class_var(compiler, (yyvsp[-7].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3130 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 82:
#line 481 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_field(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3138 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 83:
#line 487 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 3146 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 85:
#line 494 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_return_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      SPVM_OP* op_arg = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_accessor(compiler, (yyvsp[-1].opval), op_arg, (yyvsp[0].opval), op_return_type);
    }
#line 3156 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 86:
#line 502 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 3164 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 88:
#line 509 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_return_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      SPVM_OP* op_arg = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_accessor(compiler, (yyvsp[-1].opval), op_arg, (yyvsp[0].opval), op_return_type);
    }
#line 3174 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 89:
#line 515 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_return_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_accessor(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval), op_return_type);
    }
#line 3183 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 90:
#line 520 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_accessor(compiler, (yyvsp[-6].opval), (yyvsp[-2].opval), (yyvsp[0].opval), (yyvsp[-4].opval));
    }
#line 3191 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 91:
#line 524 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_arg = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      SPVM_OP* op_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_accessor(compiler, (yyvsp[-2].opval), op_arg, op_block, (yyvsp[0].opval));
    }
#line 3201 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 92:
#line 532 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-8].opval), (yyvsp[0].opval));
     }
#line 3209 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 93:
#line 536 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-8].opval), NULL);
     }
#line 3217 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 94:
#line 540 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-6].opval), NULL, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-7].opval), (yyvsp[0].opval));
     }
#line 3225 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 95:
#line 544 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-6].opval), NULL, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-7].opval), NULL);
     }
#line 3233 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 96:
#line 550 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-6].opval), NULL, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-7].opval), (yyvsp[0].opval));
     }
#line 3241 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 97:
#line 554 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3260 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 98:
#line 571 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3268 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 99:
#line 575 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3283 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 100:
#line 588 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3301 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 103:
#line 606 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[-2].opval), (yyvsp[0].opval), NULL, NULL);
    }
#line 3309 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 104:
#line 610 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), NULL, (yyvsp[0].opval));
    }
#line 3317 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 105:
#line 616 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3335 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 108:
#line 634 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_anon_method_field(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 3343 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 109:
#line 638 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_anon_method_field(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3351 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 110:
#line 642 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_FIELD, (yyvsp[-3].opval)->file, (yyvsp[-3].opval)->line);
      
      (yyval.opval) = SPVM_OP_build_anon_method_field(compiler, op_field, NULL, (yyvsp[-1].opval), (yyvsp[0].opval), (yyvsp[-3].opval));
    }
#line 3361 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 111:
#line 648 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_FIELD, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      
      (yyval.opval) = SPVM_OP_build_anon_method_field(compiler, op_field, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3371 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 112:
#line 656 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3379 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 113:
#line 660 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3394 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 114:
#line 673 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3412 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 116:
#line 690 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3420 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 117:
#line 694 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3435 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 118:
#line 707 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3453 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 133:
#line 737 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[-1].opval), NULL);
    }
#line 3461 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 134:
#line 741 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3469 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 136:
#line 746 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_operator_statement(compiler, (yyvsp[-1].opval));
    }
#line 3477 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 138:
#line 751 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
#line 3485 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 139:
#line 757 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 3493 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 140:
#line 761 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[0].opval), NULL, NULL);
    }
#line 3501 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 141:
#line 765 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-2].opval), (yyvsp[0].opval), (yyvsp[-1].opval));
    }
#line 3509 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 142:
#line 769 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-1].opval), NULL, (yyvsp[0].opval));
    }
#line 3517 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 143:
#line 773 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-3].opval), (yyvsp[0].opval), (yyvsp[-2].opval));
    }
#line 3525 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 145:
#line 780 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_print(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3533 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 146:
#line 784 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_print(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3541 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 149:
#line 790 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_make_read_only(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3549 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 150:
#line 794 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enable_options(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3557 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 151:
#line 798 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_disable_options(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3565 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 154:
#line 806 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[-8].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3573 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 155:
#line 812 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_foreach_statement(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3581 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 156:
#line 816 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_foreach_statement(compiler, (yyvsp[-8].opval), (yyvsp[-7].opval), (yyvsp[-3].opval), (yyvsp[0].opval));
    }
#line 3589 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 157:
#line 822 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3597 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 158:
#line 828 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3605 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 159:
#line 834 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[-1].opval), NULL);
    }
#line 3614 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 160:
#line 839 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3623 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 161:
#line 846 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3631 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 162:
#line 850 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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

  case 163:
#line 863 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3664 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 164:
#line 877 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 3672 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 165:
#line 883 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3680 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 166:
#line 887 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), NULL);
    }
#line 3688 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 167:
#line 893 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3696 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 168:
#line 897 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[-1].opval), NULL);
    }
#line 3704 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 169:
#line 903 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->current_file, compiler->current_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[-2].opval), (yyvsp[0].opval), NULL);
    }
#line 3714 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 170:
#line 909 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->current_file, compiler->current_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3724 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 171:
#line 916 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval), 0);
      
      // condition part has own scope
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    }
#line 3738 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 172:
#line 926 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      op_if = SPVM_OP_build_if_statement(compiler, op_if, (yyvsp[-3].opval), (yyvsp[0].opval), (yyvsp[-1].opval), 0);
      
      // condition part has own scope
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    }
#line 3753 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 173:
#line 939 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
#line 3761 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 174:
#line 943 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 3769 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 175:
#line 947 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, op_if, (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval), 0);
    }
#line 3778 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 176:
#line 954 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_block;
    }
#line 3788 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 177:
#line 962 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3796 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 178:
#line 968 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var_decl(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval), NULL);
    }
#line 3804 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 179:
#line 972 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var_decl(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL, NULL);
    }
#line 3812 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 180:
#line 978 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[0].opval));
    }
#line 3820 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 181:
#line 984 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
#line 3828 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 182:
#line 988 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3843 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1001 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
#line 3851 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1017 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_true(compiler, (yyvsp[0].opval));
    }
#line 3859 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1021 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_false(compiler, (yyvsp[0].opval));
    }
#line 3867 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1033 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_basic_type_id(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3875 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1047 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3895 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1063 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_operator = (yyvsp[-5].opval)->first;
      SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, compiler->current_file, compiler->current_line);
      
      SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, (yyvsp[-5].opval));
      SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, (yyvsp[-3].opval));
      SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, (yyvsp[-1].opval));
      
      (yyval.opval) = op_sequence;
    }
#line 3910 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1076 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3928 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1090 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[-1].opval);
    }
#line 3936 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1094 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 3944 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1100 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, operator, (yyvsp[0].opval));
    }
#line 3953 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1105 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MINUS, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, op_negate, (yyvsp[0].opval));
    }
#line 3962 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1110 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3970 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1114 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3978 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1118 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3986 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1122 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3994 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1126 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4002 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1130 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op_var(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4010 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1134 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op_var(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4018 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1138 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4026 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1142 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4034 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1146 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4042 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1151 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4050 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1155 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4058 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1161 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[0].opval));
    }
#line 4067 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1166 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[-1].opval));
    }
#line 4076 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1171 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[0].opval));
    }
#line 4085 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1176 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[-1].opval));
    }
#line 4094 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1183 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, operator, (yyvsp[0].opval));
    }
#line 4103 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1188 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, operator, (yyvsp[-1].opval));
    }
#line 4112 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1195 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, operator, (yyvsp[0].opval));
    }
#line 4121 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1200 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, operator, (yyvsp[-1].opval));
    }
#line 4130 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1215 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, operator, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4139 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1220 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, operator, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4148 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1225 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MULTIPLY, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, operator, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4157 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1230 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4165 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1234 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4173 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1238 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4181 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1242 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4189 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1246 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4197 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1250 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4205 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1256 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* ternary_op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TERNARY_OP, (yyvsp[-4].opval)->file, (yyvsp[-4].opval)->line);
      (yyval.opval) = SPVM_OP_build_ternary_op(compiler, ternary_op, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4214 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1263 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4222 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1267 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4230 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1271 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4238 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1275 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4246 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1281 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4254 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1285 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4262 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1289 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4270 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1293 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4278 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1297 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4286 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1301 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4294 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1305 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4302 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1309 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4310 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1313 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4318 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1317 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4326 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1321 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4334 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1325 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4342 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1329 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4350 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1333 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4358 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 275:
#line 1339 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4366 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1345 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_logical_or(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4374 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1349 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_logical_and(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4382 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1353 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_logical_not(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4390 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1359 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_defined_or(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4398 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 280:
#line 1365 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_type_check(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4406 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1369 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_type_check(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4414 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1373 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_type_check(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4422 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1377 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_type_check(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4430 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 284:
#line 1381 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_type_check(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4438 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1387 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type_cast = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      (yyval.opval) = SPVM_OP_build_type_cast(compiler, op_type_cast, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4447 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1392 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type_cast = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_type_cast(compiler, op_type_cast, (yyvsp[-1].opval), (yyvsp[-4].opval));
    }
#line 4456 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 287:
#line 1399 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_can(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4464 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1403 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_can(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4472 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 289:
#line 1409 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4480 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1413 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_special_assign(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4488 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 291:
#line 1419 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 4496 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 292:
#line 1423 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_length = (yyvsp[0].opval)->last;
      SPVM_OP_cut_op(compiler, (yyvsp[0].opval)->last);
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), op_length);
    }
#line 4506 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1429 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_anon_method(compiler, (yyvsp[0].opval));
    }
#line 4514 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 294:
#line 1435 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->current_file, compiler->current_line);
      int32_t is_key_values = 0;
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[-1].opval), is_key_values);
    }
#line 4524 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 295:
#line 1441 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->current_file, compiler->current_line);
      int32_t is_key_values = 1;
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[-1].opval), is_key_values);
    }
#line 4534 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 296:
#line 1447 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->current_file, compiler->current_line);
      int32_t is_key_values = 1;
      SPVM_OP* op_list_elements = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, op_list_elements, is_key_values);
    }
#line 4545 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 297:
#line 1456 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4554 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 298:
#line 1461 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, (yyvsp[-1].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-1].opval), (yyvsp[0].opval), op_operators);
    }
#line 4564 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 299:
#line 1467 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4573 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 300:
#line 1472 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-2].opval), (yyvsp[0].opval), op_operators);
    }
#line 4583 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 301:
#line 1478 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4592 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 302:
#line 1483 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-2].opval), (yyvsp[0].opval), op_operators);
    }
#line 4602 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 303:
#line 1489 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_method_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[-3].opval)->file, (yyvsp[-3].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-4].opval), op_method_name, (yyvsp[-1].opval));
    }
#line 4612 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 304:
#line 1497 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ELEMENT_ACCESS, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_element_access(compiler, op_array_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 4621 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 305:
#line 1502 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ELEMENT_ACCESS, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_element_access(compiler, op_array_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4630 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 306:
#line 1507 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ELEMENT_ACCESS, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_element_access(compiler, op_array_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4639 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 307:
#line 1514 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 4648 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 308:
#line 1519 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4657 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 309:
#line 1524 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_access = (yyvsp[-3].opval);
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      (yyval.opval) = SPVM_OP_build_field_access(compiler, op_field_access, op_array_access, (yyvsp[-1].opval));
    }
#line 4667 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 310:
#line 1532 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 4677 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 311:
#line 1540 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_unweaken_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 4687 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 312:
#line 1548 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_isweak_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 4697 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 313:
#line 1556 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_warn(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 4705 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 314:
#line 1560 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_warn(compiler, (yyvsp[0].opval), NULL);
    }
#line 4713 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 315:
#line 1566 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_copy_fields(compiler, (yyvsp[-5].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4721 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 316:
#line 1572 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_exists(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 4731 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;

  case 317:
#line 1580 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_delete(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 4741 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
    break;


#line 4745 "lib/SPVM/Builder/src/spvm_yacc.c" /* yacc.c:1646  */
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
#line 1586 "yacc/spvm_yacc.y" /* yacc.c:1906  */

