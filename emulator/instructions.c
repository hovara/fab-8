#include "instructions.h"

#include "cpu.h"

void addrm_imm(void)
{
	location = PC++;
}

void addrm_dir(void)
{
	location = addrcat(DS, readcurr());
}

void addrm_dirx(void)
{
	location = addrcat(DS, readcurr()) + X;
}

void addrm_diry(void)
{
	location = addrcat(DS, readcurr()) + Y;
}

void addrm_prei(void)
{
	location = addrcat(ES, memory[addrcat(DS, readcurr()) + X]);
}

void addrm_posi(void)
{
	location = addrcat(ES, memory[addrcat(DS, readcurr())]) + Y;
}

void addrm_abs(void)
{
	location = addrcat(readcurr(), readcurr());
}

void addrm_absx(void)
{
	location = addrcat(readcurr(), readcurr()) + X;
}

void addrm_absy(void)
{
	location = addrcat(readcurr(), readcurr()) + Y;
}

void lda(void)
{
	A = fetched; update_flagsZS(A);
}

void ldx(void)
{
	X = fetched; update_flagsZS(X);
}

void ldy(void)
{
	Y = fetched; update_flagsZS(Y);
}

void sta(void) {memory[location] = A;}
void stx(void) {memory[location] = X;}
void sty(void) {memory[location] = Y;}


void tax(void)
{
	A = X; update_flagsZS(A);
}

void tay(void)
{
	A = Y; update_flagsZS(A);
}

void txa(void)
{
	X = A; update_flagsZS(X);
}

void txy(void)
{
	X = Y; update_flagsZS(X);
}

void txsp(void)
{
	X = SP; update_flagsZS(X);
}

void txss(void)
{
	X = SS; update_flagsZS(X);
}

void tya(void)
{
	Y = A; update_flagsZS(Y);
}

void tyx(void)
{
	Y = X; update_flagsZS(Y);
}

void tyds(void)
{
	Y = DS; update_flagsZS(Y);
}

void tyes(void)
{
	Y = ES; update_flagsZS(Y);
}

void tspx(void)
{
	SP = X; update_flagsZS(SP);
}

void tssx(void)
{
	SS = X; update_flagsZS(SS);
}

void tdsy(void)
{
	DS = Y; update_flagsZS(DS);
}

void tesy(void)
{
	ES = Y; update_flagsZS(ES);
}

void ina(void)
{
	A++; update_flagsZS(A);
}

void inx(void)
{
	X++; update_flagsZS(X);
}

void iny(void)
{
	Y++; update_flagsZS(Y);
}

void inc(void)
{
	memory[location]++; update_flagsZS(memory[location]);
}

void dea(void)
{
	A--; update_flagsZS(A);
}

void dex(void)
{
	X--; update_flagsZS(X);
}

void dey(void)
{
	Y--; update_flagsZS(Y);
}

void dec(void)
{
	memory[location]--; update_flagsZS(memory[location]);
}

void adc(void)
{
	temp = A + fetched + get_flag(CARRY);
	set_flag(CARRY, temp > 255);

	if(sign(A) && sign(fetched) && !sign(temp)) set_flag(OVERFLOW, 1);
	else if(!sign(A) && !sign(fetched) && sign(temp)) set_flag(OVERFLOW, 1);
	else set_flag(OVERFLOW, 0);

	A = temp;
	update_flagsZS(A);
}

void sbb(void)
{ 
	temp = A - fetched - get_flag(CARRY);
	set_flag(CARRY, temp > 255);

	if(sign(A) && !sign(fetched) && !sign(temp)) set_flag(OVERFLOW, 1);
	else if(!sign(A) && sign(fetched) && sign(temp)) set_flag(OVERFLOW, 1);
	else set_flag(OVERFLOW, 0);

	A = temp;
	update_flagsZS(A);
}

void mul(void)
{
	temp = A * fetched;
	A = temp;

	set_flag(CARRY, temp > 255);
	update_flagsZS(A);
}

void div(void)
{
	A /= fetched; update_flagsZS(A);
}

void mod(void)
{
	A %= fetched; update_flagsZS(A);
}

void and(void)
{
	A &= fetched; update_flagsZS(A);
}

void or(void)
{
	A |= fetched; update_flagsZS(A);
}

void xor(void)
{
	A ^= fetched; update_flagsZS(A);
}

void shla(void)
{
	set_flag(CARRY, sign(A));
	A <<= 1; update_flagsZS(A);
}

void shl(void)
{
	set_flag(CARRY, sign(memory[location]));
	memory[location] <<= 1; update_flagsZS(memory[location]);
}

void shra(void)
{
	set_flag(CARRY, A & 0b00000001);
	A >>= 1; update_flagsZS(A);
}

void shr(void)
{
	set_flag(CARRY, memory[location] & 0b00000001);
	memory[location] >>= 1; update_flagsZS(memory[location]);
}

void rola(void)
{
	temp = sign(A);
	A <<= 1;
	A |= get_flag(CARRY);
	set_flag(CARRY, temp);
	update_flagsZS(A);
}

void rol(void)
{
	temp = sign(memory[location]);
	memory[location] <<= 1;
	memory[location] |= get_flag(CARRY);
	set_flag(CARRY, temp);
	update_flagsZS(memory[location]);
}

void rora(void)
{
	temp = A & 0b00000001;
	A >>= 1;
	A |= get_flag(CARRY) << 7;
	set_flag(CARRY, temp);
	update_flagsZS(A);
}

void rorr(void)
{
	temp = memory[location] & 0b00000001;
	memory[location] >>= 1;
	memory[location] |= get_flag(CARRY) << 7;
	set_flag(CARRY, temp);
	update_flagsZS(memory[location]);
}

void cmp(void)
{
	temp = A - fetched;
	set_flag(CARRY, temp > 255);

	if(sign(A) && !sign(fetched) && !sign(temp)) set_flag(OVERFLOW, 1);
	else if(!sign(A) && sign(fetched) && sign(temp)) set_flag(OVERFLOW, 1);
	else set_flag(OVERFLOW, 0);

	update_flagsZS(temp);
}

void cpx(void)
{
	temp = X - fetched;
	set_flag(CARRY, temp > 255);

	if(sign(X) && !sign(fetched) && !sign(temp)) set_flag(OVERFLOW, 1);
	else if(!sign(X) && sign(fetched) && sign(temp)) set_flag(OVERFLOW, 1);
	else set_flag(OVERFLOW, 0);

	update_flagsZS(temp);
}

void cpy(void)
{
	temp = Y - fetched;
	set_flag(CARRY, temp > 255);

	if(sign(Y) && !sign(fetched) && !sign(temp)) set_flag(OVERFLOW, 1);
	else if(!sign(Y) && sign(fetched) && sign(temp)) set_flag(OVERFLOW, 1);
	else set_flag(OVERFLOW, 0);

	update_flagsZS(temp);
}

void jmp(void) {PC = location;}

void jc(void)
{
	if(get_flag(CARRY)) PC = location;
}

void jnc(void)
{
	if(!get_flag(CARRY)) PC = location;
}

void je(void)
{
	if(get_flag(ZERO)) PC = location;
}

void jne(void)
{
	if(!get_flag(ZERO)) PC = location;
}

void js(void)
{
	if(get_flag(SIGN)) PC = location;
}

void jns(void)
{
	if(!get_flag(SIGN)) PC = location;
}

void jo(void)
{
	if(get_flag(OVERFLOW)) PC = location;
}

void jno(void)
{
	if(!get_flag(OVERFLOW)) PC = location;
}

void ja(void)
{
	if(!get_flag(CARRY) && !get_flag(ZERO)) PC = location;
}

void jna(void)
{
	if(get_flag(CARRY) || get_flag(ZERO)) PC = location;
}

void jl(void)
{
	if(get_flag(SIGN) != get_flag(OVERFLOW)) PC = location;
}

void jge(void)
{
	if(get_flag(SIGN) == get_flag(OVERFLOW)) PC = location;
}

void jg(void)
{
	if(!get_flag(ZERO) && get_flag(SIGN) == get_flag(OVERFLOW)) PC = location;
}

void jng(void)
{
	if(get_flag(ZERO) || get_flag(SIGN) != get_flag(OVERFLOW)) PC = location;
}

void loop(void)
{
	if(Y)
	{
		Y--;
		PC = location;
	}
}

void call(void)
{
	memory[addrcat(SS, SP--)] = PC >> 8;
	memory[addrcat(SS, SP--)] = PC;
	PC = location;
}
