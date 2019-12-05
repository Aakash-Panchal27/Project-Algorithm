#include<bits/stdc++.h>

using namespace std;

struct vertex {

    int parent, suffix_link, output_link, index;
    char character;
    bool isword;
    string mystr;
    array<int,26> clusters;

    vertex(char ch, int id = -1, int papa = -1)
    {
        character = ch;
        index = id;
        mystr="";
        parent = papa;
        suffix_link = output_link = -1;
        isword = false;
        for(int i = 0; i < 26; i++)
        {
            clusters[i] = -1;
        }
    }

};

class Aho_Corasick{

public:

    vector<vertex> Trie;

    Aho_Corasick()
    {
        vertex one = vertex('\0', -1 , -1);
        Trie.push_back(one);
    }

    void make_trie(vector<string> & patterns)
    {
        for(int i = 0; i < patterns.size(); i++)
        {
            add_string(patterns[i]);
        }
    }

    void add_string(string & one)
    {
        int current_vertex = 0;
        for(int i = 0; i < one.size(); i++)
        {
            //cout<<current_vertex<<endl;
            if(Trie[current_vertex].clusters[one[i]-'a'] == -1)
            {
                vertex newone = vertex(char(one[i]), int(Trie.size()), current_vertex);
                Trie.push_back( newone );
                Trie[current_vertex].clusters[int(one[i]-'a')] = int(Trie.size())-1;
            }
            current_vertex = Trie[current_vertex].clusters[int(one[i]-'a')];
        }
        Trie[current_vertex].isword = true;
        Trie[current_vertex].mystr = one;
    }


    bool find_word(string & one)
    {
        int root =0;
        for(int i=0;i<one.size();i++)
        {
            if(Trie[root].clusters[one[i]-'a']==-1)
                return false;
            root = Trie[root].clusters[one[i]-'a'];
        }

        return true;
    }

    void make_suffix_links()
    {
        int current_vertex = 0;
        Trie[0].suffix_link = 0;

        queue<int> container;

        container.push(0);

        while(container.empty() == false)
        {
            int id = container.front();
            container.pop();

            for(int i=0;i<26;i++)
            {
                if(Trie[id].clusters[i] != -1)
                {
                    Trie[Trie[id].clusters[i]].suffix_link = suffix_link_helper(Trie[id].clusters[i], i);
                    container.push(Trie[id].clusters[i]);
                }
            }
        }
    }

    int suffix_link_helper(int node, int charid)
    {
        if(Trie[node].parent == 0)
        {
            return 0;
        }

        if(Trie[node].parent == -1)
        {
            if(Trie[node].clusters[charid] != -1)
            {
                return Trie[0].clusters[charid];
            }
            else
            {
                return 0;
            }
        }

        if(Trie[Trie[Trie[node].parent].suffix_link].clusters[charid] != -1)
            return Trie[Trie[Trie[node].parent].suffix_link].clusters[charid];
        else
            return suffix_link_helper(Trie[Trie[node].parent].suffix_link, charid);

    }

    void make_output_link()
    {
        int current_vertex = 0;

        queue<int> container;

        container.push(0);

        while(container.empty() == false)
        {
            int id = container.front();
            container.pop();

            for(int i=0;i<26;i++)
            {
                if(Trie[id].clusters[i] != -1)
                {
                    Trie[Trie[id].clusters[i]].output_link = output_link_helper(Trie[id].clusters[i]);
                    container.push(Trie[id].clusters[i]);
                }
            }
        }

    }

    int output_link_helper(int node)
    {
        if(node == 0)
        {
            return -1;
        }

        if(Trie[Trie[node].suffix_link].isword == true)
        {
            return Trie[node].suffix_link;
        }
        else
        {
             return output_link_helper(Trie[node].suffix_link);
        }
    }

    void process_string(string & one)
    {
        int root = 0;
        for(int i = 0; i < one.size(); i++)
        {
            while(Trie[root].clusters[one[i]-'a'] == -1)
            {
                root = Trie[root].suffix_link;

                if(root == 0)
                {
                    break;
                }
            }

            if(Trie[root].clusters[one[i]-'a'] != -1)
                root = Trie[root].clusters[one[i]-'a'];
            else
            {
                i++;
                root = 0;
                continue;
            }

            if(Trie[root].isword == true)
            {
                cout << Trie[root].mystr << endl;
            }


            int io = root;
            while(Trie[io].output_link != -1)
            {
                if(Trie[Trie[io].output_link].isword == true)
                {
                    cout << Trie[Trie[io].output_link].mystr << endl;
                }
                io = Trie[io].output_link;
            }

        }

    }

};

int main()
{
    Aho_Corasick aho = Aho_Corasick();

    string one = "i", two = "in", three = "tin", four = "sting";

    vector<string> vec;

    vec.push_back(one);
    vec.push_back(two);
    vec.push_back(three);
    vec.push_back(four);

    aho.make_trie(vec);

    aho.make_suffix_links();

    aho.make_output_link();

    string pst = "sting";

    for(int i = 0;i < pst.size(); i++)
    {
        pst[i] = tolower(pst[i]);
    }

    aho.process_string(pst);

    return 0;
}
