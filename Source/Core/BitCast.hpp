#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_core_bit_cast
#define aura_guard_core_bit_cast
#include "Safety.hpp"
#include "Trait/TriviallyCopyable.hpp"

namespace Aura
{
    /**
     * @brief This will produce a new object of type `To` with the bit representation of the object
     * `from`.
     *
     * This method is unsafe because:
     *
     * - If the `From` type could lack a value representation for the value of `from` at the `To`
     * type, the behavior is undefined.
     * - In the other hand, if there're multiple values for that value representation, which value
     * is selected is unspecified.
     * - If a bit in the bit representation of the new resulting object doesn't correspond to a bit
     * in the bit representation of `from`, the resulting value is indeterminate.
     * - If `from`'s object is not within its lifetime, or its value is indeterminate, the
     * resulting value is indeterminate.
     * - If a bit in the bit representation of `from`, is erroneous, then the resulting new object
     * is also erroneous.
     */
    template<Trait::TriviallyCopyable To, Trait::TriviallyCopyable From> requires(sizeof(To) ==
    sizeof(From)) [[nodiscard]] constexpr auto bit_cast $unreliable(const From& from) noexcept ->
    To
    {
        return __builtin_bit_cast(To, from);
    }
}

#endif
#endif