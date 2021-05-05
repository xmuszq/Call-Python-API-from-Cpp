#include <iostream>
#include <pybind11/embed.h>
#include <pybind11/numpy.h>
#include <opencv2/opencv.hpp>

namespace py = pybind11;
 

int main() {
    py::scoped_interpreter guard{};

 

	/* 

	pass a cv Mat to python API, 2D and 3D; 
	cv mat <--> numpy 

	*/



	////////////////////////
	// Demo 5: pass a cv Mat to python API, 2D and 3D; 
	// - data flow: cv mat -->numpy-->pyapi-->return int numpy --> cv mat 
	// - 2D and 3D; 
	// - return unsigned int mat
	////////////////////////

    // import the API
    py::object cal = py::module::import("cal");

    // create an 2D cv mat in cpp
    unsigned int rows = 5;
    unsigned int cols = 3;
    cv::Mat cv_mat = cv::Mat::zeros(/*rows=*/rows, /*cols=*/cols, CV_8UC3);

    // convert 2d cv mat to numpy and pass it to python api 
	py::array_t<unsigned char> mat_py = py::array_t<unsigned char>({ cv_mat.rows,cv_mat.cols }, cv_mat.data);
    py::array_t<unsigned char> img_res1 = cal.attr("img_process")(mat_py); // use array_t<unsigned char> to define the return, as the return it's a numpy; not using py::object
    // convert the returned numpy to cpp cv mat
    py::buffer_info buf_img_res1 = img_res1.request();
    cv::Mat mat_buf_img_res1(buf_img_res1.shape[0], buf_img_res1.shape[1], CV_8UC1, (unsigned char*)buf_img_res1.ptr);
	std::cout << " returned numpy -> cv mat: channels, dims, rows and cols " << mat_buf_img_res1.channels()<< mat_buf_img_res1.dims << mat_buf_img_res1.rows << mat_buf_img_res1.cols << std::endl;
	// print out the cv mat
	std::cout << "returned cv mat = " << std::endl << " "  << mat_buf_img_res1 << std::endl << std::endl;


    // create a 3d matrix in cv
	cv::Mat mat_3d = cv::Mat::zeros(5, 5, CV_32FC(16));
    // convert 3d cv mat to py numpy and pass it to python api 
	py::array_t<unsigned char> dst = py::array_t<unsigned char>({ mat_3d.rows,mat_3d.cols,3}, mat_3d.data);
    py::array_t<unsigned char> img_res3 = cal.attr("img_process")(dst);
    // convert the returned numpy to cpp cv mat
    py::buffer_info buf_img_res3 = img_res3.request();
    cv::Mat mat_buf_img_res3(buf_img_res3.shape[0], buf_img_res3.shape[1], CV_8UC3, (unsigned char*)buf_img_res3.ptr);
	std::cout << " returned numpy -> cv mat: channels, dims, rows and cols " << mat_buf_img_res3.channels() << mat_buf_img_res3.dims << mat_buf_img_res3.rows << mat_buf_img_res3.cols << std::endl;


	////////////////////////
	// Demo 6: pass a cv Mat to python API, 2D; 
	// - data flow: cv mat -->numpy-->pyapi-->return int numpy --> cv mat 
	// - 2D; 
	// - return float mat
	////////////////////////

    py::array_t<float> img_res1_fl = cal.attr("img_process_return_float")(mat_py); // use array_t<unsigned char> to define the return, as the return it's a numpy; not using py::object
    // convert the returned numpy to cpp cv mat
    py::buffer_info buf_img_res1_fl = img_res1_fl.request();
    cv::Mat mat_buf_img_res1_fl(buf_img_res1_fl.shape[0], buf_img_res1_fl.shape[1], CV_32FC1, (float*)buf_img_res1_fl.ptr);
	std::cout << " returned numpy -> cv mat: channels, dims, rows and cols " << mat_buf_img_res1_fl.channels()<< mat_buf_img_res1_fl.dims << mat_buf_img_res1_fl.rows << mat_buf_img_res1_fl.cols << std::endl;
	// print out the cv mat
	std::cout << "returned cv mat = " << std::endl << " "  << mat_buf_img_res1_fl << std::endl << std::endl;






    /* 

	read an img in cpp with cv and 
	pass the img to DL model in python 

	*/

	////////////////////////
	// Demo 7: read an img in cpp with cv and pass the img to DL model (face detection) in python; 
	// - data flow: cv mat img -->numpy-->pyapi--> face detection
	// 
	////////////////////////


	// read img in cpp, plot it and save it
    std::string image_path="../data/2.jpg";  
    cv::Mat img_cpp = cv::imread(image_path, cv::IMREAD_COLOR);
	std::cout << "img w and h : " << img_cpp.cols << img_cpp.rows << std::endl;
	// check 
    if(img_cpp.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
	// plot in cpp
    cv::imshow("Display window", img_cpp);
	// save in cpp if needed, press 's' key to save
    int k = cv::waitKey(0); // Wait for a keystroke in the window
    if(k == 's')
    {
        cv::imwrite("../data/cpp_write.png", img_cpp);
    }
	// pass the img to python api - cal 
	py::array_t<unsigned char> py_img_dst = py::array_t<unsigned char>({ img_cpp.rows,img_cpp.cols,3}, img_cpp.data);
    py::object py_img_dst_return_1 = cal.attr("img_process")(py_img_dst);
	// pass img to python api - dl_model
	py::object dl_model = py::module::import("dl_model");
	py::object py_img_dst_return_2 = dl_model.attr("face_detect")(py_img_dst);


 
}
