// Program for using using RaspiCam

#include <opencv2/opencv.hpp>
#include <raspicam_cv.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <wiringPi.h>

using namespace std;
using namespace cv;
using namespace raspicam;

// RaspiCam_Cv Class
RaspiCam_Cv camera;

// Frame for viewing the video
Mat frame, framePers, frameGray, frameThresh, frameEdge, frameFinal, frameFinalDuplicate, matrix, ROILane;

// Points for region of Interest
Point2f source[] = {Point2f(25, 160), Point2f(330, 160), Point2f(0, 210), Point2f(360, 210)};

// Points for Perspective Wrap
Point2f destination[] = {Point2f(80, 0), Point2f(280, 0), Point2f(80, 240), Point2f(280, 240)};

// Vector for storing Intensities
// Size same as Frame Width
vector<int> histogramLane(360);

// Lane Positions
int leftLanePos, rightLanePos, centerLanePos, frameCenter, result;

// To display useful info on screen
stringstream ss;

void setup (int argc, char **argv)
{
    // Resolution 360 * 240
    // FPS set to 0 so camera can capture as many frames per second as it can

    camera.set(CAP_PROP_FRAME_WIDTH, ("-w", argc, argv, 360));
    camera.set(CAP_PROP_FRAME_HEIGHT, ("-h", argc, argv, 240));
    camera.set(CAP_PROP_BRIGHTNESS, ("-br", argc, argv, 50));
    camera.set(CAP_PROP_CONTRAST, ("-co", argc, argv, 50));
    camera.set(CAP_PROP_SATURATION, ("-sa", argc, argv, 50));
    camera.set(CAP_PROP_GAIN, ("-g", argc, argv, 50));
    camera.set(CAP_PROP_FPS, ("-fps", argc, argv, 0));
}

void perspective()
{
    /* line(image_name, point_1, point_2, color_of_line, width_of_line);

    * As opencv processes images in BGR mode -->
    * Scalar(blue_channel, green_channel, red_channel);
    */

    line(frame, source[0], source[1], Scalar(0, 0, 255), 2);
    line(frame, source[1], source[3], Scalar(0, 0, 255), 2);
    line(frame, source[3], source[2], Scalar(0, 0, 255), 2);
    line(frame, source[2], source[0], Scalar(0, 0, 255), 2);

    // line(frame, destination[0], destination[1], Scalar(0, 255, 0), 2);
    // line(frame, destination[1], destination[3], Scalar(0, 255, 0), 2);
    // line(frame, destination[3], destination[2], Scalar(0, 255, 0), 2);
    // line(frame, destination[2], destination[0], Scalar(0, 255, 0), 2);

    matrix = getPerspectiveTransform(source, destination);

    // warpPerpective(input_image, output_image, transformed_result, size_of_image);
    warpPerspective(frame, framePers, matrix, Size(360, 240));
}

void threshold()
{
    cvtColor(framePers, frameGray, COLOR_RGB2GRAY);

    // inRange(input_image, min_threshold_for_white, max_threshold_for_white, output_image);
    // These values vary for indoor and outdoor conditions
    inRange(frameGray, 240, 255, frameThresh);

    // Canny Edge Detection
    Canny(frameGray, frameEdge, 600, 700, 3, false);

    // Merging Threshold Image and Canny Edge Detection Image
    add(frameThresh, frameEdge, frameFinal);

    // Coverting the final image which is greyscale to rgb
    cvtColor(frameFinal, frameFinal, COLOR_GREY2RGB);

    /*
    * The bottom part of the lane disappears (bottom region of interest) as we apply divide 
    * function in that region containing rectangular strips to prevent this we use a duplicate frame.
    */
    cvtColor(frameFinal, frameFinalDuplicate, COLOR_RGB2BGR);
}

void histogram()
{
    for(int i=0; i<frame.size().width(); ++i)
    {
        ROILane = frameFinalDuplicate(Rect(i, 140, 1, 100));

        // Normalize the pixels by dividing by maximum possible intensity
        divide(255, ROILane, ROILane);
        histogramLane.push_back((int)(sum(ROILane)[0]));
    }
}

void laneFinder()
{
    vector<int>::iterator leftPtr, rightPtr;

    // Find the max value in less than first half of the vector
    leftPtr = max_element(histogramLane.begin(), histogramLane.begin() + 160);
    leftLanePos = distance(histogramLane.begin(), leftPtr);

    // Find the max value in less than second half of the vector
    rightPtr = max_element(histogramLane.begin() + 200, histogramLane.end());
    rightLanePos = distance(histogramLane.begin(), rightPtr);

    // Draw lines for lane positions on the final image
    line(frameFinal, Point2f(leftLanePos, 0), Point2f(leftLanePos, 240), Scalar(0, 255, 0), 2);
    line(frameFinal, Point2f(rightLanePos, 0), Point2f(rightLanePos, 240), Scalar(0, 255, 0), 2);
}

void laneCenter()
{
    centerLanePos = (rightLanePos - leftLanePos) / 2 + leftLanePos;

    // Center of the frame 360 / 2
    // Set it accordingly
    frameCenter = 180;

    // Plot Lane Center
    line(frameFinal, Point2f(centerLanePos, 0), Point2f(centerLanePos, 240), Scalar(0, 255, 0), 3);

    // Plot Frame Center
    line(frameFinal, Point2f(frameCenter, 0), Point2f(frameCenter, 240), Scalar(255, 0, 0), 3);

    result = centerLanePos - frameCenter;
}

void capture()
{
    camera.grab();
    camera.retrieve(frame);

    // Convert BGR Image to RGB Image
    // cvtColor(input_image, output_image, color);
    cvtColor(frame, frame, COLOR_BGR2RGB); 
}

int main(int argc, char **argv)
{
    wiringPiSetup();
    pinMode(21, OUTPUT);
    pinMode(22, OUTPUT);
    pinMode(23, OUTPUT);
    pinMode(24, OUTPUT);

    cout << "Connecting to Camera ..." << "\n";

    if(!camera.open())
    {
        cout << "Failed to Connect !!!" << "\n";
        return -1;
    }
    
    cout << "Connected !!!" << "\n";

    // Print Camera ID
    cout << "Camera ID = " << camera.getId() << "\n";

    // Setup RaspiCam
    setup(argc, argv);

    while(1)
    {
        auto start = std::chrono::steady_clock::now();

        // Capture Image
        capture();

        // Draw Region of Interest
        perspective();

        // Threshold Operations
        threshold();

        // Calculate Histogram
        histogram();

        // Find Lanes
        laneFinder();

        // Find Lane Center
        laneCenter();

        // Arduino Communication
        if(result == 0)
        {
            // decimal = 0
            digitalWrite(21, 0); // LSB
            digitalWrite(22, 0);
            digitalWrite(23, 0);
            digitalWrite(24, 0); // MSB

            cout << "Forward" << "\n";
        }
        else if(result > 0 && result < 10)
        {
            // decimal = 1
            digitalWrite(21, 1); // LSB
            digitalWrite(22, 0);
            digitalWrite(23, 0);
            digitalWrite(24, 0); // MSB

            cout << "Right1" << "\n";
        }
        else if(result >= 10 && result < 20)
        {
            // decimal = 2
            digitalWrite(21, 0); // LSB
            digitalWrite(22, 1);
            digitalWrite(23, 0);
            digitalWrite(24, 0); // MSB

            cout << "Right2" << "\n";
        }
        else if(result >= 20)
        {
            // decimal = 3
            digitalWrite(21, 1); // LSB
            digitalWrite(22, 1);
            digitalWrite(23, 0);
            digitalWrite(24, 0); // MSB

            cout << "Right3" << "\n";
        }
        else if(result < 0 && result > -10)
        {
            // decimal = 4
            digitalWrite(21, 0); // LSB
            digitalWrite(22, 0);
            digitalWrite(23, 1);
            digitalWrite(24, 0); // MSB

            cout << "Left1" << "\n";
        }
        else if(result <= -10 && result > -20)
        {
            // decimal = 5
            digitalWrite(21, 1); // LSB
            digitalWrite(22, 0);
            digitalWrite(23, 1);
            digitalWrite(24, 0); // MSB

            cout << "Left2" << "\n";
        }
        else if(result <= -20)
        {
            // decimal = 6
            digitalWrite(21, 0); // LSB
            digitalWrite(22, 1);
            digitalWrite(23, 1);
            digitalWrite(24, 0); // MSB

            cout << "Left3" << "\n";
        }

        ss.str(" ");
        ss.clear();
        ss << "Result = " <<result;
        putText(frame, ss.str(), Point2f(1, 50), 0, 1, Scalar(0, 0, 255), 2);

        // RGB
        namedWindow("original", WINDOW_KEEPRATIO);
        moveWindow("original", 0, 100);
        resizeWindow("original", 640, 480);

        // Display the frame
        imshow("original", frame);
        waitKey(1);

        // Perspective Wrap Image
        namedWindow("perspective", WINDOW_KEEPRATIO);
        moveWindow("perspective", 640, 100);
        resizeWindow("perspective", 640, 480);

        // Display the frame
        imshow("perspective", framePers);
        waitKey(1);

         // Canny Edge Detection
        namedWindow("final", WINDOW_KEEPRATIO);
        moveWindow("final", 1280, 100);
        resizeWindow("final", 640, 480);

        // Display the frame
        imshow("final", frameFinal);
        waitKey(1);

        auto end = std::chrono::steady_clock::now();

        std::chrono::duration<double> elapsed_seconds = end-start;
        float t = elapsed_seconds.count();
        int FPS = 1 / t;

        cout << "FPS = " << FPS << "\n";
    }

    return 0;
}