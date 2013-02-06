//
//  main.c
//  
//
//  Created by Sean Fitzgerald on 11/28/12.
//
//

#include <stdio.h>
#include "gui.h"
#include "gfx.h"
#include "menu.h"

int is_clicked(Button buttons[], int numButtons)
{
	int i, column = gfx_xpos(), row = gfx_ypos();
	for(i = 0; i < numButtons; i++)
	{
		if((column <= buttons[i].topLeftColumn)
		&& (column >= buttons[i].bottomRightColumn)
		&& (row >= buttons[i].topLeftRow)
		&& (row <= buttons[i].bottomRightRow))
			return i;
	}
	return -1;
}

Button new_button(int topLeftColumn, int topLeftRow, int bottomRightColumn, int bottomRightRow, Color color, char* name)
{
	Button newButton;
	
	newButton.topLeftColumn = topLeftColumn;
	newButton.topLeftRow = topLeftRow;
	newButton.bottomRightColumn = bottomRightColumn;
	newButton.bottomRightRow = bottomRightRow;
	newButton.color = color;
	newButton.name = name;
	
	return newButton;
}

TextBox new_textBox(int topLeftColumn, int topLeftRow, Color color, char* text, int height)
{
	TextBox newTextBox;
	
	newTextBox.topLeftColumn = topLeftColumn;
	newTextBox.topLeftRow = topLeftRow;
	newTextBox.color = color;
	newTextBox.text = text;
	newTextBox.height = height;
	
	return newTextBox;
}

void draw_buttons_and_textBoxes(Button buttons[], int numButtons, TextBox textBoxes[], int numTextBoxes)
{
	gfx_clear();
	
	int i, j;
	for(i = 0; i < numButtons; i++)
	{
		gfx_color(buttons[i].color.red, buttons[i].color.green, buttons[i].color.blue);
		
		if(buttons[i].filled)
		{
			for(j = 0; j < (buttons[i].bottomRightColumn - buttons[i].topLeftColumn); j++)
					{
						gfx_line(j, buttons[i].topLeftRow, j, buttons[i].bottomRightRow);
					}
		}
		else
		{
			gfx_line(buttons[i].topLeftColumn, buttons[i].topLeftRow, buttons[i].bottomRightColumn, buttons[i].topLeftRow);
			gfx_line(buttons[i].topLeftColumn, buttons[i].topLeftRow, buttons[i].topLeftColumn, buttons[i].bottomRightRow);
			gfx_line(buttons[i].bottomRightColumn, buttons[i].topLeftRow, buttons[i].bottomRightColumn, buttons[i].bottomRightRow);
			gfx_line(buttons[i].bottomRightColumn, buttons[i].bottomRightRow, buttons[i].topLeftColumn, buttons[i].bottomRightRow);
		}
	}
	
	for(i = 0; i < numTextBoxes; i++)
	{
		//prinLine(textBoxes[i].topLeftColumn, textBoxes[i].topLeftRow, textBoxes[i].color, textBoxes[i].text, textBoxes[i].height);
	}
}