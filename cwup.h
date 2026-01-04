#ifndef XFILE_H
#define XFILE_H

/* Handle Cross-Platform X11 Headers */
#ifdef _WIN32
    #include "X11_win32_compat.h"
#else
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/Xresource.h>
#endif

/* Struct Definition 
   We keep this in the header so other files can see the width/height 
   and the buffer if they need to! */
typedef struct {
    Display *dpy;
    Window win;
    Pixmap buffer;
    GC pen;
    int width;
    int height;
} XFile;

/* Global Variables
   Using 'extern' tells the compiler these exist in the compiled .o file
   so other scripts can access the display or window handles! :3 */
extern int screen_num, width, height;
extern Window win;
extern Display *dpy;
extern GC pen;

/* Function Prototypes */

// Initializes the X Display and creates the window
int initialise();

// Allocates and sets up the XFile abstraction and back-buffer
XFile* xfile_open(Display *d, Window w, GC p, int w_width, int w_height);

// Draws a single pixel to the buffer and copies it to the window
void xfile_put_pixel(XFile *xf, int x, int y, unsigned long color);

// Helper to convert R, G, B values (0-255) to an X11 color long
unsigned long _RGB(int r, int g, int b);

// Handles events like window exposes or resizing
int displayFrame(XFile *display_file);

#endif
