//
// Created by anton on 5/26/20.
//

struct Data {
    int x, y, z;
};

Data ** foo(Data ** v, int x) {
    for (int i = 0; i < x; i++)
        if (v[i] != 0)
            v[i] = new Data;
    return v;
}

int main () {
    const int size = 5;
    Data ** v = new Data * [size];
    foo(v, size);
    delete [] v;
}
