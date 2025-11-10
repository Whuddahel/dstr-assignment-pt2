#ifndef AMBULANCEDISPATCHER_HPP
#define AMBULANCEDISPATCHER_HPP

#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct ambulanceNode {
    string carPlate;
    int totalDutyHours;
    int dutyHours;
    ambulanceNode* nextAddress;

    ambulanceNode(const string& plate, int totalDuration, int onDutyHour) : carPlate(plate), totalDutyHours(totalDuration), dutyHours(onDutyHour), nextAddress(nullptr) {}
};

class AmbulanceDispatcher {
    private:
        ambulanceNode* rear; 
        int size;

        void updateDutyDurations() {
            if (isEmpty()) {
                return;
            }

            int newDuration = 0;

            // If only 1 ambulance, so he cannot be shift. If 2 ambulances, they shift prioritise only
            if (size <= 2) {
                newDuration = 24;
            } 
            // This system assume that there will be 2 ambulance in duty, total duty hours will be 24h * 2 ambulance = 48h
            else {
                newDuration = 48 / size;
            }

            if (newDuration * size < 48) {
                newDuration += 1;
            }

            // Reassign from front ambulance
            ambulanceNode* current = rear->nextAddress;

            for (int i = 0; i < size; i++) {
                current->totalDutyHours = newDuration;
                current = current->nextAddress;
            }
        }

    public:
        // Constructor
        AmbulanceDispatcher() : rear(nullptr), size(0) {}

        ~AmbulanceDispatcher() {
            if (isEmpty()) {
                return;
            }
            ambulanceNode* front = rear->nextAddress;
            rear->nextAddress = nullptr;
            
            ambulanceNode* current = front;

            while (current != nullptr) {
                ambulanceNode* temp = current;
                current = current->nextAddress;
                delete temp;
            }
        }

        bool isEmpty() {
            return rear == nullptr;
        }

        int getSize() {
            return size;
        }
        
        bool reset() {
            ambulanceNode* current = rear->nextAddress;

            for (int i = 0; i < size; i++) {
                current->dutyHours = 0;
                current = current->nextAddress;
            }
            return true;
        }

        void addAmbulanceInLinkedList(string carPlate) {
            ambulanceNode* newNode = new ambulanceNode(carPlate, 0, 0);

            if (isEmpty()) {
                rear = newNode; 
                // Loop back to itself
                rear->nextAddress = rear;
            } 
            else {
                // Previously A's nextAddress is A (Loop), point new's nextAddress to A (A's nextAddress), so they become loop
                newNode->nextAddress = rear->nextAddress;
                // Previously A's nextAddress is A, change it to New 
                rear->nextAddress = newNode;
                // New become the rear
                rear = newNode;
            }
            size++;

            // Recalculate all duration to equal
            updateDutyDurations();
        }

        void registerNewAmbulance() {
            string carPlate;

            cout << endl << "Enter Car Plate: ";
            getline(cin, carPlate);

            addAmbulanceInLinkedList(carPlate);
            
            cout << "[System] Ambulance " << carPlate << " has been registered." << endl;
        }

        void rotateAmbulanceShift() {
            if (isEmpty()) {
                cout << "Error: No ambulances in the schedule to rotate." << endl;
                return;
            }
            
            if (size == 1) {
                cout << "[Rotation] Only " << rear->carPlate << " is in service. It remains on duty." << endl;
                return;
            }

            ambulanceNode* firstAmbulance = rear->nextAddress;
            
            rear = firstAmbulance; 
            
            cout << "[Rotation] " << firstAmbulance->carPlate << " has moved to back of the queue." << endl;

            ambulanceNode* newOnDutyA = rear->nextAddress;
        }

        void displayAmbulanceSchedule(int time) {
            if (isEmpty()) {
                cout << endl << "The ambulance schedule is currently empty." << endl;
                return;
            }

            cout << endl << "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =" << endl;
            cout << "             Ambulance Schedule (Time: " << time << ":00)" << endl;
            cout << "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =" << endl;
            ambulanceNode* current = rear->nextAddress;

            for (int i = 0; i < size; i++) {
                string status = "[Waiting]";
                if (i == 0) status = "[On Duty 1]";
                else if (i == 1) status = "[On Duty 2]";

                cout.width(13);
                cout << left << status << current->carPlate << "  (Duty Duration: " << current->dutyHours << "/" << current->totalDutyHours << " hours)" << endl; 
                
                current = current->nextAddress;
            }
        }

        bool incrementOnDutyHours(int hours) {
            if (isEmpty()) {
                return false;
            }

            ambulanceNode* firstAmbulance = rear->nextAddress;
            int nextDutyHours = firstAmbulance->dutyHours + hours;

            // If A over time
            if (nextDutyHours > firstAmbulance->totalDutyHours) {
                cout << endl << "[System] " << firstAmbulance->carPlate << " has completed its daily duty duration." << endl;
                
                // Rotate to B & C
                rotateAmbulanceShift();
                
                // Set B & C on duty
                return incrementOnDutyHours(hours);
            }
            
            // IF A no over time, then continue
            firstAmbulance->dutyHours = nextDutyHours;

            // If only one, no need to rotate
            if (size <= 1) {
                return false;
            }

            int rotationCount = 0;
            int maxRotations = size - 1; // A should not been counted

            while (rotationCount < maxRotations) {
                ambulanceNode* secondAmbulance = firstAmbulance->nextAddress;

                nextDutyHours = secondAmbulance->dutyHours + hours;

                // If B over time
                if (nextDutyHours > secondAmbulance->totalDutyHours) {                    
                    // Get first and second pointers
                    ambulanceNode* currentA = rear->nextAddress;
                    ambulanceNode* currentB = currentA->nextAddress;
                    
                    // Set A's next pointer to B's next pointer (C)
                    currentA->nextAddress = currentB->nextAddress;
                    
                    // Point B's next to the front (rear next is front), so B is now the rear, it become loop
                    currentB->nextAddress = rear->nextAddress;
                    // Previous rear's next is front, now set to B
                    rear->nextAddress = currentB;
                    // Set B to rear
                    rear = currentB;
                    
                    cout << "[Rotation] " << currentB->carPlate << " (Paused at " << currentB->dutyHours << "/" << currentB->totalDutyHours << "hrs) has moved to the back." << endl;
                                        
                    rotationCount++;
                }
                // B no over time, continue
                else {
                    secondAmbulance->dutyHours = nextDutyHours;
                    break;
                }
            }

            if (rotationCount >= maxRotations && size > 1) {
                cout << endl << "[System] All waiting ambulances have exceeded their shift duration!" << endl;
                cout << "[System] Only " << firstAmbulance->carPlate << " is currently available." << endl;
                cout << "[System] Reset right now..." << endl;
                return reset();
            }
            
            return false;
        }
};

#endif  