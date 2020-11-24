#include <string>
#include <iostream>
#include <unordered_map>


// A. Alexandrescu "Modern Design in C++"
// "Современное проектирование на Си++"
template<class Product, class Id>
struct DefaultErrorPolicy {
	static Product* IdNotFound(const Id& name) {
		std::cerr << "Id not found!" << name << std::endl;
		return nullptr;
	}
};
template <class Product, class Id, class Creator, class ErrorPolicy = DefaultErrorPolicy<Product, Id>>
class Factory {
public:

	Product* makeStrategy(const Id& name) {
		auto it = creators_.find(name);
		if (it == creators_.end()) {
			return ErrorPolicy::IdNotFound(name);
		}

		return it->second();
	}
	void addCreator(const Id& name, Creator c) {
		creators_.insert({ name, c });
	}

	static Factory* getInstance() {
		static Factory f;
		return &f;
	}
private:
	Factory() = default;
	~Factory() = default;
	Factory(const Factory&);
	Factory& operator=(const Factory&);


	std::unordered_map<Id, Creator>  creators_;
};
