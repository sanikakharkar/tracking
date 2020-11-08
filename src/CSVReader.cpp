
#include "../include/CSVReader.hpp"

CSVReader::~CSVReader()
{
    lidarScans_.clear();
}

std::vector<LidarScan> const& CSVReader::extractData(std::string const& filename) 
{
    std::ifstream file(filename);
    std::string line;
    while(std::getline(file, line))
    {
        LidarScan scan;
        // Store timestamp
        auto pos = line.find(" ");
        scan.timestamp = std::stod(line.substr(0, pos));
        line = line.substr(pos+1);

        // Skip angles
        pos = line.find(" ");
        line = line.substr(pos+1);
        pos = line.find(" ");
        line = line.substr(pos+1);

        // Store ranges
        while(pos != std::string::npos)
        {
            pos = line.find(" ");
            scan.ranges.push_back(std::stod(line.substr(0, pos)));
            line = line.substr(pos+1);
        }

        lidarScans_.push_back(scan);
    }
    return lidarScans_;
}
