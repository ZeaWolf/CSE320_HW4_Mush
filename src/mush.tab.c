/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/mush.y"


/*
 * DO NOT MODIFY THE CONTENTS OF THIS FILE.
 * IT WILL BE REPLACED DURING GRADING
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mush.h"
#include "mush.tab.h"

STMT *mush_parsed_stmt;

int yylex();
int yyparse();

void yyerror(const char *str) {
    fprintf(stderr, "error: %s\n", str);
}

int yywrap() {
	return 1;
}


#line 99 "src/mush.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_INCLUDE_MUSH_TAB_H_INCLUDED
# define YY_YY_INCLUDE_MUSH_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUMBER = 258,
    NAME = 259,
    WORD = 260,
    STRING = 261,
    LIST = 262,
    DELETE = 263,
    RUN = 264,
    CONT = 265,
    STOP = 266,
    BG = 267,
    CAPTURE = 268,
    WAIT = 269,
    POLL = 270,
    CANCEL = 271,
    PAUSE = 272,
    SET = 273,
    UNSET = 274,
    IF = 275,
    GOTO = 276,
    SOURCE = 277,
    EQ = 278,
    PIPE = 279,
    LESS = 280,
    GREATER = 281,
    EQUAL = 282,
    LESSEQ = 283,
    GREATEQ = 284,
    AND = 285,
    OR = 286,
    NOT = 287,
    LPAREN = 288,
    RPAREN = 289,
    PLUS = 290,
    MINUS = 291,
    TIMES = 292,
    DIVIDE = 293,
    MOD = 294,
    COMMA = 295,
    SHARP = 296,
    DOLLAR = 297,
    EOL = 298,
    EoF = 299,
    UNKNOWN = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 30 "src/mush.y"

    int number;
    char *string;
    STMT *stmt;
    EXPR *expr;	
    ARG *args;
    COMMAND *cmds;
    PIPELINE *pline;

#line 207 "src/mush.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INCLUDE_MUSH_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
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
#define YYLAST   247

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  114

#define YYUNDEFTOK  2
#define YYMAXUTOK   300


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      45
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    95,    95,   102,   111,   118,   125,   133,   142,   151,
     160,   169,   178,   186,   195,   205,   214,   224,   233,   239,
     243,   251,   256,   261,   266,   273,   277,   284,   291,   296,
     304,   310,   317,   324,   331,   336,   340,   349,   358,   367,
     376,   385,   394,   403,   411,   420,   429,   438,   447,   458,
     462,   466,   467,   477,   480,   483,   484,   485,   486,   489,
     490
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "NAME", "WORD", "STRING",
  "LIST", "DELETE", "RUN", "CONT", "STOP", "BG", "CAPTURE", "WAIT", "POLL",
  "CANCEL", "PAUSE", "SET", "UNSET", "IF", "GOTO", "SOURCE", "EQ", "PIPE",
  "LESS", "GREATER", "EQUAL", "LESSEQ", "GREATEQ", "AND", "OR", "NOT",
  "LPAREN", "RPAREN", "PLUS", "MINUS", "TIMES", "DIVIDE", "MOD", "COMMA",
  "SHARP", "DOLLAR", "EOL", "EoF", "UNKNOWN", "$accept", "statement",
  "pipeline", "command_list", "command", "arg_list", "arg", "atomic_expr",
  "expr", "numeric_var", "string_var", "optional_lineno", "lineno",
  "literal_number", "literal_string", "file", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300
};
# endif

#define YYPACT_NINF (-53)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-52)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      61,   -30,   -53,   -28,    21,   -18,   -16,   -53,   -53,    28,
      92,    18,   -53,   -53,   -53,   -10,   -53,   -53,   -53,   -53,
     -53,   -53,   -53,    85,    85,    85,   -12,    31,    32,    85,
      21,     4,    85,    33,    34,    -9,   -53,     8,   -53,   116,
     -53,   -53,   -53,   -53,    -3,    21,    85,   -53,   117,   136,
     155,   -53,    16,    -1,   174,     0,   -53,   -53,     2,   208,
     -53,   -53,     3,     4,     1,   -53,   116,   -53,   -53,    29,
      -7,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,   -53,   -53,   -53,    85,   -53,    21,   -53,
     -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,
     -53,   -53,   -53,    -7,    -7,   110,   110,   110,   110,   110,
     189,    30,   -53,   -53
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    54,     0,     0,     0,     0,    18,    19,     0,
       0,    52,    53,    20,     2,     0,     4,     5,     1,    55,
      56,    57,    58,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,    25,    27,    28,
      30,    32,    33,    31,     0,     0,     0,    35,     0,     0,
       0,    12,     0,     0,     0,     0,    59,    60,     0,     0,
      49,    50,     0,     0,     0,     7,     0,    29,     6,     0,
      43,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     9,    10,    11,     0,    15,     0,    13,
      17,    34,     8,    22,    24,    23,    26,     3,    37,    38,
      36,    39,    40,    41,    42,    44,    45,    46,    47,    48,
       0,     0,    14,    16
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -53,   -53,   -53,   -22,   -53,    22,   -53,    -6,   -23,   -53,
     -53,   -53,    -4,   -53,   -53,   -52
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     9,    35,    36,    37,    38,    39,    47,    48,    41,
      42,    10,    11,    12,    43,    58
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      15,    49,    50,    62,    40,    56,    54,    57,    56,    59,
      57,    93,    95,    13,    94,    14,    63,    64,    71,    72,
      73,    74,    75,    70,     2,    16,    55,    17,    18,    44,
      45,    51,    66,    40,    65,    52,    53,    60,    61,    86,
      68,    69,    87,    89,    96,    90,    92,     0,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
      40,    67,     1,   110,     2,   -51,   -51,   -51,     3,     4,
       5,     6,    97,   113,     0,   -51,   -51,   -51,   -51,   -51,
     -51,   -51,   -51,   -51,   111,     0,     0,     0,    19,    20,
      21,    22,     0,     0,   -51,    19,    20,    21,    22,     0,
       0,     0,   -51,   -51,     7,     8,    23,    24,    25,    26,
      27,    28,    29,    30,    31,     0,     0,    46,    32,    19,
      20,    21,    22,     0,     0,    32,    33,    34,     0,     0,
       0,     0,     0,    33,    34,    71,    72,    73,    74,    75,
      76,    77,    71,    72,    73,    74,    75,    76,    77,    32,
       0,     0,    78,    79,    80,    81,    82,    33,    34,     0,
      83,    71,    72,    73,    74,    75,    76,    77,     0,     0,
       0,    78,    79,    80,    81,    82,     0,     0,     0,    84,
      71,    72,    73,    74,    75,    76,    77,     0,     0,     0,
      78,    79,    80,    81,    82,    88,     0,     0,    85,    71,
      72,    73,    74,    75,    76,    77,     0,     0,     0,    78,
      79,    80,    81,    82,    71,    72,    73,    74,    75,    76,
      77,     0,     0,     0,    78,    79,    80,    81,    82,     0,
       0,     0,   112,    71,    72,    73,    74,    75,    76,    77,
       0,     0,    91,    78,    79,    80,    81,    82
};

static const yytype_int8 yycheck[] =
{
       4,    24,    25,    12,    10,     4,    29,     6,     4,    32,
       6,    63,    64,    43,    13,    43,    25,    26,    25,    26,
      27,    28,    29,    46,     3,    43,    30,    43,     0,    11,
      40,    43,    24,    39,    43,     4,     4,     4,     4,    23,
      43,    45,    43,    43,    66,    43,    43,    -1,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      66,    39,     1,    86,     3,     4,     5,     6,     7,     8,
       9,    10,    43,    43,    -1,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    88,    -1,    -1,    -1,     3,     4,
       5,     6,    -1,    -1,    33,     3,     4,     5,     6,    -1,
      -1,    -1,    41,    42,    43,    44,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    -1,    32,    33,     3,
       4,     5,     6,    -1,    -1,    33,    41,    42,    -1,    -1,
      -1,    -1,    -1,    41,    42,    25,    26,    27,    28,    29,
      30,    31,    25,    26,    27,    28,    29,    30,    31,    33,
      -1,    -1,    35,    36,    37,    38,    39,    41,    42,    -1,
      43,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    -1,    -1,    -1,    43,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      35,    36,    37,    38,    39,    21,    -1,    -1,    43,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    -1,    35,
      36,    37,    38,    39,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    -1,    35,    36,    37,    38,    39,    -1,
      -1,    -1,    43,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    34,    35,    36,    37,    38,    39
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,     7,     8,     9,    10,    43,    44,    47,
      57,    58,    59,    43,    43,    58,    43,    43,     0,     3,
       4,     5,     6,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    33,    41,    42,    48,    49,    50,    51,    52,
      53,    55,    56,    60,    11,    40,    32,    53,    54,    54,
      54,    43,     4,     4,    54,    58,     4,     6,    61,    54,
       4,     4,    12,    25,    26,    43,    24,    51,    43,    58,
      54,    25,    26,    27,    28,    29,    30,    31,    35,    36,
      37,    38,    39,    43,    43,    43,    23,    43,    21,    43,
      43,    34,    43,    61,    13,    61,    49,    43,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    58,    43,    43
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    48,    48,    48,    48,    49,    49,    50,    51,    51,
      52,    53,    53,    53,    53,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    55,
      56,    57,    57,    58,    59,    60,    60,    60,    60,    61,
      61
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     5,     2,     2,     3,     3,     4,     4,
       4,     4,     3,     4,     6,     4,     6,     4,     1,     1,
       2,     1,     3,     3,     3,     1,     3,     1,     1,     2,
       1,     1,     1,     1,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     3,     3,     3,     3,     2,
       2,     0,     1,     1,     1,     1,     1,     1,     1,     1,
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

#define YYBACKUP(Token, Value)                                    \
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
        yyerror (YY_("syntax error: cannot back up")); \
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
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
    case 3: /* NUMBER  */
#line 75 "src/mush.y"
            { free(((*yyvaluep).string)); }
#line 1226 "src/mush.tab.c"
        break;

    case 4: /* NAME  */
#line 76 "src/mush.y"
            { free(((*yyvaluep).string)); }
#line 1232 "src/mush.tab.c"
        break;

    case 5: /* WORD  */
#line 77 "src/mush.y"
            { free(((*yyvaluep).string)); }
#line 1238 "src/mush.tab.c"
        break;

    case 6: /* STRING  */
#line 78 "src/mush.y"
            { free(((*yyvaluep).string)); }
#line 1244 "src/mush.tab.c"
        break;

    case 47: /* statement  */
#line 80 "src/mush.y"
            { free_stmt(((*yyvaluep).stmt)); }
#line 1250 "src/mush.tab.c"
        break;

    case 48: /* pipeline  */
#line 86 "src/mush.y"
            { free_pipeline(((*yyvaluep).pline)); }
#line 1256 "src/mush.tab.c"
        break;

    case 49: /* command_list  */
#line 83 "src/mush.y"
            { free_commands(((*yyvaluep).cmds)); }
#line 1262 "src/mush.tab.c"
        break;

    case 50: /* command  */
#line 82 "src/mush.y"
            { free_commands(((*yyvaluep).cmds)); }
#line 1268 "src/mush.tab.c"
        break;

    case 51: /* arg_list  */
#line 85 "src/mush.y"
            { free_args(((*yyvaluep).args)); }
#line 1274 "src/mush.tab.c"
        break;

    case 52: /* arg  */
#line 84 "src/mush.y"
            { free(((*yyvaluep).expr)); }
#line 1280 "src/mush.tab.c"
        break;

    case 54: /* expr  */
#line 81 "src/mush.y"
            { free_expr(((*yyvaluep).expr)); }
#line 1286 "src/mush.tab.c"
        break;

    case 55: /* numeric_var  */
#line 89 "src/mush.y"
            { free(((*yyvaluep).string)); }
#line 1292 "src/mush.tab.c"
        break;

    case 56: /* string_var  */
#line 90 "src/mush.y"
            { free(((*yyvaluep).string)); }
#line 1298 "src/mush.tab.c"
        break;

    case 60: /* literal_string  */
#line 88 "src/mush.y"
            { free(((*yyvaluep).string)); }
#line 1304 "src/mush.tab.c"
        break;

    case 61: /* file  */
#line 87 "src/mush.y"
            { free(((*yyvaluep).string)); }
#line 1310 "src/mush.tab.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
      yychar = yylex ();
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
#line 96 "src/mush.y"
          {
	      (yyval.stmt) = calloc(1, sizeof(STMT));
	      (yyval.stmt)->class = LIST_STMT_CLASS;
	      mush_parsed_stmt = (yyval.stmt);
	      YYACCEPT;
	  }
#line 1585 "src/mush.tab.c"
    break;

  case 3:
#line 103 "src/mush.y"
          {
	      (yyval.stmt) = calloc(1, sizeof(STMT));
	      (yyval.stmt)->class = DELETE_STMT_CLASS;
	      (yyval.stmt)->members.delete_stmt.from = (yyvsp[-3].number);
	      (yyval.stmt)->members.delete_stmt.to = (yyvsp[-1].number);
	      mush_parsed_stmt = (yyval.stmt);
	      YYACCEPT;
	  }
#line 1598 "src/mush.tab.c"
    break;

  case 4:
#line 112 "src/mush.y"
          {
	      (yyval.stmt) = calloc(1, sizeof(STMT));
	      (yyval.stmt)->class = RUN_STMT_CLASS;
	      mush_parsed_stmt = (yyval.stmt);
	      YYACCEPT;
	  }
#line 1609 "src/mush.tab.c"
    break;

  case 5:
#line 119 "src/mush.y"
          {
	      (yyval.stmt) = calloc(1, sizeof(STMT));
	      (yyval.stmt)->class = CONT_STMT_CLASS;
	      mush_parsed_stmt = (yyval.stmt);
	      YYACCEPT;
	  }
#line 1620 "src/mush.tab.c"
    break;

  case 6:
#line 126 "src/mush.y"
          {
	      (yyval.stmt) = calloc(1, sizeof(STMT));
	      (yyval.stmt)->class = STOP_STMT_CLASS;
	      (yyval.stmt)->lineno = (yyvsp[-2].number);
	      mush_parsed_stmt = (yyval.stmt);
	      YYACCEPT;
	  }
#line 1632 "src/mush.tab.c"
    break;

  case 7:
#line 134 "src/mush.y"
          {
	      (yyval.stmt) = calloc(1, sizeof(STMT));
	      (yyval.stmt)->class = FG_STMT_CLASS;
	      (yyval.stmt)->lineno = (yyvsp[-2].number);
	      (yyval.stmt)->members.sys_stmt.pipeline = (yyvsp[-1].pline);
	      mush_parsed_stmt = (yyval.stmt);
	      YYACCEPT;
	  }
#line 1645 "src/mush.tab.c"
    break;

  case 8:
#line 143 "src/mush.y"
          {
	      (yyval.stmt) = calloc(1, sizeof(STMT));
	      (yyval.stmt)->class = BG_STMT_CLASS;
	      (yyval.stmt)->lineno = (yyvsp[-3].number);
	      (yyval.stmt)->members.sys_stmt.pipeline = (yyvsp[-2].pline);
	      mush_parsed_stmt = (yyval.stmt);
	      YYACCEPT;
	  }
#line 1658 "src/mush.tab.c"
    break;

  case 9:
#line 152 "src/mush.y"
          {
	      (yyval.stmt) = calloc(1, sizeof(STMT));
	      (yyval.stmt)->class = WAIT_STMT_CLASS;
	      (yyval.stmt)->lineno = (yyvsp[-3].number);
	      (yyval.stmt)->members.jobctl_stmt.expr = (yyvsp[-1].expr);
	      mush_parsed_stmt = (yyval.stmt);
	      YYACCEPT;
	  }
#line 1671 "src/mush.tab.c"
    break;

  case 10:
#line 161 "src/mush.y"
          {
	      (yyval.stmt) = calloc(1, sizeof(STMT));
	      (yyval.stmt)->class = POLL_STMT_CLASS;
	      (yyval.stmt)->lineno = (yyvsp[-3].number);
	      (yyval.stmt)->members.jobctl_stmt.expr = (yyvsp[-1].expr);
	      mush_parsed_stmt = (yyval.stmt);
	      YYACCEPT;
	  }
#line 1684 "src/mush.tab.c"
    break;

  case 11:
#line 170 "src/mush.y"
          {
	      (yyval.stmt) = calloc(1, sizeof(STMT));
	      (yyval.stmt)->class = CANCEL_STMT_CLASS;
	      (yyval.stmt)->lineno = (yyvsp[-3].number);
	      (yyval.stmt)->members.jobctl_stmt.expr = (yyvsp[-1].expr);
	      mush_parsed_stmt = (yyval.stmt);
	      YYACCEPT;
	  }
#line 1697 "src/mush.tab.c"
    break;

  case 12:
#line 179 "src/mush.y"
          {
	      (yyval.stmt) = calloc(1, sizeof(STMT));
	      (yyval.stmt)->class = PAUSE_STMT_CLASS;
	      (yyval.stmt)->lineno = (yyvsp[-2].number);
	      mush_parsed_stmt = (yyval.stmt);
	      YYACCEPT;
	  }
#line 1709 "src/mush.tab.c"
    break;

  case 13:
#line 187 "src/mush.y"
          {
	      (yyval.stmt) = calloc(1, sizeof(STMT));
	      (yyval.stmt)->class = GOTO_STMT_CLASS;
	      (yyval.stmt)->lineno = (yyvsp[-3].number);
	      (yyval.stmt)->members.goto_stmt.lineno = (yyvsp[-1].number);
	      mush_parsed_stmt = (yyval.stmt);
	      YYACCEPT;
	  }
#line 1722 "src/mush.tab.c"
    break;

  case 14:
#line 196 "src/mush.y"
          {
	      (yyval.stmt) = calloc(1, sizeof(STMT));
	      (yyval.stmt)->class = SET_STMT_CLASS;
	      (yyval.stmt)->lineno = (yyvsp[-5].number);
	      (yyval.stmt)->members.set_stmt.name = (yyvsp[-3].string);
	      (yyval.stmt)->members.set_stmt.expr = (yyvsp[-1].expr);
	      mush_parsed_stmt = (yyval.stmt);
	      YYACCEPT;
	  }
#line 1736 "src/mush.tab.c"
    break;

  case 15:
#line 206 "src/mush.y"
          {
	      (yyval.stmt) = calloc(1, sizeof(STMT));
	      (yyval.stmt)->class = UNSET_STMT_CLASS;
	      (yyval.stmt)->lineno = (yyvsp[-3].number);
	      (yyval.stmt)->members.unset_stmt.name = (yyvsp[-1].string);
	      mush_parsed_stmt = (yyval.stmt);
	      YYACCEPT;
	  }
#line 1749 "src/mush.tab.c"
    break;

  case 16:
#line 215 "src/mush.y"
          {
	      (yyval.stmt) = calloc(1, sizeof(STMT));
	      (yyval.stmt)->class = IF_STMT_CLASS;
	      (yyval.stmt)->lineno = (yyvsp[-5].number);
	      (yyval.stmt)->members.if_stmt.expr = (yyvsp[-3].expr);
	      (yyval.stmt)->members.if_stmt.lineno = (yyvsp[-1].number);
	      mush_parsed_stmt = (yyval.stmt);
	      YYACCEPT;
	  }
#line 1763 "src/mush.tab.c"
    break;

  case 17:
#line 225 "src/mush.y"
          {
	      (yyval.stmt) = calloc(1, sizeof(STMT));
	      (yyval.stmt)->class = SOURCE_STMT_CLASS;
	      (yyval.stmt)->lineno = (yyvsp[-3].number);
	      (yyval.stmt)->members.source_stmt.file = (yyvsp[-1].string);
	      mush_parsed_stmt = (yyval.stmt);
	      YYACCEPT;
	  }
#line 1776 "src/mush.tab.c"
    break;

  case 18:
#line 234 "src/mush.y"
          {
	      (yyval.stmt) = NULL;
	      mush_parsed_stmt = (yyval.stmt);
	      YYACCEPT;
	  }
#line 1786 "src/mush.tab.c"
    break;

  case 19:
#line 240 "src/mush.y"
          {
	      YYABORT;
	  }
#line 1794 "src/mush.tab.c"
    break;

  case 20:
#line 244 "src/mush.y"
          {
	      (yyval.stmt) = NULL;
	      mush_parsed_stmt = (yyval.stmt);
	      YYACCEPT;
	  }
#line 1804 "src/mush.tab.c"
    break;

  case 21:
#line 252 "src/mush.y"
          {
	      (yyval.pline) = calloc(1, sizeof(PIPELINE));
	      (yyval.pline)->commands = (yyvsp[0].cmds);
          }
#line 1813 "src/mush.tab.c"
    break;

  case 22:
#line 257 "src/mush.y"
          {
	      (yyval.pline) = (yyvsp[-2].pline);
	      (yyval.pline)->input_file = (yyvsp[0].string);
	  }
#line 1822 "src/mush.tab.c"
    break;

  case 23:
#line 262 "src/mush.y"
          {
	      (yyval.pline) = (yyvsp[-2].pline);
	      (yyval.pline)->output_file = (yyvsp[0].string);
	  }
#line 1831 "src/mush.tab.c"
    break;

  case 24:
#line 267 "src/mush.y"
          {
	      (yyval.pline) = (yyvsp[-2].pline);
	      (yyval.pline)->capture_output = 1;
	  }
#line 1840 "src/mush.tab.c"
    break;

  case 25:
#line 274 "src/mush.y"
          {
	      (yyval.cmds) = (yyvsp[0].cmds);
	  }
#line 1848 "src/mush.tab.c"
    break;

  case 26:
#line 278 "src/mush.y"
          {
	      (yyval.cmds) = (yyvsp[-2].cmds);
	      (yyval.cmds)->next = (yyvsp[0].cmds);
	  }
#line 1857 "src/mush.tab.c"
    break;

  case 27:
#line 285 "src/mush.y"
          {
	      (yyval.cmds) = calloc(1, sizeof(COMMAND));
	      (yyval.cmds)->args = (yyvsp[0].args);
	  }
#line 1866 "src/mush.tab.c"
    break;

  case 28:
#line 292 "src/mush.y"
          {
	      (yyval.args) = calloc(1, sizeof(ARG));
	      (yyval.args)->expr = (yyvsp[0].expr);
	  }
#line 1875 "src/mush.tab.c"
    break;

  case 29:
#line 297 "src/mush.y"
          {
	      (yyval.args) = calloc(1, sizeof(ARG));
	      (yyval.args)->expr = (yyvsp[-1].expr);
	      (yyval.args)->next = (yyvsp[0].args);
	  }
#line 1885 "src/mush.tab.c"
    break;

  case 30:
#line 305 "src/mush.y"
          {
	      (yyval.expr) = (yyvsp[0].expr);
	  }
#line 1893 "src/mush.tab.c"
    break;

  case 31:
#line 311 "src/mush.y"
          {
	      (yyval.expr) = calloc(1, sizeof(EXPR));
	      (yyval.expr)->class = LIT_EXPR_CLASS;
	      (yyval.expr)->type = STRING_VALUE_TYPE;
	      (yyval.expr)->members.value = (yyvsp[0].string);
	  }
#line 1904 "src/mush.tab.c"
    break;

  case 32:
#line 318 "src/mush.y"
          {
	      (yyval.expr) = calloc(1, sizeof(EXPR));
	      (yyval.expr)->class = NUM_EXPR_CLASS;
	      (yyval.expr)->type = NUM_VALUE_TYPE;
	      (yyval.expr)->members.variable = (yyvsp[0].string);
	  }
#line 1915 "src/mush.tab.c"
    break;

  case 33:
#line 325 "src/mush.y"
          {
	      (yyval.expr) = calloc(1, sizeof(EXPR));
	      (yyval.expr)->class = STRING_EXPR_CLASS;
	      (yyval.expr)->type = STRING_VALUE_TYPE;
	      (yyval.expr)->members.variable = (yyvsp[0].string);
	  }
#line 1926 "src/mush.tab.c"
    break;

  case 34:
#line 332 "src/mush.y"
          {
	      (yyval.expr) = (yyvsp[-1].expr);
	  }
#line 1934 "src/mush.tab.c"
    break;

  case 35:
#line 337 "src/mush.y"
          {
              (yyval.expr) = (yyvsp[0].expr);
          }
#line 1942 "src/mush.tab.c"
    break;

  case 36:
#line 341 "src/mush.y"
          {
	      (yyval.expr) = calloc(1, sizeof(EXPR));
	      (yyval.expr)->class = BINARY_EXPR_CLASS;
	      (yyval.expr)->type = NUM_VALUE_TYPE;
	      (yyval.expr)->members.binary_expr.oprtr = EQUAL_OPRTR;
	      (yyval.expr)->members.binary_expr.arg1 = (yyvsp[-2].expr);
	      (yyval.expr)->members.binary_expr.arg2 = (yyvsp[0].expr);
	  }
#line 1955 "src/mush.tab.c"
    break;

  case 37:
#line 350 "src/mush.y"
          {
	      (yyval.expr) = calloc(1, sizeof(EXPR));
	      (yyval.expr)->class = BINARY_EXPR_CLASS;
	      (yyval.expr)->type = NUM_VALUE_TYPE;
	      (yyval.expr)->members.binary_expr.oprtr = LESS_OPRTR;
	      (yyval.expr)->members.binary_expr.arg1 = (yyvsp[-2].expr);
	      (yyval.expr)->members.binary_expr.arg2 = (yyvsp[0].expr);
	  }
#line 1968 "src/mush.tab.c"
    break;

  case 38:
#line 359 "src/mush.y"
          {
	      (yyval.expr) = calloc(1, sizeof(EXPR));
	      (yyval.expr)->class = BINARY_EXPR_CLASS;
	      (yyval.expr)->type = NUM_VALUE_TYPE;
	      (yyval.expr)->members.binary_expr.oprtr = GREATER_OPRTR;
	      (yyval.expr)->members.binary_expr.arg1 = (yyvsp[-2].expr);
	      (yyval.expr)->members.binary_expr.arg2 = (yyvsp[0].expr);
	  }
#line 1981 "src/mush.tab.c"
    break;

  case 39:
#line 368 "src/mush.y"
          {
	      (yyval.expr) = calloc(1, sizeof(EXPR));
	      (yyval.expr)->class = BINARY_EXPR_CLASS;
	      (yyval.expr)->type = NUM_VALUE_TYPE;
	      (yyval.expr)->members.binary_expr.oprtr = LESSEQ_OPRTR;
	      (yyval.expr)->members.binary_expr.arg1 = (yyvsp[-2].expr);
	      (yyval.expr)->members.binary_expr.arg2 = (yyvsp[0].expr);
	  }
#line 1994 "src/mush.tab.c"
    break;

  case 40:
#line 377 "src/mush.y"
          {
	      (yyval.expr) = calloc(1, sizeof(EXPR));
	      (yyval.expr)->class = BINARY_EXPR_CLASS;
	      (yyval.expr)->type = NUM_VALUE_TYPE;
	      (yyval.expr)->members.binary_expr.oprtr = GREATEQ_OPRTR;
	      (yyval.expr)->members.binary_expr.arg1 = (yyvsp[-2].expr);
	      (yyval.expr)->members.binary_expr.arg2 = (yyvsp[0].expr);
	  }
#line 2007 "src/mush.tab.c"
    break;

  case 41:
#line 386 "src/mush.y"
          {
	      (yyval.expr) = calloc(1, sizeof(EXPR));
	      (yyval.expr)->class = BINARY_EXPR_CLASS;
	      (yyval.expr)->type = NUM_VALUE_TYPE;
	      (yyval.expr)->members.binary_expr.oprtr = AND_OPRTR;
	      (yyval.expr)->members.binary_expr.arg1 = (yyvsp[-2].expr);
	      (yyval.expr)->members.binary_expr.arg2 = (yyvsp[0].expr);
	  }
#line 2020 "src/mush.tab.c"
    break;

  case 42:
#line 395 "src/mush.y"
          {
	      (yyval.expr) = calloc(1, sizeof(EXPR));
	      (yyval.expr)->class = BINARY_EXPR_CLASS;
	      (yyval.expr)->type = NUM_VALUE_TYPE;
	      (yyval.expr)->members.binary_expr.oprtr = OR_OPRTR;
	      (yyval.expr)->members.binary_expr.arg1 = (yyvsp[-2].expr);
	      (yyval.expr)->members.binary_expr.arg2 = (yyvsp[0].expr);
	  }
#line 2033 "src/mush.tab.c"
    break;

  case 43:
#line 404 "src/mush.y"
          {
	      (yyval.expr) = calloc(1, sizeof(EXPR));
	      (yyval.expr)->class = UNARY_EXPR_CLASS;
	      (yyval.expr)->type = NUM_VALUE_TYPE;
	      (yyval.expr)->members.unary_expr.oprtr = NOT_OPRTR;
	      (yyval.expr)->members.unary_expr.arg = (yyvsp[0].expr);
	  }
#line 2045 "src/mush.tab.c"
    break;

  case 44:
#line 412 "src/mush.y"
          {
	      (yyval.expr) = calloc(1, sizeof(EXPR));
	      (yyval.expr)->class = BINARY_EXPR_CLASS;
	      (yyval.expr)->type = NUM_VALUE_TYPE;
	      (yyval.expr)->members.binary_expr.arg1 = (yyvsp[-2].expr);
	      (yyval.expr)->members.binary_expr.oprtr = PLUS_OPRTR;
	      (yyval.expr)->members.binary_expr.arg2 = (yyvsp[0].expr);
	  }
#line 2058 "src/mush.tab.c"
    break;

  case 45:
#line 421 "src/mush.y"
          {
	      (yyval.expr) = calloc(1, sizeof(EXPR));
	      (yyval.expr)->class = BINARY_EXPR_CLASS;
	      (yyval.expr)->type = NUM_VALUE_TYPE;
	      (yyval.expr)->members.binary_expr.arg1 = (yyvsp[-2].expr);
	      (yyval.expr)->members.binary_expr.oprtr = MINUS_OPRTR;
	      (yyval.expr)->members.binary_expr.arg2 = (yyvsp[0].expr);
	  }
#line 2071 "src/mush.tab.c"
    break;

  case 46:
#line 430 "src/mush.y"
          {
	      (yyval.expr) = calloc(1, sizeof(EXPR));
	      (yyval.expr)->class = BINARY_EXPR_CLASS;
	      (yyval.expr)->type = NUM_VALUE_TYPE;
	      (yyval.expr)->members.binary_expr.arg1 = (yyvsp[-2].expr);
	      (yyval.expr)->members.binary_expr.oprtr = TIMES_OPRTR;
	      (yyval.expr)->members.binary_expr.arg2 = (yyvsp[0].expr);
	  }
#line 2084 "src/mush.tab.c"
    break;

  case 47:
#line 439 "src/mush.y"
          {
	      (yyval.expr) = calloc(1, sizeof(EXPR));
	      (yyval.expr)->class = BINARY_EXPR_CLASS;
	      (yyval.expr)->type = NUM_VALUE_TYPE;
	      (yyval.expr)->members.binary_expr.arg1 = (yyvsp[-2].expr);
	      (yyval.expr)->members.binary_expr.oprtr = DIVIDE_OPRTR;
	      (yyval.expr)->members.binary_expr.arg2 = (yyvsp[0].expr);
	  }
#line 2097 "src/mush.tab.c"
    break;

  case 48:
#line 448 "src/mush.y"
          {
	      (yyval.expr) = calloc(1, sizeof(EXPR));
	      (yyval.expr)->class = BINARY_EXPR_CLASS;
	      (yyval.expr)->type = NUM_VALUE_TYPE;
	      (yyval.expr)->members.binary_expr.arg1 = (yyvsp[-2].expr);
	      (yyval.expr)->members.binary_expr.oprtr = MOD_OPRTR;
	      (yyval.expr)->members.binary_expr.arg2 = (yyvsp[0].expr);
	  }
#line 2110 "src/mush.tab.c"
    break;

  case 49:
#line 459 "src/mush.y"
          { (yyval.string) = (yyvsp[0].string); }
#line 2116 "src/mush.tab.c"
    break;

  case 50:
#line 463 "src/mush.y"
          { (yyval.string) = (yyvsp[0].string); }
#line 2122 "src/mush.tab.c"
    break;

  case 51:
#line 466 "src/mush.y"
          { (yyval.number) = 0; }
#line 2128 "src/mush.tab.c"
    break;

  case 52:
#line 468 "src/mush.y"
          {
	      if((yyvsp[0].number) <= 0) {
		  yyerror("Line number must be positive");
		  YYERROR;
	      }
	      (yyval.number) = (yyvsp[0].number);
	  }
#line 2140 "src/mush.tab.c"
    break;

  case 54:
#line 480 "src/mush.y"
               { (yyval.number) = atoi((yyvsp[0].string)); free((yyvsp[0].string)); }
#line 2146 "src/mush.tab.c"
    break;

  case 55:
#line 483 "src/mush.y"
               { (yyval.string) = (yyvsp[0].string); }
#line 2152 "src/mush.tab.c"
    break;

  case 56:
#line 484 "src/mush.y"
             { (yyval.string) = (yyvsp[0].string); }
#line 2158 "src/mush.tab.c"
    break;

  case 57:
#line 485 "src/mush.y"
             { (yyval.string) = (yyvsp[0].string); }
#line 2164 "src/mush.tab.c"
    break;

  case 58:
#line 486 "src/mush.y"
               { (yyval.string) = (yyvsp[0].string); }
#line 2170 "src/mush.tab.c"
    break;

  case 59:
#line 489 "src/mush.y"
             { (yyval.string) = (yyvsp[0].string); }
#line 2176 "src/mush.tab.c"
    break;

  case 60:
#line 490 "src/mush.y"
               { (yyval.string) = (yyvsp[0].string); }
#line 2182 "src/mush.tab.c"
    break;


#line 2186 "src/mush.tab.c"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
      yyerror (YY_("syntax error"));
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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
        yyerror (yymsgp);
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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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
                  yystos[yystate], yyvsp);
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
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
#line 492 "src/mush.y"

