/*
 * rx_tx_c.c
 *
 * Created: 28/7/2022 15:05:00
 *  Author: iqmal
 */ 

#include <avr/io.h>
#include <util/delay.h>

void UART_init(uint16_t ubrr)
{
	//set baud rate to 9600
	UBRR0L = (uint8_t)(ubrr & 0xff);
	UBRR0H = (uint8_t)(ubrr >> 8);

	//enable rx and tx otherwise it is just standard i/o pins
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);	//0b00011000

	//frame format by default 8N1 (data bit, parity bit, stop bit)
}

unsigned char UART_RxChar()
{
	while ((UCSR0A & (1 << RXC0)) == 0);/* Wait till data is received */
	return (unsigned char)(UDR0);			/* Return the byte*/	//the data will auto be inside UDR0, just return it according to return type
}

void UART_TxChar(char ch)
{
	while (! (UCSR0A & (1<<UDRE0)));	/* Wait for empty transmit buffer*/
	UDR0 = ch ;							// UDR0 will auto transmit to terminal or any connected devices in mcu.
}

void UART_SendString(char *str)
{
	unsigned char j=0;
	
	while (str[j]!=0)		/* Send string till null */
	{
		UART_TxChar(str[j]);	
		j++;
	}
}

int main(void)
{
	char c;
	UART_init(103);
	
	UART_SendString("\nEcho Test ");	
	while(1)
	{
		c=UART_RxChar();
		UART_TxChar(c);
	}
}
