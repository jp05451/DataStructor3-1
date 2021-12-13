#include <iostream>

using namespace std;

//BSTree
template <typename T>
class treeNode
{
public:
    treeNode *parentNode = nullptr;
    T data;
    treeNode *nextNode[2] = {nullptr};

    treeNode(T inputData) { data = inputData; }
    treeNode(treeNode *parent, T input)
    {
        parentNode = parent;
        data = input;
    }

    void printNode()
    {
        printf("%d(", data);
        if (nextNode[0] != nullptr)
        {
            nextNode[0]->printNode();
        }
        printf(")(");
        if (nextNode[1] != nullptr)
        {
            nextNode[1]->printNode();
        }
        //cout << ")";
        printf(")");
    }

    void add(T inputData)
    {
        treeNode *preNode = this;
        treeNode *lastNode = this;

        //find the last node
        while (lastNode != nullptr)
        {
            if (inputData <= preNode->data)
            {
                lastNode = preNode->nextNode[0];
            }
            else
            {
                lastNode = preNode->nextNode[1];
            }
            if (lastNode == nullptr)
            {
                break;
            }
            else
            {
                preNode = lastNode;
            }
        }
        if (inputData <= preNode->data)
        {
            preNode->nextNode[0] = new treeNode(preNode, inputData);
        }
        else
        {
            preNode->nextNode[1] = new treeNode(preNode, inputData);
        }
    }

    void removeNode(T deleteData)
    {
        int remove;
        treeNode *deleteNode;

        //find the deleteNode
        if (deleteData <= data)
        {
            remove = 0;
            deleteNode = nextNode[0];
        }
        else
        {
            remove = 1;
            deleteNode = nextNode[1];
        }

        //delete Node
        if (deleteNode->nextNode[0] == nullptr && deleteNode->nextNode[1] == nullptr)
        //have no child node
        {
            delete deleteNode;
            nextNode[remove] = nullptr;
            return;
        }
        else if (deleteNode->nextNode[0] != nullptr && deleteNode->nextNode[1] != nullptr)
        //have two child node
        {
            if (deleteNode->nextNode[0]->nextNode[1] == nullptr)
            //don't have left child's right child
            {
                deleteNode->data = deleteNode->nextNode[0]->data;
                deleteNode->removeNode(deleteNode->data);
            }
            else
            //have left child's right child
            {
                treeNode *finalNode = deleteNode->nextNode[0]->findRightLeaf();
                deleteNode->data = finalNode->nextNode[1]->data;
                finalNode->removeNode(finalNode->nextNode[1]->data);
            }
            return;
        }
        else
        // only have one child
        {
            if (deleteNode->nextNode[0] != nullptr)
            //have left child
            {
                //deletNode->data = deletNode->nextNode[0]->data;
                nextNode[remove] = deleteNode->nextNode[0];
                // deleteNode->removeNode(deleteNode->nextNode[0]->data);
            }
            else
            //have right child
            {
                nextNode[remove] = deleteNode->nextNode[1];
            }
            delete deleteNode;
        }
    }

    treeNode *findParent(T searchData)
    {
        treeNode *tempNode = this;
        while (tempNode != nullptr)
        {
            if (searchData <= tempNode->data)
            {
                if (tempNode->nextNode[0] != nullptr)
                {
                    if (tempNode->nextNode[0]->data == searchData)
                    {
                        return tempNode;
                    }
                    else
                    {
                        tempNode = tempNode->nextNode[0];
                    }
                }
                else
                {
                    return nullptr;
                }
            }
            else
            {
                if (tempNode->nextNode[1] != nullptr)
                {
                    if (tempNode->nextNode[1]->data == searchData)
                    {
                        return tempNode;
                    }
                    else
                    {
                        tempNode = tempNode->nextNode[1];
                    }
                }
                else
                {
                    return nullptr;
                }
            }
        }
    }

    treeNode *findRightLeaf()
    {
        treeNode *tempNode = this;
        while (tempNode->nextNode[1]->nextNode[1] != nullptr)
        {
            tempNode = tempNode->nextNode[1];
        }
        return tempNode;
    }

    void destroyNode()
    {
        for (int i = 0; i < 2; i++)
        {
            if (nextNode[i] != nullptr)
            {
                if (nextNode[i]->nextNode[0] != nullptr || nextNode[i]->nextNode[1] != nullptr)
                {
                    nextNode[i]->destroyNode();
                }
                if (nextNode[i]->nextNode[0] == nullptr && nextNode[i]->nextNode[1] == nullptr)
                //last Node of the tree
                {
                    delete nextNode[i];
                    nextNode[i] = nullptr;
                }
            }
        }
    }

    void rightRotation()
    {
    }

    void leftRotation()
    {
    }
};

template <typename T>
class tree
{
    typedef treeNode<T> NODE;

public:
    void Insert(T inputData)
    {
        if (treeRoot == nullptr)
        {
            NODE *newNode = new NODE(treeRoot, inputData);
            treeRoot = newNode;
        }
        else
        {
            treeRoot->add(inputData);
        }
    }

    void Print()
    {
        if (treeRoot != nullptr)
        {
            treeRoot->printNode();
        }
        cout << endl;
    }

    void Remove(T deleteData)
    {
        if (treeRoot == nullptr)
            return;
        NODE *targetNode = treeRoot->findParent(deleteData);
        targetNode->removeNode(deleteData);
    }
    ~tree()
    {
        if (treeRoot == nullptr)
            return;

        treeRoot->destroyNode();
        delete treeRoot;
        treeRoot = nullptr;
    }

private:
    NODE *treeRoot = nullptr;
    T nodeList[MAX];
};