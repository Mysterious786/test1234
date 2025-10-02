import java.util.*;

public class Dijkstra {
    static class Edge { int to; long w; Edge(int t, long w){this.to=t;this.w=w;} }
    static class Node implements Comparable<Node> {
        int v; long dist;
        Node(int v, long dist){this.v=v;this.dist=dist;}
        public int compareTo(Node o){ return Long.compare(this.dist, o.dist); }
    }

    // Returns distances array and parent array for path reconstruction
    // n = number of vertices (0..n-1), graph as adjacency list
    public static Pair<long[], int[]> dijkstra(List<Edge>[] graph, int src) {
        int n = graph.length;
        long[] dist = new long[n];
        int[] parent = new int[n];
        Arrays.fill(dist, Long.MAX_VALUE);
        Arrays.fill(parent, -1);

        PriorityQueue<Node> pq = new PriorityQueue<>();
        dist[src] = 0;
        pq.add(new Node(src, 0));

        while (!pq.isEmpty()) {
            Node cur = pq.poll();
            int u = cur.v;
            long d = cur.dist;
            if (d != dist[u]) continue; // stale entry

            for (Edge e : graph[u]) {
                int v = e.to;
                long nd = d + e.w;
                if (nd < dist[v]) {
                    dist[v] = nd;
                    parent[v] = u;
                    pq.add(new Node(v, nd));
                }
            }
        }
        return new Pair<>(dist, parent);
    }

    // Reconstruct path from src to target using parent array
    public static List<Integer> getPath(int[] parent, int target) {
        LinkedList<Integer> path = new LinkedList<>();
        for (int v = target; v != -1; v = parent[v]) path.addFirst(v);
        return path;
    }

    // Simple Pair class
    static class Pair<A,B> {
        public final A first; public final B second;
        Pair(A a, B b){ first = a; second = b; }
    }

    // Example usage
    public static void main(String[] args){
        int n = 6; // vertices 0..5
        List<Edge>[] g = new ArrayList[n];
        for(int i=0;i<n;i++) g[i]=new ArrayList<>();

        // addEdge(u, v, weight)
        addEdge(g, 0,1,7);
        addEdge(g, 0,2,9);
        addEdge(g, 0,5,14);
        addEdge(g, 1,2,10);
        addEdge(g, 1,3,15);
        addEdge(g, 2,3,11);
        addEdge(g, 2,5,2);
        addEdge(g, 3,4,6);
        addEdge(g, 4,5,9);

        Pair<long[],int[]> res = dijkstra(g, 0);
        long[] dist = res.first;
        int[] parent = res.second;

        for(int i=0;i<n;i++){
            System.out.println("0 -> " + i + " = " + (dist[i]==Long.MAX_VALUE ? "INF" : dist[i]) +
                               "   path: " + (dist[i]==Long.MAX_VALUE ? "none" : getPath(parent, i)));
        }
    }

    static void addEdge(List<Edge>[] g, int u, int v, long w){
        g[u].add(new Edge(v,w));
        g[v].add(new Edge(u,w)); // comment out for directed graph
    }
}
