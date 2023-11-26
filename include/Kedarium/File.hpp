#ifndef KDR_FILE_HPP
#define KDR_FILE_HPP

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

namespace kdr
{
  namespace file
  {
    /**
     * Reads the contents of a file and returns it as a string.
     *
     * @param path The path to the file to be read.
     * @return A string containing the contents of the file.
     */
    const std::string getContents(const std::string& path);
  }
}

#endif // KDR_FILE_HPP
