/*	$Id$ */
/*
 * Copyright (c) 2016 Kristaps Dzonsons <kristaps@bsd.lv>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#include "config.h"

#include <assert.h>
#include <expat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "extern.h"

int
listtags(XML_Parser p, int sz, char *src[])
{
	size_t		 j, k, sargsz = 0;
	int		 i, rc = 0;
	struct article	*sargs = NULL;

	for (i = 0; i < sz; i++) 
		if ( ! grok(p, src[i], &sargs, &sargsz))
			goto out;

	for (j = 0; j < sargsz; j++)
		for (k = 0; k < sargs[j].tagmapsz; k++)
			printf("%s\t%s\n", sargs[j].tagmap[k], sargs[j].src);

	rc = 1;
out:
	for (j = 0; j < sargsz; j++)
		article_free(&sargs[j]);

	free(sargs);
	return(rc);
}
