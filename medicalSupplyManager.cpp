//
// Created by BanEdward on 27/10/2025.
//
#include <iostream>
#include "linkedlist.hpp"
#include <fstream>
#include <string>

using namespace std;

BasicStack<string> listOfItems;
Stack listOfSplittedItems;

BasicStack<string> extractItemsFile(BasicStack<string> &headPointer, string filepath)
{
    string buffer;
    bool ignoreFirst = false;

    ifstream fileContents(filepath);
    while (getline(fileContents, buffer))
    {
        if(ignoreFirst == true)
        {
            headPointer.push(buffer);
        }
        ignoreFirst = true;
    }
    fileContents.close();
    return headPointer;
}

string* split(string& inputText, string outputText[], char delimiter)
{
    int index = 0;
    string buffer = "";

    for(char character : inputText)
    {
        if(character == delimiter)
        {
            outputText[index] = buffer;
            index = index + 1;
            buffer = "";
        }
        else
        {
            buffer = buffer + character;
        }
    }

    outputText[index] = buffer;
    return outputText;
}

void listItems()
{
    cout << "Type                                                   Quantity       Batch" << endl;
    Stack listOfSplittedItemsHolder;
    while(!listOfSplittedItems.isEmpty())
    {
        StackNode buffer = listOfSplittedItems.pop();

        cout << buffer.type;
        for(int i = (55 - buffer.type.length()); i > 0; i--)
        {
            cout << " ";
        }

        cout << buffer.quantity;
        for(int i = (15 - buffer.quantity.length()); i > 0; i--)
        {
            cout << " ";
        }

        cout << buffer.batch << endl;

        listOfSplittedItemsHolder.push(buffer.type, buffer.quantity, buffer.batch);
    }

    while(listOfSplittedItemsHolder.isEmpty() == false)
    {
        StackNode buffer = listOfSplittedItemsHolder.pop();
        listOfSplittedItems.push(buffer.type, buffer.quantity, buffer.batch);
    }
}

void runMedicalSupplyManager()
{
    listOfItems = extractItemsFile(listOfItems, "items.csv");

    listOfItems.print();

    while(listOfItems.isEmpty() == false)
    {
        string bufferToBeSplit = listOfItems.pop();
        string bufferToContainSplit[3] = {""};
        split(bufferToBeSplit, bufferToContainSplit, ',');

        bufferToContainSplit[1].erase(0, 1);
        bufferToContainSplit[2].erase(0, 1);

        listOfSplittedItems.push(bufferToContainSplit[0], bufferToContainSplit[1], bufferToContainSplit[2]);
    }

    while(true)
    {
        cout << "Medical Supply Manager\n1.Add an item\n2. Withdraw an item\n3. List Items\n4. Exit\nPlease select an option: ";
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
            listItems();
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