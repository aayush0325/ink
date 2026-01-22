#include "object/environment.hpp"

Environment::Environment() : outer(nullptr) {}

Environment::Environment(std::shared_ptr<Environment> outer) : outer(outer) {}

std::unique_ptr<Object> Environment::get(const std::string &name)
{
	auto it = store.find(name);
	if (it != store.end())
	{
		return it->second->clone();
	}

	if (outer != nullptr)
	{
		return outer->get(name);
	}

	return nullptr;
}

std::shared_ptr<Environment> Environment::NewEnclosedEnvironment(std::shared_ptr<Environment> outer)
{
	return std::make_shared<Environment>(outer);
}

Object *Environment::set(const std::string &name, std::unique_ptr<Object> val)
{
	Object *ptr = val.get();
	store[name] = std::move(val);
	return ptr;
}
