#pragma once
#include <stdint.h>
#include <Mem.hpp>
#define GPIO_BASE (MMIO_BASE + 0x200000)

/**
* @brief GPIO MMIO bindings.
*/
namespace dev::crystall::gpio
{
    /**
     * @brief Pin digital state.
     */
    enum class PinState : uint8_t
    {
        Low = 0,
        High = 1,
    };

    /// List of the available pin modes.
    enum class PinMode : uint8_t
    {
        Input   = 0b000,
        Output  = 0b001,
        Alt0    = 0b100,
        Alt1    = 0b101,
        Alt2    = 0b110,
        Alt3    = 0b111,
        Alt4    = 0b011,
        Alt5    = 0b010,
    };

    /// Available Pull-UP/DOWN modes.
    enum class PudMode : uint8_t
    {
        Off     = 0b00,
        Down    = 0b01,
        Up      = 0b10,
    };

    /**
    * @brief A GPIO handling bindings.
    */
    class Gpio
    {
    public:
        /**
        * @brief Read current state of @p pin.
        *
        * @details Reads the @code GPLEV0/1 @endcode register
        * and returns the final value according to state of bin under
        * the pin number (variable @code off @endcode).
        *
        * @param[in] pin Pin number.
        * @returns Read pin value.
        */
        static PinState Read(uint8_t pin);

        /**
        * @brief Set @p pin 's state to the speicfied @p value
        *
        * @details Calculates AND mask offset out of the @p pin index
        * and enables a corresponding bit in the @code GPSET0/1 @endcode for the SET value
        * or the @code GPCLR0/1 @endcode for the CLEAR.
        *
        * @param[in] pin Pin number.
        * @param[in] value New pin state.
        */
        static void Set(uint8_t pin, PinState value);

        /**
         * @brief Override the @p pin 's working mode.
         *
         * @details Clones the given pin mode to the @code GPFSL0-5 @endcode register
         * on a @p pin's offset.
         *
         * @param[in] pin Pin number.
         * @param[in] mode New pin mode.
         */
        static void SetMode(uint8_t pin, PinMode mode);

        /**
         * @brief Override a Pull-UP/DOWN mode for the specified @p pin.
         *
         * @details Clones the @p mode to the @code GPPUD @endcode register
         * and then enables the bit in the @code GPPUDCLK0/1 @endcode register
         * corresponding to the specified @p pin.
         *
         * @param[in] pin Pin number.
         * @param[in] mode New Pull mode for the pin.
         */
        static void SetPud(uint8_t pin, PudMode mode);
    };
}