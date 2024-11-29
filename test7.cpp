#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <ios>

using namespace std;

void inventory(), database(), exit(), overview(), monthly (), yearly (), compare ();
void DisplayDatabase(), PauseDatabase();
void viewMonthDatabase(int month);


int main()
{
    system("cls");

    char Menu;
    cout << "\t\t\t\tLittle Einsteins Co. Sales Tracker" << endl;
    cout << "\t\t\t--------------------------------------------------" << endl;
    cout << "A.) Add Transaction" << endl;
    cout << "B.) View Database" << endl;
    cout << "C.) General Overview" << endl;
    cout << "D.) Exit Program" << endl;
    cin >> Menu;

    switch (Menu) {
        case 'A': case 'a':
            inventory();
            break;
        case 'B': case 'b':
            database();
            break;
        case 'C': case 'c':
            overview();
            break;
        case 'D': case 'd':
            exit();
            break;
        default:
            cout << "Invalid option! Please try again." << endl;
            main();
    }

    cin.get(); 
}

void inventory() {
    system("cls");
    int ProductChoice, CusNo, Qnt, Month;
    string ProductName;
    int Price = 0, monthlySales = 0, monthlyProductsSold = 0;

    cout << "Enter Month Product Sold (1-12): ";
    cin >> Month;

    if (Month < 1 || Month > 12) {
        cout << "Invalid Month" << endl;
        return;
    }

    string monthFiles[] = {
        "Database/JanDatabase.txt", "Database/FebDatabase.txt", "Database/MarDatabase.txt",
        "Database/AprDatabase.txt", "Database/MayDatabase.txt", "Database/JunDatabase.txt",
        "Database/JulDatabase.txt", "Database/AugDatabase.txt", "Database/SepDatabase.txt",
        "Database/OctDatabase.txt", "Database/NovDatabase.txt", "Database/DecDatabase.txt"};

    ifstream inFile(monthFiles[Month - 1]);
    int lastCusNo = 0;
    string line;

    if (inFile) {
        while (getline(inFile, line)) {
            size_t spacePos = line.find(' ');
            int cusNo = stoi(line.substr(0, spacePos));
            lastCusNo = cusNo;

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
        CusNo = lastCusNo + 1;
    } else {
        CusNo = 1;
    }

    cout << "Select Product by Number:" << endl;
    cout << "\t\t\tPrice" << endl;
    cout << "[1] Cappuccino - \t120" << endl;
    cout << "[2] Iced Coffee - \t110" << endl;
    cout << "[3] Latte - \t\t110" << endl;
    cout << "[4] Hot Cocoa - \t110" << endl;
    cout << "[5] Coffee Jelly - \t80" << endl;
    cout << "[6] Macaron - \t\t75" << endl;
    cout << "[7] Tea - \t\t70" << endl;
    cout << "[8] Muffin - \t\t65" << endl;
    cout << "[9] Bagel - \t\t65" << endl;
    cout << "[10] Espresso - \t60" << endl;

    cout << "Enter Product Number: ";
    cin >> ProductChoice;

    switch (ProductChoice) {
        case 1: {Price = 120; ProductName = "Cappuccino";} break;
        case 2: {Price = 110; ProductName = "Iced_Coffee";} break;
        case 3: {Price = 110; ProductName = "Latte";} break;
        case 4: {Price = 110; ProductName = "Hot_Cocoa";} break;
        case 5: {Price = 80; ProductName = "Coffee_Jelly";} break;
        case 6: {Price = 75; ProductName = "Macaron";} break;
        case 7: {Price = 70; ProductName = "Tea";} break;
        case 8: {Price = 65; ProductName = "Muffin";} break;
        case 9: {Price = 65; ProductName = "Bagel";} break;
        case 10: {Price = 60; ProductName = "Espresso";} break;
        default:
            cout << "Invalid Product Choice!" << endl;
            return;
    }

    cout << "Enter Quantity: ";
    cin >> Qnt;

    int Sales = Qnt * Price;

    monthlySales += Sales;
    monthlyProductsSold += Qnt;

    ofstream outFile(monthFiles[Month - 1], ios::app);
    if (!outFile) {
        cerr << "Error: Could not open file for writing." << endl;
        return;
    }

    outFile << CusNo << ' ' << ProductName << ' ' << Qnt << ' ' << Price << ' ' << Sales << ' ' << monthlySales << ' ' << monthlyProductsSold << endl;

    outFile.close();

    cout << "Transaction saved successfully." << endl;
    cout << "Total Sales: " << Sales << endl;

    main();
}


void database()
{
    system("cls");

    int Month;
    cout << "Search Databases by Month" << endl;
    cout << "[1] - January \t\t" << "[7] - July" << endl;
    cout << "[2] - February \t\t" << "[8] - August" << endl;
    cout << "[3] - March \t\t" << "[9] - September" << endl;
    cout << "[4] - April \t\t" << "[10] - October" << endl;
    cout << "[5] - May \t\t" << "[11] - November" << endl;
    cout << "[6] - June \t\t" << "[12] - December" << endl;

    cout << "Enter Month: ";
    cin >> Month;

    if (Month < 1 || Month > 12) {
        cout << "Invalid Month!" << endl;
        return;
    }

    viewMonthDatabase(Month);
}

void viewMonthDatabase(int month)
{
    string monthFiles[] = {
        "Database/JanDatabase.txt", "Database/FebDatabase.txt", "Database/MarDatabase.txt",
        "Database/AprDatabase.txt", "Database/MayDatabase.txt", "Database/JunDatabase.txt",
        "Database/JulDatabase.txt", "Database/AugDatabase.txt", "Database/SepDatabase.txt",
        "Database/OctDatabase.txt", "Database/NovDatabase.txt", "Database/DecDatabase.txt"};

    ifstream monthFile(monthFiles[month - 1]);
    if (!monthFile) {
        cout << "Unable to open file for this month." << endl;
        return;
    }
    int CusNo, ProductChoice, Qnt, Sales, Price, monthlySales, monthlyProductsSold;
    string ProductName;

    DisplayDatabase();
    while (monthFile >> CusNo >> ProductName >> Qnt >> Price >> Sales >> monthlySales >> monthlyProductsSold) {
        cout << left  << "\t" << CusNo << "\t\t"  << setw(20) << ProductName  << Qnt << "\t\t" << Price << "\t\t" << Sales << endl;
    }
    monthFile.close();
    PauseDatabase();
}


void DisplayDatabase()
{
    system("CLS");
    cout << "Customer Database" << endl;
    cout << left << "Customer Number\t\t" << "Product\t\t" << "Quantity\t" << "Price\t\t" << "Sales" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------------------" << endl;
}

void PauseDatabase()
{
    system("pause");
    cin.get();
    main();
}

void exit()
{
    system("CLS");
    cout << "Logging Off The Program(press enter)..." << endl;
    cin.get();
}


void overview ()
{
    system ("cls");

    int choice;

    cout << "[1] - Monthly Overview" << endl;
    cout << "[2] - Yearly Overview" << endl;
    cout << "[3] - Compare Monthly Sales" << endl;

    cin >> choice;

    switch (choice)
    {
        case 1 : monthly (); break;
        case 2 : yearly (); break;
        case 3 : compare (); break;
    }
}
void monthly() {

    system("cls");

    int Month;
    cout << "Search Databases by Month" << endl;
    cout << "[1] - January \t\t" << "[7] - July" << endl;
    cout << "[2] - February \t\t" << "[8] - August" << endl;
    cout << "[3] - March \t\t" << "[9] - September" << endl;
    cout << "[4] - April \t\t" << "[10] - October" << endl;
    cout << "[5] - May \t\t" << "[11] - November" << endl;
    cout << "[6] - June \t\t" << "[12] - December" << endl;

    cout << "Enter Month: ";
    cin >> Month;

    if (Month < 1 || Month > 12) {
        cout << "Invalid Month!" << endl;
        return;
    }

    string monthFiles[] = {
        "Database/JanDatabase.txt", "Database/FebDatabase.txt", "Database/MarDatabase.txt",
        "Database/AprDatabase.txt", "Database/MayDatabase.txt", "Database/JunDatabase.txt",
        "Database/JulDatabase.txt", "Database/AugDatabase.txt", "Database/SepDatabase.txt",
        "Database/OctDatabase.txt", "Database/NovDatabase.txt", "Database/DecDatabase.txt"};

    ifstream inFile(monthFiles[Month - 1]);
    int lastCusNo = 0, monthlySales = 0, monthlyProductsSold = 0;
    string line;

    if (inFile) {
        while (getline(inFile, line)) {
            size_t spacePos = line.find(' ');
            int cusNo = stoi(line.substr(0, spacePos));
            lastCusNo = cusNo;

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

        system("cls");

        cout << "Last Customer Number: " << lastCusNo << endl;
        cout << "Monthly Sales: " << monthlySales << endl;
        cout << "Monthly Products Sold: " << monthlyProductsSold << endl;

    } else {
        cout << "No data available for the selected month." << endl;
    }

    system("pause");
    main();
}

void yearly() {
    system("cls");

    int totalCustomers = 0, totalSales = 0, totalProductsSold = 0;
    string monthFiles[] = {
        "Database/JanDatabase.txt", "Database/FebDatabase.txt", "Database/MarDatabase.txt",
        "Database/AprDatabase.txt", "Database/MayDatabase.txt", "Database/JunDatabase.txt",
        "Database/JulDatabase.txt", "Database/AugDatabase.txt", "Database/SepDatabase.txt",
        "Database/OctDatabase.txt", "Database/NovDatabase.txt", "Database/DecDatabase.txt"};

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


void compare ()
{
    
}
