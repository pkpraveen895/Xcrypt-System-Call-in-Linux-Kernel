#include <crypto/skcipher.h>
#include <linux/fs.h>
#include <linux/mount.h>
#include <linux/pagemap.h>
#include <linux/compiler.h>
#include <linux/key.h>
#include <linux/namei.h>
#include <linux/file.h>
#include <linux/errno.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/linkage.h>
#include <linux/random.h>
#include <linux/moduleloader.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/crypto.h>
#include <linux/uaccess.h>
#include <linux/scatterlist.h>
#include <crypto/md5.h>
#include <crypto/hash.h>
#define BUFFER_SIZE PAGE_SIZE

struct skcipher_def
{
         struct skcipher_request *request;
         struct crypto_skcipher *tfm;
         struct scatterlist sg;
};

struct arguments
{
        char *inputfile;
        char *outputfile;
        char *keybuf;
        int flags;
        int keylen;
};

int crypto_help_function( char *key,char *data,int bytes , int flag)
{
    char *iv_data = NULL;
    int error = 0;
    struct skcipher_request *request = NULL;
    struct crypto_skcipher *skcipher = crypto_alloc_skcipher( "ctr(aes)",0,CRYPTO_ALG_ASYNC );
    
    struct skcipher_def *sk = NULL;
    //int ret_value;

    sk = kmalloc( sizeof( struct skcipher_def ),GFP_KERNEL );
    //check if memory allocation is succesful in kernel
    if( !sk )
    {   
       kfree( sk );
       return -ENOMEM;
    }
   
    // check if cipher handle allocation is successfull
    if ( IS_ERR( skcipher ) )
    {
        error = PTR_ERR(skcipher);
        printk("cipher handle allocation failed\n");
        return error;
    }
    else
    {
    	request = skcipher_request_alloc( skcipher,GFP_KERNEL );

        // check if cipher request allocation is successful
    	if ( !request )
    	{
        	crypto_free_skcipher( skcipher );
        	printk("cipher request allocation failed\n");
        	return -ENOMEM;
    	}
    }
    
    // check if key value was properly set
    if ( crypto_skcipher_setkey( skcipher,key,16 ) )
    {
        crypto_free_skcipher( skcipher );
        skcipher_request_free( request );
        printk("setting key failed in helped function\n");
        return -EAGAIN;
    }
 
    sk->request = request;
    sk->tfm = skcipher;

    iv_data = kmalloc( 16,GFP_KERNEL );
    
    // check if iv data allocation is successful
    if ( !iv_data )
    {
        printk("iv data allocation failed\n");
        error = -ENOMEM;
        goto failed;
    }
    
    sg_init_one( &sk->sg,data,bytes );
    strncpy( iv_data,"aabbccddeeffgghh",16 );
    skcipher_request_set_crypt( request,&sk->sg,&sk->sg,bytes,iv_data );
    
    if( flag == 2)
	error = crypto_skcipher_decrypt( sk->request );
    else
        error = crypto_skcipher_encrypt( sk->request );
    
failed:
    if ( iv_data )
        kfree( iv_data );

    if ( request )
        skcipher_request_free( request );

    if ( skcipher )
        crypto_free_skcipher( skcipher );
    
    return error;
}

asmlinkage extern long (*sysptr)(void *arg);

asmlinkage long cpenc(void *arg)
{
    if (arg != NULL)
    {
        int result;
        struct arguments *args;
        umode_t input_file_mode, output_file_mode;
        char *source_buff, *destination_buff;
        long int key_length = -1, output_file_length = -1, input_file_length = -1; 
        int error = 0;
        struct file *in_filp = NULL;
        struct file *out_filp = NULL;
        mm_segment_t old_fs;
        int out_bytes = 0;
        char *data = NULL;
        int bytes = 1;
  
        args = ( struct arguments * )kmalloc( sizeof( struct arguments ),GFP_KERNEL );
	
        if (args == NULL)
        {
            error = -ENOMEM;
            printk("Allocation of kernel memory failed\n");
            return error;
        }      

       result = copy_from_user( (void *)args,arg,sizeof(struct arguments) );

        if(result != 0)
        {
            error = -EFAULT;
            printk("Failed to copy from user\n");
            goto copy_from_user_failure;
        }

        if ( ( ( struct arguments* ) arg )->inputfile == NULL )
        {
            error = -EINVAL;
            printk("input file passed at user is invalid \n");
            goto copy_from_user_failure;
        }

        input_file_length = strnlen_user(((struct arguments*) arg)->inputfile, 32767 );
        
        if ( input_file_length == -1 )
        {
            error = -EFAULT;
            printk("input file passed at user has zero length \n");
            goto copy_from_user_failure;
        }

        args->inputfile = ( char * )kmalloc( input_file_length * sizeof(char),GFP_KERNEL );
        if ( ( args->inputfile ) == NULL )
        {
            error = -ENOMEM;
            printk("input file memory allocation at kernel failed \n");
            goto copy_from_user_failure;
        }

        result = strncpy_from_user(args->inputfile, ( ( struct arguments* ) arg )->inputfile, input_file_length);
        if( result != ( input_file_length - 1 ) )
        {
            error = -EFAULT;
            printk("failed to copy input file name from user \n");
            goto input_file_error;
        }

        if ( ( ( struct arguments* ) arg )->outputfile == NULL)
        {
            error = -EINVAL;
            printk("output file passed at user is invalid\n");
            goto input_file_error;
        }

        output_file_length = strnlen_user(((struct arguments*)arg)->outputfile,32767 );
        if (output_file_length == -1)
        {
            error = -EFAULT;
            printk("output file passed at user has zero length\n");
            goto input_file_error;
        }
        
        args->outputfile = (char *)kmalloc( output_file_length * sizeof(char),GFP_KERNEL );
        if ( ( args->outputfile ) == NULL )
        {
            error = -ENOMEM;
            printk("output file memory allocation at kernel failed \n");
            goto input_file_error;
        }
        
        result = strncpy_from_user( args->outputfile,((struct arguments*)arg)->outputfile, output_file_length);
        if( result != (output_file_length - 1 ) )
        {
            error = -EFAULT;
            printk("failed to copy output file name from user\n");
           goto output_file_error;
        }
       
        if ( ( ( struct arguments* ) arg )->keybuf == NULL )
        {
            error = -EINVAL;
            printk("key buffer passed at user is invalid\n");
            goto output_file_error;
        }

        key_length = strnlen_user( ( ( struct arguments* ) arg)->keybuf, 32767);

        if( key_length == -1 )
        {
            error = -EFAULT;
            printk("key buffer passed at user has zero length\n");
            goto output_file_error;
        }

        args->keybuf = (char *)kmalloc( key_length * sizeof(char), GFP_KERNEL );

        if( ( args->keybuf ) == NULL )
        {
            error = -ENOMEM;
            printk("key buff memory allocation failed at kernel\n");
            goto output_file_error;
        }

        result = strncpy_from_user( args->keybuf, ((struct arguments*)arg)->keybuf, key_length);
        if( result != ( key_length - 1 ) )
        {
            error = -EFAULT;
            printk("failed to copy key buffer from user \n");
            goto key_buffer_error;
        }
 
        if ( strlen( args->keybuf ) != args->keylen )
        {
            error = -EINVAL;
            printk("unequal kernel key buff and key buff lengths \n");
             goto key_buffer_error;
        }
        
        if( ( args->flags ) !=2 && ( args->flags ) !=1 && ( args->flags ) != 4)
        {
            error = -EINVAL;
            printk("Invalid flag argument values\n");
             goto key_buffer_error;
        }

        source_buff = (char *)kmalloc( ( PAGE_SIZE + 1 )*sizeof(char), GFP_KERNEL );
        if ( source_buff == NULL )
        {
            error = -ENOMEM;
            printk("allocation of kernel memory to source buffer failed\n");
              goto key_buffer_error;
        }

        destination_buff = ( char * )kmalloc( ( PAGE_SIZE + 1 ) * sizeof(char), GFP_KERNEL );
        if ( destination_buff == NULL)
        {
            error = -ENOMEM;
            printk("allocation of kernel memory to destination buffer failed\n");
              goto source_buffer_error;
        }

        in_filp = filp_open(args->inputfile, O_RDONLY, 0);

        if ( !in_filp || IS_ERR(in_filp) )
        {
            error = (int) PTR_ERR(in_filp);
            printk("input file opening failed with error - %d\n", error);
            goto destination_error;
        }

        input_file_mode = in_filp->f_inode->i_mode;
        in_filp->f_pos = 0;

        if( !S_ISREG(input_file_mode) )
        {
            error = -EISDIR;
            printk("irregular input file\n");
            goto input_file_creation_error;
        }
       
        out_filp = filp_open(args->outputfile, O_WRONLY | O_CREAT, input_file_mode);
        
        if( !out_filp || IS_ERR( out_filp ) )
        {
             error = PTR_ERR( out_filp );
             printk("output file creation failed\n");
             goto input_file_creation_error;
        }
        
        output_file_mode = out_filp->f_inode->i_mode;

        if(!S_ISREG(output_file_mode))
        {
            error = -EISDIR;
            printk(" irregular output file\n");
            goto output_file_creation_error;
        }                                                             

        out_filp->f_pos = 0;

        if( out_filp->f_inode->i_ino == in_filp->f_inode->i_ino )
        {
             error = -EPERM;
             printk(" output & input files are same \n");
             goto output_file_creation_error;
        }
        
        data = kmalloc(BUFFER_SIZE, GFP_USER);
        old_fs = get_fs(); 
        set_fs(KERNEL_DS);
       
        while( bytes > 0 ) 
       {
           bytes = vfs_read( in_filp,data,BUFFER_SIZE,&in_filp->f_pos );
           if( bytes < 0) 
           {
               error = bytes;
               printk(" reading input file failed\n");
               goto err;
           }
        
        if ( args->flags == 4 )
	{  
		goto copy; 
	}
        else if(args->flags == 2)
        { 
            error = crypto_help_function((char *) args->keybuf, data, bytes, args->flags);
            if(error == 0)
                printk("decryption of file successful");
            else
            {
                printk("decryption of file failed\n");
                 goto err;
            }
        }
        else if ( args->flags == 1 )
        { 
          error = crypto_help_function((char *) args->keybuf, data, bytes, args->flags);
          if(error == 0)
                printk("encryption of file successful");
          else 
          {
             printk("encryption of file failed\n");
             goto err;
          }
        }
copy:
         out_bytes = vfs_write( out_filp,data,bytes,&out_filp->f_pos );
 
         if( out_bytes <  0 ) 
         {
             error = out_bytes;
             printk("write to output file failed\n");
             goto err;
         }
 
        }

err:
    set_fs(old_fs);

    output_file_creation_error:
        if(out_filp)
            filp_close(out_filp, NULL);

    input_file_creation_error:
        if(in_filp)
            filp_close(in_filp, NULL);

    destination_error:
       if(destination_buff)
        kfree( destination_buff );

    source_buffer_error:
      if(source_buff)
        kfree( source_buff );

    key_buffer_error:
        if(args->keybuf)
        kfree( args->keybuf );
 
    output_file_error:
        if(args->outputfile)
        kfree( args->outputfile );
 
    input_file_error:
        if( args->inputfile )
        kfree( args->inputfile );
 
    copy_from_user_failure:
        kfree( args );
  
        return error;
    }
    else
    {
        printk("Null arguments in user level\n");
        return -EINVAL;
    }
}

static int __init init_sys_cpenc(void)
{
        printk("installed new sys_cpenc module\n");
        if (sysptr == NULL)
                sysptr = cpenc;
        return 0;
}
static void  __exit exit_sys_cpenc(void)
{
        if (sysptr != NULL)
                sysptr = NULL;
        printk("removed sys_cpenc module\n");
}
module_init(init_sys_cpenc);
module_exit(exit_sys_cpenc);
MODULE_LICENSE("GPL");                    
