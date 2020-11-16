#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#define UBRR FOSC/16/BAUDRATE-1
#define FOSC 16000000
#define BAUDRATE 19200

char message[8];
uint8_t i;

void USART_Init(int ubrr)
{
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;

	UCSRB = (1<<RXEN)|(1<<TXEN);
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);

}

unsigned char Re_char(void)
{
	while (!(UCSRA & (1<<RXC)));

	return UDR;
}

void Tr_char(unsigned char ch)
{
	while (!( UCSRA & (1<<UDRE)));

	UDR = ch;
}

int Tr_string(const char *S_str)
{

	while(*S_str)
	{
		Tr_char(*S_str);
		S_str++;
	}
	return 0;
}

void view()
{
	Tr_string("\r\n");
	Tr_string(message);
	Tr_string("\r\n");
}

void initialize(void)
{
	PORTC = (1<<PORTC4);
	_delay_ms(500);
	PORTC = (0<<PORTC4);
	_delay_ms(200);
}
void Ch_Select(void)
{
	for (i = 0; i < 8; i++)
	{
		while ((UCSRA & (1 << RXC)) == 0);
		message[i] = UDR;
		Tr_char(message[i]);
		if (message[i-2]=='T')
		{
			if (message[i-1]=='P')
			{
				if (message[i]=='0')
				{
					initialize();
					PORTC = (0<<PORTC3)|(0<<PORTC2)|(0<<PORTC1)|(0<<PORTC0);
					view();
					break;
				}
				else if (message[i]=='1')
				{
					initialize();
					PORTC = (0<<PORTC3)|(0<<PORTC2)|(0<<PORTC1)|(1<<PORTC0);
					view();
					break;
				}
				else if (message[i]=='2')
				{
					initialize();
					PORTC = (0<<PORTC3)|(0<<PORTC2)|(1<<PORTC1)|(0<<PORTC0);
					view();
					break;
				}
				else if (message[i]=='3')
				{
					initialize();
					PORTC = (0<<PORTC3)|(0<<PORTC2)|(1<<PORTC1)|(1<<PORTC0);
					view();
					break;
				}
				else if (message[i]=='4')
				{
					initialize();
					PORTC = (0<<PORTC3)|(1<<PORTC2)|(0<<PORTC1)|(0<<PORTC0);
					view();
					break;
				}
				else if (message[i]=='5')
				{
					initialize();
					PORTC = (0<<PORTC3)|(1<<PORTC2)|(0<<PORTC1)|(1<<PORTC0);
					view();
					break;
				}
				else if (message[i]=='6')
				{
					initialize();
					PORTC = (0<<PORTC3)|(1<<PORTC2)|(1<<PORTC1)|(0<<PORTC0);
					view();
					break;
				}
				else if (message[i]=='7')
				{
					initialize();
					PORTC = (0<<PORTC3)|(1<<PORTC2)|(1<<PORTC1)|(1<<PORTC0);
					view();
					break;
				}
				else if (message[i]=='8')
				{
					initialize();
					PORTC = (1<<PORTC3)|(0<<PORTC2)|(0<<PORTC1)|(0<<PORTC0);
					view();
					break;
				}
				else if (message[i]=='9')
				{
					initialize();
					PORTC = (1<<PORTC3)|(0<<PORTC2)|(0<<PORTC1)|(1<<PORTC0);
					view();
					break;
				}
				else
				{
					break;
				}
			}
		}
		else if (message[i]=='X')
		{
			PORTC = (1<<PORTC4);
			Tr_string("\r\n");
			Tr_string("Reset\r\n");
			break;
		}
	}
}

int main( void )
{
	USART_Init(UBRR);

	DDRC = 0xFF;
	PORTC = (1<<PORTC4);
	
	while(1)
	{
		Ch_Select();
	}
	return 0;
}

