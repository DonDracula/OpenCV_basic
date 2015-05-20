#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include"opencv2/imgproc/imgproc.hpp"  
#include <iostream>  
   
//-----------------------------------�������ռ��������֡�---------------------------------------  
//     ����������������ʹ�õ������ռ�  
//-----------------------------------------------------------------------------------------------    
using namespace std;  
using namespace cv;  
   
   
//-----------------------------------��ȫ�ֺ����������֡�--------------------------------------  
//     ������ȫ�ֺ�������  
//-----------------------------------------------------------------------------------------------  
static void ContrastAndBright(int, void *);  
   
//-----------------------------------��ȫ�ֱ����������֡�--------------------------------------  
//     ������ȫ�ֱ�������  
//-----------------------------------------------------------------------------------------------  
int contrastValue; //�Աȶ�ֵ  
int brightValue;  //����ֵ  
Mat srcImage,dstImage;  
//-----------------------------------��main( )������--------------------------------------------  
//     ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ  
//-----------------------------------------------------------------------------------------------  
int main(  )  
{  
       //�ı����̨ǰ��ɫ�ͱ���ɫ  
    //   system("color5F");   
   
       //�����û��ṩ��ͼ��  
       srcImage= imread( "Pictures\\sankarea.jpg");  
              if(!srcImage.data ) { printf("Oh��no����ȡg_srcImageͼƬ����~��\n"); return false; }  
       dstImage= Mat::zeros( srcImage.size(), srcImage.type() );  
   
       //�趨�ԱȶȺ����ȵĳ�ֵ  
       contrastValue=80;  
       brightValue=80;  
   
       //��������  
       namedWindow("��Ч��ͼ���ڡ�", 1);  
   
       //�����켣��  
       createTrackbar("�Աȶȣ�", "��Ч��ͼ���ڡ�",&contrastValue,300,ContrastAndBright );  
       createTrackbar("��   �ȣ�","��Ч��ͼ���ڡ�",&brightValue,200,ContrastAndBright );  
        
       //���ûص�����  
       ContrastAndBright(contrastValue,0);  
       ContrastAndBright(brightValue,0);  
        
       //���һЩ������Ϣ  
       cout<<endl<<"\t�š����ˣ�������������۲�ͼ��Ч��~\n\n"  
                     <<"\t���¡�q����ʱ�������˳�~!\n"  
                     <<"\n\n\t\t\t\t";  
   
       //���¡�q����ʱ�������˳�  
   while(char(waitKey(1)) != 'q') {}  
       return 0;  
}  
   
   
//-----------------------------��ContrastAndBright( )������------------------------------------  
//     �������ı�ͼ��ԱȶȺ�����ֵ�Ļص�����  
//-----------------------------------------------------------------------------------------------  
static void ContrastAndBright(int, void *)  
{  
   
       //��������  
       namedWindow("��ԭʼͼ���ڡ�", 1);  
   
       //����forѭ����ִ������ g_dstImage(i,j) =a*g_srcImage(i,j) + b  
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
   
       //��ʾͼ��  
       imshow("��ԭʼͼ���ڡ�", srcImage);  
       imshow("��Ч��ͼ���ڡ�", dstImage);  
}  