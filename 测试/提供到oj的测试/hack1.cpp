void alloc_test_a(){
    int max_level=9e5;
    DS::LinearTable A_container[10];
    for(int i=0;i<10;i++){
        for(int j=0;j<max_level;j++){
            A_container[i].push_back(j);
        }
        for(int j=0;j<max_level;j++){
            A_container[i].pop_back();
        }
        assert(A_container[i].empty());
    }
}
int main() {
    alloc_test_a();
    return 0;
}

/*
要求操作push_back(int val),pop_back(),empty()
tip：单个容器节点数不超过1e6,同一时刻节点数不超过1e6
旨在测试不同allocator的速度、与push_back(int val),pop_back()速度
p.s.基本不作正确性检验
*/