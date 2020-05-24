#include "timer.hh"

#include "memory.hh"

#include <iostream>

namespace antgb
{

Timer::Timer(Registers* reg, Irc* irc_) :
    reg(reg),
    irc(irc_)
{
    timer.unemulated_cpu_cycles = 0;
    divider.unemulated_cpu_cycles = 0;
}

} // namespace antgb
