#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_trait_sized
#define aura_guard_trait_sized

namespace Aura::Trait
{
    /**
     * @brief Satisfied iff `sizeof(Self)` is a valid constant expression. This implies that the
     * type `Self` has a compile-time known size and hence has a complete definition at the point
     * of use and its size can be determined by the compiler.
     *
     * Requirements:
     * - `Self` must not be an incomplete type (e.g., a void or a forward-declared struct).
     * - `Self` must not be a function type or an array of unknown bound.
     */
    template<class Self> concept Sized = requires
    {
        sizeof(Self);
    };
}

#endif
#endif