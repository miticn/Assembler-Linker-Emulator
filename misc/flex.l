%{
    //C code
    enum yytokentyp {
        COMMENT,
        DOLLAR,
        NUMBER,
        EOL,
        NUMBER_SIGN,
        COLON,
        DOT,
        COMMA,
        PLUS,
        LBRACKET,
        RBRACKET,
        GLOBAL=10,
        EXTERN,
        SECTION,
        WORD,
        SKIP,
        ASCII,
        EQU,
        END,
        HALT=50,
        INT,
        IRET,
        CALL,
        RET,
        JMP,
        BEQ,
        BNE,
        BGT,
        PUSH,
        POP,
        XCHG,
        ADD,
        SUB,
        MUL,
        DIV,
        NOT,
        AND,
        OR,
        XOR,
        SHL,
        SHR,
        LD,
        ST,
        CSRRD,
        CSRWR,
        IDENTIFIER = 100,

    };
%}

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

void error(){
    printf("Error");
}

yywrap(){}

main(int argc, char **argv)
{
  int tok;

  while(tok = yylex()) {
    printf("%d", tok);
    printf("\n");
  }
}
