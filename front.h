#ifndef FRONT_H
#define FRONT_H

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
#define SEMICOLON 27
#define LEFT_CBRACE 28
#define RIGHT_CBRACE 29
#define LESSER_OP 30
#define GREATER_OP 31
#define KEY_READ 32
#define KEY_WRITE 33
#define KEY_WHILE 34
#define KEY_DO 35
#define INC_OP 36
#define EQUAL_OP 37
#define NEQUAL_OP 38
#define LEQUAL_OP 39
#define GEQUAL_OP 40
#define DEC_OP 41

int lex();

#endif
