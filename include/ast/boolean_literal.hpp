#pragma once

#include "ast/ast.hpp"
#include "token/token.hpp"

namespace ast
{
	// true or false
	class BooleanLiteral : public ast::Expression
	{
	public:
		virtual std::string get_string() override;
		virtual std::string token_literal() override;
		virtual std::unique_ptr<Node> clone() const override;
		bool get_value() { return value; }

		explicit BooleanLiteral(Token token) : token(token), value(token.type == TokenType::TRUE) {}

		bool operator==(const BooleanLiteral &l) const;

	private:
		Token token;
		bool value;
	};
}