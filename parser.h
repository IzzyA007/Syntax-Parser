#ifndef PARSER_H
#define PARSER_H

extern int errorCount;

void expr();
void term();
void factor();
void statement();
void condition();
void program();

extern int syntaxError ;
extern int nextToken;
extern char *tokennames;
extern char lexeme[100];
extern int nextToken;
#endif
