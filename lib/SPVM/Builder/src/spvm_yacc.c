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
    DESCRIPTOR = 269,
    IF = 270,
    UNLESS = 271,
    ELSIF = 272,
    ELSE = 273,
    FOR = 274,
    WHILE = 275,
    LAST = 276,
    NEXT = 277,
    SWITCH = 278,
    CASE = 279,
    DEFAULT = 280,
    BREAK = 281,
    EVAL = 282,
    NAME = 283,
    VAR_NAME = 284,
    CONSTANT = 285,
    EXCEPTION_VAR = 286,
    UNDEF = 287,
    VOID = 288,
    BYTE = 289,
    SHORT = 290,
    INT = 291,
    LONG = 292,
    FLOAT = 293,
    DOUBLE = 294,
    STRING = 295,
    OBJECT = 296,
    TRUE = 297,
    FALSE = 298,
    DOT3 = 299,
    FATCAMMA = 300,
    RW = 301,
    RO = 302,
    WO = 303,
    INIT = 304,
    NEW = 305,
    RETURN = 306,
    WEAKEN = 307,
    DIE = 308,
    WARN = 309,
    PRINT = 310,
    CURRENT_CLASS_NAME = 311,
    UNWEAKEN = 312,
    ASSIGN = 313,
    SPECIAL_ASSIGN = 314,
    LOGICAL_OR = 315,
    LOGICAL_AND = 316,
    BIT_OR = 317,
    BIT_XOR = 318,
    BIT_AND = 319,
    NUMEQ = 320,
    NUMNE = 321,
    STREQ = 322,
    STRNE = 323,
    NUMGT = 324,
    NUMGE = 325,
    NUMLT = 326,
    NUMLE = 327,
    STRGT = 328,
    STRGE = 329,
    STRLT = 330,
    STRLE = 331,
    ISA = 332,
    NUMERIC_CMP = 333,
    STRING_CMP = 334,
    SHIFT = 335,
    DIVIDE = 336,
    REMAINDER = 337,
    LOGICAL_NOT = 338,
    BIT_NOT = 339,
    CREATE_REF = 340,
    DEREF = 341,
    PLUS = 342,
    MINUS = 343,
    CONVERT = 344,
    SCALAR = 345,
    STRING_LENGTH = 346,
    ISWEAK = 347,
    REFCNT = 348,
    REFOP = 349,
    DUMP = 350,
    INC = 351,
    DEC = 352,
    ARROW = 353
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 232 "spvm_yacc.tab.c" /* yacc.c:358  */

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
#define YYLAST   2994

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  113
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  76
/* YYNRULES -- Number of rules.  */
#define YYNRULES  232
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  461

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   353

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
      60,   111,    87,    84,   110,    85,    86,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   107,   108,
       2,     2,     2,     2,    92,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    58,     2,   112,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    59,     2,   109,     2,     2,     2,     2,
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
      55,    56,    57,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    88,    89,    90,    91,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    65,    65,    73,    76,    89,   103,   106,   110,   114,
     118,   124,   133,   136,   148,   162,   165,   166,   167,   168,
     169,   170,   171,   174,   189,   193,   199,   204,   211,   218,
     224,   233,   236,   249,   263,   264,   267,   271,   277,   283,
     289,   294,   299,   304,   311,   319,   338,   341,   354,   368,
     369,   372,   379,   382,   386,   389,   402,   416,   420,   423,
     436,   450,   453,   454,   455,   456,   457,   458,   459,   460,
     461,   462,   466,   467,   468,   469,   473,   477,   481,   485,
     489,   493,   497,   498,   499,   505,   511,   517,   523,   529,
     537,   551,   557,   561,   567,   571,   577,   583,   590,   601,
     615,   618,   622,   628,   636,   643,   646,   660,   663,   666,
     667,   670,   671,   672,   673,   674,   675,   676,   677,   678,
     679,   680,   681,   682,   683,   684,   685,   686,   687,   703,
     704,   705,   706,   707,   711,   717,   731,   735,   741,   746,
     751,   755,   759,   763,   767,   771,   775,   781,   786,   793,
     798,   805,   810,   815,   820,   824,   828,   832,   836,   840,
     844,   850,   854,   858,   862,   866,   870,   874,   878,   882,
     886,   890,   894,   898,   902,   908,   915,   919,   923,   927,
     933,   937,   943,   947,   951,   977,   983,   989,   998,  1005,
    1009,  1013,  1019,  1023,  1028,  1032,  1037,  1041,  1046,  1052,
    1056,  1060,  1066,  1073,  1080,  1087,  1092,  1097,  1102,  1109,
    1113,  1119,  1125,  1126,  1127,  1130,  1134,  1140,  1146,  1152,
    1158,  1164,  1170,  1176,  1184,  1190,  1194,  1200,  1204,  1210,
    1211,  1217,  1220
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CLASS", "HAS", "METHOD", "OUR", "ENUM",
  "MY", "USE", "AS", "REQUIRE", "ALLOW", "CURRENT_CLASS", "DESCRIPTOR",
  "IF", "UNLESS", "ELSIF", "ELSE", "FOR", "WHILE", "LAST", "NEXT",
  "SWITCH", "CASE", "DEFAULT", "BREAK", "EVAL", "NAME", "VAR_NAME",
  "CONSTANT", "EXCEPTION_VAR", "UNDEF", "VOID", "BYTE", "SHORT", "INT",
  "LONG", "FLOAT", "DOUBLE", "STRING", "OBJECT", "TRUE", "FALSE", "DOT3",
  "FATCAMMA", "RW", "RO", "WO", "INIT", "NEW", "RETURN", "WEAKEN", "DIE",
  "WARN", "PRINT", "CURRENT_CLASS_NAME", "UNWEAKEN", "'['", "'{'", "'('",
  "ASSIGN", "SPECIAL_ASSIGN", "LOGICAL_OR", "LOGICAL_AND", "BIT_OR",
  "BIT_XOR", "BIT_AND", "NUMEQ", "NUMNE", "STREQ", "STRNE", "NUMGT",
  "NUMGE", "NUMLT", "NUMLE", "STRGT", "STRGE", "STRLT", "STRLE", "ISA",
  "NUMERIC_CMP", "STRING_CMP", "SHIFT", "'+'", "'-'", "'.'", "'*'",
  "DIVIDE", "REMAINDER", "LOGICAL_NOT", "BIT_NOT", "'@'", "CREATE_REF",
  "DEREF", "PLUS", "MINUS", "CONVERT", "SCALAR", "STRING_LENGTH", "ISWEAK",
  "REFCNT", "REFOP", "DUMP", "INC", "DEC", "ARROW", "':'", "';'", "'}'",
  "','", "')'", "']'", "$accept", "grammar", "opt_classes", "classes",
  "class", "class_block", "opt_declarations", "declarations",
  "declaration", "init_block", "use", "require", "allow", "enumeration",
  "enumeration_block", "opt_enumeration_values", "enumeration_values",
  "enumeration_value", "our", "has", "method", "anon_method", "opt_args",
  "args", "arg", "opt_vaarg", "opt_descriptors", "descriptors",
  "opt_statements", "statements", "statement", "for_statement",
  "while_statement", "switch_statement", "switch_block", "case_statements",
  "case_statement", "default_statement", "if_require_statement",
  "if_statement", "else_statement", "block", "eval_block",
  "opt_expressions", "opt_expression", "expression_or_logical_op",
  "expression", "expressions", "unary_op", "inc", "dec", "binary_op",
  "comparison_op", "isa", "logical_op", "assign", "new", "array_init",
  "convert", "array_access", "call_spvm_method", "field_access",
  "weaken_field", "unweaken_field", "isweak_field", "array_length",
  "my_var", "var", "type", "basic_type", "ref_type", "array_type",
  "array_type_with_length", "type_or_void", "field_name", "method_name", YY_NULLPTR
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
     305,   306,   307,   308,   309,   310,   311,   312,    91,   123,
      40,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,    43,    45,    46,    42,   336,   337,
     338,   339,    64,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,    58,    59,   125,
      44,    41,    93
};
# endif

#define YYPACT_NINF -388

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-388)))

#define YYTABLE_NINF -138

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-138)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       1,   276,    11,  -388,     1,  -388,  -388,  -388,  -388,  -388,
    -388,  -388,  -388,  -388,  -388,   -46,  -388,  -388,    10,    -7,
    -388,  -388,    -3,    28,   276,   276,  -388,    31,   -72,   223,
    -388,  -388,  -388,  -388,  -388,   -40,  -388,  -388,   103,    73,
      -9,  -388,     4,    17,    -5,    18,   905,  -388,  -388,  -388,
    -388,   -10,    39,  -388,  -388,  -388,    -7,    -7,   276,  -388,
    -388,    99,   106,    71,    78,    87,   111,    69,    74,   128,
    1887,   118,    98,    31,  -388,  -388,  -388,  -388,  -388,  -388,
     276,  1265,    99,  1347,  1429,  1887,  -388,    99,   407,  1003,
    1887,  1887,  1887,  1887,  1969,    99,    99,   136,  1887,    99,
      99,  1887,  1887,  1887,  1887,  -388,  -388,   231,   129,  1101,
    -388,  -388,  -388,  -388,  -388,  -388,  -388,  -388,  -388,  -388,
    2522,  -388,  -388,  -388,  -388,  -388,  -388,  -388,  -388,  -388,
    -388,    83,  -388,    96,   131,   133,  -388,  -388,  -388,  -388,
     137,  -388,   256,   139,   219,  -388,   276,   276,   140,   142,
     190,  1691,  1789,  1511,  1789,  -388,  -388,  1887,  1183,  2762,
      31,  -388,   144,   195,   196,  -388,  -388,  2570,   149,  -388,
    2618,  -388,  2666,  2714,   154,     8,  -388,   151,  2809,   155,
     157,  -388,  2522,    48,    62,   158,     6,  -388,   210,     9,
       9,     9,  1183,     9,  -388,  -388,  2051,     9,   164,  -388,
       9,     9,    61,    61,   166,  -388,  -388,  1887,  1887,  1887,
    1887,  1887,  1887,  1887,  1887,  1887,  1887,  1887,  1887,  1887,
    1887,  1887,  1887,  1887,   276,  1887,  1887,  1887,  1887,  1887,
    1887,  1887,  1887,  1887,  -388,  -388,    93,  -388,  1887,    -3,
    1887,    -3,  -388,  -388,   219,  -388,  -388,    30,   214,   256,
     168,   165,  -388,   217,   171,  -388,  -388,   276,   707,   276,
    1789,  1789,   169,   -30,  2809,  -388,   -22,   173,  2809,    14,
    2383,    31,  -388,  -388,   507,   607,  -388,   224,  -388,  -388,
    -388,   226,    99,    -7,  -388,  1593,   276,  -388,  -388,  1887,
     174,  -388,   175,  2430,  1183,     9,   239,   256,  2809,  2809,
    2849,  2849,   295,  2888,  2888,  2888,  2888,   398,   398,   398,
     398,   398,   398,   398,   398,  -388,   398,   398,    75,    81,
      81,    81,     9,     9,     9,  1887,    -3,   707,   240,  2096,
     192,  2144,   193,   245,    99,   246,  -388,   219,   278,  -388,
    -388,   207,   309,   112,  2336,   211,  -388,    31,  1789,  1789,
      31,    31,  1789,    31,   262,  -388,  -388,  2192,  -388,  2240,
      -3,    -3,  -388,   157,   320,  2809,  -388,     9,  -388,  2476,
      -3,   267,  2288,   220,   222,   707,  -388,  -388,  -388,  -388,
     707,   284,   225,    99,  -388,  -388,  -388,   276,  -388,   312,
     270,  -388,   216,   216,    37,  -388,   313,  -388,  -388,  -388,
     227,   229,   232,  -388,   233,    99,  -388,  -388,  -388,   230,
     234,  -388,   235,   284,   236,    31,   280,    31,  -388,  -388,
     806,     7,  -388,  -388,  -388,   256,  -388,   284,  -388,  -388,
      -4,   237,  -388,  -388,  1789,  -388,   238,  -388,  -388,   241,
     283,   243,  -388,  -388,    -1,    32,    31,  -388,    99,    31,
    -388,  -388,    31,  -388,   284,  -388,   216,   244,  -388,    31,
    -388
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     2,     4,     6,   215,   216,   217,   218,
     219,   220,   221,   223,   222,     0,     1,     5,    54,    54,
       9,     7,     0,     0,     0,     0,    57,     0,     0,    54,
      15,    22,    20,    21,    18,     0,    16,    17,     0,    55,
       0,   231,     0,     0,     0,     0,    54,    23,    11,    14,
      19,     0,     0,    56,    10,     8,    54,    54,     0,    24,
      28,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      54,     0,     0,     0,   211,   113,   112,   114,   133,   134,
       0,    54,     0,    54,    54,    54,   129,     0,    54,    54,
      54,    54,    54,    54,    54,     0,     0,     0,    54,     0,
       0,    54,    54,    54,    54,    84,   184,     0,     0,    54,
      61,    63,    64,    66,    67,    68,    70,    62,    65,    69,
       0,   123,   126,   127,   124,   131,   132,   125,   119,   120,
     118,   117,   115,   116,     0,     0,   130,   121,   122,   111,
       0,   232,     0,     0,    31,    29,     0,     0,     0,   210,
     193,    54,    54,    54,    54,    72,    73,    54,    54,     0,
      95,    74,     0,   182,     0,   183,    75,     0,     0,    77,
       0,    79,     0,     0,     0,     0,    50,     0,   137,   106,
     111,   187,   137,     0,     0,     0,   212,   214,   213,   138,
     139,   140,    54,   205,   146,   145,    54,   143,     0,   141,
     142,   144,   147,   149,     0,   103,    60,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,     0,    54,    54,    54,    54,    54,
      54,    54,    54,    54,   148,   150,     0,    71,    54,     0,
      54,     0,    82,    83,     0,   230,   229,   212,     0,     0,
       0,    32,    35,    36,     0,    38,    25,     0,    54,     0,
      54,    54,     0,     0,   109,   110,     0,     0,   108,     0,
       0,    93,    94,   104,    54,    54,    76,     0,    78,    80,
      81,     0,    49,    54,   185,   136,     0,   186,   128,    54,
       0,   224,     0,   137,    54,   207,     0,     0,   180,   181,
     158,   156,   157,   161,   162,   168,   169,   163,   164,   165,
     166,   170,   171,   172,   173,   175,   167,   174,   159,   151,
     152,   160,   153,   154,   155,    54,     0,    54,   197,     0,
       0,     0,     0,   195,    46,     0,    30,    34,     0,    39,
     209,     0,    26,     0,   109,   110,   178,     0,    54,    54,
       0,     0,    54,     0,     0,    92,   225,     0,   226,     0,
       0,     0,    48,     0,     0,   135,    51,   188,   206,   137,
       0,     0,     0,     0,     0,    54,   190,   201,   191,   200,
      54,    52,    47,    46,    33,    37,   192,     0,   179,    96,
     176,   177,   100,   100,     0,    86,     0,    87,   227,   228,
       0,     0,     0,   208,     0,    46,   189,   199,   198,     0,
       0,    53,     0,    52,     0,     0,     0,     0,    98,    99,
      54,     0,    91,   202,   203,     0,   204,    52,   196,   194,
       0,     0,    27,    97,    54,   101,     0,    88,    90,     0,
       0,     0,    43,    42,     0,     0,     0,    89,    46,     0,
      41,    40,     0,    85,    52,    44,   100,     0,   102,     0,
      45
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -388,  -388,  -388,  -388,   343,   311,  -388,  -388,   323,  -388,
    -388,  -388,  -388,  -388,  -388,  -388,  -388,    19,  -388,  -388,
    -388,  -388,  -354,   271,    76,  -304,   -17,  -388,  -388,  -388,
     251,  -388,  -388,  -388,  -388,  -388,  -376,   -60,  -388,  -388,
    -387,   -27,  -388,  -248,   -35,  -131,   -18,   -36,  -388,  -388,
    -388,  -388,  -388,  -388,   126,  -388,  -388,  -388,  -388,  -388,
    -388,  -388,  -388,  -388,  -388,  -388,  -388,   -52,   -41,     2,
    -388,   307,  -388,  -241,  -224,   -13
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    21,    28,    29,    30,    31,
      32,   262,    33,    34,   145,   250,   251,   252,    35,    36,
      37,   106,   381,   382,   176,   412,   107,    39,   108,   109,
     110,   111,   112,   113,   397,   421,   114,   115,   116,   117,
     418,   118,   119,   177,   267,   263,   264,   179,   121,   122,
     123,   124,   125,   126,   265,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   246,   140,
     187,   188,   165,   248,    42,   253
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      47,    38,    40,    15,     1,    58,   419,    26,   335,   149,
     341,    16,    38,    18,    22,   330,    23,   332,   141,    24,
     422,   266,    25,   269,    26,    41,    44,    45,   120,   413,
     168,    70,    71,   348,   349,   174,   180,    48,   143,   146,
     147,   348,   349,   194,   195,   438,   162,   198,   199,   185,
      18,   427,   159,   183,   184,    46,   371,    43,    46,    27,
     148,    19,    20,   167,   290,   170,   172,   173,    50,   458,
     178,   182,   178,   189,   190,   191,   193,   348,   349,   374,
     197,   350,   163,   200,   201,   202,   203,    53,   290,   351,
      46,   120,   186,   291,   454,   348,   349,   142,   144,    54,
     348,   349,   373,    59,   442,   254,   255,   450,    51,   431,
      52,    56,   244,   234,   235,   236,   437,   291,   282,   -12,
     283,   141,   183,   441,    57,   353,    60,   409,    74,   343,
     346,   151,   410,   272,   150,   268,   400,   401,   152,   270,
     178,   238,   239,   452,   247,   420,   404,   153,   247,   247,
     457,   325,   326,   327,   240,   241,   183,   287,   285,   228,
     229,   230,   231,   232,   233,  -138,  -138,   236,   231,   232,
     233,   154,   285,   288,   293,   348,   349,   155,   295,   234,
     235,   236,   156,   315,   440,   234,   235,   236,   157,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   161,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   340,   390,   391,   185,
     329,   394,   331,   328,   184,   160,   247,    22,   196,    23,
     363,   333,    24,   416,   417,    25,   204,    26,   205,   242,
     178,   243,   344,   244,   355,   366,   249,   141,   256,   257,
     258,   247,   273,   274,   275,   277,   357,   359,   183,   247,
     281,   342,   186,   284,   286,   285,   364,   365,   292,   289,
     296,   367,    27,   297,   334,   337,   369,   336,   338,   339,
     347,   352,   363,   360,     6,   361,   356,   358,   247,   245,
       7,     8,     9,    10,    11,    12,    13,    14,   370,   247,
     375,   377,   379,   445,     6,   380,   383,   372,   385,   178,
       7,     8,     9,    10,    11,    12,    13,    14,   386,   387,
     389,   396,   388,   392,   393,   402,   395,   405,   411,   407,
     415,   363,   -13,   408,   349,   282,   423,    70,   424,   425,
     434,   428,   426,   448,   432,   429,   430,    17,   444,   446,
     447,    55,    49,   363,   449,   459,   384,   178,   362,   175,
     206,   439,   178,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   436,   345,   164,   433,   414,
     435,     0,     0,     0,     0,     0,   363,     0,     0,   234,
     235,   236,   268,   443,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    61,     0,   451,     0,   453,
      62,    26,   455,     0,     0,   456,     0,   247,     0,     0,
       0,     0,   460,     0,     0,     6,    74,    75,    76,    77,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    78,
      79,     0,     0,     0,     0,     0,     0,    80,     0,     0,
       0,     0,     0,    86,     0,    88,   158,    90,     0,     0,
    -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,
    -138,   227,   228,   229,   230,   231,   232,   233,     0,     0,
       0,    91,    92,     0,     0,     0,     0,     0,    93,    94,
      95,    96,   234,   235,   236,    97,    98,    99,   100,   101,
     102,   103,   104,     0,     0,    61,     0,     0,     0,  -105,
      62,    26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,    74,    75,    76,    77,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    78,
      79,     0,     0,     0,     0,     0,     0,    80,     0,     0,
       0,     0,     0,    86,     0,    88,   158,    90,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    91,    92,     0,     0,     0,     0,     0,    93,    94,
      95,    96,     0,     0,     0,    97,    98,    99,   100,   101,
     102,   103,   104,     0,     0,    61,     0,     0,     0,   356,
      62,    26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,    74,    75,    76,    77,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    78,
      79,     0,     0,     0,     0,     0,     0,    80,     0,     0,
       0,     0,     0,    86,     0,    88,   158,    90,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    91,    92,     0,     0,     0,     0,     0,    93,    94,
      95,    96,     0,     0,     0,    97,    98,    99,   100,   101,
     102,   103,   104,     0,     0,    61,     0,     0,     0,   358,
      62,    26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,    74,    75,    76,    77,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    78,
      79,     0,     0,     0,     0,     0,     0,    80,     0,     0,
       0,     0,     0,    86,     0,    88,   158,    90,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    91,    92,     0,     0,     0,     0,     0,    93,    94,
      95,    96,     0,     0,     0,    97,    98,    99,   100,   101,
     102,   103,   104,     0,    61,     0,     0,     0,  -105,    62,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,    74,    75,    76,    77,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    78,    79,
       0,     0,     0,     0,     0,     0,    80,     0,     0,     0,
       0,     0,    86,     0,    88,   158,    90,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      91,    92,     0,     0,     0,     0,     0,    93,    94,    95,
      96,     0,     0,     0,    97,    98,    99,   100,   101,   102,
     103,   104,     0,    61,     0,     0,     0,  -107,    62,    26,
      63,    64,     0,     0,    65,    66,    67,    68,    69,    70,
      71,    72,    73,     6,    74,    75,    76,    77,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    78,    79,     0,
       0,     0,     0,     0,     0,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    91,
      92,     0,     0,     0,     0,     0,    93,    94,    95,    96,
       0,     0,     0,    97,    98,    99,   100,   101,   102,   103,
     104,    61,     0,   105,   -58,     0,    62,    26,    63,    64,
       0,     0,    65,    66,    67,    68,    69,    70,    71,    72,
      73,     6,    74,    75,    76,    77,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    78,    79,     0,     0,     0,
       0,     0,     0,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    91,    92,     0,
       0,     0,     0,     0,    93,    94,    95,    96,     0,     0,
       0,    97,    98,    99,   100,   101,   102,   103,   104,    61,
       0,   105,   181,     0,    62,    26,    63,    64,     0,     0,
      65,    66,    67,    68,    69,    70,    71,    72,    73,     6,
      74,    75,    76,    77,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    78,    79,     0,     0,     0,     0,     0,
       0,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    91,    92,     0,     0,     0,
       0,    61,    93,    94,    95,    96,    62,    26,     0,    97,
      98,    99,   100,   101,   102,   103,   104,     0,     0,   105,
     -59,     6,    74,    75,    76,    77,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    78,    79,     0,     0,     0,
       0,     0,     0,    80,     0,     0,     0,     0,     0,    86,
       0,    88,   158,    90,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    91,    92,     0,
       0,     0,     0,    61,    93,    94,    95,    96,    62,    26,
       0,    97,    98,    99,   100,   101,   102,   103,   104,     0,
       0,     0,   181,     6,    74,    75,    76,    77,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    78,    79,     0,
       0,     0,     0,     0,     0,    80,     0,     0,     0,     0,
       0,    86,     0,    88,   158,    90,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    91,
      92,     0,     0,     0,     0,    61,    93,    94,    95,    96,
      62,    26,     0,    97,    98,    99,   100,   101,   102,   103,
     104,     0,     0,   166,     0,     6,    74,    75,    76,    77,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    78,
      79,     0,     0,     0,     0,     0,     0,    80,     0,     0,
       0,     0,     0,    86,     0,    88,   158,    90,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    91,    92,     0,     0,     0,     0,    61,    93,    94,
      95,    96,    62,    26,     0,    97,    98,    99,   100,   101,
     102,   103,   104,     0,     0,   169,     0,     6,    74,    75,
      76,    77,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    78,    79,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,    86,     0,    88,   158,    90,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    91,    92,     0,     0,     0,     0,    61,
      93,    94,    95,    96,    62,    26,     0,    97,    98,    99,
     100,   101,   102,   103,   104,     0,     0,   171,     0,     6,
      74,    75,    76,    77,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    78,    79,     0,     0,     0,     0,     0,
       0,    80,     0,     0,     0,     0,     0,    86,     0,    88,
     158,    90,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    91,    92,     0,   -54,     0,
       0,    61,    93,    94,    95,    96,    62,    26,     0,    97,
      98,    99,   100,   101,   102,   103,   104,     0,     0,  -107,
       0,     6,    74,    75,    76,    77,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    78,    79,     0,     0,     0,
       0,     0,     0,    80,     0,     0,     0,     0,     0,    86,
       0,    88,   158,    90,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    91,    92,     0,
       0,     0,     0,     0,    93,    94,    95,    96,     0,     0,
       0,    97,    98,    99,   100,   101,   102,   103,   104,    61,
       0,     0,   259,     0,    62,    26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
      74,    75,    76,    77,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    78,    79,     0,     0,     0,     0,     0,
       0,    80,     0,     0,     0,     0,     0,    86,     0,    88,
     158,   260,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    91,    92,     0,     0,     0,
       0,   261,    93,    94,    95,    96,     0,     0,     0,    97,
      98,    99,   100,   101,   102,   103,   104,    61,     0,     0,
       0,     0,    62,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6,    74,    75,
      76,    77,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    78,    79,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,    86,     0,    88,   158,   260,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    91,    92,     0,     0,     0,     0,   261,
      93,    94,    95,    96,     0,     0,     0,    97,    98,    99,
     100,   101,   102,   103,   104,    61,     0,     0,     0,     0,
      62,    26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,    74,    75,    76,    77,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    78,
      79,     0,     0,     0,     0,     0,     0,    80,     0,     0,
       0,     0,     0,    86,     0,    88,   158,    90,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    91,    92,     0,     0,     0,     0,    61,    93,    94,
      95,    96,    62,    26,     0,    97,    98,    99,   100,   101,
     102,   103,   104,     0,     0,     0,     0,     6,    74,    75,
      76,    77,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    78,    79,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,    86,     0,    88,   192,    90,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    91,    92,     0,     0,     0,     0,    61,
      93,    94,    95,    96,    62,    26,     0,    97,    98,    99,
     100,   101,   102,   103,   104,     0,     0,     0,     0,     6,
      74,    75,    76,    77,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    78,    79,     0,     0,     0,     0,     0,
       0,    80,     0,     0,     0,     0,     0,    86,     0,    88,
     294,    90,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    91,    92,     0,     0,     0,
       0,     0,    93,    94,    95,    96,     0,     0,     0,    97,
      98,    99,   100,   101,   102,   103,   104,   207,   208,     0,
       0,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     234,   235,   236,     0,     0,   207,   208,     0,   376,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   234,   235,
     236,     0,     0,   207,   208,     0,   378,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   234,   235,   236,     0,
       0,   207,   208,     0,   398,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   234,   235,   236,     0,     0,   207,
     208,     0,   399,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   234,   235,   236,     0,     0,   207,   208,     0,
     406,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     234,   235,   236,     0,   207,   208,  -137,  -137,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   234,   235,   236,
       0,   207,   208,     0,   354,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   234,   235,   236,   207,   208,   368,
       0,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     234,   235,   236,   207,   208,   403,     0,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   234,   235,   236,     0,
     237,   207,   208,     0,     0,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   234,   235,   236,     0,   276,   207,
     208,     0,     0,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   234,   235,   236,     0,   278,   207,   208,     0,
       0,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     234,   235,   236,     0,   279,   207,   208,     0,     0,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   234,   235,
     236,     0,   280,   207,   208,     0,     0,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   234,   235,   236,   271,
     207,   208,     0,     0,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   234,   235,   236,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   234,   235,   236,  -138,  -138,  -138,  -138,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   234,   235,   236
};

static const yytype_int16 yycheck[] =
{
      27,    18,    19,     1,     3,    10,   393,    14,   249,    61,
     258,     0,    29,    59,     4,   239,     6,   241,    28,     9,
     396,   152,    12,   154,    14,    28,    24,    25,    46,   383,
      82,    24,    25,    63,    64,    87,    88,   109,    51,    56,
      57,    63,    64,    95,    96,   421,    73,    99,   100,    90,
      59,   405,    70,    89,    90,    59,   297,    29,    59,    49,
      58,   107,   108,    81,    58,    83,    84,    85,   108,   456,
      88,    89,    90,    91,    92,    93,    94,    63,    64,   327,
      98,   111,    80,   101,   102,   103,   104,    14,    58,   111,
      59,   109,    90,    87,   448,    63,    64,   107,    59,   108,
      63,    64,   326,   108,   108,   146,   147,   108,     5,   413,
       7,   107,   106,   104,   105,   106,   109,    87,   110,   109,
     112,    28,   158,   427,   107,   111,   108,   375,    29,   260,
     261,    60,   380,   160,    28,   153,   360,   361,    60,   157,
     158,    58,    59,   111,   142,   108,   370,    60,   146,   147,
     454,    58,    59,    60,    58,    59,   192,   109,   110,    84,
      85,    86,    87,    88,    89,   104,   105,   106,    87,    88,
      89,    60,   110,   111,   192,    63,    64,   108,   196,   104,
     105,   106,   108,   224,   425,   104,   105,   106,    60,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   108,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   257,   348,   349,   260,
     238,   352,   240,   236,   260,   107,   224,     4,    92,     6,
     282,   244,     9,    17,    18,    12,     5,    14,   109,   108,
     258,   108,   260,   106,   271,   286,   107,    28,   108,   107,
      60,   249,   108,    58,    58,   106,   274,   275,   294,   257,
     106,   259,   260,   112,   107,   110,   283,   285,    58,   111,
     106,   289,    49,   107,    60,   110,   294,   109,    61,   108,
     111,   108,   334,    59,    28,    59,   112,   112,   286,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    59,   297,
      60,   109,   109,   434,    28,    60,    60,   325,    30,   327,
      34,    35,    36,    37,    38,    39,    40,    41,   111,    10,
     347,    59,   111,   350,   351,     5,   353,    60,    44,   109,
      18,   383,   109,   111,    64,   110,   109,    24,   109,   107,
      60,   111,   109,    60,   108,   111,   111,     4,   111,   111,
     109,    40,    29,   405,   111,   111,   337,   375,   282,    88,
     109,   421,   380,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,   420,   260,    80,   415,   387,
     417,    -1,    -1,    -1,    -1,    -1,   448,    -1,    -1,   104,
     105,   106,   420,   430,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     8,    -1,   444,    -1,   446,
      13,    14,   449,    -1,    -1,   452,    -1,   425,    -1,    -1,
      -1,    -1,   459,    -1,    -1,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    58,    59,    60,    -1,    -1,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    -1,
      -1,    84,    85,    -1,    -1,    -1,    -1,    -1,    91,    92,
      93,    94,   104,   105,   106,    98,    99,   100,   101,   102,
     103,   104,   105,    -1,    -1,     8,    -1,    -1,    -1,   112,
      13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    58,    59,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    85,    -1,    -1,    -1,    -1,    -1,    91,    92,
      93,    94,    -1,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,    -1,    -1,     8,    -1,    -1,    -1,   112,
      13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    58,    59,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    85,    -1,    -1,    -1,    -1,    -1,    91,    92,
      93,    94,    -1,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,    -1,    -1,     8,    -1,    -1,    -1,   112,
      13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    58,    59,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    85,    -1,    -1,    -1,    -1,    -1,    91,    92,
      93,    94,    -1,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,    -1,     8,    -1,    -1,    -1,   111,    13,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    58,    59,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    -1,    -1,    -1,    -1,    91,    92,    93,
      94,    -1,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,   105,    -1,     8,    -1,    -1,    -1,   111,    13,    14,
      15,    16,    -1,    -1,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      85,    -1,    -1,    -1,    -1,    -1,    91,    92,    93,    94,
      -1,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
     105,     8,    -1,   108,   109,    -1,    13,    14,    15,    16,
      -1,    -1,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,
      -1,    -1,    -1,    -1,    91,    92,    93,    94,    -1,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,     8,
      -1,   108,   109,    -1,    13,    14,    15,    16,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,
      -1,     8,    91,    92,    93,    94,    13,    14,    -1,    98,
      99,   100,   101,   102,   103,   104,   105,    -1,    -1,   108,
     109,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,
      -1,    -1,    -1,     8,    91,    92,    93,    94,    13,    14,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,    -1,
      -1,    -1,   109,    28,    29,    30,    31,    32,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    58,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      85,    -1,    -1,    -1,    -1,     8,    91,    92,    93,    94,
      13,    14,    -1,    98,    99,   100,   101,   102,   103,   104,
     105,    -1,    -1,   108,    -1,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    58,    59,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    85,    -1,    -1,    -1,    -1,     8,    91,    92,
      93,    94,    13,    14,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,    -1,    -1,   108,    -1,    28,    29,    30,
      31,    32,    -1,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    58,    59,    60,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,     8,
      91,    92,    93,    94,    13,    14,    -1,    98,    99,   100,
     101,   102,   103,   104,   105,    -1,    -1,   108,    -1,    28,
      29,    30,    31,    32,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    56,    -1,    58,
      59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    85,    -1,     5,    -1,
      -1,     8,    91,    92,    93,    94,    13,    14,    -1,    98,
      99,   100,   101,   102,   103,   104,   105,    -1,    -1,   108,
      -1,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,
      -1,    -1,    -1,    -1,    91,    92,    93,    94,    -1,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,     8,
      -1,    -1,    11,    -1,    13,    14,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      29,    30,    31,    32,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    56,    -1,    58,
      59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,
      -1,    90,    91,    92,    93,    94,    -1,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,   105,     8,    -1,    -1,
      -1,    -1,    13,    14,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      31,    32,    -1,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    58,    59,    60,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,    90,
      91,    92,    93,    94,    -1,    -1,    -1,    98,    99,   100,
     101,   102,   103,   104,   105,     8,    -1,    -1,    -1,    -1,
      13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    58,    59,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    85,    -1,    -1,    -1,    -1,     8,    91,    92,
      93,    94,    13,    14,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,    -1,    -1,    -1,    -1,    28,    29,    30,
      31,    32,    -1,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    58,    59,    60,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,     8,
      91,    92,    93,    94,    13,    14,    -1,    98,    99,   100,
     101,   102,   103,   104,   105,    -1,    -1,    -1,    -1,    28,
      29,    30,    31,    32,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    56,    -1,    58,
      59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,
      -1,    -1,    91,    92,    93,    94,    -1,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,   105,    61,    62,    -1,
      -1,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,   105,   106,    -1,    -1,    61,    62,    -1,   112,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,   105,
     106,    -1,    -1,    61,    62,    -1,   112,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   104,   105,   106,    -1,
      -1,    61,    62,    -1,   112,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,    -1,    -1,    61,
      62,    -1,   112,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   104,   105,   106,    -1,    -1,    61,    62,    -1,
     112,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,   105,   106,    -1,    61,    62,   110,   111,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,   105,   106,
      -1,    61,    62,    -1,   111,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,    61,    62,   109,
      -1,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,   105,   106,    61,    62,   109,    -1,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   104,   105,   106,    -1,
     108,    61,    62,    -1,    -1,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,    -1,   108,    61,
      62,    -1,    -1,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   104,   105,   106,    -1,   108,    61,    62,    -1,
      -1,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,   105,   106,    -1,   108,    61,    62,    -1,    -1,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,   105,
     106,    -1,   108,    61,    62,    -1,    -1,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   104,   105,   106,   107,
      61,    62,    -1,    -1,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   104,   105,   106,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   104,   105,   106,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   104,   105,   106
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,   114,   115,   116,   117,    28,    34,    35,    36,
      37,    38,    39,    40,    41,   182,     0,   117,    59,   107,
     108,   118,     4,     6,     9,    12,    14,    49,   119,   120,
     121,   122,   123,   125,   126,   131,   132,   133,   139,   140,
     139,    28,   187,    29,   182,   182,    59,   154,   109,   121,
     108,     5,     7,    14,   108,   118,   107,   107,    10,   108,
     108,     8,    13,    15,    16,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    29,    30,    31,    32,    42,    43,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    84,    85,    91,    92,    93,    94,    98,    99,   100,
     101,   102,   103,   104,   105,   108,   134,   139,   141,   142,
     143,   144,   145,   146,   149,   150,   151,   152,   154,   155,
     159,   161,   162,   163,   164,   165,   166,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     182,    28,   107,   188,    59,   127,   139,   139,   182,   180,
      28,    60,    60,    60,    60,   108,   108,    60,    59,   159,
     107,   108,   154,   182,   184,   185,   108,   159,   180,   108,
     159,   108,   159,   159,   180,   136,   137,   156,   159,   160,
     180,   109,   159,   160,   160,   181,   182,   183,   184,   159,
     159,   159,    59,   159,   180,   180,    92,   159,   180,   180,
     159,   159,   159,   159,     5,   109,   143,    61,    62,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,   104,   105,   106,   108,    58,    59,
      58,    59,   108,   108,   106,    33,   181,   182,   186,   107,
     128,   129,   130,   188,   181,   181,   108,   107,    60,    11,
      60,    90,   124,   158,   159,   167,   158,   157,   159,   158,
     159,   107,   154,   108,    58,    58,   108,   106,   108,   108,
     108,   106,   110,   112,   112,   110,   107,   109,   111,   111,
      58,    87,    58,   159,    59,   159,   106,   107,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   181,   159,   159,   159,   159,
     159,   159,   159,   159,   159,    58,    59,    60,   188,   159,
     187,   159,   187,   188,    60,   186,   109,   110,    61,   108,
     181,   156,   182,   158,   159,   167,   158,   111,    63,    64,
     111,   111,   108,   111,   111,   154,   112,   159,   112,   159,
      59,    59,   137,   180,   139,   159,   181,   159,   109,   159,
      59,   186,   159,   187,   156,    60,   112,   109,   112,   109,
      60,   135,   136,    60,   130,    30,   111,    10,   111,   154,
     158,   158,   154,   154,   158,   154,    59,   147,   112,   112,
     187,   187,     5,   109,   187,    60,   112,   109,   111,   156,
     156,    44,   138,   135,   182,    18,    17,    18,   153,   153,
     108,   148,   149,   109,   109,   107,   109,   135,   111,   111,
     111,   138,   108,   154,    60,   154,   157,   109,   149,   150,
     186,   138,   108,   154,   111,   158,   111,   109,    60,   111,
     108,   154,   111,   154,   135,   154,   154,   138,   153,   111,
     154
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   113,   114,   115,   115,   116,   116,   117,   117,   117,
     117,   118,   119,   119,   120,   120,   121,   121,   121,   121,
     121,   121,   121,   122,   123,   123,   124,   124,   125,   126,
     127,   128,   128,   129,   129,   129,   130,   130,   131,   132,
     133,   133,   133,   133,   134,   134,   135,   135,   136,   136,
     136,   137,   138,   138,   139,   139,   140,   140,   141,   141,
     142,   142,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   144,   145,   146,   147,   147,
     148,   148,   149,   149,   150,   150,   151,   151,   152,   152,
     153,   153,   153,   154,   155,   156,   156,   157,   157,   158,
     158,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   160,   160,   160,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   162,   162,   163,
     163,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   166,   167,   167,   167,   167,
     168,   168,   169,   169,   169,   170,   170,   170,   171,   172,
     172,   172,   173,   173,   173,   173,   173,   173,   173,   174,
     174,   174,   175,   176,   177,   178,   178,   178,   178,   179,
     179,   180,   181,   181,   181,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   183,   184,   184,   185,   185,   186,
     186,   187,   188
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     3,     5,     3,
       5,     3,     0,     1,     2,     1,     1,     1,     1,     2,
       1,     1,     1,     2,     3,     5,     2,     5,     3,     3,
       3,     0,     1,     3,     2,     1,     1,     3,     5,     6,
      10,    10,     9,     9,     9,    12,     0,     1,     3,     2,
       1,     3,     0,     1,     0,     1,     2,     1,     0,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     3,     2,     3,     2,
       3,     3,     2,     2,     1,     9,     5,     5,     3,     4,
       2,     1,     4,     3,     3,     2,     5,     7,     6,     6,
       0,     2,     6,     3,     3,     0,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     3,     2,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     2,     2,     1,     3,     3,     2,     4,     5,
       4,     4,     5,     2,     6,     3,     6,     3,     5,     5,
       4,     4,     6,     6,     6,     2,     4,     3,     5,     4,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     3,     3,     4,     4,     1,
       1,     1,     1
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
#line 66 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_grammar(compiler, (yyvsp[0].opval));
      compiler->op_grammar = (yyval.opval);
    }
#line 2176 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 73 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2184 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 77 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2199 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 90 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2217 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 107 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 2225 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 111 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[0].opval), (yyvsp[-1].opval));
    }
#line 2233 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 115 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), NULL, NULL);
    }
#line 2241 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 119 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), NULL, (yyvsp[-1].opval));
    }
#line 2249 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 125 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_class_block;
    }
#line 2259 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 133 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2267 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 137 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[0].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
        SPVM_OP_insert_child(compiler, (yyval.opval), (yyval.opval)->last, (yyvsp[0].opval));
      }
    }
#line 2281 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 149 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2299 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 175 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2316 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 190 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), NULL, 0);
    }
#line 2324 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 194 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), 0);
    }
#line 2332 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 200 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_use(compiler, op_use, (yyvsp[0].opval), NULL, 1);
    }
#line 2341 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 205 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_use(compiler, op_use, (yyvsp[-3].opval), (yyvsp[-1].opval), 1);
    }
#line 2350 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 212 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_allow(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2358 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 219 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), (yyvsp[-2].opval));
    }
#line 2366 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 225 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_enum_block;
    }
#line 2376 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 233 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2384 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 237 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2399 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 250 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2417 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 268 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[0].opval), NULL);
    }
#line 2425 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 272 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2433 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 278 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_our(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 2441 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 284 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_has(compiler, (yyvsp[-5].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2449 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 290 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t can_precompile = 1;
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-8].opval), (yyvsp[-7].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-9].opval), (yyvsp[0].opval), NULL, (yyvsp[-2].opval), 0, 0, can_precompile);
     }
#line 2458 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 295 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t can_precompile = 0;
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-8].opval), (yyvsp[-7].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-9].opval), NULL, NULL, (yyvsp[-2].opval), 0, 0, can_precompile);
     }
#line 2467 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 300 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t can_precompile = 1;
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), NULL, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-8].opval), (yyvsp[0].opval), NULL, (yyvsp[-2].opval), 0, 0, can_precompile);
     }
#line 2476 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 305 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t can_precompile = 0;
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), NULL, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-8].opval), NULL, NULL, (yyvsp[-2].opval), 0, 0, can_precompile);
     }
#line 2485 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 312 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t is_init = 0;
       int32_t is_anon = 1;
       int32_t can_precompile = 1;
       
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), NULL, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-8].opval), (yyvsp[0].opval), NULL, (yyvsp[-2].opval), is_init, is_anon, can_precompile);
     }
#line 2497 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 320 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2517 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 338 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2525 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 342 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2540 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 355 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2558 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 373 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2566 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 379 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 2574 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 386 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2582 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 390 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2597 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 403 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2615 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 420 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2623 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 424 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2638 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 437 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2656 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 463 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_expression_statement(compiler, (yyvsp[-1].opval));
    }
#line 2664 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 470 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[-1].opval), NULL);
    }
#line 2672 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 474 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2680 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 478 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-1].opval), NULL);
    }
#line 2688 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 482 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2696 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 486 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_warn(compiler, (yyvsp[-1].opval), NULL);
    }
#line 2704 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 490 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_warn(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2712 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 494 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_print(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2720 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 500 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    }
#line 2728 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 506 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[-8].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2736 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 512 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2744 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 518 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2752 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 524 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->cur_file, compiler->cur_line);
      op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[-1].opval), NULL);
    }
#line 2762 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 530 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->cur_file, compiler->cur_line);
      op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2772 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 538 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2790 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 552 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 2798 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 558 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2806 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 562 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), NULL);
    }
#line 2814 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 568 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2822 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 572 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[-1].opval), NULL);
    }
#line 2830 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 578 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->cur_file, compiler->cur_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[-2].opval), (yyvsp[0].opval), NULL);
    }
#line 2840 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 584 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->cur_file, compiler->cur_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2850 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 591 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    }
#line 2865 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 602 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    }
#line 2880 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 615 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    }
#line 2888 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 619 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 2896 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 623 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 2904 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 629 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_block;
    }
#line 2914 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 637 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2922 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 643 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2930 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 647 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2945 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 660 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    }
#line 2953 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 688 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2973 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 708 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_true(compiler, (yyvsp[0].opval));
    }
#line 2981 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 712 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_false(compiler, (yyvsp[0].opval));
    }
#line 2989 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 718 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3007 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 732 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[-1].opval);
    }
#line 3015 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 736 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 3023 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 742 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, op, (yyvsp[0].opval));
    }
#line 3032 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 747 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MINUS, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, op_negate, (yyvsp[0].opval));
    }
#line 3041 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 752 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3049 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 756 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3057 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 760 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3065 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 764 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3073 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 768 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3081 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 772 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3089 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 776 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3097 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 782 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, op, (yyvsp[0].opval));
    }
#line 3106 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 787 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, op, (yyvsp[-1].opval));
    }
#line 3115 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 794 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, op, (yyvsp[0].opval));
    }
#line 3124 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 799 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, op, (yyvsp[-1].opval));
    }
#line 3133 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 806 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3142 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 811 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3151 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 816 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MULTIPLY, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3160 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 821 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3168 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 825 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3176 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 829 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3184 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 833 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3192 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 837 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3200 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 841 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3208 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 845 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3216 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 851 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3224 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 855 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3232 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 859 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3240 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 863 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3248 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 867 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3256 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 871 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3264 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 875 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3272 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 879 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3280 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 883 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3288 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 887 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3296 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 891 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3304 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 895 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3312 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 899 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3320 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 903 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3328 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 909 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3336 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 916 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_or(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3344 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 920 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_and(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3352 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 924 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_not(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3360 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 928 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[-1].opval);
    }
#line 3368 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 934 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3376 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 938 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_special_assign(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3384 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 944 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 3392 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 948 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 3400 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 952 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3428 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 978 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      int32_t is_key_values = 0;
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[-1].opval), is_key_values);
    }
#line 3438 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 984 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      int32_t is_key_values = 1;
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[-1].opval), is_key_values);
    }
#line 3448 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 990 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      int32_t is_key_values = 1;
      SPVM_OP* op_list_elements = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, op_list_elements, is_key_values);
    }
#line 3459 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 999 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      (yyval.opval) = SPVM_OP_build_convert(compiler, op_convert, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3468 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1006 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 3476 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1010 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3484 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1014 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3492 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1020 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3500 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1024 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_expressions = SPVM_OP_new_op_list(compiler, (yyvsp[-1].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), op_expressions);
    }
#line 3509 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1029 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3517 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1033 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_expressions = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-2].opval), (yyvsp[0].opval), op_expressions);
    }
#line 3526 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1038 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3534 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1042 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_expressions = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-2].opval), (yyvsp[0].opval), op_expressions);
    }
#line 3543 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1047 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_method_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[-3].opval)->file, (yyvsp[-3].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-4].opval), op_method_name, (yyvsp[-1].opval));
    }
#line 3552 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1053 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 3560 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1057 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3568 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1061 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3576 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1067 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 3585 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1074 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_unweaken_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 3594 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1081 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_isweak_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 3603 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1088 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[0].opval));
    }
#line 3612 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1093 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[-1].opval));
    }
#line 3621 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1098 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[0].opval));
    }
#line 3630 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1103 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[-1].opval));
    }
#line 3639 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1110 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3647 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1114 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 3655 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1120 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[0].opval));
    }
#line 3663 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1131 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[0].opval));
    }
#line 3671 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1135 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_byte_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3681 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1141 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_short_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3691 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1147 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3701 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1153 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_long_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3711 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1159 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_float_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3721 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1165 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_double_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3731 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1171 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_any_object_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3741 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1177 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_string_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3751 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1185 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[-1].opval));
    }
#line 3759 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1191 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-2].opval), NULL);
    }
#line 3767 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1195 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-2].opval), NULL);
    }
#line 3775 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1201 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3783 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1205 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3791 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1212 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 3799 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;


#line 3803 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 1222 "yacc/spvm_yacc.y" /* yacc.c:1906  */

