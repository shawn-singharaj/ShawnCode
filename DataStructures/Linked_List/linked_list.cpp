#include "linked_list.hpp"
#include <iostream>

using std::cout;
using std::endl;

linked_list::linked_list(const linked_list& other) {
	this->length = other.length; // shallow copy
	
	if(other.head != nullptr){ // deep copy
		this->head = new node;
		this->head->val = other.head->val;
		
		node* itr = this->head;
		node* other_itr = other.head->next;
		while(other_itr != nullptr){ // copy linked list
			itr->next = new node;
			itr = itr->next;
			itr->val = other_itr->val;
			other_itr = other_itr->next;
		}
		itr->next = nullptr;
	}
	else{
		this->head = nullptr;
	}
}

linked_list& linked_list::operator=(const linked_list& other) {
	if(this == &other){
		return *this;
	}

	clear();

	if(other.head==nullptr){ // deep copy
		head = nullptr;
	}
	else{
		head = new node;
		head->val = other.head->val;

		node* itr = this->head;
		node* other_itr = other.head->next;
		while(other_itr != nullptr){
			itr->next = new node;
			itr = itr->next;
			itr->val = other_itr->val;
			other_itr = other_itr->next;
		}
		itr->next = nullptr;
	}
	return *this;
}

linked_list::~linked_list() {
	if(this->head != nullptr){ // delete each node
		node* itr = this->head;
		while(itr != nullptr){
			node* next_node = itr->next;
			delete itr;
			itr = next_node;
		}
	}
}

int linked_list::get_length() {
	return this->length;
}

void linked_list::print() {
	node* itr = this->head;
	cout << " ";
    while(itr != nullptr){
        cout << itr->val << " ";
        itr = itr->next;
    }
}

void linked_list::clear() {
	while(head != nullptr){ // pop front every node
		pop_front();
	}
	
}

void linked_list::push_front(int value) {
	node* new_head = new node; // create new node
	new_head->val = value; // set new node to value from argument
	new_head->next = this->head;  // next pointer to current head
	this->head = new_head; // head set the the new node
	this->length++;
}

void linked_list::push_back(int value) {
	node* new_tail = new node; // create new node
	new_tail->val = value; // set new node to value from argument
	new_tail->next = nullptr; // set the next to null bc its last

	if(this->head == nullptr){ // if list is empty
		this->head = new_tail;
	}
	else{
		node* itr = this->head;
		while(itr->next != nullptr){ // traverse to last node
			itr = itr->next;
		}
		itr->next = new_tail; // set next node in last node to the new node
	}	
	
	this->length++;
}

void linked_list::insert(int value, int index) {
	if(index == this->length){ // if user wants to insert into last element
		push_back(value);
	}
	else if(index == 0){ // if user wants to insert into first element
		push_front(value);
	}
	else if(index >= 1 && index <= this->length - 1){ // any other element between
		node* new_itr = new node; // create new node and assign value from argument
		new_itr-> val = value;
		new_itr->next = nullptr;
		node* itr = this->head;
		for(int i = 0; i < index - 1; i++){ // traverse to desired node
			itr = itr->next;					
		}
		new_itr->next = itr->next; // assign new node's next to the one after the user wants to insert
		itr->next = new_itr;	
		this->length++;
	}	
}

void linked_list::pop_front() {
	if(this->head != nullptr){
		node* temp_head = this->head; // set head to a temp pointer
		this->head = this->head->next; // set the new head's next to the third node
        delete temp_head; // delete old head
		this->length--;
	}
}

void linked_list::pop_back() {
	if(this->head != nullptr){
		if(this->head->next == nullptr){ // one node in list
			delete this->head;
			this->head = nullptr;
		}

		else{
			node* itr = this->head; 
			while(itr->next->next != nullptr){ // traverse to last node
				itr = itr->next;				
			}
			delete itr->next; // delete
			itr->next = nullptr;
			
		}
		this->length--;
	}
}

void linked_list::remove(int index) {
	if(index == this->length){ // if user wants to delete last node
		pop_back();
	}
	else if(index == 0){ // if user wants to delete first node
		pop_front();
	}
	else if(index >= 1 && index <= this->length - 1){ // between
		node* itr = this->head;
		for(int i = 0; i < index - 1; i++){ // traverse to desired node
			itr = itr->next;					
		}
		node* deleted_itr = itr->next; // set the one to be deleted to a temp pointer
		itr->next = itr->next->next; // link the nodes between
		delete deleted_itr; // delete the selected node
		this->length--;

	}
}

node* linked_list::merge(node* left_head, node* right_head, bool ascending){
	if(left_head == nullptr){ // base cases
		return right_head;
	}
	if(right_head == nullptr){
		return left_head;
	}

	node* result = nullptr;

	if(ascending){ // if sort_ascending
		if(left_head->val <= right_head->val){ // assign smaller number to the left, call function again
		result = left_head;
		result->next = merge(left_head->next, right_head, ascending);
		}
		else{
			result = right_head;
			result->next = merge(left_head, right_head->next, ascending);
		}
	}
	else if(!ascending){ // if sort_descending
		if(left_head->val >= right_head->val){ // assign larger number to the left, call function again
		result = left_head;
		result->next = merge(left_head->next, right_head, ascending);
		}
		else{
			result = right_head;
			result->next = merge(left_head, right_head->next, ascending);
		}
	}

	return result;
}



void linked_list::split(node* head, node** left_head, node** right_head){
	if(head == nullptr || head->next == nullptr){ // if one node
		*left_head = head;
		*right_head = nullptr;
	}

	else{ // traverse until middle
		node* slow = head;
        node* fast = head->next;

        // move fast by 2 steps and slow by 1 step
        while (fast != nullptr) {
            fast = fast->next;
            if (fast != nullptr) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        // slow is now at the middle of the list
        *left_head = head;
        *right_head = slow->next;
        slow->next = nullptr;  // split the list
	}

}

node* linked_list::merge_sort(node* head, bool ascending){
	// base case
	if(head == nullptr || head->next == nullptr){
		return head;
	}
	
		node* left_head = nullptr; // the split list heads
		node* right_head = nullptr;

		split(head, &left_head, &right_head); // call split

		left_head = merge_sort(left_head, ascending); // call functions again but for both split sides
		right_head = merge_sort(right_head, ascending);

		return merge(left_head, right_head, ascending); // merge both sides
	
}


void linked_list::sort_ascending() {
	this->head = merge_sort(this->head, true); // split the list and merge sort
}

void linked_list::sort_descending() {
	this->head = merge_sort(this->head, false); // split the list and merge sort
}
