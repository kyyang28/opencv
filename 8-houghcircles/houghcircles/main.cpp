
#include <cv.h>
#include <highgui.h>

int main()
{
    const char *pstrWindowsSrcTitle = "Original";
    const char *pstrWindowsLineName = "houghcircles";

    // 从文件中加载原图
    IplImage *pSrcImage = cvLoadImage("D:/Embedded/projects/KYYANG/System/openCV/pics/linux.jpg", CV_LOAD_IMAGE_UNCHANGED);

    // 灰度图
    IplImage *pGrayImage =  cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);
    cvCvtColor(pSrcImage, pGrayImage, CV_BGR2GRAY);
    //cvSmooth(pGrayImage, pGrayImage);

    // 圆检测(灰度图)
    CvMemStorage *pcvMStorage = cvCreateMemStorage();
    double fMinCircleGap = pGrayImage->height / 10;
    CvSeq *pcvSeqCircles = cvHoughCircles(pGrayImage, pcvMStorage, CV_HOUGH_GRADIENT, 1, fMinCircleGap);
    //每个圆由三个浮点数表示：圆心坐标(x,y)和半径

    // 绘制直线
    IplImage *pColorImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 3);
    cvCvtColor(pGrayImage, pColorImage, CV_GRAY2BGR);
    int i;
    for (i = 0; i < pcvSeqCircles->total; i++)
    {
        float* p = (float*)cvGetSeqElem(pcvSeqCircles, i);
        cvCircle(pColorImage, cvPoint(cvRound(p[0]), cvRound(p[1])), cvRound(p[2]), CV_RGB(255, 0, 0), 2);
    }

    cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
    cvShowImage(pstrWindowsSrcTitle, pSrcImage);
    cvNamedWindow(pstrWindowsLineName, CV_WINDOW_AUTOSIZE);
    cvShowImage(pstrWindowsLineName, pColorImage);

    cvWaitKey(0);

    cvReleaseMemStorage(&pcvMStorage);
    cvDestroyWindow(pstrWindowsSrcTitle);
    cvDestroyWindow(pstrWindowsLineName);
    cvReleaseImage(&pSrcImage);
    cvReleaseImage(&pGrayImage);
    cvReleaseImage(&pColorImage);

    return 0;
}
