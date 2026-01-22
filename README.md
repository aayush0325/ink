# ink

A fast, lightweight interpreter for the Monkey programming language, implemented in C++23.

## Features

- **REPL**: Interactive Read-Eval-Print Loop with syntax highlighting and history (via `readline`).
- **Data Types**: Integers, Booleans, Strings, Functions, and Closures.
- **Control Flow**: `if-else` statements, `return` statements.
- **Functions**: First-class functions, higher-order functions, and closures.
- **Testing**: Comprehensive test suite using GoogleTest.

## Dependencies

- **Compiler**: C++23 compatible compiler (e.g., GCC 13+, Clang 16+, or MSVC 19.36+).
- **Build System**: [CMake](https://cmake.org/) (3.10+).
- **Package Manager**: [vcpkg](https://vcpkg.io/) (recommended for dependencies).
- **Libraries**:
  - `readline`: For REPL history and editing.
  - `gtest`: For running the test suite.

## Build + Run

### 1. Install Dependencies

Ensure you have `vcpkg` installed and integrated with your build system.

### 2. Build the Project
```bash
cmake --preset vcpkg
cmake --build build
```

### 3. Run the REPL

```bash
./build/ink
```

## Running Tests

The project uses GoogleTest for unit and integration testing.

```bash
cd build
./tests
```

## Syntax Guide

### Variables

Use the `let` keyword to bind values to identifiers.
```javascript
let x = 5;
let y = 10;
let label = "Hello, Ink!";
```

### Arithmetic Operators

Supports standard infix operators: `+`, `-`, `*`, `/`.

```javascript
let result = (5 + 10) * 2 / 5; // 6
```

### Booleans and Comparison
```javascript
let isTrue = true;
let isFalse = false;

5 == 5; // true
10 != 9; // true
10 > 5;  // true
5 < 10;  // true
```

### Functions
Functions are defined using the `fn` keyword.
```javascript
let add = fn(a, b) {
    return a + b;
};

add(5, 10); // 15
```

### Closures
Functions carry their environment with them.
```javascript
let newAdder = fn(x) {
    return fn(y) { x + y; };
};

let addTwo = newAdder(2);
addTwo(3); // 5
```

### If-Else Expressions

`if` statements are expressions and return values.

```javascript
let max = if (x > y) { x; } else { y; };
```

## Project Structure
- `src/`: Implementation files.
- `include/`: Header files.
- `tests/`: Test suite.
- `CMakeLists.txt`: Build configuration.
