#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }

void itoa1(int n, char s[])
 {
     int i, sign;

     if ((sign = n) < 0)  /* çàïèñûâàåì çíàê */
         n = -n;          /* äåëàåì n ïîëîæèòåëüíûì ÷èñëîì */
     i = 0;
     do {       /* ãåíåðèðóåì öèôðû â îáðàòíîì ïîðÿäêå */
         s[i++] = n % 10 + '0';   /* áåðåì ñëåäóþùóþ öèôðó */
     } while ((n /= 10) > 0);     /* óäàëÿåì */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }



int main (int argc, char **argv)
{
int n, e;
char message[2048];//=(char*)malloc(sizeof(char));// ñîîáùåíèå íà ïåðåäà÷ó
char buf[sizeof(message)];
char message1[2048];
char buf1[sizeof(message)];
char buf2[sizeof(message)];
char buf3[sizeof(message)];
int port,ch;
//----------------------------------------------------------------------------
if(argc!=2){
printf("введите порт!\n");
exit(0);
}
    int bytes_read = 0;
    int sock;                 // äåñêðèïòîð ñîêåòà
    int MAX;
    int CryptoText[1000];
    int Tdecrypt[1000];
    int b = 301;
    int c;
    int j = 0;
    int ASCIIcode;
    struct sockaddr_in addr; // ñòðóêòóðà ñ àäðåñîì
    struct hostent* hostinfo;
port = atoi(argv[1]);
    sock = socket(AF_INET, SOCK_STREAM, 0); // ñîçäàíèå TCP-ñîêåòà
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    // Óêàçûâàåì ïàðàìåòðû ñåðâåðà
    addr.sin_family = AF_INET; // äîìåíû Internet
    addr.sin_port = htons(port); // èëè ëþáîé äðóãîé ïîðò...
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");
 if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) // óñòàíîâêà ñîåäèíåíèÿ ñ ñåðâåðîì
    {
        perror("Ïîäêëþ÷åíèå");
        exit(2);
    }
		printf("\nВведите имя(для выхода exit): ");
		//printf("\n");
		gets(message);
  		if (!strcmp(message, "exit")){close(sock);return 0;}
		send(sock, message, sizeof(message), 0); 
	 	bytes_read = recv(sock, buf1, sizeof(message), 0);
		bytes_read = 0;
		bytes_read = recv(sock, buf2, sizeof(message), 0);
    		printf("\nВаш ключ: %s %s\n", buf1, buf2); // ïðèåì
		e = atoi(buf1);
		n = atoi(buf2);
	int f1 = 1,f2 = 0;
while(1){//WHILE <---
//----------------------------------------------------------------------------
    printf("\nВведите сообщение(для выхода:exit): ");
   	printf("\n");
    gets(message);
    if (!strcmp(message, "exit")){close(sock);return 0;}
    printf("\nЗашифрованное сообщение: ");
	if (strcmp(message,"wr") == 0){
		f1 = 1;
		f2 = 0;
	} else
	if (strcmp(message,"dr") == 0){
		f1 =0;
		f2 =1;
	}
	if (f1 == 1){
    		MAX = strlen(message);
		b = 301;
		j = 0;
		while (j != MAX){
			c = 1;
			int i = 0;
			ASCIIcode = message[j]+b;
			while (i<e)
			{
				c = c*ASCIIcode;
				c = c%n;
				i++;
			}
		CryptoText[j] = c;
			b+=1;
			j++;
		}
		j = 0;
		message1[0] = '\0';
		while(j != MAX){
			itoa1(CryptoText[j],buf3);
			strcat(message1,buf3);
			strcat(message1," ");
			j++;
		} strcat(message1,"*");
	printf("\n %s",message1);
    	send(sock, message1, sizeof(message1), 0); // îòïðàâêà ñîîáùåíèÿ íà ñåðâåð
	} else
	if (f2 == 1){
	printf("\nВведите зашифрованное сообщение\n");
		message1[0] = '\0';
		gets(buf3);
	 	while (strcmp(buf3, "exit") != 0)
		{
			strcat(message1,buf3);
			strcat(message1," ");
			gets(buf3);
		};
		strcat(message1,"*");
		 send(sock, message1, sizeof(message1), 0); // îòïðàâêà ñîîáùåíèÿ íà ñåðâåð
	}
    // bytes_read = 0;
   //	printf("Îæèäàíèå ñîîáùåíèÿ\n");
   // bytes_read = recv(sock, buf, sizeof(message), 0);
    //printf("Ïîëó÷åíî %d bytes\tÑîîáùåíèå: %s\n", bytes_read, buf); // ïðèåì ñîîáùåíèÿ îò ñåðâåðà


}//END_WHILE

return 0;

}
