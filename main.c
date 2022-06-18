#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "tda.h"
#include "status.h"
#include "operaciones.h"
#include "direccionamiento.h"
#include "diccionario.h"

int main(int argc, char * argv[]) {

	long ciclos = TOT_CICLOS;
	uint16_t pc = 0;
	char * ptr;
	char log[MAX_CADENA] = NOMBRE_LOG;
    mos6502_t * micro = mos_crear();

    if(argc < MIN_ARG || argc > MAX_ARG){
		fprintf(stderr,"Ingrese la cantidad exacta de argumentos\n");
		mos_destruir(micro);
        return -1;
    }

	mos_cargar_rom(micro,argv[POS_ROM]);

	for(size_t i = 0; argv[i] != NULL; i++){
		if(!strcmp(argv[i],"-ciclos")){
			ciclos = atol(argv[i+1]);
		}
	    if(!strcmp(argv[i],"-log")){
			strcpy(log,argv[i+1]);
    	}
	    if(!strcmp(argv[i],"-halt")){
			pc = (uint16_t)strtol(argv[i+1],&ptr,16);
    	}
	}

	mos_setear_log(micro,log);

	for(size_t i = 0; i < ciclos - 1; i++){
		mos_ejecutar_instruccion(micro);
		mos_setear_log(micro,log);
		if(micro -> pc == pc){
			mos_destruir(micro);
			return 0;
		}
	}

	mos_destruir(micro);

    return 0;
}
