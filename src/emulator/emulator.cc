#include "emulator.hh"

#include "addresses.hh"
#include "cartridge.hh"
#include "cpu.hh"
#include "cpuregisters.hh"
#include "joypad.hh"
#include "memorybus.hh"
#include "ppu.hh"
#include "ppuregisters.hh"
#include "serial.hh"
#include "timer.hh"

Emulator::Emulator()
{
    bootrom = std::make_unique<BootRom>();
    hram = std::make_unique<Hram>();
    oam = std::make_unique<Oam>();
    vram = std::make_unique<Vram>();
    wram0 = std::make_unique<Wram0>();
    wram1 = std::make_unique<Wram1>();
    echoram = std::make_unique<EchoRam>(*wram0, *wram1);

    apu_registers = std::make_unique<ApuRegisters>();
    cpu_registers = std::make_unique<CpuRegisters>();
    joypad_registers = std::make_unique<JoypadRegisters>();
    ppu_registers = std::make_unique<PpuRegisters>();
    serial_registers = std::make_unique<SerialRegisters>();
    timer_registers = std::make_unique<TimerRegisters>();

    mem = std::make_unique<MemoryBus>(
        *bootrom,
        *echoram,
        *hram,
        *oam,
        *vram,
        *wram0,
        *wram1,
        *apu_registers,
        *cpu_registers,
        *joypad_registers,
        *ppu_registers,
        *serial_registers,
        *timer_registers
    );

    cartridge = nullptr;
    cpu = std::make_unique<Cpu>(mem.get(), *cpu_registers);
    joypad = std::make_unique<Joypad>(*joypad_registers, cpu.get());
    ppu = std::make_unique<Ppu>(mem.get(), *ppu_registers, cpu.get());
    serial = std::make_unique<Serial>(*serial_registers, cpu.get());
    timer_divider = std::make_unique<Timer>(*timer_registers, cpu.get());
}

Emulator::~Emulator() = default;

void Emulator::set_frontend(iFrontend* frontend)
{
    ppu->set_frontend(frontend);
}

void Emulator::load_rom(const std::string& filepath)
{
    cartridge = std::make_unique<Cartridge>(filepath);

    mem->set_cartridge(cartridge.get());
    reset_emulation();
}

void Emulator::button_pressed(JoypadButton button)
{
    joypad->button_pressed(button);
}

void Emulator::button_released(JoypadButton button)
{
    joypad->button_released(button);
}

void Emulator::reset_emulation()
{
    mem->hard_reset();
    cpu->hard_reset();
}
