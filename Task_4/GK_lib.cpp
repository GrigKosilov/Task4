#include "GK_lib.h"
#include <iostream>
#include "string.h"
#include <string>

	int GK::getInt() {
		int value;
		while (true) {
			std::cin >> value;
			if (std::cin.peek() == '\n') {
				std::cin.get();
				break;
			}
			else {
				std::cout << "Retype input (value must be \
                int number)" << std::endl;
				std::cin.clear();
				while (std::cin.get() != '\n') {}
			}
		}
		return (value);
	}
	double GK::getDouble() {
		double value;
		while (true) {
			std::cin >> value;
			if (std::cin.peek() == '\n') {
				std::cin.get();
				break;
			}
			else {
				std::cout << "Retype input (value must be \
                int number)" << std::endl;
				std::cin.clear();
				while (std::cin.get() != '\n') {}
			}
		}
		return (value);
	}
	char GK::getChar() {
		char value;
		while (true) {
			std::cin >> value;
			if (std::cin.peek() == '\n') {
				std::cin.get();
				break;
			}
			else {
				std::cout << "Retype input (value must be \
                int number)" << std::endl;
				std::cin.clear();
				while (std::cin.get() != '\n') {}
			}
		}
		return (value);
	}
	std::string GK::getString() {
		std::string str1;
		std::cin >> str1;
		if (!std::cout.good())
			std::cout.setstate(std::ios::failbit);
		return str1;
	}
	int GK::dialog(std::string* msgs, int N) {
		std::string errmsg = "";
		int rc, i;
		do {
			std::cout << errmsg;
			errmsg = "You are wrong. Repeate, please!";
			for (i = 0; i < N; ++i)
				std::cout << msgs[i] << std::endl;
			std::cout << "Make your choice: --> ";
			rc = GK::getInt();
		} while (rc < 0 || rc >= N);
		return rc;
	}

/* MADE BY GRIG_KOSILOV IN MEPHI 2019 */



