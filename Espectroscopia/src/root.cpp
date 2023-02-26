#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// #include "TH1F.h"
// #include "TGraph.h"
// #include "TMultiGraph.h"
// #include "TCanvas.h"
// #include "TApplication.h"
// #include "TRootCanvas.h"


using namespace std;

// function to read in values from excel into vectors
void ReadExcel(const string &filename, vector<vector<string>> &data)
{
    // open file
    ifstream file(filename);
    if (!file.is_open()) {
        fprintf(stderr, "**Failed to open file %s", filename.c_str());
        exit(0);
    }

    // read lines from the file
    string line;

    getline(file, line);
    cout << line << endl;

    while (getline(file, line))
    {
        // create a vector of strings for each row
        vector<string> row;

        // split line by comma separator
        string cell;
        size_t pos = 0;
        while ((pos = line.find(',')) != string::npos)
        {
            cell = line.substr(0, pos);
            row.push_back(cell);
            line.erase(0, pos + 1);
        }

        // add the last element to the row
        row.push_back(line);

        // add row to data vector
        data.push_back(row);
    }
}

int main ()
{
    // create vector to hold data
    vector<vector<string>> data;

    // call ReadExcel function
    ReadExcel("data/test.csv", data);

    // print out data
    for (auto row : data)
    {
        for (auto cell : row)
            cout << cell << " ";
        cout << endl;
    }

    return 0;
}