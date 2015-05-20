#include <cv.h>  
#include <highgui.h>  
#include <iostream>

using namespace cv;  
using namespace std;  

bool ROI_LinearBlending();  

int main(  )  
{  
     //  system("color5E");  
   
       if(ROI_LinearBlending( ))  
       {  
              cout<<endl<<"嗯。好了，得出了你需要的图像~! : )";  
			  ROI_LinearBlending()  ;
       }  
   
       waitKey(0);  
       return 0;  
}  

bool ROI_LinearBlending()  
{  
   
       //【1】读取图像  
       Mat srcImage4= imread("Pictures\\sankarea.jpg",1);  
       Mat logoImage= imread("Pictures\\lena.jpg");  
	  // Mat logoImage= imread("Pictures\\hat.png");  
   
       if(!srcImage4.data ) { printf("你妹，读取srcImage4错误~！ \n"); return false; }  
       if(!logoImage.data ) { printf("你妹，读取logoImage错误~！ \n"); return false; }  
   
       //【2】定义一个Mat类型并给其设定ROI区域  
       Mat imageROI;  
              //方法一  
       imageROI=srcImage4(Rect(100,150,logoImage.cols,logoImage.rows));  
       //方法二  
       //imageROI=srcImage4(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols));  
   
       //【3】将logo加到原图上  
       addWeighted(imageROI,0.5,logoImage,0.5,0.,imageROI);  
   
       //【4】显示结果  
       namedWindow("<4>区域线性图像混合示例窗口",WINDOW_NORMAL);  
       imshow("<4>区域线性图像混合示例窗口",srcImage4);  
        
       return true;  
} 