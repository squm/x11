#include<stdlib.h>
#include<X11/Xlib.h>
#include<string.h>
#include<stdio.h>

#define NCOLORS 3
const char *const assoc[] = {
  "()       function call                      left-to-right",
	"[]       array element                                   ",
	".        structure or union member                       ",
	"->       pointer reference to structure                  ",
	//  "─────────────────────────────────────────────────────────",
	"                                                         ",
	"!        logical not                        right-to-left",
	"~        bitwise complement                              ",
	"-        unary minus                                     ",
	"++       increment                                       ",
	"--       decrement                                       ",
	"&        address of                                      ",
	"*        contents of                                     ",
	"(type)   cast to type                                    ",
	"sizeof   size in bytes                                   ",
	//  "─────────────────────────────────────────────────────────",
	"                                                         ",
	"*        multiply                           left-to-right",
	"/        divide                                          ",
	"%        remainder                                       ",
	//  "─────────────────────────────────────────────────────────",
	"                                                         ",
	"+        add                                left-to-right",
	"-        subtract                                        ",
	//  "─────────────────────────────────────────────────────────",
	"                                                         ",
	"<<       bitwise left shift                 left-to-right",
	">>       bitwise right shift                             ",
	//  "─────────────────────────────────────────────────────────",
	"                                                         ",
	"<        arithmetic less than               left-to-right",
	">        arithmetic greater than                         ",
	"<=       arithmetic l than or equal to                   ",
	">=       arithmetic g than or equal to                   ",
	//  "─────────────────────────────────────────────────────────",
	"                                                         ",
	"==       arithmetic equal                   left-to-right",
	"!=       arithmetic not equal                            ",
	//  "─────────────────────────────────────────────────────────",
	"                                                         ",
	"&        bitwise and                        left-to-right",
	"^        bitwise exclusive or               left-to-right",
	"|        bitwise or                         left-to-right",
	"&&       logical and                        left-to-right",
	"||       logical or                         left-to-right",
	"? :      conditional expression             right-to-left",
	"=        assignment operator                right-to-left",
	",        sequential expression              left-to-right"
};
	void
load_font(Display *dpy, XFontStruct **font_info) {
	const char *fontname = "9x15";
	/* Access font */
	if ((*font_info = XLoadQueryFont(dpy, fontname)) == NULL)
	{
		(void) fprintf( stderr, "Basic: Cannot open font: %s\n", fontname);
		exit( -1 );
	}
}
	void
draw_assoc(Display *dpy, Pixmap pix, GC g, XFontStruct *font_info) {
	const int x_offset = 15;
	const int y_offset = 15;
	const int font_height = font_info->ascent + font_info->descent;
	const int rowlen = strlen(assoc[1]);

	int row = row;
	for (row = sizeof(assoc) / sizeof(assoc[1]); row--;) {
		XDrawString(dpy, pix, g, x_offset, y_offset + font_height * row, assoc[row], rowlen);
	}
}
	int
main () {
	Display *dpy;
	Window root;
	XWindowAttributes wa;
	GC g;
	Pixmap pix;
	const unsigned long color_green = 0x12EE12;

	/* open the display (connect to the X server) */
	dpy = XOpenDisplay (getenv ("DISPLAY"));

	/* get the root window */
	root = DefaultRootWindow (dpy);


	/* get attributes of the root window */
	XGetWindowAttributes(dpy, root, &wa);


	/* create a GC for drawing */
	g = XCreateGC (dpy, root, 0, NULL);


	/* create a pixmap as large as the root window */
	pix = XCreatePixmap (dpy, root, wa.width, wa.height, wa.depth);

	/* clear the pixmap (not done by default) */
	//  XSetForeground(dpy, g, WhitePixelOfScreen(DefaultScreenOfDisplay(dpy)) );
	//  XSetForeground(dpy, g, BlackPixelOfScreen(DefaultScreenOfDisplay(dpy)) );
	//  XFillRectangle (dpy, pix, g, 0, 0, wa.width, wa.height);

	XSetForeground(dpy, g, color_green);

	/* set the pixmap as the background of the root window */
	XSetWindowBackgroundPixmap (dpy, root, pix);

	XFontStruct *font_info;
	load_font(dpy, &font_info);
	draw_assoc(dpy, pix, g, font_info);

	/* clear the root window to make the pixmap visible */
	XClearWindow (dpy, root);

	XCloseDisplay (dpy);

	return 0;
}
