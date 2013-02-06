//
//  main.c
//  
//
//  Created by Sean Fitzgerald on 11/28/12.
//
//

#include <stdio.h>
#include "stdlib.h"
//#include "structs.h"
#include "3DStuff.h"
#include "matrix.h"

Triangle* make_cube(double sideLength, Vector position, Color color, double reflectivity)
{
	Triangle *cube = malloc(sizeof(Triangle) * 12);
	//a cube has 6 sides, each with two triangles. Hence a cube is an array of 12 Triangle structures
	
	cube[0].point1.x = position.x +sideLength / 2;
	cube[0].point1.y = position.y + - sideLength / 2;
	cube[0].point1.z = position.z+ sideLength / 2;

	cube[0].point2.x = position.x +sideLength / 2;
	cube[0].point2.y = position.y + - sideLength / 2;
	cube[0].point2.z = position.z+ - sideLength / 2;
	
	cube[0].point3.x = position.x +sideLength / 2;
	cube[0].point3.y = position.y + sideLength / 2;
	cube[0].point3.z = position.z+ sideLength / 2;
		
	cube[1].point1 = cube[0].point3;
	
	cube[1].point2 = cube[0].point2;
	
	cube[1].point3.x = position.x +sideLength / 2;
	cube[1].point3.y = position.y + sideLength / 2;
	cube[1].point3.z = position.z+ - sideLength / 2;
	
	cube[0].normal.x = cube[1].normal.x = 1;
	cube[0].normal.y = cube[1].normal.y = 0;
	cube[0].normal.z = cube[1].normal.z = 0;
		
	cube[2].point1 = cube[0].point3;
	
	cube[2].point2 = cube[1].point3;
	
	cube[2].point3.x = position.x - sideLength / 2;
	cube[2].point3.y = position.y + sideLength / 2;
	cube[2].point3.z = position.z+ sideLength / 2;

	cube[3].point1 = cube[2].point3;
	
	cube[3].point2 = cube[2].point2;
	
	cube[3].point3.x = position.x - sideLength / 2;
	cube[3].point3.y = position.y + sideLength / 2;
	cube[3].point3.z = position.z+ - sideLength / 2;
	
	cube[2].normal.x = cube[3].normal.x = 0;
	cube[2].normal.y = cube[3].normal.y = 1;
	cube[2].normal.z = cube[3].normal.z = 0;

	cube[4].point1 = cube[3].point1;
	cube[4].point2 = cube[3].point3;	
	
	cube[4].point3.x = position.x - sideLength / 2;
	cube[4].point3.y = position.y + - sideLength / 2;
	cube[4].point3.z = position.z+ sideLength / 2;
	
	cube[5].point1 = cube[4].point3;
	cube[5].point2 = cube[4].point2;
	
	cube[5].point3.x = position.x - sideLength / 2;
	cube[5].point3.y = position.y + - sideLength / 2;
	cube[5].point3.z = position.z+ - sideLength / 2;
	
	cube[4].normal.x = cube[5].normal.x = -1;
	cube[4].normal.y = cube[5].normal.y = 0;
	cube[4].normal.z = cube[5].normal.z = 0;
	
	cube[6].point1 = cube[5].point1;
	cube[6].point2 = cube[5].point3;
	cube[6].point3 = cube[0].point1;

	cube[7].point1 = cube[0].point1;
	cube[7].point2 = cube[6].point2;
	cube[7].point3 = cube[0].point2;

	cube[6].normal.x = cube[7].normal.x = 0;
	cube[6].normal.y = cube[7].normal.y = -1;
	cube[6].normal.z = cube[7].normal.z = 0;
	
	cube[8].point1 = cube[4].point3;
	cube[8].point2 = cube[0].point1;
	cube[8].point3 = cube[2].point3;

	cube[9].point1 = cube[8].point3;
	cube[9].point2 = cube[8].point2;
	cube[9].point3 = cube[0].point3;

	cube[8].normal.x = cube[9].normal.x = 0;
	cube[8].normal.y = cube[9].normal.y = 0;
	cube[8].normal.z = cube[9].normal.z = 1;
	
	cube[10].point1 = cube[0].point2;
	cube[10].point2 = cube[5].point3;
	cube[10].point3 = cube[3].point2;

	cube[11].point1 = cube[10].point3;
	cube[11].point2 = cube[10].point2;
	cube[11].point3 = cube[3].point3;
	
	cube[10].normal.x = cube[11].normal.x = 0;
	cube[10].normal.y = cube[11].normal.y = 0;
	cube[10].normal.z = cube[11].normal.z = -1;

	int i;
	for(i = 0; i < 12; i++)
	{
		cube[i].color = color;
		cube[i].reflectivity = reflectivity;
		cube[0].normal = triangle_normal(cube[0]);

	}

	
	return cube;
}

Triangle* make_prism(double sideLength, Vector position, Color color, double reflectivity)
{
  	Triangle *prism = malloc(sizeof(Triangle) * 6);
	//a cube has 6 sides, each with two triangles. Hence a cube is an array of 12 Triangle structures
	
		
	prism[0].point1.x = position.x + sideLength / 2;
	prism[0].point1.y = position.y - sideLength / 2;
	prism[0].point1.z = position.z;
	
	prism[0].point2.x = position.x - sideLength / 2;
	prism[0].point2.y = position.y + sideLength / 2;
	prism[0].point2.z = position.z;

	prism[0].point3.x = position.x + sideLength / 2;
	prism[0].point3.y = position.y + sideLength / 2;
	prism[0].point3.z = position.z;

	prism[1].point1.x = position.x - sideLength / 2;
	prism[1].point1.y = position.y - sideLength / 2;
	prism[1].point1.z = position.z;
	
	prism[1].point2 = prism[0].point2;
	prism[1].point3 = prism[0].point1;
	
	prism[2].point1.x = position.x;
	prism[2].point1.y = position.y;
	prism[2].point1.z = position.z + 1.732 * sideLength / 2;
	
	prism[2].point2 = prism[0].point1;
	prism[2].point3 = prism[0].point3;
	
	prism[3].point1 = prism[2].point1;
	prism[3].point2 = prism[0].point3;
	prism[3].point3 = prism[0].point2;
	
	prism[4].point1 = prism[2].point1;
	prism[4].point2 = prism[0].point2;
	prism[4].point3 = prism[1].point1;

	prism[5].point1 = prism[2].point1;
	prism[5].point2 = prism[1].point1;
	prism[5].point3 = prism[0].point1;
	
	int i;
	for(i = 0; i < 6; i++)
	{
		prism[i].color = color;
		prism[i].reflectivity = reflectivity;
		prism[0].normal = triangle_normal(prism[0]);
	}
	return prism;
}

Triangle* make_thick_plane(double sideLength, double thickness, Vector position, Color color, double reflectivity)
{
	Triangle *rectangularPrism = malloc(sizeof(Triangle) * 12);

	
	Vector point1;
	point1.x = position.x + sideLength / 2;
	point1.y = position.y - sideLength / 2;
	point1.z = position.z + thickness / 2;
	
	Vector point2;
	point2.x = position.x + sideLength / 2;
	point2.y = position.y - sideLength / 2;
	point2.z = position.z - thickness / 2;

	Vector point3;
	point3.x = position.x + sideLength / 2;
	point3.y = position.y + sideLength / 2;
	point3.z = position.z - thickness / 2;

	Vector point4;
	point4.x = position.x + sideLength / 2;
	point4.y = position.y + sideLength / 2;
	point4.z = position.z + thickness / 2;

	Vector point8;
	point8.x = position.x - sideLength / 2;
	point8.y = position.y - sideLength / 2;
	point8.z = position.z + thickness / 2;

	Vector point7;
	point7.x = position.x - sideLength / 2;
	point7.y = position.y - sideLength / 2;
	point7.z = position.z - thickness / 2;

	Vector point6;
	point6.x = position.x - sideLength / 2;
	point6.y = position.y + sideLength / 2;
	point6.z = position.z - thickness / 2;

	Vector point5;
	point5.x = position.x - sideLength / 2;
	point5.y = position.y + sideLength / 2;
	point5.z = position.z + thickness / 2;
	
	rectangularPrism[0].point1 = point1;
	rectangularPrism[0].point2 = point2;
	rectangularPrism[0].point3 = point3;

	rectangularPrism[1].point1 = point1;
	rectangularPrism[1].point2 = point3;
	rectangularPrism[1].point3 = point4;

	rectangularPrism[2].point1 = point4;
	rectangularPrism[2].point2 = point3;
	rectangularPrism[2].point3 = point6;

	rectangularPrism[3].point1 = point4;
	rectangularPrism[3].point2 = point6;
	rectangularPrism[3].point3 = point5;

	rectangularPrism[4].point1 = point5;
	rectangularPrism[4].point2 = point6;
	rectangularPrism[4].point3 = point7;

	rectangularPrism[5].point1 = point5;
	rectangularPrism[5].point2 = point7;
	rectangularPrism[5].point3 = point8;

	rectangularPrism[6].point1 = point8;
	rectangularPrism[6].point2 = point7;
	rectangularPrism[6].point3 = point2;
	
	rectangularPrism[7].point1 = point8;
	rectangularPrism[7].point2 = point2;
	rectangularPrism[7].point3 = point1;
	
	rectangularPrism[8].point1 = point1;
	rectangularPrism[8].point2 = point4;
	rectangularPrism[8].point3 = point5;
	
	rectangularPrism[9].point1 = point1;
	rectangularPrism[9].point2 = point5;
	rectangularPrism[9].point3 = point8;
	
	rectangularPrism[10].point1 = point2;
	rectangularPrism[10].point2 = point7;
	rectangularPrism[10].point3 = point6;
	
	rectangularPrism[11].point1 = point2;
	rectangularPrism[11].point2 = point6;
	rectangularPrism[11].point3 = point3;

	
	int i;
	for(i = 0; i < 12; i++)
	{
		rectangularPrism[i].color = color;
		rectangularPrism[i].reflectivity = reflectivity;
		rectangularPrism[0].normal = triangle_normal(rectangularPrism[0]);
		
	}
	
	
	return rectangularPrism;

}