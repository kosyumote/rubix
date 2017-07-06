#include "cube.hpp"
#include <string>

#include <GL/glew.h>
#include <GL/freeglut.h>

Cube qb; // this will hold all the state of the cube, and will be the only(!!) global varialbe




void print(int x, int y, std::string str)
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


///////////////////////// SOLVED WINDOW CALLBACKS ///////////////////////////////


void playagain(unsigned char key, int, int){ // the int's are to match the signature that glutKeyboardFunc expects - those are for the mouse coordinates, which we don't care about
    //same idea as with the original play function, but just two options
    if (key == 'y'){
	glutHideWindow();
    }

    if (key == 'n'){
	glutLeaveMainLoop();
    }
}

void solvedDisplay(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //display "SOLVED"
    print(-.9, 0, "SOLVED! Play Again? (Y/N)");
    glutKeyboardFunc(playagain); // technically this isn't the right place to do it, but w/e
}

///////////////////////////////////////////////////////////////////////////////////


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-1.5f, -1.5f, -7.0f);

    
    for(auto const& sticker : *(qb.getStickers())) // getStickers returns a pointer to a std::vector, this construction loops over the elements in the dereferenced vector
    {
	glColor3f(sticker.red, sticker.green, sticker.blue);

	glBegin(GL_QUADS);
	for(int i = 0; i < 4; ++i)
	{
	    glVertex3f(sticker.square[i][0], sticker.square[i][1], sticker.square[i][2]);
	}
	glEnd();

	
	glColor3f(0.0f, 0.0f, 0.0f);

	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < 4; ++i)
	{
	    glVertex3f(sticker.square[i][0], sticker.square[i][1], sticker.square[i][2]);
	}
	glEnd();
    }

    glFlush();
}

void play(unsigned char key, int, int)
{
    switch(key)
    {
    case 'j':
	qb.turn(Cube::U, Cube::CW);
	break;
    case 'f':
	qb.turn(Cube::U, Cube::CCW);
	break;
	
    case 'i':
	qb.turn(Cube::R, Cube::CW);
	break;
    case 'k':
	qb.turn(Cube::R, Cube::CCW);
	break;
	
    case 'd':
	qb.turn(Cube::L, Cube::CW);
	break;
    case 'e':
	qb.turn(Cube::L, Cube::CCW);
	break;
	
    case 'h':
	qb.turn(Cube::F, Cube::CW);
	break;
    case 'g':
	qb.turn(Cube::F, Cube::CCW);
	break;
    case 'w':
	qb.turn(Cube::B, Cube::CW);
	break;
    case 'o':
	qb.turn(Cube::B, Cube::CCW);
	break;
	
    case 's':
	qb.turn(Cube::D, Cube::CW);
	break;
    case 'l':
	qb.turn(Cube::D, Cube::CCW);
	break;

	/* we won't include this for now, as it's not really a turn, but rather two turns and a rotate, from the perspective of the cube
    case 'x':
	qb.turn(Cube::M, Cube::CW);
	break;
    case '.':
	qb.turn(Cube::M, Cube::CCW);
	break;	
	*/


    case 'y':
    case 't':
	qb.rotate(Cube::X, Cube::CW);
	break;
    case 'n':
    case 'b':
	qb.rotate(Cube::X, Cube::CCW);
	break;
	
    case ';':
	qb.rotate(Cube::Y, Cube::CW);
	break;
    case 'a':
	qb.rotate(Cube::Y, Cube::CCW);
	break;

    case 'p':
	qb.rotate(Cube::Z, Cube::CW);
	break;
    case 'q':
	qb.rotate(Cube::Z, Cube::CCW);
	break;


    case '-':
	qb.scramble();
	break;

	// if it's not one of the above key presses, just return
    default:
	return;

    }


    if(qb.isSolved())
    {
	glutInitWindowSize(100, 100);
	glutInitWindowPosition(50, 50);
			
	glutCreateWindow("Solved");
	glutDisplayFunc(solvedDisplay);
    }
    
}

int main(int argc, char** argv)
{
    // set up cube
    // note that qb gets constructed since it's a global variable, so even if we don't reset, it would still be fine - this is just here so we remember that we have a qb guy
    qb.reset();

    // glut setup
    glutInit(&argc, argv); // ugh glut
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // these are bitwise OR'd, as is a common standard

    // window initialization stuff
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Rubix");
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    

    // callback to deal with keypresses
    glutKeyboardFunc(play);
    
    // also a callback
    glutDisplayFunc(display);

    // this starts the loop that does the callbacks when needed
    glutMainLoop();


    return 0;
}
