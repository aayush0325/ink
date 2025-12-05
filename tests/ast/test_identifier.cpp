#include "ast/identifier.hpp"
#include "token/token.hpp"
#include "types/types.hpp"
#include <gtest/gtest.h>
#include <format>

TEST(ASTTest, IdentifierString)
{
	Token ident_token(TokenType::IDENT, "myVar");
	ast::Identifier identifier(ident_token, "myVar");

	std::string expected = "myVar";
	std::string actual = identifier.get_string();

	EXPECT_EQ(actual, expected);
}
