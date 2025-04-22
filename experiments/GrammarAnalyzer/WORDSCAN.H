#include "stdio.h"
#include "string.h"
char prog[80],token[8];
int syn,p,m,n,sum=0;
char ch;
char *rwtab[6]={"begin","if","then","while","do","end"};
void scaner()
{
m=0;
for(n=0;n<8;n++) token[n]=NULL;
ch=prog[p++];
while(ch==' ') ch=prog[p++];
if((ch>='a' && ch<='z') ||(ch>='A' && ch<='Z'))
{
   while((ch>='a' && ch<='z') ||(ch>='A' && ch<='Z')||(ch>='0' && ch<='9'))
   {
    token[m++]=ch;
    ch=prog[p++];
   }
   token[m++]='\0';
   syn=10;
   p=p-1;
   for(n=0;n<6;n++)
   {
    if(strcmp(token,rwtab[n])==0)
    {
     syn=n+1;
     break;
    }
   }
}
else
   if(ch>='0' && ch<='9')
   {
            sum=0;
    while(ch>='0' && ch<='9')
    {
     sum=sum*10+ch-'0';
     ch=prog[p++];
    }
    p=p-1;
             syn=11;
   }
   else
   {
   switch(ch)
   {
    case '<':
                m=0;
     token[m++]=ch;
     ch=prog[p];
     if(ch=='>')
     {
      syn=21;
      token[m++]=ch;
     }
     else if(ch=='=')
     {
      syn=22;
      token[m++]=ch;
     }
     else
     {
      syn=20;
                    p=p-1;
     }
     p=p+1;
     token[m]='\0';
     break;
      case '>':
                m=0;
     token[m++]=ch;
     ch=prog[p++];
     if(ch=='=')
     {
      syn=24;
      token[m++]=ch;
     }
     else
     {
      syn=23;
                    p=p-1;
     }
     break;
    case ':':
                m=0;
     token[m++]=ch;
     ch=prog[p++];
     if(ch=='=')
     {
      syn=18;
      token[m++]=ch;
     }
     else
     {
      syn=17;p=p-1;
     }
     break;
    case '+':syn=13;token[0]=ch;break;
    case '-':syn=14;token[0]=ch;break;
    case '*':syn=15;token[0]=ch;break;
    case '/':syn=16;token[0]=ch;break;
            case ';':syn=26;token[0]=ch;break;
      case '(':syn=27;token[0]=ch;break;
    case ')':syn=28;token[0]=ch;break;
    case '=':syn=25;token[0]=ch;break;
    case '#':syn=0;token[0]=ch;break;
    default:syn=-1;
   }
   }
}