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

Triangle* add_triangles(Triangle triangles[], int numberTriangles, Triangle additionalTriangles[], int numberOfExtraTriangles)
{
	Triangle *sumTriangles = malloc(sizeof(Triangle) * (numberTriangles + numberOfExtraTriangles));
	int i;
	for(i = 0; i < numberTriangles; i++)
	{
		sumTriangles[i] = triangles[i];
	}

	for(i = 0; i < numberOfExtraTriangles; i++)
	{
		sumTriangles[i + numberTriangles] = additionalTriangles[i];
	}
	
	
	return sumTriangles;
}

void blank_buffer(Buffer buffer, Color color)
{
	int i;
	
	Color black;
	black.red = color.red;
	black.green = color.green;
	black.blue = color.blue;
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
	Vector pointOfIntersection, dummyPoint;
	
	int i, j, light, triangleIntersectedByLightRay, x = 0, triangle, closestTriangleHit, totalDistance = 0;
	int *visibleLights = malloc(sizeof(int) * numberOfLights);
	
	double distanceToLight, theta;
	
	Triangle triangleCopy;
	
	for(triangle = 0; triangle < numberTriangles; triangle++)
	{
		triangles[triangle].distance = 0; //put every triangle's distance at zero
	}
	for(j = 0; j < WINDOW_HEIGHT; j+=1) //every pixel in the screen
	{
		for(i = 0; i < WINDOW_WIDTH; i+=1)
		{
			//printf("number: %d, i: %d, j: %d, x: %d\n\n", i * WINDOW_WIDTH + j, i, j, x);
			


			//start a ray from pixel in viewing direction  (starts with 0 color)
			
			pixelRay.color.red = 0;
			pixelRay.color.green = 0;
			pixelRay.color.blue = 0;
			
			pixelRay.direction = viewingWindow.normal;
			
			pixelRay.position.z = viewingWindow.topLeftCorner.z - fabs(viewingWindow.bottomRightCorner.z - viewingWindow.topLeftCorner.z) / WINDOW_HEIGHT * j;
			pixelRay.position.y = viewingWindow.topLeftCorner.y + fabs(viewingWindow.bottomRightCorner.y - viewingWindow.topLeftCorner.y) / WINDOW_WIDTH * i;
			pixelRay.position.x = (viewingWindow.planeEquationConstant - pixelRay.position.z * viewingWindow.normal.z - pixelRay.position.y * viewingWindow.normal.y) / viewingWindow.normal.x;
			//printf("pixelRay position: (%lf, %lf, %lf)\n", pixelRay.position.x, pixelRay.position.y, pixelRay.position.z);

			totalDistance = 0;
			//describe the pixelRay's position and direction in space
			x = 0;
			while(!x) //the plane cannot view a light
			{
				closestTriangleHit = ray_intersect_triangle(triangles, numberTriangles, pixelRay, &pointOfIntersection);
								
				if(closestTriangleHit != -1) //at least one triangle was found
				{
					//printf("triangle found! hit: %d\n", closestTriangleHit);
					triangleCopy = triangles[closestTriangleHit];
					
					totalDistance += triangleCopy.distance;
					pixelRay.color = add_colors(multiply_color(triangleCopy.color, triangleCopy.reflectivity), pixelRay.color);
					//change ray color based on the surface hit
					
					
					for(light = 0; light < numberOfLights; light++) //go through every light in the scene
					{
						lightRay.direction = subtract_vectors(lights[light].position, pointOfIntersection);
						lightRay.position = pointOfIntersection;
						//set up the light ray
					
						distanceToLight = distance(pointOfIntersection, lights[light].position);
						//find the distance to that light
					
						//printf("distance to light: %lf\n", distanceToLight);
						//printf("triangle normal: (%lf, %lf, %lf)\n", triangleCopy.normal.x, triangleCopy.normal.y, triangleCopy.normal.z);

						//check to see if there is a triangle between the light and lightRay position
						//printf("\ntriangleNumber: %d, testingLight intersection...\n", closestTriangleHit);
						triangleIntersectedByLightRay = ray_intersect_triangle(triangles, numberTriangles, lightRay, &dummyPoint);
						//printf("lightRayIntersection: %d\n", triangleIntersectedByLightRay);
						theta = angle_between_vectors(triangleCopy.normal, lightRay.direction);
						//printf("theta: %lf\n", theta);
						if((triangleIntersectedByLightRay == -1) && (theta < (M_PI / 2)))
						{
							//printf("no triangle blocks.\n");
							//no triangle blocks the light and the light is on the right side of the triangle
							visibleLights[x] = light;
							x++;
						}
						else
						{
							if(triangles[triangleIntersectedByLightRay].distance > distanceToLight)
							{
								//triangles are intersected by the ray, but are behind the light
								visibleLights[x] = light;
								x++;
							}
							//else; printf("lightRayIntersection: %d\n", triangleIntersectedByLightRay);
						}
					 
					}
					 
					pixelRay.direction = reflect_vector(pixelRay.direction, pointOfIntersection, triangles[closestTriangleHit].normal);
					pixelRay.position = pointOfIntersection;
				}
				else //no triangle was found to intersect the ray
				{
					pixelRay.intensity = diffuseIntensity;
					break;
				}
			}
			if(x) //there were light sources present to the pointOfIntersection
			{
				
				pixelRay.intensity = shading_value(lights, visibleLights, x, triangleCopy.normal, pixelRay.direction, pointOfIntersection, totalDistance) + diffuseIntensity;
			}
			else pixelRay.intensity = diffuseIntensity;
			pixelRay.color = multiply_color(pixelRay.color, pixelRay.intensity);
			
			pixel_to_buffer(buffer, j * WINDOW_HEIGHT + i, pixelRay.color);
			//printf("placing pixel... i: %d, j: %d, x: %d\n", i, j, x);
		}
	}

	free(visibleLights);	
	return;
}
	
int ray_intersect_triangle(Triangle triangles[], int numberTriangles, Ray pixelRay, Vector *pointOfIntersection)
{
	int triangle, closestTriangleHit = -1;	
	
	for(triangle = 0; triangle < numberTriangles; triangle++) //every 3D triangle plane
	{
		triangles[triangle].distance = ray_hit_triangle(triangles[triangle], pixelRay, pointOfIntersection);
				
		if(triangles[triangle].distance > 0.0) //ray intersects triangle
		{
			if(closestTriangleHit == -1) closestTriangleHit = triangle; //first triangle hit
			
			else if(triangles[triangle].distance < triangles[closestTriangleHit].distance) closestTriangleHit = triangle;
			//compare distance to last intersected triangle
		}
		if (closestTriangleHit != -1)
		{
			//printf("closest triangle: %d, distance: %lf\n", closestTriangleHit, triangles[closestTriangleHit].distance);
			//printf("pointOfIntersection: (%lf, %lf, %lf)\n", pointOfIntersection->x, pointOfIntersection->y, pointOfIntersection->z);
			//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
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
	//printf("position: %d, color.red: %lf, color.green: %lf, color.blue: %lf\n", position, color.red, color.green, color.blue);
	
	if(buffer.length > position) buffer.image[position] = ((((int)color.blue)&0xff) | ((((int)color.green)&0xff)<<8) | ((((int)color.red)&0xff)<<16));
	
	return;
}

void refresh_buffer()
{
	XPutImage(gfx_display, gfx_window, gfx_gc, gfx_image, 0, 0, 100, 100, gfx_image->width, gfx_image->height);
	
	return;
}

Buffer new_buffer()
{
	gfx_image = XGetImage(gfx_display, gfx_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, AllPlanes, ZPixmap);
	Buffer newBuffer;
	newBuffer.image = ((int*)(gfx_image->data));
	newBuffer.length = WINDOW_HEIGHT * WINDOW_WIDTH;
	return newBuffer;
}

double distance(Vector position1, Vector position2)
{
	return sqrt(pow(position2.x - position1.x, 2) + pow(position2.y - position1.y, 2) + pow(position2.z - position1.z, 2));
}

Vector reflect_vector(Vector vector, Vector point, Vector normal)
{
	
	return add_vectors(vector_constant_product(vector_constant_product(normal, 1 / length(normal)), -2 * dot_product(vector, vector_constant_product( normal, 1 / length(normal)))), vector);
}

double shading_value(Light lights[], int lightsVisible[], int numberOfLightsVisible, Vector normal, Vector lookVector, Vector intersection, int totalDistance)
{
	int i;
	double shadingValue = 0;
	Vector lightVector;
	lookVector = vector_constant_product(lookVector, -1);
	
	for(i = 0; i < numberOfLightsVisible; i++)
	{
		lightVector = subtract_vectors(lights[lightsVisible[i]].position, intersection);
		shadingValue += angle_between_vectors(lightVector, lookVector) / (M_PI / 2);
	}
	
	//printf("distance: %d\n", totalDistance);
	
	shadingValue *= 160000.0 / totalDistance / totalDistance;
	
	//printf("%lf\n", shadingValue);
	
	if (shadingValue > 1) return 1;
	
	return shadingValue;
}

double ray_hit_triangle(Triangle triangle, Ray ray, Vector *pointOfIntersection)
{
	double theta;
	
	theta = angle_between_vectors(vector_constant_product(ray.direction, -1), triangle.normal);
		
	//if(theta > (M_PI / 2)) return -1;
	//printf("\n\ntriangle.normal: (%lf, %lf, %lf)\n triangle.point1: (%lf, %lf, %lf)\n ray.position: (%lf, %lf, %lf)\n ray.direction: (%lf, %lf, %lf)\n\n\n", triangle.normal.x, triangle.normal.y, triangle.normal.z, triangle.point1.x, triangle.point1.y, triangle.point1.z, ray.position.x, ray.position.y, ray.position.z, ray.direction.x, ray.direction.y, ray.direction.z);

	double distanceToTriangle = (dot_product(triangle.point1, triangle.normal) - dot_product(ray.position, triangle.normal)) / dot_product(ray.direction, triangle.normal);
	
	//printf("distance: %lf\n", distanceToTriangle);
	
	if (distanceToTriangle > 10)
	{
		*pointOfIntersection = add_vectors(ray.position, vector_constant_product(ray.direction,  distanceToTriangle));
		
		//printf("pointOfIntersection: (%lf, %lf, %lf)\n", pointOfIntersection->x, pointOfIntersection->y, pointOfIntersection->z);

		double beta  = ((pointOfIntersection->x - triangle.point1.x) - (((triangle.point2.x - triangle.point1.x) * (pointOfIntersection->y - triangle.point1.y) - (pointOfIntersection->x - triangle.point1.x) * (triangle.point2.y - triangle.point1.y)) / ((triangle.point3.y - triangle.point1.y) * (triangle.point2.x - triangle.point1.x) - (triangle.point3.x - triangle.point1.x) * (triangle.point2.y - triangle.point1.y)) * (triangle.point3.x - triangle.point1.x)) ) / (triangle.point2.x - triangle.point1.x);
		double gamma = ((triangle.point2.x - triangle.point1.x) * (pointOfIntersection->y - triangle.point1.y) - (pointOfIntersection->x - triangle.point1.x) * (triangle.point2.y - triangle.point1.y)) / ((triangle.point3.y - triangle.point1.y) * (triangle.point2.x - triangle.point1.x) - (triangle.point3.x - triangle.point1.x) * (triangle.point2.y - triangle.point1.y));
		
		//double beta  = (ex - ((ex' * wy - ex * wy') / (wy'' * ex' - ex'' * wy') * ex'') ) / ex';
		//double gamma = (ex' * wy - ex * wy') / (wy'' * ex' - ex'' * wy');
		//printf("alfa: %lf, beta: %lf, gamma: %lf\n", 1 - beta - gamma, beta, gamma);

		if((beta >= 0) && (beta <= 1) && (gamma >=0) && (gamma <= 1) && ((1 - beta - gamma) >= 0) && ((1 - beta - gamma) <= 1))
		{
			//printf("\n\ntriangle.normal: (%lf, %lf, %lf)\n triangle.point1: (%lf, %lf, %lf)\n ray.position: (%lf, %lf, %lf)\n ray.direction: (%lf, %lf, %lf)\n\n\n", triangle.normal.x, triangle.normal.y, triangle.normal.z, triangle.point1.x, triangle.point1.y, triangle.point1.z, ray.position.x, ray.position.y, ray.position.z, ray.direction.x, ray.direction.y, ray.direction.z);

			//printf("pointOfIntersection: (%lf, %lf, %lf)\n", pointOfIntersection->x, pointOfIntersection->y, pointOfIntersection->z);
			//printf("alfa: %lf, beta: %lf, gamma: %lf\n", 1 - beta - gamma, beta, gamma);

			return distanceToTriangle;
		}
	}
	return -1;
}
