#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 100
#define MAX_NUM_TOKENS 1000

// Token types
typedef enum {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_OPERATOR,
    TOKEN_PUNCTUATION,
    TOKEN_NUMBER,
    TOKEN_UNKNOWN
} TokenType;

// Structure to hold a token
typedef struct {
    char value[MAX_TOKEN_LENGTH];
    TokenType type;
} Token;

// Function prototypes
void tokenize(const char *filename);
int isKeyword(const char *token);
void addToken(Token *tokens, int *tokenCount, const char *value, TokenType type);
void printTokens(Token *tokens, int tokenCount);

const char *keywords[] = {
    "int", "float", "double", "char", "return", "if", "else", "while", "for", "break", "continue", "void", "switch", "case", "default", "struct", "typedef"
};

int main() {
    char filename[256];
    printf("Enter the C source file name with extension .c: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove newline character

    tokenize(filename);
    return 0;
}

// Function to tokenize the input file
void tokenize(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    Token tokens[MAX_NUM_TOKENS];
    int tokenCount = 0;
    char currentChar;
    char currentToken[MAX_TOKEN_LENGTH];
    int tokenIndex = 0;

    while ((currentChar = fgetc(file)) != EOF) {
        if (isspace(currentChar)) {
            // If we encounter whitespace, process the current token
            if (tokenIndex > 0) {
                currentToken[tokenIndex] = '\0'; // Null-terminate the string
                if (isKeyword(currentToken)) {
                    addToken(tokens, &tokenCount, currentToken, TOKEN_KEYWORD);
                } else if (isdigit(currentToken[0])) {
                    addToken(tokens, &tokenCount, currentToken, TOKEN_NUMBER);
                } else {
                    addToken(tokens, &tokenCount, currentToken, TOKEN_IDENTIFIER);
                }
                tokenIndex = 0; // Reset token index
            }
        } else if (isalpha(currentChar) || currentChar == '_') {
            // If the character is a letter or underscore, it's part of an identifier or keyword
            currentToken[tokenIndex++] = currentChar;
        } else if (isdigit(currentChar)) {
            // If the character is a digit, it's part of a number
            currentToken[tokenIndex++] = currentChar;
        } else {
            // Handle operators and punctuation
            if (tokenIndex > 0) {
                currentToken[tokenIndex] = '\0'; // Null-terminate the string
                addToken(tokens, &tokenCount, currentToken, TOKEN_IDENTIFIER);
                tokenIndex = 0; // Reset token index
            }

            // Handle single-character tokens
            currentToken[0] = currentChar;
            currentToken[1] = '\0'; // Null-terminate
            if (strchr("+-*/=<>!&|", currentChar)) {
                addToken(tokens, &tokenCount, currentToken, TOKEN_OPERATOR);
            } else if (strchr("();,{}", currentChar)) {
                addToken(tokens, &tokenCount, currentToken, TOKEN_PUNCTUATION);
            } else {
                addToken(tokens, &tokenCount, currentToken, TOKEN_UNKNOWN);
            }
        }
    }

    // Process any remaining token at the end of the file
    if (tokenIndex > 0) {
        currentToken[tokenIndex] = '\0'; // Null-terminate the string
        if (isKeyword(currentToken)) {
            addToken(tokens, &tokenCount, currentToken, TOKEN_KEYWORD);
        } else if (isdigit(currentToken[0])) {
            addToken(tokens, &tokenCount, currentToken, TOKEN_NUMBER);
        } else {
            addToken(tokens, &tokenCount, currentToken, TOKEN_IDENTIFIER);
        }
    }

    fclose(file);
    printTokens(tokens, tokenCount);
}

// Function to check if a token is a keyword
int isKeyword(const char *token) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return 1; // Token is a keyword
        }
    }
    return 0; // Token is not a keyword
}

// Function to add a token to the token list
void addToken(Token *tokens, int *tokenCount, const char *value, TokenType type) {
    if (*tokenCount < MAX_NUM_TOKENS) {
        strcpy(tokens[*tokenCount].value, value);
        tokens[*tokenCount].type = type;
        (*tokenCount)++;
    } else {
        printf("Maximum number of tokens reached.\n");
    }
}

// Function to print the tokens
void printTokens(Token *tokens, int tokenCount) {
    printf("\n--- Tokens ---\n");
    for (int i = 0; i < tokenCount; i++) {
        const char *typeStr;
        switch (tokens[i].type) {
            case TOKEN_KEYWORD: typeStr = "Keyword"; break;
            case TOKEN_IDENTIFIER: typeStr = "Identifier"; break;
            case TOKEN_OPERATOR: typeStr = "Operator"; break;
            case TOKEN_PUNCTUATION: typeStr = "Punctuation"; break;
            case TOKEN_NUMBER: typeStr = "Number"; break;
            default: typeStr = "Unknown"; break;
        }
        printf("%s: %s\n", typeStr, tokens[i].value);
    }
}