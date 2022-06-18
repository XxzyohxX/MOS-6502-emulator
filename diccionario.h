#ifndef _DICCIONARIO_H_
#define _DICCIONARIO_H_

typedef struct {
    void (*operacion) (mos6502_t *, instruccion_t *);
    void (*direccionamiento) (mos6502_t *, instruccion_t *);    
    long ciclos;       
} opcode_t;

#endif
