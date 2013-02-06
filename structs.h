// Structure Library
// Sean T FItzgerald

#ifndef STRUCTS_H
#define STRUCTS_H


typedef struct Color {
	
	double red;
	double green;
	double blue;
	
} Color;

typedef struct Vector {
	
	double x;
	double y;
	double z;
	
} Vector;

typedef struct Target {
	int radius; //in pixels
	int centerRow;
	int centerColumn;
	
	int visible;
	//true if the target is visible otherwise false
} Target;

typedef struct Buffer {
	
	int *image; //pointer to the image data
	int length;
	
} Buffer;

typedef struct Triangle {
	
	Vector point1;
	Vector point2;
	Vector point3;
	
	Color color;
	
	Vector normal; //NOTE: MUST BE A UNIT VECTOR FOR RAY TRACER TO WORK!!!!!
	
	double distance;
	
	double absorbedLight; //between 0 and 1
	
	double reflectivity; //between 0 and 1
	
} Triangle;

typedef struct Light {
	
	Vector position;
	Color color;
	
} Light;

typedef struct View {

	Vector topLeftCorner;
	Vector bottomRightCorner;
	
	int width;
	int height;
	
	double planeEquationConstant; //normal.x * position.x + normal.y * position.y + normal.z * position.z = planeEquationConstant
	
	Vector normal;
	
} View;

typedef struct Ray {
	
	Vector direction;
	
	Vector position;
		
	Color color;

	double intensity;
	
} Ray;

#endif