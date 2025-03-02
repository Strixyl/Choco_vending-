#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

struct Vending {
    string chocoName;
    float chocoPrice;
    int chocoStock;
    int chocoCode;
};

void first(struct Vending[], float &);
void customer(struct Vending[], float &);
void purchase(struct Vending[], int, float &);
void admin(struct Vending[]);

int main(int argc, char** argv) {
    ifstream input1, input2, input3, input4;
    ofstream output, output2;

    input1.open("chocoName.txt");
    input2.open("chocoPrice.txt");
    input3.open("chocoStock.txt");
    input4.open("chocoCode.txt");
    output.open("outputfile.txt");

    if (!input1 || !input2 || !input3 || !input4 || !output) {
        cerr << "Failed to load and open one or more files" << endl;
        return 1;
    }

    const int SIZE = 8;
    Vending choco[SIZE];
    float collectedCash = 0;

    for (int i = 0; i < SIZE; i++) {
        input1 >> choco[i].chocoName;
        input2 >> choco[i].chocoPrice;
        input3 >> choco[i].chocoStock;
        input4 >> choco[i].chocoCode;
    }

    first(choco, collectedCash);

    input1.close();
    input2.close();
    input3.close();
    input4.close();

    output << "Total pesos collected: Php" << fixed << setprecision(2) << collectedCash << endl << endl;
    output2.open("chocoStock.txt");
    for (int i = 0; i < SIZE; i++) {
        output << choco[i].chocoName << " - " << choco[i].chocoStock << " left." << endl;
        output2 << choco[i].chocoStock << endl;
    }
    output2.close();
    output.close();

    return 0;
}

void first(struct Vending choco[], float &moneycollected) {
    int choice;
    char choice2;

    cout << "<<<<<<<<<<< ChocoMojo Vending Machine >>>>>>>>>>>" << endl << endl;
    cout << "\n";
    cout << "\n";
    cout << "Are you an admin(0) or a customer (1)?" << endl << "(Enter '0' or '1'): ";
    cout << "\n";
    cout << "\n";
    cin >> choice;
    string id;
    if (choice == 0) {
        do {
            cout << "Enter the admin's password: ";
            cin >> id;
            if (id == "42069") {
                admin(choco);
            } else {
                cout << "Wrong password, please try again" << endl;
            }
        } while (id != "42069");
    } else if (choice == 1) {
        cout << "Would you like to purchase a chocolate? (Y-Yes/N-No): ";
        cin >> choice2;
        choice2 = toupper(choice2);
        if (choice2 == 'Y') {
            do {
                customer(choco, moneycollected);
                cout << endl << "Would you like to continue? (Y-Yes/N-No): ";
                cin >> choice2;
                choice2 = toupper(choice2);
            } while (choice2 == 'Y');
        }
    }
}

void customer(struct Vending choco[], float &moneyCollected) {
    cout << endl << "Code" << setw(13) << "Price" << setw(20) << "Chocolate" << setw(15) << "Quantity" << endl << endl;
    for (int i = 0; i < 8; i++) {
        cout << choco[i].chocoCode << setw(10) << "Peso" << fixed << setprecision(2) << choco[i].chocoPrice << setw(20) << choco[i].chocoName << setw(10) << choco[i].chocoStock << endl;
    }
    int code;

    cout << endl << "Enter the chocolate code: ";
    cin >> code;
    for (int j = 0; j < 8; j++) {
        if (code == choco[j].chocoCode) {
            if (choco[j].chocoStock != 0) {
                purchase(choco, j, moneyCollected);
            } else {
                cout << "Out of Stock!";
                break;
            }
        }
    }
}

void purchase(struct Vending choco[], int i, float &moneyCollected) {
    float money, moneyBal, collected;
    do {
        cout << endl << "Choco: " << choco[i].chocoName << endl << "Price: Peso" << choco[i].chocoPrice << endl;
        cout << "Enter an Amount (We only accept 100, 200 and 500 pesos bills): ";
        cin >> money;

        if (money < choco[i].chocoPrice || money > 500 || money < 100) {
            cout << "Invalid Amount!" << endl;
        } else {
            moneyBal = money - choco[i].chocoPrice;
            cout << endl << "Your Balance: Peso" << moneyBal;
            choco[i].chocoStock -= 1;
            collected = money - moneyBal;
            moneyCollected += collected;
        }
    } while (money < choco[i].chocoPrice || money > 500 || money < 100);
}

void admin(struct Vending choco[]) {
    int code2, stock;
    cout << endl;
    for (int i = 0; i < 8; i++) {
        cout << choco[i].chocoCode << setw(10) << "Peso" << fixed << setprecision(2) << choco[i].chocoPrice << setw(20) << choco[i].chocoName << setw(10) << choco[i].chocoStock << endl;
    }
    cout << endl << "Enter the chocolate code that needs to be restocked: ";
    cin >> code2;
    for (int j = 0; j < 8; j++) {
        if (code2 == choco[j].chocoCode) {
            cout << "Enter the amount you want to add: ";
            cin >> stock;
            choco[j].chocoStock += stock;
        }
    }
    cout << endl;
    for (int i = 0; i < 8; i++) {
        cout << choco[i].chocoCode << setw(10) << "Peso" << fixed << setprecision(2) << choco[i].chocoPrice << setw(20) << choco[i].chocoName << setw(10) << choco[i].chocoStock << endl;
    }
}