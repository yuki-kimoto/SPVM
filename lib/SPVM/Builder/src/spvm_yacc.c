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
#line 5 "yacc/spvm_yacc.y" /* yacc.c:339  */

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
  #include "spvm_class.h"
  #include "spvm_attribute.h"
  #include "spvm_constant_string.h"

#line 89 "spvm_yacc.tab.c" /* yacc.c:339  */

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
   by #include "spvm_yacc.tab.h".  */
#ifndef YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED
# define YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED
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
    ERROR_CODE = 274,
    ERROR = 275,
    IF = 276,
    UNLESS = 277,
    ELSIF = 278,
    ELSE = 279,
    FOR = 280,
    WHILE = 281,
    LAST = 282,
    NEXT = 283,
    SWITCH = 284,
    CASE = 285,
    DEFAULT = 286,
    BREAK = 287,
    EVAL = 288,
    SYMBOL_NAME = 289,
    VAR_NAME = 290,
    CONSTANT = 291,
    EXCEPTION_VAR = 292,
    UNDEF = 293,
    VOID = 294,
    BYTE = 295,
    SHORT = 296,
    INT = 297,
    LONG = 298,
    FLOAT = 299,
    DOUBLE = 300,
    STRING = 301,
    OBJECT = 302,
    TRUE = 303,
    FALSE = 304,
    END_OF_FILE = 305,
    DOT3 = 306,
    FATCAMMA = 307,
    RW = 308,
    RO = 309,
    WO = 310,
    INIT = 311,
    NEW = 312,
    OF = 313,
    CLASS_ID = 314,
    EXTENDS = 315,
    SUPER = 316,
    RETURN = 317,
    WEAKEN = 318,
    DIE = 319,
    WARN = 320,
    PRINT = 321,
    CURRENT_CLASS_NAME = 322,
    UNWEAKEN = 323,
    ASSIGN = 324,
    SPECIAL_ASSIGN = 325,
    LOGICAL_OR = 326,
    LOGICAL_AND = 327,
    BIT_OR = 328,
    BIT_XOR = 329,
    BIT_AND = 330,
    NUMEQ = 331,
    NUMNE = 332,
    STREQ = 333,
    STRNE = 334,
    NUMGT = 335,
    NUMGE = 336,
    NUMLT = 337,
    NUMLE = 338,
    STRGT = 339,
    STRGE = 340,
    STRLT = 341,
    STRLE = 342,
    ISA = 343,
    IS_TYPE = 344,
    NUMERIC_CMP = 345,
    STRING_CMP = 346,
    SHIFT = 347,
    DIVIDE = 348,
    DIVIDE_UNSIGNED_INT = 349,
    DIVIDE_UNSIGNED_LONG = 350,
    REMAINDER = 351,
    REMAINDER_UNSIGNED_INT = 352,
    REMAINDER_UNSIGNED_LONG = 353,
    LOGICAL_NOT = 354,
    BIT_NOT = 355,
    CREATE_REF = 356,
    DEREF = 357,
    PLUS = 358,
    MINUS = 359,
    CONVERT = 360,
    SCALAR = 361,
    STRING_LENGTH = 362,
    ISWEAK = 363,
    REFCNT = 364,
    REFOP = 365,
    DUMP = 366,
    NEW_STRING_LEN = 367,
    IS_READ_ONLY = 368,
    COPY = 369,
    HAS_IMPL = 370,
    SET_ERROR_CODE = 371,
    INC = 372,
    DEC = 373,
    ARROW = 374
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 254 "spvm_yacc.tab.c" /* yacc.c:358  */

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
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   4207

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  134
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  91
/* YYNRULES -- Number of rules.  */
#define YYNRULES  270
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  532

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   374

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
      71,   132,    99,    96,   131,    97,    98,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   128,   129,
       2,     2,     2,     2,   108,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    69,     2,   133,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    70,     2,   130,     2,     2,     2,     2,
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
      65,    66,    67,    68,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,   100,   101,
     102,   103,   104,   105,   106,   107,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    68,    68,    72,    75,    88,   102,   105,   109,   113,
     117,   124,   127,   133,   142,   145,   157,   171,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   185,   201,   207,
     214,   222,   229,   235,   241,   247,   256,   259,   272,   286,
     287,   290,   294,   300,   306,   312,   316,   320,   324,   330,
     336,   354,   357,   370,   384,   385,   388,   392,   399,   402,
     406,   409,   422,   436,   440,   443,   456,   470,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   490,   494,   498,   499,   505,   506,   510,   514,
     515,   516,   522,   526,   532,   538,   542,   548,   554,   560,
     566,   575,   578,   591,   605,   611,   615,   621,   625,   631,
     637,   644,   655,   669,   672,   676,   682,   690,   697,   700,
     714,   717,   720,   721,   722,   723,   724,   725,   726,   727,
     728,   729,   730,   731,   732,   733,   734,   735,   736,   737,
     753,   754,   755,   756,   757,   758,   762,   766,   767,   768,
     769,   773,   774,   778,   781,   795,   799,   805,   810,   815,
     819,   823,   827,   831,   835,   839,   843,   847,   853,   859,
     864,   871,   876,   883,   888,   893,   898,   902,   906,   910,
     914,   918,   922,   926,   930,   934,   938,   944,   948,   952,
     956,   960,   964,   968,   972,   976,   980,   984,   988,   992,
     996,  1002,  1008,  1014,  1018,  1022,  1028,  1032,  1038,  1042,
    1046,  1072,  1078,  1084,  1093,  1098,  1105,  1109,  1113,  1119,
    1124,  1130,  1135,  1141,  1146,  1152,  1160,  1165,  1170,  1177,
    1185,  1193,  1201,  1205,  1211,  1216,  1221,  1226,  1233,  1237,
    1243,  1249,  1250,  1255,  1256,  1257,  1260,  1264,  1270,  1276,
    1282,  1288,  1294,  1300,  1305,  1313,  1319,  1323,  1329,  1333,
    1339,  1340,  1347,  1350,  1353,  1359,  1373,  1379,  1382,  1385,
    1388
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CLASS", "HAS", "METHOD", "OUR", "ENUM",
  "MY", "USE", "AS", "REQUIRE", "ALIAS", "ALLOW", "CURRENT_CLASS",
  "MUTABLE", "ATTRIBUTE", "MAKE_READ_ONLY", "INTERFACE", "ERROR_CODE",
  "ERROR", "IF", "UNLESS", "ELSIF", "ELSE", "FOR", "WHILE", "LAST", "NEXT",
  "SWITCH", "CASE", "DEFAULT", "BREAK", "EVAL", "SYMBOL_NAME", "VAR_NAME",
  "CONSTANT", "EXCEPTION_VAR", "UNDEF", "VOID", "BYTE", "SHORT", "INT",
  "LONG", "FLOAT", "DOUBLE", "STRING", "OBJECT", "TRUE", "FALSE",
  "END_OF_FILE", "DOT3", "FATCAMMA", "RW", "RO", "WO", "INIT", "NEW", "OF",
  "CLASS_ID", "EXTENDS", "SUPER", "RETURN", "WEAKEN", "DIE", "WARN",
  "PRINT", "CURRENT_CLASS_NAME", "UNWEAKEN", "'['", "'{'", "'('", "ASSIGN",
  "SPECIAL_ASSIGN", "LOGICAL_OR", "LOGICAL_AND", "BIT_OR", "BIT_XOR",
  "BIT_AND", "NUMEQ", "NUMNE", "STREQ", "STRNE", "NUMGT", "NUMGE", "NUMLT",
  "NUMLE", "STRGT", "STRGE", "STRLT", "STRLE", "ISA", "IS_TYPE",
  "NUMERIC_CMP", "STRING_CMP", "SHIFT", "'+'", "'-'", "'.'", "'*'",
  "DIVIDE", "DIVIDE_UNSIGNED_INT", "DIVIDE_UNSIGNED_LONG", "REMAINDER",
  "REMAINDER_UNSIGNED_INT", "REMAINDER_UNSIGNED_LONG", "LOGICAL_NOT",
  "BIT_NOT", "'@'", "CREATE_REF", "DEREF", "PLUS", "MINUS", "CONVERT",
  "SCALAR", "STRING_LENGTH", "ISWEAK", "REFCNT", "REFOP", "DUMP",
  "NEW_STRING_LEN", "IS_READ_ONLY", "COPY", "HAS_IMPL", "SET_ERROR_CODE",
  "INC", "DEC", "ARROW", "':'", "';'", "'}'", "','", "')'", "']'",
  "$accept", "grammar", "opt_classes", "classes", "class", "opt_extends",
  "class_block", "opt_declarations", "declarations", "declaration",
  "init_block", "use", "require", "alias", "allow", "interface",
  "enumeration", "enumeration_block", "opt_enumeration_values",
  "enumeration_values", "enumeration_value", "our", "has", "method",
  "anon_method", "opt_args", "args", "arg", "opt_vaarg", "opt_attributes",
  "attributes", "opt_statements", "statements", "statement",
  "void_return_operator", "die", "for_statement", "foreach_statement",
  "while_statement", "switch_statement", "switch_block",
  "opt_case_statements", "case_statements", "case_statement",
  "default_statement", "if_require_statement", "if_statement",
  "else_statement", "block", "eval_block", "opt_operators", "opt_operator",
  "operator", "operators", "unary_operator", "is_read_only", "inc", "dec",
  "binary_operator", "comparison_operator", "isa", "is_type",
  "logical_operator", "assign", "new", "array_init", "convert",
  "array_access", "call_spvm_method", "field_access", "weaken_field",
  "unweaken_field", "isweak_field", "has_impl", "array_length", "var_decl",
  "var", "qualified_type", "type", "basic_type", "ref_type", "array_type",
  "array_type_with_length", "return_type", "opt_type_comment",
  "type_comment", "union_type", "field_name", "method_name", "class_name",
  "class_alias_name", YY_NULLPTR
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
     315,   316,   317,   318,   319,   320,   321,   322,   323,    91,
     123,    40,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,    43,    45,    46,    42,
     348,   349,   350,   351,   352,   353,   354,   355,    64,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,   370,   371,   372,   373,   374,    58,    59,
     125,    44,    41,    93
};
# endif

#define YYPACT_NINF -426

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-426)))

#define YYTABLE_NINF -270

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-270)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      27,   307,    37,  -426,    27,  -426,  -426,  -426,  -426,  -426,
    -426,  -426,  -426,  -426,  -426,    33,  -426,  -426,    38,   -38,
    -426,  -426,    99,    85,    57,    60,    79,    81,    38,    38,
      38,  -426,    38,    52,    -2,   114,  -426,  -426,  -426,  -426,
    -426,  -426,  -426,  -426,  -426,  -426,    41,   117,   -44,  -426,
    -426,  -426,     7,    19,    11,   150,    32,    35,  1036,  -426,
    -426,  -426,    -7,    92,  -426,   115,   122,    85,    85,   140,
    -426,   140,  -426,  -426,   141,   153,  2229,  -426,  -426,   104,
     118,    15,   120,    64,    65,   134,  2229,    76,    77,    52,
    -426,  -426,  -426,  -426,  -426,  -426,   307,    38,  1512,   141,
    1631,  2229,  2229,  -426,   141,   308,  1155,  1991,  2229,  2229,
    2229,  2229,  2348,  2229,   141,   100,  2229,   141,  2229,  2229,
    2229,  2229,  2229,  2229,   141,  2229,  2229,  2229,  -426,  -426,
     240,   116,  1274,  -426,   121,  -426,  -426,  -426,  -426,  -426,
    -426,  -426,  -426,  -426,  -426,  -426,  3494,  -426,  -426,  -426,
    -426,  -426,  -426,  -426,  -426,  -426,  -426,  -426,  -426,  -426,
      73,  -426,    80,  -426,  -426,  -426,  -426,  -426,  -426,  -426,
     124,  -426,   139,   125,   221,  -426,  -426,  -426,   156,   156,
    -426,   128,   129,   131,   189,  1393,  3782,  2110,  2229,  1750,
     190,  2229,  -426,  -426,  2229,  3668,    52,  -426,   135,   194,
     206,  -426,  -426,  -426,  3552,   149,  3782,  3782,  3782,   154,
     -69,  -426,   144,  3782,   151,   -41,  -426,  3494,   -78,   307,
     157,    21,   148,  -426,   -58,  -426,   214,   -30,   -30,   -30,
     -30,  1393,   -30,   -30,  -426,  2467,   -30,   161,   -30,   -30,
     -30,   -30,   -30,   -30,   162,   -30,    12,    12,   163,  -426,
    -426,  -426,  2229,  2229,  2229,  2229,  2229,  2229,  2229,  2229,
    2229,  2229,  2229,  2229,  2229,  2229,  2229,  2229,  2229,  2229,
    2229,   307,   307,  2229,  2229,  2229,  2229,  2229,  2229,  2229,
    2229,  2229,  2229,  2229,  2229,  2229,  -426,  -426,    97,  -426,
    2229,    79,  2229,    79,   221,  -426,   232,   227,   139,   170,
     168,  -426,   229,   232,   232,  -426,  -426,   156,   798,    38,
     172,  2951,  3012,   176,  3782,   198,  3073,  3134,    52,  -426,
    -426,   439,   559,  -426,   237,   238,   141,    85,  -426,  1872,
    2229,   156,  -426,  -426,  -426,  2229,   178,  -426,   179,  3317,
    1393,   -30,   239,   221,   139,  3782,  3782,  3835,  3887,  3937,
    3937,  3986,  4035,  4035,  4035,  4035,  4080,  4080,  4080,  4080,
    4080,  4080,  4080,  4080,  -426,  -426,  4080,  4080,   169,   285,
     285,   285,   -30,   -30,   -30,   -30,   -30,   -30,   -30,  2229,
      79,   679,   242,  2641,   184,  2703,   185,   246,   307,  -426,
    -426,   141,   247,  -426,   221,   283,   191,   196,   232,   197,
    -426,    52,    52,    52,  2229,  2586,    52,   253,  -426,  -426,
    2765,  -426,  2827,    79,    79,  -426,   -41,   321,  3782,  3725,
     232,   -30,  -426,  3376,    79,  -426,   259,  2889,   201,   200,
     202,   798,  -426,  -426,  -426,  -426,   798,  -426,   257,   284,
     207,   141,  -426,  -426,  -426,  -426,  -426,  -426,   313,   133,
     133,  3610,  1393,  3195,  -426,   309,  -426,  -426,  -426,   210,
     228,   231,   156,  -426,  -426,   230,   141,  -426,  -426,  -426,
    -426,   234,   244,   307,  -426,   248,   284,    52,   292,    52,
    -426,  -426,   917,  3435,    52,   -24,   309,  -426,  -426,  -426,
     139,   232,  -426,   284,  -426,  -426,  -426,   -31,   249,  -426,
    2229,  -426,   250,   260,  -426,  -426,   261,  -426,   293,  -426,
     262,  -426,  -426,   -25,  3256,    52,    52,  -426,   141,    52,
    -426,  -426,    52,  -426,  -426,   284,  -426,   133,   263,  -426,
      52,  -426
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       3,     0,     0,     2,     4,     6,   246,   247,   248,   249,
     250,   251,   252,   254,   253,    11,     1,     5,     0,     0,
     269,    12,    60,    60,     0,     0,     0,     0,     0,     0,
       0,    63,     0,     0,     0,    60,    17,    25,    22,    26,
      23,    24,    20,    21,    18,    19,     0,    61,     0,     9,
       7,   267,     0,     0,     0,     0,     0,     0,    60,    27,
      13,    16,     0,     0,    62,     0,     0,    60,    60,     0,
      28,     0,    32,    33,     0,     0,    60,   151,   153,     0,
       0,     0,     0,     0,     0,     0,    60,     0,     0,     0,
     240,   124,   123,   125,   145,   146,     0,     0,    60,     0,
      60,    60,    60,   140,     0,    60,    60,    60,    60,    60,
      60,    60,    60,    60,     0,     0,    60,     0,    60,    60,
      60,    60,    60,    60,     0,    60,    60,    60,    85,   210,
       0,     0,    60,    67,     0,    86,    69,    70,    71,    73,
      74,    75,    77,    68,    72,    76,     0,   134,   147,   137,
     138,   135,   142,   143,   144,   149,   136,   130,   131,   129,
     128,   126,   127,    89,    90,   141,   148,   132,   133,   122,
       0,   268,     0,     0,    36,    34,    10,     8,     0,     0,
     270,     0,     0,   239,   220,    60,    91,    60,    60,    60,
       0,    60,    78,    79,    60,     0,   108,    80,     0,   208,
       0,   209,   150,    81,     0,     0,    92,    87,    88,     0,
       0,    55,     0,   156,   119,   122,   213,   156,     0,     0,
     246,     0,     0,   241,   243,   245,   244,   157,   158,   205,
     159,    60,   234,   165,   164,    60,   162,     0,   160,   161,
     163,   166,   168,   167,   233,   152,   169,   171,     0,   116,
      66,    84,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,     0,     0,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,   170,   172,     0,    83,
      60,     0,    60,     0,     0,   261,   262,     0,     0,     0,
      37,    40,    41,   262,   262,    29,    31,     0,    60,     0,
       0,     0,     0,     0,   121,     0,     0,     0,   106,   107,
     117,    60,    60,    82,     0,     0,    54,    60,   211,   155,
      60,     0,   212,   242,   139,    60,     0,   255,     0,   156,
      60,   236,     0,     0,     0,   206,   207,   203,   204,   184,
     182,   183,   187,   188,   194,   195,   189,   190,   191,   192,
     196,   197,   198,   199,   201,   202,   193,   200,   185,   173,
     174,   186,   175,   176,   177,   178,   179,   180,   181,    60,
       0,    60,   224,     0,     0,     0,     0,   222,     0,   260,
     263,    51,     0,    35,    39,     0,     0,     0,   262,     0,
      30,     0,     0,     0,    60,    60,     0,     0,   105,   256,
       0,   257,     0,     0,     0,    53,     0,     0,   154,     0,
     262,   214,   235,   156,     0,   232,     0,     0,     0,     0,
       0,    60,   217,   228,   218,   227,    60,   266,   264,    58,
      52,    51,    38,    42,    44,    43,   238,   219,   109,   113,
     113,     0,    60,     0,    97,   101,    98,   258,   259,     0,
       0,     0,     0,    56,   237,     0,    51,   216,   226,   225,
     215,     0,     0,     0,    59,     0,    58,     0,     0,     0,
     111,   112,    60,   156,     0,     0,   102,   104,   229,   230,
       0,   262,   231,    58,   223,   221,   265,     0,     0,   110,
      60,   114,     0,     0,    95,    99,     0,   103,     0,    57,
       0,    48,    47,     0,     0,     0,     0,   100,    51,     0,
      46,    45,     0,    94,    96,    58,    49,   113,     0,   115,
       0,    50
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -426,  -426,  -426,  -426,   368,  -426,   326,  -426,  -426,   358,
    -426,  -426,  -426,  -426,  -426,  -426,  -426,  -426,  -426,  -426,
       3,  -426,  -426,  -426,  -426,  -424,   294,    72,  -384,   -17,
    -426,  -426,  -426,   268,  -426,  -426,  -426,  -426,  -426,  -426,
    -426,  -426,  -426,  -415,   -84,  -426,  -426,  -425,   -33,  -426,
    -307,   -80,   -43,   -97,  -426,  -426,  -426,  -426,  -426,  -426,
    -426,  -426,  -426,  -426,  -426,  -426,  -426,  -426,  -426,  -426,
    -426,  -426,  -426,  -426,  -426,   322,   -70,   -79,  -211,    23,
    -426,   310,  -426,  -295,  -284,  -426,  -426,  -255,   -40,   -16,
     336
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    19,    25,    34,    35,    36,
      37,    38,   310,    39,    40,    41,    42,   175,   299,   300,
     301,    43,    44,    45,   129,   439,   440,   211,   475,   130,
      47,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     456,   485,   486,   140,   141,   142,   143,   480,   144,   145,
     212,   313,   213,   214,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   296,   223,   224,
     225,   226,   201,   297,   389,   390,   438,    52,   302,   170,
     181
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      59,   399,    21,   392,   183,    46,    48,    87,   333,   218,
     221,   336,    54,    55,    56,   146,    57,   476,    46,   396,
     397,    69,   173,    74,    15,   481,    22,   171,   222,   205,
       1,   330,    22,   186,   209,   215,   384,    16,   386,    58,
     487,   337,   493,   195,   234,    58,    62,   237,    63,   426,
     178,   179,   332,   329,   244,   204,   198,   206,   207,   208,
     364,   365,   326,   217,   327,   227,   228,   229,   230,   232,
     233,   507,    20,   236,   429,   238,   239,   240,   241,   242,
     243,   202,   245,   246,   247,    65,   189,   331,   218,   146,
      23,    24,   498,    18,   525,   286,   287,   288,   511,   303,
     304,    31,   529,    26,   520,    27,   505,    49,    28,   510,
      50,    29,    30,    51,   446,    31,    53,    32,    26,   199,
      27,   172,    58,    28,   471,   428,    29,    30,    60,   472,
      31,   171,    32,    64,   218,    67,   463,  -270,  -270,   288,
      70,   528,   290,   291,   311,   312,   314,    68,   316,   292,
     293,   317,   329,   334,   219,    33,   478,   479,   459,   460,
      71,    72,   174,   319,    73,   176,   379,   380,   381,   465,
      33,   219,   177,     6,   180,   187,    90,   437,   295,     7,
       8,     9,    10,    11,    12,    13,    14,   184,   339,   188,
       6,   191,   341,   192,   193,   508,     7,     8,     9,    10,
      11,    12,    13,    14,   196,   194,   197,   509,   235,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   398,   -14,
     366,   367,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   218,   -15,   248,   249,   383,   382,   385,
     251,   294,   420,   298,   387,   171,   416,   305,   306,   307,
     308,   315,   496,   321,   320,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   322,   324,   328,   410,   412,
     335,   325,   329,   338,  -269,   408,   418,   419,   342,   343,
     388,   344,   421,   400,   286,   287,   288,   423,   391,   394,
     393,   395,   430,   425,   401,   404,   405,   413,   414,   424,
     417,   409,   411,   431,   433,   435,    74,   436,   441,   443,
     444,   416,    75,   455,    31,   445,   461,    77,    78,   447,
     466,   468,   469,   473,   470,   474,   427,   477,   326,    86,
     488,     6,    20,    90,    91,    92,    93,     7,     8,     9,
      10,    11,    12,    13,    14,   218,    94,    95,   489,   490,
     492,   451,   453,   500,   518,    96,   494,    97,   448,   449,
     450,   416,    17,   454,    66,   103,   495,   105,   185,   107,
     497,   513,   515,   491,   279,   280,   281,   282,   283,   284,
     285,   517,   516,    61,   519,   530,   416,   442,   415,   210,
     250,   506,   502,   190,   108,   109,   200,   182,     0,   483,
     286,   287,   288,     0,   110,   111,   112,   113,   114,     0,
       0,     0,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,     0,     0,     0,     0,   314,
       0,  -118,     0,     0,   499,     0,   501,    74,   416,     0,
       0,   504,     0,    75,     0,    31,     0,   514,    77,    78,
       0,     0,     0,     0,   512,     0,     0,     0,     0,     0,
       0,     0,     0,    20,    90,    91,    92,    93,     0,     0,
     521,     0,   523,   524,     0,     0,   526,    94,    95,   527,
       0,     0,     0,     0,     0,     0,    96,   531,    97,     0,
       0,     0,     0,     0,     0,     0,   103,     0,   105,   185,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   108,   109,     0,     0,     0,
       0,     0,     0,     0,     0,   110,   111,   112,   113,   114,
       0,     0,     0,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,     0,    74,     0,     0,
       0,     0,   409,    75,     0,    31,     0,     0,    77,    78,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    20,    90,    91,    92,    93,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    94,    95,     0,
       0,     0,     0,     0,     0,     0,    96,     0,    97,     0,
       0,     0,     0,     0,     0,     0,   103,     0,   105,   185,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   108,   109,     0,     0,     0,
       0,     0,     0,     0,     0,   110,   111,   112,   113,   114,
       0,     0,     0,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,     0,    74,     0,     0,
       0,     0,   411,    75,   219,    31,     0,     0,    77,    78,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   220,    90,    91,    92,    93,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    94,    95,     0,
       0,     0,     0,     0,     0,     0,    96,     0,    97,     0,
       0,     0,     0,     0,     0,     0,   103,     0,   105,   185,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   108,   109,     0,     0,     0,
       0,     0,     0,     0,     0,   110,   111,   112,   113,   114,
       0,     0,     0,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,    74,     0,     0,     0,
       0,  -118,    75,     0,    31,     0,     0,    77,    78,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    20,    90,    91,    92,    93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    94,    95,     0,     0,
       0,     0,     0,     0,     0,    96,     0,    97,     0,     0,
       0,     0,     0,     0,     0,   103,     0,   105,   185,   107,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   108,   109,     0,     0,     0,     0,
       0,     0,     0,     0,   110,   111,   112,   113,   114,     0,
       0,     0,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,    74,     0,     0,     0,     0,
    -118,    75,     0,    31,     0,     0,    77,    78,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    20,    90,    91,    92,    93,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,    95,     0,     0,     0,
       0,     0,     0,     0,    96,     0,    97,     0,     0,     0,
       0,     0,     0,     0,   103,     0,   105,   185,   107,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,   109,     0,     0,     0,     0,     0,
       0,     0,     0,   110,   111,   112,   113,   114,     0,     0,
       0,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,    74,     0,     0,     0,     0,  -120,
      75,     0,    31,    76,     0,    77,    78,    79,    80,     0,
       0,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      20,    90,    91,    92,    93,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    94,    95,     0,     0,     0,     0,
       0,     0,     0,    96,     0,    97,     0,     0,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   108,   109,     0,     0,     0,     0,     0,     0,
       0,     0,   110,   111,   112,   113,   114,     0,     0,     0,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,    74,     0,   128,   -64,     0,     0,    75,
       0,    31,    76,     0,    77,    78,    79,    80,     0,     0,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    20,
      90,    91,    92,    93,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    94,    95,     0,     0,     0,     0,     0,
       0,     0,    96,     0,    97,     0,     0,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,   109,     0,     0,     0,     0,     0,     0,     0,
       0,   110,   111,   112,   113,   114,     0,     0,     0,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,    74,     0,   128,   216,     0,     0,    75,     0,
      31,    76,     0,    77,    78,    79,    80,     0,     0,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    20,    90,
      91,    92,    93,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    94,    95,     0,     0,     0,     0,     0,     0,
       0,    96,     0,    97,     0,     0,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     108,   109,     0,     0,     0,     0,     0,     0,     0,     0,
     110,   111,   112,   113,   114,     0,     0,     0,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,    74,     0,   128,   -65,     0,     0,    75,     0,    31,
       0,     0,    77,    78,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,    90,    91,
      92,    93,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    94,    95,     0,     0,     0,     0,     0,     0,     0,
      96,     0,    97,     0,     0,     0,     0,     0,     0,     0,
     103,     0,   105,   185,   107,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   108,
     109,     0,     0,     0,     0,     0,     0,     0,     0,   110,
     111,   112,   113,   114,     0,     0,     0,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
      74,     0,     0,   216,     0,     0,    75,     0,    31,     0,
       0,    77,    78,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    20,    90,    91,    92,
      93,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      94,    95,     0,     0,     0,     0,     0,     0,     0,    96,
       0,    97,     0,     0,     0,     0,     0,     0,     0,   103,
       0,   105,   185,   107,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   108,   109,
       0,     0,     0,     0,     0,     0,     0,     0,   110,   111,
     112,   113,   114,     0,     0,     0,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,    74,
       0,   203,     0,     0,     0,    75,     0,    31,     0,     0,
      77,    78,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    20,    90,    91,    92,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    94,
      95,     0,     0,     0,     0,     0,     0,     0,    96,     0,
      97,     0,     0,     0,     0,     0,     0,     0,   103,     0,
     105,   185,   107,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   108,   109,     0,
       0,     0,     0,     0,     0,     0,     0,   110,   111,   112,
     113,   114,     0,     0,     0,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,    74,     0,
     -93,     0,     0,     0,    75,     0,    31,     0,     0,    77,
      78,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    20,    90,    91,    92,    93,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    94,    95,
       0,     0,     0,     0,     0,     0,     0,    96,     0,    97,
       0,     0,     0,     0,     0,     0,     0,   103,     0,   105,
     185,   107,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   109,     0,     0,
       0,     0,     0,     0,     0,     0,   110,   111,   112,   113,
     114,     0,     0,     0,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   -60,     0,  -120,
      74,     0,     0,     0,     0,     0,    75,     0,    31,     0,
       0,    77,    78,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    20,    90,    91,    92,
      93,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      94,    95,     0,     0,     0,     0,     0,     0,     0,    96,
       0,    97,     0,     0,     0,     0,     0,     0,     0,   103,
       0,   105,   185,   107,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   108,   109,
       0,     0,     0,     0,     0,     0,     0,     0,   110,   111,
     112,   113,   114,     0,     0,     0,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,    74,
       0,     0,     0,     0,     0,    75,   219,    31,     0,     0,
      77,    78,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   220,    90,    91,    92,    93,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    94,
      95,     0,     0,     0,     0,     0,     0,     0,    96,     0,
      97,     0,     0,     0,     0,     0,     0,     0,   103,     0,
     105,   185,   107,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   108,   109,     0,
       0,     0,     0,     0,     0,     0,     0,   110,   111,   112,
     113,   114,     0,     0,     0,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,    74,     0,
       0,   309,     0,     0,    75,     0,    31,     0,     0,    77,
      78,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    20,    90,    91,    92,    93,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    94,    95,
       0,     0,     0,     0,     0,     0,     0,    96,     0,    97,
       0,     0,     0,     0,     0,     0,     0,   103,     0,   105,
     185,   107,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   109,     0,     0,
       0,     0,     0,     0,     0,     0,   110,   111,   112,   113,
     114,     0,     0,     0,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,    74,     0,     0,
       0,     0,     0,    75,     0,    31,     0,     0,    77,    78,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    20,    90,    91,    92,    93,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    94,    95,     0,
       0,     0,     0,     0,     0,     0,    96,     0,    97,     0,
       0,     0,     0,     0,     0,     0,   103,     0,   105,   185,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   108,   109,     0,     0,     0,
       0,     0,     0,     0,     0,   110,   111,   112,   113,   114,
       0,     0,     0,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,    74,     0,     0,     0,
       0,     0,    75,     0,    31,     0,     0,    77,    78,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    20,    90,    91,    92,    93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    94,    95,     0,     0,
       0,     0,     0,     0,     0,    96,     0,    97,     0,     0,
       0,     0,     0,     0,     0,   103,     0,   105,   231,   107,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   108,   109,     0,     0,     0,     0,
       0,     0,     0,     0,   110,   111,   112,   113,   114,     0,
       0,     0,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,    74,     0,     0,     0,     0,
       0,    75,     0,    31,     0,     0,    77,    78,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    20,    90,    91,    92,    93,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,    95,     0,     0,     0,
       0,     0,     0,     0,    96,     0,    97,     0,     0,     0,
       0,     0,     0,     0,   103,     0,   105,   340,   107,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,   109,     0,     0,     0,     0,     0,
       0,     0,     0,   110,   111,   112,   113,   114,     0,     0,
       0,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,    74,     0,     0,     0,     0,     0,
      75,     0,    31,     0,     0,    77,    78,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      20,    90,    91,    92,    93,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    94,    95,     0,     0,     0,     0,
       0,     0,     0,    96,     0,    97,     0,     0,     0,     0,
       0,     0,     0,   103,     0,   105,   452,   107,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   108,   109,     0,     0,     0,     0,     0,     0,
       0,     0,   110,   111,   112,   113,   114,     0,     0,     0,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   286,   287,   288,     0,
       0,     0,     0,     0,   432,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   286,   287,
     288,     0,     0,     0,     0,     0,   434,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     286,   287,   288,     0,     0,     0,     0,     0,   457,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   286,   287,   288,     0,     0,     0,     0,     0,
     458,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   286,   287,   288,     0,     0,     0,
       0,     0,   467,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   286,   287,   288,     0,
       0,     0,     0,   402,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   286,   287,   288,
       0,     0,     0,     0,   403,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   286,   287,
     288,     0,     0,     0,     0,   406,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   286,
     287,   288,     0,     0,     0,     0,   407,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     286,   287,   288,     0,     0,     0,     0,   484,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   286,   287,   288,     0,     0,     0,     0,   522,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   286,   287,   288,     0,     0,   422,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   286,   287,   288,     0,     0,   464,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     286,   287,   288,     0,     0,   503,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   286,
     287,   288,     0,   289,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   286,   287,   288,
       0,   323,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   286,   287,   288,     0,   482,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   286,   287,   288,   318,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     286,   287,   288,   462,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   286,   287,   288,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     286,   287,   288,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   286,   287,   288,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   286,   287,   288,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   286,   287,   288,  -270,  -270,  -270,  -270,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     286,   287,   288,  -270,  -270,  -270,  -270,  -270,  -270,  -270,
    -270,  -270,  -270,  -270,  -270,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   286,   287,   288
};

static const yytype_int16 yycheck[] =
{
      33,   308,    18,   298,    74,    22,    23,    31,   219,   106,
     107,    69,    28,    29,    30,    58,    32,   441,    35,   303,
     304,    10,    62,     8,     1,   450,    70,    34,   107,    99,
       3,    72,    70,    76,   104,   105,   291,     0,   293,    70,
     455,    99,   466,    86,   114,    70,     5,   117,     7,   344,
      67,    68,   130,   131,   124,    98,    89,   100,   101,   102,
     271,   272,   131,   106,   133,   108,   109,   110,   111,   112,
     113,   486,    34,   116,   381,   118,   119,   120,   121,   122,
     123,    97,   125,   126,   127,   129,    71,   128,   185,   132,
     128,   129,   476,    60,   518,   125,   126,   127,   129,   178,
     179,    16,   527,     4,   129,     6,   130,    50,     9,   493,
      50,    12,    13,    34,   398,    16,    35,    18,     4,    96,
       6,   128,    70,     9,   431,   380,    12,    13,   130,   436,
      16,    34,    18,    16,   231,   128,   420,   125,   126,   127,
     129,   525,    69,    70,   187,   188,   189,   128,   191,    69,
      70,   194,   131,   132,    15,    56,    23,    24,   413,   414,
      10,   129,    70,   196,   129,    50,    69,    70,    71,   424,
      56,    15,    50,    34,    34,    71,    35,   388,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    34,   231,    71,
      34,    71,   235,   129,   129,   490,    40,    41,    42,    43,
      44,    45,    46,    47,   128,    71,   129,   491,   108,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   307,   130,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   340,   130,     5,   130,   290,   288,   292,
     129,   127,   331,   128,   294,    34,   326,   129,   129,   128,
      71,    71,   473,    69,   129,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,    69,   127,   133,   321,   322,
     132,   127,   131,    69,   127,   318,   329,   330,   127,   127,
      58,   128,   335,   309,   125,   126,   127,   340,    71,   131,
     130,    72,   381,   343,   132,   129,   108,    70,    70,    70,
     327,   133,   133,    71,   130,   130,     8,    71,    71,    36,
     129,   391,    14,    70,    16,   129,     5,    19,    20,   132,
      71,   130,   132,    76,   132,    51,   379,    24,   131,    30,
     130,    34,    34,    35,    36,    37,    38,    40,    41,    42,
      43,    44,    45,    46,    47,   452,    48,    49,   130,   128,
     130,   404,   405,    71,    71,    57,   132,    59,   401,   402,
     403,   441,     4,   406,    48,    67,   132,    69,    70,    71,
     132,   132,   132,   462,    99,   100,   101,   102,   103,   104,
     105,   130,   132,    35,   132,   132,   466,   394,   326,   105,
     132,   485,   482,    81,    96,    97,    96,    71,    -1,   452,
     125,   126,   127,    -1,   106,   107,   108,   109,   110,    -1,
      -1,    -1,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,    -1,    -1,    -1,    -1,   482,
      -1,   133,    -1,    -1,   477,    -1,   479,     8,   518,    -1,
      -1,   484,    -1,    14,    -1,    16,    -1,   500,    19,    20,
      -1,    -1,    -1,    -1,   497,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    38,    -1,    -1,
     513,    -1,   515,   516,    -1,    -1,   519,    48,    49,   522,
      -1,    -1,    -1,    -1,    -1,    -1,    57,   530,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    69,    70,
      71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    96,    97,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   106,   107,   108,   109,   110,
      -1,    -1,    -1,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,    -1,     8,    -1,    -1,
      -1,    -1,   133,    14,    -1,    16,    -1,    -1,    19,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    69,    70,
      71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    96,    97,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   106,   107,   108,   109,   110,
      -1,    -1,    -1,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,    -1,     8,    -1,    -1,
      -1,    -1,   133,    14,    15,    16,    -1,    -1,    19,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    38,    -1,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    69,    70,
      71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    96,    97,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   106,   107,   108,   109,   110,
      -1,    -1,    -1,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,     8,    -1,    -1,    -1,
      -1,   132,    14,    -1,    16,    -1,    -1,    19,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    -1,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    69,    70,    71,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    96,    97,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   106,   107,   108,   109,   110,    -1,
      -1,    -1,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,     8,    -1,    -1,    -1,    -1,
     132,    14,    -1,    16,    -1,    -1,    19,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    57,    -1,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    69,    70,    71,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    96,    97,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   106,   107,   108,   109,   110,    -1,    -1,
      -1,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,     8,    -1,    -1,    -1,    -1,   132,
      14,    -1,    16,    17,    -1,    19,    20,    21,    22,    -1,
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    -1,    59,    -1,    -1,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    96,    97,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   106,   107,   108,   109,   110,    -1,    -1,    -1,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,     8,    -1,   129,   130,    -1,    -1,    14,
      -1,    16,    17,    -1,    19,    20,    21,    22,    -1,    -1,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    -1,    59,    -1,    -1,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    96,    97,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   106,   107,   108,   109,   110,    -1,    -1,    -1,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     8,    -1,   129,   130,    -1,    -1,    14,    -1,
      16,    17,    -1,    19,    20,    21,    22,    -1,    -1,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    57,    -1,    59,    -1,    -1,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      96,    97,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     106,   107,   108,   109,   110,    -1,    -1,    -1,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,     8,    -1,   129,   130,    -1,    -1,    14,    -1,    16,
      -1,    -1,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      57,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    69,    70,    71,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,
      97,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,
     107,   108,   109,   110,    -1,    -1,    -1,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
       8,    -1,    -1,   130,    -1,    -1,    14,    -1,    16,    -1,
      -1,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,
      -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    97,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,   107,
     108,   109,   110,    -1,    -1,    -1,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,     8,
      -1,   129,    -1,    -1,    -1,    14,    -1,    16,    -1,    -1,
      19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,
      69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    97,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,   107,   108,
     109,   110,    -1,    -1,    -1,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,     8,    -1,
     129,    -1,    -1,    -1,    14,    -1,    16,    -1,    -1,    19,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,    59,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    96,    97,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   106,   107,   108,   109,
     110,    -1,    -1,    -1,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,     5,    -1,   129,
       8,    -1,    -1,    -1,    -1,    -1,    14,    -1,    16,    -1,
      -1,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,
      -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    97,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,   107,
     108,   109,   110,    -1,    -1,    -1,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,     8,
      -1,    -1,    -1,    -1,    -1,    14,    15,    16,    -1,    -1,
      19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,
      -1,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,
      69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    97,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,   107,   108,
     109,   110,    -1,    -1,    -1,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,     8,    -1,
      -1,    11,    -1,    -1,    14,    -1,    16,    -1,    -1,    19,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,    59,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    96,    97,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   106,   107,   108,   109,
     110,    -1,    -1,    -1,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,     8,    -1,    -1,
      -1,    -1,    -1,    14,    -1,    16,    -1,    -1,    19,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    69,    70,
      71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    96,    97,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   106,   107,   108,   109,   110,
      -1,    -1,    -1,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,     8,    -1,    -1,    -1,
      -1,    -1,    14,    -1,    16,    -1,    -1,    19,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    -1,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    69,    70,    71,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    96,    97,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   106,   107,   108,   109,   110,    -1,
      -1,    -1,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,     8,    -1,    -1,    -1,    -1,
      -1,    14,    -1,    16,    -1,    -1,    19,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    57,    -1,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    69,    70,    71,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    96,    97,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   106,   107,   108,   109,   110,    -1,    -1,
      -1,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,     8,    -1,    -1,    -1,    -1,    -1,
      14,    -1,    16,    -1,    -1,    19,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    -1,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    69,    70,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    96,    97,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   106,   107,   108,   109,   110,    -1,    -1,    -1,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   125,   126,   127,    -1,
      -1,    -1,    -1,    -1,   133,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,   126,
     127,    -1,    -1,    -1,    -1,    -1,   133,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     125,   126,   127,    -1,    -1,    -1,    -1,    -1,   133,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   125,   126,   127,    -1,    -1,    -1,    -1,    -1,
     133,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   125,   126,   127,    -1,    -1,    -1,
      -1,    -1,   133,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   125,   126,   127,    -1,
      -1,    -1,    -1,   132,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,   126,   127,
      -1,    -1,    -1,    -1,   132,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,   126,
     127,    -1,    -1,    -1,    -1,   132,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,
     126,   127,    -1,    -1,    -1,    -1,   132,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     125,   126,   127,    -1,    -1,    -1,    -1,   132,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   125,   126,   127,    -1,    -1,    -1,    -1,   132,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   125,   126,   127,    -1,    -1,   130,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   125,   126,   127,    -1,    -1,   130,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     125,   126,   127,    -1,    -1,   130,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,
     126,   127,    -1,   129,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,   126,   127,
      -1,   129,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   125,   126,   127,    -1,   129,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   125,   126,   127,   128,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     125,   126,   127,   128,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,   126,   127,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     125,   126,   127,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   125,   126,   127,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   125,   126,   127,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   125,   126,   127,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     125,   126,   127,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   125,   126,   127
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,   135,   136,   137,   138,    34,    40,    41,    42,
      43,    44,    45,    46,    47,   213,     0,   138,    60,   139,
      34,   223,    70,   128,   129,   140,     4,     6,     9,    12,
      13,    16,    18,    56,   141,   142,   143,   144,   145,   147,
     148,   149,   150,   155,   156,   157,   163,   164,   163,    50,
      50,    34,   221,    35,   223,   223,   223,   223,    70,   182,
     130,   143,     5,     7,    16,   129,   140,   128,   128,    10,
     129,    10,   129,   129,     8,    14,    17,    19,    20,    21,
      22,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      35,    36,    37,    38,    48,    49,    57,    59,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    96,    97,
     106,   107,   108,   109,   110,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   129,   158,
     163,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     177,   178,   179,   180,   182,   183,   186,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     223,    34,   128,   222,    70,   151,    50,    50,   163,   163,
      34,   224,   224,   210,    34,    70,   186,    71,    71,    71,
     209,    71,   129,   129,    71,   186,   128,   129,   182,   213,
     215,   216,   223,   129,   186,   210,   186,   186,   186,   210,
     160,   161,   184,   186,   187,   210,   130,   186,   187,    15,
      34,   187,   211,   212,   213,   214,   215,   186,   186,   186,
     186,    70,   186,   186,   210,   108,   186,   210,   186,   186,
     186,   186,   186,   186,   210,   186,   186,   186,     5,   130,
     167,   129,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   125,   126,   127,   129,
      69,    70,    69,    70,   127,    39,   211,   217,   128,   152,
     153,   154,   222,   211,   211,   129,   129,   128,    71,    11,
     146,   186,   186,   185,   186,    71,   186,   186,   128,   182,
     129,    69,    69,   129,   127,   127,   131,   133,   133,   131,
      72,   128,   130,   212,   132,   132,    69,    99,    69,   186,
      70,   186,   127,   127,   128,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   212,   212,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,    69,
      70,    71,   222,   186,   221,   186,   221,   222,    58,   218,
     219,    71,   217,   130,   131,    72,   218,   218,   211,   184,
     223,   132,   132,   132,   129,   108,   132,   132,   182,   133,
     186,   133,   186,    70,    70,   161,   210,   163,   186,   186,
     211,   186,   130,   186,    70,   222,   217,   186,   221,   184,
     211,    71,   133,   130,   133,   130,    71,   212,   220,   159,
     160,    71,   154,    36,   129,   129,   218,   132,   182,   182,
     182,   186,    70,   186,   182,    70,   174,   133,   133,   221,
     221,     5,   128,   218,   130,   221,    71,   133,   130,   132,
     132,   184,   184,    76,    51,   162,   159,    24,    23,    24,
     181,   181,   129,   186,   132,   175,   176,   177,   130,   130,
     128,   211,   130,   159,   132,   132,   212,   132,   162,   182,
      71,   182,   185,   130,   182,   130,   178,   177,   217,   218,
     162,   129,   182,   132,   186,   132,   132,   130,    71,   132,
     129,   182,   132,   182,   182,   159,   182,   182,   162,   181,
     132,   182
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   134,   135,   136,   136,   137,   137,   138,   138,   138,
     138,   139,   139,   140,   141,   141,   142,   142,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   144,   145,   145,
     146,   147,   148,   149,   150,   151,   152,   152,   153,   153,
     153,   154,   154,   155,   156,   157,   157,   157,   157,   158,
     158,   159,   159,   160,   160,   160,   161,   161,   162,   162,
     163,   163,   164,   164,   165,   165,   166,   166,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   168,   168,   168,   168,
     168,   168,   169,   169,   170,   171,   171,   172,   173,   174,
     174,   175,   175,   176,   176,   177,   177,   178,   178,   179,
     179,   180,   180,   181,   181,   181,   182,   183,   184,   184,
     185,   185,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   187,   187,   187,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   189,   190,
     190,   191,   191,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   192,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   194,   195,   196,   196,   196,   197,   197,   198,   198,
     198,   199,   199,   199,   200,   200,   201,   201,   201,   202,
     202,   202,   202,   202,   202,   202,   203,   203,   203,   204,
     205,   206,   207,   207,   208,   208,   208,   208,   209,   209,
     210,   211,   211,   212,   212,   212,   213,   213,   213,   213,
     213,   213,   213,   213,   213,   214,   215,   215,   216,   216,
     217,   217,   218,   218,   219,   220,   220,   221,   222,   223,
     224
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     5,     7,     5,
       7,     0,     2,     3,     0,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     5,
       2,     5,     3,     3,     3,     3,     0,     1,     3,     2,
       1,     1,     3,     7,     7,    10,    10,     9,     9,     9,
      12,     0,     1,     3,     2,     1,     4,     6,     0,     1,
       0,     1,     2,     1,     0,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       2,     2,     3,     2,     2,     1,     1,     2,     2,     1,
       1,     2,     2,     1,     9,     7,     9,     5,     5,     3,
       4,     0,     1,     2,     1,     4,     3,     3,     2,     5,
       7,     6,     6,     0,     2,     6,     3,     3,     0,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     1,     3,     2,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     2,     2,
       1,     3,     3,     2,     4,     5,     5,     4,     4,     5,
       2,     6,     3,     6,     3,     5,     5,     4,     4,     6,
       6,     6,     4,     2,     2,     4,     3,     5,     5,     2,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     3,     4,     4,
       2,     1,     0,     1,     2,     3,     1,     1,     1,     1,
       1
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
#line 72 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2489 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 76 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2504 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 89 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2522 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 106 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), NULL, (yyvsp[-2].opval));
    }
#line 2530 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 110 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[-4].opval));
    }
#line 2538 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 114 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), NULL, NULL, (yyvsp[-2].opval));
    }
#line 2546 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 118 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), NULL, (yyvsp[-2].opval), (yyvsp[-4].opval));
    }
#line 2554 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 124 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 2562 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 128 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_extends(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 2570 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 134 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_class_block;
    }
#line 2580 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 142 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2588 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 146 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[0].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
        SPVM_OP_insert_child(compiler, (yyval.opval), (yyval.opval)->last, (yyvsp[0].opval));
      }
    }
#line 2602 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 158 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2620 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 186 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    { 
      SPVM_OP* op_method = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_METHOD, compiler->cur_file, compiler->cur_line);
      SPVM_CONSTANT_STRING* method_name_string = SPVM_CONSTANT_STRING_new(compiler, "INIT", strlen("INIT"));
      const char* method_name = method_name_string->value;
      SPVM_OP* op_method_name = SPVM_OP_new_op_name(compiler, "INIT", compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_void_type = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);

      SPVM_OP* op_list_attributes = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_attribute_static = SPVM_OP_new_op_attribute(compiler, SPVM_ATTRIBUTE_C_ID_STATIC, compiler->cur_file, compiler->cur_line);
      SPVM_OP_insert_child(compiler, op_list_attributes, op_list_attributes->first, op_attribute_static);

      (yyval.opval) = SPVM_OP_build_method(compiler, op_method, op_method_name, op_void_type, NULL, op_list_attributes, (yyvsp[0].opval), NULL, NULL, 1, 0);
    }
#line 2638 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 202 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      int32_t is_require = 0;
      SPVM_OP* op_name_class_alias = NULL;
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), op_name_class_alias, is_require);
    }
#line 2648 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 208 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      int32_t is_require = 0;
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), is_require);
    }
#line 2657 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 215 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, compiler->cur_file, compiler->cur_line);
      int32_t is_require = 1;
      (yyval.opval) = SPVM_OP_build_use(compiler, op_use, (yyvsp[0].opval), NULL, is_require);
    }
#line 2667 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 223 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_alias(compiler, op_use, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 2676 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 230 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_allow(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2684 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 236 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_implement(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2692 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 242 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), (yyvsp[-2].opval));
    }
#line 2700 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 248 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_enum_block;
    }
#line 2710 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 256 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2718 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 260 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2733 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 273 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2751 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 291 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[0].opval), NULL);
    }
#line 2759 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 295 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2767 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 301 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_our(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-2].opval));
    }
#line 2775 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 307 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_has(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-2].opval));
    }
#line 2783 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 313 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-8].opval), (yyvsp[-7].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-9].opval), (yyvsp[0].opval), NULL, (yyvsp[-2].opval), 0, 0);
     }
#line 2791 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 317 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-8].opval), (yyvsp[-7].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-9].opval), NULL, NULL, (yyvsp[-2].opval), 0, 0);
     }
#line 2799 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 321 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), NULL, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-8].opval), (yyvsp[0].opval), NULL, (yyvsp[-2].opval), 0, 0);
     }
#line 2807 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 325 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), NULL, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-8].opval), NULL, NULL, (yyvsp[-2].opval), 0, 0);
     }
#line 2815 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 331 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t is_init = 0;
       int32_t is_anon = 1;
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), NULL, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-8].opval), (yyvsp[0].opval), NULL, (yyvsp[-2].opval), is_init, is_anon);
     }
#line 2825 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 337 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       SPVM_OP* op_list_args;
       if ((yyvsp[-10].opval)->id == SPVM_OP_C_ID_LIST) {
         op_list_args = (yyvsp[-10].opval);
       }
       else {
         op_list_args = SPVM_OP_new_op_list(compiler, (yyvsp[-10].opval)->file, (yyvsp[-10].opval)->line);
         SPVM_OP_insert_child(compiler, op_list_args, op_list_args->last, (yyvsp[-10].opval));
       }
       
       int32_t is_init = 0;
       int32_t is_anon = 1;
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), NULL, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-8].opval), (yyvsp[0].opval), op_list_args, (yyvsp[-2].opval), is_init, is_anon);
     }
#line 2844 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 354 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2852 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 358 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2867 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 371 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2885 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 389 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval), NULL, NULL);
    }
#line 2893 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 393 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[-5].opval), (yyvsp[-1].opval), NULL, (yyvsp[-3].opval));
    }
#line 2901 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 399 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 2909 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 406 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2917 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 410 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2932 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 423 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2950 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 440 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2958 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 444 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2973 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 457 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2991 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 487 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[-1].opval), NULL);
    }
#line 2999 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 491 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3007 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 495 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_operator_statement(compiler, (yyvsp[-1].opval));
    }
#line 3015 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 500 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->cur_file, compiler->cur_line);
    }
#line 3023 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 507 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_warn(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3031 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 511 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_print(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3039 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 517 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_make_read_only(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3047 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 523 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3055 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 527 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[0].opval), NULL);
    }
#line 3063 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 533 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[-8].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3071 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 539 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_foreach_statement(compiler, (yyvsp[-6].opval), (yyvsp[-5].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3079 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 543 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_foreach_statement(compiler, (yyvsp[-8].opval), (yyvsp[-7].opval), (yyvsp[-3].opval), (yyvsp[0].opval));
    }
#line 3087 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 549 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3095 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 555 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3103 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 561 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->cur_file, compiler->cur_line);
      op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[-1].opval), NULL);
    }
#line 3113 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 567 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->cur_file, compiler->cur_line);
      op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3123 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 575 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 3131 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 579 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3146 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 592 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3164 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 606 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 3172 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 612 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3180 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 616 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), NULL);
    }
#line 3188 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 622 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3196 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 626 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[-1].opval), NULL);
    }
#line 3204 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 632 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->cur_file, compiler->cur_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[-2].opval), (yyvsp[0].opval), NULL);
    }
#line 3214 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 638 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->cur_file, compiler->cur_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3224 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 645 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (var_decl $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    }
#line 3239 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 656 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (var_decl $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    }
#line 3254 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 669 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->cur_file, compiler->cur_line);
    }
#line 3262 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 673 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 3270 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 677 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3278 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 683 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_block;
    }
#line 3288 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 691 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3296 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 697 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 3304 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 701 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3319 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 714 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->cur_file, compiler->cur_line);
    }
#line 3327 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 738 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      if ((yyvsp[-1].opval)->id == SPVM_OP_C_ID_LIST) {
        SPVM_OP* op_operator = (yyvsp[-1].opval)->first;
        SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, compiler->cur_file, compiler->cur_line);
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
#line 3347 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 759 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_true(compiler, (yyvsp[0].opval));
    }
#line 3355 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 763 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_false(compiler, (yyvsp[0].opval));
    }
#line 3363 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 770 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class_id(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3371 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 775 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_set_error_code(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3379 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 782 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3397 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 796 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[-1].opval);
    }
#line 3405 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 800 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 3413 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 806 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, operator, (yyvsp[0].opval));
    }
#line 3422 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 811 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MINUS, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, op_negate, (yyvsp[0].opval));
    }
#line 3431 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 816 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3439 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 820 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op_var(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3447 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 824 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3455 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 828 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3463 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 832 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3471 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 836 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op_var(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3479 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 840 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op_var(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3487 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 844 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3495 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 848 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3503 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 854 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_is_read_only(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3511 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 860 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, operator, (yyvsp[0].opval));
    }
#line 3520 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 865 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, operator, (yyvsp[-1].opval));
    }
#line 3529 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 872 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, operator, (yyvsp[0].opval));
    }
#line 3538 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 877 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, operator, (yyvsp[-1].opval));
    }
#line 3547 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 884 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, operator, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3556 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 889 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, operator, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3565 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 894 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MULTIPLY, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, operator, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3574 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 899 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3582 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 903 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3590 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 907 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3598 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 911 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3606 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 915 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3614 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 919 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3622 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 923 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3630 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 927 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3638 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 931 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3646 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 935 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3654 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 939 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3662 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 945 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3670 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 949 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3678 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 953 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3686 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 957 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3694 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 961 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3702 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 965 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3710 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 969 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3718 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 973 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3726 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 977 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3734 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 981 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3742 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 985 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3750 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 989 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3758 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 993 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3766 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 997 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3774 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1003 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_is_type(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3782 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1009 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_is_type(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3790 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1015 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_logical_or(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3798 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1019 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_logical_and(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3806 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1023 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_logical_not(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3814 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1029 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3822 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1033 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_special_assign(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3830 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1039 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 3838 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1043 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 3846 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1047 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      // Method
      SPVM_OP* op_method = (yyvsp[0].opval);
      
      // Class
      SPVM_OP* op_class = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS, op_method->file, op_method->line);
      
      // Create class block
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, op_method->file, op_method->line);
      SPVM_OP* op_list_declarations = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP_insert_child(compiler, op_list_declarations, op_list_declarations->last, op_method);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, op_list_declarations);
      
      // Build class
      SPVM_OP_build_class(compiler, op_class, NULL, op_class_block, NULL, NULL);

      // Type
      SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, op_class->uv.class->type, op_method->file, op_method->line);
      
      // New
      SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, op_method->file, op_method->line);
      (yyval.opval) = SPVM_OP_build_new(compiler, op_new, op_type, NULL);
    }
#line 3874 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1073 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      int32_t is_key_values = 0;
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[-1].opval), is_key_values);
    }
#line 3884 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1079 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      int32_t is_key_values = 1;
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[-1].opval), is_key_values);
    }
#line 3894 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1085 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      int32_t is_key_values = 1;
      SPVM_OP* op_list_elements = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, op_list_elements, is_key_values);
    }
#line 3905 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1094 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      (yyval.opval) = SPVM_OP_build_convert(compiler, op_convert, (yyvsp[-2].opval), (yyvsp[0].opval), NULL);
    }
#line 3914 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1099 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_convert(compiler, op_convert, (yyvsp[-1].opval), (yyvsp[-4].opval), NULL);
    }
#line 3923 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1106 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 3931 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1110 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3939 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1114 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3947 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1120 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3956 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1125 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, (yyvsp[-1].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-1].opval), (yyvsp[0].opval), op_operators);
    }
#line 3966 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1131 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3975 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1136 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-2].opval), (yyvsp[0].opval), op_operators);
    }
#line 3985 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1142 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3994 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1147 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-2].opval), (yyvsp[0].opval), op_operators);
    }
#line 4004 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1153 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_method_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[-3].opval)->file, (yyvsp[-3].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, op_call_method, (yyvsp[-4].opval), op_method_name, (yyvsp[-1].opval));
    }
#line 4014 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1161 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 4023 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1166 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4032 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1171 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4041 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1178 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 4051 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1186 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_unweaken_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 4061 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1194 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP_build_field_access(compiler, op_field_access, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_isweak_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 4071 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1202 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_has_impl(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 4079 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1206 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_has_impl(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 4087 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1212 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[0].opval));
    }
#line 4096 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1217 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[-1].opval));
    }
#line 4105 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1222 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[0].opval));
    }
#line 4114 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1227 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[-1].opval));
    }
#line 4123 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1234 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var_decl(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), NULL);
    }
#line 4131 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1238 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var_decl(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL, NULL);
    }
#line 4139 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1244 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[0].opval));
    }
#line 4147 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1250 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
    (yyval.opval) = SPVM_OP_build_mutable_type(compiler, (yyvsp[0].opval));
  }
#line 4155 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1261 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[0].opval));
    }
#line 4163 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1265 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_byte_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 4173 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1271 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_short_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 4183 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1277 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 4193 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1283 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_long_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 4203 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1289 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_float_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 4213 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1295 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_double_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 4223 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1301 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_any_object_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = op_type;
    }
#line 4232 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1306 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_string_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 4242 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1314 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[-1].opval));
    }
#line 4250 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1320 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-2].opval), NULL);
    }
#line 4258 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1324 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-2].opval), NULL);
    }
#line 4266 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1330 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4274 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1334 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 4282 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1341 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 4290 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1347 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->cur_file, compiler->cur_line);
    }
#line 4298 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1354 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 4306 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1360 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 4324 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1374 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 4332 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;


#line 4336 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 1390 "yacc/spvm_yacc.y" /* yacc.c:1906  */

