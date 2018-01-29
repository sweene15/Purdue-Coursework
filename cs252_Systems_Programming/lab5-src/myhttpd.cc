#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <dirent.h>
#include <cstdlib>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/stat.h>
#include <dlfcn.h>

const char * usage =
"BAD FORMAT.\n";


int QueueLength = 5;
struct sockaddr_in clientIPAddress;
struct sockaddr_in serverIPAddress;
clock_t startTime;
int requestCount = 0;
char * sortFlag = (char *)malloc(3);
char * openModules[32];
int moduleCount = 0;

// Processes time request
void processTimeRequest( int socket );
void processRequestThread(int socket);
void poolSlave(int socket);
void sort(char *arr[], int n, char* s);
static int myCompare1 (const void * a, const void *b);
static int myCompare2 (const void * a, const void *b);
static int myCompare3 (const void * a, const void *b);
static int myCompare4 (const void * a, const void *b);

void updateStats();

typedef void (*httprunfunc)(int ssock, const char* querystring);


int
main( int argc, char ** argv )
{
  startTime = clock();
  //printf("%lf\n", (double)startTime);
  // Print usage if not enough arguments
  if ( argc < 2 || argc > 3) {
    fprintf( stderr, "%s", usage );
    exit( -1 );
  }
  
  char flag[1];
  int port;
  //GETTING FLAGS
  if( argc > 2){
  flag[0] = argv[1][1];
  port = atoi(argv[2]);
  //printf("FLAG: %c\n", flag[0]);
  }
  // Get the port from the arguments
  else{
    port = atoi( argv[1] );
  }
  // Set the IP address and port for this server
  //struct sockaddr_in serverIPAddress; 
  memset( &serverIPAddress, 0, sizeof(serverIPAddress) );
  serverIPAddress.sin_family = AF_INET;
  serverIPAddress.sin_addr.s_addr = INADDR_ANY;
  serverIPAddress.sin_port = htons((u_short) port);
  
  // Allocate a socket
  int masterSocket =  socket(PF_INET, SOCK_STREAM, 0);
  if ( masterSocket < 0) {
    perror("socket");
    exit( -1 );
  }

  // Set socket options to reuse port. Otherwise we will
  // have to wait about 2 minutes before reusing the sae port number
  int optval = 1; 
  int err = setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, 
		       (char *) &optval, sizeof( int ) );
   
  // Bind the socket to the IP address and port
  int error = bind( masterSocket,
		    (struct sockaddr *)&serverIPAddress,
		    sizeof(serverIPAddress) );
  if ( error ) {
    perror("bind");
    exit( -1 );
  }
  
  // Put socket in listening mode and set the 
  // size of the queue of unprocessed connections
  error = listen( masterSocket, QueueLength);
  if ( error ) {
    perror("listen");
    exit( -1 );
  }
 
  if(strcmp(flag, "f") == 0){
    while(1){
      //printf("F FLAG RECIEVED\n");
       // Accept incoming connections
      //struct sockaddr_in clientIPAddress;
      int alen = sizeof( clientIPAddress );
      int slaveSocket = accept( masterSocket,
			      (struct sockaddr *)&clientIPAddress,
			      (socklen_t*)&alen);

      if ( slaveSocket < 0 ) {
        perror( "accept" );
        exit( -1 );
      }
      updateStats();
      pid_t slave = fork();
      if(slave == 0){
	processTimeRequest(slaveSocket);
	close(slaveSocket);
	exit(EXIT_SUCCESS);
      }
      // Close socket
      waitpid(slave,0,0);
      kill(slave, SIGKILL);
      close( slaveSocket );
     
    }

  }
  else if(strcmp(flag, "t") == 0){
    while(1){
      //printf("T FLAG RECIEVED\n");
      // Accept incoming connections
      //struct sockaddr_in clientIPAddress;
      int alen = sizeof( clientIPAddress );
      int slaveSocket = accept( masterSocket,
			      (struct sockaddr *)&clientIPAddress,
			      (socklen_t*)&alen);

      if ( slaveSocket < 0 ) {
        perror( "accept" );
        exit( -1 );
      }
      updateStats();      
      pthread_t t1;
      pthread_attr_t attr;

      pthread_attr_init(&attr);
      pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM); 

      //printf("CREATING THREAD WITH SOCKET OF %d\n", slaveSocket);
      pthread_create(&t1, &attr, (void * (*)(void
	*))processRequestThread, (void *)slaveSocket);  
      pthread_join(t1, NULL);
      if ( slaveSocket < 0 ) {
        perror( "accept" );
        exit( -1 );
      }
    }
  }
  else if(strcmp(flag, "p")== 0){

    pthread_t tid[5];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    for(int i = 0; i < 5; i++){
      pthread_create(&tid[i], &attr, (void *(*)(void *))poolSlave, (void *)masterSocket);
      //printf("test");
    }
    pthread_join(tid[0], NULL);
  } 
  else {
  
    while ( 1 ) {

      // Accept incoming connections
      //struct sockaddr_in clientIPAddress;
      int alen = sizeof( clientIPAddress );
      int slaveSocket = accept( masterSocket,
			      (struct sockaddr *)&clientIPAddress,
			      (socklen_t*)&alen);

      if ( slaveSocket < 0 ) {
        perror( "accept" );
        exit( -1 );
      }
      updateStats();
 
      // Process request.
      processTimeRequest( slaveSocket );

      // Close socket
      close( slaveSocket );
    }
  }
}
void
poolSlave(int socket){
      while ( 1 ) {

      // Accept incoming connections
      //struct sockaddr_in clientIPAddress;
      int alen = sizeof( clientIPAddress );
      int slaveSocket = accept( socket,
			      (struct sockaddr *)&clientIPAddress,
			      (socklen_t*)&alen);

      if ( slaveSocket < 0 ) {
        perror( "accept" );
        exit( -1 );
      }
      updateStats();
      // Process request.
      processTimeRequest( slaveSocket );

      // Close socket
      close( slaveSocket );
    }

}
void
processRequestThread(int socket){
  //printf("REACHEd WITH SOCKET OF %d\n", socket);
  processTimeRequest(socket);
  close(socket);
}

void
processTimeRequest( int fd )
{
  const int MaxPathLength = 1024;
  char input[MaxPathLength];
  int inLength = 0;
  int n;
  unsigned char newChar;
  unsigned char lastChar = 0;

  //PARSE: "GET /PATH/ HTML1.1" into just the path
  //GET WHOLE LINE, FROM daytime-server.cc
  while(inLength < MaxPathLength && (n = read(fd, &newChar, sizeof(newChar))) > 0 ){
    if(lastChar == '\n' && newChar == '\r') {
      n = read(fd, &newChar, sizeof(newChar));
      inLength-1;
      break;
    }
    input[inLength] = newChar;
    inLength++;
    lastChar = newChar;
  }
  requestCount++;
  //printf("%s\n", input);
  //PARSE OUT DESIRED FILEPATH  
  int spaceFlag = 0;
  char * temp = input;
  char * filePath;
  char * filePathNoKey;
  for(int i = 0; i <= inLength; i++){
    if(input[i] == ' ' && spaceFlag == 0){
      spaceFlag = i;
    }
    else if(input[i] == ' ' && spaceFlag != 0){
      temp = temp + spaceFlag + 2;
      filePath = (char *)malloc(i - spaceFlag - 1);
      *filePath = '\0';
      strncat(filePath, temp, i - spaceFlag - 2);
      //printf("Spaceflag: %d I: %d\n", spaceFlag, i);
      break;
    } 
  }
  //printf("%s\n", filePath);
  //Check Secret Key
  const char * secret_key = "memeMagic";
  char * temp2 = (char * )malloc(strlen(secret_key) + 2);
  *temp2 = '\0';
  strncat(temp2, filePath, strlen(secret_key));
  if(strcmp(temp2, secret_key) != 0){  
    return;
  }
  //Cut the key off
  filePathNoKey = filePath + strlen(secret_key);
  //printf("%s\n", filePath);

  //FIND AND ISOLATE SORT FLAGS
  *sortFlag = '\0';
  char * filePathNoKeyNoFlags = (char *)malloc(strlen(filePathNoKey) + 1);
  *filePathNoKeyNoFlags = '\0';
  for(int i = 0; i < strlen(filePathNoKey); i++){
    if(*(filePathNoKey + i) == '?'){
      //printf("SORT FLAG FOUND\n");
      strncat(sortFlag, filePathNoKey + i + 1, strlen(filePathNoKey) - i - 1); 
      //printf("FLAGS ARE: %s\n", sortFlag);
      strncat(filePathNoKeyNoFlags, filePathNoKey, i);
    }
  }
  if(*filePathNoKeyNoFlags == '\0'){
    //printf("%s\n", filePathNoKey);
    strcat(filePathNoKeyNoFlags, filePathNoKey);
  }
    //printf("%s\n", filePathNoKeyNoFlags);


  //MAP DOC PATH
  size_t cwdMax = 256;
  char *cwd = {0};
  cwd = getcwd(cwd, cwdMax);
  //printf("%s\n", cwd); 
  //Check for /icons and htdocs
  char * temp3 = (char *)malloc(16);
  char * temp4 = (char *)malloc(16);
  char * temp5 = (char *)malloc(16);
  *temp3 = '\0';
  *temp4 = '\0';
  *temp5 = '\0';
  strncat(temp3, filePathNoKeyNoFlags, 6);
  strncat(temp4, filePathNoKeyNoFlags, 7);
  strncat(temp5, filePathNoKeyNoFlags, 8);
  const char * icPath = "/icons";  
  const char * htPath = "/htdocs";
  const char * cgiPath = "/cgi-bin";
  const char * slash = "/";
  char * finalPath = (char *)malloc(MaxPathLength + cwdMax);
  strcpy(finalPath, cwd);
  strcat(finalPath, slash);
  if(strcmp(filePathNoKeyNoFlags, slash) == 0){
    strcat(finalPath, "http-root-dir/htdocs/index.html");
  }else if(strcmp(temp3, icPath) == 0 || strcmp(temp4, htPath) == 0 || strcmp(temp5, cgiPath) == 0){
    strcat(finalPath, "http-root-dir/");
    strcat(finalPath, filePathNoKeyNoFlags); 
  } else {
    strcat(finalPath, "http-root-dir/htdocs");
    strcat(finalPath, filePathNoKeyNoFlags);
  }
  //CGI STUFF
  if(strcmp(temp5, cgiPath) == 0){
    int pipefd[2];
    pipe(pipefd);
    if(fork() == 0){
      setenv("REQUEST_METHOD", "GET", 1);
      setenv("QUERY_STRING", sortFlag, 1);
      const char * header = 
        "HTTP/1.0 200 Document Follows\r\n"
        "Server: Server-type\r\n"
        "\r\n";
      write(fd, header, strlen(header));
      //printf("PATH: %s\n", finalPath);
      //printf("Query: %s\n", sortFlag);

      close(pipefd[0]);
      dup2(pipefd[1], 1);
      close(pipefd[1]);

      char * soCheck = (char *)malloc(16);
      soCheck = finalPath + strlen(finalPath) - 3;
      const char * so = ".so";
      //printf("%s\n", soCheck);
      if(strcmp(soCheck, so) == 0){
        int moduleOpen = 0;
        for(int i = 0; i < moduleCount; i++){
          if(strcmp(finalPath, openModules[i]) == 0){
            moduleOpen = 1;
          }
        }
        if(moduleOpen == 0){
          openModules[moduleCount] = finalPath;
          moduleCount++;
          void * handle = dlopen(finalPath, RTLD_LAZY);
	  httprunfunc f_httprun;
  	  f_httprun = (httprunfunc) dlsym(handle, "httprun");
          f_httprun(fd, sortFlag);  
        }
/*
        void *dlhandle;
        int (*fptr)(int, char *);
        dlhandle = dlopen(finalPath, RTLD_LAZY);
        *(void **)(&fptr) = dlsym(dlhandle, "httprun");
        (void) fptr(fd, sortFlag);
*/
      } else {
        char *argv[] = {finalPath};
        int error = execv(finalPath, argv);
        if(error == -1)
          printf("fuckup\n");
      }
    } else {
      char buffer[1024];
      close(pipefd[1]);
      ssize_t x;
      while(x = read(pipefd[0], buffer, sizeof(buffer))){
	write(fd, buffer, x);
      }
      const char * crlf = "\r\n\r\n";
      write(fd, crlf, strlen(crlf));
    }
  } else {
   //printf("%s\n", finalPath);
   //OPEN AND WRITE IT
  
    const char * header = 
    "HTTP/1.0 200 OK\r\n"
    "Server: type\r\n"
    "Content-type: type\r\n"
    "\r\n";
    write(fd, header, strlen(header));


    //BROWSING DIRECTORYS  
    //ATTEMPT TO OPEN DOC AS A DIRECTORY
    DIR *dir = opendir(finalPath);
    if(dir != NULL){
      struct dirent *entry;
      char* dirEntries[32];
      int count = 0;
      while((entry = readdir(dir))!= NULL){
        if(entry->d_name[0] != '.'){
	  dirEntries[count] = strdup(entry->d_name);
	  count++;
        }
      }  
      closedir(dir);
      const char * dirHeader = 
      "<!Doctype HTML>\n"
      "<html>\n"
      "\t<head>\n"
      "\t\t<style type = \"text/css\"></style>\n"
      "\t\t<title> CS252: HTTP Server</title>\n"
      "\t</head>\n"
      "\t<body>\n";
      const char * dirFooter =
      "\t\t</ul>\n"
      "\t</body>\n"
      "</html>\n";

      //TITLE GENERATION, w/ LIST HEADER
      char * title = (char *)malloc(128);
      *title = '\0';
      const char * titleHeader = "\t\t<h1>Index of ";
      strcat(title, titleHeader);
      strcat(title, finalPath);
      const char * titleFooter = "</h1>\n\n<img src = \"pok3.gif\">\n\n";
      strcat(title, titleFooter);
      write(fd, dirHeader, strlen(dirHeader));
      write(fd, title, strlen(title));

      //Generate Sort options
      char * sortList = (char *)malloc(1024);
      *sortList = '\0';
      const char *nameAscHeader = "\t<A HREF = \"/memeMagic";
      strcat(sortList, nameAscHeader);
      strcat(sortList, filePathNoKeyNoFlags);
      const char *nameDescHeader = "?1\"> Name Asc </A>  <A HREF = \"/memeMagic";
      strcat(sortList, nameDescHeader);
      strcat(sortList, filePathNoKeyNoFlags);
      const char *sizeAscHeader = "?2\"> Name Desc </A>  <A HREF = \"/memeMagic";
      strcat(sortList, sizeAscHeader);
      strcat(sortList, filePathNoKeyNoFlags);
      const char *sizeDescHeader = "?3\"> Size Asc </A>  <A HREF = \"/memeMagic";
      strcat(sortList, sizeDescHeader);
      strcat(sortList, filePathNoKeyNoFlags);
      const char *sizeDescFooter = "?4\"> Size Desc </A>\n";
      strcat(sortList, sizeDescFooter);
      write(fd, sortList, strlen(sortList));
      //free(sortList);



      const char * listHeader = "\t\t<ul>\n";
      write(fd, listHeader, strlen(listHeader));
      free(title);

      //SORTING
      sort(dirEntries, count, sortFlag);
 
      //printf("COUNT: %d\n", count); 
      //GENERATION OF LIST
      for(int i = 0; i < count; i++){
        //printf("ADDING: %s\n", dirEntries[i]);
    	const char *memberHeader = "\t\t<li><A HREF= \"/memeMagic";
        char * listMember = (char *)malloc(128);
        *listMember = '\0';
        strcat(listMember, memberHeader);
        strcat(listMember, filePathNoKeyNoFlags);
        strcat(listMember, slash);
        strcat(listMember, dirEntries[i]);
        const char *memberMiddle = "\"> ";
        strcat(listMember, memberMiddle);
        strcat(listMember, dirEntries[i]);
        const char *memberFooter = "</A>\n";
        strcat(listMember, memberFooter);
        write(fd, listMember, strlen(listMember));
        free(listMember);
      }
      //Generate Parent Link
      const char *parentLink = "\t\t<li><A HREF= \"/memeMagic";
      write(fd, parentLink, strlen(parentLink));
      write(fd, filePathNoKeyNoFlags, strlen(filePathNoKeyNoFlags)- 1);
      const char *parentLinkFoot = "/..\"> Parent Directory</A>\n";
      write(fd, parentLinkFoot, strlen(parentLinkFoot));
      write(fd, dirFooter, strlen(dirFooter));


    } else {
      int fp = open(finalPath, O_RDONLY);
        //if(fp < 0)
          //printf("OPEN FAIL");
      //printf("%s", header);
      //closedir(dir);
      char buf[2048];
      ssize_t x;
      while(x = read(fp, buf, 1024)){
        write(fd, buf, x);
        //printf("%s", (char *)buf);
      }
      close(fp);
    }
    const char * crlf = "\r\n\r\n";
    write(fd, crlf, 4);
  
    //write to log file
    const char *logPath = "/home/u95/sweene15/cs252/lab5-src/http-root-dir/htdocs/logs";
    int log = open(logPath, O_WRONLY|O_APPEND);
    char * newLog = (char *)malloc(128);
    *newLog = '\0';
    const char * newLogHeader = "Source: ";
    strcat(newLog, newLogHeader);
    const char * clientIP = inet_ntoa(clientIPAddress.sin_addr);
    strcat(newLog, clientIP);
    const char * newLogMiddle = "\nDirectory requested: ";
    strcat(newLog, newLogMiddle);
    strcat(newLog, finalPath);
    const char* newline = "\n";
    strcat(newLog, newline);  
    write(log, newLog, strlen(newLog));
    free(newLog);
    close(log);
  }

  free(cwd);
  free(filePath);
  free(temp2);
  free(temp3);
  free(temp4);
  free(temp5);
  free(finalPath);
  free(filePathNoKeyNoFlags);
  //close(fp);
  close(fd);
}

void updateStats(){
  clock_t currentTime = clock();
  double elapsedTime = ((double)(currentTime - startTime)) / CLOCKS_PER_SEC;
  //printf("%lf\n", (double)startTime);
  //printf("%lf\n", (double)currentTime);
  char timeString[256];
  snprintf(timeString, 256, "%lf", elapsedTime);
  char requestString[256];
  snprintf(requestString, 256, "%d", requestCount / 3);
  const char *statPath = "/home/u95/sweene15/cs252/lab5-src/http-root-dir/htdocs/stats";
  int stats = open(statPath, O_WRONLY|O_TRUNC);  
  char * newStat = (char *)malloc(512);
  *newStat = '\0';
  const char * newStat1 =
    "STAT PAGE: \n"
    "NAME: CONNOR SWEENEY\n"
    "ELAPSED TIME: ";
  const char * newStat2 = "\nNUMBER OF REQUESTS: ";
  const char * newStat3 = "\nMIN SERVICE TIME: ";
  const char * newStat4 = "\nMAX SERVICE TIME: ";
  strcat(newStat, newStat1);
  strcat(newStat, timeString);
  strcat(newStat, newStat2);
  strcat(newStat, requestString);
  strcat(newStat, newStat3);
  strcat(newStat, newStat4);
  const char * newline = "\n";
  strcat(newStat, newline);
  write(stats, newStat, strlen(newStat));
  //printf("req count: %d\n", requestCount);
  //printf("time : %f\n",  elapsedTime);
  free(newStat);
  close(stats);
}

void sort( char*arr[], int n, char* sflag){
  int flag = atoi(sflag);
  if(flag == 1){
    qsort(arr, n, sizeof (const char *), myCompare1);
    //printf("flag 1");
    flag = 0;
  }
  else if(flag == 2){
    qsort(arr, n, sizeof (const char *), myCompare2);
    flag = 0;
  }
  else if(flag == 3){
    qsort(arr, n, sizeof (const char *), myCompare3);
    flag = 0;
  }
  else if(flag == 4){
    qsort(arr, n, sizeof (const char *), myCompare4);
    flag = 0;
  }
}
static int myCompare1 (const void * a, const void * b)
{
  return strcmp (*(const char **) a, *(const char **) b);
}
static int myCompare2 (const void * a, const void * b)
{
  return (-1) * strcmp (*(const char **) a, *(const char **) b);
}
static int myCompare3 (const void * a, const void *b)
{
  struct stat stA;
  stat(*(const char **)a, &stA);
  off_t sizeA = stA.st_size;
  struct stat stB;
  stat(*(const char **)b, &stB);
  off_t sizeB = stB.st_size;
  //printf("SIZE OF %s: %jd AND SIZE OF %s: %jd\n", *(const char **)a, (intmax_t)sizeA, *(const char **)b, (intmax_t)sizeB);
  return (int)(sizeA - sizeB);
}
static int myCompare4 (const void * a, const void *b)
{
  struct stat stA;
  stat(*(const char **)a, &stA);
  off_t sizeA = stA.st_size;
  struct stat stB;
  stat(*(const char **)b, &stB);
  off_t sizeB = stB.st_size;
  //printf("SIZE OF %s: %jd AND SIZE OF %s: %jd\n", *(const char **)a, (intmax_t)sizeA, *(const char **)b, (intmax_t)sizeB);
  return (int)(sizeB - sizeA);
}
