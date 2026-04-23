#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <climits>

using namespace std;

const int MAXN = 1005;
int grid[MAXN][MAXN];
int dist[MAXN][MAXN];
int n, m;

// Directions: up, down, left, right
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

struct Point {
    int x, y;
};

// BFS to find shortest distance from start to all reachable positions
void bfs(int startX, int startY) {
    memset(dist, -1, sizeof(dist));
    queue<Point> q;
    q.push({startX, startY});
    dist[startX][startY] = 0;
    
    while (!q.empty()) {
        Point curr = q.front();
        q.pop();
        
        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            
            // Check boundaries
            if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
            
            // Check if already visited
            if (dist[nx][ny] != -1) continue;
            
            // Check if it's a construction site (1)
            if (grid[nx][ny] == 1) continue;
            
            dist[nx][ny] = dist[curr.x][curr.y] + 1;
            q.push({nx, ny});
        }
    }
}

int main() {
    cin >> n >> m;
    
    int startX = -1, startY = -1;  // Position 2 (skytim's location)
    int homeX = -1, homeY = -1;    // Position 3 (home)
    vector<Point> shops;            // All positions with 4 (umbrella shops)
    
    // Read the grid
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                startX = i;
                startY = j;
            } else if (grid[i][j] == 3) {
                homeX = i;
                homeY = j;
            } else if (grid[i][j] == 4) {
                shops.push_back({i, j});
            }
        }
    }
    
    // BFS from start position to find distances to all umbrella shops
    bfs(startX, startY);
    
    int minDistance = INT_MAX;
    
    // For each umbrella shop, calculate total distance
    for (const Point& shop : shops) {
        int distToShop = dist[shop.x][shop.y];
        
        // If shop is not reachable from start, skip it
        if (distToShop == -1) continue;
        
        // BFS from shop to find distance to home
        bfs(shop.x, shop.y);
        int distToHome = dist[homeX][homeY];
        
        // If home is not reachable from shop, skip this shop
        if (distToHome == -1) continue;
        
        // Update minimum distance
        int totalDist = distToShop + distToHome;
        minDistance = min(minDistance, totalDist);
    }
    
    cout << minDistance << endl;
    
    return 0;
}
