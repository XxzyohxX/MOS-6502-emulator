#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "tda.h"
#include "status.h"
#include "operaciones.h"
#include "direccionamiento.h"
#include "diccionario.h"

// Instrucciones

void adc(mos6502_t *procesador, instruccion_t *instruccion){
    uint16_t aux = procesador -> a + *instruccion -> m + get_status(&procesador -> status,CARRY);
	uint16_t aux2 = procesador -> a; 	
	procesador -> a = aux;
    set_carry(&procesador -> status,aux);
    set_zero(&procesador -> status,procesador -> a);
    set_negative(&procesador -> status,procesador -> a);
    set_overflow(&procesador -> status,aux2,(*instruccion -> m),aux);
}
void and_(mos6502_t *procesador, instruccion_t *instruccion){
    procesador -> a &= *instruccion -> m;
    set_zero(&procesador -> status,procesador -> a);
    set_negative(&procesador -> status,procesador -> a);
}
void asl(mos6502_t *procesador, instruccion_t *instruccion){
    uint16_t aux =  *instruccion -> m << 1;
    *instruccion -> m = aux;
    set_carry(&procesador -> status,aux);
    set_zero(&procesador -> status,*instruccion -> m);
    set_negative(&procesador -> status,*instruccion -> m);
}
void bcc(mos6502_t *procesador, instruccion_t *instruccion){
	if(!get_status(&procesador -> status,CARRY))
		procesador -> pc += (int8_t) *instruccion -> m;
}
void bcs(mos6502_t *procesador, instruccion_t *instruccion){
	if(get_status(&procesador -> status,CARRY))
		procesador -> pc += (int8_t) *instruccion -> m;
}
void beq(mos6502_t *procesador, instruccion_t *instruccion){
	if(get_status(&procesador -> status,ZERO))
		procesador -> pc += (int8_t) *instruccion -> m;
}
void bit(mos6502_t *procesador, instruccion_t *instruccion){
    set_zero(&procesador -> status,(procesador -> a) & *instruccion -> m);
    set_status(&procesador -> status,OVERFLOW,( *instruccion -> m) & 0x40);
    set_status(&procesador -> status,NEGATIVE,(*instruccion -> m) & 0x80);
}
void bmi(mos6502_t *procesador, instruccion_t *instruccion){
	if(get_status(&procesador -> status,NEGATIVE))
		procesador -> pc += (int8_t ) *instruccion -> m;
}
void bne(mos6502_t * p, instruccion_t * i){
	if(!get_status(&p -> status,ZERO))
		p -> pc += (int8_t) *i -> m;
}
void bpl(mos6502_t * p,instruccion_t *i){
	if(!get_status(&p -> status,NEGATIVE))
		p -> pc += (int8_t) *i -> m;
}
void brk(mos6502_t *procesador, instruccion_t *instruccion){
	apilar(procesador, ((procesador -> pc) + 1 )>> 8);
	apilar(procesador, (procesador -> pc) + 1);
	apilar(procesador, (procesador -> status) | (1 << 4) | (1 << 5));
	procesador -> pc = (uint8_t)procesador -> mem[0xFFFF] << 8 | procesador -> mem[0xFFFE]  ;
	set_status(&procesador -> status,INTERRUPT_DISABLE,true); 
}
void bvc(mos6502_t *procesador, instruccion_t *instruccion){
	if(!get_status(&procesador -> status,OVERFLOW))
		procesador -> pc += (int8_t) *instruccion -> m;	
}
void bvs(mos6502_t *procesador, instruccion_t *instruccion){
	if(get_status(&procesador -> status,OVERFLOW))
		procesador -> pc += (int8_t) *instruccion -> m;		
}
void clc(mos6502_t *procesador, instruccion_t *instruccion){
    set_status(&procesador -> status,CARRY,false);
}
void cld(mos6502_t *procesador, instruccion_t *instruccion){
    set_status(&procesador -> status,DECIMAL,false);
}
void cli(mos6502_t *procesador, instruccion_t *instruccion){
    set_status(&procesador -> status,INTERRUPT_DISABLE,false);	
}
void clv(mos6502_t *procesador, instruccion_t *instruccion){
    set_status(&procesador -> status,OVERFLOW,false);
}

void compare(mos6502_t * p, instruccion_t * i, uint8_t * reg){
    set_status(&p -> status,CARRY, (*reg) >= (*i -> m));
    set_status(&p -> status,ZERO, (*reg) == (*i -> m));
    set_status(&p -> status,NEGATIVE, (*reg) < (*i -> m));
}

void cmp(mos6502_t *p, instruccion_t *i){
	compare(p, i, &(p -> a));
}
void cpx(mos6502_t *p, instruccion_t *i){
	compare(p, i, &(p -> x));
}
void cpy(mos6502_t *p, instruccion_t *i){
	compare(p, i, &(p -> y));
}

void decrementar(mos6502_t * p, uint8_t * reg){
	(*reg)--;
    set_zero(&p -> status,*reg);
    set_negative(&p -> status,*reg);
}
void incrementar(mos6502_t * p, uint8_t * reg){
	(*reg)++;
    set_zero(&p -> status,*reg);
    set_negative(&p -> status,*reg);
}
void load(mos6502_t * p,instruccion_t *i, uint8_t * reg){
	(*reg) = *i -> m ;
    set_zero(&p -> status,*reg);
    set_negative(&p -> status,*reg);
}
void dec(mos6502_t *procesador, instruccion_t *instruccion){
	decrementar(procesador,instruccion -> m);	
}
void dex(mos6502_t *procesador, instruccion_t *instruccion){
	decrementar(procesador,&procesador -> x);	
}
void dey(mos6502_t *procesador, instruccion_t *instruccion){
	decrementar(procesador,&procesador -> y);	
}
void eor(mos6502_t *procesador, instruccion_t *instruccion){
    procesador -> a  ^= *instruccion -> m;
    set_zero(&procesador -> status,procesador -> a);
    set_negative(&procesador -> status,procesador -> a);
}
void inc(mos6502_t *procesador, instruccion_t *instruccion){
	incrementar(procesador,instruccion -> m);	
}
void inx(mos6502_t *procesador, instruccion_t *instruccion){
	incrementar(procesador,&procesador -> x);	
}
void iny(mos6502_t *procesador, instruccion_t *instruccion){
	incrementar(procesador,&procesador -> y);	
}
void jmp(mos6502_t *procesador, instruccion_t *instruccion){	
    procesador -> pc =  instruccion -> direccion;
}
void jsr(mos6502_t *procesador, instruccion_t *instruccion){
	apilar(procesador,((procesador -> pc) - 1 )>> 8 );
	apilar(procesador,(procesador -> pc) - 1 );
    procesador -> pc = instruccion -> direccion;
}
void lda(mos6502_t *procesador, instruccion_t *instruccion){
	load(procesador,instruccion,&procesador -> a);	
}
void ldx(mos6502_t *procesador, instruccion_t *instruccion){
	load(procesador,instruccion,&procesador -> x);	
}
void ldy(mos6502_t *procesador, instruccion_t *instruccion){
	load(procesador,instruccion,&procesador -> y);	
}
void lsr(mos6502_t *procesador, instruccion_t *instruccion){
    bool carry =  *instruccion -> m & 1;
    uint16_t aux =  *instruccion -> m >> 1;
    *instruccion -> m = aux;
    set_status(&procesador -> status,CARRY,carry);
    set_zero(&procesador -> status,*instruccion -> m);
    set_negative(&procesador -> status,*instruccion -> m);
}
void nop(mos6502_t *procesador, instruccion_t *instruccion){
}
void ora(mos6502_t *procesador, instruccion_t *instruccion){	
    procesador -> a |= *instruccion -> m;
    set_zero(&procesador -> status,procesador -> a);
    set_negative(&procesador -> status,procesador -> a);
}
void pha(mos6502_t *procesador, instruccion_t *instruccion){
	apilar(procesador, procesador -> a);
}
void php(mos6502_t *procesador, instruccion_t *instruccion){ 
	apilar(procesador, (procesador -> status) | (1 << 4) | (1 << 5));
}
void pla(mos6502_t *procesador, instruccion_t *instruccion){
	procesador -> a = desapilar(procesador);
    set_zero(&procesador -> status,procesador -> a);
    set_negative(&procesador -> status,procesador -> a);
}
void plp(mos6502_t *procesador, instruccion_t *instruccion){ 
	procesador -> status = (desapilar(procesador) & 0xcf) | ((procesador -> status) & ~0xcf);
}
void rol(mos6502_t *procesador, instruccion_t *instruccion){
    bool carry =  *instruccion -> m & 0x80;
	rotate_left(&procesador -> status, instruccion -> m);
    set_status(&procesador -> status,CARRY,carry);	
    set_zero(&procesador -> status,*instruccion -> m);
    set_negative(&procesador -> status,*instruccion -> m);
}
void ror(mos6502_t *procesador, instruccion_t *instruccion){
    bool carry =  *instruccion -> m & 1;
	rotate_right(&procesador -> status, instruccion -> m);
    set_status(&procesador -> status,CARRY,carry);	
    set_zero(&procesador -> status,*instruccion -> m);
    set_negative(&procesador -> status,*instruccion -> m);
}
void rti(mos6502_t *procesador, instruccion_t *instruccion){ 
	procesador -> status = (desapilar(procesador) & 0xcf) | ((procesador -> status) & ~0xcf);
	procesador -> pc  = desapilar(procesador)| desapilar(procesador)<< 8; 
}
void rts(mos6502_t *procesador, instruccion_t *instruccion){ 
	uint8_t byte2 =  desapilar(procesador);
	uint8_t byte1 =  desapilar(procesador);
	uint16_t byte =  byte1<<8 | byte2;
	byte += 1 ;
	procesador -> pc = byte;
}
void sbc(mos6502_t *procesador, instruccion_t *instruccion){
    uint16_t aux = procesador -> a + (~ *instruccion -> m) + get_status(&procesador -> status,CARRY);
	uint16_t aux2 = procesador -> a; 	
	procesador -> a = aux;
    set_carry(&procesador -> status,~aux);
    set_zero(&procesador -> status,procesador -> a);
    set_negative(&procesador -> status,procesador -> a);
    set_overflow(&procesador -> status,aux2,~(*instruccion -> m),aux);
}
void sec(mos6502_t *procesador, instruccion_t *instruccion){
    set_status(&procesador -> status,CARRY,true);
}
void sed(mos6502_t *procesador, instruccion_t *instruccion){
    set_status(&procesador -> status,DECIMAL,true);
}
void sei(mos6502_t *procesador, instruccion_t *instruccion){
    set_status(&procesador -> status,INTERRUPT_DISABLE,true);
}
void sta(mos6502_t *procesador, instruccion_t *instruccion){
    *instruccion -> m = procesador -> a;
}
void stx(mos6502_t *procesador, instruccion_t *instruccion){
    *instruccion -> m = procesador -> x;
}
void sty(mos6502_t *procesador, instruccion_t *instruccion){
    *instruccion -> m = procesador -> y;
}
void transfer(mos6502_t * p,instruccion_t *i, uint8_t * reg){
	(*reg) = p -> a ;
    set_zero(&p -> status,*reg);
    set_negative(&p -> status,*reg);
}
void transfer_a(mos6502_t * p,instruccion_t *i, uint8_t * reg){
	p -> a = (*reg);
    set_zero(&p -> status,p -> a);
    set_negative(&p -> status,p -> a);
}
void tax(mos6502_t *procesador, instruccion_t *instruccion){  
	transfer(procesador,instruccion, &procesador -> x);
}
void tay(mos6502_t *procesador, instruccion_t *instruccion){ 
	transfer(procesador,instruccion, &procesador -> y);
}
void tsx(mos6502_t *procesador, instruccion_t *instruccion){ 
	procesador -> x = procesador -> sp;
    set_zero(&procesador -> status,procesador -> x);
    set_negative(&procesador -> status,procesador -> x);
}
void txa(mos6502_t *procesador, instruccion_t *instruccion){
	transfer_a(procesador,instruccion, &procesador -> x);
}
void txs(mos6502_t *procesador, instruccion_t *instruccion){
    procesador -> sp = procesador -> x;
}
void tya(mos6502_t *procesador, instruccion_t *instruccion){
	transfer_a(procesador,instruccion, &procesador -> y);
}
