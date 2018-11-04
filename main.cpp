#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Schedule {
private:
    int day, month, year;
    int daysInMonth[13] = { 0, 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

public:
    Schedule();
    void getDate();
    bool isLeapYear(int y);
    int setDaysInMonth();
    void printCalender();
    void printDate();
    int calenderStartDay(int y);
    int formatMonth(int m);
};

// ******************* Declaration Functions ******************* // 

char userChoice();
int userInput(const int min, const int max);
void printMenu();

// *************************** Main **************************** // 

int main() 
{
    Schedule schedule;                              
    char choice;
    schedule.setDaysInMonth(); 
    printMenu(); 
    choice = userChoice();
    while (choice != 'Q') {
        switch (choice) {
            case 'A': schedule.getDate(); break;
            case 'B': schedule.printCalender(); break;
            case 'C': cout << "C" << endl; break;
            case 'D': schedule.printDate(); break;
            case 'E': cout << "E" << endl; break;
            default: printMenu(); break;
        }
        choice = userChoice();
    }

    return 0;
}


// ******************* Definition Class Member Functions ******************* // 

Schedule::Schedule() {day = 1; month = 1; year = 2018;}

// User inputs a date (mm.yyyy)
void Schedule::getDate()
{
    cout << "Enter day: "; day = userInput(1, 31);
    cout << "Enter month: "; month = userInput(1, 12);
    cout << "Enter year: "; year = userInput(2000, 2100);
}

// Check to see if year is leapYear
bool Schedule::isLeapYear(int year)
{
   // From Frode oblig4 
   return ((year % 400 == 0) || ((year % 4 == 0) && (year % 100) != 0));
}

//  TODO: Check leap year and february 
int Schedule::setDaysInMonth()                     // If leapYear sets february to 29
{                                                   // else to 28
     daysInMonth[2] = (isLeapYear(year)) ? 29 : 28; // OBS! [0] is not used, 
     return daysInMonth[2];                         
}

void Schedule::printDate() {                       // Prints out current date
    cout << "Current date: ";
    if (day < 10) cout << "0" << day << "/";        
    else cout << day << "/";
    if (month < 10) cout << "0" << month << "-";
    else cout << month << "-";
    cout << year;
}

int Schedule::calenderStartDay(int year) {
    int currentYear = year; 
    int defaultYear = 2018;
    int startDay = 0;

    if (year != 2018)
       startDay += (currentYear - defaultYear); 
    else startDay = 0;

    return startDay;
}

int Schedule::formatMonth(int month) {
    int firstDayMonth = 0;
    
    // Jan: 0, Feb: 3, Mar: 3, Apr: 6, May: 1, June: 4, July: 6, Aug: 2, Sep: 5, Oct: 0, Nov: 3, Dec: 5
    for (int i = 1; i < month; i++) {
        firstDayMonth += daysInMonth[i];
        firstDayMonth = firstDayMonth % 7;
    }
    return firstDayMonth;
}
void Schedule::printCalender()
{
    // TODO: Use enum instead?
    int startDay = calenderStartDay(year);
    int firstDayMonth = formatMonth(month);

    string weekday[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

    cout << weekday[0] << "\t" << weekday[1] << "\t" << weekday[2] << "\t" 
         << weekday[3] << "\t" << weekday[4] << "\t" << weekday[5] << "\t" 
         << weekday[6] << "\n";
    
    cout << setw(firstDayMonth*8+1);
    // prints calender
    for (int i = 1; i <= daysInMonth[month]; i++)
    {
        cout << i << "\t";
        if ((startDay+firstDayMonth+i) % 7 == 0) cout << "\n";

    }
    cout << "\n\n\n";
}

// ***************************** Definition Functions ************************ //
char userChoice() {
    char ch;
    cout << "\n\n Command (A, B, C, D, E, Q): ";
    cin >> ch;
    return ch;
}

int userInput(const int min, const int max) {
    int choice;        // Variable for input
    cin >> choice;     // Get input
    while (choice < min || choice > max) {
        cout << "Valid input (" << min << '-' << max << "):";
        cin >> choice;     // Get input
    }
    return choice;
}

void printMenu() {
    cout << "A) Change the date." << endl;
    cout << "B) Print calender." << endl;
    cout << "C) Add plans." << endl;
    cout << "D) Print current date." << endl;
    cout << "E) TBA." << endl;
    cout << "Q) Quit." << endl;
}
