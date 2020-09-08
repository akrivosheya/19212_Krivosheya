#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define OF 0 //OverFlow

class Array {

private:
	int* mem;
	size_t next;
	size_t size;

public:
	~Array() {
		delete[] mem;
		printf("deleted\n");
	}

	Array() {
		size = 1;
		next = 0;
		mem = new int[1];
	}

	void Copy(int* to, int* from, int until) {
		for (int i = 0; i < until; ++i) {
			to[i] = from[i];
		}
	}

	Array(Array& from) {
		size = from.size;
		next = from.next;
		mem = new int[size];
		Copy(mem, from.mem, next);
	}

	int FixArray() {
		int* tmp = new int[size * 2];
		if (tmp) {
			Copy(tmp, mem, next);
			delete[] mem;
			mem = tmp;
			size *= 2;
			return OK;
		}
		else {
			return OF;
		}
	}

	void ReadArray() {
		if (!mem) {
			return;
		}
		int count, numb = 0;
		if (scanf_s("%d", &count) == EOF) {
			return;
		}
		while (count && scanf_s("%d", &numb) != EOF) {
			if (numb == -1) {
				break;
			}
			else if (next >= size) {
				if (!FixArray()) {
					printf("Error: overflow");
					break;
				}
			}
			mem[next++] = numb;
			--count;
		}
	}

	void PrintArray() {
		if (!mem) {
			printf("empty");
		}
		for (int el = 0; el < next; ++el) {
			printf("%d\n", mem[el]);
		}
	}

	void operator= (const Array& right) {
		if (this == &right){
			return;
		}
		next = (right.next >= size) ? size : right.next;
		for (int i = 0; i < next; ++i) {
			mem[i] = right.mem[i];
		}
	}

	int operator[] (int index) {
		if (next == 0) {
			return 0;
		}
		else if (index >= int(next)) {
			return mem[next - 1];
		}
		else if (index < 0) {
			index = 0;
		}
		return mem[index];
	}
};


int main()
{
	Array a;
	a.ReadArray();
	printf("%d %d %d", a[3], a[-2], a[20]);
	Array b(a);
	b.PrintArray();
	Array c;
	c.ReadArray();
	a = c;
	a = a;
	a.PrintArray();
	return 0;
}

