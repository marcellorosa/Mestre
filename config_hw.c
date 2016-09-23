/*
 * config_hw.c
 *
 *  Created on: 10/09/2016
 *      Author: Marcelo
 */

#include <msp430.h>

//Configuração de perifericos
//--------------------------------------------------------------
//--------------------------------------------------------------
void config_clk(void)	//configura o clock
{
	//O clock foi configurado a partir do DCO para aprox SMCLK=16,0Mhz
    BCSCTL2 = SELM_0 + DIVM_0 + DIVS_0;

    if (CALBC1_16MHZ != 0xFF) {
        /* Adjust this accordingly to your VCC rise time */
        __delay_cycles(100000);

        /* Follow recommended flow. First, clear all DCOx and MODx bits. Then
         * apply new RSELx values. Finally, apply new DCOx and MODx bit values.
         */
        DCOCTL = 0x00;
        BCSCTL1 = CALBC1_16MHZ;     /* Set DCO to 16MHz */
        DCOCTL = CALDCO_16MHZ;
    }

    /*
     * Basic Clock System Control 1
     *
     * XT2OFF -- Disable XT2CLK
     * ~XTS -- Low Frequency
     * DIVA_0 -- Divide by 1
     *
     * Note: ~XTS indicates that XTS has value zero
     */
    BCSCTL1 |= XT2OFF + DIVA_0;

    /*
     * Basic Clock System Control 3
     *
     * XT2S_0 -- 0.4 - 1 MHz
     * LFXT1S_0 -- If XTS = 0, XT1 = 32768kHz Crystal ; If XTS = 1, XT1 = 0.4 - 1-MHz crystal or resonator
     * XCAP_1 -- ~6 pF
     */
    BCSCTL3 = XT2S_0 + LFXT1S_0 + XCAP_1;
}

//--------------------------------------------------------------
//--------------------------------------------------------------
void config_io(void)	//configura entradas e saídas
{
	//Por default a porta 1 será considerada entrada e a porta 2 saída
	P1DIR = 0;				//Inicialmente toda a porta P1 como entrada
	P1DIR |= BIT0 + BIT6; 			//P1.3 como saída controle RS485 (Não usar P1.0 porque é usado em algum lugar para debuguer)
	P1OUT &= ~(BIT0 + BIT6);

	//P1REN |= BIT3;	//habilita resistores de pull(up/down)
	//P1OUT |= BIT3;	//pull UP

    /* Port 1 Port Select Register */
    P1SEL = BIT1 + BIT2;	//Selecionada a função TX RX para os pino P1.1 e P1.2
    P1SEL2 = BIT1 + BIT2;	//
}

//--------------------------------------------------------------
//--------------------------------------------------------------
void config_AD(void)
{
	// Configuracao do canal ADC
 	ADC10CTL1 =  ADC10SSEL_3;
  	//INCH7  Seleciona canal A7 (p1.7);
  	//Fonte de clock do ADC10 = SMCLK (ADC10SSEL_3)= ADC10SSEL0+ADC10SSEL1;

  	ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON ;
   //Vcc e Vss como referencia (SREF_0);
   //64 ciclos do ADC10CLK (ADC10SHT_3);
   //Liga o ADC10IE;
}



