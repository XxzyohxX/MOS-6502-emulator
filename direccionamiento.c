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

// Direccionamiento de memoria

//No indexados, no en memoria

void implicito(mos6502_t * procesador, instruccion_t * instruccion){
	instruccion -> m = NULL;
}
void acumulador(mos6502_t *procesador, instruccion_t *instruccion){
	instruccion -> m = &procesador -> a;
}
void inmediato(mos6502_t *procesador, instruccion_t *instruccion){
	instruccion -> m = &procesador -> mem[(procesador -> pc)++];
}

//No indexados, en memoria

void absoluto(mos6502_t *procesador, instruccion_t *instruccion){
	instruccion -> direccion = (procesador -> mem[(procesador -> pc)+1] << 8) | (procesador -> mem[procesador -> pc]);
	instruccion -> m = &procesador -> mem[instruccion -> direccion];	
	(procesador -> pc) += 2;
}
void relativo(mos6502_t *procesador, instruccion_t *instruccion){
	instruccion -> m = &procesador -> mem[procesador -> pc++];
}
void pagina_cero(mos6502_t *procesador, instruccion_t *instruccion){
	instruccion -> direccion = procesador -> mem[procesador -> pc++] & 0x00ff;
	instruccion -> m = &(procesador -> mem[instruccion -> direccion]);
}
void indirecto(mos6502_t * procesador, instruccion_t * instruccion){
	instruccion -> direccion = (procesador -> mem[(procesador -> pc)+1] << 8) | (procesador -> mem[procesador -> pc]);	
	procesador -> pc = procesador -> mem[instruccion -> direccion] | procesador -> mem[instruccion -> direccion + 1] << 8;
	instruccion -> direccion = procesador -> pc;
}

//No indexados, en memoria

void absoluto_X(mos6502_t *procesador, instruccion_t *instruccion){
	instruccion -> direccion = (procesador -> mem[(procesador -> pc)+1] << 8) | (procesador -> mem[procesador -> pc]);
	instruccion -> direccion += procesador -> x;
	instruccion -> m = &procesador -> mem[instruccion -> direccion];	
	(procesador -> pc) += 2;
}
void absoluto_Y(mos6502_t *procesador, instruccion_t *instruccion){
	instruccion -> direccion = (procesador -> mem[(procesador -> pc)+1] << 8) | (procesador -> mem[procesador -> pc]);
	instruccion -> direccion += procesador -> y;
	instruccion -> m = &procesador -> mem[instruccion -> direccion];	
	(procesador -> pc) += 2;
}
void pagina_cero_X(mos6502_t *procesador, instruccion_t *instruccion){
	instruccion -> direccion = ((procesador -> mem[procesador -> pc++]) + (procesador -> x)) & 0x00ff;
	instruccion -> m = &(procesador -> mem[instruccion -> direccion]);
}
void pagina_cero_Y(mos6502_t *procesador, instruccion_t *instruccion){
	instruccion -> direccion = ((procesador -> mem[procesador -> pc++]) + (procesador -> y)) & 0x00ff;
	instruccion -> m = &(procesador -> mem[instruccion -> direccion]);
}
void indirecto_indexado_X(mos6502_t *procesador, instruccion_t *instruccion){
	uint8_t cte = procesador->mem[procesador->pc++]+ procesador->x;
	instruccion->direccion = (0x00<<8) | cte;
	uint16_t contenido_de_pagina_cero = procesador->mem[instruccion->direccion+1] << 8 | procesador->mem[instruccion->direccion];
	instruccion->direccion = contenido_de_pagina_cero;
	instruccion->m = &procesador->mem[instruccion->direccion];
}
void indirecto_indexado_Y(mos6502_t *procesador, instruccion_t *instruccion){
	uint8_t cte = procesador->mem[procesador->pc++];
	instruccion->direccion = (0x00<<8) | cte;
	uint16_t contenido_de_pagina_cero = procesador->mem[instruccion->direccion+1] << 8 | procesador->mem[instruccion->direccion];
	instruccion->direccion = contenido_de_pagina_cero + procesador->y;
	instruccion->m = &procesador->mem[instruccion->direccion];
}
