#include "ast/let_statement.hpp"
#include "ast/identifier.hpp"
#include "token/token.hpp"
#include "types/types.hpp"
#include <gtest/gtest.h>
#include <format>
#include <memory>

TEST(ASTTest, LetStatementString)
{
	Token let_token(TokenType::LET, "let");
	Token ident_token(TokenType::IDENT, "myVar");

	auto let_stmt = std::make_unique<ast::LetStatement>(let_token);
	let_stmt->ident = std::make_unique<ast::Identifier>(ident_token, "myVar");

	std::string expected = "let myVar;";
	std::string actual = let_stmt->get_string();

	EXPECT_EQ(actual, expected);
}
