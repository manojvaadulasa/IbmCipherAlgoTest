#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct initialData
{
	int verifyCount;
	int numberOfWords;
}firstConditionCheckData;

struct initialData initialCheck(char * text,char * key)
{
	/**	I have created a separate function to check the equality of the words as it can be used in both encryption and decryption */
	int countWordsIntext=0,countWordsInKey=0,i=0;
	while(text[i]!='\0')
	{   
		if(text[i]==' ')
		{
			countWordsIntext++;
		}	
		i++;
	}
	i=0;
	while(key[i]!='\0')
	{
		if(key[i]==' ')
		{
			countWordsInKey++;
		}	
		i++;
	}
	i=0;
	if(countWordsIntext!=countWordsInKey)
	{
		firstConditionCheckData.verifyCount=0;
		firstConditionCheckData.numberOfWords=0;
		return firstConditionCheckData;
	}
	else
	{
		firstConditionCheckData.verifyCount=1;
		firstConditionCheckData.numberOfWords=countWordsIntext+1;
		return firstConditionCheckData;
	}
}

int* countOfLettersInEachWord(char *key)
{
	/**	I have created a separate function as it can be used in both encryption and decryption */
	int *arr = calloc(firstConditionCheckData.numberOfWords, sizeof(int)),i=0;
	char *token = strtok(key," ");
	while(token != NULL)
	{
		arr[i]=strlen(token);
		i++;
		token = strtok(NULL," ");
	}
	return arr;
}

void reverseArray(int *arr,int size)
{
	/**	I have created a separate function as it can be used in both encryption and decryption */
	for(int i=0;i<size/2;i++)
	{
		arr[i] = arr[i] + arr[size-1-i];
		arr[size-1-i] = arr[i] - arr[size-1-i];
		arr[i] = arr[i] - arr[size-1-i];
	}
}

char * encrypt(char *plaintext,char *key)
{
	int i=0,j=0;
	/******* 
		Our first step is to verify that the number of words in both the ciphertext and the key is same.
	    If it isn't the same then return an empty string immediately. 
	********/
	if(initialCheck(plaintext,key).verifyCount==0) return "";

	/**	Our second step is to split the key and count the number of letters in each word and store it in an array	****/
	int *arrayForLetterCountOfWords = countOfLettersInEachWord(key);

	/*** Our third step is to reverse the array as it is a constraint given in the problem	*****/
	reverseArray(arrayForLetterCountOfWords,sizeof(arrayForLetterCountOfWords)/sizeof(int));

	/**	Our final step is encryption	*****/
	while(plaintext[i]!='\0')
	{
		if(isupper(plaintext[i]))
		{
			i++;
		}
		else if(plaintext[i]==' ')
		{
			i++;
			j++;
		}
		else
		{
			if(arrayForLetterCountOfWords[j]%2==0)
			{
				plaintext[i]+=arrayForLetterCountOfWords[j];
				if(plaintext[i]>122)
				{
					plaintext[i]-=26;
				}
				i++;
			}
			else
			{
				plaintext[i]-=arrayForLetterCountOfWords[j];
				if(plaintext[i]<97)
				{
					plaintext[i]+=26;
				}
				i++;
			}
		}
	}

	return plaintext;
}

char * decrypt(char *ciphertext,char *key)
{
	int i=0,j=0;
	/******* 
		Our first step is to verify that the number of words in both the ciphertext and the key is same.
	    If it isn't the same then return an empty string immediately. 
	********/
	if(initialCheck(ciphertext,key).verifyCount==0) return "";

	/**	Our second step is to split the key and count the number of letters in each word and store it in an array	****/
	int *arrayForLetterCountOfWords = countOfLettersInEachWord(key);

	/*** Our third step is to reverse the array as it is a constraint given in the problem	*****/
	reverseArray(arrayForLetterCountOfWords,sizeof(arrayForLetterCountOfWords)/sizeof(int));

	/**	Our final step is decryption	*****/
	while(ciphertext[i]!='\0')
	{
		if(isupper(ciphertext[i]))
		{
			i++;
		}
		else if(ciphertext[i]==' ')
		{
			i++;
			j++;
		}
		else
		{
			if(arrayForLetterCountOfWords[j]%2==0)
			{
				ciphertext[i]-=arrayForLetterCountOfWords[j];
				if(ciphertext[i]<97)
				{
					ciphertext[i]+=26;
				}
				i++;
			}
			else
			{
				ciphertext[i]+=arrayForLetterCountOfWords[j];
				if(ciphertext[i]>122)
				{
					ciphertext[i]-=26;
				}
				i++;
			}
		}
	}

	return ciphertext;
}

int main()
{
	char plaintext[] = "Give give",key[] = "bye go",encryptedMessage[]="Gkxg dfsb";
	/****************
		Note:- DO NOT use both the encrypt() and decrypt() functions together. Hence I have commented the encrypt function call here. 
		char* ciphertext= encrypt(plaintext,key);
		printf("%s\n",ciphertext);
	****************/
	char* decryptedMessage = decrypt(encryptedMessage,key);
	printf("%s\n",decryptedMessage);
    return 0;
}