// Program for taking image using RaspiCam

#include <opencv2/opencv.hpp>
#include <raspicam_cv.h>
#include <iostream>

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

    camera.grab();
    camera.retrieve(frame);

    imshow("frame", frame);
    waitKey();

    return 0;
}