#pragma once

#include <utility>
#include <type_traits>

/**
 * @brief A RAII-style helper struct that executes a callable object upon destruction.
 *
 * This template struct is designed to defer the execution of a function or callable object
 * until the end of the current scope. It is useful for ensuring that cleanup or resource
 * release code is executed automatically, similar to the "defer" statement in other languages.
 *
 * @tparam T The type of the callable object. Must be invocable with no arguments.
**/

template<class T>
class defer_t {
public:
    static_assert(std::is_invocable<T>::value);

    defer_t(T&& f) : m_func(std::forward<T>(f)) {}
    defer_t (const T& f) = delete;
    defer_t (const defer_t&) = delete;
    defer_t (defer_t&&) = delete;
    defer_t& operator=(const defer_t&) = delete;
    defer_t& operator=(defer_t&&) = delete;

    ~defer_t() {
        m_func();
    }

private:
    T m_func;
};

#define DEFER_VAR_NAME_CONCAT(x,y) x ## y
#define DEFER_VAR_NAME(x,y) DEFER_VAR_NAME_CONCAT(x,y)
#define defer(x) const defer_t DEFER_VAR_NAME(_defer,__LINE__)([&]{ x });