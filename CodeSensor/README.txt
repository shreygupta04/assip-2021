#1 Compile the code
	#compile in release mode
	cmake -DCMAKE_BUILD_TYPE="Release"
	make -j8
 
	#compile in debug mode
	cmake -DCMAKE_BUILD_TYPE="Debug"
	make -j8

#2 Run the code
	./bin/Runner GMainProgram data/ParamsSceneMaze.txt

* Right click on the window to see the menu.
(a) From the Draw menu, click on 3D to turn 3D rendering off

(b) From the Sensor menu, click on "mouse control" to allow mouse clicks

(c) Use the left mouse button to click anywhere. It should show the
cells that have been sensed (purple color for free cells, and black
color for occupied cells). Repeat this process several times clicking
on different parts of the scene.

(d) From the Scene menu, click on "draw obstacles" to turn off
obstacle rendering. This will allow you to better see the boundary of
the obstacles that are being sensed.
 
