#ifndef CPP_PRIMER_EX_12_19_PTR_H
#define CPP_PRIMER_EX_12_19_PTR_H

#include "exercise_12_09.h"
#include <stdexcept>

using std::vector;
using std::string;

class StrBlob;

class StrBlobPtr{
public:
	StrBlobPtr(): curr(0) {}
	StrBlobPtr(StrBlob &a, size_t sz = 0): wptr(a.data), curr(sz){}

	bool operator!=(const StrBlobPtr &p){return p.curr != curr;}
	string &deref() const{
		auto p = check(curr, "dereference past end");
		return (*p)[curr];
	}
	StrBlobPtr& incr(){
		check(curr, "increment past end of StrBlobPtr");
		++curr;
		return *this;
	}

private:
	std::shared_ptr<vector<string>>check(size_t i, const string &msg)const{
		auto ret = wptr.lock();
		if (!ret)
			throw std::runtime_error("unbound StrBlobPtr");
		if (i >= ret->size())
			throw std::out_of_range(msg);
		return ret;
	}
	std::weak_ptr<vector<string>> wptr;
	size_t curr;
};

#endif
