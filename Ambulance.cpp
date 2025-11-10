#include <iostream>
#include "Tp080522-Ambulance.hpp"

using namespace std;

int getValidatedInput() {
    int choice;
    while (!(cin >> choice)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

int main() {
    AmbulanceDispatcher dispatcher;
    int simulatedHour = 0; 
    int choice = 0;

    while (choice != 4) {
        
        dispatcher.displayAmbulanceSchedule(simulatedHour);

        cout << "- - - - - - - - - MENU - - - - - - - - -" << endl;
        cout << "1. Rotate [On Duty 1] ambulance" << endl;
        cout << "2. Register new ambulance" << endl;
        cout << "3. Simulate 1 hour" << endl;
        cout << "4. Exit system" << endl;
        cout << "- - - - - - - - - - - - - - - - - - - -" << endl;
        cout << "Enter your choice: ";

        choice = getValidatedInput();

        switch (choice) {
            case 1:
                dispatcher.rotateAmbulanceShift();
                break;

            case 2:
                dispatcher.registerNewAmbulance();
                cout << "[System] New ambulance added. Resetting..." << endl;
                simulatedHour = 0;
                dispatcher.reset();
                break;

            case 3: {
                simulatedHour++;
                
                bool didReset = dispatcher.incrementOnDutyHours(1); 
                
                cout << "An hour passes..." << endl;

                if (didReset) {
                    simulatedHour = 0;
                }
                break;
            }
            case 4:
                cout << "Exiting system." << endl;
                break;

            default:
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
        }
    }

    return 0;
}