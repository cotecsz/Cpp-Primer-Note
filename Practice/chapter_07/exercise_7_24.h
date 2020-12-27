#ifndef CP7_ex_7_24_h
#define CP7_ex_7_24_h

#include <string>

class Screen{
public:
	using pos = std::string::size_type;
	Screen() = default;
	Screen(pos ht, pos wd): height(ht), width(wd), contents(ht*wd, ' '){}
	Screen(pos ht, pos wd, char c): height(ht), width(wd), contents(ht*wd, c){}

	char get() const {return contents[cusor];}
	char get(pos r, pos c) const {return contents[r*width+c];}

private:
	pos cusor = 0;
	pos width = 0;
	pos height = 0;
	std::string contents;
};

#endif
