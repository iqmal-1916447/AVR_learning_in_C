/*
 * rx_tx_c.c
 *
 * Created: 28/7/2022 15:05:00
 *  Author: iqmal
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	UART_init(103);
	while(1)
	{
		UART_putc();
	}

	
}

void UART_init(uint16_t ubrr)
{
	//set baud rate to 9600
	UBRR0L = (uint8_t)(ubrr & 0xff);
	UBRR0H = (uint8_t)(ubrr >> 8);

	//enable rx and tx otherwise it is just standard i/o pins
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);	//0b00011000

	//frame format by default 8N1 (data bit, parity bit, stop bit)
}

unsigned char UART_getc()
{
	//wait for data to be received
	while(!(UCSR0A & (1 << RXC0)));
	
	//return data
	return UDR0;
}

void UART_putc()
{
	unsigned char data = UART_getc();
	//wait for transmit buffer to be empty, if UDRE0 is 1 so buffer is empty
	while(!(UCSR0A & (1 << UDRE0)));	//masking bit to get UDRE0 bit in UCSR0A register
	
	//load char data into transmit register
	UDR0 = data;
}

void UART_puts(char* s)
{
	while(*s > 0)
	{
		UART_putc(*(s++));
	}
}

