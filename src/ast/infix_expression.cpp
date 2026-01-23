#include "ast/infix_expression.hpp"

std::string ast::InfixExpression::get_string()
{
	std::string result = "";
	result += "(";
	result += left->get_string();
	result += " ";
	result += infix_operator;
	result += " ";
	result += right->get_string();
	result += ")";
	return result;
}

std::string ast::InfixExpression::token_literal()
{
	return infix_token.literal;
}

void ast::InfixExpression::set_right(std::unique_ptr<ast::Expression> right)
{
	this->right = std::move(right);
}

std::unique_ptr<ast::Node> ast::InfixExpression::clone() const
{
	auto left_clone = left->clone();
	auto clone = std::make_unique<InfixExpression>(
		infix_token, std::unique_ptr<Expression>(static_cast<Expression *>(left_clone.release())),
		infix_operator);

	if (right)
	{
		auto right_clone = right->clone();
		clone->set_right(std::unique_ptr<Expression>(
			static_cast<Expression *>(right_clone.release())));
	}
	return clone;
}