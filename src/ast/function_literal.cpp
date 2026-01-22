#include "ast/function_literal.hpp"

std::string ast::FunctionLiteral::get_string()
{
	std::string result = "";
	result += token.literal;
	result += "(";
	for (auto &it : parameters)
	{
		result += it->get_string();
		result += ",";
	}
	result += ")";
	result += body->get_string();
	return result;
}

std::string ast::FunctionLiteral::token_literal()
{
	return token.literal;
}

std::unique_ptr<ast::Node> ast::FunctionLiteral::clone() const
{
	auto clone = std::make_unique<FunctionLiteral>(token);
	std::vector<std::unique_ptr<Identifier>> params_clone;
	for (const auto &param : parameters)
	{
		auto p_clone = param->clone();
		params_clone.push_back(std::unique_ptr<Identifier>(static_cast<Identifier *>(p_clone.release())));
	}
	clone->set_parameters(std::move(params_clone));

	if (body)
	{
		auto b_clone = body->clone();
		clone->set_body(std::unique_ptr<BlockStatement>(static_cast<BlockStatement *>(b_clone.release())));
	}
	return clone;
}
