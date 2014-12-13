/*Author name: Wuzheng Ma
 *login name: WM813
 *Created on: 18 Feb 2014
 *Email:wuzheng.ma13@imperial.ac.uk
 */

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<sstream>
using namespace std;


struct Node{
	int data;
	Node* next;
};

Node* hdlist;	//Declare hdlist 

void read_from_data(int);//initialize function "r"
void bubblesort();//initialize function "s"
void write_on_file(int);//initialize function "w"
void insert_element(int);//initialze function "i"
void delete_element(int);//initialize function "i"
void entries_morethan(int, int);//initialize function "e"
void maximum(int);//initialize function "m"
void add_extranode();//initialize function "a"
int avg(int, int);//Function to calculate the average value



int main(int argc, char *argv[]){	
	ifstream infile;
	string comad, filenum;
	const string keyr = "r";		//initialize commands string
	const string keys = "s";
	const string keyw = "w";
	const string keyi = "i";
	const string keyd = "d";
	const string keye = "e";
	const string keym = "m";
	const string keya = "a";
	int file_num, insert_num, delete_num, thres_num;
	infile.open(argv[1]);
	if(!infile.is_open()){
		cout<<"could not open the CommandFile"<<endl;
		exit(EXIT_FAILURE);
	}

	while(infile>>comad){
		if(comad == keyr){		//Command r
			infile>>file_num;
			read_from_data(file_num);
			continue;
		}
		if(comad == keys){		//Command s
			bubblesort();
			continue;
		}
		if(comad == keyw){		//Command w
			write_on_file(file_num);
			continue;
		}
		if(comad == keyi){		//Command i
			infile>>insert_num;
			insert_element(insert_num);
			continue;
		}
		if(comad == keyd){		//Command d
			infile>>delete_num;
			delete_element(delete_num);
			continue;
		}
		if(comad == keye){		//Command e
			infile>>thres_num;
			entries_morethan(thres_num, file_num);
			continue;
		}
		if(comad == keym){		//Command m
			maximum(file_num);
			continue;
		}
		if(comad == keya){		//Command a
			add_extranode();
			continue;
		}
	}
	infile.close();
	cout<<"All commands have been processed."<<endl;
	return 0;
}





//Function "r"
	void read_from_data(int n){
		ifstream infile;
		stringstream ss;	
		string c;
		ss<<n;
		ss>>c;					//Transform int "n" into string
		string a = "data_";
		string b = ".txt";
		string d = a + c + b;	//d = data_c.txt, where c is the string form of n
		int n2;

		infile.open(d.c_str());  //c_str() transform the string to char*
		if(!infile.is_open()){
			cout<<"could not open data.txt"<<endl;
			exit(EXIT_FAILURE);
		}
		if(infile>>n2){						//Initialize the link list
			hdlist = new Node;
			hdlist->data = n2;
			hdlist->next = NULL;
		}
		else{
			cout<<"No elements in the input file."<<endl;	//No input data
			hdlist = NULL;
			return;
		}
		Node* currentptr=hdlist;
		while(infile>>n2){					//Add new elements
			Node* newNode = new Node;
			newNode->data = n2;
			newNode->next = NULL;
			currentptr->next = newNode;
			currentptr=newNode;
		}
		infile.close();
//		}
	}

//Function "s"
	void bubblesort(){
		if(hdlist == NULL){		//Empty list
			return;
		}
		Node *previousptr, *currentptr, *aheadptr;	//initialize three pointers pointing to
													//three adjacent points respectly
		previousptr = hdlist;
		currentptr = previousptr->next;
		aheadptr = currentptr->next;
		bool swap = true;

		while(swap){						 //This while loop will sort all the points except the first point,
										     //it ends when there is no swap happened
			swap = false;
			while(currentptr->next != NULL){
				if(currentptr->data > aheadptr->data){		//Swap happens when the current point is greater
															//than its next point
					currentptr->next = aheadptr->next;
					aheadptr->next = currentptr;
					previousptr->next = aheadptr;
					previousptr = aheadptr;
					aheadptr = currentptr->next;
					swap = true;
				}
				else{
					previousptr = currentptr;			//Otherwise update the pointers
					currentptr = aheadptr;
					aheadptr = aheadptr->next;
				}
			}
			previousptr = hdlist;				//Reset the pointers for doing afterward
			currentptr = previousptr->next;
			aheadptr = currentptr->next;
		}


		if(hdlist->data < currentptr->data){		//If the first point is the smallest one, then sorting is done
			cout<<"points have been sorted"<<endl;
		}
		else{								//Now sorts the first point with the rest sorted points
			currentptr->next=previousptr;	
			previousptr->next=aheadptr;
			hdlist=currentptr;				//If the first point is not the smallest, then points hdlist
											//to the second point
			currentptr=previousptr;
			previousptr=hdlist;
			aheadptr=currentptr->next;
			while(currentptr->data > aheadptr->data){	//Sort the first point to the right place
					currentptr->next = aheadptr->next;
					aheadptr->next = currentptr;
					previousptr->next = aheadptr;
					previousptr = aheadptr;
					aheadptr = currentptr->next;
			}
		}
	}

//Function "w"
	void write_on_file(int n){
		if(hdlist == NULL){		//Empty list
			return;
		}
		ofstream outfile;		//Initialize things
		Node* currentptr;
		currentptr = hdlist;
		stringstream ss;
		string c;
		ss<<n;
		ss>>c;
		string a = "output_";
		string b = ".txt";
		string d = a + c + b;    //d = output_c.txt, where c is the string form of n

		outfile.open(d.c_str(), ios::app);
			while(currentptr != NULL){
				outfile<<currentptr->data<<endl;
				currentptr = currentptr->next;
			}
			outfile.close();
	}

//Function "i"
	void insert_element(int number){
		Node *addoneNode;
		if(hdlist == NULL){			//Empty list
			addoneNode = new Node;
			addoneNode->data = number;
			hdlist = addoneNode;
			addoneNode->next = NULL;
			return;
		}		
		Node *previousptr, *currentptr;	//Initialize things
		addoneNode = new Node;
		addoneNode->data = number;
		previousptr = hdlist;
		currentptr = previousptr->next;
		bool found = false;

		if(addoneNode->data < previousptr->data){		//In the case which the new element is the smallest one
			addoneNode->next = hdlist;
			hdlist = addoneNode;
		}

		while((currentptr != NULL) && (!found)){				//When the new element is not the smallest.
																//loop ends when either of those conditions is not true.
			if(addoneNode->data <= currentptr->data){
				found = true;
			}
			else{
				currentptr = currentptr->next;		//Update pointers
				previousptr = previousptr->next;
			}
		}
		addoneNode->next = currentptr;		//Insert the point
		previousptr->next = addoneNode;
	}

//Function "d"
	void delete_element(int num_delete){
		bool found = false;
		Node *currentptr, *previousptr, *headptr;
		headptr = hdlist;				 //headptr is used only for the case
										//which the num_delete is the first element in the list

		if(hdlist == NULL){		//Empty list
			return;
		}
		else if(hdlist->data == num_delete){		//First element in the list
			hdlist = headptr->next;
			delete headptr;
		}
		else{
			found = false;
			previousptr = hdlist;
			currentptr = hdlist->next;
			while((currentptr != NULL) && (!found)){	//normal case
				if(currentptr->data == num_delete){
					found = true;
					previousptr->next = currentptr->next;
					delete currentptr;
				}
				else{
					currentptr = currentptr->next;
					previousptr = previousptr->next;
				}
			}
		}
	}

//Function "e"
	void entries_morethan(int thres, int n){
		if(hdlist == NULL){		//Empty list
			return;
		}
		ofstream outfile;		//Initialize things
		Node* currentptr;
		currentptr = hdlist;
		stringstream ss;
		string c;
		ss<<n;
		ss>>c;
		string a = "output_";
		string b = ".txt";
		string d = a + c + b;		//d = output_c.txt, where c is the string form of n

		int x=0;
		while(currentptr != NULL){
			if(currentptr->data > thres){
				x++;
               currentptr = currentptr->next;	//get the number of elements with value
												//greater than the threshold value
			}
			else{
				currentptr = currentptr->next;
			}
		}
		outfile.open(d.c_str(), ios::app);
			outfile<<"Number of elements with value greater than "<<thres<<":"<<x<<endl;
			outfile.close();

	}

//Function "m"
	void maximum(int n){
		if(hdlist == NULL){			//Empty list
			cout<<"No elements exists, no maximum value could be calculated."<<endl;
			return;
		}	
		ofstream outfile;			//Initialize things
		stringstream ss;
		string c;
		ss<<n;
		ss>>c;
		string a = "output_";
		string b = ".txt";
		string d = a + c + b;		//d = output_c.txt, where c is the string form of n
		Node *currentptr, *currentmax;
		currentmax = hdlist;
		currentptr = currentmax->next;
		int Max_num = currentmax->data;		//Initialize the maximum value
											// to be the first element in the list

		if(hdlist == NULL){			//Empty list
			cout<<"No elements exists, no maximum value could be calculated."<<endl;
		}
		while(currentptr != NULL){
			if(currentptr->data >= currentmax->data){		//If the current number is greater than
															//the currentmax,let it to be the max number
				Max_num = currentptr->data;
				currentmax = currentptr;
				currentptr = currentptr->next;
			}
			else{
				currentptr = currentptr->next;
			}
		}

		outfile.open(d.c_str(), ios::app);
			outfile<<"Maximum value:"<<Max_num<<endl;
			outfile.close();
	}

//Function "a"
	void add_extranode(){
		Node *currentptr, *nextptr, *betweenNode;	//Initialize pointers
		currentptr = hdlist;
		nextptr = currentptr->next;


		if((hdlist == NULL) || (nextptr == NULL)){		//Empty list or single element
			return;
		}

		while(nextptr != NULL){
			betweenNode = new Node;
			betweenNode->data = avg(currentptr->data, nextptr->data);
			currentptr->next = betweenNode;
			betweenNode->next = nextptr;
			currentptr = nextptr;			//After adding the node, update currentptr
			nextptr = nextptr->next;		//Update nextptr
		}
	}

//Function avg
	int avg(int data0, int data1){
		return (data0 + data1) / 2;
	}




