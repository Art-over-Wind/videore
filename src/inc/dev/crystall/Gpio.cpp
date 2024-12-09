#include <dev/crystall/Gpio.hpp>
#include <stdint.h>
#include <dev/crystall/Crystall.hpp>

using dev::crystall::Crystall;

namespace dev::crystall::gpio
{
    namespace
    {
        /// Structure of each register of the GPIO memory.
        struct Reg
        {
            uint32_t _;
            uint32_t reg[2];
        };

        /// GPIO memory IO map.
        struct MemMap
        {
            /// Function select registers.
            uint32_t fsl[6];

            Reg set;
            Reg clr;
            Reg lev;
            Reg eds;
            Reg ren;
            Reg fen;
            Reg hen;
            Reg len;
            Reg arn;
            Reg afn;

            /// Pull Up/Down.
            struct
            {
                uint32_t _;
                uint32_t ctrl;
                uint32_t clk[2];
            } pud;
        };

        /// Actual interface pointer.
        volatile MemMap* GpioDev = (volatile MemMap*)GPIO_BASE;
    }

    PinState Gpio::Read(const uint8_t pin)
    {
        uint8_t idx = pin / 32;
        uint8_t off = pin % 32;
        uint32_t level = GpioDev->lev.reg[idx];

        return (level & (1 << off)) ? PinState::High : PinState::Low;
    }

    void Gpio::Set(const uint8_t pin, const PinState value)
    {
        uint8_t idx = pin / 32;
        uint8_t off = pin % 32;
        uint32_t mask = 1 << off;

        switch (value)
        {
            case PinState::High:
                GpioDev->set.reg[idx] = mask;
                break;

            case PinState::Low:
                GpioDev->clr.reg[idx] = mask;
                break;
        }
    }

    void Gpio::SetMode(uint8_t pin, PinMode mode)
    {
        uint32_t tmp;
        uint8_t idx = pin / 10;
        uint8_t off = (pin * 3) % 30;

        tmp = GpioDev->fsl[idx];
        tmp &= ~(0b111 << off);
        tmp |= ((uint8_t)mode << off);
        GpioDev->fsl[idx] = tmp;
    }

    void Gpio::SetPud(uint8_t pin, PudMode mode)
    {
        uint8_t idx = pin / 32;
        uint8_t off = pin % 32;

        GpioDev->pud.ctrl = (uint32_t)mode;
        Crystall::Waste(150);
        GpioDev->pud.clk[idx] = 1 << off;
        Crystall::Waste(150);

        GpioDev->pud.ctrl = 0;
        GpioDev->pud.clk[idx] = 0;
    }
}
