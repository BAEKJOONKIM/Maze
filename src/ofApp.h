#pragma once

#include "ofMain.h"

#define MAX_NODE 5000
#define MAX_ROW 100
#define MAX_COL 100
#define LINE_LENGTH 30

typedef struct _point {
	int x;
	int y;
}Point;

class Node {
public:

	Node* right;
	Node* left;
	Node* up;
	Node* down;
	Node* parent;

	int x,y;//x는 행, y는 열
	Node() {
		this->x = 0;
		this->y = 0;
		this->right = NULL; this->left = NULL; this->up = NULL; this->down = NULL;
		this->parent = NULL;
	}
	Node(int px, int py) {
		this->x = px;
		this->y = py;
		this->right = NULL; this->left = NULL; this->up = NULL; this->down = NULL;
		this->parent = NULL;
	}
	void setRight(Node* n) {this->right = n;}
	Node* getRight(){ return this->right; }
	void setLeft(Node* n) {this->left = n;}
	Node* getLeft() { return this->left; }
	void setUp(Node* n) { this->up = n; }
	Node* getUp() { return this->up; }
	void setDown(Node* n) { this->down = n; }
	Node* getDown() { return this->down; }
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void processOpenFileSelection(ofFileDialogResult openFileResult);
		void makeTree(Node* node);

		void dfs(Node* node);
		void bfs(Node* node);
		Node* unvisited(Node* node);

		int load_flag;
		int dfs_flag;
		int bfs_flag;

		int m, n;
		
		//int edge[MAX_NODE][MAX_NODE];
		int hbar[MAX_ROW][MAX_COL];
		int vbar[MAX_ROW][MAX_COL];
		int visited[MAX_ROW][MAX_COL];

		vector<Node*> list;
		queue<Node*> queue;
		vector<Point> points;

		Node* root = new Node();
		Node* qN;


};
