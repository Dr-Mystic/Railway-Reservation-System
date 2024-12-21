#include <fstream>
using namespace std;

// Functions for File Handling
template<typename S>
bool saveArrayToFile(const char* filename, S* arrayName, int counter) 
{
    ofstream file(filename, ios::binary | ios::trunc);

    if (!file.is_open()) 
        return false;

    for (int i = 0; i < counter; ++i)
        arrayName[i].saveToStream(file);

    file.close();
    return true;
}
bool saveArraySizeToFile(int& trains, int& classes, int& capacities, int& reservations)
{
    ofstream outFile("data.bin", ios::binary | ios::trunc);

    if (!outFile)
        return false;

    outFile.write(reinterpret_cast<char*>(&trains), sizeof(trains));
    outFile.write(reinterpret_cast<char*>(&classes), sizeof(classes));
    outFile.write(reinterpret_cast<char*>(&capacities), sizeof(capacities));
    outFile.write(reinterpret_cast<char*>(&reservations), sizeof(reservations));

    outFile.close();
    return true;
}
bool saveCounterToFile(int trainCounter, int classCounter, int reservationCounter, int capacityCounter) 
{
    ofstream file("counter.bin", ios::binary | ios::trunc);

    if (!file.is_open()) 
        return false;

    file.write(reinterpret_cast<char*>(&trainCounter), sizeof(int));
    file.write(reinterpret_cast<char*>(&classCounter), sizeof(int));
    file.write(reinterpret_cast<char*>(&reservationCounter), sizeof(int));
    file.write(reinterpret_cast<char*>(&capacityCounter), sizeof(int));

    file.close();
    return true;
}
template<typename L>
bool loadArrayFromFile(const char* filename, L*& arrayName, int& counter) 
{
    ifstream file(filename, ios::binary | ios::ate);

    if (!file.is_open()) 
        return false;

    streampos size = file.tellg();
    file.seekg(0, ios::beg);

    int elements = size / sizeof(L);

    arrayName = new L[elements];

    for (int i = 0; i < elements; ++i)
        arrayName[i].loadFromStream(file);

    counter = elements;

    file.close();
    return true;
}
bool loadArraySizeFromFile(int& trains, int& classes, int& capacities, int& reservations)
{
    ifstream inFile("data.bin", ios::binary);

    if (!inFile)
        return false;

    inFile.read(reinterpret_cast<char*>(&trains), sizeof(trains));
    inFile.read(reinterpret_cast<char*>(&classes), sizeof(classes));
    inFile.read(reinterpret_cast<char*>(&capacities), sizeof(capacities));
    inFile.read(reinterpret_cast<char*>(&reservations), sizeof(reservations));
  
    inFile.close();
    return true;
}
bool loadCounterFromFile(int& trainCounter, int& classCounter, int& reservationCounter, int& capacityCounter) 
{
    ifstream file("counter.bin", ios::binary);

    if (!file.is_open())
        return false;

    file.read(reinterpret_cast<char*>(&trainCounter), sizeof(int));
    file.read(reinterpret_cast<char*>(&classCounter), sizeof(int));
    file.read(reinterpret_cast<char*>(&reservationCounter), sizeof(int));
    file.read(reinterpret_cast<char*>(&capacityCounter), sizeof(int));

    file.close();
    return true;
}
