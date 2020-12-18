#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(255, 255, 255);
	load_flag = 0;
	dfs_flag = 0;
	bfs_flag = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	Node* temp;
	int i, j, p,q;
	int startX, endX, startY, endY;
	ofSetColor(0);
	if (load_flag == 1) {
		startX = 10;
		startY = 10;
		for (i = 0; i < m + 1; i++) {
			for (j = 0; j < n + 1; j++) {
				if (hbar[i][j] == 1) {
					endX = startX + LINE_LENGTH;
					endY = startY;
					ofDrawLine(startX, startY, endX, endY);
				}
				if (vbar[i][j] == 1) {
					endX = startX;
					endY = startY + LINE_LENGTH;
					ofDrawLine(startX, startY, endX, endY);
				}
				startX += LINE_LENGTH;
			}
			startY += LINE_LENGTH;
			startX = 10;
		}
	}

	if (dfs_flag == 1) {
		ofSetColor(255, 0, 0);
		//x, y 가 행, 열 순이므로 선을 그릴때 바꿔서 입력
		for (i = 0; i < points.size()-1; i++) {
			int x1, x2, y1, y2;
			x1 = points.at(i).x*LINE_LENGTH+24;
			x2 = points.at(i + 1).x*LINE_LENGTH + 24;
			y1 = points.at(i).y*LINE_LENGTH + 24;
			y2 = points.at(i + 1).y*LINE_LENGTH + 24;
			ofDrawLine(y1,x1,y2,x2);
		}
		ofSetColor(0, 0, 255);
		for (i = 0; i < list.size() - 1; i++) {
			int x1, x2, y1, y2;
			x1 = (list.at(i)->x)*LINE_LENGTH + 24;
			x2 = (list.at(i+1)->x)*LINE_LENGTH + 24;
			y1 = (list.at(i)->y)*LINE_LENGTH + 24;
			y2 = (list.at(i+1)->y)*LINE_LENGTH + 24;
			ofDrawLine(y1, x1, y2, x2);
		}
	}

	if (bfs_flag == 1) {
		ofSetColor(255, 0, 0);
		for (i = 0; i < points.size(); i++) {
			
			int x1, x2, y1, y2,tx,ty;
			Point tp = points.at(i);
			tx = tp.x;
			ty = tp.y;
			x1 = tx * LINE_LENGTH + 24;
			y1 = ty * LINE_LENGTH + 24;
			if (vbar[tx][ty] == 0 && visited[tx][ty-1]) {
				x2 = (tx)*LINE_LENGTH + 24;
				y2 = (ty - 1)*LINE_LENGTH + 24;
				ofDrawLine(y1, x1, y2, x2);
			}
			if (vbar[tx][ty+1] == 0 && visited[tx][ty+1]) {
				x2 = (tx)*LINE_LENGTH + 24;
				y2 = (ty + 1)*LINE_LENGTH + 24;
				ofDrawLine(y1, x1, y2, x2);
			}
			if (hbar[tx][ty] == 0 && visited[tx - 1][ty]) {
				x2 = (tx - 1)*LINE_LENGTH + 24;
				y2 = (ty)*LINE_LENGTH + 24;
				ofDrawLine(y1, x1, y2, x2);
			}
			if (hbar[tx + 1][ty] == 0 && visited[tx + 1][ty]) {
				x2 = (tx + 1)*LINE_LENGTH + 24;
				y2 = (ty)*LINE_LENGTH + 24;
				ofDrawLine(y1, x1, y2, x2);
			}
		}
		ofSetColor(0, 0, 255);
		temp = qN;
		while (1) {
			int x1, x2, y1, y2;
			if (temp->parent==NULL) { break; }
			x1=(temp->x)*LINE_LENGTH + 24;
			x2 = (temp->parent->x)*LINE_LENGTH + 24;
			y1 = (temp->y)*LINE_LENGTH + 24;
			y2 = (temp->parent->y)*LINE_LENGTH + 24;
			ofDrawLine(y1, x1, y2, x2);
			
			temp = temp->parent;
		}
	}


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	int i, j;

	if (key == 'd') {
		//dfs
		for (i = 0; i < m + 1; i++) {
			for (j = 0; j < n + 1; j++) {
				visited[i][j] = 0;
			}
		}
		dfs(root);
		
		dfs_flag = 1;
		bfs_flag = 0;
		this->draw();
	}

	if (key == 'b') {
		//bfs
		for (i = 0; i < m + 1; i++) {
			for (j = 0; j < n + 1; j++) {
				visited[i][j] = 0;
			}
		}
		bfs(root);
		
		dfs_flag = 0;
		bfs_flag = 1;
		this->draw();
	}


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	if (key == 'l') {
		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select");

		if (openFileResult.bSuccess) {
			ofLogVerbose("User selected a file");

			processOpenFileSelection(openFileResult);
			load_flag = 1;
		}
	}

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) {
	int lNum = 0;
	int flag = 0;
	int i,j;
	m = 0; 
	n = 0;
	string fileName = openFileResult.getName();
	ofFile file(fileName);

	if (!file.exists()) cout << "Target file does not exists." << endl;
	else cout << "We found the target file." << endl;

	ofBuffer buffer(file);

	for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
		string line = *it;
		if (lNum%2 == 0) {
			if (flag == 0) {
				n = line.size()/2;
				flag == 1;
				for (i = 0; i < n*2; i++) {
					hbar[0][i / 2] = 1;
				}
			}
			for (i = 1; i < n*2+1; i+=2) {
				if (line[i] == '-') {
					hbar[lNum/2][i / 2] = 1;
				}
				else {
					hbar[lNum/2][i / 2] = 0;
				}
			}
		}
		else {
			//printf("%d", lNum);
			for (i = 0; i < n*2+1; i+=2) {
				if (line[i] == '|') {
					vbar[lNum/2][i / 2] = 1;
				}
				else {
					vbar[lNum/2][i / 2] = 0;
				}
			}
		}
		lNum++;
	}
	m = lNum/2;
	//for (i = 0; i < m; i++) {
	//	for (j = 0; j < n; j++) {
	//		if (vbar[i][j] == 1) {
	//			printf("h %d", vbar[i][j]);
	//		}
	//	}
	//	printf("\n");
	//}
	this->draw();

	for (i = 0; i < m + 1; i++) {
		for (j = 0; j < n + 1; j++) {
			visited[i][j] = 0;
		}
	}

	makeTree(root);


}

void ofApp::makeTree(Node* node) {
	int x = node->x;//x 행
	int y = node->y;//y 열
	visited[x][y] = 1;
	if (x > 0 && y > 0) {
		if (hbar[x][y] == 0) {
			if (visited[x - 1][y] == 0) {
				Node* uNode = new Node(x - 1, y);
				uNode->parent = node;
				node->up = uNode;
				makeTree(uNode);
			}
		}
		if (hbar[x + 1][y] == 0) {
			if (visited[x + 1][y] == 0) {
				Node* dNode = new Node(x + 1, y);
				dNode->parent = node;
				node->down = dNode;
				makeTree(dNode);
			}
		}
		if (vbar[x][y] == 0) {
			if (visited[x][y - 1] == 0) {
				Node* lNode = new Node(x, y - 1);
				lNode->parent = node;
				node->left = lNode;
				makeTree(lNode);
			}
		}
		if (vbar[x][y + 1] == 0) {
			if (visited[x][y + 1] == 0) {
				Node* rNode = new Node(x, y + 1);
				rNode->parent = node;
				node->right = rNode;
				makeTree(rNode);
			}
		}

	}
	else {
		if (x == 0 && y != 0) {
			if (vbar[x][y] == 0) {
				if (visited[x][y - 1] == 0) {
					Node* lNode = new Node(x, y-1);
					lNode->parent = node;
					node->left = lNode;
					makeTree(lNode);
				}
			}
			if (vbar[x][y + 1] == 0) {
				if (visited[x][y + 1] == 0) {
					Node* rNode = new Node(x, y + 1);
					rNode->parent = node;
					node->right = rNode;
					makeTree(rNode);
				}
			}
			if (hbar[x + 1][y] == 0) {
				if (visited[x + 1][y] == 0) {
					Node* dNode = new Node(x + 1, y);
					dNode->parent = node;
					node->down = dNode;
					makeTree(dNode);
				}
			}
		}
		if (x != 0 && y == 0) {
			if (hbar[x][y] == 0) {
				if (visited[x - 1][y] == 0) {
					Node* uNode = new Node(x - 1, y);
					uNode->parent = node;
					node->up = uNode;
					makeTree(uNode);
				}
			}
			if (hbar[x + 1][y] == 0) {
				if (visited[x + 1][y] == 0) {
					Node* dNode = new Node(x + 1, y);
					dNode->parent = node;
					node->down = dNode;
					makeTree(dNode);
				}
			}
			if (vbar[x][y + 1] == 0) {
				if (visited[x][y + 1] == 0) {
					Node* rNode = new Node(x, y + 1);
					rNode->parent = node;
					node->right = rNode;
					makeTree(rNode);
				}
			}
		}
		if (x == 0 && y == 0) {
			if (vbar[x][y + 1] == 0) {
				if (visited[x][y + 1] == 0) {
					Node* rNode = new Node(x, y + 1);
					rNode->parent = node;
					node->right = rNode;
					makeTree(rNode);
				}
			}
			if (hbar[x + 1][y] == 0) {
				if (visited[x + 1][y] == 0) {
					Node* dNode = new Node(x + 1, y);
					dNode->parent = node;
					node->down = dNode;
					makeTree(dNode);
				}
			}
		}	

	}
}

Node* ofApp::unvisited(Node* node) {
	int nx, ny;
	nx = node->x;
	ny = node->y;
	
	if (node->up != NULL && visited[nx - 1][ny] == 0) { return node->up; }
	if (node->down != NULL && visited[nx + 1][ny] == 0) { return node->down; }
	if (node->left != NULL && visited[nx][ny - 1] == 0) { return node->left; }
	if (node->right != NULL && visited[nx][ny + 1] == 0) { return node->right; }
	return NULL;
}

void ofApp::dfs(Node* node) {
	Node *top, *temp;
	int i, t;
	int tx, ty;
	if (!list.empty()) {
		t = list.size();
		for (i = 0; i < t;i++) {
			printf("list notempty\n");
			list.pop_back();
		}
	}
	if (!points.empty()) {
		t = points.size();
		for (i = 0; i < t; i++) {
			printf("points notempty\n");
			points.pop_back();
		}
	}
	list.push_back(node);
	while (list.size() != 0) {
		top = list.at(list.size() - 1);
		//printf("x : %d  y : %d\n", top->x, top->y);
		tx = top->x;
		ty = top->y;
		visited[tx][ty] = 1;
		Point tempP;
		tempP.x = tx;
		tempP.y = ty;
		points.push_back(tempP);
		if (tx == m - 1 && ty == n - 1) { break; }
		temp = unvisited(top);
		if (temp != NULL) {
			list.push_back(temp);
			visited[temp->x][temp->y] = 1;
		}
		else {
			list.pop_back();
		}
	}
	
	printf("num %d\n", points.size());
}
void ofApp::bfs(Node* node) {
	Node *front, *temp,*tmp;
	int i,t;
	int fx, fy,tx,ty;
	if (!queue.empty()) {
		t = queue.size();
		for (i = 0; i < t; i++) {
			printf("list notempty\n");
			queue.pop();
		}
	}
	if (!points.empty()) {
		t = points.size();
		for (i = 0; i < t; i++) {
			printf("points notempty\n");
			points.pop_back();
		}
	}
	queue.push(node);
	while (queue.size() != 0) {
		front = queue.front();
		fy = front->y;
		fx = front->x;
		visited[fx][fy] = 1;
		Point tempP;
		tempP.x = fx;
		tempP.y = fy;
		points.push_back(tempP);
		
		if (fx == m - 1 && fy == n - 1) { 
			qN = front;
			
			break;
		}
		if (front->up != NULL && visited[fx - 1][fy] == 0) { queue.push(front->up); }
		if (front->down != NULL && visited[fx + 1][fy] == 0) { queue.push(front->down); }
		if (front->left != NULL && visited[fx][fy - 1] == 0) { queue.push(front->left); }
		if (front->right != NULL && visited[fx][fy + 1] == 0) { queue.push(front->right); }
		queue.pop();
	}
	
}
