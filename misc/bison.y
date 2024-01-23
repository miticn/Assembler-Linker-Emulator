%{
    #include <stdio.h>
    #include <iostream>
    #include <string>
    using namespace std;
    #include "../inc/token.hpp"
    #include "../inc/assembler.hpp"
	extern int yylex(void);
    extern int yyparse();
    extern FILE *yyin;
	extern void yyerror(const char*);
%}

%output "misc/bison.cpp"
%defines "misc/bison.hpp"

%union {
    int intValue;
    char* stringValue;
    // ... other types ...
}


/* declare tokens */
%token DOLLAR
%token PERCENT
%token NUMBER
%token EOL
%token NUMBER_SIGN
%token COLON
%token DOT
%token COMMA
%token PLUS
%token LBRACKET
%token RBRACKET
%token GLOBAL
%token EXTERN
%token SECTION
%token WORD
%token SKIP
%token ASCII
%token EQU
%token END
%token HALT
%token INT
%token IRET
%token CALL
%token RET
%token JMP
%token BEQ
%token BNE
%token BGT
%token PUSH
%token POP
%token XCHG
%token ADD
%token SUB
%token MUL
%token DIV
%token NOT
%token AND
%token OR
%token XOR
%token SHL
%token SHR
%token LD
%token ST
%token CSRRD
%token CSRWR
%token <stringValue> IDENTIFIER
%token <stringValue> STRING
%token <intValue> REGISTER
%token <intValue> CONTROL_REGISTER

%%

program : program line
    | line
    ;

line : EOL
    | label EOL
    | label directive EOL
    | label command EOL
    | directive EOL
    | command EOL
    ;

label : IDENTIFIER COLON  {
        Assembler::tokenList.push_back(new LabelToken($1));
    }
    ;

directive: directive_global
    | directive_extern
    | directive_section
    | directive_word
    | directive_skip
    | directive_ascii
    | directive_equ
    | directive_end
    ;

directive_global : GLOBAL IDENTIFIER { Assembler::tokenList.push_back(new GlobalDirectiveToken($2));}
    | directive_global COMMA IDENTIFIER { Assembler::tokenList.push_back(new GlobalDirectiveToken($3));}
    ;

directive_extern : EXTERN IDENTIFIER { Assembler::tokenList.push_back(new ExternDirectiveToken($2));}
    | directive_extern COMMA IDENTIFIER { Assembler::tokenList.push_back(new ExternDirectiveToken($3));}
    ;

directive_section : SECTION IDENTIFIER { Assembler::tokenList.push_back(new SectionDirectiveToken($2));}
    ;

directive_word : WORD literal
    | WORD IDENTIFIER
    | directive_word COMMA literal
    | directive_word COMMA IDENTIFIER
    ;

directive_skip : SKIP literal;

directive_ascii : ASCII STRING;

directive_equ : EQU IDENTIFIER COMMA NUMBER;

directive_end : END;

literal : NUMBER;


command : HALT { Assembler::tokenList.push_back(new HaltCommandToken);}
    | INT { Assembler::tokenList.push_back(new IntCommandToken);}
    | IRET { 
        Assembler::tokenList.push_back(new RetCommandToken);
        Assembler::tokenList.push_back(new PopStatusCommandToken);
    }
    | RET { Assembler::tokenList.push_back(new RetCommandToken);}
    | PUSH REGISTER { Assembler::tokenList.push_back(new PushCommandToken($2));}
    | POP REGISTER { Assembler::tokenList.push_back(new PopCommandToken($2));}
    | XCHG REGISTER COMMA REGISTER { Assembler::tokenList.push_back(new XchgCommandToken($2, $4));}
    | ADD REGISTER COMMA REGISTER { Assembler::tokenList.push_back(new AddCommandToken($2, $4));}
    | SUB REGISTER COMMA REGISTER { Assembler::tokenList.push_back(new SubCommandToken($2, $4));}
    | MUL REGISTER COMMA REGISTER { Assembler::tokenList.push_back(new MulCommandToken($2, $4));}
    | DIV REGISTER COMMA REGISTER { Assembler::tokenList.push_back(new DivCommandToken($2, $4));}
    | NOT REGISTER { Assembler::tokenList.push_back(new NotCommandToken($2));}
    | AND REGISTER COMMA REGISTER { Assembler::tokenList.push_back(new AndCommandToken($2, $4));}
    | OR REGISTER COMMA REGISTER { Assembler::tokenList.push_back(new OrCommandToken($2, $4));}
    | XOR REGISTER COMMA REGISTER { Assembler::tokenList.push_back(new XorCommandToken($2, $4));}
    | SHL REGISTER COMMA REGISTER { Assembler::tokenList.push_back(new ShlCommandToken($2, $4));}
    | SHR REGISTER COMMA REGISTER { Assembler::tokenList.push_back(new ShrCommandToken($2, $4));}
    | CSRRD CONTROL_REGISTER COMMA REGISTER { Assembler::tokenList.push_back(new CsrrdCommandToken($2, $4));}
    | CSRWR REGISTER COMMA CONTROL_REGISTER { Assembler::tokenList.push_back(new CsrwrCommandToken($2, $4));}
    
    | LD operand_data COMMA REGISTER
    | ST REGISTER COMMA operand_data
    | CALL operand_jump
    | JMP operand_jump
    | BEQ REGISTER COMMA REGISTER COMMA operand_jump
    | BNE REGISTER COMMA REGISTER COMMA operand_jump
    | BGT REGISTER COMMA REGISTER COMMA operand_jump
    ;

operand_jump : literal
    | IDENTIFIER
    ;

operand_data : DOLLAR literal
    | DOLLAR IDENTIFIER
    | literal
    | IDENTIFIER
    | REGISTER
    | LBRACKET REGISTER RBRACKET
    | LBRACKET REGISTER PLUS literal RBRACKET
    | LBRACKET REGISTER PLUS IDENTIFIER RBRACKET
    ;

%%