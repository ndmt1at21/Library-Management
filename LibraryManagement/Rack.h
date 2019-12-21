#pragma once
#include <iostream>
#include <string>

class Rack
{
private:
	std::string _place;

public:
	Rack();
	Rack(std::string place);
	Rack(const Rack& other);
	~Rack();

	std::string getPlace();
	friend std::istream& operator>>(std::istream& in, Rack& rack);
	friend std::ostream& operator<<(std::ostream& out, const Rack rack);
};

