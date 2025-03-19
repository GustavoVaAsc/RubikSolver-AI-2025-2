#include<iostream>
#include "moves.cpp"
#include<stdlib.h>
#include<time.h>
#include<cmath>
#include<map>
#include<algorithm>
#include<stack>
#include<set>
#include<fstream>

#define all(v) v.begin(),v.end()
#define X first 
#define Y second
class Graph
{
    public:
        
        Cube game;
        priority_queue<pair<ll, Cube>> q;
        map<Cube,Cube> path;
        set<Cube> visited;      
        map<Cube,vector<int>> mov;
        map<Cube,ll> dist;
        Cube f,s;

        Graph() {
            game.reset();
            randomize();
            s = game;
        }

        

        void randomize() {
            srand(time(NULL));
            int t = 3 + rand() % 6; // Randomly choose 3-8 moves
            while (t--) {
                int opt = 1 + rand() % 3; // Move type: 1, 2, or 3
                bool flag = rand() % 2;   // Direction: true/false
                int param = rand() % 3;   // Row/column/depth (0,1,2)
        
                // Apply the move (no skips for param == 1)
                switch (opt) {
                    case 1: // Horizontal move (all rows allowed)
                        game.horizontal(flag, param);
                        break;
                    case 2: // Vertical move (all columns allowed)
                        game.vertical(flag, param);
                        break;
                    case 3: // Rotation (all depths allowed)
                        game.rotar(flag, param);
                        break;
                }
            }
            s = game; // Track scrambled state
        }

        bool finalState(Cube c) {
            // Check if all faces are solved using CENTER tiles as reference
            for (int face = 0; face < c.faces; face++) {
                // Get center color (works for odd-sized cubes)
                int centerX = c.length/2;
                int centerY = c.length/2;
                int targetColor = c.cube[face][centerX][centerY].color;
                
                for (int i = 0; i < c.length; i++) {
                    for (int j = 0; j < c.length; j++) {
                        if (c.cube[face][i][j].color != targetColor) {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        
        
        bool finalPhase1(Cube c) {
            int targetFace = 0; // Assuming face 0 is the first layer (e.g., white)
            int targetColor = c.cube[targetFace][0][0].color;
        
            // Check if all tiles on the target face (first layer) are solved
            for (int i = 0; i < c.length; i++) {
                for (int j = 0; j < c.length; j++) {
                    if (c.cube[targetFace][i][j].color != targetColor) {
                        return false;
                    }
                }
            }
        
            // Check adjacent faces' edges connected to the first layer
            // Face adjacency and orientation depend on your cube's implementation.
            // This example assumes:
            // - Face 0: Front (white)
            // - Face 1: Top (blue), Face 2: Right (red), Face 3: Bottom (green), Face 4: Left (orange)
        
            // Check Top Face (1): Bottom row (adjacent to Front face's top row)
            int topCenter = c.cube[1][1][1].color; // Center of Top face
            for (int j = 0; j < c.length; j++) {
                if (c.cube[1][c.length - 1][j].color != topCenter) { // Bottom row of Top face
                    return false;
                }
            }
        
            // Check Right Face (2): Left column (adjacent to Front face's right column)
            int rightCenter = c.cube[2][1][1].color; // Center of Right face
            for (int i = 0; i < c.length; i++) {
                if (c.cube[2][i][0].color != rightCenter) { // Left column of Right face
                    return false;
                }
            }
        
            // Check Bottom Face (3): Top row (adjacent to Front face's bottom row)
            int bottomCenter = c.cube[3][1][1].color; // Center of Bottom face
            for (int j = 0; j < c.length; j++) {
                if (c.cube[3][0][j].color != bottomCenter) { // Top row of Bottom face
                    return false;
                }
            }
        
            // Check Left Face (4): Right column (adjacent to Front face's left column)
            int leftCenter = c.cube[4][1][1].color; // Center of Left face
            for (int i = 0; i < c.length; i++) {
                if (c.cube[4][i][c.length - 1].color != leftCenter) { // Right column of Left face
                    return false;
                }
            }
        
            return true;
        }

        bool finalPhase2(Cube c) {
            // Already solved Phase 1 (first layer + adjacent edges)
            if (!finalPhase1(c)) return false;
        
            // Check middle layer edges (using standard 3x3 adjacency)
            // Face 1 (Top): Middle row (horizontal moves affect this)
            int topCenter = c.cube[1][1][1].color;
            for (int j = 0; j < c.length; j++) {
                if (c.cube[1][1][j].color != topCenter) return false;
            }
        
            // Face 2 (Right): Middle column
            int rightCenter = c.cube[2][1][1].color;
            for (int i = 0; i < c.length; i++) {
                if (c.cube[2][i][1].color != rightCenter) return false;
            }
        
            // Face 4 (Left): Middle column
            int leftCenter = c.cube[4][1][1].color;
            for (int i = 0; i < c.length; i++) {
                if (c.cube[4][i][1].color != leftCenter) return false;
            }
        
            return true;
        }

        bool finalPhase3(Cube c) {
            // Check entire last layer (face 5, assuming 5 is opposite face 0)
            int targetColor = c.cube[5][1][1].color;
            for (int i = 0; i < c.length; i++) {
                for (int j = 0; j < c.length; j++) {
                    if (c.cube[5][i][j].color != targetColor) return false;
                }
            }
            
            // Check last layer edges on adjacent faces
            for (int face : {1, 2, 3, 4}) { // Top, Right, Bottom, Left
                int center = c.cube[face][1][1].color;
                for (int pos = 0; pos < c.length; pos++) {
                    if (c.cube[face][2][pos].color != center) return false;
                }
            }
            
            return true;
        }


        ll heuPhase1(Cube c) {
            ll heuristic = 0;
            const int targetFace = 0; // First layer (e.g., white face)
            const int targetColor = c.cube[targetFace][1][1].color; // Center color of target face
        
            // Check target face (first layer)
            for (int i = 0; i < c.length; i++) {
                for (int j = 0; j < c.length; j++) {
                    // Count tiles not matching the target color on the first layer
                    if (c.cube[targetFace][i][j].color != targetColor) {
                        heuristic++;
                    }
                }
            }
        
            // Check adjacent face edges (order depends on your cube's adjacency mapping)
            // Example assumes:
            // Face 1: Top, Face 2: Right, Face 3: Bottom, Face 4: Left
            
            // Top face (1): Check bottom row (adjacent to first layer's top)
            const int topCenter = c.cube[1][1][1].color;
            for (int j = 0; j < c.length; j++) {
                if (c.cube[1][c.length-1][j].color != topCenter) heuristic++;
            }
        
            // Right face (2): Check left column (adjacent to first layer's right)
            const int rightCenter = c.cube[2][1][1].color;
            for (int i = 0; i < c.length; i++) {
                if (c.cube[2][i][0].color != rightCenter) heuristic++;
            }
        
            // Bottom face (3): Check top row (adjacent to first layer's bottom)
            const int bottomCenter = c.cube[3][1][1].color;
            for (int j = 0; j < c.length; j++) {
                if (c.cube[3][0][j].color != bottomCenter) heuristic++;
            }
        
            // Left face (4): Check right column (adjacent to first layer's left)
            const int leftCenter = c.cube[4][1][1].color;
            for (int i = 0; i < c.length; i++) {
                if (c.cube[4][i][c.length-1].color != leftCenter) heuristic++;
            }
        
            return heuristic;
        }

        ll heuPhase2(Cube c) {
            ll heuristic = 0;
            
            // Middle layer edges
            int centers[4] = {
                c.cube[1][1][1].color, // Top
                c.cube[2][1][1].color, // Right
                c.cube[4][1][1].color  // Left
            };
            
            // Check Top face middle row
            for (int j = 0; j < c.length; j++) {
                if (c.cube[1][1][j].color != centers[0]) heuristic++;
            }
            
            // Check Right face middle column
            for (int i = 0; i < c.length; i++) {
                if (c.cube[2][i][1].color != centers[1]) heuristic++;
            }
            
            // Check Left face middle column
            for (int i = 0; i < c.length; i++) {
                if (c.cube[4][i][1].color != centers[2]) heuristic++;
            }
            
            return heuristic;
        }

        ll heuPhase3(Cube c) {
            ll heuristic = 0;
            int lastLayerFace = 5;
            int targetColor = c.cube[lastLayerFace][1][1].color;
            
            // Last layer face tiles
            for (int i = 0; i < c.length; i++) {
                for (int j = 0; j < c.length; j++) {
                    if (c.cube[lastLayerFace][i][j].color != targetColor) heuristic++;
                }
            }
            
            // Last layer edges on adjacent faces
            for (int face : {1, 2, 3, 4}) {
                int center = c.cube[face][1][1].color;
                for (int pos = 0; pos < c.length; pos++) {
                    if (c.cube[face][2][pos].color != center) heuristic++;
                }
            }
            
            return heuristic;
        }


        void AstarPhase1() {
            Cube start = game;
            q.push({-heuPhase1(start), start});
            dist[start] = 0;  // Track best-known cost
            mov[start] = {};  // Initialize moves for start state
        
            while (!q.empty()) {
                Cube current = q.top().second;
                ll current_cost = -q.top().first;  // f = g + h
                q.pop();
        
                // Skip if we've already found a better path to this state
                if (dist[current] < current_cost - heuPhase1(current)) {
                    continue;
                }
        
                if (finalPhase1(current)) {
                    f = current;
                    return;
                }
        
                vector<int> lastMove = mov[current];
        
                for (int i = 1; i <= 3; i++) {
                    for (int j = 0; j < 2; j++) {
                        for (int k = 0; k < 3; k++) {
                            if (k == 1) continue;
        
                            // Redundant move pruning (keep your existing logic)
                            if (!lastMove.empty() && i == lastMove[0] && 
                                j == 1 - lastMove[1] && k == lastMove[2]) {
                                continue;
                            }
        
                            Cube neighbor = current;
                            switch (i)
                            {
                                case 1:
                                    neighbor.horizontal(j, k);
                                    break;
                                case 2:
                                    neighbor.vertical(j, k);
                                    break;
                                case 3:
                                    neighbor.rotar(j, k);
                                    break;
                            }
        
                            ll new_cost = dist[current] + 1;  // g-cost increases by 1
                            ll heuristic = heuPhase1(neighbor);  // h-cost
                            ll total_cost = new_cost + heuristic;
        
                            // Update if this path is better than any previous
                            if (dist.find(neighbor) == dist.end() || 
                                new_cost < dist[neighbor]) {
                                
                                dist[neighbor] = new_cost;
                                path[neighbor] = current;
                                mov[neighbor] = {i, j, k};
                                q.push({-total_cost, neighbor});  // Negative for min-heap
                            }
                        }
                    }
                }
            }
        }

        void AstarPhase2() {
            Cube start = game;
            q = priority_queue<pair<ll, Cube>>(); // Reset queue
            dist.clear();
            mov.clear();
            path.clear();
            
            q.push({-heuPhase2(start), start});
            dist[start] = 0;
            
            while (!q.empty()) {
                Cube current = q.top().second;
                ll current_cost = -q.top().first;
                q.pop();
                
                if (dist[current] < current_cost - heuPhase2(current)) continue;
                if (finalPhase2(current)) {
                    f = current;
                    return;
                }
                
                // Modified move generation (avoid disturbing first layer)
                vector<int> lastMove = mov[current];
                for (int i = 1; i <= 3; i++) {
                    for (int j = 0; j < 2; j++) {
                        for (int k = 1; k < 3; k++) { // Only middle (1) and last (2) layers
                            // Redundant move pruning (keep your existing logic)
                            if (!lastMove.empty() && i == lastMove[0] && 
                                j == 1 - lastMove[1] && k == lastMove[2]) {
                                continue;
                            }
        
                            Cube neighbor = current;
                            switch (i)
                            {
                                case 1:
                                    neighbor.horizontal(j, k);
                                    break;
                                case 2:
                                    neighbor.vertical(j, k);
                                    break;
                                case 3:
                                    neighbor.rotar(j, k);
                                    break;
                            }
        
                            ll new_cost = dist[current] + 1;  // g-cost increases by 1
                            ll heuristic = heuPhase2(neighbor);  // h-cost
                            ll total_cost = new_cost + heuristic;
        
                            // Update if this path is better than any previous
                            if (dist.find(neighbor) == dist.end() || 
                                new_cost < dist[neighbor]) {
                                
                                dist[neighbor] = new_cost;
                                path[neighbor] = current;
                                mov[neighbor] = {i, j, k};
                                q.push({-total_cost, neighbor});  // Negative for min-heap
                            }
                        }
                    }
                }
            }
        }

        void AstarPhase3() {
            Cube start = game;
            q = priority_queue<pair<ll, Cube>>(); // Reset queue
            dist.clear();
            mov.clear();
            path.clear();
            
            q.push({-heuPhase3(start), start});
            dist[start] = 0;
            
            while (!q.empty()) {
                Cube current = q.top().second;
                ll current_cost = -q.top().first;
                q.pop();
                
                if (dist[current] < current_cost - heuPhase3(current)) continue;
                if (finalPhase3(current)) {
                    f = current;
                    return;
                }
                
                // Modified move generation (avoid disturbing first layer)
                vector<int> lastMove = mov[current];
                for (int i = 1; i <= 3; i++) {
                    for (int j = 0; j < 2; j++) {
                        for (int k = 1; k < 3; k++) { // Only middle (1) and last (2) layers
                            // Redundant move pruning (keep your existing logic)
                            if (!lastMove.empty() && i == lastMove[0] && 
                                j == 1 - lastMove[1] && k == lastMove[2]) {
                                continue;
                            }
        
                            Cube neighbor = current;
                            switch (i)
                            {
                                case 1:
                                    neighbor.horizontal(j, k);
                                    break;
                                case 2:
                                    neighbor.vertical(j, k);
                                    break;
                                case 3:
                                    neighbor.rotar(j, k);
                                    break;
                            }
        
                            ll new_cost = dist[current] + 1;  // g-cost increases by 1
                            ll heuristic = heuPhase3(neighbor);  // h-cost
                            ll total_cost = new_cost + heuristic;
        
                            // Update if this path is better than any previous
                            if (dist.find(neighbor) == dist.end() || 
                                new_cost < dist[neighbor]) {
                                
                                dist[neighbor] = new_cost;
                                path[neighbor] = current;
                                mov[neighbor] = {i, j, k};
                                q.push({-total_cost, neighbor});  // Negative for min-heap
                            }
                        }
                    }
                }
            }
        }

        void printPath() {
            stack<vector<int>> moves;
            Cube current = f;

            // Reconstruct the move sequence
            while (current != s) {
                moves.push(mov[current]);
                current = path[current];
            }

            // Apply moves to the original cube
            game = s; // Reset to scrambled state
            while (!moves.empty()) {
                auto move = moves.top();
                // Execute the move on the original cube
                switch (move[0]) {
                    case 1: game.horizontal(move[1], move[2]); break;
                    case 2: game.vertical(move[1], move[2]); break;
                    case 3: game.rotar(move[1], move[2]); break;
                }
                moves.pop();
            }

            // Now game holds the solved state
        }
    };


/*
int main()
{
    Graph g;
    g.game.showCube();
    clock_t start, end;
    double cpu_time_used;
    start=clock();
    // Solve Phase 1 (First Layer)
    g.AstarPhase1();
    g.printPath();
    g.game.showCube();

    if (g.finalState(g.game)) {
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout<<cpu_time_used<<endl;
        return 0;
    }
    
    // Solve Phase 2 (Middle Layer)
    g.AstarPhase2();
    g.printPath();
    g.game.showCube();

    if (g.finalState(g.game)) {
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout<<cpu_time_used<<endl;
        return 0;
    }
    
    // Solve Phase 3 (Last Layer)
    g.AstarPhase3();
    g.printPath();
    end=clock();
    g.printPath();
    g.game.showCube();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout<<cpu_time_used<<endl;
    return 0;    
}

*/