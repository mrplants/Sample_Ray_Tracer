main: main.c
	gcc main.c gfx.c buffer.c matrix.c menu.c 3DStuff.c color.c letters.c -o main -lm -lc -lX11 -L/usr/X11/lib -L/System/ -Wall -O4
	
buffer: buffer.c
	gcc buffer.c gfx.c structs.c -o buffer -lm -lX11 -L/usr/X11/lib -L/System/ -Wall
		
gfx: gfx.c
	gcc gfx.c -o gfx -lm -lX11 -L/usr/X11/lib -Wall

letters:letters.c
	gcc letters.c -o letters gfx.c -lm -lX11 -L/usr/X11/lib -Wall


clean:
	rm -f main
