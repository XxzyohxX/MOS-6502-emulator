#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "tda.h"
#include "status.h"
#include "operaciones.h"
#include "diccionario.h"
#include "direccionamiento.h"

opcode_t opcodes[] = {
		     [0x69] = {adc,inmediato,2},
		     [0x6D] = {adc,absoluto,4},
		     [0x65] = {adc,pagina_cero,2},
		     [0x75] = {adc,pagina_cero_X,4},
			 [0x7D] = {adc,absoluto_X,4},
		     [0x79] = {adc,absoluto_Y,4},
			 [0x61] = {adc,indirecto_indexado_X,6},
		     [0x71] = {adc,indirecto_indexado_Y,5},
		     [0x29] = {and_,inmediato,2},
		     [0x2D] = {and_,absoluto,4},
		     [0x25] = {and_,pagina_cero,2},
		     [0x35] = {and_,pagina_cero_X,4},
			 [0x3D] = {and_,absoluto_X,4},
		     [0x39] = {and_,absoluto_Y,4},
			 [0x21] = {and_,indirecto_indexado_X,6},
		     [0x31] = {and_,indirecto_indexado_Y,5},
		     [0x0A] = {asl,acumulador,2},
		     [0x0E] = {asl,absoluto,6},
		     [0x06] = {asl,pagina_cero,5},
		     [0x16] = {asl,pagina_cero_X,6},
			 [0x1E] = {asl,absoluto_X,7},
			 [0x90] = {bcc,relativo,2},
			 [0xB0] = {bcs,relativo,2},
			 [0xF0] = {beq,relativo,2},
		     [0xD0] = {bne,relativo,2},
		     [0x24] = {bit,pagina_cero,3},
		     [0x2C] = {bit,absoluto,4},
			 [0x30] = {bmi,relativo,2},
		     [0x10] = {bpl,relativo,2},
		     [0x00] = {brk,implicito,7},
		     [0x50] = {bvc,relativo,2},
		     [0x70] = {bvs,relativo,2},
		     [0x18] = {clc,implicito,2},
			 [0xD8] = {cld,implicito,2},
		     [0x58] = {cli,implicito,2},
		     [0xB8] = {clv,implicito,2},	 
		     [0xC9] = {cmp,inmediato,2},
		     [0xCD] = {cmp,absoluto,4},
		     [0xC5] = {cmp,pagina_cero,3},
		     [0xD5] = {cmp,pagina_cero_X,4},
			 [0xDD] = {cmp,absoluto_X,4},
		     [0xD9] = {cmp,absoluto_Y,4},
			 [0xC1] = {cmp,indirecto_indexado_X,6},
		     [0xD1] = {cmp,indirecto_indexado_Y,5},
			 [0xE0] = {cpx,inmediato,2},
		     [0xE4] = {cpx,pagina_cero,3},
		     [0xEC] = {cpx,absoluto,4},
		     [0xC0] = {cpy,inmediato,2},
		     [0xC4] = {cpy,pagina_cero,3},
		     [0xCC] = {cpy,absoluto,4},
		     [0xCE] = {dec,absoluto,6},
		     [0xC6] = {dec,pagina_cero,5},
		     [0xD6] = {dec,pagina_cero_X,6},
		     [0xDE] = {dec,absoluto_X,7},
		     [0xCA] = {dex,implicito,2},
		     [0x88] = {dey,implicito,2},
		     [0x49] = {eor,inmediato,2},
		     [0x4D] = {eor,absoluto,4},
		     [0x45] = {eor,pagina_cero,3},
		     [0x55] = {eor,pagina_cero_X,4},
			 [0x5D] = {eor,absoluto_X,4},
		     [0x59] = {eor,absoluto_Y,4},
			 [0x41] = {eor,indirecto_indexado_X,6},
		     [0x51] = {eor,indirecto_indexado_Y,5},
		     [0xE6] = {inc,pagina_cero,5},
		     [0xF6] = {inc,pagina_cero_X,6},
		     [0xEE] = {inc,absoluto,6},
		     [0xFE] = {inc,absoluto_X,7},
		     [0xE8] = {inx,implicito,2},
		     [0xC8] = {iny,implicito,2},
		     [0x4C] = {jmp,absoluto,3},
		     [0x6C] = {jmp,indirecto,5},
			 [0x20] = {jsr,absoluto,7}, 
		     [0xA9] = {lda,inmediato,2},
		     [0xAD] = {lda,absoluto,4},
			 [0xA5] = {lda,pagina_cero,3},
		     [0xB5] = {lda,pagina_cero_X,4},
			 [0xBD] = {lda,absoluto_X,4},
		     [0xB9] = {lda,absoluto_Y,4},
			 [0xA1] = {lda,indirecto_indexado_X,6},
		     [0xB1] = {lda,indirecto_indexado_Y,5}, 
		     [0xA2] = {ldx,inmediato,2},
		     [0xAE] = {ldx,absoluto,4},
		     [0xA6] = {ldx,pagina_cero,3},
		     [0xB6] = {ldx,pagina_cero_Y,4},
			 [0xBE] = {ldx,absoluto_Y,4},
		     [0xAC] = {ldy,absoluto,4},		 
		     [0xA0] = {ldy,inmediato,2},
		     [0xA4] = {ldy,pagina_cero,3},
		     [0xB4] = {ldy,pagina_cero_X,4},
		     [0xBC] = {ldy,absoluto_X,4},
			 [0x4A] = {lsr,acumulador,2},
		     [0x46] = {lsr,pagina_cero,5},
		     [0x56] = {lsr,pagina_cero_X,6},
		     [0x4E] = {lsr,absoluto,6},
		     [0x5E] = {lsr,absoluto_X,7},
		     [0xEA] = {nop,implicito,2},
			 [0x09] = {ora,inmediato,2},
		     [0x05] = {ora,pagina_cero,3},
		     [0x15] = {ora,pagina_cero_X,4},
		     [0x0D] = {ora,absoluto,4},
		     [0x1D] = {ora,absoluto_X,4},
		     [0x19] = {ora,absoluto_Y,4},
		     [0x01] = {ora,indirecto_indexado_X,6},
		     [0x11] = {ora,indirecto_indexado_Y,5},
		     [0x48] = {pha,implicito,3},
		     [0x08] = {php,implicito,3},
		     [0x68] = {pla,implicito,4},
		     [0x28] = {plp,implicito,4},
		     [0x2A] = {rol,acumulador,2},
		     [0x26] = {rol,pagina_cero,3},
		     [0x36] = {rol,pagina_cero_X,4},
		     [0x2E] = {rol,absoluto,4},
		     [0x3E] = {rol,absoluto_X,4},
		     [0x6A] = {ror,acumulador,2},
		     [0x66] = {ror,pagina_cero,3},
		     [0x76] = {ror,pagina_cero_X,4},
		     [0x6E] = {ror,absoluto,4},
		     [0x7E] = {ror,absoluto_X,4},
			 [0x40] = {rti,implicito,6},
			 [0x60] = {rts,implicito,6},
			 [0xE9] = {sbc,inmediato,2},
		     [0xE5] = {sbc,pagina_cero,3},
		     [0xF5] = {sbc,pagina_cero_X,4},
		     [0xED] = {sbc,absoluto,4},
		     [0xFD] = {sbc,absoluto_X,4},
		     [0xF9] = {sbc,absoluto_Y,4},
		     [0xE1] = {sbc,indirecto_indexado_X,6},
		     [0xF1] = {sbc,indirecto_indexado_Y,5},
		     [0x38] = {sec,implicito,2},
			 [0xF8] = {sed,implicito,2},
			 [0x78] = {sei,implicito,2},
		     [0x85] = {sta,pagina_cero,3},
		     [0x95] = {sta,pagina_cero_X,4},
		     [0x8D] = {sta,absoluto,4},
		     [0x9D] = {sta,absoluto_X,5},
		     [0x99] = {sta,absoluto_Y,5},
		     [0x81] = {sta,indirecto_indexado_X,6},
		     [0x91] = {sta,indirecto_indexado_Y,6},
		     [0x86] = {stx,pagina_cero,3},
		     [0x96] = {stx,pagina_cero_Y,4},
		     [0x8E] = {stx,absoluto,4},
		     [0x84] = {sty,pagina_cero,3},
		     [0x94] = {sty,pagina_cero_X,4},
		     [0x8C] = {sty,absoluto,4},
			 [0xAA] = {tax,implicito,2},
			 [0xA8] = {tay,implicito,2},
			 [0xBA] = {tsx,implicito,2},
			 [0x8A] = {txa,implicito,2},
			 [0x9A] = {txs,implicito,2},
			 [0x98] = {tya,implicito,2},
};

mos6502_t *mos_crear() {
    mos6502_t *m = malloc(sizeof(mos6502_t));
    if(m == NULL)
        return NULL;

	m->mem = NULL;
    m->a = m->x = m->y = 0;
    m->status = 0x00;

    m->mem = 0x00;
    m->pc = 0x0000;

    m->ciclos = 0;

    return m;
}

void mos_destruir(mos6502_t *m) {
    free(m->mem);
    free(m);
}

void mos_resetear(mos6502_t *m, uint8_t *mem, uint16_t pc) {
    m->a = m->x = m->y = 0;
    m->status = 0x00;

    m->mem = mem;
    m->pc = pc;

    m->ciclos = 0;
}

void mos_reiniciar(mos6502_t *m) {
    m->a = m->x = m->y = 0;
    m->status = 0x00;

    m->mem = NULL;
    m->pc = 0x0000;

    m->ciclos = 0;
}

void mos_ejecutar_instruccion(mos6502_t *m){
	instruccion_t i;

	i.codigo = (m -> mem[(m->pc)]);	
	m -> pc ++;
	opcode_t cod = opcodes[i.codigo];
	i.ciclos = cod.ciclos;

	cod.direccionamiento(m,&i); 
	cod.operacion(m,&i);

	m -> ciclos += i.ciclos;
}


void mos_setear_log(mos6502_t *m, char * archivo) {
	FILE * f = fopen(archivo,"a");
	if(f == NULL)
		return;
    fprintf(f,"%04x %02x %02x %02x %02x %02x\n",m->pc,m->a,m->x,m->y,m->status,m->sp);
	fclose(f);	
}

void mos_cargar_rom(mos6502_t *m, char * archivo) {
	FILE * f = fopen(archivo,"rb");
	if(f == NULL)
		return;

    m->mem = malloc(sizeof(uint8_t)*0x10000);
    if(m->mem == NULL){
		mos_destruir(m);
        return;
	}

	if(fread(m -> mem, sizeof(uint8_t), 0x10000,f) < 0x10000){
		fprintf(stderr,"Error de lectura\n");
		return;
	}

	m->pc = (m->mem[0xfffc])| m->mem[0xfffd]<< 8;
	m->sp = 0xff;

	fclose(f);	
}

void mos_assert(const char *test, mos6502_t *m, uint16_t pc, uint8_t a, uint8_t x, uint8_t y, uint8_t status, uint8_t ciclos_micro) {
    fprintf(stderr, "%s... ", test);

    assert(m->pc == pc);
    assert(m->a == a);
    assert(m->x == x);
    assert(m->y == y);
    assert(m->status == status);
    assert(m->ciclos == ciclos_micro);

    fprintf(stderr, "OK\n");
}

void apilar(mos6502_t * m, uint8_t valor){
	m -> mem[0x100|m -> sp] = valor;	
	m -> sp--;
}

uint8_t desapilar(mos6502_t * m){
	m -> sp++;
	return m -> mem[0x100|m -> sp];
}

