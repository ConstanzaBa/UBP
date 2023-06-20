////////////////////////////////////////////// LIBRERIAS //////////////////////////////////////////////

#include <16f84a.h> //PIC a utilizar

////////////////////////////////////////////// ORDENES //////////////////////////////////////////////

#fuses XT,NOWDT,NOPROTECT,NOPUT
#use delay (clock=4000000) // se usaran retardos tomando en cuenta que la frecuencia del oscilador es de 4Mhz
#use fast_io(a) // rápida entrada y salida

////////////////////////////////////////////// DECLARACION DE VARIABLES //////////////////////////////////////////////

int modo = 1, temp = 1, i = 0;

////////////////////////////////////////////// CONFIGURACION //////////////////////////////////////////////

// PUERTOS

void Config_Puertos(void);

// INTERRUPCIONES

#INT_EXT // para la interrupción INT (RB0)
void EXT_isr(void)
{
	modo++;
	if(modo == 3)
	{
		modo = 1;
		temp = 1;
	}
}

#INT_RB // para la interrupción RB (RB4)

void RB_isr(void)
{
	if(input(PIN_B4))
	{
		temp++;
	}
	if(modo == 1 && temp == 3)
	{
		temp = 1;
	}
	if(modo == 2 && temp == 4)
	{
		temp = 1;
	}
}

////////////////////////////////////////////// PROGRAMA PRINCIPAL //////////////////////////////////////////////

void main(void)
{
	Config_Puertos(); // llamado a funcion
	while(true) // bucle infinito
	{
		if(modo == 1) // modo automatico
		{
			output_low(PIN_A2); // led verde off
			output_low(PIN_A1); // led amarillo off
			output_low(PIN_A0); // led rojo off
			
			if(temp == 1) // temporizacion 1
			{
				// led verde on
				output_high(PIN_A2);
				// led verde on durante 6 segundos
				delay_ms(6000);
				// led rojo off
				output_low(PIN_A2);
				// 5 parpadeos de un segundo led amarillo
				for(i = 0; i <= 4; i++)
				{
					// led amarillo on
					output_high(PIN_A1);
					// led amarillo on durante 1/2 segundo
					delay_ms(500);
					// led amarillo off
					output_low(PIN_A1);
					// led amarillo off durante 1/2 segundo
					delay_ms(500);
				}
				// led rojo on
				output_high(PIN_A0);
				// led rojo on durante 4 segundos
				delay_ms(4000);
				// led rojo off
				output_low(PIN_A0);
			}
			
			if(temp == 2) // temporizacion 2
			{
				// led verde on
				output_high(PIN_A2);
				// led verde on durante 4 segundos
				delay_ms(4000);
				// led rojo off
				output_low(PIN_A2);
				// 4 parpadeos de un segundo led amarillo
				for(i = 0; i <= 3; i++)
				{
					// led amarillo on
					output_high(PIN_A1);
					// led amarillo on durante 1/2 segundo
					delay_ms(500);
					// led amarillo off
					output_low(PIN_A1);
					// led amarillo off durante 1/2 segundo
					delay_ms(500);
				}
				// led rojo on
				output_high(PIN_A0);
				// led rojo on durante 6 segundos
				delay_ms(6000);
				// led rojo off
				output_low(PIN_A0);
			}
		}
		
		if(modo == 2) // modo manual
		{
			while(temp == 1)
			{
				// led verde on
				output_high(PIN_A2);
				// led amarillo off
				output_low(PIN_A1);
				// led rojo off
				output_low(PIN_A0);
			}
			while(temp == 2)
			{
				// led verde off 
				output_low(PIN_A2);
				// led amarillo on
				output_high(PIN_A1);
				// led amarillo on durante 1/2 segundo
				delay_ms(500);
				// led amarillo off 
				output_low(PIN_A1);
				// led amarillo off durante 1/2 segundo
				delay_ms(500);
				// led rojo off
				output_low(PIN_A0);
			}
			while(temp == 3)
			{
				// led verde off
				output_low(PIN_A2);
				// led amarillo off
				output_low(PIN_A1);
				// led rojo on
				output_high(PIN_A0);
			}
		}
	}
}

void Config_Puertos(void)
{
	// portA como salidas (RA0, RA1 y RA2, las demas desactivadas)
	set_tris_A(0xF8);
	set_tris_B(0xFF);
	
	// todas las interrupciones activadas
	enable_interrupts(GLOBAL);
	enable_interrupts(INT_EXT);// habilitando interrupcion externa (RB0)
	enable_interrupts(INT_RB);// habilitando interrupciones de cambio de nivel (RB4-RB7)
	
	ext_int_edge(H_TO_L);//Seleccionando flanco de interrupcion externa
	
	output_low(PIN_A2); //led verde off
	output_low(PIN_A1); //led amarillo off
	output_low(PIN_A0); //led rojo off
	
	modo = 1;
	temp = 1;
}