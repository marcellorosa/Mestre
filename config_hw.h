/*
 * config_hw.h
 *
 *  Created on: 10/09/2016
 *      Author: Marcelo
 */

#ifndef CONFIG_HW_H_
#define CONFIG_HW_H_

//Defini��o de fun��es de inicializa��o
void config_clk(void);		//Configura Clock
void config_io(void);		//Configura entradas e sa�das
//void config_uart(void);	//Este est� sendo configurado dentro de uma fun��o "portserial.c"
void config_AD(void);

#endif /* CONFIG_HW_H_ */
