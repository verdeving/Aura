#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_core_unicode
#define aura_guard_core_unicode

namespace Aura
{
    /**
     * @brief Represents the encoding of Unicode scalar values into code units.
     */
    enum class [[nodiscard]] Unicode : unsigned char
    {
        /**
         * @brief UTF-8: variable-length encoding using 8-bit code units.
         */
        UTF8,
        /**
         * @brief UTF-16: variable-length encoding using 16-bit code units (surrogates possible).
         */
        UTF16,
        /**
         * @brief UTF-32: fixed-length encoding using 32-bit code units.
         */
        UTF32
    };
}

#endif
#endif