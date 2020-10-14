#include "Factory.h"

Factory::Factory() = default;
Factory::~Factory() = default;

Factory* Factory::getInstance(){
}

Unit* Factory::makeUnit(const std::string& name) 

void Factory::addCreator(const std::string& name, creator_t c) 
