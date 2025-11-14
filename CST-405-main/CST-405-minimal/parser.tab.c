/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* externs from scanner / main */
extern int yylex();
extern FILE* yyin;
extern char* yytext;

/* Optional: define this in main.c as:
   const char* g_input_filename = NULL;
   and set it before yyparse(): g_input_filename = argv[1]; */
extern const char* g_input_filename;

void yyerror(const char* msg);

ASTNode* root = NULL;   /* Root of the Abstract Syntax Tree */

#line 92 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM = 3,                        /* NUM  */
  YYSYMBOL_FLOAT_LIT = 4,                  /* FLOAT_LIT  */
  YYSYMBOL_ID = 5,                         /* ID  */
  YYSYMBOL_INT = 6,                        /* INT  */
  YYSYMBOL_FLOAT = 7,                      /* FLOAT  */
  YYSYMBOL_BOOL = 8,                       /* BOOL  */
  YYSYMBOL_PRINT = 9,                      /* PRINT  */
  YYSYMBOL_WRITE = 10,                     /* WRITE  */
  YYSYMBOL_WRITELN = 11,                   /* WRITELN  */
  YYSYMBOL_RETURN = 12,                    /* RETURN  */
  YYSYMBOL_VOID = 13,                      /* VOID  */
  YYSYMBOL_IF = 14,                        /* IF  */
  YYSYMBOL_ELSE = 15,                      /* ELSE  */
  YYSYMBOL_WHILE = 16,                     /* WHILE  */
  YYSYMBOL_RACE = 17,                      /* RACE  */
  YYSYMBOL_FIRSTWINS = 18,                 /* FIRSTWINS  */
  YYSYMBOL_BAR = 19,                       /* BAR  */
  YYSYMBOL_BOOL_LIT = 20,                  /* BOOL_LIT  */
  YYSYMBOL_CHAR = 21,                      /* CHAR  */
  YYSYMBOL_GT = 22,                        /* GT  */
  YYSYMBOL_LT = 23,                        /* LT  */
  YYSYMBOL_GE = 24,                        /* GE  */
  YYSYMBOL_LE = 25,                        /* LE  */
  YYSYMBOL_EQ = 26,                        /* EQ  */
  YYSYMBOL_NE = 27,                        /* NE  */
  YYSYMBOL_AND = 28,                       /* AND  */
  YYSYMBOL_OR = 29,                        /* OR  */
  YYSYMBOL_NOT = 30,                       /* NOT  */
  YYSYMBOL_MUL = 31,                       /* MUL  */
  YYSYMBOL_DIV = 32,                       /* DIV  */
  YYSYMBOL_33_ = 33,                       /* '+'  */
  YYSYMBOL_34_ = 34,                       /* '-'  */
  YYSYMBOL_IFX = 35,                       /* IFX  */
  YYSYMBOL_36_ = 36,                       /* '('  */
  YYSYMBOL_37_ = 37,                       /* ')'  */
  YYSYMBOL_38_ = 38,                       /* '{'  */
  YYSYMBOL_39_ = 39,                       /* '}'  */
  YYSYMBOL_40_ = 40,                       /* ','  */
  YYSYMBOL_41_ = 41,                       /* ';'  */
  YYSYMBOL_42_ = 42,                       /* '['  */
  YYSYMBOL_43_ = 43,                       /* ']'  */
  YYSYMBOL_44_ = 44,                       /* '='  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_program = 46,                   /* program  */
  YYSYMBOL_func_list = 47,                 /* func_list  */
  YYSYMBOL_func_decl = 48,                 /* func_decl  */
  YYSYMBOL_type = 49,                      /* type  */
  YYSYMBOL_param_list = 50,                /* param_list  */
  YYSYMBOL_param = 51,                     /* param  */
  YYSYMBOL_stmt_list = 52,                 /* stmt_list  */
  YYSYMBOL_stmt = 53,                      /* stmt  */
  YYSYMBOL_if_stmt = 54,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 55,                /* while_stmt  */
  YYSYMBOL_race_stmt = 56,                 /* race_stmt  */
  YYSYMBOL_id_list = 57,                   /* id_list  */
  YYSYMBOL_decl = 58,                      /* decl  */
  YYSYMBOL_arr_decl = 59,                  /* arr_decl  */
  YYSYMBOL_arr2d_decl = 60,                /* arr2d_decl  */
  YYSYMBOL_assign = 61,                    /* assign  */
  YYSYMBOL_arr_assign = 62,                /* arr_assign  */
  YYSYMBOL_arr2d_assign = 63,              /* arr2d_assign  */
  YYSYMBOL_return_stmt = 64,               /* return_stmt  */
  YYSYMBOL_expr = 65,                      /* expr  */
  YYSYMBOL_arg_list = 66,                  /* arg_list  */
  YYSYMBOL_print_stmt = 67,                /* print_stmt  */
  YYSYMBOL_write_stmt = 68,                /* write_stmt  */
  YYSYMBOL_writeln_stmt = 69               /* writeln_stmt  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_uint8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   504

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  159

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   288


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      36,    37,     2,    33,    40,    34,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    41,
       2,    44,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    42,     2,    43,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    39,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    35
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    80,    80,    84,    85,    92,    96,   103,   104,   105,
     106,   113,   114,   118,   125,   126,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   154,   156,   164,   172,   180,   181,   185,   190,   195,
     205,   210,   216,   224,   225,   233,   234,   235,   236,   237,
     238,   241,   242,   245,   246,   247,   248,   251,   252,   253,
     254,   255,   256,   259,   260,   261,   264,   265,   269,   270,
     274,   278,   281
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "NUM", "FLOAT_LIT", "ID",
  "INT", "FLOAT", "BOOL", "PRINT", "WRITE", "WRITELN", "RETURN", "VOID",
  "IF", "ELSE", "WHILE", "RACE", "FIRSTWINS", "BAR", "BOOL_LIT", "CHAR",
  "GT", "LT", "GE", "LE", "EQ", "NE", "AND", "OR", "NOT", "MUL", "DIV",
  "'+'", "'-'", "IFX", "'('", "')'", "'{'", "'}'", "','", "';'", "'['",
  "']'", "'='", "$accept", "program", "func_list", "func_decl", "type",
  "param_list", "param", "stmt_list", "stmt", "if_stmt", "while_stmt",
  "race_stmt", "id_list", "decl", "arr_decl", "arr2d_decl", "assign",
  "arr_assign", "arr2d_assign", "return_stmt", "expr", "arg_list",
  "print_stmt", "write_stmt", "writeln_stmt", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#define YYPACT_NINF (-40)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      55,   -40,   -40,   -40,   -40,    16,    55,   -40,    34,   -40,
     -40,   -15,    19,    22,    71,   -34,   -40,   241,   -40,    39,
      55,   -27,    42,    43,    40,    54,    46,    47,    56,   109,
      80,   122,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,
     -40,   -40,   -40,   -40,   -40,   -40,   241,   -40,   256,   256,
     256,   256,   -40,   -40,   -40,   -29,   -40,   -40,   256,   256,
     -40,   310,   256,   256,   241,   -40,   157,    57,   -36,   -40,
     -40,   170,   240,   330,   390,   406,    50,   256,   166,   422,
     256,   256,   256,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   -40,   438,   454,   218,   -40,    94,    93,   -40,
     -40,    23,   -40,    59,    60,   -40,   470,    29,   271,   -40,
      -3,    -3,    -3,    -3,    -3,    -3,   166,   118,   -40,   -40,
      41,    41,   241,   241,   241,    61,   -40,   256,   256,   -40,
     -40,   -40,   256,    64,    88,   -40,   205,    -8,   284,   350,
     470,   256,   241,    89,   -40,   105,    65,   -40,   297,   -40,
      69,    81,   256,   -40,   -40,    96,   370,   -40,   -40
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     7,     8,     9,    10,     0,     2,     3,     0,     1,
       4,     0,     0,     0,     0,     0,    11,     0,    13,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    14,    26,    27,    28,    16,    21,    23,    17,
      22,    24,    25,    18,    19,    20,     0,    12,     0,     0,
       0,     0,    72,    45,    46,    49,    47,    48,     0,     0,
      44,     0,     0,     0,     0,    30,     0,    35,     0,     6,
      15,     0,     0,     0,     0,     0,     0,     0,    65,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    43,     0,     0,     0,    29,     0,     0,    37,
       5,     0,    40,     0,     0,    67,    68,     0,     0,    50,
      57,    58,    59,    60,    61,    62,    63,    64,    55,    56,
      53,    54,     0,     0,     0,     0,    36,     0,     0,    70,
      71,    66,     0,    51,    31,    33,     0,     0,     0,     0,
      69,     0,     0,     0,    38,     0,     0,    41,     0,    32,
       0,     0,     0,    52,    34,     0,     0,    39,    42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -40,   -40,   -40,   106,     2,   -40,   133,   -28,   -31,   -40,
     -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,
     -39,   -40,   -40,   -40,   -40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,    30,    15,    16,    31,    32,    33,
      34,    35,    68,    36,    37,    38,    39,    40,    41,    42,
      61,   107,    43,    44,    45
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      70,    66,     8,    19,    98,    99,    20,    76,     8,    72,
      73,    74,    75,    77,    14,    48,     9,    49,    71,    78,
      79,    12,    14,    93,    94,     1,     2,     3,    88,    89,
      90,    91,     4,   144,   145,    70,    95,   106,   108,    11,
      70,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,    53,    54,    55,    13,    53,    54,    55,
      17,     1,     2,     3,    70,   127,   131,   128,     4,   132,
      56,    57,    88,    89,    56,    57,    18,    46,    50,    51,
      58,    52,    62,    63,    58,    67,    59,   105,   138,   139,
      59,   134,   135,   140,    64,    60,   136,   125,   126,    97,
     129,   130,   148,   142,   137,    70,   141,   150,   151,   152,
     154,   149,    10,   156,    21,     1,     2,     3,    22,    23,
      24,    25,     4,    26,   155,    27,    28,    21,     1,     2,
       3,    22,    23,    24,    25,     4,    26,   157,    27,    28,
      80,    81,    82,    83,    84,    85,    86,    29,    65,    88,
      89,    90,    91,    47,     0,     0,     0,     0,     0,     0,
      29,    69,    21,     1,     2,     3,    22,    23,    24,    25,
       4,    26,     0,    27,    28,    21,     1,     2,     3,    22,
      23,    24,    25,     4,    26,     0,    27,    28,    80,    81,
      82,    83,    84,    85,     0,    29,    96,    88,    89,    90,
      91,     0,     0,     0,     0,     0,     0,     0,    29,   100,
      21,     1,     2,     3,    22,    23,    24,    25,     4,    26,
       0,    27,    28,    21,     1,     2,     3,    22,    23,    24,
      25,     4,    26,     0,    27,    28,     0,   124,     0,     0,
       0,     0,     0,    29,   143,     0,    21,     1,     2,     3,
      22,    23,    24,    25,     4,    26,    29,    27,    28,    53,
      54,    55,    80,    81,    82,    83,    84,    85,    86,    87,
       0,    88,    89,    90,    91,     0,    56,    57,     0,    29,
       0,     0,     0,   101,     0,     0,    58,     0,     0,     0,
       0,     0,    59,    80,    81,    82,    83,    84,    85,    86,
      87,     0,    88,    89,    90,    91,    80,    81,    82,    83,
      84,    85,    86,    87,   133,    88,    89,    90,    91,    80,
      81,    82,    83,    84,    85,    86,    87,   146,    88,    89,
      90,    91,    80,    81,    82,    83,    84,    85,    86,    87,
     153,    88,    89,    90,    91,     0,     0,     0,     0,     0,
       0,    92,    80,    81,    82,    83,    84,    85,    86,    87,
       0,    88,    89,    90,    91,     0,     0,     0,     0,     0,
       0,   102,    80,    81,    82,    83,    84,    85,    86,    87,
       0,    88,    89,    90,    91,     0,     0,     0,     0,     0,
       0,   147,    80,    81,    82,    83,    84,    85,    86,    87,
       0,    88,    89,    90,    91,     0,     0,     0,     0,     0,
       0,   158,    80,    81,    82,    83,    84,    85,    86,    87,
       0,    88,    89,    90,    91,     0,     0,   103,    80,    81,
      82,    83,    84,    85,    86,    87,     0,    88,    89,    90,
      91,     0,     0,   104,    80,    81,    82,    83,    84,    85,
      86,    87,     0,    88,    89,    90,    91,     0,     0,   109,
      80,    81,    82,    83,    84,    85,    86,    87,     0,    88,
      89,    90,    91,     0,     0,   122,    80,    81,    82,    83,
      84,    85,    86,    87,     0,    88,    89,    90,    91,     0,
       0,   123,    80,    81,    82,    83,    84,    85,    86,    87,
       0,    88,    89,    90,    91
};

static const yytype_int16 yycheck[] =
{
      31,    29,     0,    37,    40,    41,    40,    36,     6,    48,
      49,    50,    51,    42,    12,    42,     0,    44,    46,    58,
      59,    36,    20,    62,    63,     6,     7,     8,    31,    32,
      33,    34,    13,    41,    42,    66,    64,    76,    77,     5,
      71,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,     3,     4,     5,    37,     3,     4,     5,
      38,     6,     7,     8,    95,    42,    37,    44,    13,    40,
      20,    21,    31,    32,    20,    21,     5,    38,    36,    36,
      30,    41,    36,    36,    30,     5,    36,    37,   127,   128,
      36,   122,   123,   132,    38,    41,   124,     3,     5,    42,
      41,    41,   141,    15,    43,   136,    42,    18,     3,    44,
      41,   142,     6,   152,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    43,    16,    17,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    41,    16,    17,
      22,    23,    24,    25,    26,    27,    28,    38,    39,    31,
      32,    33,    34,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    -1,    16,    17,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    -1,    16,    17,    22,    23,
      24,    25,    26,    27,    -1,    38,    39,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      -1,    16,    17,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    -1,    16,    17,    -1,    19,    -1,    -1,
      -1,    -1,    -1,    38,    39,    -1,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    38,    16,    17,     3,
       4,     5,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    31,    32,    33,    34,    -1,    20,    21,    -1,    38,
      -1,    -1,    -1,    43,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    36,    22,    23,    24,    25,    26,    27,    28,
      29,    -1,    31,    32,    33,    34,    22,    23,    24,    25,
      26,    27,    28,    29,    43,    31,    32,    33,    34,    22,
      23,    24,    25,    26,    27,    28,    29,    43,    31,    32,
      33,    34,    22,    23,    24,    25,    26,    27,    28,    29,
      43,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    31,    32,    33,    34,    -1,    -1,    37,    22,    23,
      24,    25,    26,    27,    28,    29,    -1,    31,    32,    33,
      34,    -1,    -1,    37,    22,    23,    24,    25,    26,    27,
      28,    29,    -1,    31,    32,    33,    34,    -1,    -1,    37,
      22,    23,    24,    25,    26,    27,    28,    29,    -1,    31,
      32,    33,    34,    -1,    -1,    37,    22,    23,    24,    25,
      26,    27,    28,    29,    -1,    31,    32,    33,    34,    -1,
      -1,    37,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    31,    32,    33,    34
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,     7,     8,    13,    46,    47,    48,    49,     0,
      48,     5,    36,    37,    49,    50,    51,    38,     5,    37,
      40,     5,     9,    10,    11,    12,    14,    16,    17,    38,
      49,    52,    53,    54,    55,    56,    58,    59,    60,    61,
      62,    63,    64,    67,    68,    69,    38,    51,    42,    44,
      36,    36,    41,     3,     4,     5,    20,    21,    30,    36,
      41,    65,    36,    36,    38,    39,    52,     5,    57,    39,
      53,    52,    65,    65,    65,    65,    36,    42,    65,    65,
      22,    23,    24,    25,    26,    27,    28,    29,    31,    32,
      33,    34,    41,    65,    65,    52,    39,    42,    40,    41,
      39,    43,    41,    37,    37,    37,    65,    66,    65,    37,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    37,    37,    19,     3,     5,    42,    44,    41,
      41,    37,    40,    43,    53,    53,    52,    43,    65,    65,
      65,    42,    15,    39,    41,    42,    43,    41,    65,    53,
      18,     3,    44,    43,    41,    43,    65,    41,    41
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    49,    49,    49,
      49,    50,    50,    51,    52,    52,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    54,    54,    55,    56,    57,    57,    58,    59,    60,
      61,    62,    63,    64,    64,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    66,    66,
      67,    68,    69
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     8,     7,     1,     1,     1,
       1,     1,     3,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     5,     7,     5,     8,     1,     3,     3,     6,     9,
       4,     7,    10,     3,     2,     1,     1,     1,     1,     1,
       3,     4,     7,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     4,     3,     1,     3,
       5,     5,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif



static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yystrlen (yysymbol_name (yyarg[yyi]));
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp = yystpcpy (yyp, yysymbol_name (yyarg[yyi++]));
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


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: func_list  */
#line 80 "parser.y"
              { root = (yyvsp[0].node); }
#line 1650 "parser.tab.c"
    break;

  case 3: /* func_list: func_decl  */
#line 84 "parser.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 1656 "parser.tab.c"
    break;

  case 4: /* func_list: func_list func_decl  */
#line 85 "parser.y"
                             { (yyval.node) = createFuncList((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1662 "parser.tab.c"
    break;

  case 5: /* func_decl: type ID '(' param_list ')' '{' stmt_list '}'  */
#line 92 "parser.y"
                                                 {
        (yyval.node) = createFuncDecl((yyvsp[-7].str), (yyvsp[-6].str), (yyvsp[-4].node), (yyvsp[-1].node));
        free((yyvsp[-6].str));
    }
#line 1671 "parser.tab.c"
    break;

  case 6: /* func_decl: type ID '(' ')' '{' stmt_list '}'  */
#line 96 "parser.y"
                                      {
        (yyval.node) = createFuncDecl((yyvsp[-6].str), (yyvsp[-5].str), NULL, (yyvsp[-1].node));
        free((yyvsp[-5].str));
    }
#line 1680 "parser.tab.c"
    break;

  case 7: /* type: INT  */
#line 103 "parser.y"
          { (yyval.str) = "int"; }
#line 1686 "parser.tab.c"
    break;

  case 8: /* type: FLOAT  */
#line 104 "parser.y"
          { (yyval.str) = "float"; }
#line 1692 "parser.tab.c"
    break;

  case 9: /* type: BOOL  */
#line 105 "parser.y"
          { (yyval.str) = "bool"; }
#line 1698 "parser.tab.c"
    break;

  case 10: /* type: VOID  */
#line 106 "parser.y"
          { (yyval.str) = "void"; }
#line 1704 "parser.tab.c"
    break;

  case 11: /* param_list: param  */
#line 113 "parser.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 1710 "parser.tab.c"
    break;

  case 12: /* param_list: param_list ',' param  */
#line 114 "parser.y"
                             { (yyval.node) = createParamList((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1716 "parser.tab.c"
    break;

  case 13: /* param: type ID  */
#line 118 "parser.y"
                             { (yyval.node) = createParam((yyvsp[-1].str), (yyvsp[0].str)); free((yyvsp[0].str)); }
#line 1722 "parser.tab.c"
    break;

  case 14: /* stmt_list: stmt  */
#line 125 "parser.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 1728 "parser.tab.c"
    break;

  case 15: /* stmt_list: stmt_list stmt  */
#line 126 "parser.y"
                             { (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1734 "parser.tab.c"
    break;

  case 29: /* stmt: '{' stmt_list '}'  */
#line 146 "parser.y"
                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1740 "parser.tab.c"
    break;

  case 30: /* stmt: '{' '}'  */
#line 147 "parser.y"
                                    { (yyval.node) = NULL; }
#line 1746 "parser.tab.c"
    break;

  case 31: /* if_stmt: IF '(' expr ')' stmt  */
#line 155 "parser.y"
        { (yyval.node) = createIf((yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 1752 "parser.tab.c"
    break;

  case 32: /* if_stmt: IF '(' expr ')' stmt ELSE stmt  */
#line 157 "parser.y"
        { (yyval.node) = createIf((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1758 "parser.tab.c"
    break;

  case 33: /* while_stmt: WHILE '(' expr ')' stmt  */
#line 165 "parser.y"
        { (yyval.node) = createWhile((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1764 "parser.tab.c"
    break;

  case 34: /* race_stmt: RACE '{' stmt_list BAR stmt_list '}' FIRSTWINS ';'  */
#line 173 "parser.y"
        { (yyval.node) = createRace((yyvsp[-5].node), (yyvsp[-3].node)); }
#line 1770 "parser.tab.c"
    break;

  case 35: /* id_list: ID  */
#line 180 "parser.y"
                            { (yyval.node) = createDecl((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 1776 "parser.tab.c"
    break;

  case 36: /* id_list: id_list ',' ID  */
#line 181 "parser.y"
                            { (yyval.node) = createDeclList((yyvsp[-2].node), createDecl((yyvsp[0].str))); free((yyvsp[0].str)); }
#line 1782 "parser.tab.c"
    break;

  case 37: /* decl: type id_list ';'  */
#line 185 "parser.y"
                            { (yyval.node) = (yyvsp[-1].node); }
#line 1788 "parser.tab.c"
    break;

  case 38: /* arr_decl: type ID '[' NUM ']' ';'  */
#line 190 "parser.y"
                             { (yyval.node) = createArrayDecl((yyvsp[-4].str), (yyvsp[-2].num)); free((yyvsp[-4].str)); }
#line 1794 "parser.tab.c"
    break;

  case 39: /* arr2d_decl: type ID '[' NUM ']' '[' NUM ']' ';'  */
#line 195 "parser.y"
                                        {
        (yyval.node) = createArray2DDecl((yyvsp[-7].str), (yyvsp[-5].num), (yyvsp[-2].num));
        free((yyvsp[-7].str));
    }
#line 1803 "parser.tab.c"
    break;

  case 40: /* assign: ID '=' expr ';'  */
#line 205 "parser.y"
                            { (yyval.node) = createAssign((yyvsp[-3].str), (yyvsp[-1].node)); free((yyvsp[-3].str)); }
#line 1809 "parser.tab.c"
    break;

  case 41: /* arr_assign: ID '[' expr ']' '=' expr ';'  */
#line 211 "parser.y"
        { (yyval.node) = createArrayAssign((yyvsp[-6].str), (yyvsp[-4].node), (yyvsp[-1].node)); free((yyvsp[-6].str)); }
#line 1815 "parser.tab.c"
    break;

  case 42: /* arr2d_assign: ID '[' expr ']' '[' expr ']' '=' expr ';'  */
#line 217 "parser.y"
        { (yyval.node) = createArray2DAssign((yyvsp[-9].str), (yyvsp[-7].node), (yyvsp[-4].node), (yyvsp[-1].node)); free((yyvsp[-9].str)); }
#line 1821 "parser.tab.c"
    break;

  case 43: /* return_stmt: RETURN expr ';'  */
#line 224 "parser.y"
                            { (yyval.node) = createReturn((yyvsp[-1].node)); }
#line 1827 "parser.tab.c"
    break;

  case 44: /* return_stmt: RETURN ';'  */
#line 225 "parser.y"
                            { (yyval.node) = createReturn(NULL); }
#line 1833 "parser.tab.c"
    break;

  case 45: /* expr: NUM  */
#line 233 "parser.y"
                                  { (yyval.node) = createNum((yyvsp[0].num)); }
#line 1839 "parser.tab.c"
    break;

  case 46: /* expr: FLOAT_LIT  */
#line 234 "parser.y"
                                  { (yyval.node) = createFloatNode((yyvsp[0].fnum)); }
#line 1845 "parser.tab.c"
    break;

  case 47: /* expr: BOOL_LIT  */
#line 235 "parser.y"
                                  { (yyval.node) = createBoolNode((yyvsp[0].num)); }
#line 1851 "parser.tab.c"
    break;

  case 48: /* expr: CHAR  */
#line 236 "parser.y"
                                  { (yyval.node) = createCharNode((yyvsp[0].num)); }
#line 1857 "parser.tab.c"
    break;

  case 49: /* expr: ID  */
#line 237 "parser.y"
                                  { (yyval.node) = createVar((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 1863 "parser.tab.c"
    break;

  case 50: /* expr: '(' expr ')'  */
#line 238 "parser.y"
                                  { (yyval.node) = (yyvsp[-1].node); }
#line 1869 "parser.tab.c"
    break;

  case 51: /* expr: ID '[' expr ']'  */
#line 241 "parser.y"
                                  { (yyval.node) = createArrayAccess((yyvsp[-3].str), (yyvsp[-1].node)); free((yyvsp[-3].str)); }
#line 1875 "parser.tab.c"
    break;

  case 52: /* expr: ID '[' expr ']' '[' expr ']'  */
#line 242 "parser.y"
                                  { (yyval.node) = createArray2DAccess((yyvsp[-6].str), (yyvsp[-4].node), (yyvsp[-1].node)); free((yyvsp[-6].str)); }
#line 1881 "parser.tab.c"
    break;

  case 53: /* expr: expr '+' expr  */
#line 245 "parser.y"
                                  { (yyval.node) = createBinOp('+', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1887 "parser.tab.c"
    break;

  case 54: /* expr: expr '-' expr  */
#line 246 "parser.y"
                                  { (yyval.node) = createBinOp('-', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1893 "parser.tab.c"
    break;

  case 55: /* expr: expr MUL expr  */
#line 247 "parser.y"
                                  { (yyval.node) = createBinOp('*', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1899 "parser.tab.c"
    break;

  case 56: /* expr: expr DIV expr  */
#line 248 "parser.y"
                                  { (yyval.node) = createBinOp('/', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1905 "parser.tab.c"
    break;

  case 57: /* expr: expr GT expr  */
#line 251 "parser.y"
                                  { (yyval.node) = createBinOp('>', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1911 "parser.tab.c"
    break;

  case 58: /* expr: expr LT expr  */
#line 252 "parser.y"
                                  { (yyval.node) = createBinOp('<', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1917 "parser.tab.c"
    break;

  case 59: /* expr: expr GE expr  */
#line 253 "parser.y"
                                  { (yyval.node) = createBinOp('G', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1923 "parser.tab.c"
    break;

  case 60: /* expr: expr LE expr  */
#line 254 "parser.y"
                                  { (yyval.node) = createBinOp('L', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1929 "parser.tab.c"
    break;

  case 61: /* expr: expr EQ expr  */
#line 255 "parser.y"
                                  { (yyval.node) = createBinOp('E', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1935 "parser.tab.c"
    break;

  case 62: /* expr: expr NE expr  */
#line 256 "parser.y"
                                  { (yyval.node) = createBinOp('N', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1941 "parser.tab.c"
    break;

  case 63: /* expr: expr AND expr  */
#line 259 "parser.y"
                                  { (yyval.node) = createBinOp('&', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1947 "parser.tab.c"
    break;

  case 64: /* expr: expr OR expr  */
#line 260 "parser.y"
                                  { (yyval.node) = createBinOp('|', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1953 "parser.tab.c"
    break;

  case 65: /* expr: NOT expr  */
#line 261 "parser.y"
                                  { (yyval.node) = createUnaryOp('!', (yyvsp[0].node)); }
#line 1959 "parser.tab.c"
    break;

  case 66: /* expr: ID '(' arg_list ')'  */
#line 264 "parser.y"
                                  { (yyval.node) = createFuncCall((yyvsp[-3].str), (yyvsp[-1].node)); free((yyvsp[-3].str)); }
#line 1965 "parser.tab.c"
    break;

  case 67: /* expr: ID '(' ')'  */
#line 265 "parser.y"
                                  { (yyval.node) = createFuncCall((yyvsp[-2].str), NULL); free((yyvsp[-2].str)); }
#line 1971 "parser.tab.c"
    break;

  case 68: /* arg_list: expr  */
#line 269 "parser.y"
                                  { (yyval.node) = (yyvsp[0].node); }
#line 1977 "parser.tab.c"
    break;

  case 69: /* arg_list: arg_list ',' expr  */
#line 270 "parser.y"
                                  { (yyval.node) = createArgList((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1983 "parser.tab.c"
    break;

  case 70: /* print_stmt: PRINT '(' expr ')' ';'  */
#line 274 "parser.y"
                                  { (yyval.node) = createPrint((yyvsp[-2].node)); }
#line 1989 "parser.tab.c"
    break;

  case 71: /* write_stmt: WRITE '(' expr ')' ';'  */
#line 278 "parser.y"
                                  { (yyval.node) = createWrite((yyvsp[-2].node)); }
#line 1995 "parser.tab.c"
    break;

  case 72: /* writeln_stmt: WRITELN ';'  */
#line 281 "parser.y"
                                  { (yyval.node) = createWriteln(); }
#line 2001 "parser.tab.c"
    break;


#line 2005 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 283 "parser.y"


void yyerror(const char* msg) {
    extern YYLTYPE yylloc;
    extern char* yytext;

    int line_no = yylloc.first_line > 0 ? yylloc.first_line : 1;
    int col_no  = yylloc.first_column > 0 ? yylloc.first_column : 1;

    if (g_input_filename) {
        FILE* src = fopen(g_input_filename, "r");
        if (src) {
            char linebuf[1024];
            int current = 1;
            while (fgets(linebuf, sizeof(linebuf), src)) {
                if (current == line_no) {
                    size_t L = strlen(linebuf);
                    while (L > 0 && (linebuf[L-1] == '\n' || linebuf[L-1] == '\r'))
                        linebuf[--L] = '\0';

                    fprintf(stderr,
                        "✗ Syntax Error: %s\n"
                        "  → Line %d, column %d\n"
                        "  → Near token: '%s'\n\n"
                        "    %s\n"
                        "    %*s^\n",
                        msg, line_no, col_no,
                        yytext ? yytext : "(unknown)",
                        linebuf, col_no, "");
                    fclose(src);
                    return;
                }
                current++;
            }
            fclose(src);
        }
    }

    fprintf(stderr,
        "✗ Syntax Error: %s at line %d, column %d (near '%s')\n",
        msg, line_no, col_no, yytext ? yytext : "(unknown)");
}
