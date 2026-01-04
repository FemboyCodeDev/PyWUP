#include "cwup.h"
#include <stdio.h>
#define PY_SSIZE_T_CLEAN
#include <Python.h>

int main(int argc, char *argv[]){

	printf("main in pywup \n");
	return 0;
}



static PyObject * run_test(PyObject *self, PyObject *args){

        initialise();
        XFile *display_file = xfile_open(dpy, win, pen, width, height);
        for (int i = 0; i < 40; i++){
                xfile_put_pixel(display_file, i, 20, WhitePixel(dpy, screen_num));

        }
        for (int x = 0; x < 512; x++){
                for (int y = 0; y < 512;y++){
                        float u = (float)x / 512;
                        float v = (float)y / 512;
                        xfile_put_pixel(display_file, x, y, _RGB((int)(u*255),(int)(v*255),0));
        }
        }
        while (1){
                displayFrame(display_file);
        }


        Py_RETURN_NONE;
}



static PyObject * pywup_initialise(PyObject *self, PyObject *args){
	initialise();
	Py_RETURN_NONE;
}


static XFile * pywup_xfile_open(){
	return xfile_open(dpy, win, pen, width, height);

}

static PyObject * pywup_displayFrame(XFile *display_file){
	displayFrame(display_file);
	Py_RETURN_NONE;

}


static PyMethodDef pywup_methods[] = {
        {"run_test", (PyCFunction)run_test, METH_VARARGS, "Runs the X11 test loop"},
        {"initialise", (PyCFunction)pywup_initialise, METH_NOARGS, "Initializes X11"},
	{"xfile_open", (PyCFunction)pywup_xfile_open, METH_NOARGS, "Opens an xfile"},
	{"displayFrame", (PyCFunction)pywup_displayFrame, METH_VARARGS, "Displays the frame"},
        {NULL, NULL, 0, NULL}

};

/* Module definition */
static struct PyModuleDef pywupmodule = {
    PyModuleDef_HEAD_INIT,
    "pywup",   /* name of module */
    NULL,      /* module documentation, may be NULL */
    -1,        /* size of per-interpreter state of the module */
    pywup_methods
};


/* Module initialization function */
PyMODINIT_FUNC PyInit_pywup(void) {
    return PyModule_Create(&pywupmodule);
}

