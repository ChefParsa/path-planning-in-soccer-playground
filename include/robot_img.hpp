# ifndef ROBOT_IMAGE

    // Include OpenCV HighGUI
    # ifndef OPENCV_HIGHGUI_HPP
        # include <opencv4/opencv2/highgui.hpp>
    # endif // OPENCV_HIGHGUI_HPP

    // Include OpenCV Image Processing
    # ifndef OPENCV_IMGPROC_HPP
        # include <opencv4/opencv2/imgproc.hpp>
    # endif // OPENCV_IMGPROC_HPP
    
    // Include Necessary Libraries
    # include <iostream>

    // Size Of Robot's Image
    # define ROBOT_IMG_SIZE cv::Size(30, 30)

    /**
     * @brief MRL HSL Robot Image class
     * @details This Class Is Used For Make Robot's Image Inside Soccer Playground With OpenCV
    */
    class RobotImage {
        private:
            /**
             * @brief Robot's Image
            */
            cv::Mat robotImg;
            /**
             * @brief Resized Robot's Image
            */
            cv::Mat resized_robotImg;
        public:
            /**
             * Robot Image constructor
            */
            RobotImage();
            /**
             * @brief Method for Copy Robot Image Inside Soccer Playground
            */
            void copyToPlayground(cv::Mat&);
    };

# endif //ROBOT_IMAGE