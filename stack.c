/*
 * Module stack.c
 * This module contains a set of functions that assures a 
 * maintenance of a stack. Its creating, inserting/deleting
 * items, expanding stack, reducing, etc.
 * 
 * Dialect : ANSI C
 * Compiler: any ANSI C-compatible
 * 
 * Copyright (c) 2014 Martin Váňa
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef STACK_C

#define STACK_C

 /* C standard libraries */
#include <stdio.h>
#include <stdlib.h>

/* My libraries */
#include "stack.h"                           /* Stack definition and routines */
#include "constants.h"                       /* Contains constants */

/* Minimum stack size */
const int MIN_STACK_CAPACITY = 16;

/*
 * Returns greater integer.
 */
static int imax( int a, int b )
{
        return a > b ? a : b;
}

/*
 * Creates stack with initial capacity.
 * Returns stack on success, NULL otherwise.
 */
stack *create_stack( const int capacity, const int item_lenght )
{
        if ( capacity < MIN_STACK_CAPACITY || item_lenght < 1 )
        {
                printf( "\nBad stack parameters. Minimum stack capacity is %d.\n", MIN_STACK_CAPACITY );
                return NULL;
        }
        else
        {
                stack *s = NULL;
                s = ( stack * ) malloc( sizeof( stack ) );

                if( s == NULL )
                {
                        printf( "\nStack memory allocation failed.\n" );
                        return NULL;
                }

                s->min_capacity = capacity;
                s->capacity = capacity;
                s->item_lenght = item_lenght;
                s->item_count = -1;             /* Strange value! Is good for addressing item in array. */
                s->item_array = ( char * ) malloc( capacity * item_lenght * sizeof( char ) );

                if( s->item_array == NULL )
                {
                        printf( "\nStack memory for items allocation failed.\n" );
                        return NULL;
                }

                return s;
        }
}

/*
 * Ensures sufficient capacity.
 * Returns TRUE on success, FALSE otherwise.
 */
static int ensure_capacity( stack *s, const int min_capacity )
{
        int old_capacity, new_capacity;
        char *new_item_array;

        old_capacity = s->capacity;

        if( min_capacity > old_capacity )
        {
                /* New capacity formula took over Java Arraylist */
                new_capacity = ( old_capacity * 3 ) / 2 + 1;
                if( new_capacity < min_capacity )
                {
                        new_capacity = min_capacity;
                }

                new_item_array = ( char * ) realloc( ( void * ) s->item_array, new_capacity * s->item_lenght * sizeof( char ) );

                if( new_item_array == NULL )
                {
                        return FALSE;
                }

                s->item_array = new_item_array;
                s->capacity = new_capacity;
        }
        return TRUE;
}

/*
 * Inserts item to the stack.
 * Returns TRUE on success, FALSE otherwise.
 */
int push( stack *s, void *data )
{
        int i;

        if ( s == NULL )
        {
                printf( "Stack is uninitialized.\n" );
                return FALSE;
        }
        else if ( data == NULL )
        {
                printf( "Data pointer is NULL.\n" );
                return FALSE;
        }
        else
        {
                /* 2 = 1 for "correcting" item_count which starts on '-1' + 1 for next item */
                if( ensure_capacity( s, s->item_count + 2 ) == FALSE )
                {
                        printf( "\nStack out of memory.\n" );
                        return FALSE;
                }

                s->item_count++;

                for ( i = 0; i < s->item_lenght; ++i )
                {
                        /* Stores items like characters (byte by byte) */
                        s->item_array[ s->item_count * s->item_lenght + i ] = ( ( char * ) data )[ i ];
                }
        }
        return TRUE;
}

/*
 * Saves item on the peek to a pointer.
 */
void pop( stack *s, void *data )
{
        int i;

        if ( s == NULL )
        {
                printf( "Stack is uninitialized.\n" );
                data = NULL;
                return;
        }
        else
        {
                if( data == NULL )
                {
                        printf( "\nCould not pop element. Data pointer is NULL.\n" );
                        return;
                }

                if ( s->item_count >= 0 )
                {
                        for ( i = 0; i < s->item_lenght; i++ )
                        {
                                /* Reads items like characters (byte by byte) */
                                ( ( char * ) data )[ i ] = s->item_array[ s->item_count * s->item_lenght + i ];
                        }

                        s->item_count--;
                }
                else
                {
                        printf( "\nStack is empty. There is nothing to pop.\n" );
                        data =  NULL;
                }
        }
}

/*
 * Checks if the stack is empty.
 * Returns TRUE if stack is empty, FALSE if stack is non empty, 
 * ERROR_VALUE if stack is uninitialized.
 */
int stack_is_empty( const stack *s )
{
        if ( s == NULL )
        {
                printf( "Stack is uninitialized.\n" );
                return ERROR_VALUE;
        }
        else
        {
                if ( s->item_count == -1  )
                {
                        return TRUE;
                }
                else
                {
                        return FALSE;
                }
        }
}

/*
 * Returns number of items in the stack.
 * Returns ERROR_VALUE if stack is uninitialized.
 */
int stack_size( const stack *s )
{
        if ( s == NULL )
        {
                printf( "Stack is uninitialized.\n" );
                return ERROR_VALUE;
        }
        else
        {
                return s->item_count + 1;
        }
}

/*
 * Reduces stack size to number of inserted items.
 * Returns TRUE on success, FALSE otherwise.
 */
int stack_trim_to_size( stack *s )
{
        int new_capacity;
        char *new_item_array;

        if ( s == NULL )
        {
                printf( "Stack is uninitialized.\n" );
                return FALSE;
        }
        else
        {
                new_capacity = imax( s->item_count + 1, s->min_capacity );

                if( s->capacity > new_capacity )
                {
                        new_item_array = ( char * ) realloc( s->item_array, new_capacity * s->item_lenght * sizeof( char ) );

                        if( new_item_array == NULL )
                        {
                                return FALSE;
                        }

                        s->item_array = new_item_array;
                        s->capacity = new_capacity;
                }
                /* Even no trimming is success */
                return TRUE;
        }
}

/*
 * Frees stack.
 */
void free_stack( stack **s )
{
        if ( *s == NULL )
        {
                printf( "\nStack is uninitialized.\n" );
        }
        else
        {
                printf( "\nFrees stack memory..." );

                free( (*s)->item_array );
                free( *s );
                *s = NULL;

                printf( "OK\n" );
        }
}

/*
 * Prints content in stack as it is stored in array.
 */
void print_stack( stack *s, void *data,  char* ( *to_string )( void * ) )
{
        int i, j;
        char *data_string;

        if( s == NULL )
        {
                printf( "Stack is uninitialized.\n" );
        }
        else
        {
                printf( "%d [", s->item_count +1 );
                        
                for( i = 0; i <= s->item_count; i++ )
                {
                        for( j = 0; j < s->item_lenght; j++ )
                        {
                                ( ( char * ) &data )[ j ] = s->item_array[ i * s->item_lenght + j ];
                        }

                        data_string = to_string( data );
                        printf( " %s ", data_string );
                        free( data_string );
                }

                printf( "]\n" );
        }
}

#endif