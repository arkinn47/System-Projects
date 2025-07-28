#include <stdio.h>  // Standard input and output
#include <errno.h>  // Access to errno and Exxx macros
#include <stdint.h> // Extra fixed-width data types
#include <string.h> // String utilities
#include <err.h>    // Convenience functions for error reporting (non-standard)
//#define BLOCK_SIZE 512

static char const b64_alphabet[] =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "abcdefghijklmnopqrstuvwxyz"
  "0123456789"
  "+/";

int main(int argc, char *argv[]) //*argv[] is argument vector; argc argument count
{   FILE *user_input;
    if (argc > 2) {             // if argument is more than two values, wrong input
        errno = EINVAL; /* "Invalid Argument" */
        err(1, "Too many arguments");
    
    } else if (argc == 2 && strcmp(argv[1], "-")) {  //two inputs for file 2nd "-"
         /* open FILE */                                                          
         user_input = fopen(argv[0],"r");                                         
         if(!user_input) err(1,"%s", argv[1]);                                     
      
    } else {
         /* use stdin instead */
        user_input = stdin;
    }
    //FILE *user_input= user_input;
    int character_count = 0;

    FILE *fp = fopen("output_file.txt","wb");
    for (;;) {
       
        uint8_t input_bytes[3] = {0};  //uint8_t unsigned single byte
        size_t n_read = fread(input_bytes, 1, 3, user_input);  //uint8_t unsigned integer type
        //printf("%s\n",input_bytes); 
        //printf("%zu\n",n_read);
        if (n_read != 0) {
            /* Have data */
            int alph_ind[4];
            char output[4];
            if (n_read > 0){
                alph_ind[0] = input_bytes[0] >> 2;
                output[0] = b64_alphabet[alph_ind[0]];
                //size_t n_write = fwrite(output,1, 1,fp);
                character_count += 1;
                size_t n_write = fwrite(output, 1, 1 ,stdout);
                if(character_count%76 == 0)(fprintf(stdout,"\n"));
                //printf("%c",output[0]);
                }
            if (n_read >= 1){
                alph_ind[1] = (input_bytes[0] << 4 | input_bytes[1] >> 4) & 0x3Fu;
                output[1] = b64_alphabet[alph_ind[1]];
                //size_t n_write = fwrite(output,1, 1,fp);
                character_count += 1;
                size_t n_write = fwrite(output + 1, 1, 1 ,stdout);
                if(character_count%76 == 0)(fprintf(stdout,"\n"));
                //printf("%c",output[1]);
                 
                }
            if (n_read >= 2){
                alph_ind[2] = (input_bytes[1] << 2 | input_bytes[2] >> 6) & 0x3Fu;
                output[2] = b64_alphabet[alph_ind[2]];
                
                character_count += 1;
                size_t n_write = fwrite(output + 2, 1, 1 ,stdout);
                if(character_count%76 == 0)(fprintf(stdout,"\n"));
                //printf("%c",output[2]);
            }
            if (n_read == 3){
                alph_ind[3] =  input_bytes[2] & 0x3Fu;
                output[3] = b64_alphabet[alph_ind[3]];
                character_count += 1;
                size_t n_write = fwrite(output + 3, 1, 1 ,stdout);
                if(character_count%76 == 0)(fprintf(stdout,"\n"));
                //printf("%c",output[3]);
            }
//            ...
            /*
            char output[4];
            output[0] = b64_alphabet[alph_ind[0]];
            output[1] = b64_alphabet[alph_ind[1]];
            output[2] = b64_alphabet[alph_ind[2]];
            output[3] = b64_alphabet[alph_ind[3]];
            */
            //printf("%s",output);
            //printf("%zu",n_read);
            //... do something ...
           // size_t n_write = fwrite(output, n_read, 1 ,fp);
            //if (ferror(...)) err(...); /* Write error */
        }

        if(n_read == 0)
        {
            int remainder = ((6*character_count)/8)%3;
            switch(remainder)
            {
            case 1:
                fprintf(stdout,"==");
                break;
            case 2:
                fprintf(stdout,"=");
                break;
            }
            if(character_count%76 == 0)(fprintf(stdout,"\n"));
            //printf("\n");
            fprintf(stdout,"\n");
            break;
        } 
        
    }
    fclose(fp);
    //if (... != stdin) fclose(...); /* close opened files; */
    /* any other cleanup tasks? */
    //return fp;
}
