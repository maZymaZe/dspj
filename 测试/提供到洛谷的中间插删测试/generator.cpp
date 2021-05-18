#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<experimental/random>
using namespace std;
int m,t1,t2,cc,op;
int main(){
    experimental::reseed(time(NULL));
    scanf("%d",&m);
    printf("%d\n",m);
    m-=200000;
    cc=0;
    for(int i=0;i<200000;i++){
        t1=experimental::randint(0,cc);
        t2=experimental::randint(0,1000000);
        cc++;
        printf("1 %d %d\n",t1,t2);
    }
    int w=m/2;
    for(int i=0;i<w;i++){
        op=experimental::randint(0,4);
        if(op>2&&cc>0){
            t1=experimental::randint(0,cc-1);
            cc--;
            printf("2 %d\n",t1);
            continue;
        }
        t1=experimental::randint(0,cc);
        t2=experimental::randint(0,1000000);
        cc++;
        printf("1 %d %d\n",t1,t2);
    }
    m-=w;
    for(int i=0;i<m;i++){
        op=experimental::randint(0,4);
        if(op>1&&cc>0){
            t1=experimental::randint(0,cc-1);
            cc--;
            printf("2 %d\n",t1);
            continue;
        }
        t1=experimental::randint(0,cc);
        t2=experimental::randint(0,1000000);
        cc++;
        printf("1 %d %d\n",t1,t2);
    }
    return 0;
}