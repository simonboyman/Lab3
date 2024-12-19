/**************************
 * Lab 3: exercise 3      *
 **************************/

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>

int main() {
	std::ifstream file("../code/uppgift3_kort.txt");
	std::ofstream write("../code/outputFile.txt");
	std::string word;
	std::map<std::string, std::set<std::string>> anagrams; 
	//std::string is subject, std::set is the words. map prevents duplicate for subjects.
	//std::set doesnt allow duplicates for the words

	if (file.is_open()) {
		while (file >> word) {
			std::string subject = word;
			std::sort(subject.begin(), subject.end());
			anagrams[subject].insert(word);
		}
		file.close();
	}
	else {
		std::cout << "Unable to open file";
	}

	std::ostream_iterator<std::string> out{ write, " " };
	write << "\n" << "-- ANAGRAMS -- \n";
	for (auto group : anagrams) { //auto used for map
		if (std::ssize(group.second) > 1) {
			std::copy(group.second.begin(), group.second.end(), out); //writes all the anagrams for a subject
			write << " --> " << std::ssize(group.second) << " words\n"; 

		}
	}
}