#include "XOR_List.h"

XOR_List::XOR_List() {
	prv = nullptr;
	act = nullptr;
	nxt = nullptr;

	head = nullptr;
	tail = nullptr;

	number_of_list_elements = 0;
}
XOR_List::~XOR_List() {
	int number_of_list_elements_to_delete = number_of_list_elements;
	for (int i = 0; i < number_of_list_elements_to_delete; i++)
		del_act();
}

void XOR_List::actual() {
	print_value(act);
	cout << endl;
}
void XOR_List::next() {
	help_next();
	actual();
}
void XOR_List::prev() {
	help_prev();
	actual();
}

void XOR_List::add_beg(int value) {
	add(value, tail, head, head);
}
void XOR_List::add_end(int value) {
	add(value, tail, head, tail);
	if (prv == nxt && prv != act) {
		XOR_List_elem* temp = tail;
		tail = head;
		head = temp;
	}
}
void XOR_List::add_act(int value) {
	add(value, prv, act, act);
}

void XOR_List::del_beg() {
	if (head != nullptr && tail != nullptr) {
		XOR_List_elem* head_next = pointer_count(tail, head);
		del(tail, head, head_next);
	}
}
void XOR_List::del_end() {
	if (head != nullptr && tail != nullptr) {
		XOR_List_elem* tail_prev = pointer_count(head, tail);
		del(tail_prev, tail, head);
	}
}
void XOR_List::del_act() {
	del(prv, act, nxt);
}
void XOR_List::del_val(int value) {
	if (act != nullptr) {
		while (1) {
			if (act != nullptr && act->value == value)
				del_act();
			else
				break;
		}

		XOR_List_elem* nxt_cache = nxt;
		while (act != nxt_cache) {
			if (act->value == value)
				del_act();
			else
				help_prev();
		}
		if (act!=nullptr && act->value == value)
			del_act();
		else
			help_prev();
	}
}

void XOR_List::print_forward() {
	if (act != nullptr) {
		XOR_List_elem* prev_cache = prv;
		XOR_List_elem* actual_cache = act;
		XOR_List_elem* next_cache = nxt;

		nxt = pointer_count(tail, head);
		act = head;
		prv = tail;

		print_value(act);
		while (act != tail) {
			help_next();
			cout << " ";
			print_value(act);
		}
		cout << endl;

		prv = prev_cache;
		act = actual_cache;
		nxt = next_cache;
	}
	else
		actual();
}
void XOR_List::print_backward() {
	if (act != nullptr) {
		XOR_List_elem* prev_cache = prv;
		XOR_List_elem* actual_cache = act;
		XOR_List_elem* next_cache = nxt;

		nxt = head;
		act = tail;
		prv = pointer_count(head, tail);

		print_value(act);
		while (act != head) {
			help_prev();
			cout << " ";
			print_value(act);
		}
		cout << endl;

		prv = prev_cache;
		act = actual_cache;
		nxt = next_cache;
	}
	else
		actual();
}

void XOR_List::add(int value, XOR_List_elem* prev, XOR_List_elem* next, XOR_List_elem* swap) {
	XOR_List_elem* elem = new XOR_List_elem;
	elem->value = value;
	elem->pointer = xor_pointer_count(prev, next);
	if (swap == nullptr) {
		prv = elem;
		act = elem;
		nxt = elem;
		head = elem;
		tail = elem;
	}
	else if (act == prv && act == nxt) {
		prev->pointer = NULL;
		next->pointer = NULL;
	}
	else if (number_of_list_elements == 2) {
		next->pointer = xor_pointer_count(elem, prev);
		prev->pointer = xor_pointer_count(next, elem);
	}
	else {
		XOR_List_elem* prev_prev = pointer_count(next, prev);
		XOR_List_elem* next_next = pointer_count(prev, next);
		prev->pointer = xor_pointer_count(prev_prev, elem);
		next->pointer = xor_pointer_count(elem, next_next);
	}

	if (prev == tail && next == head) {
		if (swap == head)
			head = elem;
		else if (swap == tail)
			tail = elem;
	}

	if (prev == act && next == nxt)
		nxt = elem;
	if (prev == prv && next == act)
		prv = elem;

	number_of_list_elements++;
}

void XOR_List::print_value(XOR_List_elem* elem) {
	if (elem == nullptr)
		cout << "NULL";
	else
		cout << elem->value;
}

XOR_List_elem* XOR_List::pointer_count(XOR_List_elem* x, XOR_List_elem* xy) {
	XOR_List_elem* pointer = (XOR_List_elem*)(((uintptr_t)(x)) ^ (xy->pointer));

	return pointer;
}
uintptr_t XOR_List::xor_pointer_count(XOR_List_elem* prev, XOR_List_elem* next) {
	uintptr_t pointer = ((uintptr_t)(prev)) ^ ((uintptr_t)(next));

	return pointer;
}

void XOR_List::test() {
	if (act != nullptr) {
		cout << prv->value << act->value << nxt->value << head->value << tail->value << endl;
		cout << prv->pointer << " " << act->pointer << " " << nxt->pointer << " " << head->pointer << " " << tail->pointer << " " << endl;
		cout << prv << " " << act << " " << nxt << " " << head << " " << tail << " " << endl;
		cout << endl;
	}
}

void XOR_List::help_next() {
	if (act != nullptr) {
		prv = act;
		act = nxt;
		nxt = pointer_count(prv, act);
	}
}
void XOR_List::help_prev() {
	if (act != nullptr) {
		nxt = act;
		act = prv;
		prv = pointer_count(nxt, act);
	}
}

void XOR_List::del(XOR_List_elem* prev, XOR_List_elem* to_delete, XOR_List_elem* next) {
	if (to_delete != nullptr) {
		if (to_delete == prev && to_delete == next) {
			prv = nullptr;
			act = nullptr;
			nxt = nullptr;
			head = nullptr;
			tail = nullptr;
		}
		else if (prev == next) {
			prev->pointer = NULL;
			prv = prev;
			act = prev;
			nxt = prev;
			head = prev;
			tail = prev;
		}
		else {
			XOR_List_elem* prev_prev = pointer_count(to_delete, prev);
			XOR_List_elem* next_next = pointer_count(to_delete, next);
			prev->pointer = xor_pointer_count(prev_prev, next);
			next->pointer = xor_pointer_count(prev, next_next);

			if (to_delete == act) {
				act = prev;
				prv = prev_prev;
			}
			if (to_delete == prv)
				prv = prev;
			if (to_delete == nxt)
				nxt = next;
			if (to_delete == head)
				head = next;
			if (to_delete == tail)
				tail = prev;
		}

		delete to_delete;
		number_of_list_elements--;
	}
}