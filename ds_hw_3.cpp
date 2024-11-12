#include <iostream>
#include <vector>
#include <stack>
//#include <algorithm>
//#define INT_MIN

using namespace std;

struct Node{
    int parent;
    int distance;
    vector<int> children;
};

vector<Node> tree;

void printTree(int node, int level){
    cout<<"--------------------"<<endl;
    cout<<string(level*2,' ')<<node;
    cout<<"(" << tree[node].distance;
    cout<<"-"<<tree[node].parent<<")"<<endl;
    for (int ch: tree[node].children){
        printTree(ch, level+1);
    }
}

void printVector(){
    for (long long unsigned int i=0; i<tree.size(); i++){
        cout<<"v p-d-csize -> "<<i<<" - "<<tree[i].parent<<"-"<<tree[i].distance<<"-"<<tree[i].children.size()<<endl;
        for (long long unsigned int  j=0; j<tree[i].children.size(); j++){
            cout<<tree[i].children[j]<<" ";
        }
        cout<<endl;
    }
}

/*
void checkByDfs(int root)
{
    stack<int> stNode;
    stack<int> stDistance;
    vector<bool> v(tree.size(), false);
    int maxi = 0;
    int maxiNode = root;
    int finalNode = root;
    stNode.push(root);
    stDistance.push(0);

    while(!stNode.empty()){
        int node = stNode.top();     stNode.pop();
        int dist = stDistance.top(); stDistance.pop();
        if (dist > maxi){
            maxi = dist;
            maxiNode = node;
        }
        v[node] = true;
        for (int i=0; i<tree[node].children.size(); i++){
            int ch = tree[node].children[i];
            if (v[ch] == false){
                stNode.push(ch);
                stDistance.push(dist+tree[ch].distance);
            }
        }
        cout<<"Maximum Value: "<<maxi<<endl;
        cout<<"Root of the Path: "<<maxiNode<<endl;
        cout<<"Final Root: "<<finalNode<<endl;
    }
}

*/

void dfs(int node, int dist,
         int &maxi, int &maxiNode,
         vector<bool> &visited,
         vector<int> &path, vector<int> &maxPath) {
    visited[node] = true;
    path.push_back(node);
    //cout<<"hasil path "<< path.size()<<endl;
    if (dist > maxi) {
        maxi = dist;
        maxiNode = path[0]; // Simpan node awal jalur
        maxPath = path;
    }
    for (long long unsigned int  i = 0; i < tree[node].children.size(); i++) {
        int ch = tree[node].children[i];
        if (!visited[ch]) {
            dfs(ch, dist + tree[ch].distance, maxi, maxiNode, visited, path, maxPath);
        }
    }
    path.pop_back(); //kembali ke node sebelumnya
}

void checkByDfs() {
    vector<bool> visited(tree.size(), false);
    vector<int> path, maxPath;
    int totalMaxi = -2147483647; // kemungkinan nilai terkecil
    int totalMaxiNode = -1; // Simpan node awal jalur maksimum
    for (long long unsigned int  i = 0; i < tree.size(); i++) { //setiap kemungkinan start awal node
        int maxi = -2147483647;
        int maxiNode = -1;
        dfs(i, //start awal node
            tree[i].distance, //value node start
            maxi, //nilai maksimum didapat
            maxiNode, //node terakhir maksimum
            visited, //pertama false semua, kalau sudah diproses jadi true
            path,
            maxPath);
        if (maxi > totalMaxi) {
            totalMaxi = maxi;
            totalMaxiNode = maxiNode;
        }
        visited.assign(tree.size(), false); // semua difalsekan balik
        path.clear(); //start baru lagi untuk starting node berikutnya
    }
    cout << "Maximum Value: " << totalMaxi << endl;
    cout << "Root of the Path: " << totalMaxiNode << endl;
    cout << "Final Root: "<<maxPath[0]<<endl;
}

int main()
{
    int n, cmd, root, dist;
    long long unsigned int pr, ch;
    cin>>n>>cmd;
    tree.resize(n+1);

    cin>>root>>dist;
    tree[root].parent = -1;
    tree[root].distance = dist;
    for (int i=0; i<n; i++){
        cin>>pr>>ch>>dist;
        if (tree.size() <= ch){
            tree.resize(ch + 1);
        }
        if (tree.size() <= pr){
            tree.resize(pr + 1);
        }
        tree[ch].parent = pr;
        tree[ch].distance = dist;
        tree[pr].children.push_back(ch);
    }
    //printTree(root,0);
    string cmdstr;
    int param;
    //cout<<"Jumlah Perintah : " <<cmd<<endl;
    for (int i=0; i<cmd; i++){
        cin>>cmdstr;
        if (cmdstr == "Add"){
            cin>>pr>>ch>>dist;
            if (tree.size() <= ch){
                tree.resize(ch + 1);
                //cout<<"anda memasukkan "<<pr<<"-"<<ch<<"-"<<dist<<endl;
            }
            tree[ch].parent = pr;
            tree[ch].distance = dist;
            tree[pr].children.push_back(ch);
        }
        else if (cmdstr == "Delete"){
            cin>>param;
            if (param>=0){
                int ortu = tree[param].parent;
                for (long long unsigned int  i=0; i<tree[param].children.size(); i++){
                    tree[tree[param].children[i]].parent = ortu;
                    tree[ortu].children.push_back(tree[param].children[i]);
                }
                //for (int i=tree[ortu].children.size()-1; i>=0; i--){
                for (long long unsigned int  i=0; i<tree[ortu].children.size(); i++){
                    if (tree[ortu].children[i]==param){
                        tree[ortu].children.erase(tree[ortu].children.begin() + i);
                        break;
                    }
                }
            }
            //printVector();
        }
        else if (cmdstr == "Check"){
            checkByDfs();
        }
    }
    //printTree(root,0);
    return 0;
}

/*

0 6
0 30
Add 0 1 10
Add 0 2 20
Add 1 3 50
Add 2 4 60
Delete 2
Delete 3

2 2
0 100
0 2 1
0 3 3
Delete 2
Delete 3



4 3
0 30
0 1 7
2 3 2
2 4 13
0 2 19
Check
Add 0 5 10
Delete 2

7 3
0 -30
0 1 7
2 3 2
2 4 13
0 2 19
2 5 50
5 6 10
6 7 20
Check
Add 5 8 10
Delete 2


7 1
0 -30
0 1 7
2 3 2
2 4 13
0 2 19
2 5 50
5 6 10
6 7 20
Delete 2


4 1
0 -30
0 1 7
2 3 2
2 4 13
0 2 19
Delete 2


4 1
0 -30
0 1 7
2 3 2
2 4 13
0 2 19
Add 0 5 10

*/