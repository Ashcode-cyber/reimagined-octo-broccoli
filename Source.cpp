#include<iostream>
#include<string>


struct mounth{
	int t;
	std::string g;

	void addmounth(int r) {
		t = t + r;
	};
};



int main() {
	mounth first;
	first.t = 1;
	first.g = "hi";
	first.addmounth(3);
	std::cout << first.t << first.g;
}