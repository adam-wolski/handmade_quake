/* 
 * Most of the X11 code is based or even basicly copied from A Brief intro to X11 Programming.
 * http://math.msu.su/~vvb/2course/Borisenko/CppProjects/GWindow/xintro.html
 * So thanks to bhammond@blaze.cba.uga.edu
 */
#include "quakedef.h"

_Xconst char* WINDOW_TITLE = "Quake";
uint32 WINDOW_WIDTH = 800;
uint32 WINDOW_HEIGHT = 600;

Display *dis;
int screen;
Window win;
GC gc;

void vid_init() {
	/* get the colors black and white */
	unsigned long black,white;

	/* use the information from the environment variable DISPLAY 
	   to create the X connection:
	*/	
	dis=XOpenDisplay((char *)0);
   	screen=DefaultScreen(dis);
	black=BlackPixel(dis,screen),	/* get color black */
	white=WhitePixel(dis, screen);  /* get color white */

	/* once the display is initialized, create the window.
	   It will have the foreground white and background black
	*/
   	win=XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,	
		WINDOW_WIDTH, WINDOW_HEIGHT, 0, white, black);

	/* here is where some properties of the window can be set.
	   The third and fourth items indicate the name which appears
	   at the top of the window and the name of the minimized window
	   respectively.
	*/
	XSetStandardProperties(dis,win, WINDOW_TITLE,"",None,NULL,0,NULL);

	/* this routine determines which types of input are allowed in
	   the input.  see the appropriate section for details...
	*/
	XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);

	/* create the Graphics Context */
        gc=XCreateGC(dis, win, 0,0);        

	/* here is another routine to set the foreground and background
	   colors _currently_ in use in the window.
	*/
	XSetBackground(dis,gc,white);
	XSetForeground(dis,gc,black);

	/* clear the window and bring it on top of the other windows */
	XClearWindow(dis, win);
	XMapRaised(dis, win);
}

void vid_close() {
/* it is good programming practice to return system resources to the 
   system...
*/
        XFreeGC(dis, gc);
        XDestroyWindow(dis,win);
        XCloseDisplay(dis);	
        exit(0);
}

void vid_redraw() {
	XClearWindow(dis, win);
}
