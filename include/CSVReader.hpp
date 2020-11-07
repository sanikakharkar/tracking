#include <fstream>
#include <iostream>
#include "DataReader.hpp"

class CSVReader : public DataReader
{
public:
    ~CSVReader() override
    {}
   
    std::vector<lidarScan>& extractData(std::string const& filename) override;

protected:
    std::vector<lidarScan> lidarScans;

};

