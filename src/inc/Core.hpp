#pragma once
#include <cstdint>
#include <Memory.hpp>

// VC4 interrupt controller base address.
#define VC4_IC = MMIO_BASE + 0x2000;

/**
 * Communication with the @code VideoCore IV @endcode and the @code Cortex @endcode crystalls.
 */
namespace core
{
    /**
     * @brief Spend @p n core cycles.
     * @param n Cycles to spend.
     */
    static void Waste(uint32_t n)
    {
        for (volatile uint32_t i = 0; i < n; i++)
        {
            asm volatile("nop");
        }
    }

    /**
     * @brief Various VideoCore routine.
     */
    class Videocore
    {
    public:
        /**
         * @brief Internal QPU exceptions.
         */
        enum class Interrupt : uint8_t
        {
            Zero                    = 0,
            MisalignedAddress       = 1,
            ZeroDivision            = 2,
            UndefinedInstruction    = 3,
            ForbiddenInstruction    = 4,
            IllegalMemory           = 5,
            BusError                = 6,
            FloatingPoint           = 7,
            Isp                     = 8,
            Dummy                   = 9,
            ICache                  = 10,
            VecCore                 = 11,
            BadL2Alias              = 12,
            Breakpoint              = 13,
        };
    };
}