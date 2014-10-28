
#include <cv.h>
#include <highgui.h>

int main(int argc, char *argv[])
{
    const char *pstrImageName = "D:/Embedded/projects/KYYANG/System/openCV/pics/linux.jpg";
    const char *pstrSaveImageName = "linux_merge.jpg";
    const char *pstrWindowsSrcTitle = "Original picture";
    const char *pstrWindowsDstTitle = "Merged picture";

    double fScale = 0.314;      //缩放倍数
    CvSize czSize;              //目标图像尺寸

    //从文件中读取图像
    IplImage *pSrcImage = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_UNCHANGED);
    IplImage *pDstImage = NULL;

    //计算目标图像大小
    czSize.width = pSrcImage->width * fScale;
    czSize.height = pSrcImage->height * fScale;

    //创建图像并缩放
    pDstImage = cvCreateImage(czSize, pSrcImage->depth, pSrcImage->nChannels);
    cvResize(pSrcImage, pDstImage, CV_INTER_AREA);

    //创建窗口
    cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
    cvNamedWindow(pstrWindowsDstTitle, CV_WINDOW_AUTOSIZE);

    //在指定窗口中显示图像
    cvShowImage(pstrWindowsSrcTitle, pSrcImage);
    cvShowImage(pstrWindowsDstTitle, pDstImage);

    //等待按键事件
    cvWaitKey();

    //保存图片
    cvSaveImage(pstrSaveImageName, pDstImage);

    //销毁及释放图片
    cvDestroyWindow(pstrWindowsSrcTitle);
    cvDestroyWindow(pstrWindowsDstTitle);
    cvReleaseImage(&pSrcImage);
    cvReleaseImage(&pDstImage);

    return 0;
}

