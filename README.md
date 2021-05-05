Call python API from Cpp. 

There are many demos/examples show how to call Cpp API from Python. But very few are talking about the other way, call Python API from Cpp. Although Python is slow when compared to Cpp, it has little difference when using Python to run DL models as most of calculations are done within the model and not related to Python. Since it's easier to run DL models in Python, it's possible to setup DL runing environment in Python and simply call the Python API from Cpp to make the job done. 

In this repo, we provide several demos representing different scenarios when calling Python API from Cpp:

	  //////////////////// 
	  // Demo 1: 
	  // exacuate a simple inline python function in cpp
	  ///////////////////

	  //////////////////// 
	  // Demo 2: 
	  // import python packages installed in the system
	  ///////////////////

	  //////////////////// 
	  // Demo 3: 
	  // -import a self made function in python 
	  // -scalar as arguments, pass forth and back 
	  ///////////////////

	  //////////////////// 
	  // Demo 4: 
	  // -import a self made function in python
	  // -string as arguments, pass forth and back 
	  ///////////////////


	////////////////////////
	// Demo 5: pass a cv Mat to python API, 2D and 3D; 
	// - data flow: cv mat -->numpy-->pyapi-->return int numpy --> cv mat 
	// - 2D and 3D; 
	// - return unsigned int mat
	////////////////////////
 

	////////////////////////
	// Demo 6: pass a cv Mat to python API, 2D; 
	// - data flow: cv mat -->numpy-->pyapi-->return int numpy --> cv mat 
	// - 2D; 
	// - return float mat
	////////////////////////
 

	////////////////////////
	// Demo 7: read an img in cpp with cv and pass the img to DL model (face detection) in python; 
	// - data flow: cv mat img -->numpy-->pyapi--> face detection
	// 
	////////////////////////

To embedding the Python interpreter, the Pybind11 package is used ( it's located in the sub-folder 'pyind11').  

Requirements:
		
		cmake
		make
		mediapipe (to run demo 5-7)
		Python3



How to run the demos:

0. git clone the repo;

1. expose the 'src' folder to the system so that the building process can find the source files. An example:

	export PYTHONPATH=$PYTHONPATH:/home/zhen/Projects/PyAPI4Cpp/call-python-from-cpp/src

2. go to the build directory, (if not exist, create a 'build' folder under the './call-python-from-cpp'), do following:
	cmake ..
	make

3. to run the demo_2.cpp, contains demo 5 to demo 7, as it need to run DL models, you need to install the 'mediapipe' from Google. Install the medianpipe in the system, not in python virtual environment. As if you install it on local python virtual environment, the building process will not be able to find it. 

4. in build directory, run:
	./demo_1
	or 
	./demo_2



 





 
