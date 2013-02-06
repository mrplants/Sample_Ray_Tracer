//
//  main.h
//  
//
//  Created by Sean Fitzgerald on 11/28/12.
//
//

#ifndef THREEDSTUFF_H
#define THREEDSTUFF_H

#include "structs.h"

Triangle* make_cube(double sideLength, Vector position, Color color, double reflectivity);

Triangle* make_prism(double sideLength, Vector position, Color color, double reflectivity);

Triangle* make_thick_plane(double sideLength, double thickness, Vector position, Color color, double reflectivity);

#endif
