# ifndef MRL_SOCCER_PLAYGROUND_CONFIGS    
    # include "configs.hpp"

    /**
     * @brief Rectangle Structure
     */
    struct SoccerRectangle {
        cv::Point topLeft;
        cv::Point downRight;
        cv::Scalar color;
        int thickness;
    };
    /**
     * @brief Circle Structure
     */
    struct SoccerCircle {
        cv::Point center;
        int radius;
        cv::Scalar color;
        int thickness;
        bool filled;
    };
    /**
     * @brief Line Structure
     */
    struct SoccerLine {
        cv::Point start;
        cv::Point end;
        cv::Scalar color;
        int thickness;
    };
    /**
     * @brief MRL HSL Soccer Playground Class
     * @details This class is used to create a soccer playground with OpenCV
     */
    class SoccerPlayground {
        private:
            /**
             * @brief Playground Initialization Status
             */
            bool isInitialized;
            /**
             * @brief Playground Image
             */
            cv::Mat preview;
            /**
             * @brief Playground Rectangles
             */
            std::vector<SoccerRectangle> rectangles;
            /**
             * @brief Playground Circles
             */
            std::vector<SoccerCircle> circles;
            /**
             * @brief Playground Lines
             */
            std::vector<SoccerLine> lines;
        public:
            /**
             * @brief Initialize Soccer Playground Object
             */
            SoccerPlayground();
            /**
             * @brief Method to Get Playground Image
             * @return cv::Mat
             */
            cv::Mat getPlayground();
            /**
             * @brief Initialize Playground Rectangles
             */
            void initRectangles();
            /**
             * @brief Initialize Playground Circles
             */
            void initCircles();
            /**
             * @brief Initialize Playground Lines
             */
            void initLines();
            /**
             * @brief Method to Draw Playground
             */
            void drawPlayground();
            /**
             * @brief Method to Show Playground
             */
            void showPlayground();
    };
# endif // MRL_SOCCER_PLAYGROUND_CONFIGS