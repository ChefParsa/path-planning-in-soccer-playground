# ifndef MRL_ROBOT_IMAGE
    # include "../include/robot_img.hpp"
    /**
     * @brief robot image constructor
    */
    RobotImage::RobotImage() {
        robotImg = cv::imread("../src/robot2.png");
        if (!robotImg.empty()) {
            cv::resize(robotImg, resized_robotImg, ROBOT_IMG_SIZE);
        } else {
        std::cerr << "Image not loaded successfully." << std::endl;
        }
    }
    void RobotImage::copyToPlayground(cv::Mat& preview) {
        // Calculate the position to place the resized image in the center of the preview
        int x_center = (preview.cols - resized_robotImg.cols) / 2;
        int y_center = (preview.rows - resized_robotImg.rows) / 2;
        // Copy the resized image to the center of the preview
        resized_robotImg.copyTo(preview(cv::Rect(x_center, y_center, resized_robotImg.cols, resized_robotImg.rows)));
    }
# endif //MRL_ROBOT_IMAGE