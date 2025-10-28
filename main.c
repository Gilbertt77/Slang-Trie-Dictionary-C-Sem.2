#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define size_char 26
 //why using typedef struct? using typedef struct can make a shorter and more convenient name for the structure.Instead of using 'struct TrieNode' every time we want to declare a variable of this type,we can just write 'TrieNode'. Like giving a nickname to the structure to make the code easier to write and read.
typedef struct TrieNode{ //this function declares the variables that we needed for the program.
    struct TrieNode *children[size_char];//declares an array 'children' of size 'size_char'. each element of the array is a pointer to another 'TrieNode' struct.Represents the children of the current node in the Trie.
    bool last_Word; //declare a boolean variable named 'last_Word' ,used to mark whether the current node that represents the end of a word in the Trie.if the variable is 'true' it tells that the sequence characters from the root node to this node forms a complete word.

    char *description; //declares a pointer named description that points to a character array.
} TrieNode; //this function stores variables , pointers to child nodes , a boolean flag , and a pointer to store additional information.

TrieNode *createNode() { //this function is for creating a new Trie node, initializes the values and returns a pointer to the created node.
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode)); //allocates memory for a new 'TrieNode' using malloc function.the size of the memory allocated is from sizeof(TrieNode).
    if(node){
    	//Initialization , if the allocation is success,continue the function. If fail, malloc returns NULL and this function returns NULL.
        node->last_Word = false; 
        node->description = NULL;
        //if success,it will initialize the new allocated node. last_word flag to 'false' , description pointer to NULL. 
        for (int i = 0; i < size_char; i++) {
            node->children[i] = NULL;//iterates through each of the 'children' array of the new created node , also sets the pointer to NULL.
        }
    }
    return node; //returns a pointer to the new created node. if memorry allocation fail , function will return NULL.
}


int getIndex(char c){ //this function is for calculating the index of a char (range 0-25) or(a-z).
    return (int)(c - 'a');
}//example : char c = 'a' , return 0. char c = 'b' , return 1.

int countWords(const char* description){
    int countt = 0; // Initialize a variable to keep track of the count of words
    int Word = 0; // Initialize a variable to keep track of whether we are currently in a word
    
    // Loop through each char in the sentence until we reach the null terminator ('\0')
	while(*description) 
	{
		// Check if the current char is a letter (either lowercase or uppercase)
        if((*description >= 'a' && *description <= 'z') || (*description >= 'A' && *description <= 'Z')) 
		{
		// If we're not already in a word, increment the word count
            if(!Word) 
			{
                countt++;
                Word = 1; // Set Word to 1 to indicate that we're in a word now
            }
        } 
		else 
		{
			// If the current char is not a letter, we're not in a word
            Word = 0;
        }
        description++; // Move to the next char in the sentence
    }
    return countt; // Return the total count of the words
}


bool Validation_Slang(char *slang){ //this function is to validate or check the given string meets the syarat for a valid slang word.
    if(strlen(slang) < 2) return false; //takes a string 'slang' for input , check the length if the length leess than 2 char , then false.
    
    for (int i = 0; i < strlen(slang); i++){
        if (slang[i] == ' ') return false;//it iterates through each char of the input string.If there was ' ', then it will return false.
    }
    return true;
} //if the input passes the validation , it will return true(valid slang word).


bool Validation_Description(char *description) {
    int count = 0;
    bool inWord = false; // Flag to track if currently in a word

    // Iterate through each char in the description
    for (int i = 0; description[i] != '\0'; i++) {
        // Check if the current char is part of a word
        if (description[i] != ' ') {
            // If not in a word, increment the word count and set inWord flag to true
            if (!inWord) {
                count++;
                inWord = true;
            }
        } else {
            // If the current char is a space and inWord flag is true, set inWord flag to false
            if (inWord) {
                inWord = false;
            }
        }
    }

    // Return true if the count of words is greater than 1, otherwise return false
    return count > 1;
}


void insertSlang_Word(TrieNode *root, char *slang, char *description) { //input parameters
    TrieNode *curr = root;
    
    for (int i = 0; i < strlen(slang); i++) {//it calculates the index for each char in the slang function , using the 'getIndex' function.
        int idx = getIndex(slang[i]);
        if (!curr->children[idx]){ //checks if there is no child node at the index 'idx' in the children array of the current node , if there is no child node at the index , means that the slang word does no exist in the Trie yet.
            curr->children[idx] = createNode();//creates a new node for the char using the createNode() function. Expands the Trie to accomodate the new char of the slang word.
        }
        curr = curr->children[idx]; //updates the 'curr' pointer to point to the new created or existing node. Prepare the 'curr' pointer for the next iteration of the loop.
    }
    curr->last_Word = true; //marks the node as the end of the word by setting the 'last_Word' flag to 'true'.
    if (curr->description) free(curr->description);
    curr->description = strdup(description);
} //stores the description in the 'description' field of the node. If the node already has a description, it will free the previous allocated memory for the description.(before storing the new description).


void addSlang_Word_ToTrie(TrieNode *root) { //input takes a pointer to the root fo the Trie data structure.
    char slang[50];
    char description[100];//declare variable slang and description as char.

    do {
        printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
        scanf("%s", slang);
    } while (!Validation_Slang(slang));//do while loop to repeat the prompt until the user input a valid slang word.Validation performed by Validation_Slang function.(checks the input is longer than 1 char and does not contain any spaces).
    
    	do{
        printf("Input a new slang word description [Must be more than 2 words]: ");
        getchar(); // Clear input buffer
        fgets(description, 100, stdin);//input a description for the slang word
        description[strcspn(description, "\n")] = '\0'; // Remove newline character
	}while(countWords(description) < 3);//do while loop until input is a valid description.Checked by the 'countWords' function.Loop continues until description contains more than 1 word.

    insertSlang_Word(root, slang, description); //if both slang word and description is valid, it calls the insertSlang_Word function to insert the slang word and the description into the Trie data structure.
    printf("\n");
	printf("Successfully released new slang word.\n");
    printf("Press enter to continue...\n");
} //print the output , message confirming that the slang word and description have been successfully added to the Trie.
//this function is for user to input a new slang word and a description , then validates both inputs and then inserts both input to the Trie data structure.

void searchSlang_Word(TrieNode *root, char *slang) { //input parameters.
    TrieNode *curr = root;
    for (int i = 0; i < strlen(slang); i++) {
        int idx = getIndex(slang[i]); // calculates the index to the char by using getIndex function.
        if (!curr->children[idx]) { // checks if there is a child node at the index that we already calculated(children array) of the current node 'curr'.If there is no child node at the index,the slang word does not exist in the Trie.
            printf("There is no word '%s' in the dictionary.\n",slang);//print if there is no child node at the index.
            printf("Press enter to continue...\n");
            return;
        }
        curr = curr->children[idx];//updates the 'curr' pointer to point to the new created or existing node. Prepare the 'curr' pointer for the next iteration of the loop.
    }
    if (curr && curr->last_Word) {
        printf("Slang word: %s\nDescription: %s\n", slang, curr->description);
        printf("Press enter to continue...\n");
    } else {
        printf("There is no word '%s' in the dictionary.\n",slang);//print if there is no child node at the index.
        printf("Press enter to continue...\n");
    } //checks if the node is marked as end of a word to ensure that the full slang word exists in the Trie.
} //this function searches for a given slang word in the Trie data structure, print description if exists and prints the message if the slang word was not found in the Trie.


void searchSlang_Word_InTrie(TrieNode *root){ //input parameter
    char slang[50];
    
    do {
        printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
        scanf("%s", slang); //input the slang word
    } while (!Validation_Slang(slang)); // do while loop until the input is a valid slang word.Performed by Validation_Slang function,checks the input is longer than 1 char and does not contain any spaces.

    searchSlang_Word(root, slang);//calls the searchSlang_Word function for search the word that we input or we entered the slang word in the Trie.
}	//this function prints the description of the slang word if the slang word does exists in the Trie, or it will prints message that tells the slang word was not found.
//this function is for input a slang word then search for the word that we input before in the Trie.

void printAll(TrieNode *node, char *prefix){ //input parameters
    if (node == NULL) return; //it will check the current node, if it is NULL ,then no more nodes to be process,returns from the function.

    if (node->last_Word){
        printf("-%s\n", prefix);//checks the current node is the end of a slang word,last_Word flag is true , if it does then print prefix , it will complete a slang word.

    }

    for (int i = 0; i < size_char; i++) {
        if (node->children[i]) {
        	
            char nextPrefix[50];
            
            sprintf(nextPrefix, "%s%c", prefix, 'a' + i);
            printAll(node->children[i], nextPrefix);
        }//updating the prefix(nextPrefix) string ,then recursive calls the printAll function,current child node as the new current node and the updated variable nextPrefix as the prefix. 
    }//continues until all nodes in the Trie have been traversed. each calls,prints any slang words found along the traversal path.
} //recursive traverses the Trie , print all slang words stored in the Trie, also the description.paths in the Trie from root node to leaf nodes, print slang words when an end of word node is encountered.

void searchPrefix(TrieNode *root, char *prefix) { // input parameters
    TrieNode *curr = root;
    
    for (int i = 0; i < strlen(prefix); i++) {
        int idx = getIndex(prefix[i]); //calculates the index to the char using getIndex function.
        if (!curr->children[idx]) {
            printf("There is no prefix '%s' in the dictionary.\n",prefix);
            printf("Press enter to continue...\n");
            return; //checks if there is a child node at the calculated index in the children array of the current node 'curr'.if there is no child node,means that current index does not exist in the Trie,no words start with the given prefix.
        }
        
        curr = curr->children[idx];
        
    }
    if(curr) {
        printf("Words starts with '%s':\n", prefix);
        printAll(curr, prefix); //call printAll function to print all the slang words starting from the node that represents by the prefix.It recursively print all the words below the current node,print all the words starting with the given prefix.
    } else {
        printf("\n");
    }
} //if there is no slang words found,it will print there is no prefix ... in the dictionary.


void Slang_Word_WithPrefix(TrieNode *root) { //input parameters
    char prefix[50];

    do {
        printf("Input a prefix to be searched: ");
        scanf("%s", prefix);
    } while (!Validation_Slang(prefix)); //input a prefix word, do while loop input until a valid prefix word is entered.Validation by Validation_Slang function, checks the input is longer than one char and does not contain any spaces.

    searchPrefix(root, prefix);//calls the searchPrefix function to search all the slang words in the Trie that start with the entered prefix.
}//prints all slang words starting with the prefix or else prints a message that tells no words start with the given prefix.
//this function is to input a prefix word then searches for all slang words that starting with the prefix in the Trie.

void printAll_Slang(TrieNode *root) { //input parameters
    if (!root) {
        printf("There is no slang word yet in the dictionary.\n");
        printf("Press enter to continue...\n");
        return; //if the root of the Trie is NULL, no words stored. prints the following words below.Return from the function.
    }
    char prefix[50] = "";
    
    printf("List of all slang words in the dictionary:\n"); 
    printAll(root, prefix);// calls the printAll function , pass the root of the Trie and the empty prefix string, recursively traverses the Trie and prints all of the slang words and the description that already been stored.
} //this function is to print all of the slang words that stored in the Trie, if the Trie is empty, it will print a message that tells there is no slang word yet in the dictionary.


void view_All_Slang_Words(TrieNode *root) { //input parameters
    printAll_Slang(root);
} //calls the printAll_Slang function, pass the root of the Trie. For print all slang words that stored in the Trie.


void exit() {
    printf("Thank you... Have a nice day :)\n");
    exit(0); //exit function from stdlib.h library , passing '0' for the exit status.Closing all files,releasing all allocated memory and also returning control to the operating system.
}


int main() {
    TrieNode *root = createNode(); //initializes a Trie data structure by creating a root node that use createNode function.
	
	while(1){ //continously display the menu options and accept user input
		printf("1. Release a new slang word\n");
		printf("2. Search a slang word\n");
		printf("3. View all slang words starting with a certain prefix word\n");
		printf("4. View all slang words\n");
		printf("5. Exit\n");
		int a;
		
		scanf("%d", &a); //input for the choice that user wanted to choose
		
		switch (a){
			case 1:
    		while (true) {
        		addSlang_Word_ToTrie(root);
        		
        		char choice;
        		printf("Do you want to add more slang words? (y/n): ");
        		scanf("%c", &choice);
        		
        		if (choice != 'y' && choice != 'Y') break;
    		};
    			break; //case 1 : add a new slang word and the description to the Trie data structure using addSlang_Word_ToTrie function.Also an option to add more words if you wanted to add more new slang words.
			case 2:
				searchSlang_Word_InTrie(root);
				break; //case 2: to search a slang word in the Trie using the searchSlang_Word_InTrie function.
			case 3:
				Slang_Word_WithPrefix(root);
				break; // case 3: view all of the slang words starting with the given prefix using Slang_Word_WithPrefix function.
			case 4:
				view_All_Slang_Words(root);
				break; //case 4: view all of the slang words that already been stored in the Trie using view_All_Slang_Words function.
			case 5:
				exit();
				break; //case 5 : exiting the program by calling the exit function.
			default:
                printf("Invalid choice. Please enter a valid option.\n"); // if the user's input enters an invalid option(6,7,8,9) , looping and continues to display the menu, will be looping until the user chooses to exit the program.
		}
	}
	return 0;
}
