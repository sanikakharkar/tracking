#ifndef CSVREADER_HPP
#define CSVREADER_HPP

#include <fstream>
#include <iostream>
#include "DataReader.hpp"

// A file reader that reads LIDAR scan data from a CSV file.
class CSVReader : public DataReader
{
public:
    ~CSVReader() override;
   
    std::vector<LidarScan> const& extractData(std::string const& filename) override;

protected:
    std::vector<LidarScan> lidarScans_;

};

#endif /* CSVREADER_HPP */

