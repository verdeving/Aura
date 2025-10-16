#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_trait_same
#define aura_guard_trait_same

namespace Aura::Trait
{
    namespace Detail
    {
        template<class, class> struct Same
        {
            static consteval bool value() noexcept
            {
                return false;
            }
        };

        template<class T> struct Same<T, T>
        {
            static consteval bool value() noexcept
            {
                return true;
            }
        };
    }

    /**
     * @brief Satisfied when two types are strictly the same.
     *
     * Evaluates to `true` iff `Self` and `Another` are the same type, including const, volatile,
     * and reference qualifiers. It can be used to constrain templates to accept only identical
     * types.
     */
    template<class Self, class Another> concept Same = Detail::Same<Self, Another>::value();
}

#endif
#endif