//
//  main.h
//  
//
//  Created by Sean Fitzgerald on 11/28/12.
//
//

#ifndef MATRIX_H
#define MATRIX_H

#include "structs.h"

void multiply_triangle_and_matrix(Triangle triangles[], int numberTriangles, double transformationMatrix[][3]);
//multiplies the triangles' (x, y, z) coordinates with the transformation matrix. store it back in the triangles[] array

double dot_product(Vector vector1, Vector vector2);
//returns the dot product of vector1 and vector2

Vector vector_constant_product(Vector vector, double factor);
//returns a vector with each part of vector multiplied by factor

Vector cross_product(Vector vector1, Vector vector2);
//returns the cross product of vector1 and vector2

double length(Vector vector);
//returns the length of vector

Vector add_vectors(Vector vector1, Vector vector2);
//returns the vector sum, vector1 + vector2

Vector subtract_vectors(Vector vector1, Vector vector2);
//returns the vector difference, vector1-vector2

double angle_between_vectors(Vector vector1, Vector vector2);
//returns the angle made between the tails of vector1 and vector2

void xzDirection(double matrixTransformation[][3], double phi);

void yxDirection(double matrixTransformation[][3], double rho);

Vector triangle_normal(Triangle triangle);

#endif
