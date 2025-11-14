#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_trait_unsafely_constructible
#define aura_guard_trait_unsafely_constructible
#include "Core/Safety.hpp"

namespace Aura::Trait
{
    /**
     * @brief Satisfied when `Self` can be constructed using the injected `$` in an `$unsafe` or
     * `$unreliable` block, along with the given `Parameters`, if any.
     */
    template<class Self, class... Parameters> concept UnsafelyConstructible = __is_constructible(
    Self, const Detail::Safety<false>, Parameters...);
}

#endif
#endif