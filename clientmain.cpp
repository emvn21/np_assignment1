
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include<stdbool.h>
#include<unistd.h>
#include <calcLib.h>
#include <arpa/inet.h>
#define MAX 90
#define PORT 5000 
#define SA struct sockaddr 



void error(const char *msg)
{
    perror(msg);
    exit(0);
}
 void func(int sockfd){
    
    
    char str[255];
    char splitStrings[15][15]; 
    int i,j,cnt;
    int dnum1,dnum2;
    float fnum1,fnum2;
    int number_to_send;
    int ans;
    int converted_number;
    float float_to_send;
    float float_converted;
    char st[90];
    char slash[5] = "\\n";
    char final[20];
  
    for(;;)
    {
      memset (str, 0 , 255);
    
	    ans = read(sockfd, str, sizeof(str)); 
        printf("From Server : %s\n", str);
        
        if (strstr(str, "TCP") != NULL) {
        bzero(str, sizeof(str));  
         char msg[6] = "OK\n";
          
          write(sockfd, msg, strlen(msg)); 
          bzero(msg, sizeof(msg)); 
	 
    
    read(sockfd, str, sizeof(str)); 
    
    
    j=0; cnt=0;
    for(i=0;i<=int(strlen(str));i++)
    {
        
        if(str[i]==' '||str[i]=='\0')
        {
            splitStrings[cnt][j]='\0';
            cnt++;  
            j=0;    
        }
        else
        {
            splitStrings[cnt][j]=str[i];
            j++;
        }
    }
   
    for (i=0;i < cnt;i++) {
       
        dnum1 = atoi(splitStrings[1]);
        dnum2 = atoi(splitStrings[2]);
        
        fnum1 = atof(splitStrings[1]);
        fnum2 = atof(splitStrings[2]); 
    }
   
        if ((strcmp(splitStrings[0],"add")) == 0){
            number_to_send = dnum1 + dnum2;
        
            bzero(st, sizeof(st)); 
            
            sprintf(st, "%d\n", number_to_send);
           
            printf("From Server: %s\n", str); 
            if (write(sockfd, st, strlen(st)) < 0)
                 error("ERROR writing to socket");
            printf("Answer back to server: %s\n",st);
            bzero(str, sizeof(str)); 
            if (read(sockfd, final, sizeof(final)) < 0) 
                 error("ERROR reading from socket");

             printf("Responds from Server : %s\n",final);
             break;
            
            }
            
        if ((strcmp(splitStrings[0],"div")) == 0){
            number_to_send = dnum1/dnum2;
             bzero(st, sizeof(st)); 
             sprintf(st, "%d\n", number_to_send);
            printf("From Server: %s\n", str); 
            
            printf("Answer back to server: %s\n",st);
            if (write(sockfd, st, strlen(st)) < 0)
            printf("Error writing to server\n");
              bzero(str, sizeof(str)); 
            
            if (read(sockfd, str, sizeof(str)) < 0){
             error("ERROR reading from socket");
            } 
            printf("Responds Server : %s\n", str);
            break;
            }
            
        
        if ((strcmp(splitStrings[0],"mul")) == 0){
            number_to_send = dnum1*dnum2; 
            bzero(st, sizeof(st)); 
             sprintf(st, "%d\n", number_to_send);
            printf("From Server: %s\n", str); 
           
            printf("Answer back to server: %s\n",st);
            if (write(sockfd, st, strlen(st)) < 0)
            printf("Error writing to server\n");
            
            bzero(str, sizeof(str)); 
            if (read(sockfd, str, sizeof(str)) < 0){
             error("ERROR reading from socket");
            } 
            printf("Responded Server : %s\n",str);
            break;
            }
            
            
        if ((strcmp(splitStrings[0],"sub")) == 0){
            number_to_send = dnum1-dnum2; 
            bzero(st, sizeof(st)); 
             sprintf(st, "%d", number_to_send);
            printf("From Server: %s\n", str); 
           
            strcat(st,"\n");
            printf("Answer back to server: %s\n",st);
            
            if (write(sockfd, st, strlen(st)) < 0)
            printf("Error writing to server\n");
            
            bzero(str, sizeof(str)); 
             
            if (read(sockfd, str, sizeof(str)) < 0){
             error("ERROR reading from socket");
            } 
          
            printf("Responds Server : %s\n", str);
            
            break;
            }

        
        if ((strcmp(splitStrings[0],"fadd")) == 0){
            float_to_send = fnum1 + fnum2; 
            bzero(st, sizeof(st)); 
             sprintf(st, "%f", float_to_send);
            converted_number = htonl(number_to_send);
            printf("From Server: %s\n", str); 
           
            strcat(st,"\n");
            printf("Answer back to server: %s\n",st);
            if (write(sockfd, st, strlen(st)) < 0)
            printf("Error writing to server\n");
            bzero(str, sizeof(str)); 
             
              printf("Responds Server : ");
             if (read(sockfd, str, sizeof(str)) < 0){
             error("ERROR reading from socket");
            } 
            printf("Responds Server : %s\n", str);
           break;
            
            }

            
        if ((strcmp(splitStrings[0],"fdiv")) == 0){
            float_to_send = fnum1/fnum2; // Put your value
            bzero(st, sizeof(st)); 
            sprintf(st, "%f", float_to_send);
            converted_number = htonl(number_to_send);
            printf("From Server: %s\n", str); 
           
            strcat(st,"\n");
            printf("Answer back to server: %s\n",st);
            write(sockfd, st, strlen(st));
            if (write(sockfd, st, sizeof(st)) < 0)
            printf("Error writing to server\n");
            
            bzero(str, sizeof(str)); 
             
             if (read(sockfd, str, sizeof(str)) < 0){
             error("ERROR reading from socket");
            } 
             printf("Responds Server :%s\n ", str);
             
            break;
            }
            
        if ((strcmp(splitStrings[0],"fmul")) == 0){
            float_to_send = fnum1*fnum2; // Put your value
            bzero(st, sizeof(st)); 
            sprintf(st, "%f", float_to_send);
            converted_number = htonl(number_to_send);
            printf("From Server: %s\n", str); 
          
            strcat(st,"\n");
            printf("Answer back to server: %s\n",st);
            
            if (write(sockfd, st, strlen(st)) < 0)
            printf("Error writing to server\n");
            bzero(str, sizeof(str)); 
            
            if (read(sockfd, str, sizeof(str)) < 0){
             error("ERROR reading from socket");
            } 
            printf("Responds Server : %s\n",str);
           break;
            }
           
            
        if ((strcmp(splitStrings[0],"fsub")) == 0){
            float_to_send = fnum1-fnum2; 
            bzero(st, sizeof(st)); 
            sprintf(st, "%f", float_to_send);
            
            printf("From Server: %s\n", str); 
          
            strcat(st,"\n");
            printf("Answer back to server: %s\n",st);
            
            if (write(sockfd, st, strlen(st)) < 0)
            printf("Error writing to server\n");
            bzero(str, sizeof(str)); 
              
             if (read(sockfd, str, sizeof(str)) < 0){
             error("ERROR READING FROM SOCKET");
            } 
              printf("RESPONDS TO SERVER : %s\n", str);
             
            break;
            }
           
 bzero(str, sizeof(str));    
 
 }
 
 else {
 printf("EXITING BECAUSE THE PROTOCOL SEEMS NOT TO BE TCP\n");
 bzero(str, sizeof(str));
 break;
 }
           }
}



int main(int argc, char *argv[]) 
{ 
	int sockfd, connfd, port; 
	struct sockaddr_in servaddr, cli; 
	struct hostent *server;

	char delim[]=":";
	char *Desthost=strtok(argv[1],delim);
        char *Destport=strtok(NULL,delim);
        port = atoi(Destport);
  
        
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("SOCKET CREATION FAILED...\n"); 
		exit(0); 
	} 
	else
		printf("SOCKET CREATED..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr(Desthost); 
	servaddr.sin_port = htons(port); 
	
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("CONNECTION TO SERVER FAILED...\n"); 
		exit(0); 
	} 
	else
		printf("CONNECTED TO SERVER..\n"); 
     
	func(sockfd); 
	close(sockfd); 
} 
