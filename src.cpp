// c14,building by maze
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
#include<cassert>
namespace DS {
struct Node {
    Node *father, *children[2];  // 0-->Left,1-->Right
    int val, size;
    bool color;  // 0-->Black,1-->Red
};
class MemoryPool {
   public:
    MemoryPool() {}

   private:
    static const int MAX_POOL_SIZE = 1e6;
    Node Pool[MAX_POOL_SIZE];
    int GCrsp = 0, PoolPointer = 0;
    Node* GCstack[MAX_POOL_SIZE];

   public:
    Node* NewNode(int val = 0) {
        Node* ret;
        if (GCrsp > 0)
            ret = GCstack[GCrsp--];
        else if (PoolPointer < MAX_POOL_SIZE - 1) {
            ret = &Pool[++PoolPointer];
        } else {
            std::clog << "alloc error!" << std::endl;
            exit(1000);
        }
        ret->val = val, ret->size = 1, ret->color = false;
        ret->children[1] = ret->children[0] = ret->father = nullptr;
        return ret;
    }
    void DeleteNode(Node* node) {
        if (node == nullptr) {
            std::clog << "delete nullptr!" << std::endl;
            exit(1001);
        }
        GCstack[++GCrsp] = node;
    }
} my_pool;
struct PNI {
    Node* first;
    int second;
};
Node* PUBNodekth(Node* root, int k) {
    if(!root)return 0;
    if(root->size==k)return root->father;
    while (root != 0) {
        if (root->children[0] != 0) {
            if (k == root->children[0]->size)
                break;
            else if (k < root->children[0]->size) {
                root = root->children[0];
            } else {
                k -= root->children[0]->size + 1;
                root = root->children[1];
            }
        } else if (k > 0) {
            --k;
            root = root->children[1];
        } else
            break;
    }
    return root;
}
template <class Value, class Ref, class Ptr>
struct MyIterator {
    Node* node;
    typedef Value value_type;
    typedef Ref reference;
    typedef Ptr pointer;
    typedef MyIterator<Value, Value&, Value*> iterator;
    typedef MyIterator<Value, const Value&, const Value*> const_iterator;
    typedef MyIterator<Value, Ref, Ptr> self;
    typedef Node* link_type;

    MyIterator() {}
    MyIterator(link_type x) { node = x; }
    MyIterator(const MyIterator& it) { node = it.node; }

    reference operator*() const { return link_type(node)->val; }
    pointer operator->() const { return &(operator*()); }

    self& operator++() {
        increment();
        return *this;
    }
    self operator++(int) {
        self tmp = *this;
        increment();
        return tmp;
    }
    self& operator--() {
        decrement();
        return *this;
    }
    self operator--(int) {
        self tmp = *this;
        decrement();
        return tmp;
    }
    // TODO:test:getrank
    PNI getrank() const {
        if (!node)
            return {0, -2};
        if (!node->father)
            return {0, -1};
        if (node->father->father == node && node->color == 1) {
            return {node->father, node->father->size};
        }
        std::vector<Node*> road;
        auto pt = node;
        int ret = 0;
        road.push_back(pt);
        pt = pt->father;
        road.push_back(pt);
        pt = pt->father;
        int cnt = 2;
        while (pt != road[cnt - 2]) {
            road.push_back(pt);
            pt = pt->father;
            cnt++;
        }
        for (int i = cnt-3; i >=0; i--) {
            if (road[i] == road[i + 1]->children[1]) {
                ret += 1;
                if (road[i + 1]->children[0])
                    ret += road[i + 1]->children[0]->size;
            }           
        }
        if(road[0]->children[0])ret+=road[0]->children[0]->size;
        return {road[cnt - 2], ret};
    }
    self& operator+=(int x) {
        if(x==0) return *this;
        PNI pr = getrank();
        *this = PUBNodekth(pr.first, x + pr.second);
        return *this;
    }
    self& operator-=(int x) {
        if(x==0) return *this;
        PNI pr = getrank();
        *this = PUBNodekth(pr.first, pr.second - x);
        return *this;
    }
    reference operator[](const unsigned long long x){
        return *((*this)+x);
    }
    void increment() {
        if (node->children[1] != 0) {
            node = node->children[1];
            while (node->children[0] != 0)
                node = node->children[0];
        } else {
            Node* y = node->father;
            while (node == y->children[1]) {
                node = y;
                y = y->father;
            }
            if (node->children[1] != y)
                node = y;
        }
    }
    void decrement() {
        if (node->color == 1 && node->father->father == node) {
            node = node->children[1];
            // when node==end()
        } else if (node->children[0] != 0) {
            Node* y = node->children[0];
            while (y->children[1] != 0) {
                y = y->children[1];
            }
            node = y;
        } else {
            Node* y = node->father;
            while (node == y->children[0]) {
                node = y;
                y = node->father;
            }
            node = y;
        }
    }
    bool operator==(const MyIterator& other) const{ return (node == other.node); }
    bool operator!=(const MyIterator& other)const { return (node != other.node); }
    bool operator<(const MyIterator& other) const{
        PNI pr1 = getrank(), pr2 = other.getrank();
        return pr1.second < pr2.second;
    }
    bool operator>(const MyIterator& other)const { return (other < *this); }
    bool operator>=(const MyIterator& other)const { return !(*this < other); }
    bool operator<=(const MyIterator& other)const { return !(other < *this); }
};

template <class Value, class Ref, class Ptr>
MyIterator<Value, Ref, Ptr> operator+(MyIterator<Value, Ref, Ptr> it, int x) {
    return it += x;
}
template <class Value, class Ref, class Ptr>
MyIterator<Value, Ref, Ptr> operator+(int x, MyIterator<Value, Ref, Ptr> it) {
    return it += x;
}
template <class Value, class Ref, class Ptr>
MyIterator<Value, Ref, Ptr> operator-(MyIterator<Value, Ref, Ptr> it, int x) {
    return it -= x;
}
template <class Value, class Ref, class Ptr>
int operator-(MyIterator<Value, Ref, Ptr> it1,
                             MyIterator<Value, Ref, Ptr> it2) {
    PNI pr1 = it1.getrank(), pr2 = it2.getrank();
    if (pr1.first != pr2.first) {
        exit(4000);
    }
    return pr1.second - pr2.second;
}
class LinearTable {
   public:
    typedef size_t size_type;
    typedef int value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef Node* link_type;

   public:
    typedef MyIterator<value_type, reference, pointer> iterator;
    typedef MyIterator<value_type, const_reference, const_pointer>
        const_iterator;

   protected:
    link_type header;
    size_type node_count;
    link_type& root() const { return (link_type&)header->father; }
    link_type& leftmost() const { return (link_type&)header->children[0]; }
    link_type& rightmost() const { return (link_type&)header->children[1]; }
    static link_type& left(link_type x) { return (link_type&)x->children[0]; }
    static link_type& right(link_type x) { return (link_type&)x->children[1]; }
    static link_type& father(link_type x) { return (link_type&)x->father; }
    static reference value(link_type x) { return x->val; }
    static bool& color(link_type x) { return x->color; }

   private:
    // TODO:constants
   public:
    // get iterator
    iterator begin() { return leftmost(); }
    const_iterator begin() const { return leftmost(); }
    iterator end() { return header; }
    const_iterator end() const { return header; }
    reference front() { return leftmost()->val; }
    reference back() { return rightmost()->val; }
    const_reference front() const { return leftmost()->val; }
    const_reference back() const { return rightmost()->val; }

   public:
    // TODO:construct and destruct
    LinearTable() : node_count(0) { uniniversal_setup(); }
    ~LinearTable() { clear(), my_pool.DeleteNode(header); }
    LinearTable(size_type n, value_type value = 0) {
        node_count = 0;
        uniniversal_setup();
        for (size_type i = 0; i < n; i++) {
            push_back(value);
        }
    }
    LinearTable(const_pointer first, const_pointer last) {
        uniniversal_setup();
        for (const_pointer i = first; i != last; ++i) {
            push_back((*i));
        }
    }
    LinearTable(const_iterator first, const_iterator last) {
        uniniversal_setup();
        for (const_iterator i = first; i != last; ++i) {
            push_back((*i));
        }
    }
    LinearTable(iterator first, iterator last) {
        uniniversal_setup();
        for (iterator i = first; i != last; ++i) {
            push_back((*i));
        }
    }
    LinearTable(const LinearTable& other) {  // deep copy
        header = my_pool.NewNode();
        header->color = 1;
        node_count = 0;
        if (other.root() == 0) {
            root() = 0;
            leftmost() = rightmost() = header;
        } else {
            root() = __copy(other.root(), header);
            leftmost() = root();
            while (left(leftmost()))
                leftmost() = left(leftmost());
            rightmost() = root();
            while (right(rightmost()))
                rightmost() = right(rightmost());
            node_count = other.node_count;
        }
    }
    LinearTable& operator=(const LinearTable& other) {
        if (this != &other) {
            clear();
            node_count = 0;
            if (other.root() == 0) {
                root() = 0;
                leftmost() = rightmost() = header;
            } else {
                root() = __copy(other.root(), header);
                leftmost() = root();
                while (left(leftmost()))
                    leftmost() = left(leftmost());
                rightmost() = root();
                while (right(rightmost()))
                    rightmost() = right(rightmost());
                node_count = other.node_count;
            }
        }
        return *this;
    }
    LinearTable(LinearTable&& other) {
        header = my_pool.NewNode();
        header->children[1] = other.header->children[1];
        header->children[0] = other.header->children[0];
        header->color = other.header->color;
        header->father = other.header->father;
        header->size = other.header->size;
        node_count = other.node_count;
        (other.header)->color = 1;
        other.root() = 0;
        other.leftmost() = header;
        other.rightmost() = header;
        other.node_count = 0;
    }  // shallow copy by using move() from<utility>
   private:
    void uniniversal_setup() {
        header = my_pool.NewNode();
        color(header) = 1;
        root() = 0;
        leftmost() = header;
        rightmost() = header;
    }
    link_type clone_node(link_type x) {
        link_type tmp = my_pool.NewNode(x->val);
        tmp->color = x->color;
        tmp->size = x->size;
        tmp->children[0] = tmp->children[1] = 0;
        return tmp;
    }
    link_type __copy(link_type x, link_type p) {  // x,p!=nullptr
        link_type top = clone_node(x);
        top->father = p;
        try {
            if (x->children[1])
                top->children[1] = __copy(x->children[1], top);
            p = top;
            x = left(x);
            while (x != 0) {
                link_type y = clone_node(x);
                p->children[0] = y;
                y->father = p;
                if (x->children[1])
                    y->children[1] = __copy(x->children[1], y);
                p = y;
                x = left(x);
            }
        } catch (const std::exception& e) {
            my_pool.DeleteNode(top);
        }
        return top;
    }

   public:
    // index
    reference operator[](size_type pos) { return *(kth(pos)); }
    const_reference operator[](size_type pos) const { return *(kth(pos)); }
    iterator PubkthIt(size_type k) const { return kth(k); }

   private:
    // basic tools for BST
    iterator kth(size_type k) const {  // k from 0 to node_count
        if (node_count == 0 || k == node_count)
            return header;
        if (k > node_count || k < 0) {
            std::clog << "index out of bounds" << std::endl;
            exit(2000);
        }
        link_type ret = root();
        while (ret != 0) {
            //if(ret->children[0]==0&&k==0)return (iterator)ret;
            if (ret->children[0] != 0) {
                if (k == ret->children[0]->size)
                    break;
                else if (k < ret->children[0]->size) {
                    ret = ret->children[0];
                } else {
                    k -= ret->children[0]->size + 1;
                    ret = ret->children[1];
                }
            } else if (k > 0) {
                --k;
                ret = ret->children[1];
            } else
                break;
        }
        return (iterator)ret;
    }

   public:
    // TODO:front and back operations
    void push_back(value_type value) { push_end(value, true); }
    void push_back(size_type n, value_type value) {
        for (int i = 0; i < n; ++i)
            push_end(value, true);
    }
    void push_back(const_pointer first, const_pointer last) {
        for (const_pointer i = first; i != last; ++i) {
            push_back((*i));
        }
    }
    void push_back(const_iterator first, const_iterator last) {
        for (const_iterator i = first; i != last; ++i) {
            push_back((*i));
        }
    }
    void push_back(iterator first, iterator last) {
        for (iterator i = first; i != last; ++i) {
            push_back((*i));
        }
    }
    void pop_back() {
        if (node_count == 0) {
            std::clog << "pop in an empty container!" << std::endl;
            exit(2004);
        }
        link_type y =
            ReBalanceForErase(rightmost(), root(), leftmost(), rightmost());
        my_pool.DeleteNode(y);
        node_count--;
    }
    void pop_back(size_type n) {
        for (int i = 0; i < n; i++)
            pop_back();
    }
    void push_front(value_type value) { push_end(value, false); }
    void push_front(size_type n, value_type value) {
        for (int i = 0; i < n; ++i)
            push_end(value, false);
    }
    void push_front(const_pointer first, const_pointer last) {
        for (const_pointer i = --last; i != first; --i) {
            push_front((*i));
        }
        push_front((*first));
    }
    void push_front(const_iterator first, const_iterator last) {
        for (const_iterator i = --last; i != first; --i) {
            push_front((*i));
        }
        push_front((*first));
    }
    void push_front(iterator first, iterator last) {
        for (iterator i = --last; i != first; --i) {
            push_front((*i));
        }
        push_front((*first));
    }
    void pop_front() {
        if (node_count == 0) {
            std::clog << "pop in an empty container!" << std::endl;
            exit(2004);
        }
        link_type y =
            ReBalanceForErase(leftmost(), root(), leftmost(), rightmost());
        my_pool.DeleteNode(y);
        node_count--;
    }
    void pop_front(size_type n) {
        for (int i = 0; i < n; i++)
            pop_front();
    }

   private:
    iterator push_end(value_type value, bool situation) {  // 0 front,1 back
        link_type y = header, x = root();
        while (x != 0) {
            y = x;
            x = x->children[situation];
        }
        return __insert(x, y, value, situation);
    }

   private:
    void delete_update(link_type Root) {
        for (; Root != header; Root = Root->father)
            Root->size--;
    }

   private:
    // TODO:basic tools for rotate
    void push_up(link_type node) {
        if (node == nullptr) {
            std::clog << "empty pointer in <push_up>" << std::endl;
            exit(2001);
        }
        node->size = (node->children[0] ? node->children[0]->size : 0) +
                     (node->children[1] ? node->children[1]->size : 0) + 1;
    }
    bool get(link_type node) {
        /*   if (node == null) {
               std::clog << "empty node in <get>" << std::endl;
               exit(2002);
           }
           if (node->father == nullptr || node->father == null) {
               std::clog << "empty father in <get>" << std::endl;
               exit(2003);
           }*/
        return node == node->father->children[1];
    }

   public:
    // basic functions
    size_type size() const { return node_count; }
    size_type max_size() const { return size_type(-1); }
    bool empty() const { return node_count == 0; }
    void swap(LinearTable& other) {
        std::swap(header, other.header);
        std::swap(node_count, other.node_count);
    }
    void clear() {
        dfs_clear(root());
        leftmost() = header;
        root() = 0;
        rightmost() = header;
        node_count = 0;
    }

   private:
    void dfs_clear(link_type node) {
        if (node == nullptr)
            return;
        dfs_clear(node->children[0]);
        dfs_clear(node->children[1]);
        my_pool.DeleteNode(node);
    }

   public:
    // TODO:insert and erase
    iterator insert(iterator position, const value_type& value) {
        iterator return_iterator;
        if (position.node == header->children[0]) {
            return_iterator = push_end(value, false);
        } else if (position.node == header) {
            return_iterator = push_end(value, true);
        } else {
            if (position.node->children[0] == 0) {
                return_iterator = __insert(0, position.node, value, false);              
            } else {
                link_type x = position.node->children[0], y = position.node;
                while (x != 0) {
                    y = x;
                    x = x->children[1];
                }
                return_iterator = __insert(x, y, value, true);
            }
        }
        return return_iterator;
    }
    iterator insert(iterator position, size_type n, const value_type& value) {
        iterator return_iterator = position;
        for (int i = 1; i <= n; i++)
            return_iterator = insert(return_iterator, value);
        return return_iterator;
    }
    iterator insert(iterator position,
                    const_pointer first,
                    const_pointer last) {
        iterator return_iterator = position;
        for (const_pointer i = --last; i != first; --i)
            return_iterator = insert(return_iterator, *i);
        return_iterator = insert(return_iterator, *first);
        return return_iterator;
    }
    iterator insert(iterator position,
                    const_iterator first,
                    const_iterator last) {
        iterator return_iterator = position;
        for (const_iterator i = --last; i != first; --i)
            return_iterator = insert(return_iterator, *i);
        return_iterator = insert(return_iterator, *first);
        return return_iterator;
    }
    iterator insert(iterator position, iterator first, iterator last) {
        iterator return_iterator = position;
        for (iterator i = --last; i != first; --i)
            return_iterator = insert(return_iterator, *i);
        return_iterator = insert(return_iterator, *first);
        return return_iterator;
    }
    iterator erase(iterator position) {
        if (position.node == header) {
            exit(2005);
        }
        iterator return_iterator = position;
        ++return_iterator;
        link_type y =
            ReBalanceForErase(position.node, root(), leftmost(), rightmost());
        my_pool.DeleteNode(y);
        node_count--;
        return return_iterator;
    }
    iterator erase(iterator first, iterator last) {
        if (first == begin() && last == end()) {
            clear();
            return header;
        } else {
            while (first != last)
                erase(first++);
            return last;
        }
    }

   protected:
    iterator __insert(link_type x,
                      link_type y,
                      const value_type& v,
                      bool f_b) {  // 0 left,1 right
        link_type z;
        if (y == header || x != 0 || !f_b) {
            z = my_pool.NewNode(v);
            left(y) = z;
            if (y == header) {
                root() = z;
                rightmost() = z;
            } else if (y == leftmost()) {
                leftmost() = z;
            }
        } else {
            z = my_pool.NewNode(v);
            right(y) = z;
            if (y == rightmost()) {
                rightmost() = z;
            }
        }
        father(z) = y;
        left(z) = 0;
        right(z) = 0;
        link_type tz=y;
        while (tz != header) {
            tz->size++;
            tz = tz->father;
        }
        ReBalance(z, header->father);
        ++node_count;
        return iterator(z);
    }
    void ReBalance(link_type x, link_type& root) {
        x->color = 1;
        while (x != root && x->father->color == true) {
            bool IsFatherRight = get(x->father);
            link_type y = x->father->father->children[!IsFatherRight];
            if (y && y->color == true) {
                x->father->color = 0;
                y->color = 0;
                x->father->father->color = 1;
                x = x->father->father;
            } else {
                if (x == x->father->children[!IsFatherRight]) {
                    x = x->father;
                    Rotate(x, root, IsFatherRight);
                }
                x->father->color = 0;
                x->father->father->color = 1;
                Rotate(x->father->father, root, !IsFatherRight);
            }
        }
        root->color = 0;
    }
    void Rotate(link_type x, link_type& root, bool dir) {  // 0:left,1:right
        link_type y = x->children[!dir];
        x->children[!dir] = y->children[dir];
        if (y->children[dir] != 0) {
            y->children[dir]->father = x;
        }
        y->father = x->father;
        if (x == root)
            root = y;
        else
            x->father->children[get(x)] = y;
        y->children[dir] = x;
        x->father = y;
        push_up(x);
        push_up(y);
    }

    link_type ReBalanceForErase(link_type z,
                                link_type& root,
                                link_type& leftmost,
                                link_type& rightmost) {
   link_type y = z, x = 0,
                  x_parent = 0;  // x is the only child,y is the suf of z
        if (y->children[0] == 0) {
            x = y->children[1];
        } else if (y->children[1] == 0) {
            x = y->children[0];
        } else {
            y = y->children[1];
            while (y->children[0] != 0) {
                y = y->children[0];
            }
            x = y->children[1];
        }
        if (y != z) {
            Node* oyf=y->father;
            z->children[0]->father = y;
            y->children[0] = z->children[0];
            if (y != z->children[1]) {
                x_parent = y->father;
                if (x)
                    x->father = y->father;
                y->father->children[0] = x;
                y->children[1] = z->children[1];
                z->children[1]->father = y;
            } else
            { 
                x_parent = y;
                oyf=y;
            }
            if (root == z) {
                root = y;
            } else
                z->father->children[get(z)] = y;
            
            y->father = z->father;
            y->size=z->size;
            std::swap(y->color, z->color);
            y = z;
            delete_update(oyf);
        } else {
            x_parent = y->father;
            if (x)
                x->father = y->father;
            if (root == z) {
                root = x;
            } else {
                z->father->children[get(z)] = x;
            }
            if (leftmost == z) {
                if (z->children[1] == 0)
                    leftmost = z->father;
                else {
                    leftmost = x;
                    while (leftmost->children[0])
                        leftmost = leftmost->children[0];
                }
            }
            if (rightmost == z) {
                if (z->children[0] == 0)
                    rightmost = z->father;
                else {
                    rightmost = x;
                    while (rightmost->children[1]) {
                        rightmost = rightmost->children[1];
                    }
                }
            }
            delete_update(y->father);
        }

        
        if (y->color != true) {
            while (x != root && (x == 0 || x->color == false)) {
                bool dir = (x == x_parent->children[0]);
                link_type w = x_parent->children[dir];  // w is the uncle
                if (w->color == true) {
                    w->color = false;
                    x_parent->color = true;
                    Rotate(x_parent, root, !dir);
                    w = x_parent->children[dir];
                }
                if ((w->children[0] == 0 || w->children[0]->color == false) &&
                    (w->children[1] == 0 || w->children[1]->color == false)) {
                    w->color = true;
                    x = x_parent;
                    x_parent = x_parent->father;
                } else {
                    if (w->children[dir] == 0 ||
                        w->children[dir]->color == false) {
                        if (w->children[!dir] != 0)
                            w->children[!dir]->color = false;
                        w->color = true;
                        Rotate(w, root, dir);
                        w = x_parent->children[dir];
                    }
                    w->color = x_parent->color;
                    x_parent->color = false;
                    if (w->children[dir])
                        w->children[dir]->color = false;
                    Rotate(x_parent, root, !dir);
                    break;
                }
            }
            if (x != 0)
                x->color = false;
        }
        return y;
    }

   public:
    value_type max(iterator first, iterator last) const {
        int ret = 0x80000000;
        for (auto i = first; i != last; ++i)
            if (*i > ret)
                ret = *i;
        return ret;
    }
    value_type max(const_iterator first, const_iterator last) const {
        int ret = 0x80000000;
        for (auto i = first; i != last; ++i)
            if (*i > ret)
                ret = *i;
        return ret;
    }
    value_type min(iterator first, iterator last) const {
        int ret = 0x7fffffff;
        for (auto i = first; i != last; ++i)
            if (*i < ret)
                ret = *i;
        return ret;
    }
    value_type min(const_iterator first, const_iterator last) const {
        int ret = 0x7fffffff;
        for (auto i = first; i != last; ++i)
            if (*i < ret)
                ret = *i;
        return ret;
    }
    value_type min(iterator first, iterator last, size_type k) const {
        std::vector<value_type> tmp;
        for (auto i = first; i != last; ++i) {
            tmp.push_back(*i);
        }
        std::nth_element(tmp.begin(), tmp.begin() + k, tmp.end());
        return *(tmp.begin() + k);
    }
    value_type max(iterator first, iterator last, size_type k) const {
        std::vector<value_type> tmp;
        for (auto i = first; i != last; ++i) {
            tmp.push_back(*i);
        }
        k = tmp.size() - k - 1;
        std::nth_element(tmp.begin(), tmp.begin() + k, tmp.end());
        return *(tmp.begin() + k);
    }
    value_type min(const_iterator first,
                   const_iterator last,
                   size_type k) const {
        std::vector<value_type> tmp;
        for (auto i = first; i != last; ++i) {
            tmp.push_back(*i);
        }
        std::nth_element(tmp.begin(), tmp.begin() + k, tmp.end());
        return *(tmp.begin() + k);
    }
    value_type max(const_iterator first,
                   const_iterator last,
                   size_type k) const {
        std::vector<value_type> tmp;
        for (auto i = first; i != last; ++i) {
            tmp.push_back(*i);
        }
        k = tmp.size() - k - 1;
        std::nth_element(tmp.begin(), tmp.begin() + k, tmp.end());
        return *(tmp.begin() + k);
    }
    std::vector<value_type> min(iterator first,
                                iterator last,
                                size_type lbound,
                                size_type rbound) const {
        std::vector<value_type> tmp;
        for (auto i = first; i != last; ++i) {
            tmp.push_back(*i);
        }
        std::sort(tmp.begin(), tmp.end());
        std::vector<value_type> result;
        for (int i = lbound; i < rbound; ++i) {
            result.push_back(tmp[i]);
        }
        return result;
    }
    std::vector<value_type> max(iterator first,
                                iterator last,
                                size_type lbound,
                                size_type rbound) const {
        std::vector<value_type> tmp;
        for (auto i = first; i != last; ++i) {
            tmp.push_back(*i);
        }
        std::sort(tmp.begin(), tmp.end(), [](int a, int b) { return a > b; });
        std::vector<value_type> result;
        for (int i = lbound; i < rbound; ++i) {
            result.push_back(tmp[i]);
        }
        return result;
    }
    std::vector<value_type> min(const_iterator first,
                                const_iterator last,
                                size_type lbound,
                                size_type rbound) const {
        std::vector<value_type> tmp;
        for (auto i = first; i != last; ++i) {
            tmp.push_back(*i);
        }
        std::sort(tmp.begin(), tmp.end());
        std::vector<value_type> result;
        for (int i = lbound; i < rbound; ++i) {
            result.push_back(tmp[i]);
        }
        return result;
    }
    std::vector<value_type> max(const_iterator first,
                                const_iterator last,
                                size_type lbound,
                                size_type rbound) const {
        std::vector<value_type> tmp;
        for (auto i = first; i != last; ++i) {
            tmp.push_back(*i);
        }
        std::sort(tmp.begin(), tmp.end(), [](int a, int b) { return a > b; });
        std::vector<value_type> result;
        for (int i = lbound; i < rbound; ++i) {
            result.push_back(tmp[i]);
        }
        return result;
    }

   public:
    // TODO:sort
    void sort(iterator first, iterator last) {
        std::vector<int> tmp;
        for (auto i = first; i != last; ++i) {
            tmp.push_back(*i);
        }
        std::sort(tmp.begin(), tmp.end());
        int j = 0;
        for (auto i = first; i != last; ++i, ++j) {
            *i = tmp[j];
        }
    }
    iterator sorted_insert(const value_type& value) {
        link_type y = header;
        link_type x = root();
        iterator ret;
        while (x != 0) {
            y = x;
            x = (x->val < value) ? right(x) : left(x);
        }
        ret = __insert(x, y, value, (value > (y->val)));
        while (y != header) {
            y->size++;
            y = y->father;
        }
        return ret;
    }
    void sorted_merge(const LinearTable& other) {
        if (this == &other) {
            exit(5000);
        }
        auto it = other.begin();
        auto oit = begin();
        while (it != other.end()) {
            while (oit != end() && *oit < *it) {
                ++oit;
            }
            if (oit == end())
                break;
            insert(oit, *it);
            ++it;
        }
        while (it != other.end()) {
            push_back(*it);
            ++it;
        }
    }

   public:
    void output_all() const {
        std::cout << "all items: ";
        output_dfs(root());
        std::cout << "end" << std::endl;
    }

   private:
    void output_dfs(link_type Root) const {
        if (Root == 0)
            return;
        output_dfs((Root)->children[0]);
        std::cout << (Root)->val << ':'<<Root->size<<' ';
        output_dfs((Root)->children[1]);
    }
};
}  // namespace DS