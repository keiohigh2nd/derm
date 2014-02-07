#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <time.h>
#include <sys/time.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "opencv2/core/core.hpp"


using namespace std;


double dists_get(const cv::Mat_<double>& x,const cv::Mat_<double>& y, const int i, const int ik) {

	double ret = 0;
	for (size_t j = 0;j < 128 ; ++j) {
	    double diff = x(j,i)-y(j,ik);
            ret += diff*diff;
	}
	return ret;
}


vector<int> k_nn(cv::Mat_<double>& a, cv::Mat_<double>& b, cv::Mat_<double>& p, int k){
  
  vector<int> result_class;
  for (size_t ik = 0; ik < p.rows; ++ik) {
	
    if (k > a.rows + b.rows){
	throw "k is too big ";
    }
	
    vector<pair<double, int> > dists;
    dists.resize(a.rows + b.rows);

    for (size_t i = 0; i < a.rows; ++i) {
	dists[i] = make_pair(dists_get(a, p, i, ik), 1);
    }
	
    for (size_t i=0; i < b.rows; ++i){
	dists[i+a.rows] = make_pair(dists_get(b, p, i, ik), 0);
    }
	
    sort(dists.begin(), dists.end());
	
    int a_num = 0;
    int b_num = 0;
	
    for (size_t i = 0; i < k; ++i){
	if(dists[i].second == 0){
		++a_num;
	}else if (dists[i].second == 1){
		++b_num;
	}else{
		throw "what are you doing?";
	}
			
    }
     	
  		
    if(a_num >= b_num) {
	result_class.push_back(0);	
    }else{
	result_class.push_back(1);
    }
  }
  return result_class;
}

double gettimeofday_sec(){
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + (double)tv.tv_usec*1e-6;
}


