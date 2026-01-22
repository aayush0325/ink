#pragma once

#include "object/object.hpp"
#include <map>
#include <memory>
#include <string>

class Environment
{
public:
	Environment();
	Environment(std::shared_ptr<Environment> outer);

	std::unique_ptr<Object> get(const std::string &name);
	Object *set(const std::string &name, std::unique_ptr<Object> val);

	static std::shared_ptr<Environment> NewEnclosedEnvironment(std::shared_ptr<Environment> outer);

private:
	std::map<std::string, std::unique_ptr<Object>> store;
	std::shared_ptr<Environment> outer;
};
