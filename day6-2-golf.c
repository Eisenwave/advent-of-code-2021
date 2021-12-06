j;main(){long f[9]={},i;while(scanf("%lu,",&i)>0)++f[i];for(i=0;i<256;++i)f[(i+7)%9]+=f[i%9];for(i=0;j++<9;)i+=f[j-1];printf("%lu",i);}
