#include <iostream>
#define STRING_SIZE 100

namespace Queue {
	struct info {
		int code_customer;
		int code_problem;
		int code_desk;

		info();
		info(int);
		info& setProblem();
		info& setDesk();
		void getInfo();
	};
	class Queue {
	private:
		static const int QUOTA = 3;
		int size;
		int head = 0, tail = 0;
		bool emptiness=1;
		info* data;

		void allocf();
		void writef(int, info);
		void resizef();
		info readf(info);
	protected:
		void pushf(info);
		info popf();
	public:
		Queue();
		~Queue() {  delete[] data;  }
		
		Queue& setCustomer(int);
		int getSize();
		void getAll();
		void showAll();
		
		friend std::ostream& operator << (std::ostream&, Queue&);
		Queue& operator += (const info); //�������� � this ���� �������
		info operator -- (); //������ ���� �� �������� �������
		info operator -- (int); //������ ���� �� �������� �������
	};

}

/* MADE BY GRIG_KOSILOV IN MEPHI 2019 */