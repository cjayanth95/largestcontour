//
//  main.cpp
//  largestcontour
//
//  Created by labuser on 25/05/16.
//  Copyright © 2016 labuser. All rights reserved.
//
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

void clean(Mat src){
    int largest_area=0;
    int largest_contour_index=0;
    Rect boundRect ;
    
    Mat thr;
    cvtColor( src, thr, COLOR_BGR2GRAY ); //Convert to gray
    threshold( thr, thr, 125, 255, THRESH_BINARY ); //Threshold the gray
    
    vector<vector<Point> > contours; // Vector for storing contours
    
    findContours( thr, contours, RETR_CCOMP, CHAIN_APPROX_SIMPLE ); // Find the contours in the image
    
    for( size_t i = 0; i< contours.size(); i++ ) // iterate through each contour.
    {
        double area = contourArea( contours[i] );  //  Find the area of contour
        
        if( area > largest_area )
        {
            largest_area = area;
            largest_contour_index = i;               //Store the index of largest contour
            boundRect = boundingRect( contours[i] ); // Find the bounding rectangle for biggest contour
        }
    };
    Mat roi = src(boundRect);
    cv::imwrite(  "o78.jpg",roi );
    vector<Point>approx , outapprox , outapprox2;
    cv::approxPolyDP(contours[largest_contour_index],approx, 300, true );//get the largest contour with 4 vertices
    for (int h = 0; h<approx.size(); h++) {
        cout<<approx[h]<<" "<<endl;
    }
    
    std::vector<Point2f> quad_pts;
    std::vector<Point2f> squre_pts;
    if (approx[0].x<approx[2].x) {
        cout<<"12"<<endl;
        quad_pts.push_back(Point2f(approx[0].x,approx[0].y));
        quad_pts.push_back(Point2f(approx[1].x,approx[1].y));
        quad_pts.push_back(Point2f(approx[2].x,approx[2].y));
        quad_pts.push_back(Point2f(approx[3].x,approx[3].y));
        squre_pts.push_back(Point2f(0,0));
        
        squre_pts.push_back(Point2f(0,boundRect.height));
        
        squre_pts.push_back(Point2f(boundRect.width,boundRect.height));
        squre_pts.push_back(Point2f(boundRect.width,0));
        
        
        
        //
        //        squre_pts.push_back(Point2f(boundRect.tl().x,boundRect.tl().y));
        //
        //        squre_pts.push_back(Point2f(boundRect.tl().x,boundRect.tl().y+boundRect.height));
        //
        //        squre_pts.push_back(Point2f(boundRect.tl().x+boundRect.width,boundRect.tl().y+boundRect.height));
        //        squre_pts.push_back(Point2f(boundRect.tl().x+boundRect.width,boundRect.tl().y));
        
    }

    else{
        cout<<"as"<<endl;
                quad_pts.push_back(Point2f(approx[1].x,approx[1].y));
        quad_pts.push_back(Point2f(approx[2].x,approx[2].y));
        quad_pts.push_back(Point2f(approx[3].x,approx[3].y));
        quad_pts.push_back(Point2f(approx[0].x,approx[0].y));

        squre_pts.push_back(Point2f(boundRect.tl().x,boundRect.tl().y));
        
        squre_pts.push_back(Point2f(boundRect.tl().x,boundRect.tl().y+boundRect.height));
        
        squre_pts.push_back(Point2f(boundRect.tl().x+boundRect.width,boundRect.tl().y+boundRect.height));
        squre_pts.push_back(Point2f(boundRect.tl().x+boundRect.width,boundRect.tl().y));
        
    }
    Mat transmtx = getPerspectiveTransform(quad_pts,squre_pts);
    Mat transformed = Mat::zeros(boundRect.width, boundRect.height, CV_8UC3);
    warpPerspective(src, transformed, transmtx, boundRect.size());
    Mat dst;
    cvtColor(transformed, dst, CV_BGR2GRAY);
    cv::adaptiveThreshold(dst,dst,255,ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY,15,5);
    cv::imwrite(  "o77.jpg",dst );
    //    cout<<boundRect.tl()<<endl;
    //    cout<<boundRect.br()<<endl;
    
    drawContours( src , contours,largest_contour_index, Scalar( 0, 255, 0 ), 2 ); // Draw the largest contour using previously stored index.
    //cv::imwrite(  "o77.jpg",src );
    
    //return 0;


}
Mat boundingbox (Mat src){
    int largest_area=0;
    int largest_contour_index=0;
    Rect boundRect ;
    
    Mat thr;
    cvtColor( src, thr, COLOR_BGR2GRAY ); //Convert to gray
    threshold( thr, thr, 125, 255, THRESH_BINARY ); //Threshold the gray
    
    vector<vector<Point> > contours; // Vector for storing contours
    
    findContours( thr, contours, RETR_CCOMP, CHAIN_APPROX_SIMPLE ); // Find the contours in the image
    
    for( size_t i = 0; i< contours.size(); i++ ) // iterate through each contour.
    {
        double area = contourArea( contours[i] );  //  Find the area of contour
        
        if( area > largest_area )
        {
            largest_area = area;
            largest_contour_index = i;               //Store the index of largest contour
            boundRect = boundingRect( contours[i] ); // Find the bounding rectangle for biggest contour
        }
    };
    Mat roi = src(boundRect);
    return roi;
}
int main( int argc, char** argv )
{
//    Mat src=imread("82.jpg");
//    Mat thr;
//    cvtColor(src,thr,CV_BGR2GRAY);
//    threshold( thr, thr, 70, 255,CV_THRESH_BINARY );
//    
//    vector< vector <Point> > contours; // Vector for storing contour
//    vector< Vec4i > hierarchy;
//    int largest_contour_index=0;
//    int largest_area=0;
//    
//    Mat dst(src.rows,src.cols,CV_8UC1,Scalar::all(0)); //create destination image
//    findContours( thr.clone(), contours, hierarchy,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE ); // Find the contours in the image
//    for( int i = 0; i< contours.size(); i++ ){
//        double a=contourArea( contours[i],false);  //  Find the area of contour
//        if(a>largest_area){
//            largest_area=a;
//            largest_contour_index=i;                //Store the index of largest contour
//        }
//    }
//    
//    drawContours( dst,contours, largest_contour_index, Scalar(255,255,255),CV_FILLED, 8, hierarchy );
//    vector<vector<Point> > contours_poly(1);
//    approxPolyDP( Mat(contours[largest_contour_index]), contours_poly[0],100, true );
//    Rect boundRect=boundingRect(contours[largest_contour_index]);
//    if(contours_poly[0].size()==4){
//        std::vector<Point2f> quad_pts;
//        std::vector<Point2f> squre_pts;
//        quad_pts.push_back(Point2f(contours_poly[0][0].x,contours_poly[0][0].y));
//        quad_pts.push_back(Point2f(contours_poly[0][1].x,contours_poly[0][1].y));
//        quad_pts.push_back(Point2f(contours_poly[0][3].x,contours_poly[0][3].y));
//        quad_pts.push_back(Point2f(contours_poly[0][2].x,contours_poly[0][2].y));
//        squre_pts.push_back(Point2f(boundRect.x,boundRect.y));
//        squre_pts.push_back(Point2f(boundRect.x,boundRect.y+boundRect.height));
//        squre_pts.push_back(Point2f(boundRect.x+boundRect.width,boundRect.y));
//        squre_pts.push_back(Point2f(boundRect.x+boundRect.width,boundRect.y+boundRect.height));
//        
//        Mat transmtx = getPerspectiveTransform(quad_pts,squre_pts);
//        imwrite("result4.jpg",transmtx);
//        Mat transformed = Mat::zeros(src.rows, src.cols, CV_8UC3);
//        warpPerspective(src, transformed, transmtx, src.size());
//        Point P1=contours_poly[0][0];
//        Point P2=contours_poly[0][1];
//        Point P3=contours_poly[0][2];
//        Point P4=contours_poly[0][3];
//        
//        
//        line(src,P1,P2, Scalar(0,0,255),1,CV_AA,0);
//        line(src,P2,P3, Scalar(0,0,255),1,CV_AA,0);
//        line(src,P3,P4, Scalar(0,0,255),1,CV_AA,0);
//        line(src,P4,P1, Scalar(0,0,255),1,CV_AA,0);
//        rectangle(src,boundRect,Scalar(0,255,0),1,8,0);
//        rectangle(transformed,boundRect,Scalar( 0,255,0),1,8,0);
//        
//        imshow("quadrilateral", transformed);
//        imshow("thr",thr);
//        imshow("dst",dst);
//        imshow("src",src);
//        imwrite("result1.jpg",dst);
//        imwrite("result2.jpg",src);
//        imwrite("result3.jpg",transformed);
//        waitKey();
//    }
//    else
//        cout<<"Make sure that your are getting 4 corner using approxPolyDP..."<<endl;
    using namespace std;
    using namespace cv;
    Mat src = imread( "84.JPG" );
    Mat src1  = boundingbox(src);
    clean(src1);
//    int largest_area=0;
//    int largest_contour_index=0;
//    Rect boundRect ;
//    
//    Mat thr;
//    cvtColor( src, thr, COLOR_BGR2GRAY ); //Convert to gray
//    threshold( thr, thr, 125, 255, THRESH_BINARY ); //Threshold the gray
//    
//    vector<vector<Point> > contours; // Vector for storing contours
//    
//    findContours( thr, contours, RETR_CCOMP, CHAIN_APPROX_SIMPLE ); // Find the contours in the image
//    
//    for( size_t i = 0; i< contours.size(); i++ ) // iterate through each contour.
//    {
//        double area = contourArea( contours[i] );  //  Find the area of contour
//        
//        if( area > largest_area )
//        {
//            largest_area = area;
//            largest_contour_index = i;               //Store the index of largest contour
//            boundRect = boundingRect( contours[i] ); // Find the bounding rectangle for biggest contour
//        }
//    };
//    Mat roi = src(boundRect);
//    cv::imwrite(  "o78.jpg",roi );
//    vector<Point>approx , outapprox , outapprox2;
//    cv::approxPolyDP(contours[largest_contour_index],approx, 300, true );//get the largest contour with 4 vertices
//    for (int h = 0; h<approx.size(); h++) {
//        cout<<approx[h]<<" "<<endl;
//    }
//    
//    std::vector<Point2f> quad_pts;
//    std::vector<Point2f> squre_pts;
//    if (approx[0].x<approx[2].x) {
//        cout<<"12"<<endl;
//        quad_pts.push_back(Point2f(0,0));
//        quad_pts.push_back(Point2f(approx[1].x-approx[0].x,approx[1].y-approx[0].y));
//        quad_pts.push_back(Point2f(approx[2].x-approx[0].x,approx[2].y-approx[0].y));
//        quad_pts.push_back(Point2f(approx[3].x-approx[0].x,approx[3].y-approx[0].y));
////        squre_pts.push_back(Point2f(0,0));
////        
////        squre_pts.push_back(Point2f(0,boundRect.height));
////        
////        squre_pts.push_back(Point2f(boundRect.width,boundRect.height));
////        squre_pts.push_back(Point2f(boundRect.width,0));
//                squre_pts.push_back(Point2f(boundRect.tl().x,boundRect.tl().y));
//        
//                squre_pts.push_back(Point2f(boundRect.tl().x,boundRect.tl().y+boundRect.height));
//        
//                squre_pts.push_back(Point2f(boundRect.tl().x+boundRect.width,boundRect.tl().y+boundRect.height));
//                squre_pts.push_back(Point2f(boundRect.tl().x+boundRect.width,boundRect.tl().y));
//
//        
//    }
//    else{
//        
//        quad_pts.push_back(Point2f(0,0));
//        quad_pts.push_back(Point2f(approx[2].x-approx[1].x,approx[2].y-approx[1].y));
//        quad_pts.push_back(Point2f(approx[3].x-approx[1].x,approx[3].y-approx[1].y));
//        quad_pts.push_back(Point2f(approx[0].x-approx[1].x,approx[0].y-approx[1].y));
//        squre_pts.push_back(Point2f(boundRect.tl().x,boundRect.tl().y));
//        
//        squre_pts.push_back(Point2f(boundRect.tl().x,boundRect.tl().y+boundRect.height));
//        
//        squre_pts.push_back(Point2f(boundRect.tl().x+boundRect.width,boundRect.tl().y+boundRect.height));
//        squre_pts.push_back(Point2f(boundRect.tl().x+boundRect.width,boundRect.tl().y));
//
////        squre_pts.push_back(Point2f(0,0));
////        
////        squre_pts.push_back(Point2f(0,boundRect.height));
////        
////        squre_pts.push_back(Point2f(boundRect.width,boundRect.height));
////        squre_pts.push_back(Point2f(boundRect.width,0));
//        
//    }
//    if (approx[0].x<approx[2].x) {
//        cout<<"12"<<endl;
//        quad_pts.push_back(Point2f(approx[0].x,approx[0].y));
//        quad_pts.push_back(Point2f(approx[1].x,approx[1].y));
//         quad_pts.push_back(Point2f(approx[2].x,approx[2].y));
//         quad_pts.push_back(Point2f(approx[3].x,approx[3].y));
//                squre_pts.push_back(Point2f(0,0));
//        
//                squre_pts.push_back(Point2f(0,boundRect.height));
//        
//                squre_pts.push_back(Point2f(boundRect.width,boundRect.height));
//                squre_pts.push_back(Point2f(boundRect.width,0));
//
//        
//        
////        
////        squre_pts.push_back(Point2f(boundRect.tl().x,boundRect.tl().y));
////        
////        squre_pts.push_back(Point2f(boundRect.tl().x,boundRect.tl().y+boundRect.height));
////       
////        squre_pts.push_back(Point2f(boundRect.tl().x+boundRect.width,boundRect.tl().y+boundRect.height));
////        squre_pts.push_back(Point2f(boundRect.tl().x+boundRect.width,boundRect.tl().y));
//        
//    }
//    else{
//        cout<<"as"<<endl;
//        quad_pts.push_back(Point2f(approx[0].x,approx[0].y));
//        quad_pts.push_back(Point2f(approx[1].x,approx[1].y));
//        quad_pts.push_back(Point2f(approx[2].x,approx[2].y));
//        quad_pts.push_back(Point2f(approx[3].x,approx[3].y));
//        
//        squre_pts.push_back(Point2f(boundRect.tl().x,boundRect.tl().y));
//        
//        squre_pts.push_back(Point2f(boundRect.tl().x,boundRect.tl().y+boundRect.height));
//        
//        squre_pts.push_back(Point2f(boundRect.tl().x+boundRect.width,boundRect.tl().y+boundRect.height));
//        squre_pts.push_back(Point2f(boundRect.tl().x+boundRect.width,boundRect.tl().y));
//
//    }
//    Mat transmtx = getPerspectiveTransform(quad_pts,squre_pts);
//    Mat transformed = Mat::zeros(boundRect.width, boundRect.height, CV_8UC3);
//    warpPerspective(src, transformed, transmtx, boundRect.size());
//    cv::imwrite(  "o77.jpg",transformed );
////    cout<<boundRect.tl()<<endl;
////    cout<<boundRect.br()<<endl;
//    
//    drawContours( src , contours,largest_contour_index, Scalar( 0, 255, 0 ), 2 ); // Draw the largest contour using previously stored index.
    //cv::imwrite(  "o77.jpg",src );
    
    return 0;
}