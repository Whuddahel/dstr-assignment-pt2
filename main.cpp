//
// Created by BanEdward on 28/10/2025.
//

#include <iostream>


using namespace std;

void runMedicalSupplyManager();

int main()
{
    while(true)
    {
        cout << "Welcome to sohai jason hospital app!\n1. Patient stuff\n2. Medical Supply Manager\n3. I forgot\n4. Ambulance\n5. Exit\nPlease select an option: ";
        int choice;
        cin >> choice;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a number!" << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            cout << "Missing feature..." << endl;
            break;
        case 2:
            runMedicalSupplyManager();
            break;
        case 3:
            cout << "Missing feature..." << endl;       
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
