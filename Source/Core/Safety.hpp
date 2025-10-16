#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_core_safety
#define aura_guard_core_safety
/**
 * @brief Injects the actual safety context with the additional given arguments, if any, in the
 * function call form.
 */
#define $(...) (aura_safety_object_private_and_secret_424242 __VA_OPT__(,) __VA_ARGS__)
/**
 * @brief Injects the actual safety context with the additional given arguments, if any, in the
 * template list form.
 */
#define $t(...) <aura_safety_object_private_and_secret_424242 __VA_OPT__(,) __VA_ARGS__>
/**
 * @brief Injects the actual safety context with the additional given arguments, if any, in the
 * curly braces form.
 */
#define $b(...) {aura_safety_object_private_and_secret_424242 __VA_OPT__(,) __VA_ARGS__}
/**
 * @brief Injects the actual safety context with the additional given arguments, if any, in the
 * subscript form.
 */
#define $s(...) [aura_safety_object_private_and_secret_424242 __VA_OPT__(,) __VA_ARGS__]
/**
 * @brief Creates a safe context with the additional given parameters, if any, in the template
 * parameter list form.
 */
#define $treliable(...) template<::Aura::Detail::Safety<> \
aura_safety_object_private_and_secret_424242 __VA_OPT__(,) __VA_ARGS__>
/**
 * @brief Creates an unsafe context with the additional given parameters, if any, in the template
 * parameter list form.
 */
#define $tunreliable(...) template<::Aura::Detail::Safety<false> \
aura_safety_object_private_and_secret_424242 __VA_OPT__(,) __VA_ARGS__>
/**
 * @brief Creates a safe context with the additional given parameters, if any, in the function
 * parameter list form.
 */
#define $reliable(...) ([[maybe_unused]] const ::Aura::Detail::Safety<> \
aura_safety_object_private_and_secret_424242 __VA_OPT__(,) __VA_ARGS__)
/**
 * @brief Creates an unsafe context with the additional given parameters, if any, in the function
 * parameter list form.
 */
#define $unreliable(...) ([[maybe_unused]] const ::Aura::Detail::Safety<false> \
aura_safety_object_private_and_secret_424242 __VA_OPT__(,) __VA_ARGS__)
/**
 * @brief Creates a safe context.
 */
#define $safe if constexpr([[maybe_unused]] constexpr const ::Aura::Detail::Safety<> \
aura_safety_object_private_and_secret_424242; true)
/**
 * @brief Creates an unsafe context.
 */
#define $unsafe if constexpr([[maybe_unused]] constexpr const ::Aura::Detail::Safety<false> \
aura_safety_object_private_and_secret_424242; true)
/**
 * @brief Indicates with a boolean whether the actual context is safe.
 */
#define $safety aura_safety_object_private_and_secret_424242.am_i_safe()

namespace Aura::Detail
{
    template<bool safety = true> struct [[nodiscard]] Safety final
    {
        constexpr compl Safety() noexcept = default;

        explicit consteval Safety() noexcept = default;

        consteval Safety(const Safety&) noexcept = default;

        explicit consteval Safety(Safety&&) noexcept = delete;

        consteval auto operator=(const Safety&) noexcept -> Safety& = delete;

        consteval auto operator=(Safety&&) noexcept -> Safety& = delete;

        [[nodiscard]] consteval auto operator==(const Safety&) const noexcept -> bool = delete;

        [[nodiscard]] consteval auto operator not_eq(const Safety&) const noexcept -> bool = delete
        ;

        [[nodiscard]] static consteval auto am_i_safe() noexcept -> bool
        {
            return safety;
        }
    };
}

inline constexpr const ::Aura::Detail::Safety<> aura_safety_object_private_and_secret_424242;

#endif
#endif