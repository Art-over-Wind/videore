#include <dev/crystall/Aux.hpp>
#define AUX_CLOCK_FREQ 19200000

using dev::crystall::aux::MiniUart;

extern "C" void _main()
{
    MiniUart uart = MiniUart(AUX_CLOCK_FREQ, 115200);
    uart.PutString("Hello World!\n");
}