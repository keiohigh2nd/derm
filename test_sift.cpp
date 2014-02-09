#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "opencv2/core/core.hpp"
#include <stdio.h>
#include <vector>
#include <math.h>

void calc_position(std::vector<cv::KeyPoint>& keypoint, std::vector<double>& result) {

    std::vector<double> x_posi;
    std::vector<double> y_posi;

    double sum_x = 0;
    double sum_y = 0;

    double dis_x = 0;
    double dis_y = 0;

    for(int i=0; i < keypoint.size(); i++) {
        sum_x += keypoint[i].pt.x;
        sum_y += keypoint[i].pt.y;
	//x_posi.push_back(keypoint[i].pt.x);
	//y_posi.push_back(keypoint[i].pt.y);	
	//std::cout << "position of x"<<keypoint[i].pt.x << std::endl;
    }
   
    double x_ave;
    x_ave = sum_x/double(keypoint.size());
    double y_ave; 
    y_ave = sum_y/double(keypoint.size());
    std::cout << "x--" << x_ave << "--y--" << y_ave << std::endl;
    result.push_back(x_ave);
    result.push_back(y_ave);

    for(int i=0; i < keypoint.size(); i++) {
	dis_x += pow(keypoint[i].pt.x - x_ave,2);
	dis_y += pow(keypoint[i].pt.y - y_ave,2);
    }
    double stan_x = sqrt(dis_x/double(keypoint.size()));
    double stan_y = sqrt(dis_y/double(keypoint.size()));
    result.push_back(stan_x);
    result.push_back(stan_y);
    std::cout << "x--" << stan_x << "--y--" << stan_y << std::endl;

}

double calc_average(std::vector<double>) {

}

int check_window(cv::Mat& img, std::vector<double>& res){

    double edge_x = (res[0]-res[2])+ res[2]*2.5;
    double edge_y = (res[1]-res[3])+ res[1]*2.5;

    /*
    if(img.cols > edge_x && img.rows > edge_y){
	
    	double diff_x = (img.cols - edge_x)/double(res[2]);
    	double diff_y = (img.rows - edge_y)/double(res[3]);
		
	if(diff_x > 1 ){
		return 2;
	}
	if (diff_y > 1){
		return 3;
	}

	return 0;
    }*/

    if(img.rows > edge_x){
        return 0;
    }

    
    if(img.cols > edge_y){
        return 0;
    }

    return 1;

}

void ROI_img(cv::Mat& img, int& res_check, std::vector<double>& res){
    if (res_check == 0) {
    	cv::Mat roi_img(img, cv::Rect(res[0]-res[2], res[1]-res[3], res[2]*2.5, res[3]*2.5)); 
    	cv::imwrite("cut.jpg", roi_img);
    }
    if (res_check == 1) {
        cv::Mat roi_img(img, cv::Rect(res[0]-res[2], res[1]-res[3], res[2]*1.5, res[3]*1.5));
    	cv::imwrite("cut.jpg", roi_img);
    }
    if (res_check == 2) {
        cv::Mat roi_img(img, cv::Rect(res[0]-res[2], res[1]-res[3], res[2]*3, res[3]*3));
        cv::imwrite("cut.jpg", roi_img);
    }
    if (res_check == 3) {
        cv::Mat roi_img(img, cv::Rect(res[0]-res[2], res[1]-res[3], res[2]*3, res[3]*3));
        cv::imwrite("cut.jpg", roi_img);
    }

}

int main(int argc, char *argv[]) {

    //Input Image
    cv::Mat colorImg1 = cv::imread(argv[1]);
    if(colorImg1.empty())return-1;

    cv::Mat grayImg1;
    cv::cvtColor(colorImg1, grayImg1, CV_BGR2GRAY);
    cv::normalize(grayImg1, grayImg1, 0, 255, cv::NORM_MINMAX);

    cv::SiftFeatureDetector detector;
    cv::SiftDescriptorExtractor extractor;

    std::vector<cv::KeyPoint> keypoints1;
    detector.detect(grayImg1, keypoints1);

    cv::Mat descriptors1;    
    extractor.compute(grayImg1, keypoints1, descriptors1);    

    
    std::vector<double> res;
    calc_position(keypoints1,res);
 
    int res_check = check_window(colorImg1,res);
    ROI_img(colorImg1,res_check,res); 

    //cv::Mat roi_img(colorImg1, cv::Rect(res[0]-res[2], res[1]-res[3], res[2]*2.5, res[3]*2.5)); 
    //cv::imwrite("cut.jpg", roi_img);
    
    /* 
    cv::Mat output;
    cv::drawKeypoints(colorImg1, keypoints1, output);
    cv::imwrite("sift_result.jpg", output);
    */

    
    return 0;

}
