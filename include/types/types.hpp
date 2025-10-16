#pragma once

#include <functional>
#include "ast/ast.hpp"
#include <cstdint>
#include <memory>

typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

using prefix_parse_function = std::function<std::unique_ptr<Expression>()>;
using infix_parse_function = std::function<std::unique_ptr<Expression>(std::unique_ptr<Expression>)>;