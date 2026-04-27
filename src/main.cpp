#include <charconv>
#include <chrono>
#include <iostream>
#include <thread>

#include "SimManager.h"

static const int TOTAL_HOURS_SIM = 72;
static const int MINS_PER_HOUR = 60;
static const int TOTAL_MINS_SIM = 72 * MINS_PER_HOUR;

static const int DEFAULT_NUM_TRUCKS = 40;
static const int DEFAULT_NUM_STATIONS = 3;

bool parse_args(char* argv[], int &numTrucks, int &numStations)
{
    std::string_view stringView(argv[1]);
    std::from_chars_result result = std::from_chars(stringView.data(), stringView.data() + stringView.size(), numTrucks);
    if (result.ec == std::errc()) {
        std::cout << "Configured: " << numTrucks << " trucks.\n";
    } else {
        std::cout << "Failed to parse number of trucks!\n";
        return false;
    }

    stringView = (argv[2]);
    result = std::from_chars(stringView.data(), stringView.data() + stringView.size(), numStations);
    if (result.ec == std::errc()) {
        std::cout << "Configured: " << numStations << " unload stations.\n";
    } else {
        std::cout << "Failed to parse number of unload stations!\n";
        return false;
    }

    return true;
}

void print_help()
{
    std::cout << "Syntax:\n\t<executable>  <number_of_trucks> <number_of_unload_stations>\n";
    std::cout << "Default number of trucks: 40" << std::endl;
    std::cout << "Default number of unload stations: 3" << std::endl;
}

int main(int argc, char* argv[])
{
    int numTrucks = DEFAULT_NUM_TRUCKS;
    int numStations = DEFAULT_NUM_STATIONS;
    if (argc==1) {
        std::cout << "Simulation run with default arguments.\n";
    } else if (argc==3) {
        if (!parse_args(argv, numTrucks, numStations)) {
            print_help();
            return 0;
        }
    } else {
        print_help();
        return 0;
    }
    std::cout << "Number of trucks: " << numTrucks << ". Number of unload stations: " << numStations << "." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::shared_ptr<Coordinator> coordinator = std::make_shared<Coordinator>(numStations);
    SimManager simManager(numTrucks, coordinator);

    int currentMinute = 0;
    while (currentMinute<TOTAL_MINS_SIM) {
        currentMinute++;

        simManager.tick();
        if (!(currentMinute%MINS_PER_HOUR)) {
            simManager.print_statistics();
        }
    }
    simManager.print_metrics();

    return 0;
}