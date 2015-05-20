//-----------------------------------【头文件包含部分】---------------------------------------  
//      描述：包含程序所依赖的头文件  
//----------------------------------------------------------------------------------------------   
#include <opencv2/opencv.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  

#include <windows.h>
  
//-----------------------------------【宏定义部分】--------------------------------------------  
//  描述：定义一些辅助宏  
//------------------------------------------------------------------------------------------------  
#define WINDOW_NAME "【程序窗口】"        //为窗口标题定义的宏  
  
#define RANGE 100
#define PI 3.1415926
//-----------------------------------【命名空间声明部分】--------------------------------------  
//      描述：包含程序所使用的命名空间  
//-----------------------------------------------------------------------------------------------   
using namespace std;  
using namespace cv;  
  
  
//-----------------------------------【全局变量声明部分】--------------------------------------  
//      描述：全局变量声明  
//-----------------------------------------------------------------------------------------------  
Mat srcImage, g_dstImage, tmpImage;  
float tmp,radius;
Size info_size;
int height,width,cen_x,cen_y;

void HorO();
void ao(Mat tmpI);
  
int main( )  
{ 
	POINT p;
	
	srcImage=imread("Pictures\\萝莉2.jpg");
	/*
	 while (true)
    {
        if (GetCursorPos(&p)) //如果返回一个true，则…
        {

			cout<<"x="<<p.x<<endl;
			cout<<"y="<<p.y;
			 Sleep(100);
		}
	 }
	
	*/
	Mat partAo = srcImage(Rect(50,50,200,200));
	Mat partTu = srcImage(Rect(300,300,200,200));

	ao(partAo);

	namedWindow( WINDOW_NAME, CV_WINDOW_AUTOSIZE );  
    imshow(WINDOW_NAME, srcImage);  
	
	

	waitKey(0);
	return 0;  
}

void HorO()
{
	tmpImage = Mat (srcImage.size(),srcImage.type());

	for(int i=0;i<tmpImage.rows;i++)
	{
		tmp = RANGE *sin(i*PI/tmpImage.rows);
		for( int j =tmp; j<tmpImage.cols-tmp;j++ )
		{
		//	tmpImage.data[i*tmpImage.cols+j] = srcImage[i*srcImage.cols+(int)(i-tmp)*srcImage.cols/(srcImage.cols-2*tmp)];
			tmpImage.at<Vec3b>(i,j) = srcImage.at<Vec3b>(i,(int)((i-tmp)*srcImage.cols/(srcImage.cols-2*tmp)));
		}
	}

	imshow("li",tmpImage);
}

void ao(Mat tmpI)
{
	height=tmpI.size().height;  
	width=tmpI.size().width;  
	srcImage.copyTo(tmpImage);  

	Mat Roi = tmpImage(Rect(50,50,200,200));

	cen_x=width/2;  
	cen_y=height/2;  
	//radius=100;//you can change it!!!!!!R!!!!!  
	radius=min(cen_x,cen_y);  

	float dis;
	int distance,new_j,new_i;

	cout<<tmpI.cols<<"xxxx"<<tmpI.rows;
	for(int i=0;i<tmpI.cols;i++)
	{
		for( int j =0; j<tmpI.rows;j++ )
		{
			 distance=(j-cen_x)*(j-cen_x)+(i-cen_y)*(i-cen_y);  
    
			 dis=sqrt(distance);  
		//	 Roi.at<Vec3b>(i,j) = tmpI.at<Vec3b>(i,j);  
			if(distance<=radius*radius)  
			{
			  new_j=(int)((dis*(j-cen_x)/radius+cen_x));         
			  new_i=(int)((dis*(i-cen_y)/radius+cen_y));         
			  tmpI.at<Vec3b>(i,j) = tmpI.at<Vec3b>(new_i,new_j);  
			}
			
		}
	}

	imshow("li",tmpImage);
}

void Tu(Mat tmpI)
{
	height=tmpI.size().height;  
	width=tmpI.size().width;  
	tmpImage=Mat(srcImage.size().height,srcImage.size().width,srcImage.type());  

	Mat Roi = srcImage(Rect(0,0,200,200));

	cen_x=width/2;  
	cen_y=height/2;  
	//radius=100;//you can change it!!!!!!R!!!!!  
	radius=min(cen_x,cen_y);  

	float dis;
	int distance,new_j,new_i;

	cout<<tmpI.cols<<"xxxx"<<tmpI.rows;
	for(int i=0;i<tmpI.cols;i++)
	{
		for( int j =0; j<tmpI.rows;j++ )
		{
			 distance=(j-cen_x)*(j-cen_x)+(i-cen_y)*(i-cen_y);  
    
			 dis=sqrt(distance);  
		//	 Roi.at<Vec3b>(i,j) = tmpI.at<Vec3b>(i,j);  
			if(distance<=radius*radius)  
			{
			  new_j=(int)((dis*(j-cen_x)/radius+cen_x));         
			  new_i=(int)((dis*(i-cen_y)/radius+cen_y));         
			  Roi.at<Vec3b>(i,j) = tmpI.at<Vec3b>(new_i,new_j);  
			}
			
		}
	}

	imshow("li",tmpImage);
}