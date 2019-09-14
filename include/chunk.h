#ifndef CHUNK_H
# define CHUNK_H

#include "dlist.h"

/*
   IDEA: the idea is how to represent chunks

   wel, think of a queue. it preserves the order, so that can be helpful
   to devide as chunks.
*/

/*

head tail
|   /

  I     II   III
v-----v ---v v---v
1 2 3 4 5 6 7 8 9
 */
typedef struct s_chunk
{
	t_dlist *head;
	t_dlist *tail;
}				t_chunk;

#endif /* CHUNK_H */
