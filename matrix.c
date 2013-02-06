//
//  main.c
//  
//
//  Created by Sean Fitzgerald on 11/28/12.
//
//

#include <stdio.h>
#include <math.h>
#include "matrix.h"
#include "structs.h"

void multiply_triangle_and_matrix(Triangle triangles[], int numberTriangles, double transformationMatrix[][3])
{
	Vector tempPoint; // declare variables
	
	int triangle;
	
	for(triangle = 0; triangle < numberTriangles; triangle++)
	{
		//printf("trianglePoint1: (%lf, %lf, %lf)\ntrianglePoint2: (%lf, %lf, %lf)\ntrianglePoint3: (%lf, %lf, %lf)\n\n", triangles[triangle].point1.x, triangles[triangle].point1.y, triangles[triangle].point1.z, triangles[triangle].point2.x, triangles[triangle].point2.y, triangles[triangle].point2.z, triangles[triangle].point3.x, triangles[triangle].point3.y, triangles[triangle].point3.z);

		tempPoint.x =  triangles[triangle].point1.x * transformationMatrix[0][0] + triangles[triangle].point1.y * transformationMatrix[0][1] + triangles[triangle].point1.z * transformationMatrix[0][2];
		tempPoint.y =  triangles[triangle].point1.x * transformationMatrix[1][0] + triangles[triangle].point1.y * transformationMatrix[1][1] + triangles[triangle].point1.z * transformationMatrix[1][2];
		tempPoint.z = triangles[triangle].point1.x * transformationMatrix[2][0] + triangles[triangle].point1.y * transformationMatrix[2][1] + triangles[triangle].point1.z * transformationMatrix[2][2];

		triangles[triangle].point1.x = tempPoint.x;
		triangles[triangle].point1.y = tempPoint.y;
		triangles[triangle].point1.z = tempPoint.z;
		// store the changed point to matrix3D

		tempPoint.x =  triangles[triangle].point2.x * transformationMatrix[0][0] + triangles[triangle].point2.y * transformationMatrix[0][1] + triangles[triangle].point2.z * transformationMatrix[0][2];
		tempPoint.y =  triangles[triangle].point2.x * transformationMatrix[1][0] + triangles[triangle].point2.y * transformationMatrix[1][1] + triangles[triangle].point2.z * transformationMatrix[1][2];
		tempPoint.z =  triangles[triangle].point2.x * transformationMatrix[2][0] + triangles[triangle].point2.y * transformationMatrix[2][1] + triangles[triangle].point2.z * transformationMatrix[2][2];
		
		triangles[triangle].point2.x = tempPoint.x;
		triangles[triangle].point2.y = tempPoint.y;
		triangles[triangle].point2.z = tempPoint.z;
		// store the changed point to matrix3D

		tempPoint.x =  triangles[triangle].point3.x * transformationMatrix[0][0] + triangles[triangle].point3.y * transformationMatrix[0][1] + triangles[triangle].point3.z * transformationMatrix[0][2];
		tempPoint.y =  triangles[triangle].point3.x * transformationMatrix[1][0] + triangles[triangle].point3.y * transformationMatrix[1][1] + triangles[triangle].point3.z * transformationMatrix[1][2];
		tempPoint.z =  triangles[triangle].point3.x * transformationMatrix[2][0] + triangles[triangle].point3.y * transformationMatrix[2][1] + triangles[triangle].point3.z * transformationMatrix[2][2];
		
		triangles[triangle].point3.x = tempPoint.x;
		triangles[triangle].point3.y = tempPoint.y;
		triangles[triangle].point3.z = tempPoint.z;
		// store the changed point to matrix3D

		triangles[triangle].normal = cross_product(subtract_vectors(triangles[triangle].point1, triangles[triangle].point2), subtract_vectors(triangles[triangle].point1, triangles[triangle].point3));
		triangles[triangle].normal = vector_constant_product(triangles[triangle].normal, 1 / length(triangles[triangle].normal));
		
		//printf("trianglePoint1: (%lf, %lf, %lf)\ntrianglePoint2: (%lf, %lf, %lf)\ntrianglePoint3: (%lf, %lf, %lf)\n\n", triangles[triangle].point1.x, triangles[triangle].point1.y, triangles[triangle].point1.z, triangles[triangle].point2.x, triangles[triangle].point2.y, triangles[triangle].point2.z, triangles[triangle].point3.x, triangles[triangle].point3.y, triangles[triangle].point3.z);

	}
	return;
}
//multiplies the triangles' (x, y, z) coordinates with the transformation matrix. store it back in the triangles[] array

double dot_product(Vector vector1, Vector vector2)
{
	
	//printf("vector1: (%lf, %lf, %lf)\n", vector1.x, vector1.y, vector1.z);
	//printf("vector2: (%lf, %lf, %lf)\n", vector2.x, vector2.y, vector2.z);

	
	double dot = (vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z);
	//printf("dot: %lf\n", dot);

	return dot;
}
//returns the dot product of vector1 and vector2

Vector vector_constant_product(Vector vector, double factor)
{
	vector.x = vector.x * factor;
	vector.y = vector.y * factor;
	vector.z = vector.z * factor;

	return vector;
}
//returns a vector with each part of vector multiplied by factor

Vector cross_product(Vector vector1, Vector vector2)
{
	Vector hat;
	
	hat.x = vector1.y * vector2.z - vector1.z * vector2.y;
	hat.y = vector1.z * vector2.x - vector1.x * vector2.z;
	hat.z = vector1.x * vector2.y - vector1.y * vector2.x;
		
	return hat;

}
//returns the cross product of vector1 and vector2

double length(Vector vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}
//returns the length of vector

Vector add_vectors(Vector vector1, Vector vector2)
{
	Vector sum;
	
	sum.x = vector1.x + vector2.x;
	sum.y = vector1.y + vector2.y;
	sum.z = vector1.z + vector2.z;

	return sum;
}
//returns the vector sum, vector1 + vector2

Vector subtract_vectors(Vector vector1, Vector vector2)
{
	Vector difference;
	
	difference.x = vector1.x - vector2.x;
	difference.y = vector1.y - vector2.y;
	difference.z = vector1.z - vector2.z;
	
	return difference;

}
//returns the vector difference, vector1-vector2

double angle_between_vectors(Vector vector1, Vector vector2)
{
	return acos(dot_product(vector1, vector2) / (length(vector1) * length(vector2)));
}
//returns the angle made between the tails of vector1 and vector2

void xzDirection(double matrixTransformation[][3], double phi)
{
	matrixTransformation[0][0] = cos(phi);
	matrixTransformation[1][0] = 0;
	matrixTransformation[2][0] = sin(phi);
	matrixTransformation[0][1] = 0;
	matrixTransformation[1][1] = 1;
	matrixTransformation[2][1] = 0;
	matrixTransformation[0][2] = -sin(phi);
	matrixTransformation[1][2] = 0;
	matrixTransformation[2][2] = cos(phi);
	
	/*
	 [cos(phi) 0 -sin(phi)]
	 [0				 1				 0]
	 [sin(phi) 0  cos(phi)]
	 */
	
	return;
}

void yxDirection(double matrixTransformation[][3], double rho)
{
	matrixTransformation[0][0] = cos(rho);
	matrixTransformation[1][0] = sin(rho);
	matrixTransformation[2][0] = 0;
	matrixTransformation[0][1] = -sin(rho);
	matrixTransformation[1][1] = cos(rho);
	matrixTransformation[2][1] = 0;
	matrixTransformation[0][2] = 0;
	matrixTransformation[1][2] = 0;
	matrixTransformation[2][2] = 1;
	
	/*
	 [cos(rho   -sin(rho)         0]
	 [sin(rho)	cos(rho)          0]
	 [0                0          1]
	 */
	
	return;
}

Vector triangle_normal(Triangle triangle)
{
	Vector normal = cross_product(subtract_vectors(triangle.point1, triangle.point2), subtract_vectors(triangle.point1, triangle.point3));
	normal = vector_constant_product(triangle.normal, 1 / length(triangle.normal));
	return normal;
}
