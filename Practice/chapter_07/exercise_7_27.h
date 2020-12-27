#ifndef CP7_ex_7_27_h
#define CP7_ex_7_27_h

#include <string>
#include <iostream>

class Screen{
public:
	using pos = std::string::size_type;
	Screen() = default;
	Screen(pos ht, pos wd): height(ht), width(wd), contents(ht*wd, ' '){}
	Screen(pos ht, pos wd, char c): height(ht), width(wd), contents(ht*wd, c){}

	char get() const {return contents[cursor];}
	char get(pos r, pos c) const {return contents[r*width+c];}
	inline Screen &move(pos r, pos c);
	inline Screen &set(char c);
	inline Screen &set(pos r, pos col, char ch);

	Screen &display(std::ostream &os) {do_display(os); return *this;}
	const Screen &display(std::ostream &os) const {do_display(os); return *this;}
	
private:
	void do_display(std::ostream &os) const { os << contents;}	

private:
	pos cursor = 0;
	pos width = 0;
	pos height = 0;
	std::string contents;
};

inline Screen& Screen::move(pos r, pos c){
	cursor = r * width + c;
	return *this;
}

inline Screen& Screen::set(char c){
	contents[cursor] = c;
	return *this;
}

inline Screen& Screen::set(pos r, pos c, char ch){
	contents[r*width+c] = ch;
	return *this;
}

#endif
