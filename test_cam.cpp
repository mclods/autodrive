// Program for accessing and testing RaspiCam

#include <opencv2/opencv.hpp>
#include <raspicam_cv.h>
#include <iostream>

using namespace std;
using namespace cv;
using namespace raspicam;

int main()
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

    return 0;
}