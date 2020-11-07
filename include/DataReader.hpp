#include <vector>
#include <string>
#include "lidarScan.hpp"

class DataReader
{
public:
    virtual ~DataReader() = default;

    virtual std::vector<lidarScan>& extractData(std::string const& filename) = 0;
};

