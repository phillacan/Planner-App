#ifndef TODO_H
#define TODO_H

#include <iostream>
#include <string>
using namespace std;
class Todo
{
	private:
		string task;
		string date;
		string buckets;
	public:
		Todo(string t, string d, string b): //c'tor initialization list
		task(t), date(d), buckets(b) {}		
		string returnTask() const
		{
			return task;
		}
		
		string returnDate() const{
			return date;
		}

		string returnBuckets() const
		{
			return buckets;
		}
};

#endif