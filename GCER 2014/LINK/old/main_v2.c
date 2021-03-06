//#define MAINV2

#ifdef MAINV2

double turned_angle;
int x_rob = 100;  
int y_rob = -113; //old: 156
int y_target = 69; //new: 68 (old = 25)
#include "./template.h"

/*
 * 100 closed
 * 1300 open
 * port 3
 */
int main() {
	#define DEBUG // comment this out when in actual competition 
	set_servo_position(3, 100);	
	
	//enabling everything
	enable_servos();
	camera_open();
	camera_update();
	
	//
	backward(33);
	msleep(1000);
	
	//
	set_servo_position(3, 1300);
	msleep(100);
	left(175,0);
	msleep(1000);
	
	//
	backward(6);
	msleep(1000);
	
	int i;
	for(i=0; i<3; i++) {
		correct_angle();
		correct_distance();
		msleep(1000);
	}
	forward(40);
	//done with backing up 
	disable_servos();
}

void correct_angle() {

//constants
	double K_p = 25.0;
	double K_i = 0.07;
	double K_d = 0.01;	
	
	//values (rob is robot) 
	int x_blob, y_blob;
	int x_target = x_rob; //new: 100
	
	//for PID
	double integral = 0.0;
	double derivative = 0.0;
	double prev_error = 0.0; 
	
	//threshold value
	double EPSILON = 0.02;
	
	//init
	set_servo_position(1, 1584);
	while(1/*!in_range(E, 0, EPSILON) || !in_range(E, 0, -EPSILON)*/) {
		ghj: 
		camera_update();
		SHOW(printf("[log] area of nearest blob -->  %d\n", cam_area(0)));
		if(cam_area(0)!=0) {
			x_blob = get_object_center(0,0).x;  
			y_blob = get_object_center(0,0).y;  
		}
		else {
			SHOW(printf("[log] !!!!!!!!!! NO BLOB IN SIGHT !!!!!!!!!!!!\n")); 
			goto ghj;
			x_blob = get_object_center(0,0).x;  
			y_blob = get_object_center(0,0).y;  
		}
			
		double E = atan(
			((double)(-1*(x_blob-x_rob)))
			/((double)(y_blob-y_rob))
		);
		
		//this is a bit sketchy but it should work
		if(prev_error==0) {
			prev_error = E;
			turned_angle = E;
		}
			
		integral += (E*0.001); //update time
		derivative = (E - prev_error)/0.001;
		
		motor(MOT_LEFT, -1*((K_p*E)+(integral*K_i)+(derivative*K_d)));
		motor(MOT_RIGHT, (K_p*E)+(integral*K_i)+(derivative*K_d));
		
		msleep(1);
		printf("[log] E -> %f, I -> %f, D -> %f\n", E, integral, derivative);
		prev_error = E;
		
		if(E<=EPSILON && E>=-EPSILON) 
		{
			ao();
			break;
		}
		
	}
	printf("[log] done with angle correction");
	beep();
	msleep(1000);
}

void correct_distance() {
	camera_update();
	
	double x_blob, y_blob;
	
	//fix this!
	do{
		x_blob = get_object_center(0,0).x;  
		y_blob = get_object_center(0,0).y;  
	}while(cam_area(0)==0);
	
	double E = -y_blob + y_target;
	
	//11 used to be 10.4 here
	if(E < 0) {
		backward((((double)E)*16)/1000.);
	}
	else {	
		forward((((double)E)*16)/1000.);
	}
	msleep(1000);
	
	//dropping 
	set_servo_position(1, 200);
	msleep(1500);
	//shaking
	backward(.1);
	msleep(100);
	forward(.2);
	msleep(100);
	backward(.1);
	msleep(500);
	set_servo_position(1, 1600);
	msleep(2000);
	printf("[log] finished tribble pickup");
	
	//move back the same amount
	forward(-(((double)E)*16)/1000.);
		
	double angle = turned_angle*RADTODEG;
	if(angle < 0) {
		left(angle, 0);
	}
	else {
		right(angle, 0);
	}
	msleep(1000);
}
#endif
