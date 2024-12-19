/*****************************************
 * Lab 3: exercise 1                      *
 ******************************************/

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>

 /*
AE EM 102
AN PS 190
EM BD 23
CK EM 15
FF CK 17
AE CK 9
PS FF 50
DH FF 35
DH EM 65
PS AN 75
FF CK 18
AE EM 91
JP FF 203
*/

int main() {
	std::cout << "Enter list of friend-to-friend loans:\n";
	std::map<std::string, int> balances; //map is container, stores unique pair. no duplicates
	std::string payer_name;
	std::string receiver_name;
	int price;

	std::map<std::string, int>::const_iterator it; //const_iterator we dont modify just check
	
	while (std::cin >> payer_name >> receiver_name >> price) {
		it = balances.find(payer_name);
		if (it != balances.end()) { //if it finds already existing payer_name
			balances[payer_name] += price; //add to existing
		}
		else {
			balances[payer_name] = price; //otherwise assign
		}
		
		it = balances.find(receiver_name); 
		if (it != balances.end()) {
			balances[receiver_name] -= price;
		}
		else {
			balances[receiver_name] = -price;
		}
	}

	std::vector<std::pair<std::string, int>> loans, debts; //all loans and debts with name and balance

	std::copy_if(balances.begin(), balances.end(), std::back_inserter(loans), [](const std::pair<std::string, int>&b){ 
	//first two arguments are begin and end, third is for insert. followed by function.
		return b.second > 0;
	}); //copy and insert in back of loans
	std::sort(loans.begin(), loans.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
		if (a.second == b.second) { //if balance is same, order by name instead
			return a.first < b.first;
		}
		return a.second > b.second;
	});
	//bool check is true or false, bigger or smaller

	std::copy_if(balances.begin(), balances.end(), std::back_inserter(debts), [](const std::pair<std::string, int>& b) {
		return b.second < 0;
		}); //last is bool to check if true
	std::sort(debts.begin(), debts.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
		if (std::abs(a.second) == std::abs(b.second)) {
			return a.first < b.first;
		}
		return std::abs(a.second) < std::abs(b.second);
		});

	std::ostream_iterator<std::string> out{ std::cout, "\n" }; //iterator for writing to file or output.

	std::transform(loans.begin(), loans.end(), out, [](const auto& a) { return a.first + " " + std::to_string(a.second); });

	std::transform(debts.begin(), debts.end(), out, [](const auto& a) { return a.first + " " + std::to_string(a.second); });

	int loan_mean = std::accumulate(loans.begin(), loans.end(), 0, [](int sum, const std::pair<std::string, int> a) { //calculates sum value, starts with 0
		return sum + a.second;
	}) / std::ssize(loans);
	int debt_mean = std::accumulate(debts.begin(), debts.end(), 0, [](int sum, const std::pair<std::string, int> a) {
		return sum + std::abs(a.second);
		}) / std::ssize(debts);

	std::cout << "Mean loan amount: " << loan_mean << "\n" << "Mean debt amount: " << debt_mean;
}
