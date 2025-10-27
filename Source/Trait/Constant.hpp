#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_trait_constant
#define aura_guard_trait_constant

namespace Aura::Trait
{
    namespace Detail
    {
        template<class> struct Constant
        {
            static consteval bool value() noexcept
            {
                return false;
            }
        };

        template<class T> struct Constant<const T>
        {
            static consteval bool value() noexcept
            {
                return true;
            }
        };
    }

    /**
     * @brief Satisfied when `Self` is const qualified.
     */
    template<class Self> concept Constant = Detail::Constant<Self>::value();
}

#endif
#endif