#include "ast/expression_statement.hpp"

std::string ast::ExpressionStatement::token_literal()
{
	return token.literal;
}

std::string ast::ExpressionStatement::get_string()
{
	std::string result = "";
	if (expression != nullptr)
		result += expression->get_string();
	return result;
}

std::unique_ptr<ast::Node> ast::ExpressionStatement::clone() const
{
	auto clone = std::make_unique<ExpressionStatement>(token);
	if (expression)
	{
		auto expr_clone = expression->clone();
		clone->expression = std::unique_ptr<Expression>(static_cast<Expression *>(expr_clone.release()));
	}
	return clone;
}
