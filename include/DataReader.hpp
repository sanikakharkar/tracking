#ifndef DATAREADER_HPP
#define DATAREADER_HPP

#include <vector>
#include <string>
#include "LidarScan.hpp"

class DataReader
{
public:
    virtual ~DataReader() = default;

    virtual std::vector<LidarScan> const& extractData(std::string const& filename) = 0;
};


#endif /* DATAREADER_HPP */
