/*----------------------------------------------------------------------
Name:		Jason Hellwig
Course:		CPSC 131
Project:	No.14 Part 1
Date:		May 10 2012
Professor:	Dr. Ray Ahmadnia
Purpose:	Uses a Binary Search Tree to manage bank acounts.  Funtions
			include display, deposit, withrawl, opening and closing
			accounts.
----------------------------------------------------------------------*/
//header files
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//bank account structure
struct ACCOUNT
{
	int ID;
	string name;
	float balance;
};

//Bank class definition
template <class T>
class BST
{
private:
	struct node
	{
		T info;
		node* left, *right;
	};
	node* root;

	void insert(node*&,const T&);
	void search(node*, int, node*&);
	void display(node*);
	void deleteNode(node*&);
	void remove(node*&, int);
	void deleteAll(node*&);
public:
	BST(){root=NULL;}
	void insert(const T& acct){insert(root,acct);}
	void display(){cout<<"ID\tName\tBalance\n";display(root);}
	void balance();
	void deposit();
	void withdraw();
	void close();
	void open();
	~BST(){deleteAll(root);}
};

/*----------------------------------------------------------------------
Name:		insert
Purpose:	inserts nodes into the BST
----------------------------------------------------------------------*/
template <class T>
void BST<T>::insert(node*& p, const T& data)
{
	if (p == NULL)
	{
		p = new node;
		p->info.ID = data.ID;
		p->info.name = data.name;
		p->info.balance = data.balance;
		p->left=p->right=NULL;
	}
	else if (data.ID < p->info.ID)
		insert(p->left,data);
	else 
		insert(p->right,data);
}

/*----------------------------------------------------------------------
Name:		search
Purpose:	searches the BST for a given ID and provides a reference to
			the pointer of the found ID.
----------------------------------------------------------------------*/
template <class T>
void BST<T>::search(node* p, int ID, node*& found)
{
	if (p!= NULL && p->info.ID != ID)
	{
		if (ID < p->info.ID)
			search(p->left,ID,found);
		else
			search(p->right,ID,found);
	}
	else if (p->info.ID == ID)
		found = p;
}

/*----------------------------------------------------------------------
Name:		display
Purpose:	Displays the inorder BST
----------------------------------------------------------------------*/
template <class T>
void BST<T>::display(node* p)
{
	if (p != NULL)
	{
		display(p->left);
		cout<<p->info.ID<<'\t'<<p->info.name<<'\t'<<p->info.balance<<endl;
		display(p->right);
	}
}

/*----------------------------------------------------------------------
Name:		balance
Purpose:	displays the balance of an account
----------------------------------------------------------------------*/
template <class T>
void BST<T>::balance()
{
	cout<<"Enter your ID number:";
	int num;
	cin>>num;
	node* acct = NULL;
	search(root, num, acct);
	cout<<acct->info.name<<", you have "<<acct->info.balance<<" in your accout.\n";
}

/*----------------------------------------------------------------------
Name:		deposit
Purpose:	deposits money into an account
----------------------------------------------------------------------*/
template <class T>
void BST<T>::deposit()
{
	cout<<"Enter your ID number:";
	int num;
	cin>>num;
	node* acct = NULL;
	search(root, num, acct);
	cout<<acct->info.name<<", how much would you like to deposit?";
	float money;
	cin>>money;
	acct->info.balance+=money;
	cout<<acct->info.name<<", your new balance is "<<acct->info.balance<<".\n";
}

/*----------------------------------------------------------------------
Name:		withdraw
Purpose:	withdraws money from an account
----------------------------------------------------------------------*/
template <class T>
void BST<T>::withdraw()
{
	cout<<"Enter your ID number:";
	int num;
	cin>>num;
	node* acct = NULL;
	search(root, num, acct);
	cout<<acct->info.name<<", how much would you like to withdraw?";
	float money;
	cin>>money;
	acct->info.balance-=money;
	cout<<acct->info.name<<", your new balance is "<<acct->info.balance<<".\n";
}

/*----------------------------------------------------------------------
Name:		close
Purpose:	closes an account
----------------------------------------------------------------------*/
template <class T>
void BST<T>::close()
{
	cout<<"Enter your ID number:";
	int num;
	cin>>num;
	node* acct = NULL;
	search(root, num, acct);
	cout<<acct->info.name<<", your accout is now closed.\n";
	remove(root, num);
}

/*----------------------------------------------------------------------
Name:		remove
Purpose:	finds the selected node to remove in the BST
----------------------------------------------------------------------*/
template <class T>
void BST<T>::remove(node*& p, int n)
{
	if(n < p->info.ID)
		remove(p->left,n);
	else if(n > p->info.ID)
		remove(p->right,n);
	else
		deleteNode(p);
}

/*----------------------------------------------------------------------
Name:		deleteNode
Purpose:	deletes a node in the BST through copying
----------------------------------------------------------------------*/
template <class T>
void BST<T>::deleteNode(node*& p)
{
	node* temp;
	temp = p;
	if (p->left==NULL)
	{	
		p = p->right;
		delete temp;
	}
	else if (p->right==NULL)
	{
		p=p->left;
		delete temp;
	}
	else 
	{
		temp = p->left;
		while (temp->right != NULL)
		{
			temp=temp->right;
		}
		p->info.ID = temp->info.ID;
		p->info.name= temp->info.name;
		p->info.balance = temp->info.balance;
		remove(p->left,p->info.ID);
	}		
}

/*----------------------------------------------------------------------
Name:		open
Purpose:	oppens an account
----------------------------------------------------------------------*/
template <class T>
void BST<T>::open()
{
	cout<<"What name will this account be under?";
	ACCOUNT acct;
	cin>>acct.name;
	cout<<"Welcome "<<acct.name<<", please enter an ID number for this account:";
	cin>>acct.ID;
	cout<<"What is your starting balance:";
	cin>>acct.balance;
	insert(root,acct);
	cout<<"Thank you "<<acct.name<<", your account has been created.\n";
}

/*----------------------------------------------------------------------
Name:		deleteALL
Purpose:	deletes all nodes in the BST
----------------------------------------------------------------------*/
template <class T>
void BST<T>::deleteAll(node*& p)
{
	if (p != NULL)
	{
		deleteAll(p->left);
		deleteAll(p->right);
		delete p;
	}
}


//function prototypes
template <class T>
void CreateBST(BST<T>& bank);
void DisplayMenu();
int GetChoice();
bool StopTest();


int main()
{
	BST<ACCOUNT> Bank;
	CreateBST(Bank);
	DisplayMenu();
	int choice;
	do
	{
		choice = GetChoice();
		switch(choice)
		{
		case 1: Bank.display();break;
		case 2: Bank.balance();break;
		case 3: Bank.deposit();break;
		case 4: Bank.withdraw();break;
		case 5: Bank.close();break;
		case 6: Bank.open();break;
		default: cout<<"invalid choice\n";
		}
	}
	while (StopTest());

	return 0;
}

/*----------------------------------------------------------------------
Name:		CreateBST
Purpose:	Creates the BST from a set of data
----------------------------------------------------------------------*/
template <class T>
void CreateBST(BST<T>& bank)
{
	ifstream fin;
	fin.open("accounts_14.1.txt");
	if (!fin)
	{
		cout<<"Could not open text file, quiting...\n\n";
		exit(0);
	}
	ACCOUNT temp;
	while (!fin.eof())
	{
		fin>>temp.ID;
		fin>>temp.name;
		fin>>temp.balance;
		bank.insert(temp);
	}
	fin.close();
}

/*----------------------------------------------------------------------
Name:		GetChoice
Purpose:	Gets the users choice for the using the bank
----------------------------------------------------------------------*/
int GetChoice()
{
	cout<<"Please enter your selection(1-6):";
	int choice;
	cin>>choice;
	return choice;
}

/*----------------------------------------------------------------------
Name:		DisplayMenu
Purpose:	Displays the menu of the bank to the user
----------------------------------------------------------------------*/
void DisplayMenu()
{
	cout<<"\n\n\n\n";
	cout<<"-----------------------Bank of California------------------------------------\n";
	cout<<"Please select from one of the following choices:\n";
	cout<<"1: Display all accounts\n";
	cout<<"2: Show my balance\n";
	cout<<"3: Deposit\n";
	cout<<"4: Withdraw\n";
	cout<<"5: Close an account\n";
	cout<<"6: Open an account\n\n";
}

/*----------------------------------------------------------------------
Name:		StopTest
Purpose:	tests whether or not the end the program
----------------------------------------------------------------------*/
bool StopTest()
{
	cin.ignore(255,'\n');
	cout<<"Continue(y/n)?";
	char c;
	cin.get(c);
	cin.ignore(255,'\n');
	c = tolower(c);
	if (c == 'n')
		return 0;
	else return 1;
}

/*----------------------------------------------------------------------
sample I/O

-----------------------Bank of California------------------------------------
Please select from one of the following choices:
1: Display all accounts
2: Show my balance
3: Deposit
4: Withdraw
5: Close an account
6: Open an account

Please enter your selection(1-6):1
ID      Name    Balance
11      Tory    1111
22      Luara   1222
33      Maria   1333
44      Andre   1444
55      Cario   1555
66      Alison  1666
Continue(y/n)?y
Please enter your selection(1-6):5
Enter your ID number:55
Cario, your accout is now closed.
Continue(y/n)?y
Please enter your selection(1-6):6
What name will this account be under?Jason
Welcome Jason, please enter an ID number for this account:25
What is your starting balance:4000
Thank you Jason, your account has been created.
Continue(y/n)?y
Please enter your selection(1-6):1
ID      Name    Balance
11      Tory    1111
22      Luara   1222
25      Jason   4000
33      Maria   1333
44      Andre   1444
66      Alison  1666
Continue(y/n)?y
Please enter your selection(1-6):3
Enter your ID number:25
Jason, how much would you like to deposit?437
Jason, your new balance is 4437.
Continue(y/n)?y
Please enter your selection(1-6):2
Enter your ID number:25
Jason, you have 4437 in your accout.
Continue(y/n)?y
Please enter your selection(1-6):4
Enter your ID number:25
Jason, how much would you like to withdraw?438
Jason, your new balance is 3999.
Continue(y/n)?y
Please enter your selection(1-6):5
Enter your ID number:33
Maria, your accout is now closed.
Continue(y/n)?y
Please enter your selection(1-6):1
ID      Name    Balance
11      Tory    1111
22      Luara   1222
25      Jason   3999
44      Andre   1444
66      Alison  1666
Continue(y/n)?n

----------------------------------------------------------------------*/
