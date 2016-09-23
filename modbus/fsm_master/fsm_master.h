/*
 * fsm_master.h
 *
 *  Created on: 23/09/2016
 *      Author: Marcelo
 */

#ifndef FSM_MASTER_H_
#define FSM_MASTER_H_

typedef void (*action)(void);

typedef enum{
	ST_START,
	ST_INITIAL,
	ST_IDLE,
	ST_EMISSION,
	ST_RECEPETION,
	ST_CONTROL_WAIT,
	END_STATE

}states;

typedef struct {
	states estados;
	action acoes[END_STATE];
}fsm_master;



#endif /* FSM_MASTER_H_ */
