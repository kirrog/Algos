#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Coordinate {

public:
    Coordinate *north = nullptr;
    Coordinate *east = nullptr;
    Coordinate *south = nullptr;
    Coordinate *west = nullptr;
    int type = 0;
    int distance = INT32_MAX;
    bool checked = false;
    bool slice = false;
    int from = -1;

    void bind(Coordinate *binder, int pos) {
        switch (pos) {
            case 0: {
                north = binder;
                binder->south = this;
                break;
            }
            case 1: {
                east = binder;
                binder->west = this;
                break;
            }
            case 2: {
                south = binder;
                binder->north = this;
                break;
            }
            case 3: {
                west = binder;
                binder->east = this;
                break;
            }
            default:
                break;
        }
    }
};

int compareCoordinate(Coordinate *l, Coordinate *r) {
    if (l) {
        if (r) {
            return l->distance > r->distance;
        } else {
            return false;
        }
    } else {
        return true;
    }

}

void addToMap(vector<Coordinate *> &nodesSet, Coordinate *coordinate, int pos, int from) {
    if (coordinate) {
        if (coordinate->type) {
            if (!coordinate->slice) {
                coordinate->slice = true;
                coordinate->distance = pos + coordinate->type;
                nodesSet.push_back(coordinate);
                push_heap(nodesSet.begin(), nodesSet.end(), compareCoordinate);
                coordinate->from = from;
            } else {
                if (pos + coordinate->type < coordinate->distance) {
                    coordinate->distance = pos + coordinate->type;
                    coordinate->from = from;
                    make_heap(nodesSet.begin(), nodesSet.end(), compareCoordinate);
                }
            }
        }
    }
}

void printMap(vector<Coordinate> &maps, int width, int height) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            printf("%3d", maps[width * i + j].distance);
        }
        printf("\n");
    }
}


int main() {

    int height, width, startX, startY, endX, endY;
    cin >> height;
    cin >> width;
    cin >> startY;
    cin >> startX;
    cin >> endY;
    cin >> endX;
    vector<Coordinate> mapCoord(width * height);

    Coordinate *start = nullptr;
    Coordinate *end = nullptr;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (j == startX - 1 && i == startY - 1) {
                start = &mapCoord[width * i + j];
            }
            if (j == endX - 1 && i == endY - 1) {
                end = &mapCoord[width * i + j];
            }
            if (i < height - 1) {
                mapCoord[(width * i + j)].bind(&mapCoord[(width * (i + 1) + j)], 2);
            }
            if (j < width - 1) {
                mapCoord[(width * i + j)].bind(&mapCoord[(width * i + j + 1)], 1);
            }
            char type;
            cin >> type;
            switch (type) {
                case '.': {
                    mapCoord[(width * i + j)].type = 1;
                    break;
                }
                case 'W': {
                    mapCoord[(width * i + j)].type = 2;
                    break;
                }
                case '#': {
                    mapCoord[(width * i + j)].type = 0;
                    break;
                }
                default:
                    break;
            }
        }
    }

    vector<Coordinate *> nodeSet;
    nodeSet.reserve(width * height);

    start->distance = 0;
    start->slice = true;

    nodeSet.push_back(start);

    for (int k = 0; k < width * height && !end->checked && nodeSet[0]; ++k) {
        //        printMap(mapCoord, width, height)
        //        printf("\n\n");
        Coordinate *next = nodeSet[0];
        pop_heap(nodeSet.begin(), nodeSet.end(), compareCoordinate);
        nodeSet.pop_back();
        next->checked = true;

        addToMap(nodeSet, next->north, next->distance, 2);
        addToMap(nodeSet, next->east, next->distance, 3);
        addToMap(nodeSet, next->south, next->distance, 0);
        addToMap(nodeSet, next->west, next->distance, 1);
    }


    int size = end->distance;
    if (size == INT32_MAX) {
        printf("%d", -1);
        return 0;
    }
    printf("%d\n", size);
    vector<char> way(size);
    Coordinate *iter = end;
    int shift = 0;
    for (int i = size - 1; i >= 0; i--) {
        int ord = iter->from;
        if (iter->type == 2) {
            shift++;
        }
        switch (ord) {
            case 0: {
                way[i] = 'S';
                iter = iter->north;
                break;
            }
            case 1: {
                way[i] = 'W';
                iter = iter->east;
                break;
            }
            case 2: {
                way[i] = 'N';
                iter = iter->south;
                break;
            }
            case 3: {
                way[i] = 'E';
                iter = iter->west;
                break;
            }
            default: {
                break;
            }
        }
    }

    for (int i = shift; i < size; ++i) {
        printf("%c", way[i]);
    }


    return 0;
}
