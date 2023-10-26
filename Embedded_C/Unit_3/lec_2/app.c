#include "uart.h"
unsigned char string_buffer[100]="Learn-in-depth:mohamed sultan";
unsigned char const string_buffer_2[100]="mohamed sultan";
void main()
{
	Uart_send_string(string_buffer);
}
