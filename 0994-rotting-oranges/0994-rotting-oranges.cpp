class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        queue<pair<int,int>> q;
        int fresh = 0;

        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {
                if(grid[r][c] == 2)
                    q.push({r, c});
                else if(grid[r][c] == 1)
                    fresh++;
            }
        }

        if(fresh == 0)
            return 0;

        int minutes = 0;

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        while(!q.empty()) {
            int size = q.size();
            bool rottenThisMinute = false;

            while(size--) {
                auto [r, c] = q.front();
                q.pop();

                for(int i = 0; i < 4; i++) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];

                    if(nr >= 0 && nr < rows &&
                       nc >= 0 && nc < cols &&
                       grid[nr][nc] == 1) {

                        grid[nr][nc] = 2;
                        fresh--;
                        q.push({nr, nc});
                        rottenThisMinute = true;
                    }
                }
            }

            if(rottenThisMinute)
                minutes++;
        }

        return fresh == 0 ? minutes : -1;
    }
};