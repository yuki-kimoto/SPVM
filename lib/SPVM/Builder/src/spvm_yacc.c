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

#line 87 "spvm_yacc.tab.c" /* yacc.c:339  */

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
    SELF = 264,
    USE = 265,
    REQUIRE = 266,
    ALLOW = 267,
    DESCRIPTOR = 268,
    IF = 269,
    UNLESS = 270,
    ELSIF = 271,
    ELSE = 272,
    FOR = 273,
    WHILE = 274,
    LAST = 275,
    NEXT = 276,
    SWITCH = 277,
    CASE = 278,
    DEFAULT = 279,
    BREAK = 280,
    EVAL = 281,
    NAME = 282,
    VAR_NAME = 283,
    CONSTANT = 284,
    EXCEPTION_VAR = 285,
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
    DOT3 = 296,
    FATCAMMA = 297,
    RW = 298,
    RO = 299,
    WO = 300,
    INIT = 301,
    NEW = 302,
    RETURN = 303,
    WEAKEN = 304,
    DIE = 305,
    WARN = 306,
    PRINT = 307,
    CURRENT_CLASS = 308,
    UNWEAKEN = 309,
    ASSIGN = 310,
    SPECIAL_ASSIGN = 311,
    LOGICAL_OR = 312,
    LOGICAL_AND = 313,
    BIT_OR = 314,
    BIT_XOR = 315,
    NUMEQ = 316,
    NUMNE = 317,
    STREQ = 318,
    STRNE = 319,
    NUMGT = 320,
    NUMGE = 321,
    NUMLT = 322,
    NUMLE = 323,
    STRGT = 324,
    STRGE = 325,
    STRLT = 326,
    STRLE = 327,
    ISA = 328,
    NUMERIC_CMP = 329,
    STRING_CMP = 330,
    SHIFT = 331,
    MULTIPLY = 332,
    DIVIDE = 333,
    REMAINDER = 334,
    LOGICAL_NOT = 335,
    BIT_NOT = 336,
    CREATE_REF = 337,
    DEREF = 338,
    PLUS = 339,
    MINUS = 340,
    CONVERT = 341,
    SCALAR = 342,
    STRING_LENGTH = 343,
    ISWEAK = 344,
    REFCNT = 345,
    REFOP = 346,
    DUMP = 347,
    INC = 348,
    DEC = 349,
    ARROW = 350
  };
#endif

/* Value type.  */



int SPVM_yyparse (SPVM_COMPILER* compiler);

#endif /* !YY_SPVM_YY_SPVM_YACC_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 228 "spvm_yacc.tab.c" /* yacc.c:358  */

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
#define YYLAST   3090

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  110
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  79
/* YYNRULES -- Number of rules.  */
#define YYNRULES  236
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  466

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   350

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    64,     2,
      57,   107,     2,    81,   108,    82,    83,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   104,   105,
       2,     2,     2,     2,    89,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    55,     2,   109,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    56,     2,   106,     2,     2,     2,     2,
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
      58,    59,    60,    61,    62,    63,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    84,    85,    86,    87,    88,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    64,    64,    72,    75,    88,   102,   105,   109,   113,
     117,   123,   132,   135,   147,   161,   164,   165,   166,   167,
     168,   169,   170,   173,   183,   187,   193,   200,   207,   213,
     222,   225,   238,   252,   253,   256,   260,   266,   272,   278,
     283,   288,   293,   300,   308,   327,   330,   341,   349,   368,
     382,   383,   386,   393,   396,   399,   410,   413,   426,   440,
     444,   447,   460,   474,   477,   478,   479,   480,   481,   482,
     483,   484,   485,   486,   490,   491,   492,   493,   497,   501,
     505,   509,   513,   517,   521,   522,   523,   529,   535,   541,
     547,   553,   561,   575,   581,   585,   591,   595,   601,   607,
     614,   625,   639,   642,   646,   652,   660,   667,   670,   684,
     687,   690,   691,   694,   695,   696,   697,   698,   699,   700,
     701,   702,   703,   704,   705,   706,   707,   708,   709,   710,
     711,   727,   728,   729,   730,   733,   747,   751,   757,   762,
     767,   771,   775,   779,   783,   787,   791,   797,   802,   809,
     814,   821,   826,   831,   835,   839,   843,   847,   852,   856,
     860,   866,   870,   874,   878,   882,   886,   890,   894,   898,
     902,   906,   910,   914,   918,   924,   931,   935,   939,   943,
     949,   953,   959,   963,   967,   993,   999,  1005,  1014,  1021,
    1025,  1029,  1035,  1039,  1043,  1048,  1052,  1057,  1063,  1067,
    1071,  1077,  1084,  1091,  1098,  1103,  1108,  1113,  1120,  1124,
    1130,  1136,  1137,  1138,  1141,  1145,  1151,  1157,  1163,  1169,
    1175,  1181,  1187,  1195,  1201,  1205,  1211,  1215,  1221,  1222,
    1228,  1231,  1235,  1238,  1251,  1265,  1266
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CLASS", "HAS", "METHOD", "OUR", "ENUM",
  "MY", "SELF", "USE", "REQUIRE", "ALLOW", "DESCRIPTOR", "IF", "UNLESS",
  "ELSIF", "ELSE", "FOR", "WHILE", "LAST", "NEXT", "SWITCH", "CASE",
  "DEFAULT", "BREAK", "EVAL", "NAME", "VAR_NAME", "CONSTANT",
  "EXCEPTION_VAR", "UNDEF", "VOID", "BYTE", "SHORT", "INT", "LONG",
  "FLOAT", "DOUBLE", "STRING", "OBJECT", "DOT3", "FATCAMMA", "RW", "RO",
  "WO", "INIT", "NEW", "RETURN", "WEAKEN", "DIE", "WARN", "PRINT",
  "CURRENT_CLASS", "UNWEAKEN", "'['", "'{'", "'('", "ASSIGN",
  "SPECIAL_ASSIGN", "LOGICAL_OR", "LOGICAL_AND", "BIT_OR", "BIT_XOR",
  "'&'", "NUMEQ", "NUMNE", "STREQ", "STRNE", "NUMGT", "NUMGE", "NUMLT",
  "NUMLE", "STRGT", "STRGE", "STRLT", "STRLE", "ISA", "NUMERIC_CMP",
  "STRING_CMP", "SHIFT", "'+'", "'-'", "'.'", "MULTIPLY", "DIVIDE",
  "REMAINDER", "LOGICAL_NOT", "BIT_NOT", "'@'", "CREATE_REF", "DEREF",
  "PLUS", "MINUS", "CONVERT", "SCALAR", "STRING_LENGTH", "ISWEAK",
  "REFCNT", "REFOP", "DUMP", "INC", "DEC", "ARROW", "':'", "';'", "'}'",
  "')'", "','", "']'", "$accept", "grammar", "opt_classes", "classes",
  "class", "class_block", "opt_declarations", "declarations",
  "declaration", "init_block", "use", "require", "allow", "enumeration",
  "enumeration_block", "opt_enumeration_values", "enumeration_values",
  "enumeration_value", "our", "has", "method", "anon_method", "opt_args",
  "args", "arg", "opt_vaarg", "invocant", "opt_descriptors", "descriptors",
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
  "array_type_with_length", "type_or_void", "field_name", "method_name",
  "opt_method_names", "method_names", YY_NULLPTR
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
     305,   306,   307,   308,   309,    91,   123,    40,   310,   311,
     312,   313,   314,   315,    38,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,    43,    45,    46,   332,   333,   334,   335,   336,    64,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,    58,    59,   125,    41,    44,    93
};
# endif

#define YYPACT_NINF -378

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-378)))

#define YYTABLE_NINF -138

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-138)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      34,   245,    41,  -378,    34,  -378,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,   -35,  -378,  -378,    40,    55,
    -378,  -378,    58,    48,   245,   245,  -378,    36,    -7,    45,
    -378,  -378,  -378,  -378,  -378,    -4,  -378,  -378,    49,    83,
     -33,  -378,     8,    10,   -28,     5,  1061,  -378,  -378,  -378,
    -378,   -10,    63,  -378,  -378,  -378,    55,    55,   104,  -378,
    -378,   105,    80,    90,    95,    96,    51,    65,   100,  2042,
      67,    76,    36,   111,  -378,  -378,  -378,  -378,   245,  1441,
     105,  1520,  1599,  2042,  -378,   105,   586,  1156,  2042,  2042,
    2042,  2042,  2121,   105,   105,    16,  2042,   105,   105,  2042,
    2042,  2042,  2042,  -378,  -378,   164,    66,  1251,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,   384,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,    69,
    -378,    71,    79,    81,  -378,  -378,  -378,  -378,    73,  -378,
     229,    70,   104,  -378,   245,   245,  -378,    75,    82,    84,
    1852,  1947,  1678,  1947,  -378,  -378,  2042,  1346,  2862,    36,
    -378,    86,   871,   128,   132,  -378,  -378,  2670,    89,  -378,
    2718,  -378,  2766,  2814,    92,    21,  -378,    87,  2909,    85,
      94,  -378,   384,   -13,    28,    93,   -22,  -378,   144,     1,
       1,     1,  1346,     1,  -378,  -378,  2200,     1,    98,  -378,
       1,     1,    20,    20,    99,  -378,  -378,  2042,  2042,  2042,
    2042,  2042,  2042,  2042,  2042,  2042,  2042,  2042,  2042,  2042,
    2042,  2042,  2042,  2042,   245,  2042,  2042,  2042,  2042,  2042,
    2042,  2042,  2042,  2042,  -378,  -378,    52,  -378,  2042,    58,
    2042,    58,  -378,  -378,   104,  -378,  -378,   -21,   145,   229,
     101,   103,  -378,   154,   108,  -378,   109,   104,   245,   245,
    1947,  1947,   110,    -1,  2909,  -378,     4,   113,  2909,     6,
    2532,    36,  -378,  -378,   112,   681,   776,  -378,   159,  -378,
    -378,  -378,   160,   105,    55,  -378,  1757,   245,  -378,  -378,
    2042,   118,  -378,   120,  2578,  1346,     1,   165,   229,  2909,
    2909,   235,   235,  2948,  2987,  2987,  2987,  2987,   672,   672,
     672,   672,   672,   672,   672,   672,  -378,   672,   672,    77,
      64,    64,    64,     1,     1,     1,  2042,    58,   871,   173,
    2245,   116,  2293,   125,   183,   105,   184,  -378,   104,   213,
    -378,  -378,  -378,  -378,  -378,    78,  2485,   136,  -378,    36,
    1947,  1947,    36,    36,  1947,    36,   189,  -378,  -378,  -378,
    2341,  -378,  2389,    58,    58,  -378,    94,   241,  2909,  -378,
       1,  -378,  2624,    58,   190,  2437,   142,   143,   871,  -378,
    -378,  -378,  -378,   871,   210,   146,   147,   148,   105,  -378,
    -378,  -378,   236,   196,  -378,   126,   126,    29,  -378,   247,
    -378,  -378,  -378,   167,   168,   172,  -378,   180,   105,  -378,
    -378,  -378,   181,   182,  -378,   185,   105,   199,   210,    36,
     214,    36,  -378,  -378,   966,    -8,  -378,  -378,  -378,   229,
    -378,   210,  -378,  -378,   -30,   146,  -378,   186,  -378,  1947,
    -378,   188,  -378,  -378,   191,   233,   216,  -378,  -378,   -25,
      13,    36,  -378,   105,    36,  -378,  -378,    36,  -378,   210,
    -378,   126,   217,  -378,    36,  -378
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     2,     4,     6,   214,   215,   216,   217,
     218,   219,   220,   222,   221,     0,     1,     5,    56,    56,
       9,     7,     0,     0,     0,     0,    59,     0,     0,    56,
      15,    22,    20,    21,    18,     0,    16,    17,     0,    57,
       0,   230,     0,     0,     0,     0,    56,    23,    11,    14,
      19,     0,     0,    58,    10,     8,    56,    56,   232,    24,
      27,     0,     0,     0,     0,     0,     0,     0,     0,    56,
       0,     0,     0,   214,   210,   115,   114,   116,     0,    56,
       0,    56,    56,    56,   131,     0,    56,    56,    56,    56,
      56,    56,    56,     0,     0,     0,    56,     0,     0,    56,
      56,    56,    56,    86,   184,     0,     0,    56,    63,    65,
      66,    68,    69,    70,    72,    64,    67,    71,     0,   125,
     128,   129,   126,   133,   134,   127,   121,   122,   120,   119,
     117,   118,     0,     0,   132,   123,   124,   113,     0,   231,
       0,     0,    30,    28,     0,     0,   236,     0,   233,   209,
      56,    56,    56,    56,    74,    75,    56,    56,     0,    97,
      76,     0,    56,   182,     0,   183,    77,     0,     0,    79,
       0,    81,     0,     0,     0,     0,    51,     0,   137,   108,
     113,   187,   137,     0,     0,     0,   211,   213,   212,   138,
     139,   140,    56,   204,   146,   145,    56,   143,     0,   141,
     142,   144,   147,   149,     0,   105,    62,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,     0,    56,    56,    56,    56,    56,
      56,    56,    56,    56,   148,   150,     0,    73,    56,     0,
      56,     0,    84,    85,     0,   229,   228,   211,     0,     0,
       0,    31,    34,    35,     0,    37,     0,   235,     0,     0,
      56,    56,     0,     0,   111,   112,     0,     0,   110,     0,
       0,    95,    96,   106,     0,    56,    56,    78,     0,    80,
      82,    83,     0,    50,    56,   185,   136,     0,   186,   130,
      56,     0,   223,     0,   137,    56,   206,     0,     0,   180,
     181,   158,   156,   157,   161,   162,   168,   169,   163,   164,
     165,   166,   170,   171,   172,   173,   175,   167,   174,   159,
     151,   152,   160,   153,   154,   155,    56,     0,    56,   196,
       0,     0,     0,     0,   194,    45,     0,    29,    33,     0,
      38,    25,   234,   208,    26,     0,   111,   112,   178,     0,
      56,    56,     0,     0,    56,     0,     0,    94,   192,   224,
       0,   225,     0,     0,     0,    49,     0,     0,   135,    52,
     188,   205,   137,     0,     0,     0,     0,     0,    56,   190,
     200,   191,   199,    56,    53,    46,    47,     0,    45,    32,
      36,   179,    98,   176,   177,   102,   102,     0,    88,     0,
      89,   226,   227,     0,     0,     0,   207,     0,    45,   189,
     198,   197,     0,     0,    54,     0,     0,     0,    53,     0,
       0,     0,   100,   101,    56,     0,    93,   201,   202,     0,
     203,    53,   195,   193,     0,    48,    55,     0,    99,    56,
     103,     0,    90,    92,     0,     0,     0,    42,    41,     0,
       0,     0,    91,    45,     0,    40,    39,     0,    87,    53,
      43,   102,     0,   104,     0,    44
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -378,  -378,  -378,  -378,   287,   256,  -378,  -378,   298,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,    -5,  -378,  -378,
    -378,  -378,  -370,   -84,    56,  -331,  -378,    -9,  -378,  -378,
    -378,   224,  -378,  -378,  -378,  -378,  -378,  -328,   -90,  -378,
    -378,  -377,   -27,  -378,  -155,   -82,  -145,   283,   -75,  -378,
    -378,  -378,  -378,  -378,  -378,    88,  -378,  -378,  -378,  -378,
    -378,  -378,  -378,  -378,  -378,  -378,  -378,  -378,   -58,   -83,
       0,  -378,   262,  -378,  -235,  -209,   -47,  -378,  -378
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    21,    28,    29,    30,    31,
      32,   262,    33,    34,   143,   250,   251,   252,    35,    36,
      37,   104,   384,   385,   176,   415,   386,   105,    39,   106,
     107,   108,   109,   110,   111,   400,   425,   112,   113,   114,
     115,   422,   116,   117,   177,   267,   263,   264,   179,   119,
     120,   121,   122,   123,   124,   265,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   246,
     138,   187,   188,   165,   248,    42,   253,   147,   148
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      47,    15,   175,   149,   141,   185,   266,   274,   269,    38,
      40,   146,   183,   184,   336,    69,    70,   139,   418,   423,
      38,    18,   168,    18,    44,    45,    46,   174,   180,    58,
     331,    46,   333,   291,   291,   194,   195,     1,   431,   198,
     199,    16,   292,   292,    22,   161,    23,   144,   145,    22,
      24,    23,    25,    26,    51,    24,    52,    25,    26,   350,
     351,   254,   255,   374,   350,   351,   350,   351,    26,    19,
      20,   426,    54,   350,   351,   447,    43,    59,   163,   139,
     455,   244,   183,   459,   463,    41,    27,   437,   186,   350,
     351,    27,    46,   288,   140,   286,    53,   443,   442,    48,
     446,    50,   234,   235,   236,   196,   352,   326,   327,   328,
      60,   353,    56,   355,    57,   345,   348,   183,   376,   142,
     457,  -138,  -138,   236,   238,   239,   240,   241,   462,   283,
     284,   139,   272,    74,   424,   289,   286,   150,   350,   351,
     247,   316,   420,   421,   247,   247,   -12,   151,   231,   232,
     233,   -13,   152,   153,   403,   404,   154,   156,   228,   229,
     230,   231,   232,   233,   407,   234,   235,   236,   162,   204,
     155,   159,   205,   377,   249,   343,   244,   185,   234,   235,
     236,   160,   256,   275,   242,   184,   243,   276,   258,   329,
     257,   273,   278,   286,   445,   282,   285,   334,   287,   293,
     290,   297,   335,   298,   369,   393,   394,   337,   436,   397,
     342,   338,   339,   340,   341,   363,   364,   349,   354,   358,
     183,   373,   380,   412,   247,   366,     6,   359,   413,   361,
     378,   382,     7,     8,     9,    10,    11,    12,    13,    14,
     383,   388,   390,   391,   357,   399,   405,   408,   410,   247,
     411,   414,   417,   419,   283,   416,     6,   351,   247,   344,
     186,   245,     7,     8,     9,    10,    11,    12,    13,    14,
      69,   439,     6,   427,   428,   367,   429,   387,     7,     8,
       9,    10,    11,    12,    13,    14,   430,   247,   432,   433,
     453,    17,   434,   449,   450,   451,    55,   452,   247,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   392,   454,   464,   395,   396,    49,   398,   118,
     387,   206,   435,   389,   369,   444,   234,   235,   236,   365,
     164,     0,   441,     0,     0,     0,     0,     0,   347,     0,
     387,     0,   158,     0,     0,     0,     0,     0,   366,     0,
       0,     0,   167,     0,   170,   172,   173,     0,     0,   178,
     182,   178,   189,   190,   191,   193,     0,     0,     0,   197,
       0,     0,   200,   201,   202,   203,     0,     0,     0,     0,
     118,     0,   438,     0,   440,   387,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   448,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   247,     0,     0,
       0,     0,   456,     0,   458,     0,     0,   460,     0,   247,
     461,     0,     0,     0,     0,   268,     0,   465,     0,   270,
     178,     0,   207,   208,     0,   178,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,     0,     0,     0,     0,   294,     0,     0,     0,   296,
       0,     0,     0,     0,     0,   234,   235,   236,     0,   237,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,     0,   317,   318,
     319,   320,   321,   322,   323,   324,   325,     0,     0,     0,
       0,   330,     0,   332,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   346,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   360,   362,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   368,
       0,     0,     0,   370,     0,     0,     0,     0,   372,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,     0,     0,     0,     0,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   375,
       0,   178,     0,    73,    74,    75,    76,    77,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,     0,    78,     0,     0,     0,     0,     0,    84,
       0,    86,   157,    88,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   178,     0,     0,     0,     0,   178,    89,    90,     0,
       0,     0,     0,     0,    91,    92,    93,    94,     0,     0,
       0,    95,    96,    97,    98,    99,   100,   101,   102,    61,
       0,     0,     0,     0,    26,  -107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   268,    73,    74,
      75,    76,    77,     0,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     0,     0,     0,     0,     0,    78,     0,
       0,     0,     0,     0,    84,     0,    86,   157,    88,     0,
       0,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,
    -138,  -138,   227,   228,   229,   230,   231,   232,   233,     0,
       0,     0,    89,    90,     0,     0,     0,     0,     0,    91,
      92,    93,    94,   234,   235,   236,    95,    96,    97,    98,
      99,   100,   101,   102,    61,     0,     0,     0,     0,    26,
     359,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    73,    74,    75,    76,    77,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,     0,    78,     0,     0,     0,     0,     0,    84,
       0,    86,   157,    88,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    89,    90,     0,
       0,     0,     0,     0,    91,    92,    93,    94,     0,     0,
       0,    95,    96,    97,    98,    99,   100,   101,   102,    61,
       0,     0,     0,     0,    26,   361,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    73,    74,
      75,    76,    77,     0,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     0,     0,     0,     0,     0,    78,     0,
       0,     0,     0,     0,    84,     0,    86,   157,    88,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,    90,     0,     0,     0,     0,     0,    91,
      92,    93,    94,     0,     0,     0,    95,    96,    97,    98,
      99,   100,   101,   102,    61,     0,     0,     0,  -107,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    73,    74,    75,    76,    77,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,     0,    78,     0,     0,     0,     0,     0,    84,
       0,    86,   157,    88,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    89,    90,     0,
       0,     0,     0,     0,    91,    92,    93,    94,     0,     0,
       0,    95,    96,    97,    98,    99,   100,   101,   102,    61,
       0,     0,     0,  -109,    26,    62,    63,     0,     0,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,     0,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     0,     0,     0,     0,     0,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,    90,     0,     0,     0,     0,     0,    91,
      92,    93,    94,     0,     0,     0,    95,    96,    97,    98,
      99,   100,   101,   102,    61,     0,   103,   -60,     0,    26,
      62,    63,     0,     0,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,     0,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    89,    90,     0,
       0,     0,     0,     0,    91,    92,    93,    94,     0,     0,
       0,    95,    96,    97,    98,    99,   100,   101,   102,    61,
       0,   103,   181,     0,    26,    62,    63,     0,     0,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,     0,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     0,     0,     0,     0,     0,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,    90,     0,     0,     0,     0,     0,    91,
      92,    93,    94,     0,     0,     0,    95,    96,    97,    98,
      99,   100,   101,   102,    61,     0,   103,   -61,     0,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    73,    74,    75,    76,    77,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,     0,    78,     0,     0,     0,     0,     0,    84,
       0,    86,   157,    88,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    89,    90,     0,
       0,     0,     0,     0,    91,    92,    93,    94,     0,     0,
       0,    95,    96,    97,    98,    99,   100,   101,   102,    61,
       0,     0,   181,     0,    26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    73,    74,
      75,    76,    77,     0,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     0,     0,     0,     0,     0,    78,     0,
       0,     0,     0,     0,    84,     0,    86,   157,    88,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,    90,     0,     0,     0,     0,    61,    91,
      92,    93,    94,    26,     0,     0,    95,    96,    97,    98,
      99,   100,   101,   102,     0,     0,   166,    73,    74,    75,
      76,    77,     0,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,     0,     0,    84,     0,    86,   157,    88,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    89,    90,     0,     0,     0,     0,    61,    91,    92,
      93,    94,    26,     0,     0,    95,    96,    97,    98,    99,
     100,   101,   102,     0,     0,   169,    73,    74,    75,    76,
      77,     0,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,     0,     0,     0,     0,    78,     0,     0,     0,
       0,     0,    84,     0,    86,   157,    88,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      89,    90,     0,     0,     0,     0,    61,    91,    92,    93,
      94,    26,     0,     0,    95,    96,    97,    98,    99,   100,
     101,   102,     0,     0,   171,    73,    74,    75,    76,    77,
       0,     7,     8,     9,    10,    11,    12,    13,    14,     0,
       0,     0,     0,     0,     0,    78,     0,     0,     0,     0,
       0,    84,     0,    86,   157,    88,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    89,
      90,     0,   -56,     0,     0,    61,    91,    92,    93,    94,
      26,     0,     0,    95,    96,    97,    98,    99,   100,   101,
     102,     0,     0,  -109,    73,    74,    75,    76,    77,     0,
       7,     8,     9,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,     0,    78,     0,     0,     0,     0,     0,
      84,     0,    86,   157,    88,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    89,    90,
       0,     0,     0,     0,     0,    91,    92,    93,    94,     0,
       0,     0,    95,    96,    97,    98,    99,   100,   101,   102,
      61,     0,     0,   259,     0,    26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      74,    75,    76,    77,     0,     7,     8,     9,    10,    11,
      12,    13,    14,     0,     0,     0,     0,     0,     0,    78,
       0,     0,     0,     0,     0,    84,     0,    86,   157,   260,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    89,    90,     0,     0,     0,     0,   261,
      91,    92,    93,    94,     0,     0,     0,    95,    96,    97,
      98,    99,   100,   101,   102,    61,     0,     0,     0,     0,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    73,    74,    75,    76,    77,     0,
       7,     8,     9,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,     0,    78,     0,     0,     0,     0,     0,
      84,     0,    86,   157,   260,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    89,    90,
       0,     0,     0,     0,   261,    91,    92,    93,    94,     0,
       0,     0,    95,    96,    97,    98,    99,   100,   101,   102,
      61,     0,     0,     0,     0,    26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      74,    75,    76,    77,     0,     7,     8,     9,    10,    11,
      12,    13,    14,     0,     0,     0,     0,     0,     0,    78,
       0,     0,     0,     0,     0,    84,     0,    86,   157,    88,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    89,    90,     0,     0,     0,     0,    61,
      91,    92,    93,    94,    26,     0,     0,    95,    96,    97,
      98,    99,   100,   101,   102,     0,     0,     0,    73,    74,
      75,    76,    77,     0,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     0,     0,     0,     0,     0,    78,     0,
       0,     0,     0,     0,    84,     0,    86,   192,    88,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,    90,     0,     0,     0,     0,    61,    91,
      92,    93,    94,    26,     0,     0,    95,    96,    97,    98,
      99,   100,   101,   102,     0,     0,     0,    73,    74,    75,
      76,    77,     0,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,     0,     0,    84,     0,    86,   295,    88,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    89,    90,     0,     0,     0,     0,     0,    91,    92,
      93,    94,     0,     0,     0,    95,    96,    97,    98,    99,
     100,   101,   102,   207,   208,     0,     0,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   234,   235,   236,     0,
       0,   207,   208,     0,   379,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   234,   235,   236,     0,     0,   207,
     208,     0,   381,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   234,   235,   236,     0,     0,   207,   208,     0,
     401,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     234,   235,   236,     0,     0,   207,   208,     0,   402,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   234,   235,
     236,     0,     0,   207,   208,     0,   409,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   234,   235,   236,     0,
     207,   208,  -137,  -137,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   234,   235,   236,   207,   208,     0,   356,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   234,
     235,   236,   207,   208,   371,     0,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   234,   235,   236,   207,   208,
     406,     0,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   234,   235,   236,     0,   277,   207,   208,     0,     0,
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
       0,     0,     0,     0,     0,   234,   235,   236,     0,   281,
     207,   208,     0,     0,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   234,   235,   236,   271,   207,   208,     0,
       0,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     234,   235,   236,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   234,
     235,   236,  -138,  -138,  -138,  -138,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   234,   235,
     236
};

static const yytype_int16 yycheck[] =
{
      27,     1,    86,    61,    51,    88,   151,   162,   153,    18,
      19,    58,    87,    88,   249,    23,    24,    27,   388,   396,
      29,    56,    80,    56,    24,    25,    56,    85,    86,    57,
     239,    56,   241,    55,    55,    93,    94,     3,   408,    97,
      98,     0,    64,    64,     4,    72,     6,    56,    57,     4,
      10,     6,    12,    13,     5,    10,     7,    12,    13,    60,
      61,   144,   145,   298,    60,    61,    60,    61,    13,   104,
     105,   399,   105,    60,    61,   105,    28,   105,    78,    27,
     105,   103,   157,   453,   461,    27,    46,   418,    88,    60,
      61,    46,    56,   106,   104,   108,    13,   425,   106,   106,
     431,   105,   101,   102,   103,    89,   107,    55,    56,    57,
     105,   107,   104,   107,   104,   260,   261,   192,   327,    56,
     107,   101,   102,   103,    55,    56,    55,    56,   459,   108,
     109,    27,   159,    28,   105,   107,   108,    57,    60,    61,
     140,   224,    16,    17,   144,   145,   106,    57,    84,    85,
      86,   106,    57,    57,   363,   364,   105,    57,    81,    82,
      83,    84,    85,    86,   373,   101,   102,   103,    57,     5,
     105,   104,   106,   328,   104,   258,   103,   260,   101,   102,
     103,   105,   107,    55,   105,   260,   105,    55,   104,   236,
     108,   105,   103,   108,   429,   103,   109,   244,   104,    55,
     107,   103,    57,   104,   287,   350,   351,   106,     9,   354,
     257,   108,    58,   105,   105,    56,    56,   107,   105,   107,
     295,    56,   106,   378,   224,   283,    27,   109,   383,   109,
      57,   106,    33,    34,    35,    36,    37,    38,    39,    40,
      57,    57,    29,   107,   271,    56,     5,    57,   106,   249,
     107,    41,   104,    17,   108,   108,    27,    61,   258,   259,
     260,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      23,    57,    27,   106,   106,   284,   104,   335,    33,    34,
      35,    36,    37,    38,    39,    40,   106,   287,   107,   107,
      57,     4,   107,   107,   439,   107,    40,   106,   298,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,   349,   107,   107,   352,   353,    29,   355,    46,
     388,   107,   416,   338,   417,   425,   101,   102,   103,   283,
      78,    -1,   424,    -1,    -1,    -1,    -1,    -1,   260,    -1,
     408,    -1,    69,    -1,    -1,    -1,    -1,    -1,   416,    -1,
      -1,    -1,    79,    -1,    81,    82,    83,    -1,    -1,    86,
      87,    88,    89,    90,    91,    92,    -1,    -1,    -1,    96,
      -1,    -1,    99,   100,   101,   102,    -1,    -1,    -1,    -1,
     107,    -1,   419,    -1,   421,   453,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   434,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   417,    -1,    -1,
      -1,    -1,   449,    -1,   451,    -1,    -1,   454,    -1,   429,
     457,    -1,    -1,    -1,    -1,   152,    -1,   464,    -1,   156,
     157,    -1,    58,    59,    -1,   162,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    -1,    -1,    -1,    -1,   192,    -1,    -1,    -1,   196,
      -1,    -1,    -1,    -1,    -1,   101,   102,   103,    -1,   105,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,    -1,   225,   226,
     227,   228,   229,   230,   231,   232,   233,    -1,    -1,    -1,
      -1,   238,    -1,   240,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   260,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   275,   276,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   286,
      -1,    -1,    -1,   290,    -1,    -1,    -1,    -1,   295,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,    13,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   326,
      -1,   328,    -1,    27,    28,    29,    30,    31,    -1,    33,
      34,    35,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   378,    -1,    -1,    -1,    -1,   383,    81,    82,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,    -1,    -1,
      -1,    95,    96,    97,    98,    99,   100,   101,   102,     8,
      -1,    -1,    -1,    -1,    13,   109,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   424,    27,    28,
      29,    30,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    53,    -1,    55,    56,    57,    -1,
      -1,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    -1,
      -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,   101,   102,   103,    95,    96,    97,    98,
      99,   100,   101,   102,     8,    -1,    -1,    -1,    -1,    13,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    28,    29,    30,    31,    -1,    33,
      34,    35,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,    -1,    -1,
      -1,    95,    96,    97,    98,    99,   100,   101,   102,     8,
      -1,    -1,    -1,    -1,    13,   109,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,
      29,    30,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    53,    -1,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    -1,    -1,    -1,    95,    96,    97,    98,
      99,   100,   101,   102,     8,    -1,    -1,    -1,   107,    13,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    28,    29,    30,    31,    -1,    33,
      34,    35,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,    -1,    -1,
      -1,    95,    96,    97,    98,    99,   100,   101,   102,     8,
      -1,    -1,    -1,   107,    13,    14,    15,    -1,    -1,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    -1,    -1,    -1,    95,    96,    97,    98,
      99,   100,   101,   102,     8,    -1,   105,   106,    -1,    13,
      14,    15,    -1,    -1,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    33,
      34,    35,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,    -1,    -1,
      -1,    95,    96,    97,    98,    99,   100,   101,   102,     8,
      -1,   105,   106,    -1,    13,    14,    15,    -1,    -1,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    -1,    -1,    -1,    95,    96,    97,    98,
      99,   100,   101,   102,     8,    -1,   105,   106,    -1,    13,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    28,    29,    30,    31,    -1,    33,
      34,    35,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,    -1,    -1,
      -1,    95,    96,    97,    98,    99,   100,   101,   102,     8,
      -1,    -1,   106,    -1,    13,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,
      29,    30,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    53,    -1,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    -1,    -1,    -1,    -1,     8,    88,
      89,    90,    91,    13,    -1,    -1,    95,    96,    97,    98,
      99,   100,   101,   102,    -1,    -1,   105,    27,    28,    29,
      30,    31,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    55,    56,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    -1,    -1,    -1,    -1,     8,    88,    89,
      90,    91,    13,    -1,    -1,    95,    96,    97,    98,    99,
     100,   101,   102,    -1,    -1,   105,    27,    28,    29,    30,
      31,    -1,    33,    34,    35,    36,    37,    38,    39,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    55,    56,    57,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    -1,    -1,    -1,    -1,     8,    88,    89,    90,
      91,    13,    -1,    -1,    95,    96,    97,    98,    99,   100,
     101,   102,    -1,    -1,   105,    27,    28,    29,    30,    31,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,
      -1,    53,    -1,    55,    56,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    -1,     5,    -1,    -1,     8,    88,    89,    90,    91,
      13,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,    -1,    -1,   105,    27,    28,    29,    30,    31,    -1,
      33,    34,    35,    36,    37,    38,    39,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,
      53,    -1,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,    -1,
      -1,    -1,    95,    96,    97,    98,    99,   100,   101,   102,
       8,    -1,    -1,    11,    -1,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,
      28,    29,    30,    31,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    55,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    87,
      88,    89,    90,    91,    -1,    -1,    -1,    95,    96,    97,
      98,    99,   100,   101,   102,     8,    -1,    -1,    -1,    -1,
      13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    27,    28,    29,    30,    31,    -1,
      33,    34,    35,    36,    37,    38,    39,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,
      53,    -1,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      -1,    -1,    -1,    -1,    87,    88,    89,    90,    91,    -1,
      -1,    -1,    95,    96,    97,    98,    99,   100,   101,   102,
       8,    -1,    -1,    -1,    -1,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,
      28,    29,    30,    31,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    55,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,     8,
      88,    89,    90,    91,    13,    -1,    -1,    95,    96,    97,
      98,    99,   100,   101,   102,    -1,    -1,    -1,    27,    28,
      29,    30,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    53,    -1,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    -1,    -1,    -1,    -1,     8,    88,
      89,    90,    91,    13,    -1,    -1,    95,    96,    97,    98,
      99,   100,   101,   102,    -1,    -1,    -1,    27,    28,    29,
      30,    31,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    55,    56,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    -1,    -1,    -1,    95,    96,    97,    98,    99,
     100,   101,   102,    58,    59,    -1,    -1,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   101,   102,   103,    -1,
      -1,    58,    59,    -1,   109,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   101,   102,   103,    -1,    -1,    58,
      59,    -1,   109,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   101,   102,   103,    -1,    -1,    58,    59,    -1,
     109,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     101,   102,   103,    -1,    -1,    58,    59,    -1,   109,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,
     103,    -1,    -1,    58,    59,    -1,   109,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   101,   102,   103,    -1,
      58,    59,   107,   108,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,   102,   103,    58,    59,    -1,   107,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
     102,   103,    58,    59,   106,    -1,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,   102,   103,    58,    59,
     106,    -1,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,   102,   103,    -1,   105,    58,    59,    -1,    -1,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
     102,   103,    -1,   105,    58,    59,    -1,    -1,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,   103,
      -1,   105,    58,    59,    -1,    -1,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,   102,   103,    -1,   105,
      58,    59,    -1,    -1,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,   102,   103,   104,    58,    59,    -1,
      -1,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     101,   102,   103,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
     102,   103,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,
     103
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,   111,   112,   113,   114,    27,    33,    34,    35,
      36,    37,    38,    39,    40,   180,     0,   114,    56,   104,
     105,   115,     4,     6,    10,    12,    13,    46,   116,   117,
     118,   119,   120,   122,   123,   128,   129,   130,   137,   138,
     137,    27,   185,    28,   180,   180,    56,   152,   106,   118,
     105,     5,     7,    13,   105,   115,   104,   104,    57,   105,
     105,     8,    14,    15,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    81,
      82,    88,    89,    90,    91,    95,    96,    97,    98,    99,
     100,   101,   102,   105,   131,   137,   139,   140,   141,   142,
     143,   144,   147,   148,   149,   150,   152,   153,   157,   159,
     160,   161,   162,   163,   164,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   180,    27,
     104,   186,    56,   124,   137,   137,   186,   187,   188,   178,
      57,    57,    57,    57,   105,   105,    57,    56,   157,   104,
     105,   152,    57,   180,   182,   183,   105,   157,   178,   105,
     157,   105,   157,   157,   178,   133,   134,   154,   157,   158,
     178,   106,   157,   158,   158,   179,   180,   181,   182,   157,
     157,   157,    56,   157,   178,   178,    89,   157,   178,   178,
     157,   157,   157,   157,     5,   106,   141,    58,    59,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,   101,   102,   103,   105,    55,    56,
      55,    56,   105,   105,   103,    32,   179,   180,   184,   104,
     125,   126,   127,   186,   179,   179,   107,   108,   104,    11,
      57,    87,   121,   156,   157,   165,   156,   155,   157,   156,
     157,   104,   152,   105,   154,    55,    55,   105,   103,   105,
     105,   105,   103,   108,   109,   109,   108,   104,   106,   107,
     107,    55,    64,    55,   157,    56,   157,   103,   104,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   179,   157,   157,   157,
     157,   157,   157,   157,   157,   157,    55,    56,    57,   186,
     157,   185,   157,   185,   186,    57,   184,   106,   108,    58,
     105,   105,   186,   179,   180,   156,   157,   165,   156,   107,
      60,    61,   107,   107,   105,   107,   107,   152,   107,   109,
     157,   109,   157,    56,    56,   134,   178,   137,   157,   179,
     157,   106,   157,    56,   184,   157,   185,   154,    57,   109,
     106,   109,   106,    57,   132,   133,   136,   178,    57,   127,
      29,   107,   152,   156,   156,   152,   152,   156,   152,    56,
     145,   109,   109,   185,   185,     5,   106,   185,    57,   109,
     106,   107,   154,   154,    41,   135,   108,   104,   132,    17,
      16,    17,   151,   151,   105,   146,   147,   106,   106,   104,
     106,   132,   107,   107,   107,   133,     9,   135,   152,    57,
     152,   155,   106,   147,   148,   184,   135,   105,   152,   107,
     156,   107,   106,    57,   107,   105,   152,   107,   152,   132,
     152,   152,   135,   151,   107,   152
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   110,   111,   112,   112,   113,   113,   114,   114,   114,
     114,   115,   116,   116,   117,   117,   118,   118,   118,   118,
     118,   118,   118,   119,   120,   120,   121,   122,   123,   124,
     125,   125,   126,   126,   126,   127,   127,   128,   129,   130,
     130,   130,   130,   131,   131,   132,   132,   132,   132,   133,
     133,   133,   134,   135,   135,   136,   137,   137,   138,   138,
     139,   139,   140,   140,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   142,   143,   144,
     145,   145,   146,   146,   147,   147,   148,   148,   149,   149,
     150,   150,   151,   151,   151,   152,   153,   154,   154,   155,
     155,   156,   156,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   158,   158,   158,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   160,   160,   161,
     161,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   164,   165,   165,   165,   165,
     166,   166,   167,   167,   167,   168,   168,   168,   169,   170,
     170,   170,   171,   171,   171,   171,   171,   171,   172,   172,
     172,   173,   174,   175,   176,   176,   176,   176,   177,   177,
     178,   179,   179,   179,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   181,   182,   182,   183,   183,   184,   184,
     185,   186,   187,   187,   188,   188,   188
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     3,     5,     3,
       5,     3,     0,     1,     2,     1,     1,     1,     1,     2,
       1,     1,     1,     2,     3,     6,     2,     3,     3,     3,
       0,     1,     3,     2,     1,     1,     3,     5,     6,    10,
      10,     9,     9,     9,    12,     0,     1,     1,     3,     3,
       2,     1,     3,     0,     1,     3,     0,     1,     2,     1,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     2,     3,     2,
       3,     2,     3,     3,     2,     2,     1,     9,     5,     5,
       3,     4,     2,     1,     4,     3,     3,     2,     5,     7,
       6,     6,     0,     2,     6,     3,     3,     0,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     3,     2,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     2,     2,     1,     3,     3,     2,     4,     5,
       4,     4,     4,     6,     3,     6,     3,     5,     5,     4,
       4,     6,     6,     6,     2,     4,     3,     5,     4,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     3,     4,     4,     1,     1,
       1,     1,     0,     1,     3,     2,     1
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
#line 65 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_grammar(compiler, (yyvsp[0].opval));
      compiler->op_grammar = (yyval.opval);
    }
#line 2192 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 72 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2200 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2215 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 2233 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 106 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 2241 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 110 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[0].opval), (yyvsp[-1].opval));
    }
#line 2249 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 114 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), NULL, NULL);
    }
#line 2257 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 118 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_class(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), NULL, (yyvsp[-1].opval));
    }
#line 2265 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 124 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_class_block;
    }
#line 2275 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 132 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2283 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 136 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[0].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
        SPVM_OP_insert_child(compiler, (yyval.opval), (yyval.opval)->last, (yyvsp[0].opval));
      }
    }
#line 2297 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 148 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2315 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 174 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    { 
      SPVM_OP* op_method = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_METHOD, compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_method_name = SPVM_OP_new_op_name(compiler, "INIT", compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_void_type = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
      int32_t can_precompile = 0;
      (yyval.opval) = SPVM_OP_build_method(compiler, op_method, op_method_name, op_void_type, NULL, NULL, (yyvsp[0].opval), NULL, NULL, 1, 0, can_precompile);
    }
#line 2327 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 184 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), NULL, 0);
    }
#line 2335 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 188 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[-5].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), 0);
    }
#line 2343 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 194 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_use(compiler, op_use, (yyvsp[0].opval), NULL, 1);
    }
#line 2352 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 201 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_allow(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2360 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 208 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), (yyvsp[-2].opval));
    }
#line 2368 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 214 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_enum_block;
    }
#line 2378 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 222 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2386 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 226 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2401 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 239 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2419 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 257 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[0].opval), NULL);
    }
#line 2427 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 261 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2435 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 267 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_our(compiler, (yyvsp[-4].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 2443 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 273 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_has(compiler, (yyvsp[-5].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2451 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 279 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t can_precompile = 1;
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-8].opval), (yyvsp[-7].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-9].opval), (yyvsp[0].opval), NULL, (yyvsp[-2].opval), 0, 0, can_precompile);
     }
#line 2460 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 284 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t can_precompile = 0;
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-8].opval), (yyvsp[-7].opval), (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-9].opval), NULL, NULL, (yyvsp[-2].opval), 0, 0, can_precompile);
     }
#line 2469 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 289 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t can_precompile = 1;
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), NULL, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-8].opval), (yyvsp[0].opval), NULL, (yyvsp[-2].opval), 0, 0, can_precompile);
     }
#line 2478 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 294 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t can_precompile = 0;
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), NULL, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-8].opval), NULL, NULL, (yyvsp[-2].opval), 0, 0, can_precompile);
     }
#line 2487 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 301 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       int32_t is_begin = 0;
       int32_t is_anon = 1;
       int32_t can_precompile = 1;
       
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), NULL, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-8].opval), (yyvsp[0].opval), NULL, (yyvsp[-2].opval), is_begin, is_anon, can_precompile);
     }
#line 2499 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 309 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       SPVM_OP* op_list_args;
       if ((yyvsp[-10].opval)->id == SPVM_OP_C_ID_LIST) {
         op_list_args = (yyvsp[-10].opval);
       }
       else {
         op_list_args = SPVM_OP_new_op_list(compiler, (yyvsp[-10].opval)->file, (yyvsp[-10].opval)->line);
         SPVM_OP_insert_child(compiler, op_list_args, op_list_args->last, (yyvsp[-10].opval));
       }
       
       int32_t is_begin = 0;
       int32_t is_anon = 1;
       int32_t can_precompile = 1;
       (yyval.opval) = SPVM_OP_build_method(compiler, (yyvsp[-7].opval), NULL, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-8].opval), (yyvsp[0].opval), op_list_args, (yyvsp[-2].opval), is_begin, is_anon, can_precompile);
     }
#line 2519 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 327 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2527 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 331 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2542 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 342 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
       // Add invocant to arguments
       SPVM_OP* op_args = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
       SPVM_OP_insert_child(compiler, op_args, op_args->last, (yyvsp[0].opval));
       
       (yyval.opval) = op_args;
    }
#line 2554 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 350 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      // Add invocant to arguments
      SPVM_OP* op_args;
      if ((yyvsp[0].opval)->id == SPVM_OP_C_ID_LIST) {
        op_args = (yyvsp[0].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[0].opval));
        op_args = op_list;
      }
      
      SPVM_OP_insert_child(compiler, op_args, op_args->first, (yyvsp[-2].opval));
       
      (yyval.opval) = op_args;
    }
#line 2575 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 369 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2593 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 387 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2601 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 393 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = NULL;
    }
#line 2609 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 400 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_TYPE* type = SPVM_TYPE_new(compiler);
      type->is_self = 1;
      SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[-2].opval), op_type);
    }
#line 2621 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 410 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2629 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 414 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2644 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 427 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2662 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 444 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2670 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 448 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2685 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 461 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2703 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 487 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_expression_statement(compiler, (yyvsp[-1].opval));
    }
#line 2711 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 494 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[-1].opval), NULL);
    }
#line 2719 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 498 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2727 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 502 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-1].opval), NULL);
    }
#line 2735 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 506 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_die(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2743 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 510 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_warn(compiler, (yyvsp[-1].opval), NULL);
    }
#line 2751 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 514 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_warn(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2759 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 518 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_print(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2767 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 524 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    }
#line 2775 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 530 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[-8].opval), (yyvsp[-6].opval), (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2783 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 536 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2791 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 542 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2799 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 548 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->cur_file, compiler->cur_line);
      op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[-1].opval), NULL);
    }
#line 2809 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 554 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->cur_file, compiler->cur_line);
      op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
      (yyval.opval) = SPVM_OP_build_switch_block(compiler, op_block, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2819 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 562 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2837 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 576 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 2845 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 582 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2853 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 586 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval), NULL);
    }
#line 2861 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 592 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2869 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 596 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_default_statement(compiler, (yyvsp[-1].opval), NULL);
    }
#line 2877 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 602 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->cur_file, compiler->cur_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[-2].opval), (yyvsp[0].opval), NULL);
    }
#line 2887 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 608 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->cur_file, compiler->cur_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[-4].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 2897 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 615 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    }
#line 2912 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 626 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-5].opval)->file, (yyvsp[-5].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    }
#line 2927 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 639 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    }
#line 2935 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 643 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 2943 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 647 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 2951 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 653 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, (yyvsp[-1].opval));
      (yyval.opval) = op_block;
    }
#line 2961 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 661 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[-2].opval), (yyvsp[-1].opval));
    }
#line 2969 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 667 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 2977 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 671 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 2992 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 684 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    }
#line 3000 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 712 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3020 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 734 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3038 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 748 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[-1].opval);
    }
#line 3046 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 752 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[0].opval);
    }
#line 3054 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 758 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, op, (yyvsp[0].opval));
    }
#line 3063 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 763 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MINUS, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, op_negate, (yyvsp[0].opval));
    }
#line 3072 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 768 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3080 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 772 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3088 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 776 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3096 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 780 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3104 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 784 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3112 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 788 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3120 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 792 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3128 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 798 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, op, (yyvsp[0].opval));
    }
#line 3137 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 803 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, op, (yyvsp[-1].opval));
    }
#line 3146 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 810 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, op, (yyvsp[0].opval));
    }
#line 3155 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 815 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, op, (yyvsp[-1].opval));
    }
#line 3164 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 822 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3173 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 827 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_METHODTRACT, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3182 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 832 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3190 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 836 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3198 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 840 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3206 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 844 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3214 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 848 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BIT_AND, (yyvsp[-1].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3223 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 853 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3231 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 857 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3239 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 861 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3247 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 867 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3255 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 871 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3263 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 875 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3271 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 879 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3279 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 883 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3287 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 887 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3295 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 891 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3303 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 895 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3311 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 899 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3319 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 903 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3327 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 907 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3335 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 911 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3343 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 915 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3351 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 919 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_comparison_op(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3359 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 925 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3367 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 932 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_or(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3375 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 936 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_and(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3383 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 940 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_not(compiler, (yyvsp[-1].opval), (yyvsp[0].opval));
    }
#line 3391 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 944 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = (yyvsp[-1].opval);
    }
#line 3399 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 950 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3407 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 954 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_special_assign(compiler, (yyvsp[-1].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3415 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 960 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 3423 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 964 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 3431 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 968 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3459 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 994 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      int32_t is_key_values = 0;
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[-1].opval), is_key_values);
    }
#line 3469 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1000 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      int32_t is_key_values = 1;
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[-1].opval), is_key_values);
    }
#line 3479 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1006 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      int32_t is_key_values = 1;
      SPVM_OP* op_list_elements = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, op_list_elements, is_key_values);
    }
#line 3490 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1015 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, (yyvsp[-2].opval)->file, (yyvsp[-2].opval)->line);
      (yyval.opval) = SPVM_OP_build_convert(compiler, op_convert, (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3499 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1022 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 3507 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1026 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3515 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1030 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3523 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1036 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_call_spvm_method(compiler, NULL, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3531 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1040 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_call_spvm_method(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3539 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1044 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_expressions = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_spvm_method(compiler, (yyvsp[-2].opval), (yyvsp[0].opval), op_expressions);
    }
#line 3548 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1049 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_call_spvm_method(compiler, (yyvsp[-5].opval), (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3556 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1053 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_expressions = SPVM_OP_new_op_list(compiler, (yyvsp[-2].opval)->file, (yyvsp[-1].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_spvm_method(compiler, (yyvsp[-2].opval), (yyvsp[0].opval), op_expressions);
    }
#line 3565 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1058 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_method_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[-3].opval)->file, (yyvsp[-3].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_spvm_method(compiler, (yyvsp[-4].opval), op_method_name, (yyvsp[-1].opval));
    }
#line 3574 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1064 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
    }
#line 3582 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1068 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3590 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1072 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3598 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1078 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 3607 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1085 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_unweaken_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 3616 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1092 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, (yyvsp[-4].opval), (yyvsp[-1].opval));
      (yyval.opval) = SPVM_OP_build_isweak_field(compiler, (yyvsp[-5].opval), op_field_access);
    }
#line 3625 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1099 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[0].opval));
    }
#line 3634 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1104 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[-1].opval));
    }
#line 3643 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1109 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[0].opval));
    }
#line 3652 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1114 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[-1].opval));
    }
#line 3661 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1121 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[-3].opval), (yyvsp[-2].opval), (yyvsp[0].opval));
    }
#line 3669 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1125 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[-1].opval), (yyvsp[0].opval), NULL);
    }
#line 3677 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1131 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[0].opval));
    }
#line 3685 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1142 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[0].opval));
    }
#line 3693 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1146 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_byte_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3703 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1152 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_short_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3713 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1158 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3723 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1164 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_long_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3733 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1170 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_float_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3743 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1176 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_double_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3753 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1182 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_any_object_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3763 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1188 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      SPVM_OP* op_type = SPVM_OP_new_op_string_type(compiler, (yyvsp[0].opval)->file, (yyvsp[0].opval)->line);
      
      (yyval.opval) = op_type;
    }
#line 3773 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1196 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[-1].opval));
    }
#line 3781 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1202 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-2].opval), NULL);
    }
#line 3789 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1206 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-2].opval), NULL);
    }
#line 3797 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1212 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3805 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1216 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[-3].opval), (yyvsp[-1].opval));
    }
#line 3813 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1223 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 3821 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1235 "yacc/spvm_yacc.y" /* yacc.c:1646  */
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
#line 3829 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1239 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3844 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1252 "yacc/spvm_yacc.y" /* yacc.c:1646  */
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
#line 3862 "spvm_yacc.tab.c" /* yacc.c:1646  */
    break;


#line 3866 "spvm_yacc.tab.c" /* yacc.c:1646  */
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
#line 1268 "yacc/spvm_yacc.y" /* yacc.c:1906  */

