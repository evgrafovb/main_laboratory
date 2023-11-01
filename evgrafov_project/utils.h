#pragma once
#include <iostream>
#include <string>

#define READ_LINE(in, str) getline(in>>std::ws, str);

using namespace std;

template <typename type>
type CorrectInput(type min, type max) {
	type item;
	while ((cin >> item).fail() || item < min || item > max) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Enter a value from " << min << " to " << max << ": ";
	}
	return item;
}
