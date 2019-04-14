package com.company;

import java.io.*;

public class Main {
    /* Character classes */
    public static final int LETTER = 0;
    public static final int DIGIT = 1;
    public static final int EOF = -1;
    public static final int UNKNOWN = 99;
    /* Token codes */
    public static final int INT_LIT = 10;
    public static final int IDENT = 11;
    public static final int ASSIGN_OP = 20;
    public static final int ADD_OP = 21;
    public static final int SUB_OP = 22;
    public static final int MULT_OP = 23;
    public static final int DIV_OP = 24;
    public static final int LEFT_PAREN = 25;
    public static final int RIGHT_PAREN = 26;
    public static final int HASH_TAG = 27; // #
    public static final int LEFT_CURL = 28;    // {
    public static final int RIGHT_CURL = 29;   // }
    public static final int LESS_THAN = 30;    // <
    public static final int GREATER_THAN = 31; // >
    public static final int SEMI_COLON = 32;   // ;
    public static final int VERTICAL = 33;     // |
    public static final int TILDE = 34;    // ~
    public static final int BACK_SLASH = 35;   // '\'
    public static final int DLB_QUO = 36;   // "
    public static final int SNG_QUO = 37;  // '
    public static final int AMPERSAND = 38;  // &
    public static final int UNDERBAR = 39;  // _
    public static final int PERIOD = 40;  // .
    public static final int PERCENT = 41;  // %
    public static final int COMMA = 42;  // ,

    public static FileInputStream fr;
    public static int nextToken;
    public static int charClass;
    public static char nextChar;
    public static int lexLen;
    public static char []lexeme = new char[100];
    public static String buf;

    public static void main(String[] args) {
        File fp;
        try{
            fp = new File("/Users/kyungyoungheo/Projects/SSU-cse-linux/ssu_pl/java/src/com/company/front.in");
            fr = new FileInputStream(fp);

        }catch(FileNotFoundException e){
            System.out.println(e);

        }catch(IOException e){
            System.out.println(e);
        }
        getChar();
        System.out.println("nextToken = "+nextToken);
        do {
            lex();
        } while(nextToken != -1);

    }
    public static void addChar(){
        if(lexLen < 98){
            lexeme[lexLen++] = nextChar;
            lexeme[lexLen] = 0;
        }
        else{
            System.out.println("Error - lexeme is too long");
        }
    }
    public static void getChar(){
        try{
            if((nextChar = (char)fr.read()) != -1){
//                System.out.println(nextChar);
                if(Character.isAlphabetic(nextChar)){
                    charClass = LETTER;
                }
                else if(Character.isDigit(nextChar)){
                    charClass = DIGIT;
                }
                else{
                    charClass = UNKNOWN;
                }
            }
            else{
                charClass = -1;
            }
        }catch(IOException e){
            System.out.println(e);
        }
    }
    public static void getNonBlank(){
        while(Character.isWhitespace(nextChar)){
            getChar();
        }
    }
    public static int lex(){
        String output;
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
        output = String.valueOf(lexeme);
        System.out.print("Next token is :" + nextToken + ", Next lexeme is ");
        for(int i=0; i<lexLen; i++){
            System.out.print(lexeme[i]);
        }
        System.out.println();
        return nextToken;
    }
    public static int lookup(char ch){
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
    public static void isReserved(){
        String []keywords = {
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
            if(keywords[i].equals(buf)){
                System.out.println(buf + " is keyword");
            }
        }
    }
    public static void cpybufstr(){

        // char[] to String
        StringBuilder sb = new StringBuilder();
        for(int i=0; i<lexLen; i++){
            sb.append(lexeme[i]);
        }
        buf = sb.toString();
//        System.out.println("sb = "+sb);
    }
}
