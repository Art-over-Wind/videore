#include <dev/crystall/Aux.hpp>
#include <Console.hpp>
#include <String.hpp>
#define AUX_CLOCK_FREQ 19200000

using dev::crystall::aux::MiniUart;
using io::Console;
using type::String;



extern "C" void _main()
{
    MiniUart* Uart = new MiniUart(AUX_CLOCK_FREQ, 115200);

    Uart->PutString("Hello world!");

    delete Uart;
}