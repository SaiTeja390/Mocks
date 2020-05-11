// Example program
#include <iostream>
#include <string>
#include<vector>
using namespace std;

// template for a node in a tree. Here we are abstracting a record which has a key 
// Record is any type which has a key associated with it along with additional optional data
// the TreeNode has a left and right child pointers pointing to its left and right children respectively
template<typename R = int, typename K = int>
struct TreeNode{
    R record;
    TreeNode* left;
    TreeNode* right;
    TreeNode() = default;
    TreeNode(const R& r): record(r) {}
};

// template for a Binary Search Tree which holds records of type R, and keys of type K
template<typename R=int, typename K=int>
class BST{
    public:
    
    //DECLARATIONS
    BST() = default;

    const R* searckKey (const K& key) const;

    // DEFINITIONS
    // searches the tree for a given key
    const R* searchKey (const K& key) const {
        return searchTree(this->root, key);
        }
    
    // inserts a record into the tree if 
    // another record with the same key is not already present in the tree
    R* insertRecord(const R& node){
        auto *new_node = new TreeNode<R,K>(node);  // creates the new TreeNode with the corresponding record
        if(root == nullptr){
            root = new_node;
            return &(new_node->record);         // if the tree is empty insert the new node as root         
        }
        bool left, right;                   // boolean vars which capture whether the current node
        left = right = false;               // is its parent's left or right child  
        
        TreeNode<R,K> *parent = nullptr, *cur = root; 
        while(true){
            if(cur == nullptr && left){
                parent->left = new_node;        // if we reach a child of a leaf node it means we reached  
                break;                          // the exact position at which the new node has to be inserted 
            }
            else if(cur == nullptr && right){
                parent->right = new_node;
                break;
            }
            else if(cur->record == node){
                cerr<<"Record Already Exists"<<endl;  // if a node with the new key already exists 
                delete new_node;                      // the newly created TreeNode is deleted and 
                return &(cur->record);                // already existing node with the required key is returned 
            }
            else if(cur->record > node){
                parent = cur;
                cur = cur->left;
                left = true;
                right = false;
            }
            else{
                parent = cur;
                cur = cur->right;
                right = true;
                left = false;
                }
        }
        return &(new_node->record);           // returns the address the inserted record in the BST
    }
    
// inorder Traversal of the BST
    void inorderTraversal(TreeNode<R,K> *root){
        if(root == nullptr) return;
        inorderTraversal(root->left);
        cout<<root->record<<", ";
        inorderTraversal(root->right);
        
    }
    
    void printTree(){
        inorderTraversal(root);
    }
    
    // inserts new records into the Binary Search Tree
    void buildTree(vector<R> &records){
      for(auto &record : records){
        insertRecord(record);
      }

      }
    
    
    private:
    TreeNode<R,K> *root=nullptr;
    // R* searchTree(const R* root, const K& key) const;
    
    const R* searchTree(const TreeNode<R,K>* root, const K& key) const{
        // We had reached a leaf in our search for the given key which implies 
        // the record with the given key does not exist
        if(!root){
            cout<<"Record with key "<<key<<" does not exist"<<endl; 
            return nullptr;
        }
        
        // if the current node's val equals the given key return the current node's record
        if(root->record == key){
            return &(root->record);
        }
        
        // if the current node's val is greater than the given key the required node
        // should be present in the left sub-tree
        if(root->record > key){
            return searchTree(root->left, key);
        }
        // if the current node's val is lesser than the given key the required node
        // should be present in the right sub-tree
        return searchTree(root->right, key);
    }
    
};

// An abstraction of a typical record with key and value
template <typename K, typename V>
class Record{
    public:
    Record() = default;
    Record(K key, V value): key(key), value(value){}
    
    // operator overloading of comparison operators "==", "<", ">" through friend functions
    // to enable comparison of the objects of type Record<K,V> using these operators
    friend bool operator==(const Record<K,V> &r1, const Record<K,V> &r2){
        return r1.key == r2.key;
    }
    friend bool operator==(const Record<K,V> &r1, const K & key){
        return r1.key == key;
}    
    friend bool operator<(const Record<K,V> &r1, const Record<K,V> &r2){
        return r1.key < r2.key;
    }
    friend bool operator<(const Record<K,V> &r1, const K & key){
        return r1.key < key;
    }

    friend bool operator>(const Record<K,V> &r1, const Record<K,V> &r2){
        return r1.key > r2.key;
    }
    friend bool operator>(const Record<K,V> &r1, const K & key){
        return r1.key > key;
    }
    
    // operator overloading of "<<" (output) and ">>" (input) stream operators
    // to input into and output from the objects of type Record<K,V>
    friend ostream& operator<<(ostream &os, const Record<K,V> &record){
        os<<record.key<<" "<<record.value;
        return os;
    }
    friend istream& operator>>(istream &is, Record<K,V> &record){
        is>>record.key>>record.value;
        if(!is){
            record = Record();
        }
        return is;
    }
    private:
    K key;                         // Key
    V value;                       // Value     
};


int main()
{
  BST<int,int> int_tree;
  auto int_records = vector<int>{1,2,5,3,5,7,-1};
  int_tree.buildTree(int_records);
  cout<<"INT_TREE"<<endl;
  auto int_node = int_tree.searchKey(11);
  if(int_node) cout<<"\n"<<*(int_node)<<endl;
  
  int_tree.printTree();
  
  BST<string,string> string_tree;
  auto string_records = vector<string>{"sai","hari","ramu","phani","Samuel"};
  string_tree.buildTree(string_records);
  cout<<"\n\nSTRING_TREE"<<endl;
  auto string_node = string_tree.searchKey("sai");
  if(string_node) cout<<"\n"<<*(string_node)<<endl;
  
  string_tree.printTree();

  Record<int,string> record(2,"sai");
  BST<Record<int,string>,int> tree;    
  while(cin>>record){
    tree.insertRecord(record);   
  }
   tree.printTree();
   
  auto record_node = tree.searchKey(100);
  if(record_node){ cout<<"\n"<<*record_node<<endl;}
    return 0;
}
