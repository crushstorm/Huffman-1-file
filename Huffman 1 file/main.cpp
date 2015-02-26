//
//  main.cpp
//  HuffmanCode Alone
//
//  Created by Bernando Vialli on 4/25/13.
//  Copyright (c) 2013 Bernando Vialli. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <set>
#include <cctype>
#include<map>
#include <math.h>
#include <fstream>
#include <time.h>
using namespace std;

struct sortPairSecond
{
    bool operator()(const pair<string, int> &lhs, const pair<string, int> &rhs)
    {
        return lhs.second <= rhs.second;
        //cout << lhs.second<<endl;
    }
};
class Node
{
public:
	string c;					//stores string
	int counter;				//stores number of occurrences of string in file
    Node* left;				//point to left child
    Node* right;				//point to right child
	
	Node(){left=NULL, right=NULL, c= "", counter=0;}        //default no arg constructor
	Node(const string ch, const int count):c(ch),counter(count)	 //constructor
	{left=NULL;right=NULL;}					 //constructor
	Node(int count,Node* l, Node* r):counter(count),left(l),right(r)
	{c="";}
};



Node* createTree(multimap<int, Node> stringMap)
{
	bool done=false;
	while(!done)                             //loop until done
	{
		
		int calcNode=0;                  //local variable to calculate parent node
        if(stringMap.size()==2)	         //exit loop if last 2 elements
			done=true;
		multimap<int, Node>::iterator it1 = stringMap.begin();
		multimap<int, Node>::iterator it2 = stringMap.begin();
		it2++;
        
		calcNode=((*it1).first)+((*it2).first);   //calculate the new node counter
		Node temp(calcNode, new Node((*it1).second), new Node((*it2).second));  //create new node
		
		
		stringMap.insert(make_pair(calcNode,temp));               //insert new node
		stringMap.erase(it1);					//delete from multimap
		stringMap.erase(it2);				        //delete from multimap
	}
    
	multimap<int, Node>::iterator it1 = stringMap.begin();   //create assign and return root node
	Node* root=new Node((*it1).second);
	return root;
}

void  encode(Node* root,string s, map<string,string> & codeMap)
{
	if (root!=NULL)
	{
		encode(root->left,s+"0",codeMap);            //when traversing down left path store add 0 to string
		encode(root->right,s+"1",codeMap);           //when traversing down right path store add 1 to string
		if(root->left==NULL&&root->right==NULL)
			codeMap[root->c]=s;
    }
}

int main(int argc, const char * argv[])
{
    
    //  string str[30][3];
    int maxLength = 0;
    int numberOfBits = 0;
    int totalDistinctWord = 0;
    int totalWord = 0;
    clock_t t1,t2;
    t1=clock();
    //code goes here
    
    ifstream myfile("/Users/crushstorm/Dropbox/Spring 13/CS 577/Prog Project/HuffmanCode Alone/data/1 (5).txt");
    int a = 0;
    int b = 0;
    if(!myfile) //Always test the file open.
    {
        cout<<"Error opening output file"<<endl;
        system("pause");
        return -1;
    }
    string nextToken;
    string  array[1000];
    std::map<std::string, int> wordCount;
    long totalChar = 0;
    while (myfile >> nextToken) {
        //    cout << nextToken<<" "<<endl;
        totalWord++;
        if (maxLength < nextToken.length())
            maxLength = nextToken.length();
        //cout << maxLength<<endl;
        totalChar = totalChar+nextToken.length();
        ++wordCount[nextToken];
        //  array[a] = nextToken;
        //cout << nextToken << endl;
        a++;
    }
    
    /*   for (std::map<std::string, int>::iterator it = wordCount.begin(); it != wordCount.end(); ++it)
     {
     cout << it->first <<" : "<< it->second << endl;
     }*/
    
    /*  for (int i =0; i < a; i++)
     {
     cout << array[i] << endl;
     
     
     }*/
    cout <<endl;
   /* ifstream myfile1("/Users/crushstorm/Dropbox/Spring 13/CS 577/Prog Project/HuffmanCode Alone/speech.txt");
    if(!myfile1) //Always test the file open.
    {
        cout<<"Error opening output file"<<endl;
        system("pause");
        return -1;
    }
    string nextToken1;
    string  array1[1000];
    int totalWord1= 0;
    std::map<std::string, int> wordCount1;
    //long totalChar = 0;
    while (myfile1 >> nextToken1) {
        //    cout << nextToken<<" "<<endl;
        totalWord1++;
        //cout << maxLength<<endl;
        // totalChar = totalChar+nextToken.length();
        ++wordCount1[nextToken1];
        //  array[a] = nextToken;
        //cout << nextToken << endl;
    }
    for (std::map<std::string, int>::iterator it = wordCount1.begin(); it != wordCount1.end(); ++it)
    {
        cout << it->first <<" : "<< it->second << endl;
    }
    cin >> totalWord1;*/
    set<pair<string,int>, sortPairSecond > mySet;
    multimap<int,Node> stringMap;
    for(map<string, int>::const_iterator it = wordCount.begin(); it != wordCount.end(); ++it)
    {
        mySet.insert(*it);
    }
    for(set<pair<string, int> >::const_iterator it = mySet.begin(); it != mySet.end(); ++it)
    {
        //   cout << it->first << " = " << it->second << "\n";
        stringMap.insert(make_pair(it->second,Node(it->first,it->second)));
        totalDistinctWord++;
    }
    Node* root=createTree(stringMap);
    // Store it in binary tree
    
   // cout << totalDistinctWord<<endl;
    // Then call the tree again
    double frequency,totalFrequency=0;                             //used to compute frequency
	numberOfBits = (int)(log(totalDistinctWord)/log(2))+1;
    int totalHuffmanBit = 0;
    int lengthofEach[5000];
    //prints out multimap and frequency
    int count = 0;
	for (multimap<int,Node>::iterator it=stringMap.begin();it!=stringMap.end();++it)
	{
		cout << "String="<<(*it).second.c<<" count="<<(*it).first<<"frequency="<<(frequency=( (*it).first/(double)totalWord)*100)<<endl;
        // lengthofEach[count] = (*it).first;
		totalFrequency+=frequency;
	}
    //print the total number of characters, and also the sum of all frequency percentage (for error checking!)
    cout<<endl;
    numberOfBits *= totalWord;
	//cout <<"String count ="<<totalWord<<" total frequency ="<<totalFrequency<<endl<<endl;
    
    map<string,string> codeMap;
    string s;
    //map used to store Huffman Key
	encode(root,s, codeMap);
    count = 0;
    int total = 0 ;
    int shortestword = 0;
    string shortestword1;
    for (map<string,string>::iterator it=codeMap.begin();it!=codeMap.end();++it)
    {
        if (shortestword<(*it).second.length())
        {
            shortestword = (*it).second.length();
            shortestword1 = (*it).first;
        }
		cout<<"String "<<(*it).first<<" = "<<(*it).second<<endl;
        // total = (*it).second.length();
        count++;
        lengthofEach[count] = (*it).second.length();
        // cout << lengthofEach[count];
        
    }
    cout << shortestword1<< " "<< shortestword<<endl;
    count = 0;
    // count how many bit of the huffman code
    for (std::map<std::string, int>::iterator it = wordCount.begin(); it != wordCount.end(); ++it)
    {
      //     cout << it->first <<" : "<< it->second << endl;
        count++;
        total += lengthofEach[count]*it->second;
        //  cout << total<<endl;
    }
    double percentageCompression;
    // cout<<total<<endl;
    percentageCompression= ((double)total/numberOfBits)*100;
    cout <<percentageCompression<<endl;
    t2 = clock();
    float diff ((float)t2-(float)t1);
    float seconds = diff / CLOCKS_PER_SEC;
 //   cout<<seconds<<" seconds"<<endl;
    system("pause");
    
    return 0;
}

