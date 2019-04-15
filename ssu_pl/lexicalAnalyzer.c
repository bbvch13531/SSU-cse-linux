#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function declarations */ 
void addChar(void);
void getChar(void);
void getNonBlank(void);
int lex(void);
int lookup(char);
void isReserved(void);
void cpybufstr(void);
/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define HASH_TAG 27 // #
#define LEFT_CURL 28    // {
#define RIGHT_CURL 29   // }
#define LESS_THAN 30    // <
#define GREATER_THAN 31 // >
#define SEMI_COLON 32   // ;
#define VERTICAL 33     // |
#define TILDE 34    // ~
#define BACK_SLASH 35   // '\'
#define DLB_QUO 36   // "
#define SNG_QUO 37  // '
#define AMPERSAND 38  // &
#define UNDERBAR 39  // _
#define PERIOD 40  // .
#define PERCENT 41  // %
#define COMMA 42  // ,



FILE * fp;
int lexLen;
char lexeme[100], buf[100];
char nextToken;
char charClass;
int nextChar;

int main(int argc, char **argv){

    if((fp = fopen("front.in", "r")) == NULL){
        printf("Error - cannot open front.in \n");
    }
    else{

        getChar();
        printf("nextToken = %c\n",nextToken);
        do {
            lex();

        } while(nextToken != EOF);
        
    }
    return 0;
}
void addChar(void){
    if(lexLen <= 98){
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    }
    else{
        printf("Error - lexeme is too long\n");
    }
}
void getChar(void){

    if((nextChar = getc(fp)) != EOF){
        if(isalpha(nextChar)){
            charClass = LETTER;
        }
        else if(isdigit(nextChar)){
            charClass = DIGIT;
        }
        else{
            // printf("%c ",nextChar);
            charClass = UNKNOWN;
        }
    }
    else{
        charClass = EOF;
    }
}

void getNonBlank(void){
    while(isspace(nextChar))
        getChar();
}

int lex(void){
    lexLen = 0;
    getNonBlank();

    switch(charClass){
        /* Parse identifiers */ 
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar(); 
            }
            nextToken = IDENT;
            cpybufstr();
            isReserved();
            break;

        /* Parse integer literals */ 
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar(); 
            }
            nextToken = INT_LIT; 
            cpybufstr();
            break;

        /* Parentheses and operators */ 
        case UNKNOWN:
            lookup(nextChar); 
            getChar(); 
            cpybufstr();
            break;

        /* EOF */ 
        case EOF:
            nextToken = EOF; 
            lexeme[0] = 'E'; 
            lexeme[1] = 'O'; 
            lexeme[2] = 'F'; 
            lexeme[3] = 0; 
            break;
    } /* End of switch */
    char output[30]="";
    if(nextToken == IDENT)
        strcpy(output, "IDENTIFIER");
    else if(nextToken == INT_LIT)
        strcpy(output, "INT_LIT");
    else if(nextToken == EOF)
        strcpy(output, "EOF");
    else
        strcpy(output, "OTHERS");
    printf("Next token is : %s, Next lexeme is %s\n", output, lexeme);
    return nextToken;
}

int lookup(char ch){
    switch (ch) { 
        case '=':
            addChar();
            nextToken = ASSIGN_OP;
            break;
        case '(':
            addChar();
            nextToken = LEFT_PAREN; 
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN; 
            break;
        case '+':
            addChar(); 
            nextToken = ADD_OP; 
            break;
        case '-':
            addChar(); 
            nextToken = SUB_OP; 
            break;
        case '*':
            addChar(); 
            nextToken = MULT_OP; 
            break;
        case '/':
            addChar(); 
            nextToken = DIV_OP; 
            break;
        case '#':
            addChar(); 
            nextToken = HASH_TAG;
            break;
        case '{':
            addChar(); 
            nextToken = LEFT_CURL;
            break;
        case '}':
            addChar(); 
            nextToken = RIGHT_CURL;
            break;
        case '<':
            addChar(); 
            nextToken = LESS_THAN;
            break;
        case '>':
            addChar(); 
            nextToken = GREATER_THAN;
            break;
        case ';':
            addChar(); 
            nextToken = SEMI_COLON; 
            break;
        case '|':
            addChar(); 
            nextToken = VERTICAL; 
            break;
        case '~':
            addChar(); 
            nextToken = TILDE; 
            break;
        case '\\':
            addChar(); 
            nextToken = BACK_SLASH;
            break;
        case '"':
            addChar(); 
            nextToken = DLB_QUO;
            break;
        case '\'':
            addChar(); 
            nextToken = SNG_QUO;
            break;
        case '&':
            addChar(); 
            nextToken = AMPERSAND;
            break;
        case '_':
            addChar(); 
            nextToken = UNDERBAR;
            break;
        case '.':
            addChar(); 
            nextToken = PERIOD;
            break;  
        case '%':
            addChar(); 
            nextToken = PERCENT;
            break;
        case ',':
            addChar(); 
            nextToken = COMMA;
            break;
        default: 
            addChar(); 
            nextToken = EOF; 
            break;
    }

    return nextToken;
}

void isReserved(void){
    /*
    for if int double char long 
    
    */
   char keywords[50][20]={
       "auto",
       "break",
       "case",
       "char",
       "const",
       "continue",
       "default",
       "do",
       "int",
       "long",
       "long long",
       "register",
       "return",
       "short",
       "signed",
       "sizeof",
       "static",
       "struct",
       "switch",
       "typedef",
       "union",
       "unsigned",
       "void",
       "volatile",
       "while",
       "double",
       "else",
       "enum",
       "extern",
       "float",
       "for",
       "goto",
       "if",
       "include"
    }; 
   // 34
    for(int i=0; i<34; i++){
        if(strcmp(buf,keywords[i]) == 0){

        printf("%s is keyword\n",buf);
        }
    }
}

void cpybufstr(void){
    memset(buf,0,sizeof(buf));
    strcpy(buf, lexeme);
}