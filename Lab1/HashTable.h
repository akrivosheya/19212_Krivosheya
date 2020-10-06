#pragma once
#include <iostream>

typedef std::string Key;

struct Value {
	unsigned age = 18;
	unsigned weight = 80;
};

class HashTable {
public:
	HashTable();

	~HashTable();

	HashTable(const HashTable& b);

	void swap(HashTable& b);

	HashTable& operator=(const HashTable& b);

	void clear();

	bool insert(const Key& k, const Value& v);

	bool erase(const Key& k);

	bool contains(const Key& k);

	Value& operator[](const Key& k);

	Value& at(const Key& k);
	const Value& at(const Key& k) const;

	size_t size() const;
	bool empty() const;

	friend bool operator==(const HashTable& a, const HashTable& b);

	friend bool operator!=(const HashTable& a, const HashTable& b);

private:
	static constexpr int defaultSize = 8;
	static constexpr int mul = 2;
	size_t _size;
	size_t _count;
	struct Student {
		Key name;
		Value param;
		Student* next;
	};
	Student** tab;

	void Free(Student* stud);

	void DeleteTable(Student** trash, size_t lim);

	bool CopyChain(Student*& to, Student*& from);

	size_t Hash(const Key& k, size_t div) const;

	bool Push(Student*& to, Student* stud);

	Student* TakeFirstStudent(Student*& from);

	void IncreaseTab(void);

	bool FindAndErase(Student*& stud, const Key& k);

	bool Find(Student* stud, const Key& k) const;

	Value& Get(Student*& stud, const Key& k) const;

	Value& Get(Student*& stud, const Key& k);

	friend bool CompareStudent(HashTable::Student* a, HashTable::Student* b);
};
