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
              cout<<endl<<"�š����ˣ��ó�������Ҫ��ͼ��~! : )";  
			  ROI_LinearBlending()  ;
       }  
   
       waitKey(0);  
       return 0;  
}  

bool ROI_LinearBlending()  
{  
   
       //��1����ȡͼ��  
       Mat srcImage4= imread("Pictures\\sankarea.jpg",1);  
       Mat logoImage= imread("Pictures\\lena.jpg");  
	  // Mat logoImage= imread("Pictures\\hat.png");  
   
       if(!srcImage4.data ) { printf("���ã���ȡsrcImage4����~�� \n"); return false; }  
       if(!logoImage.data ) { printf("���ã���ȡlogoImage����~�� \n"); return false; }  
   
       //��2������һ��Mat���Ͳ������趨ROI����  
       Mat imageROI;  
              //����һ  
       imageROI=srcImage4(Rect(100,150,logoImage.cols,logoImage.rows));  
       //������  
       //imageROI=srcImage4(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols));  
   
       //��3����logo�ӵ�ԭͼ��  
       addWeighted(imageROI,0.5,logoImage,0.5,0.,imageROI);  
   
       //��4����ʾ���  
       namedWindow("<4>��������ͼ����ʾ������",WINDOW_NORMAL);  
       imshow("<4>��������ͼ����ʾ������",srcImage4);  
        
       return true;  
} 