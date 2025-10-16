#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_core_stringify
#define aura_guard_core_stringify
/**
 * @brief Stringifies its arguments.
 *
 * Will yield a string literal, which is the stringification of all the tokens passed to it.
 *
 * The encoding of the string literal will be determined based on the prefix (or the lack thereof).
 */
#define $stringify(prefix, ...) prefix###__VA_ARGS__
#endif
#endif