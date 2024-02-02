#pragma once

class Item
{
private:
	char Group;     // Any from range 'A'...'Z'
	int Subgroup;   // Any from range 0...99
	string Name;    // Any, but not empty 
	Date Timestamp; // Any 
	
public:
	static const Date Begin;
	static const Date End;
	Item();
	Item(char, int, string, Date);
	Item(const Item &);
	~Item();
	char GetGroup() const;
	int GetSubgroup() const;
	string GetName() const;
	Date GetTimestamp() const;
	bool operator==(const Item&) const;
	bool operator<(const Item&) const;
// To do
};

