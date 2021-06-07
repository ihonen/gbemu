#pragma once

#include "cpuregisters.hh"
#include "exceptions.hh"
#include "macros.hh"
#include "types.hh"
#include <array>
#include <fstream>


class MemoryBus;

class Cpu
{
public:
    struct InstructionInfo
    {
        uint8_t len_bytes;
        uint8_t cycles_on_action;
        uint8_t cycles_on_no_action;
        void (Cpu::*handler)();
    };

    enum InterruptId
    {
        VBlankInterrupt = 0x00,
        LcdStatInt      = 0x01,
        TimerInterrupt  = 0x02,
        SerialInterrupt = 0x03,
        JoypadInterrupt = 0x04,
        NoInterrupt     = 0xFF
    };

    typedef struct
    {
        InterruptId source;
        memaddr_t   vector_address;
    } InterruptInfo;

    static const uint64_t CLK_FREQ_Hz = 4194304;
    static const std::array<const InstructionInfo, 256> INSTRUCTION_TABLE;
    static const std::array<const InstructionInfo, 256> CB_INSTRUCTION_TABLE;

    std::ofstream trace_log;

    MemoryBus* mem;

    const memaddr_t INTERRUPT_VECTOR[5] = {0x0040, 0x0048, 0x0050, 0x0058, 0x0060};

    uint64_t vblank_irqs  = 0;
    uint64_t lcdstat_irqs = 0;
    uint64_t timer_irqs   = 0;
    uint64_t serial_irqs  = 0;
    uint64_t joypad_irqs  = 0;

    CpuRegisters& reg;

    const uint8_t* current_instruction = nullptr;
    bool branch_taken = false;
    bool is_halted = false;
    bool is_stopped = false;
    uint64_t clock_cycles = 0;

    static constexpr int NO_COUNTDOWN = -1;
    int DI_countdown = NO_COUNTDOWN;
    int EI_countdown = NO_COUNTDOWN;

    Cpu(MemoryBus* mem, CpuRegisters& registers);
    ~Cpu();
    void hard_reset();
    inline bool has_pending_requests();
    inline InterruptInfo next_request();
    inline void request_interrupt(int source);
    inline bool interrupt_requested(int source);
    inline bool interrupt_enabled(int source);
    inline void clear_interrupt(int source);
    inline void disable_interrupt(int source);
    inline void enable_interrupt(int source);
    void set_PC(uint16_t value);
    void restart();
    void execute(const uint8_t* const instruction = nullptr);
    inline void reset_cycles();
    inline uint64_t get_cycles();
    void jump_to_isr(memaddr_t vector_address);
    void invalid_opcode();
    inline uint8_t extract_immediate8(const uint8_t* instruction = nullptr);
    inline uint16_t extract_immediate16(const uint8_t* instruction = nullptr);

    void ADC_A_HL();
    void ADC_A_n8(uint8_t u8);
    void ADC_A_r8(uint8_t& r8);
    void ADD_A_HL();
    void ADD_A_n8(uint8_t u8);
    void ADD_A_r8(uint8_t& r8);
    void ADD_HL_r16(uint16_t& r16);
    void ADD_SP_e8(int8_t s8);
    void AND_n8(uint8_t u8);
    void AND_HL();
    void AND_r8(uint8_t& r8);
    void BIT_n3_HL(uint8_t n);
    void BIT_n3_r8(uint8_t n, uint8_t& r8);
    void CALL_cc_n16(bool cc, uint16_t n16);
    void CALL_n16(uint16_t n16);
    void CCF();
    void CP_HL();
    void CP_n8(uint8_t n8);
    void CP_r8(uint8_t& r8);
    void CPL();
    void DAA();
    void DEC_HL();
    void DEC_r16(uint16_t& r16);
    void DEC_r8(uint8_t& r8);
    void DI();
    void EI();
    void HALT();
    void INC_HL();
    void INC_r16(uint16_t& r16);
    void INC_r8(uint8_t& r8);
    void JP_HL();
    void JP_cc_n16(bool cc, uint16_t n16);
    void JP_n16(uint16_t n16);
    void JR_cc_n8(bool cc, int8_t n8);
    void JR_n8(int8_t n8);
    void LD_C_A();
    void LD_HL_n8(uint8_t n8);
    void LD_HL_r8(uint8_t& r8);
    void LD_n16_A(uint16_t n16);
    void LD_n16_SP(uint16_t n16);
    void LD_r16_A(uint16_t& r16);
    void LD_A_C();
    void LD_A_n16(uint16_t n16);
    void LD_A_r16(uint16_t& r16);
    void LD_HL_SP_e8(int8_t e8);
    void LD_r16_n16(uint16_t& r16, uint16_t n16);
    void LD_r8_HL(uint8_t& r8);
    void LD_r8_n8(uint8_t& r8, uint8_t n8);
    void LD_r8_r8(uint8_t& r8_1, uint8_t& r8_2);
    void LD_SP_HL();
    void LDD_HL_A();
    void LDD_A_HL();
    void LDH_n8_A(uint8_t n8);
    void LDH_A_n8(uint8_t n8);
    void LDI_HL_A();
    void LDI_A_HL();
    void NOP();
    void OR_HL();
    void OR_n8(uint8_t n8);
    void OR_r8(uint8_t& r8);
    void POP_r16(uint16_t& r16);
    void PUSH_r16(uint16_t& r16);
    void RES_n3_HL(uint8_t n3);
    void RES_n3_r8(uint8_t n3, uint8_t& r8);
    void RET();
    void RET_cc(bool cc);
    void RETI();
    void RL_HL();
    void RL_r8(uint8_t& r8);
    void RLA();
    void RLC_HL();
    void RLC_r8(uint8_t& r8);
    void RLCA();
    void RR_HL();
    void RR_r8(uint8_t& r8);
    void RRA();
    void RRC_HL();
    void RRC_r8(uint8_t& r8);
    void RRCA();
    void RST_f(uint8_t f);
    void SBC_A_HL();
    void SBC_A_n8(uint8_t n8);
    void SBC_A_r8(uint8_t& r8);
    void SCF();
    void SET_n3_HL(uint8_t n3);
    void SET_n3_r8(uint8_t n3, uint8_t& r8);
    void SLA_HL();
    void SLA_r8(uint8_t& r8);
    void SRA_HL();
    void SRA_r8(uint8_t& r8);
    void SRL_HL();
    void SRL_r8(uint8_t& r8);
    void STOP();
    void SUB_A_HL();
    void SUB_A_n8(uint8_t n8);
    void SUB_A_r8(uint8_t& r8);
    void SWAP_HL();
    void SWAP_r8(uint8_t& r8);
    void XOR_HL();
    void XOR_n8(uint8_t n8);
    void XOR_r8(uint8_t& r8);

    // Single-byte opcodes:
    inline void op_00(); inline void op_01(); inline void op_02(); inline void op_03();
    inline void op_04(); inline void op_05(); inline void op_06(); inline void op_07();
    inline void op_08(); inline void op_09(); inline void op_0A(); inline void op_0B();
    inline void op_0C(); inline void op_0D(); inline void op_0E(); inline void op_0F();
    inline void op_10(); inline void op_11(); inline void op_12(); inline void op_13();
    inline void op_14(); inline void op_15(); inline void op_16(); inline void op_17();
    inline void op_18(); inline void op_19(); inline void op_1A(); inline void op_1B();
    inline void op_1C(); inline void op_1D(); inline void op_1E(); inline void op_1F();
    inline void op_20(); inline void op_21(); inline void op_22(); inline void op_23();
    inline void op_24(); inline void op_25(); inline void op_26(); inline void op_27();
    inline void op_28(); inline void op_29(); inline void op_2A(); inline void op_2B();
    inline void op_2C(); inline void op_2D(); inline void op_2E(); inline void op_2F();
    inline void op_30(); inline void op_31(); inline void op_32(); inline void op_33();
    inline void op_34(); inline void op_35(); inline void op_36(); inline void op_37();
    inline void op_38(); inline void op_39(); inline void op_3A(); inline void op_3B();
    inline void op_3C(); inline void op_3D(); inline void op_3E(); inline void op_3F();
    inline void op_40(); inline void op_41(); inline void op_42(); inline void op_43();
    inline void op_44(); inline void op_45(); inline void op_46(); inline void op_47();
    inline void op_48(); inline void op_49(); inline void op_4A(); inline void op_4B();
    inline void op_4C(); inline void op_4D(); inline void op_4E(); inline void op_4F();
    inline void op_50(); inline void op_51(); inline void op_52(); inline void op_53();
    inline void op_54(); inline void op_55(); inline void op_56(); inline void op_57();
    inline void op_58(); inline void op_59(); inline void op_5A(); inline void op_5B();
    inline void op_5C(); inline void op_5D(); inline void op_5E(); inline void op_5F();
    inline void op_60(); inline void op_61(); inline void op_62(); inline void op_63();
    inline void op_64(); inline void op_65(); inline void op_66(); inline void op_67();
    inline void op_68(); inline void op_69(); inline void op_6A(); inline void op_6B();
    inline void op_6C(); inline void op_6D(); inline void op_6E(); inline void op_6F();
    inline void op_70(); inline void op_71(); inline void op_72(); inline void op_73();
    inline void op_74(); inline void op_75(); inline void op_76(); inline void op_77();
    inline void op_78(); inline void op_79(); inline void op_7A(); inline void op_7B();
    inline void op_7C(); inline void op_7D(); inline void op_7E(); inline void op_7F();
    inline void op_80(); inline void op_81(); inline void op_82(); inline void op_83();
    inline void op_84(); inline void op_85(); inline void op_86(); inline void op_87();
    inline void op_88(); inline void op_89(); inline void op_8A(); inline void op_8B();
    inline void op_8C(); inline void op_8D(); inline void op_8E(); inline void op_8F();
    inline void op_90(); inline void op_91(); inline void op_92(); inline void op_93();
    inline void op_94(); inline void op_95(); inline void op_96(); inline void op_97();
    inline void op_98(); inline void op_99(); inline void op_9A(); inline void op_9B();
    inline void op_9C(); inline void op_9D(); inline void op_9E(); inline void op_9F();
    inline void op_A0(); inline void op_A1(); inline void op_A2(); inline void op_A3();
    inline void op_A4(); inline void op_A5(); inline void op_A6(); inline void op_A7();
    inline void op_A8(); inline void op_A9(); inline void op_AA(); inline void op_AB();
    inline void op_AC(); inline void op_AD(); inline void op_AE(); inline void op_AF();
    inline void op_B0(); inline void op_B1(); inline void op_B2(); inline void op_B3();
    inline void op_B4(); inline void op_B5(); inline void op_B6(); inline void op_B7();
    inline void op_B8(); inline void op_B9(); inline void op_BA(); inline void op_BB();
    inline void op_BC(); inline void op_BD(); inline void op_BE(); inline void op_BF();
    inline void op_C0(); inline void op_C1(); inline void op_C2(); inline void op_C3();
    inline void op_C4(); inline void op_C5(); inline void op_C6(); inline void op_C7();
    inline void op_C8(); inline void op_C9(); inline void op_CA(); inline void op_CB();
    inline void op_CC(); inline void op_CD(); inline void op_CE(); inline void op_CF();
    inline void op_D0(); inline void op_D1(); inline void op_D2(); inline void op_D3();
    inline void op_D4(); inline void op_D5(); inline void op_D6(); inline void op_D7();
    inline void op_D8(); inline void op_D9(); inline void op_DA(); inline void op_DB();
    inline void op_DC(); inline void op_DD(); inline void op_DE(); inline void op_DF();
    inline void op_E0(); inline void op_E1(); inline void op_E2(); inline void op_E3();
    inline void op_E4(); inline void op_E5(); inline void op_E6(); inline void op_E7();
    inline void op_E8(); inline void op_E9(); inline void op_EA(); inline void op_EB();
    inline void op_EC(); inline void op_ED(); inline void op_EE(); inline void op_EF();
    inline void op_F0(); inline void op_F1(); inline void op_F2(); inline void op_F3();
    inline void op_F4(); inline void op_F5(); inline void op_F6(); inline void op_F7();
    inline void op_F8(); inline void op_F9(); inline void op_FA(); inline void op_FB();
    inline void op_FC(); inline void op_FD(); inline void op_FE(); inline void op_FF();

    // Two-byte opcodes:
    inline void op_CB_00(); inline void op_CB_01(); inline void op_CB_02(); inline void op_CB_03();
    inline void op_CB_04(); inline void op_CB_05(); inline void op_CB_06(); inline void op_CB_07();
    inline void op_CB_08(); inline void op_CB_09(); inline void op_CB_0A(); inline void op_CB_0B();
    inline void op_CB_0C(); inline void op_CB_0D(); inline void op_CB_0E(); inline void op_CB_0F();
    inline void op_CB_10(); inline void op_CB_11(); inline void op_CB_12(); inline void op_CB_13();
    inline void op_CB_14(); inline void op_CB_15(); inline void op_CB_16(); inline void op_CB_17();
    inline void op_CB_18(); inline void op_CB_19(); inline void op_CB_1A(); inline void op_CB_1B();
    inline void op_CB_1C(); inline void op_CB_1D(); inline void op_CB_1E(); inline void op_CB_1F();
    inline void op_CB_20(); inline void op_CB_21(); inline void op_CB_22(); inline void op_CB_23();
    inline void op_CB_24(); inline void op_CB_25(); inline void op_CB_26(); inline void op_CB_27();
    inline void op_CB_28(); inline void op_CB_29(); inline void op_CB_2A(); inline void op_CB_2B();
    inline void op_CB_2C(); inline void op_CB_2D(); inline void op_CB_2E(); inline void op_CB_2F();
    inline void op_CB_30(); inline void op_CB_31(); inline void op_CB_32(); inline void op_CB_33();
    inline void op_CB_34(); inline void op_CB_35(); inline void op_CB_36(); inline void op_CB_37();
    inline void op_CB_38(); inline void op_CB_39(); inline void op_CB_3A(); inline void op_CB_3B();
    inline void op_CB_3C(); inline void op_CB_3D(); inline void op_CB_3E(); inline void op_CB_3F();
    inline void op_CB_40(); inline void op_CB_41(); inline void op_CB_42(); inline void op_CB_43();
    inline void op_CB_44(); inline void op_CB_45(); inline void op_CB_46(); inline void op_CB_47();
    inline void op_CB_48(); inline void op_CB_49(); inline void op_CB_4A(); inline void op_CB_4B();
    inline void op_CB_4C(); inline void op_CB_4D(); inline void op_CB_4E(); inline void op_CB_4F();
    inline void op_CB_50(); inline void op_CB_51(); inline void op_CB_52(); inline void op_CB_53();
    inline void op_CB_54(); inline void op_CB_55(); inline void op_CB_56(); inline void op_CB_57();
    inline void op_CB_58(); inline void op_CB_59(); inline void op_CB_5A(); inline void op_CB_5B();
    inline void op_CB_5C(); inline void op_CB_5D(); inline void op_CB_5E(); inline void op_CB_5F();
    inline void op_CB_60(); inline void op_CB_61(); inline void op_CB_62(); inline void op_CB_63();
    inline void op_CB_64(); inline void op_CB_65(); inline void op_CB_66(); inline void op_CB_67();
    inline void op_CB_68(); inline void op_CB_69(); inline void op_CB_6A(); inline void op_CB_6B();
    inline void op_CB_6C(); inline void op_CB_6D(); inline void op_CB_6E(); inline void op_CB_6F();
    inline void op_CB_70(); inline void op_CB_71(); inline void op_CB_72(); inline void op_CB_73();
    inline void op_CB_74(); inline void op_CB_75(); inline void op_CB_76(); inline void op_CB_77();
    inline void op_CB_78(); inline void op_CB_79(); inline void op_CB_7A(); inline void op_CB_7B();
    inline void op_CB_7C(); inline void op_CB_7D(); inline void op_CB_7E(); inline void op_CB_7F();
    inline void op_CB_80(); inline void op_CB_81(); inline void op_CB_82(); inline void op_CB_83();
    inline void op_CB_84(); inline void op_CB_85(); inline void op_CB_86(); inline void op_CB_87();
    inline void op_CB_88(); inline void op_CB_89(); inline void op_CB_8A(); inline void op_CB_8B();
    inline void op_CB_8C(); inline void op_CB_8D(); inline void op_CB_8E(); inline void op_CB_8F();
    inline void op_CB_90(); inline void op_CB_91(); inline void op_CB_92(); inline void op_CB_93();
    inline void op_CB_94(); inline void op_CB_95(); inline void op_CB_96(); inline void op_CB_97();
    inline void op_CB_98(); inline void op_CB_99(); inline void op_CB_9A(); inline void op_CB_9B();
    inline void op_CB_9C(); inline void op_CB_9D(); inline void op_CB_9E(); inline void op_CB_9F();
    inline void op_CB_A0(); inline void op_CB_A1(); inline void op_CB_A2(); inline void op_CB_A3();
    inline void op_CB_A4(); inline void op_CB_A5(); inline void op_CB_A6(); inline void op_CB_A7();
    inline void op_CB_A8(); inline void op_CB_A9(); inline void op_CB_AA(); inline void op_CB_AB();
    inline void op_CB_AC(); inline void op_CB_AD(); inline void op_CB_AE(); inline void op_CB_AF();
    inline void op_CB_B0(); inline void op_CB_B1(); inline void op_CB_B2(); inline void op_CB_B3();
    inline void op_CB_B4(); inline void op_CB_B5(); inline void op_CB_B6(); inline void op_CB_B7();
    inline void op_CB_B8(); inline void op_CB_B9(); inline void op_CB_BA(); inline void op_CB_BB();
    inline void op_CB_BC(); inline void op_CB_BD(); inline void op_CB_BE(); inline void op_CB_BF();
    inline void op_CB_C0(); inline void op_CB_C1(); inline void op_CB_C2(); inline void op_CB_C3();
    inline void op_CB_C4(); inline void op_CB_C5(); inline void op_CB_C6(); inline void op_CB_C7();
    inline void op_CB_C8(); inline void op_CB_C9(); inline void op_CB_CA(); inline void op_CB_CB();
    inline void op_CB_CC(); inline void op_CB_CD(); inline void op_CB_CE(); inline void op_CB_CF();
    inline void op_CB_D0(); inline void op_CB_D1(); inline void op_CB_D2(); inline void op_CB_D3();
    inline void op_CB_D4(); inline void op_CB_D5(); inline void op_CB_D6(); inline void op_CB_D7();
    inline void op_CB_D8(); inline void op_CB_D9(); inline void op_CB_DA(); inline void op_CB_DB();
    inline void op_CB_DC(); inline void op_CB_DD(); inline void op_CB_DE(); inline void op_CB_DF();
    inline void op_CB_E0(); inline void op_CB_E1(); inline void op_CB_E2(); inline void op_CB_E3();
    inline void op_CB_E4(); inline void op_CB_E5(); inline void op_CB_E6(); inline void op_CB_E7();
    inline void op_CB_E8(); inline void op_CB_E9(); inline void op_CB_EA(); inline void op_CB_EB();
    inline void op_CB_EC(); inline void op_CB_ED(); inline void op_CB_EE(); inline void op_CB_EF();
    inline void op_CB_F0(); inline void op_CB_F1(); inline void op_CB_F2(); inline void op_CB_F3();
    inline void op_CB_F4(); inline void op_CB_F5(); inline void op_CB_F6(); inline void op_CB_F7();
    inline void op_CB_F8(); inline void op_CB_F9(); inline void op_CB_FA(); inline void op_CB_FB();
    inline void op_CB_FC(); inline void op_CB_FD(); inline void op_CB_FE(); inline void op_CB_FF();
};

FORCE_INLINE uint64_t Cpu::get_cycles()
{
    return clock_cycles;
}

FORCE_INLINE void Cpu::reset_cycles()
{
    clock_cycles = 0;
}

FORCE_INLINE bool Cpu::has_pending_requests()
{
    return (reg.read_IF() & 0x1F) != 0;
}

FORCE_INLINE Cpu::InterruptInfo Cpu::next_request()
{
    for (InterruptId i = VBlankInterrupt; i < JoypadInterrupt;
         i             = (InterruptId)((int)i + 1))
    {
        if (interrupt_enabled(i) && interrupt_requested(i))
        {
            return {(InterruptId)i, INTERRUPT_VECTOR[i]};
        }
    }

    return {NoInterrupt, 0x0000};
}

FORCE_INLINE void Cpu::request_interrupt(int source)
{
    switch (source)
    {
    case VBlankInterrupt: ++vblank_irqs; break;
    case LcdStatInt: ++lcdstat_irqs; break;
    case JoypadInterrupt: ++joypad_irqs; break;
    case TimerInterrupt: ++timer_irqs; break;
    case SerialInterrupt: ++serial_irqs; break;
    }

    reg.write_IF(reg.read_IF() | (0x01 << source));
}

FORCE_INLINE bool Cpu::interrupt_requested(int source)
{
    return (reg.read_IF() & (0x01 << source)) != 0;
}

FORCE_INLINE bool Cpu::interrupt_enabled(int source)
{
    return (reg.read_IE() & (0x01 << source)) != 0;
}

FORCE_INLINE void Cpu::clear_interrupt(int source)
{
    reg.write_IF(reg.read_IF() & ~(0x01 << source));
}

FORCE_INLINE void Cpu::disable_interrupt(int source)
{
    reg.write_IE(reg.read_IE() & ~(0x01 << source));
}

FORCE_INLINE void Cpu::enable_interrupt(int source)
{
    reg.write_IE(reg.read_IE() | (0x01 << source));
}

FORCE_INLINE uint8_t Cpu::extract_immediate8(const uint8_t* instruction)
{
    if (!instruction) instruction = current_instruction;
    return current_instruction[1];
}

FORCE_INLINE uint16_t Cpu::extract_immediate16(const uint8_t* instruction)
{
    if (!instruction) instruction = current_instruction;
    return (static_cast<uint16_t>(instruction[1])) |
           (static_cast<uint16_t>(instruction[2]) << 8);
}

FORCE_INLINE void Cpu::op_00()
{
    NOP();
}

FORCE_INLINE void Cpu::op_01()
{
    LD_r16_n16(reg.get_BC(), extract_immediate16());
}

FORCE_INLINE void Cpu::op_02()
{
    LD_r16_A(reg.get_BC());
}

FORCE_INLINE void Cpu::op_03()
{
    INC_r16(reg.get_BC());
}

FORCE_INLINE void Cpu::op_04()
{
    INC_r8(reg.get_B());
}

FORCE_INLINE void Cpu::op_05()
{
    DEC_r8(reg.get_B());
}

FORCE_INLINE void Cpu::op_06()
{
    LD_r8_n8(reg.get_B(), extract_immediate8());
}

FORCE_INLINE void Cpu::op_07()
{
    RLCA();
}

FORCE_INLINE void Cpu::op_08()
{
    LD_n16_SP(extract_immediate16());
}

FORCE_INLINE void Cpu::op_09()
{
    ADD_HL_r16(reg.get_BC());
}

FORCE_INLINE void Cpu::op_0A()
{
    LD_A_r16(reg.get_BC());
}

FORCE_INLINE void Cpu::op_0B()
{
    DEC_r16(reg.get_BC());
}

FORCE_INLINE void Cpu::op_0C()
{
    INC_r8(reg.get_C());
}

FORCE_INLINE void Cpu::op_0D()
{
    DEC_r8(reg.get_C());
}

FORCE_INLINE void Cpu::op_0E()
{
    LD_r8_n8(reg.get_C(), extract_immediate8());
}

FORCE_INLINE void Cpu::op_0F()
{
    RRCA();
}

FORCE_INLINE void Cpu::op_10()
{
    STOP();
}

FORCE_INLINE void Cpu::op_11()
{
    LD_r16_n16(reg.get_DE(), extract_immediate16());
}

FORCE_INLINE void Cpu::op_12()
{
    LD_r16_A(reg.get_DE());
}

FORCE_INLINE void Cpu::op_13()
{
    INC_r16(reg.get_DE());
}

FORCE_INLINE void Cpu::op_14()
{
    INC_r8(reg.get_D());
}

FORCE_INLINE void Cpu::op_15()
{
    DEC_r8(reg.get_D());
}

FORCE_INLINE void Cpu::op_16()
{
    LD_r8_n8(reg.get_D(), extract_immediate8());
}

FORCE_INLINE void Cpu::op_17()
{
    RLA();
}

FORCE_INLINE void Cpu::op_18()
{
    JR_n8(static_cast<int8_t>(extract_immediate8()));
}

FORCE_INLINE void Cpu::op_19()
{
    ADD_HL_r16(reg.get_DE());
}

FORCE_INLINE void Cpu::op_1A()
{
    LD_A_r16(reg.get_DE());
}

FORCE_INLINE void Cpu::op_1B()
{
    DEC_r16(reg.get_DE());
}

FORCE_INLINE void Cpu::op_1C()
{
    INC_r8(reg.get_E());
}

FORCE_INLINE void Cpu::op_1D()
{
    DEC_r8(reg.get_E());
}

FORCE_INLINE void Cpu::op_1E()
{
    LD_r8_n8(reg.get_E(), extract_immediate8());
}

FORCE_INLINE void Cpu::op_1F()
{
    RRA();
}

FORCE_INLINE void Cpu::op_20()
{
    JR_cc_n8(!reg.read_Z_flag(), static_cast<int8_t>(extract_immediate8()));
}

FORCE_INLINE void Cpu::op_21()
{
    LD_r16_n16(reg.get_HL(), extract_immediate16());
}

FORCE_INLINE void Cpu::op_22()
{
    LDI_HL_A();
}

FORCE_INLINE void Cpu::op_23()
{
    INC_r16(reg.get_HL());
}

FORCE_INLINE void Cpu::op_24()
{
    INC_r8(reg.get_H());
}

FORCE_INLINE void Cpu::op_25()
{
    DEC_r8(reg.get_H());
}

FORCE_INLINE void Cpu::op_26()
{
    LD_r8_n8(reg.get_H(), extract_immediate8());
}

FORCE_INLINE void Cpu::op_27()
{
    DAA();
}

FORCE_INLINE void Cpu::op_28()
{
    JR_cc_n8(reg.read_Z_flag(), static_cast<int8_t>(extract_immediate8()));
}

FORCE_INLINE void Cpu::op_29()
{
    ADD_HL_r16(reg.get_HL());
}

FORCE_INLINE void Cpu::op_2A()
{
    LDI_A_HL();
}

FORCE_INLINE void Cpu::op_2B()
{
    DEC_r16(reg.get_HL());
}

FORCE_INLINE void Cpu::op_2C()
{
    INC_r8(reg.get_L());
}

FORCE_INLINE void Cpu::op_2D()
{
    DEC_r8(reg.get_L());
}

FORCE_INLINE void Cpu::op_2E()
{
    LD_r8_n8(reg.get_L(), extract_immediate8());
}

FORCE_INLINE void Cpu::op_2F()
{
    CPL();
}

FORCE_INLINE void Cpu::op_30()
{
    JR_cc_n8(!reg.read_C_flag(), static_cast<int8_t>(extract_immediate8()));
}

FORCE_INLINE void Cpu::op_31()
{
    LD_r16_n16(reg.get_SP(), extract_immediate16());
}

FORCE_INLINE void Cpu::op_32()
{
    LDD_HL_A();
}

FORCE_INLINE void Cpu::op_33()
{
    INC_r16(reg.get_SP());
}

FORCE_INLINE void Cpu::op_34()
{
    INC_HL();
}

FORCE_INLINE void Cpu::op_35()
{
    DEC_HL();
}

FORCE_INLINE void Cpu::op_36()
{
    LD_HL_n8(extract_immediate8());
}

FORCE_INLINE void Cpu::op_37()
{
    SCF();
}

FORCE_INLINE void Cpu::op_38()
{
    JR_cc_n8(reg.read_C_flag(), static_cast<int8_t>(extract_immediate8()));
}

FORCE_INLINE void Cpu::op_39()
{
    ADD_HL_r16(reg.get_SP());
}

FORCE_INLINE void Cpu::op_3A()
{
    LDD_A_HL();
}

FORCE_INLINE void Cpu::op_3B()
{
    DEC_r16(reg.get_SP());
}

FORCE_INLINE void Cpu::op_3C()
{
    INC_r8(reg.get_A());
}

FORCE_INLINE void Cpu::op_3D()
{
    DEC_r8(reg.get_A());
}

FORCE_INLINE void Cpu::op_3E()
{
    LD_r8_n8(reg.get_A(), extract_immediate8());
}

FORCE_INLINE void Cpu::op_3F()
{
    CCF();
}

FORCE_INLINE void Cpu::op_40()
{
    LD_r8_r8(reg.get_B(), reg.get_B());
}

FORCE_INLINE void Cpu::op_41()
{
    LD_r8_r8(reg.get_B(), reg.get_C());
}

FORCE_INLINE void Cpu::op_42()
{
    LD_r8_r8(reg.get_B(), reg.get_D());
}

FORCE_INLINE void Cpu::op_43()
{
    LD_r8_r8(reg.get_B(), reg.get_E());
}

FORCE_INLINE void Cpu::op_44()
{
    LD_r8_r8(reg.get_B(), reg.get_H());
}

FORCE_INLINE void Cpu::op_45()
{
    LD_r8_r8(reg.get_B(), reg.get_L());
}

FORCE_INLINE void Cpu::op_46()
{
    LD_r8_HL(reg.get_B());
}

FORCE_INLINE void Cpu::op_47()
{
    LD_r8_r8(reg.get_B(), reg.get_A());
}

FORCE_INLINE void Cpu::op_48()
{
    LD_r8_r8(reg.get_C(), reg.get_B());
}

FORCE_INLINE void Cpu::op_49()
{
    LD_r8_r8(reg.get_C(), reg.get_C());
}

FORCE_INLINE void Cpu::op_4A()
{
    LD_r8_r8(reg.get_C(), reg.get_D());
}

FORCE_INLINE void Cpu::op_4B()
{
    LD_r8_r8(reg.get_C(), reg.get_E());
}

FORCE_INLINE void Cpu::op_4C()
{
    LD_r8_r8(reg.get_C(), reg.get_H());
}

FORCE_INLINE void Cpu::op_4D()
{
    LD_r8_r8(reg.get_C(), reg.get_L());
}

FORCE_INLINE void Cpu::op_4E()
{
    LD_r8_HL(reg.get_C());
}

FORCE_INLINE void Cpu::op_4F()
{
    LD_r8_r8(reg.get_C(), reg.get_A());
}

FORCE_INLINE void Cpu::op_50()
{
    LD_r8_r8(reg.get_D(), reg.get_B());
}

FORCE_INLINE void Cpu::op_51()
{
    LD_r8_r8(reg.get_D(), reg.get_C());
}

FORCE_INLINE void Cpu::op_52()
{
    LD_r8_r8(reg.get_D(), reg.get_D());
}

FORCE_INLINE void Cpu::op_53()
{
    LD_r8_r8(reg.get_D(), reg.get_E());
}

FORCE_INLINE void Cpu::op_54()
{
    LD_r8_r8(reg.get_D(), reg.get_H());
}

FORCE_INLINE void Cpu::op_55()
{
    LD_r8_r8(reg.get_D(), reg.get_L());
}

FORCE_INLINE void Cpu::op_56()
{
    LD_r8_HL(reg.get_D());
}

FORCE_INLINE void Cpu::op_57()
{
    LD_r8_r8(reg.get_D(), reg.get_A());
}

FORCE_INLINE void Cpu::op_58()
{
    LD_r8_r8(reg.get_E(), reg.get_B());
}

FORCE_INLINE void Cpu::op_59()
{
    LD_r8_r8(reg.get_E(), reg.get_C());
}

FORCE_INLINE void Cpu::op_5A()
{
    LD_r8_r8(reg.get_E(), reg.get_D());
}

FORCE_INLINE void Cpu::op_5B()
{
    LD_r8_r8(reg.get_E(), reg.get_E());
}

FORCE_INLINE void Cpu::op_5C()
{
    LD_r8_r8(reg.get_E(), reg.get_H());
}

FORCE_INLINE void Cpu::op_5D()
{
    LD_r8_r8(reg.get_E(), reg.get_L());
}

FORCE_INLINE void Cpu::op_5E()
{
    LD_r8_HL(reg.get_E());
}

FORCE_INLINE void Cpu::op_5F()
{
    LD_r8_r8(reg.get_E(), reg.get_A());
}

FORCE_INLINE void Cpu::op_60()
{
    LD_r8_r8(reg.get_H(), reg.get_B());
}

FORCE_INLINE void Cpu::op_61()
{
    LD_r8_r8(reg.get_H(), reg.get_C());
}

FORCE_INLINE void Cpu::op_62()
{
    LD_r8_r8(reg.get_H(), reg.get_D());
}

FORCE_INLINE void Cpu::op_63()
{
    LD_r8_r8(reg.get_H(), reg.get_E());
}

FORCE_INLINE void Cpu::op_64()
{
    LD_r8_r8(reg.get_H(), reg.get_H());
}

FORCE_INLINE void Cpu::op_65()
{
    LD_r8_r8(reg.get_H(), reg.get_L());
}

FORCE_INLINE void Cpu::op_66()
{
    LD_r8_HL(reg.get_H());
}

FORCE_INLINE void Cpu::op_67()
{
    LD_r8_r8(reg.get_H(), reg.get_A());
}

FORCE_INLINE void Cpu::op_68()
{
    LD_r8_r8(reg.get_L(), reg.get_B());
}

FORCE_INLINE void Cpu::op_69()
{
    LD_r8_r8(reg.get_L(), reg.get_C());
}

FORCE_INLINE void Cpu::op_6A()
{
    LD_r8_r8(reg.get_L(), reg.get_D());
}

FORCE_INLINE void Cpu::op_6B()
{
    LD_r8_r8(reg.get_L(), reg.get_E());
}

FORCE_INLINE void Cpu::op_6C()
{
    LD_r8_r8(reg.get_L(), reg.get_H());
}

FORCE_INLINE void Cpu::op_6D()
{
    LD_r8_r8(reg.get_L(), reg.get_L());
}

FORCE_INLINE void Cpu::op_6E()
{
    LD_r8_HL(reg.get_L());
}

FORCE_INLINE void Cpu::op_6F()
{
    LD_r8_r8(reg.get_L(), reg.get_A());
}

FORCE_INLINE void Cpu::op_70()
{
    LD_HL_r8(reg.get_B());
}

FORCE_INLINE void Cpu::op_71()
{
    LD_HL_r8(reg.get_C());
}

FORCE_INLINE void Cpu::op_72()
{
    LD_HL_r8(reg.get_D());
}

FORCE_INLINE void Cpu::op_73()
{
    LD_HL_r8(reg.get_E());
}

FORCE_INLINE void Cpu::op_74()
{
    LD_HL_r8(reg.get_H());
}

FORCE_INLINE void Cpu::op_75()
{
    LD_HL_r8(reg.get_L());
}

FORCE_INLINE void Cpu::op_76()
{
    HALT();
}

FORCE_INLINE void Cpu::op_77()
{
    LD_HL_r8(reg.get_A());
}

FORCE_INLINE void Cpu::op_78()
{
    LD_r8_r8(reg.get_A(), reg.get_B());
}

FORCE_INLINE void Cpu::op_79()
{
    LD_r8_r8(reg.get_A(), reg.get_C());
}

FORCE_INLINE void Cpu::op_7A()
{
    LD_r8_r8(reg.get_A(), reg.get_D());
}

FORCE_INLINE void Cpu::op_7B()
{
    LD_r8_r8(reg.get_A(), reg.get_E());
}

FORCE_INLINE void Cpu::op_7C()
{
    LD_r8_r8(reg.get_A(), reg.get_H());
}

FORCE_INLINE void Cpu::op_7D()
{
    LD_r8_r8(reg.get_A(), reg.get_L());
}

FORCE_INLINE void Cpu::op_7E()
{
    LD_A_r16(reg.get_HL());
}

FORCE_INLINE void Cpu::op_7F()
{
    LD_r8_r8(reg.get_A(), reg.get_A());
}

FORCE_INLINE void Cpu::op_80()
{
    ADD_A_r8(reg.get_B());
}

FORCE_INLINE void Cpu::op_81()
{
    ADD_A_r8(reg.get_C());
}

FORCE_INLINE void Cpu::op_82()
{
    ADD_A_r8(reg.get_D());
}

FORCE_INLINE void Cpu::op_83()
{
    ADD_A_r8(reg.get_E());
}

FORCE_INLINE void Cpu::op_84()
{
    ADD_A_r8(reg.get_H());
}

FORCE_INLINE void Cpu::op_85()
{
    ADD_A_r8(reg.get_L());
}

FORCE_INLINE void Cpu::op_86()
{
    ADD_A_HL();
}

FORCE_INLINE void Cpu::op_87()
{
    ADD_A_r8(reg.get_A());
}

FORCE_INLINE void Cpu::op_88()
{
    ADC_A_r8(reg.get_B());
}

FORCE_INLINE void Cpu::op_89()
{
    ADC_A_r8(reg.get_C());
}

FORCE_INLINE void Cpu::op_8A()
{
    ADC_A_r8(reg.get_D());
}

FORCE_INLINE void Cpu::op_8B()
{
    ADC_A_r8(reg.get_E());
}

FORCE_INLINE void Cpu::op_8C()
{
    ADC_A_r8(reg.get_H());
}

FORCE_INLINE void Cpu::op_8D()
{
    ADC_A_r8(reg.get_L());
}

FORCE_INLINE void Cpu::op_8E()
{
    ADC_A_HL();
}

FORCE_INLINE void Cpu::op_8F()
{
    ADC_A_r8(reg.get_A());
}

FORCE_INLINE void Cpu::op_90()
{
    SUB_A_r8(reg.get_B());
}

FORCE_INLINE void Cpu::op_91()
{
    SUB_A_r8(reg.get_C());
}

FORCE_INLINE void Cpu::op_92()
{
    SUB_A_r8(reg.get_D());
}

FORCE_INLINE void Cpu::op_93()
{
    SUB_A_r8(reg.get_E());
}

FORCE_INLINE void Cpu::op_94()
{
    SUB_A_r8(reg.get_H());
}

FORCE_INLINE void Cpu::op_95()
{
    SUB_A_r8(reg.get_L());
}

FORCE_INLINE void Cpu::op_96()
{
    //
    SUB_A_HL();
}

FORCE_INLINE void Cpu::op_97()
{
    SUB_A_r8(reg.get_A());
}

FORCE_INLINE void Cpu::op_98()
{
    SBC_A_r8(reg.get_B());
}

FORCE_INLINE void Cpu::op_99()
{
    SBC_A_r8(reg.get_C());
}

FORCE_INLINE void Cpu::op_9A()
{
    SBC_A_r8(reg.get_D());
}

FORCE_INLINE void Cpu::op_9B()
{
    SBC_A_r8(reg.get_E());
}

FORCE_INLINE void Cpu::op_9C()
{
    SBC_A_r8(reg.get_H());
}

FORCE_INLINE void Cpu::op_9D()
{
    SBC_A_r8(reg.get_L());
}

FORCE_INLINE void Cpu::op_9E()
{
    SBC_A_HL();
}

FORCE_INLINE void Cpu::op_9F()
{
    SBC_A_r8(reg.get_A());
}

FORCE_INLINE void Cpu::op_A0()
{
    AND_r8(reg.get_B());
}

FORCE_INLINE void Cpu::op_A1()
{
    AND_r8(reg.get_C());
}

FORCE_INLINE void Cpu::op_A2()
{
    AND_r8(reg.get_D());
}

FORCE_INLINE void Cpu::op_A3()
{
    AND_r8(reg.get_E());
}

FORCE_INLINE void Cpu::op_A4()
{
    AND_r8(reg.get_H());
}

FORCE_INLINE void Cpu::op_A5()
{
    AND_r8(reg.get_L());
}

FORCE_INLINE void Cpu::op_A6()
{
    AND_HL();
}

FORCE_INLINE void Cpu::op_A7()
{
    AND_r8(reg.get_A());
}

FORCE_INLINE void Cpu::op_A8()
{
    XOR_r8(reg.get_B());
}

FORCE_INLINE void Cpu::op_A9()
{
    XOR_r8(reg.get_C());
}

FORCE_INLINE void Cpu::op_AA()
{
    XOR_r8(reg.get_D());
}

FORCE_INLINE void Cpu::op_AB()
{
    XOR_r8(reg.get_E());
}

FORCE_INLINE void Cpu::op_AC()
{
    XOR_r8(reg.get_H());
}

FORCE_INLINE void Cpu::op_AD()
{
    XOR_r8(reg.get_L());
}

FORCE_INLINE void Cpu::op_AE()
{
    XOR_HL();
}

FORCE_INLINE void Cpu::op_AF()
{
    XOR_r8(reg.get_A());
}

FORCE_INLINE void Cpu::op_B0()
{
    OR_r8(reg.get_B());
}

FORCE_INLINE void Cpu::op_B1()
{
    OR_r8(reg.get_C());
}

FORCE_INLINE void Cpu::op_B2()
{
    OR_r8(reg.get_D());
}

FORCE_INLINE void Cpu::op_B3()
{
    OR_r8(reg.get_E());
}

FORCE_INLINE void Cpu::op_B4()
{
    OR_r8(reg.get_H());
}

FORCE_INLINE void Cpu::op_B5()
{
    OR_r8(reg.get_L());
}

FORCE_INLINE void Cpu::op_B6()
{
    OR_HL();
}

FORCE_INLINE void Cpu::op_B7()
{
    OR_r8(reg.get_A());
}

FORCE_INLINE void Cpu::op_B8()
{
    CP_r8(reg.get_B());
}

FORCE_INLINE void Cpu::op_B9()
{
    CP_r8(reg.get_C());
}

FORCE_INLINE void Cpu::op_BA()
{
    CP_r8(reg.get_D());
}

FORCE_INLINE void Cpu::op_BB()
{
    CP_r8(reg.get_E());
}

FORCE_INLINE void Cpu::op_BC()
{
    CP_r8(reg.get_H());
}

FORCE_INLINE void Cpu::op_BD()
{
    CP_r8(reg.get_L());
}

FORCE_INLINE void Cpu::op_BE()
{
    CP_HL();
}

FORCE_INLINE void Cpu::op_BF()
{
    CP_r8(reg.get_A());
}

FORCE_INLINE void Cpu::op_C0()
{
    RET_cc(!reg.read_Z_flag());
}

FORCE_INLINE void Cpu::op_C1()
{
    POP_r16(reg.get_BC());
}

FORCE_INLINE void Cpu::op_C2()
{
    JP_cc_n16(!reg.read_Z_flag(), extract_immediate16());
}

FORCE_INLINE void Cpu::op_C3()
{
    JP_n16(extract_immediate16());
}

FORCE_INLINE void Cpu::op_C4()
{
    CALL_cc_n16(!reg.read_Z_flag(), extract_immediate16());
}

FORCE_INLINE void Cpu::op_C5()
{
    PUSH_r16(reg.get_BC());
}

FORCE_INLINE void Cpu::op_C6()
{
    ADD_A_n8(extract_immediate8());
}

FORCE_INLINE void Cpu::op_C7()
{
    RST_f(0x00);
}

FORCE_INLINE void Cpu::op_C8()
{
    RET_cc(reg.read_Z_flag());
}

FORCE_INLINE void Cpu::op_C9()
{
    RET();
}

FORCE_INLINE void Cpu::op_CA()
{
    JP_cc_n16(reg.read_Z_flag(), extract_immediate16());
}

FORCE_INLINE void Cpu::op_CB()
{
    // SHOULD NOT END UP HERE
}

FORCE_INLINE void Cpu::op_CC()
{
    CALL_cc_n16(reg.read_Z_flag(), extract_immediate16());
}

FORCE_INLINE void Cpu::op_CD()
{
    CALL_n16(extract_immediate16());
}

FORCE_INLINE void Cpu::op_CE()
{
    ADC_A_n8(extract_immediate8());
}

FORCE_INLINE void Cpu::op_CF()
{
    RST_f(0x08);
}

FORCE_INLINE void Cpu::op_D0()
{
    RET_cc(!reg.read_C_flag());
}

FORCE_INLINE void Cpu::op_D1()
{
    POP_r16(reg.get_DE());
}

FORCE_INLINE void Cpu::op_D2()
{
    JP_cc_n16(!reg.read_C_flag(), extract_immediate16());
}

FORCE_INLINE void Cpu::op_D3()
{
    invalid_opcode();
}

FORCE_INLINE void Cpu::op_D4()
{
    CALL_cc_n16(!reg.read_C_flag(), extract_immediate16());
}

FORCE_INLINE void Cpu::op_D5()
{
    PUSH_r16(reg.get_DE());
}

FORCE_INLINE void Cpu::op_D6()
{
    SUB_A_n8(extract_immediate8());
}

FORCE_INLINE void Cpu::op_D7()
{
    RST_f(0x10);
}

FORCE_INLINE void Cpu::op_D8()
{
    RET_cc(reg.read_C_flag());
}

FORCE_INLINE void Cpu::op_D9()
{
    RETI();
}

FORCE_INLINE void Cpu::op_DA()
{
    JP_cc_n16(reg.read_C_flag(), extract_immediate16());
}

FORCE_INLINE void Cpu::op_DB()
{
    invalid_opcode();
}

FORCE_INLINE void Cpu::op_DC()
{
    CALL_cc_n16(reg.read_C_flag(), extract_immediate16());
}

FORCE_INLINE void Cpu::op_DD()
{
    invalid_opcode();
}

FORCE_INLINE void Cpu::op_DE()
{
    SBC_A_n8(extract_immediate8());
}

FORCE_INLINE void Cpu::op_DF()
{
    RST_f(0x18);
}

FORCE_INLINE void Cpu::op_E0()
{
    LDH_n8_A(extract_immediate8());
}

FORCE_INLINE void Cpu::op_E1()
{
    POP_r16(reg.get_HL());
}

FORCE_INLINE void Cpu::op_E2()
{
    LD_C_A();
}

FORCE_INLINE void Cpu::op_E3()
{
    invalid_opcode();
}

FORCE_INLINE void Cpu::op_E4()
{
    invalid_opcode();
}

FORCE_INLINE void Cpu::op_E5()
{
    PUSH_r16(reg.get_HL());
}

FORCE_INLINE void Cpu::op_E6()
{
    AND_n8(extract_immediate8());
}

FORCE_INLINE void Cpu::op_E7()
{
    RST_f(0x20);
}

FORCE_INLINE void Cpu::op_E8()
{
    ADD_SP_e8(static_cast<int8_t>(extract_immediate8()));
}

FORCE_INLINE void Cpu::op_E9()
{
    JP_n16(reg.get_HL());
}

FORCE_INLINE void Cpu::op_EA()
{
    LD_n16_A(extract_immediate16());
}

FORCE_INLINE void Cpu::op_EB()
{
    invalid_opcode();
}

FORCE_INLINE void Cpu::op_EC()
{
    invalid_opcode();
}

FORCE_INLINE void Cpu::op_ED()
{
    invalid_opcode();
}

FORCE_INLINE void Cpu::op_EE()
{
    XOR_n8(extract_immediate8());
}

FORCE_INLINE void Cpu::op_EF()
{
    RST_f(0x28);
}

FORCE_INLINE void Cpu::op_F0()
{
    LDH_A_n8(extract_immediate8());
}

FORCE_INLINE void Cpu::op_F1()
{
    POP_r16(reg.get_AF());
    // Only the upper nibble of F can be written into, so make sure the lower
    // nibble is zero.
    reg.write_F(reg.read_F());
}

FORCE_INLINE void Cpu::op_F2()
{
    LD_A_C();
}

FORCE_INLINE void Cpu::op_F3()
{
    DI();
}

FORCE_INLINE void Cpu::op_F4()
{
    invalid_opcode();
}

FORCE_INLINE void Cpu::op_F5()
{
    PUSH_r16(reg.get_AF());
}

FORCE_INLINE void Cpu::op_F6()
{
    OR_n8(extract_immediate8());
}

FORCE_INLINE void Cpu::op_F7()
{
    RST_f(0x30);
}

FORCE_INLINE void Cpu::op_F8()
{
    LD_HL_SP_e8(static_cast<int8_t>(extract_immediate8()));
}

FORCE_INLINE void Cpu::op_F9()
{
    LD_SP_HL();
}

FORCE_INLINE void Cpu::op_FA()
{
    LD_A_n16(extract_immediate16());
}

FORCE_INLINE void Cpu::op_FB()
{
    EI();
}

FORCE_INLINE void Cpu::op_FC()
{
    invalid_opcode();
}

FORCE_INLINE void Cpu::op_FD()
{
    invalid_opcode();
}

FORCE_INLINE void Cpu::op_FE()
{
    CP_n8(extract_immediate8());
}

FORCE_INLINE void Cpu::op_FF()
{
    RST_f(0x38);
}

FORCE_INLINE void Cpu::op_CB_00()
{
    RLC_r8(reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_01()
{
    RLC_r8(reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_02()
{
    RLC_r8(reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_03()
{
    RLC_r8(reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_04()
{
    RLC_r8(reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_05()
{
    RLC_r8(reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_06()
{
    RLC_HL();
}

FORCE_INLINE void Cpu::op_CB_07()
{
    RLC_r8(reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_08()
{
    RRC_r8(reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_09()
{
    RRC_r8(reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_0A()
{
    RRC_r8(reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_0B()
{
    RRC_r8(reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_0C()
{
    RRC_r8(reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_0D()
{
    RRC_r8(reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_0E()
{
    RRC_HL();
}

FORCE_INLINE void Cpu::op_CB_0F()
{
    RRC_r8(reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_10()
{
    RL_r8(reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_11()
{
    RL_r8(reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_12()
{
    RL_r8(reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_13()
{
    RL_r8(reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_14()
{
    RL_r8(reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_15()
{
    RL_r8(reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_16()
{
    RL_HL();
}

FORCE_INLINE void Cpu::op_CB_17()
{
    RL_r8(reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_18()
{
    RR_r8(reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_19()
{
    RR_r8(reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_1A()
{
    RR_r8(reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_1B()
{
    RR_r8(reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_1C()
{
    RR_r8(reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_1D()
{
    RR_r8(reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_1E()
{
    RR_HL();
}

FORCE_INLINE void Cpu::op_CB_1F()
{
    RR_r8(reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_20()
{
    SLA_r8(reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_21()
{
    SLA_r8(reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_22()
{
    SLA_r8(reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_23()
{
    SLA_r8(reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_24()
{
    SLA_r8(reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_25()
{
    SLA_r8(reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_26()
{
    SLA_HL();
}

FORCE_INLINE void Cpu::op_CB_27()
{
    SLA_r8(reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_28()
{
    SRA_r8(reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_29()
{
    SRA_r8(reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_2A()
{
    SRA_r8(reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_2B()
{
    SRA_r8(reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_2C()
{
    SRA_r8(reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_2D()
{
    SRA_r8(reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_2E()
{
    SRA_HL();
}

FORCE_INLINE void Cpu::op_CB_2F()
{
    SRA_r8(reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_30()
{
    SWAP_r8(reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_31()
{
    SWAP_r8(reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_32()
{
    SWAP_r8(reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_33()
{
    SWAP_r8(reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_34()
{
    SWAP_r8(reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_35()
{
    SWAP_r8(reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_36()
{
    SWAP_HL();
}

FORCE_INLINE void Cpu::op_CB_37()
{
    SWAP_r8(reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_38()
{
    SRL_r8(reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_39()
{
    SRL_r8(reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_3A()
{
    SRL_r8(reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_3B()
{
    SRL_r8(reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_3C()
{
    SRL_r8(reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_3D()
{
    SRL_r8(reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_3E()
{
    SRL_HL();
}

FORCE_INLINE void Cpu::op_CB_3F()
{
    SRL_r8(reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_40()
{
    BIT_n3_r8(0, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_41()
{
    BIT_n3_r8(0, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_42()
{
    BIT_n3_r8(0, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_43()
{
    BIT_n3_r8(0, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_44()
{
    BIT_n3_r8(0, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_45()
{
    BIT_n3_r8(0, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_46()
{
    BIT_n3_HL(0);
}

FORCE_INLINE void Cpu::op_CB_47()
{
    BIT_n3_r8(0, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_48()
{
    BIT_n3_r8(1, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_49()
{
    BIT_n3_r8(1, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_4A()
{
    BIT_n3_r8(1, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_4B()
{
    BIT_n3_r8(1, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_4C()
{
    BIT_n3_r8(1, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_4D()
{
    BIT_n3_r8(1, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_4E()
{
    BIT_n3_HL(1);
}

FORCE_INLINE void Cpu::op_CB_4F()
{
    BIT_n3_r8(1, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_50()
{
    BIT_n3_r8(2, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_51()
{
    BIT_n3_r8(2, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_52()
{
    BIT_n3_r8(2, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_53()
{
    BIT_n3_r8(2, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_54()
{
    BIT_n3_r8(2, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_55()
{
    BIT_n3_r8(2, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_56()
{
    BIT_n3_HL(2);
}

FORCE_INLINE void Cpu::op_CB_57()
{
    BIT_n3_r8(2, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_58()
{
    BIT_n3_r8(3, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_59()
{
    BIT_n3_r8(3, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_5A()
{
    BIT_n3_r8(3, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_5B()
{
    BIT_n3_r8(3, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_5C()
{
    BIT_n3_r8(3, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_5D()
{
    BIT_n3_r8(3, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_5E()
{
    BIT_n3_HL(3);
}

FORCE_INLINE void Cpu::op_CB_5F()
{
    BIT_n3_r8(3, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_60()
{
    BIT_n3_r8(4, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_61()
{
    BIT_n3_r8(4, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_62()
{
    BIT_n3_r8(4, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_63()
{
    BIT_n3_r8(4, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_64()
{
    BIT_n3_r8(4, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_65()
{
    BIT_n3_r8(4, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_66()
{
    BIT_n3_HL(4);
}

FORCE_INLINE void Cpu::op_CB_67()
{
    BIT_n3_r8(4, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_68()
{
    BIT_n3_r8(5, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_69()
{
    BIT_n3_r8(5, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_6A()
{
    BIT_n3_r8(5, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_6B()
{
    BIT_n3_r8(5, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_6C()
{
    BIT_n3_r8(5, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_6D()
{
    BIT_n3_r8(5, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_6E()
{
    BIT_n3_HL(5);
}

FORCE_INLINE void Cpu::op_CB_6F()
{
    BIT_n3_r8(5, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_70()
{
    BIT_n3_r8(6, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_71()
{
    BIT_n3_r8(6, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_72()
{
    BIT_n3_r8(6, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_73()
{
    BIT_n3_r8(6, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_74()
{
    BIT_n3_r8(6, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_75()
{
    BIT_n3_r8(6, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_76()
{
    BIT_n3_HL(6);
}

FORCE_INLINE void Cpu::op_CB_77()
{
    BIT_n3_r8(6, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_78()
{
    BIT_n3_r8(7, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_79()
{
    BIT_n3_r8(7, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_7A()
{
    BIT_n3_r8(7, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_7B()
{
    BIT_n3_r8(7, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_7C()
{
    BIT_n3_r8(7, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_7D()
{
    BIT_n3_r8(7, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_7E()
{
    BIT_n3_HL(7);
}

FORCE_INLINE void Cpu::op_CB_7F()
{
    BIT_n3_r8(7, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_80()
{
    RES_n3_r8(0, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_81()
{
    RES_n3_r8(0, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_82()
{
    RES_n3_r8(0, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_83()
{
    RES_n3_r8(0, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_84()
{
    RES_n3_r8(0, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_85()
{
    RES_n3_r8(0, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_86()
{
    RES_n3_HL(0);
}

FORCE_INLINE void Cpu::op_CB_87()
{
    RES_n3_r8(0, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_88()
{
    RES_n3_r8(1, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_89()
{
    RES_n3_r8(1, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_8A()
{
    RES_n3_r8(1, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_8B()
{
    RES_n3_r8(1, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_8C()
{
    RES_n3_r8(1, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_8D()
{
    RES_n3_r8(1, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_8E()
{
    RES_n3_HL(1);
}

FORCE_INLINE void Cpu::op_CB_8F()
{
    RES_n3_r8(1, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_90()
{
    RES_n3_r8(2, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_91()
{
    RES_n3_r8(2, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_92()
{
    RES_n3_r8(2, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_93()
{
    RES_n3_r8(2, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_94()
{
    RES_n3_r8(2, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_95()
{
    RES_n3_r8(2, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_96()
{
    RES_n3_HL(2);
}

FORCE_INLINE void Cpu::op_CB_97()
{
    RES_n3_r8(2, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_98()
{
    RES_n3_r8(3, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_99()
{
    RES_n3_r8(3, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_9A()
{
    RES_n3_r8(3, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_9B()
{
    RES_n3_r8(3, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_9C()
{
    RES_n3_r8(3, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_9D()
{
    RES_n3_r8(3, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_9E()
{
    RES_n3_HL(3);
}

FORCE_INLINE void Cpu::op_CB_9F()
{
    RES_n3_r8(3, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_A0()
{
    RES_n3_r8(4, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_A1()
{
    RES_n3_r8(4, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_A2()
{
    RES_n3_r8(4, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_A3()
{
    RES_n3_r8(4, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_A4()
{
    RES_n3_r8(4, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_A5()
{
    RES_n3_r8(4, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_A6()
{
    RES_n3_HL(4);
}

FORCE_INLINE void Cpu::op_CB_A7()
{
    RES_n3_r8(4, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_A8()
{
    RES_n3_r8(5, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_A9()
{
    RES_n3_r8(5, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_AA()
{
    RES_n3_r8(5, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_AB()
{
    RES_n3_r8(5, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_AC()
{
    RES_n3_r8(5, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_AD()
{
    RES_n3_r8(5, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_AE()
{
    RES_n3_HL(5);
}

FORCE_INLINE void Cpu::op_CB_AF()
{
    RES_n3_r8(5, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_B0()
{
    RES_n3_r8(6, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_B1()
{
    RES_n3_r8(6, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_B2()
{
    RES_n3_r8(6, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_B3()
{
    RES_n3_r8(6, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_B4()
{
    RES_n3_r8(6, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_B5()
{
    RES_n3_r8(6, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_B6()
{
    RES_n3_HL(6);
}

FORCE_INLINE void Cpu::op_CB_B7()
{
    RES_n3_r8(6, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_B8()
{
    RES_n3_r8(7, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_B9()
{
    RES_n3_r8(7, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_BA()
{
    RES_n3_r8(7, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_BB()
{
    RES_n3_r8(7, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_BC()
{
    RES_n3_r8(7, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_BD()
{
    RES_n3_r8(7, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_BE()
{
    RES_n3_HL(7);
}

FORCE_INLINE void Cpu::op_CB_BF()
{
    RES_n3_r8(7, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_C0()
{
    SET_n3_r8(0, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_C1()
{
    SET_n3_r8(0, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_C2()
{
    SET_n3_r8(0, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_C3()
{
    SET_n3_r8(0, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_C4()
{
    SET_n3_r8(0, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_C5()
{
    SET_n3_r8(0, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_C6()
{
    SET_n3_HL(0);
}

FORCE_INLINE void Cpu::op_CB_C7()
{
    SET_n3_r8(0, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_C8()
{
    SET_n3_r8(1, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_C9()
{
    SET_n3_r8(1, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_CA()
{
    SET_n3_r8(1, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_CB()
{
    SET_n3_r8(1, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_CC()
{
    SET_n3_r8(1, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_CD()
{
    SET_n3_r8(1, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_CE()
{
    SET_n3_HL(1);
}

FORCE_INLINE void Cpu::op_CB_CF()
{
    SET_n3_r8(1, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_D0()
{
    SET_n3_r8(2, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_D1()
{
    SET_n3_r8(2, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_D2()
{
    SET_n3_r8(2, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_D3()
{
    SET_n3_r8(2, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_D4()
{
    SET_n3_r8(2, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_D5()
{
    SET_n3_r8(2, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_D6()
{
    SET_n3_HL(2);
}

FORCE_INLINE void Cpu::op_CB_D7()
{
    SET_n3_r8(2, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_D8()
{
    SET_n3_r8(3, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_D9()
{
    SET_n3_r8(3, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_DA()
{
    SET_n3_r8(3, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_DB()
{
    SET_n3_r8(3, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_DC()
{
    SET_n3_r8(3, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_DD()
{
    SET_n3_r8(3, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_DE()
{
    SET_n3_HL(3);
}

FORCE_INLINE void Cpu::op_CB_DF()
{
    SET_n3_r8(3, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_E0()
{
    SET_n3_r8(4, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_E1()
{
    SET_n3_r8(4, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_E2()
{
    SET_n3_r8(4, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_E3()
{
    SET_n3_r8(4, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_E4()
{
    SET_n3_r8(4, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_E5()
{
    SET_n3_r8(4, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_E6()
{
    SET_n3_HL(4);
}

FORCE_INLINE void Cpu::op_CB_E7()
{
    SET_n3_r8(4, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_E8()
{
    SET_n3_r8(5, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_E9()
{
    SET_n3_r8(5, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_EA()
{
    SET_n3_r8(5, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_EB()
{
    SET_n3_r8(5, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_EC()
{
    SET_n3_r8(5, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_ED()
{
    SET_n3_r8(5, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_EE()
{
    SET_n3_HL(5);
}

FORCE_INLINE void Cpu::op_CB_EF()
{
    SET_n3_r8(5, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_F0()
{
    SET_n3_r8(6, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_F1()
{
    SET_n3_r8(6, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_F2()
{
    SET_n3_r8(6, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_F3()
{
    SET_n3_r8(6, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_F4()
{
    SET_n3_r8(6, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_F5()
{
    SET_n3_r8(6, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_F6()
{
    SET_n3_HL(6);
}

FORCE_INLINE void Cpu::op_CB_F7()
{
    SET_n3_r8(6, reg.get_A());
}

FORCE_INLINE void Cpu::op_CB_F8()
{
    SET_n3_r8(7, reg.get_B());
}

FORCE_INLINE void Cpu::op_CB_F9()
{
    SET_n3_r8(7, reg.get_C());
}

FORCE_INLINE void Cpu::op_CB_FA()
{
    SET_n3_r8(7, reg.get_D());
}

FORCE_INLINE void Cpu::op_CB_FB()
{
    SET_n3_r8(7, reg.get_E());
}

FORCE_INLINE void Cpu::op_CB_FC()
{
    SET_n3_r8(7, reg.get_H());
}

FORCE_INLINE void Cpu::op_CB_FD()
{
    SET_n3_r8(7, reg.get_L());
}

FORCE_INLINE void Cpu::op_CB_FE()
{
    SET_n3_HL(7);
}

FORCE_INLINE void Cpu::op_CB_FF()
{
    SET_n3_r8(7, reg.get_A());
}
