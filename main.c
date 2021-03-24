#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 

char encodeRot13(char c);
int indexOf(char c, char* s);
int stringLength(char* s);
char* encodeRot13String(char* s);
char* concatenate(char* str1, char* str2);

int main() 
{ 
    // ftok to generate unique key 
    key_t key = ftok("shmfile",65); 

    printf("%d\n", IPC_CREAT);
    // shmget returns an identifier in shmid 
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
  
    // shmat to attach to shared memory 
    char *str = (char*) shmat(shmid,(void*)0,0); 
  
    printf("Write Data : \n"); 
    scanf("%s", str);
    sprintf(str, encodeRot13String(str));
    printf("Data written in memory: %s\n",str);   
    
    //detach from shared memory  
    sprintf(str, str);
    shmdt(str); 
  
    return 0; 

}

char* encodeRot13String(char* s)
{
    //how big will my output be?
    int length = stringLength(s);
    char* answer = (char*)malloc(length * (int)sizeof(char));
    for(int i = 0; i < length; i++)
    {
        char* charToCat = (char*)malloc(1);
        charToCat[0] = encodeRot13(*(s + i));
        //char charToCat  = encodeRot13(s + i);
        answer = concatenate(answer, charToCat);
    }
    return answer;
}

int stringLength(char* s)
{
    int count = 0;
    while(*s != '\0')
    {
        count++;
        s = s + 1;
    }
    return count;
}

char encodeRot13(char c)
{
    char* alphabet = "abcdefghijklmnopqrstuvwxyz";
    int index = indexOf(c, alphabet);
    //printf("%d\n", index);
    index = (index + 13)%26; //17 + 13 = 30
    //printf("%d\n", index);
    //return alphabet[index];
    return *(alphabet + index);
}

int indexOf(char c, char* s)
{
    int s_length = stringLength(s);
    for(int i = 0; i < s_length; i++)
    {
        if(c  == *(s+i))
        {
            return i;
        }
    }
    return -1;
}

char* concatenate(char* str1, char* str2)
{
    int str1Length = stringLength(str1);
    int str2Length = stringLength(str2);
    int totalLength = str1Length + str2Length;
    char* ans = (char*)malloc(totalLength * (int)sizeof(char));
    for(int i = 0; i < totalLength; i++)
    {
        if(i < str1Length)
        {
            *(ans + i) = *(str1 + i);
        }
        else
        {
            *(ans + i) = *(str2 + (i - str1Length));
        }
    }
    return ans;
}

