#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "linkedlist.hpp"

using namespace std;

// Patient structure
struct Patient {
    string patientID;
    string name;
    string conditionType;
    string admissionTime;
};


struct PatientQueueNode {
    Patient data;
    PatientQueueNode* next;
};

//FIFO
class PatientQueue {
private:
    PatientQueueNode* front;  
    PatientQueueNode* rear;   
    int size;

public:
    PatientQueue() : front(nullptr), rear(nullptr), size(0) {}

    bool isEmpty() {
        return front == nullptr;
    }

    int getSize() {
        return size;
    }

    void enqueue(const Patient& patient) {
        PatientQueueNode* newNode = new PatientQueueNode;
        newNode->data = patient;
        newNode->next = nullptr;

        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    Patient dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty! No patients to discharge.");
        }

        PatientQueueNode* temp = front;
        Patient patient = temp->data;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
        size--;
        return patient;
    }

    Patient peek() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty!");
        }
        return front->data;
    }

    // Display all patients 
    void display() {
        if (isEmpty()) {
            cout << "\nNo patients in queue\n" << endl;
            return;
        }

        cout << "\n--------------------------------------------" << endl;
        cout << "     PATIENT QUEUE (" << size << " patients)" << endl;
        cout << "--------------------------------------------" << endl;
        cout << left << setw(12) << "Patient ID" 
             << setw(25) << "Name" 
             << setw(20) << "Condition" 
             << "Admission Time" << endl;
        cout << "----------------------------------------" << endl;

        PatientQueueNode* current = front;
        int position = 1;
        
        while (current != nullptr) {
            cout << left << setw(12) << current->data.patientID
                 << setw(25) << current->data.name
                 << setw(20) << current->data.conditionType
                 << current->data.admissionTime << endl;
            current = current->next;
            position++;
        }
        cout << "========================================\n" << endl;
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open file for writing." << endl;
            return;
        }

        file << "PatientID,Name,ConditionType,AdmissionTime" << endl;

        PatientQueueNode* current = front;
        while (current != nullptr) {
            file << current->data.patientID << ","
                 << current->data.name << ","
                 << current->data.conditionType << ","
                 << current->data.admissionTime << endl;
            current = current->next;
        }

        file.close();
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            return; 
        }

        string line;
        getline(file, line); 

        while (getline(file, line)) {
            if (line.empty()) continue;

            Patient patient;
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);

            patient.patientID = line.substr(0, pos1);
            patient.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            patient.conditionType = line.substr(pos2 + 1, pos3 - pos2 - 1);
            patient.admissionTime = line.substr(pos3 + 1);

            enqueue(patient);
        }

        file.close();
    }

    ~PatientQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

PatientQueue patientQueue;
int patientCounter = 1000; 

string generatePatientID() {
    patientCounter++;
    return "P" + to_string(patientCounter);
}

string getCurrentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    string hour = to_string(ltm->tm_hour);
    string min = to_string(ltm->tm_min);
    
    if (hour.length() == 1) hour = "0" + hour;
    if (min.length() == 1) min = "0" + min;
    
    return hour + ":" + min;
}

void admitPatient() {
    cout << "\n========================================" << endl;
    cout << "         ADMIT NEW PATIENT" << endl;
    cout << "========================================" << endl;

    Patient newPatient;
    newPatient.patientID = generatePatientID();

    cin.ignore(); 
    
    cout << "Enter Patient Name: ";
    getline(cin, newPatient.name);
    
    cout << "Enter Condition Type (e.g., Fever, Injury, Checkup): ";
    getline(cin, newPatient.conditionType);
    
    newPatient.admissionTime = getCurrentTime();

    patientQueue.enqueue(newPatient);
    patientQueue.saveToFile("patients.csv");

    cout << "\n[SUCCESS] Patient admitted successfully!" << endl;
    cout << "Patient ID: " << newPatient.patientID << endl;
    cout << "Name: " << newPatient.name << endl;
    cout << "Condition: " << newPatient.conditionType << endl;
    cout << "Admission Time: " << newPatient.admissionTime << endl;
    cout << "Queue Position: " << patientQueue.getSize() << endl;
    cout << "-----------------------------------------\n" << endl;
}

void dischargePatient() {
    cout << "\n-----------------------------------------" << endl;
    cout << "         DISCHARGE PATIENT" << endl;
    cout << "-----------------------------------------" << endl;

    try {
        Patient discharged = patientQueue.dequeue();
        patientQueue.saveToFile("patients.csv");

        cout << "\n[SUCCESS] Patient discharged successfully!" << endl;
        cout << "Patient ID: " << discharged.patientID << endl;
        cout << "Name: " << discharged.name << endl;
        cout << "Condition: " << discharged.conditionType << endl;
        cout << "Admission Time: " << discharged.admissionTime << endl;
        cout << "\nRemaining patients in queue: " << patientQueue.getSize() << endl;
        cout << "-----------------------------------------\n" << endl;

    } catch (const runtime_error& e) {
        cout << "\n[ERROR] " << e.what() << endl;
        cout << "-----------------------------------------\n" << endl;
    }
}

void viewPatientQueue() {
    patientQueue.display();
}

void runPatientAdmissionClerk() {
    patientQueue.loadFromFile("patients.csv");

    cout << "\n--------------------------------------------" << endl;
    cout << "   PATIENT ADMISSION CLERK SYSTEM" << endl;
    cout << "--------------------------------------------" << endl;

    while (true) {
        cout << "\n--- Patient Admission Menu ---" << endl;
        cout << "1. Admit Patient" << endl;
        cout << "2. Discharge Patient" << endl;
        cout << "3. View Patient Queue" << endl;
        cout << "4. Return to Main Menu" << endl;
        cout << "------------------------------" << endl;
        cout << "Select an option: ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n[ERROR] Please enter a valid number!\n" << endl;
            continue;
        }

        switch (choice) {
            case 1:
                admitPatient();
                break;
            case 2:
                dischargePatient();
                break;
            case 3:
                viewPatientQueue();
                break;
            case 4:
                cout << "\nReturning to main menu...\n" << endl;
                return;
            default:
                cout << "\nInvalid option. Please try again.\n" << endl;
        }
    }
}