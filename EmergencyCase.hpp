// NOTE: This header file is simply a struct and the definition of its comparator operators.
// -------------------------------------------------------------------------------------
#ifndef EMERGENCY_CASE_HPP
#define EMERGENCY_CASE_HPP

#include <string>
#include <iostream>
using namespace std;

// -------------------------------------------------------------------------------------
struct EmergencyCase
{
    string name;
    string emergType; // e.g., "Cardiac Arrest", "Fracture", "Dropped as a Child"...
    int priority; // Higher number means higher priority

    // Custom comparator for priority
    bool operator<(const EmergencyCase &other) const
    {
        return priority < other.priority;
    }
    bool operator>(const EmergencyCase &other) const
    {
        return priority > other.priority;
    }

    friend ostream& operator<<(ostream& os, const EmergencyCase& e) { // This is for the << operator for nice printing
        os << e.name << " | " << e.emergType << " | Priority: " << e.priority;
        return os;
    }
};

#endif