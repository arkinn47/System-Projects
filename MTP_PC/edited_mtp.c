#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#define BUFFER_SIZE 50000
#define THREAD_NUM 4

char buffer_1[BUFFER_SIZE]; // Buffer 1, shared resource between input thread and square-root thread
int count_1 = 0; // Number of items in the buffer 1
int prod_idx_1 = 0;  // Index where the input thread will put the next item
int con_idx_1 = 0;  // Index where the space-line break thread will pick up the next item
pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;  // Initialize the mutex for buffer 1
pthread_cond_t full_1 = PTHREAD_COND_INITIALIZER; // Initialize the condition variable for buffer 1
char output[5] = {0};


char buffer_2[BUFFER_SIZE]; // Buffer 2, shared resource between square root thread and output thread
int count_2 = 0;  // Number of items in the buffer 2
int prod_idx_2 = 0;  // Index where the space-line thread will put the next item
int con_idx_2 = 0;  // Index where the plus-sign thread will pick up the next item
pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;  // Initialize the mutex for buffer 2
pthread_cond_t full_2 = PTHREAD_COND_INITIALIZER;  // Initialize the condition variable for buffer 2
//char thread_1_character;

char buffer_3[BUFFER_SIZE];
int count_3 = 0; // Number of items in the buffer 1
int prod_idx_3 = 0;  // Index where the input thread will put the next item
int con_idx_3 = 0;  // Index where the space-line break thread will pick up the next item
pthread_mutex_t mutex_3 = PTHREAD_MUTEX_INITIALIZER;  // Initialize the mutex for buffer 1
pthread_cond_t full_3 = PTHREAD_COND_INITIALIZER; // Initialize the condition variable for buffer 1

//char character_store[1];
char stop[6] = {0};
int started = 0;
int signaler = 0;
int number_of_line_seperators = 0;
int non_terminator = 0;
int terminator_distance = 0;
int first_stop = 0;
char first_S = 0;
char *character_store = NULL;


char item_ls[1] = {'a'};
char item_ot[1] = {'a'};
char item_ps[1] = {'a'};

char items_ot[81];

void put_buffer_1(char character_1){
      pthread_mutex_lock(&mutex_1);
      buffer_1[prod_idx_1] = character_1;
      prod_idx_1 = prod_idx_1 + 1;
      count_1++;
      pthread_cond_signal(&full_1);
      pthread_mutex_unlock(&mutex_1);}


void *get_input(){
   size_t len = 0;
while(1){
       getline( &character_store, &len, stdin);
       if (strcmp(character_store, "STOP\n") == 0  || strcmp(character_store, "\nSTOP\n") == 0){
        put_buffer_1('\n');
        put_buffer_1('\n'); 
         break;} 
      for(int i = 0; i < strlen(character_store); i++) {put_buffer_1(character_store[i]);}
             }
      free(character_store);
              return NULL;
      }                                                    

void put_buffer_2(char character_2){
      pthread_mutex_lock(&mutex_2);
      buffer_2[prod_idx_2] = character_2;
      prod_idx_2 = prod_idx_2 + 1;
      count_2++;
      pthread_cond_signal(&full_2);
      pthread_mutex_unlock(&mutex_2);}

char get_buffer_1(){
      pthread_mutex_lock(&mutex_1);
      while(count_1 == 0)
        pthread_cond_wait(&full_1, &mutex_1);       
      char item = buffer_1[con_idx_1];
      con_idx_1 = con_idx_1 + 1;
      count_1--;
      pthread_mutex_unlock(&mutex_1);
      return item;}

void *line_seperator(){  
  while(1){ 
    item_ls[0] = get_buffer_1();
    if(item_ls[0] == '\n'){
     item_ls[0] = get_buffer_1();
      if(item_ls[0] == '\n'){
          put_buffer_2('\n');
           break;
       } else{
       put_buffer_2(' ');
       put_buffer_2(item_ls[0]);}
    } else{
       put_buffer_2(item_ls[0]);}
   }
  return NULL;}

char get_buffer_2(){
      pthread_mutex_lock(&mutex_2);
      while(count_2 == 0)
        pthread_cond_wait(&full_2, &mutex_2);       
      char item = buffer_2[con_idx_2];
      con_idx_2 = con_idx_2 + 1;
      count_2--;
      pthread_mutex_unlock(&mutex_2);
      return item;}


void put_buffer_3(char character_3){
      pthread_mutex_lock(&mutex_3);
      buffer_3[prod_idx_3] = character_3;
      prod_idx_3 = prod_idx_3 + 1;
      count_3++;
      pthread_cond_signal(&full_3);
      pthread_mutex_unlock(&mutex_3);}

void *plus_sign(){
      while(1){
      item_ps[0] = get_buffer_2();


      if(item_ps[0] == '\n'){
          put_buffer_3('\n');
          break;}

      if(item_ps[0] == '+'){
          item_ps[0] = get_buffer_2();
      
          if(item_ps[0] == '+'){
          put_buffer_3('^'); 
          } 
          else{
               put_buffer_3('+');
               put_buffer_3(item_ps[0]);}
      }  
      else {put_buffer_3(item_ps[0]);}
      }
    return NULL;
      }

char get_buffer_3(){
      pthread_mutex_lock(&mutex_3);
      while(count_3 == 0)
        pthread_cond_wait(&full_3, &mutex_3);       
      char item = buffer_3[con_idx_3];
      con_idx_3 = con_idx_3 + 1;
      count_3--;     
      pthread_mutex_unlock(&mutex_3);
      return item;} 
                  
void *output_thread(){
     int printed_characters = 0;
     items_ot[80] = '\n';
     while(1){       
     item_ot[0] = get_buffer_3();
     items_ot[printed_characters%80] = item_ot[0];
     printed_characters++;
     if(printed_characters%80 == 0 && printed_characters > 0){

     write(STDOUT_FILENO, items_ot, 81);
     }
      if(item_ot[0] == '\n'){
          write(STDOUT_FILENO, items_ot, 81);
          break;}
     }
return NULL;} 



int main(){pthread_t th0, th1, th2, th3;
    //Create threads
    pthread_create(&th0,NULL, get_input, NULL);
    pthread_create(&th1,NULL, line_seperator, NULL);
    pthread_create(&th2,NULL, plus_sign, NULL);
    pthread_create(&th3,NULL, output_thread, NULL);

    //Join threads
    pthread_join(th0, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);

    //Destroy threads
    pthread_mutex_destroy(&mutex_1);
    pthread_cond_destroy(&full_1);

    pthread_mutex_destroy(&mutex_2);
    pthread_cond_destroy(&full_2);

    pthread_mutex_destroy(&mutex_3);
    pthread_cond_destroy(&full_3);


    return EXIT_SUCCESS;}
