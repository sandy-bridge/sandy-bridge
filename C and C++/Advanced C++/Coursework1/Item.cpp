#include "Main.h"

extern default_random_engine Generator;
extern uniform_int_distribution<int> GroupDistribution;
extern uniform_int_distribution<int> SubgroupDistribution;
const Date Item::Begin = Date(1, 1, 2018), Item::End = Date(31, 12, 2018);

Item::Item() 
{  // creates a pseudo-random item
	Group = (char)GroupDistribution(Generator);
	Subgroup = SubgroupDistribution(Generator);
	Name = ::CreateRandomName();
	Timestamp = Date::CreateRandomDate(Begin, End);
}

Item::Item(char c, int i, string s, Date timestamp)
{
	Group = c;
	Subgroup = i;
	Name = s;
	Timestamp = timestamp;
}

Item::Item(const Item& Original)
{
	Group = Original.Group;
	Subgroup = Original.Subgroup;
	Timestamp = Original.Timestamp;
	Name = Original.Name;
}

Item::~Item()
{
}

char Item::GetGroup() const
{
	return this->Group;
}

int Item::GetSubgroup() const
{
	return this->Subgroup;
}

string Item::GetName() const
{
	return this->Name;
}

Date Item::GetTimestamp() const
{
	return this->Timestamp;
}

bool Item::operator==(const Item& Right) const
{
	if (this->Group != Right.Group) {
		return false;
	}
	if (this->Subgroup != Right.Subgroup) {
		return false;
	}
	if (this->Name != Right.Name) {
		return false;
	}
	if (this->Timestamp != Right.Timestamp) {
		return false;
	}
	return true;
}

bool Item::operator<(const Item& Right) const
{
	if (Name < Right.Name) {
		return true;
	}
	return false;
}

// To do
