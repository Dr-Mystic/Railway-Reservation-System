#include <iostream>
#include <cstring>
#include <limits>
#include <ctime>
#include "file_handling.h"
#include "trains.h"
#include "train_classes.h"
#include "train_capacities.h"
#include "reservations.h"
using namespace std;

void trainOperations(Train*, TrainCapacity*, int, int, int, int, int);
void trainClassOperations(TrainClass*, TrainCapacity*, int, int, int, int, int);
void trainCapacityOperations(Train*, TrainCapacity*, TrainClass*, Reservation*, int, int, int, int, int);
void reservationOperations(Train*, TrainCapacity*, TrainClass*, Reservation*, int, int, int, int, int);

int main()
{
    system("clear");
    cout << "+-------------------------------------------------+\n";
    cout << "|      Welcome to Railway Reservation System      |\n";
    cout << "+-------------------------------------------------+\n";
    cout << "|  Please enter the following details for setup   |\n";
    cout << "+-------------------------------------------------+\n\n";

    Train* trains;
    TrainClass* trainClasses;
    TrainCapacity* trainCapacities;
    Reservation* reservations;

    int menuChoice, trainCounter, capacityCounter, classCounter, reservationCounter, noOfTrains, noOfClasses, noOfCapacities, noOfReservations;
    
    // Loading Data
    if (loadArrayFromFile("trains.bin", trains, trainCounter)&&loadArrayFromFile("trainClasses.bin", trainClasses, classCounter)&&loadArrayFromFile("reservations.bin", reservations, reservationCounter)&&loadArrayFromFile("trainCapacities.bin", trainCapacities, capacityCounter)&&loadCounterFromFile(trainCounter, classCounter, reservationCounter, capacityCounter)&&loadArraySizeFromFile(noOfTrains, noOfClasses, noOfCapacities, noOfReservations))
      cout << "Data loaded from saved files.\n\n";
    else
    {
        // Default Initialization
        noOfTrains = 4, noOfClasses = 4;
        noOfCapacities = noOfTrains * noOfClasses;
        noOfReservations = 100;

        trains = new Train[noOfTrains];
        trainClasses = new TrainClass[noOfClasses];
        trainCapacities = new TrainCapacity[noOfCapacities];
        reservations = new Reservation[noOfReservations];

        trainCounter = 0, capacityCounter = 0, classCounter = 0, reservationCounter = 0;
        cout << "Couldn't find saved data. Arrays initialzed with default values.\n\n";
    }

    wait();
    system("clear");

    while (true)
    {
        bool validation = false;
        // Main Menu
        do
        {
            cout << "+--------------------------------------+\n";
            cout << "|               Main Menu              |\n";
            cout << "+--------------------------------------+\n";
            cout << "| 1. Train                             |\n";
            cout << "| 2. Train Class Menu                  |\n";
            cout << "| 3. Train Capacity Menu               |\n";
            cout << "| 4. Reservation Menu                  |\n";
            cout << "| 5. Save Data                         |\n";
            cout << "| 6. Exit Program                      |\n";
            cout << "+--------------------------------------+\n";
            cout << "Enter your choice: ";
            cin >> menuChoice;
            if (cin.fail() || menuChoice < 1 || menuChoice > 6)
            {
                inputValidation();
                cout << "Please select a number from the list.\n\n";
            }
            else
            {
                validation = true;
                system("clear");
            }
        } while (validation == false);

        // Train Operations
        if (menuChoice == 1)
        {
            trainOperations(trains, trainCapacities, trainCounter, noOfTrains, capacityCounter, noOfCapacities, noOfClasses);
        }
        // Train Class Operations
        else if (menuChoice == 2)
        {
            trainClassOperations(trainClasses, trainCapacities, classCounter, noOfClasses, noOfTrains, noOfCapacities, capacityCounter);
        }
        // Train Capacity Operations
        else if (menuChoice == 3)
        {
            trainCapacityOperations(trains, trainCapacities, trainClasses, reservations, reservationCounter, trainCounter, classCounter, capacityCounter, noOfCapacities);
        }
        // Reservation Operations
        else if (menuChoice == 4)
        {
            reservationOperations(trains, trainCapacities, trainClasses, reservations, trainCounter, classCounter, capacityCounter, reservationCounter, noOfReservations);
        }
        // Data Saving
        else if (menuChoice == 5)
        {
            if (saveArrayToFile("trains.bin", trains, sizeof(Train) * trainCounter)&&
                saveArrayToFile("trainClasses.bin", trainClasses, sizeof(TrainClass) * classCounter)&&
                saveArrayToFile("reservations.bin", reservations, sizeof(Reservation) * reservationCounter)&&
                saveArrayToFile("trainCapacities.bin", trainCapacities, sizeof(TrainCapacity) * capacityCounter)&&
                saveCounterToFile(trainCounter, classCounter, reservationCounter, capacityCounter)&&
                saveArraySizeToFile(noOfTrains, noOfClasses, noOfCapacities, noOfReservations))
                cout << "Data saved successfully\n\n";
            else
                cout << "Couldn't save data.\n\n";
        }
        // Deallocation and Termination
        else if (menuChoice == 6)
        {
            delete[] trains;
            delete[] trainCapacities;
            delete[] trainClasses;
            delete[] reservations;
            return 0;
        }
    }
}

void trainOperations(Train* trains, TrainCapacity* trainCapacities, int trainCounter, int noOfTrains, int capacityCounter, int noOfCapacities, int noOfClasses)
{
        system("clear");
        int trainChoice;
        while (true)
        {
            bool validation = false;
            // Train Menu
            do
            {
                cout << "+------------------------------+\n";
                cout << "|          Train Menu          |\n";
                cout << "+------------------------------+\n";
                cout << "| 1. Insert record             |\n";
                cout << "| 2. Update train name         |\n";
                cout << "| 3. Delete a record           |\n";
                cout << "| 4. Display a specific record |\n";
                cout << "| 5. Display all records       |\n";
                cout << "| 6. Return to main menu       |\n";
                cout << "+------------------------------+\n";
                cout << "Enter your choice: ";
                cin >> trainChoice;
                if (cin.fail() || trainChoice < 1 || trainChoice > 6)
                {
                    inputValidation();
                    cout << "Please select a number from the list.\n\n";
                }
                else
                {
                    validation = true;
                    system("clear");
                }
            } while (validation == false);

            // Insertion
            if (trainChoice == 1)
            {
                if (trainCounter == noOfTrains)
                {
                        noOfTrains *= 2;
                        Train* temp = new Train[noOfTrains];
                        for (int i = 0; i < trainCounter; i++)
                            temp[i] = trains[i];
                        delete[] trains;
                        trains = temp;

                        noOfCapacities = noOfTrains * noOfClasses;
                        TrainCapacity* temp2 = new TrainCapacity[noOfCapacities];
                        for (int i = 0; i < capacityCounter; i++)
                            temp2[i] = trainCapacities[i];
                        delete[] trainCapacities;
                        trainCapacities = temp2;
                }

                bool unique;
                int id;
                validation = false;
                do
                {
                    unique = true;
                    cout << "Enter train ID: ";
                    cin >> id;

                    if (id < 1 || cin.fail())
                    {
                        inputValidation();
                        cout << "Please enter a positive integer.\n\n";
                        continue;
                    }
                    else
                    {
                        validation = true;
                    }

                    for (int i = 0; i < trainCounter; i++)
                        if (trains[i].getTrainId() == id)
                        {
                            unique = false;
                            system("clear");
                            cout << "Please enter a unique ID.\n\n";
                        }

                } while (validation == false || unique == false);

                trains[trainCounter].insert(id);
                trainCounter++;
                system("clear");
                cout << "Record inserted successfully.\n\n";
                wait();
                system("clear");
            }

            // Updation
            if (trainChoice == 2)
            {
                // Searching for record
                validation = false;
                while (true)
                {
                    cout << "Enter train ID for updation: ";
                    int id;
                    cin >> id;

                    if (cin.fail() || id < 1)
                    {
                        inputValidation();
                        cout << "Please enter a positive integer.\n\n";
                        continue;
                    }

                    for (int i = 0; i < trainCounter; i++)
                        if (trains[i].getTrainId() == id)
                        {
                            validation = true;

                            // Updation Mechanism
                            system("clear");
                            cout << "Enter new train name: ";
                            char temp[40];
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cin.get(temp, 40);
                            trains[i].setTrainName(temp);
                        }

                    if (validation == true)
                    {
                        system("clear");
                        cout << "Record updated successfully.\n\n";
                        wait();
                        system("clear");
                        break;
                    }
                    else
                    {
                        system("clear");
                        cout << "Record not found.\n\n";
                        wait();
                        system("clear");
                        break;
                    }
                }
            }

            // Deletion
            if (trainChoice == 3)
            {
                // Searching for record
                validation = false;
                while (true)
                {
                    cout << "Enter train ID for deletion: ";
                    int id;
                    cin >> id;

                    if (cin.fail() || id < 1)
                    {
                        inputValidation();
                        cout << "Please enter a positive integer.\n\n";
                        continue;
                    }

                    for (int i = 0; i < capacityCounter; i++)
                        if (trainCapacities[i].getTrainId() == id)
                        {
                            validation = true;
                            break;
                        }

                    if (validation == true)
                    {
                        system("clear");
                        cout << "Record is present in train capacity class.\n\n";
                        break;
                    }
                    // Deletion Mechanism
                    else
                    {
                        bool found = false;
                        for (int i = 0; i < trainCounter; i++)
                        {
                            if (trains[i].getTrainId() == id)
                            {
                                found = true;
                                for (i; i < trainCounter - 1; i++)
                                    trains[i] = trains[i + 1];

                                cout << "Record deleted.\n\n";
                                wait();
                                system("clear");
                                trainCounter--;
                                break;
                            }
                        }
                        if (!found)
                        {
                            cout << "Record not found.\n\n";
                            wait();
                            system("clear");
                        }
                        break;
                    }
                }
            }

            // Displaying specific record
            if (trainChoice == 4)
            {
                validation = false;
                while (true)
                {
                    cout << "Enter train ID: ";
                    int id;
                    cin >> id;

                    if (cin.fail() || id < 1)
                    {
                        inputValidation();
                        cout << "Please enter a positive integer.\n\n";
                        continue;
                    }

                    for (int i = 0; i < trainCounter; i++)
                        if (trains[i].getTrainId() == id)
                        {
                            trains[i].display();
                            validation = true;
                        }

                    if (validation == false)
                        cout << "\nRecord not found.\n\n";

                    wait();
                    system("clear");
                    break;
                }
            }

            // Displaying all records
            if (trainChoice == 5)
            {
                for (int i = 0; i < trainCounter; i++)
                    trains[i].display();

                if (trainCounter == 0)
                    cout << "No records found.\n\n";

                wait();
                system("clear");
            }

            // Exiting to main menu
            if (trainChoice == 6)
                break;
        }
}
void trainClassOperations(TrainClass* trainClasses, TrainCapacity* trainCapacities, int classCounter, int noOfClasses, int noOfTrains, int noOfCapacities, int capacityCounter)
{
    system("clear");
    int classChoice;
    while (true)
    {
        bool validation = false;
        // Train Class Menu
        do
        {
            cout << "+--------------------------------+\n";
            cout << "|        Train Class Menu        |\n";
            cout << "+--------------------------------+\n";
            cout << "| 1. Insert record               |\n";
            cout << "| 2. Update class name           |\n";
            cout << "| 3. Delete a record             |\n";
            cout << "| 4. Display a specific record   |\n";
            cout << "| 5. Display all records         |\n";
            cout << "| 6. Return to main menu         |\n";
            cout << "+--------------------------------+\n";
            cout << "Enter your choice: ";
            cin >> classChoice;
            if (cin.fail() || classChoice < 1 || classChoice > 6)
            {
                inputValidation();
                cout << "Please select a number from the list.\n\n";
            }
            else
            {
                validation = true;
                system("clear");
            }
        } while (validation == false);

        // Insertion
        if (classChoice == 1)
        {
            if (classCounter == noOfClasses)
            {
                noOfClasses *= 2;
                TrainClass* temp = new TrainClass[noOfClasses];
                for (int i = 0; i < classCounter; i++)
                    temp[i] = trainClasses[i];
                delete[] trainClasses;
                trainClasses = temp;

                noOfCapacities = noOfTrains * noOfClasses;
                TrainCapacity* temp2 = new TrainCapacity[noOfCapacities];
                for (int i = 0; i < capacityCounter; i++)
                    temp2[i] = trainCapacities[i];
                delete[] trainCapacities;
                trainCapacities = temp2;
            }

            bool unique;
            int id;
            validation = false;
            do
            {
                unique = true;
                cout << "Enter class ID: ";
                cin >> id;

                if (id < 1 || cin.fail())
                {
                    inputValidation();
                    cout << "Please enter a positive integer.\n\n";
                    continue;
                }
                else
                {
                    validation = true;
                }

                for (int i = 0; i < classCounter; i++)
                    if (trainClasses[i].getClassId() == id)
                    {
                        unique = false;
                        system("clear");
                        cout << "Please enter a unique ID.\n\n";
                    }

            } while (validation == false || unique == false);

            trainClasses[classCounter].insert(id);
            classCounter++;
            system("clear");
            cout << "Record inserted successfully.\n\n";
            wait();
            system("clear");
        }

        // Updation
        if (classChoice == 2)
        {
            // Searching for record
            validation = false;
            while (true)
            {
                cout << "Enter class ID for updation: ";
                int id;
                cin >> id;

                if (cin.fail() || id < 1)
                {
                    inputValidation();
                    cout << "Please enter a positive integer.\n\n";
                    continue;
                }

                for (int i = 0; i < classCounter; i++)
                    if (trainClasses[i].getClassId() == id)
                    {
                        validation = true;

                        // Updation Mechanism
                        system("clear");
                        cout << "Enter new class name: ";
                        char temp[40];
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin.get(temp, 40);
                        trainClasses[i].setClassName(temp);
                    }

                if (validation == true)
                {
                    system("clear");
                    cout << "Record updated successfully.\n\n";
                    wait();
                    system("clear");
                    break;
                }
                else
                {
                    system("clear");
                    cout << "Record not found.\n\n";
                    wait();
                    system("clear");
                    break;
                }
            }
        }

        // Deletion
        if (classChoice == 3)
        {
            // Searching for record
            validation = false;
            while (true)
            {
                cout << "Enter class ID for deletion: ";
                int id;
                cin >> id;

                if (cin.fail() || id < 1)
                {
                    inputValidation();
                    cout << "Please enter a positive integer.\n\n";
                    continue;
                }

                for (int i = 0; i < capacityCounter; i++)
                    if (trainCapacities[i].getClassId() == id)
                    {
                        validation = true;
                        break;
                    }

                if (validation == true)
                {
                    system("clear");
                    cout << "Record is present in train capacity class.\n\n";
                    break;
                }
                // Deletion Mechanism
                else
                {
                    bool found = false;
                    for (int i = 0; i < classCounter; i++)
                    {
                        if (trainClasses[i].getClassId() == id)
                        {
                            found = true;
                            for (i; i < classCounter - 1; i++)
                                trainClasses[i] = trainClasses[i + 1];

                            cout << "Record deleted.\n\n";
                            wait();
                            system("clear");
                            classCounter--;
                            break;
                        }
                    }
                    if (!found)
                    {
                        cout << "Record not found.\n\n";
                        wait();
                        system("clear");
                    }
                    break;
                }
            }
        }

        // Displaying specific record
        if (classChoice == 4)
        {
            validation = false;
            while (true)
            {
                cout << "Enter class ID: ";
                int id;
                cin >> id;

                if (cin.fail() || id < 1)
                {
                    inputValidation();
                    cout << "Please enter a positive integer.\n\n";
                    continue;
                }

                for (int i = 0; i < classCounter; i++)
                    if (trainClasses[i].getClassId() == id)
                    {
                        trainClasses[i].display();
                        validation = true;
                    }

                if (validation == false)
                    cout << "\nRecord not found.\n\n";

                wait();
                system("clear");
                break;
            }
        }

        // Displaying all records
        if (classChoice == 5)
        {
            for (int i = 0; i < classCounter; i++)
                trainClasses[i].display();

            if (classCounter == 0)
                cout << "No records found.\n\n";

            wait();
            system("clear");
        }

        // Exiting to main menu
        if (classChoice == 6)
            break;
    }
}
void trainCapacityOperations(Train* trains, TrainCapacity* trainCapacities, TrainClass* trainClasses, Reservation* reservations, int reservationCounter, int trainCounter, int classCounter, int capacityCounter, int noOfCapacities)
{
    system("clear");
    int capacityChoice;
    while (true)
    {
        bool validation = false;
        // Train Capacity Menu
        do
        {
            cout << "+-------------------------------+\n";
            cout << "|      Train Capacity Menu      |\n";
            cout << "+-------------------------------+\n";
            cout << "| 1. Insert record              |\n";
            cout << "| 2. Update attributes          |\n";
            cout << "| 3. Delete a record            |\n";
            cout << "| 4. Display a specific record  |\n";
            cout << "| 5. Display all records        |\n";
            cout << "| 6. Return to main menu        |\n";
            cout << "+-------------------------------+\n";
            cout << "Enter your choice: ";
            cin >> capacityChoice;
            if (cin.fail() || capacityChoice < 1 || capacityChoice > 6)
            {
                inputValidation();
                cout << "Please select a number from the list.\n\n";
            }
            else
            {
                validation = true;
                system("clear");
            }
        } while (validation == false);

        // Insertion
        if (capacityChoice == 1)
        {
            if (capacityCounter == noOfCapacities)
            {
                system("clear");
                cout << "Data has been inserted for all trains and classes. Please create another train or class.\n\n";
                continue;
            }

            bool trainExists, classExists;
            int tid, cid;
            trainExists = false;
            classExists = false;

            while (true)
            {
                cout << "Enter train ID: ";
                cin >> tid;

                if (tid < 1 || cin.fail())
                {
                    inputValidation();
                    cout << "Please enter a positive integer.\n\n";
                    continue;
                }

                while (true)
                {
                    cout << "Enter class ID: ";
                    cin >> cid;

                    if (cid < 1 || cin.fail())
                    {
                        inputValidation();
                        cout << "Please enter a positive integer.\n\n";
                        continue;
                    }
                    break;
                }

                for (int i = 0; i < trainCounter; i++)
                    if (trains[i].getTrainId() == tid)
                    {
                        trainExists = true;
                        break;
                    }

                for (int i = 0; i < classCounter; i++)
                    if (trainClasses[i].getClassId() == cid)
                    {
                        classExists = true;
                        break;
                    }

                if (!trainExists)
                {
                    system("clear");
                    cout << "Train doesn't exist.\n\n";
                    break;
                }

                if (!classExists)
                {
                    system("clear");
                    cout << "Class doesn't exist.\n\n";
                    break;
                }

                for (int i = 0; i < capacityCounter; i++)
                {
                    if (trainCapacities[i].getTrainId() == tid && trainCapacities[i].getClassId() == cid)
                    {
                        trainExists = false;
                        classExists = false;
                        system("clear");
                        cout << "Please enter unique train and class IDs.\n\n";
                        break;
                    }
                }
                break;
            }

            if (trainExists == true && classExists == true)
            {
                trainCapacities[capacityCounter].insert(tid, cid);
                capacityCounter++;
                system("clear");
                cout << "Record inserted successfully.\n\n";
            }
            wait();
            system("clear");
        }

        // Updation
        if (capacityChoice == 2)
        {
            // Searching for record
            validation = false;
            while (true)
            {
                int tid, cid;
                cout << "Enter train ID for updation: ";
                cin >> tid;

                if (cin.fail() || tid < 1)
                {
                    inputValidation();
                    cout << "Please enter a positive integer.\n\n";
                    continue;
                }

                while (true)
                {
                    cout << "\nEnter class ID for updation: ";
                    cin >> cid;

                    if (cin.fail() || cid < 1)
                    {
                        inputValidation();
                        cout << "Please enter a positive integer.\n\n";
                        continue;
                    }
                    break;
                }

                for (int i = 0; i < capacityCounter; i++)
                    if (trainCapacities[i].getClassId() == cid && trainCapacities[i].getTrainId() == tid)
                    {
                        validation = true;

                        // Updation Mechanism
                        system("clear");
                        while (true)
                        {
                            cout << "Enter new total seats: ";
                            int seats;
                            cin >> seats;
                            system("clear");

                            if (cin.fail() || seats < 1)
                            {
                                inputValidation();
                                cout << "Please enter a positive value.\n\n";
                                continue;
                            }
                            trainCapacities[i].setTotalSeats(seats);
                            break;
                        }

                        while (true)
                        {
                            cout << "Enter new rate: ";
                            int rate;
                            cin >> rate;
                            system("clear");

                            if (cin.fail() || rate < 1)
                            {
                                inputValidation();
                                cout << "Please enter a positive value.\n\n";
                                continue;
                            }
                            trainCapacities[i].setRate(rate);
                            break;
                        }
                        break;
                    }

                if (validation == true)
                {
                    system("clear");
                    cout << "Record updated successfully.\n\n";
                    wait();
                    system("clear");
                    break;
                }
                else
                {
                    system("clear");
                    cout << "Record not found.\n\n";
                    wait();
                    system("clear");
                    break;
                }
            }
        }

        // Deletion
        if (capacityChoice == 3)
        {
            // Searching for record
            validation = false;
            while (true)
            {
                int tid, cid;
                cout << "Enter train ID for deletion: ";
                cin >> tid;

                if (cin.fail() || tid < 1)
                {
                    inputValidation();
                    cout << "Please enter a positive integer.\n\n";
                    continue;
                }

                while (true)
                {
                    cout << "Enter class ID for deletion: ";
                    cin >> cid;

                    if (cin.fail() || cid < 1)
                    {
                        inputValidation();
                        cout << "Please enter a positive integer.\n\n";
                        continue;
                    }
                    break;
                }

                for (int i = 0; i < reservationCounter; i++)
                    if (reservations[i].getClassId() == cid && reservations[i].getTrainId() == tid)
                    {
                        validation = true;
                        break;
                    }

                if (validation == true)
                {
                    system("clear");
                    cout << "Record is present in reservation class.\n\n";
                    break;
                }
                // Deletion Mechanism
                else
                {
                    bool found = false;
                    for (int i = 0; i < capacityCounter; i++)
                    {
                        if (trainCapacities[i].getClassId() == cid && trainCapacities[i].getTrainId() == tid)
                        {
                            found = true;
                            for (i; i < capacityCounter - 1; i++)
                                trainCapacities[i] = trainCapacities[i + 1];

                            system("clear");
                            cout << "Record deleted.\n\n";
                            wait();
                            system("clear");
                            capacityCounter--;
                            break;
                        }
                    }
                    if (!found)
                    {
                        cout << "Record not found.\n\n";
                        wait();
                        system("clear");
                    }
                    break;
                }
            }
        }

        // Displaying specific record
        if (capacityChoice == 4)
        {
            validation = false;
            while (true)
            {
                int tid, cid;
                cout << "Enter train ID: ";
                cin >> tid;

                if (cin.fail() || tid < 1)
                {
                    inputValidation();
                    cout << "Please enter a positive integer.\n\n";
                    continue;
                }

                while (true)
                {
                    cout << "Enter class ID: ";
                    cin >> cid;

                    if (cin.fail() || cid < 1)
                    {
                        inputValidation();
                        cout << "Please enter a positive integer.\n\n";
                        continue;
                    }
                    break;
                }

                for (int i = 0; i < capacityCounter; i++)
                    if (trainCapacities[i].getClassId() == cid && trainCapacities[i].getTrainId() == tid)
                    {
                        trainCapacities[i].display();
                        validation = true;
                        break;
                    }

                if (validation == false)
                    cout << "\nRecord not found.\n\n";

                wait();
                system("clear");
                break;
            }
        }

        // Displaying all records
        if (capacityChoice == 5)
        {
            for (int i = 0; i < capacityCounter; i++)
                trainCapacities[i].display();

            if (capacityCounter == 0)
                cout << "No records found.\n\n";

            wait();
            system("clear");
        }

        // Exiting to main menu
        if (capacityChoice == 6)
            break;
    }
}
void reservationOperations(Train* trains, TrainCapacity* trainCapacities, TrainClass* trainClasses, Reservation* reservations, int trainCounter, int classCounter, int capacityCounter, int reservationCounter, int noOfReservations)
{
    int reservationChoice;
    while (true)
    {
        bool validation = false;
        // Reservation Menu
        do
        {
            system("clear");
            cout << "+----------------------------------------+\n";
            cout << "|            Reservation Menu            |\n";
            cout << "+----------------------------------------+\n";
            cout << "| 1. Insert record                       |\n";
            cout << "| 2. Update attributes                   |\n";
            cout << "| 3. Delete a specific record            |\n";
            cout << "| 4. Display records for specific date   |\n";
            cout << "| 5. Display all records                 |\n";
            cout << "| 6. Display available seats             |\n";
            cout << "| 7. Check booking                       |\n";
            cout << "| 8. Return to main menu                 |\n";
            cout << "+----------------------------------------+\n";
            cout << "Enter your choice: ";
            cin >> reservationChoice;
            if (cin.fail() || reservationChoice < 1 || reservationChoice > 8)
            {
                inputValidation();
                cout << "Please select a number from the list.\n\n";
            }
            else
            {
                validation = true;
                system("clear");
            }
        } while (validation == false);

        // Insertion
        if (reservationChoice == 1)
        {
            bool trainExists, classExists, ticketValidation;
            int tid, cid;
            trainExists = false;
            classExists = false;

            while (true)
            {
                cout << "Enter train ID: ";
                cin >> tid;

                if (tid < 1 || cin.fail())
                {
                    inputValidation();
                    cout << "Please enter a positive integer.\n\n";
                    continue;
                }

                while (true)
                {
                    cout << "Enter class ID: ";
                    cin >> cid;

                    if (cid < 1 || cin.fail())
                    {
                        inputValidation();
                        cout << "Please enter a positive integer.\n\n";
                        continue;
                    }
                    break;
                }

                for (int i = 0; i < trainCounter; i++)
                    if (trains[i].getTrainId() == tid)
                    {
                        trainExists = true;
                        break;
                    }

                for (int i = 0; i < classCounter; i++)
                    if (trainClasses[i].getClassId() == cid)
                    {
                        classExists = true;
                        break;
                    }

                if (!trainExists && !classExists)
                {
                    system("clear");
                    cout << "Train doesn't exist.\n";
                    cout << "Class doesn't exist.\n\n";
                    wait();
                    break;
                }
                else if (!classExists)
                {
                    system("clear");
                    cout << "Class doesn't exist.\n\n";
                    wait();
                    break;
                }
                else if (!trainExists)
                {
                    system("clear");
                    cout << "Train doesn't exist.\n\n";
                    wait();
                    break;
                }
                break;
            }

            if (trainExists == true && classExists == true)
            {
                int ticket = 0, ticketNo = 0;
                char date[50];
                do
                {
                    cout << "Enter date in given format(dd/mm/yyyy): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get(date, 50);
                } while (!dateValidationPast(date));

                for (int i = 0; i < reservationCounter; i++)
                {
                    if (reservations[i].getTrainId() == tid && reservations[i].getClassId() == cid)
                    {   if (strcmp(reservations[i].getDate(), date) == 0)
                        {    
                            ticket++;
                            ticketNo = reservations[i].getTicketNo();
                        }
                    }
                }

                for (int i = 0; i < capacityCounter; i++)
                {
                    if (trainCapacities[i].getTrainId() == tid && trainCapacities[i].getClassId() == cid && trainCapacities[i].getTotalSeats() == ticket)
                    {
                        system("clear");
                        cout << "There are no available seats.\n\n";
                        wait();
                        break;
                    }
                    else
                    {
                        if (reservationCounter == noOfReservations)
                        {
                            noOfReservations *= 2;
                            Reservation* temp = new Reservation[noOfReservations];
                            for (int i = 0; i < reservationCounter; i++)
                                temp[i] = reservations[i];
                            delete[] reservations;
                            reservations = temp;
                        }
                        reservations[reservationCounter].insert(tid, cid, ticketNo, date);
                        reservationCounter++;
                        system("clear");
                        cout << "Your ticket number is: " << ticketNo + 1;
                        cout << "\n\nRecord inserted successfully.\n\n";
                        wait();
                        break;
                    }
                }

            }
            system("clear");
        }

        // Updation
        if (reservationChoice == 2)
        {
            // Entering details
            bool trainExists, classExists;
            int tid, cid, ticket;
            trainExists = false;
            classExists = false;
            validation = false;

            while (true)
            {
                cout << "Enter train ID for updation: ";
                cin >> tid;

                if (tid < 1 || cin.fail())
                {
                    inputValidation();
                    cout << "Please enter a positive integer.\n\n";
                    continue;
                }

                while (true)
                {
                    cout << "Enter class ID for updation: ";
                    cin >> cid;

                    if (cid < 1 || cin.fail())
                    {
                        inputValidation();
                        cout << "Please enter a positive integer.\n\n";
                        continue;
                    }
                    break;
                }

                for (int i = 0; i < trainCounter; i++)
                    if (trains[i].getTrainId() == tid)
                    {
                        trainExists = true;
                        break;
                    }

                for (int i = 0; i < classCounter; i++)
                    if (trainClasses[i].getClassId() == cid)
                    {
                        classExists = true;
                        break;
                    }

                if (!trainExists && !classExists)
                {
                    system("clear");
                    cout << "Train doesn't exist.\n";
                    cout << "Class doesn't exist.\n\n";
                    wait();
                    break;
                }
                else if (!classExists)
                {
                    system("clear");
                    cout << "Class doesn't exist.\n\n";
                    wait();
                    break;
                }
                else if (!trainExists)
                {
                    system("clear");
                    cout << "Train doesn't exist.\n\n";
                    wait();
                    break;
                }
                else
                    validation = true;
                break;

            }

            while (validation == true)
            {
                cout << "Enter ticket number for updation: ";
                cin >> ticket;

                if (ticket < 1 || cin.fail())
                {
                    inputValidation();
                    cout << "Please enter a positive integer.\n\n";
                    continue;
                }
                break;
            }
            validation = false;

            if (trainExists == true && classExists == true)
            {
                char date[50];
                do
                {
                    cout << "Enter date in given format(dd/mm/yyyy): ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get(date, 50);
                } while (!dateValidationPast(date));

                // Searching for record
                for (int i = 0; i < reservationCounter; i++)
                {
                    if (reservations[i].getTrainId() == tid && reservations[i].getClassId() == cid)
                    {
                        if (strcmp(reservations[i].getDate(), date) == 0 && reservations[i].getTicketNo() == ticket)
                        {
                            // Updation mechanism
                            system("clear");
                            cout << "Please enter new CNIC: ";
                            char temp[50];
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cin.get(temp, 50);
                            reservations[i].setCNIC(temp);
                            cout << "\nPlease enter new passenger name: ";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cin.get(temp, 50);
                            reservations[i].setPassengerName(temp);
                            validation = true;
                            break;
                        }
                    }
                }

                if (validation == true)
                {
                    system("clear");
                    cout << "Record updated successfully.\n\n";
                    wait();
                    system("clear");
                }
                else
                {
                    system("clear");
                    cout << "Record not found.\n\n";
                    wait();
                    system("clear");
                }
            }
        }

        // Deletion
        if (reservationChoice == 3)
        {
            // Entering details
            bool trainExists, classExists;
            int tid, cid, ticket;
            trainExists = false;
            classExists = false;
            validation = false;

            while (true)
            {
                cout << "Enter train ID for deletion: ";
                cin >> tid;

                if (tid < 1 || cin.fail())
                {
                    inputValidation();
                    cout << "Please enter a positive integer.\n\n";
                    continue;
                }

                while (true)
                {
                    cout << "Enter class ID for deletion: ";
                    cin >> cid;

                    if (cid < 1 || cin.fail())
                    {
                        inputValidation();
                        cout << "Please enter a positive integer.\n\n";
                        continue;
                    }
                    break;
                }

                for (int i = 0; i < trainCounter; i++)
                    if (trains[i].getTrainId() == tid)
                    {
                        trainExists = true;
                        break;
                    }

                for (int i = 0; i < classCounter; i++)
                    if (trainClasses[i].getClassId() == cid)
                    {
                        classExists = true;
                        break;
                    }

                if (!trainExists && !classExists)
                {
                    system("clear");
                    cout << "Train doesn't exist.\n";
                    cout << "Class doesn't exist.\n\n";
                    wait();
                    break;
                }
                else if (!classExists)
                {
                    system("clear");
                    cout << "Class doesn't exist.\n\n";
                    wait();
                    break;
                }
                else if (!trainExists)
                {
                    system("clear");
                    cout << "Train doesn't exist.\n\n";
                    wait();
                    break;
                }
                else
                    validation = true;
                break;

            }

            while (validation == true)
            {
                cout << "Enter ticket number for deletion: ";
                cin >> ticket;

                if (ticket < 1 || cin.fail())
                {
                    inputValidation();
                    cout << "Please enter a positive integer.\n\n";
                    continue;
                }
                break;
            }
            validation = false;

            if (trainExists == true && classExists == true)
            {
                int index;
                char date[50];
                do
                {
                    cout << "Enter date in given format(dd/mm/yyyy): ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get(date, 50);
                } while (!dateValidation(date));

                // Searching for record
                for (int i = 0; i < reservationCounter; i++)
                    if (reservations[i].getTrainId() == tid && reservations[i].getClassId() == cid)
                        if (strcmp(reservations[i].getDate(), date) == 0 && reservations[i].getTicketNo() == ticket)
                        {
                            index = i;
                            validation = true;
                        }

                if (validation == true)
                {
                    // Deletion mechanism
                    for (index; index < reservationCounter - 1; index++)
                        reservations[index] = reservations[index + 1];
                    reservationCounter--;
                    system("clear");
                    cout << "Record deleted successfully.\n\n";
                    wait();
                    system("clear");
                }
                else
                {
                    system("clear");
                    cout << "Record not found.\n\n";
                    wait();
                    system("clear");
                }
            }
        }

        // Displaying records for specific date
        if (reservationChoice == 4)
        {
            // Entering details
            bool trainExists, classExists;
            int tid, cid;
            trainExists = false;
            classExists = false;
            validation = false;

            while (true)
            {
                cout << "Enter train ID: ";
                cin >> tid;

                if (tid < 1 || cin.fail())
                {
                    inputValidation();
                    cout << "Please enter a positive integer.\n\n";
                    continue;
                }

                while (true)
                {
                    cout << "Enter class ID: ";
                    cin >> cid;

                    if (cid < 1 || cin.fail())
                    {
                        inputValidation();
                        cout << "Please enter a positive integer.\n\n";
                        continue;
                    }
                    break;
                }

                for (int i = 0; i < trainCounter; i++)
                    if (trains[i].getTrainId() == tid)
                    {
                        trainExists = true;
                        break;
                    }

                for (int i = 0; i < classCounter; i++)
                    if (trainClasses[i].getClassId() == cid)
                    {
                        classExists = true;
                        break;
                    }

                if (!trainExists && !classExists)
                {
                    system("clear");
                    cout << "Train doesn't exist.\n";
                    cout << "Class doesn't exist.\n\n";
                    wait();
                    break;
                }
                else if (!classExists)
                {
                    system("clear");
                    cout << "Class doesn't exist.\n\n";
                    wait();
                    break;
                }
                else if (!trainExists)
                {
                    system("clear");
                    cout << "Train doesn't exist.\n\n";
                    wait();
                    break;
                }
                break;
            }

            if (trainExists == true && classExists == true)
            {
                char date[50];
                do
                {
                    cout << "Enter date in given format(dd/mm/yyyy): ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get(date, 50);
                } while (!dateValidation(date));

                system("clear");
                // Searching for record
                for (int i = 0; i < reservationCounter; i++)
                    if (reservations[i].getTrainId() == tid && reservations[i].getClassId() == cid && strcmp(reservations[i].getDate(), date) == 0)
                    {
                        reservations[i].display();
                        validation = true;
                    }

                if (!validation)
                {
                    system("clear");
                    cout << "No record found.\n\n";
                    wait();
                    system("clear");
                }
                else
                {
                    wait();
                    system("clear");
                }
            }
        }

        // Displaying all records
        if (reservationChoice == 5)
        {
            for (int i = 0; i < reservationCounter; i++)
                reservations[i].display();

            if (reservationCounter == 0)
                cout << "No records found.\n\n";

            wait();
            system("clear");
        }

        // Displaying available seats
        if (reservationChoice == 6)
        {
            // Entering details
            bool trainExists, classExists;
            int tid, cid;
            trainExists = false;
            classExists = false;
            validation = false;

            while (true)
            {
                cout << "Enter train ID: ";
                cin >> tid;

                if (tid < 1 || cin.fail())
                {
                    inputValidation();
                    cout << "Please enter a positive integer.\n\n";
                    continue;
                }

                while (true)
                {
                    cout << "Enter class ID: ";
                    cin >> cid;

                    if (cid < 1 || cin.fail())
                    {
                        inputValidation();
                        cout << "Please enter a positive integer.\n\n";
                        continue;
                    }
                    break;
                }

                for (int i = 0; i < trainCounter; i++)
                    if (trains[i].getTrainId() == tid)
                    {
                        trainExists = true;
                        break;
                    }

                for (int i = 0; i < classCounter; i++)
                    if (trainClasses[i].getClassId() == cid)
                    {
                        classExists = true;
                        break;
                    }

                if (!trainExists && !classExists)
                {
                    system("clear");
                    cout << "Train doesn't exist.\n";
                    cout << "Class doesn't exist.\n\n";
                    wait();
                    break;
                }
                else if (!classExists)
                {
                    system("clear");
                    cout << "Class doesn't exist.\n\n";
                    wait();
                    break;
                }
                else if (!trainExists)
                {
                    system("clear");
                    cout << "Train doesn't exist.\n\n";
                    wait();
                    break;
                }
                break;
            }

            if (trainExists == true && classExists == true)
            {
                int ticket = 0;
                char date[50];
                do
                {
                    cout << "Enter date in given format(dd/mm/yyyy): ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get(date, 50);
                } while (!dateValidation(date));

                // Searching for latest ticket
                for (int i = 0; i < reservationCounter; i++)
                    if (reservations[i].getTrainId() == tid && reservations[i].getClassId() == cid && strcmp(reservations[i].getDate(), date) == 0)
                        ticket++;

                system("clear");
                cout << "Remaining tickets: ";
                for (int i = 0; i < capacityCounter; i++)
                    if (trainCapacities[i].getTrainId() == tid && trainCapacities[i].getClassId() == cid)
                        cout << trainCapacities[i].getTotalSeats() - ticket << endl << endl;
                wait();
                system("clear");
            }
        }

        // Checking specific booking
        if (reservationChoice == 7)
        {
            validation = false;
            system("clear");
            char temp[20];
            cout << "Enter CNIC: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get(temp, 20);
            system("clear");

            for (int i = 0; i < reservationCounter; i++)
                if (strcmp(reservations[i].getCNIC(), temp) == 0)
                {
                    reservations[i].display();
                    validation = true;
                }

            if (!validation)
            {
                system("clear");
                cout << "No record found.\n\n";
                wait();
                system("clear");
            }
            else
            {
                wait();
                system("clear");
            }
        }

        // Exiting to main menu
        if (reservationChoice == 8)
            break;
    }
}