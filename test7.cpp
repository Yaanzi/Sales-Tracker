#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ios>

using namespace std;

const string monthFiles[] = {
    "Database/JanDatabase.txt", "Database/FebDatabase.txt", "Database/MarDatabase.txt",
    "Database/AprDatabase.txt", "Database/MayDatabase.txt", "Database/JunDatabase.txt",
    "Database/JulDatabase.txt", "Database/AugDatabase.txt", "Database/SepDatabase.txt",
    "Database/OctDatabase.txt", "Database/NovDatabase.txt", "Database/DecDatabase.txt"
};

const string monthNames[] = {
    "January", "February", "March", "April", "May", "June", 
    "July", "August", "September", "October", "November", "December"
};

void inventory(), database(), exitProgram(), overview(), monthly(), yearly(), compare ();
void displayDatabase(), viewMonthDatabase(int), monthlyChoice (int& Month);
void ReadData(int Month, int& lastCusNo, int& monthlySales, int& monthlyProductsSold);



int main() {
    char menu;
    do {
        system("cls");
        cout << "\t\t\t-----------------------------------------------\n";
        cout << "\t\t\t|\033[1;94m      Little Einsteins Co. Sales Tracker     \033[0m|\n";
        cout << "\t\t\t-----------------------------------------------\n";
        cout << "\t\t\t\t----------------------------\n";
        cout << "\t\t\t\t|  A.) Add Transaction     |\n";
        cout << "\t\t\t\t|  B.) View Database       |\n";
        cout << "\t\t\t\t|  C.) General Overview    |\n";
        cout << "\t\t\t\t|  D.) Exit Program        |\n";
        cout << "\t\t\t\t----------------------------\n";
        cin >> menu;
        
        switch (menu) {
            case 'A': case 'a': inventory(); break;
            case 'B': case 'b': database(); break;
            case 'C': case 'c': overview(); break;
            case 'D': case 'd': exitProgram(); break;
            default: cout << "Invalid option! Please try again.\n";
        }
    } while (true);
}

void inventory() {
    system("cls");
    int productChoice, cusNo, qty, month, price = 0, monthlySales = 0, monthlyProductsSold = 0;
    string productName;
    
    cout << "Enter the month (1-12): ";
    cin >> month;
    if (month < 1 || month > 12) { cout << "Invalid month\n"; return; }

    ifstream inFile(monthFiles[month - 1]);
    int lastCusNo = 0;
    ReadData(month, lastCusNo, monthlySales, monthlyProductsSold);
    cusNo = (lastCusNo == 0) ? 1 : lastCusNo + 1;

    cout << "-----------------------------" << endl;
    cout << "|\033[1m Select Product by Number: \033[0m|" << endl;
    cout << "|---------------------------|" << endl;
    cout << "|                     Price |" << endl;
    cout << "| [1] Cappuccino    -  120  |" << endl;
    cout << "| [2] Iced Coffee   -  110  |" << endl;
    cout << "| [3] Latte         -  110  |" << endl;
    cout << "| [4] Hot Cocoa     -  110  |" << endl;
    cout << "| [5] Coffee Jelly  -  80   |" << endl;
    cout << "| [6] Macaron       -  75   |" << endl;
    cout << "| [7] Tea           -  70   |" << endl;
    cout << "| [8] Muffin        -  65   |" << endl;
    cout << "| [9] Bagel         -  65   |" << endl;
    cout << "| [10] Espresso     -  60   |" << endl;
    cout << "-----------------------------" << endl;
    cout << "-----------------------------" << endl;
    cout << "Enter Product Number: ";
    cin >> productChoice;

    switch (productChoice) {
        case 1: price = 120; productName = "Cappuccino"; break;
        case 2: price = 110; productName = "Iced_Coffee"; break;
        case 3: price = 110; productName = "Latte"; break;
        case 4: price = 110; productName = "Hot_Cocoa"; break;
        case 5: price = 80; productName = "Coffee_Jelly"; break;
        case 6: price = 75; productName = "Macaron"; break;
        case 7: price = 70; productName = "Tea"; break;
        case 8: price = 65; productName = "Muffin"; break;
        case 9: price = 65; productName = "Bagel"; break;
        case 10: price = 60; productName = "Espresso"; break;
        default: cout << "Invalid choice!\n"; return;
    }

    cout << "Enter quantity: ";
    cin >> qty;

    int sales = qty * price;
    monthlySales += sales;
    monthlyProductsSold += qty;

    ofstream outFile(monthFiles[month - 1], ios::app);
    if (!outFile) { cerr << "Error opening file.\n"; return; }
    outFile << cusNo << ' ' << productName << ' ' << qty << ' ' << price << ' ' << sales << ' ' << monthlySales << ' ' << monthlyProductsSold << endl;
    outFile.close();

    system ("cls");
    cout << "Transaction saved. "<< endl;
    system ("pause");
}

void database()
{
    system("cls");
    
    int Month;
    monthlyChoice(Month);
    viewMonthDatabase(Month);
}

void overview() {
    system("cls");
    int choice;
    cout << "---------------------------------" << endl;
    cout << "|\033[1;94m       Database Overview       \033[0m|" << endl;
    cout << "|-------------------------------|" << endl;
    cout << "|  [1] - Monthly Overview       |" << endl;
    cout << "|  [2] - Yearly Overview        |" << endl;
    cout << "|  [3] - Compare Monthly Sales  |" << endl;
    cout << "---------------------------------" << endl;
    cout << "Choose an Option Between 1-3: ";
    cin >> choice;
    switch (choice) {
        case 1: monthly(); break;
        case 2: yearly(); break;
        case 3: compare(); break;
    }
}

void exitProgram() {
    system("CLS");
    cout << "Logging Off (press enter)...\n";
    cin.ignore();
    cin.get();
    exit(0);
}

void monthlyChoice(int& month) {
    cout << "------------------------------------------------" << endl;
    cout << "|\033[1;94m         Search Databases by Month           \033[0m|" << endl;
    cout << "|----------------------------------------------|" << endl;
    cout << "|   [1] - January      |   [7] - July          |" << endl;
    cout << "|   [2] - February     |   [8] - August        |" << endl;
    cout << "|   [3] - March        |   [9] - September     |" << endl;
    cout << "|   [4] - April        |   [10] - October      |" << endl;
    cout << "|   [5] - May          |   [11] - November     |" << endl;
    cout << "|   [6] - June         |   [12] - December     |" << endl;
    cout << "------------------------------------------------" << endl;
    
    cout << "\nEnter Month: ";
    cin >> month;
    if (month < 1 || month > 12) { cout << "Invalid month\n"; return; }
}

void viewMonthDatabase(int month) {
    ifstream monthFile(monthFiles[month - 1]);
    if (!monthFile) { cout << "Unable to open file.\n"; 
    system("pause"); 
    return; }
    
    int cusNo, qty, sales, price, monthlySales, monthlyProductsSold;
    string productName;

    system("CLS");
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "|\t\t\t\t\t\033[1mCustomer Database\t\t\t\t\t\033[0m|" << endl;
    cout << "|-------------------------------------------------------------------------------|" << endl;
    cout << left << "|Customer Number\t\tProduct\t\tQuantity\tPrice\t\tSales\t|" << endl;
    cout << "|-------------------------------------------------------------------------------|" << endl;

    while (monthFile >> cusNo >> productName >> qty >> price >> sales >> monthlySales >> monthlyProductsSold) {
        cout <<left << "|\t" << cusNo << "\t\t" << setw(20) << productName << qty << "\t\t" << price << "\t\t" << sales << "\t|" << endl;
    }
    monthFile.close();

    cout << "---------------------------------------------------------------------------------\n";
    system("pause");
}

void ReadData(int Month, int& lastCusNo, int& monthlySales, int& monthlyProductsSold) {
    ifstream inFile(monthFiles[Month - 1]);
    string line;

    monthlySales = 0;
    monthlyProductsSold = 0;
    lastCusNo = 0;

    if (inFile) {
        while (getline(inFile, line)) {
            size_t spacePos = line.find(' ');
            lastCusNo = stoi(line.substr(0, spacePos));

            size_t lastSpace = line.rfind(' ');
            if (lastSpace != string::npos) {
                string lastPart = line.substr(lastSpace + 1);
                size_t secondLastSpace = line.rfind(' ', lastSpace - 1);
                string secondLastPart = line.substr(secondLastSpace + 1, lastSpace - secondLastSpace - 1);

                monthlyProductsSold = stoi(lastPart);
                monthlySales = stoi(secondLastPart);
            }
        }
        inFile.close();
    } else {
        cout << "No data available for the selected month." << endl;
        system("pause");
        main();
    }
}

void monthly() {
    system("cls");
    int month, lastCusNo = 0, monthlySales = 0, monthlyProductsSold = 0;
    monthlyChoice(month);
    ReadData(month, lastCusNo, monthlySales, monthlyProductsSold);
    system("cls");
    cout << "Last Customer Number: " << lastCusNo << endl;
    cout << "Monthly Sales: " << monthlySales << endl;
    cout << "Monthly Products Sold: " << monthlyProductsSold << endl;
    system("pause");
}


void yearly() {
    system("cls");

    int totalCustomers = 0, totalSales = 0, totalProductsSold = 0;

    for (int i = 0; i < 12; i++) {
        ifstream inFile(monthFiles[i]);
        int monthlySales = 0, monthlyProductsSold = 0, customersInMonth = 0;
        string line;

        if (inFile) {
            while (getline(inFile, line)) {
                size_t lastSpace = line.rfind(' ');
                if (lastSpace != string::npos) {
                    string lastPart = line.substr(lastSpace + 1);
                    size_t secondLastSpace = line.rfind(' ', lastSpace - 1);
                    string secondLastPart = line.substr(secondLastSpace + 1, lastSpace - secondLastSpace - 1);

                    monthlyProductsSold += stoi(lastPart);
                    monthlySales += stoi(secondLastPart);
                    customersInMonth++;
                }
            }
            inFile.close();

            totalSales += monthlySales;
            totalProductsSold += monthlyProductsSold;
            totalCustomers += customersInMonth;
        }
    }

    cout << "Yearly Overview:" << endl;
    cout << "Total Customers: " << totalCustomers << endl;
    cout << "Total Products Sold: " << totalProductsSold << endl;
    cout << "Total Sales: " << totalSales << endl;

    system("pause");
    main();
}

void compare() {
    system("cls");

    int month1, month2;
    cout << "Enter the first month number to compare (1-12): ";
    cin >> month1;
    cout << "Enter the second month number to compare (1-12): ";
    cin >> month2;

    if (month1 < 1 || month1 > 12 || month2 < 1 || month2 > 12) {
        cout << "Invalid months entered!" << endl;
        return;
    }

    system("cls");

    int lastCusNo1 = 0, monthlySales1 = 0, monthlyProductsSold1 = 0;
    int lastCusNo2 = 0, monthlySales2 = 0, monthlyProductsSold2 = 0;

    ReadData(month1, lastCusNo1, monthlySales1, monthlyProductsSold1);
    ReadData(month2, lastCusNo2, monthlySales2, monthlyProductsSold2);

    cout << "-------------------------------------" << endl;
    cout << "|\033[1;94m    Monthly Sales Comparison      \033[0m|" << endl;
    cout << "|-----------------------------------|" << endl;

    cout << left << "|      " << monthNames[month1 - 1] << " Sales: \t" << setw(12) << monthlySales1 << "|" << endl;
    cout << left << "|      " << monthNames[month2 - 1] << " Sales: \t" << setw(12) << monthlySales2 << "|"<< endl;

    cout << "-------------------------------------" << endl << endl;

    if (monthlySales1 > monthlySales2) {
        
        cout << monthNames[month1 - 1] << " had higher monthly sales than " << monthNames[month2 - 1] << "." << endl << endl;
    } else if (monthlySales1 < monthlySales2) {
        cout << monthNames[month2 - 1] << " had higher monthly sales than " << monthNames[month1 - 1] << "." << endl << endl;
    } else {
        cout << "Both months have the same sales." << endl << endl;
    }

    system("pause");
}


