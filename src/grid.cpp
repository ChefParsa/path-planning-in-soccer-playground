# ifndef MRL_GRID_PLAYGROUND
    # include "../include/grid.hpp"
# endif // MRL_GRID_PLAYGROUND
# include <iostream>
using namespace std;

Grid::Grid(cv::Mat& preview) {
    show_grid = false;
    show_point = false;
    grid_drawed = false;
    point_drawed = false;
    main_preview = preview.clone();
    grid_columns = (FIELD_LENGTH / 2) * SCALE / MOVE_BLOCK_LENGTH;
    grid_rows = (FIELD_WIDTH / 2) * SCALE / MOVE_BLOCK_WIDTH;
    if (int((FIELD_LENGTH / 2) * SCALE) % MOVE_BLOCK_LENGTH == 0) {
        columns_divisible = true;
        remaining_length = None;
        cell_number_length = grid_columns * 2;
    }
    else {
        columns_divisible = false;
        remaining_length = int((FIELD_LENGTH / 2) * SCALE) % MOVE_BLOCK_LENGTH;
        cell_number_length = (grid_columns * 2) + 2;
    }
    if (int((FIELD_WIDTH / 2) * SCALE) % MOVE_BLOCK_WIDTH == 0) {
        rows_divisible = true;
        remaining_width = None;
        cell_number_width = grid_rows * 2;
    }
    else {
        rows_divisible = false;
        remaining_width = int((FIELD_WIDTH / 2) * SCALE) % MOVE_BLOCK_WIDTH;
        cell_number_width = (grid_rows * 2) + 2;
    }

    point_status.resize(cell_number_width, vector<int>(cell_number_length, -1));
    //point_location.resize(cell_number_width, vector<pair<int, int>>(cell_number_length, make_pair(-1, -1)));

    cout << "columns_divisible : " << columns_divisible << endl;
    cout << "rows_divisible : " << rows_divisible << endl;
    cout << "remaining_length : " << remaining_length << endl;
    cout << "remaining_width : " << remaining_width << endl;
    cout << "MOVE_BLOCK_LENGTH / 2 : " << MOVE_BLOCK_LENGTH / 2 << endl;
    cout << "MOVE_BLOCK_WIDTH / 2 : " << MOVE_BLOCK_WIDTH / 2 << endl;
    cout << "grid_columns : " << grid_columns << endl;
    cout << "grid_rows : " << grid_rows << endl;
    /*
    for (const auto& row : point_status) {
        for (const auto& element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "rows " << point_status.size() << endl;
    cout << "columns " << point_status[0].size() << endl;
    */
    /*
    for (const auto& row : point_location) {
        for (const auto& pair : row) {
            cout << "(" << pair.first << ", " << pair.second << ") ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "rows " << point_location.size() << endl;
    cout << "columns " << point_location[0].size() << endl;
    */
}

void Grid::drawGrid(cv::Mat& preview, int rows, int cols, bool& grid_drawed) {
    int cellWidth = MOVE_BLOCK_WIDTH; //FIELD_LENGTH * SCALE / cols;
    int cellLength = MOVE_BLOCK_LENGTH; //FIELD_WIDTH * SCALE / rows;
    
    for (int i = 1; i < rows + 1; i++) {
        int y = i * cellWidth;
        
        for (int j = 0; j < cols; j++) {
            int x = j * cellLength;
            
            squareOfGrid square;

            square.topLeft = cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
            (y - cellWidth) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

            square.bottomRight = cv::Point(x + cellLength + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
            y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

            square.center = cv::Point(x + cellLength / 2 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
            (y - cellWidth / 2)+ (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

            square.type = 0;

            cv::rectangle(preview, cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE,
            (y - cellWidth) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), 
            cv::Point(x + cellLength + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
            y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), GRID_COLOR, GRID_THICKNESS);

            square_info.push_back(square);

            cv::circle(preview, square.center, 2, cv::Scalar(0, 0, 255), -1);
            
            if (columns_divisible == false && j == cols - 1) {
                squareOfGrid square;

                square.topLeft = cv::Point(x + cellLength  + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                (y - cellWidth) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                square.bottomRight = cv::Point((FIELD_LENGTH  + BORDER_STRIP_WIDTH) * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

                square.type = 1;

                cv::rectangle(preview, cv::Point(x + cellLength  + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                (y - cellWidth) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), 
                cv::Point((FIELD_LENGTH  + BORDER_STRIP_WIDTH) * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), GRID_COLOR, GRID_THICKNESS);

                if (remaining_length < cellLength / 2) {
                    square.center = cv::Point((FIELD_LENGTH  + BORDER_STRIP_WIDTH) * SCALE, 
                    (y - cellWidth / 2)+ (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                }
                else {
                    square.center = cv::Point(x + cellLength * 1.5 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                    (y - cellWidth / 2)+ (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                }
                //cout << " baghi mande " << int((FIELD_LENGTH / 2) * SCALE) % MOVE_BLOCK_LENGTH << endl;
                //cout << " tool " << cellLength / 2 << endl;
                square_info.push_back(square);
                cv::circle(preview, square.center, 2, cv::Scalar(0, 0, 255), -1);

                //cout << "remaining length " << remaining_length << endl;
                //cout << "cell length " << cellLength / 2 << endl;
            }
            
        }
        
        if (rows_divisible == false && i == rows) {
            //cout << 1 << endl;
            for (int j = 0; j < cols; j++) {
                int x = j * cellLength;

                squareOfGrid square;

                square.topLeft = cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

                square.bottomRight = cv::Point(x + cellLength + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                (FIELD_WIDTH + BORDER_STRIP_WIDTH) * SCALE);

                square.type = 1;

                if (remaining_width < cellWidth / 2) {
                    square.center = cv::Point(x + cellLength / 2 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                    (FIELD_WIDTH + BORDER_STRIP_WIDTH) * SCALE);
                }
                else {
                    //cout << "are" << endl;
                    square.center = cv::Point(x + cellLength / 2 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                    (y + cellWidth / 2) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                }

                //cout << "remaining_width " << remaining_width << endl;
                //cout << "cellWidth / 2 "<< cellWidth / 2 << endl;

                square_info.push_back(square);

                cv::rectangle(preview, cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), 
                cv::Point(x + cellLength + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                (FIELD_WIDTH + BORDER_STRIP_WIDTH) * SCALE), GRID_COLOR, GRID_THICKNESS);
            
                cv::circle(preview, square.center, 2, cv::Scalar(0, 0, 255), -1);
            
            if (columns_divisible == false && j == cols - 1){
                //cout << 2 << endl;
                squareOfGrid square;

                square.topLeft = cv::Point(x + cellLength  + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE),

                square.bottomRight = cv::Point((FIELD_LENGTH + BORDER_STRIP_WIDTH) * SCALE, 
                (FIELD_WIDTH + BORDER_STRIP_WIDTH) * SCALE);

                square.type = 1;
                if (remaining_length < cellLength / 2 && remaining_width < cellWidth / 2) {
                    //cout << 1 << endl;
                    square.center = cv::Point((FIELD_LENGTH + BORDER_STRIP_WIDTH) * SCALE, 
                    (FIELD_WIDTH + BORDER_STRIP_WIDTH) * SCALE);
                }
                else if (remaining_length >= cellLength / 2 && remaining_width < cellWidth / 2) {
                    //cout << 2 << endl;
                    square.center = cv::Point(x + cellLength * 1.5 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                    (FIELD_WIDTH + BORDER_STRIP_WIDTH) * SCALE);
                }
                else if (remaining_length >= cellLength / 2 && remaining_width >= cellWidth / 2) {
                    //cout << 3 << endl;
                    square.center = cv::Point(x + cellLength * 1.5 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                    (y + cellWidth / 2) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                }
                else if (remaining_length < cellLength / 2 && remaining_width >= cellWidth / 2) {
                    //cout << 4 << endl;
                    square.center = cv::Point((FIELD_LENGTH + BORDER_STRIP_WIDTH) * SCALE, 
                    (y + cellWidth / 2) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                }

                square_info.push_back(square);

                cv::rectangle(preview, cv::Point(x + cellLength  + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), 
                cv::Point((FIELD_LENGTH + BORDER_STRIP_WIDTH) * SCALE, 
                (FIELD_WIDTH + BORDER_STRIP_WIDTH) * SCALE), GRID_COLOR, GRID_THICKNESS);

                cv::circle(preview, square.center, 2, cv::Scalar(0, 0, 255), -1);
                }
            }
            
        }
    //cout << i << endl;
    }
    /*
    for (const auto& element : square_info) {
        cout << element.center << " ";
    }
    cout << endl << endl;
    */
    for (int i = 1; i < rows + 1; i++) {
        int y = i * -cellWidth;
        
        for (int j = 0; j < cols; j++) {
            int x = j * cellLength;
            
            squareOfGrid square;

            square.topLeft = cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
            y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

            square.bottomRight = cv::Point(x + cellLength + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
            (y + cellWidth) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

            square.center = cv::Point(x + cellLength / 2 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
            (y + cellWidth / 2)+ (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

            square.type = 0;

            cv::rectangle(preview, cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE,
            y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), 
            cv::Point(x + cellLength + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
            (y + cellWidth) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), GRID_COLOR, GRID_THICKNESS);

            square_info.push_back(square);

            cv::circle(preview, square.center, 2, cv::Scalar(0, 0, 255), -1);
            
            if (columns_divisible == false && j == cols - 1) {
                squareOfGrid square;

                square.topLeft = cv::Point(x + cellLength  + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

                square.bottomRight = cv::Point((FIELD_LENGTH  + BORDER_STRIP_WIDTH) * SCALE, 
                (y + cellWidth) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

                square.type = 1;

                cv::rectangle(preview, cv::Point(x + cellLength  + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), 
                cv::Point((FIELD_LENGTH  + BORDER_STRIP_WIDTH) * SCALE, 
                (y + cellWidth) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), GRID_COLOR, GRID_THICKNESS);

                if (remaining_length < cellLength / 2) {
                    square.center = cv::Point((FIELD_LENGTH  + BORDER_STRIP_WIDTH) * SCALE, 
                    (y + cellWidth / 2)+ (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                }
                else {
                    square.center = cv::Point(x + cellLength * 1.5 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                    (y + cellWidth / 2)+ (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                }
                //cout << " baghi mande " << int((FIELD_LENGTH / 2) * SCALE) % MOVE_BLOCK_LENGTH << endl;
                //cout << " tool " << cellLength / 2 << endl;
                square_info.push_back(square);
                cv::circle(preview, square.center, 2, cv::Scalar(0, 0, 255), -1);

                //cout << "remaining length " << remaining_length << endl;
                //cout << "cell length " << cellLength / 2 << endl;
            }
            
        }
        
        if (rows_divisible == false && i == rows) {
            //cout << 1 << endl;
            for (int j = 0; j < cols; j++) {
                int x = j * cellLength;
                
                squareOfGrid square;

                square.topLeft = cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                BORDER_STRIP_WIDTH * SCALE);

                square.bottomRight = cv::Point(x + cellLength + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

                square.type = 1;

                if (remaining_width < cellWidth / 2) {
                    square.center = cv::Point(x + cellLength / 2 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                    BORDER_STRIP_WIDTH * SCALE);
                }
                else {
                    //cout << "are" << endl;
                    square.center = cv::Point(x + cellLength / 2 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                    (y - cellWidth / 2) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                }

                //cout << "remaining_width " << remaining_width << endl;
                //cout << "cellWidth / 2 "<< cellWidth / 2 << endl;

                square_info.push_back(square);

                cv::rectangle(preview, cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                BORDER_STRIP_WIDTH * SCALE), 
                cv::Point(x + cellLength + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), GRID_COLOR, GRID_THICKNESS);
            
                cv::circle(preview, square.center, 2, cv::Scalar(0, 0, 255), -1);
                //cv::circle(preview, cv::Point(x + cellLength + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                //y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), 2, cv::Scalar(0, 0, 255), -1);
                //cout << y << endl;
            
            
            if (columns_divisible == false && j == cols - 1){
                //cout << 2 << endl;
                squareOfGrid square;

                square.topLeft = cv::Point(x + cellLength  + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                BORDER_STRIP_WIDTH * SCALE),

                square.bottomRight = cv::Point((FIELD_LENGTH + BORDER_STRIP_WIDTH) * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

                square.type = 1;
                if (remaining_length < cellLength / 2 && remaining_width < cellWidth / 2) {
                    square.center = cv::Point((FIELD_LENGTH + BORDER_STRIP_WIDTH) * SCALE, 
                    BORDER_STRIP_WIDTH * SCALE);
                }
                else if (remaining_length >= cellLength / 2 && remaining_width < cellWidth / 2) {
                    square.center = cv::Point(x + cellLength * 1.5 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                    BORDER_STRIP_WIDTH * SCALE);
                }
                else if (remaining_length >= cellLength / 2 && remaining_width >= cellWidth / 2) {
                    square.center = cv::Point(x + cellLength * 1.5 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                    (y - cellWidth / 2) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                }
                else if (remaining_length < cellLength / 2 && remaining_width >= cellWidth / 2) {
                    square.center = cv::Point((FIELD_LENGTH  + BORDER_STRIP_WIDTH) * SCALE, 
                    (y - cellWidth / 2) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                }

                square_info.push_back(square);

                cv::rectangle(preview, cv::Point(x + cellLength  + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                BORDER_STRIP_WIDTH * SCALE), 
                cv::Point((FIELD_LENGTH + BORDER_STRIP_WIDTH) * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), GRID_COLOR, GRID_THICKNESS);

                cv::circle(preview, square.center, 2, cv::Scalar(0, 0, 255), -1);
                }
            }
            
        }
    //cout << i << endl;
    }
    /*
    for (const auto& element : square_info) {
        cout << element.center << " ";
    }
    cout << endl << endl;
    */
    
    for (int i = 1; i < rows + 1; i++) {
        int y = i * cellWidth;
        
        for (int j = 1; j < cols + 1; j++) {
            int x = j * -cellLength;
            
            squareOfGrid square;

            square.topLeft = cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
            (y - cellWidth) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

            square.bottomRight = cv::Point(x + cellLength + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
            y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

            square.center = cv::Point(x + cellLength / 2 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
            (y - cellWidth / 2)+ (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

            square.type = 0;

            cv::rectangle(preview, cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE,
            (y - cellWidth) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), 
            cv::Point(x + cellLength + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
            y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), GRID_COLOR, GRID_THICKNESS);

            square_info.push_back(square);

            cv::circle(preview, square.center, 2, cv::Scalar(0, 0, 255), -1);
            
            if (columns_divisible == false && j == cols) {
                squareOfGrid square;

                square.topLeft = cv::Point(BORDER_STRIP_WIDTH * SCALE, 
                (y - cellWidth) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                square.bottomRight = cv::Point(x + (FIELD_LENGTH / 2  + BORDER_STRIP_WIDTH) * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

                square.type = 1;

                cv::rectangle(preview, cv::Point(BORDER_STRIP_WIDTH * SCALE,
                (y - cellWidth) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), 
                cv::Point(x + (FIELD_LENGTH / 2  + BORDER_STRIP_WIDTH) * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), GRID_COLOR, GRID_THICKNESS);

                if (remaining_length < cellLength / 2) {
                    square.center = cv::Point(BORDER_STRIP_WIDTH * SCALE, 
                    (y - cellWidth / 2)+ (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                }
                else {
                    square.center = cv::Point(x - cellLength / 2 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                    (y - cellWidth / 2)+ (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                }
                //cout << " baghi mande " << int((FIELD_LENGTH / 2) * SCALE) % MOVE_BLOCK_LENGTH << endl;
                //cout << " tool " << cellLength / 2 << endl;
                square_info.push_back(square);
                cv::circle(preview, square.center, 2, cv::Scalar(0, 0, 255), -1);

                //cout << "remaining length " << remaining_length << endl;
                //cout << "cell length " << cellLength / 2 << endl;
            }
            
        }
        
        if (rows_divisible == false && i == rows) {
            //cout << 1 << endl;
            for (int j = 1; j < cols + 1; j++) {
                int x = j * -cellLength;

                squareOfGrid square;

                square.topLeft = cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

                square.bottomRight = cv::Point(x + cellLength + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                (FIELD_WIDTH + BORDER_STRIP_WIDTH) * SCALE);

                square.type = 1;

                if (remaining_width < cellWidth / 2) {
                    square.center = cv::Point(x + cellLength / 2 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                    (FIELD_WIDTH + BORDER_STRIP_WIDTH) * SCALE);
                }
                else {
                    //cout << "are" << endl;
                    square.center = cv::Point(x + cellLength / 2 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                    (y + cellWidth / 2) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                }

                //cout << "remaining_width " << remaining_width << endl;
                //cout << "cellWidth / 2 "<< cellWidth / 2 << endl;

                square_info.push_back(square);

                cv::rectangle(preview, cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), 
                cv::Point(x + cellLength + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                (FIELD_WIDTH + BORDER_STRIP_WIDTH) * SCALE), GRID_COLOR, GRID_THICKNESS);
            
                cv::circle(preview, square.center, 2, cv::Scalar(0, 0, 255), -1);
            
            if (columns_divisible == false && j == cols){
                //cout << 2 << endl;
                squareOfGrid square;

                square.topLeft = cv::Point(BORDER_STRIP_WIDTH * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE),

                square.bottomRight = cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                (FIELD_WIDTH + BORDER_STRIP_WIDTH) * SCALE);

                square.type = 1;
                if (remaining_length < cellLength / 2 && remaining_width < cellWidth / 2) {
                    //cout << 1 << endl;
                    square.center = cv::Point(BORDER_STRIP_WIDTH * SCALE, 
                    (FIELD_WIDTH + BORDER_STRIP_WIDTH) * SCALE);
                }
                else if (remaining_length >= cellLength / 2 && remaining_width < cellWidth / 2) {
                    //cout << 2 << endl;
                    square.center = cv::Point(x - cellLength / 2 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                    (FIELD_WIDTH + BORDER_STRIP_WIDTH) * SCALE);
                }
                else if (remaining_length >= cellLength / 2 && remaining_width >= cellWidth / 2) {
                    //cout << 3 << endl;
                    square.center = cv::Point(x - cellLength / 2 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                    (y + cellWidth / 2) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                }
                else if (remaining_length < cellLength / 2 && remaining_width >= cellWidth / 2) {
                    //cout << 4 << endl;
                    square.center = cv::Point(BORDER_STRIP_WIDTH * SCALE, 
                    (y + cellWidth / 2) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                }

                square_info.push_back(square);

                cv::rectangle(preview, cv::Point(BORDER_STRIP_WIDTH * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), 
                cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                (FIELD_WIDTH + BORDER_STRIP_WIDTH) * SCALE), GRID_COLOR, GRID_THICKNESS);

                cv::circle(preview, square.center, 2, cv::Scalar(0, 0, 255), -1);
                }
            }
            
        }
    //cout << i << endl;
    }
    /*
    for (const auto& element : square_info) {
        cout << element.center << " ";
    }
    cout << endl << endl;
    */
    
    for (int i = 1; i < rows + 1; i++) {
        int y = i * -cellWidth;
        
        for (int j = 1; j < cols + 1; j++) {
            int x = j * -cellLength;
            
            squareOfGrid square;

            square.topLeft = cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
            y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

            square.bottomRight = cv::Point(x + cellLength + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
            (y + cellWidth) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

            square.center = cv::Point(x + cellLength / 2 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
            (y + cellWidth / 2)+ (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

            square.type = 0;

            cv::rectangle(preview, cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE,
            y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), 
            cv::Point(x + cellLength + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
            (y + cellWidth) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), GRID_COLOR, GRID_THICKNESS);

            square_info.push_back(square);

            cv::circle(preview, square.center, 2, cv::Scalar(0, 0, 255), -1);
            
            if (columns_divisible == false && j == cols) {
                squareOfGrid square;

                square.topLeft = cv::Point(BORDER_STRIP_WIDTH * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

                square.bottomRight = cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                (y + cellWidth) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

                square.type = 1;

                cv::rectangle(preview, cv::Point(BORDER_STRIP_WIDTH * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), 
                cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                (y + cellWidth) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), GRID_COLOR, GRID_THICKNESS);

                if (remaining_length < cellLength / 2) {
                    square.center = cv::Point(BORDER_STRIP_WIDTH * SCALE, 
                    (y + cellWidth / 2) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                }
                else {
                    square.center = cv::Point(x - cellLength / 2 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                    (y + cellWidth / 2) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                }
                //cout << " baghi mande " << int((FIELD_LENGTH / 2) * SCALE) % MOVE_BLOCK_LENGTH << endl;
                //cout << " tool " << cellLength / 2 << endl;
                square_info.push_back(square);
                cv::circle(preview, square.center, 2, cv::Scalar(0, 0, 255), -1);

                //cout << "remaining length " << remaining_length << endl;
                //cout << "cell length " << cellLength / 2 << endl;
            }
            
        }
        
        if (rows_divisible == false && i == rows) {
            //cout << 1 << endl;
            for (int j = 1; j < cols + 1; j++) {
                int x = j * -cellLength;
                
                squareOfGrid square;

                square.topLeft = cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                BORDER_STRIP_WIDTH * SCALE);

                square.bottomRight = cv::Point(x + cellLength + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

                square.type = 1;

                if (remaining_width < cellWidth / 2) {
                    square.center = cv::Point(x + cellLength / 2 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                    BORDER_STRIP_WIDTH * SCALE);
                }
                else {
                    //cout << "are" << endl;
                    square.center = cv::Point(x + cellLength / 2 + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                    (y - cellWidth / 2) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                }

                //cout << "remaining_width " << remaining_width << endl;
                //cout << "cellWidth / 2 "<< cellWidth / 2 << endl;

                square_info.push_back(square);

                cv::rectangle(preview, cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                BORDER_STRIP_WIDTH * SCALE), 
                cv::Point(x + cellLength + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), GRID_COLOR, GRID_THICKNESS);
            
                cv::circle(preview, square.center, 2, cv::Scalar(0, 0, 255), -1);
                //cv::circle(preview, cv::Point(x + cellLength + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                //y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), 2, cv::Scalar(0, 0, 255), -1);
                //cout << y << endl;
            
            
            if (columns_divisible == false && j == cols) {
                //cout << 2 << endl;
                squareOfGrid square;

                square.topLeft = cv::Point(BORDER_STRIP_WIDTH * SCALE, 
                BORDER_STRIP_WIDTH * SCALE),

                square.bottomRight = cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);

                square.type = 1;
                if (remaining_length < cellLength / 2 && remaining_width < cellWidth / 2) {
                    square.center = cv::Point(BORDER_STRIP_WIDTH * SCALE, 
                    BORDER_STRIP_WIDTH * SCALE);
                }
                else if (remaining_length >= cellLength / 2 && remaining_width < cellWidth / 2) {
                    square.center = cv::Point((x - cellLength / 2) + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                    BORDER_STRIP_WIDTH * SCALE);
                }
                else if (remaining_length >= cellLength / 2 && remaining_width >= cellWidth / 2) {
                    square.center = cv::Point((x - cellLength / 2) + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                    (y - cellWidth / 2) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                }
                else if (remaining_length < cellLength / 2 && remaining_width >= cellWidth / 2) {
                    square.center = cv::Point(BORDER_STRIP_WIDTH * SCALE, 
                    (y - cellWidth / 2) + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE);
                }

                square_info.push_back(square);

                cv::rectangle(preview, cv::Point(BORDER_STRIP_WIDTH * SCALE, 
                BORDER_STRIP_WIDTH * SCALE), 
                cv::Point(x + (FIELD_LENGTH / 2 + BORDER_STRIP_WIDTH) * SCALE, 
                y + (FIELD_WIDTH / 2 + BORDER_STRIP_WIDTH) * SCALE), GRID_COLOR, GRID_THICKNESS);

                cv::circle(preview, square.center, 2, cv::Scalar(0, 0, 255), -1);
                }
            }
            
        }
    //cout << i << endl;
    }
    /*
    for (const auto& element : square_info) {
        cout << element.center << " ";
    }
    cout << endl << endl;
    */

    grid_drawed = true;
    cout << square_info.size() << endl;
    //cv::circle(preview, cv::Point(130, 765), 2, cv::Scalar(255, 0, 0), -3);
    makePairPoints();
}

template <typename T>
vector<vector<T>> transpose(const vector<vector<T>>& matrix) {
    vector<vector<T>> result(matrix[0].size(), vector<T>(matrix.size()));
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            result[j][i] = matrix[i][j];
        }
    }
    return result;
}

// Custom comparator function to sort pairs based on both elements
bool pair_cmp(const pair<int, int>& a, const pair<int, int>& b) {
    // Compare first elements
    if (a.second != b.second) {
        return a.second < b.second;
    }
    // If first elements are equal, compare second elements
    return a.first < b.first;
}

void Grid::makePairPoints() {
    /*
    int start_index = 0;
    for (int i = 0; i < cell_number_width; i++) {
        for (int j =0; j < cell_number_length; j++) {
            point_location[i][j].first = square_info[start_index].center.x;
            point_location[i][j].second = square_info[start_index].center.y;
            //cout << square_info[start_index].center << " ";
            start_index += 1;
        }
        //cout << endl;
        //start_index += 1;
        //cout << endl;
        //cout << start_index << endl << endl;
    }
    //cout << start_index << endl;
    */
   /*
    for (int i = 0; i < cell_number_width; i++) {
        for (int j =0; j < cell_number_length; j++) {
            cout << "(" << point_location[i][j].first << ", " << point_location[i][j].second << ") ";
        }
    }
   */


    for (auto& square : square_info) {
        point_location.push_back(make_pair(square.center.x, square.center.y));
    }

    for(const auto& location : point_location) {
        cout << "(" << location.first << ", " << location.second << ") ";
    }

    cout << endl << endl;
    
    sort(point_location.begin(), point_location.end(), pair_cmp);

    point_location_2D.resize(cell_number_width, std::vector<std::pair<int, int>>(cell_number_length));

    for (int i = 0; i < cell_number_width; i++) {
        for (int j = 0; j < cell_number_length; j++) {
            // Calculate the index in the 1D vector corresponding to the element in the 2D vector
            int index = i * cell_number_length + j;
            // Copy the element from the 1D vector to the 2D vector
            point_location_2D[i][j] = point_location[index];
        }
    }

    for (int i = 0; i < cell_number_width; i++) {
        for (int j = 0; j < cell_number_length; j++) {
            cout << "(" << point_location_2D[i][j].first << ", " << point_location_2D[i][j].second << ") ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "row : " << point_location_2D.size();
    cout << "col : " << point_location_2D[0].size();

    cout << endl << endl;
    
    /*
    for(const auto& location : point_location) {
        cout << "(" << location.first << ", " << location.second << ") ";
    }
    */

    /*
    for (auto& innerVector : point_location) {
        sort(innerVector.begin(), innerVector.end());
    }
    // Step 2: Transpose the 2D vector
    auto transposed = transpose(point_location);

    // Step 3: Sort each inner vector (row-wise sorting)
    for (auto& innerVector : transposed) {
        sort(innerVector.begin(), innerVector.end());
    }

    // Step 4: Transpose the 2D vector back to its original orientation
    point_location = transpose(transposed);
    */
    
    
    
   /*
    for (int i = 0; i < cell_number_width; i++) {
        for (int j =0; j < cell_number_length; j++) {
            cout << "(" << point_location[i][j].first << ", " << point_location[i][j].second << ") ";
        }
    }
    */

    cout << endl << endl;
    /*
    for (int i = 0; i < cell_number_width; i++) {
        for (int j = 0; j < cell_number_length; j++) {
            point_status[i][j] = 1;
        }
    }
    */
    for (int i = 0; i < cell_number_width; i++) {
        for (int j = 0; j < cell_number_length; j++) {
            cout << point_status[i][j] << " ";
        }
        cout << endl;
    }


    cout << endl << endl;

    int i= 0;
    int j = 0;
    for (auto& location : point_location) {
        if (j == cell_number_length) {
            //cout << endl;
            j = 0;
            i++;
        }
        for (auto& square : square_info) {
            if (square.center.x == location.first && square.center.y == location.second) {
                //cout << square.type << " ";
                point_status[i][j] = square.type;
                j++;
                break;
            }
        }
    }
    
    for (int i = 0; i < cell_number_width; i++) {
        for (int j = 0; j < cell_number_length; j++) {
            cout << point_status[i][j] << " ";
        }
        cout << endl;
    }


    cout << endl << endl;

    cout << endl;
    //cout << "row :" << point_location.size() << endl;
    //cout<< "columns :" << point_location[0].size() << endl;
}

std::vector<std::vector<int>> Grid::returnPointStatus() {
    return point_status;
}

std::vector<std::vector<std::pair<int, int>>> Grid::returnPointLocation_2D() {
    return point_location_2D;
}

void Grid::showGrid(cv::Mat& preview) {
    while (true) {
        if (show_grid && !grid_drawed) {
            // Draw the grid on the image
            drawGrid(preview, grid_rows, grid_columns, grid_drawed);   
        }
/*
        if (show_point && !point_drawed) {
            // Draw the grid on the image
            drawPoint(preview, grid_rows, grid_columns, point_drawed);   
        }
*/
        cv::imshow("World", preview);

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
/*
void Grid::drawPoint(cv::Mat& preview, int rows, int cols, bool& point_drawed) {
    int point_x = move_block;//(FIELD_LENGTH * SCALE) / cols;
    int point_y = move_block; //(FIELD_WIDTH * SCALE) / rows;

    for (int i = 0; i < rows * 2; i++) {
        if (i % 2 == 0)
            continue;
        int y = i * point_y / 2;
        for (int j = 0; j < cols * 2; j++) {
            if (j % 2 == 0)
                continue;
            int x = j * point_x / 2;
            cv::Point center (x + BORDER_STRIP_WIDTH * SCALE, y + BORDER_STRIP_WIDTH * SCALE);
            cv::circle(preview, center, .5, cv::Scalar(0, 0, 255), -1);
        }
    }
    if (columns_divisible == false) 
        for (int i = 0; i < rows * 2; i++) {
            if (i % 2 == 0)
                continue;
            int y = i * move_block / 2;
            cv::Point center ((FIELD_LENGTH  + BORDER_STRIP_WIDTH) * SCALE, y + BORDER_STRIP_WIDTH * SCALE);
            cv::circle(preview, center, .8, cv::Scalar(0, 0, 255), -1);
        }
    if (rows_divisible == false) 
        for (int i = 0; i < cols * 2; i++) {
            if (i % 2 == 0)
                continue;
            int x = i * move_block / 2;
            cv::Point center (x + BORDER_STRIP_WIDTH * SCALE, (FIELD_WIDTH + BORDER_STRIP_WIDTH) * SCALE);
            cv::circle(preview, center, .8, cv::Scalar(0, 0, 255), -1);
        }
    point_drawed = true;
}
*/