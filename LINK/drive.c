// Created on Fri February 14 2014

#include ".\drive.h"
#include ".\generic.h"
#include ".\slowservo.h"

#define ARM 3//arm port
#define light_start_sensor 0
// change "ks" and motor ports in library

int main()
{
	light_start(light_start_sensor);
	forward(40.00);
	left(90,ks/2);
	forward(20.00);
	right(90,ks/2);
	motor(ARM,50);//move arm up
	forward(20.00);//get over to the scoring area
	motor(ARM,-30);//move arm down to drop hangers on ledge
	left(40,ks/2);
	right(50,ks/2);
	left(10,ks/2);//deposit hangers and push them to the sides
	backward(5.00);//back up, going to get blue hangers next
	for(int i=0; i<2; i++)
	{
		motor(ARM,-50);
		forward(5.00);//get arm down to the blue hangers
		motor(ARM,20);
		forward(5.00);
		motor(ARM,-20);
		backward(10.00);
		motor(ARM,40);
		forward(10.00);
		motor(ARM,10);
		backward(7.00);
		forward(2.00);
		motor(ARM,-10);
		backward(10.00);
		motor(ARM,10);
		forward(7.00);//collect one bottom blue multiplier hanger and deliver to top
	}
	//go back a little
	//do same thing as the regular hangers to place blue on top
	printf("finished");
	return 0;
}
