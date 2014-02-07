#pragma once

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>                                  
#include <opencv2/features2d/features2d.hpp>                          
#include "opencv2/core/core.hpp"                                      
#include <stdio.h>                                                    
#include <vector>  
#include <string>

void extract_sift(std::string tmp_name, cv::Mat_<double>& test_descriptors, std::vector<cv::KeyPoint>& test_keypoints);

void visualize_keypoint(std::vector<int> res, std::vector<cv::KeyPoint>&test_keypoints ,cv::Mat& res_img);
