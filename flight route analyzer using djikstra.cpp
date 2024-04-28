Source Code:
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long long int ll;
typedef unsigned int ui;
typedef unsigned long long ull;
typedef unsigned long long int ulli;

vector<pair<int, int>> g[10000];
vector<pair<int, int>> REV[10000];
vector<pair<int, pair<int, int>>> edges;
vector<int> parent(10000);
vector<bool> visited(10000, false);
map<string, int> mp;
map<int, string> revmp;
int hash_value = 0;

void fast_io()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
}

// Initializes DSU
void init()
{
    for (int i = 0; i <= hash_value + 5; i++)
    {
        visited[i] = false;
        parent[i] = i;
    }
}

// Maps an airport name to an index
void H(string s)
{
    hash_value++;
    mp[s] = hash_value;
    revmp[hash_value] = s;
}

// Gets the index of an airport
int getHash(string s)
{
    return mp[s];
}

// Gets airport name from index
string getAirport(int x)
{
    return revmp[x];
}

void create_airport(string s)
{
    H(s);
    cout << "Airport " << s << " has been created." << endl << endl;
}

// Creates an edge
void create_route(string a, string b, int c)
{
    int x = getHash(a);
    int y = getHash(b);
    g[x].push_back({y, c});
    REV[y].push_back({x, c});
    edges.push_back({c, {x, y}});
    cout << "Route between " << a << " and " << b << " has been created with cost " << c << "." << endl << endl;
}

// Test function
void dfs(int x)
{
    visited[x] = true;
    cout << getAirport(x) << " ";
    vector<pair<int, int>>::iterator y;
    for (y = g[x].begin(); y != g[x].end(); y++)
    {
        if (!visited[y->first])
        {
            dfs(y->first);
        }
    }
}

void findCheapest(string s, string d)
{
    int src = getHash(s);
    int dest = getHash(d);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(hash_value + 10, INT_MAX);

    pq.push({0, src});
    dist[src] = 0;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        vector<pair<int, int>>::iterator i;
        for (i = g[u].begin(); i != g[u].end(); i++)
        {
            int v = i->first;
            int wgt = i->second;
            if (dist[v] > dist[u] + wgt)
            {
                dist[v] = dist[u] + wgt;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Routes and Costs:" << endl;
    for (int i = 1; i <= hash_value; i++)
    {
        for (auto p : g[i])
        {
            cout << getAirport(i) << " -> " << getAirport(p.first) << ": " << p.second << endl;
        }
    }

    cout << "Cheapest Route from " << s << " to " << d << " is: " << dist[dest] << endl << endl;
}

int find_set(int v)
{
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void merge(int a, int b)
{
    a = find_set(a);
    b = find_set(b);
    if (a != b)
    {
        parent[b] = a;
    }
}

void dsu()
{
    init();
    for (int i = 0; i <= hash_value; i++)
    {
        vector<pair<int, int>>::iterator it;
        for (it = g[i].begin(); it != g[i].end(); it++)
        {
            merge(i, it->first);
        }
    }

    set<int> st;
    for (int i = 1; i <= hash_value; i++)
    {
        st.insert(find_set(i));
    }

    vector<int> disjoint;
    for (auto it = st.begin(); it != st.end(); it++)
    {
        disjoint.push_back(*it);
    }

    if (disjoint.size() == 1)
    {
        cout << "All cities are connected. No new flight routes are necessary." << endl << endl;
    }
    else
    {
        cout << "Required New Routes are:" << endl;
        for (int i = 1; i < disjoint.size(); i++)
        {
            cout << getAirport(disjoint[i - 1]) << " -> " << getAirport(disjoint[i]) << endl;
        }
    }
}

// Kruskal's MST
void kruskal()
{
    init();
    sort(edges.begin(), edges.end());
    cout << "The following Flight Routes can be cancelled:" << endl;
    for (int e = 0; e < edges.size(); e++)
    {
        int u = edges[e].second.first;
        int v = edges[e].second.second;
        if (find_set(u) != find_set(v))
        {
            merge(u, v);
        }
        else
        {
            cout << getAirport(u) << " -> " << getAirport(v) << endl;
        }
    }
    cout << endl;
}

int main()
{
    fast_io();

    cout << "Welcome to the City Route Analyzer!" << endl;
    cout << "Choose the source city:" << endl;
    cout << "1. New York" << endl;
    cout << "2. London" << endl;
    cout << "3. Paris" << endl;
    cout << "4. Tokyo" << endl;
    cout << "5. Sydney" << endl;
    cout << "6. Dubai" << endl;

    int src_index;
    cin >> src_index;
    string source;
    switch (src_index)
    {
    case 1:
        source = "New York";
        break;
    case 2:
        source = "London";
        break;
    case 3:
        source = "Paris";
        break;
    case 4:
        source = "Tokyo";
        break;
    case 5:
        source = "Sydney";
        break;
    case 6:
        source = "Dubai";
        break;
    default:
        cout << "Invalid input" << endl;
        return 0;
    }

    cout << "Choose the destination city:" << endl;
    cout << "1. New York" << endl;
    cout << "2. London" << endl;
    cout << "3. Paris" << endl;
    cout << "4. Tokyo" << endl;
    cout << "5. Sydney" << endl;
    cout << "6. Dubai" << endl;

    int dest_index;
    cin >> dest_index;
    string destination;
    switch (dest_index)
    {
    case 1:
        destination = "New York";
        break;
    case 2:
        destination = "London";
        break;
    case 3:
        destination = "Paris";
        break;
    case 4:
        destination = "Tokyo";
        break;
    case 5:
        destination = "Sydney";
        break;
    case 6:
        destination = "Dubai";
        break;
    default:
        cout << "Invalid input" << endl;
        return 0;
    }

    // Add sample airports and routes
    create_airport("New York");
    create_airport("London");
    create_airport("Paris");
    create_airport("Tokyo");
    create_airport("Sydney");
    create_airport("Dubai");

    create_route("New York", "London", 300);
    create_route("New York", "Paris", 400);
    create_route("New York", "Tokyo", 500);
    create_route("London", "Paris", 200);
    create_route("London", "Tokyo", 450);
    create_route("London", "Sydney", 700);
    create_route("Paris", "Tokyo", 600);
    create_route("Paris", "Sydney", 550);
    create_route("Tokyo", "Sydney", 350);
    create_route("Sydney", "Dubai", 400);

    findCheapest(source, destination);
    dsu();
    kruskal();

    return 0;
}
