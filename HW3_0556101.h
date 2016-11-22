#pragma once
#ifndef HW3_0556101 
#define HW3_0556101 

#include<iostream>
#include<deque>
#include<string>
using namespace std;

//class tree node
class TreeNode {
	friend class GeneralTree;
private:
	string data;//node data
	TreeNode *child, *sibling;//child link and sibling link
							  //construct
	TreeNode(string data) {
		this->data = data;
		child = NULL;
		sibling = NULL;
	}
	//destruct
	~TreeNode()
	{
		delete(child);
		delete(sibling);
	}
};

//class general tree
class GeneralTree {
public:
	TreeNode *root; //root link
					//contruct
	GeneralTree(const std::string& str) {
		string temp = str;//temp of string str
		string dTemp = getNext(temp);//get the data of root
		root = new TreeNode(dTemp);//build the root

		deque<TreeNode*> parentStack;//stack for parent node
		TreeNode *nowNode = root;//pointer to the node now

								 //traverse the string temp to build the tree
		while (!temp.empty()) {
			dTemp = getNext(temp);//get the symbol or the data
								  //get symbol "(", then enter to the child node
			if (dTemp == "(") {
				parentStack.push_back(nowNode);
				dTemp = getNext(temp);
				TreeNode *childNode = new TreeNode(dTemp);
				nowNode->child = childNode;
				nowNode = childNode;
			}
			//get symbol ")", then back to the child node
			else if (dTemp == ")") {
				nowNode = parentStack.back();
				parentStack.pop_back();
			}
			//get data, then enter to the sibling node
			else {
				TreeNode *siblingNode = new TreeNode(dTemp);
				nowNode->sibling = siblingNode;
				nowNode = siblingNode;
			}
		}
		nowNode = NULL;
		delete(nowNode);
	}

	//destruct
	~GeneralTree() {
		delete_rec(root);
	}
	//destruct
	void delete_rec(TreeNode *nowNode) {
		if (nowNode == NULL)
			return;
		preorder_rec(nowNode->child);
		preorder_rec(nowNode->sibling);
		delete(nowNode);
	}

	//preorder using recursive
	void preorder_rec() {
		preorder_rec(root);
	}
	//preorder using recursive
	void preorder_rec(TreeNode *nowNode) {
		if (nowNode == NULL)
			return;

		cout << nowNode->data << " ";
		preorder_rec(nowNode->child);
		preorder_rec(nowNode->sibling);
		if (nowNode == root) {
			cout << endl;
		}

	}
	//preorder using nowrecursive
	void preorder_nonrec() {
		if (root == NULL) {
			return;
		}
		deque<TreeNode*> parentStack;//stack for parent node
		TreeNode *nowNode = root;//pointer to the node now

								 //traverse the tree
		do
		{
			cout << nowNode->data << " ";//print the data
										 //enter to the child
			if (nowNode->child != NULL) {
				parentStack.push_back(nowNode);
				nowNode = nowNode->child;
				continue;
			}

			//enter to the sibling
			if (nowNode->sibling != NULL) {
				nowNode = nowNode->sibling;
				continue;
			}

			//back to the parent which has sibling untraversed
			while (!parentStack.empty() && nowNode->sibling == NULL) {
				nowNode = parentStack.back();
				parentStack.pop_back();
			}
			//enter to the sibling or end of traversal
			if (!parentStack.empty())nowNode = nowNode->sibling;

		} while (!parentStack.empty());

		cout << endl;
	}

	//postorder using recursive
	void postorder_rec() {
		if (root == NULL) {
			return;
		}
		postorder_rec(root);
	}
	//postorder using recursive
	void postorder_rec(TreeNode *nowNode) {
		if (nowNode == NULL)
			return;
		postorder_rec(nowNode->child);
		cout << nowNode->data << " ";
		postorder_rec(nowNode->sibling);
		if (nowNode == root) {
			cout << endl;
		}
	}

	//postorder using nowrecursive
	void postorder_nonrec() {
		if (root == NULL) {
			return;
		}
		deque<TreeNode*> parentStack;//stack for parent node
		TreeNode *nowNode = root;//pointer to the node now

								 //traverse the tree
		do
		{

			//enter to the child
			if (nowNode->child != NULL) {
				parentStack.push_back(nowNode);
				nowNode = nowNode->child;
				continue;
			}
			cout << nowNode->data << " ";//print the data

										 //enter to the sibling
			if (nowNode->sibling != NULL) {
				nowNode = nowNode->sibling;
				continue;
			}

			//back to the parent which has sibling untraversed
			while (!parentStack.empty() && nowNode->sibling == NULL) {
				nowNode = parentStack.back();
				cout << nowNode->data << " ";//print the data

				parentStack.pop_back();
			}
			//enter to the sibling or end of traversal
			if (!parentStack.empty()) {
				nowNode = nowNode->sibling;
			}

		} while (!parentStack.empty());

		cout << endl;
	}

	//levelorder using queue without recursive
	void levelorder() {
		if (root == NULL) {
			return;
		}
		deque<TreeNode*> parentStack;//stack for parent node
		TreeNode *nowNode = root;//pointer to the node now

		parentStack.push_back(nowNode);//push root to stack
		cout << nowNode->data << " ";//then print it

									 //traverse the tree
		while (!parentStack.empty()) {
			nowNode = parentStack.front();//first in first out order
			parentStack.pop_front();
			//enter to next level
			if (nowNode->child) {
				nowNode = nowNode->child;
				parentStack.push_back(nowNode);
				cout << nowNode->data << " ";
				//print the data of that level
				while (nowNode->sibling != NULL)
				{
					nowNode = nowNode->sibling;
					parentStack.push_back(nowNode);
					cout << nowNode->data << " ";
				}
			}

		}
		cout << endl;

	}

	//get the symbol or the data
	string getNext(string& str) {
		string temp;
		bool s = false;
		int startIndex = 0;
		int endLength = 0;
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == ' ') {
				if (s) {
					temp.assign(str, startIndex, endLength);
					str.erase(0, i + 1);
					return temp;
				}
				else {
					continue;
				}
			}
			else if (str[i] == '(') {
				str.erase(0, i + 1);
				return "(";
			}
			else if (str[i] == ')') {
				str.erase(0, i + 1);
				return ")";
			}
			else {
				if (!s) {
					s = true;
					startIndex = i;
					endLength++;
				}
				else {
					endLength++;
				}

			}


		}


		temp.assign(str, startIndex, endLength);
		str = "";
		return temp;
	}


};


#endif