
#include <cv.h>
#include <highgui.h>

int main(int argc, char *argv[])
{
    const char *pstrImageName = "D:/Embedded/projects/KYYANG/System/openCV/pics/linux.jpg";
    const char *pstrWindowsTitle = "First OpenCV Program";

    //从文件中读取图像
    IplImage *pImage = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_UNCHANGED);

    //创建窗口
    cvNamedWindow(pstrWindowsTitle, CV_WINDOW_AUTOSIZE);

    //在指定窗口中显示图像
    cvShowImage(pstrWindowsTitle, pImage);

    //等待按键事件
    cvWaitKey();

    cvDestroyWindow(pstrWindowsTitle);
    cvReleaseImage(&pImage);

    return 0;
}
