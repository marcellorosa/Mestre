/*
 * config_hw.h
 *
 *  Created on: 10/09/2016
 *      Author: Marcelo
 */

#ifndef CONFIG_HW_H_
#define CONFIG_HW_H_

//Definição de funções de inicialização
void config_clk(void);		//Configura Clock
void config_io(void);		//Configura entradas e saídas
//void config_uart(void);	//Este está sendo configurado dentro de uma função "portserial.c"
void config_AD(void);

#endif /* CONFIG_HW_H_ */
