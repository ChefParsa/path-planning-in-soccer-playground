# include "../include/soccerPlayground_v2.hpp"
# include "../include/robot_img.hpp"
# include "../include/grid.hpp"
# include "../include/a_star.hpp"
# include <iostream>
using namespace std;

int main() {
    SoccerPlayground playground;
    cv::Mat tmp = playground.getPlayground();
    //RobotImage robot_img;
    //robot_img.copyToPlayground(tmp);
    Grid grid(tmp);
    grid.showGrid(tmp);
    std::vector<std::vector<int>> pointStatus = grid.returnPointStatus();
    std::vector<std::vector<std::pair<int, int>>> pointLocation = grid.returnPointLocation_2D();
    /*
    for (auto& innervec: pointStatus) {
        for (auto& element : innervec) {
            cout << element << " ";
        }
        cout << endl;
    }
    */
    //playground.showPlayground();
    //RobotImage image;
    // Source is the left-most bottom-most corner
	Pair src = make_pair(8, 6);

	// Destination is the left-most top-most corner
	Pair dest = make_pair(1, 1);

    Astar pathPlaning(pointStatus, src, dest);

	pathPlaning.aStarSearch(tmp);

    pathPlaning.drawPath(tmp, pointLocation);

    return 0;
}