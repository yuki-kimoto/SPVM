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
  #include "spvm_descriptor.h"

#line 88 "spvm_yacc.tab.c" /* yacc.c:339  */

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
    ALLOW = 267,
    CURRENT_CLASS = 268,
    MUTABLE = 269,
    DESCRIPTOR = 270,
    IF = 271,
    UNLESS = 272,
    ELSIF = 273,
    ELSE = 274,
    FOR = 275,
    WHILE = 276,
    LAST = 277,
    NEXT = 278,
    SWITCH = 279,
    CASE = 280,
    DEFAULT = 281,
    BREAK = 282,
    EVAL = 283,
    NAME = 284,
    VAR_NAME = 285,
    CONSTANT = 286,
    EXCEPTION_VAR = 287,
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
    TRUE = 298,
    FALSE = 299,
    END_OF_FILE = 300,
    DOT3 = 301,
    FATCAMMA = 302,
    RW = 303,
    RO = 304,
    WO = 305,
    INIT = 306,
    NEW = 307,
    RETURN = 308,
    WEAKEN = 309,
    DIE = 310,
    WARN = 311,
    PRINT = 312,
    CURRENT_CLASS_NAME = 313,
    UNWEAKEN = 314,
    MAKE_READ_ONLY = 315,
    ASSIGN = 316,
    SPECIAL_ASSIGN = 317,
    LOGICAL_OR = 318,
    LOGICAL_AND = 319,
    BIT_OR = 320,
    BIT_XOR = 321,
    BIT_AND = 322,
    NUMEQ = 323,
    NUMNE = 324,
    STREQ = 325,
    STRNE = 326,
    NUMGT = 327,
    NUMGE = 328,
    NUMLT = 329,
    NUMLE = 330,
    STRGT = 331,
    STRGE = 332,
    STRLT = 333,
    STRLE = 334,
    ISA = 335,
    ISA_NUMERIC_ARRAY = 336,
    ISA_MULNUM_ARRAY = 337,
    ISA_OBJECT_ARRAY = 338,
    ISA_ARRAY = 339,
    NUMERIC_CMP = 340,
    STRING_CMP = 341,
    SHIFT = 342,
    DIVIDE = 343,
    REMAINDER = 344,
    DIV_UINT = 345,
    DIV_ULONG = 346,
    REM_UINT = 347,
    REM_ULONG = 348,
    LOGICAL_NOT = 349,
    BIT_NOT = 350,
    CREATE_REF = 351,
    DEREF = 352,
    PLUS = 353,
    MINUS = 354,
    CONVERT = 355,
    SCALAR = 356,
    STRING_LENGTH = 357,
    ISWEAK = 358,
    REFCNT = 359,
    REFOP = 360,
    DUMP = 361,
    NEW_STRING_LEN = 362,
    COPY = 363,
    IS_READ_ONLY = 364,
    GET_ELEM_WIDTH = 365,
    INC = 366,
    DEC = 367,
    ARROW = 368
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 247 "spvm_yacc.tab.c" /* yacc.c:358  */

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
#define YYLAST   3318

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  128
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  77
/* YYNRULES -- Number of rules.  */
#define YYNRULES  247
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  489

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   368

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
      62,   126,    94,    91,   125,    92,    93,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   122,   123,
       2,     2,     2,     2,   103,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    60,     2,   127,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    61,     2,   124,     2,     2,     2,     2,
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
      55,    56,    57,    58,    59,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    95,    96,    97,    98,    99,   100,   101,
     102,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    66,    66,    74,    77,    90,   104,   107,   111,   115,
     119,   125,   134,   137,   149,   163,   166,   167,   168,   169,
     170,   171,   172,   175,   190,   194,   200,   205,   212,   219,
     225,   234,   237,   250,   264,   265,   268,   272,   278,   284,
     290,   295,   300,   305,   312,   320,   339,   342,   355,   369,
     370,   373,   380,   383,   387,   390,   403,   417,   421,   424,
     437,   451,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   467,   468,   469,   470,   474,   478,   482,   486,
     490,   494,   498,   499,   500,   504,   509,   515,   521,   527,
     533,   541,   555,   561,   565,   571,   575,   581,   587,   594,
     605,   619,   622,   626,   632,   640,   647,   650,   664,   667,
     670,   671,   674,   675,   676,   677,   678,   679,   680,   681,
     682,   683,   684,   685,   686,   687,   688,   689,   690,   691,
     707,   708,   709,   710,   711,   715,   721,   735,   739,   745,
     750,   755,   759,   763,   767,   771,   775,   779,   783,   787,
     791,   795,   801,   806,   813,   818,   825,   830,   835,   840,
     844,   848,   852,   856,   860,   864,   868,   872,   876,   880,
     886,   890,   894,   898,   902,   906,   910,   914,   918,   922,
     926,   930,   934,   938,   944,   948,   952,   956,   960,   966,
     970,   974,   978,   984,   988,   994,   998,  1002,  1028,  1034,
    1040,  1049,  1056,  1060,  1064,  1070,  1074,  1079,  1083,  1088,
    1092,  1097,  1103,  1107,  1111,  1117,  1124,  1131,  1138,  1143,
    1148,  1153,  1160,  1164,  1170,  1176,  1177,  1183,  1184,  1185,
    1188,  1192,  1198,  1204,  1210,  1216,  1222,  1228,  1234,  1242,
    1248,  1252,  1258,  1262,  1268,  1269,  1275,  1278
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CLASS", "HAS", "METHOD", "OUR", "ENUM",
  "MY", "USE", "AS", "REQUIRE", "ALLOW", "CURRENT_CLASS", "MUTABLE",
  "DESCRIPTOR", "IF", "UNLESS", "ELSIF", "ELSE", "FOR", "WHILE", "LAST",
  "NEXT", "SWITCH", "CASE", "DEFAULT", "BREAK", "EVAL", "NAME", "VAR_NAME",
  "CONSTANT", "EXCEPTION_VAR", "UNDEF", "VOID", "BYTE", "SHORT", "INT",
  "LONG", "FLOAT", "DOUBLE", "STRING", "OBJECT", "TRUE", "FALSE",
  "END_OF_FILE", "DOT3", "FATCAMMA", "RW", "RO", "WO", "INIT", "NEW",
  "RETURN", "WEAKEN", "DIE", "WARN", "PRINT", "CURRENT_CLASS_NAME",
  "UNWEAKEN", "'['", "'{'", "'('", "MAKE_READ_ONLY", "ASSIGN",
  "SPECIAL_ASSIGN", "LOGICAL_OR", "LOGICAL_AND", "BIT_OR", "BIT_XOR",
  "BIT_AND", "NUMEQ", "NUMNE", "STREQ", "STRNE", "NUMGT", "NUMGE", "NUMLT",
  "NUMLE", "STRGT", "STRGE", "STRLT", "STRLE", "ISA", "ISA_NUMERIC_ARRAY",
  "ISA_MULNUM_ARRAY", "ISA_OBJECT_ARRAY", "ISA_ARRAY", "NUMERIC_CMP",
  "STRING_CMP", "SHIFT", "'+'", "'-'", "'.'", "'*'", "DIVIDE", "REMAINDER",
  "DIV_UINT", "DIV_ULONG", "REM_UINT", "REM_ULONG", "LOGICAL_NOT",
  "BIT_NOT", "'@'", "CREATE_REF", "DEREF", "PLUS", "MINUS", "CONVERT",
  "SCALAR", "STRING_LENGTH", "ISWEAK", "REFCNT", "REFOP", "DUMP",
  "NEW_STRING_LEN", "COPY", "IS_READ_ONLY", "GET_ELEM_WIDTH", "INC", "DEC",
  "ARROW", "':'", "';'", "'}'", "','", "')'", "']'", "$accept", "grammar",
  "opt_classes", "classes", "class", "class_block", "opt_declarations",
  "declarations", "declaration", "init_block", "use", "require", "allow",
  "enumeration", "enumeration_block", "opt_enumeration_values",
  "enumeration_values", "enumeration_value", "our", "has", "method",
  "anon_method", "opt_args", "args", "arg", "opt_vaarg", "opt_descriptors",
  "descriptors", "opt_statements", "statements", "statement",
  "for_statement", "while_statement", "switch_statement", "switch_block",
  "case_statements", "case_statement", "default_statement",
  "if_require_statement", "if_statement", "else_statement", "block",
  "eval_block", "opt_expressions", "opt_expression",
  "expression_or_logical_op", "expression", "expressions", "unary_op",
  "inc", "dec", "binary_op", "comparison_op", "isa", "logical_op",
  "assign", "new", "array_init", "convert", "array_access",
  "call_spvm_method", "field_access", "weaken_field", "unweaken_field",
  "isweak_field", "array_length", "my_var", "var", "qualified_type",
  "type", "basic_type", "ref_type", "array_type", "array_type_with_length",
  "qualified_type_or_void", "field_name", "method_name", YY_NULLPTR
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
      91,   123,    40,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,    43,    45,    46,    42,   343,   344,   345,   346,   347,
     348,   349,   350,    64,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     367,   368,    58,    59,   125,    44,    41,    93
};
# endif

#define YYPACT_NINF -420

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-420)))

#define YYTABLE_NINF -139

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-139)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       7,   397,    16,  -420,     7,  -420,  -420,  -420,  -420,  -420,
    -420,  -420,  -420,  -420,  -420,   -26,  -420,  -420,    49,    24,
      -2,    21,    23,    45,   397,   397,  -420,    62,   -39,   245,
    -420,  -420,  -420,  -420,  -420,    15,  -420,  -420,   114,    88,
     -43,  -420,  -420,  -420,     8,    28,    -3,    33,   743,  -420,
    -420,  -420,  -420,   -12,    85,  -420,   126,   135,    24,    24,
     397,  -420,  -420,   151,   154,   122,   129,   130,   131,    71,
     101,   184,  1915,   125,   127,    62,  -420,  -420,  -420,  -420,
    -420,  -420,   397,  1120,   151,  1233,  1271,  1915,  -420,   151,
     367,   856,  1764,  -420,  1915,  1915,  1915,  1953,   151,   151,
     149,  1915,   151,   151,  1915,  1915,  1915,  1915,  1915,  1915,
    1915,  1915,  -420,  -420,   248,   132,   969,  -420,  -420,  -420,
    -420,  -420,  -420,  -420,  -420,  -420,  -420,  2637,  -420,  -420,
    -420,  -420,  -420,  -420,  -420,  -420,  -420,  -420,   -40,  -420,
      80,   136,   138,  -420,  -420,  -420,  -420,   134,  -420,   324,
     140,   235,  -420,  -420,  -420,   161,   161,   143,   147,   208,
    1538,  1802,  1384,  1802,  -420,  -420,  1915,  1082,  2937,    62,
    -420,   148,   212,   213,  -420,  -420,  2697,   155,  -420,  2757,
    -420,  2817,  2877,   156,    12,  -420,   159,  2996,   150,   165,
    -420,  2637,    35,   397,    44,   152,  -420,    10,  -420,   223,
       6,     6,     6,  1082,     6,  -420,  -420,  2046,     6,   167,
    -420,     6,     6,     6,     6,     6,     6,    13,    13,   169,
    -420,  -420,  1915,  1915,  1915,  1915,  1915,  1915,  1915,  1915,
    1915,  1915,  1915,  1915,  1915,  1915,  1915,  1915,  1915,   397,
    -420,  -420,  -420,  -420,  1915,  1915,  1915,  1915,  1915,  1915,
    1915,  1915,  1915,  1915,  1915,  1915,  1915,  -420,  -420,    93,
    -420,  1915,    23,  1915,    23,  -420,  -420,   235,  -420,  -420,
      11,   219,   324,   170,   164,  -420,   229,   174,  -420,  -420,
     161,   591,   397,  1651,  1802,   172,   -20,  2996,  -420,   -10,
     176,  2996,    42,  2462,    62,  -420,  -420,   460,   498,  -420,
     241,  -420,  -420,  -420,   242,   151,    24,  -420,  1500,   161,
    -420,  -420,  -420,  1915,   177,  -420,   178,  2521,  1082,     6,
     247,   324,  2996,  2996,  3048,  3048,  3099,  3150,  3150,  3150,
    3150,  3197,  3197,  3197,  3197,  3197,  3197,  3197,  3197,  -420,
    3197,  3197,   221,    67,    67,    67,     6,     6,     6,     6,
       6,     6,     6,  1915,    23,   591,   244,  2103,   185,  2163,
     186,   260,   151,   262,  -420,   235,   294,  -420,  -420,   200,
     317,   110,  2403,   202,  -420,    62,  1802,  1802,    62,    62,
    1802,    62,   268,  -420,  -420,  2223,  -420,  2283,    23,    23,
    -420,   165,   325,  2996,  -420,     6,  -420,  2579,    23,   269,
    2343,   209,   206,   591,  -420,  -420,  -420,  -420,   591,   288,
     211,   151,  -420,  -420,  -420,   397,  -420,   320,   276,  -420,
     160,   160,    51,  -420,   319,  -420,  -420,  -420,   222,   225,
     233,  -420,   232,   151,  -420,  -420,  -420,   231,   250,  -420,
     251,   288,   224,    62,   283,    62,  -420,  -420,   629,   -13,
    -420,  -420,  -420,   324,  -420,   288,  -420,  -420,   -28,   252,
    -420,  -420,  1802,  -420,   253,  -420,  -420,   243,   306,   255,
    -420,  -420,   -21,    46,    62,  -420,   151,    62,  -420,  -420,
      62,  -420,   288,  -420,   160,   257,  -420,    62,  -420
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     2,     4,     6,   230,   231,   232,   233,
     234,   235,   236,   238,   237,     0,     1,     5,    54,    54,
       0,     0,     0,     0,     0,     0,    57,     0,     0,    54,
      15,    22,    20,    21,    18,     0,    16,    17,     0,    55,
       0,     9,     7,   246,     0,     0,     0,     0,    54,    23,
      11,    14,    19,     0,     0,    56,     0,     0,    54,    54,
       0,    24,    28,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    54,     0,     0,     0,   224,   114,   113,   115,
     134,   135,     0,    54,     0,    54,    54,    54,   130,     0,
      54,    54,    54,    85,    54,    54,    54,    54,     0,     0,
       0,    54,     0,     0,    54,    54,    54,    54,    54,    54,
      54,    54,    84,   197,     0,     0,    54,    61,    63,    64,
      66,    67,    68,    70,    62,    65,    69,     0,   124,   127,
     128,   125,   132,   133,   126,   120,   121,   119,   118,   116,
     117,     0,     0,   131,   122,   123,   112,     0,   247,     0,
       0,    31,    29,    10,     8,     0,     0,     0,   223,   206,
      54,    54,    54,    54,    72,    73,    54,    54,     0,    96,
      74,     0,   195,     0,   196,    75,     0,     0,    77,     0,
      79,     0,     0,     0,     0,    50,     0,   138,   107,   112,
     200,   138,     0,     0,     0,     0,   225,   227,   229,   228,
     139,   140,   141,    54,   218,   147,   146,    54,   144,     0,
     142,   143,   145,   148,   149,   150,   151,   152,   154,     0,
     104,    60,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,     0,
     185,   186,   187,   188,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,   153,   155,     0,
      71,    54,     0,    54,     0,    82,    83,     0,   245,   244,
     227,     0,     0,     0,    32,    35,    36,     0,    38,    25,
       0,    54,     0,    54,    54,     0,     0,   110,   111,     0,
       0,   109,     0,     0,    94,    95,   105,    54,    54,    76,
       0,    78,    80,    81,     0,    49,    54,   198,   137,     0,
     199,   226,   129,    54,     0,   239,     0,   138,    54,   220,
       0,     0,   193,   194,   167,   165,   166,   170,   171,   177,
     178,   172,   173,   174,   175,   179,   180,   181,   182,   184,
     176,   183,   168,   156,   157,   169,   158,   159,   164,   160,
     161,   162,   163,    54,     0,    54,   210,     0,     0,     0,
       0,   208,    46,     0,    30,    34,     0,    39,   222,     0,
      26,     0,   110,   111,   191,     0,    54,    54,     0,     0,
      54,     0,     0,    93,   240,     0,   241,     0,     0,     0,
      48,     0,     0,   136,    51,   201,   219,   138,     0,     0,
       0,     0,     0,    54,   203,   214,   204,   213,    54,    52,
      47,    46,    33,    37,   205,     0,   192,    97,   189,   190,
     101,   101,     0,    87,     0,    88,   242,   243,     0,     0,
       0,   221,     0,    46,   202,   212,   211,     0,     0,    53,
       0,    52,     0,     0,     0,     0,    99,   100,    54,     0,
      92,   215,   216,     0,   217,    52,   209,   207,     0,     0,
      27,    98,    54,   102,     0,    89,    91,     0,     0,     0,
      43,    42,     0,     0,     0,    90,    46,     0,    41,    40,
       0,    86,    52,    44,   101,     0,   103,     0,    45
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -420,  -420,  -420,  -420,   366,   331,  -420,  -420,   344,  -420,
    -420,  -420,  -420,  -420,  -420,  -420,  -420,     9,  -420,  -420,
    -420,  -420,  -352,   296,    79,  -419,   -14,  -420,  -420,  -420,
     271,  -420,  -420,  -420,  -420,  -420,  -400,   -58,  -420,  -420,
    -402,   -27,  -420,  -256,   -59,  -155,   -18,   -60,  -420,  -420,
    -420,  -420,  -420,  -420,   105,  -420,  -420,  -420,  -420,  -420,
    -420,  -420,  -420,  -420,  -420,  -420,  -420,   -61,   -41,  -179,
       2,  -420,   310,  -420,  -271,  -253,   -19
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    21,    28,    29,    30,    31,
      32,   285,    33,    34,   152,   273,   274,   275,    35,    36,
      37,   113,   409,   410,   185,   440,   114,    39,   115,   116,
     117,   118,   119,   120,   425,   449,   121,   122,   123,   124,
     446,   125,   126,   186,   290,   286,   287,   188,   128,   129,
     130,   131,   132,   133,   288,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   269,   196,
     147,   198,   199,   174,   271,    44,   276
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,   363,   158,    15,    38,    40,   289,    60,   292,   358,
       1,   360,    72,    73,   311,    38,    16,   148,    18,   447,
     261,   262,   459,   177,   450,   369,    46,    47,   183,   189,
     127,   192,   194,    48,   150,    18,   469,   205,   206,    26,
      48,   209,   210,    41,   155,   156,   376,   377,   171,   466,
     399,   195,    43,    22,   168,    23,   376,   377,    24,   441,
     339,    25,   157,   485,    26,   176,    42,   179,   181,   182,
     314,   314,   187,   191,   187,    45,   200,   201,   202,   204,
      56,   455,   486,   208,   172,    50,   211,   212,   213,   214,
     215,   216,   217,   218,   197,   470,    19,    20,   127,   402,
      27,   401,   478,    55,   315,   315,   378,   192,   376,   377,
     149,   465,   376,   377,   277,   278,   379,   376,   377,    53,
      61,    54,   148,    48,   482,   257,   258,   259,   371,   374,
      58,   267,  -139,  -139,   259,   428,   429,   305,    52,   306,
     263,   264,   295,   192,   291,   432,   151,   437,   293,   187,
      59,   270,   438,   353,   354,   355,    62,   270,   270,   310,
     308,   250,   251,   252,   253,   254,   255,   256,   381,   308,
     312,   153,   480,   -12,   448,   193,   376,   377,   444,   445,
     154,    76,   468,   159,   160,   317,   257,   258,   259,   319,
       6,   161,   162,   163,   164,   270,     7,     8,     9,    10,
      11,    12,    13,    14,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   418,   419,   194,   165,   422,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   368,
     356,   270,   195,   357,   391,   359,   166,   169,   361,    22,
     170,    23,   207,   219,    24,   267,   220,    25,   192,   265,
      26,   266,   272,   187,   148,   372,   279,   383,   394,   280,
     281,   296,   297,   298,   270,   308,   300,   304,   313,   385,
     387,   362,   270,   316,   370,   197,   307,   309,   320,   365,
     393,   321,   392,   366,   364,   395,    27,   367,   375,   380,
     397,   391,   388,   389,   384,   386,   403,   473,   398,   405,
     407,   270,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   408,   270,   411,   413,   414,   415,   416,   424,
     430,   433,   436,   435,   439,   400,   305,   187,   193,   443,
     257,   258,   259,   377,    72,   462,   451,   460,   417,   452,
     391,   420,   421,     6,   423,   453,   454,   456,   268,     7,
       8,     9,    10,    11,    12,    13,    14,   475,   476,   -13,
      17,    57,   391,    51,   412,    63,   457,   458,   472,   474,
      64,   477,    26,   487,   390,   187,   184,   221,   373,   464,
     187,   467,   173,     0,     0,     0,     6,    76,    77,    78,
      79,     0,     7,     8,     9,    10,    11,    12,    13,    14,
      80,    81,     0,     0,     0,   391,   461,   442,   463,    82,
       0,     0,     0,     0,     0,    88,     6,    90,   167,    92,
     291,   471,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,     0,     0,     0,   479,     0,   481,     0,     0,
     483,     0,     0,   484,     0,   270,     0,     0,    94,    95,
     488,     0,     0,     0,     0,     0,     0,     0,    63,    96,
      97,    98,    99,    64,     0,    26,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,     0,     6,
      76,    77,    78,    79,  -106,     7,     8,     9,    10,    11,
      12,    13,    14,    80,    81,     0,    63,     0,     0,     0,
       0,    64,    82,    26,     0,     0,     0,     0,    88,     0,
      90,   167,    92,     0,     0,     0,     0,     6,    76,    77,
      78,    79,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    80,    81,     0,     0,     0,     0,     0,     0,     0,
      82,    94,    95,     0,     0,     0,    88,     0,    90,   167,
      92,     0,    96,    97,    98,    99,     0,     0,     0,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,     0,     0,     0,     0,     0,     0,   384,     0,    94,
      95,     0,     0,     0,     0,     0,     0,     0,     0,    63,
      96,    97,    98,    99,    64,     0,    26,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,     0,
       6,    76,    77,    78,    79,   386,     7,     8,     9,    10,
      11,    12,    13,    14,    80,    81,     0,    63,     0,     0,
       0,     0,    64,    82,    26,     0,     0,     0,     0,    88,
       0,    90,   167,    92,     0,     0,     0,     0,     6,    76,
      77,    78,    79,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    80,    81,     0,     0,     0,     0,     0,     0,
       0,    82,    94,    95,     0,     0,     0,    88,     0,    90,
     167,    92,     0,    96,    97,    98,    99,     0,     0,     0,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,     0,     0,     0,     0,     0,  -106,     0,     0,
      94,    95,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    96,    97,    98,    99,     0,     0,     0,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
       0,    63,     0,     0,     0,  -108,    64,     0,    26,    65,
      66,     0,     0,    67,    68,    69,    70,    71,    72,    73,
      74,    75,     6,    76,    77,    78,    79,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    80,    81,     0,     0,
       0,     0,     0,     0,     0,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    94,    95,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    96,    97,    98,    99,     0,
       0,     0,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,    63,     0,   112,   -58,     0,    64,
       0,    26,    65,    66,     0,     0,    67,    68,    69,    70,
      71,    72,    73,    74,    75,     6,    76,    77,    78,    79,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    80,
      81,     0,     0,     0,     0,     0,     0,     0,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    94,    95,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    96,    97,
      98,    99,     0,     0,     0,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,    63,     0,   112,
     190,     0,    64,     0,    26,    65,    66,     0,     0,    67,
      68,    69,    70,    71,    72,    73,    74,    75,     6,    76,
      77,    78,    79,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    80,    81,     0,     0,     0,     0,     0,     0,
       0,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      94,    95,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    96,    97,    98,    99,     0,     0,     0,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
      63,     0,   112,   -59,     0,    64,     0,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,    76,    77,    78,    79,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    80,    81,     0,    63,     0,
       0,     0,     0,    64,    82,    26,     0,     0,     0,     0,
      88,     0,    90,   167,    92,     0,     0,     0,     0,     6,
      76,    77,    78,    79,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    80,    81,     0,     0,     0,     0,     0,
       0,     0,    82,    94,    95,     0,     0,     0,    88,     0,
      90,   167,    92,     0,    96,    97,    98,    99,     0,     0,
       0,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,     0,     0,     0,   190,     0,     0,     0,
       0,    94,    95,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    96,    97,    98,    99,     0,     0,     0,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,    63,     0,   175,     0,     0,    64,     0,    26,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     6,    76,    77,    78,    79,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    80,    81,     0,    63,
       0,     0,     0,     0,    64,    82,    26,     0,     0,     0,
       0,    88,     0,    90,   167,    92,     0,     0,     0,     0,
       6,    76,    77,    78,    79,     0,     7,     8,     9,    10,
      11,    12,    13,    14,    80,    81,     0,     0,     0,     0,
       0,     0,     0,    82,    94,    95,     0,     0,     0,    88,
       0,    90,   167,    92,     0,    96,    97,    98,    99,     0,
       0,     0,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,     0,     0,   178,     0,     0,     0,
       0,     0,    94,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    96,    97,    98,    99,     0,     0,     0,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,    63,     0,   180,     0,     0,    64,     0,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,    76,    77,    78,    79,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    80,    81,     0,
       0,     0,     0,     0,     0,     0,    82,     0,     0,     0,
       0,     0,    88,     0,    90,   167,    92,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,    95,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    96,    97,    98,    99,
       0,     0,     0,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   -54,     0,  -108,    63,     0,
       0,     0,     0,    64,     0,    26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
      76,    77,    78,    79,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    80,    81,     0,    63,     0,     0,   282,
       0,    64,    82,    26,     0,     0,     0,     0,    88,     0,
      90,   167,    92,     0,     0,     0,     0,     6,    76,    77,
      78,    79,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    80,    81,     0,     0,     0,     0,     0,     0,     0,
      82,    94,    95,     0,     0,     0,    88,     0,    90,   167,
     283,     0,    96,    97,    98,    99,     0,     0,     0,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,    94,
      95,     0,     0,     0,     0,     0,     0,     0,     0,   284,
      96,    97,    98,    99,     0,     0,     0,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,    63,
       0,     0,     0,     0,    64,   193,    26,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       6,    76,    77,    78,    79,     0,     7,     8,     9,    10,
      11,    12,    13,    14,    80,    81,     0,     0,     0,     0,
       0,     0,     0,    82,     0,     0,     0,     0,     0,    88,
       0,    90,   167,   283,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    94,    95,     0,     0,     0,     0,     0,     0,
       0,     0,   284,    96,    97,    98,    99,     0,     0,     0,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,    63,     0,     0,     0,     0,    64,   193,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,    76,    77,    78,    79,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    80,    81,     0,
      63,     0,     0,     0,     0,    64,    82,    26,     0,     0,
       0,     0,    88,     0,    90,   167,    92,     0,     0,     0,
       0,     6,    76,    77,    78,    79,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    80,    81,     0,     0,     0,
       0,     0,     0,     0,    82,    94,    95,     0,     0,     0,
      88,     0,    90,   167,   283,     0,    96,    97,    98,    99,
       0,     0,     0,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,    94,    95,     0,     0,     0,     0,     0,
       0,     0,     0,   284,    96,    97,    98,    99,     0,     0,
       0,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,    63,     0,     0,     0,     0,    64,     0,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,    76,    77,    78,    79,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    80,    81,
       0,    63,     0,     0,     0,     0,    64,    82,    26,     0,
       0,     0,     0,    88,     0,    90,   167,    92,     0,     0,
       0,     0,     6,    76,    77,    78,    79,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    80,    81,     0,     0,
       0,     0,     0,     0,     0,    82,    94,    95,     0,     0,
       0,    88,     0,    90,   203,    92,     0,    96,    97,    98,
      99,     0,     0,     0,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,     0,     0,     0,     0,
       0,     0,     0,     0,    94,    95,     0,     0,     0,     0,
       0,     0,     0,     0,    63,    96,    97,    98,    99,    64,
       0,    26,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,     0,     6,    76,    77,    78,    79,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    80,
      81,     0,     0,     0,     0,     0,     0,     0,    82,     0,
       0,     0,     0,     0,    88,     0,    90,   318,    92,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    94,    95,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    96,    97,
      98,    99,     0,     0,     0,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   222,   223,     0,
       0,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   257,   258,   259,     0,     0,   222,   223,     0,
     404,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   257,   258,   259,     0,     0,   222,   223,     0,
     406,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   257,   258,   259,     0,     0,   222,   223,     0,
     426,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   257,   258,   259,     0,     0,   222,   223,     0,
     427,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   257,   258,   259,     0,     0,   222,   223,     0,
     434,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   257,   258,   259,     0,   222,   223,  -138,  -138,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   257,   258,   259,     0,   222,   223,     0,   382,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     257,   258,   259,   222,   223,   396,     0,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   257,   258,
     259,   222,   223,   431,     0,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   257,   258,   259,     0,
     260,   222,   223,     0,     0,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   257,   258,   259,     0,
     299,   222,   223,     0,     0,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   257,   258,   259,     0,
     301,   222,   223,     0,     0,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   257,   258,   259,     0,
     302,   222,   223,     0,     0,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   257,   258,   259,     0,
     303,   222,   223,     0,     0,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   257,   258,   259,   294,
     222,   223,     0,     0,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   257,   258,   259,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   257,   258,   259,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   257,   258,
     259,  -139,  -139,  -139,  -139,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   257,
     258,   259,  -139,  -139,  -139,  -139,  -139,  -139,  -139,  -139,
    -139,  -139,  -139,  -139,  -139,  -139,  -139,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   257,   258,   259
};

static const yytype_int16 yycheck[] =
{
      27,   272,    63,     1,    18,    19,   161,    10,   163,   262,
       3,   264,    25,    26,   193,    29,     0,    29,    61,   421,
      60,    61,   441,    84,   424,   281,    24,    25,    89,    90,
      48,    91,    92,    61,    53,    61,   455,    98,    99,    15,
      61,   102,   103,    45,    58,    59,    66,    67,    75,   449,
     321,    92,    29,     4,    72,     6,    66,    67,     9,   411,
     239,    12,    60,   482,    15,    83,    45,    85,    86,    87,
      60,    60,    90,    91,    92,    30,    94,    95,    96,    97,
     123,   433,   484,   101,    82,   124,   104,   105,   106,   107,
     108,   109,   110,   111,    92,   123,   122,   123,   116,   355,
      51,   354,   123,    15,    94,    94,   126,   167,    66,    67,
     122,   124,    66,    67,   155,   156,   126,    66,    67,     5,
     123,     7,    29,    61,   476,   119,   120,   121,   283,   284,
     122,   121,   119,   120,   121,   388,   389,   125,   123,   127,
      60,    61,   169,   203,   162,   398,    61,   403,   166,   167,
     122,   149,   408,    60,    61,    62,   123,   155,   156,   124,
     125,    94,    95,    96,    97,    98,    99,   100,   126,   125,
     126,    45,   126,   124,   123,    14,    66,    67,    18,    19,
      45,    30,   453,    29,    62,   203,   119,   120,   121,   207,
      29,    62,    62,    62,   123,   193,    35,    36,    37,    38,
      39,    40,    41,    42,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   376,   377,   283,   123,   380,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   280,
     259,   239,   283,   261,   305,   263,    62,   122,   267,     4,
     123,     6,   103,     5,     9,   121,   124,    12,   318,   123,
      15,   123,   122,   281,    29,   283,   123,   294,   309,   122,
      62,   123,    60,    60,   272,   125,   121,   121,   126,   297,
     298,    62,   280,    60,   282,   283,   127,   122,   121,   125,
     308,   122,   306,    64,   124,   313,    51,   123,   126,   123,
     318,   362,    61,    61,   127,   127,    62,   462,    61,   124,
     124,   309,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,    62,   321,    62,    31,   126,    10,   126,    61,
       5,    62,   126,   124,    46,   353,   125,   355,    14,    19,
     119,   120,   121,    67,    25,    62,   124,   123,   375,   124,
     411,   378,   379,    29,   381,   122,   124,   126,    34,    35,
      36,    37,    38,    39,    40,    41,    42,   124,    62,   124,
       4,    40,   433,    29,   365,     8,   126,   126,   126,   126,
      13,   126,    15,   126,   305,   403,    90,   116,   283,   448,
     408,   449,    82,    -1,    -1,    -1,    29,    30,    31,    32,
      33,    -1,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    -1,   476,   443,   415,   445,    52,
      -1,    -1,    -1,    -1,    -1,    58,    29,    60,    61,    62,
     448,   458,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,   472,    -1,   474,    -1,    -1,
     477,    -1,    -1,   480,    -1,   453,    -1,    -1,    91,    92,
     487,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,   102,
     103,   104,   105,    13,    -1,    15,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,    -1,    29,
      30,    31,    32,    33,   127,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    -1,     8,    -1,    -1,    -1,
      -1,    13,    52,    15,    -1,    -1,    -1,    -1,    58,    -1,
      60,    61,    62,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    -1,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    91,    92,    -1,    -1,    -1,    58,    -1,    60,    61,
      62,    -1,   102,   103,   104,   105,    -1,    -1,    -1,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,    -1,    -1,    -1,    -1,    -1,    -1,   127,    -1,    91,
      92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,
     102,   103,   104,   105,    13,    -1,    15,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,    -1,
      29,    30,    31,    32,    33,   127,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    -1,     8,    -1,    -1,
      -1,    -1,    13,    52,    15,    -1,    -1,    -1,    -1,    58,
      -1,    60,    61,    62,    -1,    -1,    -1,    -1,    29,    30,
      31,    32,    33,    -1,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    91,    92,    -1,    -1,    -1,    58,    -1,    60,
      61,    62,    -1,   102,   103,   104,   105,    -1,    -1,    -1,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,    -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,
      91,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,   103,   104,   105,    -1,    -1,    -1,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
      -1,     8,    -1,    -1,    -1,   126,    13,    -1,    15,    16,
      17,    -1,    -1,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    -1,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    91,    92,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,    -1,
      -1,    -1,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,     8,    -1,   123,   124,    -1,    13,
      -1,    15,    16,    17,    -1,    -1,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,
     104,   105,    -1,    -1,    -1,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,     8,    -1,   123,
     124,    -1,    13,    -1,    15,    16,    17,    -1,    -1,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    -1,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      91,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,   103,   104,   105,    -1,    -1,    -1,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
       8,    -1,   123,   124,    -1,    13,    -1,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    -1,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,     8,    -1,
      -1,    -1,    -1,    13,    52,    15,    -1,    -1,    -1,    -1,
      58,    -1,    60,    61,    62,    -1,    -1,    -1,    -1,    29,
      30,    31,    32,    33,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    52,    91,    92,    -1,    -1,    -1,    58,    -1,
      60,    61,    62,    -1,   102,   103,   104,   105,    -1,    -1,
      -1,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,    -1,    -1,    -1,   124,    -1,    -1,    -1,
      -1,    91,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,    -1,    -1,    -1,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,     8,    -1,   123,    -1,    -1,    13,    -1,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    33,    -1,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,     8,
      -1,    -1,    -1,    -1,    13,    52,    15,    -1,    -1,    -1,
      -1,    58,    -1,    60,    61,    62,    -1,    -1,    -1,    -1,
      29,    30,    31,    32,    33,    -1,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    91,    92,    -1,    -1,    -1,    58,
      -1,    60,    61,    62,    -1,   102,   103,   104,   105,    -1,
      -1,    -1,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,    -1,    -1,   123,    -1,    -1,    -1,
      -1,    -1,    91,    92,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,   103,   104,   105,    -1,    -1,    -1,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,     8,    -1,   123,    -1,    -1,    13,    -1,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    30,    31,    32,    33,    -1,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,
      -1,    -1,    58,    -1,    60,    61,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    92,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,
      -1,    -1,    -1,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,     5,    -1,   123,     8,    -1,
      -1,    -1,    -1,    13,    -1,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      30,    31,    32,    33,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    -1,     8,    -1,    -1,    11,
      -1,    13,    52,    15,    -1,    -1,    -1,    -1,    58,    -1,
      60,    61,    62,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    -1,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    91,    92,    -1,    -1,    -1,    58,    -1,    60,    61,
      62,    -1,   102,   103,   104,   105,    -1,    -1,    -1,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,
      92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
     102,   103,   104,   105,    -1,    -1,    -1,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      29,    30,    31,    32,    33,    -1,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    58,
      -1,    60,    61,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    91,    92,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   101,   102,   103,   104,   105,    -1,    -1,    -1,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,     8,    -1,    -1,    -1,    -1,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    30,    31,    32,    33,    -1,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
       8,    -1,    -1,    -1,    -1,    13,    52,    15,    -1,    -1,
      -1,    -1,    58,    -1,    60,    61,    62,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    -1,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    91,    92,    -1,    -1,    -1,
      58,    -1,    60,    61,    62,    -1,   102,   103,   104,   105,
      -1,    -1,    -1,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    92,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,   102,   103,   104,   105,    -1,    -1,
      -1,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,     8,    -1,    -1,    -1,    -1,    13,    -1,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,     8,    -1,    -1,    -1,    -1,    13,    52,    15,    -1,
      -1,    -1,    -1,    58,    -1,    60,    61,    62,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    33,    -1,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    91,    92,    -1,    -1,
      -1,    58,    -1,    60,    61,    62,    -1,   102,   103,   104,
     105,    -1,    -1,    -1,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    91,    92,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     8,   102,   103,   104,   105,    13,
      -1,    15,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,    -1,    29,    30,    31,    32,    33,
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,
      -1,    -1,    -1,    -1,    58,    -1,    60,    61,    62,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,
     104,   105,    -1,    -1,    -1,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,    64,    65,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   119,   120,   121,    -1,    -1,    64,    65,    -1,
     127,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   119,   120,   121,    -1,    -1,    64,    65,    -1,
     127,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   119,   120,   121,    -1,    -1,    64,    65,    -1,
     127,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   119,   120,   121,    -1,    -1,    64,    65,    -1,
     127,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   119,   120,   121,    -1,    -1,    64,    65,    -1,
     127,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   119,   120,   121,    -1,    64,    65,   125,   126,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   119,   120,   121,    -1,    64,    65,    -1,   126,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     119,   120,   121,    64,    65,   124,    -1,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,   120,
     121,    64,    65,   124,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   119,   120,   121,    -1,
     123,    64,    65,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   119,   120,   121,    -1,
     123,    64,    65,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   119,   120,   121,    -1,
     123,    64,    65,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   119,   120,   121,    -1,
     123,    64,    65,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   119,   120,   121,    -1,
     123,    64,    65,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   119,   120,   121,   122,
      64,    65,    -1,    -1,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   119,   120,   121,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,   120,   121,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,   120,
     121,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,
     120,   121,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   119,   120,   121
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,   129,   130,   131,   132,    29,    35,    36,    37,
      38,    39,    40,    41,    42,   198,     0,   132,    61,   122,
     123,   133,     4,     6,     9,    12,    15,    51,   134,   135,
     136,   137,   138,   140,   141,   146,   147,   148,   154,   155,
     154,    45,    45,    29,   203,    30,   198,   198,    61,   169,
     124,   136,   123,     5,     7,    15,   123,   133,   122,   122,
      10,   123,   123,     8,    13,    16,    17,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    30,    31,    32,    33,
      43,    44,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    91,    92,   102,   103,   104,   105,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   123,   149,   154,   156,   157,   158,   159,   160,
     161,   164,   165,   166,   167,   169,   170,   174,   176,   177,
     178,   179,   180,   181,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   198,    29,   122,
     204,    61,   142,    45,    45,   154,   154,   198,   195,    29,
      62,    62,    62,    62,   123,   123,    62,    61,   174,   122,
     123,   169,   198,   200,   201,   123,   174,   195,   123,   174,
     123,   174,   174,   195,   151,   152,   171,   174,   175,   195,
     124,   174,   175,    14,   175,   196,   197,   198,   199,   200,
     174,   174,   174,    61,   174,   195,   195,   103,   174,   195,
     195,   174,   174,   174,   174,   174,   174,   174,   174,     5,
     124,   158,    64,    65,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   119,   120,   121,
     123,    60,    61,    60,    61,   123,   123,   121,    34,   196,
     198,   202,   122,   143,   144,   145,   204,   196,   196,   123,
     122,    62,    11,    62,   101,   139,   173,   174,   182,   173,
     172,   174,   173,   174,   122,   169,   123,    60,    60,   123,
     121,   123,   123,   123,   121,   125,   127,   127,   125,   122,
     124,   197,   126,   126,    60,    94,    60,   174,    61,   174,
     121,   122,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   197,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,    60,    61,    62,   204,   174,   203,   174,
     203,   204,    62,   202,   124,   125,    64,   123,   196,   171,
     198,   173,   174,   182,   173,   126,    66,    67,   126,   126,
     123,   126,   126,   169,   127,   174,   127,   174,    61,    61,
     152,   195,   154,   174,   196,   174,   124,   174,    61,   202,
     174,   203,   171,    62,   127,   124,   127,   124,    62,   150,
     151,    62,   145,    31,   126,    10,   126,   169,   173,   173,
     169,   169,   173,   169,    61,   162,   127,   127,   203,   203,
       5,   124,   203,    62,   127,   124,   126,   171,   171,    46,
     153,   150,   198,    19,    18,    19,   168,   168,   123,   163,
     164,   124,   124,   122,   124,   150,   126,   126,   126,   153,
     123,   169,    62,   169,   172,   124,   164,   165,   202,   153,
     123,   169,   126,   173,   126,   124,    62,   126,   123,   169,
     126,   169,   150,   169,   169,   153,   168,   126,   169
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   128,   129,   130,   130,   131,   131,   132,   132,   132,
     132,   133,   134,   134,   135,   135,   136,   136,   136,   136,
     136,   136,   136,   137,   138,   138,   139,   139,   140,   141,
     142,   143,   143,   144,   144,   144,   145,   145,   146,   147,
     148,   148,   148,   148,   149,   149,   150,   150,   151,   151,
     151,   152,   153,   153,   154,   154,   155,   155,   156,   156,
     157,   157,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   159,   160,   161,   162,
     162,   163,   163,   164,   164,   165,   165,   166,   166,   167,
     167,   168,   168,   168,   169,   170,   171,   171,   172,   172,
     173,   173,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   175,   175,   175,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   177,   177,   178,   178,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   181,   181,   181,   181,   181,   182,
     182,   182,   182,   183,   183,   184,   184,   184,   185,   185,
     185,   186,   187,   187,   187,   188,   188,   188,   188,   188,
     188,   188,   189,   189,   189,   190,   191,   192,   193,   193,
     193,   193,   194,   194,   195,   196,   196,   197,   197,   197,
     198,   198,   198,   198,   198,   198,   198,   198,   198,   199,
     200,   200,   201,   201,   202,   202,   203,   204
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     4,     6,     4,
       6,     3,     0,     1,     2,     1,     1,     1,     1,     2,
       1,     1,     1,     2,     3,     5,     2,     5,     3,     3,
       3,     0,     1,     3,     2,     1,     1,     3,     5,     6,
      10,    10,     9,     9,     9,    12,     0,     1,     3,     2,
       1,     3,     0,     1,     0,     1,     2,     1,     0,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     3,     2,     3,     2,
       3,     3,     2,     2,     1,     1,     9,     5,     5,     3,
       4,     2,     1,     4,     3,     3,     2,     5,     7,     6,
       6,     0,     2,     6,     3,     3,     0,     1,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     2,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     2,     3,
       3,     2,     3,     3,     3,     2,     2,     1,     3,     3,
       2,     4,     5,     4,     4,     5,     2,     6,     3,     6,
       3,     5,     5,     4,     4,     6,     6,     6,     2,     4,
       3,     5,     4,     2,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     3,     4,     4,     1,     1,     1,     1
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
        case 2:
#line 67 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_grammar(compiler, (yyvsp[0].opval));
      compiler->op_grammar = (yyval.opval);
    }
#line 2270 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 74 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2278 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2293 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2311 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 108 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[-1].opval), NULL);
    }
#line 2319 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 112 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-5].opval), (yyvsp[-4].opval), (yyvsp[-1].opval), (yyvsp[-2].opval));
    }
#line 2327 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 116 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), NULL, NULL);
    }
#line 2335 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 120 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-5].opval), (yyvsp[-4].opval), NULL, (yyvsp[-2].opval));
    }
#line 2343 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 126 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_class_block;
    }
#line 2353 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 134 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2361 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 138 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[0].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
        SPVM_OP_insert_child(compiler, (yyval.opval), (yyval.opval)->last, (yyvsp[0].opval));
      }
    }
#line 2375 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 150 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2393 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 176 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    { 
      SPVM_OP* op_method = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_METHOD, compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_method_name = SPVM_OP_new_op_name(compiler, "INIT", compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_void_type = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);

      SPVM_OP* op_list_descriptors = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_descriptor_static = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_STATIC, compiler->cur_file, compiler->cur_line);
      SPVM_OP_insert_child(compiler, op_list_descriptors, op_list_descriptors->first, op_descriptor_static);

      int32_t can_precompile = 0;
      (yyval.opval) = SPVM_OP_build_method(compiler, op_method, op_method_name, op_void_type, NULL, op_list_descriptors, (yyvsp[0].opval), NULL, NULL, 1, 0, can_precompile);
    }
#line 2410 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 191 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), NULL, 0);
    }
#line 2418 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 195 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), 0);
    }
#line 2426 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 201 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_use(compiler, op_use, (yyvsp[0].opval), NULL, 1);
    }
#line 2435 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 206 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_use(compiler, op_use, (yyvsp[-3].opval), (yyvsp[-1].opval), 1);
    }
#line 2444 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 213 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_allow(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2452 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 220 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), (yyvsp[-2].opval));
    }
#line 2460 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 226 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_enum_block;
    }
#line 2470 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 234 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2478 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 238 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2493 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 251 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2511 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 269 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[0].opval), NULL);
    }
#line 2519 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 273 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2527 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 279 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_our(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 2535 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 285 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_has(compiler, (yyvsp[-5].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2543 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 291 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t can_precompile = 1;
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-8].opval), (yyvsp[-7].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-9].opval), (yyvsp[0].opval), NULL, (yyvsp[-2].opval), 0, 0, can_precompile);
     }
#line 2552 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 296 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t can_precompile = 0;
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-8].opval), (yyvsp[-7].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-9].opval), NULL, NULL, (yyvsp[-2].opval), 0, 0, can_precompile);
     }
#line 2561 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 301 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t can_precompile = 1;
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), NULL, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-8].opval), (yyvsp[0].opval), NULL, (yyvsp[-2].opval), 0, 0, can_precompile);
     }
#line 2570 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 306 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t can_precompile = 0;
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), NULL, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-8].opval), NULL, NULL, (yyvsp[-2].opval), 0, 0, can_precompile);
     }
#line 2579 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 313 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t is_init = 0;
       int32_t is_anon = 1;
       int32_t can_precompile = 1;
       
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), NULL, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-8].opval), (yyvsp[0].opval), NULL, (yyvsp[-2].opval), is_init, is_anon, can_precompile);
     }
#line 2591 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 321 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
       int32_t can_precompile = 1;
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), NULL, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-8].opval), (yyvsp[0].opval), op_list_args, (yyvsp[-2].opval), is_init, is_anon, can_precompile);
     }
#line 2611 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 339 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2619 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 343 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2634 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 356 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2652 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 374 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[-2].opval), (yyvsp[0].opval), NULL);
    }
#line 2660 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 380 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 2668 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 387 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2676 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 391 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2691 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 404 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2709 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 421 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2717 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 425 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2732 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 438 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2750 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 464 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_expression_statement(compiler, (yyvsp[-1].opval));
    }
#line 2758 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 471 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[-1].opval), NULL);
    }
#line 2766 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 475 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2774 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 479 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-1].opval), NULL);
    }
#line 2782 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 483 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2790 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 487 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_warn(compiler, (yyvsp[-1].opval), NULL);
    }
#line 2798 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 491 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_warn(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2806 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 495 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_print(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2814 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 501 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    }
#line 2822 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 504 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
    (yyval.opval) = (yyvsp[0].opval);
  }
#line 2830 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 510 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[-8].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2838 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 516 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2846 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 522 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2854 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 528 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->cur_file, compiler->cur_line);
      op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[-1].opval), NULL);
    }
#line 2864 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 534 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->cur_file, compiler->cur_line);
      op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2874 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 542 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2892 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 556 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 2900 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 562 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2908 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 566 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), NULL);
    }
#line 2916 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 572 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2924 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 576 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[-1].opval), NULL);
    }
#line 2932 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 582 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->cur_file, compiler->cur_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[-2].opval), (yyvsp[0].opval), NULL);
    }
#line 2942 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 588 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->cur_file, compiler->cur_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2952 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 595 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    }
#line 2967 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 606 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    }
#line 2982 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 619 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    }
#line 2990 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 623 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 2998 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 627 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3006 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 633 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_block;
    }
#line 3016 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 641 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 3024 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 647 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 3032 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 651 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3047 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 664 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    }
#line 3055 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 692 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      if ((yyvsp[-1].opval)->id == SPVM_OP_C_ID_LIST) {
        SPVM_OP* op_expression = (yyvsp[-1].opval)->first;
        SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, compiler->cur_file, compiler->cur_line);
        while ((op_expression = SPVM_OP_sibling(compiler, op_expression))) {
          SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_expression);
          SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_expression);
          op_expression = op_stab;
        }
        (yyval.opval) = op_sequence;
      }
      else {
        (yyval.opval) = (yyvsp[-1].opval);
      }
    }
#line 3075 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 712 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_true(compiler, (yyvsp[0].opval));
    }
#line 3083 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 716 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_false(compiler, (yyvsp[0].opval));
    }
#line 3091 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 722 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3109 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 736 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[-1].opval);
    }
#line 3117 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 740 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 3125 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 746 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, op, (yyvsp[0].opval));
    }
#line 3134 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 751 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MINUS, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, op_negate, (yyvsp[0].opval));
    }
#line 3143 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 756 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3151 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 760 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3159 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 764 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3167 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 768 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3175 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 772 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3183 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 776 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3191 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 780 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3199 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 784 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3207 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 788 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3215 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 792 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3223 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 796 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3231 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 802 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, op, (yyvsp[0].opval));
    }
#line 3240 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 807 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, op, (yyvsp[-1].opval));
    }
#line 3249 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 814 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, op, (yyvsp[0].opval));
    }
#line 3258 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 819 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, op, (yyvsp[-1].opval));
    }
#line 3267 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 826 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3276 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 831 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3285 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 836 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MULTIPLY, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3294 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 841 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3302 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 845 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3310 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 849 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3318 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 853 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3326 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 857 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3334 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 861 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3342 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 865 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3350 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 869 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3358 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 873 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3366 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 877 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3374 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 881 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3382 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 887 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3390 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 891 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3398 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 895 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3406 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 899 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3414 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 903 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3422 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 907 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3430 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 911 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3438 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 915 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3446 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 919 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3454 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 923 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3462 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 927 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3470 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 931 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3478 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 935 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3486 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 939 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3494 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 945 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3502 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 949 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[0].opval), (yyvsp[-1].opval), NULL);
    }
#line 3510 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 953 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[0].opval), (yyvsp[-1].opval), NULL);
    }
#line 3518 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 957 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[0].opval), (yyvsp[-1].opval), NULL);
    }
#line 3526 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 961 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[0].opval), (yyvsp[-1].opval), NULL);
    }
#line 3534 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 967 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_or(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3542 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 971 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_and(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3550 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 975 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_not(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3558 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 979 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[-1].opval);
    }
#line 3566 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 985 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3574 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 989 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_special_assign(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3582 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 995 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 3590 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 999 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 3598 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1003 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
      SPVM_OP_build_class(compiler, op_class, NULL, op_class_block, NULL);

      // Type
      SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, op_class->uv.class->op_type->uv.type, op_method->file, op_method->line);
      
      // New
      SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, op_method->file, op_method->line);
      (yyval.opval) = SPVM_OP_build_new(compiler, op_new, op_type, NULL);
    }
#line 3626 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1029 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      int32_t is_key_values = 0;
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[-1].opval), is_key_values);
    }
#line 3636 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1035 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      int32_t is_key_values = 1;
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[-1].opval), is_key_values);
    }
#line 3646 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1041 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      int32_t is_key_values = 1;
      SPVM_OP* op_list_elements = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, op_list_elements, is_key_values);
    }
#line 3657 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1050 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      (yyval.opval) = SPVM_OP_build_convert(compiler, op_convert, (yyvsp[-2].opval), (yyvsp[0].opval), NULL);
    }
#line 3666 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1057 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 3674 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1061 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3682 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1065 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3690 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1071 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3698 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1075 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_expressions = SPVM_OP_new_op_list(compiler, (yyvsp[-1].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), op_expressions);
    }
#line 3707 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1080 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3715 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1084 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_expressions = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-2].opval), (yyvsp[0].opval), op_expressions);
    }
#line 3724 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1089 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3732 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1093 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_expressions = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-2].opval), (yyvsp[0].opval), op_expressions);
    }
#line 3741 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1098 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_method_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[-3].opval)->file, (yyvsp[-3].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-4].opval), op_method_name, (yyvsp[-1].opval));
    }
#line 3750 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1104 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 3758 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1108 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3766 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1112 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3774 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1118 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 3783 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1125 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_unweaken_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 3792 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1132 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_isweak_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 3801 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1139 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[0].opval));
    }
#line 3810 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1144 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[-1].opval));
    }
#line 3819 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1149 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[0].opval));
    }
#line 3828 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1154 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[-1].opval));
    }
#line 3837 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1161 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval), NULL);
    }
#line 3845 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1165 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL, NULL);
    }
#line 3853 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1171 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[0].opval));
    }
#line 3861 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1177 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
    (yyvsp[0].opval)->uv.type->is_mutable = 1;
    (yyval.opval) = (yyvsp[0].opval);
  }
#line 3870 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1189 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[0].opval));
    }
#line 3878 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1193 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_byte_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3888 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1199 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_short_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3898 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1205 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3908 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1211 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_long_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3918 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1217 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_float_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3928 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1223 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_double_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3938 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1229 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_any_object_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3948 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1235 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_string_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3958 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1243 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[-1].opval));
    }
#line 3966 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1249 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-2].opval), NULL);
    }
#line 3974 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1253 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-2].opval), NULL);
    }
#line 3982 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1259 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3990 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1263 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3998 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1270 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 4006 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;


#line 4010 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 1280 "yacc/spvm_yacc.y" /* yacc.c:1906  */

