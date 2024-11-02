#include <opencv2/opencv.hpp>
#include "glad/glad.h"
#include "threepp/threepp.hpp"
#include "geoGeneration.hpp"
#include "gridManager.hpp"

using namespace threepp;
using namespace cv;

void getContours(Mat imgDil, Mat img) {
    std::vector<std::vector<Point> > contours;
    std::vector<Vec4i> hierarchy;


    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    //drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

    std::vector<std::vector<Point> > conPoly{contours.size()};
    std::vector<Rect> boundRect{contours.size()};

    for (int i{}; i < contours.size(); i++) {
        int area = contourArea(contours[i]);
        if (area < 4000) {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
            drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
            boundRect[i] = boundingRect(conPoly[i]);
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
        }
    }
    std::cout << "Topleft corner: " << boundRect[0].tl() << " RightBotton corner: " << boundRect[0].br() << std::endl;
}


int main(int argc, char **argv) {
    //Canvas creation
    Canvas canvas("RandomGeometry", {{"aa", 4}});
    constexpr std::pair<int, int> imageSize{800, 800};
    canvas.setSize({imageSize.first, imageSize.second});

    //Renderer creation
    GLRenderer renderer(canvas.size());

    //Creates scene
    auto scene{Scene::create()};

    //Orthographic camera
    auto camera = OrthographicCamera::create(0, imageSize.first,
                                             0, imageSize.second, -1000, 1000);
    camera->position.z = 10;

    // Framebuffer (Help from GPT)
    std::vector<unsigned char> pixels(imageSize.first * imageSize.second * 3);

    //OPENCV Window
    std::string windowName{"ThreePP"};
    namedWindow(windowName, WINDOW_AUTOSIZE);

    //Mapping coords to a grid
    GridManager mainGrid(imageSize.first, 15, 50);
    mainGrid.createGrid();

    //GeoGen class for generating "random geometries"
    GeoGen test(40, 10, geoGen::Shape::CIRCLE, Color::burlywood);
    GeoGen test2(40, 15, geoGen::Shape::CUBE, Color::red);
    GeoGen test3(40, 4, geoGen::Shape::CUBE, Color::green);
    GeoGen test4(40, 4, geoGen::Shape::CUBE, Color::orange);
    test.generate(mainGrid, *scene);
    test2.generate(mainGrid, *scene);
    test3.generate(mainGrid, *scene);
    test4.generate(mainGrid, *scene); 


    //Single test mesh
    // auto testmesh{MeshBasicMaterial::create()};
    // testmesh->color = Color::red;
    // testmesh->side=Side::Double;
    //
    // auto testgeo{CircleGeometry::create(50, 50, 0, 2 * std::numbers::pi)};
    //
    // auto testmesh2{Mesh::create(testgeo, testmesh)};
    // testmesh2->position.set(400, 400, 0);
    //
    // scene->add(testmesh2);

    //TEST CODE FOR OPENCV

    /*Mat threeppCamHSV;
    Mat mask;

    int hmin{};
    int hmax{179};
    int smin{};
    int smax{255};
    int vmin{};
    int vmax{255};

    namedWindow("Trackbars", (640, 200));
    createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    createTrackbar("Hue Max", "Trackbars", &hmax, 179);
    createTrackbar("Sat Min", "Trackbars", &smin, 255);
    createTrackbar("Sat Max", "Trackbars", &smax, 255);
    createTrackbar("Val Min", "Trackbars", &vmin, 255);
    createTrackbar("Val Max", "Trackbars", &vmax, 255);*/

    Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

    //TEST CODE FOR OPENCV

    //Render loop
    Clock clock;
    canvas.animate([&]() {
        renderer.render(*scene, *camera);

        //Pixels are read into the buffer here.
        glReadPixels(0, 0, imageSize.first, imageSize.second, GL_BGR, GL_UNSIGNED_BYTE, pixels.data());

        //Creates an OPENCV Mat object for the pixels. (https://stackoverflow.com/questions/38489423/c-convert-rgb-1-d-array-to-opencv-mat-image)
        Mat threeppCam{imageSize.second, imageSize.first, CV_8UC3, pixels.data()};

        //OpenCV uses a different origin for the image, so it is flipped here.
        flip(threeppCam, threeppCam, 0);

        //TEST CODE FOR OPENCV COLOR RECOGNITION

        /*cvtColor(threeppCam, threeppCamHSV, COLOR_BGR2HSV);

        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);

        inRange(threeppCamHSV, lower, upper, mask);

        imshow("HSV", threeppCamHSV);
        imshow("maskTEST", mask);*/

        //Preprocessing
        cvtColor(threeppCam, imgGray, COLOR_BGR2GRAY);
        GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
        Canny(imgBlur, imgCanny, 25, 75);
        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        dilate(imgCanny, imgDil, kernel);


        //TEST CODE FOR OPENCV COLOR RECOGNITION

        //getContours(imgDil, threeppCam);

        imshow(windowName, threeppCam);
        imshow("Processed Image", imgDil);


        //TEST CODE
        //std::cout << mainGrid.getTestValue(14).first << std::endl;


        waitKey(1);
    });
}
