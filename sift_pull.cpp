#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "opencv2/core/core.hpp"
#include <stdio.h>
#include <vector>
#include <string>


void visualize_keypoint(std::vector<int> res, std::vector<cv::KeyPoint>&test_keypoints ,cv::Mat& res_img) {

cv::Scalar red = (0,0,256);
cv::Scalar green = (0,256,0);

std::vector<cv::KeyPoint> good_keypoints;
std::vector<cv::KeyPoint> mal_keypoints;

int count_neg = 0;
int count_pos = 0;

for(size_t i = 0; i < res.size(); ++i ) {
  if (res[i] == 0) {
        good_keypoints.push_back(test_keypoints[i]);
	count_neg += 1;
  } else {
        mal_keypoints.push_back(test_keypoints[i]);
	count_pos += 1;
  }
}

cv::Mat img_keypoints = res_img.clone();

cv::drawKeypoints( res_img, mal_keypoints, img_keypoints, red);
cv::imwrite("res.png", img_keypoints);

std::cout << count_pos << "@@" << count_neg << std::endl;
if(count_pos >= count_neg){
  std::cout << "pos" << std::endl;
} else {
  std::cout << "neg" << std::endl;
}

//cv::imshow("Keypoints 1", img_keypoints );

}




void sift_calc(std::string pos_name, std::string neg_name, std::string test_name){ 
 
    //pos
    cv::Mat_<double> pos;
    std::vector<cv::KeyPoint> pos_keypoints; 
    cv::Mat colorImg0 = cv::imread(pos_name);

    if(colorImg0.empty()){
        std::cout << "No Image" << std::endl;
        return ;
    }

    cv::Mat grayImg0;
    cv::cvtColor(colorImg0, grayImg0, CV_BGR2GRAY);
    cv::normalize(grayImg0, grayImg0, 0, 255, cv::NORM_MINMAX);

    cv::SiftFeatureDetector detector;
    cv::SiftDescriptorExtractor extractor;

    detector.detect(grayImg0, pos_keypoints);
    extractor.compute(grayImg0, pos_keypoints, pos);
    std::cout << "size of positive ketpoints" << pos_keypoints.size() << std::endl;
 

    //neg
    cv::Mat_<double> neg;
    std::vector<cv::KeyPoint> neg_keypoints;
    cv::Mat colorImg1 = cv::imread(neg_name);

    if(colorImg1.empty()){
        std::cout << "No Image" << std::endl;
        return ;
    }

    cv::Mat grayImg1;
    cv::cvtColor(colorImg1, grayImg1, CV_BGR2GRAY);
    cv::normalize(grayImg1, grayImg1, 0, 255, cv::NORM_MINMAX);

    detector.detect(grayImg1, neg_keypoints);
    extractor.compute(grayImg1, neg_keypoints, neg);
    std::cout << "size of negative ketpoints" << neg_keypoints.size() << std::endl;



    //test
    cv::Mat_<double> test;
    std::vector<cv::KeyPoint> test_keypoints;
   
    cv::Mat colorImg2 = cv::imread(test_name);

    if(colorImg2.empty()){
        std::cout << "No Image" << std::endl;
        return ;
    }

    cv::Mat grayImg2;
    cv::cvtColor(colorImg2, grayImg2, CV_BGR2GRAY);
    cv::normalize(grayImg2, grayImg2, 0, 255, cv::NORM_MINMAX);

    detector.detect(grayImg2, test_keypoints);
    extractor.compute(grayImg2, test_keypoints, test);
    std::cout << "size of test ketpoints" << test_keypoints.size() << std::endl;

    
    //calc
    int k = 10;
    std::vector<int> ret = k_nn(pos, neg, test, k);
   
    //draw
    cv::Mat test_img = cv::imread(test_name, 0);
    visualize_keypoint(ret, test_keypoints , test_img);


    return ;

}


void extract_sift(std::string tmp_name, cv::Mat_<double> test_descriptors, std::vector<cv::KeyPoint>& test_keypoints) {
    

    cv::Mat colorImg = cv::imread(tmp_name);

    if(colorImg.empty()){
        std::cout << "No Image" << std::endl;
        return ;
    }

    cv::Mat grayImg;
    cv::cvtColor(colorImg, grayImg, CV_BGR2GRAY);
    cv::normalize(grayImg, grayImg, 0, 255, cv::NORM_MINMAX);

    cv::SiftFeatureDetector detector;
    cv::SiftDescriptorExtractor extractor;

    detector.detect(grayImg, test_keypoints);

    extractor.compute(grayImg, test_keypoints, test_descriptors);    
   
    //std::cout << test_descriptors.size() << std::endl;
    //std::cout << test_descriptors.rows << std::endl; 
 
    return ;

}

