#pragma once
#include <stdint.h>
#include <lib/Mmio.hpp>
#include <dev/crystall/Gpio.hpp>
#define AUX_BASE (MMIO_BASE + 0x215000)
#define AUX_PIN_UART_TX 14
#define AUX_PIN_UART_RX 15

using dev::crystall::gpio::Gpio;
using dev::crystall::gpio::PinMode;
using dev::crystall::gpio::PudMode;

/**
 * The AUX controller and their peripherals interface.
 */
namespace dev::crystall::aux {
    namespace
    {
        /// AUX memory map.
        struct MemMap
        {
            uint32_t irq;
            uint32_t enable;

            /// Reserved.
            uint32_t _[14];

            /// Mini UART registers.
            struct
            {
                uint32_t io;
                uint32_t ier;
                uint32_t iir;
                uint32_t lcr;
                uint32_t mcr;
                uint32_t lsr;
                uint32_t msr;
                uint32_t scratch;
                uint32_t ctrl;
                uint32_t stat;
                uint32_t baud;
            } uart;

            /// SPI1 & SPI2 registers.
            struct
            {
                uint32_t ctrl0;
                uint32_t ctrl1;
                uint32_t stat;
                uint32_t io;
                uint32_t peek;
            } spi[2];
        };

        /**
         * @brief Pointer to the actual MMIO interface.
         */
        volatile MemMap* AuxDev = (volatile MemMap*)AUX_BASE;
    }

    /**
     * @brief The Mini UART peripheral interface.
     */
    class MiniUart
    {
    public:
        /**
        * @brief Creates a new UART interface and initializes the device.
        *
        * @param[in] clk The system clock frequency.
        * @param[in] baud Requested speed in baud (Baudrate).
        */
        MiniUart(const uint32_t clk, const uint32_t baud)
        {
            Gpio::SetMode(AUX_PIN_UART_TX, PinMode::Alt5);
            Gpio::SetMode(AUX_PIN_UART_RX, PinMode::Alt5);
            Gpio::SetPud(AUX_PIN_UART_TX, PudMode::Off);
            Gpio::SetPud(AUX_PIN_UART_RX, PudMode::Off);

            AuxDev->enable      = 1;
            AuxDev->uart.ier    = 0;
            AuxDev->uart.ctrl   = 0;
            AuxDev->uart.lcr    = 0b11;
            AuxDev->uart.mcr    = 0;
            AuxDev->uart.ier    = 0;
            AuxDev->uart.iir    = 0;
            AuxDev->uart.baud   = (clk / (baud * 8)) - 1;
            AuxDev->uart.lcr    = 0b11;
            AuxDev->uart.ctrl   = 0b10;
        }

        /**
         * @brief Sends a single ASCII character via the UART interface.
         *
         * @param[in] c Character to send.
         */
        void PutChar(char c);

        /**
         * @brief Sends a string via the UART interface.
         *
         * @param[in] str String to send.
         */
        void PutString(const char* str)
        {
            while (*str) PutChar(*str++);
        }
    };
}