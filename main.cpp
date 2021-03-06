#include <iostream>
#include <time.h>
#include <stdlib.h>
#include<vector>

using namespace std;

struct Owner{
	string name;
	string address;
	string mobile;
	string phone;
	float value;
	string password;
	int ownerNum;
	
};
struct Node{
	time_t dt;
	Owner *owner;
	int nodeNum;
	int nodeId;
	Node *refNodeId;
	vector<int> childNodeId;
	vector<Node*> refChildNodeId;
	
};
Node *getNode(int num, Owner *own){
	Node *np=new Node;
	np->dt=time(0);
	np->owner=own;
	np->nodeNum=num;
	np->nodeId=(num);
	vector<Node*> v;
	np->refChildNodeId=v;
	np->refNodeId=NULL;
	vector<int> s;
	np->childNodeId=s;
	return np;
}

void query3(Node *child,int id,vector<Node*> &v){
	for(int i=0;i<v.size();i++){
		if(v[i]->nodeId==id){
			v[i]->refChildNodeId.push_back(child);
			v[i]->childNodeId.push_back(child->nodeId);
			child->refNodeId=v[i];
			break;
		}	
	}
}
string encrypt(string s,int n){
	string sol=s;
	for(int i=0;i<sol.length();i++){
		sol[i]+=n;
	}
	return sol;
}
string decrypt(string data,int n){
	string sol=data;
	for(int i=0;i<sol.length();i++){
		sol[i]-=n;
	}
	return sol;
}
Owner *getOwner(int num,string name, string address, string mobile, string phone, float value,string pass){
	
	Owner *own=new Owner;
	own->ownerNum=num;
	own->address=encrypt(address,num);
	own->address=encrypt(name,num);
	own->address=encrypt(mobile,num);
	own->address=encrypt(phone,num);
	own->value=value;
	own->password=encrypt(pass,num);
	return own;	
}
bool query4(vector<Owner*> &owners,Owner *currOwner,vector<Node*> &v){
	cout<<"enter NodeId: ";
			int id;
			cin>>id;
			bool f=false;
			for(int i=0;i<v.size();i++){
				if(v[i]->nodeId==id){
					if(currOwner==v[i]->owner){
						f=true;
					}
					break;
				}	
			}
		
			return f;
}
void query5(vector<Owner*> &owners, Owner *currOwner, vector<Node*> &v){
	//todo
}
void query6(vector<Owner*> &owners,Owner *currOwner, vector<Node*> &v){
	//todo
}
void query7(vector<Node*> v){
	//todo
}
void dfs(Node *root,int &n,int num){
	if(root==NULL){
		n=max(n,num);
	}
	int count=num+1;
	vector<Node*> child=root->refChildNodeId;
	for(int i=0;i<child.size();i++){
		dfs(child[i],n,num+1);
	}
	n=max(n,count);
}
void mergeSet(vector<Node*> &first, vector<Node*> &second,Owner *currOwner){
	//merge sets of same owner
	
	
}
int main(){
	St:
    int num=0,nOwners=0;
    vector<vector<Node*> > set;
    vector<Node*> v;
    vector<Owner*> owners;
    int q;

    Owner *currOwner;
    bool f=false;
    
    while(!f){
    	cout<<"Enter 1 to login 2 to signup: ";
    	
    cin>>q;
    	if(q==1){
			cout<<"enter password and key: ";
	    	string pass;
	    	int key;
	    	cin>>pass;
	    	cin>>key;
	    	for(int i=0;i<owners.size();i++){
	    		if(owners[i]->ownerNum==key){
	    			if(pass==decrypt(owners[i]->password,owners[i]->ownerNum)){
	    				f=true;
	    				currOwner=owners[i];
	    				break;
					}
				}
			}
			cout<<"unable to login!"<<endl;
		}else{
			cout<<"Enter name, address, mobile,phone, value, password:"<<endl;
			string name,address,mobile,phone,pass;
			float value;
			cin>>name>>address>>mobile>>phone;
			cin>>value;
			cin>>pass;
			currOwner=getOwner(nOwners++,name, address, mobile, phone, value,pass);
			owners.push_back(currOwner);
			cout<<"your key is "<<currOwner->ownerNum<<endl;
			f=true;
		}
	}
    
    cout << "Enter one of the queries:" << endl << endl;
    cout << "1. Create the Genesis Node." << endl;
    cout << "2. Create set of child nodes of a particular node." << endl;
    cout << "3. Create a child node that originates from a particular node"<< endl;
    cout << "4. Verify the owner of the node." << endl;
    cout << "5. Edit value of a node" << endl;
    cout << "6. Transfer ownership of a particular node value." << endl;
	cout << "7. Find the longest chain of the genesis node." << endl;
   	cout << "8. Find the longest chain of any node." << endl;
	cout << "9. Merge 2 nodes " << endl;
	cout << "10. Logout."<< endl << endl;
    
    
    while(1){
    	cout<<"Enter Query: ";
		cin>>q;
		if(q==1){
			//push a hardcoded first node 
			vector<Node*> v;
			v.push_back(getNode(num++,currOwner));
			set.push_back(v);
		}else if(q==2){
			//push a set of first nodes
			int n=0;
			cout<<"Enter number of nodes: ";
			cin>>n;
			vector<Node*> v(1);
			for(int i=0;i<n;i++){
				v[0]=(getNode(num++,currOwner));	
				set.push_back(v);
			}
			cout<<"nodes pushed"<<endl;
		}else if(q==3){
			//adding node to any set
			Node *np=getNode(num++,currOwner);
			v.push_back(np);
			cout<<"Enter setNo: ";
			int setNo;
			cin>>setNo;
			set[setNo].push_back(np);
			
			
		}else if(q==4){
			//verify owner
			bool f=false;
			for(int i=0;i<set.size();i++){
				f=query4(owners,currOwner,set[i]);
				if(f){
					cout<<"you are the owner!"<<endl;
				}		
			}
			if(!f){			
				cout<<"you are not owner!"<<endl;
			}
		}else if(q==5){
			//break up a node 
			query5(owners,currOwner,v);
			
		}else if(q==6){
			// transfer owner
			query6(owners,currOwner,v);
			
			
		}else if(q==7){
			//longest chain of main node
			int mx=-1;
			for(int i=0;i<set.size();i++){
				
				dfs(set[i][0],mx,0);	
			}
			cout<<"max chain="<<mx<<endl;
			
		}else if(q==8){
			//longest chain of sub node
			cout<<"enter node id: "<<endl;
			int id;
			cin>>id;
			int ans=-1;
			bool f=false;
			
		}else if(q==9){
			//merge nodes
			cout<<"enter 1st and 2nd set number: "<<endl;
			int f,s;
			cin>>f>>s;
			mergeSet(set[f],set[s],currOwner);
			
		}else if(q==10){
			//log out
			currOwner=NULL;
			goto St;
		}else {
			break;
		}
	}
    return 0;
}
