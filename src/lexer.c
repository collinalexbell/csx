#include <stdbool.h>
#include <ctype.h>
#include "lexer.h"

#define MAX_TOKEN_LENGTH 1000

Lexer create_lexer(const char* input) {
    Lexer lexer;
    lexer.input = input;
    lexer.position = 0;
    lexer.length = strlen(input);
    return lexer;
}

bool is_jsx_start(Lexer* lexer) {
    // Check if we're at the start of a JSX expression
    if (lexer->position < lexer->length && lexer->input[lexer->position] == '<') {
        // Peek ahead to ensure it's not a comparison operator
        if (lexer->position + 1 < lexer->length && 
            lexer->input[lexer->position + 1] != '=' && 
            !isspace(lexer->input[lexer->position + 1])) {
            return true;
        }
    }
    return false;
}

bool is_jsx_end(Lexer* lexer) {
    // Check if we're at the end of a JSX expression
    if (lexer->position < lexer->length && lexer->input[lexer->position] == '>') {
        // Peek behind to ensure it's not a comparison operator
        if (lexer->position > 0 && lexer->input[lexer->position - 1] != '-') {
            return true;
        }
    }
    return false;
}

Token get_next_token(Lexer* lexer) {
    Token token;
    token.type = TOKEN_UNKNOWN;
    token.value[0] = '\0';

    // Skip whitespace
    while (lexer->position < lexer->length && isspace(lexer->input[lexer->position])) {
        lexer->position++;
    }

    if (lexer->position >= lexer->length) {
        token.type = TOKEN_EOF;
        return token;
    }

    if (is_jsx_start(lexer)) {
        token.type = TOKEN_JSX_START;
        strncpy(token.value, "<", MAX_TOKEN_LENGTH - 1);
        lexer->position++;
    } else if (is_jsx_end(lexer)) {
        token.type = TOKEN_JSX_END;
        strncpy(token.value, ">", MAX_TOKEN_LENGTH - 1);
        lexer->position++;
    } else {
        // Handle other token types (C code, JSX attributes, etc.)
        // This is a simplified version, you'll need to expand this
        int start = lexer->position;
        while (lexer->position < lexer->length && 
               !isspace(lexer->input[lexer->position]) && 
               !is_jsx_start(lexer) && 
               !is_jsx_end(lexer)) {
            lexer->position++;
        }
        int length = lexer->position - start;
        if (length > 0) {
            token.type = TOKEN_TEXT;
            strncpy(token.value, &lexer->input[start], length);
            token.value[length] = '\0';
        }
    }

    return token;
}
