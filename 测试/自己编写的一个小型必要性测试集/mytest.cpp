DS::LinearTable container, container_another;
const DS::LinearTable con_container(3, 4);
void push_back_test1() {
    container.clear();
    for (int i = 1; i <= 10; i++) {
        container.push_back(i);
        container.output_all();
    }
}
void push_back_test2() {
    container.clear();
    for (int i = 1; i <= 5; i++) {
        container.push_back(i, i);
        container.output_all();
    }
}
void push_back_test3() {
    container.clear();
    container.push_back(2, 0);
    int a[3] = {1, 2, 3};
    container.push_back(a, a + 3);
    container.output_all();
}
/*void push_back_test6() {
    container.clear();
    container.push_back(2, 0);
    std::vector<int> a={1,2, 3};
    container.push_back(a.begin(),a.end());
    container.output_all();
}*/
void push_back_test4() {
    container.clear();
    container.push_back(2, 0);
    container_another.push_back(3, 3);
    container.push_back(container_another.begin(), container_another.end());
    container.output_all();
}
void push_back_test5() {
    container.clear();
    container.push_back(2, 0);
    container.push_back(con_container.begin(), con_container.end());
    container.output_all();
}
void push_front_test1() {
    container.clear();
    for (int i = 1; i <= 10; i++) {
        container.push_front(i);
        container.output_all();
    }
}
void push_front_test2() {
    container.clear();
    for (int i = 1; i <= 5; i++) {
        container.push_front(i, i);
        container.output_all();
    }
}
void push_front_test3() {
    container.clear();
    container.push_front(2, 0);
    int a[3] = {1, 2, 3};
    container.push_front(a, a + 3);
    container.output_all();
}
void push_front_test4() {
    container.clear();
    container.push_back(2, 0);
    container_another.push_back(3, 3);
    container.push_front(container_another.begin(), container_another.end());
    container.output_all();
}
void push_front_test5() {
    container.clear();
    container.push_back(2, 0);
    container.push_front(con_container.begin(), con_container.end());
    container.output_all();
}
void pop_back_test1() {
    container.clear();
    for (int i = 1; i <= 10; i++) {
        container.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        container.pop_back();
        container.output_all();
    }
}
void pop_back_test2() {
    container.clear();
    for (int i = 1; i <= 10; i++) {
        container.push_back(i);
    }
    for (int i = 1; i <= 4; i++) {
        container.pop_back(i);
        container.output_all();
    }
}
void pop_front_test1() {
    container.clear();
    for (int i = 1; i <= 10; i++) {
        container.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        container.pop_front();
        container.output_all();
    }
}
void pop_front_test2() {
    container.clear();
    for (int i = 1; i <= 10; i++) {
        container.push_back(i);
    }
    for (int i = 1; i <= 4; i++) {
        container.pop_front(i);
        container.output_all();
    }
}
void size_test() {
    container.clear();
    for (int i = 0; i < 5; i++) {
        container.push_back(i);
        std::cout << container.size() << " ";
    }
    for (int i = 0; i < 5; i++) {
        container.pop_back();
        std::cout << container.size() << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < 5; i++) {
        container.push_front(i);
        std::cout << container.size() << " ";
    }
    for (int i = 0; i < 5; i++) {
        container.pop_front();
        std::cout << container.size() << " ";
    }
    std::cout << std::endl;
}
void clear_test() {
    container.clear();
    container.output_all();
    container.push_back(90, 8);
    container.output_all();
    container.clear();
    container.output_all();
}
void swap_test() {
    container.clear();
    container_another.clear();
    container.push_back(3, 1);
    container_another.push_back(3, 2);
    container.output_all();
    container_another.output_all();
    container.swap(container_another);
    container.output_all();
    container_another.output_all();
}
void kth_test() {
    container.clear();
    for (int i = 0; i < 40; i++)
        container.push_back(i);
    for (int i = 0; i < 40; i++)
        std::cout << container[i] << " ";
    std::cout << std::endl;
}
void construct_test() {
    container.clear();
    for (int i = 0; i < 40; i++)
        container.push_back(i);
    const DS::LinearTable con_container_k(container);
    con_container_k.output_all();
    DS::LinearTable container_k(con_container_k);
    container_k.output_all();
    auto p1 = con_container_k.begin(), p2 = con_container_k.end();
    DS::LinearTable container_i(++p1, --p2);
    container_i.output_all();
    auto p3 = container_k.begin(), p4 = container_k.end();
    DS::LinearTable container_j(++p3, --p4);
    container_j.output_all();
    int a[4] = {1, 2, 3, 4};
    DS::LinearTable container_h(a, a + 4);
    container_h.output_all();
    DS::LinearTable container_l(std::move(container_h));
    container_l.output_all();
    std::cout << container_h.size() << std::endl;
}
void begin_end_test() {
    container.clear();
    int a[4] = {1, 2, 3, 4};
    container.push_back(a, a + 4);
    const DS::LinearTable con_container_k(container);
    auto p1 = con_container_k.begin(), p2 = con_container_k.end();
    --p2;
    std::cout << *p1 << " " << *p2 << std::endl;
    auto p3 = container.begin(), p4 = container.end();
    --p4;
    std::cout << *p3 << " " << *p4 << std::endl;
    *p3 = -1, *p4 = -4;
    std::cout << container[0] << " " << container[3] << std::endl;
}
void front_back_test() {
    container.clear();
    int a[4] = {1, 2, 3, 4};
    container.push_back(a, a + 4);
    const DS::LinearTable con_container_k(container);
    std::cout << con_container_k.front() << " " << con_container_k.back()
              << std::endl;
    std::cout << container.front() << " " << container.back() << std::endl;
    container.front() = -1, container.back() = -4;
    std::cout << container[0] << " " << container[3] << std::endl;
}
void insert_test1() {
    container.clear();
    for (int i = 1; i <= 10; i++) {
        container.push_back(i);
    }
    auto it = container.PubkthIt(3);
    for (int i = 15; i <= 25; i++) {
        it = container.insert(it, i);
        container.output_all();
    }
}
void insert_test2() {
    container.clear();
    for (int i = 15; i <= 30; i++) {
        container.push_back(i);
    }
    auto it = container.PubkthIt(5);
    for (int i = 1; i <= 4; i++) {
        it = container.insert(it, i, i);
        container.output_all();
    }
}
void insert_test3() {
    container.clear();
    for (int i = 15; i <= 30; i++) {
        container.push_back(i);
    }
    auto it = container.PubkthIt(5);
    int a[3] = {1, 2, 3};
    for (int i = 1; i <= 3; i++) {
        it = container.insert(it, a, a + 3);
        for (int j = 0; j < 3; j++) {
            a[j] += 100;
        }
        container.output_all();
    }
}
void insert_test4() {
    container.clear();
    for (int i = 15; i <= 30; i++) {
        container.push_back(i);
    }
    auto it = container.PubkthIt(5);
    container_another.push_back(3, 3);
    container.insert(it, container_another.begin(), container_another.end());
    container.output_all();
}
void insert_test5() {
    container.clear();
    for (int i = 15; i <= 30; i++) {
        container.push_back(i);
    }
    auto it = container.PubkthIt(5);
    container.insert(it, con_container.begin(), con_container.end());
    container.output_all();
}
void erase_test1() {
    container.clear();
    for (int i = 1; i <= 10; i++) {
        container.push_back(i);
    }
    auto it = container.PubkthIt(5);
    for (int i = 5; i > 0; i--) {
        it = container.erase(it);
        container.output_all();
    }
}
void erase_test2() {
    container.clear();
    for (int i = 1; i <= 10; i++) {
        container.push_back(i);
    }
    auto it1 = container.PubkthIt(3), it2 = container.PubkthIt(6);
    container.erase(it1, it2);
    container.output_all();
}
void max_test1() {
    int a[10] = {4, 6, 2, 3, 1, 9, 0, 7, 8, 5};
    const DS::LinearTable con_container_k(a, a + 10);
    std::cout << con_container_k.max(con_container_k.begin(),
                                     con_container_k.end())
              << std::endl;
    DS::LinearTable container_k(con_container_k);
    std::cout << container_k.max(container_k.begin(), container_k.end())
              << std::endl;
}
void min_test1() {
    int a[10] = {4, 6, 2, 3, 1, 9, 0, 7, 8, 5};
    const DS::LinearTable con_container_k(a, a + 10);
    std::cout << con_container_k.min(con_container_k.begin(),
                                     con_container_k.end())
              << std::endl;
    DS::LinearTable container_k(con_container_k);
    std::cout << container_k.min(container_k.begin(), container_k.end())
              << std::endl;
}
void max_test2() {
    int a[10] = {4, 6, 2, 3, 1, 9, 0, 7, 8, 5};
    const DS::LinearTable con_container_k(a, a + 10);
    std::cout << con_container_k.max(con_container_k.begin(),
                                     con_container_k.end(), 3)
              << std::endl;
    DS::LinearTable container_k(con_container_k);
    std::cout << container_k.max(container_k.begin(), container_k.end(), 3)
              << std::endl;
}
void min_test2() {
    int a[10] = {4, 6, 2, 3, 1, 9, 0, 7, 8, 5};
    const DS::LinearTable con_container_k(a, a + 10);
    std::cout << con_container_k.min(con_container_k.begin(),
                                     con_container_k.end(), 3)
              << std::endl;
    DS::LinearTable container_k(con_container_k);
    std::cout << container_k.min(container_k.begin(), container_k.end(), 3)
              << std::endl;
}
void min_test3() {
    int a[10] = {4, 6, 2, 3, 1, 9, 0, 7, 8, 5};
    const DS::LinearTable con_container_k(a, a + 10);
    auto v1 = con_container_k.min(con_container_k.begin(),
                                  con_container_k.end(), 4, 7);
    for (int i : v1)
        std::cout << i << ' ';
    std::cout << std::endl;
    DS::LinearTable container_k(con_container_k);
    auto v2 = container_k.min(container_k.begin(), container_k.end(), 4, 7);
    for (int i : v2)
        std::cout << i << ' ';
    std::cout << std::endl;
}
void max_test3() {
    int a[10] = {4, 6, 2, 3, 1, 9, 0, 7, 8, 5};
    const DS::LinearTable con_container_k(a, a + 10);
    auto v1 = con_container_k.max(con_container_k.begin(),
                                  con_container_k.end(), 4, 7);
    for (int i : v1)
        std::cout << i << ' ';
    std::cout << std::endl;
    DS::LinearTable container_k(con_container_k);
    auto v2 = container_k.max(container_k.begin(), container_k.end(), 4, 7);
    for (int i : v2)
        std::cout << i << ' ';
    std::cout << std::endl;
}
void sort_test() {
    int a[10] = {4, 6, 2, 3, 1, 9, 0, 7, 8, 5};
    DS::LinearTable container_k(a, a + 10);
    auto it1 = container_k.PubkthIt(2), it2 = container_k.PubkthIt(7);
    container_k.sort(it1, it2);
    container_k.output_all();
    container_k.sort(container_k.begin(), container_k.end());
    container_k.output_all();
}
void sorted_insert_test() {
    container.clear();
    for (int i = 2; i <= 20; i += 2)
        container.push_back(i);
    for (int i = 1; i <= 21; i += 2)
        container.sorted_insert(i), container.output_all();
}
void sorted_merge_test() {
    container.clear();
    container_another.clear();
    for (int i = 2; i <= 20; i += 2)
        container.push_back(i);
    for (int i = 1; i <= 25; i += 2)
        container_another.push_back(i);
    container.sorted_merge(container_another);
    container.output_all();
    container_another.output_all();
}
void iterator_test1() {
    container.clear();
    for (int i = 1; i <= 10; i++) {
        container.push_back(i);
    }
    auto it = container.begin();
    for (int i = 0; i < 10; i++) {
        std::cout << *(it + i) << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << *(i + it) << " ";
    }
    std::cout << std::endl;
}
void iterator_test2() {
    container.clear();
    for (int i = 1; i <= 10; i++) {
        container.push_back(i);
    }
    auto it = container.end();
    for (int i = 1; i <= 10; i++) {
        std::cout << *(it - i) << " ";
    }
    std::cout << std::endl;
}
void iterator_test3() {
    container.clear();
    for (int i = 1; i <= 10; i++) {
        container.push_back(i);
    }
    DS::LinearTable::iterator its[11];
    its[0] = container.begin();
    for (int i = 1; i <= 10; i++) {
        its[i] = its[i-1] + 1;
    }
    std::cout <<(its[5] < its[10])<< std::endl;
    std::cout << (its[0] > its[1]) << (its[4] >= its[4]) << (its[5] < its[10])
              << (its[2] <= its[0]) << (its[1] != its[3]) << (its[8] == its[9])
              << std::endl;
    std::cout<< (its[0]-its[7])<<' '<< (its[1]-its[0])<<' '<< (its[2]-its[7])<<' '<< (its[3]-its[3])<<std::endl;
}
void debugITR(){
    container.clear();
    for (int i = 1; i <= 100; i++) {
        container.push_back(i);
    }
    DS::LinearTable::iterator its[101];
    auto it = container.begin();
    for (int i = 0; i <= 100; i++) {
        its[i]=it++;
        std::cout<<its[i].getrank().second<<' ';
    }
    std::cout<<std::endl;
    for (int i = 0; i <= 100; i++) {
        std::cout<<(its[i].node)->size<<' ';
    }
}
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
/*void std_sort_test() {
    int a[10] = {4, 6, 2, 3, 1, 9, 0, 7, 8, 5};
    DS::LinearTable container_k(a, a + 10);
    std::sort(container_k.begin(), container_k.end());
    container_k.output_all();
}*/
void itkth_test() {
    int a[10] = {4, 6, 2, 3, 1, 9, 0, 7, 8, 5};
    DS::LinearTable container_k(a, a + 10);
    auto i= container_k.begin();
    i++;
    std::cout<<i[2]<<" "<<i[3]<<std::endl;
}
void foreach_test(){
    DS::LinearTable a;
    for(int i=0;i<10;i++)a.push_back(i);
    for(auto i:a){
        std::cout<<i;
    }
}
