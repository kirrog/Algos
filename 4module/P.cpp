#include <iostream>
#include <vector>

using namespace std;

struct Airport {
    bool checked = false;
    vector<int> airlines;
    vector<bool> ability;
};

void checkOutAirport(vector<Airport> &airports, int airportNum) {
    airports[airportNum].checked = true;
    for (int i = 0; i < airports.size(); ++i) {
        if (airports[airportNum].ability[i] && !(airports[i].checked)) {
            checkOutAirport(airports, i);
        }
    }
}

void checkInAirport(vector<Airport> &airports, int airportNum) {
    airports[airportNum].checked = true;
    for (int i = 0; i < airports.size(); ++i) {
        if (airports[i].ability[airportNum] && !(airports[i].checked)) {
            checkInAirport(airports, i);
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
    int left = 0;
    int right = INT32_MAX;

    for (int i = 0; i < size; ++i) {
        airports[i].airlines.resize(size);
        airports[i].ability.resize(size);
        for (int j = 0; j < size; ++j) {
            int airDist;
            cin >> airDist;
            airports[i].airlines[j] = airDist;
        }
    }

    while (left < right) {
        int middle = (left + right) / 2;
        setAbility(airports, middle);
        uncheckAirports(airports);
        checkInAirport(airports, 0);
        bool checked = true;
        for (int i = 0; (i < size) && checked; ++i) {
            checked &= airports[i].checked;
        }
        if (checked) {
            uncheckAirports(airports);
            checkOutAirport(airports, 0);
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