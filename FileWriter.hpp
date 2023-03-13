#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class FileWriter
{
public:
    static void writeToFile(string fileName,string outputString);
};

static void writeToFile(string fileName,string outputString){
    //string fileName: It is the name of the file we want to write our second var which is outputString
    //string outputString: It is the string we want to write into our file named fileName
    //This function creates and writes to a file.
    
    fstream myFile;
    myFile.open(fileName,ios::out);
    myFile << outputString << endl;
    if(myFile.fail())
    {
        cout<<"Failed to write\n";
    }
    myFile.close();
}
