// NOTE: This file is the actual code and implementation of the Emergency Department Officer (role 3) - by Edward Fong Yu Xian
// -------------------------------------------------------------------------------------
#include "PriorityQueue.hpp"
#include "EmergencyCase.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
string FILE_NAME = "emergency_cases.csv";
PriorityQueue<EmergencyCase> emergencyQueue(50);

void loadEmergencyCases()
{
    ifstream file(FILE_NAME); // Input file stream, read-only mode
    if (!file.is_open())
    {
        cerr << "Could not open the file - '" << FILE_NAME << "'" << endl;
        return;
    }

    string buffer;
    getline(file, buffer); // Skip header line

    while (getline(file, buffer))
    {
        stringstream ss(buffer);
        string priorityStr;
        EmergencyCase caseEntry;

        getline(ss, caseEntry.name, ',');
        getline(ss, caseEntry.emergType, ',');
        getline(ss, priorityStr, ',');
        if (priorityStr.empty())
            continue; // Skip if priority is missing
        caseEntry.priority = stoi(priorityStr);

        emergencyQueue.push(caseEntry);
    }
};

void logEmergencyCase()
{
    EmergencyCase newCase;
    cout << "Enter Patient Name: ";
    getline(cin, newCase.name);
    if (newCase.name.find(',') != string::npos)
    {
        cout << "Commas are not allowed in the name. Please try again." << endl;
        return;
    }
    cout << "Enter Emergency Type: ";
    getline(cin, newCase.emergType);
    if (newCase.emergType.find(',') != string::npos)
    {
        cout << "Commas are not allowed in the emergency type. Please try again." << endl;
        return;
    }
    cout << "Enter Priority (Higher number means higher priority): ";
    if (!(cin >> newCase.priority))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input for priority. Please enter a number." << endl;
        return;
    };

    ofstream file(FILE_NAME, ios::app); // Append mode
    file << newCase.name << "," << newCase.emergType << "," << newCase.priority << endl;
    file.close();

    emergencyQueue.push(newCase);
    cout << "Emergency case logged successfully." << endl;
};

void processCase()
{
    if (emergencyQueue.isEmpty())
    {
        cout << "No emergency cases to process." << endl;
        return;
    }
    EmergencyCase nextCase = emergencyQueue.pop();
    cout << "Processing case: " << nextCase << endl;
}

void viewPendingCases()
{
    if (emergencyQueue.isEmpty())
    {
        cout << "No pending emergency cases." << endl;
        return;
    }

    // Create a temporary copy of the priority queue to display cases without modifying the original
    PriorityQueue<EmergencyCase> tempQueue = emergencyQueue;
    cout << "Pending Emergency Cases (Ordered by Priority):" << endl;

    int count = 1;
    while (!tempQueue.isEmpty())
    {
        EmergencyCase caseEntry = tempQueue.pop();
        cout << count << ". " << caseEntry << endl;
        count++;
    }
}
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
            logEmergencyCase();
            break;
        case 2:
            processCase();
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