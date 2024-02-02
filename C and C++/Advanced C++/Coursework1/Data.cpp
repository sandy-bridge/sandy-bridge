#include "Main.h"

optional<Item> Data::InsertItemObject(Item item)
{
	if (DataStructure.find(item.GetGroup()) == DataStructure.end()) {
		DataStructure[item.GetGroup()] = new map<int, set<Item>>;
	}
	auto group = DataStructure.find(item.GetGroup())->second;
	auto existing_item = find_if((*group)[item.GetSubgroup()].begin(), (*group)[item.GetSubgroup()].end(), [&](auto x) -> bool { return x.GetName() == item.GetName(); });
	if (existing_item != (*group)[item.GetSubgroup()].end()) {
		return nullopt;
	}
	existing_item = find_if((*group)[item.GetSubgroup()].begin(), (*group)[item.GetSubgroup()].end(), [&](auto x) -> bool { return x.GetTimestamp() == item.GetTimestamp(); });
	if (existing_item != (*group)[item.GetSubgroup()].end()) {
		return nullopt;
	}
	auto result = (*group)[item.GetSubgroup()].insert(item);
	if (result.second == true) {
		return item;
	}
	return nullopt;
}

Data::Data(int n)
{
	for (int i = 0; i < n; i++) {
		Item item;
		InsertItemObject(item);
	}
}

Data::Data()
{
}

Data::~Data()
{
	for (auto g : DataStructure) {
		delete(g.second);
	}
}

void Data::PrintAll()
{
	for (const auto& m : DataStructure) {
		cout << m.first << ":\n"; //group name
		for (const auto& g : *(m.second)) {
			cout << g.first << ": "; //subgroup name
			for (auto it = g.second.begin(); it != g.second.end();) {
				char* monthName = new char[4];
				it->GetTimestamp().GetMonth(monthName, 4);
				cout << it->GetName() << " " << it->GetTimestamp().GetDay() << " " << monthName << " " << it->GetTimestamp().GetYear();
				delete[] monthName;
				if (++it != g.second.end()) {
					cout << "; ";
				}
				else {
					cout << endl;
				}
			}
		}
	}
}
int Data::CountItems()
{
	int counter = 0;
	for (const auto& m : DataStructure) {
		for (const auto& g : *(m.second)) {
			for (const auto& s : g.second) {
				counter++;
			}
		}
	}
	return counter;
}
optional<Item> Data::InsertItem(char c, int i, string s, optional<Date> d)
{
	if (s == "" || c < 65 || c > 90 || i < 0 || i > 99) {
		return nullopt;
	}
	if (!d.has_value()) {
		d = Date::CreateRandomDate(Item::Begin, Item::End);
	}
	Item item(c, i, s, d.value());
	return InsertItemObject(item);
}

optional<Item> Data::GetItem(char c, int i, string s)
{
	if (DataStructure.find(c) != DataStructure.end()) {
		if (DataStructure.find(c)->second->find(i) != DataStructure.find(c)->second->end()) {
			auto items = DataStructure.find(c)->second->find(i);
			if (items != DataStructure.find(c)->second->end()) {
				auto item = find_if(items->second.begin(), items->second.end(), [&](auto x) -> bool { return x.GetName() == s; });
				if (item != items->second.end()) {
					return *item;
				}
			}
		}
	}
	return nullopt;
}
void Data::PrintItem(char c, int i, string s)
{
	if (DataStructure.find(c) != DataStructure.end()) {
		if (DataStructure.find(c)->second->find(i) != DataStructure.find(c)->second->end()) {
			auto items = DataStructure.find(c)->second->find(i);
			if (items != DataStructure.find(c)->second->end()) {
				auto item = find_if(items->second.begin(), items->second.end(), [&](auto x) -> bool { return x.GetName() == s; });
				if (item != items->second.end()) {
					char* monthName = new char[4];
					item->GetTimestamp().GetMonth(monthName, 4);
					cout << item->GetName() << " " << item->GetTimestamp().GetDay() << " " << monthName << " " << item->GetTimestamp().GetYear() << endl;
					delete[] monthName;
					return;
				}
			}
		}
	}
	throw invalid_argument(string("Item not found!\n"));
}

map<int, set<Item>>* Data::GetGroup(char c)
{
	if (DataStructure.find(c) != DataStructure.end()) {
		return DataStructure.find(c)->second;
	}
	return nullptr;
}

void Data::PrintGroup(char c)
{
	auto m = DataStructure.find(c);
	if (m == DataStructure.end()) {
		throw invalid_argument(string("Group not found!"));
	}
	for (const auto& g : *(m->second)) {
		cout << g.first << ": "; //subgroup name
		for (auto it = g.second.begin(); it != g.second.end();) {
			char* monthName = new char[4];
			it->GetTimestamp().GetMonth(monthName, 4);
			cout << it->GetName() << " " << it->GetTimestamp().GetDay() << " " << monthName << " " << it->GetTimestamp().GetYear();
			delete[] monthName;
			if (++it != g.second.end()) {
				cout << "; ";
			}
			else {
				cout << endl;
			}
		}
	}
}

int Data::CountGroupItems(char c)
{
	int counter = 0;
	auto m = DataStructure.find(c);
	for (const auto& g : *(m->second)) {
		for (const auto& s : g.second) {
			counter++;
		}
	}
	return counter;
}

set<Item>* Data::GetSubGroup(char c, int i)
{
	if (DataStructure.find(c) != DataStructure.end()) {
		if (DataStructure.find(c)->second->find(i) != DataStructure.find(c)->second->end()) {
			return &DataStructure.find(c)->second->find(i)->second;
		}
	}
	return nullptr;
}

void Data::PrintSubgroup(char c, int i)
{
	if (DataStructure.find(c) != DataStructure.end()) {
		if (DataStructure.find(c)->second->find(i) != DataStructure.find(c)->second->end()) {
			for (const auto& it : DataStructure.find(c)->second->find(i)->second) {
				char* monthName = new char[4];
				it.GetTimestamp().GetMonth(monthName, 4);
				cout << it.GetName() << " " << it.GetTimestamp().GetDay() << " " << monthName << " " << it.GetTimestamp().GetYear() << endl;
				delete[] monthName;
			}
			return;
		}
	}
	throw invalid_argument(string("Subgroup not found!\n"));
}

int Data::CountSubgroupItems(char c, int i)
{
	int counter = 0;
	auto m = DataStructure.find(c);
	if (m != DataStructure.end()) {
		auto g = m->second->find(i);
		if (g != m->second->end()) {
			for (const auto& s : g->second) {
				counter++;
			}
		}
	}
	return counter;
}

bool Data::RemoveItem(char c, int i, string s)
{
	if ((this->GetItem(c, i, s)).has_value()) {
		if (DataStructure.find(c) != DataStructure.end()) {
			if (DataStructure.find(c)->second->find(i) != DataStructure.find(c)->second->end()) {
				auto items = DataStructure.find(c)->second->find(i);
				if (items != DataStructure.find(c)->second->end()) {
					items->second.erase((this->GetItem(c, i, s)).value());
					if (items->second.empty()) {
						DataStructure.find(c)->second->erase(i);
					}
				}
				if (DataStructure.find(c)->second->empty()) {
					delete DataStructure.find(c)->second;
					DataStructure.erase(c);
				}
				return true;
			}
		}
	}
	return false;
}

bool Data::RemoveSubgroup(char c, int i)
{
	if (DataStructure.find(c) != DataStructure.end()) {
		if (DataStructure.find(c)->second->find(i) != DataStructure.find(c)->second->end()) {
			DataStructure.find(c)->second->erase(i);
			if (DataStructure.find(c)->second->empty()) {
				delete DataStructure.find(c)->second;
				DataStructure.erase(c);
			}
			return true;
		}
	}
	return false;
}

bool Data::RemoveGroup(char c)
{
	if (DataStructure.find(c) != DataStructure.end()) {
		delete DataStructure.find(c)->second;
		DataStructure.erase(c);
		return true;
	}
	return false;
}

set<Item>* Data::InsertSubgroup(char c, int i, initializer_list<tuple<string, optional<Date>>> items)
{
	if (c < 65 || c > 90 || i < 0 || i > 99) {
		return nullptr;
	}
	for (const auto& item : items) {
		if (get<0>(item) == "") {
			return nullptr;
		}
		if (this->GetItem(c, i, get<0>(item)) != nullopt) {
			return nullptr;
		}
	}
	if (DataStructure.find(c) == DataStructure.end()) {
		DataStructure[c] = new map<int, set<Item>>;
	}
	else if (DataStructure.find(c)->second->find(i) != DataStructure.find(c)->second->end()) {
		return nullptr;
	}
	for_each(items.begin(), items.end(), [&](const tuple <string, optional<Date>>& t) {this->InsertItem(c, i, get<0>(t), get<1>(t)); });
	return this->GetSubGroup(c, i);
}

map<int, set<Item>>* Data::InsertGroup(char c, initializer_list<int> subgroups, initializer_list<initializer_list<tuple<string, optional<Date>>>> items)
{
	if (DataStructure.find(c) != DataStructure.end()) {
		return nullptr;
	}
	if (subgroups.size() != items.size()) {
		return nullptr;
	}
	for (const auto& i : subgroups) {
		if (i < 0 || i > 99) {
			return nullptr;
		}
	}
	map<string, int> duplicates;
	for (const auto& sg_items : items) {
		for (const auto& item : sg_items) {
			if (get<0>(item) == "") {
				return nullptr;
			}
			duplicates[get<0>(item)]++;
		}
	}
	if (any_of(duplicates.begin(), duplicates.end(), [](auto it) -> bool { return it.second > 1; })) {
		return nullptr;
	}
	DataStructure[c] = new map<int, set<Item>>;
	auto i = subgroups.begin();
	auto subgroup_items = items.begin();
	for (; i != subgroups.end() && subgroup_items != items.end(); ++i, ++subgroup_items) {
		this->InsertSubgroup(c, *i, *subgroup_items);
	}
	return DataStructure[c];
}


