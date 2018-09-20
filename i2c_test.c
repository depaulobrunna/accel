#include <stdio.h>
#include <string.h>
#include <pigpio.h>

int main()
{

	if (gpioInitialise() < 0)
	{
   		printf("not initialise");
	}
	else{}
}
