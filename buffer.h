//
//  main.h
//  
//
//  Created by Sean Fitzgerald on 11/28/12.
//
//



#ifndef BUFFER_H
#define BUFFER_H

#include "structs.h"

Triangle* add_triangles(Triangle triangles[], int numberTriangles, Triangle additionalTriangles[], int numberOfExtraTriangles);

void blank_buffer(Buffer buffer, Color color);
//fills in the buffer with all white pixels

void draw_targets(Buffer buffer, Target targets[], int numberOfTargets);
//overwrites on the buffer wherever there is a target

void ray_trace_to_buffer(View viewingWindow, Buffer buffer, Triangle triangles[], int numberTriangles, Light lights[], int numberOfLights, int diffuseIntensity);
//ray-traces every pixel on the buffer using triangles and lights. Fills in the buffer pixels witth colors

int ray_intersect_triangle(Triangle triangles[], int numberTriangles, Ray pixelRay, Vector *pointOfIntersection);
//checks if any triangle plane is intersected by lightRay. Returns -1 if it does not intersect, otherwise returns triangleNumber of nearest triangle. It also inputs the distance to that triangle in the triangle's structure and fills in pointOfIntersection with where the ray hits the triangle

void pixel_to_buffer(Buffer buffer, int position, Color color);
//add a pixel to the buffer

void refresh_buffer();
//redraws the current buffer to the screen, completely replacing what was there before

Color add_colors(Color color1, Color color2);
//add two colors together

Color multiply_color(Color color, double factor);
//multiply a color by a factor. Colors clamp to 255

double distance(Vector position1, Vector position2);
//returns the distance between the two points using pythagorus' method

Vector reflect_vector(Vector vector, Vector point, Vector normal);
//returns a vector the is the reflection of vector 'vector' at point 'point' with normal 'normal'

double shading_value(Light lights[], int lightsVisible[], int numberOfLightsVisible, Vector normal, Vector lookVector, Vector intersection, int distance);
//returns the shading value associated with Ray 'lightRay' based on its current value and its reflected angle with the light

double ray_hit_triangle(Triangle triangle, Ray ray, Vector *pointOfIntersection);
//determines if a ray hits a triangle. If true, returns distance to triangle. Otherwise returns -1.

Buffer new_buffer();
//creates and returns a new buffer that points to gfx_image->data and has length WINDOW_WIDTH * WINDOW_HEIGHT

#endif
