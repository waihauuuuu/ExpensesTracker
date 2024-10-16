#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

void Login();
void Registration();
void Forgot();
void Finance();
void Record();
void Edit();
void Delete();
void Display();
void Income();
void Expenses();
void PredictionE();

int main()
{
	int response;
	//Display option for user to choose
	cout << "==============================================================================\n\n";
	cout << "                           WELCOME TO LOGIN PAGE\n\n";
	cout << "==============================================================================\n\n";
	cout << "                           Press 1 | LOGIN\n";
	cout << "                           Press 2 | REGISTER\n";
	cout << "                           Press 3 | Forgot Password\n";
	cout << "                           Press 4 | EXIT\n\n";
	cout << "                           Please Select your choice: ";
	cin >> response;
	cout << "\n";

	//Switch Case
	switch (response)
	{
	case 1:			
		//Jump to login function
		system("cls");
		Login();
		break;
	case 2:
		//Jump to registration function
		system("cls");
		Registration();
		break;
	case 3:
		//Jump to forgot function
		system("cls");
		Forgot();
		break;
	case 4:
		//terminate programme
		cout << "                           THANK YOU!\n";
		break;
	default:
		//Error checking
		system("cls");
		cout << "\nInvalid input please enter again: " << endl;
		cin.clear();  //Clear the error flag
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //Discard invalid input
		main();
		break;
	}
}


void Finance()
{
	while (true)
	{
		int response;


		// Main Page loop that jumps between functions AFTER login()
		// Allow user to choose their function using numbers

		cout << "\n              Money Expense Tracker               " << endl;
		cout << "==================================================" << endl;
		cout << "Please choose a function below" << endl;
		cout << "1. Record a new input" << endl;
		cout << "2. Edit a record" << endl;
		cout << "3. Delete a record" << endl;
		cout << "4. Display a report" << endl;
		cout << "==================================================" << endl;
		cout << "Enter your function: ";
		cin >> response;

		//Jump to respective function
		//Save in Header Files???
		switch (response) {
		case 0:
			cout << "\nWhy is this happening???" << endl;
			system("CLS");
			continue;
		case 1:
			// Jump to Function Record()
			system("CLS");
			Record();
			break;
		case 2:
			system("CLS");
			Edit();
			break;
		case 3:
			system("CLS");
			Delete();
			break;
		case 4:
			system("CLS");
			Display();
			break;
		default:
		{
			//Error checking
			system("cls");
			cout << "\nInvalid input please enter again: " << endl << endl;
			cin.clear();  //Clear the error flag
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //Discard invalid input
			Finance();
			break;
		}
		}
	}
}

void Login()
{
	//Declare variables
	int Pass = 0;
	string User_ID, Password, Record_User_ID, Record_Password;
	//Prompt and get username and password
	cout << "Please enter the username and pasword:  " << endl;
	cout << "USERNAME: ";
	cin >> User_ID;
	cout << "PASSWORD: ";
	cin >> Password;
	cout << endl;

	//input username and password from login.txt
	ifstream input("login.txt");

	while (input >> Record_User_ID >> Record_Password)
	{
		if (Record_User_ID == User_ID && Record_Password == Password)
		{
			Pass = 1;
		}
	}
	input.close();

	//if username and password same as user id and password in login.txt
	if (Pass == 1)
	{
		//login successful
		system("cls");
		cout << "Login Sucessful!\n\n";
		Finance();

	}
	else
	{
		//login error
		system("cls");
		cout << "Login Error! \nPlease check your username and password.\n\n";
		Login();
	}
}

void Registration()
{
	//Declare variables
	string R_User_ID, R_Password, Record_User_ID, Record_Password;
	system("cls");
	//Prompt and get username and password
	cout << "Enter the username: ";
	cin >> R_User_ID;
	cout << "Enter the password: ";
	cin >> R_Password;

	//insert the username and password into login.txt
	ofstream f1("login.txt", ios::app);
	f1 << R_User_ID << " " << R_Password << endl;
	system("cls");
	cout << "Registration is successful! \n";
	main();
}

void Forgot()
{
	//Declare variable
	int option;
	system("cls");

	//Display option
	cout << "You forgot the password?\n";
	cout << "Press 1 | Search your ID by username" << endl;
	cout << "Press 2 | Main Menu" << endl;
	cout << "\nEnter your option: ";
	cin >> option;

	//Switch Case
	switch (option)
	{
		case 1:
		{
			//User enter the username they remembered
			int Pass = 0;
			string Record_User_ID, Record_Password, F_User_ID;
			cout << "\nEnter the username which you remebered: ";
			cin >> F_User_ID;

			ifstream f2("login.txt");
			while (f2 >> Record_User_ID >> Record_Password);
			{
				//if username same as username in login.txt
				if (F_User_ID == Record_User_ID)
				{
					Pass = 1;
				}
			}
			f2.close();
			if (Pass == 1)
			{
				//Display password
				cout << "\n\nYour account is found!";
				cout << "\nYour password: " << Record_Password << endl;
				main();
			}
			else
			{
				cout << "\n\nSorry! Your account is not found!\n";
				Forgot();
			}
			break;
		}
		case 2:
		{
			//back to main
			main();
		}
		default:
		{
			//Error checking
			system("cls");
			cout << "\nInvalid input please enter again: " << endl << endl;
			cin.clear();  //Clear the error flag
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //Discard invalid input
			Display();
			break;
		}
	}
}

int LineCount() {

	//open text file
	fstream file;
	string filename = "Record.txt";
	file.open(filename, ios::in);

	// Count the number of lines in the file
	int lineCount = 1;
	string line;
	while (getline(file, line)) {
		lineCount++;
	}
	file.close();

	return lineCount;
}

void Record() {

	system("CLS");

	// Variables for loop
	bool Exit = false;
	char Change_Date;

	time_t now = time(0);

	tm* ltm = localtime(&now);

	// Variables for User input

	string Date, Category, Note, InOrEx;
	float Amount;

	int year = (1900 + ltm->tm_year);
	int month = (1 + ltm->tm_mon);
	int day = (ltm->tm_mday);

	// Get user input for Date, Amount, Category and Note
	// Get a response on recording Income or Expenses or Exit?
	if (Exit == true) {

		// Display a message notifying the users they exited and jump back to main function selection page
		cout << "\n==================================================" << endl;
		cout << "You have choosen to exit the Record() Function" << endl;
		cout << "==================================================" << endl;
	}
	else
	{
		cout << "\n==================================================" << endl;
		cout << "Enter the following info to be recorded" << endl;
		cout << "==================================================" << endl;
		cout << "\nDate : " << year << "-" << month << "-" << day << " [Correct date?](Y/N) : ";
		cin >> Change_Date;

		// Cheack if users want to change the date. If so 
		if (Change_Date == 'Y' || Change_Date == 'y') {

			string temp = to_string(year) + "-" + to_string(month) + "-" + to_string(day);
			Date = temp;
		}
		else {
			cout << "You have chosen to change the date." << endl;
			cout << "Enter your Date (YYYY-MM-DD): ";
			cin >> Date;
		}

		cout << "\nAmount (RM): " << endl;
		cin >> Amount;

		// Category Income or Expenses
		// Cheack if users want to store as income or expenses
		cout << "\nCategory [Income or Expenses?](I/E): ";
		cin >> InOrEx;

		while (InOrEx != "I" && InOrEx != "i" && InOrEx != "E" && InOrEx != "e")
		{
			cout << "\nInvalid input, Choose between Income or Expenses (I/E): ";
			cin >> InOrEx;
		}

		if (InOrEx == "I" || InOrEx == "i") {
			Category = "Income";
		}
		else {
			Category = "Expenses";
		}

		cin.ignore(256, '\n');
		cout << "\nNote: " << endl;
		getline(cin, Note);
	}

	// Create or Open a text File

	// Open text file
	fstream file;
	string filename = "Record.txt";
	file.open(filename, ios::in | ios::out | ios::app);

	if (!file.is_open()) {
		//File doesn't exist, createa new file
		file.open(filename, ios::out);
		if (!file.is_open()) {
			std::cerr << "Failed to create or open the file." << endl;
		}
	}

	file << Date << " " << Amount << " " << Category << " " << Note << endl;
	system("cls");
	cout << "Adding...";

	// close file
	file.close();
	cout << "Record written into file" << endl;
}

// Function to split a string based on a delimiter
vector<string> split(const string& str, char delimiter) {
	vector<string> tokens;
	size_t start = 0, end = 0;
	while ((end = str.find(delimiter, start)) != string::npos) {
		tokens.push_back(str.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(str.substr(start));
	return tokens;
}

// Function for edit()
void Edit() {

	fstream file("Record.txt");
	// Show the array
	string Date, Category, Note;
	int Amount;
	int Count = 0;

	string tempAmount;
	string Line;

	// Print out Array
	cout << "\n==================================================" << endl;
	cout << "\t\tList of Records" << endl;
	cout << "==================================================" << endl;
	cout << "No." << "\t" << "Date" << "\t\t" << "Amount" << "\t" << "Category" << "\t" << "Note";

	while (getline(file, Line)) {
		stringstream ss(Line);
		getline(ss, Date, ' ');
		Date = Date.substr(0, 4) + "-" + Date.substr(5, 2) + "-" + Date.substr(8, 2);
		getline(ss, tempAmount, ' ');
		Amount = stoi(tempAmount);
		getline(ss, Category, ' ');
		getline(ss, Note);
		// The array itself
		cout << "\n" << (Count + 1) << std::left << Date << std::right << "     " << Amount << std::left << "     " << Category << "\t   " << Note << "\n";
		Count++;
	}
	file.close();


	// The User input
	string filename = "Record.txt"; // Replace with your file name
	int rowNumber, fieldIndex;
	string newValue;
	char InOrEx;

	cout << "\nEnter the record number to update: ";
	cin >> rowNumber;

	cout << "Enter the field index to update (1: Date, 2: Amount, 3: Category, 4: Note): ";
	cin >> fieldIndex;

	switch (fieldIndex) {
	case 1:
		cout << "\n Enter new date(YYYY-MM-DD) : ";
		cin.ignore(); // Clear the newline character from the buffer
		getline(cin, newValue);
		break;
	case 2:
		cout << "Enter new amount : ";
		cin.ignore();
		getline(cin, newValue);
		break;
	case 3:
		cout << "Change category to Income or Expenses(I/E) : ";
		cin >> InOrEx;
		if (InOrEx == 'I' || InOrEx == 'i') {
			newValue = "Income";
		}
		if (InOrEx == 'E' || InOrEx == 'e') {
			newValue = "Expenses";
		}
		break;
	case 4:
		cout << "Enter new Note: ";
		cin.ignore(); // Clear the newline character from the buffer
		getline(cin, newValue);
		break;
	}

	cout << newValue << endl;

	// THe Process 
	ifstream fileIn(filename);
	ofstream fileOut("temp.txt"); // Temporary file to store modified data

	if (!fileIn || !fileOut) {
		cerr << "Error opening files." << endl;
		return;
	}

	string line;
	int currentRow = 0;
	fieldIndex--;
	while (getline(fileIn, line)) {
		if (currentRow == (rowNumber - 1)) {
			vector<string> fields = split(line, ',');

			// Update the specified field
			if (fieldIndex >= 0 && fieldIndex < fields.size()) {
				fields[fieldIndex] = newValue;
			}
			else {
				cerr << "Invalid field index." << endl;
				return;
			}

			// Reconstruct the modified line
			string updatedLine = fields[0];
			for (size_t i = 1; i < fields.size(); ++i) {
				updatedLine += " " + fields[i];
			}

			fileOut << updatedLine << endl;
		}
		else {
			fileOut << line << endl;
		}

		currentRow++;
	}

	fileIn.close();
	fileOut.close();

	// Replace the original file with the temporary file
	remove(filename.c_str());
	rename("temp.txt", filename.c_str());

	cout << "Field updated successfully." << endl;
}

// Delete() Function
void Delete() {

	//Loop through file to get number of rows
	//Number of rows store into lineCount
	//get which column user want to delete = j
	//use array[lineCount][j] to find the position 

	// Open text file
	fstream file("Record.txt");
	/*string filename = "Record.txt";*/
	/*file.open(filename, ios::in);*/
	if (!file.is_open()) {
		cout << "No Data present";
		file.close();
	}
	else {

		string Date, Category, Note;
		int Amount;
		int Count = 0;

		string tempAmount;
		string Line;

		// Print out Array
		cout << "\n==================================================" << endl;
		cout << "\t\tList of Records" << endl;
		cout << "==================================================" << endl;
		cout << "No." << "\t" << "Date" << "\t\t" << "Amount" << "\t" << "Category" << "\t" << "Note";

		while (getline(file, Line)) {
			stringstream ss(Line);
			getline(ss, Date, ' ');
			Date = Date.substr(0, 4) + "-" + Date.substr(5, 2) + "-" + Date.substr(8, 2);
			getline(ss, tempAmount, ' ');
			Amount = stoi(tempAmount);
			getline(ss, Category, ' ');
			getline(ss, Note);
			// The array itself
			cout << "\n" << (Count + 1) << "\t" << Date << "\t\t" << Amount << "\t" << Category << "    " << Note;
			Count++;
		}
		file.close();
	}

	//Get user response on which record

	cout << "\n\nEnter the number of the following Record you would like to Delete : ";
	int ResponseNum;
	cin >> ResponseNum;

	// Delete a line
	fstream read_file;

	read_file.open("Record.txt");

	if (read_file.fail()) {
		cout << "Error opening file." << endl;
	}

	vector <string> lines;
	string line;

	while (getline(read_file, line))
		lines.push_back(line);

	read_file.close();

	if (ResponseNum > line.size()) {
		cout << "Line" << ResponseNum;
		cout << "not in file" << endl;

		cout << "File has " << lines.size();
		cout << "lines." << endl;

	}

	ofstream write_file;
	write_file.open("Record.txt");

	if (write_file.fail()) {
		cout << "Error opening file" << endl;
	}

	ResponseNum--;
	for (int i = 0; i < lines.size(); i++)
		if (i != ResponseNum)
			write_file << lines[i] << endl;

	write_file.close();
}


void Display()
{
	//Declare variable
	int option;
	//Display choice for user to choose to display
	cout << "Please select category to display: \n";
	cout << "1. Income\n";
	cout << "2. Expenses\n";
	cout << "3. Back\n\n";
	cout << "Please select your choice: ";
	cin >> option;
	switch (option)
	{
	case 1:
	{
		system("cls");
		Income();
		break;
	}
	case 2:
	{
		system("cls");
		Expenses();
		break;
	}
	case 3:
	{
		system("cls");
		Finance();
		break;
	}
	default:
	{
		//Error checking
		system("cls");
		cout << "\nInvalid input please enter again: " << endl << endl;
		cin.clear();  //Clear the error flag
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //Discard invalid input
		Display();
		break;
	}
	}
}

void Income()
{
	//Decclare variable
	int inner;
	//Display choice for user to choose
	cout << "You are displaying Income\n";
	cout << "1. Display via Date\n";
	cout << "2. Display Total\n";
	cout << "3. Back\n\n";
	cout << "Please select your choice: ";
	cin >> inner;
	switch (inner)
	{
	case 1:
	{
		system("cls");
		cout << "Display via Date:\n\n";
		//Declare variables
		time_t now = time(0);
		tm* ltm = localtime(&now);

		string back = ""; // to back to display menu
		int Pass = 0;
		char Change_Date;
		string DateStore;
		string Amount;
		string CategoryStore;
		string Note;
		string Date;
		string Category = "Income";
		int Count = 0;

		int year = (1900 + ltm->tm_year);
		int month = (1 + ltm->tm_mon);
		int day = (ltm->tm_mday);

		//Prompt and get date
		cout << "Date : " << year << "-" << month << "-" << day << " [Correct date?](Y/N) : ";
		cin >> Change_Date;
		// Cheack if users want to change the date. If so 
		if (Change_Date == 'Y' || Change_Date == 'y')
		{
			string temp = to_string(year) + "-" + to_string(month) + "-" + to_string(day);
			Date = temp;
		}
		else
		{
			cout << "\nYou have chosen to change the date." << endl;
			cout << "Enter your Date (YYYY-MM-DD): ";
			cin >> Date;
		}

		cout << "\n\n==================================================" << endl;
		cout << "\t\tList of Records" << endl;
		cout << "==================================================" << endl;
		cout << "No." << std::left << "      " << "Date" << std::right << "      " << "Amount" << std::left << "   " << "Category" << "\t   " << "Note\n";

		//Compare date and the date store in text file
		ifstream input("Record.txt");

		while (input >> DateStore >> Amount >> CategoryStore)
		{
			std::getline(input, Note);

			if (DateStore == Date && CategoryStore == Category)
			{
				Pass = 1;
			}

			if (Pass == 1)
			{
				//Display the income
				cout << std::left;
				cout << (Count + 1) << "     " << DateStore << "     " << Amount << "     " << Category << "\t   " << Note << "\n";
				Count++;
				Pass = 0;
			}
		}
		input.close();

		Pass = 2;
		if (Pass == 2)
		{
			//Case where no income is found for the date
			cout << "\nNo more income found for the specified date.\n\n";
		}

		do
		{
			// Ask the user whether to continue
			std::cout << "Back? (Y/N): ";
			std::cin >> back;

		} while (back != "Y" && back != "y");

		system("cls");
		Income();

		break;
	}
	case 2:
	{
		system("cls");
		cout << "Display Total:\n";
		//Declare variables
		string back = "";
		int Pass = 0;
		string DateStore;
		string Amount;
		string CategoryStore;
		string Note;
		float total = 0;
		string Category = "Income";
		int Count = 0;

		cout << "\n==================================================" << endl;
		cout << "\t\tList of Records" << endl;
		cout << "==================================================" << endl;
		cout << "No." << std::left << "      " << "Date" << std::right << "      " << "Amount" << std::left << "   " << "Category" << "\t   " << "Note\n";

		//Compare date and the date store in text file
		ifstream input("Record.txt");

		while (input >> DateStore >> Amount >> CategoryStore)
		{
			std::getline(input, Note);

			if (CategoryStore == Category)
			{
				//Display the income
				cout << (Count + 1) << std::left << DateStore << std::right << "     " << Amount << std::left << "     " << Category << "\t   " << Note << "\n";
				Count++;
				total += std::stof(Amount);
			}
		}
		input.close();

		cout << "\nTotal of Income: RM" << std::fixed << std::setprecision(2) << total << "\n\n";

		do
		{
			// Ask the user whether to continue
			std::cout << "Back? (Y/N): ";
			std::cin >> back;

		} while (back != "Y" && back != "y");

		system("cls");
		Income();
		break;
	}
	case 4:
	{
		system("cls");
		Display();
		break;
	}
	default:
	{
		//Error checking
		system("cls");
		cout << "\nInvalid input please enter again: " << endl << endl;
		cin.clear();  //Clear the error flag
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //Discard invalid input
		Income();
		break;
	}
	}
}

void Expenses()
{
	//Decclare variable
	int inner;

	//Display choice for user to choose
	cout << "You are displaying Expenses\n";
	cout << "1. Display via Date\n";
	cout << "2. Display Total\n";
	cout << "3. Display Prediction\n";
	cout << "4. Back\n\n";
	cout << "Please select your choice: ";
	cin >> inner;
	cout << "\n";
	switch (inner)
	{
	case 1:
	{
		system("cls");
		cout << "Display via Date:\n\n";
		//Declare variables
		time_t now = time(0);
		tm* ltm = localtime(&now);

		string back = "";
		int Pass = 0;
		char Change_Date;
		string DateStore;
		string Amount;
		string CategoryStore;
		string Note;
		string Date;
		string Category = "Expenses";
		int Count = 0;

		int year = (1900 + ltm->tm_year);
		int month = (1 + ltm->tm_mon);
		int day = (ltm->tm_mday);

		//Prompt and get date
		cout << "\nDate: " << year << "-" << month << "-" << day << " [Correct date?](Y/N) : ";
		cin >> Change_Date;
		// Cheack if users want to change the date. If so 
		if (Change_Date == 'Y' || Change_Date == 'y')
		{
			string temp = to_string(year) + "-" + to_string(month) + "-" + to_string(day);
			Date = temp;
		}
		else
		{
			cout << "\nYou have chosen to change the date." << endl;
			cout << "Enter your Date (YYYY-MM-DD): ";
			cin >> Date;
		}

		cout << "\n\n==================================================" << endl;
		cout << "\t\tList of Records" << endl;
		cout << "==================================================" << endl;
		cout << "No." << std::left << "      " << "Date" << std::right << "      " << "Amount" << std::left << "   " << "Category" << "\t   " << "Note\n";

		//Compare date and the date store in text file
		ifstream input("Record.txt");

		while (input >> DateStore >> Amount >> CategoryStore)
		{
			std::getline(input, Note);

			if (DateStore == Date && CategoryStore == Category)
			{
				Pass = 1;
			}

			if (Pass == 1)
			{
				//Display the expenses
				cout << (Count + 1) << std::left << Date << std::right << "     " << Amount << std::left << "     " << Category << "\t   " << Note << "\n";
				Count++;
				Pass = 0;
			}
		}
		input.close();

		Pass = 2;
		if (Pass == 2)
		{
			//Case where no expenses is found for the date
			cout << "\nNo more income found for the specified date.\n";
		}

		do
		{
			// Ask the user whether to continue
			std::cout << "Back? (Y/N): ";
			std::cin >> back;

		} while (back != "Y" && back != "y");

		system("cls");
		Expenses();

		break;
	}
	case 2:
	{
		system("cls");
		cout << "Display Total:\n";

		//Declare variables
		string back = "";
		int Pass = 0;
		string DateStore;
		string Amount;
		string CategoryStore;
		string Note;
		float total = 0;
		string Category = "Expenses";
		int Count = 0;

		cout << "\n==================================================" << endl;
		cout << "\t\tList of Records" << endl;
		cout << "==================================================" << endl;
		cout << "No." << std::left << "      " << "Date" << std::right << "      " << "Amount" << std::left << "   " << "Category" << "\t   " << "Note\n";

		//Compare date and the date store in text file
		ifstream input("Record.txt");

		while (input >> DateStore >> Amount >> CategoryStore)
		{
			std::getline(input, Note);

			if (CategoryStore == Category)
			{
				//Display the expenses
				cout << (Count + 1) << std::left << DateStore << std::right << "     " << Amount << std::left << "     " << Category << "\t   " << Note << "\n";
				Count++;
				total += std::stof(Amount);

			}
		}
		input.close();

		cout << "\nTotal of Expenses: RM" << std::fixed << std::setprecision(2) << total << "\n\n";

		do
		{
			// Ask the user whether to continue
			std::cout << "Back? (Y/N): ";
			std::cin >> back;

		} while (back != "Y" && back != "y");

		system("cls");
		Expenses();

		break;
	}
	case 3:
	{
		PredictionE();
		break;
	}
	case 4:
	{
		system("cls");
		Display();
		break;
	}
	default:
	{
		//Error checking
		system("cls");
		cout << "\nInvalid input please enter again: " << endl << endl;
		cin.clear();  //Clear the error flag
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //Discard invalid input
		Expenses();
		break;
	}
	}
}

void PredictionE()
{
	system("cls");
	cout << "Display Prediction:\n\n";
	//Declare variables
	time_t now = time(0);
	tm* ltm = localtime(&now);

	string back = "";
	int Pass = 0;
	string DateStore;
	string Amount;
	string CategoryStore;
	string Note;
	string Date;
	string predict;
	string Category = "Expenses";
	int option;

	int year = (1900 + ltm->tm_year);
	int month = (1 + ltm->tm_mon);
	int day = (ltm->tm_mday);

	cout << "1. Daily\n";
	cout << "2. Monthly\n";
	cout << "3. Annually\n";
	cout << "4. Back\n\n";
	cout << "Please select your choice: ";
	cin >> option;

	switch (option)
	{
	case 1:
	{
		int month;
		float i = 0;
		float sum = 0.0f;
		float average;
		string SMonth;
		int Count = 0;
		cout << "\nPlease select a month (1 to 12): \n";
		cout << "1.  January\n";
		cout << "2.  February\n";
		cout << "3.  March\n";
		cout << "4.  April\n";
		cout << "5.  May\n";
		cout << "6.  June\n";
		cout << "7.  July\n";
		cout << "8.  August\n";
		cout << "9.  September\n";
		cout << "10. October\n";
		cout << "11. November\n";
		cout << "12. December\n\n";
		cout << "Please select your choice: ";
		cin >> month;

		switch (month)
		{
		case 1:
		{
			SMonth = "01";
			break;
		}
		case 2:
		{
			SMonth = "02";
			break;
		}
		case 3:
		{
			SMonth = "03";
			break;
		}
		case 4:
		{
			SMonth = "04";
			break;
		}
		case 5:
		{
			SMonth = "05";
			break;
		}
		case 6:
		{
			SMonth = "06";
			break;
		}
		case 7:
		{
			SMonth = "07";
			break;
		}
		case 8:
		{
			SMonth = "08";
			break;
		}
		case 9:
		{
			SMonth = "09";
			break;
		}
		case 10:
		{
			SMonth = "10";
			break;
		}
		case 11:
		{
			SMonth = "11";
			break;
		}
		case 12:
		{
			SMonth = "12";
			break;
		}
		default:
		{
			//Error checking
			system("cls");
			cout << "\nInvalid input please enter again: " << endl << endl;
			cin.clear();  //Clear the error flag
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //Discard invalid input
			Expenses();
			break;
		}
		}

		cout << "\n\n==================================================" << endl;
		cout << "\t\tList of Records" << endl;
		cout << "==================================================" << endl;
		cout << std::left;
		cout << setw(10) << "No." << setw(10) << "Date" << setw(10) << "Amount" << setw(10) << "Category" << setw(10) << "Note\n";

		string MonthStore;

		//Compare date and the date store in text file
		ifstream input("Record.txt");

		while (input >> DateStore >> Amount >> CategoryStore)
		{
			std::getline(input, Note);

			std::string MonthStore = DateStore.substr(5, 2); //Extract month

			if (CategoryStore == Category && MonthStore == SMonth)
			{
				Pass = 1;
			}

			if (Pass == 1)
			{
				//Display the prediction
				cout << std::left;
				cout << setw(10) << (Count + 1) << setw(10) << " " << DateStore << " " << setw(10) << Amount << setw(10) << Category << setw(10) << Note << "\n";
				Count++;
				sum += stof(Amount);
				Pass = 0;
				i += 1;
			}
		}
		input.close();

		average = sum / i;
		cout << "\nYou have used RM" << std::fixed << std::setprecision(2) << sum << " in month(" << SMonth << ")";
		cout << "\nPrediction for next day: RM" << std::fixed << std::setprecision(2) << average << "\n\n";

		do
		{
			// Ask the user whether to continue
			std::cout << "Back? (Y/N): ";
			std::cin >> back;

		} while (back != "Y" && back != "y");

		system("cls");
		PredictionE();

		break;
	}
	case 2:
	{
		string MonthStore;
		string SYear;
		string YearStore;
		float monthly[12] = { 0.0f };
		float sum = 0.0f;
		float average;
		int Count = 0;

		cout << "\nPlease insert a year: ";
		cin >> SYear;

		cout << "\n\n==================================================" << endl;
		cout << "\t\tList of Records" << endl;
		cout << "==================================================" << endl;
		cout << "No." << std::left << "      " << "Date" << std::right << "      " << "Amount" << std::left << "   " << "Category" << "\t   " << "Note\n";

		//Compare date and the date store in text file
		ifstream input("Record.txt");

		while (input >> DateStore >> Amount >> CategoryStore)
		{
			std::getline(input, Note);

			std::string YearStore = DateStore.substr(0, 4); //Extract year
			std::string MonthStore = DateStore.substr(5, 2); //Extract month

			for (int j = 1; j <= 12; j++)
			{
				if (CategoryStore == Category && stoi(MonthStore) == j && YearStore == SYear)
				{
					Pass = 1;
				}

				if (Pass == 1)
				{
					//Display the prediction
					cout << (Count + 1) << std::left << DateStore << std::right << "     " << Amount << std::left << "     " << Category << "\t   " << Note << "\n";
					Count++;
					monthly[j] += stof(Amount);
					Pass = 0;
				}
			}
		}
		input.close();

		cout << "\n";

		for (int k = 1; k < 13; k++)
		{
			cout << "Month (" << k << "): RM" << monthly[k] << endl;
			sum += monthly[k];
		}

		average = sum / 12;
		cout << "\nPrediction for next month: RM" << std::fixed << std::setprecision(2) << average << "\n\n";

		do
		{
			// Ask the user whether to continue
			std::cout << "Back? (Y/N): ";
			std::cin >> back;

		} while (back != "Y" && back != "y");

		system("cls");
		PredictionE();
			
		break;
	}
	case 3:
	{
		int Year1;
		int Year2;
		int range = 0;
		int Count = 0;

		//Range of Year to Predict
		cout << "\nRange of year to predict next year expenses\n";
		cout << "Please insert the starting year: ";
		cin >> Year1;
		cout << "Until?: ";
		cin >> Year2;
		if (Year2 > Year1)
		{
			range = Year2 - Year1;
		}
		else
		{
			system("cls");
			cout << "\nSecond Year must larger than First Year provided!";
			PredictionE();

		}

		float annual[10000] = { 0.0f };
		int tempYear = Year1;
		float sum = 0.0f;
		float average = 0;

		//Compare date and the date store in text file
		ifstream input("Record.txt");


		for (int j = 0; j <= range; j++)
		{
			//Reset file pointer to the beginning for each year
			input.clear(); //Clear any error flags
			input.seekg(0, ios::beg);

			while (input >> DateStore >> Amount >> CategoryStore)
			{
				std::getline(input, Note);

				string YearStore = DateStore.substr(0, 4); //Extract year

				if (CategoryStore == Category && stoi(YearStore) == tempYear)
				{
					Pass = 1;
				}

				if (Pass == 1)
				{
					//Display the prediction
					Count++;
					annual[j] += stof(Amount);
					Pass = 0;
				}
			}

			if (tempYear != Year2)
			{
				tempYear += 1;
			}
			else
			{
				break;
			}
		}
		input.close();

		cout << "\n";
		tempYear = Year1;

		for (int k = 0; k <= range; k++)
		{
			cout << "Year " << tempYear << ": RM" << annual[k] << endl;
			sum += annual[k];
			if (tempYear != Year2)
			{
				tempYear += 1;
			}
		}

		average = sum / (range + 1);
		cout << "\nPrediction for next year: RM" << std::fixed << std::setprecision(2) << average << "\n\n";

		do
		{
			// Ask the user whether to continue
			std::cout << "Back? (Y/N): ";
			std::cin >> back;

		} while (back != "Y" && back != "y");

		system("cls");
		PredictionE();

		break;
	}
	case 4:
	{
		system("cls");
		Display();
	}
	default:
	{
		//Error checking
		system("cls");
		cout << "\nInvalid input please enter again: " << endl << endl;
		cin.clear();  //Clear the error flag
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //Discard invalid input
		Expenses();
		break;
	}
	}	
}