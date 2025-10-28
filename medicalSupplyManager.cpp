//
// Created by BanEdward on 27/10/2025.
//
#include <iostream>

using namespace std;

void runMedicalSupplyManager()
{
    while(true)
    {
        cout << "Medical Supply Manager\n1.Add an item\n2. Withdraw an item\n3. List Items\n4. Exit\nPlease select an option: " << endl;
        int choice;
        cin >> choice;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a number!" << endl;
            continue;
        }

        if(choice == 2)
        {
            cout << "test" << endl;
        }
    }
}