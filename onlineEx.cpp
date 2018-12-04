#include<iostream>
#include<cstdlib>
using namespace std;
class hash{
    private:
        int hash_pos;
        int array[40];
    public:
        hash();
        void insert();
        void search();
        int Hash(int );
        int reHash(int );
        void Delete();
};
hash::hash(){
    for(int i = 0; i < 40; i++){
        array[i] = '*';
    }
}
void hash::insert(){
    int data;
    int count = 0;
    cout<<"Enter the data to insert: ";
    cin>>data;
    hash_pos = Hash(data);
    if(hash_pos >= 40){
        hash_pos = 0;
    }
    while(array[hash_pos] != '*'){
        hash_pos = reHash(hash_pos);
        count++;
        if(count>=40){
            cout<<"Memory Full!!No space is avaible for storage";
            break;
        }
    }
    if(array[hash_pos] == '*'){
        array[hash_pos] = data;
    }
    cout<<"Data is stored at index "<<hash_pos<<endl;
}
int hash::Hash(int key){
    return key%100;
}
int hash::reHash(int key){
    return (key+1)%100;
}
void hash::search(){
    int key,i;
    bool isFound = false;
    cout<<"Enter the key to search: ";
    cin>>key;
    for(i = 0; i < 40; i++){
        if(array[i] == key){
            isFound = true;
            break;
        }
    }
    if(isFound){
        cout<<"The key is found at index "<< i <<endl;
    }else{
        cout<<"No record found!!"<<endl;
    }
}
void hash::Delete(){
    int key,i;
    bool isFound = false;
    cout<<"Enter the key to delete: ";
    cin>>key;
    for(i = 0; i < 40; i++){
        if(array[i] == key){
            isFound = true;
            break;
        }
    }
    if(isFound){
        array[i] = '*';
        cout<<"The key is deleted"<<endl;
    }else{
        cout<<"No key is Found!!";
    }
}
int main(){
    hash h;
    int choice;
    while(1){
        cout<<"\n1. Insert\n2. Search\n3. Delete\n4. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice){
            case 1:
                h.insert();
                break;
            case 2:
                h.search();
                break;
            case 3:
                h.Delete();
                break;
            case 4:
                exit(0);
            default:
                cout<<"\nEnter correct option\n";
                break;
        }
    }
    return 0;
}
