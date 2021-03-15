#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "include/CSVReader.hpp"
#include "include/Tracker.hpp"

int main(int argc, char** argv)
{
    std::fstream datafile;

    if (argc < 2)
    {
        std::cerr << "Invalid arguments. Try -h for help." << std::endl;
        exit(1);
    }

    std::string option(argv[1]);
    if (option.compare("-h") == 0 || option.compare("--help") == 0)
    {
        std::cerr << "Enter data file type followed by name. Supported types: " << std::endl;
        std::cerr << "-c, --csv <filename.csv>: CSV file " << std::endl;
        std::cerr << "-r, --rosbag <filename.bag>: Rosbag file [NOT IMPLEMENTED]" << std::endl;
        exit(0);
    }
    else 
    {
        if (argc != 3)
        {
            std::cerr << "Invalid arguments. Try -h for help." << std::endl;
            exit(1);
        }
        std::string filename(argv[2]);
        if (option.compare("-c") == 0 || option.compare("--csv") == 0)
        {
            datafile.open(filename);
            if (datafile.is_open())
            {
                CSVReader reader;   
                auto const& lidarScans = reader.extractData(filename);
                Tracker tracker;
                tracker.track(lidarScans);
                datafile.close();
            }
            else
            {
                std::cerr << "Enter a valid CSV file name." << std::endl;
                exit(1);
            }
        }
        else if (option.compare("-r") == 0 || option.compare("--rosbag") == 0)
        {
            std::cerr << "Rosbag option is not implemented. Please use the CSV option instead." << std::endl;
        }
        else
        {
            std::cerr << "Invalid arguments. Try -h for help." << std::endl;
            exit(1);
        } 
    }
    

    return 0;
}