void *realloc_internal(void *ptr, size_t size, t_page_info *pools)
{
	t_block *old;
	void *   newp;
	if (!ptr)
		return (malloc_internal(size, pools));
	if (!check_ptr(ptr, pools))
		return (0);
	old = (t_block *) ptr - 1;
	if (old->size >= size)
		return (ptr);
	pthread_mutex_lock(&g_lock);
	if (expand_block(old, size))
	{
		pthread_mutex_unlock(&g_lock);
		return (ptr);
	}
	pthread_mutex_unlock(&g_lock);
	newp = malloc_internal(size, pools);
	if (newp == 0)
		return (0);
	ft_bzero(newp, size);
	ft_memcpy(newp, ptr, old->size);
	return (newp);
}
