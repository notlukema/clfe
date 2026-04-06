module;
#include <functional>
export module Function_t;
export template <typename T> using Function = std::function<T>;
