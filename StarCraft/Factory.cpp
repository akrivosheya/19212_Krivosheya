#include "Factory.h"

Factory::Factory() = default;
Factory::~Factory() = default;

Factory* Factory::getInstance(){
	static Factory f;
	return &f;
}

Unit* Factory::makeUnit(const std::string& name) {
	creator_t c = creators_.at(name);
	return c();
}

void Factory::addCreator(const std::string& name, creator_t c) {
	creators_.insert(name, c);
}
