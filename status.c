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

//Funciones utilizadas en el ejercicio obligatorio 3

uint8_t mask[] = {MASK_CARRY,MASK_ZERO,MASK_INTERRUPT_DISABLE,MASK_DECIMAL,MASK_BREAK,MASK_GUION,MASK_OVERFLOW,MASK_NEGATIVE};

bool get_status(uint8_t *reg, flag_t flag){
    return (*reg & mask[flag]); 
}

void set_status(uint8_t *reg, flag_t flag, bool status){
    if(status)
      *reg |= mask[flag];
    else
      *reg &=  ~mask[flag]; 
}

void set_zero(uint8_t *reg, uint8_t res){
    if(!res)
      set_status(reg,ZERO,true);
    else	
      set_status(reg,ZERO,false);
}

void set_negative(uint8_t *reg, uint8_t res){
    if(res & MASK_NEGATIVO)
      set_status(reg,NEGATIVE,true);
    else	
      set_status(reg,NEGATIVE,false);
}

void set_carry(uint8_t *reg, uint16_t res){
    if(res & MASK_ACARREO)
      set_status(reg,CARRY,true);
    else	
      set_status(reg,CARRY,false);
}

void set_overflow(uint8_t *reg, uint8_t a, uint8_t b, uint8_t res){
    if((!(a & MASK_NEGATIVO) && !(b & MASK_NEGATIVO) && (res & MASK_NEGATIVO)) || ((a & MASK_NEGATIVO) && (b & MASK_NEGATIVO) && !(res & MASK_NEGATIVO)))
      set_status(reg,OVERFLOW,true);
    else	
      set_status(reg,OVERFLOW,false);
}

void rotate_left(uint8_t *reg, uint8_t *x){
    bool aux = *x & MASK_NEGATIVO; 
    *x = *x << 1;  
    *x |= get_status(reg,CARRY) << POSICION_ACARREO;  
    set_status(reg,CARRY,aux);
}

void rotate_right(uint8_t *reg, uint8_t *x){
    bool aux = *x & MASK_ACARREO_U8; 
    *x = *x >> 1;  
    *x |= get_status(reg,CARRY) << POSICION_NEGATIVO;  
    set_status(reg,CARRY,aux);
}
