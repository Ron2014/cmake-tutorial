// A simple program that builds a sqrt table
#include <cmath>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
  // make sure we have enough arguments
  if (argc < 2) {
    return 1;
  }

  // open out stream file
  std::ofstream fout(argv[1], std::ios_base::out);
  const bool fileOpen = fout.is_open();

  if (fileOpen) {

    /**
     * // Table.h
     * double sqrtTable[] = {sqrt(0), sqrt(1), sqrt(2), ..., sqrt(9), 0};
     */

    fout << "double sqrtTable[] = {" << std::endl;
    for (int i = 0; i < 10; ++i) {
      fout << sqrt(static_cast<double>(i)) << "," << std::endl;
    }
    // close the table with a zero
    fout << "0};" << std::endl;
    fout.close();
  }

  return fileOpen ? 0 : 1; // return 0 if wrote the file
}
