#pragma once

#include "ast/ast.hpp"
#include "token/token.hpp"

namespace ast
{
	class BlockStatement : public ast::Statement
	{
	public:
		virtual std::string token_literal() override;
		virtual std::string get_string() override;
		virtual std::unique_ptr<Node> clone() const override;

		BlockStatement(Token token) : token(token) {}

		void insert_statement(std::unique_ptr<ast::Statement>);

		// Getter method for testing
		const std::vector<std::unique_ptr<ast::Statement>> &get_statements() const { return statements; }

	private:
		Token token; // { token
		std::vector<std::unique_ptr<ast::Statement>> statements;
	};
}
