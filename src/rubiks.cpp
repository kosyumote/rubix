//#include <Windows.h>

// had to install the following package on Mint
//
//  libglew-dev  

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>     
#include <ctime>


//global variables
int soltf = 0; //int that checks for the amount of pieces in the correct place; if 54, then solved
static int i = -1;//needed for getRand function

struct sticker{//an array of 54 of these is made
	int position;//the cube has 54 different positions (1-54), and as the cube moves, the position changes
	GLfloat x, y, z; //this represents color, Red, Blue Green values - each color is assigned a different set of x y and z
};


sticker pieces[54];//this represents all the pieces, that are later initilized to be in all positions 1-54, with colors also assigned


void playagain(unsigned char key, int xmouse, int ymouse);
//precondition: none
//postcondition: awaits input, and will react by returning to cube or closing program

void print(int x, int y, int z, std::string str);
//precondition: takes in values for where on screen and a string
//postcondition: prints string to screen

void play(unsigned char key, int xmouse, int ymouse);
//precondition: opengl window is open
//postcondition: awaits input, and will react by calling the turn functions

int getRand();
//precondition: none needed
//postcondition: random int 1-20 is assigned 

void display();
//precondition: sticker pieces are declared with position and color
//postcondition: displays based off of sticker arry

void solvedDisplay();
//precondition: opengl window is open
//postcondition: displays text by calling print function

//for all turn/rotate functions
//precondition: pieces array is initialized
//postcondition: will change position of all pieces effected by the turn/rotation
void turnR();
void turnL();
void turnU();
void turnD();
void turnF();
void turnB();
void turnM();
void rotateX();
void rotateY();
void rotateZ();
void turnRp();
void turnLp();
void turnUp();
void turnDp();
void turnFp();
void turnBp();
void turnMp();
void rotateXp();
void rotateYp();
void rotateZp();

void scramble();
//precondition: pieces array is initialized
//postcondition: randomly scrambles the stickers using the turn/rotate functions and the random function

int main(int argc, char** argv)
{
	for (int i = 0; i < 54; i++){//sets up positions
		pieces[i].position = i + 1;
	}

	//sets up colors - positioning goes U, F, R, B, L, D; looking at face top left to right, by rows
	for (int i = 0; i < 9; i++){
		pieces[i].x = 1.0;
		pieces[i].y = 1.0;
		pieces[i].z = 0.0;
	}
	for (int i = 9; i < 18; i++){
		pieces[i].x = 1.0;
		pieces[i].y = 0.0;
		pieces[i].z = 0.0;
	}
	for (int i = 18; i < 27; i++){
		pieces[i].x = 0.0;
		pieces[i].y = 1.0;
		pieces[i].z = 0.0;
	}
	for (int i = 27; i < 36; i++){
		pieces[i].x = 1.0;
		pieces[i].y = 0.7;
		pieces[i].z = 0.0;
	}
	for (int i = 36; i < 45; i++){
		pieces[i].x = 0.0;
		pieces[i].y = 0.0;
		pieces[i].z = 1.0;
	}
	for (int i = 45; i < 54; i++){
		pieces[i].x = 1.0;
		pieces[i].y = 1.0;
		pieces[i].z = 1.0;	
	}

	//code needed to set up window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitDisplayMode(GLUT_RGB);

	//code to open window
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Rubix");

	
	//code to go to function that takes in input
	for (int i = 0; i < 10; i++){
		glutKeyboardFunc(play);

	}
	//display function
	glutDisplayFunc(display);

	
	//code needed to make the code go on until told to stop
		glutMainLoop();
	
	



		


	return 0;
}





void play(unsigned char key, int xmouse, int ymouse){
	
	

	

//awaits input and calls appropriate move functions
		if (key == 'j'){
			turnU();
		}

		if (key == 'f'){
			turnUp();
		}

		if (key == 'i'){
			turnR();
		}
		if (key == 'k'){
			turnRp();
		}
		if (key == 'e'){
			turnLp();
		}
		if (key == 'd'){
			turnL();
		}
		if (key == 'h'){
			turnF();
		}
		if (key == 'g'){
			turnFp();
		}
		if (key == 'o'){
			turnBp();
		}
		if (key == 'w'){
			turnB();
		}
		if (key == 'l'){
			turnDp();
		}
		if (key == 's'){
			turnD();
		}
		if (key == ';'){
			rotateY();
		}
		if (key == 'a'){
			rotateYp();
		}
		if (key == '.'){
			turnMp();
		}
		if (key == 'x'){
			turnM();
		}
		if (key == 'y'){
			rotateX();
		}
		if (key == 't'){
			rotateX();
		}
		if (key == 'n'){
			rotateXp();
		}
		if (key == 'b'){
			rotateXp();
		}
		if (key == 'p'){
			rotateZ();
		}
		if (key == 'q'){
			rotateZp();
		}
		if (key == '-'){
			scramble();
		}

		
		//checks if solved
		soltf = 0;
		for (int i = 0; i < 54; i++){
			if (pieces[i].position == i + 1){
				soltf++;
			}
		}
		

		//redisplays
		glutPostRedisplay();
	
		//if solved go to a new window
		if (soltf == 54){

			glutInitWindowSize(900, 900);
			glutInitWindowPosition(50, 50);
			

			
			glutCreateWindow("Solved");
			glutDisplayFunc(solvedDisplay);
		}
		
	
}


void display(){

	//SUPER EXTENSIVE CODE THAT DISPLAYS EVERYTHING - SIMPLY BASED ON DRAWING SHAPES AND HAVING COORDINATES FOR THE ENDS

	for (int i = 0; i < 54; i++){

		if (pieces[i].position == 1){

			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.1, 0.7);			//17
			glVertex2f(0.3, 0.7);			//18
			glVertex2f(0.2, 0.6);		//13
			glVertex2f(0.0, 0.6);		//14
			glEnd();

			glFlush();
		}

		if (pieces[i].position == 2){

			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.3, 0.7);			//17
			glVertex2f(0.5, 0.7);			//18
			glVertex2f(0.4, 0.6);		//13
			glVertex2f(0.2, 0.6);		//14
			glEnd();

			glFlush();
		}

		if (pieces[i].position == 3){

			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.4, 0.6);			//17
			glVertex2f(0.5, 0.7);			//18
			glVertex2f(0.7, 0.7);		//13
			glVertex2f(0.6, 0.6);		//14
			glEnd();

			glFlush();
		}

		if (pieces[i].position == 4){

			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(-0.1, 0.5);			//17
			glVertex2f(0.0, 0.6);			//18
			glVertex2f(0.2, 0.6);		//13
			glVertex2f(0.1, 0.5);		//14
			glEnd();

			glFlush();
		}

		if (pieces[i].position == 5){

			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.1, 0.5);			//17
			glVertex2f(0.2, 0.6);			//18
			glVertex2f(0.4, 0.6);		//13
			glVertex2f(0.3, 0.5);		//14
			glEnd();

			glFlush();
		}

		if (pieces[i].position == 6){

			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.3, 0.5);			//17
			glVertex2f(0.4, 0.6);			//18
			glVertex2f(0.6, 0.6);		//13
			glVertex2f(0.5, 0.5);		//14
			glEnd();

			glFlush();
		}

		if (pieces[i].position == 7){

			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(-0.2, 0.4);			//17
			glVertex2f(0.0, 0.4);			//18
			glVertex2f(0.1, 0.5);		//13
			glVertex2f(-0.1, 0.5);		//14
			glEnd();

			glFlush();
		}

		if (pieces[i].position == 8){

			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.0, 0.4);			//17
			glVertex2f(0.2, 0.4);			//18
			glVertex2f(0.3, 0.5);		//13
			glVertex2f(0.1, 0.5);		//14
			glEnd();

			glFlush();
		}

		if (pieces[i].position == 9){

			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.2, 0.4);			//17
			glVertex2f(0.4, 0.4);			//18
			glVertex2f(0.5, 0.5);		//13
			glVertex2f(0.3, 0.5);		//14
			glEnd();

			glFlush();
		}

		if (pieces[i].position == 10){

			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.0, 0.2);			//17
			glVertex2f(0.0, 0.4);			//18
			glVertex2f(-0.2, 0.4);		//13
			glVertex2f(-0.2, 0.2);		//14
			glEnd();

			glFlush();
		}

		if (pieces[i].position == 11){

			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.0, 0.2);			//17
			glVertex2f(0.0, 0.4);			//18
			glVertex2f(0.2, 0.4);		//13
			glVertex2f(0.2, 0.2);		//14
			glEnd();

			glFlush();
		}

		if (pieces[i].position == 12){

			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.4, 0.2);			//17
			glVertex2f(0.4, 0.4);			//18
			glVertex2f(0.2, 0.4);		//13
			glVertex2f(0.2, 0.2);		//14
			glEnd();

			glFlush();
		}


		if (pieces[i].position == 13){
			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.0, 0.0);			//17
			glVertex2f(0.0, 0.2);			//18
			glVertex2f(-0.2, 0.2);		//13
			glVertex2f(-0.2, 0.0);		//14
			glEnd();

			glFlush();

		}

		if (pieces[i].position == 14){
			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.0, 0.0);			//17
			glVertex2f(0.0, 0.2);			//18
			glVertex2f(0.2, 0.2);		//13
			glVertex2f(0.2, 0.0);		//14
			glEnd();

			glFlush();
		}

		if (pieces[i].position == 15){
			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.2, 0.0);			//17
			glVertex2f(0.2, 0.2);			//18
			glVertex2f(0.4, 0.2);		//13
			glVertex2f(0.4, 0.0);		//14
			glEnd();

			glFlush();
		}

		if (pieces[i].position == 16){
			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.0, 0.0);			//17
			glVertex2f(0.0, -0.2);			//18
			glVertex2f(-0.2, -0.2);		//13
			glVertex2f(-0.2, 0.0);		//14
			glEnd();

			glFlush();
		}

		if (pieces[i].position == 17){
			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.0, 0.0);			//17
			glVertex2f(0.0, -0.2);			//18
			glVertex2f(0.2, -0.2);		//13
			glVertex2f(0.2, 0.0);		//14
			glEnd();

			glFlush();
		}
		if (pieces[i].position == 18){
			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.2, 0.0);			//17
			glVertex2f(0.4, 0.0);			//18
			glVertex2f(0.4, -0.2);		//13
			glVertex2f(0.2, -0.2);		//14
			glEnd();

			glFlush();
		}

		if (pieces[i].position == 19){
			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.4, 0.2);			//17
			glVertex2f(0.4, 0.4);			//18
			glVertex2f(0.5, 0.5);		//13
			glVertex2f(0.5, 0.3);		//14
			glEnd();

			glFlush();
		}
		if (pieces[i].position == 20){
			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.5, 0.5);			//17
			glVertex2f(0.5, 0.3);			//18
			glVertex2f(0.6, 0.4);		//13
			glVertex2f(0.6, 0.6);		//14
			glEnd();

			glFlush();
		}
		if (pieces[i].position == 21){
			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.6, 0.6);			//17
			glVertex2f(0.6, 0.4);			//18
			glVertex2f(0.7, 0.5);		//13
			glVertex2f(0.7, 0.7);		//14
			glEnd();

			glFlush();
		}

		if (pieces[i].position == 22){
			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.4, 0.0);			//17
			glVertex2f(0.4, 0.2);			//18
			glVertex2f(0.5, 0.3);		//13
			glVertex2f(0.5, 0.1);		//14
			glEnd();

			glFlush();
		}

		if (pieces[i].position == 23){
			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.5, 0.1);			//17
			glVertex2f(0.5, 0.3);			//18
			glVertex2f(0.6, 0.4);		//13
			glVertex2f(0.6, 0.2);		//14
			glEnd();

			glFlush();
		}

		if (pieces[i].position == 24){
			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.6, 0.2);			//17
			glVertex2f(0.6, 0.4);			//18
			glVertex2f(0.7, 0.5);		//13
			glVertex2f(0.7, 0.3);		//14
			glEnd();

			glFlush();
		}


		if (pieces[i].position == 25){
			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.4, 0.0);			//17
			glVertex2f(0.4, -0.2);			//18
			glVertex2f(0.5, -0.1);		//14
			glVertex2f(0.5, 0.1);		//13
			glEnd();

			glFlush();
		}

		if (pieces[i].position == 26){
			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.5, -0.1);			//17
			glVertex2f(0.5, 0.1);			//18
			glVertex2f(0.6, 0.2);		//13
			glVertex2f(0.6, 0.0);		//14
			glEnd();

			glFlush();
		}
		if (pieces[i].position == 27){
			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(pieces[i].x, pieces[i].y, pieces[i].z);
			glVertex2f(0.6, 0.0);			//17
			glVertex2f(0.6, 0.2);			//18
			glVertex2f(0.7, 0.3);		//13
			glVertex2f(0.7, 0.1);		//14
			glEnd();

			glFlush();
		}
		
	}

	//insert lines between pieces

	//first 4 are front side
	glLineWidth(4.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, -0.2, 0.0);
	glVertex3f(0.0, 0.4, 0);
	glEnd();

	glLineWidth(4.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.2, -0.2, 0.0);
	glVertex3f(0.2, 0.4, 0);
	glEnd();

	glLineWidth(4.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(-0.2, 0.0, 0.0);
	glVertex3f(0.4, 0.0, 0);
	glEnd();

	glLineWidth(4.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(-0.2, 0.2, 0.0);
	glVertex3f(0.4, 0.2, 0);
	glEnd();

	//next 4 are top side

	glLineWidth(4.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.4, 0.0);
	glVertex3f(0.3, 0.7, 0);
	glEnd();

	glLineWidth(4.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.2, 0.4, 0.0);
	glVertex3f(0.5, 0.7, 0);
	glEnd();

	glLineWidth(2.5);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(-0.2, 0.5, 0.0);
	glVertex3f(0.5, 0.5, 0);
	glEnd();

	glLineWidth(2.5);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(-0.1, 0.6, 0.0);
	glVertex3f(0.6, 0.6, 0);
	glEnd();

	//next 4 are right side

	glLineWidth(4.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.4, 0.0, 0.0);
	glVertex3f(0.7, 0.3, 0);
	glEnd();

	glLineWidth(4.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.4, 0.2, 0.0);
	glVertex3f(0.7, 0.5, 0);
	glEnd();

	glLineWidth(3.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(0.5, -0.1, 0);
	glEnd();

	glLineWidth(3.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.6, 0.6, 0.0);
	glVertex3f(0.6, 0.0, 0);
	glEnd();

	//three last lines

	glLineWidth(4.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.4, 0.4, 0.0);
	glVertex3f(0.7, 0.7, 0);
	glEnd();

	glLineWidth(3.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.4, 0.4, 0.0);
	glVertex3f(0.4, -0.2, 0);
	glEnd();

	glLineWidth(3.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(-0.2, 0.4, 0.0);
	glVertex3f(0.4, 0.4, 0);
	glEnd();
	glFlush();

}



void turnR(){

	//goes through each pieces of the array to find which pieces is in which position, and moves them accordingly
	for (int i = 0; i < 54; i++){


		if (pieces[i].position == 3){
			pieces[i].position = 34;
		}
		else if (pieces[i].position == 6){
			pieces[i].position = 31;
		}
		else if (pieces[i].position == 9){
			pieces[i].position = 28;
		}
		else if (pieces[i].position == 12){
			pieces[i].position = 3;
		}
		else if (pieces[i].position == 15){
			pieces[i].position = 6;
		}
		else if (pieces[i].position == 18){
			pieces[i].position = 9;
		}
		else if (pieces[i].position == 48){
			pieces[i].position = 12;
		}
		else if (pieces[i].position == 51){
			pieces[i].position = 15;
		}
		else if (pieces[i].position == 54){
			pieces[i].position = 18;
		}
		else if (pieces[i].position == 28){
			pieces[i].position = 54;
		}
		else if (pieces[i].position == 31){
			pieces[i].position = 51;
		}
		else if (pieces[i].position == 34){
			pieces[i].position = 48;
		}
		else if (pieces[i].position == 19){
			pieces[i].position = 21;
		}
		else if (pieces[i].position == 20){
			pieces[i].position = 24;
		}
		else if (pieces[i].position == 21){
			pieces[i].position = 27;
		}
		else if (pieces[i].position == 22){
			pieces[i].position = 20;
		}
		else if (pieces[i].position == 23){
			pieces[i].position = 23;
		}
		else if (pieces[i].position == 24){
			pieces[i].position = 26;
		}
		else if (pieces[i].position == 25){
			pieces[i].position = 19;
		}
		else if (pieces[i].position == 26){
			pieces[i].position = 22;
		}
		else if (pieces[i].position == 27){
			pieces[i].position = 25;
		}


	}
}
void turnL(){

	for (int i = 0; i < 54; i++){


		if (pieces[i].position == 1){
			pieces[i].position = 10;
		}
		else if (pieces[i].position == 4){
			pieces[i].position = 13;
		}
		else if (pieces[i].position == 7){
			pieces[i].position = 16;
		}
		else if (pieces[i].position == 10){
			pieces[i].position = 46;
		}
		else if (pieces[i].position == 13){
			pieces[i].position = 49;
		}
		else if (pieces[i].position == 16){
			pieces[i].position = 52;
		}
		else if (pieces[i].position == 46){
			pieces[i].position = 36;
		}
		else if (pieces[i].position == 49){
			pieces[i].position = 33;
		}
		else if (pieces[i].position == 52){
			pieces[i].position = 30;
		}
		else if (pieces[i].position == 30){
			pieces[i].position = 7;
		}
		else if (pieces[i].position == 33){
			pieces[i].position = 4;
		}
		else if (pieces[i].position == 36){
			pieces[i].position = 1;
		}
		else if (pieces[i].position == 37){
			pieces[i].position = 39;
		}
		else if (pieces[i].position == 38){
			pieces[i].position = 42;
		}
		else if (pieces[i].position == 39){
			pieces[i].position = 45;
		}
		else if (pieces[i].position == 40){
			pieces[i].position = 38;
		}
		else if (pieces[i].position == 41){
			pieces[i].position = 41;
		}
		else if (pieces[i].position == 42){
			pieces[i].position = 44;
		}
		else if (pieces[i].position == 43){
			pieces[i].position = 37;
		}
		else if (pieces[i].position == 44){
			pieces[i].position = 40;
		}
		else if (pieces[i].position == 45){
			pieces[i].position = 43;
		}


	}

}
void turnU(){
	
	for (int i = 0; i < 54; i++){


		if (pieces[i].position == 1){
			pieces[i].position = 3;
		}
		else if (pieces[i].position == 2){
			pieces[i].position = 6;
		}
		else if (pieces[i].position == 3){
			pieces[i].position = 9;
		}
		else if (pieces[i].position == 4){
			pieces[i].position = 2;
		}
		else if (pieces[i].position == 5){
			pieces[i].position = 5;
		}
		else if (pieces[i].position == 6){
			pieces[i].position = 8;
		}
		else if (pieces[i].position == 7){
			pieces[i].position = 1;
		}
		else if (pieces[i].position == 8){
			pieces[i].position = 4;
		}
		else if (pieces[i].position == 9){
			pieces[i].position = 7;
		}
		else if (pieces[i].position == 10){
			pieces[i].position = 37;
		}
		else if (pieces[i].position == 11){
			pieces[i].position = 38;
		}
		else if (pieces[i].position == 12){
			pieces[i].position = 39;
		}
		else if (pieces[i].position == 19){
			pieces[i].position = 10;
		}
		else if (pieces[i].position == 20){
			pieces[i].position = 11;
		}
		else if (pieces[i].position == 21){
			pieces[i].position = 12;
		}
		else if (pieces[i].position == 28){
			pieces[i].position = 19;
		}
		else if (pieces[i].position == 29){
			pieces[i].position = 20;
		}
		else if (pieces[i].position == 30){
			pieces[i].position = 21;
		}
		else if(pieces[i].position == 37){
			pieces[i].position = 28;
		}
		else if(pieces[i].position == 38){
			pieces[i].position = 29;
		}
		else if(pieces[i].position == 39){
			pieces[i].position = 30;
		}


	}
}
void turnD(){


	for (int i = 0; i < 54; i++){


		if (pieces[i].position == 16){
			pieces[i].position = 25;
		}
		else if (pieces[i].position == 17){
			pieces[i].position = 26;
		}
		else if (pieces[i].position == 18){
			pieces[i].position = 27;
		}
		else if (pieces[i].position == 25){
			pieces[i].position = 34;
		}
		else if (pieces[i].position == 26){
			pieces[i].position = 35;
		}
		else if (pieces[i].position == 27){
			pieces[i].position = 36;
		}
		else if (pieces[i].position == 34){
			pieces[i].position = 43;
		}
		else if (pieces[i].position == 35){
			pieces[i].position = 44;
		}
		else if (pieces[i].position == 36){
			pieces[i].position = 45;
		}
		else if (pieces[i].position == 43){
			pieces[i].position = 16;
		}
		else if (pieces[i].position == 44){
			pieces[i].position = 17;
		}
		else if (pieces[i].position == 45){
			pieces[i].position = 18;
		}
		else if (pieces[i].position == 46){
			pieces[i].position = 48;
		}
		else if (pieces[i].position == 47){
			pieces[i].position = 51;
		}
		else if (pieces[i].position == 48){
			pieces[i].position = 54;
		}
		else if (pieces[i].position == 49){
			pieces[i].position = 47;
		}
		else if (pieces[i].position == 50){
			pieces[i].position = 50;
		}
		else if (pieces[i].position == 51){
			pieces[i].position = 53;
		}
		else if (pieces[i].position == 52){
			pieces[i].position = 46;
		}
		else if (pieces[i].position == 53){
			pieces[i].position = 49;
		}
		else if (pieces[i].position == 54){
			pieces[i].position = 52;
		}


	}
}
void turnF(){

	for (int i = 0; i < 54; i++){


		if (pieces[i].position == 7){
			pieces[i].position = 19;
		}
		else if (pieces[i].position == 8){
			pieces[i].position = 22;
		}
		else if (pieces[i].position == 9){
			pieces[i].position = 25;
		}
		else if (pieces[i].position == 19){
			pieces[i].position = 48;
		}
		else if (pieces[i].position == 22){
			pieces[i].position = 47;
		}
		else if (pieces[i].position == 25){
			pieces[i].position = 46;
		}
		else if (pieces[i].position == 48){
			pieces[i].position = 45;
		}
		else if (pieces[i].position == 47){
			pieces[i].position = 42;
		}
		else if (pieces[i].position == 46){
			pieces[i].position = 39;
		}
		else if (pieces[i].position == 45){
			pieces[i].position = 7;
		}
		else if (pieces[i].position == 42){
			pieces[i].position = 8;
		}
		else if (pieces[i].position == 39){
			pieces[i].position = 9;
		}
		else if (pieces[i].position == 10){
			pieces[i].position = 12;
		}
		else if (pieces[i].position == 11){
			pieces[i].position = 15;
		}
		else if (pieces[i].position == 12){
			pieces[i].position = 18;
		}
		else if (pieces[i].position == 13){
			pieces[i].position = 11;
		}
		else if (pieces[i].position == 14){
			pieces[i].position = 14;
		}
		else if (pieces[i].position == 15){
			pieces[i].position = 17;
		}
		else if (pieces[i].position == 16){
			pieces[i].position = 10;
		}
		else if (pieces[i].position == 17){
			pieces[i].position = 13;
		}
		else if (pieces[i].position == 18){
			pieces[i].position = 16;
		}


	}
}
void turnB(){

	for (int i = 0; i < 54; i++){


		if (pieces[i].position == 1){
			pieces[i].position = 43;
		}
		else if (pieces[i].position == 2){
			pieces[i].position = 40;
		}
		else if (pieces[i].position == 3){
			pieces[i].position = 37;
		}
		else if (pieces[i].position == 21){
			pieces[i].position = 1;
		}
		else if (pieces[i].position == 24){
			pieces[i].position = 2;
		}
		else if (pieces[i].position == 27){
			pieces[i].position = 3;
		}
		else if (pieces[i].position == 54){
			pieces[i].position = 21;
		}
		else if (pieces[i].position == 53){
			pieces[i].position = 24;
		}
		else if (pieces[i].position == 52){
			pieces[i].position = 27;
		}
		else if (pieces[i].position == 37){
			pieces[i].position = 52;
		}
		else if (pieces[i].position == 40){
			pieces[i].position = 53;
		}
		else if (pieces[i].position == 43){
			pieces[i].position = 54;
		}
		else if (pieces[i].position == 28){
			pieces[i].position = 30;
		}
		else if (pieces[i].position == 29){
			pieces[i].position = 33;
		}
		else if (pieces[i].position == 30){
			pieces[i].position = 36;
		}
		else if (pieces[i].position == 31){
			pieces[i].position = 29;
		}
		else if (pieces[i].position == 32){
			pieces[i].position = 32;
		}
		else if (pieces[i].position == 33){
			pieces[i].position = 35;
		}
		else if (pieces[i].position == 34){
			pieces[i].position = 28;
		}
		else if (pieces[i].position == 35){
			pieces[i].position = 31;
		}
		else if (pieces[i].position == 36){
			pieces[i].position = 34;
		}


	}


}
void turnM(){

	for (int i = 0; i < 54; i++){

		if (pieces[i].position == 2){
			pieces[i].position = 11;
		}
		else if (pieces[i].position == 5){
			pieces[i].position = 14;
		}
		else if (pieces[i].position == 8){
			pieces[i].position = 17;
		}
		else if (pieces[i].position == 11){
			pieces[i].position = 47;
		}
		else if (pieces[i].position == 14){
			pieces[i].position = 50;
		}
		else if (pieces[i].position == 17){
			pieces[i].position = 53;
		}
		else if (pieces[i].position == 47){
			pieces[i].position = 35;
		}
		else if (pieces[i].position == 50){
			pieces[i].position = 32;
		}
		else if (pieces[i].position == 53){
			pieces[i].position = 29;
		}
		else if (pieces[i].position == 35){
			pieces[i].position = 2;
		}
		else if (pieces[i].position == 32){
			pieces[i].position = 5;
		}
		else if (pieces[i].position == 29){
			pieces[i].position = 8;
		}
		
	}
}
void rotateX(){

	for (int i = 0; i < 54; i++){


		if (pieces[i].position == 3){
			pieces[i].position = 34;
		}
		else if (pieces[i].position == 6){
			pieces[i].position = 31;
		}
		else if (pieces[i].position == 9){
			pieces[i].position = 28;
		}
		else if (pieces[i].position == 12){
			pieces[i].position = 3;
		}
		else if (pieces[i].position == 15){
			pieces[i].position = 6;
		}
		else if (pieces[i].position == 18){
			pieces[i].position = 9;
		}
		else if (pieces[i].position == 48){
			pieces[i].position = 12;
		}
		else if (pieces[i].position == 51){
			pieces[i].position = 15;
		}
		else if (pieces[i].position == 54){
			pieces[i].position = 18;
		}
		else if (pieces[i].position == 28){
			pieces[i].position = 54;
		}
		else if (pieces[i].position == 31){
			pieces[i].position = 51;
		}
		else if (pieces[i].position == 34){
			pieces[i].position = 48;
		}
		else if (pieces[i].position == 19){
			pieces[i].position = 21;
		}
		else if (pieces[i].position == 20){
			pieces[i].position = 24;
		}
		else if (pieces[i].position == 21){
			pieces[i].position = 27;
		}
		else if (pieces[i].position == 22){
			pieces[i].position = 20;
		}
		else if (pieces[i].position == 23){
			pieces[i].position = 23;
		}
		else if (pieces[i].position == 24){
			pieces[i].position = 26;
		}
		else if (pieces[i].position == 25){
			pieces[i].position = 19;
		}
		else if (pieces[i].position == 26){
			pieces[i].position = 22;
		}
		else if (pieces[i].position == 27){
			pieces[i].position = 25;
		}
		else if (pieces[i].position == 2){
			pieces[i].position = 35;
		}
		else if (pieces[i].position == 5){
			pieces[i].position = 32;
		}
		else if (pieces[i].position == 8){
			pieces[i].position = 29;
		}
		else if (pieces[i].position == 11){
			pieces[i].position = 2;
		}
		else if (pieces[i].position == 14){
			pieces[i].position = 5;
		}
		else if (pieces[i].position == 17){
			pieces[i].position = 8;
		}
		else if (pieces[i].position == 47){
			pieces[i].position = 11;
		}
		else if (pieces[i].position == 50){
			pieces[i].position = 14;
		}
		else if (pieces[i].position == 53){
			pieces[i].position = 17;
		}
		else if (pieces[i].position == 35){
			pieces[i].position = 47;
		}
		else if (pieces[i].position == 32){
			pieces[i].position = 50;
		}
		else if (pieces[i].position == 29){
			pieces[i].position = 53;
		}
		else if (pieces[i].position == 1){
			pieces[i].position = 36;
		}
		else if (pieces[i].position == 4){
			pieces[i].position = 33;
		}
		else if (pieces[i].position == 7){
			pieces[i].position = 30;
		}
		else if (pieces[i].position == 10){
			pieces[i].position = 1;
		}
		else if (pieces[i].position == 13){
			pieces[i].position = 4;
		}
		else if (pieces[i].position == 16){
			pieces[i].position = 7;
		}
		else if (pieces[i].position == 46){
			pieces[i].position = 10;
		}
		else if (pieces[i].position == 49){
			pieces[i].position = 13;
		}
		else if (pieces[i].position == 52){
			pieces[i].position = 16;
		}
		else if (pieces[i].position == 30){
			pieces[i].position = 52;
		}
		else if (pieces[i].position == 33){
			pieces[i].position = 49;
		}
		else if (pieces[i].position == 36){
			pieces[i].position = 46;
		}
		else if (pieces[i].position == 37){
			pieces[i].position = 43;
		}
		else if (pieces[i].position == 38){
			pieces[i].position = 40;
		}
		else if (pieces[i].position == 39){
			pieces[i].position = 37;
		}
		else if (pieces[i].position == 40){
			pieces[i].position = 44;
		}
		else if (pieces[i].position == 41){
			pieces[i].position = 41;
		}
		else if (pieces[i].position == 42){
			pieces[i].position = 38;
		}
		else if (pieces[i].position == 43){
			pieces[i].position = 45;
		}
		else if (pieces[i].position == 44){
			pieces[i].position = 42;
		}
		else if (pieces[i].position == 45){
			pieces[i].position = 39;
		}

	}
}
void rotateY(){

	for (int i = 0; i < 54; i++){


		if (pieces[i].position == 1){
			pieces[i].position = 3;
		}
		else if (pieces[i].position == 2){
			pieces[i].position = 6;
		}
		else if (pieces[i].position == 3){
			pieces[i].position = 9;
		}
		else if (pieces[i].position == 4){
			pieces[i].position = 2;
		}
		else if (pieces[i].position == 5){
			pieces[i].position = 5;
		}
		else if (pieces[i].position == 6){
			pieces[i].position = 8;
		}
		else if (pieces[i].position == 7){
			pieces[i].position = 1;
		}
		else if (pieces[i].position == 8){
			pieces[i].position = 4;
		}
		else if (pieces[i].position == 9){
			pieces[i].position = 7;
		}
		else if (pieces[i].position == 10){
			pieces[i].position = 37;
		}
		else if (pieces[i].position == 11){
			pieces[i].position = 38;
		}
		else if (pieces[i].position == 12){
			pieces[i].position = 39;
		}
		else if (pieces[i].position == 19){
			pieces[i].position = 10;
		}
		else if (pieces[i].position == 20){
			pieces[i].position = 11;
		}
		else if (pieces[i].position == 21){
			pieces[i].position = 12;
		}
		else if (pieces[i].position == 28){
			pieces[i].position = 19;
		}
		else if (pieces[i].position == 29){
			pieces[i].position = 20;
		}
		else if (pieces[i].position == 30){
			pieces[i].position = 21;
		}
		else if (pieces[i].position == 37){
			pieces[i].position = 28;
		}
		else if (pieces[i].position == 38){
			pieces[i].position = 29;
		}
		else if (pieces[i].position == 39){
			pieces[i].position = 30;
		}
		else if (pieces[i].position == 16){
			pieces[i].position = 43;
		}
		else if (pieces[i].position == 17){
			pieces[i].position = 44;
		}
		else if (pieces[i].position == 18){
			pieces[i].position = 45;
		}
		else if (pieces[i].position == 25){
			pieces[i].position = 16;
		}
		else if (pieces[i].position == 26){
			pieces[i].position = 17;
		}
		else if (pieces[i].position == 27){
			pieces[i].position = 18;
		}
		else if (pieces[i].position == 34){
			pieces[i].position = 25;
		}
		else if (pieces[i].position == 35){
			pieces[i].position = 26;
		}
		else if (pieces[i].position == 36){
			pieces[i].position = 27;
		}
		else if (pieces[i].position == 43){
			pieces[i].position = 34;
		}
		else if (pieces[i].position == 44){
			pieces[i].position = 35;
		}
		else if (pieces[i].position == 45){
			pieces[i].position = 36;
		}
		else if (pieces[i].position == 46){
			pieces[i].position = 52;
		}
		else if (pieces[i].position == 47){
			pieces[i].position = 49;
		}
		else if (pieces[i].position == 48){
			pieces[i].position = 46;
		}
		else if (pieces[i].position == 49){
			pieces[i].position = 53;
		}
		else if (pieces[i].position == 50){
			pieces[i].position = 50;
		}
		else if (pieces[i].position == 51){
			pieces[i].position = 47;
		}
		else if (pieces[i].position == 52){
			pieces[i].position = 54;
		}
		else if (pieces[i].position == 53){
			pieces[i].position = 51;
		}
		else if (pieces[i].position == 54){
			pieces[i].position = 48;
		}
		else if (pieces[i].position == 13){
			pieces[i].position = 40;
		}
		else if (pieces[i].position == 14){
			pieces[i].position = 41;
		}
		else if (pieces[i].position == 15){
			pieces[i].position = 42;
		}
		else if (pieces[i].position == 22){
			pieces[i].position = 13;
		}
		else if (pieces[i].position == 23){
			pieces[i].position = 14;
		}
		else if (pieces[i].position == 24){
			pieces[i].position = 15;
		}
		else if (pieces[i].position == 31){
			pieces[i].position = 22;
		}
		else if (pieces[i].position == 32){
			pieces[i].position = 23;
		}
		else if (pieces[i].position == 33){
			pieces[i].position = 24;
		}
		else if (pieces[i].position == 40){
			pieces[i].position = 31;
		}
		else if (pieces[i].position == 41){
			pieces[i].position = 32;
		}
		else if (pieces[i].position == 42){
			pieces[i].position = 33;
		}

	}
}
void rotateZ(){

	for (int i = 0; i < 54; i++){

		if (pieces[i].position == 1){
			pieces[i].position = 21;
		}
		else if (pieces[i].position == 2){
			pieces[i].position = 24;
		}
		else if (pieces[i].position == 3){
			pieces[i].position = 27;
		}
		else if (pieces[i].position == 21){
			pieces[i].position = 54;
		}
		else if (pieces[i].position == 24){
			pieces[i].position = 53;
		}
		else if (pieces[i].position == 27){
			pieces[i].position = 52;
		}
		else if (pieces[i].position == 54){
			pieces[i].position = 43;
		}
		else if (pieces[i].position == 53){
			pieces[i].position = 40;
		}
		else if (pieces[i].position == 52){
			pieces[i].position = 37;
		}
		else if (pieces[i].position == 37){
			pieces[i].position = 3;
		}
		else if (pieces[i].position == 40){
			pieces[i].position = 2;
		}
		else if (pieces[i].position == 43){
			pieces[i].position = 1;
		}
		else if (pieces[i].position == 28){
			pieces[i].position = 34;
		}
		else if (pieces[i].position == 29){
			pieces[i].position = 31;
		}
		else if (pieces[i].position == 30){
			pieces[i].position = 28;
		}
		else if (pieces[i].position == 31){
			pieces[i].position = 35;
		}
		else if (pieces[i].position == 32){
			pieces[i].position = 32;
		}
		else if (pieces[i].position == 33){
			pieces[i].position = 29;
		}
		else if (pieces[i].position == 34){
			pieces[i].position = 36;
		}
		else if (pieces[i].position == 35){
			pieces[i].position = 33;
		}
		else if (pieces[i].position == 36){
			pieces[i].position = 30;
		}
		else if (pieces[i].position == 7){
			pieces[i].position = 19;
		}
		else if (pieces[i].position == 8){
			pieces[i].position = 22;
		}
		else if (pieces[i].position == 9){
			pieces[i].position = 25;
		}
		else if (pieces[i].position == 19){
			pieces[i].position = 48;
		}
		else if (pieces[i].position == 22){
			pieces[i].position = 47;
		}
		else if (pieces[i].position == 25){
			pieces[i].position = 46;
		}
		else if (pieces[i].position == 48){
			pieces[i].position = 45;
		}
		else if (pieces[i].position == 47){
			pieces[i].position = 42;
		}
		else if (pieces[i].position == 46){
			pieces[i].position = 39;
		}
		else if (pieces[i].position == 45){
			pieces[i].position = 7;
		}
		else if (pieces[i].position == 42){
			pieces[i].position = 8;
		}
		else if (pieces[i].position == 39){
			pieces[i].position = 9;
		}
		else if (pieces[i].position == 10){
			pieces[i].position = 12;
		}
		else if (pieces[i].position == 11){
			pieces[i].position = 15;
		}
		else if (pieces[i].position == 12){
			pieces[i].position = 18;
		}
		else if (pieces[i].position == 13){
			pieces[i].position = 11;
		}
		else if (pieces[i].position == 14){
			pieces[i].position = 14;
		}
		else if (pieces[i].position == 15){
			pieces[i].position = 17;
		}
		else if (pieces[i].position == 16){
			pieces[i].position = 10;
		}
		else if (pieces[i].position == 17){
			pieces[i].position = 13;
		}
		else if (pieces[i].position == 18){
			pieces[i].position = 16;
		}
		else if (pieces[i].position == 4){
			pieces[i].position = 20;
		}
		else if (pieces[i].position == 5){
			pieces[i].position = 23;
		}
		else if (pieces[i].position == 6){
			pieces[i].position = 26;
		}
		else if (pieces[i].position == 20){
			pieces[i].position = 51;
		}
		else if (pieces[i].position == 23){
			pieces[i].position = 50;
		}
		else if (pieces[i].position == 26){
			pieces[i].position = 49;
		}
		else if (pieces[i].position == 49){
			pieces[i].position = 38;
		}
		else if (pieces[i].position == 50){
			pieces[i].position = 41;
		}
		else if (pieces[i].position == 51){
			pieces[i].position = 44;
		}
		else if (pieces[i].position == 44){
			pieces[i].position = 4;
		}
		else if (pieces[i].position == 41){
			pieces[i].position = 5;
		}
		else if (pieces[i].position == 38){
			pieces[i].position = 6;
		}

	}

}
void turnRp(){
	for (int i = 0; i < 54; i++){


		if (pieces[i].position == 3){
			pieces[i].position = 12;
		}
		else if (pieces[i].position == 6){
			pieces[i].position = 15;
		}
		else if (pieces[i].position == 9){
			pieces[i].position = 18;
		}
		else if (pieces[i].position == 12){
			pieces[i].position = 48;
		}
		else if (pieces[i].position == 15){
			pieces[i].position = 51;
		}
		else if (pieces[i].position == 18){
			pieces[i].position = 54;
		}
		else if (pieces[i].position == 48){
			pieces[i].position = 34;
		}
		else if (pieces[i].position == 51){
			pieces[i].position = 31;
		}
		else if (pieces[i].position == 54){
			pieces[i].position = 28;
		}
		else if (pieces[i].position == 28){
			pieces[i].position = 9;
		}
		else if (pieces[i].position == 31){
			pieces[i].position = 6;
		}
		else if (pieces[i].position == 34){
			pieces[i].position = 3;
		}
		else if (pieces[i].position == 19){
			pieces[i].position = 25;
		}
		else if (pieces[i].position == 20){
			pieces[i].position = 22;
		}
		else if (pieces[i].position == 21){
			pieces[i].position = 19;
		}
		else if (pieces[i].position == 22){
			pieces[i].position = 26;
		}
		else if (pieces[i].position == 23){
			pieces[i].position = 23;
		}
		else if (pieces[i].position == 24){
			pieces[i].position = 20;
		}
		else if (pieces[i].position == 25){
			pieces[i].position = 27;
		}
		else if (pieces[i].position == 26){
			pieces[i].position = 24;
		}
		else if (pieces[i].position == 27){
			pieces[i].position = 21;
		}


	}
}
void turnLp(){

	for (int i = 0; i < 54; i++){


		if (pieces[i].position == 1){
			pieces[i].position = 36;
		}
		else if (pieces[i].position == 4){
			pieces[i].position = 33;
		}
		else if (pieces[i].position == 7){
			pieces[i].position = 30;
		}
		else if (pieces[i].position == 10){
			pieces[i].position = 1;
		}
		else if (pieces[i].position == 13){
			pieces[i].position = 4;
		}
		else if (pieces[i].position == 16){
			pieces[i].position = 7;
		}
		else if (pieces[i].position == 46){
			pieces[i].position = 10;
		}
		else if (pieces[i].position == 49){
			pieces[i].position = 13;
		}
		else if (pieces[i].position == 52){
			pieces[i].position = 16;
		}
		else if (pieces[i].position == 30){
			pieces[i].position = 52;
		}
		else if (pieces[i].position == 33){
			pieces[i].position = 49;
		}
		else if (pieces[i].position == 36){
			pieces[i].position = 46;
		}
		else if (pieces[i].position == 37){
			pieces[i].position = 43;
		}
		else if (pieces[i].position == 38){
			pieces[i].position = 40;
		}
		else if (pieces[i].position == 39){
			pieces[i].position = 37;
		}
		else if (pieces[i].position == 40){
			pieces[i].position = 44;
		}
		else if (pieces[i].position == 41){
			pieces[i].position = 41;
		}
		else if (pieces[i].position == 42){
			pieces[i].position = 38;
		}
		else if (pieces[i].position == 43){
			pieces[i].position = 45;
		}
		else if (pieces[i].position == 44){
			pieces[i].position = 42;
		}
		else if (pieces[i].position == 45){
			pieces[i].position = 39;
		}


	}

}
void turnUp(){
	for (int i = 0; i < 54; i++){


		if (pieces[i].position == 1){
			pieces[i].position = 7;
		}
		else if(pieces[i].position == 2){
			pieces[i].position = 4;
		}
		else if (pieces[i].position == 3){
			pieces[i].position = 1;
		}
		else if (pieces[i].position == 4){
			pieces[i].position = 8;
		}
		else if (pieces[i].position == 5){
			pieces[i].position = 5;
		}
		else if (pieces[i].position == 6){
			pieces[i].position = 2;
		}
		else if (pieces[i].position == 7){
			pieces[i].position = 9;
		}
		else if (pieces[i].position == 8){
			pieces[i].position = 6;
		}
		else if (pieces[i].position == 9){
			pieces[i].position = 3;
		}
		else if (pieces[i].position == 10){
			pieces[i].position = 19;
		}
		else if (pieces[i].position == 11){
			pieces[i].position = 20;
		}
		else if (pieces[i].position == 12){
			pieces[i].position = 21;
		}
		else if (pieces[i].position == 19){
			pieces[i].position = 28;
		}
		else if (pieces[i].position == 20){
			pieces[i].position = 29;
		}
		else if (pieces[i].position == 21){
			pieces[i].position = 30;
		}
		else if (pieces[i].position == 28){
			pieces[i].position = 37;
		}
		else if (pieces[i].position == 29){
			pieces[i].position = 38;
		}
		else if (pieces[i].position == 30){
			pieces[i].position = 39;
		}
		else if (pieces[i].position == 37){
			pieces[i].position = 10;
		}
		else if (pieces[i].position == 38){
			pieces[i].position = 11;
		}
		else if (pieces[i].position == 39){
			pieces[i].position = 12;
		}


	}
}
void turnDp(){

	for (int i = 0; i < 54; i++){


		if (pieces[i].position == 16){
			pieces[i].position = 43;
		}
		else if (pieces[i].position == 17){
			pieces[i].position = 44;
		}
		else if (pieces[i].position == 18){
			pieces[i].position = 45;
		}
		else if (pieces[i].position == 25){
			pieces[i].position = 16;
		}
		else if (pieces[i].position == 26){
			pieces[i].position = 17;
		}
		else if (pieces[i].position == 27){
			pieces[i].position = 18;
		}
		else if (pieces[i].position == 34){
			pieces[i].position = 25;
		}
		else if (pieces[i].position == 35){
			pieces[i].position = 26;
		}
		else if (pieces[i].position == 36){
			pieces[i].position = 27;
		}
		else if (pieces[i].position == 43){
			pieces[i].position = 34;
		}
		else if (pieces[i].position == 44){
			pieces[i].position = 35;
		}
		else if (pieces[i].position == 45){
			pieces[i].position = 36;
		}
		else if (pieces[i].position == 46){
			pieces[i].position = 52;
		}
		else if (pieces[i].position == 47){
			pieces[i].position = 49;
		}
		else if (pieces[i].position == 48){
			pieces[i].position = 46;
		}
		else if (pieces[i].position == 49){
			pieces[i].position = 53;
		}
		else if (pieces[i].position == 50){
			pieces[i].position = 50;
		}
		else if (pieces[i].position == 51){
			pieces[i].position = 47;
		}
		else if (pieces[i].position == 52){
			pieces[i].position = 54;
		}
		else if (pieces[i].position == 53){
			pieces[i].position = 51;
		}
		else if (pieces[i].position == 54){
			pieces[i].position = 48;
		}


	}

}
void turnFp(){

	for (int i = 0; i < 54; i++){


		if (pieces[i].position == 7){
			pieces[i].position = 45;
		}
		else if (pieces[i].position == 8){
			pieces[i].position = 42;
		}
		else if (pieces[i].position == 9){
			pieces[i].position = 39;
		}
		else if (pieces[i].position == 19){
			pieces[i].position = 7;
		}
		else if (pieces[i].position == 22){
			pieces[i].position = 8;
		}
		else if (pieces[i].position == 25){
			pieces[i].position = 9;
		}
		else if (pieces[i].position == 48){
			pieces[i].position = 19;
		}
		else if (pieces[i].position == 47){
			pieces[i].position = 22;
		}
		else if (pieces[i].position == 46){
			pieces[i].position = 25;
		}
		else if (pieces[i].position == 45){
			pieces[i].position = 48;
		}
		else if (pieces[i].position == 42){
			pieces[i].position = 47;
		}
		else if (pieces[i].position == 39){
			pieces[i].position = 46;
		}
		else if (pieces[i].position == 10){
			pieces[i].position = 16;
		}
		else if (pieces[i].position == 11){
			pieces[i].position = 13;
		}
		else if (pieces[i].position == 12){
			pieces[i].position = 10;
		}
		else if (pieces[i].position == 13){
			pieces[i].position = 17;
		}
		else if (pieces[i].position == 14){
			pieces[i].position = 14;
		}
		else if (pieces[i].position == 15){
			pieces[i].position = 11;
		}
		else if (pieces[i].position == 16){
			pieces[i].position = 18;
		}
		else if (pieces[i].position == 17){
			pieces[i].position = 15;
		}
		else if (pieces[i].position == 18){
			pieces[i].position = 12;
		}


	}

}
void turnBp(){

	for (int i = 0; i < 54; i++){


		if (pieces[i].position == 1){
			pieces[i].position = 21;
		}
		else if (pieces[i].position == 2){
			pieces[i].position = 24;
		}
		else if (pieces[i].position == 3){
			pieces[i].position = 27;
		}
		else if (pieces[i].position == 21){
			pieces[i].position = 54;
		}
		else if (pieces[i].position == 24){
			pieces[i].position = 53;
		}
		else if (pieces[i].position == 27){
			pieces[i].position = 52;
		}
		else if (pieces[i].position == 54){
			pieces[i].position = 43;
		}
		else if (pieces[i].position == 53){
			pieces[i].position = 40;
		}
		else if (pieces[i].position == 52){
			pieces[i].position = 37;
		}
		else if (pieces[i].position == 37){
			pieces[i].position = 3;
		}
		else if (pieces[i].position == 40){
			pieces[i].position = 2;
		}
		else if (pieces[i].position == 43){
			pieces[i].position = 1;
		}
		else if (pieces[i].position == 28){
			pieces[i].position = 34;
		}
		else if (pieces[i].position == 29){
			pieces[i].position = 31;
		}
		else if (pieces[i].position == 30){
			pieces[i].position = 28;
		}
		else if (pieces[i].position == 31){
			pieces[i].position = 35;
		}
		else if (pieces[i].position == 32){
			pieces[i].position = 32;
		}
		else if (pieces[i].position == 33){
			pieces[i].position = 29;
		}
		else if (pieces[i].position == 34){
			pieces[i].position = 36;
		}
		else if (pieces[i].position == 35){
			pieces[i].position = 33;
		}
		else if (pieces[i].position == 36){
			pieces[i].position = 30;
		}


	}

}
void turnMp(){

	for (int i = 0; i < 54; i++){

		if (pieces[i].position == 2){
			pieces[i].position = 35;
		}
		else if (pieces[i].position == 5){
			pieces[i].position = 32;
		}
		else if (pieces[i].position == 8){
			pieces[i].position = 29;
		}
		else if (pieces[i].position == 11){
			pieces[i].position = 2;
		}
		else if (pieces[i].position == 14){
			pieces[i].position = 5;
		}
		else if (pieces[i].position == 17){
			pieces[i].position = 8;
		}
		else if (pieces[i].position == 47){
			pieces[i].position = 11;
		}
		else if (pieces[i].position == 50){
			pieces[i].position = 14;
		}
		else if (pieces[i].position == 53){
			pieces[i].position = 17;
		}
		else if (pieces[i].position == 35){
			pieces[i].position = 47;
		}
		else if (pieces[i].position == 32){
			pieces[i].position = 50;
		}
		else if (pieces[i].position == 29){
			pieces[i].position = 53;
		}

	}
}
void rotateXp(){
	for (int i = 0; i < 54; i++){


		if (pieces[i].position == 1){
			pieces[i].position = 10;
		}
		else if (pieces[i].position == 4){
			pieces[i].position = 13;
		}
		else if (pieces[i].position == 7){
			pieces[i].position = 16;
		}
		else if (pieces[i].position == 10){
			pieces[i].position = 46;
		}
		else if (pieces[i].position == 13){
			pieces[i].position = 49;
		}
		else if (pieces[i].position == 16){
			pieces[i].position = 52;
		}
		else if (pieces[i].position == 46){
			pieces[i].position = 36;
		}
		else if (pieces[i].position == 49){
			pieces[i].position = 33;
		}
		else if (pieces[i].position == 52){
			pieces[i].position = 30;
		}
		else if (pieces[i].position == 30){
			pieces[i].position = 7;
		}
		else if (pieces[i].position == 33){
			pieces[i].position = 4;
		}
		else if (pieces[i].position == 36){
			pieces[i].position = 1;
		}
		else if (pieces[i].position == 37){
			pieces[i].position = 39;
		}
		else if (pieces[i].position == 38){
			pieces[i].position = 42;
		}
		else if (pieces[i].position == 39){
			pieces[i].position = 45;
		}
		else if (pieces[i].position == 40){
			pieces[i].position = 38;
		}
		else if (pieces[i].position == 41){
			pieces[i].position = 41;
		}
		else if (pieces[i].position == 42){
			pieces[i].position = 44;
		}
		else if (pieces[i].position == 43){
			pieces[i].position = 37;
		}
		else if (pieces[i].position == 44){
			pieces[i].position = 40;
		}
		else if (pieces[i].position == 45){
			pieces[i].position = 43;
		}
		else if (pieces[i].position == 3){
			pieces[i].position = 12;
		}
		else if (pieces[i].position == 6){
			pieces[i].position = 15;
		}
		else if (pieces[i].position == 9){
			pieces[i].position = 18;
		}
		else if (pieces[i].position == 12){
			pieces[i].position = 48;
		}
		else if (pieces[i].position == 15){
			pieces[i].position = 51;
		}
		else if (pieces[i].position == 18){
			pieces[i].position = 54;
		}
		else if (pieces[i].position == 48){
			pieces[i].position = 34;
		}
		else if (pieces[i].position == 51){
			pieces[i].position = 31;
		}
		else if (pieces[i].position == 54){
			pieces[i].position = 28;
		}
		else if (pieces[i].position == 28){
			pieces[i].position = 9;
		}
		else if (pieces[i].position == 31){
			pieces[i].position = 6;
		}
		else if (pieces[i].position == 34){
			pieces[i].position = 3;
		}
		else if (pieces[i].position == 19){
			pieces[i].position = 25;
		}
		else if (pieces[i].position == 20){
			pieces[i].position = 22;
		}
		else if (pieces[i].position == 21){
			pieces[i].position = 19;
		}
		else if (pieces[i].position == 22){
			pieces[i].position = 26;
		}
		else if (pieces[i].position == 23){
			pieces[i].position = 23;
		}
		else if (pieces[i].position == 24){
			pieces[i].position = 20;
		}
		else if (pieces[i].position == 25){
			pieces[i].position = 27;
		}
		else if (pieces[i].position == 26){
			pieces[i].position = 24;
		}
		else if (pieces[i].position == 27){
			pieces[i].position = 21;
		}
		if (pieces[i].position == 2){
			pieces[i].position = 11;
		}
		else if (pieces[i].position == 5){
			pieces[i].position = 14;
		}
		else if (pieces[i].position == 8){
			pieces[i].position = 17;
		}
		else if (pieces[i].position == 11){
			pieces[i].position = 47;
		}
		else if (pieces[i].position == 14){
			pieces[i].position = 50;
		}
		else if (pieces[i].position == 17){
			pieces[i].position = 53;
		}
		else if (pieces[i].position == 47){
			pieces[i].position = 35;
		}
		else if (pieces[i].position == 50){
			pieces[i].position = 32;
		}
		else if (pieces[i].position == 53){
			pieces[i].position = 29;
		}
		else if (pieces[i].position == 35){
			pieces[i].position = 2;
		}
		else if (pieces[i].position == 32){
			pieces[i].position = 5;
		}
		else if (pieces[i].position == 29){
			pieces[i].position = 8;
		}
	}
}
void rotateYp(){

	for (int i = 0; i < 54; i++){


		if (pieces[i].position == 16){
			pieces[i].position = 25;
		}
		else if (pieces[i].position == 17){
			pieces[i].position = 26;
		}
		else if (pieces[i].position == 18){
			pieces[i].position = 27;
		}
		else if (pieces[i].position == 25){
			pieces[i].position = 34;
		}
		else if (pieces[i].position == 26){
			pieces[i].position = 35;
		}
		else if (pieces[i].position == 27){
			pieces[i].position = 36;
		}
		else if (pieces[i].position == 34){
			pieces[i].position = 43;
		}
		else if (pieces[i].position == 35){
			pieces[i].position = 44;
		}
		else if (pieces[i].position == 36){
			pieces[i].position = 45;
		}
		else if (pieces[i].position == 43){
			pieces[i].position = 16;
		}
		else if (pieces[i].position == 44){
			pieces[i].position = 17;
		}
		else if (pieces[i].position == 45){
			pieces[i].position = 18;
		}
		else if (pieces[i].position == 46){
			pieces[i].position = 48;
		}
		else if (pieces[i].position == 47){
			pieces[i].position = 51;
		}
		else if (pieces[i].position == 48){
			pieces[i].position = 54;
		}
		else if (pieces[i].position == 49){
			pieces[i].position = 47;
		}
		else if (pieces[i].position == 50){
			pieces[i].position = 50;
		}
		else if (pieces[i].position == 51){
			pieces[i].position = 53;
		}
		else if (pieces[i].position == 52){
			pieces[i].position = 46;
		}
		else if (pieces[i].position == 53){
			pieces[i].position = 49;
		}
		else if (pieces[i].position == 54){
			pieces[i].position = 52;
		}
		else if (pieces[i].position == 1){
			pieces[i].position = 7;
		}
		else if (pieces[i].position == 2){
			pieces[i].position = 4;
		}
		else if (pieces[i].position == 3){
			pieces[i].position = 1;
		}
		else if (pieces[i].position == 4){
			pieces[i].position = 8;
		}
		else if (pieces[i].position == 5){
			pieces[i].position = 5;
		}
		else if (pieces[i].position == 6){
			pieces[i].position = 2;
		}
		else if (pieces[i].position == 7){
			pieces[i].position = 9;
		}
		else if (pieces[i].position == 8){
			pieces[i].position = 6;
		}
		else if (pieces[i].position == 9){
			pieces[i].position = 3;
		}
		else if (pieces[i].position == 10){
			pieces[i].position = 19;
		}
		else if (pieces[i].position == 11){
			pieces[i].position = 20;
		}
		else if (pieces[i].position == 12){
			pieces[i].position = 21;
		}
		else if (pieces[i].position == 19){
			pieces[i].position = 28;
		}
		else if (pieces[i].position == 20){
			pieces[i].position = 29;
		}
		else if (pieces[i].position == 21){
			pieces[i].position = 30;
		}
		else if (pieces[i].position == 28){
			pieces[i].position = 37;
		}
		else if (pieces[i].position == 29){
			pieces[i].position = 38;
		}
		else if (pieces[i].position == 30){
			pieces[i].position = 39;
		}
		else if (pieces[i].position == 37){
			pieces[i].position = 10;
		}
		else if (pieces[i].position == 38){
			pieces[i].position = 11;
		}
		else if (pieces[i].position == 39){
			pieces[i].position = 12;
		}
		else if (pieces[i].position == 13){
			pieces[i].position = 22;
		}
		else if (pieces[i].position == 14){
			pieces[i].position = 23;
		}
		else if (pieces[i].position == 15){
			pieces[i].position = 24;
		}
		else if (pieces[i].position == 22){
			pieces[i].position = 31;
		}
		else if (pieces[i].position == 23){
			pieces[i].position = 32;
		}
		else if (pieces[i].position == 24){
			pieces[i].position = 33;
		}
		else if (pieces[i].position == 31){
			pieces[i].position = 40;
		}
		else if (pieces[i].position == 32){
			pieces[i].position = 41;
		}
		else if (pieces[i].position == 33){
			pieces[i].position = 42;
		}
		else if (pieces[i].position == 40){
			pieces[i].position = 13;
		}
		else if (pieces[i].position == 41){
			pieces[i].position = 14;
		}
		else if (pieces[i].position == 42){
			pieces[i].position = 15;
		}
	}

}
void rotateZp(){

	for (int i = 0; i < 54; i++){


		if (pieces[i].position == 7){
			pieces[i].position = 45;
		}
		else if (pieces[i].position == 8){
			pieces[i].position = 42;
		}
		else if (pieces[i].position == 9){
			pieces[i].position = 39;
		}
		else if (pieces[i].position == 19){
			pieces[i].position = 7;
		}
		else if (pieces[i].position == 22){
			pieces[i].position = 8;
		}
		else if (pieces[i].position == 25){
			pieces[i].position = 9;
		}
		else if (pieces[i].position == 48){
			pieces[i].position = 19;
		}
		else if (pieces[i].position == 47){
			pieces[i].position = 22;
		}
		else if (pieces[i].position == 46){
			pieces[i].position = 25;
		}
		else if (pieces[i].position == 45){
			pieces[i].position = 48;
		}
		else if (pieces[i].position == 42){
			pieces[i].position = 47;
		}
		else if (pieces[i].position == 39){
			pieces[i].position = 46;
		}
		else if (pieces[i].position == 10){
			pieces[i].position = 16;
		}
		else if (pieces[i].position == 11){
			pieces[i].position = 13;
		}
		else if (pieces[i].position == 12){
			pieces[i].position = 10;
		}
		else if (pieces[i].position == 13){
			pieces[i].position = 17;
		}
		else if (pieces[i].position == 14){
			pieces[i].position = 14;
		}
		else if (pieces[i].position == 15){
			pieces[i].position = 11;
		}
		else if (pieces[i].position == 16){
			pieces[i].position = 18;
		}
		else if (pieces[i].position == 17){
			pieces[i].position = 15;
		}
		else if (pieces[i].position == 18){
			pieces[i].position = 12;
		}

		else if (pieces[i].position == 1){
			pieces[i].position = 43;
		}
		else if (pieces[i].position == 2){
			pieces[i].position = 40;
		}
		else if (pieces[i].position == 3){
			pieces[i].position = 37;
		}
		else if (pieces[i].position == 21){
			pieces[i].position = 1;
		}
		else if (pieces[i].position == 24){
			pieces[i].position = 2;
		}
		else if (pieces[i].position == 27){
			pieces[i].position = 3;
		}
		else if (pieces[i].position == 54){
			pieces[i].position = 21;
		}
		else if (pieces[i].position == 53){
			pieces[i].position = 24;
		}
		else if (pieces[i].position == 52){
			pieces[i].position = 27;
		}
		else if (pieces[i].position == 37){
			pieces[i].position = 52;
		}
		else if (pieces[i].position == 40){
			pieces[i].position = 53;
		}
		else if (pieces[i].position == 43){
			pieces[i].position = 54;
		}
		else if (pieces[i].position == 28){
			pieces[i].position = 30;
		}
		else if (pieces[i].position == 29){
			pieces[i].position = 33;
		}
		else if (pieces[i].position == 30){
			pieces[i].position = 36;
		}
		else if (pieces[i].position == 31){
			pieces[i].position = 29;
		}
		else if (pieces[i].position == 32){
			pieces[i].position = 32;
		}
		else if (pieces[i].position == 33){
			pieces[i].position = 35;
		}
		else if (pieces[i].position == 34){
			pieces[i].position = 28;
		}
		else if (pieces[i].position == 35){
			pieces[i].position = 31;
		}
		else if (pieces[i].position == 36){
			pieces[i].position = 34;
		}
		else if (pieces[i].position == 4){
			pieces[i].position = 44;
		}
		else if (pieces[i].position == 5){
			pieces[i].position = 41;
		}
		else if (pieces[i].position == 6){
			pieces[i].position = 38;
		}
		else if (pieces[i].position == 20){
			pieces[i].position = 4;
		}
		else if (pieces[i].position == 23){
			pieces[i].position = 5;
		}
		else if (pieces[i].position == 26){
			pieces[i].position = 6;
		}
		else if (pieces[i].position == 49){
			pieces[i].position = 26;
		}
		else if (pieces[i].position == 50){
			pieces[i].position = 23;
		}
		else if (pieces[i].position == 51){
			pieces[i].position = 20;
		}
		else if (pieces[i].position == 44){
			pieces[i].position = 51;
		}
		else if (pieces[i].position == 41){
			pieces[i].position = 50;
		}
		else if (pieces[i].position == 38){
			pieces[i].position = 49;
		}
	}

}

void scramble(){
//randomly generates a unmber 50 times and each number corresponds to a different move
	for (int i = 0; i < 50; i++){

		int random;

		

		random = getRand();

		switch (random){

		case 1:
			turnU();
			break;
		case 2:
			turnR();
			break;
		case 3:
			turnB();
			break;
		case 4:
			turnL();
			break;
		case 5:
			turnF();
			break;
		case 6:
			turnD();
			break;
		case 7:
			rotateX();
			break;
		case 8:
			rotateY();
			break;
		case 9:
			rotateZ();
			break;
		case 10:
			turnM();
			break;
		case 11:
			turnUp();
			break;
		case 12:
			turnFp();
			break;
		case 13:
			turnRp();
			break;
		case 14:
			turnBp();
			break;
		case 15:
			turnLp();
			break;
		case 16:
			turnDp();
			break;
		case 17:
			rotateXp();
			break;
		case 18:
			rotateYp();
			break;
		case 19:
			rotateZp();
			break;
		case 20:
			turnMp();
			break;


		}
	}
}



int getRand() { 
	if (i == 100) 
		i = 0; 
	int rands[100]; 
	srand((unsigned)time(0)); 
	for (int index = 0; 
		index<100; index++) 
	{ rands[index] = (rand() % 20) + 1; }
	i++; 
	int n = rands[i]; 
	return n; 
}


void solvedDisplay(){
	//display "SOLVED"
	print(-.9, 0, 0, "SOLVED! Play Again? (Y/N)");
	glutKeyboardFunc(playagain);
}

//default code for printing text
void print(int x, int y, int z, std::string str)
{
	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);
	//get the length of the string to display
	int len = (int) str.size();

	//loop to display character by character
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}
	glFlush();
};


void playagain(unsigned char key, int xmouse, int ymouse){
	//same idea as with the original play function, but just two options
	if (key == 'y'){
		glutHideWindow();
	}

	if (key == 'n'){
		glutLeaveMainLoop();
	}
}
