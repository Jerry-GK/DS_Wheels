#include "..\include\Graph\adjList.h"

alGraph::alGraph(int ver_num)
{
    vertex_num=ver_num;
    edge_num=0;
    total_weight=0;
    for(int i=0;i<vertex_num;i++)
    {
        g[i]=(vert*)malloc(sizeof(vert));
        g[i]->index=i;
        g[i]->next=NULL;
        g[i]->weight=0;
        indeg[i]=0;
    }
}

void alGraph:: AddEdge(int i, int j,int w=0)
{
    if(!inRange(i)||!inRange(j))
    {
        cout<<"Error: no such vertex to add and edge!"<<endl;
    }
    vert* new_v=(vert*)malloc(sizeof(vert));
    new_v->index=j;
    new_v->next=g[i]->next;
    new_v->weight=w;
    g[i]->next=new_v;
    
    indeg[j]++;
    edge_num++;
    total_weight+=w;
}
void alGraph::AddDoubleEdge(int i, int j,int w=0)
{
    this->AddEdge(i,j,w);
    this->AddEdge(j,i,w);
    return;
}
void alGraph:: ChangeWeight(int i, int j, int w)
{
    if(!inRange(i)||!inRange(j))
    {
        cout<<"Error: no such vertex to delete an edge!"<<endl;
    }
    vert* temp=g[i];
    while(temp->next!=NULL&&temp->next->index!=j)
    {
        temp=temp->next;
    }
    if(temp->next==NULL)
    {
        cout<<"Error: no such edge to delete!"<<endl;
        return;
    }
    else
    {
        total_weight=total_weight-temp->next->weight+w;
        temp->next->weight=w;
    }
}
int alGraph::GetWeight(int i, int j)
{
    if(!inRange(i)||!inRange(j))
    {
        cout<<"Error: no such vertex to delete an edge!"<<endl;
    }
    vert* temp=g[i];
    while(temp->next!=NULL&&temp->next->index!=j)
    {
        temp=temp->next;
    }
    if(temp->next==NULL)
    {
        return -1;
    }
    else
    {
        return temp->next->weight;
    }
}
void alGraph:: DeleteEdge(int i, int j)
{
    if(!inRange(i)||!inRange(j))
    {
        cout<<"Error: no such vertex to delete an edge!"<<endl;
    }
    vert* temp=g[i];
    while(temp->next!=NULL&&temp->next->index!=j)
    {
        temp=temp->next;
    }
    if(temp->next==NULL)
    {
        cout<<"Error: no such edge to delete!"<<endl;
        return;
    }
    else
    {
        vert* ttemp=temp->next;
        total_weight-=ttemp->weight;
        temp->next=temp->next->next;
        free(ttemp);
        indeg[j]--;
        edge_num--;
    }
    
}
alGraph alGraph::Copy()
{
    alGraph alg(this->vertex_num);
    alg.edge_num=this->edge_num;
    for(int i=0;i<this->vertex_num;i++)
    {
        vert* temp1=this->g[i]->next;
        vert* back=alg.g[i];
        while(temp1!=NULL)
        {
            vert* temp2=new vert;
            temp2->index=temp1->index;
            temp2->weight=temp1->weight;
            temp2->next=NULL;
            back->next=temp2;
            back=temp2;
            temp1=temp1->next;
        }
    }
    return alg;
}
alGraph alGraph::Reverse()
{
    //travel G and Gr at the same time
    alGraph Gr(this->vertex_num);
    Gr.edge_num=this->edge_num;
    for(int i=0;i<this->vertex_num;i++)
    {
        vert* temp1=this->g[i]->next;
        while(temp1!=NULL)
        {
            vert* back=Gr.g[temp1->index];
            vert* temp2=new vert;
            temp2->index=i;
            temp2->weight=temp1->weight;
            temp2->next=back->next;
            back->next=temp2;

            temp1=temp1->next;
        }
    }
    return Gr;
}

int alGraph::GetOutDegree(int i)
{
    if(!inRange(i))
    {
        cout<<"Error: no such a vertex!"<<endl;
        return -1;
    }
    int outdeg=0;
    vert* temp=g[i]->next;
    while(temp!=NULL)
    {
        outdeg++;
        temp=temp->next;
    }
    return outdeg;
}
int alGraph::GetInDegree(int i)
{
    if(!inRange(i))
    {
        cout<<"Error: no such a vertex!"<<endl;
        return -1;
    }
    return indeg[i];
}
void alGraph:: ShowGraph()
{
    cout<<"Here is the graph:"<<endl;
    for(int i=0;i<this->vertex_num;i++)
    {
        bool have=false;
        vert* temp=g[i]->next;
        while(temp!=NULL)
        {
            cout<<"( "<<i<<" -> "<<temp->index<<",w="<<temp->weight<<" ) ";
            have=true;
            temp=temp->next;
        }
        if(have)
            cout<<endl;
    }
}
int alGraph::Dijkstra(int i,int j,vector<int> * retPath=NULL)
{
    int dist[MAX_SIZE];
    bool known[MAX_SIZE];//determin whether a vertex has been select to the konwn set yet
    vector<int> path[MAX_SIZE];//vector path[k] records the shortest path from i to k:path[k][0]->....->path[k][s]
    for(int i=0;i<MAX_SIZE;i++)
    {
        dist[i]=INT_MAX;
        known[i]=false;
    }
    dist[i]=0;//the distance of the starting point is set to 0 initially
    path[i].push_back(i);

    while(1)
    {
        int minDist=INT_MAX,min_index=-1;
        for(int k=0;k<vertex_num;k++)//select the smallest length among the unknown vertices, this can done better by priority queue.
        {//This procedure(find_min) reveals why weighted graphs takes more time than unweighted graphs in shortest path seraching
            if(known[k]==false && minDist>dist[k])
            {
                minDist=dist[k];
                min_index=k;
            }
        }
        //In the first turn the starting vertex will be selected(min_index == i)
        if(min_index==-1)
            break;//all vertices has been selected
            
        known[min_index]=true;
        //cout<<min_index<<endl;

        vert* temp=g[min_index]->next;
        while(temp!=NULL)//update all the distance of vertices adjacent to the new vertex in the set 
        {
            if(known[temp->index]==false && dist[min_index]+temp->weight < dist[temp->index])
            {
                dist[temp->index]=dist[min_index]+temp->weight;

                path[temp->index].assign(path[min_index].begin(),path[min_index].end());
                path[temp->index].push_back(temp->index);
            }
            temp=temp->next;
        }
    }
    
    if(retPath!=NULL)
    {
        if(dist[j]==INT_MAX)
        {
            cout<<"No such a Path!"<<endl;
            return dist[j];
        }
        *retPath=path[j];
    }
    return dist[j];
}
int alGraph::SecLen(int i,int j,vector<int>* retPath=NULL)
{
    vector<int> vp;
    this->Dijkstra(i,j,&vp);
    int SecShortestLen=INT_MAX;

    int vps=vp.size();
    for(int k=0;k<vps;k++)
    {
        int tempWeight=this->GetWeight(vp[k],vp[k+1]);
        this->DeleteEdge(vp[k],vp[k+1]);
        int ShortestAfterDelete=this->Dijkstra(i,j);
        if(SecShortestLen>ShortestAfterDelete)
        {
            SecShortestLen=ShortestAfterDelete;
        }
        this->AddEdge(vp[k],vp[k+1],tempWeight);
    }
    return SecShortestLen;
}
int alGraph::WeaklyConnectedComponents()
{
    djSet djs(vertex_num);
    for(int i=0;i<vertex_num;i++)
    {
        vert* temp=g[i]->next;
        while(temp!=NULL)
        {
            djs.setUnion(i,temp->index);
            temp=temp->next;
        }
    }
    return djs.comp_num();
}
int alGraph::StronglyConnectedComponents()
{
    //Three parts in this special dfs algorithm

    //1.the first dfs to number vertices in postorder of the spanning forest
    int known[MAX_SIZE]={0};
    int Num[MAX_SIZE]={0};
    int counter=0;
    for(int i=0;i<vertex_num;i++)
    {
        if(!known[i])
        {
            known[i]=1;
            DFS_SCC_1(i,known,Num,counter);
        }
    }
    //2.reverse G to Gr
    alGraph Gr=this->Reverse();
    //3.the second dfs for Gr, vertice with big number first
    int NumBig[MAX_SIZE];//Insertion sort: NumBig[i] has the (i+1)th biggest number in Num (0<= i <=vertice_num-1)
    for(int i=0;i<vertex_num;i++)
        NumBig[i]=i;
    for(int i=1;i<vertex_num;i++)
    {
        int newVal=NumBig[i];
        int j;
        for(j=i;j>0&&Num[NumBig[j-1]]<Num[newVal];j--)//Insertion sort
        {
            NumBig[j]=NumBig[j-1];
        }
        NumBig[j]=newVal;
    }

    int comp=0;
    for(int i=0;i<MAX_SIZE;i++)
    {
        known[i]=0;//reset the known set
    }
    for(int i=0;i<vertex_num;i++)//dfs vertice with bigger Num first
    {
        if(!known[NumBig[i]])
        {
            known[NumBig[i]]=1;
            DFS_SCC_2(Gr,NumBig[i],known);
            //cout<<endl;
            comp++;//The end of a big DFS represents the end of traversal for a strongly component
        }
    }
    return comp;
}

void alGraph::DFS_SCC_1(int i,int* known,int* Num, int &counter)
{
    vert* temp=this->g[i]->next;
    while(temp!=NULL)
    {
        if(known[temp->index]==0)
        {
            known[temp->index]=1;
            DFS_SCC_1(temp->index,known,Num,counter);
        }
        temp=temp->next;
    }
    Num[i]=counter++;//number vertices in postorder of the spanning forest
    return;
}
void alGraph::DFS_SCC_2(alGraph& Gr,int i,int* known)
{  
    //add ouput instructions here if you need to ouput each strlongly connected component
    //cout<<i<<" ";
    vert* temp=Gr.g[i]->next;
    while(temp!=NULL)
    {
        if(known[temp->index]==0)
        {
            known[temp->index]=1;
            DFS_SCC_2(Gr,temp->index,known);
        }
        temp=temp->next;
    }
    return;//a dfs that does nothing    
}

int alGraph::ArticulationVertices()
{
    //construct an arbitary spanning tree and build the Num Array. Add back edges at the same time
    const int root=0;//the root of the spanning tree, randomly selected.
    int Num[MAX_SIZE]={0};
    int known[MAX_SIZE]={0};
    int Parent[MAX_SIZE]={0};
    alGraph ST(this->vertex_num);

    known[root]=1;
    Num[root]=0;
    Parent[root]=-1;
    int counter=0;//to number the vertices
    DFS_BCC(root,known,ST,Num,Parent,counter);
    if(ST.edge_num!=this->edge_num)
    {
        cout<<"Error:Not connected!"<<endl;
        return -1;
    }
    //recursively build the Low Array: Low[i] = min{Num[i], Low[j](i->j:tree edge), Num[j](i-->j:back edge)}
    int Low[MAX_SIZE];
    AssignLow(ST,root,Num,Low);

    //analyze the two arrays and return the number of articulation vertices
    bool isArt[MAX_SIZE]={0};
    for(int i=0;i<ST.vertex_num;i++)
    {
        if(i==root)//a root with at least two children is an articulation vertex
        {
            int children=0;
            vert* temp=ST.g[root]->next;
            while(temp!=NULL)
            {
                if(temp->weight==0)//back edge is not concerned
                    children++;
                if(children>=2)
                {
                    isArt[root]=true;
                    break;
                }
                temp=temp->next;
            }
        }
        else if(Low[i]>=Num[Parent[i]]&&Parent[i]!=root)//anaylyze if Parent[i] is an articulation vertex
            isArt[Parent[i]]=true;
    }
    int ArtNum=0;
    for(int i=0;i<ST.vertex_num;i++)
    {
        if(isArt[i])
        {
            ArtNum++;
            cout<<"v["<<i<<"] is an articulation vertex."<<endl;
        }
    }
    if(ArtNum==0)
        cout<<"No articulation vertex."<<endl;
    return ArtNum;
}
int alGraph::AssignLow(alGraph ST,int i,int* Num,int* Low)
{
    //Low[i] = min{Num[i], Low[j](i->j:tree edge), Num[j](i-->j:back edge)}
    int minLow;
    minLow=Num[i];
    vert* temp=ST.g[i]->next;
    while(temp!=NULL)//minLow = min{Num[i], Num[j](i-->j:back edge)}
    {
        if(temp->weight==1&&Num[temp->index]<minLow)
        {
            minLow=Num[temp->index];
        }
        temp=temp->next;
    }

    temp=ST.g[i]->next;
    int minLowChild=INT_MAX;
    while(temp!=NULL)//minLow = Low[i]
    {     
        if(temp->weight==0)
        {
            minLowChild=AssignLow(ST,temp->index,Num,Low);
            if(minLowChild<minLow)
                minLow=minLowChild;
        }
        temp=temp->next;
    }  
    Low[i]=minLow;
    return minLow;
}

void alGraph::DFS_BCC(int i, int* known,alGraph& alg,int* Num,int* Parent, int& counter)
{
    vert* temp=g[i]->next;
    while(temp!=NULL)
    {
        if(known[temp->index]==0)
        {
            known[temp->index]=1;
            alg.AddEdge(i,temp->index);//weight==0, not a back edge
            Num[temp->index]=++counter;  
            Parent[temp->index]=i;
            DFS_BCC(temp->index,known,alg,Num,Parent,counter);
        }
        else
        {
            alg.AddEdge(i,temp->index,1);//weight==1, is a back edge
        }
        temp=temp->next;
    }
    return;
}

bool alGraph::isCyclic()
{   
    int ind[MAX_SIZE];
    for(int i=0;i<vertex_num;i++)
        ind[i]=GetInDegree(i);
    queue<int> q;
    int rest_ver=vertex_num;
    for(int i=0;i<vertex_num;i++)
    {
        if(indeg[i]==0)
            q.push(i);
    }
    while(!q.empty())
    {
        int t=q.front();
        q.pop();
        rest_ver--;
        vert *temp=g[t]->next;
        while(temp!=NULL)
        {
            if(--ind[temp->index] == 0)
                q.push(temp->index);
            temp=temp->next;
        }
    }
    if(rest_ver!=0)
        return true;
    else
        return false;
}
vector<int> alGraph:: TopSort()
{
    vector<int> ret;
    ret.resize(this->vertex_num);
    queue<int> q;
    int retsize=0;
    for(int i=0;i<vertex_num;i++)
    {
        if(indeg[i]==0)
            q.push(i);
    }
    while(!q.empty())
    {
        int t=q.front();
        q.pop();
        ret[retsize]=t;
        retsize++;
        vert *temp=g[t]->next;
        while(temp!=NULL)
        {
            if(--indeg[temp->index] == 0)
                q.push(temp->index);
            temp=temp->next;
        }
    }
    if(retsize!=vertex_num)
        cout<<"Not a DAG! No topological sort."<<endl;
    return ret;
}

PathAndLen alGraph::UnweightedShortestPath(int i, int j)
{
    int dist[MAX_SIZE];
    vector<int> paths[MAX_SIZE];
    for(int i=0;i<vertex_num;i++)
        paths[i].push_back(i);

    for(int k=0;k<vertex_num;k++)
    {
        dist[k]=INT_MAX;
    }
    dist[i]=0;//set dist[k] to INT_MAX except the starting point(set to 0)

    queue<vert*> q;
    q.push(g[i]);
    while(!q.empty())
    {
        vert* v=q.front();
        q.pop();

        vert* temp=v->next;
        while(temp!=NULL)
        {
            if(dist[temp->index]==INT_MAX)
            {
                dist[temp->index]=dist[v->index]+1;
                paths[temp->index]=paths[v->index];
                paths[temp->index].push_back(temp->index);
                q.push(g[temp->index]);//load an adjacent vertex to the konwn set, update its distance
            }
            temp=temp->next;//load every adjacent point(In weighted graph it doesn't work, 
                            //because through a vertex that has not been in the set a shorter path may exist)
        }
    }

    PathAndLen retpl;
    retpl.path=paths[j];
    retpl.len=dist[j];
    return retpl;
}

int alGraph::CriticalLen(int source,int end)
{
    if(this->isCyclic()==true)
    {
        cout<<"Error:Not a DAG. No Critical Path!"<<endl;
        return -1;
    }
    int EC[MAX_SIZE]={0};
    int LC[MAX_SIZE]={0};
    vector<int> topo=this->TopSort();
    int source_ind=0;
    int end_ind=0;
    for(int i=0;i<vertex_num;i++)
    {
        if(topo[i]==source)
            source_ind=i;
        if(topo[i]==end)
            end_ind=i;
    }
    
    for(int i=source_ind+1;i<=end_ind;i++)
    {
        int maxEC=0;
        for(int j=source_ind;j<i;j++)
        {
            int weight=GetWeight(topo[j],topo[i]);
            if(weight!=-1&&maxEC<EC[topo[j]]+weight)
            {
                maxEC=EC[topo[j]]+weight;
            }
        }
        EC[topo[i]]=maxEC;
    }

    LC[topo[end_ind]]=EC[topo[end_ind]];
    for(int i=end_ind-1;i>=0;i--)
    {
        int minLC=INT_MAX;
        for(int j=end_ind;j>i;j--)
        {
            int weight=GetWeight(topo[i],topo[j]);
            if(weight!=-1&&minLC>LC[topo[j]]-weight)
            {
                minLC=LC[topo[j]]-weight;
            }
        }
        LC[topo[i]]=minLC;
    }

    for(int i=source_ind;i<=end_ind;i++)
    {
        cout<<"EC["<<topo[i]<<"] = "<<EC[topo[i]]<<"  LC["<<topo[i]<<"] = "<<LC[topo[i]]<<endl;
    }
    return EC[topo[end_ind]];
}
int alGraph::MaxFlow(int source, int end)
{
    int flowMax=0;
    alGraph residual=this->Copy();//copy the original graph as the residual graph

    PathAndLen flow=residual.UnweightedShortestPath(source,end);
    while(flow.len!=INT_MAX)
    {
        //select a flow path in the residual graph that with the capacity minCap;Can be done better by priority queue.
        int minCap=INT_MAX;
        vector<int> FlowPath=flow.path;
        for(int i=0;i<FlowPath.size()-1;i++)
        {
            int edgeCap=residual.GetWeight(FlowPath[i],FlowPath[i+1]);
            if(minCap>edgeCap)
            {
                minCap=edgeCap;
            }
        }
        if(minCap==INT_MAX)
        {
            cout<<"Error!"<<endl;
            return -1;
        }

        flowMax+=minCap;
        //update the residual graph

        for(int i=0;i<FlowPath.size()-1;i++)
        {
            int original_cap=residual.GetWeight(FlowPath[i],FlowPath[i+1]);
            if(original_cap - minCap <= 0)
                residual.DeleteEdge(FlowPath[i],FlowPath[i+1]);
            else
                residual.ChangeWeight(FlowPath[i],FlowPath[i+1],original_cap-minCap);

            original_cap=residual.GetWeight(FlowPath[i+1],FlowPath[i]);
            if(residual.GetWeight(FlowPath[i+1],FlowPath[i])!=-1)
                residual.ChangeWeight(FlowPath[i+1],FlowPath[i],original_cap+minCap);
            else
                residual.AddEdge(FlowPath[i+1],FlowPath[i],minCap);
        }
        flow=residual.UnweightedShortestPath(source,end);
    }
    return flowMax;
}

int alGraph::Diameter()
{
    if(this->isCyclic()==true)
    {
        cout<<"Error:Not Acyclic!"<<endl;
        return -1;
    }
    int MaxPath[MAX_SIZE];
    int ind[MAX_SIZE];
    for(int i=0;i<vertex_num;i++)
        MaxPath[i]=0;

    for(int i=0;i<vertex_num;i++)
        ind[i]=this->GetInDegree(i);

    for(int i=0;i<vertex_num;i++)
        if(ind[i]==0)
            solve(i,MaxPath,ind);

    int maxD=-1;
    for(int i=0;i<vertex_num;i++)
        if(maxD<MaxPath[i])
            maxD=MaxPath[i];

    return maxD;
}

alGraph alGraph::MST_Prim()
{
    alGraph MST(this->vertex_num);

    int lowCost[MAX_SIZE];//store the minimum cost to load a vertex into the set
    int minSource[MAX_SIZE];//minSource[i] stores the index k of the vertex that makes k->i be lowCost[i].

    bool known[MAX_SIZE];//determin whether a vertex has been select to the konwn set yet
    for(int i=0;i<MAX_SIZE;i++)
    {
        lowCost[i]=INT_MAX;
        minSource[i]=-1;
        known[i]=false;
    }
    lowCost[0]=0;//arbitarily select a strating vertex

    while(1)
    {
        int minCost=INT_MAX,min_index=-1;
        for(int k=0;k<vertex_num;k++)
        {
            if(known[k]==false && minCost>lowCost[k])
            {
                minCost=lowCost[k];
                min_index=k;
            }
        }
        if(min_index<0)
            break;
        
        if(minSource[min_index]>=0)
            MST.AddEdge(minSource[min_index],min_index,this->GetWeight(minSource[min_index],min_index));

        known[min_index]=true;

        vert* temp=g[min_index]->next;
        while(temp!=NULL)//update all the lowcost of vertices adjacent to the new vertex in the set 
        {
            if(known[temp->index]==false && temp->weight < lowCost[temp->index])//the only differece from Dijstra
            {
                lowCost[temp->index]=temp->weight;
                minSource[temp->index]=min_index;
            }
            temp=temp->next;
        }
    }

    if(MST.edge_num!=this->vertex_num-1)
    {
        cout<<"No Spanning Tree!"<<endl;
        MST=alGraph(0);
    }
    return MST;
}
alGraph alGraph::MST_Kruskal()
{
    alGraph graCopy=this->Copy();
    alGraph MST(this->vertex_num);
    djSet vertSet(this->vertex_num);//connected vertices are in the same set

    while(1)
    {
        int minCost=INT_MAX;
        int v=-1,w=-1;
        for(int i=0;i<graCopy.vertex_num;i++)//select the shortest edge. It can be done faster by priortiy queue.
        {
            vert* temp=graCopy.g[i]->next;
            while(temp!=NULL)
            {
                if(temp->weight<minCost)
                {
                    minCost=temp->weight;
                    v=i;
                    w=temp->index;
                }
                temp=temp->next;
            }
        }

        graCopy.DeleteEdge(v,w);
        if(vertSet.find(v)!=vertSet.find(w))//this means selecting (v,w) won't produce a circle 
        {
            vertSet.setUnion(v,w);//(v,w) are connected
            MST.AddEdge(v,w,minCost);//add v<->w into the MST
        }
        if(graCopy.edge_num==0)
        {
            break;
        }
    }
    
    if(MST.edge_num!=this->vertex_num-1)
    {
        cout<<"No Spanning Tree!"<<endl;
        MST=alGraph(0);
    }
    return MST;
}

bool alGraph::EulerCircuit(int start)
{
    alGraph Gc=this->Copy();
    cout<<"Euler Circuit(component):";
    int TravelEdges=-1;
    DFS_EC(Gc,start,TravelEdges);

    return TravelEdges==Gc.edge_num;
} 
void alGraph::DFS_EC(alGraph& G,int start,int& TravelEdges)
{
    cout<<start<<" ";
    TravelEdges++;
    vert* temp=G.g[start]->next;
    while(temp!=NULL)
    {
        if(temp->weight!=-1)
        {
            temp->weight=-1;
            DFS_EC(G,temp->index,TravelEdges);
            break;//break here makes Euler dfs. Without break, it will be a spanning tree dfs.
        }
        temp=temp->next;
    }
}


bool alGraph::inRange(int i)
{
    return i>=0&&i<vertex_num;
}
void alGraph::solve(int id,int MaxPath[MAX_SIZE],int ind[MAX_SIZE])
{
    vert* temp=g[id]->next;
    if(temp==NULL)
    {
        return;
    }
    while(temp!=NULL)
    {
        MaxPath[temp->index]=max(MaxPath[temp->index],MaxPath[id]+temp->weight);
        if(--ind[temp->index]==0)
        {
            solve(temp->index,MaxPath,ind);
        }
        temp=temp->next;
    }
}

int alGraph::max(int a, int b)
{
    return a>b?a:b;
}

void alGraph::DFS_TEST(int start)
{
    //cout<<start<<" ";//preoder
    alGraph Gc=this->Copy();
    vert* temp=Gc.g[start]->next;
    while(temp!=NULL)
    {
        if(temp->weight!=-1)
        {
            temp->weight=-1;
            //cout<<start<<" ";
            DFS_TEST(temp->index);
            //cout<<start<<" ";
        }
        temp=temp->next;
    }
    cout<<start<<" ";//postorder
    return;
}
