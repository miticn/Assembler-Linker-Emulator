%{
    //C code
    #include "bison.tab.h"
%}

%option noyywrap

COMMENT   "#".*\n
NUMBER ([0-9])+
IDENTIFIER [A-Za-z_][A-Za-z0-9_]*
WHITESPACE [ \t]

%%
{NUMBER} {return NUMBER;}
{COMMENT} {}
"\n" {return EOL;}
{WHITESPACE}  {}
"#" {return NUMBER_SIGN;}
"$" {return DOLLAR;}
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


{IDENTIFIER} {return IDENTIFIER;}
%%

int yyerror(const char* msg)
{
    fprintf(stderr, "lexer error: %s\n", msg);
    return 0;
}

int main(int argc, char** argv)
{
    yyin = fopen(argv[1], "r");
    int token;
    while(token = yylex())
    {
        printf("%d\n", token);
    }
    return 0;
}