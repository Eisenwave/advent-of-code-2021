long f[9],i,k,s;main(){while(scanf("%ld,",&i)>0)++f[i],++s;for(;k<256;++k)i=f[k%9],f[(k+7)%9]+=i,s+=i;printf("%ld",s);}
