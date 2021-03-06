#pragma once

#include "emulator/memory/addresses.hh"
#include "emulator/interfaces/imemorybusnode.hh"

#include <array>
#include <cstdint>

class ApuRegisters : public iMemoryBusNode
{
public:    
    ApuRegisters();
    virtual ~ApuRegisters() override;

    virtual bool owns(addr_t address) override;
    virtual uint8_t* get(addr_t address) override;
    virtual uint8_t read(addr_t address) override;
    virtual void write(addr_t address, uint8_t value) override;

protected:
    uint8_t NR10;
    uint8_t NR11;
    uint8_t NR12;
    uint8_t NR13;
    uint8_t NR14;

    uint8_t NR21;
    uint8_t NR22;
    uint8_t NR23;
    uint8_t NR24;

    uint8_t NR30;
    uint8_t NR31;
    uint8_t NR32;
    uint8_t NR33;
    uint8_t NR34;

    uint8_t NR41;
    uint8_t NR42;
    uint8_t NR43;
    uint8_t NR44;

    uint8_t NR50;
    uint8_t NR51;
    uint8_t NR52;

    std::array<uint8_t, WAVERAM_SIZE> waveram;
};
