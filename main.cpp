#include <iostream>
#include <cassert>
#include <string> 
#include <vector>
#include <fstream>
#include <map>
#include "Todo.h"
using namespace std;


/* The map has keys as buckets and values as pointers to
	vectors of Todo pointers(the Todo objects are dynamically
	allocated) */

void storeItem(map<string, vector<Todo*>*>& b,Todo* taskitem);
void Menu(map<string, vector<Todo*>*>& b);
Todo* userInput(const map<string, vector<Todo*>*>& b);
void printItems(const map<string, vector<Todo*>*>& b);
void printBuckets(const map<string, vector<Todo*>* >& b);
void importBuckets(map<string, vector<Todo*>* >& b);
void storeBuckets(map<string, vector<Todo*>* >& b);
void importTodo(map<string, vector<Todo*>*>& b);
void storeTodo(map<string, vector<Todo*>*>& b);

int main()
{
	map<string, vector<Todo*>* > buckets;
	importBuckets(buckets);
	importTodo(buckets);
	Menu(buckets);
	for(auto i = buckets.begin(); i != buckets.end(); ++i)
	{
		for(auto j = i->second->begin(); j != i->second->end(); ++i)
			delete *j;	//deleting todo instances
		delete i->second; //deleting map values using iter
	}
	storeBuckets(buckets);
	storeTodo(buckets);
	return 0;
}


void Menu(map<string, vector<Todo*>* >& b)
{
	while (true)
	{
		cout << "\nWelcome to the Planner App\
				\n1) Create To Do\
				\n2) View To Do\
				\n3) Create Buckets\
        		\n4) Delete Todos\
				\n5) View Buckets\
				\n6) Exit Program" << endl;
		string menuOption;
		cin >> menuOption;
		cin.ignore();
		cout << endl;
		if (menuOption == "6")
			break;
		else if(menuOption == "5")
		{
			int counter = 1;
			for(auto i = b.begin(); i != b.end(); ++i)
			{
				cout << counter << ". " << i->first << endl;
				++counter;
			}
		}
		else if (menuOption == "3")
		{
			cout << "Please enter the name of the new bucket: ";
			string temp;
			getline(cin, temp);
			b[temp] = new vector<Todo*>;
		}
		else if (menuOption == "2") {
			printItems(b);
		}
		else if (menuOption == "1"){
			Todo* temp = userInput(b);
			storeItem(b,temp);
		}

	}
}


Todo* userInput(const map<string, vector<Todo*>* >& b)
{
	string task,date,bucket;
  	int num;
	string bucketChoice;
	
	cout << "Please enter task: " << endl;
	getline(cin, task,'\n');
	cout << "Please enter date mmdd: " << endl;
	cin >> date;
	cin.ignore();
	if(b.empty())
	{
		cout << "You have not made any buckets yet." << endl;
		return nullptr;
	}
	cout << "Please enter bucket name to place this item in: " << endl;

	printBuckets(b);
	cin >> bucketChoice;
	cin.ignore();

	Todo* temp = new Todo(task,date,bucketChoice);
	return temp;

}


void storeItem(map<string, vector<Todo*>*>& b,Todo* taskitem) // & passing it in by reference, manipulating it directly
{
	b[taskitem->returnBuckets()]->push_back(taskitem);
}

void printItems(const map<string, vector<Todo*>*>& b)
{

	for(auto i = b.begin(); i != b.end(); ++i)
	{
		if(i->second->empty())
			continue;
		int count = 1;
		cout << "Bucket: " << i->first << endl;
		for(auto j = (i->second)->begin(); j != (i->second)->end(); ++j)
		{
			cout << "*** " << count << " ***" <<"\nTask: " << (*j)->returnTask() << "\nDate: " << (*j)->returnDate() << endl;
			++count;
		}
		cout << endl;
	}
	return;
}

void printBuckets(const map<string, vector<Todo*>*>& b)
{
	int count = 1;
	for(auto i = b.begin(); i != b.end(); ++i)
	{
		cout << count << ". " << i->first << endl;
		++count;
	}
	return;
}


void importBuckets(map<string, vector<Todo*>*>& b)
{
	string tempBucket;
	ifstream inFile; // creating an instance of of infile
	inFile.open("buckets.txt");
	while(getline(inFile, tempBucket, '\n'))
	{
		vector<Todo*>* temp = new vector<Todo*>;
		b[tempBucket] = temp;
	}
	return;
}

void storeBuckets(map<string, vector<Todo*>*>& b)
{
	ofstream outFile;
	outFile.open("buckets.txt");
	for(auto i = b.begin(); i != b.end(); ++i)
		outFile << i->first << endl;
}

void importTodo(map<string, vector<Todo*>*>& b)
{
	string name, date, bucket;
	ifstream inFile;
	inFile.open("storage.txt");
	while(getline(inFile,name, '\n'))
	{
		getline(inFile, date, '\n');
		getline(inFile, bucket, '\n');
		Todo* temp = new Todo(name,date,bucket);
		b[bucket]->push_back(temp);
	}
}

void storeTodo(map<string, vector<Todo*>*>& b)
{
	ofstream outFile;
	outFile.open("storage.txt");
	for(auto i = b.begin(); i != b.end(); ++i)
	{
		for(auto j = (i->second)->begin(); j != (i->second)->end(); ++j)
		{
			outFile << (*j)->returnTask() << endl << (*j)->returnDate() << endl << (*j)->returnBuckets() << endl;
		}
	}
}