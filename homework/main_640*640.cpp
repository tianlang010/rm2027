//导入库
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <fmt/format.h>
//导入该死的头文件
#include "tools.hpp"

int main(int argc, char* argv[])
{
    // 1. 检查是否提供了图片路径
    if (argc < 2)
    {
        fmt::print("Usage: {} image_path\n", argv[0]);
        return 1;
    }

    // 2. 读取图片
    cv::Mat image = cv::imread(argv[1]);

    // 3. 检查图片是否读取成功
    if (image.empty())
    {
        fmt::print("Cannot read image: {}\n", argv[1]);
        return 1;
    }

    // 4. 调用tools中的缩放函数
    cv::Mat result = ResizeWithPadding(image);

    // 5. 显示最终结果
    cv::imshow("Result", result);

    // 6. 等待用户按键
    cv::waitKey(0);

    // 7. 关闭窗口并结束程序
    cv::destroyAllWindows();

    return 0;
}
