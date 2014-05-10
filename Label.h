#ifndef _LABEL_H
#define _LABEL_H

#include <iostream>
#include <sstream>
#include <string>

//followed example from three address code example
class Label {
    private:
	static unsigned next;
	const unsigned num;
    public:
	Label(void);
	std::string str() const { std::stringstream ss; ss << "L" << num; return ss.str(); }

};

inline std::ostream& operator<<(std::ostream& out, const Label& label) {
  out << label.str();
  return out;
}

#endif //LABEL_H
