#include "ast/if_expression.hpp"

std::string ast::IfExpression::get_string()
{
	std::string result = "";
	result += "if";
	result += condition->get_string();
	result += " ";
	result += consequence->get_string();
	if (alternative != nullptr)
	{
		result += "else";
		result += alternative->get_string();
	}
	return result;
}

std::string ast::IfExpression::token_literal()
{
	return token.literal;
}

void ast::IfExpression::set_condition(std::unique_ptr<Expression> expr)
{
	condition = std::move(expr);
}

void ast::IfExpression::set_consequence(std::unique_ptr<BlockStatement> expr)
{
	consequence = std::move(expr);
}

void ast::IfExpression::set_alternative(std::unique_ptr<BlockStatement> expr)
{
	alternative = std::move(expr);
}

std::unique_ptr<ast::Node> ast::IfExpression::clone() const
{
	auto clone = std::make_unique<IfExpression>(token);
	if (condition)
	{
		auto cond_clone = condition->clone();
		clone->set_condition(std::unique_ptr<Expression>(static_cast<Expression *>(cond_clone.release())));
	}
	if (consequence)
	{
		auto stmt = consequence->clone();
		clone->set_consequence(std::unique_ptr<BlockStatement>(static_cast<BlockStatement *>(stmt.release())));
	}
	if (alternative)
	{
		auto stmt = alternative->clone();
		clone->set_alternative(std::unique_ptr<BlockStatement>(static_cast<BlockStatement *>(stmt.release())));
	}
	return clone;
}