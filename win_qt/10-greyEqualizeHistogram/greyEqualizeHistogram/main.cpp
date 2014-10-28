
#include <cv.h>
#include <highgui.h>

void FillWhite(IplImage *pImage)
{
    cvRectangle(pImage, cvPoint(0, 0), cvPoint(pImage->width, pImage->height), CV_RGB(255, 255, 255), CV_FILLED);
}

// 创建灰度图像的直方图
CvHistogram* CreateGrayImageHist(IplImage **ppImage)
{
    int nHistSize = 256;
    float fRange[] = {0, 255};  //灰度级的范围
    float *pfRanges[] = {fRange};
    CvHistogram *pcvHistogram = cvCreateHist(1, &nHistSize, CV_HIST_ARRAY, pfRanges);
    cvCalcHist(ppImage, pcvHistogram);
    return pcvHistogram;
}

// 根据直方图创建直方图图像
IplImage* CreateHisogramImage(int nImageWidth, int nScale, int nImageHeight, CvHistogram *pcvHistogram)
{
    IplImage *pHistImage = cvCreateImage(cvSize(nImageWidth * nScale, nImageHeight), IPL_DEPTH_8U, 1);
    FillWhite(pHistImage);

    //统计直方图中的最大直方块
    float fMaxHistValue = 0;
    cvGetMinMaxHistValue(pcvHistogram, NULL, &fMaxHistValue, NULL, NULL);

    //分别将每个直方块的值绘制到图中
    int i;
    for(i = 0; i < nImageWidth; i++)
    {
        float fHistValue = cvQueryHistValue_1D(pcvHistogram, i); //像素为i的直方块大小
        int nRealHeight = cvRound((fHistValue / fMaxHistValue) * nImageHeight);  //要绘制的高度
        cvRectangle(pHistImage,
            cvPoint(i * nScale, nImageHeight - 1),
            cvPoint((i + 1) * nScale - 1, nImageHeight - nRealHeight),
            cvScalar(i, 0, 0, 0),
            CV_FILLED
            );
    }

    return pHistImage;
}

int main( int argc, char** argv )
{
    const char *pstrWindowsSrcTitle = "Original picture";
    const char *pstrWindowsGrayTitle = "Grey picture";
    const char *pstrWindowsHistTitle = "Histogram";
    const char *pstrWindowsGrayEqualizeTitle = "Grey - equalized";
    const char *pstrWindowsHistEqualizeTitle = "Histogram - equalized";

    // 从文件中加载原图
    IplImage *pSrcImage = cvLoadImage("D:/Embedded/projects/KYYANG/System/openCV/pics/linux.jpg", CV_LOAD_IMAGE_UNCHANGED);
    IplImage *pGrayImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);
    IplImage *pGrayEqualizeImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);

    // 灰度图
    cvCvtColor(pSrcImage, pGrayImage, CV_BGR2GRAY);
    // 直方图图像数据
    int nHistImageWidth = 255;
    int nHistImageHeight = 150;
    int nScale = 2;

    // 灰度直方图及直方图图像
    CvHistogram *pcvHistogram = CreateGrayImageHist(&pGrayImage);
    IplImage *pHistImage = CreateHisogramImage(nHistImageWidth, nScale, nHistImageHeight, pcvHistogram);

    // 均衡化
    cvEqualizeHist(pGrayImage, pGrayEqualizeImage);

    // 均衡化后的灰度直方图及直方图图像
    CvHistogram *pcvHistogramEqualize = CreateGrayImageHist(&pGrayEqualizeImage);
    IplImage *pHistEqualizeImage = CreateHisogramImage(nHistImageWidth, nScale, nHistImageHeight, pcvHistogramEqualize);

    // 显示
    cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
    cvNamedWindow(pstrWindowsGrayTitle, CV_WINDOW_AUTOSIZE);
    cvNamedWindow(pstrWindowsHistTitle, CV_WINDOW_AUTOSIZE);
    cvNamedWindow(pstrWindowsGrayEqualizeTitle, CV_WINDOW_AUTOSIZE);
    cvNamedWindow(pstrWindowsHistEqualizeTitle, CV_WINDOW_AUTOSIZE);

    //显示代码….
    cvShowImage(pstrWindowsSrcTitle, pSrcImage);                        //显示原始图
    cvShowImage(pstrWindowsGrayTitle, pGrayImage);                      //显示灰度图
    cvShowImage(pstrWindowsHistTitle, pHistImage);                      //显示灰度直方图
    cvShowImage(pstrWindowsGrayEqualizeTitle,pGrayEqualizeImage);       //显示均衡化后的灰度图
    cvShowImage(pstrWindowsHistEqualizeTitle, pHistEqualizeImage);      //显示均衡化后的灰度直方图

    cvWaitKey(0);

    //回收资源代码…
    cvReleaseHist(&pcvHistogram);
    cvReleaseHist(&pcvHistogramEqualize);
    cvDestroyWindow(pstrWindowsSrcTitle);
    cvDestroyWindow(pstrWindowsGrayTitle);
    cvDestroyWindow(pstrWindowsHistTitle);
    cvDestroyWindow(pstrWindowsGrayEqualizeTitle);
    cvDestroyWindow(pstrWindowsHistEqualizeTitle);
    cvReleaseImage(&pSrcImage);
    cvReleaseImage(&pGrayImage);
    cvReleaseImage(&pHistImage);
    cvReleaseImage(&pGrayEqualizeImage);
    cvReleaseImage(&pHistEqualizeImage);

    return 0;
}
