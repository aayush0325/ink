#include "ast/integer_literal.hpp"

std::string ast::IntegerLiteral::token_literal()
{
	return token.literal;
}

std::string ast::IntegerLiteral::get_string()
{
	return token.literal;
}

bool ast::IntegerLiteral::set_integer_value_from_token()
{
	try
	{
		integer_value = std::stoll(token.literal);
		return true;
	}
	catch (const std::invalid_argument)
	{
		std::cout << "Invalid input: not a number" << std::endl;
		return false;
	}
	catch (const std::out_of_range)
	{
		std::cout << "Input out of range for uint64_t" << std::endl;
		return false;
	}
}