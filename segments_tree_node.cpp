#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

typedef long long ll;

struct Node {
    ll info;
    int treel;
    int treer;
    Node* left = NULL;
    Node* right = NULL;
    Node* pred = NULL;
};

void init(Node* Elem, int treel, int treer) {
    Elem -> treel = treel;
    Elem -> treer = treer;
    Elem -> info = 0;
    if (treel != treer) {
        int mid = (treel + treer) / 2;
        // [treel, mid] [mid + 1, treer]
        Node* Eleml = new Node;
        Node* Elemr = new Node;
        Elem -> left = Eleml;
        Eleml -> pred = Elem;
        Elem -> right = Elemr;
        Elemr -> pred = Elem;
        init(Elem -> left, treel, mid);
        init(Elem -> right, mid + 1, treer);

    }
}

void change_elem(Node* Elem, int data, int id) {
    if (id == Elem -> treel && id == Elem -> treer) {
        Elem -> info = data;
    }
    else {
        int mid = (Elem -> treel + Elem -> treer) / 2;
        if (Elem -> treel <= id && mid >= id) {
            change_elem(Elem -> left, data, id);
        }
        else  {
            change_elem(Elem -> right, data, id);
        }
        Elem -> info = Elem -> left -> info + Elem -> right -> info;
    }
}

ll sumTree(Node* Elem, int l, int r) {
    if (l < Elem -> treel && Elem -> treer <= r)
        return Elem -> info;
    if (Elem -> treer < l || r < Elem -> treel)
        return 0; // нейтральный элемент
    return sumTree(Elem -> left, l, r)  + sumTree(Elem -> right, l, r);
}

int main() {
    int n, q;
    cin >> n >> q;
    Node* Root = new Node;
    init(Root, 1, n);
    vector <int> A (n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> A[i];
        change_elem(Root, A[i], i);
    }
    for (int i = 0; i < q; ++i) {
        int key;
        cin >> key;
        if (key == 2) {
            int data, id;
            cin >> id >> data;
            change_elem(Root, data, id);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << sumTree(Root, l, r) << '\n';
        }
    }
}