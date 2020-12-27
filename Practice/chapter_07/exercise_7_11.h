#ifndef CP7_ex_7_11_h
#define CP7_ex_7_11_h

#include <iostream>
#include <string>

class Sales_data{
	friend Sales_data add(const Sales_data&, const Sales_data&);
	friend std::ostream &print(std::ostream&, const Sales_data&);
	friend std::istream &read(std::istream&, const Sales_data&);
public:
	Sales_data() = default;
	Sales_data(const std::string s):bookNo(s){ }
	Sales_data(const std::string s, unsigned n, double p):
				bookNo(s), units_sold(n), revenue(p*n){ }
	Sales_data(std::istream &is);
	
	std::string isbn() const {return bookNo;};
	Sales_data &combine(const Sales_data &rhs);
private:
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

Sales_data &Sales_data::combine(const Sales_data &rhs){
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

std::istream &read(std::istream &is, Sales_data &item){
  	double price = 0;
  	is >> item.bookNo >> item.units_sold >> price;
  	item.revenue = price * item.units_sold;
  	return is;
}

Sales_data::Sales_data(std::istream &is){
	read(is, *this);
}

std::ostream &print(std::ostream &os, Sales_data &item){
  	os << item.isbn() << " " << item.units_sold << " " 
       << item.revenue;
  	return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs){
  	Sales_data sum = lhs;
  	sum.combine(rhs);
  	return sum;
}

#endif
