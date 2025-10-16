#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_meta_remove_references
#define aura_guard_meta_remove_references

namespace Aura::Meta
{
    namespace Detail
    {
        template<class T> struct RemoveReferences
        {
            using type = T;
        };

        template<class T> struct RemoveReferences<T&>
        {
            using type = T;
        };

        template<class T> struct RemoveReferences<T&&>
        {
            using type = T;
        };
    }

    /**
     * @brief Removes r-value and l-value reference qualifiers (& or &&) from `Self`, if any.
     */
    template<class Self> using RemoveReferences = Detail::RemoveReferences<Self>::type;
}

#endif
#endif