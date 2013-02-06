//
//  buffer.c
//
//
//  Created by Sean Fitzgerald on 11/28/12.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <X11/Xlib.h>
#include "matrix.h"
#include "structs.h"
#include "buffer.h"
#include "graphicsConstants.h"


/*
 void blank_buffer(Buffer buffer)
 {
 int i;
 
 Color black;
 black.red = 255;
 black.green = 255;
 black.blue = 255;
 //make a new color called black and set its RGB value to black
 
 for(i = 0; i < buffer.length; i++)
 {
 pixel_to_buffer(buffer, i, black);
 //set the ith pixel to black
 }
 
 return;
 }
 
 void draw_targets(Buffer buffer, Target targets[], int numberOfTargets)
 {
 
 }
 
 void ray_trace_to_buffer(View viewingWindow, Buffer buffer, Triangle triangles[], int numberTriangles, Light lights[], int numberOfLights, int diffuseIntensity)
 {
 
 Ray pixelRay, lightRay;
 Point pointOfIntersection, dummyPoint;
 
 int i, j, light, triangleIntersectedByLightRay, x = 0, triangle, closestTriangleHit;
 int *visibleLights = malloc(sizeof(int) * numberOfLights);
 
 double distanceToLight, colorIntensity;
 
 for(triangle = 0; triangle < numberTriangles; triangle++)
 {
 triangles[triangle].distance = 0; //put every triangle's distance at zero
 }
 
 for(j = 0; j < WINDOW_HEIGHT; j++) //every pixel in the screen
 {
 for(i = 0; i < WINDOW_WIDTH; i++)
 {
 //start a ray from pixel in viewing direction  (starts with 0 intensityFactor, 100% color)
 
 pixelRay.color.red = 0;
 pixelRay.color.green = 0;
 pixelRay.color.blue = 0;
 
 pixelRay.direction = viewingWindow.normal;
 
 pixelRay.position.x = viewingWindow.topLeftCorner.x + viewingWindow.width / WINDOW_WIDTH * i;
 pixelRay.position.y = viewingWindow.topLeftCorner.y - viewingWindow.height / WINDOW_HEIGHT * j;
 pixelRay.position.z = (viewingWindow.planeEquationConstant - pixelRay.position.x * viewingWindow.normal.x - pixelRay.position.y * viewingWindow.normal.y) / viewingWindow.normal.z;
 
 //describe the pixelRay's position and direction in space
 
 while(!x) //the plane cannot view a light
 {
 closestTriangleHit = ray_intersect_triangle(triangles, numberTriangles, pixelRay, &pointOfIntersection);
 
 if(closestTriangleHit != -1) //at least one triangle was found
 {
 Triangle triangleCopy = triangles[closestTriangleHit];
 
 triangleCopy.color = multiply_color(triangleCopy.color, -1);
 pixelRay.color = add_colors(multiply_color(triangleCopy.color, triangleCopy.reflectivity), pixelRay.color);
 //change ray color based on the surface hit
 
 x = 0;
 
 for(light = 0; light < numberOfLights; light++) //go through every light in the scene
 {
 lightRay.direction.x = lights[light].position.x - pixelRay.position.x;
 lightRay.direction.y = lights[light].position.x - pixelRay.position.x;
 lightRay.direction.z = lights[light].position.x - pixelRay.position.x;
 lightRay.position = pointOfIntersection;
 //set up the light ray
 
 distanceToLight = distance(pointOfIntersection, lights[light].position);
 //find the distance to that light
 
 
 //check to see if there is a triangle between the light and lightRay position
 triangleIntersectedByLightRay = ray_intersect_triangle(triangles, numberTriangles, lightRay, &dummyPoint);
 if((triangleIntersectedByLightRay = -1) && (angle_between_vectors(triangleCopy.normal, lightRay.direction) < (M_PI / 4)))
 {
 //no triangle blocks the light and the light is on the right side of the triangle
 visibleLights[x] = light;
 x++;
 }
 else if(triangles[triangleIntersectedByLightRay].distance > distanceToLight)
 {
 //triangles are intersected by the ray, but are behind the light
 visibleLights[x] = light;
 x++;
 }
 }
 pixelRay.direction = reflect_vector(pixelRay.direction, pointOfIntersection, triangles[closestTriangleHit].normal);
 }
 else //no triangle was found to intersect the ray
 {
 pixelRay.intensity = diffuseIntensity;
 break;
 }
 }
 if(x)
 {
 pixelRay.intensity = shading_value(lights, visibleLights, x, triangleCopy.normal, pixelRay.direction, pointOfIntersection);
 }
 else colorIntensity = pixelRay.intensity;
 pixelRay.color = multiply_color(pixelRay.color, pixelRay.intensity);
 pixel_to_buffer(buffer, i * WINDOW_WIDTH + j, pixelRay.color);
 }
 }
 }
 
 int ray_intersect_triangle(Triangle triangles[], int numberTriangles, Ray pixelRay, Point *pointOfIntersection)
 {
 int triangle, closestTriangleHit = -1;
 
 for(triangle = 0; triangle < numberTriangles; triangle++) //every 3D triangle plane
 {
 
 if((triangles[triangle].distance = ray_hit_triangle(triangles[triangle], pixelRay)) > 0.0) //ray intersects triangle
 {
 if(closestTriangleHit = -1) closestTriangleHit = triangle; //first triangle hit
 
 else if(triangles[triangle].distance < triangles[closestTriangleHit].distance) closestTriangleHit = triangle;
 //compare distance to last intersected triangle
 }
 }
 return closestTriangleHit;
 }
 
 Color add_colors(Color color1, Color color2)
 {
 Color colorSum;
 
 colorSum.red = color1.red + color2.red;
 colorSum.green = color1.green + color2.green;
 colorSum.blue = color1.blue + color2.blue;
 //add the (r, g, b) values of the colors
 
 if(colorSum.red < 0) colorSum.red = 0;
 if(colorSum.green < 0) colorSum.green = 0;
 if(colorSum.blue < 0) colorSum.blue = 0;
 
 if(colorSum.red > 255) colorSum.red = 255;
 if(colorSum.green > 255) colorSum.green = 255;
 if(colorSum.blue > 255) colorSum.blue = 255;
 //clamp to the [0, 255] range
 
 return colorSum;
 }
 
 Color multiply_color(Color color, double factor)
 {
 Color colorProduct;
 
 colorProduct.red = color.red * factor;
 colorProduct.green = color.green * factor;
 colorProduct.blue = color.blue * factor;
 //multiply the (r, g, b) values of the color by the color factor
 
 if(colorProduct.red < 0) colorProduct.red = 0;
 if(colorProduct.green < 0) colorProduct.green = 0;
 if(colorProduct.blue < 0) colorProduct.blue = 0;
 
 if(colorProduct.red > 255) colorProduct.red = 255;
 if(colorProduct.green > 255) colorProduct.green = 255;
 if(colorProduct.blue > 255) colorProduct.blue = 255;
 //clamp to the [0, 255] range
 
 return colorProduct;
 
 }
 
 void pixel_to_buffer(Buffer buffer, int position, Color color)
 {
 buffer.image[position] = (((i)&0xff) | (((j)&0xff)<<8) | (((j)&0xff)<<16));
 
 return;
 }
 
 void refresh_buffer()
 {
 XPutImage(gfx_display, gfx_window, gfx_gc, gfx_image, 0, 0, 0, 0, gfx_image->width, gfx_image->height);
 
 return;
 }
 
 Buffer new_buffer()
 {
 gfx_image = XGetImage(gfx_display, gfx_window, 0, 0, 600, 600, AllPlanes, ZPixmap);
 Buffer newBuffer;
 newBuffer.image = ((int*)(gfx_image->data));
 newBuffer.length = WINDOW_HEIGHT * WINDOW_WIDTH;
 return newBuffer;
 }
 
 double distance(Point position1, Point position2)
 {
 return sqrt(pow(position2.x - position1.x, 2) + pow(position2.y - position1.y, 2) + pow(position2.z - position1.z, 2));
 }
 
 Vector reflect_vector(Vector vector, Point point, Vector normal)
 {
 return subtract_vectors(vector_constant_product(normal, 2 * dot_product(vector, normal)), vector);
 }
 
 double shading_value(Light lights[], int lightsVisible[], int numberOfLightsVisible, Vector normal, Vector lookVector, Point intersection)
 {
 int i;
 double shadingValue = 0, theta;
 Vector lightVector;
 lookVector = vector_constant_product(lookVector, -1);
 
 for(i = 0; i < numberOfLightsVisible; i++)
 {
 lightVector = subtractVectors(lights[lightsVisible[i]].position, intersection);
 shadingValue += angle_between_vectors(lightVector, lookVector) / (M_PI / 4);
 if (shadingValue > 1) return 1;
 }
 return shadingValue;
 }
 
 double ray_hit_triangle(Triangle triangle, Ray ray, Point *pointOfIntersection)
 {
 if(angle_between_vectors(vector_constant_product(ray.direction, -1), triangle.normal) > (M_PI / 4)) return -1;
 
 double distanceToTriangle = (dot_product(triangle.point1, triangle.normal) - dot_product(ray.position, triangle.normal)) / dot_product(ray.direction, triangle.normal);
 
 if (distanceToTriangle > 0.01)
 {
 *pointOfIntersection = vector_constant_product(triangle.normal,  distanceToTriangle);
 
 double beta  = ((pointOnPlane.x - triangle.point1.x) - ((pointOnPlane.y - triangle.point1.y) * (triangle.point2.x - triangle.point1.x) - (pointOnPlane.x - triangle.point1.x) * (triangle.point2.y - triangle.point1.y)) / ((triangle.point2.y - triangle.point1.y) * (triangle.point3.x - triangle.point1.x) + (triangle.point3.y - triangle.point1.y)) * (triangle.point3.x - triangle.point1.x)) / (triangle.point2.x - triangle.point1.x);
 double gamma = ((pointOnPlane.y - triangle.point1.y) * (triangle.point2.x - triangle.point1.x) - (pointOnPlane.x - triangle.point1.x) * (triangle.point2.y - triangle.point1.y)) / ((triangle.point2.y - triangle.point1.y) * (triangle.point3.x - triangle.point1.x) + (triangle.point3.y - triangle.point1.y));
 if((beta >= 0) && (beta <= 1) && (gamma >=0) && (gamma <= 1) && ((1 - beta - gamma) >= 0) && ((1 - beta - gamma) <= 1)) return distanceToTriangle;
 }
 return -1;
 }
 
 */