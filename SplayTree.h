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
	
        SNode* accessVal(SNode*& rootnode, int a)
		{
            if (rootnode == NULL)
				return NULL; //EMPTY TREE

            if (rootnode->value == a)
			{
                return rootnode;
			}

            if (rootnode->leftChild == NULL && rootnode->rightChild == NULL)
			{
				return NULL;
			}


            SNode* current = rootnode;

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
			///HERE SHOULD BREAK AND CURRENT = EITHER NODE WITH VAL A OR A DIDNT EXIST SO ITS THE ONE BEFORE

			while(current->parent != NULL) ///DO THE UP MOVEMENT UNTILL WE HAVE NO PARENT (WE ARE ROOT!)
			{

                if (rootnode->rightChild && rootnode->rightChild->value == 500)
                    rootnode = rootnode;

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
                        if (current->rightChild)
                            current->rightChild->parent = parent;
                        if (current->leftChild)
						    current->leftChild->parent = grandParent;
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
                
			}

            rootnode = current;

            if (current->value == a) //current->value == a?
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
				
                split(root, a, t1, t2);

                if (t1 && t1->value == a)
                {
                    exist = true;

                    root = t1;
                    root->rightChild = t2;
                    if (t2)
                        t2->parent = root;
                }
                else 
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
			SNode* result = accessVal(root, a);

			if(result != NULL)
				cout << "item " << a << " found" << endl;
			else
				cout << "item " << a << " not found" << endl;
		}

		void deleteVal(int a)
		{
            
            bool isDeleted = false;
			SNode* exist = accessVal(root, a);

            if (exist && root->leftChild == NULL && root->rightChild == NULL)
			{
				delete root;
				root = NULL;
				isDeleted = true;
			}
			else if (exist)
			{
				SNode* left = root->leftChild;
				SNode* right = root->rightChild;

                delete root;
                root = NULL;
                isDeleted = true;

				if(left)
					left->parent = NULL;
				if(right)
					right->parent = NULL;

                if (right == NULL)
                    root = left;
                else
                    root = join(left, right);
                
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
            SNode* n;
            queue <SNode*> q1;
            queue <SNode*> q2;
            queue <SNode*> * p1 = &q1;
            queue <SNode*> * p2 = &q2;
            p1->push(root);
            
            while (!p1->empty() || !p2->empty())
            {
                int flag = false;
                while (!p1->empty())
                {
                    n = p1->front();
                    p1->pop();

                    if (flag)
                        cout << ", ";
                    cout << n->value;
                    flag = true;

                    if (n->leftChild)
                        p2->push(n->leftChild);
                    if (n->rightChild)
                        p2->push(n->rightChild);
                }
                cout << std::endl;

                queue <SNode*> * tmp = p2;
                p2 = p1;
                p1 = tmp;
            }
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

        void printRootandChildren(SNode* proot)
        {
            cout << "--------\n";
            if (!proot)
                return;

            SNode* n;
            queue <SNode*> q1;
            queue <SNode*> q2;
            queue <SNode*> * p1 = &q1;
            queue <SNode*> * p2 = &q2;
            p1->push(proot);

            while (!p1->empty() || !p2->empty())
            {
                int flag = false;
                while (!p1->empty())
                {
                    n = p1->front();
                    p1->pop();

                    if (flag)
                        cout << ", ";
                    
                    std::cout << ((n->leftChild) ? n->leftChild->value : 0) 
                        << "<" << n->value << ">" 
                        << ((n->rightChild) ? n->rightChild->value : 0);

                    flag = true;

                    if (n->leftChild)
                        p2->push(n->leftChild);
                    if (n->rightChild)
                        p2->push(n->rightChild);
                }
                cout << std::endl;

                queue <SNode*> * tmp = p2;
                p2 = p1;
                p1 = tmp;
            }
        }


		SNode* join(SNode* t1, SNode* t2) //lol dont think these go here
		{
			if(t1)
			{
				SNode* large = t1;
                
                while(large->rightChild != NULL)
				{
					large = large->rightChild;
				}
				accessVal(t1, large->value);

				t1->rightChild = t2;

				if(t2)
					t2->parent = t1;

                return t1;
			}
			else
			{
				t2->parent = NULL;
                return t2;
			}
		}


        void split(SNode *rootnode, int a, SNode *&pt1, SNode *&pt2)
		{
			 SNode* t1 = NULL;
			 SNode* t2 = NULL;
			 
             accessVal(rootnode, a);

             if (rootnode)
             {
                 if (rootnode->value > a)
                 {
                     t1 = rootnode->leftChild;
                     rootnode->leftChild = NULL;

                     if (t1)
                         t1->parent = NULL;

                     t2 = rootnode;
                 }
                 else
                 {
                     t2 = rootnode->rightChild;
                     rootnode->rightChild = NULL;

                     if (t2)
                         t2->parent = NULL;

                     t1 = rootnode;
                 }
             }
			pt1 = t1;
			pt2 = t2;			
		}
};



#endif