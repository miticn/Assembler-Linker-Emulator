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
#line 1 "misc/bison.y"

    #include <stdio.h>
    #include <iostream>
    #include <string>
    #include <cstdint>
    using namespace std;
    #include "../inc/token.hpp"
    #include "../inc/assembler.hpp"
    //#include "../inc/operand.hpp"
	extern int yylex(void);
    extern int yyparse();
    extern FILE *yyin;
	extern void yyerror(const char*);


#line 87 "misc/bison.cpp"

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

#include "bison.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_DOLLAR = 3,                     /* DOLLAR  */
  YYSYMBOL_PERCENT = 4,                    /* PERCENT  */
  YYSYMBOL_NUMBER = 5,                     /* NUMBER  */
  YYSYMBOL_EOL = 6,                        /* EOL  */
  YYSYMBOL_NUMBER_SIGN = 7,                /* NUMBER_SIGN  */
  YYSYMBOL_COLON = 8,                      /* COLON  */
  YYSYMBOL_DOT = 9,                        /* DOT  */
  YYSYMBOL_COMMA = 10,                     /* COMMA  */
  YYSYMBOL_PLUS = 11,                      /* PLUS  */
  YYSYMBOL_LBRACKET = 12,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 13,                  /* RBRACKET  */
  YYSYMBOL_GLOBAL = 14,                    /* GLOBAL  */
  YYSYMBOL_EXTERN = 15,                    /* EXTERN  */
  YYSYMBOL_SECTION = 16,                   /* SECTION  */
  YYSYMBOL_WORD = 17,                      /* WORD  */
  YYSYMBOL_SKIP = 18,                      /* SKIP  */
  YYSYMBOL_ASCII = 19,                     /* ASCII  */
  YYSYMBOL_EQU = 20,                       /* EQU  */
  YYSYMBOL_END = 21,                       /* END  */
  YYSYMBOL_HALT = 22,                      /* HALT  */
  YYSYMBOL_INT = 23,                       /* INT  */
  YYSYMBOL_IRET = 24,                      /* IRET  */
  YYSYMBOL_CALL = 25,                      /* CALL  */
  YYSYMBOL_RET = 26,                       /* RET  */
  YYSYMBOL_JMP = 27,                       /* JMP  */
  YYSYMBOL_BEQ = 28,                       /* BEQ  */
  YYSYMBOL_BNE = 29,                       /* BNE  */
  YYSYMBOL_BGT = 30,                       /* BGT  */
  YYSYMBOL_PUSH = 31,                      /* PUSH  */
  YYSYMBOL_POP = 32,                       /* POP  */
  YYSYMBOL_XCHG = 33,                      /* XCHG  */
  YYSYMBOL_ADD = 34,                       /* ADD  */
  YYSYMBOL_SUB = 35,                       /* SUB  */
  YYSYMBOL_MUL = 36,                       /* MUL  */
  YYSYMBOL_DIV = 37,                       /* DIV  */
  YYSYMBOL_NOT = 38,                       /* NOT  */
  YYSYMBOL_AND = 39,                       /* AND  */
  YYSYMBOL_OR = 40,                        /* OR  */
  YYSYMBOL_XOR = 41,                       /* XOR  */
  YYSYMBOL_SHL = 42,                       /* SHL  */
  YYSYMBOL_SHR = 43,                       /* SHR  */
  YYSYMBOL_LD = 44,                        /* LD  */
  YYSYMBOL_ST = 45,                        /* ST  */
  YYSYMBOL_CSRRD = 46,                     /* CSRRD  */
  YYSYMBOL_CSRWR = 47,                     /* CSRWR  */
  YYSYMBOL_IDENTIFIER = 48,                /* IDENTIFIER  */
  YYSYMBOL_STRING = 49,                    /* STRING  */
  YYSYMBOL_REGISTER = 50,                  /* REGISTER  */
  YYSYMBOL_CONTROL_REGISTER = 51,          /* CONTROL_REGISTER  */
  YYSYMBOL_YYACCEPT = 52,                  /* $accept  */
  YYSYMBOL_program = 53,                   /* program  */
  YYSYMBOL_line = 54,                      /* line  */
  YYSYMBOL_label = 55,                     /* label  */
  YYSYMBOL_directive = 56,                 /* directive  */
  YYSYMBOL_directive_global = 57,          /* directive_global  */
  YYSYMBOL_directive_extern = 58,          /* directive_extern  */
  YYSYMBOL_directive_section = 59,         /* directive_section  */
  YYSYMBOL_directive_word = 60,            /* directive_word  */
  YYSYMBOL_directive_skip = 61,            /* directive_skip  */
  YYSYMBOL_directive_ascii = 62,           /* directive_ascii  */
  YYSYMBOL_directive_equ = 63,             /* directive_equ  */
  YYSYMBOL_directive_end = 64,             /* directive_end  */
  YYSYMBOL_command = 65,                   /* command  */
  YYSYMBOL_ld_instuction = 66,             /* ld_instuction  */
  YYSYMBOL_st_instuction = 67              /* st_instuction  */
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  89
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   243

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  186

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   306


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
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    79,    79,    80,    83,    84,    85,    86,    87,    88,
      91,    96,    97,    98,    99,   100,   101,   102,   103,   106,
     107,   110,   111,   114,   117,   118,   119,   120,   123,   125,
     127,   129,   132,   133,   134,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   169,   172,   175,   180,   184,   187,   190,
     193,   198,   202,   206,   209,   212,   215,   218,   221
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "DOLLAR", "PERCENT",
  "NUMBER", "EOL", "NUMBER_SIGN", "COLON", "DOT", "COMMA", "PLUS",
  "LBRACKET", "RBRACKET", "GLOBAL", "EXTERN", "SECTION", "WORD", "SKIP",
  "ASCII", "EQU", "END", "HALT", "INT", "IRET", "CALL", "RET", "JMP",
  "BEQ", "BNE", "BGT", "PUSH", "POP", "XCHG", "ADD", "SUB", "MUL", "DIV",
  "NOT", "AND", "OR", "XOR", "SHL", "SHR", "LD", "ST", "CSRRD", "CSRWR",
  "IDENTIFIER", "STRING", "REGISTER", "CONTROL_REGISTER", "$accept",
  "program", "line", "label", "directive", "directive_global",
  "directive_extern", "directive_section", "directive_word",
  "directive_skip", "directive_ascii", "directive_equ", "directive_end",
  "command", "ld_instuction", "st_instuction", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-44)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      95,   -44,   -43,   -41,   -40,     5,     4,    17,    19,   -44,
     -44,   -44,   -44,     6,   -44,     7,    18,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    46,    35,    36,    38,    61,     0,   -44,   138,
      80,    79,    81,   -44,    82,   -44,   -44,   -44,   -44,    84,
     -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,    83,
     -44,   -44,   -44,   -44,    88,    89,    92,   -44,   -44,   135,
     136,   137,   139,   140,   -44,   141,   176,   177,   178,   179,
       8,   180,    98,   181,   182,   183,   184,   185,   -44,   -44,
     -44,   -44,   190,   191,   -44,   150,   151,    52,   -44,   195,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   205,   206,   167,   -10,   168,   169,    47,
     170,   171,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   211,
     213,   214,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,
     -44,   -44,   175,   186,   -44,    55,   216,   -44,   -44,    56,
     -44,   187,   -44,   -44,   -44,   -44,    57,    58,    59,   -44,
     -44,   188,   215,   189,   -44,   -44,    -9,   -44,   -44,   -44,
     -44,   -44,   -44,   217,   219,   -44,    60,   -44,   192,   193,
     218,   220,   -44,   -44,   -44,   -44
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     4,     0,     0,     0,     0,     0,     0,     0,    31,
      32,    33,    34,     0,    35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,     0,
       0,    11,    12,    13,    14,    15,    16,    17,    18,     0,
      61,    62,    19,    21,    23,    24,    25,    28,    29,     0,
      51,    52,    53,    54,     0,     0,     0,    36,    37,     0,
       0,     0,     0,     0,    43,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    10,     1,
       2,     5,     0,     0,     8,     0,     0,     0,     9,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     6,     7,    20,    22,    26,    27,    30,     0,
       0,     0,    38,    39,    40,    41,    42,    44,    45,    46,
      47,    48,     0,     0,    65,     0,     0,    66,    67,     0,
      73,     0,    74,    75,    49,    50,     0,     0,     0,    63,
      64,     0,     0,     0,    71,    72,     0,    55,    56,    57,
      58,    59,    60,     0,     0,    68,     0,    76,     0,     0,
       0,     0,    69,    70,    77,    78
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -44,   -44,   197,   -44,   196,   -44,   -44,   -44,   -44,   -44,
     -44,   -44,   -44,   199,   -44,   -44
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      89,   145,   176,   146,   177,    52,     1,    53,    54,    57,
      55,    60,    62,   113,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    80,
     149,    81,   150,    56,    61,    63,   114,   126,    82,   151,
     161,   164,   167,   169,   171,   180,    58,    59,    64,    88,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    85,    94,    86,    87,    95,
      98,    96,    97,    99,    83,   152,    84,   153,   100,   101,
     127,     1,   102,   162,   165,   168,   170,   172,   181,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    91,   103,   104,   105,   116,   106,
     107,   108,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,   109,   110,   111,   112,
     115,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     128,   173,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   147,   148,
     154,   156,   155,   157,   158,   159,   163,   178,   174,   179,
       0,   184,     0,   185,    90,    92,   160,   166,    93,   175,
       0,     0,   182,   183
};

static const yytype_int8 yycheck[] =
{
       0,    11,    11,    13,    13,    48,     6,    48,    48,     5,
       5,     5,     5,     5,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,     3,
       3,     5,     5,    48,    48,    48,    48,     5,    12,    12,
       5,     5,     5,     5,     5,     5,    49,    48,    50,     8,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,     6,    51,    50,    10,
       6,    10,    10,    10,    48,    48,    50,    50,    10,    10,
      48,     6,    10,    48,    48,    48,    48,    48,    48,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,     6,    10,    10,    10,    50,    10,
      10,    10,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    10,    10,    10,    10,
      10,    10,    10,    10,    10,    10,     6,     6,    48,    48,
       5,    13,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    10,    10,    50,    50,    50,
      50,    10,    51,    10,    10,    50,    10,    10,    13,    10,
      -1,    13,    -1,    13,    37,    39,    50,    50,    39,    50,
      -1,    -1,    50,    50
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    48,    48,    48,     5,    48,     5,    49,    48,
       5,    48,     5,    48,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
       3,     5,    12,    48,    50,    50,    51,    50,     8,     0,
      54,     6,    56,    65,     6,    10,    10,    10,     6,    10,
      10,    10,    10,    10,    10,    10,    10,    10,    10,    10,
      10,    10,    10,     5,    48,    10,    50,    10,    10,    10,
      10,    10,     6,     6,    48,    48,     5,    48,     5,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    10,    10,    50,    11,    13,    50,    50,     3,
       5,    12,    48,    50,    50,    51,    10,    10,    10,    50,
      50,     5,    48,    10,     5,    48,    50,     5,    48,     5,
      48,     5,    48,    13,    13,    50,    11,    13,    10,    10,
       5,    48,    50,    50,    13,    13
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    52,    53,    53,    54,    54,    54,    54,    54,    54,
      55,    56,    56,    56,    56,    56,    56,    56,    56,    57,
      57,    58,    58,    59,    60,    60,    60,    60,    61,    62,
      63,    64,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    66,    66,    66,    66,    66,    66,    66,
      66,    67,    67,    67,    67,    67,    67,    67,    67
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     2,     3,     3,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     2,     3,     2,     2,     2,     3,     3,     2,     2,
       4,     1,     1,     1,     1,     1,     2,     2,     4,     4,
       4,     4,     4,     2,     4,     4,     4,     4,     4,     4,
       4,     2,     2,     2,     2,     6,     6,     6,     6,     6,
       6,     1,     1,     5,     5,     4,     4,     4,     6,     8,
       8,     5,     5,     4,     4,     4,     6,     8,     8
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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
#  undef YYSTACK_RELOCATE
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
  case 10: /* label: IDENTIFIER COLON  */
#line 91 "misc/bison.y"
                          {
        Assembler::tokenList.push_back(new LabelToken((yyvsp[-1].stringValue)));
    }
#line 1268 "misc/bison.cpp"
    break;

  case 19: /* directive_global: GLOBAL IDENTIFIER  */
#line 106 "misc/bison.y"
                                     { Assembler::tokenList.push_back(new GlobalDirectiveToken((yyvsp[0].stringValue)));}
#line 1274 "misc/bison.cpp"
    break;

  case 20: /* directive_global: directive_global COMMA IDENTIFIER  */
#line 107 "misc/bison.y"
                                        { Assembler::tokenList.push_back(new GlobalDirectiveToken((yyvsp[0].stringValue)));}
#line 1280 "misc/bison.cpp"
    break;

  case 21: /* directive_extern: EXTERN IDENTIFIER  */
#line 110 "misc/bison.y"
                                     { Assembler::tokenList.push_back(new ExternDirectiveToken((yyvsp[0].stringValue)));}
#line 1286 "misc/bison.cpp"
    break;

  case 22: /* directive_extern: directive_extern COMMA IDENTIFIER  */
#line 111 "misc/bison.y"
                                        { Assembler::tokenList.push_back(new ExternDirectiveToken((yyvsp[0].stringValue)));}
#line 1292 "misc/bison.cpp"
    break;

  case 23: /* directive_section: SECTION IDENTIFIER  */
#line 114 "misc/bison.y"
                                       { Assembler::tokenList.push_back(new SectionDirectiveToken((yyvsp[0].stringValue)));}
#line 1298 "misc/bison.cpp"
    break;

  case 32: /* command: HALT  */
#line 132 "misc/bison.y"
               { Assembler::tokenList.push_back(new HaltCommandToken);}
#line 1304 "misc/bison.cpp"
    break;

  case 33: /* command: INT  */
#line 133 "misc/bison.y"
          { Assembler::tokenList.push_back(new IntCommandToken);}
#line 1310 "misc/bison.cpp"
    break;

  case 34: /* command: IRET  */
#line 134 "misc/bison.y"
           { 
        Assembler::tokenList.push_back(new RetCommandToken);
        Assembler::tokenList.push_back(new PopStatusCommandToken);
    }
#line 1319 "misc/bison.cpp"
    break;

  case 35: /* command: RET  */
#line 138 "misc/bison.y"
          { Assembler::tokenList.push_back(new RetCommandToken);}
#line 1325 "misc/bison.cpp"
    break;

  case 36: /* command: PUSH REGISTER  */
#line 139 "misc/bison.y"
                    { Assembler::tokenList.push_back(new PushCommandToken((yyvsp[0].intValue)));}
#line 1331 "misc/bison.cpp"
    break;

  case 37: /* command: POP REGISTER  */
#line 140 "misc/bison.y"
                   { Assembler::tokenList.push_back(new PopCommandToken((yyvsp[0].intValue)));}
#line 1337 "misc/bison.cpp"
    break;

  case 38: /* command: XCHG REGISTER COMMA REGISTER  */
#line 141 "misc/bison.y"
                                   { Assembler::tokenList.push_back(new XchgCommandToken((yyvsp[-2].intValue), (yyvsp[0].intValue)));}
#line 1343 "misc/bison.cpp"
    break;

  case 39: /* command: ADD REGISTER COMMA REGISTER  */
#line 142 "misc/bison.y"
                                  { Assembler::tokenList.push_back(new AddCommandToken((yyvsp[-2].intValue), (yyvsp[0].intValue)));}
#line 1349 "misc/bison.cpp"
    break;

  case 40: /* command: SUB REGISTER COMMA REGISTER  */
#line 143 "misc/bison.y"
                                  { Assembler::tokenList.push_back(new SubCommandToken((yyvsp[-2].intValue), (yyvsp[0].intValue)));}
#line 1355 "misc/bison.cpp"
    break;

  case 41: /* command: MUL REGISTER COMMA REGISTER  */
#line 144 "misc/bison.y"
                                  { Assembler::tokenList.push_back(new MulCommandToken((yyvsp[-2].intValue), (yyvsp[0].intValue)));}
#line 1361 "misc/bison.cpp"
    break;

  case 42: /* command: DIV REGISTER COMMA REGISTER  */
#line 145 "misc/bison.y"
                                  { Assembler::tokenList.push_back(new DivCommandToken((yyvsp[-2].intValue), (yyvsp[0].intValue)));}
#line 1367 "misc/bison.cpp"
    break;

  case 43: /* command: NOT REGISTER  */
#line 146 "misc/bison.y"
                   { Assembler::tokenList.push_back(new NotCommandToken((yyvsp[0].intValue)));}
#line 1373 "misc/bison.cpp"
    break;

  case 44: /* command: AND REGISTER COMMA REGISTER  */
#line 147 "misc/bison.y"
                                  { Assembler::tokenList.push_back(new AndCommandToken((yyvsp[-2].intValue), (yyvsp[0].intValue)));}
#line 1379 "misc/bison.cpp"
    break;

  case 45: /* command: OR REGISTER COMMA REGISTER  */
#line 148 "misc/bison.y"
                                 { Assembler::tokenList.push_back(new OrCommandToken((yyvsp[-2].intValue), (yyvsp[0].intValue)));}
#line 1385 "misc/bison.cpp"
    break;

  case 46: /* command: XOR REGISTER COMMA REGISTER  */
#line 149 "misc/bison.y"
                                  { Assembler::tokenList.push_back(new XorCommandToken((yyvsp[-2].intValue), (yyvsp[0].intValue)));}
#line 1391 "misc/bison.cpp"
    break;

  case 47: /* command: SHL REGISTER COMMA REGISTER  */
#line 150 "misc/bison.y"
                                  { Assembler::tokenList.push_back(new ShlCommandToken((yyvsp[-2].intValue), (yyvsp[0].intValue)));}
#line 1397 "misc/bison.cpp"
    break;

  case 48: /* command: SHR REGISTER COMMA REGISTER  */
#line 151 "misc/bison.y"
                                  { Assembler::tokenList.push_back(new ShrCommandToken((yyvsp[-2].intValue), (yyvsp[0].intValue)));}
#line 1403 "misc/bison.cpp"
    break;

  case 49: /* command: CSRRD CONTROL_REGISTER COMMA REGISTER  */
#line 152 "misc/bison.y"
                                            { Assembler::tokenList.push_back(new CsrrdCommandToken((yyvsp[-2].intValue), (yyvsp[0].intValue)));}
#line 1409 "misc/bison.cpp"
    break;

  case 50: /* command: CSRWR REGISTER COMMA CONTROL_REGISTER  */
#line 153 "misc/bison.y"
                                            { Assembler::tokenList.push_back(new CsrwrCommandToken((yyvsp[-2].intValue), (yyvsp[0].intValue)));}
#line 1415 "misc/bison.cpp"
    break;

  case 51: /* command: CALL NUMBER  */
#line 155 "misc/bison.y"
                  { Assembler::tokenList.push_back(new CallCommandToken(OperandJump((yyvsp[0].intValue)))); }
#line 1421 "misc/bison.cpp"
    break;

  case 52: /* command: CALL IDENTIFIER  */
#line 156 "misc/bison.y"
                      { Assembler::tokenList.push_back(new CallCommandToken(OperandJump((yyvsp[0].stringValue)))); }
#line 1427 "misc/bison.cpp"
    break;

  case 53: /* command: JMP NUMBER  */
#line 157 "misc/bison.y"
                 { Assembler::tokenList.push_back(new JmpCommandToken(OperandJump((yyvsp[0].intValue)))); }
#line 1433 "misc/bison.cpp"
    break;

  case 54: /* command: JMP IDENTIFIER  */
#line 158 "misc/bison.y"
                     { Assembler::tokenList.push_back(new JmpCommandToken(OperandJump((yyvsp[0].stringValue)))); }
#line 1439 "misc/bison.cpp"
    break;

  case 55: /* command: BEQ REGISTER COMMA REGISTER COMMA NUMBER  */
#line 159 "misc/bison.y"
                                               { Assembler::tokenList.push_back(new BeqCommandToken((yyvsp[-4].intValue), (yyvsp[-2].intValue), OperandJump((yyvsp[0].intValue)))); }
#line 1445 "misc/bison.cpp"
    break;

  case 56: /* command: BEQ REGISTER COMMA REGISTER COMMA IDENTIFIER  */
#line 160 "misc/bison.y"
                                                   { Assembler::tokenList.push_back(new BeqCommandToken((yyvsp[-4].intValue), (yyvsp[-2].intValue), OperandJump((yyvsp[0].stringValue)))); }
#line 1451 "misc/bison.cpp"
    break;

  case 57: /* command: BNE REGISTER COMMA REGISTER COMMA NUMBER  */
#line 161 "misc/bison.y"
                                               { Assembler::tokenList.push_back(new BneCommandToken((yyvsp[-4].intValue), (yyvsp[-2].intValue), OperandJump((yyvsp[0].intValue)))); }
#line 1457 "misc/bison.cpp"
    break;

  case 58: /* command: BNE REGISTER COMMA REGISTER COMMA IDENTIFIER  */
#line 162 "misc/bison.y"
                                                   { Assembler::tokenList.push_back(new BneCommandToken((yyvsp[-4].intValue), (yyvsp[-2].intValue), OperandJump((yyvsp[0].stringValue)))); }
#line 1463 "misc/bison.cpp"
    break;

  case 59: /* command: BGT REGISTER COMMA REGISTER COMMA NUMBER  */
#line 163 "misc/bison.y"
                                               { Assembler::tokenList.push_back(new BgtCommandToken((yyvsp[-4].intValue), (yyvsp[-2].intValue), OperandJump((yyvsp[0].intValue)))); }
#line 1469 "misc/bison.cpp"
    break;

  case 60: /* command: BGT REGISTER COMMA REGISTER COMMA IDENTIFIER  */
#line 164 "misc/bison.y"
                                                   { Assembler::tokenList.push_back(new BgtCommandToken((yyvsp[-4].intValue), (yyvsp[-2].intValue), OperandJump((yyvsp[0].stringValue)))); }
#line 1475 "misc/bison.cpp"
    break;

  case 63: /* ld_instuction: LD DOLLAR NUMBER COMMA REGISTER  */
#line 169 "misc/bison.y"
                                               { 
        Assembler::tokenList.push_back(new LdCommandToken(OperandData(OperandData::OperandDataType::LITERAL_VALUE, (yyvsp[-2].intValue), nullptr, 0), (yyvsp[0].intValue))); 
    }
#line 1483 "misc/bison.cpp"
    break;

  case 64: /* ld_instuction: LD DOLLAR IDENTIFIER COMMA REGISTER  */
#line 172 "misc/bison.y"
                                         { 
        Assembler::tokenList.push_back(new LdCommandToken(OperandData(OperandData::OperandDataType::SYMBOL_VALUE, 0, (yyvsp[-2].stringValue), 0), (yyvsp[0].intValue))); 
    }
#line 1491 "misc/bison.cpp"
    break;

  case 65: /* ld_instuction: LD NUMBER COMMA REGISTER  */
#line 175 "misc/bison.y"
                              {
        Assembler::tokenList.push_back(new LdCommandToken(OperandData(OperandData::OperandDataType::LITERAL_VALUE, (yyvsp[-2].intValue), nullptr, 0), (yyvsp[0].intValue)));
        Assembler::tokenList.push_back(new LdCommandToken(OperandData(OperandData::OperandDataType::MEMORY_REGISTER, 0, nullptr, (yyvsp[0].intValue)), (yyvsp[0].intValue))); 

    }
#line 1501 "misc/bison.cpp"
    break;

  case 66: /* ld_instuction: LD IDENTIFIER COMMA REGISTER  */
#line 180 "misc/bison.y"
                                  {
        Assembler::tokenList.push_back(new LdCommandToken(OperandData(OperandData::OperandDataType::SYMBOL_VALUE, 0, (yyvsp[-2].stringValue), 0), (yyvsp[0].intValue)));
        Assembler::tokenList.push_back(new LdCommandToken(OperandData(OperandData::OperandDataType::MEMORY_REGISTER, 0, nullptr, (yyvsp[0].intValue)), (yyvsp[0].intValue))); 
    }
#line 1510 "misc/bison.cpp"
    break;

  case 67: /* ld_instuction: LD REGISTER COMMA REGISTER  */
#line 184 "misc/bison.y"
                                {
        Assembler::tokenList.push_back(new LdCommandToken(OperandData(OperandData::OperandDataType::REGISTER_VALUE, 0, nullptr, (yyvsp[-2].intValue)), (yyvsp[0].intValue))); 
    }
#line 1518 "misc/bison.cpp"
    break;

  case 68: /* ld_instuction: LD LBRACKET REGISTER RBRACKET COMMA REGISTER  */
#line 187 "misc/bison.y"
                                                  {
        Assembler::tokenList.push_back(new LdCommandToken(OperandData(OperandData::OperandDataType::MEMORY_REGISTER, 0, nullptr, (yyvsp[-3].intValue)), (yyvsp[0].intValue))); 
    }
#line 1526 "misc/bison.cpp"
    break;

  case 69: /* ld_instuction: LD LBRACKET REGISTER PLUS NUMBER RBRACKET COMMA REGISTER  */
#line 190 "misc/bison.y"
                                                              {
        Assembler::tokenList.push_back(new LdCommandToken(OperandData(OperandData::OperandDataType::MEMORY_REGISTER_OFFSET_LITERAL, (yyvsp[-3].intValue), nullptr, (yyvsp[-5].intValue)), (yyvsp[0].intValue))); 
    }
#line 1534 "misc/bison.cpp"
    break;

  case 70: /* ld_instuction: LD LBRACKET REGISTER PLUS IDENTIFIER RBRACKET COMMA REGISTER  */
#line 193 "misc/bison.y"
                                                                  {
        Assembler::tokenList.push_back(new LdCommandToken(OperandData(OperandData::OperandDataType::MEMORY_REGISTER_OFFSET_SYMBOL, 0, (yyvsp[-3].stringValue), (yyvsp[-5].intValue)), (yyvsp[0].intValue)));
    }
#line 1542 "misc/bison.cpp"
    break;

  case 71: /* st_instuction: ST REGISTER COMMA DOLLAR NUMBER  */
#line 198 "misc/bison.y"
                                               {
                cout<<"ERROR: StCommandToken: can't change literal value."<<endl;
                exit(1);
            }
#line 1551 "misc/bison.cpp"
    break;

  case 72: /* st_instuction: ST REGISTER COMMA DOLLAR IDENTIFIER  */
#line 202 "misc/bison.y"
                                         {
                cout<<"ERROR: StCommandToken: can't change symbol value."<<endl;
                exit(1);
    }
#line 1560 "misc/bison.cpp"
    break;

  case 73: /* st_instuction: ST REGISTER COMMA NUMBER  */
#line 206 "misc/bison.y"
                              {
        Assembler::tokenList.push_back(new StCommandToken((yyvsp[-2].intValue), OperandData(OperandData::OperandDataType::MEMORY_LITERAL, (yyvsp[0].intValue), nullptr, 0)));
    }
#line 1568 "misc/bison.cpp"
    break;

  case 74: /* st_instuction: ST REGISTER COMMA IDENTIFIER  */
#line 209 "misc/bison.y"
                                  {
        Assembler::tokenList.push_back(new StCommandToken((yyvsp[-2].intValue), OperandData(OperandData::OperandDataType::MEMORY_SYMBOL, 0, (yyvsp[0].stringValue), 0)));
    }
#line 1576 "misc/bison.cpp"
    break;

  case 75: /* st_instuction: ST REGISTER COMMA REGISTER  */
#line 212 "misc/bison.y"
                                {
        Assembler::tokenList.push_back(new StCommandToken((yyvsp[-2].intValue), OperandData(OperandData::OperandDataType::REGISTER_VALUE, 0, nullptr, (yyvsp[0].intValue))));
    }
#line 1584 "misc/bison.cpp"
    break;

  case 76: /* st_instuction: ST REGISTER COMMA LBRACKET REGISTER RBRACKET  */
#line 215 "misc/bison.y"
                                                  {
        Assembler::tokenList.push_back(new StCommandToken((yyvsp[-4].intValue), OperandData(OperandData::OperandDataType::MEMORY_REGISTER, 0, nullptr, (yyvsp[-1].intValue))));
    }
#line 1592 "misc/bison.cpp"
    break;

  case 77: /* st_instuction: ST REGISTER COMMA LBRACKET REGISTER PLUS NUMBER RBRACKET  */
#line 218 "misc/bison.y"
                                                              {
        Assembler::tokenList.push_back(new StCommandToken((yyvsp[-6].intValue), OperandData(OperandData::OperandDataType::MEMORY_REGISTER_OFFSET_LITERAL, (yyvsp[-1].intValue), nullptr, (yyvsp[-3].intValue))));
    }
#line 1600 "misc/bison.cpp"
    break;

  case 78: /* st_instuction: ST REGISTER COMMA LBRACKET REGISTER PLUS IDENTIFIER RBRACKET  */
#line 221 "misc/bison.y"
                                                                  {
        Assembler::tokenList.push_back(new StCommandToken((yyvsp[-6].intValue), OperandData(OperandData::OperandDataType::MEMORY_REGISTER_OFFSET_SYMBOL, 0, (yyvsp[-1].stringValue), (yyvsp[-3].intValue))));
    }
#line 1608 "misc/bison.cpp"
    break;


#line 1612 "misc/bison.cpp"

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
      yyerror (YY_("syntax error"));
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 226 "misc/bison.y"