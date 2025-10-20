#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_trait_function
#define aura_guard_trait_function

namespace Aura::Trait
{
    /**
     * @brief Satisfied when `Self` is a possibly-qualified free function or an static member
     * function.
     */
    template<class Self> concept Function = __is_function(Self);
}

#endif
#endif