#include <cstdio>
int main(){
decltype(0ull)f[9]{},i;
while(scanf("%llu,",&i)>0)++f[i];
for(i=0;i<256;++i)f[(i+7)%9]+=f[i%9];
for(i=0;auto x:f)i+=x;
printf("%llu",i);
}
