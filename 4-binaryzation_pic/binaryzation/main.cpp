

#include <cv.h>
#include <highgui.h>

IplImage *g_pGrayImage = NULL;
IplImage *g_pBinaryImage = NULL;
const char *pstrWindowsBinaryTitle = "Binaryzation";

void on_trackbar(int pos)
{
    // 转为二值图
    cvThreshold(g_pGrayImage, g_pBinaryImage, pos, 255, CV_THRESH_BINARY);

    // 显示二值图
    cvShowImage(pstrWindowsBinaryTitle, g_pBinaryImage);
}

int main( int argc, char** argv )
{
    const char *pstrWindowsSrcTitle = "Original picture";
    const char *pstrWindowsToolBarName = "Binaryzation threshold";

    // 从文件中加载原图
    IplImage *pSrcImage = cvLoadImage("D:/Embedded/projects/KYYANG/System/openCV/pics/linux.jpg", CV_LOAD_IMAGE_UNCHANGED);

    // 转为灰度图
    g_pGrayImage =  cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);
    cvCvtColor(pSrcImage, g_pGrayImage, CV_BGR2GRAY);

    // 创建二值图
    g_pBinaryImage = cvCreateImage(cvGetSize(g_pGrayImage), IPL_DEPTH_8U, 1);

    // 显示原图
    cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
    cvShowImage(pstrWindowsSrcTitle, pSrcImage);

    // 创建二值图窗口
    cvNamedWindow(pstrWindowsBinaryTitle, CV_WINDOW_AUTOSIZE);

    // 滑动条
    int nThreshold = 0;
    cvCreateTrackbar(pstrWindowsToolBarName, pstrWindowsBinaryTitle, &nThreshold, 254, on_trackbar);

    on_trackbar(1);

    cvWaitKey(0);

    cvDestroyWindow(pstrWindowsSrcTitle);
    cvDestroyWindow(pstrWindowsBinaryTitle);
    cvReleaseImage(&pSrcImage);
    cvReleaseImage(&g_pGrayImage);
    cvReleaseImage(&g_pBinaryImage);

    return 0;
}
