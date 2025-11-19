#pragma once

#include "ast/ast.hpp"
#include "ast/identifier.hpp"
#include "ast/block_statement.hpp"
#include "token/token.hpp"

namespace ast
{
	class FunctionLiteral : public Expression
	{
	public:
		std::string get_string();
		std::string token_literal();

		// Getter methods for testing
		const std::vector<std::unique_ptr<ast::Identifier>> &get_parameters() const { return parameters; }
		const std::unique_ptr<ast::BlockStatement> &get_body() const { return body; }

		// Setter methods for parser
		void set_parameters(std::vector<std::unique_ptr<ast::Identifier>> &&params) { parameters = std::move(params); }
		void set_body(std::unique_ptr<ast::BlockStatement> b) { body = std::move(b); }

		FunctionLiteral(Token token) : token(token) {}

	private:
		Token token; // fn
		std::vector<std::unique_ptr<ast::Identifier>> parameters;
		std::unique_ptr<ast::BlockStatement> body;
	};
}
