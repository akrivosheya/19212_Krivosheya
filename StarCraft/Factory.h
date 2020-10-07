#include "Unit.h"

typedef Unit* (*creator_t)();

class Factory {
public:
	
	Unit* makeUnit(const std::string& name);

	void addCreator(const std::string& name, creator_t c);
	
	static Factory* getInstance();

private:
	Factory();
	~Factory();
	Factory(const Factory&);
	Factory& operator=(const Factory&);
	HashTable creators_;//???????????????
};
