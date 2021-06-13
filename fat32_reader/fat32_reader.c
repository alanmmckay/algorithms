/***********************************************************
 * Name of program: 
 * Authors: 
 * Description: Starter code for project 4
 **********************************************************/

/* These are the included libraries.  You may need to add more. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>


/* Put any symbolic constants (defines)*/
#define True 1  /* C has no booleans! */
#define False 0
#define MAX_CMD 80
#define CD 16
#define DELETED 229
#define LS 0
#define READING 32

/* These are globals.  You set these values once in the main function
   when the program starts. */    
uint16_t bPerSec = 0;
uint8_t  secPer = 0;
uint16_t resSec = 0;
uint8_t  numFats = 0;
uint32_t fatsz32 = 0;
int fd;
uint32_t root_addr = 0;
uint32_t rootCluster = 0;

//Used to help determine where items exist within the FAT:
uint32_t fatReference;
uint32_t fatData;

//Used to help parse through clusters of data:
uint32_t clusterSize = 0;
uint32_t clusterOffset = 0;
uint32_t currentCluster = 2;
uint32_t currentPosition;
uint32_t parsePosition;
uint32_t parseCluster;

//Directory Entry Attributes:
uint32_t init;
uint32_t attr;
char name[12];
uint16_t clusterHi;
uint16_t clusterLo;

//random variables:
uint32_t loopBool;
char data[256];


uint32_t fat_sector_number(int clusterNumber){//gets sector number in respect to the FAT [NOT USED]
    uint32_t value = resSec + ((clusterNumber * 4) / bPerSec);
    return value;
}

uint32_t fat_entity_offset(int clusterNumber){//offset with respect to the FAT
    uint32_t value = (clusterNumber * 4) % bPerSec;
    return value;
}

uint32_t first_sector_of_cluster(int clusterNumber){//first sector number within data
    uint32_t value = ((clusterNumber - 2) * secPer) + (resSec + (numFats * fatsz32));
    return value;
}

uint32_t convert_sector_to_byte_position(int sector){
    uint32_t value = sector * bPerSec;
    return value;
}

void remove_spaces(char *name){
    //function which removes the spaces from a short name
    char newName[12];
    memset(newName,' ', 12);
    int i;
    int j;
    int k;
    for(i=0;i<8;i++){
        if(name[i] != 0x20){
            newName[i] = name[i];
        }else{
            break;
        }
    }
    if(name[8] != 0x20){
        newName[i] = '.';
        i++;
        for(j=8;j<11;j++){
            newName[i] = name[j];
            i++;
        }
    }
    for(k=0;k<12;k++){
        if(newName[k] == ' '){
            newName[k] = '\0';
            break;
        }
    }
    strcpy(name,newName);
}



/********************************************
 * This function displays the image's info
 *******************************************/
void print_info(){
    printf("BPB_BytesPerSec is 0x%x, %i\n",bPerSec, bPerSec);
    printf("BPB_SecPerClus is 0x%x, %i\n",secPer, secPer);
    printf("BPB_RsvdSecCnt is 0x%x, %i\n",resSec, resSec);
    printf("BPB_NumFATs is 0x%x, %i\n",numFats, numFats);
    printf("BPB_FATSz32 is 0x%x, %i\n",fatsz32, fatsz32);
    printf("Root addr is 0x%x\n", root_addr);
    printf("\n");
}


/********************************************
 * This function changes the value of 
 * currentCluster; a variable which is used 
 * by the readData function to know which 
 * cluster within the data region to read.
 *******************************************/
uint32_t accessData(int accessType, char cmd_line[MAX_CMD]){
    
    uint32_t oldCluster = currentCluster;
    int success = 0;
    
    
    //*** TOKEN LOGIC ***///
    //assuming one space....
    char tokenString[80];

    char tokenParameter[2] = " ";
    char *token;

    char *tokenArray[2];
    int tokenCounter = 0;
    
    strcpy(tokenString,cmd_line);

    tokenString[strlen(tokenString) - 1] = '\0';
    token = strtok(tokenString, tokenParameter);

    tokenArray[0] = token;
    token = strtok(NULL, tokenParameter);
    tokenArray[1] = token;
    //*** --- ***//
    
    if(tokenArray[1] != NULL){
        //variables which track the positional data of parsing through the file system:
        currentPosition = convert_sector_to_byte_position(first_sector_of_cluster(currentCluster));
        clusterOffset = 0;
        parsePosition = currentPosition;
        parseCluster = currentCluster;
        
        //directory entry attributes:
        init = 0;
        attr = 0;
        bzero(name, MAX_CMD);
        clusterHi = 0;
        clusterLo = 0;
        
        //variables pertaining to the FAT:
        fatReference = 0;
        fatData = 0;
        
        //conditional switch:
        loopBool = 0;
        
        //for every cluster
        while(True){
            parsePosition = convert_sector_to_byte_position(first_sector_of_cluster(parseCluster)); 
            //for every directory entry
            fatReference = 0;
            clusterOffset = 0;
            fatData = 0;
            //printf("parseCluster: %u\n",parseCluster);
            //printf("parsePosition: %u\n",parsePosition);
            while((clusterOffset < clusterSize) && (loopBool==0)){
                //check first byte:
                lseek(fd,parsePosition, SEEK_SET);
                read(fd,&init,1);
                if((init != 0) && (init != 229)){
                    //check attr attribute:
                    lseek(fd,parsePosition+11,SEEK_SET);
                    read(fd,&attr,1);
                    //accessType is a parameter to this function
                    if((attr == accessType)){
                        lseek(fd,parsePosition,SEEK_SET);
                        read(fd,&name,11);
                        remove_spaces(name);
                        if(strcmp(name,tokenArray[1]) == 0){
                            //move pointer to next position
                            //determine cluster number
                                //set cluster number
                            if((attr == accessType)){
                            lseek(fd,parsePosition+20,SEEK_SET);
                            read(fd,&clusterHi,2);
                            htole16(clusterHi);
                            
                            lseek(fd,parsePosition+26,SEEK_SET);
                            read(fd,&clusterLo,2);
                            htole16(clusterLo);
                            
                            currentCluster = ((clusterHi << 16) + clusterLo);

                            if(currentCluster == 0){
                                if(accessType == READING){//this check makes...
                                    //... sure that an empty file isn't being...
                                    //... read.
                                    loopBool = 1;
                                    break;
                                }
                                currentCluster = 2;
                            }
                            success = 1;
                            //printf("currentCluster: %u\n",currentCluster);
                            break;
                            }else{
                                if(accessType == READING){//this check makes...
                                    //... sure that a directory isn't being...
                                    //... read.
                                    loopBool = 1;
                                    break;
                                }
                            }
                        }
                    }
                }
                
                if(init == 0){
                    loopBool = 1;
                }
                
                clusterOffset = clusterOffset + 32;
                parsePosition = parsePosition + 32;
            }//end for every directory entry loop
            
            if(success == 1){
                //we've found the neccessary entity; we can exit the function
                if(accessType == CD){
                    printf("directory changed");
                }
                return 0;
            }
            
            //time to walk through the FAT table to make sure there aren't more...
            //...clusters to parse through...
            fatReference = (resSec * bPerSec) + fat_entity_offset(parseCluster);
            //printf("%u\n",fatReference);
            lseek(fd,fatReference,SEEK_SET);
            read(fd,&fatData,4);
            fatData = htole32(fatData);
            //printf("%u\n",fatData);
            
            if(fatData == 268435448){
                loopBool = 1;
            }else{
                parseCluster = fatData;
            }
            
            if(loopBool == 1){
                if(accessType == CD){
                    printf("invalid directory");
                }
                return oldCluster;
            }  
        }//end for every cluster loop   
    }
}


/********************************************
 * This function reads data based on what the
 * currentCluster value is set to. It displays
 * the data based on the readType Parameter.
 *******************************************/
void readData(int readType, char cmd_line[MAX_CMD]){
    
    uint32_t oldCluster = currentCluster;
    
    //data is used to display text data:
    memset(data,' ', 12);
    
    //variables which track the positional data of parsing through the file system:
    currentPosition = convert_sector_to_byte_position(first_sector_of_cluster(currentCluster));
    clusterOffset = 0;
    parsePosition = currentPosition;
    parseCluster = currentCluster;
    
    //directory entry attributes:
    init = 0;
    attr = 0;
    bzero(name, MAX_CMD);
    clusterHi = 0;
    clusterLo = 0;
    
    //variables pertaining to the FAT:
    fatReference = 0;
    fatData = 0;
    
    loopBool = 0;
    
    //for every cluster
    while(True){
        parsePosition = convert_sector_to_byte_position(first_sector_of_cluster(parseCluster)); 
        //for every directory entry
        fatReference = 0;
        clusterOffset = 0;
        fatData = 0;
        //printf("parseCluster: %u\n",parseCluster);
        //printf("parsePosition: %u\n",parsePosition);
        while((clusterOffset < clusterSize) && (loopBool==0)){
            //check first byte:
            lseek(fd,parsePosition, SEEK_SET);
            read(fd,&init,1);
            
            if(readType == READING){
                if(init != 0){
                    lseek(fd,parsePosition, SEEK_SET);
                    read(fd,&data,32);
                    printf("%s",data);   
                }
            }
            
            if(readType == LS){
                if((init != 0) && (init != 229)){
                    //check attr attribute:
                    lseek(fd,parsePosition+11,SEEK_SET);
                    read(fd,&attr,1);
                    if((attr == 16) || (attr == 32)){
                        //read the name:
                        lseek(fd,parsePosition,SEEK_SET);
                        read(fd,&name,11);
                        remove_spaces(name);
                        printf("%s\n",name);
                    }
                }
                
            }else if(readType == DELETED){
                if(init == DELETED){
                    //check attr attribute:
                    lseek(fd,parsePosition+11,SEEK_SET);
                    read(fd,&attr,1);
                    if((attr == 16) || (attr == 32)){
                        //read the name:
                        lseek(fd,parsePosition,SEEK_SET);
                        read(fd,&name,11);
                        remove_spaces(name);
                        printf("%s\n",name);
                    }
                }
            }
            
            if(init == 0){
                loopBool = 1;
            }
            
            clusterOffset = clusterOffset + 32;
            parsePosition = parsePosition + 32;
        }//end for every directory entry loop
        
        //time to walk through the FAT table to make sure there aren't more...
        //...clusters to parse through...
        fatReference = (resSec * bPerSec) + fat_entity_offset(parseCluster);
        //printf("%u\n", fat_entity_offset(parseCluster));
        //printf("%u\n",fatReference);
        lseek(fd,fatReference,SEEK_SET);
        read(fd,&fatData,4);
        fatData = htole32(fatData);
        //printf("%u\n",fatData);
        
        if(fatData == 268435448){
            loopBool = 1;
        }else{
            parseCluster = fatData;
        }
        
        if(loopBool == 1){
            break;
        }
    }//end for every cluster loop
}





int main(int argc, char *argv[])
{
	char cmd_line[MAX_CMD];
	/* Parse args and open our image file */
	fd = open("fat32.img", O_RDONLY);
	/* Check to see if it opened successfully */
        if(fd == -1) {
	    perror(argv[1]);
            return -1;
	}

	/* Parse boot sector and get information */

	/* Seek to byte 11 in the file */
	lseek(fd,11, SEEK_SET);

	/* Read and store BPB_BytesPerSec for 2 bytes */
	/* Note: use the & when reading into numbers.  You don't need to
         * use it if you are reading into strings. */
	read(fd, &bPerSec,2);
	bPerSec = htole16(bPerSec); // convert to little endian order

	/* Read and store BPB_SecPerClus for 1 bytes */
	read(fd, &secPer,1);

	/* Read and store BPB_RsvdSecCnt for 2 bytes */
	read(fd, &resSec,2);
	resSec = htole16(resSec);

	/* Read and store BPB_NumFATS for 1 bytes */
	read(fd, &numFats,1);

	/* Seek to byte 36 in the file */
	lseek(fd, 36, SEEK_SET);

	/* Read and store BPB_FATSz32 for 4 bytes */
	read(fd, &fatsz32,4);
	fatsz32 = htole32(fatsz32);
    
    lseek(fd,44, SEEK_SET);
    read(fd, &rootCluster,4);
    rootCluster = htole32(rootCluster);
    currentCluster = rootCluster;
    root_addr = first_sector_of_cluster(currentCluster);
    root_addr = convert_sector_to_byte_position(root_addr);
    clusterSize = secPer * bPerSec;
    
	/* Main loop.  You probably want to create a helper function
       for each command besides quit. */
	while(True) {
        
        /* Zero the command line, just in case */
		bzero(cmd_line, MAX_CMD);

		/* Print the prompt */
		printf("]");

		/* Get input from the user into cmd_line */
		fgets(cmd_line,MAX_CMD,stdin);

		/* Start comparing input */
		if(strncmp(cmd_line,"info",4)==0) {
			print_info();  //TODO: Finish this function!
		}

		else if(strncmp(cmd_line,"volume",6)==0) {
            //need to add a conditional for the case where the volume name does not exist
            char volumeName[12];
            lseek(fd,root_addr, SEEK_SET);
            read(fd, volumeName, 11);
            remove_spaces(volumeName);
            printf("%s\n",volumeName);
		}

		else if(strncmp(cmd_line,"stat",4)==0) {
			printf("Not yet implemented.\n\n");
		}

		else if(strncmp(cmd_line,"cd",2)==0) {
            accessData(CD, cmd_line);
		}

		else if(strncmp(cmd_line,"ls",2)==0) {
            readData(LS, cmd_line);
		}

		else if(strncmp(cmd_line,"deleted",7)==0) {
			readData(DELETED, cmd_line);
		}

		else if(strncmp(cmd_line,"read",4)==0) {
            uint32_t oldCluster = currentCluster;
            uint32_t returnCluster = 0;
			returnCluster = accessData(READING, cmd_line);
            if(returnCluster == 0){
                readData(READING, cmd_line);
            }
            currentCluster = oldCluster;
		}

		else if(strncmp(cmd_line,"quit",4)==0) {
			printf("Quitting.\n\n");
 			break;
		}

		else {
			printf("Unrecognized command.\n\n");
		}

	}
    
	/* Close the file */
	close(fd);

	return 0; /* Success */
}

