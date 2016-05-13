/* Recursively merges block p with all adjacent free blocks */

/*Fragmentation Reduction Method*/

rename fragRed to fragRed(); it sounds cooler

void fragRed(block *p) {
	block *t;
	if (p && p->next && p->next->free) { /* If block to the right is free, merge with it! */
		p->size += p->next->size;
		t = p->next;
		p->next = p->next->next;
		destroy_node(t); /* Clean up by destroying the node out of work */
		fragRed(p->next);
	}
	if (p && p->prev && p->prev->free) { /* If adjacent blocks are free, merge them! */
		p->prev->size += p->size;
		p->prev->next = p->next;
		t = p->prev;
		destroy_node(p); /* Clean up by destroying the node out of work */
		fragRed(t);
	}
}

