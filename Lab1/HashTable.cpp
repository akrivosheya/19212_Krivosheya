#include "HashTable.h"
#include <iostream>

HashTable::HashTable() : _size(defaultSize), _count(0), tab(new HashTable::Student* [_size]) {
	std::fill(tab, tab + _size, nullptr);
}

HashTable::~HashTable() {
	DeleteTable(tab, _size);
}

HashTable::HashTable(const HashTable& b) : _size(b._size), _count(b._count), tab(new Student* [_size]) {
	std::fill(tab, tab + _size, nullptr);
	for (size_t i = 0; i < _size; ++i) {
		CopyChain(tab[i], b.tab[i]);
	}
}

void HashTable::swap(HashTable& b) {
	Student** ttab = tab;
	size_t tsize = _size;
	size_t tcount = _count;
	tab = b.tab;
	_size = b._size;
	_count = b._count;
	b.tab = ttab;
	b._size = tsize;
	b._count = tcount;
}

HashTable& HashTable::operator=(const HashTable& b) {
	if (this == &b) {
		return *this;
	}
	DeleteTable(tab, _size);
	_size = b._size;
	_count = b._count;
	tab = new Student * [_size];
	std::fill(tab, tab + _size, nullptr);
	for (size_t i = 0; i < _size; ++i) {
		CopyChain(tab[i], b.tab[i]);
	}
	return *this;
}

void HashTable::clear() {
	DeleteTable(tab, _size);
	tab = new Student * [defaultSize];
	std::fill(tab, tab + _size, nullptr);
	_count = 0;
}

bool HashTable::insert(const Key& k, const Value& v) {
	if (_count / (double)_size > 1.0) {
		IncreaseTab();
	}
	size_t i = Hash(k, _size);
	Student* stud = new Student{ k, v, nullptr };
	if (Push(tab[i], stud)) {
		++_count;
		return true;
	}
	else {
		delete stud;
		return false;
	}
}

bool HashTable::erase(const Key& k) {
	size_t i = Hash(k, _size);
	if (!FindAndErase(tab[i], k)) {
		return false;
	}
	--_count;
	return true;
}

bool HashTable::contains(const Key& k) {
	size_t i = Hash(k, _size);
	if (!Find(tab[i], k)) {
		return false;
	}
	return true;
}

Value& HashTable::operator[](const Key& k) {
	size_t i = Hash(k, _size);
	if (!contains(k)) {
		Value v;
		Student* stud = new Student{ k, v, nullptr };
		Push(tab[i], stud);
		++_count;
		return stud->param;
	}
	return Get(tab[i], k);
}

Value& HashTable::at(const Key& k) {
	size_t i = Hash(k, _size);
	return Get(tab[i], k);
}
const Value& HashTable::at(const Key& k) const {
	size_t i = Hash(k, _size);
	return Get(tab[i], k);
}

size_t HashTable::size() const {
	return _size;
}
bool HashTable::empty() const {
	if (_count) {
		return false;
	}
	return true;
}

bool operator==(const HashTable& a, const HashTable& b) {
	if (a._size != b._size || a._count != b._count) {
		return false;
	}
	HashTable::Student* studA = nullptr;
	for (size_t i = 0, N = a._size; i < N; ++i) {
		if ((!a.tab[i] && b.tab[i]) || (a.tab[i] && !b.tab[i])) {
			return false;
		}
		studA = a.tab[i];
		while (studA) {
			if (!CompareStudent(studA, b.tab[i])) {
				return false;
			}
			studA = studA->next;
		}
	}
	return true;
}

bool operator!=(const HashTable& a, const HashTable& b) {
	return !(a == b);
}

void HashTable::Free(Student* stud) {
	if (stud == nullptr) {
		return;
	}
	Free(stud->next);
	delete stud;
}

void HashTable::DeleteTable(Student** trash, size_t lim) {
	for (size_t i = 0; i < lim; ++i) {
		Free(trash[i]);
	}
	delete[] trash;
}

bool HashTable::CopyChain(Student*& to, Student*& from) {
	if (!from) {
		return true;
	}
	to = new Student{ from->name, from->param, nullptr };
	return CopyChain(to->next, from->next);
}

size_t HashTable::Hash(const Key& k, size_t div) const {
	size_t res = 0;
	int lim = k.size();
	for (int i = 0; i < lim; ++i) {
		res = (res * 31 + k[i]) % div;
	}
	return res;
}

bool HashTable::Push(Student*& to, Student* stud) {
	if (to == nullptr) {
		to = stud;
		return true;
	}
	else if (to->name != stud->name && Push(to->next, stud)) {
		return true;
	}
	else {
		return false;
	}
}

HashTable::Student* HashTable::TakeFirstStudent(Student*& from) {
	if (!from) {
		return nullptr;
	}
	Student* stud = from;
	from = from->next;
	stud->next = nullptr;
	return stud;
}

void HashTable::IncreaseTab(void) {
	Student** newTab = new Student * [_size * mul];
	std::fill(newTab, newTab + _size * mul, nullptr);
	Student* stud = nullptr;
	for (size_t i = 0, k; i < _size; ++i) {
		stud = TakeFirstStudent(tab[i]);
		while (stud) {
			k = Hash(stud->name, _size * mul);
			Push(newTab[k], stud);
			stud = TakeFirstStudent(tab[i]);
		}
	}
	DeleteTable(tab, _size);
	tab = newTab;
	_size = _size * mul;
}

bool HashTable::FindAndErase(Student*& stud, const Key& k) {
	if (!stud) {
		return false;
	}
	else if (stud->name != k) {
		return FindAndErase(stud->next, k);
	}
	else {
		Student* next = stud->next;
		delete stud;
		stud = next;
		return true;
	}
}

bool HashTable::Find(Student* stud, const Key& k) const {
	if (stud == nullptr) {
		return false;
	}
	else if (stud->name != k) {
		return Find(stud->next, k);
	}
	else {
		return true;
	}
}

Value& HashTable::Get(Student*& stud, const Key& k) const {
	if (stud && stud->name == k) {
		return stud->param;
	}
	else if (stud) {
		return Get(stud->next, k);
	}
}

Value& HashTable::Get(Student*& stud, const Key& k) {
	if (stud && stud->name == k) {
		return stud->param;
	}
	else if (stud) {
		return Get(stud->next, k);
	}
}

bool CompareStudent(HashTable::Student* a, HashTable::Student* b) {
	while (b) {
		if (a->name != b->name) {
			b = b->next;
			continue;
		}
		else if (a->param.age == b->param.age && a->param.weight == b->param.weight) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
