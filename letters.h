
//
// letters.h Created by Kelly D Gawne on 11/28/12.
//
//

#ifndef _LETTERS_H
#define _LETTERS_H


typedef struct Button {
  int xcenter;
  int ycenter;
  int xsize;
  int ysize;
  char string[50];
	int filled;
} Button;

//Display start up screen
void display_start(void);

//Display main console
void display_console(void);

// //Print a button.
void draw_button(Button button);

//Check to see if the mouse is on a button (use after they click)
int mouse_on_button(Button button);

//Prints a given string at location (row, col), wrapping at rowmax.
void print_string( char string[100], int row, int col, int rowmax, int height);
//Prints the given letter
void print_letter( char letter, int row, int col, int height);

//Draws an arc. Yeah, don't ask about the order.
void draw_arc(float alfa, float beta, float xPos, float yRad, float xRad, float yPos);

//Each function draws its respective letter to the screen. THANKS KELLY!!!

void A(int row, int column, int height); //Column is the X direction, row is the Y direction!!
void B(int row, int column, int height);
void C(int row, int column, int height);
void D(int row, int column, int height);
void E(int row, int column, int height);
void F(int row, int column, int height);
void G(int row, int column, int height);
void H(int row, int column, int height);
void I(int row, int column, int height);
void J(int row, int column, int height);
void K(int row, int column, int height);
void L(int row, int column, int height);
void M(int row, int column, int height);
void N(int row, int column, int height);
void O(int row, int column, int height);
void P(int row, int column, int height);
void Q(int row, int column, int height);
void R(int row, int column, int height);
void S(int row, int column, int height);
void T(int row, int column, int height);
void U(int row, int column, int height);
void V(int row, int column, int height);
void W(int row, int column, int height);
void X(int row, int column, int height);
void Y(int row, int column, int height);
void Z(int row, int column, int height);

//And now the numbers!
void draw_zero(int row, int column, int height);
void draw_one(int row, int column, int height);
void draw_two(int row, int column, int height);
void draw_three(int row, int column, int height);//Dem curves...
void draw_four(int row, int column, int height);
void draw_five(int row, int column, int height);//But no seriously. Check out that 5.
void draw_six(int row, int column, int height);
void draw_seven(int row, int column, int height);
void draw_eight(int row, int column, int height);
void draw_nine(int row, int column, int height);

// And some punks
void draw_period(int row, int column, int height);
void draw_comma(int row, int column, int height);
void draw_exclaim(int row, int column, int height);




#endif
