#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<stack>
#include<list>
#include<map>

using namespace std;

const int INF = 1000000000;


class Graph{
private:
    struct Trans{
        int id;
        int dst;
        int trafspace;
        int currDistance;
        int status;                 // 1 = order, 2 = drop, 3 = complete    (sudah ada permintaan)
        int finishstatus;           // 1 = order, 2 = drop, 3 = complete    (fakta yg terjadi)
        int targetcust;
        vector<int> ruteygdiambil;
    };
    struct Edge{
        int to;
        int distance;
        int traficSpace;
        int currTraficSpace;
    };
    struct Node{
        int driverNumber; //jumlah driver
        bool visit;
        int distance;
    };
    int jnode;
    vector<vector<Edge>> edges;
    vector<Node> nodes;
    vector<Trans> trans;
public:

    class Compare {
        public:
            bool operator()(pair<int, int> below, pair<int, int> above)
            {
                if (below.first > above.first) {
                    return true;
                }
                else if (below.first == above.first
                            && below.second > above.second) {
                    return true;
                }

                return false;
            }
    };

    Graph(int jnode)
    {
        this->jnode = jnode;
        this->edges.resize(105);
        this->nodes.resize(105);
        for(int i = 0; i <= jnode; i++) {
            edges[i].resize(105);
        }
    }
    void addEdge(int from, int to, int distance, int trafspace){
        Edge newEdge            = {to, distance, trafspace, trafspace};
        this->edges[from][to]   = newEdge;
        Edge newEdgeRev         = {from, distance, trafspace, trafspace};
        this->edges[to][from]   = newEdgeRev;
    }
                                // node awal
    int dijkstra(int idtrans, int start, int target, int ts, vector<int> &parent){
        vector<int>     dist(105, INF);       // array bobot
        vector<bool>    visited(105, false);  // array visited
        dist[start]     = 0;                        // posisi start diberi bobot 0
        parent[start]   = 0;                        // titik keberangkatan tidak memiliki parent

        /*
        priority_queue<PII,
                        vector<PII>, Compare> ds;
        priority_queue<pair<int, int>,
                        vector<pair<int, int>>,
                        greater<pair<int, int>>> pq;
        */
        priority_queue<pair<int, int>,
                        vector<pair<int, int>>,
                        Compare> pq;
        pq.push({0, start});

        int found   = 0;
        while(!pq.empty()){
            int u   = pq.top().second;
            pq.pop();

            //cout << "cek = " << u << endl;

            if(visited[u]) continue; else { visited[u] = true; }

            if(u == target) {
                found = 1;
                break;
            }
            else {
                for (int i = 0; i < edges[u].size(); i++){
                    if(edges[u][i].traficSpace >= ts) {
                        int v = edges[u][i].to;
                        int w = edges[u][i].distance;

                        if(!visited[v]) {
                            if (dist[u] + w < dist[v]){     // ganti bobot @ verteks
                                parent[v]   = u;
                                dist[v]     = dist[u] + w;
                                pq.push({dist[v], v});
                            }
                        }
                    }
                }
            }
        }

        if(found == 1) {
            return dist[target];
        }
        else {
            return -1;
        }
    }

    void updateTraffic(int startPoint, vector<int> rute, int addOn) {               // update traffic
        int k = startPoint;
        while(k != 0) {
            int m = rute[k];
            edges[k][m].traficSpace+=addOn;
            if(m != 0) {
                edges[m][k].traficSpace+=addOn;
            }
            k = m;
        }
    }

    int anotherDijkstra(int idtrans, int start, int ts, int *maxdist, vector<int> &parent){
        vector<int>     dist(105, INF);       // array bobot
        vector<bool>    visited(105, false);  // array visited
        dist[start]     = 0;                        // posisi start diberi bobot 0
        parent[start]   = 0;                        // titik keberangkatan tidak memiliki parent

        priority_queue<pair<int, int>,
                        vector<pair<int, int>>,
                        Compare> pq;
        pq.push({0, start});

        int found   = -1;
        //int maxdist = 0;
        while(!pq.empty()){
            int u   = pq.top().second;
            pq.pop();

            //cout << "cek = " << u << endl;

            if(visited[u]) continue; else {
                if(nodes[u].driverNumber > 0) {
                    if(found == -1) {
                        found = u;
                        *maxdist = dist[u];
                    }
                    else if(dist[u] < *maxdist) {
                        found = u;
                        *maxdist = dist[u];
                    }
                }
                visited[u] = true;
            }

            if(nodes[u].driverNumber == 0) {
                for (int i = 0; i < edges[u].size(); i++){
                    if(edges[u][i].traficSpace >= ts) {
                        int v = edges[u][i].to;
                        int w = edges[u][i].distance;

                        if(!visited[v]) {
                            if (dist[u] + w < dist[v]){     // ganti bobot @ verteks
                                //cout << "tree = " << dist[u] + w << " from " << i << endl;
                                parent[v]   = u;
                                dist[v]     = dist[u] + w;

                                if(nodes[v].driverNumber > 0) {
                                    if(found == -1) {
                                        found = v;
                                        *maxdist = dist[v];
                                    }
                                    else if(dist[v] < *maxdist) {
                                        found = v;
                                        *maxdist = dist[v];
                                    }
                                    visited[u] = true;
                                } else { pq.push({dist[v], v}); }
                            }
                        }
                    }
                }
            }
        }

        //cout << "result = " << found << " , " << maxdist << "\n";
        return found;

        /*
        if(found!= -1) {
            return -1; //dist[target];
        }
        else {
            return found;
        }
        */
    }

    void order(int ID, int dst, int ts){
        vector<int> ruteygdiambil(105, -1);
        int minindex    = -1;
        int mindistance = INF;

        vector<int> parent(105, -1);      // array parent
        minindex = anotherDijkstra(ID, dst, ts, &mindistance, parent);
        ruteygdiambil   = parent;

        // bagian ini diganti dulu
        /*
        for (int i = 1; i < nodes.size(); i++){
            if(nodes[i].driverNumber > 0) {
                vector<int> parent(jnode + 1, -1);      // array parent
                int result = dijkstra(ID, i, dst, ts, parent);
                if(result != -1 && result < mindistance) {
                    ruteygdiambil   = parent;
                    mindistance     = result;
                    minindex        = i;
                }
            }
        }
        */

        if(minindex == -1) {
            cout << "Just walk. T-T\n";
        }
        else {
            cout << "Order " << ID << " from: " << minindex << "\n";

            updateTraffic(dst, ruteygdiambil, -ts);
            nodes[minindex].driverNumber-=1;
            addTrans(ID, dst, ts, mindistance, ruteygdiambil);
        }
    }

    void drop(int IDTrans, int dst){
        for(int i = 0; i < trans.size(); i++) {
            if(trans[i].id == IDTrans) {
                trans[i].targetcust     = dst;
                trans[i].status         = 2;
                int src                 = trans[i].dst;
                int ts                  = trans[i].trafspace;
                vector<int> rutelama    = trans[i].ruteygdiambil;

                updateTraffic(trans[i].dst, rutelama, ts);

                vector<int> parent(105, -1);      // array parent
                int result = dijkstra(IDTrans, src, dst, ts, parent);
                if(result != -1) {
                    cout << "Order " << IDTrans << " distance: "
                            << (result + trans[i].currDistance) << "\n";

                    updateTraffic(dst, parent, -ts);

                    trans[i].dst            = dst;
                    trans[i].ruteygdiambil  = parent;
                    trans[i].finishstatus   = 2;
                }
                else {
                    cout << "No Way Home\n";
                }
            }
        }
    }

    void complete(int IDTrans){
        for(int i = 0; i < trans.size(); i++) {
            if(trans[i].id == IDTrans) {
                vector<int> rutelama            = trans[i].ruteygdiambil;
                int ts                          = trans[i].trafspace;

                updateTraffic(trans[i].dst, rutelama, ts);

                trans[i].status                 = 3;
                trans[i].finishstatus           = 3;
                nodes[trans[i].dst].driverNumber+=1;
            }
        }

        // check transaction before
        for(int i = 0; i < trans.size(); i++) {
            if(trans[i].status == 2 && trans[i].finishstatus == 1) {
                drop(trans[i].id, trans[i].targetcust);
            }
        }
    }

    void placeDriver(int v, int jdriver){
        nodes[v].driverNumber = jdriver;
    }

    void addTrans(int id, int dst, int ts, int currdis, vector<int> rutediambil){
        Trans t = {id, dst, ts, currdis, 1, 1, -1, rutediambil};
        trans.push_back(t);
    }

    void cetakEdge()
    {
        for (int i=0; i<edges.size(); i++){
            //cout<<"Dari Node : "<<i<<endl;
            for (int j =0; j<edges[i].size(); j++){
                cout<<"  [to="<<edges[i][j].to<<"]-[dist="<<edges[i][j].distance<<"]-[tf="<<edges[i][j].traficSpace<<"]"<<endl;
            }
        }
    }

    void cetakNodes()
    {
        for (int i=0; i<nodes.size(); i++){
            cout<<"Nodes ke "<<i<<endl;
            cout<<"Jumlah Driver : "<<nodes[i].driverNumber<<endl;
            cout<<"Distance : "<<nodes[i].distance<<endl;
            cout<<"Visited  : "<<nodes[i].visit<<endl;
            cout<<".............."<<endl;
        }
    }
    void cetakTransaksi()
    {
        for (int i=0; i<trans.size(); i++){
            cout<<"> Trans ID : "<<trans[i].id<<endl;
            cout<<"> Dest     : "<<trans[i].dst<<endl;
            cout<<"> TS       : "<<trans[i].trafspace<<endl;
            cout<<".............."<<endl;
        }
    }
};

int main()
{
    int jnode, jedge, jplace;
    cin >>  jnode >> jedge >> jplace;
    Graph g(105);
    string cmd;
    int v,c;
    for (int i=0; i<jplace; i++)
    {
        cin>>cmd>>v>>c;
        g.placeDriver(v,c);
    }
    //g.cetakNodes();
    int s,d,dis,t;
    for (int i=0; i<jedge; i++)
    {
        cin>>cmd>>s>>d>>dis>>t;
        g.addEdge(s,d,dis,t);
    }
    //g.cetakEdge();
    getline(cin, cmd);
    int ncmd;

    cin>>ncmd;

    //cout << "ncmd = " << ncmd << "\n";

    int ID,src,ts,dst;
    for (int i=0; i<ncmd; i++){
        cin>>cmd;
        //cout << "command = " << cmd << "\n";
        if (cmd == "Order"){
            cin>>ID>>src>>ts;
            g.order(ID,src,ts);
        }else if (cmd=="Drop"){
            cin>>ID>>dst;
            g.drop(ID, dst);
        }else if (cmd=="Complete"){
            cin>>ID;
            g.complete(ID);
        }
    }
}
