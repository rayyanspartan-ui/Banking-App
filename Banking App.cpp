
#include <iostream>
#include <map>
#include <fstream>
#include <exception>

using namespace std;

class Account
{
private:
	string firstName;
	string lastName;
	long AccountNo;
	float balance;
	static long default_Number;
public:
	Account();
	Account(string f, string l, float b);
	string getFname();
	string getLname();
	long getAccNo();
	float getBal();

	void Deposit(float depAm);
	void Withdraw(float withAm);
	static void setAccountNumber(long AccNo);
	static long getPrevNo();
	friend ofstream& operator<<(ofstream& ofs, Account &acc);
	friend ifstream& operator>>(ifstream& ifs, Account& acc);
	friend ostream& operator<<(ostream& os, Account& acc);
};
long Account::default_Number = 0;

class Bank
{
private:
	map<long, Account> accounts;
public:
	Bank();
	Account OpenAcc(string f, string l, float b);
	Account BalEnq(long a);
	Account Deposit(long accno, float amount);
	Account Withdraw(long accno, float amount);
	void CloseAcc(long accno);
	void ShowAll();
	~Bank();
};


int main()
{
	Bank b;
	Account acc;
	string f, n;
	long accno;
	float bal;
	int choice;
	float ammount;


	do
	{

		cout << "*****Welcome to you rbanking home page*****" << endl;
		cout << "Menu:" << endl;
		cout << "1. Open an account" << endl;
		cout << "2. Retrieve your balance" << endl;
		cout << "3. Make a deposit" << endl;
		cout << "4. Make a withdrawal" << endl;
		cout << "5. Close an account" << endl;
		cout << "6. Display all accounts" << endl;
		cout << "7. Quit" << endl;
		cout << "Please enter the option you would like to select: " << endl;
		cin >> choice;

		switch (choice) 
		{
			case 1:
				cout << "Please enter your first name: " << endl;
				cin >> f;
				cout << "Please enter your last name: " << endl;
				cin >> n;
				cout << "Please enter the balance you would like to open with: " << endl;
				cin >> bal;
				acc = b.OpenAcc(f, n, bal);
				cout << "Account created" << endl;
				cout << acc << endl;
				break;

			case 2:
				cout << "Please enter your account number: " << endl;
				cin >> accno;
				acc = b.BalEnq(accno);
				cout << acc << endl;
				break;

			case 3:
				cout << "Please enter your account number: " << endl;
				cin >> accno;
				cout << "Please enter the amount you want to deposit: " << endl;
				cin >> ammount;
				acc = b.Deposit(accno, ammount);
				cout << "New balance: " << acc << endl;
				break;
			
			case 4:
				cout << "Please enter your account number: " << endl;
				cin >> accno;
				cout << "Please enter the amount you want to withdraw: " << endl;
				cin >> ammount;
				acc = b.Withdraw(accno, ammount);
				cout << "New balance: " << acc << endl;
				break;
			
			case 5:
				cout << "Please enter your account number: " << endl;
				cin >> accno;
				b.CloseAcc(accno);
				cout << "Account closed" << endl;
				break;


			case 6:
				b.ShowAll();
				break;

			case 7: 
				break;
			default:
				cout << "\nEnter correct choice" << endl;
				exit(0);
		}

	} while (choice != 7);

	return 0;
}

//Implementation of Account class methods:
Account::Account(){};

Account::Account(string f, string l, float b) 
{
	firstName = f;
	lastName = l;
	balance = b;
	default_Number++;
	AccountNo = default_Number;
}
string Account:: getFname()
{
	return firstName;
}
string Account::getLname()
{
	return lastName;
}
long Account::getAccNo()
{
	return AccountNo;
}
float Account::getBal()
{
	return balance;
}
void Account::Deposit(float depAm)
{
	balance += depAm;
}
void Account::Withdraw(float withAm) 
{
	if (withAm > balance)
	{
		throw runtime_error("Insufficient funds");
	}
	balance -= withAm;
}
void Account::setAccountNumber(long AccNo)
{
	default_Number = AccNo;
}
long Account::getPrevNo()
{
	return default_Number;
}
ofstream& operator<<(ofstream& ofs, Account& acc)
{
	ofs << acc.AccountNo << endl;
	ofs << acc.firstName << endl;
	ofs << acc.lastName << endl;
	ofs << acc.balance << endl;
	return ofs;
}
ifstream& operator>>(ifstream& ifs, Account& acc) 
{
	ifs >> acc.AccountNo >> acc.firstName >> acc.lastName >> acc.balance;
	return ifs;
}
ostream& operator<<(ostream& os, Account& acc)
{
	os << "Account No: " << acc.getAccNo() << endl;
	os << "First name: " << acc.getFname() << endl;
	os << "Last name: " << acc.getLname() << endl;
	os << "Balance: " << acc.getBal() << endl;
	return os;
}

////Implementation of Bank class methods:

Bank::Bank()
{
	Account account;
	ifstream infile("Bank.txt");
	long maxID = 0;

	accounts.clear();

	if (!infile)
	{
		 Account::setAccountNumber(0); 
		 return;
	}

	map<long, Account>::iterator itr;

	while (infile >> account)
	{
		long id = account.getAccNo();

		if (accounts.find(id) != accounts.end())
		{
			throw runtime_error("Duplicate account number found");
		}

		for (itr = accounts.begin(); itr != accounts.end(); itr++) 
		{
			if (itr->second.getFname() == account.getFname() && itr->second.getLname() == account.getLname())
			{
				throw runtime_error(string("Duplicate account holder found with name: ") + account.getFname() + " " + account.getLname());
			}
		}

		accounts.insert(pair<long, Account>(id, account));

		if (id > maxID) 
		{
			maxID = id;
		}
	}
	Account::setAccountNumber(maxID);
	infile.close();
}
Account Bank::OpenAcc(string f, string l, float b) 
{
	Account account(f, l, b);
	ofstream outfile;

	long id = account.getAccNo();

	map<long, Account>::iterator itr;
	
	if (accounts.find(id) != accounts.end())
	{
		throw runtime_error("Duplicate account number found");
	}

	for (itr = accounts.begin(); itr != accounts.end(); itr++)
	{
		if (itr->second.getFname() == f && itr->second.getLname() == l)
		{
			throw runtime_error("Duplicate account holder found with name: " + f + " " + l);
		}
	}

	accounts.insert(pair<long, Account>(id, account));
	outfile.open("Bank.txt", ios::app);
	if (!outfile)
	{
		throw runtime_error("Unable to open file");
	}
	outfile << account;
	outfile.close();

	return account;
}
Account Bank::BalEnq(long accno) {
	map<long, Account>::iterator itr = accounts.find(accno);
	return itr->second;
}
Account Bank::Deposit(long accno, float amount)
{
	map<long, Account>::iterator itr = accounts.find(accno);
	itr->second.Deposit(amount);
	return itr->second;
}
Account Bank::Withdraw(long accno, float amount)
{
	map<long, Account>::iterator itr = accounts.find(accno);
	itr->second.Withdraw(amount);
	return itr->second;
}
void Bank::CloseAcc(long accno) 
{
	map<long, Account>::iterator itr = accounts.find(accno);
	accounts.erase(itr);
	cout << "Account deleted";
}
void Bank::ShowAll()
{
	map<long, Account>::iterator itr;
	for (itr = accounts.begin(); itr != accounts.end(); itr++)
	{
		cout << itr->first << endl << itr->second << endl;
	}
}

Bank::~Bank()
{
	ofstream outfile;
	outfile.open("Bank.txt", ios::trunc);
	map<long, Account>::iterator itr;
	for (itr = accounts.begin(); itr != accounts.end(); itr++)
	{
		outfile << itr->second;
	}
	outfile.close();
}