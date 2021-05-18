void alloc_test_b(){
    std::vector<int> v1={1,2};
    DS::LinearTable a(v1.begin(),v1.end());
    assert(a.size()==2);
    std::vector<long long> v2={1,2};
    DS::LinearTable b(v2.begin(),v2.end());
    assert(b.size()==2);
    std::deque<int> d1={1,2};
    DS::LinearTable c(d1.begin(),d1.end());
    assert(c.size()==2);
}
int main() {
    alloc_test_b();
    return 0;
}
/*
需要支持 使用stl迭代器参与构造 ,size()
类似于
std::vector<int> v1;
DS::LinearTable a(v1.begin(),v1.end());
*/