#pragma once

/**
 * Tools to communicate with the VideoCore itself.
 */
namespace dev::crystall {
    class Crystall
    {
    public:
        /**
         * Waste @p n CPU cycles.
         *
         * @param[in] n Count of cycles to waste.
         */
        static void Waste(uint32_t n)
        {
            for (volatile uint32_t i = 0; i < n; i++)
            {
                asm volatile("nop");
            }
        }
    };
}