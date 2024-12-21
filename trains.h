#include <iostream>
#include <fstream>
using namespace std;

class Train
{
    int trainId;
    char trainName[50];
    char source[30];
    char destination[30];

public:
    // Getter Methods
    int getTrainId() const { return trainId; }
    const char* getTrainName() const { return trainName; }
    const char* getSource() const { return source; }
    const char* getDestination() const { return destination; }

    // Setter Methods
    void setTrainId(int tId)
    {
        trainId = tId;
    }

    void setTrainName(const char* cName)
    {
        strcpy(trainName, cName);
    }

    void setSource(const char* src)
    {
        strcpy(source, src);
    }

    void setDestination(const char* dest)
    {
        strcpy(destination, dest);
    }

    // Insert and Display Interface
    void insert(int id)
    {
        setTrainId(id);

        cout << "Enter train name: ";
        char temp[40];
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get(temp, 40);
        setTrainName(temp);

        cout << "Enter source: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get(temp, 40);
        setSource(temp);

        cout << "Enter destination: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get(temp, 40);
        setDestination(temp);
    }

    void display()
    {
        cout << "\nTrain Id: " << trainId;
        cout << "\nTrain Name: " << trainName;
        cout << "\nSource: " << source;
        cout << "\nDestination: " << destination << endl << endl;
    }

    // Serialization and Deserialization Methods
    void saveToStream(ofstream& stream) 
    {
        stream.write(reinterpret_cast<const char*>(&trainId), sizeof(trainId));
        stream.write(reinterpret_cast<const char*>(&trainName), sizeof(trainName));
        stream.write(reinterpret_cast<const char*>(&source), sizeof(source));
        stream.write(reinterpret_cast<const char*>(&destination), sizeof(destination));
    }

    void loadFromStream(ifstream& stream) 
    {
        stream.read(reinterpret_cast<char*>(&trainId), sizeof(trainId));
        stream.read(reinterpret_cast<char*>(&trainName), sizeof(trainName));
        stream.read(reinterpret_cast<char*>(&source), sizeof(source));
        stream.read(reinterpret_cast<char*>(&destination), sizeof(destination));
    }
};
