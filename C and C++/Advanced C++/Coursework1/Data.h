#pragma once
class Data
{
private:
	map<char, map<int, set<Item> >*> DataStructure;
	optional<Item> InsertItemObject(Item);
public:
	Data(int n);
	Data();
	~Data();
	void PrintAll();
	int CountItems();
	optional<Item> InsertItem(char c, int i, string s, optional<Date> d = nullopt);
	optional<Item> GetItem(char c, int i, string s);
	void PrintItem(char c, int i, string s);
	map<int, set<Item>>* GetGroup(char c);
	void PrintGroup(char c);
	int CountGroupItems(char c);
	set<Item>* GetSubGroup(char c, int i);
	void PrintSubgroup(char c, int i);
	int CountSubgroupItems(char c, int i);
	bool RemoveItem(char c, int i, string s);
	bool RemoveSubgroup(char c, int i);
	bool RemoveGroup(char c);
	set<Item>* InsertSubgroup(char c, int i, initializer_list<tuple<string, optional<Date>>> items);
	map<int, set<Item>>* InsertGroup(char c, initializer_list<int> subgroups, initializer_list<initializer_list<tuple<string, optional<Date>>>> items);
};

