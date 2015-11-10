#include<stdio.h>
#include<wiringPi.h>

#define M1_L 7 // 4
#define M1_R 0 // 17
#define M2_F 2 // 27
#define M2_R 3 // 22

void movStop();
void movLeft();
void movRigt();
void movForw();
void movBack();


int main(int argc, char* argv[])
{
	int data;
	if(wiringPiSetup () == -1)
		return 1;

	pinMode(M1_L, OUTPUT);
	pinMode(M1_R, OUTPUT);
	pinMode(M2_F, OUTPUT);
	pinMode(M2_R, OUTPUT);

	data =(int)argv[1][0];
	
	//left
	if(data == 'l')
	{
		movLeft();
		delay(200);
		movStop();
	}
	//right
	else if(data == 'r')
	{
		movRigt();
		delay(200);
		movStop();
	}
	//fow
	if(data == 'f')
	{
		movForw();
	}
	//bac
	else if(data == 'b')
	{	
		movBack();
	}
	//stop
	if(data == 's'){
		movStop();
	}
	return 0;
}

//left
void movLeft(){
	digitalWrite(M1_L,0);
	digitalWrite(M1_R,1);
	digitalWrite(M2_F,1);
	digitalWrite(M2_R,0);
}

//right
void movRigt(){
	digitalWrite(M1_L,1);
	digitalWrite(M1_R,0);
	digitalWrite(M2_F,0);
	digitalWrite(M2_R,1);
}

//stop
void movStop(){
	digitalWrite(M1_L,0);
	digitalWrite(M1_R,0);
	digitalWrite(M2_F,0);
	digitalWrite(M2_R,0);
}

//forw
void movForw(){
	digitalWrite(M1_L,0);
	digitalWrite(M1_R,1);
	digitalWrite(M2_F,0);
	digitalWrite(M2_R,1);
}

//back
void movBack(){
	digitalWrite(M1_L,1);
	digitalWrite(M1_R,0);
	digitalWrite(M2_F,1);
	digitalWrite(M2_R,0);
}
