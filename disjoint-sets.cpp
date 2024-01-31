// Homework Disjoint Sets
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class DisjoinSet // interface
{
public:
    virtual ~DisjoinSet() {}
    virtual void MakeSet(int x) = 0;
    virtual int Find(int x) = 0;
    virtual void Union(int x, int y) = 0;

//verifica si hay un camino entre x e y
    virtual bool isConnected(int x, int y) = 0;
};

template <typename T>
class DisjoinSetTree: public DisjoinSet{
private:
    int *rank, *parent;
    T data;
public:
    DisjoinSetTree(T* data, int n){
        rank = new int[n];
        parent = new int[n];
        MakeSet(n);
    }
// implement all functions
    void MakeSet(int x) override {
        for (int i = 0; i < x; ++i)
            parent[i] = i;
    }

    int Find(int x) override {
        if (parent[x] != x) {
            parent[x] = Find(parent[x]);
        }
        return parent[x];
    }
    void Union(int x, int y) override {
        int xset = Find(x);
        int yset = Find(y);

        if (xset == yset)
            return;

        if (rank[xset] < rank[yset]) {
            parent[xset] = yset;
        }
        else if (rank[xset] > rank[yset]) {
            parent[yset] = xset;
        }else {
            parent[yset] = xset;
            rank[xset] = rank[xset] + 1;
        }
    }
    bool isConnected(int x, int y) override {
        int xset = Find(x);
        int yset = Find(y);
        if (xset == yset)
            return true;
        return false;
    }
    ~DisjoinSetTree() override {
        delete[] rank;
        delete[] parent;
    }
};

template <typename T>
class DisjoinSetArray: public DisjoinSet{
private:
    int *parent;
    int n;
    T *data;
public:
    DisjoinSetArray(T* data, int n){
        parent = new int[n];
        MakeSet(n);
    }
// implement all functions
    void MakeSet(int x) override {
        for (int i = 0; i < x; ++i)
            parent[i] = i;
    }
    int Find(int x) override {
        while (x != parent[x])
            x = parent[x];
        return x;
    }
    void Union(int x, int y) override {
        int xset = Find(x);
        int yset = Find(y);

        if (xset != yset)
            parent[yset] = xset;
    }
    bool isConnected(int x, int y) override {
        int xset = Find(x);
        int yset = Find(y);
        if (xset == yset)
            return true;
        return false;
    }
    ~DisjoinSetArray() override {
        delete[] parent;
    }
};

int main (){
    const int n = 10; // tamaño de los conjuntos

    DisjoinSetTree<int> tree_set(nullptr, n);
    DisjoinSetArray<int> array_set(nullptr, n);

    tree_set.Union(0, 1);
    tree_set.Union(2, 3);
    tree_set.Union(4, 5);

    array_set.Union(1, 2);
    array_set.Union(3, 4);
    array_set.Union(6, 7);

    cout << "Tree set " << endl;
    cout << "0 y 1 estan conectados: " << tree_set.isConnected(0, 1) << endl;
    cout << "0 y 2 estan conectados: " << tree_set.isConnected(0, 2) << endl;
    cout << "Array set " << endl;
    cout << "1 y 3 estan conectados: " << array_set.isConnected(1, 3) << endl;
    cout << "1 y 6 estan conectados: " << array_set.isConnected(1, 6) << endl;

}