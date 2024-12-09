#include "Aux.hpp"

namespace dev::crystall::aux {
    void MiniUart::PutChar(const char c)
    {
        while ( !(AuxDev->uart.lsr & 0x20) );
        AuxDev->uart.io = c;
    }
}