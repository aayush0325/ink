#pragma once

#include "ast/ast.hpp"
#include "ast/identifier.hpp"
#include "token/token.hpp"
#include <memory>

namespace ast
{
	// Assignment statement: let <Identifier> = <Expression>
	class LetStatement : public Statement
	{
	public:
		virtual std::string token_literal() override;
		virtual std::string get_string() override;
		virtual std::unique_ptr<Node> clone() const override;
		explicit LetStatement(Token token) : token(token), ident(nullptr), value(nullptr) {}

		void set_value(std::unique_ptr<Expression> expr);
		const std::unique_ptr<Expression> &get_value() const { return value; }

		std::unique_ptr<Identifier> ident;

	private:
		Token token; // the "LET" token
		std::unique_ptr<Expression> value;
	};
}
