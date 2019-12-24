#include "Metro.h"
#include "GK_lib.h"
#include <iostream>
#include "string.h"
#include <string>
#include <vector>

	std::ostream& operator << (std::ostream& cout, Station& my) {
		my.show();
		return cout;
	}
	void Station::show() {
		std::cout << this->getName() << " is ";
		switch (this->getType()) {
		case 0: {std::cout << "direct" << std::endl; break; }
		case 1: {std::cout << "interchange" << std::endl; break; }
		case 2: {std::cout << "hub" << std::endl; break; }
		default: {std::cout << "direct" << std::endl; break; }
		}
	}
	void Station::setType(int type0) {
		switch (type0) {
		case 0: {type = direct; break; }
		case 1: {type = interchange; break; }
		case 2: {type = hub; break; }
		default: {type = direct; break; }
		}
	}
	int Station::add(std::string name0) {
		setNameP(name0);
		return 1;
	}
	void Interchange::show() {
		std::cout << this->getName() << " is ";
		switch (this->getType()) {
		case 0: {std::cout << "direct" << std::endl; break; }
		case 1: {std::cout << "interchange" << std::endl; break; }
		case 2: {std::cout << "hub" << std::endl; break; }
		default: {std::cout << "direct" << std::endl; break; }
		}
		std::cout << "Interchanges list:" << std::endl;
		std::string* lines_name_out;
		getNames(lines_name_out);
		for (int i = 0; i < INTERCHANGE_NUM; i++)
			std::cout << lines_name_out[i] << std::endl;
		std::cout << std::endl;
	}
	bool Interchange::setNames(std::string input_l) {
		for (int i = 0; i < INTERCHANGE_NUM; i++) {
			if (lines_name[i] == "\0") {
				lines_name[i] = input_l;
				return true;
			}
		}
		return false;
	}
	void Hub::show() {
		std::cout << this->getName() << " is ";
		switch (this->getType()) {
		case 0: {std::cout << "direct" << std::endl; break; }
		case 1: {std::cout << "interchange" << std::endl; break; }
		case 2: {std::cout << "hub" << std::endl; break; }
		default: {std::cout << "direct" << std::endl; break; }
		}
		std::cout << "Hub list:" << std::endl;
		std::string* lines_name_out;
		std::string* stations_name_out;
		getNames(lines_name_out, stations_name_out);
		for (int i = 0; i < INTERCHANGE_NUM; i++)
			std::cout << lines_name_out[i] << "-" << stations_name_out[i] << std::endl;
		std::cout << std::endl;
	}
	bool Hub::setNames(std::string input_l, std::string input_s) {
		for (int i = 0; i < INTERCHANGE_NUM; i++) {
			if (lines_name[i] == "\0" && stations_name[i] == "\0") {
				lines_name[i] = input_l;
				stations_name[i] = input_s;
				return true;
			}
			if (lines_name[i] == "\0" || stations_name[i] == "\0")
				throw "WRONG_WRITING";
		}
		return false;
	}

	std::istream& operator >> (std::istream& cin, Station& my) {
		std::cout << "Please, enter name" << std::endl;
		std::string name = GK::getString();

		if (my.add(name) == 1) {
			std::cout << "Fine. Let's check it:" << std::endl;
			my.show();
		}
		else std::cout << "Something went wrong" << std::endl;

		return cin;
	}
	std::istream& operator >> (std::istream& cin, Interchange& my) {
		std::cout << "Please, enter name" << std::endl;
		std::string name = GK::getString();

		if (my.add(name) == 1) {
			std::cout << "Fine. Let's check it:" << std::endl;
			my.show();
		}
		else {
			std::cout << "Something went wrong" << std::endl;
			return cin;
		}

		do {
			std::cout << "Do you want to add interchange?" << std::endl
				<< "1 - yes, other - no" << std::endl;
			if (GK::getInt() != 1)
				break;
			std::cout << "Please, enter name of interchange-line" << std::endl;
		} while (my.setNames(GK::getString()));
		std::cout << "Fine. Let's check it:" << std::endl;
		my.show();

		return cin;
	}
	std::istream& operator >> (std::istream& cin, Hub& my) {
		std::cout << "Please, enter name" << std::endl;
		std::string name = GK::getString();

		if (my.add(name) == 1) {
			std::cout << "Fine. Let's check it:" << std::endl;
			my.show();
		}
		else {
			std::cout << "Something went wrong" << std::endl;
			return cin;
		}

		do {
			std::cout << "Do you want to add interchange?" << std::endl
				<< "1 - yes, other - no" << std::endl;
			if (GK::getInt() != 1)
				break;
			std::cout << "Please, enter name of interchange-line and interchange-station" << std::endl;
		} while (my.setNames(GK::getString(), GK::getString()));
		std::cout << "Fine. Let's check it:" << std::endl;
		my.show();

		return cin;
	}//добавить станцию-пересадку


	void Line::setList(std::vector<Station*> station_list0) {
		std::vector< Station* > buf_list = station_list0;
		for (auto it = buf_list.begin(); it < buf_list.end(); it++)
			this->add(station_list0.end(), *(it._Ptr));
	}
	std::vector< Station* >::iterator Line::place_find() {
		std::cout << "Where will new station be constructed?" << std::endl
			<< "0 - at the begin, 1- at the end, other - in the middle" << std::endl;
		
		switch (GK::getInt()) {
		case 0: {
			return this->station_list.begin();
		}
		case 1: {
			return this->station_list.end();
		}
		default: {
			std::cout << "Print station name to add new station before it" << std::endl;
			std::vector< Station* >::iterator it_place;
			try { return this->find(GK::getString()); }
			catch (...) { throw "NOT FOUND"; }
		}
		}
	}
	std::vector< Station* >::iterator Line::find(std::string name0) {
		for (std::vector< Station* >::iterator it = station_list.begin(); it < station_list.end(); it++)
			if ((*(it._Ptr))->getName() == name0)
				return it;

		throw "NOT FOUND";
	}
	Station* Line::operator [] (std::string name0) {
		Station* stantion1;
		try { stantion1 = *(find(name0)); }
		catch (...) { std::cout << "Station with this name doesn't exist" << std::endl; return nullptr; }
		return stantion1;
	}
	void Line::operator -- () {
		std::cout << "Please entere name of station you'd like to delete" << std::endl;
		try { this->station_list.erase(find(GK::getString())); }
		catch (...) { std::cout << "Station with this name doesn't exist" << std::endl; }
	}
	std::istream& operator >> (std::istream& cin, Line& line0) {
		std::cout << "You want to add a station" << std::endl
				  << "Please enter it's future name" << std::endl;
			Station* new_station = new(Station);
			new_station->setNameP(GK::getString());
			try { line0.add(line0.place_find(), new_station); }
			catch (...) { std::cout << "Something went wrong" << std::endl; return cin; }
			return cin;
	}
	std::ostream& operator << (std::ostream& cout, Line& my) {
		std::cout << "This is " << my.getName() << " line" << std::endl

			<< "These are stations on it:" << std::endl;
		std::vector< Station* > buf_list = my.getList();
		for (auto it = buf_list.begin(); it < buf_list.end(); it++)
			std::cout << *(*(it._Ptr)) << std::endl;

		return cout;
	}
	bool Line::add(std::vector< Station* >::iterator it0, Station* station0) {
		try { this->station_list.insert(it0, station0); } //
		catch (...) { throw "NOT ADDED"; }
		return true;
	}

	void System::setList(std::vector<Line*> line_list0) {
		std::vector< Line* > buf_list = line_list0;
		for (auto it = buf_list.begin(); it < buf_list.end(); it++)
			this->line_list.push_back(*(it._Ptr));
	}
	std::vector< Line* >::iterator System::find(std::string name0) {
		for (std::vector< Line* >::iterator it = line_list.begin(); it < line_list.end(); it++)
			if ((*(it._Ptr))->getName() == name0)
				return it;

		throw "NOT FOUND";
	}
	Line* System::operator [] (std::string name0) {
		Line* line1;
		try { line1 = *(find(name0)); }
		catch (...) { std::cout << "Line with this name doesn't exist" << std::endl; return nullptr; }
		return line1;
	}
	void System::operator -- () {
		std::cout << "Please entere name of line you'd like to delete" << std::endl;
		try { this->line_list.erase( find(GK::getString()) ); }
		catch (...) { std::cout << "Line with this name doesn't exist" << std::endl;}
	}
	std::ostream& operator << (std::ostream& cout, System& my) {
		std::cout << "These are lines of " << my.getName() << " system" << std::endl;

		std::vector< Line* > buf_list = my.getList();
		if (buf_list.empty())
			std::cout << "There are no lines here..." << std::endl;
		else
			for (auto it = buf_list.begin(); it < buf_list.end(); it++)
				std::cout << (*(it._Ptr))->getName() << std::endl << std::endl;

		return cout;
	}
	std::istream& operator >> (std::istream& cin, System& system0) {
		std::cout << "You want to add a line" << std::endl
				  << "Please enter it's future name" << std::endl;
		Line* new_line = new(Line);
		new_line->setName(GK::getString());
		std::cout << "Do you want to add stations on this line right now?" << std::endl
				  << "1 - yes, other - no" << std::endl;
		while (GK::getInt() == 1) {
			std::cin >> *new_line;
			std::cout << "Do you want to add more stations right now?" << std::endl
					  << "1 - yes, other - no" << std::endl;
		}
		system0.line_list.push_back(new_line);
		return cin;
	}


	/*
		std::istream& operator >> (std::istream& cin, Line& line0) {
		std::cout << "You want to add a station" << std::endl
			<< "Is this station has at least one interchange-line?" << std::endl
			<< "1 - yes, other - no" << std::endl;

		if (GK::getInt() == 1) {
			std::cout << "Is at least one interchange-station has diffrent name?" << std::endl
				<< "1 - yes, other - no" << std::endl;
			if (GK::getInt() == 1) {
				Hub* new_station = new(Hub);
				std::cout << "Finaly, station's info" << std::endl;
				std::cin >> *new_station;
				try { line0.add(line0.place_find(), reinterpret_cast<Station*>(new_station)); }
				catch (...) { std::cout << "Something went wrong" << std::endl; return cin; }
				return cin;
			}
			else {
				Interchange* new_station = new(Interchange);
				std::cout << "Finaly, station's info" << std::endl;
				std::cin >> *new_station;
				try { line0.add(line0.place_find(), reinterpret_cast<Station*>(new_station)); }
				catch (...) { std::cout << "Something went wrong" << std::endl; return cin; }
				return cin;
			}
		}
		else {
			Station* new_station = new(Station);
			std::cout << "Finaly, station's info" << std::endl;
			std::cin >> *new_station;
			try { line0.add(line0.place_find(), reinterpret_cast<Station*>(new_station)); } //
			catch (...) { std::cout << "Something went wrong" << std::endl; return cin; }
			return cin;
		}
	}*/
	void Line::clean(std::vector< Station* >::iterator it) {
		this->station_list.erase(it);
	}
	void System::make_interchange(Line*& line1, Station*& station1, Line*& line2, Station*& station2) {
		if (station1->getName() == station2->getName()) {
			switch (station1->getType()) {
			case 1: {
				if (!(reinterpret_cast<Interchange*>(station1)->setNames(line2->getName())))
					return;
				else
					break;
			}
			case 2: {
				if (!(reinterpret_cast<Hub*>(station1)->setNames(line2->getName(), station2->getName())))
					return;
				else
					break;
			}
			default: {
				Interchange* new_station = new(Interchange);
				new_station->setName(station1->getName());
				new_station->setNames(line2->getName());

				std::vector< Station* >::iterator station1_it = line1->find(station1->getName());
				std::vector< Station* >::iterator station2_it = station1_it;
				if (station1_it == line1->lbegin() ) {
					station2_it = line1->lbegin();
					line1->clean(station1_it);

				}
				else {
					if (station1_it == line1->lend()) {
						station2_it = line1->lend();
						line1->clean(station1_it);
					}
					else {
						station2_it = station1_it--;
						line1->clean(station1_it);
					}
				}

				try { line1->add(station1_it, reinterpret_cast<Station*>(new_station)); }
				catch (...) { std::cout << "Something went wrong" << std::endl; return; }
				break;
			}
			}
			switch (station2->getType()) {
			case 1: {
				if (!(reinterpret_cast<Interchange*>(station2)->setNames(line1->getName())))
					return;
				else
					break;
			}
			case 2: {
				if (!(reinterpret_cast<Hub*>(station2)->setNames(line1->getName(), station1->getName())))
					return;
				else
					break;
			}
			default: {
				Interchange* new_station = new(Interchange);
				new_station->setName(station2->getName());
				new_station->setNames(line1->getName());

				std::vector< Station* >::iterator station1_it = line2->find(station1->getName());
				std::vector< Station* >::iterator station2_it = station1_it;
				if (station1_it == line2->lbegin()) {
					station2_it = line2->lbegin();
					line2->clean(station1_it);

				}
				else {
					if (station1_it == line1->lend()) {
						station2_it = line1->lend();
						line2->clean(station1_it);
					}
					else {
						station2_it = station1_it--;
						line2->clean(station1_it);
					}
				}

				try { line2->add(station1_it, reinterpret_cast<Station*>(new_station)); }
				catch (...) { std::cout << "Something went wrong" << std::endl; return; }
				break;
			}
			}
			return;
		}

		else {
			switch (station1->getType()) {
			case 1: {
				Hub* new_station = new(Hub);
				new_station->setName(station1->getName());

				std::string* line_name_buf;
				reinterpret_cast<Interchange*>(station1)->getNames(line_name_buf);
				for (int i=0; i<INTERCHANGE_NUM; i++)
					if (line_name_buf[i] != "\0")
						new_station->setNames(line_name_buf[i], station1->getName());

				new_station->setNames(line2->getName(), station2->getName());

				std::vector< Station* >::iterator station1_it = line1->find(station1->getName());
				std::vector< Station* >::iterator station2_it = station1_it;
				if (station1_it == line1->lbegin()) {
					line1->clean(station1_it);
					station2_it = line1->lbegin();
					

				}
				else {
					if (station1_it == line1->lend()) {
						line1->clean(station1_it);
						station2_it = line1->lend();
						
					}
					else {
						line1->clean(station1_it);
						station2_it = station1_it--;
						
					}
				}

				try { line1->add(station1_it, reinterpret_cast<Station*>(new_station)); }
				catch (...) { std::cout << "Something went wrong" << std::endl; return; }
				break;
			}
			case 2: {
				if (!(reinterpret_cast<Hub*>(station1)->setNames(line2->getName(), station2->getName())))
					return;
				else
					break;
			}
			default: {
				Hub* new_station = new(Hub);
				new_station->setName(station1->getName());
				new_station->setNames(line2->getName(), station2->getName());

				std::vector< Station* >::iterator station1_it = line1->find(station1->getName());
				std::vector< Station* >::iterator station2_it = station1_it;
				auto buf = line1->getList();
				if (station1_it == line1->lbegin()) {
					line1->clean(station1_it);
					station2_it = line1->lbegin();

				}
				else {
					if (station1_it == line1->lend()) {
						line1->clean(station1_it);
						station2_it = line1->lend();
						
					}
					else {
						line1->clean(station1_it);
						station2_it = station1_it--;
						
					}
				}


				//

				try { line1->add(station2_it, reinterpret_cast<Station*>(new_station)); }
				catch (...) { std::cout << "Something went wrong" << std::endl; return; }
				break;
			}
			}
			switch (station2->getType()) {
			case 1: {
				Hub* new_station = new(Hub);
				new_station->setName(station2->getName());

				std::string* line_name_buf;
				reinterpret_cast<Interchange*>(station2)->getNames(line_name_buf);
				for (int i = 0; i < INTERCHANGE_NUM; i++)
					if (line_name_buf[i] != "\0")
						new_station->setNames(line_name_buf[i], station2->getName());

				new_station->setNames(line1->getName(), station1->getName());

				std::vector< Station* >::iterator station1_it = line2->find(station2->getName());
				std::vector< Station* >::iterator station2_it = station1_it;
				if (station1_it == line2->lbegin()) {
					line2->clean(station1_it);
					station2_it = line2->lbegin();
					

				}
				else {
					if (station1_it == line1->lend()) {
						line2->clean(station1_it);
						station2_it = line1->lend();
						
					}
					else {
						line2->clean(station1_it);
						station2_it = station1_it--;
						
					}
				}

				try { line2->add(station1_it, reinterpret_cast<Station*>(new_station)); }
				catch (...) { std::cout << "Something went wrong" << std::endl; return; }
				break;
			}
			case 2: {
				if (!(reinterpret_cast<Hub*>(station2)->setNames(line1->getName(), station1->getName())))
					return;
				else
					break;
			}
			default: {
				Hub* new_station = new(Hub);
				new_station->setName(station2->getName());
				new_station->setNames(line1->getName(), station1->getName());

				std::vector< Station* >::iterator station1_it = line2->find(station2->getName());
				std::vector< Station* >::iterator station2_it = station1_it;
				if (station1_it == line2->lbegin()) {
					line2->clean(station1_it);
					station2_it = line2->lbegin();
					

				}
				else {
					if (station1_it == line1->lend()) {
						line2->clean(station1_it);
						station2_it = line1->lend();
						
					}
					else {
						line2->clean(station1_it);
						station2_it = station1_it--;
						
					}
				}

				try { line2->add(station2_it, reinterpret_cast<Station*>(new_station)); }
				catch (...) { std::cout << "Something went wrong" << std::endl; return; }
				break;
			}
			}
		}

	}


