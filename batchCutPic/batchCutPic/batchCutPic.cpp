// batchCutPic.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\imgproc\imgproc_c.h>
#include <opencv2\ml\ml.hpp>
#include <time.h>   
#include <math.h>
#include <dirent.h>
#include<iomanip>
#include<fstream>

using namespace std; 
using namespace cv; 
#define MAX_SIZE 32

string int2str(int &i) {
		string s;
		stringstream ss(s);
		ss << i;

		return ss.str();
}



int _tmain(int argc, _TCHAR* argv[])
{
	int Height;
    int Width;
    DIR *dir;
    dirent *entry;
    IplImage *src = 0;          //來源影像指標
    IplImage *dst = 0;          //目標影像指標
	IplImage *dst2 = 0;          //目標影像指標
    double scale = 1;           //縮放倍數為1倍
    CvSize dst_cvsize;          //目標影像尺寸
	CvSize dst_cvsize2;          //目標影像尺寸
 
    double times;
    //QueryPerformanceFrequency(&fre); //取得CPU頻率
    //QueryPerformanceCounter(&startTime); //取得開機到現在經過幾個CPU Cycle
    //doing something
	string data_dir = ".\\Data\\test\\";
	dir=opendir(data_dir.c_str());//開啟目標影像所在位置資料夾
	int obj_num=1;
    while(entry=readdir(dir)){
        if(strstr(entry->d_name,".jpg")||
            strstr(entry->d_name,".JPG")||
            strstr(entry->d_name,".jpeg")||
            strstr(entry->d_name,".JPEG")||
            strstr(entry->d_name,".png")||
            strstr(entry->d_name,".PNG")||
			strstr(entry->d_name,".PPM")||
			strstr(entry->d_name,".ppm")||
			strstr(entry->d_name,".bmp")||
			strstr(entry->d_name,".BMP")){
			cout<<entry->d_name<<endl;
			string load_name = data_dir + entry->d_name;
			src=cvLoadImage(load_name.c_str(), 1);//開啟影像
            Height=src->height;//or Height=cvGetDimSize(src,0);
            Width=src->width;//or Width=cvGetDimSize(src,1);
           
			CvRect rect;
			rect=cvRect(0,Height/2,Width,Height/2);

			//設定目標影像大小
            //dst_cvsize.width = src->width * scale;       //目標影像的寬為源影像寬的scale倍
            //dst_cvsize.height = src->height * scale; //目標影像的高為源影像高的scale倍

			dst = cvCreateImage( cvSize(rect.width, rect.height), src->depth, src->nChannels );		//創立目標影像
			
			cvSetImageROI( src, rect );  
			cvCopy( src, dst, 0 );  
			cvResetImageROI( src );
 
            //cout<<setw(15)<<entry->d_name
            //<<setw(3)<<'H'<<setw(5)<<Height
            //<<setw(3)<<'W'<<setw(5)<<Width
            //<<setw(3)<<'h'<<setw(4)<<dst_cvsize.height
            //<<setw(3)<<'w'<<setw(4)<<dst_cvsize.width<<endl;
			
			string save_dir = data_dir+ "cut_pic";
			//string save_name= save_dir +"\\"+ int2str(obj_num) + entry->d_name;
			string tmp = entry->d_name;//entry->d_name.find(".")-1
			string f_name = tmp.substr(0,tmp.find("."));
			string save_name= save_dir +"\\"+ f_name + ".bmp";
			if( opendir(save_dir.c_str())==NULL ){
				printf("cut_pic 無此資料夾\n");
				system("pause");
				exit(1);
			}
			else{
				cvSaveImage(save_name.c_str(), dst);//儲存影像
			}
			obj_num++;

            cvReleaseImage(&src);   //釋放來源影像佔用的記憶體
            cvReleaseImage(&dst);   //釋放目標影像佔用的記憶體
			cvReleaseImage(&dst2);   //釋放目標影像佔用的記憶體
        }
    }

	system("pause");
	return 0;
}

