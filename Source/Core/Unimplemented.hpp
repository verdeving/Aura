#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_core_unimplemented
#define aura_guard_core_unimplemented
/**
 * @brief Indicates unimplemented functions that when called will produce a compile-time error that
 * always says "not implemented".
 */
#define $unimplemented = delete("not implemented")
#endif
#endif