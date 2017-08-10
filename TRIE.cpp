#include<iostream>
#include<cstdlib>
#include<vector>
#include<stack>

using namespace std;

struct Node
{
	Node* parent=NULL;
	Node* children[26];
	int occurances=0;	
};

void Insert(Node* TrieRoot,string word)
{
	Node* root=TrieRoot;
	for(int i=0;i<word.length();++i)
	{
		if(root->children[word[i]-'a']!=NULL)
		{
			root=root->children[word[i]-'a'];
			continue;
		}
		Node* temp=new Node();
		temp->parent=root;
		root->children[word[i]-'a'] = temp;
		root=temp;
	}
	root->occurances += 1;
}

int Search(Node* TrieRoot,string word)
{
	for(int i=0;i<word.length();++i)
	{
		if(TrieRoot->children[word[i]-'a']==NULL)
		return 0;
		
		TrieRoot=TrieRoot->children[word[i]-'a'];
	}
	if(TrieRoot->occurances>0)
	return TrieRoot->occurances;
	
	return 0;      //   return 1;
}

void Delete(Node* TrieNode,string word)
{
	Node* root=TrieNode;			
	vector< Node* > vec;
	for(int i=0;i<word.length();++i)
	{
		if(root->children[word[i]-'a']==NULL)
		{
			cout<<"ERROR 404, \""<<word<<"\" Not Found\n";
			return;
		}
		root=root->children[word[i]-'a'];
		vec.push_back(root);
	}
	root->occurances -=1;
	while(!vec.empty())
	{
		Node* tmp=(vec.back());
		vec.pop_back();
		if(tmp->occurances!=0)
		return;
		free(tmp);		
	}
	vec.clear();
}

int main()
{
	Node* TrieRoot=new Node();
	Insert(TrieRoot,"the");
	Insert(TrieRoot,"this");
	Insert(TrieRoot,"facade");
	Insert(TrieRoot,"facebook");
	Insert(TrieRoot,"this");
	
	int t=0;
	t = Search(TrieRoot,"this");
	t ? cout<<t<<"\n" : cout<<"Not Found\n";
	t = Search(TrieRoot,"facebook");
	t ? cout<<t<<"\n" : cout<<"Not Found\n";    

/*	t = Search(TrieRoot,"this");
	t ? cout<<"Found\n" : cout<<"Not Found\n";
	t = Search(TrieRoot,"facebook");
	t ? cout<<"Found\n" : cout<<"Not Found\n";     */
		
	Delete(TrieRoot,"facebook");
	t = Search(TrieRoot,"facebook");
	t ? cout<<t<<"\n" : cout<<"Not Found\n";
	
	Delete(TrieRoot,"poop");
	
	Delete(TrieRoot,"this");
	t = Search(TrieRoot,"this");
	t ? cout<<t<<"\n" : cout<<"Not Found\n";
	
	
	return 0;
}

