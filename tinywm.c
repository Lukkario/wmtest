/* TinyWM is written by Nick Welch <nick@incise.org> in 2005 & 2011.
 *
 * This software is in the public domain
 * and is provided AS IS, with NO WARRANTY. */

#include <X11/Xlib.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

void swallow_keystroke(Display * dpy, XEvent * ev)
{
	XAllowEvents(dpy, AsyncKeyboard, ev->xkey.time);
}

int main(void)
{
    Display * dpy;
    XWindowAttributes attr;
    XButtonEvent start;
    XEvent ev;
    KeyCode F2;

    if(!(dpy = XOpenDisplay(0x0))) return 1;

    Window root = XDefaultRootWindow(dpy);

    F2 = XKeysymToKeycode(dpy, XStringToKeysym("F2"));
    XGrabKey(dpy, F2, AnyModifier, DefaultRootWindow(dpy), 1, GrabModeAsync, GrabModeAsync);
 //   XSelectInput(dpy, root, ButtonPressMask);

    //XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("F1")), Mod1Mask,
    //        DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);
    XGrabButton(dpy, 1, Mod1Mask, DefaultRootWindow(dpy), True, ButtonPressMask|ButtonReleaseMask|PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None);
    //XGrabButton(dpy, 3, Mod1Mask, DefaultRootWindow(dpy), True,
    //        ButtonPressMask|ButtonReleaseMask|PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None);

    start.subwindow = None;
    system("polybar example &");
    for(;;)
    {
        XNextEvent(dpy, &ev);
	//if(ev.type == KeyPress && ev.xkey.subwindow != None)
            //XRaiseWindow(dpy, ev.xkey.subwindow);
	   // system("rofi -show run");
	if(ev.type == KeyPress)
	{	
		if(ev.xkey.keycode == F2 && ev.xkey.state & Mod1Mask)
		{
			//system("notify-send Pressed Alt+F2");
			system("rofi -show run");
			swallow_keystroke(dpy, &ev);
		}
	}

        else if( (ev.type == ButtonPress || ev.xbutton.button == Button1))// && ev.xbutton.subwindow != None)
        {
	    system("notify-send clicked");
	    //XSetWMHints(dpy, start.subwindow, &xwmh);
	    //XGrabPointer(dpy, ev.xbutton.subwindow, True, PointerMotionMask|ButtonReleaseMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
            //XGetWindowAttributes(dpy, ev.xbutton.subwindow, &attr);
            //start = ev.xbutton;
	    /*int xdiff = ev.xbutton.x_root - start.x_root;
	    int ydiff = ev.xbutton.y_root - start.y_root;
	    XMoveWindow(dpy, start.subwindow,
		attr.x + (start.button==1 ? xdiff : 0),
		attr.y + (start.button==1 ? ydiff : 0));*/
        }
        else if(ev.type == MotionNotify && start.subwindow != None)
        {
            int xdiff = ev.xbutton.x_root - start.x_root;
            int ydiff = ev.xbutton.y_root - start.y_root;
            XMoveResizeWindow(dpy, start.subwindow,
                attr.x + (start.button==1 ? xdiff : 0),
                attr.y + (start.button==1 ? ydiff : 0),
                MAX(1, attr.width + (start.button==3 ? xdiff : 0)),
                MAX(1, attr.height + (start.button==3 ? ydiff : 0)));
        }
        else if(ev.type == ButtonRelease)
	{
            start.subwindow = None;
	    XUngrabPointer(dpy, CurrentTime);
	}
    }
}

