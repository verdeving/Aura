#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_core_move
#define aura_guard_core_move
#include "Meta/RemoveLvalueReference.hpp"
/**
 * @brief Moves the provided arguments.
 */
#define $move(...) static_cast<::Aura::Meta::RemoveLvalueReference<decltype(__VA_ARGS__)>&&>(\
__VA_ARGS__)
#endif
#endif