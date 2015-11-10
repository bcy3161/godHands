#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <unistd.h>
 
#define SA      struct sockaddr
#define MAXLINE 4096
#define MAXSUB  500
 
 
#define LISTENQ         1024
 
extern int h_errno;
 
const char *apikey = "AIzaSyDWAJlxoBRj38lQ6zZZMOGwMT6dI1436iI";
 
ssize_t process_http(int sockfd, char *host, char *page, char *poststr)
{
    char sendline[MAXLINE + 1], recvline[MAXLINE + 1];
    ssize_t n;
    snprintf(sendline, MAXSUB,
            "POST %s HTTP/1.0\r\n"
            "Host: %s\r\n"
            "Content-type: application/json\r\n"
            "Authorization:key=%s\r\n"
            "Content-length: %d\r\n\r\n"
            "%s", page, host, apikey, strlen(poststr), poststr);
 
    printf("sendline : \n%s\n",sendline);
    write(sockfd, sendline, strlen(sendline));
    while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = '\0';
        printf("%s", recvline);
    }
    return n;
 
}
 
int main(void)
{
    int sockfd;
    struct sockaddr_in servaddr;
 
    char **pptr;
    char *hname = "gcm-http.googleapis.com";
    char *page = "/gcm/send";
    char *poststr = "{ \"data\": {\"messageEY\": \"oh my goodness\" }, \"to\" : \"dtP7UMbNE4w:APA91bFJLX4A1sMc_S1Vcro54cYgoNToI9KKGpWKXiKh3YeNG7_GG7kbU3fiWHSX_JLfouZLgYkDUb1HS_WuPJB_5rpt_nkq7x7eY5pVW6Uko95sePNFaFR0SvKxpJGZQqO1SjOxqPwq\"}\r\n";
 
 
 
    char str[50];
    struct hostent *hptr;
    if ((hptr = gethostbyname(hname)) == NULL) {
        fprintf(stderr, " gethostbyname error for host: %s: %s",
                hname, hstrerror(h_errno));
        exit(1);
    }
    printf("hostname: %s\n", hptr->h_name);
    if (hptr->h_addrtype == AF_INET
            && (pptr = hptr->h_addr_list) != NULL) {
        printf("address: %s\n",
                inet_ntop(hptr->h_addrtype, *pptr, str,
                    sizeof(str)));
    } else {
        fprintf(stderr, "Error call inet_ntop \n");
    }
 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(80);
    inet_pton(AF_INET, str, &servaddr.sin_addr);
 
    printf("connection...\n");
    connect(sockfd, (SA *) & servaddr, sizeof(servaddr));
    printf("process http...\n---------------------------\n%s\n----------------------\n",poststr);
    process_http(sockfd, hname, page, poststr);
    close(sockfd);
    exit(0);
 
}
