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
	std::getline(in, rack._place, '\n');
	return in;
}

std::ostream& operator<<(std::ostream& out, const Rack rack)
{
	out << rack._place;
	return out;
}

void Rack::showPlace()
{
	std::cout << "Vi tri sach luu duoi dang: day.tang-vi tri" << std::endl;
	std::cout << "Vi du: 1.2-5" << std::endl;
	std::cout << "1: day thu nhat" << std::endl;
	std::cout << "2: tang thu 2 trong day" << std::endl;
	std::cout << "5: vi tri thu 5 trong tang do" << std::endl;
}