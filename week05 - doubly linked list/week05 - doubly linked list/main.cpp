#include <iostream>

struct LinkedListNode {
	int data;
	LinkedListNode* next;
	LinkedListNode* random;
	LinkedListNode(int x = 0, LinkedListNode* next = nullptr) : data(x), next(next) {}
};
void printList(LinkedListNode* head) {
	LinkedListNode* iter = head;
	while (iter) {
		std::cout << iter->data << ' ';
		iter = iter->next;
	}
}


void ReverseSpecifiedPortionOfLinkedList(LinkedListNode* node, int start, int end) {
	LinkedListNode* next = nullptr, * prev = node, * fst = node, * last;
	for (size_t i = 0; i < start-1; i++)
	{
		if (!fst->next)
			return;
		fst = fst->next;
	}

	prev = fst;
	node = prev->next;
	last = prev->next;
	for (size_t i = 0; i <= end-start; i++)
	{
		if (!node) {
			return;
		}
		next = node->next;
		node->next = prev;		
		prev = node;
		node = next;
	}
	fst->next = prev;
	last->next = node;
}

int main() {
	LinkedListNode* head = new LinkedListNode(1);
	head->next = new LinkedListNode(2);
	head->next->next = new LinkedListNode(3);
	head->next->next->next = new LinkedListNode(4);
	head->next->next->next->next = new LinkedListNode(5);
	head->next->next->next->next->next = new LinkedListNode(6);
	head->next->next->next->next->next->next = new LinkedListNode(7);

	std::cout << "Original list: ";
	printList(head);

	// Reverse the portion of the list from position 1 to 4
	ReverseSpecifiedPortionOfLinkedList(head, 1, 4);

	std::cout << "Modified list: ";
	printList(head);

	// Clean up memory
	while (head) {
		LinkedListNode* temp = head;
		head = head->next;
		delete temp;
	}

}