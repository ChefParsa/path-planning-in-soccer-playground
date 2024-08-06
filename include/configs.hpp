//-- MRL HSL Soccer Playground Configs
# ifndef MRL_SOCCER_PLAYGROUND_CONFIGS
    # define MRL_SOCCER_PLAYGROUND_CONFIGS
    //-- Define Project Version
    # define PROJECT_VERSION "1.1"
    //-- Define Playground Dimensions
    # define GOAL_DEPTH 0.6                 //-- Goal Depth in Meters
    # define GOAL_WIDTH 2.6                 //-- Goal Width in Meters
    # define GOAL_HEIGHT 1.2                //-- Goal Height in Meters (Not Used)
    # define FIELD_WIDTH 6.0                //-- Field Width in Meters
    # define FIELD_LENGTH 9.0               //-- Field Length in Meters
    # define GOAL_AREA_WIDTH 3.0            //-- Goal Area Width in Meters
    # define GOAL_AREA_LENGTH 1.0           //-- Goal Area Length in Meters
    # define BORDER_STRIP_WIDTH 1.0         //-- Border Strip Width in Meters
    # define PENALTY_AREA_WIDTH 5.0         //-- Penalty Area Width in Meters
    # define PENALTY_AREA_LENGTH 2.0        //-- Penalty Area Length in Meters
    # define PENALTY_MARK_DISTANCE 1.5      //-- Penalty Mark Distance in Meters
    # define CENTER_CIRCLE_DIAMETER 1.5     //-- Center Circle Diameter in Meters
    # define SCALE 110                     //-- Define Playground View Scale
    //-- Include OpenCV HighGUI
    # ifndef OPENCV_HIGHGUI_HPP
        # include <opencv4/opencv2/highgui.hpp>
    # endif // OPENCV_HIGHGUI_HPP
    //-- Include OpenCV Image Processing
    # ifndef OPENCV_IMGPROC_HPP
        # include <opencv4/opencv2/imgproc.hpp>
    # endif // OPENCV_IMGPROC_HPP
    //-- Include X11 Library
    # ifndef _X11_XLIB_H_
        # include <X11/Xlib.h>
    # endif // _X11_XLIB_H_
    //-- Include Necessary Libraries
    # include <vector>
    //-- Color of Playground Opponent Goal Area
    # define OPPONENT_GOAL_AREA_COLOR cv::Scalar(0, 255, 255)
    //-- Color of Playground Team Goal Area
    # define TEAM_GOAL_AREA_COLOR cv::Scalar(255, 255, 0)
    //-- Color of Playground Background
    # define BACKGROUND_COLOR cv::Scalar(7, 17, 0)
    //-- White color
    # define White_COLOR cv::Scalar(255, 255, 255)
    //-- Filled With Color
    # define FILLED_WITH_COLOR cv::FILLED
    //-- Window Name
    # define WINDOW_NAME "Soccer Playground"
    //-- Playground Line Thickness
    # define LINE_THICKNESS 1
    //-- Playground Line Type
    # define LINE_TYPE cv::LINE_AA
    //-- Playground Line Shift
    # define LINE_SHIFT 0
    //-- Playground Circle Radius
    # define CIRCLE_RADIUS 6
# endif // MRL_SOCCER_PLAYGROUND_CONFIGS