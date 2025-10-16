#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_core_address
#define aura_guard_core_address
#include "Trait/Sized.hpp"

namespace Aura
{
    /**
     * @brief Obtains the actual memory address of an object, bypassing any overloaded unary
     * `operator&` of `Self`.
     *
     * It guarantees retrieval of the true underlying pointer to the object, even if the type
     * `Self` has a custom address-of operator.
     *
     * @tparam Self The `Sized` type of the object.
     *
     * @param object A reference to the object whose address is to be obtained. Must be
     * addressable.
     *
     * @return A pointer to the referenced object. The returned pointer is never null.
     */
    template<Trait::Sized Self> [[nodiscard]] constexpr auto address(Self& object) noexcept -> Self
    *
    {
        return __builtin_addressof(object);
    }
}

#endif
#endif