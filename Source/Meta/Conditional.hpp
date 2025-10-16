#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_meta_conditional
#define aura_guard_meta_conditional

namespace Aura::Meta
{
    namespace Detail
    {
        template<bool, class, class T> struct Conditional
        {
            using type = T;
        };

        template<class T, class U> struct Conditional<true, T, U>
        {
            using type = T;
        };
    }

    /**
     * @brief Selects one of two types based on the result of `Condition`.
     *
     * @tparam Condition — A `bool` constant expression evaluated at compile time.
     * @tparam True — The type to select iff `Condition` is `true`.
     * @tparam False — The type to select iff `Condition` is `false`.
     */
    template<bool Condition, class True, class False> using Conditional = Detail::Conditional<
    Condition, True, False>::type;
}

#endif
#endif