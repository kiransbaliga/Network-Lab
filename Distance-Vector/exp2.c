#include <stdio.h>
#include <string.h>
struct gr{
    char lef;
    char rig[10][10];
    int len;
}ol[10],ne[10];
int graind=0,lin;
struct fi{
    char lef;
    char rig[10];
    int len;
}firs[10];
void fir(char ch,int ind,int loop){
    int i,j;
    for(i=0;i<lin;i++){
        if(ne[i].lef==ch){
            for(j=0;j<ne[i].len;j++){
                if((ne[i].rig[j][0]<='z'&&ne[i].rig[j][0]>='a')||ne[i].rig[j][0]=='+'||ne[i].rig[j][0]=='-'||ne[i].rig[j][0]=='*'||ne[i].rig[j][0]=='/'||ne[i].rig[j][0]=='^'){
                    firs[ind].rig[firs[ind].len]=ne[i].rig[j][0];
                    firs[ind].len++;
                }
                else if(ne[i].rig[j][0]=='$'){
                    if(loop=0){
                        firs[ind].rig[firs[ind].len]=ne[i].rig[j][0];
                        firs[ind].len++;
                    }
                    else{
                        fir(ne[i].rig[j][1],ind,1)
                    }
                }
            }
        }
    }
}
void main(){
    int i,j,riind=0;
    for(i=0;i<10;i++){
        ne[i].len=0;
    }
    for(i=0;i<10;i++){
        firs[i].len=0;
    }
    char tem[20];
    scanf("%i",&lin);
    for(i=0;i<lin;i++){
        scanf("%s",tem);
        ne[i].lef=tem[0];
        for(j=3;j<strlen(tem);j++){
            if(tem[j]!='|'){
                ne[i].rig[ne[i].len][riind]=tem[j];
            }
            riind++;
            if(tem[j]=='|' || j==(strlen(tem)-1)){
               riind=0;
               ne[i].len+=1;
            }
        }
    }
    for(i=0;i<lin;i++){
       for(j=0;j<ne[i].len;j++){
         printf("%c->%s\n",ne[i].lef,ne[i].rig[j]);
       }
    }
}
