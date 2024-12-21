#include <iostream>
#include <fstream>
using namespace std;

class TrainClass
{
    int classId;
    char className[30];

public:
    // Getter Methods
    int getClassId() const { return classId; }
    const char* getClassName() const { return className; }

    // Setter Methods
    void setClassId(int cId)
    {
        classId = cId;
    }

    void setClassName(const char* cName)
    {
        strcpy(className, cName);
    }

    // Insert and display functionalities
    void insert(int id)
    {
        setClassId(id);

        cout << "Enter class name: ";
        char temp[40];
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get(temp, 40);
        setClassName(temp);
    }

    void display()
    {
        cout << "\nClass Id: " << classId;
        cout << "\nClass Name: " << className << endl << endl;
    }

    // Serialization and Deserialization Methods
    void saveToStream(ofstream& stream)
    {
        stream.write(reinterpret_cast<const char*>(&classId), sizeof(classId));
        stream.write(reinterpret_cast<const char*>(&className), sizeof(className));
    }

    void loadFromStream(ifstream& stream)
    {
        stream.read(reinterpret_cast<char*>(&classId), sizeof(classId));
        stream.read(reinterpret_cast<char*>(&className), sizeof(className));
    }
};
