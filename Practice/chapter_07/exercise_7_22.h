#ifndef CP7_ex_07_22_h
#define CP7_ex_07_22_h

#include <string>

class Person{
	friend std::istream &read(std::istream &is, Person &person);
	friend std::ostream &print(std::ostream &os, const Person &person);

public:
	Person() = default;
	Person(std::string& sname, std::string &saddress):name(sname), address(saddress) { }
	Person(std::istream &is){ read(is, *this);}
	auto get_name() const -> std::string const& {return name;};
	auto get_addr() const -> std::string const& {return address;};

private:
	std::string name;
	std::string address;
};

std::ostream &print(std::ostream &os, const Person &person){
	os << person.name  << person.address;
	return os;
}

std::istream &read(std::istream &is, Person &person){
	is >> person.name >> person.address;
	return is;
}
#endif

