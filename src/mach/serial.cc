#include "serial.hh"

Serial::Serial(Memory* memory, InterruptController* irc_)
{
    irc = irc_;
    mem = memory;
    cpu_cycles_left_in_transfer = 0;
}

void Serial::emulate(uint64_t cpu_cycles)
{
    if (mem->hff01_sb != 0x00 && mem->hff02_sc == 0x81)
    {
        cout << (char)mem->hff01_sb << endl;
        mem->hff01_sb = 0x00;
        cpu_cycles_left_in_transfer = CPU_CYCLES_PER_BYTE;
    }

    if (cpu_cycles_left_in_transfer <= cpu_cycles)
    {
        irc->request_interrupt(InterruptController::SerialInterrupt);
        cpu_cycles_left_in_transfer = 0;
        mem->hff02_sc = 0x01;
    }
    else
    {
        cpu_cycles_left_in_transfer -= cpu_cycles;
    }

}
