#ifndef _TDA_H_
#define _TDA_H_

#define MAX_CADENA 20
#define MAX_ARG 8
#define MIN_ARG 2
#define NOMBRE_LOG "archivo.log"
#define POS_ROM 1
#define TOT_CICLOS 83007452

typedef struct {
    uint8_t a, x, y;    // Registros A, X e Y.
    uint16_t pc;        // Program counter.
    uint8_t status;     // Registro de status.
    uint8_t sp;         // Stack pointer.
    uint8_t *mem;       // Memoria.
    long ciclos;        // Cantidad de ciclos totales de ejecución.
} mos6502_t;

mos6502_t *mos_crear();
void mos_destruir(mos6502_t *mos);
void mos_resetear(mos6502_t *m, uint8_t *mem, uint16_t pc);
void mos_reiniciar(mos6502_t *m);
void mos_ejecutar_instruccion(mos6502_t *m);
void mos_setear_log(mos6502_t *m, char * archivo);
void mos_cargar_rom(mos6502_t *m, char * archivo);
void mos_assert(const char *test, mos6502_t *m, uint16_t pc, uint8_t a, uint8_t x, uint8_t y, uint8_t status, uint8_t ciclos_micro);
void apilar(mos6502_t * m, uint8_t valor);
uint8_t desapilar(mos6502_t * m);

#endif
