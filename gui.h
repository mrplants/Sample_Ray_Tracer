//
//  main.h
//  
//
//  Created by Sean Fitzgerald on 11/28/12.
//
//

#ifndef GUI_H
#define GUI_H

#include "structs.h"

int is_clicked(Button button[], int numButtons);
//returns the number of the button that is clicked. -1 if no button has been clicked.

Button new_button(int topLeftColumn, int topLeftRow, int bottomRightColumn, int bottomRightRow, Color color, char* name);
//returns a new Button structure

TextBox new_textBox(int topLeftColumn, int topLeftRow, Color color, char* text, int height);
//returns a new TextBox structure

void draw_buttons_and_textBoxes(Button buttons[], int numButtons, TextBox textBoxes[], int numTextBoxes);
//clears the screen, then redraws all the buttons, filling them in if necessary, and prints the textBoxes

#endif
