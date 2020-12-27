#ifndef CPP_PRIMER_EX_12_02_H
#define CPP_PRIMER_EX_12_02_H

#include <vector>
#include <memory>
#include <string>
#include <initializer_list>
#include <exception>


class StrBlob{
public:
  	typedef std::vector<std::string>::size_type size_type;
  	StrBlob();
  	StrBlob(std::initializer_list<std::string> il);
  	size_type size() const {return data->size();}
  	bool empty() const {return data->empty();}
  	void push_back(const std::string &t) {data->push_back(t);}
  	void pop_back();
  	std::string &front();
  	std::string &back();
	const std::string &front() const;
	const std::string &back() const;

private:
  	std::shared_ptr<std::vector<std::string>> data;
  	void check(size_type i, const std::string &msg) const;
};

#endif
