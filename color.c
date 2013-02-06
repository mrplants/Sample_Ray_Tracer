

#include <stdio.h>
#include "color.h"
//#include "structs.h"

Color redColor()
{
	Color color;
	color.red = 255;
	color.green = 0;
	color.blue = 0;
	return color;
}

Color greenColor()
{
	Color color;
	color.red = 0;
	color.green = 255;
	color.blue = 0;
	return color;
}

Color blueColor()
{
	Color color;
	color.red = 0;
	color.green = 0;
	color.blue = 255;
	return color;
}

Color cyanColor()
{
	Color color;
	color.red = 0;
	color.green = 255;
	color.blue = 255;
	return color;
}

Color magentaColor()
{
	Color color;
	color.red = 255;
	color.green = 0;
	color.blue = 255;
	return color;
}

Color yellowColor()
{
	Color color;
	color.red = 255;
	color.green = 255;
	color.blue = 0;
	return color;
}

Color blackColor()
{
	Color color;
	color.red = 0;
	color.green = 0;
	color.blue = 0;
	return color;
}

Color whiteColor()
{
	Color color;
	color.red = 255;
	color.green = 255;
	color.blue = 255;
	return color;
}

