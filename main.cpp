#include <opencv2/opencv.hpp>
#include <iostream>


int main(int argc, char **argv) {
    cv::VideoCapture cap(0);

    if (cap.isOpened() == false) {
        std::cout << "Unable to open camera\n";
        std::cin.get();
        return -1;
    }

    double dWidth{cap.get(cv::CAP_PROP_FRAME_WIDTH)};
    double dHeight{cap.get(cv::CAP_PROP_FRAME_HEIGHT)};

    std::cout << "The resolution is:" << dWidth << "x" << dHeight << std::endl;

    cv::namedWindow("Video Capture", cv::WINDOW_AUTOSIZE);

    while (true) {
        cv::Mat frame;
        bool bSuccess = cap.read(frame);

        if (bSuccess == false) {
            std::cout << "Camera got disconnected\n";
            std::cin.get();
            return -1;
        }
        cv::imshow("Video Capture", frame);
        const auto key = cv::waitKey(1);
        if (key == 'q') {
            break;
        }
    }
    return 0;
}
