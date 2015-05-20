#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include"opencv2/imgproc/imgproc.hpp"  
#include <iostream>  
   
//-----------------------------------【命名空间声明部分】---------------------------------------  
//     描述：包含程序所使用的命名空间  
//-----------------------------------------------------------------------------------------------    
using namespace std;  
using namespace cv;  
   
   
//-----------------------------------【全局函数声明部分】--------------------------------------  
//     描述：全局函数声明  
//-----------------------------------------------------------------------------------------------  
static void ContrastAndBright(int, void *);  
   
//-----------------------------------【全局变量声明部分】--------------------------------------  
//     描述：全局变量声明  
//-----------------------------------------------------------------------------------------------  
int contrastValue; //对比度值  
int brightValue;  //亮度值  
Mat srcImage,dstImage;  
//-----------------------------------【main( )函数】--------------------------------------------  
//     描述：控制台应用程序的入口函数，我们的程序从这里开始  
//-----------------------------------------------------------------------------------------------  
int main(  )  
{  
       //改变控制台前景色和背景色  
    //   system("color5F");   
   
       //读入用户提供的图像  
       srcImage= imread( "Pictures\\sankarea.jpg");  
              if(!srcImage.data ) { printf("Oh，no，读取g_srcImage图片错误~！\n"); return false; }  
       dstImage= Mat::zeros( srcImage.size(), srcImage.type() );  
   
       //设定对比度和亮度的初值  
       contrastValue=80;  
       brightValue=80;  
   
       //创建窗口  
       namedWindow("【效果图窗口】", 1);  
   
       //创建轨迹条  
       createTrackbar("对比度：", "【效果图窗口】",&contrastValue,300,ContrastAndBright );  
       createTrackbar("亮   度：","【效果图窗口】",&brightValue,200,ContrastAndBright );  
        
       //调用回调函数  
       ContrastAndBright(contrastValue,0);  
       ContrastAndBright(brightValue,0);  
        
       //输出一些帮助信息  
       cout<<endl<<"\t嗯。好了，请调整滚动条观察图像效果~\n\n"  
                     <<"\t按下“q”键时，程序退出~!\n"  
                     <<"\n\n\t\t\t\t";  
   
       //按下“q”键时，程序退出  
   while(char(waitKey(1)) != 'q') {}  
       return 0;  
}  
   
   
//-----------------------------【ContrastAndBright( )函数】------------------------------------  
//     描述：改变图像对比度和亮度值的回调函数  
//-----------------------------------------------------------------------------------------------  
static void ContrastAndBright(int, void *)  
{  
   
       //创建窗口  
       namedWindow("【原始图窗口】", 1);  
   
       //三个for循环，执行运算 g_dstImage(i,j) =a*g_srcImage(i,j) + b  
       for(int y = 0; y < srcImage.rows; y++ )  
       {  
              for(int x = 0; x < srcImage.cols; x++ )  
              {  
                     for(int c = 0; c < 3; c++ )  
                     {  
                            dstImage.at<Vec3b>(y,x)[c]= saturate_cast<uchar>( (contrastValue*0.01)*(srcImage.at<Vec3b>(y,x)[c] ) + brightValue );  
                     }  
              }  
       }  
   
       //显示图像  
       imshow("【原始图窗口】", srcImage);  
       imshow("【效果图窗口】", dstImage);  
}  