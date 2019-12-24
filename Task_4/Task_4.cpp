#include <iostream>
#include "GK_lib.h"
#include "Metro.h"



int D_Show(Line*& Line0) {
	std::cout << *Line0;
	return 1;
}
int D_Add(Line*& Line0) {
	std::cin >> *Line0;
	return 1;
}
int D_Delete(Line*& Line0) {
	Line0--;
	return 1;
}
int (*fptr_line[])(Line*&) = { NULL, D_Show, D_Add, D_Delete };
int D_Open(System& MosMetro) {
	std::string msgs_line[] = { "0.Quit", "1.Show Line", "2.Add station", "3.Delete station" };

	std::cout << "Please enter name of line you'd like to open" << std::endl;
	Line* founded_line=MosMetro[GK::getString()]; 
	if (!founded_line)
		return 1;

	int rc;
	std::cout << "Welcome to the " <<  founded_line->getName() << " line menu!" << std::endl;
	while (rc = GK::dialog(msgs_line, sizeof(msgs_line) / sizeof(msgs_line[0])))
		if (!fptr_line[rc](founded_line))
			break;
	return 1;
}
int D_Show(System& MosMetro) {
	std::cout << MosMetro;
	return 1;
}
int D_Add(System& MosMetro) {
	std::cin >> MosMetro;
	return 1;
}
int D_Delete(System& MosMetro) {
	//MosMetro--;
	return 1;
}
int D_Interchange(System& MosMetro) {
	std::cout << "Please entere name of the first line you'd like to make an interchange on" << std::endl;
	Line* founded_line1 = MosMetro[GK::getString()];
	if (!founded_line1)
		return 1;
	std::cout << "Please entere name of station you'd like to convert into an interchange" << std::endl;
	Station* founded_station1 = (*founded_line1)[GK::getString()];
	if (!founded_station1)
		return 1;

	std::cout << "Please entere name of the second line you'd like to make an interchange on" << std::endl;
	Line* founded_line2 = MosMetro[GK::getString()];
	if (!founded_line2)
		return 1;
	std::cout << "Please entere name of station you'd like to convert into an interchange" << std::endl;
	Station* founded_station2 = (*founded_line2)[GK::getString()];
	if (!founded_station2)
		return 1;

	MosMetro.make_interchange(founded_line1, founded_station1, founded_line2, founded_station2);

	return 1;
}
void find_exit(System& Metro, std::vector< std::pair < std::string, Station*> > maze, int keyA, int keyB) {
	enum Color { white, gray, black };
	std::vector< Color > color; std::vector< int > len; std::vector< int > prev;
	color.reserve(maze.size()); len.reserve(maze.size()); prev.reserve(maze.size());
	for (int i = 0; i < maze.size(); ++i) {
		color.push_back(white); len.push_back(-1); prev.push_back(0);
	}
	color[keyA] = gray; len[keyA] = 0; prev[keyA] = 0;

	typedef struct edge {
		int key;
		struct edge* next;
	} edge;
	edge* queue = new(edge);
	edge* last = queue;
	queue->key = keyA; queue->next = nullptr;

	while (queue) {
		std::pair < std::string, Station*> p_pair = maze[queue->key]; //взяли станцию

		if (p_pair.second->getType() != direct) {
			std::string* lines_name = { '\0' }; std::string* stations_name = { '\0' };
			if (p_pair.second->getType() == interchange) {
				Interchange* p_st = reinterpret_cast<Interchange*>(p_pair.second);
				p_st->getNames(lines_name);
				for (int i = 0; i < INTERCHANGE_NUM; i++)
					stations_name[i] = p_pair.second->getName();
			}
			if (p_pair.second->getType() == hub) {
				Hub* p_st = reinterpret_cast<Hub*>(p_pair.second);
				p_st->getNames(lines_name, stations_name);
			}

			for (int i = 0; i < INTERCHANGE_NUM; i++) {
				if (lines_name[i] == "\0" || stations_name[i] == "\0")
					break;

				std::pair < std::string, Station*> find_pair =
				{ lines_name[i], (*Metro[lines_name[i]])[stations_name[i]] };

				int j = -1;
				for (j=0; j < maze.size(); j++) {
					if (maze[j] == find_pair)
						break;
				}

					if (color[j] == white) {
						color[j] = gray;
						len[j] = len[queue->key] + 1;
						if (j == keyB) {
							prev[j] = queue->key;
							printf("	The way is:");
							std::cout << maze[keyB].second->getName();
							while (prev[j] != keyA) {
								std::cout << "<-" << maze[prev[j]].second->getName();
								j = prev[j];
							}
							std::cout << "<-" << maze[keyA].second->getName();
						}
						prev[j] = queue->key;
						last->next = new(edge);
						last = last->next;
						last->next = nullptr;
						last->key = j;
					}
				
			}
		}

		auto y2 = (*(Metro[p_pair.first]->getListP()))[(*(Metro[p_pair.first]->getListP())).size() - 1]->getName();

		if ((*(Metro[p_pair.first]->getListP()->begin()))->getName() == p_pair.second->getName()) {
			int j = queue->key+1;
			if (color[j] == white) {
				color[j] = gray;
				len[j] = len[queue->key] + 1;
				if (j == keyB) {
					prev[j] = queue->key;
					printf("	The way is:");
					std::cout << maze[keyB].second->getName();
					while (prev[j] != keyA) {
						std::cout << "<-" << maze[prev[j]].second->getName();
						j = prev[j];
					}
					std::cout << "<-" << maze[keyA].second->getName();
				}
				prev[j] = queue->key;
				last->next = new(edge);
				last = last->next;
				last->next = nullptr;
				last->key = j;
			}
		}
		else if ((*(Metro[p_pair.first]->getListP()))[(*(Metro[p_pair.first]->getListP())).size()-1]->getName() == p_pair.second->getName()) {
			int j = queue->key-1;
			if (color[j] == white) {
				color[j] = gray;
				len[j] = len[queue->key] + 1;
				if (j == keyB) {
					prev[j] = queue->key;
					printf("	The way is:");
					std::cout << maze[keyB].second->getName();
					while (prev[j] != keyA) {
						std::cout << "<-" << maze[prev[j]].second->getName();
						j = prev[j];
					}
					std::cout << "<-" << maze[keyA].second->getName();
				}
				prev[j] = queue->key;
				last->next = new(edge);
				last = last->next;
				last->next = nullptr;
				last->key = j;
			}
		}
		else {
			int j = queue->key-1;
			if (color[j] == white) {
				color[j] = gray;
				len[j] = len[queue->key] + 1;
				if (j == keyB) {
					prev[j] = queue->key;
					printf("	The way is:");
					std::cout<< maze[keyB].second->getName();
					while (prev[j] != keyA) {
						std::cout << "<-" << maze[prev[j]].second->getName();
						j = prev[j];
					}
					std::cout << "<-" << maze[keyA].second->getName();
				}
				prev[j] = queue->key;
				last->next = new(edge);
				last = last->next;
				last->next = nullptr;
				last->key = j;
			}
			j = queue->key+1;
			if (color[j] == white) {
				color[j] = gray;
				len[j] = len[queue->key] + 1;
				if (j == keyB) {
					prev[j] = queue->key;
					printf("	The way is:");
					std::cout << maze[keyB].second->getName();
					while (prev[j] != keyA) {
						std::cout << "<-" << maze[prev[j]].second->getName();
						j = prev[j];
					}
					std::cout << "<-" << maze[keyA].second->getName();
				}
				prev[j] = queue->key;
				last->next = new(edge);
				last = last->next;
				last->next = nullptr;
				last->key = j;
			}
		}

		color[queue->key] = black;
		queue = queue->next;
	}
}
int D_Find(System& MosMetro) {
	std::vector< std::pair < std::string, Station*> > maze;
	for (int i = 0; i < MosMetro.getList().size(); i++) {
		Line* cur_line = (*(MosMetro.getListP()))[i];
		for (int j = 0; j < cur_line->getList().size(); j++) {
			Station* cur_st = (*(cur_line->getListP()))[j];
			std::pair < std::string, Station*> buf = { cur_line->getName(), cur_st };
			maze.push_back(buf);
		}
	}

	std::cout << "Please entere name of the first line you'd like to start your way" << std::endl;
	Line* founded_line1 = MosMetro[GK::getString()];
	if (!founded_line1)
		return 1;
	std::cout << "Please entere name of station you'd like to start your way" << std::endl;
	Station* founded_station1 = (*founded_line1)[GK::getString()];
	if (!founded_station1)
		return 1;
	std::pair < std::string, Station*> pair1 = { founded_line1->getName(), founded_station1 };


	std::cout << "Please entere name of the second line you'd like to end your way" << std::endl;
	Line* founded_line2 = MosMetro[GK::getString()];
	if (!founded_line2)
		return 1;
	std::cout << "Please entere name of station you'd like to end your way" << std::endl;
	Station* founded_station2 = (*founded_line2)[GK::getString()];
	if (!founded_station2)
		return 1;
	std::pair < std::string, Station*> pair2 = { founded_line2->getName(), founded_station2 };

	int keyA=-1, keyB=-1;
	for (int i = 0; i < maze.size(); i++) {
		if (maze[i] == pair1)
			keyA = i;
		if (maze[i] == pair2)
			keyB = i;
	}

	find_exit(MosMetro, maze, keyA, keyB);
	return 1;
}
int (*fptr_system[])(System&) = { NULL, D_Show, D_Add, D_Delete, D_Open, D_Interchange, D_Find };
int main() {
	std::string msgs_system[] = { "0.Quit", "1.Show system", "2.Add line", "3.Delete line",
								  "4.Open exact line menu", "5.Create an interchage",
								  "6. Find way" };

	System MosMetro("Moscow Metro"); int rc;
	std::cout << "Welcome to the " << MosMetro.getName() << " system menu!" << std::endl;
	while (rc = GK::dialog(msgs_system, sizeof(msgs_system) / sizeof(msgs_system[0]))) {
		if (!fptr_system[rc](MosMetro))
			break;
	}


	std::cout << "See you soon!" << std::endl;
	return 1;
}

// system("cls");