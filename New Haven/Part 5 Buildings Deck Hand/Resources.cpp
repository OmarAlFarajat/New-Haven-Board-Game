#include "Resources.h"
#include <iostream>

using namespace std;

Resources::Resources() {
	cout << "Picking a random resource" << endl;

}

Resources::Resources(string value) {
	if (isValidValue(value)) {
		this->value = value;
		cout << "Successfully created a resource" << endl;
	}
	else {
		cout << "Value is not valid" << endl;
	}

}

bool Resources::isValidValue(string value) {
	return (find(begin(this->valid_values), end(this->valid_values), value) != end(this->valid_values));

}

