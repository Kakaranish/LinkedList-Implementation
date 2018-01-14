#include <iostream>
#include <conio.h>
#include <stdio.h>


/*
INSERT(x, p, L) – wstaw x na pozycjê p na liœcie L
• LOCATE(x, L) zwraca pozycjê pierwszego wyst¹pienia //OK
elementu x w liœcie L.
• RETRIEVE(p, L) – zwraca element wystêpuj¹cy w L na pozycji p. //OK
• DELETE(p, L) – usuwa element na pozycji p z listy.
• NEXT(p, L) – zwraca pozycjê nastêpn¹ w stosunku do p w L. //OK
• PREVIOUS(p, L) - zwraca pozycjê nastêpn¹ w stosunku do p w L//OK
• MAKENULL(L).Czyni listê pust¹ i zwraca pozycjê END(L).
• FIRST(L) – zwraca pozycjê pierwszego elementu w L.  //OK
• PRINT_LIST(L) – wypisuje elementy w kolejnoœci wystêpowania
*/

struct Node {
public:
	int value;
	Node* nextNode = nullptr;

	Node() {}
	Node(int value) : value(value) {}
};

class List {
private:
	Node * head = nullptr;
	bool showMessages = true;
public:
	//Constructor
	List() {}

	//Methods
	bool isListEmpty() {
		if (head == nullptr)
			return true;
		else return false;
	}
	Node* getFirst() {
		return head;
	}
	Node* getLast() {
		if (isListEmpty()) {
			if(showMessages)
				std::cerr << "Lista jest pusta! Nie odnaleziono ostatniego elementu!" << std::endl;
			return nullptr;
		}

		Node* tmpNodePtr = head;
		while (true) {
			if (tmpNodePtr->nextNode == nullptr)
				return tmpNodePtr;
			else
				tmpNodePtr = tmpNodePtr->nextNode;
		}
	}
	Node* getNext(Node* position) {
		if (isListEmpty()) {
			if (showMessages)
				std::cerr << "Lista jest pusta! Nie odnaleziono nastepnego wezla!" << std::endl;
			return nullptr;
		}

		Node* tmpNodePtr = head;
		while (tmpNodePtr != nullptr) {
			if (tmpNodePtr == position)
				return tmpNodePtr->nextNode;
			else
				tmpNodePtr = tmpNodePtr->nextNode;
		}

		if (showMessages)
			std::cerr << "Nie odnaleziono kolejnego wezla dla danej pozycji!" << std::endl;
		return nullptr;
	}
	Node* getPrevious(Node* position) {
		if (isListEmpty()) {
			if (showMessages)
				std::cerr << "Lista jest pusta! Nie odnaleziono podanego wezla!" << std::endl;
			return nullptr;
		}
		else if (position == head) {
			if (showMessages)
				std::cerr << "Nie istnieje wezel poprzedzajacy glowe listy!" << std::endl;
			return nullptr;
		}

		Node* prevTmpNodePtr = nullptr, *tmpNodePtr = head;

		while (tmpNodePtr != nullptr) {
			if (tmpNodePtr == position) 
				return prevTmpNodePtr;
			else {
				prevTmpNodePtr = tmpNodePtr;
				tmpNodePtr = tmpNodePtr->nextNode;
			}
		}
	}
	Node* locate(int value) {
		if (isListEmpty()) {
			if (showMessages)
				std::cout << "Lista jest pusta! Nie odnaleziono podanego elementu!" << std::endl;
			return nullptr;
		}

		Node* tmpNodePtr = head;
		while (tmpNodePtr != nullptr) {
			if (tmpNodePtr->value == value) 
				return tmpNodePtr;
			tmpNodePtr = tmpNodePtr->nextNode;
		}
		return nullptr;
	}
	int retrieve(Node* node) {
		if (isListEmpty()) 
			throw std::exception("Node doesn't exist in list!");
		
		Node* tmpNodePtr = head;
		while (tmpNodePtr != nullptr) {
			if (tmpNodePtr == node)
				return tmpNodePtr->value;
			else
				tmpNodePtr = tmpNodePtr->nextNode;
		}

		throw std::exception("Node doesn't exist in list!");
	}
	void insert(Node* position, int value) {
		if (isListEmpty() && position!=nullptr) {
			if(showMessages)
				std::cerr << "Lista jest pusta! Nie odnaleziono podanego elementu!" << std::endl;
			return;
		}

		Node* tmpNodePtr;
		if (isListEmpty() && position == nullptr) {
			head = new Node(value);
			return;
		}

		//chcemy wstawiaæ w miejsce tego node'a
		Node* beforePosition = getPrevious(position);
		if (beforePosition == nullptr) {
			head = new Node(value);
			head->nextNode = position;
		}
		else {
			beforePosition->nextNode = new Node(value);
			beforePosition->nextNode->nextNode = position;
		}
	}
	void _delete(Node* position) {
		if (isListEmpty()) {
			std::cout << "Lista jest pusta! Nie ma nic do usuniecia!" << std::endl;
			return;
		}
		
		//TODO
		Node* beforePosition = getPrevious(position);
		Node* afterPosition = getNext(position);
		beforePosition->nextNode = afterPosition;
		delete position;		
	}
	void makeNull() {
		if (isListEmpty()) {
			if (showMessages)
				std::cerr << "Lista jest pusta! Nie ma czego usuwac" << std::endl;
			return;
		}
		Node* tmpPtr = head;
		Node* tmpPtrNext = tmpPtr->nextNode;
		while (tmpPtr != nullptr) {
			delete tmpPtr;
			tmpPtr = tmpPtrNext;
			if(tmpPtrNext != nullptr)
				tmpPtrNext = tmpPtrNext->nextNode;
		}
		head = nullptr;
	}


	void duplicateList() {
		if (isListEmpty()) {
			if (showMessages)
				std::cerr << "Lista jest pusta! Nie ma czego duplikowac!" << std::endl;
			return;
		}
		Node* lastNode = getLast(); //chcemy tylko raz wywolac ta funkcje
		Node* tmpPtr = head;
		
		while (tmpPtr != lastNode) {
			insert(getLast()->nextNode, tmpPtr->value);
			tmpPtr = tmpPtr->nextNode;
		}
		insert(getLast()->nextNode, tmpPtr->value);
		tmpPtr = tmpPtr->nextNode;

	}
	void deleteDuplicates() {
		if (isListEmpty()) {
			if (showMessages)
				std::cerr << "Lista jest pusta! Nie ma duplikatow do usuniecia" << std::endl;
			return;
		}

		Node* tmpPtr = head;	
		while (tmpPtr != nullptr) {
			Node* tmpTmpPtr = tmpPtr->nextNode;
			int valToRemove = tmpPtr->value;

			while (tmpTmpPtr != nullptr){
				if (tmpTmpPtr->value == valToRemove) {
					Node* tmpTmpTmpPtr = tmpTmpPtr->nextNode;
					_delete(tmpTmpPtr);
					tmpTmpPtr = tmpTmpTmpPtr;
				}
				else
					tmpTmpPtr = tmpTmpPtr->nextNode;
			}
			
			tmpPtr = tmpPtr->nextNode;
		}
	}



	void printList() {
		if (isListEmpty()) {
			std::cout << "Lista jest pusta!" << std::endl;
			return;
		}

		Node* tmpPtr = head;
		int counter = 1;
		while (tmpPtr != nullptr) {
			std::cout << counter++ << ") " << tmpPtr->value << std::endl;
			tmpPtr = tmpPtr->nextNode;
			
		}

	}

	void setShowMessages(bool value) {
		showMessages = value;
	}
};

//TODO
//Duplikowanie i usuwanie duplikaotw

int main(int argc, char* argv[]) {


	List list;
	list.setShowMessages(false);
	
	list.insert(list.getFirst(), 20);
	for (int i = 1; i <= 5; i++)
		list.insert(list.getLast()->nextNode, i);

	std::cout << "Lista przed duplikacji: " << std::endl;
	list.printList();

	
	list.duplicateList();
	std::cout << std::endl << "Lista po duplikacji: " << std::endl;
	list.printList();

	std::cout << std::endl << "Lista po drugiej duplikacji: " << std::endl;
	list.duplicateList();
	list.printList();


	std::cout << std::endl << "After removing duplicates: " << std::endl;
	list.deleteDuplicates();
	list.printList();



	_getch();
	return 0;
}

