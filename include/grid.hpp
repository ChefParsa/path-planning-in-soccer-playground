# ifndef GRID_PLAYGROUND

    // Include playground Config
    # ifndef PLAYGROUND_CONFIGS
        # include "configs.hpp"
    # endif // PLAYGROUND_CONFIGS

    // Include OpenCV HighGUI
    # ifndef OPENCV_HIGHGUI_HPP
        # include <opencv4/opencv2/highgui.hpp>
    # endif // OPENCV_HIGHGUI_HPP

    // Include OpenCV Image Processing
    # ifndef OPENCV_IMGPROC_HPP
        # include <opencv4/opencv2/imgproc.hpp>
    # endif // OPENCV_IMGPROC_HPP
    // include Necessary Library
    # include <algorithm>
    // Define Move Block Width
    # define MOVE_BLOCK_WIDTH 15
    # define MOVE_BLOCK_LENGTH 20

    // Define Grid Color
    # define GRID_COLOR cv::Scalar(165, 131, 62)

    // Define Grid Thickness
    # define GRID_THICKNESS 1

    enum GRID_TYPES {
        GRID_TYPE_NORMAL,
        GRID_TYPE_BARRIER,
        GRID_TYPE_HAS_BALL,
        GRID_TYPE_HAS_AGENT
    };

    class Grid {
        private:
            bool show_grid;
            int grid_rows;
            int grid_columns;
            bool grid_drawed;
            bool point_drawed;
            bool show_point;
            cv::Mat main_preview;
            bool rows_divisible;
            bool columns_divisible;
            int remaining_length;
            int remaining_width;
            int cell_number_length;
            int cell_number_width;
            struct squareOfGrid {
                cv::Point topLeft;
                cv::Point bottomRight;
                cv::Point center;
                int type;
            };
            //std::vector<pair<int, int>> middle_points;
            std::vector<squareOfGrid> square_info;
            std::vector<std::vector<int>> point_status;
            //std::vector <std::vector<std::pair<int, int>>> point_location;
            // 1D Point Location
            std::vector<std::pair<int, int>> point_location;
            // 2D Point Location
            std::vector<std::vector<std::pair<int, int>>> point_location_2D;
        public:
            Grid(cv::Mat&);
            void showGrid(cv::Mat&);
            void drawGrid(cv::Mat&, int, int, bool&);
            void makePairPoints();
            std::vector<std::vector<int>> returnPointStatus();
            std::vector<std::vector<std::pair<int, int>>> returnPointLocation_2D();
            //void drawPoint(cv::Mat&, int, int, bool&);
    };
# endif // GRID_PLAYGROUND

/*
enum GRID_TYPES {
    GRID_TYPE_NORMAL,
    GRID_TYPE_BARRIER,
    GRID_TYPE_HAS_BALL,
    GRID_TYPE_HAS_AGENT
};

class Grid {
    private:
        cv::Point bottomRight;
        cv::Point topLeft;
        cv::Point middle;
        int type;
}
*/

/*
    class Grid {
        private:
            bool show_grid;
            int grid_rows;
            int grid_columns;
            bool grid_drawed;
            bool point_drawed;
            bool show_point;
            std::vector <cv::Mat> main_preview;
        public:
            Grid(cv::Mat&);
            void showGrid();
            cv::Mat drawGrid(cv::Mat, int, int, bool&);
            cv::Mat drawPoint(cv::Mat, int, int, bool&);
    };
# endif // GRID_PLAYGROUND
*/


/*
# ifndef MRL_GRID_PLAYGROUND
    # include "include/grid.hpp"
# endif // MRL_GRID_PLAYGROUND

# include <iostream>
using namespace std;

Grid::Grid(cv::Mat& preview) {
    show_grid = false;
    show_point = false;
    grid_drawed = false;
    point_drawed = false;
    main_preview = preview.clone();
    grid_columns = 30;
    grid_rows = 30;
}

void Grid::drawGrid(cv::Mat& preview, int rows, int cols, bool& grid_drawed) {
    int cellWidth = FIELD_LENGTH * SCALE / cols;
    int cellHeight = FIELD_WIDTH * SCALE / rows;
    // Draw vertical lines
    for (int i = 1; i < cols; i++) {
        int x = i * cellWidth;
        cv::line(preview, cv::Point(x + BORDER_STRIP_WIDTH * SCALE, BORDER_STRIP_WIDTH * SCALE),
        cv::Point(x + BORDER_STRIP_WIDTH * SCALE, (BORDER_STRIP_WIDTH + FIELD_WIDTH) * SCALE), cv::Scalar(165, 131, 62), 1);
    }

    // Draw horizontal lines
    for (int j = 1; j < rows; j++) {
        int y = j * cellHeight;
        cv::line(preview, cv::Point(BORDER_STRIP_WIDTH * SCALE, y + BORDER_STRIP_WIDTH * SCALE),
        cv::Point((BORDER_STRIP_WIDTH + FIELD_LENGTH) * SCALE, y + BORDER_STRIP_WIDTH * SCALE), cv::Scalar(165, 131, 62), 1);
    }
    grid_drawed = true;    
}

void Grid::showGrid(cv::Mat& preview) {
    while (true) {
        if (show_grid && !grid_drawed) {
            // Draw the grid on the image
            drawGrid(preview, grid_rows, grid_columns, grid_drawed);   
        }

        if (show_point && !point_drawed) {
            // Draw the grid on the image
            drawPoint(preview, grid_rows, grid_columns, point_drawed);   
        }

        cv::imshow("Grid", preview);

        char key = cv::waitKey(30);

        // Press 'g' to toggle the grid
        if (key == 'g' || key == 'G') {
            show_grid = !show_grid;
            grid_drawed = false;
            preview = main_preview.clone();  // Clear the image when toggling
        }

        if (key == 'p' || key == 'P') {
            show_point = !show_point;
            point_drawed = false;
            preview = main_preview.clone();  // Clear the image when toggling
        }

        // Press 'esc' to exit the program
        if (key == 27) {
            break;
        }
    }
    cv::destroyAllWindows();
}

void Grid::drawPoint(cv::Mat& preview, int rows, int cols, bool& point_drawed) {
    int point_x = (FIELD_LENGTH * SCALE) / cols;
    int point_y = (FIELD_WIDTH * SCALE) / rows;

    for (int i = 0; i < (rows * 2) + 1; i++) {
        int y = i * point_y / 2;
        for (int j = 0; j < (cols * 2) + 1; j++) {
            int x = j * point_x / 2;
            cv::Point center (x + BORDER_STRIP_WIDTH * SCALE, y + BORDER_STRIP_WIDTH * SCALE);
            cv::circle(preview, center, 2, cv::Scalar(0, 0, 255), -1);
        }
    }
    point_drawed = true;
}
*/