#include "cpu.hh"

/* ADC */

void GBMachine::CPU::ADC_A_HL()
{
    ADC_A_n8(mem[HL]);
}

void GBMachine::CPU::ADC_A_n8(uint8_t n8)
{
    uint16_t result = A + n8 + C_flag_get();
    C_flag_update(result > 0xFF);
    H_flag_update((A & 0x0F) + (n8 & 0x0F) + C_flag_get() > 0x0F);
    N_flag_reset();
    Z_flag_update(result == 0);
    A = static_cast<uint8_t>(result);
}

void GBMachine::CPU::ADC_A_r8(uint8_t& r8)
{
    ADC_A_n8(r8);
}

/* ADD */

void GBMachine::CPU::ADD_A_HL()
{
    ADD_A_n8(mem[HL]);
}

void GBMachine::CPU::ADD_A_n8(uint8_t n8)
{
    uint16_t result = A + n8;
    C_flag_update(result > 0xFF);
    H_flag_update((A & 0x0F) + (n8 & 0x0F) > 0x0F);
    N_flag_reset();
    Z_flag_update(result == 0);
    A = static_cast<uint8_t>(result);
}

void GBMachine::CPU::ADD_A_r8(uint8_t& r8)
{
    ADD_A_n8(r8);
}

void GBMachine::CPU::ADD_HL_r16(uint16_t& r16)
{
    uint32_t result = HL + r16;
    C_flag_update(result > 0xFFFF);
    H_flag_update(((HL >> 8) & 0x0F) + ((r16 >> 8) & 0x0F) > 0x0F);
    N_flag_reset();
    HL = static_cast<uint16_t>(result);
}

void GBMachine::CPU::ADD_SP_e8(int8_t e8)
{
    uint32_t result = static_cast<uint32_t>(SP) + e8;
    C_flag_update(result > 0xFFFF);
    H_flag_update(((SP & 0x000F) + (static_cast<uint8_t>(e8 & 0x0F))) > 0x0F);
    N_flag_reset();
    Z_flag_reset();
    SP = static_cast<uint16_t>(result);
}

/* AND */

void GBMachine::CPU::AND_n8(uint8_t n8)
{
    A &= n8;
    C_flag_reset();
    H_flag_set();
    N_flag_reset();
    Z_flag_update(A == 0);
}

void GBMachine::CPU::AND_HL()
{
    AND_n8(mem[HL]);
}

void GBMachine::CPU::AND_r8(uint8_t& r8)
{
    AND_n8(r8);
}

/* BIT */
void GBMachine::CPU::BIT_n3_HL(uint8_t n3)
{
    BIT_n3_r8(n3, mem[HL]);
}

void GBMachine::CPU::BIT_n3_r8(uint8_t n3, uint8_t& r8)
{
    H_flag_set();
    N_flag_reset();
    Z_flag_update(!((r8 >> n3) & 0x01));
}

/* CALL */

void GBMachine::CPU::CALL_n16(uint16_t n16)
{
    PUSH_r16(PC);
    PC = n16;
}

void GBMachine::CPU::CALL_cc_n16(bool cc, uint16_t n16)
{
    if (cc)
    {
        CALL_n16(n16);
        branch_taken = true;
    }
    else branch_taken = false;
}

/* CCF */

void GBMachine::CPU::CCF()
{
    C_flag_update(!C_flag_get());
    H_flag_reset();
    N_flag_reset();
}

/* CP */

void GBMachine::CPU::CP_HL()
{
    CP_n8(mem[HL]);
}

void GBMachine::CPU::CP_n8(uint8_t n8)
{
    C_flag_update(A < n8);
    H_flag_update((A & 0x0F) < (n8 & 0x0F));
    N_flag_set();
    Z_flag_update(A == n8);
}

void GBMachine::CPU::CP_r8(uint8_t& r8)
{
    CP_n8(r8);
}

/* CPL */

void GBMachine::CPU::CPL()
{
    A = ~(A);
}

/* DAA */

void GBMachine::CPU::DAA()
{
    if (!N_flag_get())
    {
        if (C_flag_get() || A > 0x99)
        {
            A += 0x60;
            C_flag_set();
        }
        if (H_flag_get() || (A & 0x0F) < 0x09)
        {
            A += 0x06;
        }
    }
    else
    {
        if (C_flag_get()) A -= 0x60;
        if (H_flag_get()) A -= 0x06;
    }

    H_flag_reset();
    Z_flag_update(A == 0);
}

/* DEC */

void GBMachine::CPU::DEC_HL()
{
    DEC_r8(mem[HL]);
}

void GBMachine::CPU::DEC_r16(uint16_t& r16)
{
    --(r16);
}

void GBMachine::CPU::DEC_r8(uint8_t& r8)
{
    --(r8);
    H_flag_update((r8 & 0x0F) == 0x0F);
    N_flag_set();
    Z_flag_update(r8 == 0);
}

/* DI */

void GBMachine::CPU::DI()
{
    if (DI_status == IMEStatus::DO_NOTHING)
        DI_status = IMEStatus::RESET_NEXT_CYCLE;
}

/* EI */
void GBMachine::CPU::EI()
{
    if (EI_status == IMEStatus::DO_NOTHING)
        EI_status = IMEStatus::SET_NEXT_CYCLE;
}

/* HALT */

void GBMachine::CPU::HALT()
{
    is_halted = true;
}

/* INC */

void GBMachine::CPU::INC_HL()
{
    INC_r8(mem[HL]);
}

void GBMachine::CPU::INC_r16(uint16_t& r16)
{
    ++(r16);
}

void GBMachine::CPU::INC_r8(uint8_t& r8)
{
    uint16_t result = r8 + 1;
    H_flag_update((r8 & 0x0F) + 1 > 0x0F);
    N_flag_reset();
    Z_flag_update(result == 0);
    r8 = static_cast<uint8_t>(result);
}

/* JP */

void GBMachine::CPU::JP_HL()
{
    JP_n16(HL);
}

void GBMachine::CPU::JP_cc_n16(bool cc, uint16_t n16)
{
    if (cc)
    {
        JP_n16(n16);
        branch_taken = true;
    }
    else branch_taken = false;
}

void GBMachine::CPU::JP_n16(uint16_t n16)
{
    PC = n16;
}

/* JR */

void GBMachine::CPU::JR_cc_n8(bool cc, int8_t n8)
{
    if (cc)
    {
        JR_n8(n8);
        branch_taken = true;
    }
    else branch_taken = false;
}

void GBMachine::CPU::JR_n8(int8_t n8)
{
    PC += n8;
}

/* LD */

void GBMachine::CPU::LD_C_A()
{
    mem[0xFF00 + C] = A;
}

void GBMachine::CPU::LD_HL_n8(uint8_t n8)
{
    mem[HL] = n8;
}

void GBMachine::CPU::LD_HL_r8(uint8_t& r8)
{
    LD_HL_n8(r8);
}

void GBMachine::CPU::LD_n16_A(uint16_t n16)
{
    mem[n16] = A;
}

void GBMachine::CPU::LD_n16_SP(uint16_t n16)
{
    // TODO: Check if both bytes of SP should be written.
    mem[n16] = static_cast<uint8_t>(SP);
}

void GBMachine::CPU::LD_r16_A(uint16_t& r16)
{
    LD_n16_A(r16);
}

void GBMachine::CPU::LD_A_C()
{
    A = mem[0xFF00 + C];
}

void GBMachine::CPU::LD_A_n16(uint16_t n16)
{
    A = mem[n16];
}

void GBMachine::CPU::LD_A_r16(uint16_t& r16)
{
    LD_A_n16(r16);
}

void GBMachine::CPU::LD_HL_SP_e8(int8_t e8)
{
    uint32_t result =static_cast<uint32_t>(SP) + e8;
    C_flag_update(result > 0xFFFF);
    H_flag_update((SP & 0x000F) + static_cast<uint16_t>(e8 & 0x0F) > 0x0F);
    N_flag_reset();
    Z_flag_reset();
    HL = static_cast<uint16_t>(result);
}

void GBMachine::CPU::LD_r16_n16(uint16_t& r16, uint16_t n16)
{
    r16 = n16;
}

void GBMachine::CPU::LD_r8_HL(uint8_t& r8)
{
    r8 = mem[HL];
}

void GBMachine::CPU::LD_r8_n8(uint8_t& r8, uint8_t n8)
{
    r8 = n8;
}

void GBMachine::CPU::LD_r8_r8(uint8_t& r8_1, uint8_t& r8_2)
{
    r8_1 = r8_2;
}

void GBMachine::CPU::LD_SP_HL()
{
    SP = HL;
}

void GBMachine::CPU::LDD_HL_A()
{
    mem[HL] = A;
    --(HL);
}

void GBMachine::CPU::LDD_A_HL()
{
    A = mem[HL];
    --(HL);
}

void GBMachine::CPU::LDH_n8_A(uint8_t n8)
{
    mem[0xFF00 + n8] = A;
}

void GBMachine::CPU::LDH_A_n8(uint8_t n8)
{
    A = mem[0xFF00 + n8];
}

void GBMachine::CPU::LDI_HL_A()
{
    mem[HL] = A;
    ++(HL);
}

void GBMachine::CPU::LDI_A_HL()
{
    A = mem[HL];
    ++(HL);
}

/* NOP */

void GBMachine::CPU::NOP()
{

}

/* OR */

void GBMachine::CPU::OR_HL()
{
    OR_n8(mem[HL]);
}

void GBMachine::CPU::OR_n8(uint8_t n8)
{
    A |= n8;
    C_flag_reset();
    H_flag_reset();
    N_flag_reset();
    Z_flag_update(A == 0);
}

void GBMachine::CPU::OR_r8(uint8_t& r8)
{
    OR_n8(r8);
}

/* POP */

void GBMachine::CPU::POP_r16(uint16_t& r16)
{
    ++(SP);
    r16 |= mem[SP];
    ++(SP);
    r16 |= mem[SP] << 8;
}

/* PUSH */

void GBMachine::CPU::PUSH_r16(uint16_t& r16)
{
    mem[SP] = static_cast<uint8_t>(r16);
    --(SP);
    mem[SP] = static_cast<uint8_t>(r16 >> 8);
    --(SP);
}

/* RES */

void GBMachine::CPU::RES_n3_HL(uint8_t n3)
{
    RES_n3_r8(n3, mem[HL]);
}

void GBMachine::CPU::RES_n3_r8(uint8_t n3, uint8_t& r8)
{
    r8 &= ~(0x01 << n3);
}

/* RET */

void GBMachine::CPU::RET()
{
    ++(SP);
    PC |= mem[SP];
    ++(SP);
    PC |= mem[SP] << 8;
}

void GBMachine::CPU::RET_cc(bool cc)
{
    if (cc)
    {
        RET();
        branch_taken = true;
    }
    else branch_taken = false;
}

/* RETI */

void GBMachine::CPU::RETI()
{
    RET();
    if (is_interrupted)
    {
        is_interrupted = false;
        curr_interrupt = nullptr;
    }
    enable_interrupts_now();
}

void GBMachine::CPU::RL_HL()
{
    RL_r8(mem[HL]);
}

void GBMachine::CPU::RL_r8(uint8_t& r8)
{
    uint8_t result = r8;
    uint8_t msbit = (result >> 7) & 0x01;
    result <<= 1;
    result |= C_flag_get();
    C_flag_update(msbit != 0);
    H_flag_reset();
    N_flag_reset();
    C_flag_update(result == 0);
    r8 = result;
}

/* RLA */

void GBMachine::CPU::RLA()
{
    RL_r8(A);
}

/* RLC */

void GBMachine::CPU::RLC_HL()
{
    RLC_r8(mem[HL]);
}

void GBMachine::CPU::RLC_r8(uint8_t& r8)
{
    uint8_t result = r8;
    uint8_t msbit = (result >> 7) & 0x01;
    result <<= 1;
    result |= msbit;
    C_flag_update(msbit != 0);
    H_flag_reset();
    N_flag_reset();
    C_flag_update(result == 0);
    r8 = result;
}

/* RLCA */

void GBMachine::CPU::RLCA()
{
    RLC_r8(A);
}

/* RR */

void GBMachine::CPU::RR_HL()
{
    RR_r8(mem[HL]);
}

void GBMachine::CPU::RR_r8(uint8_t& r8)
{
    uint8_t result = r8;
    uint8_t lsbit = result & 0x01;
    result >>= 1;
    result |= (C_flag_get() << 7);
    C_flag_update(lsbit != 0);
    H_flag_reset();
    N_flag_reset();
    C_flag_update(result == 0);
    r8 = result;
}

/* RRA */

void GBMachine::CPU::RRA()
{
    RR_r8(A);
}

/* RRC */

void GBMachine::CPU::RRC_HL()
{
    RRC_r8(mem[HL]);
}

void GBMachine::CPU::RRC_r8(uint8_t& r8)
{
    uint8_t result = r8;
    uint8_t lsbit = result & 0x01;
    result >>= 1;
    result |= (lsbit << 7);
    C_flag_update(lsbit != 0);
    H_flag_reset();
    N_flag_reset();
    C_flag_update(result == 0);
    r8 = result;
}

/* RRCA */

void GBMachine::CPU::RRCA()
{
    RRC_r8(A);
}

void GBMachine::CPU::RST_f(uint8_t f)
{
    PUSH_r16(PC);
    PC = 0x0000 + f;
}

/* SBC */

void GBMachine::CPU::SBC_A_HL()
{
    SBC_A_n8(mem[HL]);
}

void GBMachine::CPU::SBC_A_n8(uint8_t n8)
{
    uint16_t result = A - n8 - C_flag_get();
    H_flag_update((A & 0x0F) - (n8 & 0x0F) - C_flag_get() > 0x0F);
    C_flag_update(result > 0xFF);
    N_flag_set();
    Z_flag_update(result == 0);
    A = static_cast<uint8_t>(result);
}

void GBMachine::CPU::SBC_A_r8(uint8_t& r8)
{
    SBC_A_n8(r8);
}

void GBMachine::CPU::SUB_A_HL()
{
    SUB_A_n8(mem[HL]);
}

/* SCF */

void GBMachine::CPU::SCF()
{
    C_flag_set();
    H_flag_reset();
    N_flag_reset();
}

/* SET */

void GBMachine::CPU::SET_n3_HL(uint8_t n3)
{
    SET_n3_r8(n3, mem[HL]);
}

void GBMachine::CPU::SET_n3_r8(uint8_t n3, uint8_t& r8)
{
    r8 |= 0x01 << n3;
}

/* SLA */

void GBMachine::CPU::SLA_HL()
{
    SLA_r8(mem[HL]);
}

void GBMachine::CPU::SLA_r8(uint8_t& r8)
{
    uint8_t result = r8;
    result <<= 1;
    result &= ~(0x01);
    C_flag_update(((r8 >> 7) & 0x01) != 0);
    H_flag_reset();
    N_flag_reset();
    Z_flag_update(result == 0);
    r8 = result;
}

/* SRA */

void GBMachine::CPU::SRA_HL()
{
    SRA_r8(mem[HL]);
}

void GBMachine::CPU::SRA_r8(uint8_t& r8)
{
    uint8_t result = r8;
    uint8_t msb = r8 & (0x01 << 7);
    result >>= 1;
    result |= msb;
    C_flag_update(r8 & 0x01);
    H_flag_reset();
    N_flag_reset();
    Z_flag_update(result == 0);
    r8 = result;
}

/* SRL */

void GBMachine::CPU::SRL_HL()
{
    SRL_r8(mem[HL]);
}

void GBMachine::CPU::SRL_r8(uint8_t& r8)
{
    uint8_t result = r8;
    result >>= 1;
    result &= ~(0x01 << 7);
    C_flag_update(r8 & 0x01);
    H_flag_reset();
    N_flag_reset();
    Z_flag_update(result == 0);
    r8 = result;
}

/* STOP */

void GBMachine::CPU::STOP()
{
    is_stopped = true;
    // TODO: Turn off display
}

/* SUB */

void GBMachine::CPU::SUB_A_n8(uint8_t n8)
{
    uint16_t result = A - n8;
    C_flag_update(result > 0xFF);
    H_flag_update((A & 0x0F) - (n8 & 0x0F) > 0x0F);
    N_flag_set();
    Z_flag_update(result == 0);
    A = static_cast<uint8_t>(result);
}

void GBMachine::CPU::SUB_A_r8(uint8_t& r8)
{
    SUB_A_n8(r8);
}

/* SWAP */

void GBMachine::CPU::SWAP_HL()
{
    SWAP_r8(mem[HL]);
}

void GBMachine::CPU::SWAP_r8(uint8_t& r8)
{
    r8 = static_cast<uint8_t>(((r8 & 0x0F) << 4) | ((r8 & 0xF0) >> 4));
    C_flag_reset();
    H_flag_reset();
    N_flag_reset();
    Z_flag_update(r8 == 0);
}

/* XOR */

void GBMachine::CPU::XOR_HL()
{
    XOR_n8(mem[HL]);
}

void GBMachine::CPU::XOR_n8(uint8_t n8)
{
    A ^= n8;
    C_flag_reset();
    H_flag_reset();
    N_flag_reset();
    Z_flag_update(A == 0);
}

void GBMachine::CPU::XOR_r8(uint8_t& r8)
{
    XOR_n8(r8);
}
