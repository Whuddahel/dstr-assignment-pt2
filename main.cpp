//
// Created by BanEdward on 28/10/2025.
//
// #include "EmergencyDepartmentOfficer.hpp"

#include <iostream>

using namespace std;

void runMedicalSupplyManager();
void runPatientAdmissionClerk();
void runEmergencyDepartmentOfficer();

int main()
{
    while (true)
    {
        cout << "Welcome to Hospital Patient Care Management System app!\n1. Patient Admission Clerk\n2. Medical Supply Manager\n3. Emergency Department Officer\n4. Ambulance Dispatcher\n5. Exit\nPlease select an option: ";
        int choice;
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a number!" << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            runPatientAdmissionClerk();
            break;
        case 2:
            runMedicalSupplyManager();
            break;
        case 3:
            runEmergencyDepartmentOfficer();
            break;
        case 4:
            cout << "Missing feature..." << endl;
            break;
        case 5:
            cout << "Thank you for using this program!" << endl;
            return 0;
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
        }

        // if(choice == 2)
        // {
        //     runMedicalSupplyManager();
        // }
        // else if(choice == 5)
        // {
        //     cout << "Thank you for using this program!" << endl;
        //     break;
        // }
        // else
        // {
        //     cout << "Missing feature..." << endl;
        // }
    }
}
