#include "serial.hh"

#include "memory.hh"

Serial::Serial(Registers* reg, Irc* irc_) :
    irc(irc_),
    reg(reg)
{
    cpu_cycles_left_in_transfer = 0;
}