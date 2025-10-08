#include "utils/utils.hpp"

bool is_letter(const char &c)
{
	return (c >= 'a' and c <= 'z') or (c >= 'A' and c <= 'Z') or (c == '_');
}

bool is_number(const char &c)
{
	return (c >= '0') and (c <= '9');
}