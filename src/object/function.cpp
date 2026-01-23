#include "object/function.hpp"

Function::Function(
	std::vector<std::unique_ptr<ast::Identifier>> params,
	std::unique_ptr<ast::BlockStatement> body,
	std::shared_ptr<Environment> env)
	: parameters(std::move(params)), body(std::move(body)), env(env) {}

object_type Function::get_type()
{
	return FUNCTION_OBJ;
}

std::string Function::inspect()
{
	std::stringstream ss;
	ss << "fn(";
	for (size_t i = 0; i < parameters.size(); ++i)
	{
		ss << parameters[i]->get_string();
		if (i < parameters.size() - 1)
		{
			ss << ", ";
		}
	}
	ss << ") {\n";
	ss << body->get_string();
	ss << "\n}";
	return ss.str();
}

std::unique_ptr<Object> Function::clone() const
{
	std::vector<std::unique_ptr<ast::Identifier>> params_clone;
	for (const auto &param : parameters)
	{
		auto p_clone = param->clone();
		params_clone.push_back(std::unique_ptr<ast::Identifier>(
			static_cast<ast::Identifier *>(p_clone.release())));
	}

	auto body_clone = body->clone();
	auto body_ptr = std::unique_ptr<ast::BlockStatement>(
		static_cast<ast::BlockStatement *>(body_clone.release()));

	return std::make_unique<Function>(
		std::move(params_clone), std::move(body_ptr), env);
}
