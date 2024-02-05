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
    LPAREN = 269,                  /* LPAREN  */
    RPAREN = 270,                  /* RPAREN  */
    GLOBAL = 271,                  /* GLOBAL  */
    EXTERN = 272,                  /* EXTERN  */
    SECTION = 273,                 /* SECTION  */
    WORD = 274,                    /* WORD  */
    SKIP = 275,                    /* SKIP  */
    ASCII = 276,                   /* ASCII  */
    EQU = 277,                     /* EQU  */
    END = 278,                     /* END  */
    HALT = 279,                    /* HALT  */
    INT = 280,                     /* INT  */
    IRET = 281,                    /* IRET  */
    CALL = 282,                    /* CALL  */
    RET = 283,                     /* RET  */
    JMP = 284,                     /* JMP  */
    BEQ = 285,                     /* BEQ  */
    BNE = 286,                     /* BNE  */
    BGT = 287,                     /* BGT  */
    PUSH = 288,                    /* PUSH  */
    POP = 289,                     /* POP  */
    XCHG = 290,                    /* XCHG  */
    ADD = 291,                     /* ADD  */
    SUB = 292,                     /* SUB  */
    MUL = 293,                     /* MUL  */
    DIV = 294,                     /* DIV  */
    NOT = 295,                     /* NOT  */
    AND = 296,                     /* AND  */
    OR = 297,                      /* OR  */
    XOR = 298,                     /* XOR  */
    SHL = 299,                     /* SHL  */
    SHR = 300,                     /* SHR  */
    LD = 301,                      /* LD  */
    ST = 302,                      /* ST  */
    CSRRD = 303,                   /* CSRRD  */
    CSRWR = 304,                   /* CSRWR  */
    IDENTIFIER = 305,              /* IDENTIFIER  */
    STRING = 306,                  /* STRING  */
    REGISTER = 307,                /* REGISTER  */
    CONTROL_REGISTER = 308         /* CONTROL_REGISTER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "misc/bison.y"

    uint intValue;
    char* stringValue;
    // ... other types ...

#line 123 "misc/bison.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_MISC_BISON_HPP_INCLUDED  */
