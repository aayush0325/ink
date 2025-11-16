#pragma once

#include "ast/ast.hpp"
#include "token/token.hpp"

namespace ast
{
	class BlockStatement : public ast::Statement
	{
	public:
		std::string token_literal();
		std::string get_string();

		BlockStatement(Token token) : token(token) {}

		void insert_statement(std::unique_ptr<ast::Statement>);

		// Getter method for testing
		const std::vector<std::unique_ptr<ast::Statement>> &get_statements() const { return statements; }

	private:
		Token token; // { token
		std::vector<std::unique_ptr<ast::Statement>> statements;
	};
}
