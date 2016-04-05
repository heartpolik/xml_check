#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

#define test "D:\\Projects\\clion\\xml_valid\\test.xml"

FILE * fp = fopen(test,"r");

bool validFlag = true;

struct element
{
    char tag[255];
    element* next = NULL;
};

element* stack = NULL;

void push(element* head, char* name)  //how can i change parameter 'head' ???
{
    element* tmp = new element;
    tmp->next=head;
    strcpy(tmp->tag,name);
    stack=tmp;   // !!! its WRONG !!!
}

void pop(element* head)
{
    if (head != NULL)
    {
        stack = head->next;
        delete(head);
    }
    else
    {
        validFlag = false;
       // printf("NO ELEMENT\n");
    }
}

void findKey(char* tag , char temp)
{
    tag[0] = temp;
    int i=1;
    while(!feof(fp))
    {
        do{
            temp = fgetc(fp);
            tag[i]=temp;
            if(temp=='>')
            {
                tag[i]='\0';
               // printf("%s>\n",tag);
                return;
            }
            ++i;
            if (temp=='<')
            {
                validFlag = false;
                return;
            };
        }while(temp!=' ');
        tag[i-1]='\0';
        do
        {
            temp = fgetc(fp);
        } while(temp!='>');
        //printf("%s ...>\n",tag);
        return;
    };
    validFlag = false;
}

void read()
{
    char rtag[255];
    while (!feof(fp))
    {
        if (validFlag)
        {
            if (fgetc(fp) == '<')
            {
               // printf("<");
                char tmp = fgetc(fp);
                if (tmp != '/') {
                    findKey(rtag,tmp);
               //     printf("PUSHING!\n");   //here i has found full tag with brackets
                    push(stack,rtag);
                }
                else
                {
               //     printf("/");
                    tmp = fgetc(fp);
                    findKey(rtag, tmp);
               //     printf("COMPARING!");
                    if(!strcmp(stack->tag,rtag))
                    {
               //         printf("CMP IS OK, POPING!\n");
                        pop(stack);
                        continue;
                    }
                    else
                    {
               //         printf("NOT COMPARE!\n");
                        validFlag = false;
                    };
                };

            };

        };

    };
}

int main() {

    read();
    if(validFlag)
    {
        printf("XML is valid");
    }
    else printf("Wrong XML LOL");
    getchar();

    return 0;
}