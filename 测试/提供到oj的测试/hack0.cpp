void construct_test_a() {
    int a[4] = {1, 2, 3, 4};
    DS::LinearTable container;
    for (int i = 1; i <= 4; i++)
        container.push_back(i);
    for (int i = 0; i < 4; i++)
        assert(container[i] == a[i]);
    const DS::LinearTable con_container_k(container);
    for (int i = 0; i < 4; i++)
        assert(con_container_k[i] == a[i]);
    DS::LinearTable container_k(con_container_k);
    for (int i = 0; i < 4; i++)
        assert(container_k[i] == a[i]);
    auto p1 = con_container_k.begin(), p2 = con_container_k.end();
    DS::LinearTable container_i(p1, p2);
    for (int i = 0; i < 4; i++)
        assert(container_i[i] == a[i]);
    auto p3 = container_k.begin(), p4 = container_k.end();
    DS::LinearTable container_j(p3, p4);
    for (int i = 0; i < 4; i++)
        assert(container_j[i] == a[i]);
    DS::LinearTable container_h(a, a + 4);
    for (int i = 0; i < 4; i++)
        assert(container_h[i] == a[i]);
    DS::LinearTable container_l(std::move(container_h));
    for (int i = 0; i < 4; i++)
        assert(container_l[i] == a[i]);
    assert(container_h.size() == 0);
}
int main(){
    construct_test_a();
    return 0;
}
/*
文字表述，要求支持容器的各种构造函数
1，默认构造函数
2，拷贝构造函数
3，从其他容器的迭代器构造（包括LinearTable,vector...)
4，从指针构造
5，移动构造

tip：测试数据会涉及到常量容器，以及begin，end函数
*/