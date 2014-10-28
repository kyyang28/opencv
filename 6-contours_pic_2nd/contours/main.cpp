
#include <cv.h>
#include <highgui.h>

IplImage *g_pGrayImage = NULL;
const char *pstrWindowsBinaryTitle = "Binaryzation";
const char *pstrWindowsOutLineTitle = "Outline";
CvSeq *g_pcvSeq = NULL;

void on_trackbar(int pos)
{
    // 转为二值图
    IplImage *pBinaryImage = cvCreateImage(cvGetSize(g_pGrayImage), IPL_DEPTH_8U, 1);
    cvThreshold(g_pGrayImage, pBinaryImage, pos, 255, CV_THRESH_BINARY);

    // 显示二值图
    cvShowImage(pstrWindowsBinaryTitle, pBinaryImage);

    CvMemStorage* cvMStorage = cvCreateMemStorage();

    // 检索轮廓并返回检测到的轮廓的个数
    cvFindContours(pBinaryImage,cvMStorage, &g_pcvSeq);

    IplImage *pOutlineImage = cvCreateImage(cvGetSize(g_pGrayImage), IPL_DEPTH_8U, 3);
    int _levels = 5;
    cvZero(pOutlineImage);
    cvDrawContours(pOutlineImage, g_pcvSeq, CV_RGB(255,0,0), CV_RGB(0,255,0), _levels);
    cvShowImage(pstrWindowsOutLineTitle, pOutlineImage);

    cvReleaseMemStorage(&cvMStorage);
    cvReleaseImage(&pBinaryImage);
    cvReleaseImage(&pOutlineImage);
}

int main( int argc, char** argv )
{
    const char *pstrWindowsSrcTitle = "Original";
    const char *pstrWindowsToolBarName = "Binaryzation";

    // 从文件中加载原图
    IplImage *pSrcImage = cvLoadImage("D:/Embedded/projects/KYYANG/System/openCV/pics/linux.jpg", CV_LOAD_IMAGE_UNCHANGED);

    // 显示原图
    cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
    cvShowImage(pstrWindowsSrcTitle, pSrcImage);

    // 转为灰度图
    g_pGrayImage =  cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);
    cvCvtColor(pSrcImage, g_pGrayImage, CV_BGR2GRAY);

    // 创建二值图和轮廓图窗口
    cvNamedWindow(pstrWindowsBinaryTitle, CV_WINDOW_AUTOSIZE);
    cvNamedWindow(pstrWindowsOutLineTitle, CV_WINDOW_AUTOSIZE);

    // 滑动条
    int nThreshold = 0;
    cvCreateTrackbar(pstrWindowsToolBarName, pstrWindowsBinaryTitle, &nThreshold, 254, on_trackbar);

    on_trackbar(1);

    cvWaitKey(0);

    cvDestroyWindow(pstrWindowsSrcTitle);
    cvDestroyWindow(pstrWindowsBinaryTitle);
    cvDestroyWindow(pstrWindowsOutLineTitle);
    cvReleaseImage(&pSrcImage);
    cvReleaseImage(&g_pGrayImage);

    return 0;
}
