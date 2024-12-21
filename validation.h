#include <iostream>
using namespace std;

// Functions for Validation
void wait()
{
    cout << "Press Enter to continue...";
    cin.get();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void inputValidation()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    system("clear");
}
bool dateValidationPast(const char* inputDate)
{
    char dayString[3], monthString[3], yearString[5];
    strncpy(dayString, inputDate, 2);
    dayString[2] = '\0';

    strncpy(monthString, inputDate + 3, 2);
    monthString[2] = '\0';

    strncpy(yearString, inputDate + 6, 4);
    yearString[4] = '\0';

    int day = atoi(dayString);
    int month = atoi(monthString);
    int year = atoi(yearString);

    if (month > 12)
        return false;

    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        daysInMonth[2] = 29;

    if (day > daysInMonth[month])
        return false;

   time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);

    if (year < localTime->tm_year + 1900 ||
        (year == localTime->tm_year + 1900 && (month < localTime->tm_mon + 1 ||
            (month == localTime->tm_mon + 1 && day < localTime->tm_mday)))) {
        return false;
    }

    return true;
}
bool dateValidation(const char* inputDate)
{
    char dayString[3], monthString[3], yearString[5];
    strncpy(dayString, inputDate, 2);
    dayString[2] = '\0';

    strncpy(monthString, inputDate + 3, 2);
    monthString[2] = '\0';

    strncpy(yearString, inputDate + 6, 4);
    yearString[4] = '\0';

    int day = atoi(dayString);
    int month = atoi(monthString);
    int year = atoi(yearString);

    if (month > 12)
        return false;

    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        daysInMonth[2] = 29;

    if (day > daysInMonth[month])
        return false;

    return true;
}