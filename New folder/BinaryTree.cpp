#include<iostream>
using namespace std;

struct node {
	int price;
	long long int mno ; //Mobile Number
	string pname; //Product Name
	string sname; //Seller Name
	int  catno;
	struct node *left;
	struct node *right;
	public:
		node()
		{
			price = 0;
			mno = 0;
			pname = '\0';
			sname = '\0';
			catno = '\0';
			left = NULL ;
			right = NULL;
		}
		void inputData();
};


struct node *createNode(string pn , string sn , int p , long long int mn)
{
	struct node *nod;
	nod = new node;
	
	
	nod->pname = pn;
	
	nod->price = p;
	
	nod->sname = sn;
	
	nod->mno = mn ;
	nod->left = NULL ;
	nod->right = NULL;
	return nod;
}

struct node *insert(struct node *root  , string pn , string sn , int price , long long int mno)
{
	if(root==NULL)
	{
		return createNode(pn,sn,price,mno);
	}
	else if(pn < root->pname)
	{
		root->left =  insert(root->left , pn,sn,price,mno);
	}
	else if(pn > root->pname)
	{
		root->right = insert(root->right , pn,sn,price,mno);
	}
	return root;
}

void inorder(struct node *root)
{
	
	if(root != NULL)
	{
		// Traverse left
		inorder(root->left);
		//Print node
		cout<<"\n\n : "<<root->pname<<"   "<<root->sname<<"  "<<root->price<<"   "<<root->mno;
		// Traverse right
		inorder(root->right);
	}
}

int main()
{
	struct node *root = NULL;
	int opt,price;
	string pn,sn;
	long long int mno;
	printf("\nEnter First Entry  : ");
	cout<<"\nEnter Product Name : ";
	getline(cin,pn);
	cout<<"\nEnter Sellar Name : ";
	getline(cin,sn);
	cout<<"\nEnter Price : ";
	cin>>price;
	cout<<"\nEnter Contact Number : ";
	cin>>mno;
	root = createNode(pn,sn,price,mno);
	while(1)
	{
		printf("\n\nEnter : 1:Insert data  \n2:Inorder traversal \n0:Exit");
		printf("\nEnter Option : ");
		scanf("%d",&opt);
		if(opt==0)
		{
			return 0;
		}
		switch(opt)
		{
			case 1:
				cout<<"\nEnter Product Name : ";
				getline(cin,pn);
				getline(cin,pn);
				cout<<"\nEnter Sellar Name : ";
				getline(cin,sn);
				cout<<"\nEnter Price : ";
				cin>>price;
				cout<<"\nEnter Contact Number : ";
				cin>>mno;
				insert(root , pn,sn,price,mno);
				break;
			case 2:
				inorder(root);
				break;
			}
		}
			 
}
