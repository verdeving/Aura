#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_core_todo
#define aura_guard_core_todo
/**
 * @brief Indicates to-do functions that when called will produce a compile-time error that always
 * says "not yet implemented".
 */
#define $todo = delete("not yet implemented")
#endif
#endif