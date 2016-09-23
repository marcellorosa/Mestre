/*
 * fsm_master.c
 *
 *  Created on: 23/09/2016
 *      Author: Marcelo
 */

#include "fsm_master.h"
#include "mbport.h"

void init_fsm_master(void){
	xMBPortSerialInit(0,57600,8,MB_PAR_EVEN); //configurar e inicializa a UART
}


