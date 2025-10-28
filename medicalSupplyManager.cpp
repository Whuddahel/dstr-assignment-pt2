//
// Created by BanEdward on 27/10/2025.
//
#include <iostream>
#include "linkedlist.hpp"

using namespace std;

string *extractItemsFile(BasicStackNode<> headPointer, string filepath)
{
    string buffer;
    int count = 0;
    bool ignoreFirst = false;

    ifstream fileContents(filepath);
    while (getline(fileContents, buffer))
    {
        if(ignoreFirst == true)
        {
            buffer = trimCsvContents(buffer);
            filteredFileContents[count] = buffer;
            count = count + 1;
        }
        ignoreFirst = true;
    }
    fileContents.close();
    return filteredFileContents;
}

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

        if(choice == 1)
        {
            cout << "enter" << endl;
        }
        else if(choice == 2)
        {
            cout << "withdraw" << endl;
        }
        else if(choice == 3)
        {
            cout << "listItems" << endl;
        }
        else if(choice == 4)
        {
            cout << "Exit back to main menu" << endl;
            break;
        }
        else
        {
            cout << "Wrong input" << endl;
        }
    }
}