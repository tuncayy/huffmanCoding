#include<iostream>
#include<vector>
#include<string>
#include <map>
#include <bitset>
#include <fstream>

using namespace std;

struct node
{
	node * leftChild;
	node * rightChild;
	double frequency;
    char content;
	string code;
};

vector<node> nodeArr; //store char and frequences 

node minNumber()
{
	int temp = INT_MAX;
    vector<node>::iterator i1,pos;
    for(i1 = nodeArr.begin();i1!=nodeArr.end();i1++)
 {
	  if(temp>(*i1).frequency)				// find node that has min frequrncy currently
	  {
		 pos = i1;
		 temp = (*i1).frequency;
	  }
 }
 
 node tempNode = (*pos);   // put min to the node
 nodeArr.erase(pos);    //delete min at the end
 

 return tempNode;
}

void setNodeArray(char letters[], int freq[], int size)
{
	
	 for(int i = 0;i<size;i++)
	 {
  
	  node tempNode;
 
	  tempNode.frequency = freq[i];
	  tempNode.content = letters[i];
	  tempNode.leftChild = NULL;
	  tempNode.rightChild = NULL;
	  nodeArr.push_back(tempNode); //put freq,content, left and right child to the array
	 }
}
node buildHuffmantree()
{
	while(!nodeArr.empty())
 { 
  
	  node * tempNode = new node;   
      node * tempNode1 = new node;
      node * tempNode2 = new node;
	  *tempNode1 = minNumber();    //get two minimum frequence
	  *tempNode2 = minNumber();
   
  
   tempNode->leftChild = tempNode1;
   tempNode->rightChild = tempNode2;
   tempNode->frequency = tempNode1->frequency+tempNode2->frequency;
   nodeArr.push_back(*tempNode);
   if(nodeArr.size() == 1)//only the root node exsits
   {
    break;
   }
 }
    return nodeArr[0]; //root
}

string codes[29];
char letter[29];
int i = 0;
void search(node *temproot,string s)
{
	
   node *root1 = new node;
   root1 = temproot;
   root1->code = s;
   if(root1 == NULL)
   {
    cout << "root is not decleared" << endl;
   }
   else if(root1->leftChild == NULL && root1->rightChild == NULL) // when recursion come to last node complete code and put in arrays
   {
    
    cout<<"letter  "<< root1->content <<endl;	
    cout<<"code "<< root1->code <<endl;

	codes[i] = root1->code;
	letter[i] = root1->content;
	i++;
	
   }
   else
   {
   
   root1->leftChild->code = s.append("0");		
   s.erase(s.end()-1);
   root1->rightChild->code = s.append("1");
   s.erase(s.end()-1);


      search(root1->leftChild,s.append("0"));   // recursion section
   s.erase(s.end()-1);
      search(root1->rightChild,s.append("1"));
   s.erase(s.end()-1);

 }
   
}
int asciiarr[29];
string asciibinary[29];
void convertToASCII()
{
	
	char ctemp;
	int ascii;
	
	for(int i = 0; i < 29; i++) // Loop through the inputted string
    {
			ctemp = letter[i];
            ascii = ctemp;
			asciiarr[i] = ascii;
			       
    }

	for(int a = 0; a < 29; a++)
	{
		asciibinary[a] = bitset<8>(asciiarr[a]).to_string();
	}


}

int main()
{
	
	string text = "Hey, Jude, dont make it bad Take a sad song and make it betterRemember to let her into your heartThen you can start to make it better";
	char letters[28];
	int letterCount[28];

	map<char,int> counter;  // first variable will be char, second will be intager
	
	for(int i = 0; i < text.size();i++)
	{
		++counter[tolower(text[i])];
		
	}
	int i = 0;
	for (map<char, int>::iterator c = counter.begin(); c != counter.end(); ++c) 
	{
		cout << c->first << "= " << c->second << '\n';
		letters[i] = c->first;
		letterCount[i] = c->second;
		i++;
	}
	
	setNodeArray(letters,letterCount,i);

	node root = buildHuffmantree();

	search(&root,"");

	
	
	string huffman = "";
	for(int a = 0; a < text.size(); a++)
	{
		for(int b = 0; b < i; b++)
		{
			if(tolower(text.at(a)) == letter[b])
			{
				cout << codes[b] << " ";
				huffman.append(codes[b]);
				huffman.append(" ");
			}
		}
	}

	convertToASCII();

	cout << endl;
	cout << endl;
	cout << endl;

	string ascii = "";
		for(int a = 0; a < text.size(); a++)
	{
		for(int b = 0; b < i; b++)
		{
			if(tolower(text.at(a)) == letter[b])
			{
				cout << asciibinary[b] << " ";
				ascii.append(asciibinary[b]);
				ascii.append(" ");
			}
		}
	}


		ofstream myfile;
  myfile.open ("ascii.txt");
  myfile << ascii;
  myfile.close();

  myfile.open ("hufmann.txt");
  myfile << huffman;
  myfile.close();

	system("pause");
	return 0;
}
