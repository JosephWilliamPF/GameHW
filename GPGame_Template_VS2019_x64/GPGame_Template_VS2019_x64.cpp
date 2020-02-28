// Simplified Renderer application for GP course
// Features:
// Reduced OpenGL version from 4.5 to 3.3 to allow it to render in older laptops.
// Added Shapes library for rendering cubes, spheres and vectors.
// Added examples of matrix multiplication on Update.
// Added resize screen and keyboard callbacks.
// Added FPS camera functionality
// Update 2019/01 updated libraries and created project for VS2017 including directory dependant links to libraries.
// Update 2020/01 updated libraries for x64 and for VS2020, also adding MAC compiled Libraries.

// Suggestions or extra help please do email me at S.Padilla@hw.ac.uk

// Standard C++ libraries
#include <iostream>
#include <vector>
using namespace std;

// Helper graphic libraries
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "graphics.h"
#include "shapes.h"

// MAIN FUNCTIONS
void startup();
void updateCamera();
void updateSceneElements();
void renderScene();

// CALLBACK FUNCTIONS
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void onMouseMoveCallback(GLFWwindow* window, double x, double y);
void onMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset);

// VARIABLES
bool        quit = false;
float       deltaTime = 0.0f;    // Keep track of time per frame.
float       lastTime = 0.0f;    // variable to keep overall time.
bool        keyStatus[1024];    // Hold key status.
bool		mouseEnabled = true; // keep track of mouse toggle.






// MAIN GRAPHICS OBJECT
Graphics    myGraphics;        // Runing all the graphics in this object 

/*----------------------DEMO OBJECTS---------------------*/
Arrow       arrowX;
Arrow       arrowY;
Arrow       arrowZ;
Cube        myFloor;
Line        myLine;
Cylinder    myCylinder;
/*-------------------------------------------------------*/

/*-------------------------CROWD-------------------------*/

Cube        myC5;
Cube		myC6;
Cube		myC7;
Cube		myC8;
Cube		myC9;
/*-------------------------------------------------------*/


/*-----------------------LABYRINTH-----------------------*/
Cube        myC1;
Cube		myC2;
Cube        myC3;
Cube        myC4;
/*-------------------------------------------------------*/

/*----------------------MAGIC_SPHERE---------------------*/
Sphere		myS[9][9][9];

int			Sx[9];
int			Sy[9];
int			Sz[9];

float		LenghtX;
float		LenghtY;
float		LenghtZ;
/*-------------------------------------------------------*/

/*------------------------PHYSICS-------------------------*/
//the masse is equal to 1kg​
//te size of the cube is 1m^3​
// The rotor value is k = 1​


Sphere      mySphere;

float m = 1.0f;
float k = 1.3f;

float Cx = 0.0f;
float Cy = 10.0f;
float Cz = 0.0f;

float g = 0.0000000067;
float D_sphere = 0.9f; //Non Deformation de la sphere​
float speed_up = 0.0f;
float speed_down = 0.0f;
float speed = 0.0f;
float h;
float S = 1.0f;
float key = 0.0f;
float h_seuil = Cy / 3 * k;
int i;
int nb_boid;
int a = 0;
int b = 0;
float x;

float cube_x  = 12.0f;
float cube_y  = 0.5f;
float cube_z  = 0.0f;
float cube_x2 = 13.0f;
float cube_y2 = 0.5f;
float cube_z2 = 0.0f;

/*-------------------------------------------------------*/





// Some global variable to do the animation.
float t = 0.001f;            // Global variable for animation


int main()
{
	int errorGraphics = myGraphics.Init();			// Launch window and graphics context
	if (errorGraphics) return 0;					// Close if something went wrong...

	startup();										// Setup all necessary information for startup (aka. load texture, shaders, models, etc).



	// MAIN LOOP run until the window is closed
	while (!quit) {

		// Update the camera transform based on interactive inputs or by following a predifined path.
		updateCamera();

		// Update position, orientations and any other relevant visual state of any dynamic elements in the scene.
		updateSceneElements();

		// Render a still frame into an off-screen frame buffer known as the backbuffer.
		renderScene();

		// Swap the back buffer with the front buffer, making the most recently rendered image visible on-screen.
		glfwSwapBuffers(myGraphics.window);        // swap buffers (avoid flickering and tearing)

	}


	myGraphics.endProgram();            // Close and clean everything up...

   // cout << "\nPress any key to continue...\n";
   // cin.ignore(); cin.get(); // delay closing console to read debugging errors.

	return 0;
}

void startup() {
	// Keep track of the running time
	GLfloat currentTime = (GLfloat)glfwGetTime();    // retrieve timelapse
	deltaTime = currentTime;                        // start delta time
	lastTime = currentTime;                            // Save for next frame calculations.

	// Callback graphics and key update functions - declared in main to avoid scoping complexity.
	// More information here : https://www.glfw.org/docs/latest/input_guide.html
	glfwSetWindowSizeCallback(myGraphics.window, onResizeCallback);            // Set callback for resize
	glfwSetKeyCallback(myGraphics.window, onKeyCallback);                    // Set Callback for keys
	glfwSetMouseButtonCallback(myGraphics.window, onMouseButtonCallback);    // Set callback for mouse click
	glfwSetCursorPosCallback(myGraphics.window, onMouseMoveCallback);        // Set callback for mouse move
	glfwSetScrollCallback(myGraphics.window, onMouseWheelCallback);            // Set callback for mouse wheel.

	// Calculate proj_matrix for the first time.
	myGraphics.aspect = (float)myGraphics.windowWidth / (float)myGraphics.windowHeight;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);

	// Load Geometry examples

	// colors : https://gist.github.com/romsalva/7324210

	// Optimised Graphics
	myGraphics.SetOptimisations();        // Cull and depth testing

	/*----------------------DEMO OBJECTS---------------------*/
	arrowX.Load(); arrowY.Load(); arrowZ.Load();
	arrowX.fillColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); arrowX.lineColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	arrowY.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); arrowY.lineColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	arrowZ.fillColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); arrowZ.lineColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	myFloor.Load();
	myFloor.fillColor = glm::vec4(130.0f / 255.0f, 96.0f / 255.0f, 61.0f / 255.0f, 1.0f);    // Sand Colour
	myFloor.lineColor = glm::vec4(130.0f / 255.0f, 96.0f / 255.0f, 61.0f / 255.0f, 1.0f);    // Sand again

	myCylinder.Load();
	myCylinder.fillColor = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
	myCylinder.lineColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	myLine.Load();
	myLine.fillColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	myLine.lineColor = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	myLine.lineWidth = 5.0f;
	/*-------------------------------------------------------*/

	/*-----------------------LABYRINTH-----------------------*/
	myC1.Load();
	myC1.fillColor = glm::vec4(0.96f, 0.55f, 0.33f, 1.0F);

	myC2.Load();
	myC2.fillColor = glm::vec4(0.96f, 0.55f, 0.33f, 1.0f);

	myC3.Load();
	myC3.fillColor = glm::vec4(0.96f, 0.55f, 0.33f, 1.0f);

	myC4.Load();
	myC4.fillColor = glm::vec4(0.96f, 0.55f, 0.33f, 1.0f);
	/*-------------------------------------------------------*/

	/*----------------------MAGIC_SPHERE---------------------
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				myS[i][j][k].Load();
				Sx[i] = i / 2;
				Sy[j] = j / 2;
				Sz[k] = k / 2;
			}
		}
	}

	LenghtX = Sx[8] - Sx[0];
	LenghtY = Sy[8] - Sy[0];
	LenghtZ = Sz[8] - Sz[0];
	-------------------------------------------------------*/

	
	/*-------------------------CROWD-------------------------*/
	myC5.Load();
	myC6.Load();
	myC7.Load();
	myC8.Load();
	myC9.Load();
	/*-------------------------------------------------------*/



	/*------------------------PHYSICS-------------------------*/
	
	mySphere.Load();
	mySphere.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	/*-------------------------------------------------------*/

}

void updateCamera() {

	// calculate movement for FPS camera
	GLfloat xoffset = myGraphics.mouseX - myGraphics.cameraLastX;
	GLfloat yoffset = myGraphics.cameraLastY - myGraphics.mouseY;    // Reversed mouse movement
	myGraphics.cameraLastX = (GLfloat)myGraphics.mouseX;
	myGraphics.cameraLastY = (GLfloat)myGraphics.mouseY;

	GLfloat sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	myGraphics.cameraYaw += xoffset;
	myGraphics.cameraPitch += yoffset;

	// check for pitch out of bounds otherwise screen gets flipped
	if (myGraphics.cameraPitch > 89.0f) myGraphics.cameraPitch = 89.0f;
	if (myGraphics.cameraPitch < -89.0f) myGraphics.cameraPitch = -89.0f;

	// Calculating FPS camera movement (See 'Additional Reading: Yaw and Pitch to Vector Calculations' in VISION)
	glm::vec3 front;
	front.x = cos(glm::radians(myGraphics.cameraYaw)) * cos(glm::radians(myGraphics.cameraPitch));
	front.y = sin(glm::radians(myGraphics.cameraPitch));
	front.z = sin(glm::radians(myGraphics.cameraYaw)) * cos(glm::radians(myGraphics.cameraPitch));

	myGraphics.cameraFront = glm::normalize(front);

	// Update movement using the keys
	GLfloat cameraSpeed = 10.0f * deltaTime;
	if (keyStatus[GLFW_KEY_W]) myGraphics.cameraPosition += cameraSpeed * myGraphics.cameraFront;
	if (keyStatus[GLFW_KEY_S]) myGraphics.cameraPosition -= cameraSpeed * myGraphics.cameraFront;
	if (keyStatus[GLFW_KEY_A]) myGraphics.cameraPosition -= glm::normalize(glm::cross(myGraphics.cameraFront, myGraphics.cameraUp)) * cameraSpeed;
	if (keyStatus[GLFW_KEY_D]) myGraphics.cameraPosition += glm::normalize(glm::cross(myGraphics.cameraFront, myGraphics.cameraUp)) * cameraSpeed;

	// IMPORTANT PART
	// Calculate my view matrix using the lookAt helper function
	if (mouseEnabled) {
		myGraphics.viewMatrix = glm::lookAt(myGraphics.cameraPosition,			// eye
			myGraphics.cameraPosition + myGraphics.cameraFront,					// centre
			myGraphics.cameraUp);												// up
	}
}

/*--------------------------MATHS-------------------------*/
float dieu(float min, float max)
{

	float azar;
	azar = (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
	return azar;
}


int god(int min, int max)
{
	int azar;
	azar = std::rand() % (max - min) + min + 1;
	return azar;
}


int godz(int min, int max)
{

	int azar;
	azar = std::rand() % (max - min) + min + 1;
	return azar;
}

/*--------------------------------------------------------*/

/*------------------------PHYSICS-------------------------*/
void Fall() {

	// Somme de Fext = m.a d ou vu que l on est dans le vide m.a = m.g soit: a = g​
	h = Cy;
	speed = sqrt(2 * g * h);
	/*-----------state 1: GO DOWN*/
	if (Cy > 0.5f && a % 2 == 0 && a != 4200000) { speed = speed + g; Cy = Cy - speed * t; S = 1.0f; }
	/*-----------state 2: SPEED = 0*/
	if (Cy <= 0.5f && a % 2 == 0 && a != 4200000) { a = a + 1;   S = S * speed + D_sphere; speed = 0.0f; }
	/*-----------state 3: GO UP*/
	if (Cy <= h_seuil && a % 2 != 0 && a != 4200000) { speed = speed - 3 * g; Cy = Cy + speed * t; }
	/*-----------state 4: SPEED = 0*/
	if (Cy >= h_seuil && a % 2 != 0 && a != 4200000) { h_seuil = h_seuil / k; a = a * 2; speed = 0.0f; h = Cy; }

	/*-----------Avoid infinity while*/
	if (h_seuil <= 0.5f) { a = 4200000; speed = 0.0f; S = 1.0f; Cy = 0.5f; }
}
/*-------------------------------------------------------*/


/*-------------------------CROWD-------------------------*/


void Position_C1() {
	//int signe; // 1 = avance, 0 egale recule​
	float p1 = 0.0f;
	float p2 = 0.0f;
	int coin = 0;
	int coin_z = 0;
	coin_z = godz(1, 100);
	coin = god(1, 100);

	if (coin > 50) {
		//p1 = dieu(cube_x, 1.0f);​
		p1 = 0.1f;
		p2 = cube_x - p1;
		if (p2 < 24.0f && p2 > 2.0f && p2!=cube_x2) { cube_x = cube_x - p1 ; }
		else { (cube_x = cube_x + p1); }
	}

	if (coin <= 50) {
		//p1 = dieu(cube_x, 1.0f);​
		p1 = 0.1f;
		p2 = cube_x + p1;
		if (p2 < 24.0f && p2 > 2.0f && p2 != cube_x2) { cube_x = cube_x + p1 ; }
		else { (cube_x = cube_x - p1); }
	}

	

	if (coin_z > 50) {
		//p1 = dieu(cube_x, 1.0f);​
		p1 = 0.1f;
		p2 = cube_z - p1;
		if (p2 < 10.0f && p2 > -10.0f && p2 != cube_z2) { cube_z = cube_z - p1 ; }
		else { (cube_z = cube_z + p1); }
	}

	if (coin_z <= 50) {
		//p1 = dieu(cube_x, 1.0f);​
		p1 = 0.1f;
		p2 = cube_z + p1;
		if (p2 < 10.0f && p2 > -10.0f && p2 != cube_z2) {cube_z = cube_z + p1; }
		else { (cube_z = cube_z - p1); }
	}
}




void updateSceneElements() {

	glfwPollEvents();                                // poll callbacks

	// Calculate frame time/period -- used for all (physics, animation, logic, etc).
	GLfloat currentTime = (GLfloat)glfwGetTime();    // retrieve timelapse
	deltaTime = currentTime - lastTime;                // Calculate delta time
	lastTime = currentTime;                            // Save for next frame calculations.

	// Do not forget your ( T * R * S ) http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/

	if (keyStatus[GLFW_KEY_J]) { cube_x = cube_x + 0.001f; }
	if (keyStatus[GLFW_KEY_K]) { cube_x = cube_x - 0.001f; }
	if (keyStatus[GLFW_KEY_I]) { cube_z = cube_z - 0.001f; }
	if (keyStatus[GLFW_KEY_N]) { cube_z = cube_z + 0.001f; }
	if (keyStatus[GLFW_KEY_E]) { Position_C1(); }






	/*-------------------------CROWD-------------------------*/
	

	glm::mat4 mv_matrix_c5 =
		glm::translate(glm::vec3(cube_x, 0.5f, cube_z)) *
		glm::mat4(1.0f);
	myC5.mv_matrix = myGraphics.viewMatrix * mv_matrix_c5;
	myC5.proj_matrix = myGraphics.proj_matrix;


	glm::mat4 mv_matrix_c6 =
		glm::translate(glm::vec3(cube_x2 = cube_x - (1.0f + 1) + (((float)rand()) / (float)RAND_MAX) * (13.0f - (1.0f + 1)), 0.5f, cube_z2 = cube_z + 1.0f+ (1.0f + 1) + (((float)rand()) / (float)RAND_MAX) * (7.0f - (1.0f + 1))))*
		glm::mat4(1.0f);
	myC6.mv_matrix = myGraphics.viewMatrix * mv_matrix_c6;
	myC6.proj_matrix = myGraphics.proj_matrix;


	glm::mat4 mv_matrix_c7 =
		glm::translate(glm::vec3(cube_x2 = cube_x + ((1.0f + 1) + (((float)rand()) / (float)RAND_MAX) * (12.0f - (1.0f + 1))), 0.5f, cube_z2 = cube_z + 1.0f - (1.0f + 1) - (((float)rand()) / (float)RAND_MAX) * (7.0f - (1.0f + 1)))) *
		glm::mat4(1.0f);
	myC7.mv_matrix = myGraphics.viewMatrix * mv_matrix_c7;
	myC7.proj_matrix = myGraphics.proj_matrix;


	glm::mat4 mv_matrix_c8 =
		glm::translate(glm::vec3(cube_x2 = cube_x + ((3.0f + 1) + (((float)rand()) / (float)RAND_MAX) * (9.0f - (3.0f + 1))), 0.5f, cube_z2 = cube_z + 4.0f + ((2.0f + 1) + (((float)rand()) / (float)RAND_MAX) * (7.0f - (2.0f + 1))))) *
		glm::mat4(1.0f);
	myC8.mv_matrix = myGraphics.viewMatrix * mv_matrix_c8;
	myC8.proj_matrix = myGraphics.proj_matrix;



	glm::mat4 mv_matrix_c9 =
		glm::translate(glm::vec3(cube_x2 = cube_x - ((6.0f + 1) + (((float)rand()) / (float)RAND_MAX) * (9.0f - (6.0f + 1))), 0.5f, cube_z2 = cube_z + 4.0f - ((2.0f + 1) - (((float)rand()) / (float)RAND_MAX) * (7.0f - (2.0f + 1))))) *
		glm::mat4(1.0f);
	myC9.mv_matrix = myGraphics.viewMatrix * mv_matrix_c9;
	myC9.proj_matrix = myGraphics.proj_matrix;
	/*-------------------------------------------------------*/


	/*------------------------PHYSICS-------------------------*/
	Fall();
	// calculate Sphere movement​
	glm::mat4 mv_matrix_sphere =
		glm::translate(glm::vec3(Cx, Cy, Cz)) *
		//glm::rotate(-t, glm::vec3(0.0f, 1.0f, 0.0f)) *​
		//glm::rotate(-t, glm::vec3(0.0f, 0.0f, 1.0f)) *​
		glm::scale(glm::vec3(1.0f, S, 1.0f)) *
		glm::mat4(1.0f);
	mySphere.mv_matrix = myGraphics.viewMatrix * mv_matrix_sphere;
	mySphere.proj_matrix = myGraphics.proj_matrix;
	/*-------------------------------------------------------*/

/*----------------------DEMO OBJECTS---------------------*/
	//Calculate Arrows translations (note: arrow model points up)
	glm::mat4 mv_matrix_x =
		glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::scale(glm::vec3(0.2f, 0.5f, 0.2f)) *
		glm::mat4(1.0f);
	arrowX.mv_matrix = myGraphics.viewMatrix * mv_matrix_x;
	arrowX.proj_matrix = myGraphics.proj_matrix;

	glm::mat4 mv_matrix_y =
		glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)) *
		//glm::rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *    // already model pointing up
		glm::scale(glm::vec3(0.2f, 0.5f, 0.2f)) *
		glm::mat4(1.0f);
	arrowY.mv_matrix = myGraphics.viewMatrix * mv_matrix_y;
	arrowY.proj_matrix = myGraphics.proj_matrix;

	glm::mat4 mv_matrix_z =
		glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::scale(glm::vec3(0.2f, 0.5f, 0.2f)) *
		glm::mat4(1.0f);
	arrowZ.mv_matrix = myGraphics.viewMatrix * mv_matrix_z;
	arrowZ.proj_matrix = myGraphics.proj_matrix;

	// Calculate floor position and resize
	myFloor.mv_matrix = myGraphics.viewMatrix *
		glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)) *
		glm::scale(glm::vec3(1000.0f, 0.001f, 1000.0f)) *
		glm::mat4(1.0f);
	myFloor.proj_matrix = myGraphics.proj_matrix;

	// Calculate cylinder
	myCylinder.mv_matrix = myGraphics.viewMatrix *
		glm::translate(glm::vec3(-1.0f, 0.5f, 2.0f)) *
		glm::mat4(1.0f);
	myCylinder.proj_matrix = myGraphics.proj_matrix;

	// Calculate Line
	myLine.mv_matrix = myGraphics.viewMatrix *
		glm::translate(glm::vec3(1.0f, 0.5f, 2.0f)) *
		glm::mat4(1.0f);
	myLine.proj_matrix = myGraphics.proj_matrix;
/*-------------------------------------------------------*/


/*-----------------------LABYRINTH-----------------------*/
	glm::mat4 mv_matrix_c1 =
		glm::translate(glm::vec3(1.0f, 0.5f, 0.0f)) *
		glm::scale(glm::vec3(1.0f, 1.0f, 23.0f)) *
		glm::mat4(1.0f);
	myC1.mv_matrix = myGraphics.viewMatrix * mv_matrix_c1;
	myC1.proj_matrix = myGraphics.proj_matrix;

	glm::mat4 mv_matrix_c2 =
		glm::translate(glm::vec3(13.0f, 0.5f, -11.0f)) *
		glm::scale(glm::vec3(23.0f, 1.0f, 1.0f)) *
		glm::mat4(1.0f);
	myC2.mv_matrix = myGraphics.viewMatrix * mv_matrix_c2;
	myC2.proj_matrix = myGraphics.proj_matrix;

	glm::mat4 mv_matrix_c3 =
		glm::translate(glm::vec3(13.0f, 0.5f, 11.0f)) *
		glm::scale(glm::vec3(23.0f, 1.0f, 1.0f)) *
		glm::mat4(1.0f);
	myC3.mv_matrix = myGraphics.viewMatrix * mv_matrix_c3;
	myC3.proj_matrix = myGraphics.proj_matrix;

	glm::mat4 mv_matrix_c4 =
		glm::translate(glm::vec3(24.0f, 0.5f, 0.0f)) *
		glm::scale(glm::vec3(1.0f, 1.0f, 23.0f)) *
		glm::mat4(1.0f);
	myC4.mv_matrix = myGraphics.viewMatrix * mv_matrix_c4;
	myC4.proj_matrix = myGraphics.proj_matrix;
/*-------------------------------------------------------*/

	
/*----------------------MAGIC_SPHERE---------------------
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				glm::mat4 mv_matrix_s =
					glm::translate(glm::vec3(6.0f + 1.25 * i, 0.5f + 1.0f * j, 0.0f+ * k)) *
					glm::rotate(-t, glm::vec3(0.0f, 1.0f, 0.0f)) *
					glm::rotate(-t, glm::vec3(1.0f, 0.0f, 0.0f)) *
					glm::mat4(1.0f);
				myS[i][j][k].mv_matrix = myGraphics.viewMatrix * mv_matrix_s;
				myS[i][j][k].proj_matrix = myGraphics.proj_matrix;
			}
		}
	}
-------------------------------------------------------*/

/*----------------------------TEST-----------------------*/
		// BIZARERIE 1
	//glm::mat4 mv_matrix_cube3 =
		//glm::translate(glm::vec3(8.0f, 2.5f, 4.0f)) *
		//glm::scale(glm::vec3(6.0f, 5.0f, 3.0f)) *
		//glm::mat4(1.0f);
	//myCube2.mv_matrix = myGraphics.viewMatrix * mv_matrix_cube2;
	//myCube2.proj_matrix = myGraphics.proj_matrix;

	//Place The Wall on the Map
	//myWall.mv_matrix = myGraphics.viewMatrix *
		//glm::translate(glm::vec3(2.0f, 1.0f, 1.0f)) *
		//glm::scale(glm::vec3(1000.0f, 0.001f, 1000.0f)) *
		//glm::mat4(1.0f);
	//myWall.proj_matrix = myGraphics.proj_matrix;
/*-------------------------------------------------------*/


	t += 0.01f; // increment movement variable


	if (glfwWindowShouldClose(myGraphics.window) == GL_TRUE) quit = true; // If quit by pressing x on window.

}

void renderScene() {
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();

	// Draw objects in screen
	
	
/*----------------------DEMO OBJECTS---------------------*/
	myFloor.Draw();

	mySphere.Draw();
	myC5.Draw();
	myC6.Draw();
	myC7.Draw();
	myC8.Draw();
	myC9.Draw();

	arrowX.Draw();
	arrowY.Draw();
	arrowZ.Draw();

	myLine.Draw();
	myCylinder.Draw();
/*-------------------------------------------------------*/


/*-----------------------LABYRINTH-----------------------*/
	myC1.Draw();
	myC2.Draw();
	myC3.Draw();
	myC4.Draw();
/*-------------------------------------------------------*/


/*----------------------MAGIC_SPHERE---------------------
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				myS[i][j][k].Draw();
			}
		}
	}
-------------------------------------------------------*/
}


// CallBack functions low level functionality.
void onResizeCallback(GLFWwindow* window, int w, int h) {    // call everytime the window is resized
	//myGraphics.windowWidth = w;
	//myGraphics.windowHeight = h;

	glfwGetFramebufferSize(window, &myGraphics.windowWidth, &myGraphics.windowHeight);

	myGraphics.aspect = (float)w / (float)h;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);
}

void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { // called everytime a key is pressed
	if (action == GLFW_PRESS) keyStatus[key] = true;
	else if (action == GLFW_RELEASE) keyStatus[key] = false;

	// toggle showing mouse.
	if (keyStatus[GLFW_KEY_M]) {
		mouseEnabled = !mouseEnabled;
		myGraphics.ToggleMouse();
	}
	// If exit key pressed.
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

}

void onMouseMoveCallback(GLFWwindow* window, double x, double y) {
	int mouseX = static_cast<int>(x);
	int mouseY = static_cast<int>(y);

	myGraphics.mouseX = mouseX;
	myGraphics.mouseY = mouseY;

	// helper variables for FPS camera
	if (myGraphics.cameraFirstMouse) {
		myGraphics.cameraLastX = (GLfloat)myGraphics.mouseX; myGraphics.cameraLastY = (GLfloat)myGraphics.mouseY; myGraphics.cameraFirstMouse = false;
	}
}

void onMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset) {
	int yoffsetInt = static_cast<int>(yoffset);
}
