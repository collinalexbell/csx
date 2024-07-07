#ifndef LEXER_H
#define LEXER_H

#include <string.h>

typedef enum {
    TOKEN_UNKNOWN,
    TOKEN_JSX_START,
    TOKEN_JSX_END,
    TOKEN_TEXT,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char value[1000];  // Adjust size as needed
} Token;

typedef struct {
    const char* input;
    int position;
    int length;
} Lexer;

Lexer create_lexer(const char* input);
Token get_next_token(Lexer* lexer);

#endif // LEXER_H
