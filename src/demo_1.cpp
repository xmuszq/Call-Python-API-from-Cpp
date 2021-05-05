#include <iostream>
#include <string>
#include <vector>
#include <pybind11/embed.h> // everything needed for embedding
namespace py = pybind11;

int main(int argc, char** argv)
{
  py::scoped_interpreter guard{}; // start the interpreter of python and keep it alive

  //////////////////// 
  // Demo 1: 
  // exacuate a simple inline python function in cpp
  ///////////////////
  
  py::print("printd from python - Hello, World!"); // note: string needs to use "", not '' in cpp


  //////////////////// 
  // Demo 2: 
  // import python packages installed in the system
  ///////////////////

  py::object sys = py::module::import("sys");
  std::string sys_version = sys.attr("version").cast<std::string>();
  std::cout << "sys version: " << sys_version << std::endl;
  py::object scipy = py::module::import("scipy");
  std::string scipy_version = scipy.attr("__version__").cast<std::string>();
  std::cout << "scipy version: " << scipy_version << std::endl;
 

  //////////////////// 
  // Demo 3: 
  // -import a self made function in python 
  // -scalar as arguments, pass forth and back 
  ///////////////////
  // import the API
  py::object cal = py::module::import("cal");
  float a = 1.1;
  float b = 2.2;
  py::object res_ceil = cal.attr("add_ceil")(a, b); // the add_ceil uses math package in python
  int n1 = res_ceil.cast<int>();
  std::cout << "calulation results from cpp: " << n1 << std::endl;


  //////////////////// 
  // Demo 4: 
  // -import a self made function in python
  // -string as arguments, pass forth and back 
  ///////////////////

  std::string s1 = "Hello"; 
  std::string s2 = "world"; 
  py::object sp = cal.attr("str_process")(s1, s2);
  std::string s = sp.cast<std::string>();
  std::cout << "calulation results from cpp: " << s << std::endl;
 
/*
  // import a self made function in python
  // vector as arguments
  std::vector<int>  v1; 
  v1.assign(5,10);

  py::object pv = cal.attr("vector_process")(v1);
  for (int i = 0; i < pv.size(); i++)
	std::cout << pv[i] << " ";

  std::vector<int> cv = pv.cast<std::vector<int>>();
  std::cout << "from cpp, the vector elements are: ";
  for (int i = 0; i < cv.size(); i++)
	std::cout << cv[i] << " ";
*/
 
  return 0;
}
