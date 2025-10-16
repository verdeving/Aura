#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_core_concat
#define aura_guard_core_concat
/**
 * @brief Concatenates the tokens of the `lhs` and the `rhs`.
 */
#define $concat(lhs, rhs) lhs##rhs
#endif
#endif