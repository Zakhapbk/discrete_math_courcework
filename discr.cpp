#include<bits/stdc++.h>
#include<gtk/gtk.h>
#define PICT_NAME "g.jpg"
using namespace std;
 
int a,b,i,j;
vector<vector<pair<int,int> > > graph;
typedef vector <pair<int,int>> lest;
vector<int> color;
bool vis[100000];
char name[16][9]={"red","blue","yellow","green","black","white","pink","orange",
                "brown","purple","gold","grey","bronze","darkred","coral"} ;

void colour(int node)
{
	queue<int> q;
	int c=0;
	set<int> already_colored;
	if(vis[node])
		return;
	vis[node]=1;
 
	for(i=0;i<graph[node].size();i++)
	{
		if(color[graph[node][i].second]!=-1)
		{
			already_colored.insert(color[graph[node][i].second]);
		}
	}
	
 
	for(i=0;i<graph[node].size();i++)
	{
		if(!vis[graph[node][i].first])
		{
			q.push(graph[node][i].first);
		}
		if(color[graph[node][i].second]==-1)
		{
			while(already_colored.find(c)!=already_colored.end())
			c++;
			color[graph[node][i].second]=c;
			already_colored.insert(c);
			c++;
		}
	}
	while(!q.empty())
	{
		int tmp=q.front();
		q.pop();
		colour(tmp);
	}
	
	return;
}

void write(int a,int b,const char * fname, const lest &lst ){
ofstream out(fname);
    out << "graph n {\n";
    for (int i = 1; i < a+1; ++i) {
        out << "  " << i << ";\n";
    }
for (int i = 0; i < b; i++){
out << "  " << lst[i].first + 1 << " -- " << " " << lst[i].second + 1<< " " <<"[color="<< name[color[i]] << "]"<< ";\n";
}
out << "}\n";
}
 
int main(int argc, char ** argv)
{
	int x,y;
	set<int> empty;
	lest lst;
	cout<<"Введите количество вершин и рёбер =>";
	cin>>a>>b;
	cout<<"\n";
	lst.resize(b);
	graph.resize(a); //  Number of Vertices.
	color.resize(b,-1); // Number of Edges.
     for(int i = 0; i < sizeof(vis); i++){
         vis[i] = 0;
     }
	for(i = 0; i < b; i++)
	{
		cout<<"\n Как связаны вершины?  "<<i+1<<" :";
		cin>>x>>y;
		x--; y--;
		graph[x].push_back(make_pair(y,i));
		graph[y].push_back(make_pair(x,i));
                lst[i] = make_pair(x,y);

	}
	cout<<"\n";
	colour(0);
	int rnd = 1;
	for(int node = 0; node < a;node++ ){
	for(i=0;i<graph[node].size()-1;i++){
	    if((color[graph[node][i].second]!=-1)&&(color[graph[node][i].second] == color[graph[node][i+1].second])){
	        color[graph[node][i+1].second]=color[graph[node][i].second]+rnd;
	       
	    }
	     rnd++;
	}

	}
	int cr = 0;
	for (int i = 0; i < a; i++){
	    if (graph[i].size() > cr) cr = graph[i].size();
	}
	int max = 0;
    write(a,b,"g.dot", lst);
   system("dot g.dot -Tpng -og.jpg");
  
	for(i = 0;i < b; i++)
	{ 
	if(color[i] >= max ) max = color[i];
		cout<<"Ребро "<<i+1<<" имеет цвет "<<name[color[i]]<<"\n";
	}
	cout << "Граф окрашен в " << max+1  << " цветов " <<"\n";
	cout << "Максимальная степень графа = " << cr <<"\n";
   GtkWidget * win;
    GtkWidget * img;
    
    gtk_init(&argc, &argv);
    
    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    img = gtk_image_new_from_file(PICT_NAME);
    gtk_window_set_title(GTK_WINDOW(win), PICT_NAME);
    gtk_window_set_default_size(GTK_WINDOW(win), 560, 539);
    gtk_container_add(GTK_CONTAINER(win), img);
    
    gtk_widget_show_all(win);
    
    g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_main();
    
    return 0;
    
	
}

