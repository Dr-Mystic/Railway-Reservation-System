#include <iostream>
#include <fstream>
#include "validation.h"
using namespace std;

class TrainCapacity
{
    int trainId;
    int classId;
    int totalSeats;
    int rate;

public:
    // Getter Methods
    int getTrainId() const { return trainId; }
    int getClassId() const { return classId; }
    int getTotalSeats() const { return totalSeats; }
    int getRate() const { return rate; }

    // Setter Methods
    void setTrainId(int tId)
    {
        trainId = tId;
    }

    void setClassId(int cId)
    {
        classId = cId;
    }

    void setTotalSeats(int seats)
    {
        totalSeats = seats;
    }

    void setRate(int price)
    {
        rate = price;
    }

    // Insert and display interface
    void insert(int tid, int cid)
    {
        setTrainId(tid);
        setClassId(cid);

        while (true)
        {
            cout << "Enter total seats: ";
            int seats;
            cin >> seats;

            if (cin.fail() || seats < 1)
            {
                inputValidation();
                cout << "Please enter a positive value.\n\n";
                continue;
            }
            setTotalSeats(seats);
            break;
        }


        while (true)
        {
            cout << "Enter rate: ";
            int rate;
            cin >> rate;

            if (cin.fail() || rate < 1)
            {
                inputValidation();
                cout << "Please enter a positive value.\n\n";
                continue;
            }
            setRate(rate);
            break;
        }
    }

    void display()
    {
        cout << "\nTrain Id: " << trainId;
        cout << "\nClass ID: " << classId;
        cout << "\nTotal Seats: " << totalSeats;
        cout << "\nRate: " << rate << endl << endl;
    }

    // Serialization and Deserialization Methods
    void saveToStream(ofstream& stream)
    {
        stream.write(reinterpret_cast<const char*>(&trainId), sizeof(trainId));
        stream.write(reinterpret_cast<const char*>(&classId), sizeof(classId));
        stream.write(reinterpret_cast<const char*>(&totalSeats), sizeof(totalSeats));
        stream.write(reinterpret_cast<const char*>(&rate), sizeof(rate));
    }

    void loadFromStream(ifstream& stream)
    {
        stream.read(reinterpret_cast<char*>(&trainId), sizeof(trainId));
        stream.read(reinterpret_cast<char*>(&classId), sizeof(classId));
        stream.read(reinterpret_cast<char*>(&totalSeats), sizeof(totalSeats));
        stream.read(reinterpret_cast<char*>(&rate), sizeof(rate));
    }
};
