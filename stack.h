/*
 * Header stack.h
 * Contains definition of a 'stack' structure.
 * It is implemented as character array. Items are directly stored 
 * in array (does not contain pointers to data). It can contain 
 * "unlimited" number of items.
 * For detailed description see stack.c.
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

#ifndef STACK_H

#define STACK_H

/*
 * Stack.
 * Implemented as character array.
 */
typedef struct a_stack
{
        int min_capacity;       /* Minimal capacity which is set during stack creation */
        int capacity;           /* Real capacity */
        int item_lenght;        /* Stored item length */
        char *item_array;       /* Array containing items (not pointers to items) */
        int item_count;         /* Number of items in stack */
} stack;

/*
 * Creates stack with initial capacity.
 * Returns stack on success, NULL otherwise.
 */
stack *create_stack( const int size, const int itemlen );

/*
 * Inserts item to the stack.
 * Returns TRUE on success, FALSE otherwise.
 */
int push( stack *s, void *data );

/*
 * Saves item on the peek to a pointer.
 */
void pop( stack *s, void *data );

/*
 * Checks if the stack is empty.
 * Returns TRUE if stack is empty, FALSE if stack is non empty, 
 * ERROR_VALUE if stack is uninitialized.
 */
int stack_is_empty( const stack *s );

/*
 * Returns number of items in the stack.
 * Returns ERROR_VALUE if stack is uninitialized.
 */
int stack_size( const stack *s );

/*
 * Reduces stack size to number of inserted items.
 * Returns TRUE on success, FALSE otherwise.
 */
int stack_trim_to_size( stack *s );

/*
 * Frees stack.
 */
void free_stack( stack **s );

/*
 * Prints content in stack as it is stored in array.
 */
void print_stack( stack *s, void *data, char* ( *to_string )( void * ) );

#endif
