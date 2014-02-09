#!/bin/bash
set -xu


files="/home/keiohigh2nd/MM/*"

g++ -o a.out test_sift.cpp -I/home/appl/opencv-2.4.6.1/include -L/home/appl/opencv-2.4.6.1/lib -lopencv_highgui -lopencv_core -lopencv_imgproc -lopencv_features2d -lopencv_nonfree

for filepath in ${files}
do
  echo ${filepath}
  ./a.out ${filepath}
  mv cut.jpg ${filepath}
done

echo done
