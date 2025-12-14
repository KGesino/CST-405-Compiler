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
  YYSYMBOL_SWAP = 20,                      /* SWAP  */
  YYSYMBOL_BOOL_LIT = 21,                  /* BOOL_LIT  */
  YYSYMBOL_CHAR = 22,                      /* CHAR  */
  YYSYMBOL_GT = 23,                        /* GT  */
  YYSYMBOL_LT = 24,                        /* LT  */
  YYSYMBOL_GE = 25,                        /* GE  */
  YYSYMBOL_LE = 26,                        /* LE  */
  YYSYMBOL_EQ = 27,                        /* EQ  */
  YYSYMBOL_NE = 28,                        /* NE  */
  YYSYMBOL_AND = 29,                       /* AND  */
  YYSYMBOL_OR = 30,                        /* OR  */
  YYSYMBOL_NOT = 31,                       /* NOT  */
  YYSYMBOL_MUL = 32,                       /* MUL  */
  YYSYMBOL_DIV = 33,                       /* DIV  */
  YYSYMBOL_UMINUS = 34,                    /* UMINUS  */
  YYSYMBOL_35_ = 35,                       /* '+'  */
  YYSYMBOL_36_ = 36,                       /* '-'  */
  YYSYMBOL_IFX = 37,                       /* IFX  */
  YYSYMBOL_38_ = 38,                       /* '('  */
  YYSYMBOL_39_ = 39,                       /* ')'  */
  YYSYMBOL_40_ = 40,                       /* '{'  */
  YYSYMBOL_41_ = 41,                       /* '}'  */
  YYSYMBOL_42_ = 42,                       /* ','  */
  YYSYMBOL_43_ = 43,                       /* '['  */
  YYSYMBOL_44_ = 44,                       /* ']'  */
  YYSYMBOL_45_ = 45,                       /* ';'  */
  YYSYMBOL_46_ = 46,                       /* '='  */
  YYSYMBOL_YYACCEPT = 47,                  /* $accept  */
  YYSYMBOL_program = 48,                   /* program  */
  YYSYMBOL_func_list = 49,                 /* func_list  */
  YYSYMBOL_func_decl = 50,                 /* func_decl  */
  YYSYMBOL_type = 51,                      /* type  */
  YYSYMBOL_param_list = 52,                /* param_list  */
  YYSYMBOL_param = 53,                     /* param  */
  YYSYMBOL_stmt_list = 54,                 /* stmt_list  */
  YYSYMBOL_stmt = 55,                      /* stmt  */
  YYSYMBOL_swap_stmt = 56,                 /* swap_stmt  */
  YYSYMBOL_if_stmt = 57,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 58,                /* while_stmt  */
  YYSYMBOL_race_stmt = 59,                 /* race_stmt  */
  YYSYMBOL_id_list = 60,                   /* id_list  */
  YYSYMBOL_decl = 61,                      /* decl  */
  YYSYMBOL_arr_decl = 62,                  /* arr_decl  */
  YYSYMBOL_arr2d_decl = 63,                /* arr2d_decl  */
  YYSYMBOL_assign = 64,                    /* assign  */
  YYSYMBOL_arr_assign = 65,                /* arr_assign  */
  YYSYMBOL_arr2d_assign = 66,              /* arr2d_assign  */
  YYSYMBOL_return_stmt = 67,               /* return_stmt  */
  YYSYMBOL_expr = 68,                      /* expr  */
  YYSYMBOL_arg_list = 69,                  /* arg_list  */
  YYSYMBOL_print_stmt = 70,                /* print_stmt  */
  YYSYMBOL_write_stmt = 71,                /* write_stmt  */
  YYSYMBOL_writeln_stmt = 72               /* writeln_stmt  */
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
#define YYLAST   579

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  177

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


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
      38,    39,     2,    35,    42,    36,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    45,
       2,    46,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    43,     2,    44,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,     2,     2,     2,     2,
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
      37
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    83,    83,    87,    88,    95,    99,   106,   107,   108,
     109,   116,   117,   121,   122,   129,   130,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   161,   169,   171,   179,   187,
     195,   196,   200,   205,   210,   220,   225,   231,   239,   240,
     248,   249,   250,   251,   252,   253,   256,   257,   260,   261,
     262,   263,   266,   267,   268,   269,   270,   271,   274,   275,
     276,   277,   280,   281,   285,   286,   290,   294,   297
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
  "IF", "ELSE", "WHILE", "RACE", "FIRSTWINS", "BAR", "SWAP", "BOOL_LIT",
  "CHAR", "GT", "LT", "GE", "LE", "EQ", "NE", "AND", "OR", "NOT", "MUL",
  "DIV", "UMINUS", "'+'", "'-'", "IFX", "'('", "')'", "'{'", "'}'", "','",
  "'['", "']'", "';'", "'='", "$accept", "program", "func_list",
  "func_decl", "type", "param_list", "param", "stmt_list", "stmt",
  "swap_stmt", "if_stmt", "while_stmt", "race_stmt", "id_list", "decl",
  "arr_decl", "arr2d_decl", "assign", "arr_assign", "arr2d_assign",
  "return_stmt", "expr", "arg_list", "print_stmt", "write_stmt",
  "writeln_stmt", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#define YYPACT_NINF (-34)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      45,   -34,   -34,   -34,   -34,     7,    45,   -34,    30,   -34,
     -34,     2,    -5,     9,    42,   -30,   -34,   262,    20,    24,
      45,   -27,    27,    41,    49,    10,    58,    59,    60,    63,
      75,    97,   130,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,    54,   262,
     -34,   207,   284,   284,   284,   284,   -34,   -34,   -34,   -33,
     -34,   -34,   284,   284,   284,   -34,   268,   284,   284,   262,
      98,   -34,   146,    61,   -19,   -34,   -34,   -34,   168,    62,
     515,    -6,   342,   300,   430,   447,   211,   284,   543,   543,
     464,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   -34,   481,   498,   246,    64,   -34,   107,
     106,   -34,   -34,   -34,    67,   284,    11,   -34,    72,    73,
     -34,    17,   364,   -34,   -15,   -15,   -15,   -15,   -15,   -15,
     543,   529,   -34,   -34,    28,    28,   262,   262,   262,   116,
      78,   -34,   -34,   515,   284,   284,   -34,   -34,   -34,    80,
     110,   -34,   184,    87,   -21,   386,   314,   284,   262,   109,
      83,   126,   -34,    85,   -34,   408,   -34,    88,   -34,    90,
     284,   -34,   -34,   103,   328,   -34,   -34
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     7,     8,     9,    10,     0,     2,     3,     0,     1,
       4,     0,     0,     0,     0,     0,    11,     0,    13,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    15,    30,    27,    28,    29,    17,    22,
      24,    18,    23,    25,    26,    19,    20,    21,     0,     0,
      12,     0,     0,     0,     0,     0,    78,    50,    51,    54,
      52,    53,     0,     0,     0,    49,     0,     0,     0,     0,
       0,    34,     0,    40,     0,     6,    16,    14,     0,     0,
      74,     0,     0,     0,     0,     0,     0,     0,    70,    71,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    48,     0,     0,     0,     0,    33,     0,
       0,    42,     5,    32,     0,     0,     0,    45,     0,     0,
      73,     0,     0,    55,    62,    63,    64,    65,    66,    67,
      68,    69,    60,    61,    58,    59,     0,     0,     0,     0,
       0,    41,    31,    75,     0,     0,    76,    77,    72,    56,
      36,    38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    43,     0,    46,     0,    37,     0,    35,     0,
       0,    57,    39,     0,     0,    44,    47
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -34,   -34,   -34,   143,    93,   -34,   141,   -24,   -28,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -25,    79,   -34,   -34,   -34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,    31,    15,    16,    32,    33,    34,
      35,    36,    37,    74,    38,    39,    40,    41,    42,    43,
      44,    80,    81,    45,    46,    47
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      66,     1,     2,     3,    76,    86,    72,     9,     4,    19,
      87,    51,    20,    57,    58,    59,    52,    99,   100,    53,
     101,   102,   161,   110,   162,    78,   111,    82,    83,    84,
      85,    60,    61,   114,    13,    11,   115,    88,    89,    90,
      12,    62,   104,   105,    76,   106,    63,    18,    64,    17,
      76,     1,     2,     3,   144,    65,   148,   145,     4,   115,
      99,   100,   122,    48,    49,    54,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,    76,    55,
      21,     1,     2,     3,    22,    23,    24,    25,     4,    26,
     143,    27,    28,     8,    56,    29,    67,    68,    77,     8,
      69,    70,    73,   107,   109,    14,   139,   113,   150,   151,
     140,   141,   142,    14,   152,    30,    71,   146,   147,   155,
     156,   153,   154,   157,    76,   158,   160,   167,   168,   169,
     166,   170,   165,   172,   173,    21,     1,     2,     3,    22,
      23,    24,    25,     4,    26,   174,    27,    28,   175,    10,
      29,    21,     1,     2,     3,    22,    23,    24,    25,     4,
      26,    50,    27,    28,     0,   121,    29,     0,     0,     0,
      30,    75,     0,    21,     1,     2,     3,    22,    23,    24,
      25,     4,    26,     0,    27,    28,    30,   108,    29,    21,
       1,     2,     3,    22,    23,    24,    25,     4,    26,     0,
      27,    28,     0,     0,    29,     0,     0,     0,    30,   112,
      57,    58,    59,     0,    57,    58,    59,     0,     0,     0,
       0,     0,     0,     0,    30,   159,     0,     0,    60,    61,
       0,     0,    60,    61,     0,     0,     0,     0,    62,     0,
       0,     0,    62,    63,     0,    64,    79,    63,     0,    64,
     120,    21,     1,     2,     3,    22,    23,    24,    25,     4,
      26,     0,    27,    28,     0,   138,    29,    21,     1,     2,
       3,    22,    23,    24,    25,     4,    26,     0,    27,    28,
       0,     0,    29,     0,     0,     0,    30,    57,    58,    59,
       0,    91,    92,    93,    94,    95,    96,    97,    98,     0,
      99,   100,    30,   101,   102,    60,    61,     0,     0,     0,
       0,     0,     0,   103,     0,    62,     0,     0,     0,     0,
      63,     0,    64,    91,    92,    93,    94,    95,    96,    97,
      98,     0,    99,   100,     0,   101,   102,    91,    92,    93,
      94,    95,    96,    97,    98,   117,    99,   100,     0,   101,
     102,    91,    92,    93,    94,    95,    96,    97,    98,   164,
      99,   100,     0,   101,   102,    91,    92,    93,    94,    95,
      96,    97,    98,   176,    99,   100,     0,   101,   102,     0,
       0,     0,     0,     0,     0,     0,   116,    91,    92,    93,
      94,    95,    96,    97,    98,     0,    99,   100,     0,   101,
     102,     0,     0,     0,     0,     0,     0,     0,   149,    91,
      92,    93,    94,    95,    96,    97,    98,     0,    99,   100,
       0,   101,   102,     0,     0,     0,     0,     0,     0,     0,
     163,    91,    92,    93,    94,    95,    96,    97,    98,     0,
      99,   100,     0,   101,   102,     0,     0,     0,     0,     0,
       0,     0,   171,    91,    92,    93,    94,    95,    96,    97,
      98,     0,    99,   100,     0,   101,   102,     0,     0,   118,
      91,    92,    93,    94,    95,    96,    97,    98,     0,    99,
     100,     0,   101,   102,     0,     0,   119,    91,    92,    93,
      94,    95,    96,    97,    98,     0,    99,   100,     0,   101,
     102,     0,     0,   123,    91,    92,    93,    94,    95,    96,
      97,    98,     0,    99,   100,     0,   101,   102,     0,     0,
     136,    91,    92,    93,    94,    95,    96,    97,    98,     0,
      99,   100,     0,   101,   102,     0,     0,   137,    91,    92,
      93,    94,    95,    96,    97,    98,     0,    99,   100,     0,
     101,   102,    91,    92,    93,    94,    95,    96,    97,     0,
       0,    99,   100,     0,   101,   102,    91,    92,    93,    94,
      95,    96,     0,     0,     0,    99,   100,     0,   101,   102
};

static const yytype_int16 yycheck[] =
{
      25,     6,     7,     8,    32,    38,    30,     0,    13,    39,
      43,    38,    42,     3,     4,     5,    43,    32,    33,    46,
      35,    36,    43,    42,    45,    49,    45,    52,    53,    54,
      55,    21,    22,    39,    39,     5,    42,    62,    63,    64,
      38,    31,    67,    68,    72,    69,    36,     5,    38,    40,
      78,     6,     7,     8,    43,    45,    39,    46,    13,    42,
      32,    33,    87,    43,    40,    38,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   106,    38,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
     115,    16,    17,     0,    45,    20,    38,    38,    44,     6,
      40,    38,     5,     5,    43,    12,    42,    45,   136,   137,
       3,     5,    45,    20,   138,    40,    41,    45,    45,   144,
     145,     5,    44,    43,   152,    15,    39,    18,    45,     3,
     158,    46,   157,    45,    44,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   170,    16,    17,    45,     6,
      20,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    20,    16,    17,    -1,    86,    20,    -1,    -1,    -1,
      40,    41,    -1,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    -1,    16,    17,    40,    41,    20,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    -1,
      16,    17,    -1,    -1,    20,    -1,    -1,    -1,    40,    41,
       3,     4,     5,    -1,     3,     4,     5,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,    -1,    -1,    21,    22,
      -1,    -1,    21,    22,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    31,    36,    -1,    38,    39,    36,    -1,    38,
      39,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    -1,    16,    17,    -1,    19,    20,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    -1,    16,    17,
      -1,    -1,    20,    -1,    -1,    -1,    40,     3,     4,     5,
      -1,    23,    24,    25,    26,    27,    28,    29,    30,    -1,
      32,    33,    40,    35,    36,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    31,    -1,    -1,    -1,    -1,
      36,    -1,    38,    23,    24,    25,    26,    27,    28,    29,
      30,    -1,    32,    33,    -1,    35,    36,    23,    24,    25,
      26,    27,    28,    29,    30,    45,    32,    33,    -1,    35,
      36,    23,    24,    25,    26,    27,    28,    29,    30,    45,
      32,    33,    -1,    35,    36,    23,    24,    25,    26,    27,
      28,    29,    30,    45,    32,    33,    -1,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    23,    24,    25,
      26,    27,    28,    29,    30,    -1,    32,    33,    -1,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    23,
      24,    25,    26,    27,    28,    29,    30,    -1,    32,    33,
      -1,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    23,    24,    25,    26,    27,    28,    29,    30,    -1,
      32,    33,    -1,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    23,    24,    25,    26,    27,    28,    29,
      30,    -1,    32,    33,    -1,    35,    36,    -1,    -1,    39,
      23,    24,    25,    26,    27,    28,    29,    30,    -1,    32,
      33,    -1,    35,    36,    -1,    -1,    39,    23,    24,    25,
      26,    27,    28,    29,    30,    -1,    32,    33,    -1,    35,
      36,    -1,    -1,    39,    23,    24,    25,    26,    27,    28,
      29,    30,    -1,    32,    33,    -1,    35,    36,    -1,    -1,
      39,    23,    24,    25,    26,    27,    28,    29,    30,    -1,
      32,    33,    -1,    35,    36,    -1,    -1,    39,    23,    24,
      25,    26,    27,    28,    29,    30,    -1,    32,    33,    -1,
      35,    36,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    32,    33,    -1,    35,    36,    23,    24,    25,    26,
      27,    28,    -1,    -1,    -1,    32,    33,    -1,    35,    36
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,     7,     8,    13,    48,    49,    50,    51,     0,
      50,     5,    38,    39,    51,    52,    53,    40,     5,    39,
      42,     5,     9,    10,    11,    12,    14,    16,    17,    20,
      40,    51,    54,    55,    56,    57,    58,    59,    61,    62,
      63,    64,    65,    66,    67,    70,    71,    72,    43,    40,
      53,    38,    43,    46,    38,    38,    45,     3,     4,     5,
      21,    22,    31,    36,    38,    45,    68,    38,    38,    40,
      38,    41,    54,     5,    60,    41,    55,    44,    54,    39,
      68,    69,    68,    68,    68,    68,    38,    43,    68,    68,
      68,    23,    24,    25,    26,    27,    28,    29,    30,    32,
      33,    35,    36,    45,    68,    68,    54,     5,    41,    43,
      42,    45,    41,    45,    39,    42,    44,    45,    39,    39,
      39,    69,    68,    39,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    39,    39,    19,    42,
       3,     5,    45,    68,    43,    46,    45,    45,    39,    44,
      55,    55,    54,     5,    44,    68,    68,    43,    15,    41,
      39,    43,    45,    44,    45,    68,    55,    18,    45,     3,
      46,    44,    45,    44,    68,    45,    45
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    49,    49,    50,    50,    51,    51,    51,
      51,    52,    52,    53,    53,    54,    54,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    56,    57,    57,    58,    59,
      60,    60,    61,    62,    63,    64,    65,    66,    67,    67,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    69,    69,    70,    71,    72
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     8,     7,     1,     1,     1,
       1,     1,     3,     2,     4,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     4,     3,     2,     7,     5,     7,     5,     8,
       1,     3,     3,     6,     9,     4,     7,    10,     3,     2,
       1,     1,     1,     1,     1,     3,     4,     7,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     4,     3,     1,     3,     5,     5,     2
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
#line 83 "parser.y"
              { root = (yyvsp[0].node); }
#line 1675 "parser.tab.c"
    break;

  case 3: /* func_list: func_decl  */
#line 87 "parser.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 1681 "parser.tab.c"
    break;

  case 4: /* func_list: func_list func_decl  */
#line 88 "parser.y"
                             { (yyval.node) = createFuncList((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1687 "parser.tab.c"
    break;

  case 5: /* func_decl: type ID '(' param_list ')' '{' stmt_list '}'  */
#line 95 "parser.y"
                                                 {
        (yyval.node) = createFuncDecl((yyvsp[-7].str), (yyvsp[-6].str), (yyvsp[-4].node), (yyvsp[-1].node));
        free((yyvsp[-6].str));
    }
#line 1696 "parser.tab.c"
    break;

  case 6: /* func_decl: type ID '(' ')' '{' stmt_list '}'  */
#line 99 "parser.y"
                                      {
        (yyval.node) = createFuncDecl((yyvsp[-6].str), (yyvsp[-5].str), NULL, (yyvsp[-1].node));
        free((yyvsp[-5].str));
    }
#line 1705 "parser.tab.c"
    break;

  case 7: /* type: INT  */
#line 106 "parser.y"
          { (yyval.str) = "int"; }
#line 1711 "parser.tab.c"
    break;

  case 8: /* type: FLOAT  */
#line 107 "parser.y"
          { (yyval.str) = "float"; }
#line 1717 "parser.tab.c"
    break;

  case 9: /* type: BOOL  */
#line 108 "parser.y"
          { (yyval.str) = "bool"; }
#line 1723 "parser.tab.c"
    break;

  case 10: /* type: VOID  */
#line 109 "parser.y"
          { (yyval.str) = "void"; }
#line 1729 "parser.tab.c"
    break;

  case 11: /* param_list: param  */
#line 116 "parser.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 1735 "parser.tab.c"
    break;

  case 12: /* param_list: param_list ',' param  */
#line 117 "parser.y"
                             { (yyval.node) = createParamList((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1741 "parser.tab.c"
    break;

  case 13: /* param: type ID  */
#line 121 "parser.y"
                             { (yyval.node) = createParam((yyvsp[-1].str), (yyvsp[0].str), 0, -1); free((yyvsp[0].str)); }
#line 1747 "parser.tab.c"
    break;

  case 14: /* param: type ID '[' ']'  */
#line 122 "parser.y"
                             { (yyval.node) = createParam((yyvsp[-3].str), (yyvsp[-2].str), 1, -1); free((yyvsp[-2].str)); }
#line 1753 "parser.tab.c"
    break;

  case 15: /* stmt_list: stmt  */
#line 129 "parser.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 1759 "parser.tab.c"
    break;

  case 16: /* stmt_list: stmt_list stmt  */
#line 130 "parser.y"
                             { (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1765 "parser.tab.c"
    break;

  case 31: /* stmt: ID '(' arg_list ')' ';'  */
#line 151 "parser.y"
                                    { (yyval.node) = createFuncCallStmt((yyvsp[-4].str), (yyvsp[-2].node)); free((yyvsp[-4].str)); }
#line 1771 "parser.tab.c"
    break;

  case 32: /* stmt: ID '(' ')' ';'  */
#line 152 "parser.y"
                                    { (yyval.node) = createFuncCallStmt((yyvsp[-3].str), NULL); free((yyvsp[-3].str)); }
#line 1777 "parser.tab.c"
    break;

  case 33: /* stmt: '{' stmt_list '}'  */
#line 153 "parser.y"
                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1783 "parser.tab.c"
    break;

  case 34: /* stmt: '{' '}'  */
#line 154 "parser.y"
                                    { (yyval.node) = NULL; }
#line 1789 "parser.tab.c"
    break;

  case 35: /* swap_stmt: SWAP '(' ID ',' ID ')' ';'  */
#line 162 "parser.y"
        { (yyval.node) = createSwap((yyvsp[-4].str), (yyvsp[-2].str)); free((yyvsp[-4].str)); free((yyvsp[-2].str)); }
#line 1795 "parser.tab.c"
    break;

  case 36: /* if_stmt: IF '(' expr ')' stmt  */
#line 170 "parser.y"
        { (yyval.node) = createIf((yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 1801 "parser.tab.c"
    break;

  case 37: /* if_stmt: IF '(' expr ')' stmt ELSE stmt  */
#line 172 "parser.y"
        { (yyval.node) = createIf((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1807 "parser.tab.c"
    break;

  case 38: /* while_stmt: WHILE '(' expr ')' stmt  */
#line 180 "parser.y"
        { (yyval.node) = createWhile((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1813 "parser.tab.c"
    break;

  case 39: /* race_stmt: RACE '{' stmt_list BAR stmt_list '}' FIRSTWINS ';'  */
#line 188 "parser.y"
        { (yyval.node) = createRace((yyvsp[-5].node), (yyvsp[-3].node)); }
#line 1819 "parser.tab.c"
    break;

  case 40: /* id_list: ID  */
#line 195 "parser.y"
                            { (yyval.node) = createDecl((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 1825 "parser.tab.c"
    break;

  case 41: /* id_list: id_list ',' ID  */
#line 196 "parser.y"
                            { (yyval.node) = createDeclList((yyvsp[-2].node), createDecl((yyvsp[0].str))); free((yyvsp[0].str)); }
#line 1831 "parser.tab.c"
    break;

  case 42: /* decl: type id_list ';'  */
#line 200 "parser.y"
                            { (yyval.node) = (yyvsp[-1].node); }
#line 1837 "parser.tab.c"
    break;

  case 43: /* arr_decl: type ID '[' NUM ']' ';'  */
#line 205 "parser.y"
                             { (yyval.node) = createArrayDecl((yyvsp[-4].str), (yyvsp[-2].num)); free((yyvsp[-4].str)); }
#line 1843 "parser.tab.c"
    break;

  case 44: /* arr2d_decl: type ID '[' NUM ']' '[' NUM ']' ';'  */
#line 210 "parser.y"
                                        {
        (yyval.node) = createArray2DDecl((yyvsp[-7].str), (yyvsp[-5].num), (yyvsp[-2].num));
        free((yyvsp[-7].str));
    }
#line 1852 "parser.tab.c"
    break;

  case 45: /* assign: ID '=' expr ';'  */
#line 220 "parser.y"
                            { (yyval.node) = createAssign((yyvsp[-3].str), (yyvsp[-1].node)); free((yyvsp[-3].str)); }
#line 1858 "parser.tab.c"
    break;

  case 46: /* arr_assign: ID '[' expr ']' '=' expr ';'  */
#line 226 "parser.y"
        { (yyval.node) = createArrayAssign((yyvsp[-6].str), (yyvsp[-4].node), (yyvsp[-1].node)); free((yyvsp[-6].str)); }
#line 1864 "parser.tab.c"
    break;

  case 47: /* arr2d_assign: ID '[' expr ']' '[' expr ']' '=' expr ';'  */
#line 232 "parser.y"
        { (yyval.node) = createArray2DAssign((yyvsp[-9].str), (yyvsp[-7].node), (yyvsp[-4].node), (yyvsp[-1].node)); free((yyvsp[-9].str)); }
#line 1870 "parser.tab.c"
    break;

  case 48: /* return_stmt: RETURN expr ';'  */
#line 239 "parser.y"
                            { (yyval.node) = createReturn((yyvsp[-1].node)); }
#line 1876 "parser.tab.c"
    break;

  case 49: /* return_stmt: RETURN ';'  */
#line 240 "parser.y"
                            { (yyval.node) = createReturn(NULL); }
#line 1882 "parser.tab.c"
    break;

  case 50: /* expr: NUM  */
#line 248 "parser.y"
                                  { (yyval.node) = createNum((yyvsp[0].num)); }
#line 1888 "parser.tab.c"
    break;

  case 51: /* expr: FLOAT_LIT  */
#line 249 "parser.y"
                                  { (yyval.node) = createFloatNode((yyvsp[0].fnum)); }
#line 1894 "parser.tab.c"
    break;

  case 52: /* expr: BOOL_LIT  */
#line 250 "parser.y"
                                  { (yyval.node) = createBoolNode((yyvsp[0].num)); }
#line 1900 "parser.tab.c"
    break;

  case 53: /* expr: CHAR  */
#line 251 "parser.y"
                                  { (yyval.node) = createCharNode((yyvsp[0].num)); }
#line 1906 "parser.tab.c"
    break;

  case 54: /* expr: ID  */
#line 252 "parser.y"
                                  { (yyval.node) = createVar((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 1912 "parser.tab.c"
    break;

  case 55: /* expr: '(' expr ')'  */
#line 253 "parser.y"
                                  { (yyval.node) = (yyvsp[-1].node); }
#line 1918 "parser.tab.c"
    break;

  case 56: /* expr: ID '[' expr ']'  */
#line 256 "parser.y"
                                  { (yyval.node) = createArrayAccess((yyvsp[-3].str), (yyvsp[-1].node)); free((yyvsp[-3].str)); }
#line 1924 "parser.tab.c"
    break;

  case 57: /* expr: ID '[' expr ']' '[' expr ']'  */
#line 257 "parser.y"
                                  { (yyval.node) = createArray2DAccess((yyvsp[-6].str), (yyvsp[-4].node), (yyvsp[-1].node)); free((yyvsp[-6].str)); }
#line 1930 "parser.tab.c"
    break;

  case 58: /* expr: expr '+' expr  */
#line 260 "parser.y"
                                  { (yyval.node) = createBinOp('+', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1936 "parser.tab.c"
    break;

  case 59: /* expr: expr '-' expr  */
#line 261 "parser.y"
                                  { (yyval.node) = createBinOp('-', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1942 "parser.tab.c"
    break;

  case 60: /* expr: expr MUL expr  */
#line 262 "parser.y"
                                  { (yyval.node) = createBinOp('*', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1948 "parser.tab.c"
    break;

  case 61: /* expr: expr DIV expr  */
#line 263 "parser.y"
                                  { (yyval.node) = createBinOp('/', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1954 "parser.tab.c"
    break;

  case 62: /* expr: expr GT expr  */
#line 266 "parser.y"
                                  { (yyval.node) = createBinOp('>', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1960 "parser.tab.c"
    break;

  case 63: /* expr: expr LT expr  */
#line 267 "parser.y"
                                  { (yyval.node) = createBinOp('<', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1966 "parser.tab.c"
    break;

  case 64: /* expr: expr GE expr  */
#line 268 "parser.y"
                                  { (yyval.node) = createBinOp('G', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1972 "parser.tab.c"
    break;

  case 65: /* expr: expr LE expr  */
#line 269 "parser.y"
                                  { (yyval.node) = createBinOp('L', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1978 "parser.tab.c"
    break;

  case 66: /* expr: expr EQ expr  */
#line 270 "parser.y"
                                  { (yyval.node) = createBinOp('E', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1984 "parser.tab.c"
    break;

  case 67: /* expr: expr NE expr  */
#line 271 "parser.y"
                                  { (yyval.node) = createBinOp('N', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1990 "parser.tab.c"
    break;

  case 68: /* expr: expr AND expr  */
#line 274 "parser.y"
                                  { (yyval.node) = createBinOp('&', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1996 "parser.tab.c"
    break;

  case 69: /* expr: expr OR expr  */
#line 275 "parser.y"
                                  { (yyval.node) = createBinOp('|', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2002 "parser.tab.c"
    break;

  case 70: /* expr: NOT expr  */
#line 276 "parser.y"
                                  { (yyval.node) = createUnaryOp('!', (yyvsp[0].node)); }
#line 2008 "parser.tab.c"
    break;

  case 71: /* expr: '-' expr  */
#line 277 "parser.y"
                                  { (yyval.node) = createUnaryOp('-', (yyvsp[0].node)); }
#line 2014 "parser.tab.c"
    break;

  case 72: /* expr: ID '(' arg_list ')'  */
#line 280 "parser.y"
                                  { (yyval.node) = createFuncCall((yyvsp[-3].str), (yyvsp[-1].node)); free((yyvsp[-3].str)); }
#line 2020 "parser.tab.c"
    break;

  case 73: /* expr: ID '(' ')'  */
#line 281 "parser.y"
                                  { (yyval.node) = createFuncCall((yyvsp[-2].str), NULL); free((yyvsp[-2].str)); }
#line 2026 "parser.tab.c"
    break;

  case 74: /* arg_list: expr  */
#line 285 "parser.y"
                                  { (yyval.node) = (yyvsp[0].node); }
#line 2032 "parser.tab.c"
    break;

  case 75: /* arg_list: arg_list ',' expr  */
#line 286 "parser.y"
                                  { (yyval.node) = createArgList((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2038 "parser.tab.c"
    break;

  case 76: /* print_stmt: PRINT '(' expr ')' ';'  */
#line 290 "parser.y"
                                  { (yyval.node) = createPrint((yyvsp[-2].node)); }
#line 2044 "parser.tab.c"
    break;

  case 77: /* write_stmt: WRITE '(' expr ')' ';'  */
#line 294 "parser.y"
                                  { (yyval.node) = createWrite((yyvsp[-2].node)); }
#line 2050 "parser.tab.c"
    break;

  case 78: /* writeln_stmt: WRITELN ';'  */
#line 297 "parser.y"
                                  { (yyval.node) = createWriteln(); }
#line 2056 "parser.tab.c"
    break;


#line 2060 "parser.tab.c"

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

#line 299 "parser.y"


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
