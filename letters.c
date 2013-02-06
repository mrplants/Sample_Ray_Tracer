//
//  letters.c
//  
//
//  Created by Kelly D Gawne on 11/28/12.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "gfx.h"
#include "letters.h"

 //int main (void){
 //  display_start();
 //  display_console();
 //  return 0;
 //}

void display_start(void){ //Function to display start screen
  
  int xSize = 1000, ySize = 500; //Please don't screw with this too much...
  int height = 20;
  int col;
  //gfx_open(xSize, ySize, "3d Graphing");
  
while(1){
  
  //First title
  gfx_color(255,255,255);
  char string[] = "Polygons, Prisms, and Pyramids, OH MY!";
  col = xSize / 2 - (height / 2 +2) * strlen(string);  //Center a single line string
  print_string( string, 20, col, 990, 15/8.0*height);
  
  //Subtitle
  char string2[] = "A 3d graphing program";
  gfx_color(130, 200, 250);
  col = xSize / 2 - (height / 2) * strlen(string2);  //Center a single line string
  print_string( string2, ySize / 4, col, 980, height*3/2.0);
  
  //by line  
  char string3[] = "By sean fitzgerald and Kelly Gawne";
  gfx_color(90, 170, 40);
  col = xSize / 2 - (height / 2+1) * strlen(string2);  //Center a single line string
  print_string( string3, ySize*(1 / 3.0), col, 980, height);
  
  //Descrip
  char string4[] = "Choose a shape and watch it go!";
  gfx_color(255, 255, 255);
  col = xSize / 2 - (height / 2 +4) * strlen(string4)/2.0;  //Center a single line string
  print_string( string4, ySize*(2 / 3.0), col, 980, height);
  
  //Continue Button
  Button startbutton;
  startbutton.xcenter = xSize / 2;
  startbutton.ycenter = ySize / 2;
  startbutton.xsize = 100;
  startbutton.ysize = 50;
  strcpy(startbutton.string, "Begin");
	startbutton.filled = 0;
  
  gfx_color(205, 60, 90);  
  draw_button(startbutton);
  
  //Only continue if start button is clicked.
  while(gfx_event_waiting()){
  if(gfx_wait()==1){
    if(mouse_on_button(startbutton)) return;
  }
  }
}
}

void display_console(void){
  int height = 20;
  
  gfx_clear();
  while(1){
    //Divide screen in two
    gfx_color(0,135,140);
    gfx_line(500,0,500,500);
    
    //Create exit button
    gfx_color(255,0,0);  
    Button exit;
    exit.xsize = 30;
    exit.ysize = 20;
    exit.xcenter = 1000-exit.xsize/2.0;
    exit.ycenter = exit.ysize/2.0;
    strcpy(exit.string,"X");
    draw_button(exit);
    
    //Create add shape button
    gfx_color(240,15,25);  
    Button addshape;
    addshape.xsize = 190;
    addshape.ysize = 50;
    addshape.xcenter = 510 + addshape.xsize/2.0;
    addshape.ycenter = 490 - addshape.ysize/2.0;
    strcpy(addshape.string,"Add Shape ");
    draw_button(addshape);
    
    //Create go button to launch free sim
    gfx_color(255,235,40);  
    Button go;
    go.xsize = 80;
    go.ysize = 50;
    go.xcenter = 765;
    go.ycenter = addshape.ycenter;
    strcpy(go.string,"Go!");
    draw_button(go);
    
    //Create clear button to reset sim
    gfx_color(240,115,25);  
    Button clear;
    clear.xsize = 140;
    clear.ysize = 50;
    clear.xcenter = 900;
    clear.ycenter = addshape.ycenter;
    strcpy(clear.string,"Clear");
    draw_button(clear);
    
    //Direct User to choose a shape
    gfx_color(5,135,185);
    char string[50];
    strcpy(string, "Choose a shape:");
    print_string(string, height, 500 + 2 * (height/2), 1000-exit.xsize, height);
    
    //Direct User to choose a color
    gfx_color(5,135,185);
    strcpy(string, "Choose a color:");
    print_string(string, 250, 500 + 2 * (height/2), 1000, height);    

    
    while(gfx_event_waiting()){
      if(gfx_wait()==1){
	if(mouse_on_button(exit)) return;
      }
    }
  }
}

//again with the exploding structures.
int mouse_on_button(Button button){
    int x = gfx_xpos();
    int y = gfx_ypos();
    
    if((abs(x-button.xcenter) <= button.xsize/2.0) && (abs(y - button.ycenter) <= button.ysize/2.0)){
      return 1;
    }else{
      return 0;
    } 
}

void draw_button(Button button){
  int height = button.ysize*(1 / 2.0);
  
	//Create box
  gfx_line(button.xcenter - button.xsize/2, button.ycenter - button.ysize/2, button.xcenter - button.xsize/2, button.ycenter + button.ysize/2);
  gfx_line(button.xcenter - button.xsize/2, button.ycenter - button.ysize/2, button.xcenter + button.xsize/2, button.ycenter - button.ysize/2);
  gfx_line(button.xcenter + button.xsize/2, button.ycenter + button.ysize/2, button.xcenter - button.xsize/2, button.ycenter + button.ysize/2);
  gfx_line(button.xcenter + button.xsize/2, button.ycenter + button.ysize/2, button.xcenter + button.xsize/2, button.ycenter - button.ysize/2);
	

	
  //Center text in button
  float difference = (strlen(button.string)/2.0+0.5) * height/2.0;
  int colstart = button.xcenter - difference;
//   printf("char number: %f\twidth: %f\tdifference: %f\n",strlen(button.string)/2.0, height/2.0, difference);
//   printf("xcenter: %d\tfinal: %d\n", button.xcenter,colstart);
  
	int i;
	if(button.filled)
	{
		for (i = 1; i < (button.xsize); i++)
		{
			gfx_line(button.xcenter - button.xsize/2 + i, button.ycenter - button.ysize/2 + 1, button.xcenter - button.xsize/2 + i, button.ycenter + button.ysize/2 - 1);
		}
	
		gfx_color(0, 0, 0);
	
		print_string(button.string,  button.ycenter - height/2.0, colstart, button.xcenter + button.xsize / 2, height);
	}
	else
	{
		gfx_color(0, 0, 0);

		for (i = 1; i < (button.xsize); i++)
		{
			gfx_line(button.xcenter - button.xsize/2 + i, button.ycenter - button.ysize/2 + 1, button.xcenter - button.xsize/2 + i, button.ycenter + button.ysize/2 - 1);
		}
		
		gfx_color(255, 255, 255);
		print_string(button.string,  button.ycenter - height/2.0, colstart, button.xcenter + button.xsize / 2, height);
	}
	
	
}

void print_string( char string[], int row, int col, int colmax, int height){ //Colmax limits the length of a line, creating a textbox.
  int i, newcol = col;

  for ( i = 0; i < strlen(string); i++){ 
    if(((string[i] >= 'a') && (string[i] <= 'z')) || ((string[i] >= 'A') && (string[i] <= 'Z'))){ 
      //If letter, convert to lower, then print.   
      string[i] = tolower(string[i]);;
      print_letter(string[i], row, newcol, height);
    }else if (isdigit(string[i]) || string[i]=='.' || string[i] =='!' || string[i] == ','){
      //If it is another valid character, print.
      print_letter(string[i], row, newcol, height);
    }
    
    if (newcol + (3.5/5.0) * height >= colmax){
      row += 3/2.0 * height; // new line
      newcol = col;
    }else{
      newcol += (3.5/5.0) * height;
    }
  }
  
}
  
void print_letter( char letter, int row, int col, int height){
  switch (letter){
       case 'a':
	 A(row, col, height);
	 break;
       case 'b':
	  
	 B(row, col, height);
	 break;
       case 'c':
	  
	 C(row, col, height);
	 break;
       case 'd':
	  
	 D(row, col, height);
	 break;
       case 'e':
	  
	 E(row, col, height);
	 break;
       case 'f':
	  
	 F(row, col, height);
	 break;
       case 'g':
	  
	 G(row, col, height);
	 break;
       case 'h':
	  
	 H(row, col, height);
	 break;
       case 'i':
	  
	 I(row, col, height);
	 break;
       case 'j':
	  
	 J(row, col, height);
	 break;
       case 'k':
	  
	 K(row, col, height);
	 break;
       case 'l':
	  
	 L(row, col, height);
	 break;
       case 'm':
	  
	 M(row, col, height);
	 break;
       case 'n':
	  
	 N(row, col, height);
	 break;
       case 'o':
	  
	 O(row, col, height);
	 break;
       case 'p':
	  
	 P(row, col, height);
	 break;
       case 'q':
	  
	 Q(row, col, height);
	 break;
       case 'r':
	  
	 R(row, col, height);
	 break;
       case 's':
	  
	 S(row, col, height);
	 break;
       case 't':
	  
	 T(row, col, height);
	 break;
       case 'u':
	  
	 U(row, col, height);
	 break;
       case 'v':
	  
	 V(row, col, height);
	 break;
       case 'w':
	  
	 W(row, col, height);
	 break;
       case 'x':
	  
	 X(row, col, height);
	 break;
       case 'y':
	  
	 Y(row, col, height);
	 break;
       case 'z':
	 Z(row, col, height);
	 break;
       case '0':
	 draw_zero(row, col, height);
	 break;
       case '1':
	 draw_one(row, col, height);
	 break;
       case '2':
	 draw_two(row, col, height);
	 break;
       case '3':
	 draw_three(row, col, height);
	 break;
       case '4':
	 draw_four(row, col, height);
	 break;
       case '5':
	 draw_five(row, col, height);
	 break;
         case '6':
	 draw_six(row, col, height);
	 break;
       case '7':
	 draw_seven(row, col, height);
	 break;
       case '8':
	 draw_eight(row, col, height);
	 break;
       case '9':
	 draw_nine(row, col, height);
	 break;
       case '.':
	 draw_period(row, col, height);
	 break;
       case '!':
	 draw_exclaim(row, col, height);
	 break;
       case ',':
	 draw_comma(row, col, height);
	 break;
  }
}

void draw_arc(float alfa, float beta, float xPos, float yRad, float xRad, float yPos)
{
  float i;
  float xPoint, x2Point = xRad * cos(alfa) + xPos;
  float yPoint, y2Point = yRad * sin(alfa) + yPos;
  while (alfa >= beta)
    {
      beta += 2 * 3.14159;
    }
  i = alfa;
  for(i; i <= beta; i+=.1)
    {
      xPoint = xRad * cos(i) + xPos;
      yPoint = yRad * sin(i) + yPos;
      gfx_line(xPoint, yPoint, x2Point, y2Point); //NOTE: Replace w/ pixel_to_buffer...
      x2Point = xPoint;
      y2Point = yPoint;
    }

}

void A(int row, int column, int height){ //Column is the X direction, row is the Y direction!!
gfx_line(column + (75.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (75.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (100.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (60.0000 - 50) / 50 * height / 2, row + (166.0000 - 100) / 100 * height, column + (93.0000 - 50) / 50 * height / 2, row + (166.0000 - 100) / 100 * height);
}
void B(int row, int column, int height){
draw_arc(-1.7500, 1.0800, column + (69.000000 - 50) / 50 * height / 2,(23.00) / 100 * height,  (25.00) / 50 * height / 2, row + (123.000000 - 100) / 100 * height);
draw_arc(-1.3000, 1.5600,  column + (71.000000 - 50) / 50 * height / 2, (29.00) / 100 * height,(30.00) / 50 * height / 2, row + (172.000000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height, column + (75.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (72.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height);
}
void C(int row, int column, int height){
draw_arc(0.5300, 5.6200,column + (25.00) / 50 * height / 2, (50.00) / 100 * height, (75.000000 - 50) / 50 * height / 2, row + (151.000000 - 100) / 100 * height);
}
void D(int row, int column, int height){
draw_arc(4.8100, 7.8700, column + (75.000000 - 50) / 50 * height / 2,(50.00) / 100 * height,  (26.00) / 50 * height / 2, row + (151.000000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (70.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height, column + (73.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
}
void E(int row, int column, int height){
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (98.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height, column + (101.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (146.0000 - 100) / 100 * height, column + (84.0000 - 50) / 50 * height / 2, row + (146.0000 - 100) / 100 * height);
}
void F(int row, int column, int height){
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (99.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (144.0000 - 100) / 100 * height, column + (83.0000 - 50) / 50 * height / 2, row + (144.0000 - 100) / 100 * height);
}
void G(int row, int column, int height){
draw_arc(0.2100, 5.5800,column + (24.00) / 50 * height / 2, (50.00) / 100 * height, (74.000000 - 50) / 50 * height / 2, row + (151.000000 - 100) / 100 * height);
gfx_line(column + (78.0000 - 50) / 50 * height / 2, row + (160.0000 - 100) / 100 * height, column + (98.0000 - 50) / 50 * height / 2, row + (160.0000 - 100) / 100 * height);
}
void H(int row, int column, int height){
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (100.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (100.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (51.0000 - 50) / 50 * height / 2, row + (156.0000 - 100) / 100 * height, column + (100.0000 - 50) / 50 * height / 2, row + (156.0000 - 100) / 100 * height);
}
void I(int row, int column, int height){
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (100.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height);
gfx_line(column + (75.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (75.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height, column + (100.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
}
void J(int row, int column, int height){
draw_arc(-0.0000, 3.0100,column + (25.00) / 50 * height / 2, (40.00) / 100 * height, (75.000000 - 50) / 50 * height / 2, row + (161.000000 - 100) / 100 * height);
gfx_line(column + (100.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (100.0000 - 50) / 50 * height / 2, row + (164.0000 - 100) / 100 * height);
}
void K(int row, int column, int height){
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (51.0000 - 50) / 50 * height / 2, row + (147.0000 - 100) / 100 * height, column + (100.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (147.0000 - 100) / 100 * height, column + (85.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height);
}
void L(int row, int column, int height){
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height, column + (99.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
}
void M(int row, int column, int height){
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (75.0000 - 50) / 50 * height / 2, row + (141.0000 - 100) / 100 * height);
gfx_line(column + (100.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (100.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (100.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (76.0000 - 50) / 50 * height / 2, row + (140.0000 - 100) / 100 * height);
}
void N(int row, int column, int height){
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (100.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (100.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (100.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
}
void O(int row, int column, int height){
draw_arc(0.0000, 6.4000,column + (25.00) / 50 * height / 2, (50.00) / 100 * height, (75.000000 - 50) / 50 * height / 2, row + (151.000000 - 100) / 100 * height);
}
void P(int row, int column, int height){
draw_arc(4.7200, 7.6800, column + (73.000000 - 50) / 50 * height / 2, (25.00) / 100 * height, (25.00) / 50 * height / 2, row + (125.000000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (74.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (150.0000 - 100) / 100 * height, column + (74.0000 - 50) / 50 * height / 2, row + (150.0000 - 100) / 100 * height);
}
void Q(int row, int column, int height){
gfx_line(column + (81.0000 - 50) / 50 * height / 2, row + (169.0000 - 100) / 100 * height, column + (100.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
draw_arc(0.0000, 6.4000,column + (25.00) / 50 * height / 2, (46.00) / 100 * height, (76.000000 - 50) / 50 * height / 2, row + (155.000000 - 100) / 100 * height);
}
void R(int row, int column, int height){
  draw_arc(4.6700, 6.2700,  column + (76.000000 - 50) / 50 * height / 2,(52.00) / 100 * height, (25.00) / 50 * height / 2, row + (202.000000 - 100) / 100 * height);
draw_arc(4.7200, 7.6800, column + (73.000000 - 50) / 50 * height / 2, (25.00) / 100 * height, (25.00) / 50 * height / 2, row + (125.000000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (74.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (150.0000 - 100) / 100 * height, column + (74.0000 - 50) / 50 * height / 2, row + (150.0000 - 100) / 100 * height);
}
void S(int row, int column, int height){
draw_arc(2.0400, 6.0200,column + (20.00) / 50 * height / 2, (20.00) / 100 * height, (71.000000 - 50) / 50 * height / 2, row + (120.000000 - 100) / 100 * height);
draw_arc(-1.1200, 3.8400,column + (25.00) / 50 * height / 2, (25.00) / 100 * height, (75.000000 - 50) / 50 * height / 2, row + (176.000000 - 100) / 100 * height);
gfx_line(column + (62.0000 - 50) / 50 * height / 2, row + (138.0000 - 100) / 100 * height, column + (85.0000 - 50) / 50 * height / 2, row + (152.0000 - 100) / 100 * height);
}
void T(int row, int column, int height){
  gfx_line(column + (75.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (75.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (100.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height);
}
void U(int row, int column, int height){
draw_arc(0.0000, 3.2400,column + (25.00) / 50 * height / 2, (40.00) / 100 * height, (75.000000 - 50) / 50 * height / 2, row + (161.000000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (50.0000 - 50) / 50 * height / 2, row + (167.0000 - 100) / 100 * height);
gfx_line(column + (100.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (100.0000 - 50) / 50 * height / 2, row + (162.0000 - 100) / 100 * height);
}
void V(int row, int column, int height){
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (75.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (100.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (75.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
}
void W(int row, int column, int height){
  gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (60.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (75.0000 - 50) / 50 * height / 2, row + (150.0000 - 100) / 100 * height, column + (60.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (75.0000 - 50) / 50 * height / 2, row + (150.0000 - 100) / 100 * height, column + (90.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (90.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height, column + (100.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height);
}
void X(int row, int column, int height){
  gfx_line(column + (55.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (100.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (95.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
}
void Y(int row, int column, int height){
  gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (75.0000 - 50) / 50 * height / 2, row + (150.0000 - 100) / 100 * height);
gfx_line(column + (100.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (75.0000 - 50) / 50 * height / 2, row + (150.0000 - 100) / 100 * height);
gfx_line(column + (75.0000 - 50) / 50 * height / 2, row + (150.0000 - 100) / 100 * height, column + (75.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
}
void Z(int row, int column, int height){
  gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (100.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height);
gfx_line(column + (100.0000 - 50) / 50 * height / 2, row + (100.0000 - 100) / 100 * height, column + (51.0000 - 50) / 50 * height / 2, row + (199.0000 - 100) / 100 * height);
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height, column + (100.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (59.0000 - 50) / 50 * height / 2, row + (146.0000 - 100) / 100 * height, column + (96.0000 - 50) / 50 * height / 2, row + (146.0000 - 100) / 100 * height);
}

//And now the numbers!
void draw_zero(int row, int column, int height) {
  int width=height/2;
  draw_arc( 0, 2*M_PI, column + width/2,height/2,width/2, row + height/2);

}
void draw_one(int row, int column, int height) {
  int width=height/2;
  gfx_line(column+width/2,row,column+width/2,row+height);
}

void draw_two(int row, int column, int height) {
  int width=height/2;
  draw_arc(-M_PI, 0, column + width/2,height/4, width/2,row + height/4);
  gfx_line(column+width,row+height/4,column,row+height);
	gfx_line(column,row+height,column+width,row+height);
}

//Dem curves...
void draw_three(int row, int column, int height) {
  int width=height/2;
  draw_arc(-2*M_PI/3.0,M_PI/2, column+width/2, height/6, width/2.5, row+height/6);
  draw_arc(-M_PI/2,2/3.0*M_PI, column+width/2,height/3,width/2, row+height*2/3-1.0);
}

void draw_four(int row, int column, int height) {
  int width=height/2;
  gfx_line(column,row,column,row+height/2);
  gfx_line(column,row+height/2,column+width,row+height/2);
  gfx_line(column+3/4.0*width,row,column+3/4.0*width,row+height);
}

//But no seriously. Check out that 5.
void draw_five(int row, int column, int height) {
  int width=height/2;
  gfx_line(column,row,column+width,row);
  gfx_line(column,row,column,row+height/2.1);
  draw_arc(-1*M_PI,-M_PI/2, column+width/2,height/5.5,width/2,row+height/2);
  draw_arc(-1*M_PI/2,M_PI/2, column+width/2,height/3,width/2,row+height*2/3.0);
  draw_arc(M_PI/2,M_PI, column+width/2,height/4.1, width/2, row+3/4.0*height);
}

void draw_six(int row, int column, int height) {
  int width=height/2;
  draw_arc(-9/8.0*M_PI,-M_PI/4.0, column+width/2,height/2,width/1.9,row+height/2);
  draw_arc(0,2*M_PI, column+width/2,height/3,width/2,row+2/3.0*height);
}


void draw_seven(int row, int column, int height) {
  int width=height/2;
  gfx_line(column,row,column+width,row);
  gfx_line(column+width,row,column+width/4,row+height);
}

void draw_eight(int row, int column, int height) {
  int width=height/2;
  draw_arc(0,2*M_PI, column+width/2,height/6,width/2.5, row+height/6);
  draw_arc(0,2*M_PI, column+width/2,height/3, width/2, row+height*2/3-1.0);
}

void draw_nine(int row, int column, int height) {
  int width=height/2;
  draw_arc(0,2*M_PI, column+width/2,height/4,width/2, row+height/4);
 	gfx_line(column+width,row+height/6,column+width,row+height);
}

void draw_period(int row, int column, int height) {
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (195.0000 - 100) / 100 * height, column + (55.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (55.0000 - 50) / 50 * height / 2, row + (195.0000 - 100) / 100 * height, column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
}

void draw_comma(int row, int column, int height) {
draw_arc(-1.0500, 1.7800,column + (54.000000 - 50) / 50 * height / 2, (6.00) / 100 * height,  (5.00) / 50 * height / 2, row + (200.000000 - 100) / 100 * height);
}

void draw_exclaim(int row, int column, int height) {
gfx_line(column + (50.0000 - 50) / 50 * height / 2, row + (195.0000 - 100) / 100 * height, column + (55.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (55.0000 - 50) / 50 * height / 2, row + (195.0000 - 100) / 100 * height, column + (50.0000 - 50) / 50 * height / 2, row + (200.0000 - 100) / 100 * height);
gfx_line(column + (53.0000 - 50) / 50 * height / 2, row + (104.0000 - 100) / 100 * height, column + (53.0000 - 50) / 50 * height / 2, row + (185.0000 - 100) / 100 * height);
gfx_line(column + (54.0000 - 50) / 50 * height / 2, row + (104.0000 - 100) / 100 * height, column + (54.0000 - 50) / 50 * height / 2, row + (185.0000 - 100) / 100 * height);

}