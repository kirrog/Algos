#include <iostream>
#include <vector>

using namespace std;

struct Airport {
    bool checked = false;
    vector<int> airlines;
    vector<bool> ability;
};

void checkOutAirport(vector<Airport> &airports, int airportNum, int maxDist) {
    airports[airportNum].checked = true;
    for (int i = 0; i < airports.size(); ++i) {
        int airDist = airports[airportNum].airlines[i];
        if (airDist && airDist <= maxDist) {
            if (!airports[i].checked) {
                checkOutAirport(airports, i, maxDist);
            }
        }
    }
}

void checkInAirport(vector<Airport> &airports, int airportNum, int maxDist) {
    airports[airportNum].checked = true;
    for (int i = 0; i < airports.size(); ++i) {
        int airportDistance = airports[i].airlines[airportNum];
        if (airportDistance && airportDistance <= maxDist) {
            if (!airports[i].checked) {
                checkInAirport(airports, i, maxDist);
            }
        }
    }
}

void uncheckAirports(vector<Airport> &airports) {
    for (int i = 0; i < airports.size(); ++i) {
        airports[i].checked = false;
    }
}

void setAbility(vector<Airport> &airports, int maxDist) {
    for (int i = 0; i < airports.size(); ++i) {
        for (int j = 0; j < airports.size(); ++j) {
            airports[i].ability[j] = airports[i].airlines[j] <= maxDist;
        }
    }
}

int main() {

    int size;
    cin >> size;
    if (size == 1) {
        cout << 0;
        return 0;
    }
    vector<Airport> airports(size);
    int left = INT32_MAX;
    int right = 0;

    for (int i = 0; i < size; ++i) {
        airports[i].airlines.resize(size);
        airports[i].ability.resize(size);
        for (int j = 0; j < size; ++j) {
            int airportDistance;
            cin >> airportDistance;
            if (airportDistance > right) {
                right = airportDistance;
            }
            if (airportDistance && airportDistance < left) {
                left = airportDistance;
            }
            airports[i].airlines[j] = airportDistance;
        }
    }

    while (left < right) {
        int middle = (left + right) / 2;
        uncheckAirports(airports);
        checkInAirport(airports, 0, middle);
        bool checked = true;
        for (int i = 0; (i < size) && checked; ++i) {
            checked &= airports[i].checked;
        }
        if (checked) {
            uncheckAirports(airports);
            checkOutAirport(airports, 0, middle);
            for (int i = 0; (i < size) && checked; ++i) {
                checked &= airports[i].checked;
            }
        }
        if (checked) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }

    cout << left;

    return 0;
}