#include<iostream>
#include<stdio.h>
using namespace std;

#define TT printf("%s,%d\n",__func__,__LINE__)
//红黑树

//每个节点,不是红色就是黑色的
//根节点是黑色的
//如果一个节点是红色的,则它的两个子节点是黑色的
//对每个节点,从该节点到其所有后代叶节点的简单路径上,均包含相同数目的黑色节点。

enum col
{
	RED,
	BLACK
};

template<class K ,class V>
struct RBTreeNode
{
	K _key;
	V _value;
	RBTreeNode<K,V> *_left;
	RBTreeNode<K,V> *_right;
	RBTreeNode<K,V> *_parent;
	col _col;
	RBTreeNode(K key,V value):_key(key),_value(value)
							  ,_left(NULL),_right(NULL)
							  ,_parent(NULL),_col(RED)
	{}
};


template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K,V> Node;
public:
	RBTree():_root(NULL)
	{}
	bool Insert(K key,V value)
	{
		if(_root==NULL)
		{
			_root=new Node(key,value);
			_root->_col=BLACK;
			return true;
		}
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

		///////

		cur=new Node(key,value);
		//通过key值来判断插入到左还是右
		Node *uncle=NULL;
		if(parent->_key<key)
		{
			parent->_right=cur;
			cur->_parent=parent;
		}
		else
		{
			parent->_left=cur;
			cur->_parent=parent;
		}
		///////////////////////////


		Node *grandfather=NULL;
		while(cur)
		{
			///////////////

////////////////////////////

			parent=cur->_parent;
			if(parent==NULL)
				break;
			grandfather=parent->_parent;
			if(grandfather==NULL)
				break;
			else
			{
				Node *uncle=NULL;
				if(parent==grandfather->_left)
					uncle=grandfather->_right;
				else
					uncle=grandfather->_left;
				if(parent->_col==RED&&uncle!=NULL&&uncle->_col==RED&&grandfather->_col==BLACK)
				{
					if(parent==grandfather->_left&&cur==parent->_right)
					{
						RotateL(parent);

						////////

						swap(cur,parent);
					//	cout<<cur->_key<<":"<<parent->_key<<endl;
					}
					else if(parent==grandfather->_right&&cur==parent->_left)
					{
						RotateR(parent);
						swap(cur,parent);
					}
					parent->_col=BLACK;
					uncle->_col=BLACK;
					grandfather->_col=RED;
					cur=grandfather;
				}
				else if(parent->_col==RED&&grandfather->_col==BLACK&&(uncle==NULL||uncle->_col==BLACK))
				{
					if(parent==grandfather->_left&&cur==parent->_left)
						RotateR(grandfather);
					else if(parent==grandfather->_right&&cur==parent->_right)
						RotateL(grandfather);
					else if(parent==grandfather->_left&&cur==parent->_right)
					{
						RotateL(parent);
						RotateR(grandfather);
						swap(cur,parent);
					}
					else if(parent==grandfather->_right&&cur==parent->_left)
					{
						RotateR(parent);
						RotateL(grandfather);
						swap(parent,cur);
					}
					parent->_col=BLACK;
					grandfather->_col=RED;
				}
			}
			break;
		}
		_root->_col=BLACK;
	}
	
	void InOrder()
	{
		_InOrder(_root);
		cout<<"NULL"<<endl;
	}
	bool IsBalance()
	{
		if(_root==NULL)
			return true;
		if(_root->_col!=BLACK)
		{
			cout<<"根节点不是黑色"<<endl;
			return false;
		}
		Node *cur=_root;
		int B_num=0;
		//统计一条路径上的黑色节点个数
		while(cur)
		{
			if(cur->_col==BLACK)
				B_num++;
			cur=cur->_left;
		}
		//cout<<B_num<<endl;
		int count=0;
		//return _IsBalance(_root,B_num,count);
		if(_IsBalance(_root,B_num,count))
		{
			cout<<"is a RBTree!!"<<endl;
			return true;
		}
		return false;
	}
	~RBTree()
	{}
protected:
	bool _IsBalance(Node *root,int &count_B,int count)
	{
		if(root==NULL)
			return true;
		if(root->_col==BLACK)
			count++;
		if(root->_col==RED&&((root->_left!=NULL&&root->_left->_col==RED)||(root->_right!=NULL&&root->_right->_col==RED)))
		{
			cout<<"连续的红节点"<<endl;
			return false;
		}
		if(root->_left==NULL&&root->_right==NULL)
		{
			if(count!=count_B)
			{
				cout<<"路径上黑色节点数不一样"<<endl;
				return false;
			}
		}
		_IsBalance(root->_left,count_B,count);
		_IsBalance(root->_right,count_B,count);


		return true;
	}
	void RotateR(Node *parent)
	{
		Node *ppNode=parent->_parent;
		Node *subL=parent->_left;
		Node *subLR=subL->_right;

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
	}
	void RotateL(Node *parent)
	{
		Node *ppNode=parent->_parent;
		Node *subR=parent->_right;
		Node *subRL=subR->_left;

		parent->_right=subRL;
		if(subRL!=NULL)
			subRL->_parent=parent;

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
	}
	void _InOrder(Node *root)
	{
		if(root==NULL)
			return;
		_InOrder(root->_left);
		cout<<root->_key<<"->"<<root->_col<<":";
		_InOrder(root->_right);
	}
private:
	Node *_root;
};


void test()
{
	RBTree<int,int> rb;
	int a[]={1,3,7,2,4,8,9,5,6,0};
	for(int i=0;i<sizeof(a)/sizeof(a[0]);++i)
	{
		rb.Insert(a[i],i);
		rb.InOrder();
	}
	rb.IsBalance();
}

