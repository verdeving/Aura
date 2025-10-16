#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_core_forward
#define aura_guard_core_forward
/**
 * @brief Performs forwarding of the given arguments: the value category is preserved except for
 * prvalues becoming xvalues.
 */
#define $forward(...) static_cast<decltype(__VA_ARGS__)&&>(__VA_ARGS__)
#endif
#endif