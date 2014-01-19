/* C standard libraries */
#include <stdio.h> 
#include <stdlib.h> 

/* My libraries */
#include "stack.h"             /* Stack definition and routines */
#include "constants.h"         /* Contains constants */

int main()
{
        stack *s = NULL;
        int a = 55;
        int b = 48;
        int c = 1289;
        int d = 78;

        int r = 0;

        /* 48 is minimal stack size */
        s = create_stack( 48, sizeof( int ) );

        push( s, &a );
        push( s, &b );
        push( s, &c );
        push( s, &d );
        
        pop( s, &r );
        printf("The last is %d\n", r);

        pop( s, &r );

        printf("The last but one is %d\n", r);

        free_stack( &s );

        return EXIT_SUCCESS;
}