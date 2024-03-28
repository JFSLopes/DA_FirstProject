#ifndef DA_FIRSTPROJECT_FILEPARSE_H
#define DA_FIRSTPROJECT_FILEPARSE_H

class Graph;
class City;

#include "Graph.h"
#include <fstream>

/**
 * @namespace FileParse
 * @brief Contains the functions used for parsing the files
 */
namespace FileParse{
    /**
     * @brief Responsible for reading and parsing all files
     *
     * @param g Pointer to the graph where the information will be stored
     * @param cities Name of the cities file
     * @param pipes Name of the pipes file
     * @param reservoirs Name of the reservoir file
     * @param stations Name of the stations file
     * @param path Name of the path being used
     * @return True if was able to open all files, false otherwise
     */
    bool readFiles(Graph* g, std::string& cities, std::string& pipes, std::string& reservoirs, std::string& stations, std::string& path);
    /**
     * @bried Reads amd parses the data from the cities file
     *
     * @param g Graph being filed with the information
     * @param in File being read
     */
    void readCities(Graph* g, std::ifstream& in);
    /**
     * @bried Reads and parses the data from the pipes file
     *
     * @param g Graph being filed with the information
     * @param in File being read
     */
    void readPipes(Graph* g, std::ifstream& in);
    /**
     * @bried Reads and parses the data from the reservoir file
     *
     * @param g Graph being filed with the information
     * @param in File being read
     */
    void readReservoirs(Graph* g, std::ifstream& in);
    /**
     * @bried Reads and parses the data from the stations file
     *
     * @param g Graph being filed with the information
     * @param in File being read
     */
    void readStations(Graph* g, std::ifstream& in);
}

#endif
