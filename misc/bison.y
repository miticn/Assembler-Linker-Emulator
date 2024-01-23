%{
    #include <stdio.h>
    #include <iostream>
    #include <string>
    using namespace std;
    #include "../inc/token.hpp"
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
%token STRING
%token REGISTER
%token CONTROL_REGISTER

%%

program : program line
    | line
    ;

line : EOL
    | label EOL
    | label directive EOL
    | label command EOL
    | directive EOL
    | command EOL{
        cout << "COMMAND EOL" << endl;
    }
    ;

label : IDENTIFIER COLON  {
    cout<<$1 <<" test" << endl;
    tokenList.push_back(new LabelToken($1));
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

directive_global : GLOBAL symbols
    ;

directive_extern : EXTERN symbols
    ;

directive_section : SECTION IDENTIFIER;

directive_word : WORD symbols_or_literals;

directive_skip : SKIP literal;

directive_ascii : ASCII STRING;

directive_equ : EQU literal COMMA ;

directive_end : END;

symbols : symbols COMMA IDENTIFIER
    | IDENTIFIER
    ;

symbols_or_literals : symbols_or_literals COMMA IDENTIFIER
    | symbols_or_literals COMMA literal
    | literal
    | IDENTIFIER
    ;

literal : NUMBER;


command : HALT
    | INT {cout << "INT" << endl;}
    | IRET
    | RET
    | PUSH REGISTER
    | POP REGISTER
    | XCHG REGISTER COMMA REGISTER
    | ADD REGISTER COMMA REGISTER
    | SUB REGISTER COMMA REGISTER
    | MUL REGISTER COMMA REGISTER
    | DIV REGISTER COMMA REGISTER
    | NOT REGISTER
    | AND REGISTER COMMA REGISTER
    | OR REGISTER COMMA REGISTER
    | XOR REGISTER COMMA REGISTER
    | SHL REGISTER COMMA REGISTER
    | SHR REGISTER COMMA REGISTER
    | CSRRD CONTROL_REGISTER COMMA REGISTER
    | CSRWR REGISTER COMMA CONTROL_REGISTER
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
    | PERCENT REGISTER
    | LBRACKET PERCENT REGISTER RBRACKET
    | LBRACKET PERCENT REGISTER PLUS literal RBRACKET
    | LBRACKET PERCENT REGISTER PLUS IDENTIFIER RBRACKET
    ;

%%