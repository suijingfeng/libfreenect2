# GLFW3 Tutorials
Code for show kinect2's rgb image and depth image in seperate windows.

## Tutorial 1: glMultiWin

[This tutorial](http://blog.gvnott.com/2013/05/18/tutorial-multiple-windows-with-glfw3-and-glew-mx/) shows how to get multiply windows going with GLFW3 and GLEW MX.
I modify this tuterial to show rgb image, depth image, ir image and point cloud with four seperate windows.

![](https://github.com/suijingfeng/libfreenect2/blob/master/glMultiWin/doc/fourwin.png)


## Extra: Multi-Threaded Demo

This code is some attempts to add threading to the code from Tutorial 1. 
The idea was to have each window run on a seperate thread.
I just ported his code to ubuntu16.04 linux, provide a CMakeLists file. 

## dependency
* GLFW3, GLEW MX, GLM. for ubuntu16.04, sudo apt-get intall libglfw-dev libglfw3 libglewmx-dev libglm
* OpenCV 3.2.0 and PCL (if build cvPclGrabber)

## build
* cd libfreenect
* mkdir build
* cd build
* cmake ..
* make

## run
* cd bin/
* ./main or ./Kinect2Grabber

