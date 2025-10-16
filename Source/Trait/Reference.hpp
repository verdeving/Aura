#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_trait_reference
#define aura_guard_trait_reference

namespace Aura::Trait
{
    namespace Detail
    {
        template<class> struct Reference
        {
            static consteval bool value() noexcept
            {
                return false;
            }
        };
        
        template<class T> struct Reference<T&>
        {
            static consteval bool value() noexcept
            {
                return true;
            }
        };

        template<class T> struct Reference<T&&>
        {
            static consteval bool value() noexcept
            {
                return true;
            }
        };
    }

    /**
     * @brief Satisfied when `Self` is an l-value or r-value reference type.
     */
    template<class Self> concept Reference = Detail::Reference<Self>::value();
}

#endif
#endif