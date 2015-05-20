//-----------------------------------������˵����----------------------------------------------  
//      ��������:������OpenCV���Ž̳�֮ʮ����OpenCV��Ե��⣺Canny����,Sobel����,Laplace����,Scharr�˲����ϼ��ϼ��� ��������Դ��   
//      ��������IDE�汾��Visual Studio 2010  
//      <span style="white-space:pre">  </span>��������OpenCV�汾��    2.4.7 
//      2014��6��16�� Study by ���Ӻ�
//----------------------------------------------------------------------------------------------  
  
  
  
//-----------------------------------��ͷ�ļ��������֡�---------------------------------------  
//      ����������������������ͷ�ļ�  
//----------------------------------------------------------------------------------------------   
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
  
//-----------------------------------�������ռ��������֡�--------------------------------------  
//      ����������������ʹ�õ������ռ�  
//-----------------------------------------------------------------------------------------------   
using namespace cv;  
  
  
//-----------------------------------��ȫ�ֱ����������֡�--------------------------------------  
//      ������ȫ�ֱ�������  
//-----------------------------------------------------------------------------------------------  
//ԭͼ��ԭͼ�ĻҶȰ棬Ŀ��ͼ  
Mat g_srcImage, g_srcGrayImage,g_dstImage,g_srcGray;  
  
//Canny��Ե�����ر���  
Mat g_cannyDetectedEdges;  
int g_cannyLowThreshold=1;//TrackBarλ�ò���    
  
//Sobel��Ե�����ر���  
Mat g_sobelGradient_X, g_sobelGradient_Y;  
Mat g_sobelAbsGradient_X, g_sobelAbsGradient_Y;  
int g_sobelKernelSize=1;//TrackBarλ�ò���    

//Laplace�任��ر���
Mat g_laplaceDetectEdges,g_laplaceAbsDetectEdges;
int g_laplaceKernelSize=1;//TrackBarλ�ò���    
  
//Scharr�˲�����ر���  
Mat g_scharrGradient_X, g_scharrGradient_Y;  
Mat g_scharrAbsGradient_X, g_scharrAbsGradient_Y;  
  
  
//-----------------------------------��ȫ�ֺ����������֡�--------------------------------------  
//      ������ȫ�ֺ�������  
//-----------------------------------------------------------------------------------------------  
static void ShowHelpText( );  
static void on_Canny(int, void*);//Canny��Ե��ⴰ�ڹ������Ļص�����  
static void on_Sobel(int, void*);//Sobel��Ե��ⴰ�ڹ������Ļص�����  
static void on_Laplace(int, void*);//Laplace�任���ڹ������Ļص����� 
void Scharr( );//��װ��Scharr��Ե�����ش���ĺ���  
  
  
//-----------------------------------��main( )������--------------------------------------------  
//      ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ  
//-----------------------------------------------------------------------------------------------  
int main( int argc, char** argv )  
{  
    //�ı�console������ɫ  
    system("color 2F");    
  
    //��ʾ��ӭ��  
    ShowHelpText();  
  
    //����ԭͼ  
    g_srcImage = imread("Pictures\\����1.png");  
    if( !g_srcImage.data ) { printf("Oh��no����ȡsrcImage����~�� \n"); return false; }  
  
    //��ʾԭʼͼ  
    namedWindow("��ԭʼͼ��");  
    imshow("��ԭʼͼ��", g_srcImage);  
  
    // ������srcͬ���ͺʹ�С�ľ���(dst)  
    g_dstImage.create( g_srcImage.size(), g_srcImage.type() );  
  
    // ��ԭͼ��ת��Ϊ�Ҷ�ͼ��  
    cvtColor( g_srcImage, g_srcGrayImage, CV_BGR2GRAY );  
  
    // ������ʾ����  
    namedWindow( "��Ч��ͼ��Canny��Ե���", CV_WINDOW_AUTOSIZE );  
    namedWindow( "��Ч��ͼ��Sobel��Ե���", CV_WINDOW_AUTOSIZE );  
	namedWindow("��Ч��ͼ��Laplace�任",CV_WINDOW_AUTOSIZE);

  
    // ����trackbar  
    createTrackbar( "����ֵ��", "��Ч��ͼ��Canny��Ե���", &g_cannyLowThreshold, 120, on_Canny );  
    createTrackbar( "����ֵ��", "��Ч��ͼ��Sobel��Ե���", &g_sobelKernelSize, 3, on_Sobel );  
	createTrackbar( "����ֵ��", "��Ч��ͼ��Laplace�任", &g_laplaceKernelSize,5,on_Laplace );
  
    // ���ûص�����  
    on_Canny(0, 0);  
    on_Sobel(0, 0);  
	on_Laplace(0,0);
  
    //���÷�װ��Scharr��Ե������ĺ���  
    Scharr( );  
  
    //��ѯ��ȡ������Ϣ��������Q�������˳�  
    while((char(waitKey(1)) != 'q')) {}  
  
    return 0;  
}  
  
  
//-----------------------------------��ShowHelpText( )������----------------------------------  
//      ���������һЩ������Ϣ  
//----------------------------------------------------------------------------------------------  
static void ShowHelpText()  
{  
    //���һЩ������Ϣ  
    printf( "\n\n\t�š����гɹ���������������۲�ͼ��Ч��~\n\n"  
        "\t���¡�q����ʱ�������˳�~!\n"  
        "\n\n\t\t\t\t Bye" );  
}  
  
  
//-----------------------------------��on_Canny( )������----------------------------------  
//      ������Canny��Ե��ⴰ�ڹ������Ļص�����  
//-----------------------------------------------------------------------------------------------  
void on_Canny(int, void*)  
{  
    // ��ʹ�� 3x3�ں�������  
    blur( g_srcGrayImage, g_cannyDetectedEdges, Size(3,3) );  
  
    // �������ǵ�Canny����  
    Canny( g_cannyDetectedEdges, g_cannyDetectedEdges, g_cannyLowThreshold, g_cannyLowThreshold*3, 3 );  
  
    //�Ƚ�g_dstImage�ڵ�����Ԫ������Ϊ0   
    g_dstImage = Scalar::all(0);  
  
    //ʹ��Canny��������ı�Եͼg_cannyDetectedEdges��Ϊ���룬����ԭͼg_srcImage����Ŀ��ͼg_dstImage��  
    g_srcImage.copyTo( g_dstImage, g_cannyDetectedEdges);  
  
    //��ʾЧ��ͼ  
    imshow( "��Ч��ͼ��Canny��Ե���", g_dstImage );  
}  
  
  
  
//-----------------------------------��on_Sobel( )������----------------------------------  
//      ������Sobel��Ե��ⴰ�ڹ������Ļص�����  
//-----------------------------------------------------------------------------------------  
void on_Sobel(int, void*)  
{  
    // �� X�����ݶ�  
    Sobel( g_srcImage, g_sobelGradient_X, CV_16S, 1, 0, (2*g_sobelKernelSize+1), 1, 1, BORDER_DEFAULT );  
    convertScaleAbs( g_sobelGradient_X, g_sobelAbsGradient_X );//�������ֵ���������ת����8λ  
  
    // ��Y�����ݶ�  
    Sobel( g_srcImage, g_sobelGradient_Y, CV_16S, 0, 1, (2*g_sobelKernelSize+1), 1, 1, BORDER_DEFAULT );  
    convertScaleAbs( g_sobelGradient_Y, g_sobelAbsGradient_Y );//�������ֵ���������ת����8λ  
  
    // �ϲ��ݶ�  
    addWeighted( g_sobelAbsGradient_X, 0.5, g_sobelAbsGradient_Y, 0.5, 0, g_dstImage );  
  
    //��ʾЧ��ͼ  
    imshow("��Ч��ͼ��Sobel��Ե���", g_dstImage);   
  
}  
  
  
//-----------------------------------��Scharr( )������----------------------------------  
//      ��������װ��Scharr��Ե�����ش���ĺ���  
//-----------------------------------------------------------------------------------------  
void Scharr( )  
{  
    // �� X�����ݶ�  
    Scharr( g_srcImage, g_scharrGradient_X, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT );  
    convertScaleAbs( g_scharrGradient_X, g_scharrAbsGradient_X );//�������ֵ���������ת����8λ  
  
    // ��Y�����ݶ�  
    Scharr( g_srcImage, g_scharrGradient_Y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT );  
    convertScaleAbs( g_scharrGradient_Y, g_scharrAbsGradient_Y );//�������ֵ���������ת����8λ  
  
    // �ϲ��ݶ�  
    addWeighted( g_scharrAbsGradient_X, 0.5, g_scharrAbsGradient_Y, 0.5, 0, g_dstImage );  
  
    //��ʾЧ��ͼ  
    imshow("��Ч��ͼ��Scharr�˲���", g_dstImage);   
}  

void on_Laplace(int, void*){
  
    //��3��ʹ�ø�˹�˲���������  
    GaussianBlur( g_srcImage, g_srcImage, Size(3,3), 0, 0, BORDER_DEFAULT );  
  
    //��4��ת��Ϊ�Ҷ�ͼ  
    cvtColor( g_srcImage, g_srcGray, CV_RGB2GRAY );  
  
    //��5��ʹ��Laplace����  
    Laplacian( g_srcGray, g_laplaceDetectEdges, CV_16S, 2*g_laplaceKernelSize+1, 1, 0, BORDER_DEFAULT );  
  
    //��6���������ֵ���������ת����8λ  
    convertScaleAbs( g_laplaceDetectEdges, g_laplaceAbsDetectEdges );  
  
    //��7����ʾЧ��ͼ  
    imshow( "��Ч��ͼ��Laplace�任", g_laplaceAbsDetectEdges );  
}