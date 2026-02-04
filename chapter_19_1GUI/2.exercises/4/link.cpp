

#include "link.h"

//------------------------------------------------------------------------------

bool operator<(const God& a, const God& b)
{ return a.name < b.name; }

bool operator>(const God& a, const God& b)
{ return a.name > b.name; }

bool operator==(const God& a, const God& b)
{
	return      a.name == b.name
		&& a.mythology == b.mythology
		&& a.transport == b.transport
		   && a.weapon == b.weapon;
}

bool operator!=(const God& a, const God& b)
{ return  !( a == b ); }

ostream& operator<<(ostream& ost, const God& g)
{
	ost << "{ " << g.name << ", " << g.mythology << ", " << g.transport << ", " << g.weapon << " }";
	return ost;
}

//------------------------------------------------------------------------------

