#include<iostream>


using namespace std;

template<class K,class V>
struct BSTreeNode
{
	K _key;
	V _value;
	BSTreeNode *_left;
	BSTreeNode *_right;
	BSTreeNode(K key,V value):_left(NULL),_right(NULL)
	{
		_key=key;
		_value=value;
	}
};

template<class K,class V>
class BSTree
{
	typedef BSTreeNode<K,V> Node;
public:
	BSTree():_root(NULL)
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
				{
					cur=cur->_left;
					if(cur==NULL)
					{
						parent->_left=new Node(key,value);
						return true;
					}
				}
				else if(cur->_key<key)
				{
					cur=cur->_right;
					if(cur==NULL)
					{
						parent->_right=new Node(key,value);
						return true;
					}
				}
				else
					return false;
			}
			return true;
		}
		
		
	}	
	bool RemoveR(K key)
	{
		return _RemoveR(_root,key);
	}
	Node* Find(K key)
	{
		Node *cur=_root;
		while(cur)
		{
			if(cur->_key<key)
				cur=cur->_right;
			else if(cur->_key>key)
				cur=cur->_left;
			else
				return cur;
		}
		return NULL;
	}
	void InOrder()
	{
		_InOrder(_root);
	}

	~BSTree()
	{}
protected:
	void _InOrder(Node *root)
	{
		if(root==NULL)
			return;
		_InOrder(root->_left);
			cout<<root->_key<<"->";
		_InOrder(root->_right);
	}
	//×××××××××××××××××××××××××××××××××××××××××
	bool _RemoveR(Node  *&root,K &key)
	{
		if(root==NULL)
			return false;
		if(root->_key>key)
			return _RemoveR(root->_left,key);
		else if(root->_key<key)
			return _RemoveR(root->_right,key);
		else
		{
			if(root->_left==NULL)
				root=root->_right;
			else if(root->_right==NULL)
				root=root->_left;
			else
			{
				Node *cur=root->_right;
				while(cur->_left)
					cur=cur->_left;
				root->_key=cur->_key;
				root->_value=cur->_value;
				//××××××××××××××××××××××××××××××××××××××××××××××
				_RemoveR(root->_right,root->_key);
			}
		}
		return true;
	}
protected:
	Node *_root;
};


void test()
{
	int a[]={5,1,3,2,7,8,9,6,4};
	BSTree<int,int> bs;
	for(int i=0;i<sizeof(a)/sizeof(a[0]);++i)
	{
		bs.Insert(a[i],i);
	}
	bs.InOrder();
	cout<<"NULL"<<endl;
	//bs.RemoveR(1);
	//bs.RemoveR(2);
	bs.RemoveR(3);
	bs.InOrder();
	cout<<"NULL"<<endl;
	bs.RemoveR(2);
	bs.InOrder();
	cout<<"NULL"<<endl;
	bs.RemoveR(1);
	bs.InOrder();
	cout<<"NULL"<<endl;	
	bs.RemoveR(4);
	bs.InOrder();
	cout<<"NULL"<<endl;
	bs.RemoveR(5);
	bs.InOrder();
	cout<<"NULL"<<endl;
}

