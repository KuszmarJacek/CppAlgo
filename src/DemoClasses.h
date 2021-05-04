#pragma once
#include <iostream>

class Foo
{
private:
	std::string name;

public:
	Foo(std::string _name) :
		a(0), name(_name)
	{};

	Foo(int _a, std::string _name) :
		a(_a), name(_name)
	{};

	std::string getName()
	{
		return name;
	}

	int a;

	friend bool operator==(const Foo& lhs, const Foo& rhs)
	{
		if(lhs.a == rhs.a)
		{
			return true;
		}

		return false;
	}

	friend std::ostream& operator<<(std::ostream& os, const Foo& foo)
	{
		os << foo.a << " " << foo.name << "\n";

		return os;
	}

	friend bool operator<(const Foo& lhs, const Foo& rhs)
	{
		return lhs.a < rhs.a;
	}

	friend bool operator>(const Foo& lhs, const Foo& rhs)
	{
		return operator<(rhs, lhs);
	}
};

class Bar
{
private:
	int a;
	char* b;
public:
	Bar(int i)
		: a{ i }
		, b{ new char('b') }
	{}

	int getA() const
	{
		return a;
	}

	char getB() const
	{
		return *b;
	}

	friend std::ostream& operator<<(std::ostream& out, const Bar& foo)
	{
		out << foo.getA() << foo.getB() << '\n';
		return out;
	}
};

