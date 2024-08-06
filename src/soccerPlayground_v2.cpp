# ifndef MRL_SOCCER_PLAYGROUND
    # include "../include/soccerPlayground_v2.hpp"
    /**
     * @brief Initialize Soccer Playground Object
     */
    SoccerPlayground::SoccerPlayground() {
        rectangles.resize(0);
        circles.resize(0);
        lines.resize(0);
        preview = cv::Mat(
            (FIELD_WIDTH + BORDER_STRIP_WIDTH * 2) * SCALE,
            (FIELD_LENGTH + BORDER_STRIP_WIDTH * 2) * SCALE,
            CV_8UC3,
            BACKGROUND_COLOR
        );
        //Initialize Shapes
        initRectangles();
        initCircles();
        initLines();

        isInitialized = true;

        drawPlayground();
    }
    /**
     * @brief Method to Preview
     * @return cv::Mat
     */
    cv::Mat SoccerPlayground::getPlayground() {
        return preview;
    }
    /**
     * @brief Method to Show Playground
    */
   void SoccerPlayground::showPlayground(){
        cv::imshow(WINDOW_NAME, preview);
        cv::waitKey(0);
        cv::destroyAllWindows();
   }
    /**
     * @brief Initialize Playground Rectangles
     */
    void SoccerPlayground::initRectangles() {
        //-- Goal Area Left
        rectangles.push_back({
            cv::Point(
                BORDER_STRIP_WIDTH * SCALE,
                (BORDER_STRIP_WIDTH + (FIELD_WIDTH - GOAL_AREA_WIDTH) / 2) * SCALE
            ),
            cv::Point(
                (BORDER_STRIP_WIDTH + GOAL_AREA_LENGTH) * SCALE,
                (BORDER_STRIP_WIDTH + (FIELD_WIDTH + GOAL_AREA_WIDTH) / 2) * SCALE
            ),
            White_COLOR,
            LINE_THICKNESS,
        });
        //-- Goal Area Right
        rectangles.push_back({
            cv::Point(
                (BORDER_STRIP_WIDTH + (FIELD_LENGTH - GOAL_AREA_LENGTH)) * SCALE,
                (BORDER_STRIP_WIDTH + (FIELD_WIDTH - GOAL_AREA_WIDTH) / 2) * SCALE
            ),
            cv::Point(
                (BORDER_STRIP_WIDTH + FIELD_LENGTH) * SCALE,
                (BORDER_STRIP_WIDTH + (FIELD_WIDTH + GOAL_AREA_WIDTH) / 2) * SCALE
            ),
            White_COLOR,
            LINE_THICKNESS,
        });
        //-- Goal Left
        rectangles.push_back({
            cv::Point(
                BORDER_STRIP_WIDTH * SCALE,
                (BORDER_STRIP_WIDTH + (FIELD_WIDTH - GOAL_WIDTH) / 2) * SCALE
            ),
            cv::Point(
                (BORDER_STRIP_WIDTH - GOAL_DEPTH) * SCALE,
                (BORDER_STRIP_WIDTH + (FIELD_WIDTH + GOAL_WIDTH) / 2) * SCALE
            ),
            TEAM_GOAL_AREA_COLOR,
            LINE_THICKNESS,
        });
        //-- Goal Right
        rectangles.push_back({
            cv::Point(
                (BORDER_STRIP_WIDTH + FIELD_LENGTH + GOAL_DEPTH) * SCALE,
                (BORDER_STRIP_WIDTH + (FIELD_WIDTH - GOAL_WIDTH) / 2) * SCALE
            ),
            cv::Point(
                (BORDER_STRIP_WIDTH + FIELD_LENGTH) * SCALE,
                (BORDER_STRIP_WIDTH + (FIELD_WIDTH + GOAL_WIDTH) / 2) * SCALE
            ),
            OPPONENT_GOAL_AREA_COLOR,
            LINE_THICKNESS,
        });
        //-- Penalty Area Left
        rectangles.push_back({
            cv::Point(
                BORDER_STRIP_WIDTH * SCALE,
                (BORDER_STRIP_WIDTH + (FIELD_WIDTH - PENALTY_AREA_WIDTH) / 2) * SCALE
            ),
            cv::Point(
                (BORDER_STRIP_WIDTH + PENALTY_AREA_LENGTH) * SCALE,
                (BORDER_STRIP_WIDTH + (FIELD_WIDTH - PENALTY_AREA_WIDTH) / 2 + PENALTY_AREA_WIDTH) * SCALE
            ),
            White_COLOR,
            LINE_THICKNESS,
        });
        //-- Penalty Area Right
        rectangles.push_back({
            cv::Point(
                (BORDER_STRIP_WIDTH + (FIELD_LENGTH - PENALTY_AREA_LENGTH)) * SCALE,
                (BORDER_STRIP_WIDTH + (FIELD_WIDTH - PENALTY_AREA_WIDTH) / 2) * SCALE
            ),
            cv::Point(
                (BORDER_STRIP_WIDTH + FIELD_LENGTH) * SCALE,
                (BORDER_STRIP_WIDTH + (FIELD_WIDTH - PENALTY_AREA_WIDTH) / 2 + PENALTY_AREA_WIDTH) * SCALE
            ),
            White_COLOR,
            LINE_THICKNESS,
        });
        //-- Main Rectangle
        rectangles.push_back({
            cv::Point(
                BORDER_STRIP_WIDTH * SCALE,
                BORDER_STRIP_WIDTH * SCALE
            ),
            cv::Point(
                (BORDER_STRIP_WIDTH + FIELD_LENGTH) * SCALE,
                (BORDER_STRIP_WIDTH + FIELD_WIDTH) * SCALE
            ),
            White_COLOR,
            LINE_THICKNESS,
        });
    }
    void SoccerPlayground::initCircles() {
        //-- Background Center Circle
        circles.push_back({
            cv::Point(
                (BORDER_STRIP_WIDTH + FIELD_LENGTH / 2) * SCALE,
                (BORDER_STRIP_WIDTH + FIELD_WIDTH / 2) * SCALE
            ),
            int(CENTER_CIRCLE_DIAMETER * SCALE / 2),
            BACKGROUND_COLOR,
            LINE_THICKNESS,
            true
        });
        //-- Center Circle
        circles.push_back({
            cv::Point(
                (BORDER_STRIP_WIDTH + FIELD_LENGTH / 2) * SCALE,
                (BORDER_STRIP_WIDTH + FIELD_WIDTH / 2) * SCALE
            ),
            int(CENTER_CIRCLE_DIAMETER * SCALE / 2),
            White_COLOR,
            LINE_THICKNESS,
            false
        });
        //-- Center Point
        circles.push_back({
            cv::Point(
                (BORDER_STRIP_WIDTH + FIELD_LENGTH / 2) * SCALE,
                (BORDER_STRIP_WIDTH + FIELD_WIDTH / 2) * SCALE
            ),
            CIRCLE_RADIUS,
            White_COLOR,
            LINE_THICKNESS,
            true
        });
        //-- Left Penalty Mark
        circles.push_back({
            cv::Point(
                (BORDER_STRIP_WIDTH + PENALTY_MARK_DISTANCE) * SCALE,
                (BORDER_STRIP_WIDTH + FIELD_WIDTH / 2) * SCALE
            ),
            CIRCLE_RADIUS,
            White_COLOR,
            LINE_THICKNESS,
            true
        });
        //-- Right Penalty Mark
        circles.push_back({
            cv::Point(
                (BORDER_STRIP_WIDTH + FIELD_LENGTH - PENALTY_MARK_DISTANCE) * SCALE,
                (BORDER_STRIP_WIDTH + FIELD_WIDTH / 2) * SCALE
            ),
            CIRCLE_RADIUS,
            White_COLOR,
            LINE_THICKNESS,
            true
        });
    }
    void SoccerPlayground::initLines() {
        //-- Half Line
        lines.push_back({
            cv::Point(
                (BORDER_STRIP_WIDTH + FIELD_LENGTH / 2) * SCALE,
                BORDER_STRIP_WIDTH * SCALE
            ),
            cv::Point(
                (BORDER_STRIP_WIDTH + FIELD_LENGTH / 2) * SCALE,
                (BORDER_STRIP_WIDTH + FIELD_WIDTH) * SCALE
            ),
            White_COLOR,
            LINE_THICKNESS,
        });
    }
    /**
     * @brief Method to Draw Playground
     */
    void SoccerPlayground::drawPlayground() {
        //-- Draw Rectangles
        for (int i = 0; i < rectangles.size(); i++) {
            cv::rectangle(
                preview,
                rectangles[i].topLeft,
                rectangles[i].downRight,
                rectangles[i].color,
                rectangles[i].thickness
            );
        }
        //-- Draw Lines
        for (int i = 0; i < lines.size(); i++) {
            cv::line(
                preview,
                lines[i].start,
                lines[i].end,
                lines[i].color,
                lines[i].thickness
            );
        }
        //-- Draw Circles
        for (int i = 0; i < circles.size(); i++) {
            if (circles[i].filled)
                circles[i].thickness = FILLED_WITH_COLOR;
            cv::circle(
                preview,
                circles[i].center,
                circles[i].radius,
                circles[i].color,
                circles[i].thickness
            );
        }
    }
# endif // MRL_SOCCER_PLAYGROUND