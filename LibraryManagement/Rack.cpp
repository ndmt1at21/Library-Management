#include "Rack.h"

Rack::Rack() {}

Rack::Rack(std::string place)
{
	_place = place;
}

Rack::Rack(const Rack& other)
{
	_place = other._place;
}

Rack::~Rack() {}

std::string Rack::getPlace()
{
	return _place;
}

std::istream& operator>>(std::istream& in, Rack& rack)
{
	char ch;
	std::getline(in, rack._place, '\n');
	return in;
}

std::ostream& operator<<(std::ostream& out, const Rack rack)
{
	out << rack._place;
	return out;
}