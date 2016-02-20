#include "quakedef.h"
#include <time.h>

/*
 * ################################################################################################
 *                                             Timer
 * ################################################################################################
 */

/*
===============================================================================================
        Function: sys_get_time
        Returns elapsed time in seconds since first call of this funtion.
===============================================================================================
*/
f64 sys_get_time()
{
        struct timeval tp;  
        static int secbase;

        gettimeofday(&tp, NULL);

        if (!secbase) {
                secbase = tp.tv_sec;
                return tp.tv_usec/1000000.0;
        }

        return (tp.tv_sec - secbase) + tp.tv_usec/1000000.0;
}

/*
===============================================================================================
        Function: sys_capture_events
        TODO
===============================================================================================
*/
void sys_capture_events() {
        XEvent event;		/* the XEvent declaration !!! */
	KeySym key;		/* a dealie-bob to handle KeyPress Events */	
	char text[255];		/* a char buffer for KeyPress Events */

	/* look for events forever... */
	while(1) {		
		/* get the next event and stuff it into our event variable.
		   Note:  only events we set the mask for are detected!
		*/
		XNextEvent(dis, &event);
	
		if (event.type==Expose && event.xexpose.count==0) {
		/* the window was exposed redraw it! */
			vid_redraw();
		}
		if (event.type==KeyPress&&
		    XLookupString(&event.xkey,text,255,&key,0)==1) {
		/* use the XLookupString routine to convert the invent
		   KeyPress data into regular text.  Weird but necessary...
		*/
			if (text[0]=='q') {
				vid_close();
			}
			printf("You pressed the %c key!\n",text[0]);
		}
		if (event.type==ButtonPress) {
		/* tell where the mouse Button was Pressed */
			printf("You pressed a button at (%i,%i)\n",
				event.xbutton.x,event.xbutton.y);
		}
	}
}
