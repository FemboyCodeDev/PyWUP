import pywup

pywup.initialise()
print("start")
xfile = pywup.xfile_open()
print("end")
#pywup.run_test()
while True:
	pywup.displayFrame(xfile)
