#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_meta_remove_lvalue_reference
#define aura_guard_meta_remove_lvalue_reference

namespace Aura::Meta
{
    namespace Detail
    {
        template<class T> struct RemoveLvalueReference
        {
            using type = T;
        };

        template<class T> struct RemoveLvalueReference<T&>
        {
            using type = T;
        };
    }

    /**
     * @brief Removes l-value reference qualifiers (&) from `Self`, if any.
     */
    template<class Self> using RemoveLvalueReference = Detail::RemoveLvalueReference<Self>::type;
}

#endif
#endif