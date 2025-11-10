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
Stack listOfSplittedItemsHolder;
Stack listOfSplittedItemsFlipper;

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

void loadFileSequence()
{
    listOfItems.destroy();
    listOfSplittedItems.destroy();
    listOfSplittedItemsHolder.destroy();


    listOfItems = extractItemsFile(listOfItems, "items.csv");

    // listOfItems.print();

    while(listOfItems.isEmpty() == false)
    {
        string bufferToBeSplit = listOfItems.pop();
        string bufferToContainSplit[3] = {""};
        split(bufferToBeSplit, bufferToContainSplit, ',');

        bufferToContainSplit[1].erase(0, 1);
        bufferToContainSplit[2].erase(0, 1);

        listOfSplittedItems.push(bufferToContainSplit[0], bufferToContainSplit[1], bufferToContainSplit[2]);
    }
}

void listItems()
{
    cout << endl;
    cout << "Type                                                |  Quantity    |  Batch" << endl;

    while(!listOfSplittedItems.isEmpty())
    {
        StackNode buffer = listOfSplittedItems.pop();

        cout << buffer.type;
        for(int i = (52 - buffer.type.length()); i > 0; i--)
        {
            cout << " ";
        }
        cout << "|  ";

        cout << buffer.quantity;
        for(int i = (12 - buffer.quantity.length()); i > 0; i--)
        {
            cout << " ";
        }
        cout << "|  ";

        cout << buffer.batch << endl;

        listOfSplittedItemsHolder.push(buffer.type, buffer.quantity, buffer.batch);
    }

    while(listOfSplittedItemsHolder.isEmpty() == false)
    {
        StackNode buffer = listOfSplittedItemsHolder.pop();
        listOfSplittedItems.push(buffer.type, buffer.quantity, buffer.batch);
    }
}

void addItem()
{
    string inputBuffer[3] = {""};
    cout << "Enter Item Type: ";
    cin >> inputBuffer[0];
    cout << "Enter Quantity: ";
    cin >> inputBuffer[1];
    cout << "Enter Batch No.: ";
    cin >> inputBuffer[2];

    listOfSplittedItems.push(inputBuffer[0], inputBuffer[1], inputBuffer[2]);
    ofstream fileContents("items.csv", ios::app); //append mode
    fileContents << inputBuffer[0] << ", " << inputBuffer[1] << ", " << inputBuffer[2] << endl;
    fileContents.close();

    loadFileSequence();

}

void retrieveItem()
{
    ofstream fileContents("items.csv");
    fileContents << "type, quantity, batch" << endl;

    while(listOfSplittedItems.isEmpty() == false)
    {
        StackNode buffer = listOfSplittedItems.pop();
        listOfSplittedItemsHolder.push(buffer.type, buffer.quantity, buffer.batch);
    }

    StackNode lastRetrievedItem = listOfSplittedItemsHolder.pop();
    cout << "Retrieved " << lastRetrievedItem.quantity << "x " << lastRetrievedItem.type << " from batch " << lastRetrievedItem.batch << endl;

    while(listOfSplittedItemsHolder.isEmpty() == false)
    {
        StackNode buffer = listOfSplittedItemsHolder.pop();
        listOfSplittedItems.push(buffer.type, buffer.quantity, buffer.batch);
    }

    while(listOfSplittedItems.isEmpty() == false)
    {
        StackNode buffer = listOfSplittedItems.pop();
        // listOfSplittedItemsHolder.push(buffer.type, buffer.quantity, buffer.batch);

        fileContents << buffer.type << ", " << buffer.quantity << ", " << buffer.batch << endl;
    }
    fileContents.close();

    loadFileSequence();
}

void runMedicalSupplyManager()
{
    loadFileSequence();

    while(true)
    {
        cout << "Medical Supply Manager\n1. Add an item\n2. Withdraw an item\n3. List Items\n4. Exit\nPlease select an option: ";
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
            addItem();
        }
        else if(choice == 2)
        {
           retrieveItem();
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