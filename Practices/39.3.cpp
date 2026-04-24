#include <iostream>
#include <string>
#include <memory>
#include<vector>
#include<map>
using namespace std;

struct Node {
 char data;
 shared_ptr<Node> left;
 shared_ptr<Node> right;

 Node(char d) : data(d), left(nullptr), right(nullptr) {}
 Node() : data('\0'), left(nullptr), right(nullptr) {}
};

shared_ptr<Node> rebuildHuffmanTree(const string& s, int& index) {
 if (index >= s.length()) return nullptr;

 if (s[index] == '1') {
     index++; // 跳过'1'
     char ch = s[index++]; // 读取字符
     return make_shared<Node>(ch);
 } else if (s[index] == '0') {
     index++; // 跳过'0'
     auto node = make_shared<Node>();
     node->left = rebuildHuffmanTree(s, index);
     node->right = rebuildHuffmanTree(s, index);
     return node;
 }
 return nullptr;
}

// 辅助函数：打印树结构（前序遍历）
void printTree(const shared_ptr<Node>& root, string prefix = "") {
 if (!root) return;

 if (root->data != '\0') {
     cout << prefix << "Leaf: " << root->data << endl;
 } else {
     cout << prefix << "Internal Node" << endl;
 }
 printTree(root->left, prefix + "  ");
 printTree(root->right, prefix + "  ");
}

map<int,pair<string,string>>stat;
map<string,string>mall;
int main(){
   int S,D;
   cin>>S>>D;
   for(int i=0;i<S;i++){
    string a,b;
    cin>>a>>b;
    stat[i+1]={a,b};

   }
   string s;
   cin>>s;
   int N;
   cin>>N;
   int cur=S+1;
   for(int t=0;t<N;t++){
    int a;
    cin>>a;
    if(a==1){
      int i;
      cin>>i;
    if(i<=S){
        string value_print=stat[i].second;
        if(value_print[0]=='H'&&value_print[1]=='H')value_print=value_print.substr(1);
     cout<<stat[i].first<<":"<<value_print<<endl;
    }else{
    string value_print=mall[i].second;
        if(value_print[0]=='H'&&value_print[1]=='H')value_print=value_print.substr(1);
         
 cout<<mall[i].first<<":"<<value_print<<endl;
    
    }
    }
    if(a==2){
   int i;
   cin>>i;
   if(i==0){
   int k,v;
   cin>>k>>v;

   }
   else{
    string key;
    i<=S?(key=stat[i].first):(key=mall[i].first);
   int v;
   cin>>v;
   }
    }
    if(a==3){

    }

   }
}
