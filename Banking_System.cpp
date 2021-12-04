#include <iostream>
#include <stdlib.h>
#include <map>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <windows.h>

#define B_MAG "\x1B[45m"
#define MAG "\x1B[35m"
#define BLU "\x1B[34m"
#define B_BLU "\x1B[44m"
#define B_RED "\x1B[41;1m"
#define RED "\x1B[31;1m"
#define RE "\x1B[31m"
#define B_CYAN "\x1B[46m"
#define CYAN "\x1B[36m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define RESET "\x1B[0m"
#define BOLD "\x1B[1m"

using namespace std;

class Account
{
private:
    long accountNumber;
    string firstName;
    string lastName;
    float balance;
    static long NextAccountNumber;

public:
    Account() {}
    Account(string fname, string lname, float balance);
    long getAccNo() { return accountNumber; }
    string getFirstName() { return firstName; }
    string getLastName() { return lastName; }
    float getBalance() { return balance; }
    void Deposit(float amount);
    void Withdraw(float amount);
    static void setLastAccountNumber(long accountNumber);
    static long getLastAccountNumber();
    friend ofstream &operator<<(ofstream &ofs, Account &acc);
    friend ifstream &operator>>(ifstream &ifs, Account &acc);
    friend ostream &operator<<(ostream &os, Account &acc);
};
long Account::NextAccountNumber = 0;
class Bank
{
private:
    map<long, Account> accounts;

public:
    Bank();
    Account OpenAccount(string fname, string lname, float balance);
    Account BalanceEnquiry(long accountNumber);
    Account Deposit(long accountNumber, float amount);
    Account Withdraw(long accountNumber, float amount);
    void CloseAccount(long accountNumber);
    void ShowAllAccounts();
    ~Bank();
};
int main()
{
    Bank b;
    Account acc;
    int choice;
    string fname, lname;
    long accountNumber;
    float balance;
    float amount;
    int pin;
    time_t tt;
    struct tm *ti;
    time(&tt);
    ti = localtime(&tt);
    cout << "\n  " << asctime(ti) << setw(50);

    cout << setw(50) << "***" MAG "Banking System" RESET "***" << endl;
    cout << setw(65) << "Object Oriented Programming Project Submission" << endl;
    cout << setw(60) << "Made by: EN20CS301165 Harshpratap Singh" << endl;
    cout << setw(30);
    cout << "------------------------------------------------------------------------" << endl;
    Sleep(750);
    do
    {
        cout << "\n\tSelect one option below ";
        cout << "\n\t1 <- Open an Account";
        cout << "\n\t2 <- Balance Enquiry";
        cout << "\n\t3 <- Deposit";
        cout << "\n\t4 <- Withdrawal";
        cout << "\n\t5 <- Close an Account";
        cout << "\n\t6 <- Show All Accounts (For Bank staff only)";
        cout << "\n\t7 <- Quit";
        cout << "\n\t8 <- Help";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "\nEnter First Name: ";
            cin >> fname;
            cout << "Enter Last Name: ";
            cin >> lname;
            cout << "Enter initial Balance: ";
            cin >> balance;

            acc = b.OpenAccount(fname, lname, balance);
            cout << "\n" GRN "Congratulations! Account is Created" RESET " " << endl;
            cout << acc;
            system("pause");
            break;
        case 2:
            cout << "Enter Account Number: ";

            cin >> accountNumber;

            acc = b.BalanceEnquiry(accountNumber);
            cout << endl
                 << "Your Account Details: " << endl;
            cout << acc;
            system("pause");
            break;
        case 3:
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            cout << "Enter Amount: ";
            cin >> amount;

            acc = b.Deposit(accountNumber, amount);
            cout << endl
                 << " " GRN "Amount is Deposited!" RESET " " << endl;
            cout << acc;
            system("pause");
            break;
        case 4:
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            cout << "Enter Amount: ";
            cin >> amount;

            acc = b.Withdraw(accountNumber, amount);
            cout << acc;
            system("pause");
            break;
        case 5:
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            b.CloseAccount(accountNumber);
            cout << endl
                 << " " GRN "Account is Closed!" RESET " " << endl;
            cout << acc;
            system("pause");
            break;
        case 6:
            int key;
            cout << "Enter the key: ";
            cin >> key;
            if (key == 78936)
            {
                b.ShowAllAccounts();
            }
            else
            {
                cout << " " RED "Incorrect key!" RESET " " << endl;
            }
            system("pause");

            break;
        case 7:
            break;
        case 8:
            system("cmd /c start https://www.google.com/webhp?hl=en&sa=X&ved=0ahUKEwjy8qyOhp_0AhU663MBHUZmC44QPAgI/");
            break;
        default:
            cout << " " CYAN "\nPlease enter a valid choice" RESET " ";
            exit(0);
        }
    } while (choice != 7);
    return 0;
}
Account::Account(string fname, string lname, float balance)
{
    NextAccountNumber++;
    accountNumber = NextAccountNumber;
    firstName = fname;
    lastName = lname;
    this->balance = balance;
}
void Account::Deposit(float amount)
{
    balance += amount;
}
void Account::Withdraw(float amount)
{
    if (balance - amount < 0)
        cout << " " RED "Not enough amount present in your account to complete ths transaction" RESET " " << endl;
    else
    {
        balance -= amount;
        cout << endl
             << " " GRN "Amount Withdrawn!" RESET " " << endl;
    }
}
void Account::setLastAccountNumber(long accountNumber)
{
    NextAccountNumber = accountNumber;
}
long Account::getLastAccountNumber()
{
    return NextAccountNumber;
}
ofstream &operator<<(ofstream &ofs, Account &acc)
{
    ofs << acc.accountNumber << endl;
    ofs << acc.firstName << endl;
    ofs << acc.lastName << endl;
    ofs << acc.balance << endl;
    return ofs;
}
ifstream &operator>>(ifstream &ifs, Account &acc)
{
    ifs >> acc.accountNumber;
    ifs >> acc.firstName;
    ifs >> acc.lastName;
    ifs >> acc.balance;
    return ifs;
}
ostream &operator<<(ostream &os, Account &acc)
{
    os << "\t\tFirst Name:" << acc.getFirstName() << endl;
    os << "\t\tLast Name:" << acc.getLastName() << endl;
    os << "\t\tAccount Number:" << acc.getAccNo() << endl;
    os << "\t\tBalance:" << acc.getBalance() << endl;
    return os;
}
Bank::Bank()
{
    Account account;
    ifstream infile;

    infile.open("File.data");
    if (!infile)
    {
        cout << "Error in Opening! File Not Found!!" << endl;
        return;
    }
    while (!infile.eof())
    {
        infile >> account;
        accounts.insert(pair<long, Account>(account.getAccNo(), account));
    }
    Account::setLastAccountNumber(account.getAccNo());
    infile.close();
}
Account Bank::OpenAccount(string fname, string lname, float balance)
{
    ofstream outfile;
    Account account(fname, lname, balance);
    accounts.insert(pair<long, Account>(account.getAccNo(), account));
    outfile.open("File.data", ios::trunc);
    map<long, Account>::iterator itr;
    for (itr = accounts.begin(); itr != accounts.end(); itr++)
    {
        outfile << itr->second;
    }
    outfile.close();
    return account;
}
Account Bank::BalanceEnquiry(long accountNumber)
{
    map<long, Account>::iterator itr = accounts.find(accountNumber);
    return itr->second;
}
Account Bank::Deposit(long accountNumber, float amount)
{
    map<long, Account>::iterator itr = accounts.find(accountNumber);
    itr->second.Deposit(amount);
    return itr->second;
}
Account Bank::Withdraw(long accountNumber, float amount)
{
    map<long, Account>::iterator itr = accounts.find(accountNumber);
    itr->second.Withdraw(amount);
    return itr->second;
}
void Bank::CloseAccount(long accountNumber)
{
    map<long, Account>::iterator itr = accounts.find(accountNumber);
    cout << "Account Deleted" << itr->second;
    accounts.erase(accountNumber);
}
void Bank::ShowAllAccounts()
{
    map<long, Account>::iterator itr;
    for (itr = accounts.begin(); itr != accounts.end(); itr++)
    {
        cout << "Account " << itr->first << endl
             << itr->second << endl;
    }
}
Bank::~Bank()
{

    ofstream outfile;
    outfile.open("File.data", ios::trunc);
    map<long, Account>::iterator itr;
    for (itr = accounts.begin(); itr != accounts.end(); itr++)
    {
        outfile << itr->second;
    }
    outfile.close();
}
