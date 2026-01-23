#include "ast/return_statement.hpp"

std::string ast::ReturnStatement::token_literal()
{
	return token.literal; // the return token
}

std::string ast::ReturnStatement::get_string()
{
	std::string result = "";
	result += token_literal();
	result += " ";
	while (return_value != nullptr)
		result += return_value->get_string();

	result += ";";
	return result;
}

void ast::ReturnStatement::set_return_value(std::unique_ptr<ast::Expression> val)
{
	return_value = std::move(val);
}

std::unique_ptr<ast::Node> ast::ReturnStatement::clone() const
{
	auto clone = std::make_unique<ReturnStatement>(token);
	if (return_value)
	{
		auto val_clone = return_value->clone();
		clone->set_return_value(std::unique_ptr<Expression>(
			static_cast<Expression *>(val_clone.release())));
	}
	return clone;
}