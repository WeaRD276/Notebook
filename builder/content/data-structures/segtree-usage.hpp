// Example of (Sum + Range Add) with Lazy Segment Tree
struct S
{
    long long sum;
    int len;
};

using F = long long;

S op(S a, S b)
{ 
    return {a.sum + b.sum, a.len + b.len};
}

S e(){
    return {0, 0}; 
}

S mapping(F f, S x) { 
    return {x.sum + f * x.len, x.len}; 
}

F composition(F f, F g) { 
    return f + g;
}

F id() {
    return 0;
}

vector<S> v(n, {0, 1}); // each segment length = 1 initially
LazySegTree<S, op, e, F, mapping, composition, id> seg(v);
