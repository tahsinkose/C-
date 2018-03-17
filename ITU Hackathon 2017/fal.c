#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	
	char name1[100];
	char name2[100];
    
    size_t characters;
	int i,result=0,tmp;
    
   

    //printf("Type something: ");
    
    //printf("%zu characters were read.\n",characters);
    
    
   scanf("%s",name1);
   scanf("%s",name2);
   
   characters = strlen(name1);
    
	//printf("You typed: '%s'\n",name1);
	//printf("You typed: '%s'\n",name2);
	for(i=0;i<characters;i++)
	{
		tmp = name1[i] - name2[i];
		result += abs(tmp);
	}
	printf("%d\n",result);
    return(0);
}
