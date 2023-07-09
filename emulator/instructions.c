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