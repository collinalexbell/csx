#include "unity.h"
#include "lexer.h"

void setUp(void) {}
void tearDown(void) {}

void test_lexer_differentiates_jsx_and_c_code(void) {
    const char* input = "int main() { return <div>Hello, JSX!</div>; }";
    Lexer lexer = create_lexer(input);
    Token token;

    // C code: "int main() { return "
    token = get_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_TEXT, token.type);
    TEST_ASSERT_EQUAL_STRING("int", token.value);

    token = get_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_TEXT, token.type);
    TEST_ASSERT_EQUAL_STRING("main()", token.value);

    token = get_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_TEXT, token.type);
    TEST_ASSERT_EQUAL_STRING("{", token.value);

    token = get_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_TEXT, token.type);
    TEST_ASSERT_EQUAL_STRING("return", token.value);

    // JSX start: "<div>"
    token = get_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_JSX_START, token.type);
    TEST_ASSERT_EQUAL_STRING("<", token.value);

    token = get_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_TEXT, token.type);
    TEST_ASSERT_EQUAL_STRING("div", token.value);

    token = get_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_JSX_END, token.type);
    TEST_ASSERT_EQUAL_STRING(">", token.value);

    // JSX content: "Hello, JSX!"
    token = get_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_TEXT, token.type);
    TEST_ASSERT_EQUAL_STRING("Hello,", token.value);

    token = get_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_TEXT, token.type);
    TEST_ASSERT_EQUAL_STRING("JSX!", token.value);

    // JSX end: "</div>"
    token = get_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_JSX_START, token.type);
    TEST_ASSERT_EQUAL_STRING("<", token.value);

    token = get_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_TEXT, token.type);
    TEST_ASSERT_EQUAL_STRING("/div", token.value);

    token = get_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_JSX_END, token.type);
    TEST_ASSERT_EQUAL_STRING(">", token.value);

    // C code: "; }"
    token = get_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_TEXT, token.type);
    TEST_ASSERT_EQUAL_STRING(";", token.value);

    token = get_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_TEXT, token.type);
    TEST_ASSERT_EQUAL_STRING("}", token.value);

    // End of input
    token = get_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_EOF, token.type);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_lexer_differentiates_jsx_and_c_code);
    return UNITY_END();
}
