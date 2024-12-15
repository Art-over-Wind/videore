#include <dev/crystall/Aux.hpp>
#include <String.hpp>

using dev::crystall::aux::MiniUart;
using io::Console;
using type::String;

/**
 * @brief A main runtime function.
 * @param entry Entry address.
 */
extern "C" void _main(uint32_t entry)
{
    MiniUart* uart = new MiniUart(AUX_CLOCK_FREQ, 115200);

    uart->PutString("[Windscape Videore]\n");

    String s1 = "Hello \n";
    uart->PutString("BREAK 1: ");
    uart->Print(s1);

    String s2 = "World!\n";
    uart->PutString("BREAK 2: ");
    uart->Print(s2);

    String str = s1.Add(s2);
    uart->PutString("BREAK 3: ");
    uart->Print(str);

    delete uart;
}