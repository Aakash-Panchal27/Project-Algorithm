//g++  5.4.0

#include <bits/stdc++.h>

using namespace std;


struct node{
    int frequency;
    char in;
    node * left;
    node * right;
    node(int freq, char i)
    {
        frequency=freq;
        in = i;
        left=NULL;
        right=NULL;
    }
   
};

struct comparator{

    bool operator()(node*one,node*two)
    {
          if(one->frequency>two->frequency)return true;
            else return false;
    }
   
};

void obtain_huffmancodes(node*rootm, string current)
{
	if(rootm->left== NULL && rootm->right== NULL && rootm->in!='0')
	{
	cout<<rootm->in<<"-"<<current<<endl;
	return;
	}
	
	obtain_huffmancodes(rootm->left, string(current+"0"));
	obtain_huffmancodes(rootm->right, string(current+"1"));

}

int main()
{
    string input;
   
    cin>>input;
   
    unordered_map<char,int> freq;
   
   
    for(int i=0;i<input.size();i++)
    {
        freq[input[i]]++;
    }
   
    priority_queue<node*, vector<node*>, comparator> container;
   
    for(auto val:freq)
    {
    node* temp=new node(val.second, val.first);
        container.push(temp);
    }
   
    //cout<<container.top()->in<<endl;
   
   
    while(container.size()>=2)
    {
    node*one=container.top();
   
    container.pop();
   
    node * two = container.top();
   
    container.pop();
   
    node* curr=new node(one->frequency+two->frequency,'0');
   
    curr->left = one;
    curr->right= two;
   
    container.push(curr);
   
    }
   
    node*rootm = container.top();
   
    container.pop();
   
    string ans="";
   
    obtain_huffmancodes(rootm,ans);
   
   
}
