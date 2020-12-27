#ifndef CP7_ex_7_41_h
#define CP7_ex_7_41_h

#include <iostream>
#include <string>

class Sales_data;


class Sales_data{
	friend Sales_data add(const Sales_data&, const Sales_data&);
	friend std::ostream &print(std::ostream&, const Sales_data&);
	friend std::istream &read(std::istream&, Sales_data&);

public:
	Sales_data(const std::string &s, unsigned n, double p):bookNo(s), units_sold(n), revenue(p*n){
		std::cout << "Sales_data(const std::string s, unsigned, double)" << std::endl;
	}

	Sales_data():Sales_data("", 0, 0.0f)
	{
		std::cout << "Sales_data()" << std::endl;
	}

	Sales_data(const std::string &s):Sales_data(s, 0, 0.0f)
	{
		std::cout << "Sales_data(const string&)" << std::endl;
	}

	Sales_data(std::istream &is);
	
	std::string isbn() const {return bookNo;};
	Sales_data &combine(const Sales_data &rhs);
private:
	inline double avg_price() const;

private:
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

inline double Sales_data::avg_price() const {
	return units_sold ? revenue / units_sold : 0;
}


#endif
