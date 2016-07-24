//#pragma once
#include <stdio.h>
#include<stdlib.h>
#define __Trace(...)  printf("%s %d \n",__func__ ,__LINE__ );printf(__VA_ARGS__)
#include<iostream>
using namespace std;

//三叉链
template<class K,class V>
struct AVLTreeNode
{
	AVLTreeNode *_left;
	AVLTreeNode *_right;
	AVLTreeNode *_parent;

	K _key;
	V _value;
	int _bs;   //平衡因子

	AVLTreeNode(K key,V value):_key(key),_value(value)
				 ,_bs(0),_left(NULL)
			         ,_right(NULL),_parent(NULL)				 
	{}
};


template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K,V> Node;
public:
	AVLTree():_root(NULL)
	{}
	~AVLTree()
	{}
	bool Insert(K key,V value)
	{
		if(_root==NULL)
			_root=new Node(key,value);
		else
		{
			Node *cur=_root;
			Node *parent=NULL;
			while(cur)
			{
				parent=cur;
				if(cur->_key>key)
					cur=cur->_left;
				else if(cur->_key<key)
					cur=cur->_right;
				else
					return false;
			}

			Node *node=new Node(key,value);
			if(parent->_key>key)
			{
				parent->_left=node;
				node->_parent=parent;
			}
			else if(parent->_key<key)
			{
				parent->_right=node;
				node->_parent=parent;
			}
			cur=node;
			//////////////////////////////
			// InOrder();
			while(parent)
			{
				if(parent->_left==cur)
					--parent->_bs;
				if(parent->_right==cur)
					++parent->_bs;
				//调整到0的时候这个树就是个AVL树
				if(parent->_bs==0)
					break;
				if(parent->_bs==1||parent->_bs==-1)
				{
					if(parent->_parent==NULL)
						break;
					cur=parent;
					parent=parent->_parent;
				}
				if(parent->_bs==2)
				{
					if(cur->_bs==1)
						RotateL(parent);
					else
						RotateRL(parent);   //右左双旋
				}
				if(parent->_bs==-2)
				{
					if(cur->_bs==-1)
					{
						RotateR(parent);
					}
					else
					{
						RotateLR(parent);    //左右双旋
					}
				}
			}
		}
		return true;
	}
  //中序遍历
	void InOrder()
	{
		_InOrder(_root);
		cout << "NULL" <<endl;
	}
	//求树的高度
	int Heigh()
	{
		return _Heigh(_root);
	}
	//判断是不是平衡树
	//依据是从最左子树开始判断高度是不是大于2
	//没有判断平衡因子   ××××××××××××××××××
	bool IsBalance()
	{
		if(_root==NULL)
		{
			cout<<"1"<<endl;
			return true;
		}
		return _IsBalance(_root);
	}
protected:
	bool _IsBalance(Node *root)
	{
		if(root==NULL)
			return true;
		int heigh_l=_Heigh(root->_left);
		int heigh_r=_Heigh(root->_right);
		if(heigh_r-heigh_l!=root->_bs)
			return false;
		return abs(heigh_l-heigh_r)<2 && _IsBalance(root->_left) && _IsBalance(root->_right);
	}

	
	int _Heigh(Node *root)
	{
		if(root==NULL)
			return 0;
		int HeighL=_Heigh(root->_left);
		int HeighR=_Heigh(root->_right);
		return HeighL > HeighR ? HeighL+1 : HeighR+1;
	}
	void RotateL(Node *parent)
	{

		Node *subR=parent->_right;
		Node *subRL=subR->_left;
		Node *ppNode=parent->_parent;
		
		//parent 向下调整
		parent->_right=subRL;
		if(subRL!=NULL)
			subRL->_parent=parent;

		//subR向上调整
		subR->_left=parent;
		
		parent->_parent=subR;
		if(ppNode==NULL)
		{
			subR->_parent=NULL;
			_root=subR;
		}
		else
		{
			subR->_parent=ppNode;
			if(ppNode->_left==parent)
				ppNode->_left=subR;
			else
				ppNode->_right=subR;
		}
		
		parent->_bs=subR->_bs=0;
	}
	void RotateR(Node *&parent)
	{

		Node *subL=parent->_left;
		Node *subLR=subL->_right;
		Node *ppNode=parent->_parent;
		
		parent->_left=subLR;
		if(subLR!=NULL)
			subLR->_parent=parent;

		subL->_right=parent;
		parent->_parent=subL;
		if(ppNode==NULL)
		{
			subL->_parent=NULL;
			_root=subL;
		}
		else
		{
			subL->_parent=ppNode;
			if(ppNode->_left==parent)
				ppNode->_left=subL;
			else
				ppNode->_right=subL;
		}
		parent->_bs=subL->_bs=0;
	}
	void RotateLR(Node *parent)
	{

		Node *subL=parent->_left;
		Node *subLR=subL->_right;

		int bs=subLR->_bs;

		RotateL(parent->_left);
		RotateR(parent);

		if(bs==-1)
		{
			subL->_bs=0;
			parent->_bs=1;
		}
		else if(bs==1)
		{
			subL->_bs=-1;
			parent->_bs=0;
		}
		else
			subL->_bs=parent->_bs=0;
		subLR->_bs=0;
	}
	void RotateRL(Node *parent)
	{

		Node *subR=parent->_right;
		Node *subRL=subR->_left;
		int bs=subRL->_bs;

		RotateR(parent->_right);
		RotateL(parent);

		if(bs==1)
		{
			parent->_bs=-1;
			subR->_bs=0;
		}
		else if(bs==-1)
		{
			parent->_bs=0;
			subR->_bs=0;
		}
		else
			parent->_bs=subR->_bs=0;
		subRL->_bs=0;

	}
	//中序遍历

	void _InOrder(Node *root)
	{
		if(root==NULL)
			return;
		_InOrder(root->_left);
		cout<<root->_key<<"->";
		_InOrder(root->_right);
	}
private:
	Node *_root;
};



void test()
{
	int a[]={8,2,1,4,5,0,7,3,9,6};
	AVLTree<int,int> avl;
	int i=0;
	for(i=0;i<sizeof(a)/sizeof(a[0]);i++)
	{
		avl.Insert(a[i],i);
		avl.InOrder();
		cout<<"heigh is:"<<avl.Heigh()<<endl <<endl;
	}
	avl.IsBalance();
}
