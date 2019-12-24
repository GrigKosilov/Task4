#include "Queue.h"
#include "GK_lib.h"
#include <iostream>
#include "string.h"

namespace Queue {
	info::info() {
		code_customer = 0;
		code_problem = 0;
		code_desk = 0;
	}
	info::info(int c_c) {
		code_customer = c_c;
		code_problem = 0;
		code_desk = 0;
	}
	info& info::setProblem() {
		std::cout << "Enter your problem code pls ";
		code_problem = GK::getInt();
		return *this;
	}
	info& info::setDesk() {
		std::cout << "Enter desk code pls ";
		code_desk = GK::getInt();
		return *this;
	}
	void info::getInfo() {
		std::cout << "#     " << code_customer << "    |    " << code_problem;
		if (!code_desk)
			std::cout << "    | none #" << std::endl;
		else
			std::cout << "    |  " << code_desk << "   #" << std::endl;
	}

	void Queue::resizef() {
		info* old_data = data;
		try {
			data = new info[size];
		}
		catch (std::bad_alloc & ba) {
			std::cout << "BAD ALLOC" << ba.what() << std::endl;
			exit(0);
		}

		int old_tail = tail;
		tail = 0;

		while (head < old_tail)
			data[tail++] = old_data[head++];
		head = 0;
		//delete[] old_data;
	}
	void Queue::allocf() {
		try {
			data = new info[size];
		}
		catch (std::bad_alloc & ba) {
			std::cout << "BAD ALLOCATION!" << ba.what() << std::endl;
			exit(0);
		}
	}
	void Queue::pushf(info data0) {
		if (tail >= size) {
			size += QUOTA;
			resizef();
		}
		if (emptiness == 1)
			emptiness = 0;
		writef(tail++, data0);
		return;
	}
	void Queue::writef(int pos, info data0) {
		data[pos].code_customer = data0.code_customer;
		data[pos].code_problem = data0.code_problem;
		data[pos].code_desk = data0.code_desk;
	}
	info Queue::popf() {
		if (emptiness == 1) {
			info data_null;
			data_null.code_customer = 99099;
			data_null.code_problem = 88088;
			data_null.code_desk = 77077;
			return data_null;
		}
		info data1 = readf(data[head++]);
		if (head == tail) {
			emptiness = 1;
			head = 0, tail = 0;
		}
		if (head > QUOTA) {
			size -= QUOTA;
			resizef();
		}
		return data1;
	}
	info Queue::readf(info data) {
		info data1;
		data1.code_customer = data.code_customer;
		data1.code_problem = data.code_problem;
		data1.code_desk = data.code_desk;
		return data1;
	}
	Queue::Queue() : size(QUOTA), head(0), tail(0), emptiness(1) {
		allocf();
	}
	Queue& Queue::setCustomer(int c_c) {
		info data1(c_c);
		pushf(data1.setProblem());
		return *this;
	}

	int Queue::getSize() {
		return tail-head;
	}
	void Queue::getAll() {
		if (emptiness == 1) {
			std::cout << "#     Nobody is in queue    #" << std::endl;
			return;
		}	
		while (emptiness != 1) {
			popf().getInfo();
		}
	}
	void Queue::showAll() {
		int i = head;
		for (; i != tail; i++) {
			data[i].getInfo();
		}
		if (i == 0)
			std::cout << "#     Nobody is in queue    #" << std::endl;
	}

	std::ostream& operator <<(std::ostream& cout, Queue& queue) {
		queue.showAll();
		return cout;
	}
	info Queue::operator -- () {
		return popf();
	}
	info Queue::operator --(int) {
		return popf();
	}
	Queue& Queue::operator += (const info data0){
		if ( data0.code_customer != 99099 &&
			 data0.code_problem != 88088  &&
			 data0.code_desk != 77077      )
			pushf(data0);

		return *this;
	}
}