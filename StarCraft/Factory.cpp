#include "Factory.h"

Unit* Factory::makeUnit(const std::string& name) {
	creator_t c = creators_.at(name);
	return c();
}

void Factory::addCreator(const std::string& name, creator_t c) {
	creators_.insert(name, c);
}
