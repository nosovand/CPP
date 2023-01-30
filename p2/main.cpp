#include <iostream>
#include <sstream>
#include <algorithm>
#include "main.hpp"

int id = 1;


Database::Database(){
	// Database constructor
}

// add item to the database
void Database::add(Item * a) {
	db.push_back(a);
}

bool Item::sort_name (const Item* b) const{
		return (name < b->name);
}

bool Item::sort_year (const Item* b) const{
		return (stoi(year) < stoi(b->year));
}


// definition of the sort function according to name
bool sort_name::operator()(const Item* a, const Item* b){
bool tmp = a->sort_name(b);
return tmp;
}

bool sort_year::operator()(const Item* a, const Item* b){

return a->sort_year(b);
}

void Database::find(string x){
int ind = 0;
std::cout << "+----------------------------------------------------------+" << '\n';
std::cout << "| Search for \"" << x << "\"";
for (int i = 0; i < 44-(int)x.length(); i++){
	std::cout << " ";
}
std::cout << "|" << '\n';

for (int i = 0; i < (int)db.size(); i++){
	if(db[i]->checkForPhrase(x) == true){
		db[i]->printItem();
		ind++;
	}
}
std::cout << "+----+-----------------------------------------------------+" << '\n';
std::cout << "| Total: " << ind << "                                                 |" << '\n';
std::cout << "+----------------------------------------------------------+" << '\n';
}

void Database::list(){
std::cout << "+----------------------------------------------------------+" << '\n';
std::cout << "| List of all records                                      |" << '\n';

for (int i = 0; i < (int)db.size(); i++)
db[i]->printItem();

std::cout << "+----+-----------------------------------------------------+" << '\n';
std::cout << "| Total: " << db.size() << "                                                 |" << '\n';
std::cout << "+----------------------------------------------------------+" << '\n';

}

void Database::remove(int x) {
	/*odstraní z databáze položku s číslem id, nic nevypisuje*/
	bool found = false;
	for (auto i = db.begin(); i != db.end(); i++){
		int k = i - db.begin();
		if (db[k]->checkID(x) == true){
		try {
			db.erase(i);
			found = true;
		}
		catch(...){

		}
	}
}

if(found == false){
		std::cout << "+----------------------------------------------------------+" << '\n';
		std::cout << "| ID = " << x << " is not in the database";
		for (int i = 0; i < 29 - int(to_string(x).length()); i++){
			std::cout << " ";
		}
			std::cout << "|" << '\n';

	std::cout << "+----------------------------------------------------------+" << '\n';
}
}

bool Item::checkID(int x){
bool tmp = false;
	(x == ID) ? (tmp =  true) : (tmp = false);
	return tmp;
}

void Database::erase(string x){
	/*smaže položky databáze, které obsahují
	v některém z atributů text retezec, nic nevypisuje*/
	for (auto i = db.begin(); i != db.end(); i++){
		int k = i - db.begin();
		if (db[k]->checkForPhrase(x) == true){
		try {
			db.erase(i);
			i--;
		}
		catch(...){

		}
	}
}
}
void Database::sort(string a, string b){
if (b == "desc") reverse(db.begin(), db.end());
if(a == "name") {
	std::sort(db.begin(), db.end(), sort_name());
}
if(a == "year") {
	std::sort(db.begin(), db.end(), sort_year());
}

if (b == "desc") reverse(db.begin(), db.end());
}

// constructor of the Item class
Item::Item(std::string a, std::string b){
Item::name = a;
Item::year = b;
Item::ID = id;
id++;
}

Item::~Item(){

}

void Item::printItem(){

}

bool Item::checkForPhrase(string x){
bool found = false;

return found;
}

bool Book::checkForPhrase(string x){
	bool found = false;
	if (name.find(x) != std::string::npos){
		found = true;
	}
	if (year.find(x) != std::string::npos){
		found = true;
	}
	if (author.find(x) != std::string::npos){
		found = true;
	}


	return found;
}

bool Journal::checkForPhrase(string x){
	bool found = false;
	if (name.find(x) != std::string::npos){
		found = true;
	}
	if (year.find(x) != std::string::npos){
		found = true;
	}
	if (volume.find(x) != std::string::npos){
		found = true;
	}
	if (issue.find(x) != std::string::npos){
		found = true;
	}
	return found;
}

Journal::Journal(string a, string b, string c, string d):Item(a, d){
	Journal::volume = b;
	Journal::issue = c;
}

void Journal::printItem(){
	std::cout << "+----+-----------------------------------------------------+" << '\n';
	std::cout << "|  " << ID << " | " << name;
	for (int i = 0; i < 52-(int)name.length(); i++){
		std::cout << " ";
	}
	std::cout << "|" << '\n';

	std::cout << "|    | " << year << ", " << volume << "(" << issue << ")";
	for (int i = 0; i < 48-(int)year.length()-(int)volume.length()-(int)issue.length(); i++){
		std::cout << " ";
	}
	std::cout << "|" << '\n';
}

Book::Book(string a, string b, string c):Item(a,c){
Book::author = b;
}

void Book::printItem(){
	std::cout << "+----+-----------------------------------------------------+" << '\n';
	std::cout << "|  " << ID << " | " << name;
	for (int i = 0; i < 52-int(name.length()); i++){
		std::cout << " ";
	}
	std::cout << "|" << '\n';

	std::cout << "|    | " << year << ", " << author;
	for (int i = 0; i < 50-int(author.length())-(int)year.length(); i++){
		std::cout << " ";
	}
	std::cout << "|" << '\n';
}
Database::~Database(){
	for (auto i = db.begin(); i != db.end(); i++)
		delete *i;
	db.clear();
}

void unknownCommand(string x){
	std::cout << "+----------------------------------------------------------+" << '\n';
	std::cout << "| Unknown command \"" << x << "\"";
	for (int i = 0; i < 39-(int)x.length(); i++) {
		std::cout << " ";
	}
	std::cout << "|" << '\n';
	std::cout << "+----------------------------------------------------------+" << '\n';
}

void noArgument(string x){
	std::cout << "+----------------------------------------------------------+" << '\n';
	std::cout << "| Command \"" << x << "\" expects some argument";
	for (int i = 0; i < 25-(int)x.length(); i++) {
		std::cout << " ";
	}
	std::cout << "|" << '\n';
	std::cout << "+----------------------------------------------------------+" << '\n';
}



int main() {
	Database db;
	db.add(new Journal("IEEE Transaction on Computers", "C-35", "10", "1986"));
	db.add(new Journal("IEEE Transaction on Computers", "C-35", "11", "1986"));
	db.add(new Journal("IEEE Transactions on Communications", "28", "8", "1980"));

	db.add(new Book("Dva roky prazdnin", "Jules Verne", "1888"));
	db.add(new Book("Tajuplny ostrov", "Jules Verne", "1874"));
	db.add(new Book("Ocelove mesto", "Jules Verne", "1879"));

	std::string a;
	while (std::getline(std::cin, a)) {
		size_t position;
		if ((position = a.find(":")) == std::string::npos) {
			if (a == "list"){
				db.list();

			}
			else {
				if (a == "find"){
					noArgument(a);
				}
				else if (a == "erase"){
					noArgument(a);
				}
				else if(a == "remove"){
					noArgument(a);
				}
				else if(a == "sort"){
					noArgument(a);
				}
				else{
				unknownCommand(a);
			}
			}
		}
		else {
			std::string command = a.substr(0, position);
			std::string argument = a.substr(position+1);
			if (command == "find"){
				db.find (argument);
			}
			else if (command == "remove"){
				int tmp;
				try{
					tmp =	stoi(argument);
				}
				catch(std::invalid_argument& e){

				}
				db.remove(tmp);

			}
			else if(command == "erase"){
				db.erase(argument);
			}
			else if(command == "sort"){
				size_t argPosition;
				if ((argPosition = argument.find(":")) == std::string::npos) {
					db.sort(argument);
				}
				else{
					std::string argument1 = argument.substr(0, position);
					std::string argument2 = argument.substr(position+1);
					db.sort(argument1, argument2);
				}
			}
			else {
				std::cout << "unnown command " << command << '\n';
			}
		}

	}
	return 0;
}
