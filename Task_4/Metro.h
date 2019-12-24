#include <vector>
#include "string.h"
#include <string>
#include <iostream>

/*	http://www.cplusplus.com/reference/algorithm/find/
	https://ru.cppreference.com/w/cpp/container/vector
	https://www.wikiwand.com/ru/Vector_(C%2B%2B)		*/

	#define INTERCHANGE_NUM 3 // кол-во пересадок
	enum station_type { direct, interchange, hub };

	class Station {
	private:
		std::string name;
		station_type type;
	public:
		virtual ~Station() {};
		Station() {
			name = "IN_CONSTRUCT"; type = direct; }
		Station(std::string name0) {
			name = name0; type = direct; }
		//~Station() {
		//	delete& name; }
		
		std::string getName() {
			return name; }
		station_type getType() {
			return type; }
		//А как мне его const объявить?
		virtual void show();
		friend std::ostream& operator << (std::ostream&, Station&);
	
		void setNameP(std::string name0) {
			name = name0; }
		void setType(int);
		int add(std::string);
		friend std::istream& operator >> (std::istream&, Station&);
	};
	class Interchange : private Station {
	private:
		std::string lines_name[INTERCHANGE_NUM];
	public:
		Interchange() {
			setName("IN_CONSTRUCT"); setType(interchange); }
		Interchange(std::string name0) {
			setName(name0); setType(direct); }
		//~Interchange() {
		//	delete[] lines_name; }
		void setName(std::string name0) {
			setNameP(name0);
		}

		void show();
		//friend std::ostream& operator << (std::ostream&, Interchange&); //Показать инфо о линиях-пересадках
		friend std::istream& operator >> (std::istream&, Interchange&); //добавить линию-пересадку
		void getNames(std::string*& output) {
			output = lines_name;
		}
		bool setNames(std::string);
	};
	class Hub : private Station {
	private:
		std::string lines_name[INTERCHANGE_NUM];
		std::string stations_name[INTERCHANGE_NUM];
	public:
		Hub() {
			setName("IN_CONSTRUCT"); setType(hub); }
		Hub(std::string name0) {
			setName(name0); setType(direct); }
		//~Hub() {
		//	delete[] lines_name, stations_name; }
		void setName(std::string name0) {
			setNameP(name0);
		}

		void getNames(std::string*& output_l, std::string*& output_s ) {
			output_l = lines_name; output_s = stations_name;
		}
		void show();
		//friend std::ostream& operator << (std::ostream&, Hub&); //Показать инфо о станцию-пересадку
		bool setNames(std::string, std::string);
		friend std::istream& operator >> (std::istream&, Hub&); //добавить станцию-пересадку
	};
	class Line {
	private:
		std::string name;
		std::vector< Station* > station_list;
	public:
		Line() {
			name = "IN_CONSTRUCT"; station_list;
		}
		Line(std::string name0) {
			name = name0; station_list;
		}
		void setName(std::string name0) {
			name = name0;
		}
		void setList(std::vector< Station* >);
		std::string getName() {
			return name;
		}
		std::vector< Station* > getList() {
			return station_list;
		}
		std::vector< Station* >* getListP() {
			return &station_list;
		}

		std::vector< Station* >::iterator place_find();
		std::vector< Station* >::iterator find(std::string); //Вернуть указатель на нужную станцию
		Station* operator [] (std::string); //Вывести инфо о станции с нужным названием
		void operator -- ();
		friend std::ostream& operator << (std::ostream&, Line&); //Показать все станции на линии
		friend std::istream& operator >> (std::istream&, Line&); //добавить станцию, введя о ней инфу
		bool add(std::vector< Station* >::iterator, Station*);
		void clean(std::vector< Station* >::iterator);

		std::vector< Station* >::iterator lbegin() { return this->station_list.begin(); }
		std::vector< Station* >::iterator lend() { return this->station_list.end(); }
	};
	class System {
	private:
		std::string name;
		std::vector< Line* > line_list;
	public:
		System() {
			name = "IN_CONSTRUCT"; line_list;
		}
		System(std::string name0) {
			name = name0; line_list;
		}
		void setName(std::string name0) {
			name = name0;
		}
		void setList(std::vector< Line* >);
		std::string getName() {
			return name;
		}
		std::vector< Line* > getList() {
			return line_list;
		}
		std::vector< Line* >* getListP() {
			return &line_list;
		}
		void make_interchange(Line*&, Station*&, Line*&, Station*&);

		std::vector< Line* >::iterator find(std::string); //Вернуть указатель на нужную станцию
		Line* operator [] (std::string); //Вывести инфо о станции с нужным названием
		void operator -- ();
		friend std::ostream& operator << (std::ostream&, System&); //Показать все линии в системе
		friend std::istream& operator >> (std::istream&, System&); //добавить линию, введя о ней инфу
	};