/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_MISC_BISON_HPP_INCLUDED
# define YY_YY_MISC_BISON_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    DOLLAR = 258,                  /* DOLLAR  */
    PERCENT = 259,                 /* PERCENT  */
    NUMBER = 260,                  /* NUMBER  */
    EOL = 261,                     /* EOL  */
    NUMBER_SIGN = 262,             /* NUMBER_SIGN  */
    COLON = 263,                   /* COLON  */
    DOT = 264,                     /* DOT  */
    COMMA = 265,                   /* COMMA  */
    PLUS = 266,                    /* PLUS  */
    LBRACKET = 267,                /* LBRACKET  */
    RBRACKET = 268,                /* RBRACKET  */
    GLOBAL = 269,                  /* GLOBAL  */
    EXTERN = 270,                  /* EXTERN  */
    SECTION = 271,                 /* SECTION  */
    WORD = 272,                    /* WORD  */
    SKIP = 273,                    /* SKIP  */
    ASCII = 274,                   /* ASCII  */
    EQU = 275,                     /* EQU  */
    END = 276,                     /* END  */
    HALT = 277,                    /* HALT  */
    INT = 278,                     /* INT  */
    IRET = 279,                    /* IRET  */
    CALL = 280,                    /* CALL  */
    RET = 281,                     /* RET  */
    JMP = 282,                     /* JMP  */
    BEQ = 283,                     /* BEQ  */
    BNE = 284,                     /* BNE  */
    BGT = 285,                     /* BGT  */
    PUSH = 286,                    /* PUSH  */
    POP = 287,                     /* POP  */
    XCHG = 288,                    /* XCHG  */
    ADD = 289,                     /* ADD  */
    SUB = 290,                     /* SUB  */
    MUL = 291,                     /* MUL  */
    DIV = 292,                     /* DIV  */
    NOT = 293,                     /* NOT  */
    AND = 294,                     /* AND  */
    OR = 295,                      /* OR  */
    XOR = 296,                     /* XOR  */
    SHL = 297,                     /* SHL  */
    SHR = 298,                     /* SHR  */
    LD = 299,                      /* LD  */
    ST = 300,                      /* ST  */
    CSRRD = 301,                   /* CSRRD  */
    CSRWR = 302,                   /* CSRWR  */
    IDENTIFIER = 303,              /* IDENTIFIER  */
    STRING = 304,                  /* STRING  */
    REGISTER = 305,                /* REGISTER  */
    CONTROL_REGISTER = 306         /* CONTROL_REGISTER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "misc/bison.y"

    uint intValue;
    char* stringValue;
    // ... other types ...

#line 121 "misc/bison.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_MISC_BISON_HPP_INCLUDED  */
