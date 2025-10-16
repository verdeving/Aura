#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_trait_bounded_array
#define aura_guard_trait_bounded_array
#include "Sized.hpp"

namespace Aura::Trait
{
    namespace Detail
    {
        template<class> struct BoundedArray
        {
            static consteval bool value() noexcept
            {
                return false;
            }
        };

        template<class T, unsigned Size> struct BoundedArray<T[Size]>
        {
            static consteval bool value() noexcept
            {
                return true;
            }
        };
    }

    /**
     * @brief Satisfied when `Self` is `Sized` and is a C-like array type with a known size.
     */
    template<class Self> concept BoundedArray = Sized<Self> and Detail::BoundedArray<Self>::value()
    ;
}

#endif
#endif