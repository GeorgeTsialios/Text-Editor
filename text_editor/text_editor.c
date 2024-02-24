#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define M 18

struct listelement{
char word[M];
struct listelement *next;
};
typedef struct listelement Listelement;
typedef Listelement *Listelement_ptr;
typedef Listelement *List;

int get_choice(void);
/* 1 */
void clear_list(List *mylist);
Listelement_ptr createnewelement(char word[M]);
void addtolist(List* mylist,Listelement_ptr element_ptr);
void get_file_name(List *mylist);
void get_file_text(char name[M+5],List *mylist);
void report_list(List const mylist);
/* 2 */
void get_voc(List *mylist);
/* 4 */
void ask_file_name(List mylist);
void save_text(List mylist,char name[M]);
void freport_list(List mylist,FILE *file_ptr);
/* 5 */
void stat_words_len_histogram(List mylist,int count[M][2]);
void print_histogram(int x[M][2]);
int stat_number_words(List mylist);
int stat_num_diff_words(List mylist);
int stat_number_chars(List mylist);
void show_statistics(List mylist,int c[M][2]);
void ask_stats_name(List mylist,int c[M][2]);
void save_stats(char name[20],List mylist,int c[M][2]);
void fprint_histogram(FILE *f_ptr,int x[M][2]);
/* 6 */
int search_vocabulary(Listelement_ptr iterator,List vocab);
int get_correction_choice();
void replace_word(Listelement_ptr toreplace_ptr);
void add_vocabulary(Listelement_ptr toadd_ptr,List *vocab);


int main()
{
int a,b,count[M][2],d,e;
List whole_text=NULL,vocabulary=NULL;
Listelement_ptr iterator;
printf("Loading Vocabulary. Please wait for a few seconds...\n");
get_voc(&vocabulary);

for(a=1; a!=0;)
 {
  b=get_choice();
  switch (b)
  {
    case 1: 
            
            clear_list(&whole_text);
              
            get_file_name(&whole_text);
            printf("\n\n FILE TEXT:\n");
            report_list(whole_text);
            break;
    
    case 2:
    	    printf("\n\n VOCABULARY:\n");
    	    report_list(vocabulary);
    	    break;
    	    
    case 3:  
             iterator=whole_text;
             printf("\n You have selected to correct your text. The correction process begins.\n"); 
             for (d=search_vocabulary(iterator,vocabulary);  iterator!=NULL; d=search_vocabulary(iterator,vocabulary))
             {
            
	     
    	     if (d>0)
    	       {
    	       if(iterator->next==NULL)
    	       {
		 printf("\n Correction process is over.");
		 printf("\n This is your corrected text:\n");
		 report_list(whole_text);
		 break;
	       }
    	       else
    	       {
    	       iterator=iterator->next;
    	       continue;
               }
               }
    	     if (d==0)
    	       {
    	       	printf("\n The word '%s' which is found in your text text does not exist in the vocabulary."
    	       	" What do you want to do?\n",iterator->word);
	        e=get_correction_choice();
	
	        
		if (e==1)
		 {
		  replace_word(iterator);
		  continue;
	         }
		  
		if (e==2)
		{
		  add_vocabulary(iterator,&vocabulary);
		  continue;	
		}
		  
		if (e==3)
		    {
		     if(iterator->next!=NULL)
		           {
		           iterator=iterator->next;
		           continue;
		           }
		     else
		         {
		           printf("\n Correction process is over.");
		           printf("\n This is your corrected text:\n");
		           report_list(whole_text);
		           break;	
			 }
		    }
		if (e==4)
		    {
		   printf("\n You have selected to exit the correction process.");
		   printf("\n This is your text so far:\n");
		   report_list(whole_text);
		   break;
	            }
		  
	       }
             }
	     printf("\n You are taken back to the main menu.\n");
    	     break;	
    	    
    case 4: 
            if (whole_text!=NULL)
                ask_file_name(whole_text);
                
    	    else 
    	       printf("\n Your text is empty. You are taken back to the main menu.\n");
    	    break;
    	    
    case 5:  
            stat_words_len_histogram(whole_text,count);
    	    show_statistics(whole_text,count);
    	    ask_stats_name(whole_text,count);
    	    break;
    	    
    case 6:
    	    printf("\n You have selected to quit the program.\n");
    	    a=0;
    	    break;
   
    default:
    	    printf("\n You did not select one of the existing options. Please try again.\n");
    	    break; 
  }
 }
return 0;
}

int get_choice(void)
{
int x;
printf("\n MAIN MENU\n");
printf("\n Type:\n 1 to enter a text\n 2 to see the vocabulary\n 3 to correct the text you entered\n 4 to save your corrected text" 
         " to a file\n 5 to show & save the statistics of your text\n 6 to quit the program\n");
  printf("\n Type here:");
  scanf("%d",&x);
return x;
}

Listelement_ptr createnewelement(char word[M])
{
Listelement_ptr newelement_ptr;

newelement_ptr=malloc(sizeof (Listelement));
strcpy(newelement_ptr->word,word);
newelement_ptr->next=NULL;

return newelement_ptr;
}

void addtolist(List *mylist,Listelement_ptr element_ptr)
{
Listelement_ptr iterator=*mylist;

if (*mylist==NULL)
    {
    *mylist=element_ptr;
    return;
    }

     for (; iterator->next!=NULL; iterator=iterator->next) ;
     iterator->next=element_ptr;
}

void get_file_name(List *mylist)
{
char file_name[M+5];
printf("\n Please do the following:\n 1)Write your text in a .txt type file.\n 2)Place the file in the"
" text_editor folder.\n 3)Write here your file's name (please do not use spaces):");
scanf("%s",file_name);
strcat(file_name,".txt");
get_file_text(file_name,mylist);
}

void get_file_text(char name[M+5],List *mylist)
{
FILE *file_ptr;
char word[M];
Listelement_ptr element_ptr;
file_ptr=fopen(name,"rt");

if (file_ptr==NULL)
   {   
    printf("\n Can not find file named: %s\n",name);
    printf(" Try again!\n");
    get_file_name(mylist);
   }

while( fscanf(file_ptr,"%17s",word)!=EOF )
    {
      element_ptr=createnewelement(word);
      addtolist(mylist,element_ptr);
    }
fclose(file_ptr);
}

void report_list(List const mylist)
{
Listelement_ptr iterator=mylist;
if (mylist==NULL)
  printf("\nYour file is empty.");
printf("\n");
for(; iterator!=NULL; iterator=iterator->next)
    printf("%s ",iterator->word);
printf("\n");
}

void get_voc(List *mylist)
{
FILE *file_ptr;
char word[M];
Listelement_ptr element_ptr;
file_ptr=fopen("englishWords.txt","rt");

while( fscanf(file_ptr,"%17s",word)!=EOF )
    {
      element_ptr=createnewelement(word);
      addtolist(mylist,element_ptr);
    }
fclose(file_ptr);
}

void ask_file_name(List mylist)
{
char f_name[M];
printf("\n Your corrected text will now be saved in a new file.\n Please name"
" this new file (do not use spaces):");
scanf("%s",f_name);
strcat(f_name,".txt");
save_text(mylist,f_name);
}

void save_text(List mylist,char name[M])
{
FILE *file_ptr;
file_ptr=fopen(name,"wt");
freport_list(mylist,file_ptr);
fclose(file_ptr);
printf("\n Your corrected text has been saved in a file named '%s'",name);
printf("\n It is located inside the text_editor folder.\n");
}

void freport_list(List mylist,FILE *file_ptr)
{
Listelement_ptr iterator=mylist;

for(; iterator!=NULL; iterator=iterator->next)
    fprintf(file_ptr,"%s ",iterator->word);
    
fprintf(file_ptr,"\n");
}

void stat_words_len_histogram(List mylist,int count[M][2])
{
int i;
Listelement_ptr iterator;

for (i=0; i<M; i++)
   {
   count[i][0]=i;
   count[i][1]=0;
   }

for (iterator=mylist; iterator!=NULL; iterator=iterator->next)
    {
     if (strlen(iterator->word)<=17)
        count[strlen(iterator->word)][1]++;
    }
}

void print_histogram(int x[M][2])
{
int i,j,max=0;
for (i=1; i<M; i++)
  {
    if (x[i][1]>max)
      max=x[i][1];
  }

if (max<=100)
{
printf("\n \t\tWord Length Histogram:\n\n");
   for (i=1; i<M; i++)
   {
     printf("Number of words with length = %2d in your text : %d ",x[i][0],x[i][1]);
     for (j=0; j<x[i][1]; j++)
       printf("*");
     printf("\n");
   } 
}
if (100<max && max<1000)
{
printf("\n \t\tWord Length Histogram:\n\n");
   for (i=1; i<M; i++)
   {
     printf("Number of words with length = %2d in your text : %d ",x[i][0],x[i][1]);
     for (j=0; j<x[i][1]/10; j++)
       printf("*");
     printf("\n");
   } 	
}
if (max>=1000)
{
printf("\n \t\tWord Length Histogram:\n\n");
   for (i=1; i<M; i++)
   {
     printf("Number of words with length = %2d in your text : %d ",x[i][0],x[i][1]);
     for (j=0; j<x[i][1]/100; j++)
       printf("*");
     printf("\n");
   } 		
}
}

int stat_number_words(List mylist)
{
int number=0;
Listelement_ptr iterator;

for (iterator=mylist; iterator!=NULL; iterator=iterator->next)
    number++;
 
return number;
}

int stat_num_diff_words(List mylist)
{

List diff_words=NULL;
Listelement_ptr iterator,diff_iterator,random_ptr;
random_ptr=createnewelement("rdmafrf");
addtolist(&diff_words,random_ptr);

for (iterator=mylist; iterator!=NULL; iterator=iterator->next)
{
  for (diff_iterator=diff_words; diff_iterator!=NULL; diff_iterator=diff_iterator->next)
       {
       	 if ( strcmp(iterator->word,diff_iterator->word)==0 )
       	     break;
       	 if (diff_iterator->next==NULL)
       	     diff_iterator->next=createnewelement(iterator->word);
       }
}
   	
return stat_number_words(diff_words)-1;	
}

int stat_number_chars(List mylist)
{
int number=0;
Listelement_ptr iterator;

for (iterator=mylist; iterator!=NULL; iterator=iterator->next)
     number+= strlen(iterator->word);

return number;
}

void show_statistics(List mylist,int c[M][2])
{
printf("\n \t\tTEXT STATISTICS\n");
printf("\n Your text consists of %d words.",stat_number_words(mylist));
printf("\n Your text consists of %d different words.",stat_num_diff_words(mylist));
printf("\n Your text consists of %d characters (without space).",stat_number_chars(mylist));
printf("\n Your text consists of %d characters (including space).\n",(stat_number_chars(mylist)+stat_number_words(mylist)-1));
print_histogram(c);
}

void ask_stats_name(List mylist,int c[M][2])
{
char stats_name[20];
printf("\n\n The statistics of the text will be saved in a new file."
"\n Please name this new file(without using spaces):");
scanf("%s", stats_name);
strcat(stats_name,".txt");
save_stats(stats_name,mylist,c);
}

void save_stats(char name[20],List mylist,int c[M][2])
{
FILE *stats_ptr;
stats_ptr=fopen(name,"wt");

fprintf(stats_ptr,"\t\tTEXT STATISTICS:\n");	
fprintf(stats_ptr,"\nYour text consists of %d words.",stat_number_words(mylist));
fprintf(stats_ptr,"\nYour text consists of %d different words.",stat_num_diff_words(mylist));
fprintf(stats_ptr,"\nYour text consists of %d characters (without space).",stat_number_chars(mylist));
fprintf(stats_ptr,"\nYour text consists of %d characters (including space).\n",(stat_number_chars(mylist)+stat_number_words(mylist)-1));
fprint_histogram(stats_ptr,c);

fclose(stats_ptr);	
printf("\n Your text's statistics have been saved in this file: %s",name);
printf("\n It is located inside the text_editor folder.\n");
}

void fprint_histogram(FILE * f_ptr,int x[M][2])
{
int i,j,max=0;
for (i=1; i<M; i++)
  {
    if (x[i][1]>max)
      max=x[i][1];
  }

if (max<=100)
{
fprintf(f_ptr,"\n \t\tWord Length Histogram:\n\n");
   for (i=1; i<M; i++)
   {
     fprintf(f_ptr,"Number of words with length = %2d in your text : %d ",x[i][0],x[i][1]);
     for (j=0; j<x[i][1]; j++)
       fprintf(f_ptr,"*");
     fprintf(f_ptr,"\n");
   } 
}
if (100<max && max<1000)
{
fprintf(f_ptr,"\n \t\tWord Length Histogram:\n\n");
   for (i=1; i<M; i++)
   {
     fprintf(f_ptr,"Number of words with length = %2d in your text : %d ",x[i][0],x[i][1]);
     for (j=0; j<x[i][1]/10; j++)
       fprintf(f_ptr,"*");
     fprintf(f_ptr,"\n");
   } 	
}
if (max>=1000)
{
fprintf(f_ptr,"\n \t\tWord Length Histogram:\n\n");
   for (i=1; i<M; i++)
   {
     fprintf(f_ptr,"Number of words with length = %2d in your text : %d ",x[i][0],x[i][1]);
     for (j=0; j<x[i][1]/100; j++)
       fprintf(f_ptr,"*");
     fprintf(f_ptr,"\n");
   } 		
}
}

int get_correction_choice()
{
int choice;

printf("\n Press:\n 1 to replace this word\n 2 to add this word to the vocabulary\n 3 to move on to the next word"
"\n 4 to return to the main menu\n Press here:");
for( scanf("%d",&choice); choice!=1 && choice!=2 && choice!=3 &&choice!=4; scanf("%d",&choice) )
    {
    printf("\n You did not select one of the valid options. Try again!\n");
    printf("\n Press:\n 1 to replace this word\n 2 to add this word to the vocabulary\n 3 to continue the correction"
" process\n 4 to return to the main menu\n Press here:");
    }
return choice;
}

int search_vocabulary(Listelement_ptr iterator,List vocab)
{
Listelement_ptr vocab_iterator;

for (vocab_iterator=vocab; vocab_iterator!=NULL; vocab_iterator=vocab_iterator->next)
    {
     if ( strcmp(vocab_iterator->word,iterator->word)==0 )
        return 1;
    }
return 0;
}

void replace_word(Listelement_ptr toreplace_ptr)
{
char replacement[M];
printf("\n Write one word to replace '%s'.\n",toreplace_ptr->word);
printf(" Write here:");
scanf("%s",replacement);
strcpy(toreplace_ptr->word,replacement);
printf("\n The replacement has been made.\n");
}

void add_vocabulary(Listelement_ptr toadd_ptr,List *vocab)
{
Listelement_ptr newelement_ptr;
printf("\n The word '%s' has been added to the vocabulary.\n",toadd_ptr->word);
newelement_ptr=createnewelement(toadd_ptr->word);
addtolist(vocab,newelement_ptr);
}

void clear_list(List *mylist)
{
Listelement_ptr next_elem,iterator=*mylist;

while(iterator!=NULL)
{
next_elem=iterator->next;
free(iterator);
iterator=next_elem;
}
*mylist=NULL;
}

