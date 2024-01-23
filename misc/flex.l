%{
    //C code
    #include "bison.hpp"
    #include <iostream>
    using namespace std;
%}

%option outfile="misc/flex.cpp" header-file="misc/flex.hpp"

%option noyywrap

COMMENT   #.*\n
NUMBER ([0-9])+
IDENTIFIER [A-Za-z_][A-Za-z0-9_]*
WHITESPACE [ \t]
STRING   \".*\"
REGISTER %r(1[0-5]|[0-9])

%%
{NUMBER} {return NUMBER;}
{COMMENT} {cout << "comment" << endl; return EOL;}
"\n" {return EOL;}
{WHITESPACE}  {}
"#" {return NUMBER_SIGN;}
"$" {return DOLLAR;}
"%" {return PERCENT;}
":" {return COLON;}
"." {return DOT;}
"," {return COMMA;}
"+" {return PLUS;}
"[" {return LBRACKET;}
"]" {return RBRACKET;}
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
{STRING} {return STRING;}
{REGISTER} {return REGISTER;}
"" {return CONTROL_REGISTER;}


{IDENTIFIER} {
    yylval.stringValue = strdup(yytext);
    return IDENTIFIER;
}
%%

int yyerror(const char* msg)
{
    fprintf(stderr, "lexer error: %s\n", msg);
    return 0;
}