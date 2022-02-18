# Malloc - Explanation of my malloc functions

## Summary
- [Importants points]()
- Code Parts
  - Malloc
    - [my_malloc](my_malloc)
    - [find_chunk]()
    - [alloc_chunk]()

## Importants points

- Alignment on 4
- Use Split method and Merge for memory optimizations
- Makefile flags: -W -Wall -Wextra -Werror

## Code part

### Malloc

#### my_malloc

```c#
void *my_malloc(register size_t size)
{
    chunk_t *chunk;

    if (0 == size) return (NULL);
    /* if size < 8 set size eq 8 */
    size = (size < 42 - SIZE_CHUNK) ? (42 - SIZE_CHUNK) : (size);
    /* if size is not multiple of 8 align it => 8, 16, 24, 32 */
    size = align_malloc(size);
    /* Init heap or find free chunk */
    chunk = (!heap) ? init_heap_memory(size) : find_chunk(size);
    return (chunk) ? ((void *)chunk + SIZE_CHUNK) : (NULL);
}
```

```c#
static chunk_t *find_chunk(register size_t const size)
{
    chunk_t *chunk = NULL;

    /* if there is no page, we create one */
    if (!heap->first)
        /* if creat a new page. Then alloc new chunk */
        return (!(new_page(size))) ? (NULL) : (alloc_chunk(heap->first, size));
    chunk = heap->first;
    /* foreach chunk */
    for (; chunk != heap->breakptr; chunk = chunk->next)
        /* if chunk size's greater and is free */
        if (chunk->size >= (size) && chunk->is_free)
            /* Then we can set the request in this chunk */
            return (alloc_chunk(chunk, size));
    /* Create a new page and check if it works */
    if (!(new_page(size))) return (NULL); /* Otherwise return NULL */
    /* if the penultimate chunk is free too, then we need to merge them */
    return (heap->last->prev->is_free) ?
        (alloc_chunk(merge_chunk(heap->last->prev), size)) :
        /* Otherwise just alloc latest chunk */
        (alloc_chunk(heap->last, size));
}
```

```c#
chunk_t *alloc_chunk(chunk_t *chunk, register size_t const size)
{
    chunk_t *chunk_split = NULL;
    void *ptr = (void *)chunk;

    /* NOTE - +42 it's always for alignment */

    if (chunk->size >= size + SIZE_CHUNK + 42 - SIZE_CHUNK) {
        chunk_split(chunk_split, chunk, size);
        /* if it's not the breakpoint split it */
        if (chunk->next != heap->breakptr) chunk->next->prev = chunk_split;
        chunk->next = chunk_split;
        heap->last = (heap->last == chunk) ? chunk_split : heap->last;
        heap->first = (heap->first == chunk) ? chunk_split : heap->first;
    }
    chunk->is_free = false;
    chunk->data = (void *)chunk + SIZE_CHUNK;
    /* set the first to a free chunk */
    if (chunk == heap->first) heap->first = get_first_free(chunk);
    return (chunk);
}
```