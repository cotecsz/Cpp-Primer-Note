#ifndef CP7_ex_07_05_h
#define CP7_ex_07_05_h

#include <string>

struct Person;
std::istream &read(std::istream &is, Person &person);

struct Person{
	Person() = default;
	Person(std::string& sname, std::string &saddress):name(sname), address(saddress) { }
	Person(std::istream &is){ read(is, *this);}

	std::string name;
	std::string address;

	auto get_name() const -> std::string const& {return name;};
	auto get_addr() const -> std::string const& {return address;};
};

std::istream &read(std::istream &is, Person &person){
	return is >> person.name >> person.address;
}

std::ostream &print(std::ostream &os, const Person &person){
	os << person.name << " " << person.address;
	return os;
}

std::istream &read(std::istream &is, Person person){
	is >> person.name >> person.address;
	return is;
}
#endif

