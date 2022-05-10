#pragma once
#include <iostream>

using namespace std;

typedef struct XOR_List_elem {
	int value = NULL;
	uintptr_t pointer = NULL;
};

class XOR_List
{
	XOR_List_elem* prv, * act, * nxt;
	XOR_List_elem* head, * tail;
	int number_of_list_elements;

public:
	XOR_List();
	~XOR_List();

	void actual();
	void next();
	void prev();

	void add_beg(int);
	void add_end(int);
	void add_act(int);

	void del_beg();
	void del_end();
	void del_act();
	void del_val(int);

	void print_forward();
	void print_backward();
private:
	void add(int, XOR_List_elem*, XOR_List_elem*, XOR_List_elem*);
	void print_value(XOR_List_elem*);
	XOR_List_elem* pointer_count(XOR_List_elem*, XOR_List_elem*);
	uintptr_t xor_pointer_count(XOR_List_elem*, XOR_List_elem*);
	void test();
	void help_next();
	void help_prev();
	void del(XOR_List_elem*, XOR_List_elem*, XOR_List_elem*);
};