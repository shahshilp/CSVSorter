#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "simpleCSVsorter.h"
#include "mergesort.c"

char *strtok_new(char *c, char *delim);
const char* getfield(char* line, int colNum);
int getHeaderNum(char* headerLine, char* colName);

void MergeSortChar(node ** headRef);
void MergeSortInt(node ** headRef);
node* SortedMergeChar(node* a, node* b);
node* SortedMergeInt(node* a, node* b);
void splitIntoSublists(node* sourcePtr, node** frontPtrPtr, node** backPtrPtr);

void printSortedList(node *node, int dataType) 
{ 
  while(node!=NULL) 
  { 
    if(dataType == 0)
    {
      printf("%s ", node->rowLine); 
      node = node->next; 
    }
    else if (dataType == 1)
    {
      printf("%s ", node->rowLine); 
      node = node->next; 
    }
  } 
} 

int main(int argc, char *argv[])
{
  char* headerName = argv[2];
  
  //Store each line
  char *buffer; //Line stored in this variable
  size_t bufsize = 5000;
  buffer = (char *)malloc(bufsize * sizeof(char)); //Allocate space
  size_t characters; //Number of characters read. -1 if end of file
  
  if(headerName == NULL)
  {
    fprintf(stderr, "Header is null \n");
    exit(1);
  }
 
  int dataType;
  
  if (strcmp (headerName, "color") ==0 || //check if string
    strcmp (headerName, "director_name") ==0 ||
    strcmp (headerName, "actor_2_name") ==0 ||
    strcmp (headerName, "genres") ==0 ||
    strcmp (headerName, "actor_1_name") ==0 ||
    strcmp (headerName, "movie_title") ==0 ||
    strcmp (headerName, "actor_3_name") ==0 ||
    strcmp (headerName, "plot_keywords") ==0 ||
    strcmp (headerName, "movie_imdb_link") ==0 ||
    strcmp (headerName, "language") ==0 ||
    strcmp (headerName, "country") ==0 ||
    strcmp (headerName, "content_rating") ==0)
  {
    dataType = 0;
  }
  else if ((strcmp (headerName, "num_critic_for_reviews") ==0 || //check if int
    strcmp (headerName, "duration") ==0 ||
    strcmp (headerName, "director_facebook_likes") ==0 ||
    strcmp (headerName, "actor_3_facebook_likes") ==0 ||
    strcmp (headerName, "actor_1_facebook_likes") ==0 ||
    strcmp (headerName, "gross") ==0 ||
    strcmp (headerName, "num_voted_users") ==0 ||
    strcmp (headerName, "cast_total_facebook_likes") ==0 ||
    strcmp (headerName, "facenumber_in_poster") ==0 ||
    strcmp (headerName, "num_user_for_reviews") ==0 ||
    strcmp (headerName, "budget") ==0 ||
    strcmp (headerName, "title_year") ==0 ||
    strcmp (headerName, "actor_2_facebook_likes") ==0 ||
    strcmp (headerName, "imdb_score") ==0 ||
    strcmp (headerName, "aspect_ratio") ==0 ||
    strcmp (headerName, "movie_facebook_likes") ==0))
  {
    dataType = 1;
  }
  else{
    fprintf(stderr, "No header found \n");
    dataType = -1;
    exit(1);
  }

 
 	//get individual lines of CSV
	getline(&buffer,&bufsize,stdin); //Gets first line, which is the line of column names
  char* headerLine = strdup(buffer); //Store list of columns
  
  if(headerLine == NULL)
  {
    fprintf(stderr, "No lines in CSV file. \n");
    exit(1);
  }
  
  printf("%s", headerLine);
  
  //Last 2 values of the line are new line characters, so replace that with null terminating characters
  size_t len = strlen(headerLine);
  headerLine[len-1] = '\0';
  headerLine[len-2] = '\0';
  
  //getHeaderNum is used to see which column number the data is under
  int headerNum = getHeaderNum(headerLine, headerName);
  
  node * head;
  head = malloc(sizeof(node)); //Initially allocate space for the head node
  
  //Pointer nodes for linking multiple nodes
  node *prev;
  node *curr;
  
  int nodeCounter = 0;
  
  characters = getline(&buffer,&bufsize,stdin); //Gets next line in CSV
	while (characters != -1)
	{ 
    char *tempLine = strdup(buffer);
    char *eachTerm = getfield(tempLine, headerNum); //Gets the data under the specified column
    
    //Create head node if this is the first iteration
    if(nodeCounter == 0)
    {
      head->rowLine = strdup(buffer);
      head->headerName = headerName;
      
      //Check data type and assign to intValue or charValue accordingly
      if(dataType == 0)
      {
        head->charValue = eachTerm;
      }
      else if (dataType == 1)
      {
        head->intValue = atoi(eachTerm);
      }
      
      head->next = NULL;
      
      //printf("%s\n", buffer);
      //printf("%s\n", head->rowLine);
      
      prev = head;
      curr = head;
    }
    else //Create new nodes and link them
    {
      node * tempNode; 
      tempNode = malloc(sizeof(node)); //Allocate more space for each node created
    
      tempNode->rowLine = strdup(buffer);
      tempNode->headerName = headerName;
      
      if(dataType == 0)
      {
        tempNode->charValue = eachTerm;
      }
      else if (dataType == 1)
      {
        tempNode->intValue = atoi(eachTerm);
      }
      
      //tempNode->charValue = eachTerm;
      tempNode->next = NULL;
      
      //printf("%s\n", tempNode->rowLine);
      //printf("%s\n", buffer);
      
      curr = tempNode;
      prev->next = curr;
      prev = tempNode; 
   }

    nodeCounter++;
    characters = getline(&buffer,&bufsize,stdin); //Get the next line and loop again
  }
 
  //Call appropriate merge sort function based on if it is sorting on an int or a char
  if(dataType == 0)
  {
    MergeSortChar(&head);
  }
  else if(dataType == 1)
  {
    MergeSortInt(&head);
  }

  node * finalPtr = head;
  printSortedList(finalPtr, dataType); //Print out each row
  
  return 0;
	
}
