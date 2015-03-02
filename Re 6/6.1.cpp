#include <iostream>
#include <fstream>
#include "json-c"

using namespace std;
struct wordItem{

    string word;

    int count;

};



int main(int argc, char* argv[])

{

    char * fileName;        // stores the file we will be opening
    ifstream inStream;      // stream for reading in file
    wordItem *arr;          // array for storing words
    wordItem *arr2;         // used for dynamically doubling array size
    int timesDoubled = 0;   // stores the times we double the array
    int arrLoc = 0;         // stores the location of the last element in the arr
    int arrCapacity = 10;   // stores the capacity of the array
    // open the file
    fileName = argv[1];
    inStream.open(fileName);
    // throw an error if we couldn't open the file
    if (!inStream)
    {
        cout << "Error: Could not open file for reading" << endl;
        return 0;
    }
    arr = new wordItem[arrCapacity]; // declare our initial array
    string word;                     // stores each word we read in
    wordItem tmp;                    // stores our word item temporarily
    bool wordFound;                  // flag for whether we have found the word
    // loop until the end of the file
    while (!inStream.eof())
    {
        wordFound = false;
        // read in a word
        inStream >> word;
            // check if the word has already been found
            for (int i = 0; i < arrLoc; i++)
            {
                if (word==arr[i].word)
                {
                    wordFound=true;
                    arr[i].count++;
                    break;
                }
            }
            tmp.word = word;
            tmp.count = 1;
            if (arrLoc < arrCapacity)
            {
                 if(!wordFound)
                 {
                    arr[arrLoc++] = tmp;
                 }
            }
            else
           {
                arrCapacity*=2;
                // allocate new array
                arr2 = new wordItem[arrCapacity];
                // copy the original array in
                for (int i = 0; i < arrCapacity/2; i++)
                {
                       arr2[i] = arr[i];
                }
                // free the memory associated with arr
                delete[] arr;
                // make arr point to the new memory we just allocated
                arr = arr2;
                // increment our double count
                timesDoubled++;
                if(!wordFound) {
                          arr[arrLoc++] = tmp;
                }
               }
      }
    // close the file
    inStream.close();
    for (int i = 0; i < arrLoc; i++)
    {
        cout << arr[i].count << " - " << arr[i].word << endl;
    }
    cout << "#" << endl;
    cout << "Array doubled: "<<timesDoubled << endl;
}