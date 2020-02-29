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

// CROWND
/*-------------------------CROWD-------------------------

Cube        myC5;
Cube		myC6;
Cube		myC7;
Cube		myC8;
Cube		myC9;
-------------------------------------------------------*/

// LABYRINTH 
/*-----------------------LABYRINTH-----------------------
Cube        myC1;
Cube		myC2;
Cube        myC3;
Cube        myC4;
-------------------------------------------------------*/

// MAGIC SPHERE 
/*----------------------MAGIC_SPHERE---------------------
Sphere		myS[9][9][9];

int			Sx[9];
int			Sy[9];
int			Sz[9];

float		LenghtX;
float		LenghtY;
float		LenghtZ;
-------------------------------------------------------*/ 


// PHYSICS 
/*------------------------PHYSICS-------------------------
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


-------------------------------------------------------*/

/*------------------------MATRIX LABYRIH-------------------------*/

	//---------- PLAYERS
Cube        MyT1;

float		cube_x = 12.0f;
float		cube_y = 0.5f;
float		cube_z = 0.0f;

float		cube_x2 = 13.0f;
float		cube_y2 = 0.5f;
float		cube_z2 = 0.0f;

	//---------- OULIGHTS
Cube		MC1[22];
Cube		MC2[12];
Cube		MC3[22];
Cube		MC4[12];

int			MC1x[22];
int			MC2z[12];
int			MC3x[22];
int			MC4z[12];

float		L_C1x;
float		L_C2z;
float		L_C3x;
float		L_C4z;

	//---------- OULIGHTS
Cube		MyO1[2][3];
Cube		MyO2[7];
Cube		MyO3[6][2];
Cube        MyO4[4];
Cube		MyO5[3][5];
Cube		MyO6[2];
Cube		MyO7[2][2];
Cube		MyO8[3][4];
Cube		MyO9[3][4];
Cube		MyO10[7];
Cube		MyO11[8];
Cube		MyO12[2];
Cube		MyO13[5];
Cube		MyO14[6];
Cube		MyO15[2];
Cube		MyO16[3];
Cube		MyO17[7];
Cube		MyO18[3][2];
Cube		MyO19[3][4];
Cube		MyO20[3][2];
Cube		MyO21[2];


int			MyO1x[2];
int			MyO2x[7];
int			MyO3x[6];
int			MyO4x[4];
int			MyO5x[3];
int			MyO6x[2];
int			MyO7x[2];
int			MyO8x[3];
int			MyO9x[3];
int			MyO12x[2];
int			MyO16x[3];
int			MyO17x[7];
int			MyO18x[3];
int			MyO19x[3];
int			MyO20x[3];
int			MyO21x[2];

int			MyO1z[3];
int			MyO3z[2];
int			MyO5z[5];
int			MyO7z[2];
int			MyO8z[4];
int			MyO9z[4];
int			MyO10z[7];
int			MyO11z[8];
int			MyO13z[5];
int			MyO14z[6];
int			MyO15z[2];
int			MyO18z[2];
int			MyO19z[4];
int			MyO20z[2];


float		L_O1x;
float		L_O2x;
float		L_O3x;
float		L_O5x;
float		L_O4x;
float		L_O6x;
float		L_O7x;
float		L_O8x;
float		L_O9x;
float		L_O12x;
float		L_O16x;
float		L_O17x;
float		L_O18x;
float		L_O19x;
float		L_O20x;
float		L_O21x;

float		L_O1z;
float		L_O3z;
float		L_O5z;
float		L_O7z;
float		L_O8z;
float		L_O9z;
float		L_O10z;
float		L_O11z;
float		L_O13z;
float		L_O14z;
float		L_O15z;
float		L_O18z;
float		L_O19z;
float		L_O20z;


/*--------------------------------------------------------------*/


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

	/*----------------------LOAD OBJECTS---------------------*/

	// FLOOR LOAD
	myFloor.Load();
	myFloor.fillColor = glm::vec4(130.0f / 255.0f, 96.0f / 255.0f, 61.0f / 255.0f, 1.0f);    // Sand Colour
	myFloor.lineColor = glm::vec4(130.0f / 255.0f, 96.0f / 255.0f, 61.0f / 255.0f, 1.0f);    // Sand again

	// ARROW LOAD
	/* arrowX.Load(); arrowY.Load(); arrowZ.Load();
	arrowX.fillColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); arrowX.lineColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	arrowY.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); arrowY.lineColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	arrowZ.fillColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); arrowZ.lineColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); */
																								 
	// CYLINDER LOAD
	/* myCylinder.Load();
	myCylinder.fillColor = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
	myCylinder.lineColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); */

	// LINE LOAD
	/* myLine.Load();
	myLine.fillColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	myLine.lineColor = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	myLine.lineWidth = 5.0f; */

	// LABYRINTH LOAD
	/*-----------------------LABYRINTH-----------------------
	myC1.Load();
	myC1.fillColor = glm::vec4(0.96f, 0.55f, 0.33f, 1.0F);

	myC2.Load();
	myC2.fillColor = glm::vec4(0.96f, 0.55f, 0.33f, 1.0f);

	myC3.Load();
	myC3.fillColor = glm::vec4(0.96f, 0.55f, 0.33f, 1.0f);

	myC4.Load();
	myC4.fillColor = glm::vec4(0.96f, 0.55f, 0.33f, 1.0f);
	-------------------------------------------------------*/

	// MAGIC SPHERE LOAD
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

	// CROWND LOAD
	/*-------------------------CROWD-------------------------
	myC5.Load();
	myC6.Load();
	myC7.Load();
	myC8.Load();
	myC9.Load();
	-------------------------------------------------------*/

	// PHYSICS LOAD	
	/*------------------------PHYSICS-------------------------
	
	mySphere.Load();
	mySphere.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	-------------------------------------------------------*/

	// MATRIX_LABYRINTH LOAD
	/*------------------------MATRIX LABYRINTH-------------------------*/
	
	//----------- LOAD PLAYER
	MyT1.Load();
	MyT1.fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0F);


	//----------- LOAD OUTLIGHTS
	for (int i = 0; i < 22; i++) {
		MC1[i].Load();
		MC1[i].fillColor = glm::vec4(0.0f, 0.68f, 0.93f, 1.0F);
		MC1x[i] = i / 2;
	}
	L_C1x = MC1x[21] - MC1x[0];

	for (int k = 0; k < 12; k++) {
		MC2[k].Load();
		MC2[k].fillColor = glm::vec4(0.0f, 0.68f, 0.93f, 1.0F);
		MC2z[k] = k / 2;
			
	}
	L_C2z = MC2z[11] - MC2z[0];

	for (int i = 0; i < 22; i++) {
		MC3[i].Load();
		MC3[i].fillColor = glm::vec4(0.0f, 0.68f, 0.93f, 1.0F);
		MC3x[i] = i / 2;
	}
	L_C3x = MC3x[21] - MC3x[0];

	for (int k = 0; k < 12; k++) {
		MC4[k].Load();
		MC4[k].fillColor = glm::vec4(0.0f, 0.68f, 0.93f, 1.0F);
		MC4z[k] = k / 2;

	}
	L_C4z = MC4z[11] - MC4z[0];


	//----------- LOAD OBSTACLE

	for (int i = 0; i < 7; i++) {
		MyO2[i].Load();
		MyO2[i].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
		MyO2x[i] = i / 2;
	}
	L_O2x = MyO2x[6] - MyO2x[0];

	for (int i = 0; i < 6; i++) {
		for (int k = 0; k < 2; k++) {
			MyO3[i][k].Load();
			MyO3[i][k].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
			MyO3x[i] = i / 2;
			MyO3z[k] = k / 2;
		}
	}
	L_O3x = MyO3x[5] - MyO3x[0];
	L_O3z = MyO3z[1] - MyO3z[0];

	for (int i = 0; i < 4; i++) {
		MyO4[i].Load();
		MyO4[i].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
		MyO4x[i] = i / 2;
	}
	L_O4x = MyO4x[3] - MyO4x[0];

	for (int i = 0; i < 2; i++) {
		MyO6[i].Load();
		MyO6[i].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
		MyO6x[i] = i / 2;
	}
	L_O6x = MyO6x[1] - MyO6x[0];

	for (int i = 0; i < 2; i++) {
		for (int k = 0; k < 2; k++) {
			MyO7[i][k].Load();
			MyO7[i][k].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
			MyO7x[i] = i / 2;
			MyO7z[k] = k / 2;

		}
	}
	L_O7x = MyO7x[1] - MyO7x[0];
	L_O7z = MyO7z[1] - MyO7z[0];

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 4; k++) {
			MyO8[i][k].Load();
			MyO8[i][k].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
			MyO8x[i] = i / 2;
			MyO8z[k] = k / 2;

		}
	}
	L_O8x = MyO8x[2] - MyO8x[0];
	L_O8z = MyO8z[3] - MyO8z[0];

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 4; k++) {
			MyO9[i][k].Load();
			MyO9[i][k].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
			MyO9x[i] = i / 2;
			MyO9z[k] = k / 2;

		}
	}
	L_O9x = MyO9x[2] - MyO9x[0];
	L_O9z = MyO9z[3] - MyO9z[0];

	for (int i = 0; i < 2; i++) {
		MyO12[i].Load();
		MyO12[i].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
		MyO12x[i] = i / 2;
	}
	L_O12x = MyO12x[1] - MyO12x[0];

	for (int i = 0; i < 2; i++) {
		for (int k = 0; k < 3; k++) {
			MyO1[i][k].Load();
			MyO1[i][k].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
			MyO1z[i] = i / 2;
			MyO1x[k] = k / 2;

		}
	}
	L_O1x = MyO1x[1] - MyO1x[0];
	L_O1z = MyO1z[2] - MyO1z[0];

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 5; k++) {
			MyO5[i][k].Load();
			MyO5[i][k].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
			MyO5x[i] = i / 2;
			MyO5z[k] = k / 2;
		}
	}
	L_O5x = MyO5x[2] - MyO3x[0];
	L_O5z = MyO5z[4] - MyO3z[0];

	for (int k = 0; k < 7; k++) {
		MyO10[k].Load();
		MyO10[k].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
		MyO10z[k] = k / 2;
	}
	L_O10z = MyO10z[6] - MyO10z[0];

	for (int k = 0; k < 8; k++) {
		MyO11[k].Load();
		MyO11[k].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
		MyO11z[k] = k / 2;
	}
	L_O11z = MyO11z[7] - MyO11z[0];

	for (int k = 0; k < 5; k++) {
		MyO13[k].Load();
		MyO13[k].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
		MyO13z[k] = k / 2;
	}
	L_O13z = MyO13z[4] - MyO13z[0];

	for (int k = 0; k < 6; k++) {
		MyO14[k].Load();
		MyO14[k].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
		MyO14z[k] = k / 2;
	}
	L_O14z = MyO14z[5] - MyO14z[0];

	for (int k = 0; k < 2; k++) {
		MyO15[k].Load();
		MyO15[k].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
		MyO15z[k] = k / 2;
	}
	L_O15z = MyO15z[1] - MyO15z[0];

	for (int i = 0; i < 3; i++) {
		MyO16[i].Load();
		MyO16[i].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
		MyO16x[i] = i / 2;
	}
	L_O16x = MyO16x[2] - MyO16x[0];

	for (int i = 0; i < 7; i++) {
		MyO17[i].Load();
		MyO17[i].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
		MyO17x[i] = i / 2;
	}
	L_O17x = MyO17x[6] - MyO17x[0];

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 2; k++) {
			MyO18[i][k].Load();
			MyO18[i][k].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
			MyO18x[i] = i / 2;
			MyO18z[k] = k / 2;
		}
	}
	L_O18x = MyO18x[2] - MyO18x[0];
	L_O18z = MyO18z[1] - MyO18z[0];

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 4; k++) {
			MyO19[i][k].Load();
			MyO19[i][k].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
			MyO19x[i] = i / 2;
			MyO19z[k] = k / 2;
		}
	}
	L_O19x = MyO19x[2] - MyO19x[0];
	L_O19z = MyO19z[3] - MyO19z[0];

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 2; k++) {
			MyO20[i][k].Load();
			MyO20[i][k].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
			MyO20x[i] = i / 2;
			MyO20z[k] = k / 2;
		}
	}
	L_O20x = MyO20x[2] - MyO20x[0];
	L_O20z = MyO20z[1] - MyO20z[0];

	for (int i = 0; i < 2; i++) {
		MyO21[i].Load();
		MyO21[i].fillColor = glm::vec4(1.0f, 0.94f, 0.0f, 1.0f);
		MyO21x[i] = i / 2;
	}
	L_O21x = MyO21x[1] - MyO21x[0];



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

// MATHS
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

// PHYSICS
/*------------------------PHYSICS-------------------------

 void Fall() {

	// Somme de Fext = m.a d ou vu que l on est dans le vide m.a = m.g soit: a = g​
	h = Cy;
	speed = sqrt(2 * g * h);
	//-----------state 1: GO DOWN
	if (Cy > 0.5f && a % 2 == 0 && a != 4200000) { speed = speed + g; Cy = Cy - speed * t; S = 1.0f; }
	//-----------state 2: SPEED = 0
	if (Cy <= 0.5f && a % 2 == 0 && a != 4200000) { a = a + 1;   S = S * speed + D_sphere; speed = 0.0f; }
	//-----------state 3: GO UP
	if (Cy <= h_seuil && a % 2 != 0 && a != 4200000) { speed = speed - 3 * g; Cy = Cy + speed * t; }
	//-----------state 4: SPEED = 0
	if (Cy >= h_seuil && a % 2 != 0 && a != 4200000) { h_seuil = h_seuil / k; a = a * 2; speed = 0.0f; h = Cy; }
	//-----------Avoid infinity while
	if (h_seuil <= 0.5f) { a = 4200000; speed = 0.0f; S = 1.0f; Cy = 0.5f; }
} 
-------------------------------------------------------*/


// CROWD
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
/*--------------------------------------------------------*/



void updateSceneElements() {

	glfwPollEvents();                                // poll callbacks

	// Calculate frame time/period -- used for all (physics, animation, logic, etc).
	GLfloat currentTime = (GLfloat)glfwGetTime();    // retrieve timelapse
	deltaTime = currentTime - lastTime;                // Calculate delta time
	lastTime = currentTime;                            // Save for next frame calculations.

	// Do not forget your ( T * R * S ) http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/

	// CUBE KEY MOVEMENT
	
	if (keyStatus[GLFW_KEY_J]) { cube_x = cube_x + 0.01f; }
	if (keyStatus[GLFW_KEY_L]) { cube_x = cube_x - 0.01f; }
	if (keyStatus[GLFW_KEY_K]) { cube_z = cube_z - 0.01f; }
	if (keyStatus[GLFW_KEY_I]) { cube_z = cube_z + 0.01f; }
	if (keyStatus[GLFW_KEY_E]) { Position_C1(); }
	

	// CROWD & phyics POSITIONS
/*-------------------------CROWD-------------------------
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
-------------------------------------------------------*/
	

	// PHYSICS POSIIONS

/*------------------------PHYSICS-------------------------
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
-------------------------------------------------------*/

	// LABYRINTH POSITION
/*-----------------------LABYRINTH-----------------------
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

	// MAGIG_SPHERE POSITION
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

	// TEST BIZARERIE POSITION
/*----------------------------TEST-----------------------
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
-------------------------------------------------------*/


/*----------------------DEMO OBJECTS---------------------*/
	//Calculate Arrows translations (note: arrow model points up)
/*
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
*/

	// Calculate floor position and resize

	myFloor.mv_matrix = myGraphics.viewMatrix *
		glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)) *
		glm::scale(glm::vec3(1000.0f, 0.001f, 1000.0f)) *
		glm::mat4(1.0f);
	myFloor.proj_matrix = myGraphics.proj_matrix;

	// Calculate cylinder
/*
	myCylinder.mv_matrix = myGraphics.viewMatrix *
		glm::translate(glm::vec3(10.0f, 0.5f, 10.0f)) *
		glm::mat4(1.0f);
	myCylinder.proj_matrix = myGraphics.proj_matrix;
*/

	// Calculate Line
/*
	myLine.mv_matrix = myGraphics.viewMatrix *
		glm::translate(glm::vec3(1.0f, 0.5f, 2.0f)) *
		glm::mat4(1.0f);
	myLine.proj_matrix = myGraphics.proj_matrix;
*/
/*-------------------------------------------------------*/

	// MATRIX LABYRINTH POSITION
/*------------------------MATRIX LABYRINTH-------------------------*/

	//---------- PLAYER
	glm::mat4 mv_matrix_T1 =
		glm::translate(glm::vec3(cube_x, 0.5f, cube_z)) *
		glm::mat4(1.0f);
	MyT1.mv_matrix = myGraphics.viewMatrix * mv_matrix_T1;
	MyT1.proj_matrix = myGraphics.proj_matrix;

	//---------- OULIGHTS
	for (int i = 0; i < 22; i++) {
		glm::mat4 mv_matrix_MC1 =
		glm::translate(glm::vec3(2.0f + 1.0f *i, 0.5f, 0.0f)) *
		glm::mat4(1.0f);
		MC1[i].mv_matrix = myGraphics.viewMatrix * mv_matrix_MC1;
		MC1[i].proj_matrix = myGraphics.proj_matrix;
	}

	for (int k = 0; k < 12; k++) {
		glm::mat4 mv_matrix_MC2 =
		glm::translate(glm::vec3(23.0f, 0.5f, 1.0f + 1.0f * k)) *
		glm::mat4(1.0f);
		MC2[k].mv_matrix = myGraphics.viewMatrix * mv_matrix_MC2;
		MC2[k].proj_matrix = myGraphics.proj_matrix;
	}

	for (int i = 0; i < 22; i++) {
		glm::mat4 mv_matrix_MC3 =
			glm::translate(glm::vec3(0.0f + 1.0f * i, 0.5f, 12.0f)) *
			glm::mat4(1.0f);
		MC3[i].mv_matrix = myGraphics.viewMatrix * mv_matrix_MC3;
		MC3[i].proj_matrix = myGraphics.proj_matrix;
	}

	for (int k = 0; k < 12; k++) {
		glm::mat4 mv_matrix_MC4 =
			glm::translate(glm::vec3(0.0f, 0.5f, 0.0f + 1.0f * k)) *
			glm::mat4(1.0f);
		MC4[k].mv_matrix = myGraphics.viewMatrix * mv_matrix_MC4;
		MC4[k].proj_matrix = myGraphics.proj_matrix;
	}

	//---------- OBSTACLES

	for (int i = 0; i < 7; i++) {
		glm::mat4 mv_matrix_MO2 =
			glm::translate(glm::vec3(5.0f + 1.0f * i, 0.5f, 2.0f)) *
			glm::mat4(1.0f);
		MyO2[i].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO2;
		MyO2[i].proj_matrix = myGraphics.proj_matrix;
	}

	for (int i = 0; i < 6; i++) {
		for (int k = 0; k < 2; k++) {
			glm::mat4 mv_matrix_MO3 =
				glm::translate(glm::vec3(13.0f + 1.0f * i, 0.5f, 1.0f + 1.0f * k)) *
				glm::mat4(1.0f);
			MyO3[i][k].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO3;
			MyO3[i][k].proj_matrix = myGraphics.proj_matrix;
		}
	}

	for (int i = 0; i < 4; i++) {
		glm::mat4 mv_matrix_MO4 =
			glm::translate(glm::vec3(19.0f + 1.0f * i, 0.5f, 1.0f)) *
			glm::mat4(1.0f);
		MyO4[i].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO4;
		MyO4[i].proj_matrix = myGraphics.proj_matrix;
	}

	for (int i = 0; i < 2; i++) {
		glm::mat4 mv_matrix_MO6 =
			glm::translate(glm::vec3(17.0f + 1.0f * i, 0.5f, 7.0f)) *
			glm::mat4(1.0f);
		MyO6[i].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO6;
		MyO6[i].proj_matrix = myGraphics.proj_matrix;
	}

	for (int i = 0; i < 2; i++) {
		for (int k = 0; k < 2; k++) {
			glm::mat4 mv_matrix_MO7 =
				glm::translate(glm::vec3(17.0f + 1.0f * i, 0.5f, 4.0f + 1.0f * k)) *
				glm::mat4(1.0f);
			MyO7[i][k].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO7;
			MyO7[i][k].proj_matrix = myGraphics.proj_matrix;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 4; k++) {
			glm::mat4 mv_matrix_MO8 =
				glm::translate(glm::vec3(13.0f + 1.0f * i, 0.5f, 4.0f + 1.0f * k)) *
				glm::mat4(1.0f);
			MyO8[i][k].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO8;
			MyO8[i][k].proj_matrix = myGraphics.proj_matrix;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 4; k++) {
			glm::mat4 mv_matrix_MO9 =
				glm::translate(glm::vec3(9.0f + 1.0f * i, 0.5f, 4.0f + 1.0f * k)) *
				glm::mat4(1.0f);
			MyO9[i][k].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO9;
			MyO9[i][k].proj_matrix = myGraphics.proj_matrix;
		}
	}

	for (int i = 0; i < 2; i++) {
		glm::mat4 mv_matrix_MO12 =
			glm::translate(glm::vec3(2.0f + 1.0f * i, 0.5f, 5.0f)) *
			glm::mat4(1.0f);
		MyO12[i].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO12;
		MyO12[i].proj_matrix = myGraphics.proj_matrix;
	}

	for (int i = 0; i < 2; i++) {
		for (int k = 0; k < 3; k++) {
			glm::mat4 mv_matrix_MO1 =
				glm::translate(glm::vec3(2.0f + 1.0f * i, 0.5f, 1.0f + 1.0f * k)) *
				glm::mat4(1.0f);
			MyO1[i][k].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO1;
			MyO1[i][k].proj_matrix = myGraphics.proj_matrix;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 5; k++) {
			glm::mat4 mv_matrix_MO5 =
				glm::translate(glm::vec3(20.0f + 1.0f * i, 0.5f, 3.0f + 1.0f * k)) *
				glm::mat4(1.0f);
			MyO5[i][k].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO5;
			MyO5[i][k].proj_matrix = myGraphics.proj_matrix;
		}
	}

	for (int k = 0; k < 7; k++) {
		glm::mat4 mv_matrix_MO10 =
			glm::translate(glm::vec3(7.0f, 0.5f, 3.0f + 1.0f* k)) *
			glm::mat4(1.0f);
		MyO10[k].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO10;
		MyO10[k].proj_matrix = myGraphics.proj_matrix;
	}

	for (int k = 0; k < 8; k++) {
		glm::mat4 mv_matrix_MO11 =
			glm::translate(glm::vec3(5.0f, 0.5f, 5.0f + 1.0f * k)) *
			glm::mat4(1.0f);
		MyO11[k].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO11;
		MyO11[k].proj_matrix = myGraphics.proj_matrix;
	}
	
	for (int k = 0; k < 5; k++) {
		glm::mat4 mv_matrix_MO13 =
			glm::translate(glm::vec3(3.0f, 0.5f, 6.0f + 1.0f * k)) *
			glm::mat4(1.0f);
		MyO13[k].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO13;
		MyO13[k].proj_matrix = myGraphics.proj_matrix;
	}

	for (int k = 0; k < 6; k++) {
		glm::mat4 mv_matrix_MO14 =
			glm::translate(glm::vec3(1.0f, 0.5f, 7.0f + 1.0f * k)) *
			glm::mat4(1.0f);
		MyO14[k].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO14;
		MyO14[k].proj_matrix = myGraphics.proj_matrix;
	}

	for (int k = 0; k < 2; k++) {
		glm::mat4 mv_matrix_MO15 =
			glm::translate(glm::vec3(7.0f, 0.5f, 11.0f + 1.0f * k)) *
			glm::mat4(1.0f);
		MyO15[k].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO15;
		MyO15[k].proj_matrix = myGraphics.proj_matrix;
	}

	for (int i = 0; i < 3; i++) {
		glm::mat4 mv_matrix_MO16 =
			glm::translate(glm::vec3(7.0f + 1.0f * i, 0.5f, 10.0f)) *
			glm::mat4(1.0f);
		MyO16[i].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO16;
		MyO16[i].proj_matrix = myGraphics.proj_matrix;
	}

	for (int i = 0; i < 7; i++) {
		glm::mat4 mv_matrix_MO17 =
			glm::translate(glm::vec3(7.0f + 1.0f * i, 0.5f, 8.0f)) *
			glm::mat4(1.0f);
		MyO17[i].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO17;
		MyO17[i].proj_matrix = myGraphics.proj_matrix;
	}

	
	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 2; k++) {
			glm::mat4 mv_matrix_MO18 =
				glm::translate(glm::vec3(12.0f + 1.0f * i, 0.5f, 9.0f + 1.0f * k)) *
				glm::mat4(1.0f);
			MyO18[i][k].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO18;
			MyO18[i][k].proj_matrix = myGraphics.proj_matrix;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 4; k++) {
			glm::mat4 mv_matrix_MO19 =
				glm::translate(glm::vec3(13.0f + 1.0f * i, 0.5f, 9.0f + 1.0f * k)) *
				glm::mat4(1.0f);
			MyO19[i][k].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO19;
			MyO19[i][k].proj_matrix = myGraphics.proj_matrix;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 2; k++) {
			glm::mat4 mv_matrix_MO20 =
				glm::translate(glm::vec3(19.0f + 1.0f * i, 0.5f, 9.0f + 1.0f * k)) *
				glm::mat4(1.0f);
			MyO20[i][k].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO20;
			MyO20[i][k].proj_matrix = myGraphics.proj_matrix;
		}
	}

	for (int i = 0; i < 2; i++) {
		glm::mat4 mv_matrix_MO21 =
			glm::translate(glm::vec3(17.0f + 1.0f * i, 0.5f, 11.0f)) *
			glm::mat4(1.0f);
		MyO21[i].mv_matrix = myGraphics.viewMatrix * mv_matrix_MO21;
		MyO21[i].proj_matrix = myGraphics.proj_matrix;
	}
/*--------------------------------------------------------------*/

	t += 0.01f; // increment movement variable


	if (glfwWindowShouldClose(myGraphics.window) == GL_TRUE) quit = true; // If quit by pressing x on window.

}

void renderScene() {
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();

	// Draw objects in screen
	
	
/*----------------------DEMO OBJECTS---------------------*/
	myFloor.Draw();

	arrowX.Draw();
	arrowY.Draw();
	arrowZ.Draw();

	//myLine.Draw();
	myCylinder.Draw();
/*-------------------------------------------------------*/

	// PHYSICS 
/*----------------------MAGIC_SPHERE---------------------
	mySphere.Draw();
-------------------------------------------------------*/

	// CROWD DRAW
/*----------------------CROWD---------------------
	
	myC5.Draw();
	myC6.Draw();
	myC7.Draw();
	myC8.Draw();
	myC9.Draw();
-------------------------------------------------*/

	// LABYRINTH DRAW
/*-----------------------LABYRINTH-----------------------
	myC1.Draw();
	myC2.Draw();
	myC3.Draw();
	myC4.Draw();
-------------------------------------------------------*/

	// MAGIC SPHERE DRAW
/*----------------------MAGIC_SPHERE---------------------
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				myS[i][j][k].Draw();
			}
		}
	}
-------------------------------------------------------*/


	// MATRIX LABYRINTH LOAD
/*------------------------MATRIX LABYRINTH-------------------------*/

	//---------- PLAYER
	MyT1.Draw();

	//---------- OUTLIGHT
	for (int i = 0; i < 22; i++) {
		MC1[i].Draw();
	}

	for (int k = 0; k < 12; k++) {
		MC2[k].Draw();
	}

	for (int i = 0; i < 22; i++) {
		MC3[i].Draw();
	}

	for (int k = 0; k < 12; k++) {
		MC4[k].Draw();
	}

	//---------- OBSTACLE
	for (int i = 0; i < 7; i++) {
		MyO2[i].Draw();
	}

	for (int i = 0; i < 6; i++) {
		MyO2[i].Draw();
	}

	for (int i = 0; i < 4; i++) {
		MyO4[i].Draw();
	}

	for (int i = 0; i < 6; i++) {
		for (int k = 0; k < 2; k++){
			MyO3[i][k].Draw();
		}
	}

	for (int i = 0; i < 2; i++) {
		MyO6[i].Draw();
	}

	for (int i = 0; i < 2; i++) {
		for (int k = 0; k < 2; k++) {
			MyO7[i][k].Draw();
		}
	
	}

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 4; k++) {
			MyO8[i][k].Draw();
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 4; k++) {
			MyO9[i][k].Draw();
		}
	}

	for (int i = 0; i < 2; i++) {
		MyO12[i].Draw();
	}
	
	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {
			MyO1[i][k].Draw();
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 5; k++) {
			MyO5[i][k].Draw();
		}
	}

	for (int k = 0; k < 5; k++) {
		MyO10[k].Draw();
	}

	for (int k = 0; k < 7; k++) {
		MyO11[k].Draw();
	}

	for (int k = 0; k < 5; k++) {
		MyO13[k].Draw();
	}

	for (int k = 0; k < 5; k++) {
		MyO14[k].Draw();
	}

	for (int k = 0; k < 1; k++) {
		MyO15[k].Draw();
	}

	for (int i = 0; i < 3; i++) {
		MyO16[i].Draw();
	}

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 2; k++) {
			MyO18[i][k].Draw();
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {
			MyO19[i][k].Draw();
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 2; k++) {
			MyO20[i][k].Draw();
		}
	}

	for (int i = 0; i < 2; i++) {
		MyO21[i].Draw();
	}
/*--------------------------------------------------------------*/
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
