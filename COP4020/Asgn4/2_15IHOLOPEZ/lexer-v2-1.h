
#ifndef LEXER
#define LEXER
int try_match(char *);
int try_lookahead(char *);
void must_match(char *);
void advance(void);
void fail(char *, ...);
void lexer_reset(char *);
#endif

#ifdef LEXER_TRUE
char *identifier = "[a-zA-Z_][a-zA-Z0-9._]*";
char *number = "([0-9]+)|(-[0-9]+)";
#else
extern char *identifier;
extern char *number;
extern char *current_token;
extern char *next_token;
#endif
