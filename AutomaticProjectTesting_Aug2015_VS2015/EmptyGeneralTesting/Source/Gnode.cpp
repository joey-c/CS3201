#include "Gnode.h"

Gnode::Gnode() {
	value = -1;
	left = NULL;
	right = NULL;
	prev = NULL;
	otherPrev = NULL;
	type = NOTYPE;
}

Gnode::~Gnode() {}

Gnode *Gnode::createGnode(int num) {
	Gnode *node = new Gnode;
	node->value = num;
	return node;
}

Gnode *Gnode::createGnode(Type t, int num) {
	Gnode *node = new Gnode;
	node->value = num;
	node->type = t;
	return node;
}

void Gnode::setNext(Gnode *curr, Gnode *next) {
        curr->right = next;
        next->prev = curr;
}

void Gnode::setNextIf(Gnode *curr, Gnode *ifNode, Gnode *elseNode) {
	curr->left = ifNode;
	curr->right = elseNode;
	ifNode->prev = curr;
	elseNode->prev = curr;
}

void Gnode::setNextEndIf(Gnode *lastChildThen, Gnode *lastChildElse, Gnode *other) {
	lastChildThen->right = other;
	lastChildElse->right = other;
	other->prev = lastChildElse;
	other->otherPrev = lastChildThen;
}

void Gnode::setNextWhile(Gnode* parent, Gnode* lastchild, Gnode* other){
	parent->left = other;
	lastchild->right = parent;
	other->prev = parent;
}

vector <Gnode *> Gnode::getNext() {
	vector<Gnode*> gnodes;

	if (right != NULL) {
		gnodes.push_back(right);
	}
	if (left != NULL) {
		gnodes.push_back(left);
	}

	return gnodes;
}

vector <Gnode *> Gnode::getPrev() {
	vector<Gnode*> prevGnodes;

	if (prev != NULL) {
		prevGnodes.push_back(prev);
	}
	if (otherPrev != NULL) {
		prevGnodes.push_back(otherPrev);
	}

	return prevGnodes;
}

int Gnode::getValue() {
	return value;
}

Gnode *Gnode::getRight() {
	return right;
}

Gnode *Gnode::getLeft() {
	return left;
}

Gnode::Type Gnode::getType() {
	return type;
}

void printVector(vector<Gnode *> nodeVector) {

	cout << "vec size: " << nodeVector.size() << "\n";

	for (vector<Gnode *>::iterator node = nodeVector.begin(); node != nodeVector.end(); ++node) {
		cout << (**node).getValue() << endl;
	}
}

int main() {
	
}