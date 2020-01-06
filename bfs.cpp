#include <bits/stdc++.h>
#include <GL/glut.h>
#include <unistd.h>
using namespace std;

//fontstyle??
GLvoid *font_style = GLUT_BITMAP_HELVETICA_18;

int nodes,edges,vt=0;
vector<int> visited;
vector<pair<int,int> > cds;
vector<vector<int> > graph;
unordered_map<string,int> col;
int nodep=0;

void display();
void mouse(int,int,int,int);
void reshape(int,int);
void drawstr(GLuint x, GLuint y, const char* format, int length){
    glRasterPos2i(x, y);  
    for(int i=0; i<length; ++i)
    {
        glutBitmapCharacter(font_style, *(format+i) );
    }
}

/*
void dfs(int s){
	visited[s]=1;
	display();
	usleep(1000000);
	cout<<s<<endl;
	for(int i=0;i<graph[s].size();i++){
		if(!visited[graph[s][i]]){
			col[to_string(s)+to_string(graph[s][i])]=1;
		    col[to_string(graph[s][i])+to_string(s)]=1;
			dfs(graph[s][i]);
			col[to_string(s)+to_string(graph[s][i])]=0;
		    col[to_string(graph[s][i])+to_string(s)]=0;
		}
	}
	visited[s]=-1;
	display();
	usleep(1000000);
}
*/

queue<int> q;
void bfs(int s){
    q.push(s);
    visited[s]=1;
    display();
    usleep(2000000);
    while(!q.empty()){
    	int f = q.front();
    	for(int i=0;i<graph[f].size();i++){
    		if(!visited[graph[f][i]]){
    			q.push(graph[f][i]);
    			visited[graph[f][i]]=1;
    			col[to_string(f)+to_string(graph[f][i])]=1;
		        col[to_string(graph[f][i])+to_string(f)]=1;
    			display();
                usleep(2000000);
    		}
    	}
    	visited[f]=-1;
    	display();
        usleep(2000000);
    	q.pop();
    }
}


void reshape(int w,int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,500,0);
	glMatrixMode(GL_MODELVIEW);
}

void display(){
	glEnable(GL_DEPTH_TEST);
	glClearColor(1,1,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    glPointSize(30);
    string tmp;
    for(int i=0;i<cds.size();i++){
    	glColor3f(1,1,1);
        drawstr(cds[i].first-5,cds[i].second+5,to_string(i).c_str(),1);
    	glBegin(GL_POINTS);
    	if(visited[i]==0)
    	    glColor3f(1.0,0.0,0.0);
    	if(visited[i]==1)
    		glColor3f(0.0,1.0,0.0);
    	if(visited[i]==-1)
    		glColor3f(0.0,0.0,1.0);
    	glVertex2f(cds[i].first,cds[i].second);
    	glEnd();
    }
   
    if(nodep){
    glLineWidth(5);
    glBegin(GL_LINES);
    for(int i=0;i<nodes;i++){
    	for(int j=0;j<graph[i].size();j++){
    		int c = (col[to_string(i)+to_string(graph[i][j])])?1:0;
    		glColor3f(c,c,c);
    		glVertex2f(cds[i].first,cds[i].second);
    		glVertex2f(cds[graph[i][j]].first,cds[graph[i][j]].second);
    	}
    }
    glEnd();
    }
    glColor3f(0,0,0);
    tmp = "BREADTH FIRST SEARCH";
    drawstr(150,400,tmp.c_str(),tmp.length());
    tmp = "RED : Node that's never been processed";
    drawstr(100,420,tmp.c_str(),tmp.length());
    tmp = "GREEN : Node which's just been processed";
    drawstr(100,440,tmp.c_str(),tmp.length());
    tmp = "BLUE : Node who's Children are visited";
    drawstr(100,460,tmp.c_str(),tmp.length());
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)  {  
    if(vt<nodes)
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)   
        { 
            cds.push_back(make_pair(x,y));
            cout<<x<<'\t'<<y<<'\n';
            vt++;
            if(vt==nodes)nodep=1;
            display();
            //usleep(600000);
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)   
    {
        cout<<"\nRunning BFS\n";
        for(int i=0;i<nodes;i++)
        {
            if(visited[i]==0)
            {
                //usleep(600000);
                bfs(i);
            }
        }
    }
}

int main(int argc,char** argv){
	cout<<"Enter Number of Nodes:"<<endl;
	cin>>nodes;
	cout<<"Enter Number of Edges:"<<endl;
	cin>>edges;
	graph.resize(nodes);
	visited.resize(nodes,0);
	//cds.resize(nodes);
	cout<<"Enter Edges(node x,node y): "<<endl;
	for(int i=0;i<edges;i++){
		int a,b;
		cin>>a>>b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Breadth First Search");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}