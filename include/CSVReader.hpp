#ifndef CSVREADER_HPP
#define CSVREADER_HPP

#include <fstream>
#include <iostream>
#include "DataReader.hpp"

class CSVReader : public DataReader
{
public:
    ~CSVReader() override;
   
    std::vector<LidarScan> const& extractData(std::string const& filename) override;

protected:
    std::vector<LidarScan> lidarScans_;

};

#endif /* CSVREADER_HPP */

