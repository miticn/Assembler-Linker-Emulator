%{
    //C code
    #include "bison.hpp"
    #include <iostream>
    #include <cstdint>
    using namespace std;
%}

%option outfile="misc/flex.cpp" header-file="misc/flex.hpp"

%option noyywrap
%option yylineno

COMMENT   #.*\n

NUMBERDEC [0-9]|[1-9][0-9]*
NUMBERHEX 0[Xx][0-9A-Fa-f]+
NUMBEROCT 0[0-7]+
NUMBERBIN 0[Bb][01]+
IDENTIFIER [A-Za-z_][A-Za-z0-9_]*
WHITESPACE [ \t]
STRING   \".*\"
REGISTER %r(1[0-5]|[0-9])|%sp|%pc
CONTROL_REGISTER %cr[0-2]|%status|%handler|%cause

%%
{NUMBERDEC}|{NUMBERHEX}|{NUMBEROCT}|{NUMBERBIN} {
    yylval.intValue = strtol(yytext, NULL, 0);
    return NUMBER;
}
{COMMENT} {return EOL;}
"\n" {return EOL;}
{WHITESPACE}  {}
"#" {return NUMBER_SIGN;}
"$" {return DOLLAR;}
"%" {return PERCENT;}
":" {return COLON;}
"." {return DOT;}
"," {return COMMA;}
"+" {return PLUS;}
"-" {return MINUS;}
"[" {return LBRACKET;}
"]" {return RBRACKET;}
"(" {return LPAREN;}
")" {return RPAREN;}
".global" {return GLOBAL;}
".extern" {return EXTERN;}
".section" {return SECTION;}
".word" {return WORD;}
".skip" {return SKIP;}
".ascii" {return ASCII;}
".equ" {return EQU;}
".end" {return END;}
"halt" {return HALT;}
"int" {return INT;}
"iret" {return IRET;}
"call" {return CALL;}
"ret" {return RET;}
"jmp" {return JMP;}
"beq" {return BEQ;}
"bne" {return BNE;}
"bgt" {return BGT;}
"push" {return PUSH;}
"pop" {return POP;}
"xchg" {return XCHG;}
"add" {return ADD;}
"sub" {return SUB;}
"mul" {return MUL;}
"div" {return DIV;}
"not" {return NOT;}
"and" {return AND;}
"or" {return OR;}
"xor" {return XOR;}
"shl" {return SHL;}
"shr" {return SHR;}
"ld" {return LD;}
"st" {return ST;}
"csrrd" {return CSRRD;}
"csrwr" {return CSRWR;}
{STRING} {
    //remove quotes
    yytext[strlen(yytext) - 1] = '\0';
    yylval.stringValue = strdup(yytext + 1);
    return STRING;
}
{REGISTER} {
    if (yytext[1] == 's' && yytext[2] == 'p')
        yylval.intValue = 14;
    else if (yytext[1] == 'p' && yytext[2] == 'c')
        yylval.intValue = 15;
    else
        yylval.intValue = atoi(yytext + 2);
    return REGISTER;
}
{CONTROL_REGISTER} {
    if (yytext[1]=='s')
        yylval.intValue = 0;
    else if (yytext[1]=='h')
        yylval.intValue = 1;
    else if (yytext[1]=='c')
        yylval.intValue = 2;
    else 
        yylval.intValue = atoi(yytext + 3);
    return CONTROL_REGISTER;
}


{IDENTIFIER} {
    yylval.stringValue = strdup(yytext);
    return IDENTIFIER;
}
%%

int yyerror(const char* msg)
{
    fprintf(stderr, "%s. Error line: %d at %s\n",msg, yylineno,yytext);
    return 0;
}