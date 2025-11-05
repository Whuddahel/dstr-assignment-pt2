// NOTE: This file is the actual code and implementation of the Emergency Department Officer (role 3) - by Edward Fong Yu Xian
// -------------------------------------------------------------------------------------
#include <iostream>
#include "PriorityQueue.hpp"
#include "EmergencyCase.hpp"

using namespace std;
void loadEmergencyCases();

void runEmergencyDepartmentOfficer()
{
    while (true)
    {
        loadEmergencyCases();

        cout << "[Emergency Department Officer Menu]\n1. Log Emergency Case\n2. Process Most Critical Case\n3. View Pending Cases (Order by Priority)\n4. Exit\nPlease select an option: ";
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Missing feature..." << endl;
            break;
        case 2:
            cout << "Missing feature..." << endl;
            break;
        case 3:
            cout << "Missing feature..." << endl;
            break;
        case 4:
            cout << "Thank you for using this program!" << endl;
            return;
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
        }
    }
}