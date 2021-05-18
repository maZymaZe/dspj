void foreach_test(){
    DS::LinearTable a;
    for(int i=0;i<10;i++)a.push_back(i);
    for(auto i:a){
        std::cout<<i;
    }
}
int main() {
    foreach_test();
    return 0;
}
/*
tip:需要支持pushback,及对容器的foreach语法(C11)
stdout:
0123456789
*/