# Defer.hpp

**Defer.hpp** is a lightweight C++ header-only library that brings Go-style `defer` semantics to C++. It enables you to schedule code to run automatically at the end of the current scope, making resource management and cleanup tasks concise and exception-safe.
To use just copy header to your project.

## Features

- Simple, single-header implementation
- No dependencies beyond the C++ standard library
- Exception-safe scope exit handling
- Useful for RAII, resource cleanup, and more

## Example

```cpp
#include "Defer.hpp"

void example() {
    FILE* file = fopen("data.txt", "r");
    defer (if (file) fclose(file); );

    // ... use file ...
}
```