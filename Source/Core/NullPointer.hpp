#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_core_null_pointer
#define aura_guard_core_null_pointer

namespace Aura
{
    /**
     * @brief The type representing the `nullptr` prvalue.
     */
    using NullPointer = decltype(nullptr);
}

#endif
#endif