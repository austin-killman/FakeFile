#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include "dataStructures.h"

struct Recipe * allRecipes;
int allRecipeSize = 0;

int main(int a, char** args) {
    char * fileName = "fakefile";
    if( access( fileName, F_OK ) == -1 ) {
        return 0;
    }
    allRecipes= malloc(0);
    
    FILE * file = fopen(fileName,"r");
    int preReqCount=0;
    char character = 'a';
    bool newLineCheck = true;
    bool ignoreLine  = false;
    bool buildRecipe= false;
    bool preReqCheck = false;
    bool firstCommand = false;
    while((character=fgetc(file))!=EOF){
        if(character == '\n'){
            printf("|%d|",preReqCount);
            allRecipes[allRecipeSize-1].preReqCount = preReqCount;
            printf("\n");
            ignoreLine = false;
            newLineCheck = true;
            buildRecipe= false;
            preReqCheck = false;
            firstCommand = true;
            continue;
        }
       
        if(newLineCheck && character=='#'){
            ignoreLine = true;
        }
        if(!ignoreLine && newLineCheck && character != '\t'){
            preReqCount = 0;
            allRecipeSize++;
            allRecipes = realloc(allRecipes,sizeof(struct Recipe)* allRecipeSize);
            buildRecipe = true;
        }

        if(character == '\t'){
            buildRecipe = false;
        }

        if(buildRecipe){
            if(character == ':'){
                preReqCheck = true;
                newLineCheck = false;
                allRecipes[allRecipeSize-1].preReq = false;
                allRecipes[allRecipeSize-1].preReqPath = malloc(0);
                //preReqCount ++;
                continue;
            }

            if(preReqCheck){
                
                if(character == ' '){
                    printf("here\n");
                    allRecipes[allRecipeSize-1].preReqPath = realloc(allRecipes[allRecipeSize-1].preReqPath, sizeof(char *) * (preReqCount+1));
                    allRecipes[allRecipeSize-1].preReqPath[preReqCount] = malloc(sizeof(char));
                    allRecipes[allRecipeSize-1].preReqPath[preReqCount][0] = '\0'; 
                    allRecipes[allRecipeSize-1].preReqCount = 0;
                    preReqCount++;
                }else{
                    
                    allRecipes[allRecipeSize-1].preReq = true;
                    allRecipes[allRecipeSize-1].preReqPath[preReqCount-1] = realloc(allRecipes[allRecipeSize-1].preReqPath[preReqCount-1],(sizeof(allRecipes[allRecipeSize-1].preReqPath[preReqCount-1])) +1);
                    strncat(allRecipes[allRecipeSize-1].preReqPath[preReqCount-1], &character, 1);
                } 
            }
        }else if(!ignoreLine){
            if(firstCommand){
                
            }
        }
        newLineCheck = false;
       
    }
    int d=0;
    while(allRecipes[0].preReqPath[0][d]!='\0')
    {
        printf("%c",allRecipes[0].preReqPath[0][d]);
        d++;
    }
    printf("\n%d\n",allRecipes[0].preReqCount);

    for(int j=0; j<allRecipeSize;j++){
        for (int i = 0; i < allRecipes[j].preReqCount; i++)
        {
            free(allRecipes[j].preReqPath[i]);
        }
        free(allRecipes[j].preReqPath);
    } 
    free(allRecipes);

    fclose(file);
}