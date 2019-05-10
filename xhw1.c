// header files
#include <string.h>
#include <asm/unistd.h>
#include <errno.h>
#include <openssl/sha.h>
#include <unistd.h>
#include <openssl/md5.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <getopt.h>

// macro
#ifndef __NR_cpenc
#error xcpenc system call not defined
#endif

struct args
{
    char *input_file, *output_file, *key_buffer;
    int flags, key_length;
};
// structure to store arguments

int main( int argc,char * const argv[ ] )
{
    int opt = 0, command_flag = -1;
    int  input_file_length, output_file_length;
    int error = 0;
    char *password = NULL;
    char  *input_file = NULL, *output_file = NULL;
    while ( ( opt = getopt( argc,argv,"hp:d:e:c:" ) ) != -1 )
    {
        switch ( opt )
        {
            // retrieve each argument and store accordingly
            case 'h' :
                printf("Syntax is: ./xhw1 -p \"passwordKey\" -e|-d|-c <input_file> <output_file>\n");
                exit( 1 );
                
                
            case 'p' :
                if ( argc > 2 )
                {
                    password = optarg;
                }
                break;
                
            case 'c' :
            case 'e' :
            case 'd' :
                if( opt == 'c' )
                    command_flag = 4;
                else if( opt == 'e' )
                    command_flag = 1;
                else
                    command_flag = 2;
                
                if ( argc > 4 )
                {
                    input_file = optarg;
                    // input file stored
                }
                if ( argc > 5 )
                {
                    output_file = argv[ optind ];
                    // output file stored
                }
                break;
                
            // check if arguments are valid
            case '?':
                if( optopt != 'e'|| optopt != 'c'||optopt != 'p'||optopt != 'd')
                    printf ("Unknown opt. \n");
                else
                    printf (" invalid arguments for the option -%c.\n", optopt);
                
                printf("Syntax is: ./xhw1 -p \"passwordKey\" -e|-d|-c <input_file> <output_file>\n");
                return 1;
                
            default:
                printf("Syntax is: ./xhw1 -p \"passwordKey\" -e|-d|-c <input_file> <output_file>\n");
                exit( 1 );
        }
    }
    
    if ( argc != 6 )
    {
        printf("Syntax is: ./xhw1 -p \"passwordKey\" -e|-d|-c <input_file> <output_file>\n");
        exit(1);
    }
    
    if( strlen( password ) < 6 )
    {
        error = -1;
        printf(" invalid Password key - it should have a minimum of 6 characters\n");
        exit(error);
    }
    
    if( strcmp( input_file,"NULL" ) == 0)
    {
        error = -1;
        printf(" invalid input file \n");
        exit(error);
    }
    
    if( strcmp( output_file,"NULL" ) == 0)
    {
        error = -1;
        printf(" invalid output file\n ");
        exit(error);
    }
    
    input_file_length = strlen( input_file );
    output_file_length = strlen( output_file );
    
    struct args *arguments;
    arguments = malloc( sizeof( struct args ) );
    if( arguments == NULL )
    {
        error = -1;
        printf(" memory allocation failed\n ");
        exit(error);
    }
    
    arguments->input_file = malloc( ( input_file_length + 1)*sizeof(char));
    arguments->output_file = malloc( ( output_file_length + 1)*sizeof(char));
    
    if ( ( arguments->input_file ) == NULL || ( arguments->output_file ) == NULL )
    {
        error = -1;
        printf(" memory allocation failed \n ");
        goto memory_allocation_failure;
    }
    
    arguments->key_buffer = malloc( ( MD5_DIGEST_LENGTH + 1 )*sizeof(char));
    
    if( ( arguments->key_buffer ) == NULL )
    {
        error = -1;
        printf("memory allocation failed\n");
        goto memory_allocation_failure;
    }
    
    strcpy( arguments->input_file,input_file );
    strcpy( arguments->output_file,output_file );
    
    if( ( arguments->input_file ) == NULL || ( arguments->output_file )==NULL)
    {
        error = -1;
        if( ( arguments->output_file ) == NULL )
            printf("invalid output file is entered at user\n");
        else
            printf("invalid input file is entered at user\n");
        
        goto memory_allocation_failure;
    }
    
    arguments->flags = command_flag;
    
    MD5((unsigned char*)password, strlen(password), (unsigned char*)(arguments->key_buffer));
    
    if ( ( arguments->key_buffer ) == NULL )
    {
        error = -1;
        printf("User level - md5 generation failed\n");
        goto memory_allocation_failure;
    }
    else
        arguments->key_length = strlen( arguments->key_buffer );
    
    void *dummyptr = (void *)(arguments);
    error = syscall( __NR_cpenc,dummyptr );
    
    if ( error == 0 )
        printf("syscall returned %d\n", error);
    else
    {
        perror( " SYSCALL ERROR " );
        printf( " user level - syscall returned %d ( errno = %d ) \n",error,errno );
    }

memory_allocation_failure:
    
    if(arguments)
        free(arguments);
    
    exit(error);
}
