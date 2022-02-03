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
#define YYLAST   3172

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  113
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  76
/* YYNRULES -- Number of rules.  */
#define YYNRULES  232
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  463

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

#define YYPACT_NINF -374

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-374)))

#define YYTABLE_NINF -138

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-138)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      36,   150,    42,  -374,    36,  -374,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,   -29,  -374,  -374,    58,    35,
    -374,  -374,    26,    37,   150,   150,  -374,    -1,   -19,    59,
    -374,  -374,  -374,  -374,  -374,     3,  -374,  -374,    17,    85,
     -25,  -374,     6,     8,     4,    23,  1044,  -374,  -374,  -374,
    -374,   -10,    73,  -374,  -374,  -374,    35,    35,   150,  -374,
    -374,   108,   113,    82,    86,   101,   102,    55,    56,   105,
    2026,    38,    64,    -1,  -374,  -374,  -374,  -374,  -374,  -374,
     150,  1404,   108,  1486,  1568,  2026,  -374,   108,   546,  1142,
    2026,  2026,  2026,  2026,  2108,   108,   108,    74,  2026,   108,
     108,  2026,  2026,  2026,  2026,  -374,  -374,   168,    70,  1240,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    2661,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,   -22,  -374,    47,    72,    87,  -374,  -374,  -374,  -374,
      75,  -374,   171,    89,   165,  -374,   150,   150,    94,    96,
     134,  1830,  1928,  1650,  1928,  -374,  -374,  2026,  1322,  2901,
      -1,  -374,   106,   155,   157,  -374,  -374,  2709,   112,  -374,
    2757,  -374,  2805,  2853,   114,   -81,  -374,   107,  2948,   116,
     110,  -374,  2661,    14,    10,   117,   -30,  -374,   163,    -2,
      -2,    -2,  1322,    -2,  -374,  -374,  2190,    -2,   118,  -374,
      -2,    -2,    12,    12,   115,  -374,  -374,  2026,  2026,  2026,
    2026,  2026,  2026,  2026,  2026,  2026,  2026,  2026,  2026,  2026,
    2026,  2026,  2026,  2026,   150,  2026,  2026,  2026,  2026,  2026,
    2026,  2026,  2026,  2026,  -374,  -374,    91,  -374,  2026,    26,
    2026,    26,  -374,  -374,   165,  -374,  -374,   -35,   169,   171,
     121,   122,  -374,   162,   123,  -374,  -374,    35,   846,   150,
    1928,  1928,   124,   -13,  2948,  -374,    11,   125,  2948,    25,
    2522,    -1,  -374,  -374,   646,   746,  -374,   175,  -374,  -374,
    -374,   177,   108,    35,  -374,  1732,    35,  -374,  -374,  2026,
     126,  -374,   127,  2569,  1322,    -2,   178,   171,  2948,  2948,
    2988,  2988,  3027,  3066,  3066,  3066,  3066,   296,   296,   296,
     296,   296,   296,   296,   296,  -374,   296,   296,    71,    65,
      65,    65,    -2,    -2,    -2,  2026,    26,   846,   180,  2235,
     132,  2283,   133,   183,   108,   185,  -374,   165,   216,  -374,
     150,   136,   239,    63,  2475,   140,  -374,    -1,  1928,  1928,
      -1,    -1,  1928,    -1,   193,  -374,  -374,  2331,  -374,  2379,
      26,    26,  -374,   110,   248,  2948,   150,    -2,  -374,  2615,
      26,   195,  2427,   147,   146,   846,  -374,  -374,  -374,  -374,
     846,   214,   149,   108,  -374,  -374,  -374,  -374,   150,  -374,
     244,   199,  -374,   111,   111,    31,  -374,   240,  -374,  -374,
    -374,   156,   158,   159,  -374,  -374,   160,   108,  -374,  -374,
    -374,   161,   164,  -374,   167,   214,   173,    -1,   208,    -1,
    -374,  -374,   945,    -8,  -374,  -374,  -374,   171,  -374,   214,
    -374,  -374,   -24,   172,  -374,  -374,  1928,  -374,   176,  -374,
    -374,   179,   210,   182,  -374,  -374,   -21,    29,    -1,  -374,
     108,    -1,  -374,  -374,    -1,  -374,   214,  -374,   111,   184,
    -374,    -1,  -374
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
       0,    32,    35,    36,     0,    38,    25,    54,    54,     0,
      54,    54,     0,     0,   109,   110,     0,     0,   108,     0,
       0,    93,    94,   104,    54,    54,    76,     0,    78,    80,
      81,     0,    49,    54,   185,   136,    54,   186,   128,    54,
       0,   224,     0,   137,    54,   207,     0,     0,   180,   181,
     158,   156,   157,   161,   162,   168,   169,   163,   164,   165,
     166,   170,   171,   172,   173,   175,   167,   174,   159,   151,
     152,   160,   153,   154,   155,    54,     0,    54,   197,     0,
       0,     0,     0,   195,    46,     0,    30,    34,     0,    39,
       0,     0,    26,     0,   109,   110,   178,     0,    54,    54,
       0,     0,    54,     0,     0,    92,   225,     0,   226,     0,
       0,     0,    48,     0,     0,   135,     0,   188,   206,   137,
       0,     0,     0,     0,     0,    54,   190,   201,   191,   200,
      54,    52,    47,    46,    33,    37,   209,   192,     0,   179,
      96,   176,   177,   100,   100,     0,    86,     0,    87,   227,
     228,     0,     0,     0,    51,   208,     0,    46,   189,   199,
     198,     0,     0,    53,     0,    52,     0,     0,     0,     0,
      98,    99,    54,     0,    91,   202,   203,     0,   204,    52,
     196,   194,     0,     0,    27,    97,    54,   101,     0,    88,
      90,     0,     0,     0,    43,    42,     0,     0,     0,    89,
      46,     0,    41,    40,     0,    85,    52,    44,   100,     0,
     102,     0,    45
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -374,  -374,  -374,  -374,   267,   233,  -374,  -374,   247,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,   -53,  -374,  -374,
    -374,  -374,  -364,   194,     7,  -360,    -9,  -374,  -374,  -374,
     181,  -374,  -374,  -374,  -374,  -374,  -341,  -137,  -374,  -374,
    -373,   -27,  -374,  -250,  -131,  -151,   246,   -78,  -374,  -374,
    -374,  -374,  -374,  -374,    34,  -374,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,   -55,   -86,     1,
    -374,   217,  -374,  -244,  -226,   -44
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    21,    28,    29,    30,    31,
      32,   262,    33,    34,   145,   250,   251,   252,    35,    36,
      37,   106,   381,   382,   176,   414,   107,    39,   108,   109,
     110,   111,   112,   113,   398,   423,   114,   115,   116,   117,
     420,   118,   119,   177,   267,   263,   264,   179,   121,   122,
     123,   124,   125,   126,   265,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   246,   140,
     187,   188,   165,   248,    42,   253
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      47,   266,    15,   269,   185,   335,   149,   143,   341,    38,
      40,   183,   184,   330,    58,   332,    70,    71,   141,   415,
      38,   421,    51,   290,    52,    44,    45,   168,   290,   282,
      18,   283,   174,   180,    18,    46,   238,   239,    46,     1,
     194,   195,    16,   429,   198,   199,   162,   146,   147,    26,
     348,   349,   291,   371,    41,   433,   424,   291,    46,   148,
     254,   255,    22,    22,    23,    23,    43,    24,    24,   443,
      25,    25,    26,    26,   348,   349,   244,   374,    19,    20,
     183,   163,   440,    54,   444,   460,   456,   452,   348,   349,
      48,   186,   348,   349,   348,   349,   459,   142,   350,    53,
     373,   439,   234,   235,   236,   240,   241,    27,    27,   343,
     346,    50,    59,    56,   183,    57,  -138,  -138,   236,   141,
     285,   288,   351,   287,   285,   411,   348,   349,   418,   419,
     412,    60,   144,   272,   401,   402,   353,    74,   315,   422,
     454,   150,   151,   247,   406,   160,   152,   247,   247,   325,
     326,   327,   231,   232,   233,   228,   229,   230,   231,   232,
     233,   153,   154,   155,   156,   157,   196,   -12,   -13,   234,
     235,   236,   161,   204,   185,   234,   235,   236,     6,   205,
     242,   244,   184,   442,     7,     8,     9,    10,    11,    12,
      13,    14,   328,   141,   258,   243,   249,   391,   392,     6,
     333,   395,   256,   257,   245,     7,     8,     9,    10,    11,
      12,    13,    14,   274,   273,   275,   183,   286,   277,   284,
     281,   292,   297,   338,   296,   247,   285,   363,   289,   334,
     336,   339,   337,   352,   360,   347,   361,   370,   356,   358,
     375,   377,   379,   380,   355,   383,   385,   387,   340,   388,
     247,   389,   397,   403,   386,   407,   409,   410,   413,   282,
     342,   186,   417,   349,    70,   425,   427,   426,   436,   428,
     450,    17,   430,    55,   364,   431,    49,   366,   432,   363,
     404,   434,   175,   446,   384,   447,   441,   448,   449,   362,
     206,   438,   120,   451,   345,   461,     0,   164,   247,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   159,     0,     0,     0,
     390,     0,     0,   393,   394,     0,   396,   167,   363,   170,
     172,   173,     0,     0,   178,   182,   178,   189,   190,   191,
     193,   247,     0,     0,   197,     0,     0,   200,   201,   202,
     203,     0,   363,     0,     0,   120,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   247,  -138,  -138,
    -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,   227,
     228,   229,   230,   231,   232,   233,     0,     0,     0,   416,
     435,     0,   437,     0,     0,   363,     0,     0,     0,   268,
     234,   235,   236,   270,   178,   445,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   453,
       0,   455,     0,     0,   457,     0,     0,   458,   247,     0,
       0,     0,     0,     0,   462,     0,     0,     0,   293,     0,
       0,     0,   295,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
       0,   316,   317,   318,   319,   320,   321,   322,   323,   324,
       0,     0,     0,     0,   329,     0,   331,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   178,     0,   344,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     357,   359,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   365,     0,     0,     0,   367,     0,     0,     0,     0,
     369,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,     0,     0,     0,     0,    62,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   372,     0,   178,     6,    74,    75,    76,    77,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    78,    79,
       0,     0,     0,     0,     0,     0,    80,     0,     0,     0,
       0,     0,    86,     0,    88,   158,    90,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   178,     0,     0,     0,     0,   178,     0,     0,     0,
      91,    92,     0,     0,     0,     0,     0,    93,    94,    95,
      96,     0,     0,     0,    97,    98,    99,   100,   101,   102,
     103,   104,     0,     0,    61,     0,     0,     0,  -105,    62,
      26,     0,     0,     0,     0,     0,     0,     0,   268,     0,
       0,     0,     0,     0,     6,    74,    75,    76,    77,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    78,    79,
       0,     0,     0,     0,     0,     0,    80,     0,     0,     0,
       0,     0,    86,     0,    88,   158,    90,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      91,    92,     0,     0,     0,     0,     0,    93,    94,    95,
      96,     0,     0,     0,    97,    98,    99,   100,   101,   102,
     103,   104,     0,     0,    61,     0,     0,     0,   356,    62,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,    74,    75,    76,    77,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    78,    79,
       0,     0,     0,     0,     0,     0,    80,     0,     0,     0,
       0,     0,    86,     0,    88,   158,    90,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      91,    92,     0,     0,     0,     0,     0,    93,    94,    95,
      96,     0,     0,     0,    97,    98,    99,   100,   101,   102,
     103,   104,     0,     0,    61,     0,     0,     0,   358,    62,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,    74,    75,    76,    77,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    78,    79,
       0,     0,     0,     0,     0,     0,    80,     0,     0,     0,
       0,     0,    86,     0,    88,   158,    90,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      91,    92,     0,     0,     0,     0,     0,    93,    94,    95,
      96,     0,     0,     0,    97,    98,    99,   100,   101,   102,
     103,   104,     0,    61,     0,     0,     0,  -105,    62,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,    74,    75,    76,    77,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    78,    79,     0,
       0,     0,     0,     0,     0,    80,     0,     0,     0,     0,
       0,    86,     0,    88,   158,    90,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    91,
      92,     0,     0,     0,     0,     0,    93,    94,    95,    96,
       0,     0,     0,    97,    98,    99,   100,   101,   102,   103,
     104,     0,    61,     0,     0,     0,  -107,    62,    26,    63,
      64,     0,     0,    65,    66,    67,    68,    69,    70,    71,
      72,    73,     6,    74,    75,    76,    77,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    78,    79,     0,     0,
       0,     0,     0,     0,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    91,    92,
       0,     0,     0,     0,     0,    93,    94,    95,    96,     0,
       0,     0,    97,    98,    99,   100,   101,   102,   103,   104,
      61,     0,   105,   -58,     0,    62,    26,    63,    64,     0,
       0,    65,    66,    67,    68,    69,    70,    71,    72,    73,
       6,    74,    75,    76,    77,     0,     7,     8,     9,    10,
      11,    12,    13,    14,    78,    79,     0,     0,     0,     0,
       0,     0,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,     0,    93,    94,    95,    96,     0,     0,     0,
      97,    98,    99,   100,   101,   102,   103,   104,    61,     0,
     105,   181,     0,    62,    26,    63,    64,     0,     0,    65,
      66,    67,    68,    69,    70,    71,    72,    73,     6,    74,
      75,    76,    77,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    78,    79,     0,     0,     0,     0,     0,     0,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    91,    92,     0,     0,     0,     0,
      61,    93,    94,    95,    96,    62,    26,     0,    97,    98,
      99,   100,   101,   102,   103,   104,     0,     0,   105,   -59,
       6,    74,    75,    76,    77,     0,     7,     8,     9,    10,
      11,    12,    13,    14,    78,    79,     0,     0,     0,     0,
       0,     0,    80,     0,     0,     0,     0,     0,    86,     0,
      88,   158,    90,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,    61,    93,    94,    95,    96,    62,    26,     0,
      97,    98,    99,   100,   101,   102,   103,   104,     0,     0,
       0,   181,     6,    74,    75,    76,    77,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    78,    79,     0,     0,
       0,     0,     0,     0,    80,     0,     0,     0,     0,     0,
      86,     0,    88,   158,    90,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    91,    92,
       0,     0,     0,     0,    61,    93,    94,    95,    96,    62,
      26,     0,    97,    98,    99,   100,   101,   102,   103,   104,
       0,     0,   166,     0,     6,    74,    75,    76,    77,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    78,    79,
       0,     0,     0,     0,     0,     0,    80,     0,     0,     0,
       0,     0,    86,     0,    88,   158,    90,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      91,    92,     0,     0,     0,     0,    61,    93,    94,    95,
      96,    62,    26,     0,    97,    98,    99,   100,   101,   102,
     103,   104,     0,     0,   169,     0,     6,    74,    75,    76,
      77,     0,     7,     8,     9,    10,    11,    12,    13,    14,
      78,    79,     0,     0,     0,     0,     0,     0,    80,     0,
       0,     0,     0,     0,    86,     0,    88,   158,    90,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    91,    92,     0,     0,     0,     0,    61,    93,
      94,    95,    96,    62,    26,     0,    97,    98,    99,   100,
     101,   102,   103,   104,     0,     0,   171,     0,     6,    74,
      75,    76,    77,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    78,    79,     0,     0,     0,     0,     0,     0,
      80,     0,     0,     0,     0,     0,    86,     0,    88,   158,
      90,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    91,    92,     0,   -54,     0,     0,
      61,    93,    94,    95,    96,    62,    26,     0,    97,    98,
      99,   100,   101,   102,   103,   104,     0,     0,  -107,     0,
       6,    74,    75,    76,    77,     0,     7,     8,     9,    10,
      11,    12,    13,    14,    78,    79,     0,     0,     0,     0,
       0,     0,    80,     0,     0,     0,     0,     0,    86,     0,
      88,   158,    90,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,     0,    93,    94,    95,    96,     0,     0,     0,
      97,    98,    99,   100,   101,   102,   103,   104,    61,     0,
       0,   259,     0,    62,    26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     6,    74,
      75,    76,    77,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    78,    79,     0,     0,     0,     0,     0,     0,
      80,     0,     0,     0,     0,     0,    86,     0,    88,   158,
     260,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    91,    92,     0,     0,     0,     0,
     261,    93,    94,    95,    96,     0,     0,     0,    97,    98,
      99,   100,   101,   102,   103,   104,    61,     0,     0,     0,
       0,    62,    26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,    74,    75,    76,
      77,     0,     7,     8,     9,    10,    11,    12,    13,    14,
      78,    79,     0,     0,     0,     0,     0,     0,    80,     0,
       0,     0,     0,     0,    86,     0,    88,   158,   260,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    91,    92,     0,     0,     0,     0,   261,    93,
      94,    95,    96,     0,     0,     0,    97,    98,    99,   100,
     101,   102,   103,   104,    61,     0,     0,     0,     0,    62,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,    74,    75,    76,    77,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    78,    79,
       0,     0,     0,     0,     0,     0,    80,     0,     0,     0,
       0,     0,    86,     0,    88,   158,    90,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      91,    92,     0,     0,     0,     0,    61,    93,    94,    95,
      96,    62,    26,     0,    97,    98,    99,   100,   101,   102,
     103,   104,     0,     0,     0,     0,     6,    74,    75,    76,
      77,     0,     7,     8,     9,    10,    11,    12,    13,    14,
      78,    79,     0,     0,     0,     0,     0,     0,    80,     0,
       0,     0,     0,     0,    86,     0,    88,   192,    90,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    91,    92,     0,     0,     0,     0,    61,    93,
      94,    95,    96,    62,    26,     0,    97,    98,    99,   100,
     101,   102,   103,   104,     0,     0,     0,     0,     6,    74,
      75,    76,    77,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    78,    79,     0,     0,     0,     0,     0,     0,
      80,     0,     0,     0,     0,     0,    86,     0,    88,   294,
      90,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    91,    92,     0,     0,     0,     0,
       0,    93,    94,    95,    96,     0,     0,     0,    97,    98,
      99,   100,   101,   102,   103,   104,   207,   208,     0,     0,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   234,
     235,   236,     0,     0,   207,   208,     0,   376,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   234,   235,   236,
       0,     0,   207,   208,     0,   378,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   234,   235,   236,     0,     0,
     207,   208,     0,   399,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   234,   235,   236,     0,     0,   207,   208,
       0,   400,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   234,   235,   236,     0,     0,   207,   208,     0,   408,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   234,
     235,   236,     0,   207,   208,  -137,  -137,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   234,   235,   236,     0,
     207,   208,     0,   354,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   234,   235,   236,   207,   208,   368,     0,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   234,
     235,   236,   207,   208,   405,     0,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   234,   235,   236,     0,   237,
     207,   208,     0,     0,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   234,   235,   236,     0,   276,   207,   208,
       0,     0,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   234,   235,   236,     0,   278,   207,   208,     0,     0,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   234,
     235,   236,     0,   279,   207,   208,     0,     0,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   234,   235,   236,
       0,   280,   207,   208,     0,     0,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   234,   235,   236,   271,   207,
     208,     0,     0,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   234,   235,   236,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   234,   235,   236,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   234,   235,   236,  -138,  -138,  -138,  -138,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     234,   235,   236
};

static const yytype_int16 yycheck[] =
{
      27,   152,     1,   154,    90,   249,    61,    51,   258,    18,
      19,    89,    90,   239,    10,   241,    24,    25,    28,   383,
      29,   394,     5,    58,     7,    24,    25,    82,    58,   110,
      59,   112,    87,    88,    59,    59,    58,    59,    59,     3,
      95,    96,     0,   407,    99,   100,    73,    56,    57,    14,
      63,    64,    87,   297,    28,   415,   397,    87,    59,    58,
     146,   147,     4,     4,     6,     6,    29,     9,     9,   429,
      12,    12,    14,    14,    63,    64,   106,   327,   107,   108,
     158,    80,   423,   108,   108,   458,   450,   108,    63,    64,
     109,    90,    63,    64,    63,    64,   456,   107,   111,    14,
     326,   109,   104,   105,   106,    58,    59,    49,    49,   260,
     261,   108,   108,   107,   192,   107,   104,   105,   106,    28,
     110,   111,   111,   109,   110,   375,    63,    64,    17,    18,
     380,   108,    59,   160,   360,   361,   111,    29,   224,   108,
     111,    28,    60,   142,   370,   107,    60,   146,   147,    58,
      59,    60,    87,    88,    89,    84,    85,    86,    87,    88,
      89,    60,    60,   108,   108,    60,    92,   109,   109,   104,
     105,   106,   108,     5,   260,   104,   105,   106,    28,   109,
     108,   106,   260,   427,    34,    35,    36,    37,    38,    39,
      40,    41,   236,    28,    60,   108,   107,   348,   349,    28,
     244,   352,   108,   107,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    58,   108,    58,   294,   107,   106,   112,
     106,    58,   107,    61,   106,   224,   110,   282,   111,    60,
     109,   108,   110,   108,    59,   111,    59,    59,   112,   112,
      60,   109,   109,    60,   271,    60,    30,   111,   257,    10,
     249,   111,    59,     5,   340,    60,   109,   111,    44,   110,
     259,   260,    18,    64,    24,   109,   107,   109,    60,   109,
      60,     4,   111,    40,   283,   111,    29,   286,   111,   334,
     366,   108,    88,   111,   337,   436,   423,   111,   109,   282,
     109,   422,    46,   111,   260,   111,    -1,    80,   297,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,
     347,    -1,    -1,   350,   351,    -1,   353,    81,   383,    83,
      84,    85,    -1,    -1,    88,    89,    90,    91,    92,    93,
      94,   340,    -1,    -1,    98,    -1,    -1,   101,   102,   103,
     104,    -1,   407,    -1,    -1,   109,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   366,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    -1,    -1,   388,
     417,    -1,   419,    -1,    -1,   450,    -1,    -1,    -1,   153,
     104,   105,   106,   157,   158,   432,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   446,
      -1,   448,    -1,    -1,   451,    -1,    -1,   454,   427,    -1,
      -1,    -1,    -1,    -1,   461,    -1,    -1,    -1,   192,    -1,
      -1,    -1,   196,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
      -1,   225,   226,   227,   228,   229,   230,   231,   232,   233,
      -1,    -1,    -1,    -1,   238,    -1,   240,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   258,    -1,   260,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     274,   275,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   285,    -1,    -1,    -1,   289,    -1,    -1,    -1,    -1,
     294,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,    13,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   325,    -1,   327,    28,    29,    30,    31,    32,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    58,    59,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   375,    -1,    -1,    -1,    -1,   380,    -1,    -1,    -1,
      84,    85,    -1,    -1,    -1,    -1,    -1,    91,    92,    93,
      94,    -1,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,   105,    -1,    -1,     8,    -1,    -1,    -1,   112,    13,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   422,    -1,
      -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    58,    59,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    -1,    -1,    -1,    -1,    91,    92,    93,
      94,    -1,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,   105,    -1,    -1,     8,    -1,    -1,    -1,   112,    13,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    58,    59,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    -1,    -1,    -1,    -1,    91,    92,    93,
      94,    -1,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,   105,    -1,    -1,     8,    -1,    -1,    -1,   112,    13,
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
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    58,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      85,    -1,    -1,    -1,    -1,    -1,    91,    92,    93,    94,
      -1,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
     105,    -1,     8,    -1,    -1,    -1,   111,    13,    14,    15,
      16,    -1,    -1,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      -1,    -1,    -1,    -1,    -1,    91,    92,    93,    94,    -1,
      -1,    -1,    98,    99,   100,   101,   102,   103,   104,   105,
       8,    -1,   108,   109,    -1,    13,    14,    15,    16,    -1,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,
      -1,    -1,    -1,    91,    92,    93,    94,    -1,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,     8,    -1,
     108,   109,    -1,    13,    14,    15,    16,    -1,    -1,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,
       8,    91,    92,    93,    94,    13,    14,    -1,    98,    99,
     100,   101,   102,   103,   104,   105,    -1,    -1,   108,   109,
      28,    29,    30,    31,    32,    -1,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    56,    -1,
      58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,
      -1,    -1,     8,    91,    92,    93,    94,    13,    14,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,    -1,    -1,
      -1,   109,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      -1,    -1,    -1,    -1,     8,    91,    92,    93,    94,    13,
      14,    -1,    98,    99,   100,   101,   102,   103,   104,   105,
      -1,    -1,   108,    -1,    28,    29,    30,    31,    32,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    58,    59,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    -1,    -1,    -1,     8,    91,    92,    93,
      94,    13,    14,    -1,    98,    99,   100,   101,   102,   103,
     104,   105,    -1,    -1,   108,    -1,    28,    29,    30,    31,
      32,    -1,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    58,    59,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    -1,    -1,     8,    91,
      92,    93,    94,    13,    14,    -1,    98,    99,   100,   101,
     102,   103,   104,   105,    -1,    -1,   108,    -1,    28,    29,
      30,    31,    32,    -1,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    56,    -1,    58,    59,
      60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,     5,    -1,    -1,
       8,    91,    92,    93,    94,    13,    14,    -1,    98,    99,
     100,   101,   102,   103,   104,   105,    -1,    -1,   108,    -1,
      28,    29,    30,    31,    32,    -1,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    56,    -1,
      58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,
      -1,    -1,    -1,    91,    92,    93,    94,    -1,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,     8,    -1,
      -1,    11,    -1,    13,    14,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,
      30,    31,    32,    -1,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    56,    -1,    58,    59,
      60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,
      90,    91,    92,    93,    94,    -1,    -1,    -1,    98,    99,
     100,   101,   102,   103,   104,   105,     8,    -1,    -1,    -1,
      -1,    13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,    31,
      32,    -1,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    58,    59,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    -1,    -1,    90,    91,
      92,    93,    94,    -1,    -1,    -1,    98,    99,   100,   101,
     102,   103,   104,   105,     8,    -1,    -1,    -1,    -1,    13,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    58,    59,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    -1,    -1,    -1,     8,    91,    92,    93,
      94,    13,    14,    -1,    98,    99,   100,   101,   102,   103,
     104,   105,    -1,    -1,    -1,    -1,    28,    29,    30,    31,
      32,    -1,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    58,    59,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    -1,    -1,     8,    91,
      92,    93,    94,    13,    14,    -1,    98,    99,   100,   101,
     102,   103,   104,   105,    -1,    -1,    -1,    -1,    28,    29,
      30,    31,    32,    -1,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    56,    -1,    58,    59,
      60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,
      -1,    91,    92,    93,    94,    -1,    -1,    -1,    98,    99,
     100,   101,   102,   103,   104,   105,    61,    62,    -1,    -1,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,
     105,   106,    -1,    -1,    61,    62,    -1,   112,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,   105,   106,
      -1,    -1,    61,    62,    -1,   112,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   104,   105,   106,    -1,    -1,
      61,    62,    -1,   112,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   104,   105,   106,    -1,    -1,    61,    62,
      -1,   112,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,   105,   106,    -1,    -1,    61,    62,    -1,   112,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,
     105,   106,    -1,    61,    62,   110,   111,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   104,   105,   106,    -1,
      61,    62,    -1,   111,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   104,   105,   106,    61,    62,   109,    -1,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,
     105,   106,    61,    62,   109,    -1,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   104,   105,   106,    -1,   108,
      61,    62,    -1,    -1,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   104,   105,   106,    -1,   108,    61,    62,
      -1,    -1,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,   105,   106,    -1,   108,    61,    62,    -1,    -1,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,
     105,   106,    -1,   108,    61,    62,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,   105,   106,
      -1,   108,    61,    62,    -1,    -1,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   104,   105,   106,   107,    61,
      62,    -1,    -1,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   104,   105,   106,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   104,   105,   106,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,   105,   106,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,   105,   106
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
     139,   156,   182,   158,   159,   167,   158,   111,    63,    64,
     111,   111,   108,   111,   111,   154,   112,   159,   112,   159,
      59,    59,   137,   180,   139,   159,   139,   159,   109,   159,
      59,   186,   159,   187,   156,    60,   112,   109,   112,   109,
      60,   135,   136,    60,   130,    30,   181,   111,    10,   111,
     154,   158,   158,   154,   154,   158,   154,    59,   147,   112,
     112,   187,   187,     5,   181,   109,   187,    60,   112,   109,
     111,   156,   156,    44,   138,   135,   182,    18,    17,    18,
     153,   153,   108,   148,   149,   109,   109,   107,   109,   135,
     111,   111,   111,   138,   108,   154,    60,   154,   157,   109,
     149,   150,   186,   138,   108,   154,   111,   158,   111,   109,
      60,   111,   108,   154,   111,   154,   135,   154,   154,   138,
     153,   111,   154
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
       1,     4,     0,     1,     0,     1,     2,     1,     0,     1,
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
       4,     4,     6,     6,     6,     2,     4,     3,     5,     5,
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
#line 2212 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 73 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2220 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2235 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2253 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 107 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 2261 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 111 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[0].opval), (yyvsp[-1].opval));
    }
#line 2269 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 115 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), NULL, NULL);
    }
#line 2277 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 119 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), NULL, (yyvsp[-1].opval));
    }
#line 2285 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 125 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_class_block;
    }
#line 2295 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 133 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2303 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2317 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2335 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2352 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 190 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), NULL, 0);
    }
#line 2360 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 194 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), 0);
    }
#line 2368 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 200 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_use(compiler, op_use, (yyvsp[0].opval), NULL, 1);
    }
#line 2377 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 205 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_use(compiler, op_use, (yyvsp[-3].opval), (yyvsp[-1].opval), 1);
    }
#line 2386 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 212 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_allow(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2394 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 219 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), (yyvsp[-2].opval));
    }
#line 2402 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 225 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_enum_block;
    }
#line 2412 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 233 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2420 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2435 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2453 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 268 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[0].opval), NULL);
    }
#line 2461 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 272 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2469 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 278 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_our(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 2477 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 284 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_has(compiler, (yyvsp[-5].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2485 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 290 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t can_precompile = 1;
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-8].opval), (yyvsp[-7].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-9].opval), (yyvsp[0].opval), NULL, (yyvsp[-2].opval), 0, 0, can_precompile);
     }
#line 2494 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 295 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t can_precompile = 0;
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-8].opval), (yyvsp[-7].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-9].opval), NULL, NULL, (yyvsp[-2].opval), 0, 0, can_precompile);
     }
#line 2503 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 300 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t can_precompile = 1;
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), NULL, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-8].opval), (yyvsp[0].opval), NULL, (yyvsp[-2].opval), 0, 0, can_precompile);
     }
#line 2512 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 305 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t can_precompile = 0;
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), NULL, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-8].opval), NULL, NULL, (yyvsp[-2].opval), 0, 0, can_precompile);
     }
#line 2521 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 312 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t is_init = 0;
       int32_t is_anon = 1;
       int32_t can_precompile = 1;
       
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), NULL, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-8].opval), (yyvsp[0].opval), NULL, (yyvsp[-2].opval), is_init, is_anon, can_precompile);
     }
#line 2533 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2553 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 338 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2561 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2576 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2594 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 373 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[-3].opval), (yyvsp[0].opval), (yyvsp[-1].opval));
    }
#line 2602 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 379 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 2610 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 386 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2618 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2633 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2651 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 420 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2659 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2674 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2692 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 463 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_expression_statement(compiler, (yyvsp[-1].opval));
    }
#line 2700 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 470 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[-1].opval), NULL);
    }
#line 2708 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 474 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2716 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 478 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-1].opval), NULL);
    }
#line 2724 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 482 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2732 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 486 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_warn(compiler, (yyvsp[-1].opval), NULL);
    }
#line 2740 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 490 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_warn(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2748 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 494 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_print(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2756 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 500 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    }
#line 2764 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 506 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[-8].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2772 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 512 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2780 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 518 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2788 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 524 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->cur_file, compiler->cur_line);
      op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[-1].opval), NULL);
    }
#line 2798 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 530 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->cur_file, compiler->cur_line);
      op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2808 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2826 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 552 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 2834 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 558 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2842 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 562 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), NULL);
    }
#line 2850 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 568 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2858 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 572 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[-1].opval), NULL);
    }
#line 2866 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 578 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->cur_file, compiler->cur_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[-2].opval), (yyvsp[0].opval), NULL);
    }
#line 2876 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 584 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->cur_file, compiler->cur_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2886 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2901 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2916 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 615 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    }
#line 2924 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 619 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 2932 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 623 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 2940 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 629 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_block;
    }
#line 2950 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 637 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2958 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 643 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2966 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2981 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 660 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    }
#line 2989 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 3009 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 708 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_true(compiler, (yyvsp[0].opval));
    }
#line 3017 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 712 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_false(compiler, (yyvsp[0].opval));
    }
#line 3025 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 3043 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 732 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[-1].opval);
    }
#line 3051 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 736 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 3059 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 742 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, op, (yyvsp[0].opval));
    }
#line 3068 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 747 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MINUS, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, op_negate, (yyvsp[0].opval));
    }
#line 3077 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 752 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3085 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 756 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3093 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 760 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3101 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 764 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3109 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 768 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3117 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 772 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3125 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 776 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3133 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 782 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, op, (yyvsp[0].opval));
    }
#line 3142 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 787 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, op, (yyvsp[-1].opval));
    }
#line 3151 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 794 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, op, (yyvsp[0].opval));
    }
#line 3160 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 799 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, op, (yyvsp[-1].opval));
    }
#line 3169 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 806 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3178 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 811 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3187 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 816 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MULTIPLY, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3196 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 821 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3204 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 825 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3212 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 829 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3220 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 833 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3228 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 837 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3236 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 841 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3244 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 845 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3252 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 851 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3260 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 855 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3268 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 859 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3276 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 863 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3284 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 867 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3292 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 871 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3300 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 875 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3308 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 879 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3316 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 883 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3324 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 887 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3332 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 891 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3340 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 895 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3348 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 899 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3356 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 903 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3364 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 909 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3372 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 916 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_or(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3380 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 920 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_and(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3388 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 924 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_not(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3396 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 928 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[-1].opval);
    }
#line 3404 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 934 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3412 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 938 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_special_assign(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3420 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 944 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 3428 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 948 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 3436 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 3464 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 978 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      int32_t is_key_values = 0;
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[-1].opval), is_key_values);
    }
#line 3474 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 984 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      int32_t is_key_values = 1;
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[-1].opval), is_key_values);
    }
#line 3484 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 990 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      int32_t is_key_values = 1;
      SPVM_OP* op_list_elements = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, op_list_elements, is_key_values);
    }
#line 3495 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 999 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      (yyval.opval) = SPVM_OP_build_convert(compiler, op_convert, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3504 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1006 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 3512 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1010 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3520 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1014 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3528 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1020 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3536 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1024 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_expressions = SPVM_OP_new_op_list(compiler, (yyvsp[-1].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), op_expressions);
    }
#line 3545 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1029 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3553 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1033 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_expressions = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-2].opval), (yyvsp[0].opval), op_expressions);
    }
#line 3562 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1038 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3570 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1042 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_expressions = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-2].opval), (yyvsp[0].opval), op_expressions);
    }
#line 3579 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1047 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_method_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[-3].opval)->file, (yyvsp[-3].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_method(compiler, (yyvsp[-4].opval), op_method_name, (yyvsp[-1].opval));
    }
#line 3588 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1053 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 3596 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1057 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3604 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1061 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3612 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1067 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 3621 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1074 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_unweaken_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 3630 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1081 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_isweak_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 3639 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1088 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[0].opval));
    }
#line 3648 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1093 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[-1].opval));
    }
#line 3657 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1098 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[0].opval));
    }
#line 3666 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1103 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[-1].opval));
    }
#line 3675 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1110 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[0].opval), (yyvsp[-1].opval));
    }
#line 3683 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1114 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL, NULL);
    }
#line 3691 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1120 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[0].opval));
    }
#line 3699 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1131 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[0].opval));
    }
#line 3707 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1135 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_byte_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3717 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1141 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_short_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3727 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1147 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3737 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1153 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_long_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3747 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1159 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_float_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3757 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1165 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_double_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3767 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1171 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_any_object_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3777 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1177 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_string_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3787 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1185 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[-1].opval));
    }
#line 3795 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1191 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-2].opval), NULL);
    }
#line 3803 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1195 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-2].opval), NULL);
    }
#line 3811 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1201 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3819 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1205 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3827 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1212 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 3835 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;


#line 3839 "spvm_yacc.tab.c" /* yacc.c:1646  */
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

