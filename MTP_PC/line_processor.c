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
//items_ot[80] ='\n';



//int index_3 = 0;
//pthread_mutex_t mutex_buffer_3;
//pthread_cond_t condition_3;
//char input_bytes[1000];
void put_buffer_1(char character_1){
      pthread_mutex_lock(&mutex_1);
      buffer_1[prod_idx_1] = character_1;
      prod_idx_1 = prod_idx_1 + 1;
      count_1++;
      pthread_cond_signal(&full_1);
      pthread_mutex_unlock(&mutex_1);}


void *get_input(){
   size_t len = 0;
  // char *character_store = NULL;
   //char character_store[1];
   //read( STDIN_FILENO, character_store, 1);
   //fgets(character_store, 2, stdin);
  // goto start;   
  //fgets(stop, 6, stdin);
while(1){//fgets(character_store, 2, stdin) != NULL)
       getline( &character_store, &len, stdin);
       if (strcmp(character_store, "STOP\n") == 0  || strcmp(character_store, "\nSTOP\n") == 0){
       //goto out;
        put_buffer_1('\n');
        put_buffer_1('\n'); 
         //exit(0);
         break;
       //goto out;
      } 
       //else{
      // printf("%s", character_store);
                for(int i = 0; i < strlen(character_store); i++) 
                   {put_buffer_1(character_store[i]);}
         //    }
               //if (strcmp(character_store, "STOP\n") == 0  || strcmp(character_store, "\nSTOP\n") == 0) break;
             }
                //break;
          /* else if(feof(stdin)){
            character_store[0] = EOF;
           put_buffer_1(character_store[0]);}
            break;*/
        //if (character_store[0] != EOF){
        //
       // put_buffer_1(character_store[0]);//}
        //    else{exit(0);}
   /*     if(character_store[0] != '\n') {
          non_terminator++;} else {
          terminator_distance = non_terminator;
          non_terminator = 0;
          }      
        if(character_store[0] == '\n'  ) started = 0; 
       stop[started%6] = character_store[0];
          first_stop = 1;        */
             // printf("%s\n", character_store);
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
  //char item2[1] = {0};
  //char item[]={'a'};  
  while(1){ 
    item_ls[0] = get_buffer_1();
    
    if(item_ls[0] == '\n'){
     item_ls[0] = get_buffer_1();
      if(item_ls[0] == '\n'){
          put_buffer_2('\n');
          //put_buffer_2('\n');
           break;
       //goto out2;
       } else{
        
      //  put_buffer_2(' ');
       //item_ls[0] = ' ';
       put_buffer_2(' ');
       put_buffer_2(item_ls[0]);

    }} else{
       put_buffer_2(item_ls[0]);}
 
     //   else{
     // :item_ls[0] = ' ';  
   // put_buffer_2(item_ls[0]);}
    
    //if(strcmp(item_ls, "EOF") == 0) break;
    
   //if(item_ls[0] == EOF) break;
   // printf("sdfvsdfvsdfvsdfvsdfv\n");
   // printf("%c", buffer_2[count_2 - 1]);  
  //fflush(stdout);
  /*pthread_mutex_lock(&mutex_buffer_1);    
  if (index_1 > 0){
  thread_1_character = buffer_1[index_1 - 1];
  index_1--;}
  pthread_mutex_unlock(&mutex_buffer_1);
  if (thread_1_character == '\n') thread_1_character = ' ';
  pthread_mutex_lock(&mutex_buffer_2); 
  if (index_2 < 50000){
      buffer_2[index_2] = thread_1_character;
      index_2++;}
  pthread_mutex_unlock(&mutex_buffer_2);*/
   //if(item[0] == EOF)break;
   }
  //printf("===========================%s\n", character_store);
//out2:
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
      //char item[] = {'a'};
      while(1){
      item_ps[0] = get_buffer_2();


      if(item_ps[0] == '\n'){
          put_buffer_3('\n');
          break;}


         // put_buffer_3('\n');



      if(item_ps[0] == '+'){
          item_ps[0] = get_buffer_2();
          if(item_ps[0] == '+'){
          put_buffer_3('^'); 
          } else{put_buffer_3('+');
                 put_buffer_3(item_ps[0]);}
      }  //else if(item_ps[0] == '\n'){
      
      //item_ps[0] = get_buffer_2();
       //if(item_ps[0] == '\n')

         // put_buffer_3('\n');
          //put_buffer_3('\n');

        //   break;
      // goto out3;
   //   } else
      else {




        put_buffer_3(item_ps[0]);}
         //if(item_ps[0] == EOF)break;

      //printf("%c", buffer_3[count_3 - 1]);
      // printf("sdfvsdfvsdfvsdfvsdfv\n");
   // if(strchr(item_ps, EOF) != NULL) break;
    /*if(item_ps[0] == '\0') {
      printf("===============================\n");
      goto out3;
      break;}*/
 
      //fflush(stdout);
   //if(item[0] == EOF)break;
      }
     // printf("===========================%s\n", character_store);

//out3:
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
    // char item[1] = {'a'};
     //char items[81];
     items_ot[80] = '\n';
     //char breaker[1] = "\n";
     while(1){       
     item_ot[0] = get_buffer_3();

     
    /* if(item_ot[0] == '\n'){
      
      item_ls[0] = get_buffer_3();
       if(item_ls[0] == '\n'){


           break;
       goto out4;}  }*/

     //if (item[0] != EOF || item[0] ){
     /*if(item_ot[0] == EOF && printed_characters%80 == 1) {
       items_ot[80] = '\0';
         printf("1234=========================================\n");}else{
           printf("=========================================\n"); */

     items_ot[printed_characters%80] = item_ot[0];
     printed_characters++;//}

     //fprintf(stdout,"%c",item[0]);            
     //fflush(stdout);                          
     
     //pthread_mutex_lock(&mutex_3);              
     //while(count_3%80 != 0)                      
     //    pthread_cond_wait(&full_3, &mutex_3);
     //if(count_3%80 == 0 && count_3 > 0 && write(STDOUT_FILENO, buffer_3, 80)%80 == 0){
     //   printf("\n");
     //}
     //pthread_mutex_unlock(&mutex_3);

     //write(STDOUT_FILENO, item, 1);
     //printed_characters++; = printed_characters + 1;
     //if (character_store[0] == '\0' || character_store[0] ==  EOF) exit(0);       
  //  printf("=========================================%d\n", printed_characters );
     if(printed_characters%80 == 0 && printed_characters > 0){
     //printf("%s", items);
     //fflush(stdout);    
    //   if (strchr(items_ot, '\0')!= NULL) break;
     write(STDOUT_FILENO, items_ot, 81);
     //printf("\n");
     //write(STDOUT_FILENO, "\n", 1);
     //printf("%d avsadvasdv\n", printed_characters); 
     }
     // if(item_ot[0] == '\n') exit(0);
      if(item_ot[0] == '\n'){
          //put_buffer_3('\n');
          break;}

     /*printf("======================SDFVFVS===================%d\n", printed_characters );

     if (strchr(items_ot,EOF ) != NULL){ 
      printf("-----------=================%d\n", printed_characters );
       break;}
     printf("================------------=====%d\n", printed_characters );*/

    //if(item_ot[0] == '\0')break;
     //printed_characters++;
     }
//out4:
    // printf("===========================%s\n", character_store);

    // exit(0);
return NULL;} 



int main(){
   // pthread_t th[THREAD_NUM];
    pthread_t th0, th1, th2, th3;
    //pthread_mutex_init(&mutex_buffer_1, NULL); 
    //pthread_cond_init(&buffer_1_condition, NULL);
    pthread_create(&th0,NULL, get_input, NULL);
    
    //pthread_mutex_init(&mutex_buffer_2, NULL); 
    //pthread_cond_init(&buffer_2_condition, NULL);
    pthread_create(&th1,NULL, line_seperator, NULL);

    //pthread_mutex_init(&mutex_buffer_2, NULL); 
    //pthread_cond_init(&buffer_2_condition, NULL);
    pthread_create(&th2,NULL, plus_sign, NULL);

    //pthread_mutex_init(&mutex_buffer_2, NULL); 
    //pthread_cond_init(&buffer_2_condition, NULL);
    pthread_create(&th3,NULL, output_thread, NULL);


 
///////////////////////////////////////////////////////

    pthread_join(th0, NULL);
    //pthread_mutex_destroy(&mutex_buffer_1);
    //pthread_cond_destroy(&buffer_1_condition);

    pthread_join(th1, NULL);
    //pthread_mutex_destroy(&mutex_buffer_2);
    //pthread_cond_destroy(&buffer_2_condition);
    
    pthread_join(th2, NULL);
    //pthread_mutex_destroy(&mutex_buffer_2);
    //pthread_cond_destroy(&buffer_2_condition);

    pthread_join(th3, NULL);
    //pthread_mutex_destroy(&mutex_buffer_2);
    //pthread_cond_destroy(&buffer_2_condition);


    pthread_mutex_destroy(&mutex_1);
    pthread_cond_destroy(&full_1);

    pthread_mutex_destroy(&mutex_2);
    pthread_cond_destroy(&full_2);

    pthread_mutex_destroy(&mutex_3);
    pthread_cond_destroy(&full_3);
 
    //pthread_mutex_destroy(&mutex_3);
    //pthread_cond_destroy(&full_3);


    return EXIT_SUCCESS;}