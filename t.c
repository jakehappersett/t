#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//char path[20];
///////////////// begin linked list stuff ///////////
typedef struct node
{
  char val[50];
  struct node *next;
} node_t;

void printlist(node_t *head)
{
  node_t *current = head;
  int i = 1;
  FILE *fp;
  fp = fopen("test.txt", "w+");
  while (current != NULL)
  {
    printf("%d : %s", i, current->val);
    //make these two seperate functions
    fprintf(fp, "%s", current->val);
    current = current->next;
    i++;
  }
  fclose(fp);
  printf("\n");
}

void push(node_t *head, char val[50])
//adds new item to end
{
  node_t *current = head;
  while (current->next != NULL)
  {
    current = current->next;
  }

  current->next = malloc(sizeof(node_t));
  strcpy(current->next->val, val);
  current->next->next = NULL;
}

int readin(node_t *head)
{
  FILE *fp;
  fp = fopen("test.txt", "r");
  if (fp == NULL)
  {
    fp = fopen("test.txt", "w+");
  }
  int i = 0;
  char buffer[1024];
  while (fgets(buffer, 1024, fp))
  {
    if (i == 0)
    {
      strcpy(head->val, buffer);
      i++;
    }
    else
    {
      push(head, buffer);
      i++;
    }
  }
  fclose(fp);
}
////////////////////// main //////////////////////////

int main(int argc, char *argv[])
{
  // global variable definition
  // strcpy(path,getenv("HOME"));
  // strcat(path,"/.todo");
  //initialize linked list
  node_t *head = NULL;
  head = malloc(sizeof(node_t));
  if (head == NULL)
  {
    return 1;
  }

  //read in old list create new if not
  readin(head);

  int opt;
  while ((opt = getopt (argc, argv, "hlr:a:d:")) != -1)
  {
    switch (opt)
    {
      case 'h':
        printf("usage: [-h | -r | -l | -a | -d]\n"
              "\t-h show this help\n"
              "\t-r {~/.tlist} read file\n"
              "\t-l list\n"
              "\t-a {item} add to list\n"
              "\t-d {number} delete number\n");
              break;
      case 'r': readin(optarg); break;
      case 'l': printlist(head); break;
      case 'a': push(head, optarg); printlist(head); break;
      case 'd': break;
    }
  }
  // readin(head);
  // print_list(head);
  return 0;
}
