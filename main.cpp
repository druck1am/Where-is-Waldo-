//
//  main.cpp
//  opencvprac
//
//  Created by Alex Druckenmiller on 1/22/20.
//  Copyright © 2020 Alex Druckenmiller. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//This function will take in an image, and display it.
void open_picture(Mat pic_in){
    imshow("Waldo Pictre", pic_in);
    waitKey(0);
    destroyWindow("Waldo");
};


int main(int argc, const char * argv[]) {
    //read in orginal image
    Mat original = imread("/Users/alexdruckenmiller/Desktop/waldo2.jpg");
    //read in template
    Mat templ = imread("/Users/alexdruckenmiller/Desktop/waldotempl.jpg");
    
    //make results array. This will make a copy of the original image to be used for the matching method.
    Mat result;
    original.copyTo(result);
    
    //template matching function is used here. I used the TM_CCOEFF_NORMED method, because it is more accurate.         
    //I used minMaxLoc to find the values for the minimum and maximum points where the template and original image match.
    double minVal;
    double maxVal;
    Point minLoc;
    Point maxLoc;
    
    matchTemplate(original, templ, result, TM_CCOEFF_NORMED);
    normalize( result, result, 0, 1, NORM_MINMAX);
    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc);
    
    //this makes another copy of the original image to be used for the display. 
    //A rectagle will then be traced around the template, and displayed on the screen.
    Mat display;
    original.copyTo(display);
    
    rectangle(display, maxLoc, Point( maxLoc.x + templ.cols , maxLoc.y + templ.rows ), Scalar::all(0), 12, 8, 0 );
    
    
    //diplay the results image
    open_picture(result);
    //diplay the final image
    open_picture(display);
    
    return 0;
}
