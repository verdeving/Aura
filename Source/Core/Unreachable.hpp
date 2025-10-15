#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_core_unreachable
#define aura_guard_core_unreachable

namespace Aura
{
    /**
     * @brief Indicates unreachable code. If the control flow of the execution reaches this code,
     * the behavior is always undefined.
     * 
     * This is useful any time that the compiler can’t determine that some code is unreachable. For
     * example:
     *
     * - Switch arms that dynamically terminate.
     * - Loops that dynamically terminate.
     * - Iterators that dynamically terminate.
     */
     [[noreturn]] inline auto unreachable() noexcept -> void
     {
        __builtin_unreachable();
     }
}

#endif
#endif