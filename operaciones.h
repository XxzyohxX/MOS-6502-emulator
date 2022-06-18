#ifndef _OPERACIONES_H_
#define _OPERACIONES_H_

typedef struct {
    uint8_t codigo;     // Opcode.
    short ciclos;       // Cantidad de ciclos de la instrucción.
    uint8_t *m;         // Puntero al operando (registro o memoria).
    uint16_t direccion; // Dirección del operando (si corresponde).
} instruccion_t;

// Instrucciones

void adc(mos6502_t *procesador, instruccion_t *instruccion);
void and_(mos6502_t *procesador, instruccion_t *instruccion);
void asl(mos6502_t *procesador, instruccion_t *instruccion);
void bcc(mos6502_t *procesador, instruccion_t *instruccion);
void bcs(mos6502_t *procesador, instruccion_t *instruccion);
void beq(mos6502_t *procesador, instruccion_t *instruccion);
void bit(mos6502_t *procesador, instruccion_t *instruccion);
void bmi(mos6502_t *procesador, instruccion_t *instruccion);
void bne(mos6502_t *procesador, instruccion_t *instruccion);
void bpl(mos6502_t *procesador, instruccion_t *instruccion);
void brk(mos6502_t *procesador, instruccion_t *instruccion);
void bvc(mos6502_t *procesador, instruccion_t *instruccion);
void bvs(mos6502_t *procesador, instruccion_t *instruccion);
void clc(mos6502_t *procesador, instruccion_t *instruccion);
void cld(mos6502_t *procesador, instruccion_t *instruccion);
void cli(mos6502_t *procesador, instruccion_t *instruccion);
void clv(mos6502_t *procesador, instruccion_t *instruccion);
void cmp(mos6502_t *procesador, instruccion_t *instruccion);
void cpx(mos6502_t *procesador, instruccion_t *instruccion);
void cpy(mos6502_t *procesador, instruccion_t *instruccion);
void dec(mos6502_t *procesador, instruccion_t *instruccion);
void dex(mos6502_t *procesador, instruccion_t *instruccion);
void dey(mos6502_t *procesador, instruccion_t *instruccion);
void eor(mos6502_t *procesador, instruccion_t *instruccion);
void inc(mos6502_t *procesador, instruccion_t *instruccion);
void inx(mos6502_t *procesador, instruccion_t *instruccion);
void iny(mos6502_t *procesador, instruccion_t *instruccion);
void jmp(mos6502_t *procesador, instruccion_t *instruccion);
void jsr(mos6502_t *procesador, instruccion_t *instruccion);
void lda(mos6502_t *procesador, instruccion_t *instruccion);
void ldx(mos6502_t *procesador, instruccion_t *instruccion);
void ldy(mos6502_t *procesador, instruccion_t *instruccion);
void lsr(mos6502_t *procesador, instruccion_t *instruccion);
void nop(mos6502_t *procesador, instruccion_t *instruccion);
void ora(mos6502_t *procesador, instruccion_t *instruccion);
void pha(mos6502_t *procesador, instruccion_t *instruccion);
void php(mos6502_t *procesador, instruccion_t *instruccion);
void pla(mos6502_t *procesador, instruccion_t *instruccion);
void plp(mos6502_t *procesador, instruccion_t *instruccion);
void rol(mos6502_t *procesador, instruccion_t *instruccion);
void ror(mos6502_t *procesador, instruccion_t *instruccion);
void rti(mos6502_t *procesador, instruccion_t *instruccion);
void rts(mos6502_t *procesador, instruccion_t *instruccion);
void sbc(mos6502_t *procesador, instruccion_t *instruccion);
void sec(mos6502_t *procesador, instruccion_t *instruccion);
void sed(mos6502_t *procesador, instruccion_t *instruccion);
void sei(mos6502_t *procesador, instruccion_t *instruccion);
void sta(mos6502_t *procesador, instruccion_t *instruccion);
void stx(mos6502_t *procesador, instruccion_t *instruccion);
void sty(mos6502_t *procesador, instruccion_t *instruccion);
void tax(mos6502_t *procesador, instruccion_t *instruccion);
void tay(mos6502_t *procesador, instruccion_t *instruccion);
void tsx(mos6502_t *procesador, instruccion_t *instruccion);
void txa(mos6502_t *procesador, instruccion_t *instruccion);
void txs(mos6502_t *procesador, instruccion_t *instruccion);
void tya(mos6502_t *procesador, instruccion_t *instruccion);

//Funciones auxiliares

void decrementar(mos6502_t * p, uint8_t * reg);
void incrementar(mos6502_t * p, uint8_t * reg);
void load(mos6502_t * p,instruccion_t *i,uint8_t * reg);
void transfer(mos6502_t * p,instruccion_t *i, uint8_t * reg);
void transfer_a(mos6502_t * p,instruccion_t *i, uint8_t * reg);
void compare(mos6502_t * p, instruccion_t * i, uint8_t * reg);

#endif
