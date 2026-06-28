class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {

        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses, 0);

        for(auto &p : prerequisites) {
            int course = p[0];
            int prereq = p[1];

            adj[prereq].push_back(course);
            indegree[course]++;
        }

        queue<int> q;

        for(int i = 0; i < numCourses; i++) {
            if(indegree[i] == 0)
                q.push(i);
        }

        int completed = 0;

        while(!q.empty()) {
            int node = q.front();
            q.pop();

            completed++;

            for(int nei : adj[node]) {
                indegree[nei]--;

                if(indegree[nei] == 0)
                    q.push(nei);
            }
        }

        return completed == numCourses;
    }
};