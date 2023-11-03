#pragma once
#include <iostream>
#include <string>

#define READ_LINE(in, str) getline(in>>std::ws, str); cerr << str << endl;
#define LOAD_LINE(in, str) getline(in>>std::ws, str);

using namespace std;

class redirect_output_wrapper
{
	std::ostream& stream;
	std::streambuf* const old_buf;
public:
	redirect_output_wrapper(std::ostream& src)
		:old_buf(src.rdbuf()), stream(src)
	{
	}

	~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
	}
	void redirect(std::ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};

template <typename type>
type CorrectInput(type min, type max) {
	type item;
	while ((cin >> item).fail() || item < min || item > max) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Enter a value from " << min << " to " << max << ": ";
	}
	std::cerr << item << endl;
	return item;
}