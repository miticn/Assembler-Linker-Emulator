%{
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

%}

%output "misc/bison.cpp"
%defines "misc/bison.hpp"

%union {
    uint intValue;
    char* stringValue;
    // ... other types ...
}

/* declare tokens */
%token DOLLAR
%token PERCENT
%token <intValue> NUMBER
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

directive_word : WORD NUMBER { Assembler::tokenList.push_back(new WordDirectiveToken($2));}
    | WORD IDENTIFIER { Assembler::tokenList.push_back(new WordDirectiveToken(0,$2,true));}
    | directive_word COMMA NUMBER { Assembler::tokenList.push_back(new WordDirectiveToken($3));}
    | directive_word COMMA IDENTIFIER { Assembler::tokenList.push_back(new WordDirectiveToken(0,$3,true));}
    ;

directive_skip : SKIP NUMBER { Assembler::tokenList.push_back(new SkipDirectiveToken($2));}
    ;

directive_ascii : ASCII STRING { Assembler::tokenList.push_back(new AsciiDirectiveToken($2));}
    ;

directive_equ : EQU IDENTIFIER COMMA NUMBER { Assembler::tokenList.push_back(new EquDirectiveToken($2, $4));}
    ;

directive_end : END { Assembler::tokenList.push_back(new EndDirectiveToken);}
    ;


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

    | CALL NUMBER { Assembler::tokenList.push_back(new CallCommandToken(OperandJump($2))); }
    | CALL IDENTIFIER { Assembler::tokenList.push_back(new CallCommandToken(OperandJump($2))); }
    | JMP NUMBER { Assembler::tokenList.push_back(new JmpCommandToken(OperandJump($2))); }
    | JMP IDENTIFIER { Assembler::tokenList.push_back(new JmpCommandToken(OperandJump($2))); }
    | BEQ REGISTER COMMA REGISTER COMMA NUMBER { Assembler::tokenList.push_back(new BeqCommandToken($2, $4, OperandJump($6))); }
    | BEQ REGISTER COMMA REGISTER COMMA IDENTIFIER { Assembler::tokenList.push_back(new BeqCommandToken($2, $4, OperandJump($6))); }
    | BNE REGISTER COMMA REGISTER COMMA NUMBER { Assembler::tokenList.push_back(new BneCommandToken($2, $4, OperandJump($6))); }
    | BNE REGISTER COMMA REGISTER COMMA IDENTIFIER { Assembler::tokenList.push_back(new BneCommandToken($2, $4, OperandJump($6))); }
    | BGT REGISTER COMMA REGISTER COMMA NUMBER { Assembler::tokenList.push_back(new BgtCommandToken($2, $4, OperandJump($6))); }
    | BGT REGISTER COMMA REGISTER COMMA IDENTIFIER { Assembler::tokenList.push_back(new BgtCommandToken($2, $4, OperandJump($6))); }
    | ld_instuction
    | st_instuction
    ;

ld_instuction: LD DOLLAR NUMBER COMMA REGISTER { 
        Assembler::tokenList.push_back(new LdCommandToken(OperandData(OperandData::OperandDataType::LITERAL_VALUE, $3, nullptr, 0), $5)); 
    }
    | LD DOLLAR IDENTIFIER COMMA REGISTER{ 
        Assembler::tokenList.push_back(new LdCommandToken(OperandData(OperandData::OperandDataType::SYMBOL_VALUE, 0, $3, 0), $5)); 
    }
    | LD NUMBER COMMA REGISTER{
        Assembler::tokenList.push_back(new LdCommandToken(OperandData(OperandData::OperandDataType::LITERAL_VALUE, $2, nullptr, 0), $4));
        Assembler::tokenList.push_back(new LdCommandToken(OperandData(OperandData::OperandDataType::MEMORY_REGISTER, 0, nullptr, $4), $4)); 

    }
    | LD IDENTIFIER COMMA REGISTER{
        Assembler::tokenList.push_back(new LdCommandToken(OperandData(OperandData::OperandDataType::SYMBOL_VALUE, 0, $2, 0), $4));
        Assembler::tokenList.push_back(new LdCommandToken(OperandData(OperandData::OperandDataType::MEMORY_REGISTER, 0, nullptr, $4), $4)); 
    }
    | LD REGISTER COMMA REGISTER{
        Assembler::tokenList.push_back(new LdCommandToken(OperandData(OperandData::OperandDataType::REGISTER_VALUE, 0, nullptr, $2), $4)); 
    }
    | LD LBRACKET REGISTER RBRACKET COMMA REGISTER{
        Assembler::tokenList.push_back(new LdCommandToken(OperandData(OperandData::OperandDataType::MEMORY_REGISTER, 0, nullptr, $3), $6)); 
    }
    | LD LBRACKET REGISTER PLUS NUMBER RBRACKET COMMA REGISTER{
        Assembler::tokenList.push_back(new LdCommandToken(OperandData(OperandData::OperandDataType::MEMORY_REGISTER_OFFSET_LITERAL, $5, nullptr, $3), $8)); 
    }
    | LD LBRACKET REGISTER PLUS IDENTIFIER RBRACKET COMMA REGISTER{
        Assembler::tokenList.push_back(new LdCommandToken(OperandData(OperandData::OperandDataType::MEMORY_REGISTER_OFFSET_SYMBOL, 0, $5, $3), $8));
    }
    ;

st_instuction: ST REGISTER COMMA DOLLAR NUMBER {
                cout<<"ERROR: StCommandToken: can't change literal value."<<endl;
                exit(1);
            }
    | ST REGISTER COMMA DOLLAR IDENTIFIER{
                cout<<"ERROR: StCommandToken: can't change symbol value."<<endl;
                exit(1);
    }
    | ST REGISTER COMMA NUMBER{
        Assembler::tokenList.push_back(new StCommandToken($2, OperandData(OperandData::OperandDataType::MEMORY_LITERAL, $4, nullptr, 0)));
    }
    | ST REGISTER COMMA IDENTIFIER{
        Assembler::tokenList.push_back(new StCommandToken($2, OperandData(OperandData::OperandDataType::MEMORY_SYMBOL, 0, $4, 0)));
    }
    | ST REGISTER COMMA REGISTER{
        Assembler::tokenList.push_back(new StCommandToken($2, OperandData(OperandData::OperandDataType::REGISTER_VALUE, 0, nullptr, $4)));
    }
    | ST REGISTER COMMA LBRACKET REGISTER RBRACKET{
        Assembler::tokenList.push_back(new StCommandToken($2, OperandData(OperandData::OperandDataType::MEMORY_REGISTER, 0, nullptr, $5)));
    }
    | ST REGISTER COMMA LBRACKET REGISTER PLUS NUMBER RBRACKET{
        Assembler::tokenList.push_back(new StCommandToken($2, OperandData(OperandData::OperandDataType::MEMORY_REGISTER_OFFSET_LITERAL, $7, nullptr, $5)));
    }
    | ST REGISTER COMMA LBRACKET REGISTER PLUS IDENTIFIER RBRACKET{
        Assembler::tokenList.push_back(new StCommandToken($2, OperandData(OperandData::OperandDataType::MEMORY_REGISTER_OFFSET_SYMBOL, 0, $7, $5)));
    }
    ;

%%