#ifndef SPLAYTREE_H
#define SPLAYTREE_H


#include "SNode.h"
#include <stdlib.h>
#include <queue>
#include <math.h>

using namespace std;

class SplayTree
{
	public:
		SNode* root;


		SplayTree()
		{
			root = NULL;
		}

		SplayTree(int a) //not needed
		{
			root = new SNode(a);
		}
	
		SNode* accessVal(int a)
		{
			if(root == NULL)
				return NULL; //EMPTY TREE

			if(root->value == a)
			{
				return root;
			}

			if(root->leftChild == NULL && root->rightChild == NULL)
			{
				return NULL;
			}


			SNode* current = root;

			while(current->value != a)
			{
				if(a > current->value)
				{
					if(current->rightChild != NULL)
						current = current->rightChild;
					else
						break;
				}
				else
				{
					if(current->leftChild != NULL)
						current = current->leftChild;
					else
						break;
				}
			}
			///HERE SHOULD BERAK AND CURRENT = EITHER NODE WITH VAL A OR A DIDNT EXIST SO ITS THE ONE BEFORE


			while(current->parent != NULL) ///DO THE UP MOVEMENT UNTILL WE HAVE NO PARENT (WE ARE ROOT!)
			{

				bool meOnLeft = (current == current->parent->leftChild);

				if(current->parent->parent == NULL) //CHILD OF ROOT
				{

					SNode* parent = current->parent;

					if(meOnLeft) //LEFT CHILD = ROTATE RIGHT
					{

					    parent->leftChild = current->rightChild;
					    if (current->rightChild)
					        current->rightChild->parent = parent;
					    parent->parent = current;
					    current->rightChild = parent;
					} 
					else 
					{
					    parent->rightChild = current->leftChild;
					    if (current->leftChild)
					        current->leftChild->parent = parent;
					    parent->parent = current;
					    current->leftChild = parent;

					}
					current->parent = NULL;

				}
				else	// ZIG ZIG OR ZIG ZAG
				{
					bool parentOnLeft = (current->parent == current->parent->parent->leftChild);

                    SNode* grandParent = current->parent->parent;
                    SNode* parent = current->parent;

                    SNode* grandParentParent = grandParent->parent;

                    if(meOnLeft && parentOnLeft) //NODES LEFT LEFT : RIGHT RIGHT rotation
					{
						if (current->rightChild)
						    current->rightChild->parent = parent;
						if (parent->rightChild)
						    parent->rightChild->parent = grandParent;

						current->parent = grandParent->parent;
						grandParent->parent = parent;
						parent->parent = current;
						grandParent->leftChild = parent->rightChild;
						parent->rightChild = grandParent;
						parent->leftChild = current->rightChild;
						current->rightChild = parent;

					}
					else if(!meOnLeft && !parentOnLeft) //NODES RIGHT RIGHT : LEFT LEFT rotation
					{
						if (current->leftChild)
						    current->leftChild->parent = parent;
						if (parent->leftChild)
						    parent->leftChild->parent = grandParent;
						current->parent = grandParent->parent;
						grandParent->parent = parent;
						parent->parent = current;
						grandParent->rightChild = parent->leftChild;
						parent->leftChild = grandParent;
						parent->rightChild = current->leftChild;
						current->leftChild = parent;

					}
					else if(!meOnLeft && parentOnLeft) //Nodes meR pL : LEFT RIGHT						
					{
						if (current->leftChild)
						    current->leftChild->parent = parent;
						if (current->rightChild)
						    current->rightChild->parent = grandParent;
						current->parent = grandParent->parent;
						grandParent->parent = current;
						parent->parent = current;
						grandParent->leftChild = current->rightChild;
						parent->rightChild = current->leftChild;
						current->leftChild = parent;
						current->rightChild = grandParent;

					}
					else if(meOnLeft && !parentOnLeft) //Nodes meL pR : RIGHT LEFT
					{
						if (current->leftChild)
						    current->leftChild->parent = grandParent;
						if (current->rightChild)
						    current->rightChild->parent = parent;
						current->parent = grandParent->parent;
						grandParent->parent = current;
						parent->parent = current;
						grandParent->rightChild = current->leftChild;
						parent->leftChild = current->rightChild;
						current->rightChild = parent;
						current->leftChild = grandParent;

					}
                    if (grandParentParent) {
                        if (grandParentParent->leftChild == grandParent)
                        {
                            grandParentParent->leftChild = current;
                        }
                        else {
                            grandParentParent->rightChild = current;
                        }
                    }
				}
//                print();
			}

			root = current;

			if(root->value == a) //current->value == a?
				return current;  //root?
			else
				return NULL;

		}


		void insertVal(int a)
		{
//            cout << "inserting " << a << endl;
            bool exist = false;
			if(root == NULL)
			{
				root = new SNode(a);
			}
			else
			{
				SNode* t1 = NULL;
				SNode* t2 = NULL;
				exist = split(a, &t1, &t2);

				if(exist == false)
				{
					root = new SNode(a);

					root->rightChild = t2;
					if(t2)
						t2->parent = root;

					root->leftChild = t1;
					if(t1)
						t1->parent = root;
				}

			}

			if(exist)
			{
				cout << "item " << a << " not inserted; already present" << endl;
			}
			else
			{
				cout << "item " << a << " inserted" << endl;
			}


		}

		void findVal(int a)
		{
			SNode* result = accessVal(a);

			if(result != NULL)
				cout << "item " << a << " found" << endl;
			else
				cout << "item " << a << " not found" << endl;
		}

		void deleteVal(int a)
		{
			bool isDeleted = false;
			SNode* exist = accessVal(a);

			if(root != NULL && root->leftChild == NULL && 
				root->rightChild == NULL && root->value == a)
			{
				delete root;
				root = NULL;
				isDeleted = true;
			}
			else if(exist != NULL)
			{
				SNode* left = exist->leftChild;
				SNode* right = exist->rightChild;

				if(left)
					left->parent = NULL;
				if(right)
					right->parent = NULL;

				root = join(left, right);
				isDeleted = true;
			}


			if(isDeleted)
			{
				cout << "item " << a << " deleted" << endl;
			}
			else
			{
				cout << "item " << a << " not deleted; not present" << endl;
			}

		}

		void print()
		{
/*			queue <SNode*> printlist;
			SNode* current = root;
			printlist.push(current);
			int p = 1;
			int count = 1;

			while(printlist.empty() == false)
			{
				current = printlist.front();
				printlist.pop();

				if(current)
					cout << current->value;

				if(count % p == 0)
					cout << endl;
				else if(cout % p != 0 && current)
					cout << ", ";

				if(current)
					printlist.push(current->leftChild);
				if(current)
					printlist.push(current->rightChild);

				count++;
				p*=2;
			}

*/


			printHelper(root);
			cout << endl;
		}



		protected:


		void printHelper(SNode* me)
		{
			if(me != NULL)
			{	
				printHelper(me->leftChild);
				cout << me->value << " ";
				printHelper(me->rightChild);
			}
		}


		SNode* join(SNode* t1, SNode* t2) //lol dont think these go here
		{
			if(t1)
			{
				root = t1;
				SNode* large = t1;

				while(large->rightChild != NULL)
				{
					large = large->rightChild;
				}

				accessVal(large->value);

				root->rightChild = t2;

				if(t2)
					t2->parent = root;
			}
			else
			{
				root = t2;
				t2->parent = NULL;
			}

			return root;
		}


		bool split(int a, SNode **pt1, SNode **pt2)
		{
			 SNode* t1 = NULL;
			 SNode* t2 = NULL;
			 SNode* aNode = accessVal(a);
			 if(aNode != NULL)
			 {
			 	return true;
			 }
			 else
			 {
			 	if(root->value > a)
			 	{
			 		t1 = root->leftChild;
			 		root->leftChild = NULL;

			 		if(t1)
			 			t1->parent = NULL;

			 		t2 = root;

			 	}
			 	else
			 	{
			 		t2 = root->rightChild;
			 		root->rightChild = NULL;

			 		if(t2)
			 			t2->parent = NULL;

			 		t1 = root;
			 	}

			 	*pt1 = t1;
			 	*pt2 = t2;

			 	return false;
			 }
		}
};



#endif