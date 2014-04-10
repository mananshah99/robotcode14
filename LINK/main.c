/*
* Main program for LINK driving
* 
* Major TODOs:  
* 	1. Squaring up after backing out from the hangers
*	2. Picking up blue hangers
*	3. Moving out of the way for the create
*
*
*
*/

#include "./drive.h"			// driving library
#include "./generic.h"			// generic functionality
#include "./slowservo.h"		// for slowservo


#define ARM 0				// arm port
#define LS 0				// light sensor port
#define HANGER_HOLDER 3			// mini-servo for holding hangers in's port

// Right motor turn 90 degrees to the left (with mrp)
// mrp(MOT_RIGHT, Power, -1544)

/*******ARM SERVO IMPORTANT VALUES****
*
*	Position		Value
*	----------------------
*	Top				350		
*	Middle			1000
*	Bottom			1800
*
* servo_slow(int port, int end, float time) 
* 
*************************************/

#define TOP 350
#define DROP 480
#define MID 1160
#define BOT 1655

/**
 * Hanger holder miniservo position values
 * Position		Value	Description
 * LEFT_CLOSE	2000	holding hangers on the left side of the arm
 * MIDDLE		1500
 * RIGHT_CLOSE	0 	holding hangers of the right side of the arm
**/

#define LEFT_CLOSE 2000
#define MIDDLE 1500
#define RIGHT_CLOSE 0

//Define MAIN to run the primary program

#define MAIN
//#define servo_test
//#define DPTEST
//#define hanger_release_test
//#define left_motor_test
//#define square_up_and_blue_hanger_test

//start position is with back against PVC pipe and left side one inch from left pipe surrounding starting box
#ifdef MAIN
int main()	
{
	//light_start(LS);			// light start
	shut_down_in(120.);
	enable_servos();
	printf("Starting\n");
	set_servo_position(HANGER_HOLDER, RIGHT_CLOSE);
	msleep(100);
	set_servo_position(ARM,BOT);
	msleep(100);
	motor(MOT_LEFT, -50);
	motor(MOT_RIGHT, -50);
	msleep(500);
	ao();
	msleep(500);
	forward(55.00);
	msleep(500);
	left(240,ks/2);				// left 90 degrees (more because the function undershoots)
	msleep(500);
	forward(31.00);
	msleep(500);
	right(270,ks/2);			// right 90 degrees, but uses the arm to move cube,so adding more, not changed to using both wheels anymore
	msleep(500);
	left(20,ks/2); 				//return from pushing exercise bench away from robot
	backward(15.00);	//sometimes arm hits the bottom rack after
	msleep(500);
	/*
	mrp(MOT_LEFT,400,5);
	mrp(MOT_RIGHT,-400,5); //turn 90 degrees
	msleep(1000);
	bmd(MOT_LEFT);
	bmd(MOT_RIGHT);
	*/
	printf("Lifting up arm....\n");
	set_servo_position(ARM, TOP);		// move arm up to top ledge
	msleep(2500);
	printf("At Hangers and Depositing!\n");
	forward(20.00);				// get over to the scoring area
	msleep(1000);				// stop to stop the arm shaking
	forward(17.00);
	msleep(500);
	set_servo_position(HANGER_HOLDER, MIDDLE);	// precaution due to holding on to the left pillar
	msleep(500);
	set_servo_position(ARM, DROP);		// move arm down to drop hangers on ledge
	msleep(500);
	motor(MOT_LEFT,50);			//going to push it to the right and then turn arm away
	motor(MOT_RIGHT, -50);			//using both wheels to turn
	msleep(700);
	bmd(MOT_LEFT);
	bmd(MOT_RIGHT);
	msleep(500);	//stop it running
	set_servo_position(HANGER_HOLDER, LEFT_CLOSE);
	msleep(200);
	ao();	//to stop right motor before I start
	msleep(500);
	mrp(MOT_LEFT, 1000, -1500);		//left(220,ks/2); //let go of hangers onto the ledge by turning 90 degrees
	msleep(1000);
	ao();
	msleep(1500);
	backward(30.00);
	
	printf("Leaving Hangers\n");
	
	/*  (BACKUP CODE)  wiggle to drop off the hangers 
	left(40,ks/2);				// left 30 degrees
	right(60,ks/2);				// right 50 degrees
	left(20,ks/2);				// deposit hangers and push them to the sides, left 20 degrees back
	*/
	
	msleep(500);
	left(250, ks/2);			//fully let go of hangers, then square up twice on pipes behind
	msleep(500);
	set_servo_position(ARM, BOT); //arm will mess up backing up, might will hit rack 
	msleep(1500);
	left(230,ks/2);
	msleep(1500);
	forward(60.00);
	right(250,ks/2);				//turn right to square up on pipe next to starting box
	msleep(500);
	
	//THIS PART IS BEING TESTED AND SOON WILL BE REPLACED
	
	/*set_servo_position(HANGER_HOLDER, RIGHT_CLOSE);
	msleep(500);
	motor(MOT_LEFT, -100);
	motor(MOT_RIGHT, -100);
	msleep(2000);	//square up
	forward(7.00);				//parallel to rack
	msleep(500);
	right(245,ks/2);
	msleep(500);
	ao();			//for next square up
	msleep(100);
	motor(MOT_LEFT, -100);
	motor(MOT_RIGHT, -100);		//square up again on other pipe
	msleep(2000);
	forward(80.00);
	
	printf("Now at blue hangers\n");
	printf("Moving blue hangers to top rack one at a time\n");
	
	set_servo_position(ARM, MID);
	msleep(300);
	left(30, ks/2);
	msleep(300);
	set_servo_position(HANGER_HOLDER, LEFT_CLOSE);
	msleep(300);
	backward(10.00);
	msleep(300);
	right(30, ks/2);
	msleep(300);
	backward(10.00);
	msleep(300);
	set_servo_position(ARM, TOP);
	msleep(300);
	forward(15.00);
	msleep(300);*/
	
	
	/* COMMENTING UNTESTED OLD VERSION OF CODE THAT PROBABLY DON'T WORK, THIS CODE HAS THE ROBOT NOT SQUARING UP
	
	mrp(MOT_LEFT, 500, 1544); 		// undo the turn to be straight again
	backward(10.00);			// back up 10 cm, going to get blue hangers next
	msleep(500);
	
	
	/** Don't try FIXING WITH SLOWSERVO anymore, slowservo library broken**/
	/*
	int i;			
	for(i=0; i<2; i++) {			// moves each blue hanger up 
		set_servo_position(ARM, TOP);	// move to the top 
		forward(5.00);			// get arm down to the blue hangers
		set_servo_position(ARM,TOP+20);				
		forward(5.00);			// check if breaks something
		set_servo_position(ARM,DROP);
		backward(10.00);	
		set_servo_position(ARM,MID);
		forward(10.00);
		set_servo_position(ARM,MID+10);
		backward(7.00);
		forward(2.00);
		set_servo_position(ARM,MID);
		backward(10.00);
		set_servo_position(ARM,MID+10);
		forward(7.00);			//collect one bottom blue multiplier hanger and deliver top
		backward(5.00);
	}
	*/
	
	
	ao();
	printf("finished");
	return 0;
}
#endif

//to test slowservo, it doesn't work currently
#ifdef servo_test
int main()
{
	enable_servos();
	servo_slow(1,1007,5000);
	msleep(10000);
	disable_servos();
	printf("Done!\n");
	return 0;
}
#endif

//Drive Path Test
#ifdef DPTEST
int main()
{
	enable_servos();
	forward(40.00);
	left(90,ks/2);
	forward(20.00);
	
	//add clearing out exercise bench and botguy before hangers
	right(90,ks/2);
	servo_slow(ARM,1000,10);		//move arm up
	forward(20.00);				//get over to the scoring area
	return 0;
}
#endif

//Hanger Release Test
#ifdef hanger_release_test
int main()
{
	set_servo_position(ARM, DROP);		// move arm down to drop hangers on ledge
	msleep(1000);
	motor(MOT_LEFT,50);			//going to push it to the right and then turn arm away
	motor(MOT_RIGHT, -50);			//using both wheels to turn
	msleep(1000);
	bmd(MOT_LEFT);
	bmd(MOT_RIGHT);
	mrp(MOT_LEFT, 400, -800);		//left(220,ks/2); //let go of hangers onto the ledge
	msleep(1000);
	printf("done\n");
	return 0;
}
#endif

//left motor test, make sure it starts with the arm up next to top rack holding hangers
#ifdef left_motor_test
int main()
{
	set_servo_position(HANGER_HOLDER, LEFT_CLOSE);
	set_servo_position(ARM, DROP);		//sets up the arm and the holder
	msleep(1000);
	motor(MOT_LEFT,50);			//going to push it to the right and then turn arm away
	motor(MOT_RIGHT, -50);		//using both wheels to turn
	msleep(1000);
	bmd(MOT_LEFT);
	bmd(MOT_RIGHT);
	msleep(1000);
	ao();
	mrp(MOT_LEFT, 1000, -800);
	msleep(2000);
	printf("done\n");
}
#endif

#ifdef square_up_and_blue_hanger_test

//this starts straight after the first square up

int main()
{
	enable_servos();
	set_servo_position(ARM, BOT);
	msleep(100);
	set_servo_position(HANGER_HOLDER, RIGHT_CLOSE);
	msleep(500);
	motor(MOT_LEFT, -100);
	motor(MOT_RIGHT, -100);
	msleep(500);	//square up
	ao();
	msleep(100);
	forward(5.50);				//parallel to rack
	msleep(500);
	right(235,ks/2);
	msleep(500);
	ao();			//for next square up
	msleep(100);
	motor(MOT_LEFT, -100);
	motor(MOT_RIGHT, -100);		//square up again on other pipe
	msleep(2000);
	forward(10.00);
	msleep(500);
	right(5, ks/2);
	msleep(100);
	forward(78.00);
	msleep(500);
	
	printf("Now at blue hangers\n");
	printf("Moving blue hangers to top rack one at a time\n");
	
	set_servo_position(ARM, MID);
	msleep(2000);
	left(40, ks/2);
	msleep(500);
	set_servo_position(HANGER_HOLDER, LEFT_CLOSE);
	msleep(500);
	/*right(10, ks/2);
	msleep(500);*/
	set_servo_position(ARM, MID+20);
	msleep(500);
	backward(10.00);
	msleep(500);
	backward(10.00);
	msleep(500);
	set_servo_position(ARM, TOP);
	msleep(500);
	forward(15.00);
	msleep(500);
	set_servo_position(HANGER_HOLDER, RIGHT_CLOSE);
	msleep(500);
	set_servo_position(ARM, DROP);
	msleep(500);
	left(10,ks/2);
	msleep(500);
	motor(MOT_RIGHT, -100);
	msleep(500);
}

#endif
