#pragma once
#include <iostream>
#include "Strategy.h"

typedef std::string Key;
typedef Strategy* (*creator_t)();

class HashTable {
public:
	HashTable();

	~HashTable();

	HashTable(const HashTable& b);

	void swap(HashTable& b);

	HashTable& operator=(const HashTable& b);

	void clear();

	bool insert(const Key& k, const creator_t& v);

	bool erase(const Key& k);

	bool contains(const Key& k);

	creator_t& operator[](const Key& k);

	creator_t& at(const Key& k);
	const creator_t& at(const Key& k) const;

	size_t size() const;
	bool empty() const;

	friend bool operator==(const HashTable& a, const HashTable& b);

	friend bool operator!=(const HashTable& a, const HashTable& b);

private:
	static constexpr int defaultSize = 8;
	static constexpr int mul = 2;
	static constexpr int err = -1;
	size_t _size;
	size_t _count;
	struct Creator {
		Key name;
		creator_t param;
		Creator* next;
	};
	Creator** tab;

	void Free(Creator* stud);

	void DeleteTable(Creator** trash, size_t lim);

	bool CopyChain(Creator*& to, Creator*& from);

	size_t Hash(const Key& k, size_t div) const;

	bool Push(Creator*& to, Creator* stud);

	Creator* TakeFirstCreator(Creator*& from);

	void IncreaseTab(void);

	bool FindAndErase(Creator*& stud, const Key& k);

	bool Find(Creator* stud, const Key& k) const;

	const creator_t& Get(Creator* stud, const Key& k) const;

	creator_t& Get(Creator* stud, const Key& k);

	friend bool CompareCreator(Creator* a, Creator* b);
};
