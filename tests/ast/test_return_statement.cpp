#include "ast/return_statement.hpp"
#include "token/token.hpp"
#include "types/types.hpp"
#include <gtest/gtest.h>
#include <format>
#include <memory>

TEST(ASTTest, ReturnStatementString)
{
	Token return_token(TokenType::RETURN, "return");

	auto return_stmt = std::make_unique<ast::ReturnStatement>(return_token);

	std::string expected = "return ;";
	std::string actual = return_stmt->get_string();

	EXPECT_EQ(actual, expected);
}
