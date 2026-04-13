#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;


const string filename = "DataBaseBank";

struct sclient
{
	string acount_number;
	string pincode;
	string name;
	string phone;
	double acount_balance = 0;
	bool markof_delet = false;
};

/////////////////////////الدوال المشتركه هنا اااااااااااالسلام عليكم يا دوال مشتركه هههههه////////////////
///هنحط ده عشان هو مش شايفها عشان هيا تحت 



// ===== Forward Declarations =====
sclient convertLineToStrust(string line, string delim = "#//#");
bool check_acountnumberistrue(string acountnumber, vector<sclient>& vclient, sclient& client);
double calcTotalBalances(vector<sclient> vclient);





// داله استخراج الدتا من الملف اكتر واحده مهمه يعتبر 
vector<sclient>vloaddatainfile(string filename)//كان ممكن هنا مش اعرف البراميتر ده عشان هو متعرف علي الداله كلها فوق ولكن عرفتو عشان سهوله الفهم لو هرجع لككود بعدين 
{
	vector<sclient>vclient;
	fstream myfile;
	myfile.open(filename, ios::in);
	if (myfile.is_open())
	{
		string line;
		while (getline(myfile, line))
		{
			vclient.push_back(convertLineToStrust(line));//هنا احنا عاوزين نحط في الفيكتور الدتا كا استركشر عشان سهوله الاستخراج والبحث وتكون البنات واضحه فا هتروح نحول السطر ال استخرجناه الي داتا استركشر 
		}
		myfile.close();
	}
	return vclient;
}

// داله تحويل السطر الي كلمات 
vector<string>vsplitstring(string line, string delim)//واحد يسال هنا ليه عملنا الفيكتور استرينج عشان يا معلم البيانات اصلا كلها استرينج 
{
	vector<string>vstring;
	string world = "";
	int pos = 0;
	while ((pos = line.find(delim)) != string::npos)
	{
		world = line.substr(0, pos);
		if (world != "")
		{
			vstring.push_back(world);
		}
		line.erase(0, pos + delim.length());// في رايي ده اهم سطر في الكود ده اصلا مش تعضيه كدا 
	}
	if (line != "")
	{
		vstring.push_back(line);
	}
	return vstring;
}

// يلا داله تحويل السطر ال داتا 
sclient convertLineToStrust(string line, string delim )
{
	sclient client;
	vector<string>vstring = vsplitstring(line, delim);//ده استدعاء داله 
	client.acount_number = vstring[0];
	client.pincode = vstring[1];
	client.name = vstring[2];
	client.phone = vstring[3];
	client.acount_balance = stod(vstring[4]); // اكيد مش محتاج اعرفك ليه صح 
	return client;
}

//يلا بقا داله تحويل الدتا ال سطر 
string convertDataToLine(sclient client, string delim = "#//#")// ان عارف ان اهنا بيحصل لبس كتير لمغظم الناس لان احنا مسيمين مغظم المتغيرات كدا sclient clientولكن عاوزك تفهم با صديقي المتغير ده اسمه لكل داتا محلي مش جولوبل يعني ال هيوصل هنا ال انت عاوز توصله ال هو عم تطلب من المستخدم يدخل البنات  مثلا ده ال هيدخل هنا مش حجاه تانيه اتمني تكون فاهمني 
{
	return
		client.acount_number + delim
		+ client.pincode + delim
		+ client.name + delim
		+ client.phone + delim
		+ to_string(client.acount_balance);
}

// داله تخزين السطور في الملف ////////
void addDataLineToFile(string filename, string linedata)
{
	fstream myfile;
	myfile.open(filename, ios::out | ios::app);
	if (myfile.is_open())
	{
		myfile << linedata << endl;
		myfile.close();
	}
}

// داله حزف جميع الداتا من الفيل وملي تاني //////////
void DeletDataAndSaveAgain(string filename, vector<sclient>vclient)
{
	fstream myfile;
	myfile.open(filename, ios::out);
	if (myfile.is_open())
	{
		/// هنا بنعمل لوب ونرجع نكتب الداتا تاني بعد ما نحذف
		for (sclient C : vclient)
		{
			if (C.markof_delet == false)
			{
				myfile << convertDataToLine(C) << endl;
			}
		}
		myfile.close();
	}
}

// داله add ///
// اول حاجه سؤال ال العميل يدخل الداتا ////

sclient read_out()
{
	sclient client;
	vector<sclient> vclient = vloaddatainfile(filename); // ← حمّل الداتا
	sclient temp; // ← مؤقت للداله

	cin.ignore();
	cout << "enter acount number ? ";
	getline(cin, client.acount_number);

	// ← زود الـ while هنا
	while (check_acountnumberistrue(client.acount_number, vclient, temp))
	{
		cout << "\nNumber [" << client.acount_number << "] already exists, Enter another? ";
		getline(cin, client.acount_number);
	}

	cout << "Enter PinCode? ";
	getline(cin, client.pincode);
	cout << "Enter Name? ";
	getline(cin, client.name);
	cout << "Enter Phone? ";
	getline(cin, client.phone);
	cout << "Enter AccountBalance? ";
	cin >> client.acount_balance;
	cin.ignore();
	return client;
}

void MadeOpearteAdd()
{
	sclient client = read_out();
	addDataLineToFile(filename, convertDataToLine(client));// هنا بنضيف الداتا في الملف 
}

void addnewclient()
{
	char check = 'y';
	do
	{
		system("cls");
		cout << "Adding New Client:\n\n";
		MadeOpearteAdd();
		cout << "\nClient Added Successfully, do you want to add more? Y/N? ";
		cin >> check;
	} while (check == 'y' || check == 'Y');
}

// عرض العملاء ////////////////////////
void PrintDataClient(sclient client)
{
	cout << "| " << setw(15) << left << client.acount_number;
	cout << "| " << setw(10) << left << client.pincode;
	cout << "| " << setw(40) << left << client.name;
	cout << "| " << setw(12) << left << client.phone;
	cout << "| " << setw(12) << left << client.acount_balance;
}

void printDesinData(vector<sclient>vclient)
{
	cout << "\n\t\t Client List (" << vclient.size() << ") Client(s).\n";
	cout << string(90, '_') << "\n\n";

	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(10) << left << "Pin Code";
	cout << "| " << setw(40) << left << "Client Name";
	cout << "| " << setw(12) << left << "Phone";
	cout << "| " << setw(12) << left << "Balance";

	cout << "\n" << string(90, '_') << "\n\n";

	for (sclient c : vclient)
	{
		PrintDataClient(c);
		cout << endl;
	}
}

void ShowClient()
{
	vector<sclient>vclient = vloaddatainfile(filename);
	printDesinData(vclient);
}

// دال البحث /////////////////////////
bool check_acountnumberistrue(string acountnumber, vector<sclient>& vclient, sclient& client)
{
	for (sclient& c : vclient)
	{
		if (c.acount_number == acountnumber)
		{
			client = c;
			return true;
		}
	}
	return false;
}

void PrintClientCard(sclient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "\nAccount Number : " << Client.acount_number;
	cout << "\nPin Code       : " << Client.pincode;
	cout << "\nName           : " << Client.name;
	cout << "\nPhone          : " << Client.phone;
	cout << "\nAccount Balance: " << Client.acount_balance;
}

void search()
{
	vector<sclient>vclient = vloaddatainfile(filename);

	string acountnumber;
	cout << "entert the acount number you want to show data ? ";
	cin >> acountnumber;

	sclient client;

	if (check_acountnumberistrue(acountnumber, vclient, client))
	{
		PrintClientCard(client);
	}
	else
		cout << "\nClient with Account Number Not Found!";
}

// داله الحذف /////////////////////////
bool markdeletclient(string acountnumber, vector<sclient>& vclient)
{
	for (sclient& c : vclient)
	{
		if (c.acount_number == acountnumber)
		{
			c.markof_delet = true;
			return true;
		}
	}
	return false;
}

void delet()
{
	vector<sclient>vclient = vloaddatainfile(filename);

	string acountnumber;
	cout << "entert the acount number you want to delete ? ";
	cin >> acountnumber;

	sclient client;

	if (check_acountnumberistrue(acountnumber, vclient, client))
	{
		PrintClientCard(client);

		char Answer;
		cout << "\nAre you sure? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			markdeletclient(acountnumber, vclient);
			DeletDataAndSaveAgain(filename, vclient);
			vclient = vloaddatainfile(filename); //هنا بعمل ريفرش للداتا بمهني بخلي الفيكتور ياخد الدتا تاني من الاول من الملف بعد التعديلات 
			cout << "\nClient Deleted Successfully.";
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << acountnumber << ") Not Found!"; 
	}
}

// داله تعديل /////////////////////////
sclient ChangeClientRecord(string acountnumber)
{
	sclient client;
	client.acount_number = acountnumber;

	cout << "Enter PinCode? ";
	getline(cin, client.pincode);
	cout << "Enter Name? ";
	getline(cin, client.name);
	cout << "Enter Phone? ";
	getline(cin, client.phone);
	cout << "Enter AccountBalance? ";
	cin >> client.acount_balance;
	cin.ignore();
	return client;
}
void updata_data()
{
	vector<sclient> vclient = vloaddatainfile(filename);

	string acountnumber;
	cout << "enter account number you want to update ? ";
	cin >> acountnumber;

	bool found = false;
	bool updated = false; // ← زيادة	 

	for (sclient& c : vclient)
	{
		if (c.acount_number == acountnumber)
		{
			found = true;

			PrintClientCard(c);

			char Answer;
			cout << "\nAre you sure? Y/N? ";
			cin >> Answer;

			if (toupper(Answer) == 'Y')
			{
				cin.ignore();
				c = ChangeClientRecord(acountnumber);
				updated = true; // ← سجّل إن في تعديل فعلي
				cout << "\nClient Updated Successfully.\n";
			}
			break;
		}
	}

	if (updated) // ← بس احفظ لو في تعديل فعلي
		DeletDataAndSaveAgain(filename, vclient);
	else if (!found)
		cout << "\nClient not found!\n";
}
// دوال التحويلات يلا بيناااااااا/////
void depost()
{
	vector<sclient> vclient = vloaddatainfile(filename);

	string acountnumber;
	cout << "enter account number you want to deposit? ";
	cin >> acountnumber;

	sclient client;
	while (!check_acountnumberistrue(acountnumber, vclient, client))
	{
		cout << "\nNot found! Enter another account number: ";
		cin >> acountnumber;
	}

	PrintClientCard(client);

	char Answer;
	cout << "\nAre you sure? Y/N? ";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		double amount;
		cout << "Enter deposit amount? ";
		cin >> amount;

		for (sclient& c : vclient)
		{
			if (c.acount_number == acountnumber)
			{
				c.acount_balance += amount;
				DeletDataAndSaveAgain(filename, vclient);
				cout << "\nDeposit successful! New Balance: " << c.acount_balance << "\n";
				break;
			}
		}
	}
}

void withdraw()
{
	vector<sclient> vclient = vloaddatainfile(filename);

	string acountnumber;
	cout << "enter account number you want to withdraw? ";
	cin >> acountnumber;

	sclient client;
	while (!check_acountnumberistrue(acountnumber, vclient, client))
	{
		cout << "\nNot found! Enter another account number: ";
		cin >> acountnumber;
	}

	PrintClientCard(client);

	char Answer;
	cout << "\nAre you sure? Y/N? ";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		double amount;
		cout << "Enter withdraw amount? ";
		cin >> amount;

		while (amount > client.acount_balance)
		{
			cout << "\nAmount exceeds balance! Max you can withdraw: "
				 << client.acount_balance << "\n";
			cout << "Enter another amount? ";
			cin >> amount;
		}

		for (sclient& c : vclient)
		{
			if (c.acount_number == acountnumber)
			{
				c.acount_balance -= amount;
				DeletDataAndSaveAgain(filename, vclient);
				cout << "\nWithdraw successful! New Balance: " << c.acount_balance << "\n";
				break;
			}
		}
	}
}

//داله عرض total balance ///////////////

void PrintTotalbalance(sclient client)
{
	cout << "| " << setw(15) << left << client.acount_number;
	cout << "| " << setw(40) << left << client.name;
	cout << "| " << setw(12) << left << client.acount_balance;
}

void printDesinbalance(vector<sclient> vclient)
{
	cout << "\n\t\t Balances List (" << vclient.size() << ") Client(s).\n";
	cout << string(70, '_') << "\n\n";

	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(40) << left << "Client Name";
	cout << "| " << setw(12) << left << "Balance";

	cout << "\n" << string(70, '_') << "\n\n";

	for (sclient c : vclient)
	{
		PrintTotalbalance(c);
		cout << endl;
	}

	cout << string(70, '_') << "\n";
	cout << "\n\t\t Total Balances = " << calcTotalBalances(vclient) << "\n"; // ← السطر ده بس
}
double calcTotalBalances(vector<sclient> vclient)
{
	double total = 0;
	for (sclient c : vclient)
		total += c.acount_balance;
	return total;
}


// ========================================
// Enums
// ========================================
enum enMainMenuChoice
{
	eShowClientList = 1,
	eAddNewClient = 2,
	eDeleteClient = 3,
	eUpdateClientInfo = 4,
	eFindClient = 5,
	eTransactions = 6,
	eExit = 7
};

enum enTransactionsMenuChoice
{
	eDeposit = 1,
	eWithdraw = 2,
	eTotalBalances = 3,
	eMainMenu = 4
};

// ========================================
// Transactions Sub-Menu
// ========================================
void ShowTotalBalances()
{
	vector<sclient> vclient = vloaddatainfile(filename);
	printDesinbalance(vclient);
}

enTransactionsMenuChoice readTransactionsMenu()
{
	int choice;
	cout << "\n" << string(50, '=') << "\n";
	cout << "\t\tTransactions Menue Screen\n";
	cout << string(50, '=') << "\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	cout << string(50, '=') << "\n";
	cout << "Choose what do you want to do? [1 to 4]? ";
	cin >> choice;
	return (enTransactionsMenuChoice)choice;
}

void TransactionsMenu()
{
	enTransactionsMenuChoice choice;
	do
	{
		system("cls");
		choice = readTransactionsMenu();
		switch (choice)
		{
		case eDeposit:
			depost();
			system("pause>0");
			break;
		case eWithdraw:
			withdraw();
			system("pause>0");
			break;
		case eTotalBalances:
			ShowTotalBalances();
			system("pause>0"); 
			break;
		case eMainMenu:
			break;
		}
	} while (choice != eMainMenu);
}

// ========================================
// Main Menu
// ========================================
enMainMenuChoice readMainMenu()
{
	int choice;
	do
	{
		cout << "\n" << string(50, '=') << "\n";
		cout << "\t\tMain Menue Screen\n";
		cout << string(50, '=') << "\n";
		cout << "\t[1] Show Client List.\n";
		cout << "\t[2] Add New Client.\n";
		cout << "\t[3] Delete Client.\n";
		cout << "\t[4] Update Client Info.\n";
		cout << "\t[5] Find Client.\n";
		cout << "\t[6] Transactions.\n";
		cout << "\t[7] Exit.\n";
		cout << string(50, '=') << "\n";
		cout << "Choose what do you want to do? [1 to 7]? ";
		cin >> choice;

		if (choice < 1 || choice > 7)
			cout << "\nInvalid choice! Please enter [1 to 7].\n";

	} while (choice < 1 || choice > 7); // ← كرر لو خارج النطاق

	return (enMainMenuChoice)choice;
}
int main()
{
	enMainMenuChoice choice;
	do
	{
		system("cls");
		choice = readMainMenu();
		switch (choice)
		{                                                                                                                                   
		case eShowClientList:
			ShowClient();
			system("pause>0");
			break;
		case eAddNewClient:
			addnewclient();
			system("pause>0");
			break;
		case eDeleteClient:
			delet();
			system("pause>0");                                          
			break;
		case eUpdateClientInfo:
			updata_data();                                                                                                      
			system("pause>0");                                                                
			break;
		case eFindClient:
			search();
			system("pause>0");
			break;
		case eTransactions:
			TransactionsMenu(); // ← بيفتح السب منيو
			break;
		case eExit:
			cout << "\nGoodbye!\n"; 
			break;
		}
	} while (choice != eExit);

	return 0;
}
