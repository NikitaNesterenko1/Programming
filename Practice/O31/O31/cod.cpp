#include <iostream>
#include <vector>
#include <fstream>

std::ostream& operator<< (std::ostream& stream, std::vector<int>& vec) {
	stream << vec.size() << "\t|";
	for (auto& elem : vec) {
		stream << ' ' << &elem;
	}
	return stream;
}

int main() {
	std::vector<int> vec;
	std::ofstream file("data.txt");

	
	for (int i = 0; i < 64; ++i) {
		vec.push_back(0);
		file << vec << "\n";
	}
	file << "\n";

	
	while (!vec.empty()) {
		vec.pop_back();
		file << vec << "\n";
	}

	
}