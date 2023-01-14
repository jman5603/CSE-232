#include <iostream>
#include <math.h>
#include <cmath>
#include <string>
#include <iomanip>

using std::floor;
using std::string;
using std::stoi;
using std::stod;
using std::setprecision;
using std::abs;
using std::ceil;
using std::getline;
using std::round;

// converts the dollar amount from a double to a formatted string.
string dollarAmount(double const & balance)
{
    string stringBalance = "";
    if (balance < 0)
    {
        stringBalance += '-';
    }
    int newBalance = round(abs(balance) * 100);
    int pennies = newBalance % 100;
    int dollars = newBalance / 100;
    stringBalance += std::to_string(dollars) + '.';
    if (((pennies % 10) == 0) && (pennies < 10))
    {
        stringBalance += std::to_string(pennies) + '0';
    }
    else if (pennies < 10)
    {
        stringBalance += '0' + std::to_string(pennies);
    }
    else
    {
        stringBalance += std::to_string(pennies);
    }
    
    return stringBalance;
}

void deposit(double & balance, double const & amount)
{
    balance += amount;
}

bool withdraw(double & balance, double & amount)
{
    if (balance >= amount)
    {
        balance -= amount;
        return true;
    }
    return false;
}

void overdraft(double & balance, double const & amount)
{
    balance -= amount;
    balance -= 35;
}

double interest_for_month(double const & balance, double const & apr)
{
    double interest = balance * pow((1+((apr/100)/1)), (1));
    double interestTotal = interest - balance;
    double month = interestTotal / 12;
    return floor(month * 100.0) / 100.0;
}

void string_date_to_int_ptrs(string date, int *year, int *month, int *day)
{
    *year = stoi(date.substr(0,4));
    *month = stoi(date.substr(5,2));
    *day = stoi(date.substr(8,2));
}

void string_date_to_ints(string date, int &year, int &month, int &day)
{
    year = stoi(date.substr(0,4));
    month = stoi(date.substr(5,2));
    day = stoi(date.substr(8,2));
}

int number_of_first_of_months(string date1, string date2)
{
    int year1, month1, day1, year2, month2, day2;
    string_date_to_ints(date1, year1, month1, day1);
    string_date_to_ints(date2, year2, month2, day2);
    return (((year2 - year1)*12) + (month2 - month1));
}

double interest_earned(double balance, double const & apr, string const & begin, string const & end)
{
    int months = number_of_first_of_months(begin, end);
    double interestTotal = 0.0;
    for (int i = 0; i < months; i++)
    {
        double interest = interest_for_month(balance, apr);
        interestTotal += interest;
        balance += interest;
    }
    return interestTotal;
}

string process_command(string const & line, string & date1, double & balance, double const & apr)
{
    string date2 = line.substr(0,10);
    string command = line.substr(11);
    string returnString = "";
    double amount = stod(command.substr(command.find('$')+1));
    int months = 0;
    double interest = 0.0;
    if ((date1 != ""))
    {
        months = number_of_first_of_months(date1, date2);
        if (balance > 0)
        {
            interest += interest_earned(balance, apr, date1, date2);
            balance += interest_earned(balance, apr, date1, date2);
        }
    }
    if (command.find("Deposit") != string::npos)
    {
        if (months == 0)
        {
            deposit(balance, amount);
            date1 = date2;
            return ("On " + date2 + ": Instructed to perform \"" + command + "\"\nBalance: " + dollarAmount(balance) + "\n");
        }
        else
        {
        deposit(balance, amount);
        string returnString = "On " + date2 + ": Instructed to perform \"" + command + "\"\nSince " + date1 + ", interest has accrued " + 
        std::to_string(months) + " times.\n$" + dollarAmount(interest) + " interest has been earned.\nBalance: " + dollarAmount(balance) + "\n";
        date1 = date2;
        return returnString;
        }
    }

    else if (command.find("Withdraw") != string::npos)
    {
        if (months == 0)
        {
            if (balance < amount)
            {
                overdraft(balance, amount);
                date1 = date2;
                return ("On " + date2 + ": Instructed to perform \"" + command + "\"\nOverdraft!\nBalance: " + dollarAmount(balance) + "\n");
            }
            else
            {
                withdraw(balance, amount);
                date1 = date2;
                return ("On " + date2 + ": Instructed to perform \"" + command + "\"\nBalance: " + dollarAmount(balance) + "\n");
            }
        }
        else
        {
            if (balance < amount)
            {
                overdraft(balance, amount);
                string returnString = "On " + date2 + ": Instructed to perform \"" + command + "\"\nSince " + date1 + ", interest has accrued " + 
                    std::to_string(months) + " times.\n$" + dollarAmount(interest) + " interest has been earned.\nOverdraft!\nBalance: " + 
                    dollarAmount(balance) + "\n";
                date1 = date2;
                return returnString;
            }
            else
            {
                withdraw(balance, amount);
                string returnString = "On " + date2 + ": Instructed to perform \"" + command + "\"\nSince " + date1 + ", interest has accrued " + 
                    std::to_string(months) + " times.\n$" + dollarAmount(interest) + " interest has been earned.\nBalance: " + 
                    dollarAmount(balance) + "\n";
                date1 = date2;
                return returnString;
            }
        }
    }
}

string process_commands(string & input, double const & apr)
{
    double balance = 0.0;
    string date1 = "";
    string output = "";
    while (input.find('\n') != string::npos)
    {
        string command = input.substr(0, input.find('\n'));
        input.replace(0, input.find('\n') + 1, "");
        output += process_command(command, date1, balance, apr);
    }
    return output;
}

int main()
{
    // example chain of commands to be executed
    string line = "2016-09-03 Deposit $400.50\n";
    std::string input = 
    "2016-09-02 Deposit $600\n"
    "2016-09-02 Withdraw $23.54\n"
    "2016-09-04 Withdraw $58\n"
    "2016-11-02 Deposit $200\n"
    "2017-03-02 Withdraw $1200\n"
    "2019-11-02 Deposit $1500\n"
    "2020-03-02 Withdraw $100\n"
    "2021-03-02 Deposit $100\n";
    double apr = 7;

    string command = process_commands(input, apr);
    std::cout << command << std::endl;

    return 0;
}
