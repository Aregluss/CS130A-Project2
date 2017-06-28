#ifndef SNODE_H
#define SNODE_H

class SNode
{
	public:
		SNode* rightChild;
        SNode* leftChild;
        SNode* parent;
		int value;

		
		SNode(int val)
		{
			value = val;
			rightChild = NULL;
			leftChild = NULL;
            parent = NULL;

		}

        bool operator<(const SNode& other)
        {
           return (value < other.value);
        }

        bool operator>(const SNode& other)
        {
           return (value > other.value);
        }

        bool operator==(const SNode& other)
        {
            return (value == other.value);
        }

        bool operator!=(const SNode& other)
        {
            return (value != other.value);
        }

        bool operator=(const SNode& other)
        {
            value = other.value;
            rightChild = other.rightChild;
            leftChild = other.leftChild;
            parent = other.parent;
        }

};

#endif