#include "front.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
/* Global Variables */
int nextToken;
char *tokennames;
fpos_t position; 
int syntaxError = 0;
// track position of input stream

/* Local Variables */
static int charClass;
 char lexeme[100];
static char nextChar;
static int lexLen;
static FILE *in_fp;


/* Local Function Declarations */
static void addChar();
static void getChar();
static void getNonBlank();




/* main driver */
int main(int argc, char* argv[]) {
  printf("DCooke Analyzer :: R11712482 \n \n");
  if (argc != 2) {
    printf("File was not provided");
    return 2;
  }

  
  if ((in_fp = fopen(argv[1], "r")) == NULL) {
    printf("ERROR - cannot open front.in \n");
    return 3; // Exit code 3 for non-existing file
  } 
    //if (argc != 2) {
      //printf("Error: Please provide a source file as input.\n");
      //return 2; // Exit code 2 for missing input file
    //}
  else {
    getChar();
    do {
      lex();
      statement();
      
    } while (nextToken != EOF);
  }
if (syntaxError==1) {
    return 1; // Exit code 1 for syntax error
  } 
else {
    printf("Syntax Validated\n");
    return 0; // Exit code 0 for no syntax error
  }
}

/* lookup - a function to lookup operators and parentheses and return the token
 */
static int lookup(char ch) {
  switch (ch) {
  case '(':
    addChar();
    nextToken = LEFT_PAREN;
    tokennames = "LEFT_PAREN";
    break;
  case ')':
    addChar();
    nextToken = RIGHT_PAREN;
    tokennames = "RIGHT_PAREN";
    break;
    case '+':
    addChar();
    fgetpos(in_fp, &position);
    getChar();
    if (nextChar == '+') {
      addChar();
      nextToken = INC_OP;
      tokennames = "INC_OP";
    } else {
      fsetpos(in_fp, &position);
      nextToken = ADD_OP;
      tokennames = "ADD_OP";
    }
    break;
  case '-':
    addChar();
    fgetpos(in_fp, &position);
    getChar();
    if (nextChar == '-') {
      addChar();
      nextToken = DEC_OP;
      tokennames = "DEC_OP";
    } else {
      fsetpos(in_fp, &position);
      nextToken = SUB_OP;
      tokennames = "SUB_OP";
    }
    break;
  case '*':
    addChar();
    nextToken = MULT_OP;
    tokennames = "MULT_OP";
    break;
  case '/':
    addChar();
    nextToken = DIV_OP;
    tokennames = "DIV_OP";
    break;
  case ';':
    addChar();
    nextToken = SEMICOLON;
    tokennames = "SEMICOLON";
    break;
  case '}':
    addChar();
    nextToken = RIGHT_CBRACE;
    tokennames = "RIGHT_CBRACE";
    break;
  case '{':
    addChar();
    nextToken = LEFT_CBRACE;
    tokennames = "LEFT_CBRACE";
    break;
  case '=':
    addChar();
    fgetpos(in_fp, &position);
    getChar();
    if (nextChar == '=') {
      addChar();
      nextToken = EQUAL_OP;
      tokennames = "EQUAL_OP";
    } else {
      fsetpos(in_fp, &position);
      nextToken = ASSIGN_OP;
      tokennames = "ASSIGN_OP";
    }
    break;
  case '!':
    addChar();
    fgetpos(in_fp, &position);
    getChar();
    if (nextChar == '=') {
      addChar();
      nextToken = NEQUAL_OP;
      tokennames = "NEQUAL_OP ";
    } else {
      fsetpos(in_fp, &position);
      nextToken = UNKNOWN;
      tokennames = "UNKNOWN";
    }
    break;
  case '<':
    addChar();
    fgetpos(in_fp, &position);
    getChar();
    if (nextChar == '=') {
      addChar();
      nextToken = LEQUAL_OP;
      tokennames = "LEQUAL_OP";
    } else {
      fsetpos(in_fp, &position);
      nextToken = LESSER_OP;
      tokennames = "LESSER_OP";
    }
    break;
  case '>':
    addChar();
    fgetpos(in_fp, &position);
    getChar();
    if (nextChar == '=') {
      addChar();
      nextToken = GEQUAL_OP;
      tokennames = "GEQUAL_OP";
    } else {
      fsetpos(in_fp, &position);
      nextToken = GREATER_OP;
      tokennames = "GREATER_OP";
    }
    break;

  default:
    addChar();
    nextToken = UNKNOWN;
    tokennames = "UNKNOWN";
    break;
    nextToken = EOF;
    break;
  }
  return nextToken;
}

/* addChar - a function to add nextChar to lexeme */
static void addChar() {
  if (lexLen <= 98) {
    lexeme[lexLen++] = nextChar;
    lexeme[lexLen] = 0;
  } else {
    printf("Error - lexeme is too long \n");
  }
}

/* getChar - a function to get the next character of input and determine its
 * character class */
static void getChar() {
  if ((nextChar = getc(in_fp)) != EOF) {
    if (isalpha(nextChar))
      charClass = LETTER;
    else if (isdigit(nextChar))
      charClass = DIGIT;
    else
      charClass = UNKNOWN;
  } else {
    charClass = EOF;
  }
}

/* getNonBlank - a function to call getChar until it returns a non-whitespace
 * character */
static void getNonBlank() {
  while (isspace(nextChar))
    getChar();
}

/* lex - a simple lexical analyzer for arithmetic expressions */
int lex() {
  lexLen = 0;
  getNonBlank();
  switch (charClass) {
  /* Parse identifiers */
  case LETTER:
    addChar();
    getChar();
    while (charClass == LETTER || charClass == DIGIT) {
      addChar();
      getChar();
    }
    if (strcmp(lexeme, "read") == 0) {
      nextToken = KEY_READ;
      tokennames = "KEY_READ";
    } else if (strcmp(lexeme, "write") == 0) {
      nextToken = KEY_WRITE;
      tokennames = "KEY_WRITE";
    } else if (strcmp(lexeme, "while") == 0) {
      nextToken = KEY_WHILE;
      tokennames = "KEY_WHILE";
    } else if (strcmp(lexeme, "do") == 0) {
      nextToken = KEY_DO;
      tokennames = "KEY_DO";
    } else {
      nextToken = IDENT;
      tokennames = "IDENT";
    }
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
    tokennames = "INT_LIT";
    break;

  /* Parentheses and operators */
  case UNKNOWN:
    lookup(nextChar);
    getChar();
    break;

  /* EOF */
  case EOF:
    nextToken = EOF;
    lexeme[0] = 'E';
    lexeme[1] = 'O';
    lexeme[2] = 'F';
    lexeme[3] = 0;
    break;
  }
  if (nextToken == EOF) {
    exit(0);
  }
  printf("%s %s \n", lexeme, tokennames);
  return nextToken;
}
