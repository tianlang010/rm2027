//避免重复包含头文件，使用#pragma once
#pragma once

//使用包含opencv的头文件
#include <opencv2/core.hpp>

// 声明一个缩放函数，我需要让函数输入一张图片，然后根据函数进行缩放，输出一张缩放后的图片
cv::Mat ResizeWithPadding(const cv::Mat& input);

//我去我简直是个天才