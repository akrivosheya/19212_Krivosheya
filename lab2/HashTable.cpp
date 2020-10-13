#include "HashTable.h"

HashTable::HashTable() : _size(defaultSize), _count(0), tab(new HashTable::Creator* [_size]) {
	std::fill(tab, tab + _size, nullptr);
}

HashTable::~HashTable() {
	DeleteTable(tab, _size);
}

HashTable::HashTable(const HashTable& b) : _size(b._size), _count(b._count), tab(new Creator* [_size]) {
	std::fill(tab, tab + _size, nullptr);
	for (size_t i = 0; i < _size; ++i) {
		CopyChain(tab[i], b.tab[i]);
	}
}

void HashTable::swap(HashTable& b) {
	Creator** ttab = tab;
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
	tab = new Creator * [_size];
	std::fill(tab, tab + _size, nullptr);
	for (size_t i = 0; i < _size; ++i) {
		CopyChain(tab[i], b.tab[i]);
	}
	return *this;
}

void HashTable::clear() {
	DeleteTable(tab, _size);
	tab = new Creator * [defaultSize];
	std::fill(tab, tab + _size, nullptr);
	_count = 0;
}

bool HashTable::insert(const Key& k, const creator_t& v) {
	if (_count / (double)_size > 1.0) {
		IncreaseTab();
	}
	size_t i = Hash(k, _size);
	Creator* stud = new Creator{ k, v, nullptr };
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

creator_t& HashTable::operator[](const Key& k) {
	size_t i = Hash(k, _size);
	if (!contains(k)) {
		creator_t v;
		Creator* cr = new Creator{ k, v, nullptr };
		Push(tab[i], cr);
		++_count;
		return cr->param;
	}
	return Get(tab[i], k);
}

creator_t& HashTable::at(const Key& k) {
	size_t i = Hash(k, _size);
	try {
		return Get(tab[i], k);
	}
	catch (int) {
		throw err;
	}
}
const creator_t& HashTable::at(const Key& k) const {
	size_t i = Hash(k, _size);
	try {
		return Get(tab[i], k);
	}
	catch (int) {
		throw err;
	}
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
	HashTable::Creator* crA = nullptr;
	for (size_t i = 0, N = a._size; i < N; ++i) {
		if ((!a.tab[i] && b.tab[i]) || (a.tab[i] && !b.tab[i])) {
			return false;
		}
		crA = a.tab[i];
		while (crA) {
			if (!CompareCreator(crA, b.tab[i])) {
				return false;
			}
			crA = crA->next;
		}
	}
	return true;
}

bool operator!=(const HashTable& a, const HashTable& b) {
	return !(a == b);
}

void HashTable::Free(Creator* cr) {
	if (cr == nullptr) {
		return;
	}
	Free(cr->next);
	delete cr;
}

void HashTable::DeleteTable(Creator** trash, size_t lim) {
	for (size_t i = 0; i < lim; ++i) {
		Free(trash[i]);
	}
	delete[] trash;
}

bool HashTable::CopyChain(Creator*& to, Creator*& from) {
	if (!from) {
		return true;
	}
	to = new Creator{ from->name, from->param, nullptr };
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

bool HashTable::Push(Creator*& to, Creator* cr) {
	if (to == nullptr) {
		to = cr;
		return true;
	}
	else if (to->name != cr->name && Push(to->next, cr)) {
		return true;
	}
	else {
		return false;
	}
}

HashTable::Creator* HashTable::TakeFirstCreator(Creator*& from) {
	if (!from) {
		return nullptr;
	}
	Creator* cr = from;
	from = from->next;
	cr->next = nullptr;
	return cr;
}

void HashTable::IncreaseTab(void) {
	Creator** newTab = new Creator * [_size * mul];
	std::fill(newTab, newTab + _size * mul, nullptr);
	Creator* cr = nullptr;
	for (size_t i = 0, k; i < _size; ++i) {
		cr = TakeFirstCreator(tab[i]);
		while (cr) {
			k = Hash(cr->name, _size * mul);
			Push(newTab[k], cr);
			cr = TakeFirstCreator(tab[i]);
		}
	}
	DeleteTable(tab, _size);
	tab = newTab;
	_size = _size * mul;
}

bool HashTable::FindAndErase(Creator*& cr, const Key& k) {
	if (!cr) {
		return false;
	}
	else if (cr->name != k) {
		return FindAndErase(cr->next, k);
	}
	else {
		Creator* next = cr->next;
		delete cr;
		cr = next;
		return true;
	}
}

bool HashTable::Find(Creator* cr, const Key& k) const {
	if (cr == nullptr) {
		return false;
	}
	else if (cr->name != k) {
		return Find(cr->next, k);
	}
	else {
		return true;
	}
}

const creator_t& HashTable::Get(Creator* cr, const Key& k) const {
	while (cr) {
		if (cr->name == k) {
			return cr->param;
		}
		else {
			cr = cr->next;
		}
	}
	throw err;
}

creator_t& HashTable::Get(Creator* cr, const Key& k) {
	while (cr) {
		if (cr->name == k) {
			return cr->param;
		}
		else {
			cr = cr->next;
		}
	}
	throw err;
}

bool CompareCreator(HashTable::Creator* a, HashTable::Creator* b) {
	while (b) {
		if (a->name != b->name) {
			b = b->next;
			continue;
		}
		else if (a->param == b->param) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
