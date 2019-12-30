#include <stdio.h>
#include "C4172.aDiAdam.h"

/*
    warning: function returns address of local variable [enabled by default] [duplicate]
    https://stackoverflow.com/questions/17312336/warning-function-returns-address-of-local-variable-enabled-by-default
*/
char *chktype
(
      char *Buffer
    , int Size
)
{
    // This pointer variable is allocated on the stack, but that's okay because
    // it's a pointer to a string literal, which are always constant.
    // (Technically, you should add the "const" qualifier to the declaration.)
    const char *strng = "Content-Type: ";

    int sz;
    char *found = (char *) strstr (Buffer, strng);
    char *found1 = (char *) strstr(found, "\r\n");
    sz=strlen(found)-strlen(found1);

    // Like all the above variables, the one is also allocated on the stack.
    // But it's the source of your problem here, because it's the one that
    // you are returning at the end of the function.
    // Problem is, it goes away at the end of the function!
    //char type[sz];
    char type[4000];
    
    strncpy(type, found1, sz-1);
    
    return(type);
}

char *chktypeUsingMalloc
(
      char *Buffer
    , int Size
)
{
    
    const char *strng = "Content-Type: ";

    int sz;
    char *found = (char *) strstr (Buffer, strng);
    char *found1 = (char *) strstr(found, "\r\n");
    sz=strlen(found)-strlen(found1);

    char *type = NULL;

    int iLength = 0;
    int iSize =0;
    
    /*
        Get length of string that we will be allocating
    */
    iLength = sz;

    printf 
    (
          "\t allocating %d for char datatype \r\n"
        , iLength 
    );

    /*
        Memory Block is 
            sizeof data structure (size) 
            times 
            length of string
    */
    iSize = sizeof(char) 
                    * ( iLength)
                ;                   

    /*
        Allocate Object
    */
    type = ( char * ) 
                malloc
                ( 
                    iSize
                );
    

    /*
        reset object (type)
    */
    memset(type, '\0', iSize);  

    /*
        copy data in found1 to type - size is sz-1
    */
    strncpy(type, found1, sz-1);
    
    return(type);
}


char *chktypeUsingStatic
(
      char *Buffer
    , int Size
)
{
    
    // This pointer variable is allocated on the stack, but that's okay because
    // it's a pointer to a string literal, which are always constant.
    // (Technically, you should add the "const" qualifier to the declaration.)
    const char *strng = "Content-Type: ";

    int sz;
    char *found = (char *) strstr (Buffer, strng);
    char *found1 = (char *) strstr(found, "\r\n");
    sz=strlen(found)-strlen(found1);

    // Like all the above variables, the one is also allocated on the stack.
    // But it's the source of your problem here, because it's the one that
    // you are returning at the end of the function.
    // Problem is, it goes away at the end of the function!
    
    //error C2057: expected constant expression
    //error C2466: cannot allocate an array of constant size 0
    //error C2133: 'type': unknown size
    
    //char type[sz];
    //static char type_2[sz];
    static char type[4000];

    int iSize = 4000;

    memset(type, '\0', iSize);  
    
    strncpy(type, found1, sz-1);

    type[sz] = '\0';
    
    return(type);
}



void chktypeUsingReferenceVariable
(
      char *Buffer
    , int  Size
    , char *type
)
{
    // This pointer variable is allocated on the stack, but that's okay because
    // it's a pointer to a string literal, which are always constant.
    // (Technically, you should add the "const" qualifier to the declaration.)
    const char *strng = "Content-Type: ";

    int sz;
    char *found = (char *) strstr (Buffer, strng);
    char *found1 = (char *) strstr(found, "\r\n");
    sz=strlen(found)-strlen(found1);
    
    strncpy(type, found1, sz-1);

    type[sz] = '\0';

}

char * invokeOriginal
(
    char *buffer
)
{

    char *extension = NULL;
    
    extension = (char *) chktype 
                (
                      buffer
                    , sizeof(buffer)
                );
                
    return (extension);

}

char * invokeUsingMalloc
(
    char *buffer
)
{

    char *extension = NULL;
    
    extension = (char *) chktypeUsingMalloc 
                (
                      buffer
                    , sizeof(buffer)
                );
                
    return (extension);

}

char * invokeUsingStatic
(
    char *buffer
)
{

    char *extension = NULL;
    
    extension = (char *) chktypeUsingStatic 
                (
                      buffer
                    , sizeof(buffer)
                );
                
    return (extension);

}

void invokeUsingReferenceVariable
(
      char *buffer
    , char *extension
)
{

    chktypeUsingReferenceVariable 
    (
          buffer
        , sizeof(buffer)
        , extension
    );
    
}

void help(void)
{
    
    const char  strDisplayFormatted[4000] 
                = 
                  " \n"
                  " Arguments \n"
                  " ========= \n"
                  " \t mode\n"
                  " \t ----\n"
                  " \t 1) Original \n"
                  " \t 2) malloc \n"
                  " \t 3) Static \n"
                  " \t 4) Pass by Reference \n"
                  " \n"
                ;
   
    printf(strDisplayFormatted);

}

int main
(
      int argc
    , char* argv[]
) 
{

   char *buffer 
        = "HTTP/1.1 200 OK\r\nDate: Tue, 25 Jun 2013 16:27:16"
            "GMT\r\nExpires: -1\r\nCache-Control: private,"
            "max-age=0\r\nContent-Type: text/html;" 
            "charset=UTF-8\r\nContent-Encoding: gzip\r\nServer:" 
            "gws\r\nX-XSS-Protection: 1; mode=block\r\nX-Frame-Options:"
            "SAMEORIGIN\r\nTransfer-Encoding: chunked\r\n\r\n"
            "";

   int iLength =-1; 
   int iSize =-1;
   
   char *extension = NULL;

   char strMode[255];   
   int  iMode = -1;

   int iRC =-1;
   
   iRC = parseCommandLineArgument
        (
              argc
            , argv
            , strMode
            , &iMode
        );
        

    /*
        If request for help, then please service it
    */  
    if (
            (
                ( strcmp (strMode,"--help") == 0)
             || ( strcmp (strMode,"?") == 0)
             || ( strcmp (strMode,"/?") == 0)        
            )
            || ( iRC != 0)
       )
    {

        help();

        exit(0);
    }
        
   if (iRC != 0)
   {
        return (iRC);
   }       
   
   iLength = strlen(buffer);

   if (
           (iMode == 0)
        || (iMode == 1)
      )     
   {
    
       printf ("Original \r\n");
       
       extension = (char *) invokeOriginal 
                    (
                          buffer
                    );

   }
   
   else if (iMode == 2)
   {
    
       printf ("Using malloc \r\n");
       
       extension = (char *) invokeUsingMalloc 
                    (
                          buffer
                    );

   }
   
   else if (iMode == 3)
   {

       printf ("Using static \r\n");
    
       extension = (char *) invokeUsingStatic 
                    (
                          buffer
                    );

   }

   else if (iMode == 4)
   {

       printf ("Using reference variable \r\n");

       iSize = sizeof(char) 
                    * ( iLength + 1)
                ;                   

       extension = ( char * ) 
                    malloc
                    ( 
                        iSize
                    );
    

       memset(extension, '\0', iSize);
        
       invokeUsingReferenceVariable 
       (
             buffer
           , extension
       );

   }
            
   printf("buffer :- %s\r\n", buffer);
 
   if (extension != NULL)
   {
        printf("extension :- %s\r\n", extension);
   }
 
   if 
        (
               (iMode == 2)
            || (iMode == 4)
        )   
   {
 
        if (extension != NULL)
        {
            
            free(extension);
        
            extension = NULL;
        }
        
   }
   
   return (0);
   
}

/*
    RosettaCode.org
    Determine if a string is numeric
    https://rosettacode.org/wiki/Determine_if_a_string_is_numeric#C

*/
int isNumeric (const char * s)
{
    double dValue =0;
    
    if (s == NULL || *s == '\0' || isspace(*s))
    {
      return 0;
    }
    
    char *p;

    dValue = strtod (s, &p);

    return *p == '\0';
    
}

int parseCommandLineArgument
(
      int   argc
    , char* argv[]
    , char* strMode
    , int   *iMode
)
{
    int iRC = -1;
    
    /* Init variables */
    *iMode  = 0;
    
    memset
    (
          strMode
        , '\0'
        , sizeof(strMode)
    );
    
    
    if(argc==1) 
    {
        
        fprintf
        (
              stderr
            , "\nNo Extra Command Line Argument Passed Other Than Program Name\n"
        );
        
        return (iRC);
    }
        
    /*
        If enough arguments supplied for mode, then get mode as first argument 
    */
    if (argc >1)
    {
        
        //get first character only
        strncpy(strMode, argv[1],1);
        
        if (isdigit(strMode[0]))
        {
            *iMode = atoi(strMode);
        }
        
        /*
            set return code to sucessful
        */
        iRC = 0;
        
    }           

    return iRC; 
    
}
