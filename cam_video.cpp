// Program for taking video using RaspiCam

#include <opencv2/opencv.hpp>
#include <raspicam_cv.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;
using namespace cv;
using namespace raspicam;

Mat frame;

void setup (int argc, char **argv, RaspiCam_Cv &camera)
{
    camera.set(CAP_PROP_FRAME_WIDTH, ("-w", argc, argv, 360));
    camera.set(CAP_PROP_FRAME_HEIGHT, ("-h", argc, argv, 240));
    camera.set(CAP_PROP_BRIGHTNESS, ("-br", argc, argv, 50));
    camera.set(CAP_PROP_CONTRAST, ("-co", argc, argv, 50));
    camera.set(CAP_PROP_SATURATION, ("-sa", argc, argv, 50));
    camera.set(CAP_PROP_GAIN, ("-g", argc, argv, 50));
    camera.set(CAP_PROP_FPS, ("-fps", argc, argv, 0));
}

int main(int argc, char **argv)
{
    RaspiCam_Cv camera;

    cout << "Connecting to Camera ..." << "\n";

    if(!camera.open())
    {
        cout << "Failed to Connect !!!" << "\n";
        return -1;
    }
    
    cout << "Connected !!!" << "\n";
    cout << "Camera ID = " << camera.getId() << "\n";

    setup(argc, argv, camera);

    while(1)
    {
        auto start = std::chrono::steady_clock::now();
        camera.grab();
        camera.retrieve(frame);
        auto end = std::chrono::steady_clock::now();

        std::chrono::duration<double> elapsed_seconds = end-start;
        float t = elapsed_seconds.count();
        int FPS = 1 / t;

        cout << "FPS = " << FPS << "\n";
    
        imshow("frame", frame);
        waitKey(1);
    }

    return 0;
}