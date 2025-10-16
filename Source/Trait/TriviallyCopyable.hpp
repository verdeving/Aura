#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_trait_trivially_copyable
#define aura_guard_trait_trivially_copyable
#include "Sized.hpp"

namespace Aura::Trait
{
    /**
     * @brief Satisfied when `Self` is `Sized`, has a trivial destructor, and has at least one of
     * the following:
     *
     * - An eligible copy constructor.
     * - An eligible move constructor.
     * - An eligible copy assignment.
     * - An eligible move assignment.
     *
     * Where each of these special member functions must be trivial.
     */
    template<class Self> concept TriviallyCopyable = Sized<Self> and __is_trivially_copyable(Self);
}

#endif
#endif