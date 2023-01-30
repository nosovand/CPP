#include <vector>
#include <string>

#ifndef __MAIN_HPP__
#define __MAIN_HPP__

struct sort_name;
using namespace std;

class Item {
	protected:
		int ID;
		std::string name, year;
	public:
		Item (std::string a, std::string b);
		virtual ~Item ();
		bool sort_name(const Item* b) const;
		bool sort_year(const Item* b) const;
		//virtual bool sort_year(int x);
		virtual void printItem();
		virtual bool checkForPhrase(string x);
		virtual bool checkID(int x);
};

// Book related to the Database
class Book : public Item{
std::string author;
public:
	Book(string a, string b, string c);
	void printItem();
	bool checkForPhrase(string x);
};

// Journal related to the Database
class Journal : public Item{
std::string volume, issue;
public:
	Journal(string a, string b, string c, string d);
	void printItem();
	bool checkForPhrase(string x);
};

// declaration of the sort function according to name
struct sort_name {
	inline bool operator() (const Item *a, const Item * b);
};

struct sort_year {
	inline bool operator() (const Item *a, const Item * b);
};

class Database {
	private:
		std::vector<Item *> db;
	public:
		Database ();
		~Database();
		void add(Item * a);
		void find(string x);
		void list();
		void remove(int x);
		void erase(string x);
		void sort(string a, string b = " ");
		Item* getItem(int x){
			return db[x];
		}

};

#endif // __MAIN_HPP__
