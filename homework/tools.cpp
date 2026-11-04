//把刚才写的函数实现放近来
#include "tools.hpp"

//使用opencv的头文件
#include <opencv2/imgproc.hpp>
//fmt
#include <fmt/format.h>
//这俩不知道是什么，关于计算的先include进来
#include <algorithm>
#include <cmath>

// 先将图片等比例缩放，并居中放入640×640画布
cv::Mat ResizeWithPadding(const cv::Mat& input)
{
    // 1. 设置画布(canvas)大小
    const int canvasSize = 640;

    // 2. 获取original图矩阵的宽（cols）和高（rows）
    int originalWidth = input.cols;
    int originalHeight = input.rows;

    // 3. ##计算等比例缩放系数(我设置了一个计算宽高最小缩放系数的函数，保证图片不会超出画布)。使用static_cast<double>来强制转换为double类型，避免整数除法导致的精度丢失。
    double scale = std::min(
        static_cast<double>(canvasSize) / originalWidth,
        static_cast<double>(canvasSize) / originalHeight
    );

    // 4. ##计算缩放后(new)的宽高，取画布大小和缩放后大小的最小值，保证不会超出画布，且有一边为640，说白了就是最大化。还有一点就是强制取整数，我不清楚这是否会导致图像出现锯齿，毕竟缩放后可能是小数。
    int newWidth = std::min(
        canvasSize,
        std::max(1, static_cast<int>(std::round(originalWidth * scale)))
    );

    int newHeight = std::min(
        canvasSize,
        std::max(1, static_cast<int>(std::round(originalHeight * scale)))
    );

    // 5. 缩放图片
    cv::Mat resizedImage;

    int interpolation = scale < 1.0
        ? cv::INTER_AREA    //缩小使用INTER_AREA
        : cv::INTER_LINEAR; //放大使用INTER_LINEAR
    //调用cv工具
    cv::resize(
        input,              //输入
        resizedImage,            //接受缩放结果
        cv::Size(newWidth, newHeight),   //指定缩放后的大小
        0,                    //不另外指定水平、竖直缩放系数
        0,
        interpolation            //指定缩放时使用的插值方法，也就是说在缩放时如何计算新像素的值
    );

    // 6. 创建640×640的黑色（ZEROS）画布
    cv::Mat canvas = cv::Mat::zeros(
        canvasSize,
        canvasSize,
        input.type()
    );

    // 7. 计算图片放置的位置
    int offsetX = (canvasSize - newWidth) / 2;  //问：除2应该就是正中央吧？   //回答：这布做得很好，offsetX和offsetY的计算是为了将缩放后的图片居中放置在画布上。通过计算画布大小减去缩放后图片的宽度和高度，然后除以2，就可以得到图片在画布上的偏移量，从而实现居中显示。
    int offsetY = (canvasSize - newHeight) / 2;

    // ##8. 将缩放后的图片复制到画布中央
    cv::Rect roi(offsetX, offsetY, newWidth, newHeight);

    resizedImage.copyTo(canvas(roi));

    // 9. 使用fmt输出处理参数，马的搞那么多英文就是为了这个玩意。
    fmt::print("初始像素: {} x {}\n",
               originalWidth, originalHeight);

    fmt::print("缩放比例: {:.4f}\n", scale);

    fmt::print("处理后像素: {} x {}\n",
               newWidth, newHeight);

    fmt::print("图像偏移距离 X : {}, 图像偏移距离 Y : {}\n",
               offsetX, offsetY);

    // 10. 返回最终图片，大功告成
    return canvas;
}
