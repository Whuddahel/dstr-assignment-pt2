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
int QUEUE_SIZE = 50;
PriorityQueue<EmergencyCase> emergencyQueue(QUEUE_SIZE);

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
        if (buffer.empty())
        {
            continue;
        }
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

    ifstream inFile(FILE_NAME);
    ofstream tempFile("temp.csv");
    string buffer;

    while (getline(inFile, buffer))
    {
        // build what this case would look like in the file
        string currentLine = nextCase.name + "," + nextCase.emergType + "," + to_string(nextCase.priority);

        // if line matches the processed case, skip it
        if (buffer == currentLine)
            continue;

        tempFile << buffer << "\n";
    }

    inFile.close();
    tempFile.close();

    // replace the old file
    remove(FILE_NAME.c_str());
    rename("temp.csv", FILE_NAME.c_str());

    cout << "Case removed from CSV.\n";
}

void viewPendingCases()
{
    if (emergencyQueue.isEmpty())
    {
        cout << "No pending emergency cases." << endl;
        return;
    }

    EmergencyCase arrayOfEmergCase[QUEUE_SIZE];
    int elementCount = 0;
    cout << endl
         << "Patient Name                                       |  Emergency Type              |  Priority" << endl;
    for (int i = 0; i <= QUEUE_SIZE; i++)
    {
        EmergencyCase emergCase = emergencyQueue.getElementAt(i);
        if (emergCase.name.empty())
        {
            break;
        }
        arrayOfEmergCase[elementCount++] = emergCase;
    }

    for (int i = 0; i < elementCount - 1; i++)
    {
        for (int j = 0; j < elementCount - i - 1; j++)
        {
            if (arrayOfEmergCase[j].priority < arrayOfEmergCase[j + 1].priority)
            {
                EmergencyCase temp = arrayOfEmergCase[j];
                arrayOfEmergCase[j] = arrayOfEmergCase[j + 1];
                arrayOfEmergCase[j + 1] = temp;
            }
        }
    }

    for (int i; i < elementCount; i++)
    {
        EmergencyCase emergCase = arrayOfEmergCase[i];
        cout << emergCase.name;
        for (int j = 0; j < 51 - static_cast<int>(emergCase.name.size()); j++)
        {
            cout << " ";
        }
        cout << "|  " << emergCase.emergType;
        for (int j = 0; j < 28 - static_cast<int>(emergCase.emergType.size()); j++)
        {
            cout << " ";
        }
        cout << "|  " << emergCase.priority << endl;
    }

    cout << endl;
    // Create a temporary copy of the priority queue to display cases without modifying the original
    // PriorityQueue<EmergencyCase> tempQueue = emergencyQueue;
    // cout << "Pending Emergency Cases (Ordered by Priority):" << endl;
    // tempQueue.display();
    // int count = 1;
    // while (!tempQueue.isEmpty())
    // {
    //     EmergencyCase caseEntry = tempQueue.pop();
    //     cout << count << ". " << caseEntry << endl;
    //     count++;
    // }
}
void runEmergencyDepartmentOfficer()
{
    loadEmergencyCases();
    while (true)
    {
        // emergencyQueue.display();
        cout << "[Emergency Department Officer Menu]\n1. Log Emergency Case\n2. Process Most Critical Case\n3. View Pending Cases (Order by Priority)\n4. Exit\nPlease select an option: ";
        int choice;
        cin >> choice;
        cin.ignore(10000, '\n');

        switch (choice)
        {
        case 1:
            logEmergencyCase();
            break;
        case 2:
            processCase();
            break;
        case 3:
            viewPendingCases();
            break;
        case 4:
            cout << "Exiting back to User Select Menu." << endl;
            return;
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
        }
    }
}