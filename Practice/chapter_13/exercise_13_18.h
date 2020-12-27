#ifndef CPP_PRIMER_EX_13_18_H
#define CPP_PRIMER_EX_13_18_H

#include <string>
using std::string;

class Employee{
public:
	Employee();
	Employee(const string &name);

	const int id() const {return id_;}

private:
	string name_;
	int id_;
	static int s_increment;
};

int Employee::s_increment = 0;

Employee::Employee(){
	id_ = s_increment++;
}

Employee::Employee(const string& name){
	id_ = s_increment++;
	name_ = name;
}

#endif
