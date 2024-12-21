#include <iostream>
#include <fstream>
using namespace std;

class Reservation
{
    int trainId;
    int classId;
    int ticketNo;
    char date[11];
    char cnic[15];
    char passengerName[50];

public:
    // Getter Methods
    int getTrainId() const { return trainId; }
    int getClassId() const { return classId; }
    int getTicketNo() const { return ticketNo; }
    const char* getDate() const { return date; }
    const char* getCNIC() const { return cnic; }
    const char* getPassengerName() const { return passengerName; }

    // Setter Methods
    void setTrainId(int tId)
    {
        trainId = tId;
    }

    void setClassId(int cId)
    {
        classId = cId;
    }

    void setTicketNo(int tNo)
    {
        ticketNo = tNo;;
    }

    void setDate(const char* day)
    {
        strcpy(date, day);
    }

    void setCNIC(const char* nic)
    {
        strcpy(cnic, nic);
    }

    void setPassengerName(const char* name)
    {
        strcpy(passengerName, name);
    }

    // Insert and display interface
    void insert(int tid, int cid, int previousTicket, const char* date)
    {
        setTrainId(tid);
        setClassId(cid);
        setTicketNo(previousTicket + 1);
        setDate(date);

        char temp[50];
        cout << "Enter CNIC: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get(temp, 50);
        setCNIC(temp);

        cout << "Enter passenger name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get(temp, 50);
        setPassengerName(temp);
    }

    void display()
    {
        cout << "Train Id: " << trainId;
        cout << "\nClass ID: " << classId;
        cout << "\nTicket Number: " << ticketNo;
        cout << "\nDate: " << date;
        cout << "\nCNIC: " << cnic;
        cout << "\nPassenger Name: " << passengerName << endl << endl;
    }

    // Serialization and Deserialization Methods
    void saveToStream(ofstream& stream)
    {
        stream.write(reinterpret_cast<const char*>(&trainId), sizeof(trainId));
        stream.write(reinterpret_cast<const char*>(&classId), sizeof(classId));
        stream.write(reinterpret_cast<const char*>(&ticketNo), sizeof(ticketNo));
        stream.write(reinterpret_cast<const char*>(&date), sizeof(date));
        stream.write(reinterpret_cast<const char*>(&cnic), sizeof(cnic));
        stream.write(reinterpret_cast<const char*>(&passengerName), sizeof(passengerName));
    }

    void loadFromStream(ifstream& stream)
    {
        stream.read(reinterpret_cast<char*>(&trainId), sizeof(trainId));
        stream.read(reinterpret_cast<char*>(&classId), sizeof(classId));
        stream.read(reinterpret_cast<char*>(&ticketNo), sizeof(ticketNo));
        stream.read(reinterpret_cast<char*>(&date), sizeof(date));
        stream.read(reinterpret_cast<char*>(&cnic), sizeof(cnic));
        stream.read(reinterpret_cast<char*>(&passengerName), sizeof(passengerName));
    }
};
