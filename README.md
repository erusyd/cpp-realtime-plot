# cpp-realtime-plot
realtime plot in c++ using matplotpp https://github.com/yuichikatori/matplotpp
two threads: one for plotting and another for feed data
one class to handle plot and another to generate data

# todo
add explanations
clean code

# remarks
ploting library use glut then no other way to use singleton design pattern to pass glut callback function (cf. http://paulsolt.com/blog/2009/07/openglglut-classes-oop-and-problems)
