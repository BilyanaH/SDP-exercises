#include <list>
#include <iostream>
#include <cassert>
using namespace std;

struct LinkedListNode {
	int data;
	LinkedListNode* next;
	LinkedListNode(int x = 0, LinkedListNode* next = nullptr) : data(x), next(next) {}
};
struct MultilevelDoublyLinkedListNode {
	int data;
	MultilevelDoublyLinkedListNode* next;
	MultilevelDoublyLinkedListNode* prev;
	MultilevelDoublyLinkedListNode* child;
};
LinkedListNode* reverse(LinkedListNode* head) {
	LinkedListNode* prev = nullptr;
	LinkedListNode* curr = head;
	LinkedListNode* next = head->next;

	while (curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;

	}
	return prev;
}

bool loop(LinkedListNode* head) {
	LinkedListNode* first = head;
	LinkedListNode* second = head->next;
	while (second) {
		if (first == second) {
			return true;
		}
		first = first->next;
		second = second->next->next;

	}
	return false;

}
LinkedListNode* merge(LinkedListNode* a, LinkedListNode* b) {
	LinkedListNode dummy{ 0, nullptr };
	LinkedListNode* now = &dummy;


	while (a && b) {
		if (a->data <= b->data) {
			now->next = a;
			a = a->next;
		}
		else {
			now->next = b;
			b = b->next;
		}
		now = now->next;
	}
	if (a)
	{
		while (a) {
			now->next = a;
			a = a->next;
			now = now->next;
		}
	}
	else if (b)
	{
		while (b) {
			now->next = b;
			b = b->next;
			now = now->next;

		}
	}
	return dummy.next;

}

LinkedListNode* mergeSort(LinkedListNode* head) {
	if (!head || !head->next)
	{
		return head;
	}
	LinkedListNode* slow = head, * fast = head, * temp = head;

	while (fast && fast->next) {
		fast = fast->next->next;
		temp = slow;
		slow = slow->next;
	}
	temp->next = nullptr;
	LinkedListNode* l1 = mergeSort(head), * l2 = mergeSort(slow);
	return merge(l1, l2);
}


LinkedListNode* sumNumbers(LinkedListNode* l1, LinkedListNode* l2) {
	LinkedListNode* dummyHead = new LinkedListNode(), * curr = dummyHead;
	bool carry = false;
	while (l1 || l2) {
		curr->next = new LinkedListNode();
		curr = curr->next;
		int x = l1 ? l1->data : 0;
		int y = l2 ? l2->data : 0;
		curr->data = (x + y + carry) % 10;
		carry = (x + y + carry) / 10;
		l1 = l1 ? l1->next : 0;
		l2 = l2 ? l2->next : 0;
	}
	if (carry) {
		curr->next = new LinkedListNode(1);
	}
	return dummyHead->next;
}
LinkedListNode* deleteNode(LinkedListNode* node) {
	
	node->data  = node->next->data;
	LinkedListNode* tmp = node->next;
	node->next = node->next->next;
	return tmp;
}
LinkedListNode* removeNthFromEnd(LinkedListNode* head, int n) {
	LinkedListNode* dummyHead = new LinkedListNode(),
		* slow = dummyHead, * fast = dummyHead;
	dummyHead->next = head;
	for (size_t i = 0; i <= n; i++)
	{
		fast = fast->next;
	}
	while (fast) {
		slow = slow->next;
		fast = fast->next;
	}
	slow->next = slow->next->next;
	return dummyHead->next;
}

MultilevelDoublyLinkedListNode* FlattenMultilevelDoublyLinkedList(MultilevelDoublyLinkedListNode* head) {
	if (!head)
	{
		return nullptr;
	}
	MultilevelDoublyLinkedListNode* iter = head, * next = head->next;
	if (head->child)
	{
		head->next = FlattenMultilevelDoublyLinkedList(head->child);
		head->next->prev = head;
		while (iter->next)
		{
			iter = iter->next;
		}

		if (next)
		{
			next->prev = iter;
		}

		head->child = nullptr;
	}
	iter->next = FlattenMultilevelDoublyLinkedList(next);
	return head;
}
void printDoublyLinkedList(MultilevelDoublyLinkedListNode* head) {
	while (head->next) {
		cout << head->data << ' ';
		head = head->next;
		assert(!head->child);
	}
	cout << head->data<<endl;
	while (head->prev)
	{
		cout << head->data << ' ';
		head = head->prev;
	}	
	cout << head->data << endl;

}
void printList(LinkedListNode* head) {
	LinkedListNode* iter = head;
	while (iter) {
		std::cout << iter->data << ' ';
		iter = iter->next;
	}
}
int main() {
	LinkedListNode* head = new LinkedListNode{ 1,
		new LinkedListNode {2,
		new LinkedListNode {3, nullptr} } };
	LinkedListNode* head2 = new LinkedListNode{ 1, nullptr };
	head2->next = new LinkedListNode{ 2, nullptr };
	head2->next->next = new LinkedListNode{ 3, nullptr };
	head2->next->next->next = new LinkedListNode{ 4, nullptr };
	head2->next->next->next->next = new LinkedListNode{ 5, nullptr };
	head2->next->next->next->next->next = head2->next;

	//printList(head);
	printList(reverse(head));
	assert(loop(head) == false);
	assert(loop(head2) == true);


	LinkedListNode* list1 = new LinkedListNode{ 4, new LinkedListNode{5, new LinkedListNode{6, nullptr}} };
	LinkedListNode* list2 = new LinkedListNode{ 1, new LinkedListNode{2, new LinkedListNode{3, nullptr}} };

	// Merge two sorted lists
	LinkedListNode* merged = merge(list1, list2);

	// Print merged sorted list
	std::cout << "Merged sorted list: ";
	printList(merged);

	head = new LinkedListNode{ 1,
		new LinkedListNode {5,
		new LinkedListNode {3,
		new LinkedListNode {-5,
		new LinkedListNode {9,
		new LinkedListNode {2, nullptr}}}}}};
	std::cout << "Sort list: ";
	printList(head);
	std::cout << endl;
	printList(mergeSort(head));

	std::cout << endl;
	list1 = new LinkedListNode{ 2,
	   new LinkedListNode{4,
	   new LinkedListNode{3, nullptr}}};
	list2 = new LinkedListNode{ 5,
	   new LinkedListNode{6,
	   new LinkedListNode{4, nullptr}}};
	printList(sumNumbers(list1, list2));

	std::cout << endl;
	list1 = new LinkedListNode{ 0, nullptr};
	list2 = new LinkedListNode{ 0, nullptr };
	printList(sumNumbers(list1, list2));

	std::cout << endl;
	list1 = new LinkedListNode{ 9,
	    new LinkedListNode{9,
	    new LinkedListNode{9, 
		new LinkedListNode{9, nullptr}}}};
	list2 = new LinkedListNode{ 9,
	    new LinkedListNode{9,
	    new LinkedListNode{9, 
		new LinkedListNode{9, 
		new LinkedListNode{9, 
		new LinkedListNode{9, 
		new LinkedListNode{9, nullptr}}}}}}};
	printList(sumNumbers(list1, list2));

	std::cout << endl;
	LinkedListNode* head3 = new LinkedListNode(1);
	head3->next = new LinkedListNode(2);
	head3->next->next = new LinkedListNode(3);
	head3->next->next->next = new LinkedListNode(4);
	deleteNode(head3->next);
	printList(head3);

	removeNthFromEnd(head3, 2);
	printList(head3);

	delete head3->next->next; // delete node with value 4
	delete head3->next;        // delete node with value 3
	delete head3;

	//8
	MultilevelDoublyLinkedListNode* head8 = new MultilevelDoublyLinkedListNode{ 1 };
	MultilevelDoublyLinkedListNode* n2 = new MultilevelDoublyLinkedListNode{ 2 };
	MultilevelDoublyLinkedListNode* n3 = new MultilevelDoublyLinkedListNode{ 3 };
	MultilevelDoublyLinkedListNode* n4 = new MultilevelDoublyLinkedListNode{ 4 };
	MultilevelDoublyLinkedListNode* n5 = new MultilevelDoublyLinkedListNode{ 5 };
	MultilevelDoublyLinkedListNode* n6 = new MultilevelDoublyLinkedListNode{ 6 };
	MultilevelDoublyLinkedListNode* n7 = new MultilevelDoublyLinkedListNode{ 7 };
	MultilevelDoublyLinkedListNode* n8 = new MultilevelDoublyLinkedListNode{ 8 };
	MultilevelDoublyLinkedListNode* n9 = new MultilevelDoublyLinkedListNode{ 9 };
	MultilevelDoublyLinkedListNode* n10 = new MultilevelDoublyLinkedListNode{ 10 };
	MultilevelDoublyLinkedListNode* n11 = new MultilevelDoublyLinkedListNode{ 11 };
	MultilevelDoublyLinkedListNode* n12 = new MultilevelDoublyLinkedListNode{ 12 };

	head8->next = n2;

	n2->next = n3;
	n2->prev = head8;

	n3->next = n4;
	n3->prev = n2;
	n3->child = n7;

	n4->next = n5;
	n4->prev = n3;

	n5->next = n6;
	n5->prev = n4;

	n6->prev = n5;

	n7->next = n8;

	n8->next = n9;
	n8->prev = n7;
	n8->child = n11;

	n9->next = n10;
	n9->prev = n8;

	n10->prev = n9;

	n11->next = n12;

	n12->prev = n11;

	head8 = FlattenMultilevelDoublyLinkedList(head8);
	std::cout << endl;
	printDoublyLinkedList(head8);
}