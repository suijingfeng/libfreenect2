# GLFW3 Tutorials

Code for my tutorials on using GLFW3.

## Tutorial 1: glMultiWin

[This tutorial](http://blog.gvnott.com/2013/05/18/tutorial-multiple-windows-with-glfw3-and-glew-mx/) shows how to get mulitpuls windows going with GLFW3 and GLEW MX. and I modify it to show rgb image and depth image with two seperate windows.

![](https://github.com/suijingfeng/libfreenect2/tree/master/glMultiWin/doc/succeed.png)

## Extra: Multi-Threaded Demo

This code is some attempts I made to add threading to the code from Tutorial 1. The idea was to have each window run on a seperate thread.

I just ported his code to ubuntu16.04 linux, provide a CMakeLists file. 
