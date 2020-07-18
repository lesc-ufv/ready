#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
#include<map>
#include <queue>

class PathFinder {
public:
    static bool
    pathFinder(int start, int target, std::map<int, std::vector<int>> graph, std::vector<std::vector<int>> &paths);
};


#endif //PATHFINDER_H
