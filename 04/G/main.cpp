#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct event {
    int x;
    int y_start;
    int y_end;
    int state;
};

bool cmp(const event f, const event s) {
    if (f.x == s.x) {
        if (f.state == s.state)
            return f.y_start < s.y_start;
        else
            return f.state > s.state;
    }
    return f.x < s.x;
}
vector <event> events;

const int MAXN = 5e6 + 10;
const int INF = 1e9;
struct point {
    int y;
    long long mx;
};

point t[MAXN];
long long dt[MAXN];
void BuildTree(int v, int l, int r)
{
    dt[v] = 0;
    t[v] = {-1, -1};
    if (r - l == 1)
    {
        t[v] = {l, 0};
    }
    else
    {
        int m = (l + r) / 2;
        BuildTree(v * 2, l, m);
        BuildTree(v * 2 + 1, m, r);
        if (t[v * 2].mx >= t[v * 2 + 1].mx)
            t[v] = t[v * 2];
        else
            t[v] = t[v * 2 + 1];
    }
}


void push(int v)
{
    if (dt[v] == 0)
    {
        return;
    }
    t[v * 2] = {t[v * 2].y, t[v * 2].mx + dt[v]};
    t[v * 2 + 1] = {t[v * 2 + 1].y, t[v * 2 + 1].mx + dt[v]};
    dt[2 * v] += dt[v];
    dt[2 * v + 1] += dt[v];
    dt[v] = 0;
}

void add(int v, int l, int r, int ql, int qr, long long d)
{
    push(v);
    if ((r <= ql) || (qr <= l))
    {
        return;
    }

    if ((ql <= l) && (r <= qr))
    {
        t[v] = {t[v].y, t[v].mx + d};
        dt[v] += d;
        return;
    }

    int m = (l + r) / 2;
    add(v * 2, l, m, ql, qr, d);
    add(v * 2 + 1, m, r, ql, qr, d);
    if (t[v * 2].mx >= t[v * 2 + 1].mx)
        t[v] = t[v * 2];
    else
        t[v] = t[v * 2 + 1];
}

point get_max(int v, int l, int r, int ql, int qr)
{
    push(v);
    if (l >= qr || r <= ql)
    {
        return {-1, -1};
    }
    else
    {
        if (l >= ql && r <= qr)
        {
            return t[v];
        }
        else
        {
            int m = (l + r) / 2;
            point m1 = get_max(2 * v, l, m, ql, qr);
            point m2 = get_max(2 * v + 1, m, r, ql, qr);

            if (m1.mx >= m2.mx)
                return m1;
            else
                return m2;
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;

    int left = INF;
    int right = -INF;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        left = min(left, min(y1, y2));
        right = max(right, max(y1, y2));
        events.push_back({x1, y1, y2, 1});
        events.push_back({x2, y1, y2, -1});
    }

    BuildTree(1, left, right + 1);
    sort(events.begin(), events.end(), cmp);

    point ans = {-1, -1};
    int x = -1;
    for (auto event : events) {
        add(1, left, right + 1, event.y_start, event.y_end + 1, event.state);
        point p = get_max(1, left, right + 1, left, right + 1);
        if (p.mx > ans.mx) {
            ans = p;
            x = event.x;
        }
    }

    cout << ans.mx << endl;
    cout << x << " " << ans.y;
    return 0;
}