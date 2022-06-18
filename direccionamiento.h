#ifndef _DIRECCIONES_H_
#define _DIRECCIONES_H_

// Direccionamiento de memoria

void implicito(mos6502_t * procesador, instruccion_t * instruccion);
void acumulador(mos6502_t *procesador, instruccion_t *instruccion);
void inmediato(mos6502_t *procesador, instruccion_t *instruccion);
void absoluto(mos6502_t *procesador, instruccion_t *instruccion);
void relativo(mos6502_t *procesador, instruccion_t *instruccion);
void pagina_cero(mos6502_t *procesador, instruccion_t *instruccion);
void indirecto(mos6502_t * procesador, instruccion_t * instruccion);
void absoluto_X(mos6502_t *procesador, instruccion_t *instruccion);
void absoluto_Y(mos6502_t *procesador, instruccion_t *instruccion);
void pagina_cero_X(mos6502_t *procesador, instruccion_t *instruccion);
void pagina_cero_Y(mos6502_t *procesador, instruccion_t *instruccion);
void indirecto_indexado_X(mos6502_t *procesador, instruccion_t *instruccion);
void indirecto_indexado_Y(mos6502_t *procesador, instruccion_t *instruccion);

#endif
