%{
#include <stdio.h>
#include <stdio.h>
	extern int yylex(void);
  extern int yyparse();
  extern FILE *yyin;
	extern void yyerror(const char*);
%}

/* declare tokens */
%token COMMENT
%token DOLLAR
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
%token IDENTIFIER

%%

program : program line
    | line
    ;

line : EOL
    | label EOL
    | label directive EOL
    | label command EOL
    ;

label : IDENTIFIER COLON
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

directive_ascii : ASCII;

directive_equ : EQU ;

directive_end : END;

command : HALT
    ;

symbols : symbols IDENTIFIER
    | IDENTIFIER
    ;

literals : literals |  literal
    | literal
    ;

symbols_or_literals : symbols_or_literals IDENTIFIER
    | symbols_or_literals literal
    | literal
    | IDENTIFIER
    ;

literal : NUMBER;

%%