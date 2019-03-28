//queue up "entry" number of ways to get into maze.
queue<Space> open;
unordered_map< pair< pair<int,int>, pair<int, int> >, pair< pair<int,int>, pair<int, int> > > visited;
// top row
for (int j = 0; j < width; j++) {
  Space x(-1, j, 'S', SOUTH);
  open.push(x);
}
// bottom row facing up
for (int j = 0; j < width; j++) {
  Space x(width, j, 'S', NORTH);
  open.push(x);
}
// left row facing right
for (int i = 0; i < height; i++) {
  Space x(i, -1, 'S', EAST);
  open.push(x);
}
// right row facing left
for (int i = 0; i < height; i++) {
  Space x(i, height, 'S', WEST);
  open.push(x);
}
// actual bfs
Space start;
while (!open.empty()) {
  Space curr = open.front();
  open.pop();
  if (curr.state == '*') {
    start = curr;
  }
  int r1 = curr.row;
  int c1 = curr.col;
  vector<Space> nextNodes;
  int things = 0;
  findNextNodes(curr, nextNodes, things);
  for (int i = 0; i < things; i++) {
    Space next = nextNodes.at(i);
    int r2 = next.row;
    int c2 = next.col;
    // if past bounds of maze, get out
    if (r >= height || c >=  width || r == -1 || c == -1) {
      continue;
    }
    // if unseen
    if (!visited.count(next)) {
      visited.insert(<r2, c2> , <r1, c1>);
      open.push(next);
    }
  }
}
// traceback path
vector<Space> path;
Space curr = start;
int curr_r = curr.row;
int curr_c = curr.col;
while (visited.count(<curr_r, curr_c>) != 0) {
  path.push_back(curr);
  Space back = visited[curr];
  curr = back;
  curr_r = curr.row;
  curr_c = curr.col;
}
return path;
