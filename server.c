#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
 int i1 = 0;

typedef struct{
char name[10];
int i2;
}alex;
int sundaram(int n)
{
int *a;
 a = (int*)malloc(n* sizeof(int));
int i, j, k;
memset(a, 0, sizeof(int) * n);
for(i = 1; 3*i+1 < n; i++)
{
for(j = 1; (k = i+j+2*i*j) < n && j <= i; j++)
a[k] = 1;
}

for(i = n-1; i >= 1; i--)
if(a[i] == 0)
{
return (2 * i + 1);
break;
}
free(a);
}

int gcd(int a, int b)
{
int c;
while (b)
{
c = a % b;
a = b;
b = c;
}
return abs(a);
}

 void reverse(char s[])
 {
     int i2, j;
     char c;

     for (i2 = 0, j = strlen(s)-1; i2<j; i2++, j--) {
         c = s[i2];
         s[i2] = s[j];
         s[j] = c;
     }
 }

void itoa1(int n, char s[])
 {
     int i2, sign;

     if ((sign = n) < 0)  /* çàïèñûâàåì çíàê */
         n = -n;          /* äåëàåì n ïîëîæèòåëüíûì ÷èñëîì */
     i2 = 0;
     do {       /* ãåíåðèðóåì öèôðû â îáðàòíîì ïîðÿäêå */
         s[i2++] = n % 10 + '0';   /* áåðåì ñëåäóþùóþ öèôðó */
     } while ((n /= 10) > 0);     /* óäàëÿåì */
     if (sign < 0)
         s[i2++] = '-';
     s[i2] = '\0';
     reverse(s);
 }




int schet (int n)
{
		    if (n != 0)
        return 1 + schet (n/10);
    else
        return 0;
}




int main(int argc, char **argv)
{
   alex alexan[100];
    int sock, listener;       // äåñêðèïòîðû ñîêåòîâ
    struct sockaddr_in addr; // ñòðóêòóðà ñ àäðåñîì
    char buf[4000];       // áóôóð äëÿ ïðèåìà
   char buf1[4000];
	 char buf4[4000];
    int bytes_read;           // êîë-âî ïðèíÿòûõ áàéò
 if(argc!=2){
printf("Введите порт\n");
exit(0);
}

    listener = socket(AF_INET, SOCK_STREAM, 0); // ñîçäàåì ñîêåò äëÿ âõîäíûõ ïîäêëþ÷åíèé
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }

    // Óêàçûâàåì ïàðàìåòðû ñåðâåðà
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    //-addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0) // ñâÿçûâàåìñÿ ñ ñåòåâûì óñòðîéñòâî. Ñåé÷àñ ýòî óñòðîéñòâî lo - "ïåòëÿ", êîòîðîå èñïîëüçóåòñÿ äëÿ îòëàäêè ñåòåâûõ ïðèëîæåíèé
    {
        perror("bind");
        exit(2);
    }

    listen(listener, 2); // î÷åðåäü âõîäíûõ ïîäêëþ÷åíèé
    while(1)
    {
        sock = accept(listener,NULL, NULL); // ïðèíèìàåì âõîäíûå ïîäêëþ÷åíèå è ñîçäàåì îòäåëíûé ñîêåò äëÿ êàæäîãî íîâîãî ïîäêëþ÷èâøåãîñÿ êëèåíòà
        if(sock < 0)
        {
            perror("Ошибка подключения");
            exit(3);
        }
 i1++;
//alexan[i1].i2 = i1;

srand( (unsigned)time( NULL ) );
int p = rand()%100;
int q = rand()%100;
int p_simple = sundaram(p);
int q_simple = sundaram(q);
int n = p_simple*q_simple;
int d, d_simple = 0;
while (d_simple !=1)
{
	d = rand()%100;
	d_simple = gcd (d, ((p_simple-1)*(q_simple-1)));
}
int e = 0, e_simple = 0;
while (e_simple !=1)
{
e += 1;
e_simple = (e*d)%((p_simple-1)*(q_simple-1));
}
bytes_read = recv(sock, buf1, 2048, 0); // ïðèíèìàåì ñîîáùåíèå îò êëèåíòà
int j7 = 0;
int ss = 0;
do
{
 if(strcmp(alexan[j7].name,buf1) == 0){
	 printf("Пользователь вернулся %d - %s\n", alexan[j7].i2, buf1);
	ss = 1;
	break;
	}
 j7++;
}while (j7 != i1);
j7=0;
if (ss==0){
while( alexan[j7].i2 != 0)
	j7++;
alexan[j7].name[0]='\0';
strcat(alexan[j7].name,buf1);
alexan[j7].i2 = j7+1;
 printf("Пользователь подключился %d - %s\n", alexan[j7].i2, alexan[j7].name);
}
switch(fork())
{
case -1:
 perror("fork");
 break;
case 0:
close(listener);
 //bytes_read = recv(sock, buf1, 2048, 0); // ïðèíèìàåì ñîîáùåíèå îò êëèåíòà
// if(bytes_read <= 0) break;
itoa1(e,buf);
send(sock, buf, bytes_read, 0);
itoa1(n,buf);
send(sock, buf, bytes_read, 0);
        while(1)
        {
        //    printf("Îæèäàåì ñîîáùåíèå...\n");
            bytes_read = recv(sock, buf, 4000, 0); // ïðèíèìàåì ñîîáùåíèå îò êëèåíòà
	   printf("Пользователь %s - %d \tВвел сообщение:%s\n", buf1,j7+1, buf);
            if(bytes_read <= 0) break;
	 	int j1 = 0;
		int i3 = 0;
		int j5 = 0;
		int CryptoText[10000];
		int Tdecrypt[10000];
		char buf2[10];
		do{
			if (buf[j1] == ' ')
			{
				CryptoText[i3] = atoi(buf2);
				i3++;
				j5=0;
				buf2[0]='\0';
				buf2[1]='\0';
				buf2[2]='\0';
				buf2[3]='\0';
				buf2[4]='\0';
				buf2[5]='\0';
				buf2[6]='\0';
			} else{
			buf2[j5] = buf[j1];
			j5++;
			}
			j1++;

		}while (buf[j1] != '*');
		int b = 301;
		int m;
		int i4;
		j1 = 0;
		while (j1 != i3)
		{

			m = 1;
			i4 = 0;
			while (i4<d)
			{
				m = m*CryptoText[j1];
				m = m%n;
				i4++;
			}
			m = m-b;
			Tdecrypt[j1] = m;
			b+=1;
			j1++;
		}
		j1 = 0;
		while (j1 != i3)
		{
			 buf4[j1]=Tdecrypt[j1];
			j1++;

		}
		j1 = 0;
		printf("\n %s \n", buf4);
		while (i3 != j1){
			buf4[j1]='\0';
			j1++;
		}
          //  printf("Îòïðàâëÿþ ïðèíÿòîå ñîîáùåíèå êëèåíòó\n");
         //   send(sock, buf, bytes_read, 0); // îòïðàâëÿåì ïðèíÿòîå ñîîáùåíèå êëèåíòó
        }

        close(sock); // çàêðûâàåì ñîêåò
       break;
default:
close(sock);
}
    }

    return 0;
}
