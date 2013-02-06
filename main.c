//
//  main.c
//  
//
//  Created by Sean Fitzgerald on 11/28/12.
//
//

#include "main.h"

int WINDOW_HEIGHT;
int WINDOW_WIDTH;

int GUI_HEIGHT;
int GUI_WIDTH;

int main(void)
{
	
	GUI_WIDTH = 1000;
	GUI_HEIGHT = 500;
	//specify the window height and width

	gfx_open(GUI_WIDTH, GUI_HEIGHT, "Playing With Shapes");
	//open a new window
	
	WINDOW_WIDTH = 300;
	WINDOW_HEIGHT = 300;

	
	Buffer buffer = new_buffer();
	//create a new Buffer to use for the window refresh
	
	int lightNumber = 0, numTriangles = 0, diffuseIntensity = 0, i;
	double transformationMatrix[3][3], phi, rho;
	
	diffuseIntensity = 0.2;
	
	Triangle *triangles;
	
	
	Vector objectPosition;
	/*
	cubePosition.x = 0;
	cubePosition.y = -150;
	cubePosition.z = 0;
	
	Triangle *cube = make_cube(100, cubePosition, blueColor() , .7);
	
	cubePosition.x = 0;
	cubePosition.y = 0;
	cubePosition.z = -150;
	
	Triangle *prism = make_prism(150, cubePosition, redColor() , .7);

	cubePosition.x = 0;
	cubePosition.y = 150;
	cubePosition.z = 0;
	
	Triangle *cube2 = make_cube(100, cubePosition, yellowColor() , .7);
	
	cubePosition.x = 0;
	cubePosition.y = 0;
	cubePosition.z = 150;
	
	Triangle *prism2 = make_prism(150, cubePosition, greenColor() , .7);
	
	cubePosition.x = 0;
	cubePosition.y = 300;
	cubePosition.z = 0;
	
	Triangle *rectangle = make_thick_plane(300, 20, cubePosition, magentaColor(), .7);
	
	cubePosition.x = 0;
	cubePosition.y = 0;
	cubePosition.z = 0;
	
	Triangle *light = make_cube(40, cubePosition, cyanColor() , .7);
	//create all my objects in separate scenes

	numTriangles = 0;
	triangles = add_triangles(cube, numTriangles+=12, prism, 6);
	numTriangles += 6;
	triangles = add_triangles(triangles, numTriangles, prism2, 6);
	numTriangles += 6;
	triangles = add_triangles(triangles, numTriangles, cube2, 12);
	numTriangles += 12;
	triangles = add_triangles(triangles, numTriangles, rectangle, 12);
	numTriangles += 12;
	triangles = add_triangles(triangles, numTriangles, light, 12);
	numTriangles += 12;
	//combine them all into one scene
	*/
	View viewingWindow;
	//create the viewing window for my scene
	
	Vector cubePosition;
	
	cubePosition.x = 0;
	cubePosition.y = 0;
	cubePosition.z = 0;
	
	Triangle *light = make_cube(20, cubePosition, cyanColor() , .7);
	triangles = light;
	numTriangles = 12;
	
	viewingWindow.topLeftCorner.x = 500;
	viewingWindow.topLeftCorner.y = -300;
	viewingWindow.topLeftCorner.z = 300;
	
	viewingWindow.bottomRightCorner.x = 500;
	viewingWindow.bottomRightCorner.y = 300;
	viewingWindow.bottomRightCorner.z = -300;

	viewingWindow.normal.x = -1;
	viewingWindow.normal.y = 0;
	viewingWindow.normal.z = 0;
		
	viewingWindow.planeEquationConstant = -500;
	//define the properties of the viewing window for my screen
	
	lightNumber = 1;
	Light lights[lightNumber];
	
	lights[0].position.x = 700;
	lights[0].position.y = 0;
	lights[0].position.z = 0;
	
	int height = 20;
	Button exitButton;
	exitButton.xsize = 30;
	exitButton.ysize = 20;
	exitButton.xcenter = 1000-exitButton.xsize/2.0;
	exitButton.ycenter = exitButton.ysize/2.0;
	strcpy(exitButton.string,"X");
	//create exitButton
    
	//Create add shape button
	Button addshape;
	addshape.xsize = 190;
	addshape.ysize = 50;
	addshape.xcenter = 510 + addshape.xsize/2.0;
	addshape.ycenter = 490 - addshape.ysize/2.0;
	strcpy(addshape.string,"Add Shape ");
	addshape.filled = 0;
	
	//Create go button to launch free sim
	Button go;
	go.xsize = 80;
	go.ysize = 50;
	go.xcenter = 765;
	go.ycenter = addshape.ycenter;
	strcpy(go.string,"Go!");
	go.filled = 1;
	
	//Create clear button to reset sim
	Button clear;
	clear.xsize = 140;
	clear.ysize = 50;
	clear.xcenter = 900;
	clear.ycenter = addshape.ycenter;
	strcpy(clear.string,"Clear");
	clear.filled = 0;
	
	//Red
	gfx_color(255,0,0);
	Button red;
	red.xsize = 90;
	red.ysize = 40;
	red.xcenter = 570;
	red.ycenter = 310;
	strcpy(red.string, "Red");
	red.filled = 0;

	
	//Blue
	gfx_color(50,50,127);
	Button blue;
	blue.xsize = 90;
	blue.ysize = 40;
	blue.xcenter = 670;
	blue.ycenter = 310;
	strcpy(blue.string, "Blue");
	blue.filled = 0;
	
	//Yellow
	gfx_color(238, 240, 12);
	Button yellow;
	yellow.xsize = 90;
	yellow.ysize = 40;
	yellow.xcenter = 770;
	yellow.ycenter = 310;
	strcpy(yellow.string, "Yellow");
	yellow.filled = 0;
	
	//Green
	gfx_color(0, 150, 0);
	Button green;
	green.xsize = 90;
	green.ysize = 40;
	green.xcenter = 870;
	green.ycenter = 310;
	strcpy(green.string, "green");
	green.filled = 0;
	
	//Purple
	gfx_color(129, 0, 123);
	Button purple;
	purple.xsize = 90;
	purple.ysize = 40;
	purple.xcenter = 570;
	purple.ycenter = 360;
	strcpy(purple.string, "purple");
	purple.filled = 0;
	
	//Orange
	gfx_color(255, 146, 30);
	Button orange;
	orange.xsize = 90;
	orange.ysize = 40;
	orange.xcenter = 670;
	orange.ycenter = 360;
	strcpy(orange.string, "orange");
	orange.filled = 0;
	
	//White
	gfx_color(255, 255, 255);
	Button white;
	white.xsize = 90;
	white.ysize = 40;
	white.xcenter = 770;
	white.ycenter = 360;
	strcpy(white.string, "white");
	white.filled = 0;
	
	//Pink
	gfx_color(210, 95, 150);
	Button pink;
	pink.xsize = 90;
	pink.ysize = 40;
	pink.xcenter = 870;
	pink.ycenter = 360;
	strcpy(pink.string, "pink");
	pink.filled = 0;
	
	//Create cube button
	Button cube;
	cube.xsize = 200;
	cube.ysize = 50;
	cube.xcenter = 750;
	cube.ycenter = 80;
	strcpy(cube.string,"cube");
	cube.filled = 0;
	
	//Create pyramid button
	Button pyramid;
	pyramid.xsize = 200;
	pyramid.ysize = 50;
	pyramid.xcenter = 750;
	pyramid.ycenter = 140;
	strcpy(pyramid.string,"pyramid");
	pyramid.filled = 0;
	
	//Create prism button
	Button prism;
	prism.xsize = 200;
	prism.ysize = 50;
	prism.xcenter = 750;
	prism.ycenter = 200;
	strcpy(prism.string,"prism");
	prism.filled = 0;

	
	

	
	display_start();
	//display's the main screen!
	char string[50];
	gfx_clear();
	
	gfx_color(5,135,185);
	strcpy(string, "Choose a shape:");
	print_string(string, height, 500 + 2 * (height/2), 1000-exitButton.xsize, height);
	gfx_color(5,135,185);
	strcpy(string, "Choose a color:");
	print_string(string, 250, 500 + 2 * (height/2), 1000, height);
		
	Button *buttons[8];
	int numButtons = 8;
	
	buttons[0] = &red;
	buttons[1] = &orange;
	buttons[2] = &yellow;
	buttons[3] = &green;
	buttons[4] = &blue;
	buttons[5] = &purple;
	buttons[6] = &pink;
	buttons[7] = &white;
	
	ray_trace_to_buffer(viewingWindow, buffer, triangles,  numTriangles, lights, lightNumber, diffuseIntensity);
	refresh_buffer();

	while(1)
	{
		
		if(go.filled)
		{
			xzDirection(transformationMatrix, .01 * 3); //set the transformation matrix
			multiply_triangle_and_matrix(triangles, numTriangles, transformationMatrix);
			yxDirection(transformationMatrix, .01 * 4); //set the transformation matrix
			multiply_triangle_and_matrix(triangles, numTriangles, transformationMatrix);
			ray_trace_to_buffer(viewingWindow, buffer, triangles,  numTriangles, lights, lightNumber, diffuseIntensity);
			refresh_buffer();
		}
		
		gfx_color(0,135,140);
    gfx_line(500,0,500,500);
    gfx_color(255,0,0);
    draw_button(exitButton);
    gfx_color(240,15,25);
    draw_button(addshape);
    gfx_color(255,235,40);
    draw_button(go);
    gfx_color(240,115,25);
    draw_button(clear);
		gfx_color(255,0,0);
    draw_button(red);
		gfx_color(50,50,127);
    draw_button(blue);
		gfx_color(238, 240, 12);
    draw_button(yellow);
		gfx_color(0, 150, 0);
    draw_button(green);
		gfx_color(129, 0, 123);
    draw_button(purple);
		gfx_color(255, 146, 30);
    draw_button(orange);
		gfx_color(255, 255, 255);
    draw_button(white);
		gfx_color(210, 95, 150);
    draw_button(pink);
		gfx_color(90,170,45);
		draw_button(cube);
		gfx_color(90,170,45);
		draw_button(pyramid);
		gfx_color(90,170,45);
		draw_button(prism);
		
		
		if(gfx_event_waiting())
		{
			switch (gfx_wait()) // wait for a button to be pressed.
			{
				case 81: // left arrow
					phi = -0.07; // set the transformation angle
					yxDirection(transformationMatrix, phi); //set the transformation matrix
					multiply_triangle_and_matrix(triangles, numTriangles, transformationMatrix);
					ray_trace_to_buffer(viewingWindow, buffer, triangles,  numTriangles, lights, lightNumber, diffuseIntensity);
					break;
				case 82: // up arrow
					rho = 0.07;
					xzDirection(transformationMatrix, rho);
					multiply_triangle_and_matrix(triangles, numTriangles, transformationMatrix);
					ray_trace_to_buffer(viewingWindow, buffer, triangles,  numTriangles, lights, lightNumber, diffuseIntensity);
					break;
				case 83: // right arrow
					phi = 0.07;
					yxDirection(transformationMatrix, phi);
					multiply_triangle_and_matrix(triangles, numTriangles, transformationMatrix);
					ray_trace_to_buffer(viewingWindow, buffer, triangles,  numTriangles, lights, lightNumber, diffuseIntensity);
					break;
				case 84: // down arrow
					rho = -0.07;
					xzDirection(transformationMatrix, rho);
					multiply_triangle_and_matrix(triangles, numTriangles, transformationMatrix);
					ray_trace_to_buffer(viewingWindow, buffer, triangles,  numTriangles, lights, lightNumber, diffuseIntensity);
					break;
				case'p':
					gfx_wait();
					break;
				case 1: //the mouse button has been clicked
					if(mouse_on_button(red))
					{
						for(i = 0; i < numButtons; i++) {buttons[i]->filled = 0;}
						if(red.filled) red.filled = 0;
						else red.filled = 1;
					}
					if(mouse_on_button(orange))
					{
						for(i = 0; i < numButtons; i++) {buttons[i]->filled = 0;}
						if(orange.filled) orange.filled = 0;
						else orange.filled = 1;
					}
					if(mouse_on_button(yellow))
					{
						for(i = 0; i < numButtons; i++) {buttons[i]->filled = 0;}
						if(yellow.filled) yellow.filled = 0;
						else yellow.filled = 1;
					}
					if(mouse_on_button(green))
					{
						for(i = 0; i < numButtons; i++) {buttons[i]->filled = 0;}
						if(green.filled) green.filled = 0;
						else green.filled = 1;
					}
					if(mouse_on_button(pink))
					{
						for(i = 0; i < numButtons; i++) {buttons[i]->filled = 0;}
						if(pink.filled) pink.filled = 0;
						else pink.filled = 1;
					}
					if(mouse_on_button(blue))
					{
						for(i = 0; i < numButtons; i++) {buttons[i]->filled = 0;}
						if(blue.filled) blue.filled = 0;
						else blue.filled = 1;
					}
					if(mouse_on_button(purple))
					{
						for(i = 0; i < numButtons; i++) {buttons[i]->filled = 0;}
						if(purple.filled) purple.filled = 0;
						else purple.filled = 1;
					}
					if(mouse_on_button(white))
					{
						for(i = 0; i < numButtons; i++) {buttons[i]->filled = 0;}
						if(white.filled) white.filled = 0;
						else white.filled = 1;
					}
					if(mouse_on_button(go))
					{
						if(go.filled) go.filled = 0;
						else go.filled = 1;
					}
					if(mouse_on_button(cube))
					{
						if(cube.filled) cube.filled = 0;
						else
						{
							cube.filled = 1;
							prism.filled = 0;
							pyramid.filled = 0;
						}
					}
					if(mouse_on_button(prism))
					{
						if(prism.filled) prism.filled = 0;
						else
						{
							cube.filled = 0;
							prism.filled = 1;
							pyramid.filled = 0;
						}
					}
					if(mouse_on_button(pyramid))
					{
						if(pyramid.filled) pyramid.filled = 0;
						else
						{
							cube.filled = 0;
							prism.filled = 0;
							pyramid.filled = 1;
						}
					}
					if(mouse_on_button(addshape))
					{
						int colorFilled = 0;
						for(i = 0; i < numButtons; i++)
						{
							if(buttons[i]->filled) colorFilled = 1;
						}
						if(!colorFilled) break;
						
						
						Color shapeColor;
						
						if(blue.filled)
						{
							shapeColor.red = 50;
							shapeColor.green = 50;
							shapeColor.blue = 127;
						}
						else if(yellow.filled)
						{
							shapeColor.red = 238;
							shapeColor.green = 240;
							shapeColor.blue = 12;
						}
						else if(green.filled)
						{
							shapeColor.red = 0;
							shapeColor.green = 150;
							shapeColor.blue = 0;
						}
						else if(purple.filled)
						{
							shapeColor.red = 129;
							shapeColor.green = 0;
							shapeColor.blue = 123;
						}
						else if(orange.filled)
						{
							shapeColor.red = 255;
							shapeColor.green = 146;
							shapeColor.blue = 30;
						}
						else if(white.filled)
						{
							shapeColor.red = 255;
							shapeColor.green = 255;
							shapeColor.blue = 255;
						}
						else if(pink.filled)
						{
							shapeColor.red = 210;
							shapeColor.green = 95;
							shapeColor.blue = 150;
						}
						else if(red.filled)
						{
							shapeColor.red = 255;
							shapeColor.green = 0;
							shapeColor.blue = 0;
						}
						
						
						if (cube.filled)
						{
							//(rand() % 600) - 300
							objectPosition.x = 0;
							objectPosition.y = 0;
							objectPosition.z = 0;
							
							//75 + (rand() % 100)
							Triangle *cube = make_cube(200, objectPosition, shapeColor, .7);
							//add_triangles(triangles, numTriangles, cube, 12);
							//numTriangles += 12;
							triangles = cube;
							numTriangles = 12;
						}
						else if (pyramid.filled)
						{
							objectPosition.x = 0;
							objectPosition.y = 0;
							objectPosition.z = 0;
							
							Triangle *pyramid = make_prism(200, objectPosition, shapeColor, .7);
							//add_triangles(triangles, numTriangles, pyramid, 6);
							triangles = pyramid;
							//numTriangles += 6;
							numTriangles = 6;
						}
						else if(prism.filled)
						{
							objectPosition.x = 0;
							objectPosition.y = 0;
							objectPosition.z = 0;
							
							//5 + (rand() % 30)
							Triangle *prism = make_thick_plane(200, 20, objectPosition, shapeColor, .7);
							//add_triangles(triangles, numTriangles, prism, 12);
							//numTriangles += 12;
							triangles = prism;
							numTriangles = 12;
						}
						ray_trace_to_buffer(viewingWindow, buffer, triangles,  numTriangles, lights, lightNumber, diffuseIntensity);
						refresh_buffer();
						addshape.filled = 0;
					}

					if(mouse_on_button(clear))
					{
						triangles = light;
						numTriangles = 12;
						ray_trace_to_buffer(viewingWindow, buffer, triangles,  numTriangles, lights, lightNumber, diffuseIntensity);
					}
					if(mouse_on_button(exitButton))
					{
						free(triangles);
						exit(0);
					}
					break;
			}
		}
		refresh_buffer();
	}
	return 0;
}