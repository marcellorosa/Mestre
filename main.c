#include <msp430.h> 

#include "config_hw.h"
#include "fsm_master.h"

#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
//#include "mb.h"
#include "mbport.h"

#include "mbcrc.h"

#define WRT_STARTING_REG 		0
#define READ_STARTING_REG 		0
#define MAX_BYTE_MBPDU			22

char mb_writeMultipleRegisters(UCHAR *data_PDU, USHORT *data, USHORT length);
char mb_readHoldingRegisters(UCHAR *data_PDU, USHORT qtd_regs);

void montar_data_PDU(UCHAR slaveAddress, UCHAR functionCode, UCHAR *modBus_PDU, USHORT * data, USHORT length);

char a = 0;

UCHAR rtuBuffer[MAX_BYTE_MBPDU];

UCHAR countBuffer = 0;

USHORT event[6] = {12, 4, 6, 8, 10, 2};
USHORT size = 6;

UCHAR *mb_PDU;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    config_clk();				//configura o clk
    config_io(); 				//configurar das portas

    //xMBPortSerialInit(0,57600,8,MB_PAR_EVEN); //configurar e inicializa a UART

    mb_PDU = rtuBuffer;

    //size = 2;

    while(1){


    	if(a == 0){

    	montar_data_PDU((UCHAR)10, (UCHAR)0x10,mb_PDU,(USHORT*)event,size);

    	vMBPortSerialEnable(FALSE,TRUE);

    	_delay_cycles(100000);

    	}else{
    		montar_data_PDU((UCHAR)10, (UCHAR)0x3,mb_PDU,(USHORT*)event,1);

    		vMBPortSerialEnable(FALSE,TRUE);
    		_delay_cycles(100000);
    	}
    }
	
}

void send_UART(){

	if(countBuffer != 0){
		xMBPortSerialPutByte((char) *mb_PDU);
		mb_PDU++;
		countBuffer--;
	}else{
		mb_PDU = rtuBuffer;
		vMBPortSerialEnable(TRUE,FALSE);
		a++;
	}
}

void receive_UART(){

	UCHAR ucByte;
	P1OUT ^= BIT6;
	/* Always read the character. */
	( void )xMBPortSerialGetByte( ( CHAR * ) & ucByte );

	rtuBuffer[countBuffer++] = ucByte;

}

void montar_data_PDU(UCHAR slaveAddress, UCHAR functionCode, UCHAR *modBus_PDU, USHORT * data, USHORT length){

	USHORT CRC16;
	countBuffer = 0; //ver isso depois

	modBus_PDU[countBuffer++] = slaveAddress;
	modBus_PDU[countBuffer++] = functionCode;

	switch (functionCode) {
		case 3:
			mb_readHoldingRegisters(modBus_PDU,length);
			break;
		case 16:
			mb_writeMultipleRegisters(modBus_PDU,data,length);
			break;
		//default:
		//	break;
	}

	CRC16 = usMBCRC16(modBus_PDU,countBuffer);
	modBus_PDU[countBuffer++] = (UCHAR) (CRC16 & 0xFF);
	modBus_PDU[countBuffer++] = (UCHAR) (CRC16 >> 8);
}

char mb_writeMultipleRegisters(UCHAR *data_PDU, USHORT *data, USHORT length){


	//UCHAR index = 1;

	//Starting Address
	data_PDU[countBuffer++] = (UCHAR) WRT_STARTING_REG >> 8;
	data_PDU[countBuffer++] = (UCHAR) (WRT_STARTING_REG & 0xFF);

	//Quantity of Registers
	data_PDU[countBuffer++] = (UCHAR) (length >> 8);
	data_PDU[countBuffer++] = (UCHAR) (length & 0xFF);

	//Byte Count
	data_PDU[countBuffer++] = (UCHAR) (2*length);

	while((countBuffer - 7) < 2*length){
		data_PDU[countBuffer++] = (UCHAR) (*data) >> 8;
		data_PDU[countBuffer++] = (UCHAR) (*data & 0xFF);
		data++;
	}

	return 1;
}

char mb_readHoldingRegisters(UCHAR *data_PDU, USHORT qtd_regs){

	//Starting Address
	data_PDU[countBuffer++] = (UCHAR) READ_STARTING_REG >> 8;
	data_PDU[countBuffer++] = (UCHAR) (READ_STARTING_REG & 0xFF);

	//Quantity of Registers
	data_PDU[countBuffer++] = (UCHAR) (qtd_regs >> 8);
	data_PDU[countBuffer++] = (UCHAR) (qtd_regs & 0xFF);

	return 1;
}
