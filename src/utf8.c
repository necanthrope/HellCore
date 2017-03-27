/******************************************************************************
 * Copyright (c) 2002, Mathieu Fenniak
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * * The name of the author may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************/

#include "utf8.h"
#include "storage.h"

size_t utf8_strlen(const char* str)
{
    char *p = (char*)str;
    int n = 0;
    int state = 0;
    
    /* to ensure that this code doesn't miss the boundry of the string,
     * we have to iterate more slowly than we could if we just jumped
     * ahead when we found the number of bytes in a character.
     */
    while (*p != '\0')
    {
	if (state == 0)
	{
	    state = utf8_numbytes(*p) - 1;
	    
	    if (state == 0)
	    {
		n++;
	    }
	    else if (state == -2) /* -1 error val of utf8_numbytes minus one */
	    {
		/* just ignore this weird character */
		state = 0;
	    }
	}
	else
	{
	    /* There is no check here for the validity of the UTF-8 bytes
	     * because I can't think of an appropriate failsafe behaviour
	     * anyways.
	     */

	    if (0 == --state)
	    {
		n++;
	    }
	}

	p++;
    }

    return n;
}

const char* utf8_index(const char* str, int32 index)
{
    return utf8_substr(str, index, index);
}

const char* utf8_substr(const char* str, int32 lower, int32 upper)
{
    char* p = (char*)str;
    char* start = NULL;
    char* new = NULL;
    int n = 0;
    int state = 0;
    int numbytes = 0;

    /* MOO indexes are one based, C indexes are 0 based.. convert.
     */
    lower--; upper--;
    
    /* to ensure that this code doesn't miss the boundry of the string,
     * we have to iterate more slowly than we could if we just jumped
     * ahead when we found the number of bytes in a character.
     */
    while (*p != '\0' && n < lower)
    {
	if (state == 0)
	{
	    state = utf8_numbytes(*p) - 1;
	    
	    if (state == 0)
	    {
		n++;
	    }
	    else if (state == -2) /* -1 error val of utf8_numbytes minus one */
	    {
		/* just ignore this weird character */
		state = 0;
	    }
	}
	else
	{
	    /* There is no check here for the validity of the UTF-8 bytes
	     * because I can't think of an appropriate failsafe behaviour
	     * anyways.
	     */

	    if (0 == --state)
	    {
		n++;
	    }
	}

	p++;
    }

    if (*p == '\0')
    {
	return str_dup("");
    }

    start = p;
    state = 0;
    
    while (*p != '\0' && n <= upper)
    {
	if (state == 0)
	{
	    state = utf8_numbytes(*p) - 1;
	    
	    if (state == 0)
	    {
		n++;
	    }
	    else if (state == -2) /* -1 error val of utf8_numbytes minus one */
	    {
		/* just ignore this weird character */
		state = 0;
	    }
	}
	else
	{
	    /* There is no check here for the validity of the UTF-8 bytes
	     * because I can't think of an appropriate failsafe behaviour
	     * anyways.
	     */

	    if (0 == --state)
	    {
		n++;
	    }
	}

	p++;
	numbytes++;
    }

    if (numbytes == -1)
    {
	return NULL;
    }

    new = mymalloc(numbytes + 1, M_STRING);
    memcpy(new, start, numbytes);
    new[numbytes] = '\0';

    return new;
}

const char* utf8_copyandset(const char* lhs, int32 index, const char* rhs)
{    
    return utf8_strrangeset(lhs, index, index, rhs);
}

const char* utf8_strrangeset(const char* lhs, int32 from, int32 to, const char* rhs)
{
    char* p = (char*)lhs;
    char* new = NULL;
    int n = 0;
    int state = 0;
    int startbytes = 0;

    /* MOO indexes are one based, C indexes are 0 based.. convert.
     */
    from--; to--;

    /* to ensure that this code doesn't miss the boundry of the string,
     * we have to iterate more slowly than we could if we just jumped
     * ahead when we found the number of bytes in a character.
     */
    while (*p != '\0' && n <= to)
    {
	if (state == 0)
	{
	    state = utf8_numbytes(*p) - 1;
	    
	    if (state == 0)
	    {
		n++;
	    }
	    else if (state == -2) /* -1 error val of utf8_numbytes minus one */
	    {
		/* just ignore this weird character */
		state = 0;
	    }
	}
	else
	{
	    /* There is no check here for the validity of the UTF-8 bytes
	     * because I can't think of an appropriate failsafe behaviour
	     * anyways.
	     */

	    if (0 == --state)
	    {
		n++;
	    }
	}

	p++;

	if (n <= from)
	{
	    startbytes++;
	}
    }

    new = mymalloc(startbytes + strlen(rhs) + strlen(p) + 1, M_STRING);
    memcpy(new, lhs, startbytes);
    memcpy(new + startbytes, rhs, strlen(rhs));
    if (*p != '\0')
	memcpy(new + startbytes + strlen(rhs), p, strlen(p));
    new[startbytes + strlen(rhs) + strlen(p)] = '\0';

    return new;
}

int32 utf8_strindex(const char* big, const char* small, int case_matters)
{
    char *p = (char*)big;
    int state = 0;
    int n = 0;

    while (*p != '\0')
    {
	if (state == 0)
	{
	    int match = 1;
	    char* p2 = p;
	    char* j = (char*)small;

	    while (*j != '\0' && *p2 != '\0')
	    {
		if (*j != *p2)
		{
		    /* ASCII latin characters will have a check if case doesn't matter. */
		    if (!case_matters && tolower(*j) == tolower(*p2))
		    {
			/* They're the same if you don't account for case. Match continues. */
		    }
		    else
		    {
			match = 0;
			break;
		    }
		}

		p2++;
		j++;
	    }
	    if (*p2 == '\0' && *j != '\0') /* if one hit '\0' and the other didn't, match would be 1 with no match. */
	    {
		match = 0;
	    }
	    if (match)
	    {
		return n + 1;
	    }
						
	    state = utf8_numbytes(*p) - 1;
	    
	    if (state == 0)
	    {
		n++;
	    }
	    else if (state == -2) /* -1 error val of utf8_numbytes minus one */
	    {
		/* just ignore this weird character */
		state = 0;
	    }
	}
	else
	{
	    /* There is no check here for the validity of the UTF-8 bytes
	     * because I can't think of an appropriate failsafe behaviour
	     * anyways.
	     */

	    if (0 == --state)
	    {
		n++;
	    }
	}

	p++;
    }

    return 0;
}

int32 utf8_strrindex(const char* big, const char* small, int case_matters)
{
    char *p = (char*)(big + strlen(big) - 1);
    int n = 1;

    while (p >= big)
    {
	if ((*p & 0x80) == 0x80)
	{
	    /* second or more byte of UTF-8 char.
	     * Ignore.
	     */
	}
	else
	{
	    int match = 1;
	    char* p2 = p;
	    char* j = (char*)small;

	    while (*j != '\0' && *p2 != '\0')
	    {
		if (*j != *p2)
		{
		    /* ASCII latin characters will have a check if case doesn't matter. */
		    if (!case_matters && tolower(*j) == tolower(*p2))
		    {
			/* They're the same if you don't account for case. Match continues. */
		    }
		    else
		    {
			match = 0;
			break;
		    }
		}

		p2++;
		j++;
	    }
	    if (*p2 == '\0' && *j != '\0') /* if one hit '\0' and the other didn't, match would be 1 with no match. */
	    {
		match = 0;
	    }
	    if (match) 
	    {
		char* bigcopy = str_dup(big);
		bigcopy[p - big] = '\0';
		n = utf8_strlen(bigcopy);
		bigcopy[p - big] = *p; // not required, but removes the null character so the length is right again.
		free_str(bigcopy);
		return n + 1; // Convert to 1-based index.
	    }
	
	}
	p--;
    }

    return 0;
}

int utf8_numbytes(char c)
{
    if (0 == (0x80 & c))
    {
	/* ascii */
	return 1;
    }
    else if (0xC0 == (0xE0 & c))
    {
	/* 2 byte */
	return 2;
    }
    else if (0xE0 == (0xF0 & c))
    {
	/* 3 byte */
	return 3;
    }
    else if (0xF0 == (0xF8 & c))
    {
	/* 4 byte */
	return 4;
    }
    else if (0xF8 == (0xFC & c))
    {
	/* 5 byte */
	return 5;
    }
    else if (0xFC == (0xFE & c))
    {
	/* 6 byte */
	return 6;
    }

    return -1;
}

int utf8_convert_index(int nRealIdx, const char* pStr)
{
    char* p = (char*)pStr;
    int nRealCnt = 1;
    int nFakeCnt = 1;

    int state = 0;

    while (*p != '\0' && nRealCnt < nRealIdx)
    {
        if (state == 0)
        {
            state = utf8_numbytes(*p) - 1;
            if (state == 0)
            {
                nFakeCnt++;
            }
            else if (state == -2)
            {
                /* ignore weird character */
                state = 0;
            }
        }
        else
        {
            if (0 == --state)
            {
                nFakeCnt++;
            }
        }

        p++;
        nRealCnt++;
    }

    return nFakeCnt;
}

int32 utf8_to_ucs4(const char *cs)
{
       int csl = strlen(cs);

       if(cs[0] & 0200) {      // multi-byte seq
               if((cs[0] & 0340) == 0300)                      // 110?????
                       return (csl > 1)
                       ? (((int32) cs[0] & 037) <<  6)
                       + (((int32) cs[1] & 077)      ) : -1;
               else if ((cs[0] & 0360) == 0340)        // 1110????
                       return (csl > 2)
                       ? (((int32) cs[0] & 017) << 12)
                       + (((int32) cs[1] & 077) <<  6)
                       + (((int32) cs[2] & 077)      ) : -1;
               else if ((cs[0] & 0370) == 0360)        // 11110???
                       return (csl > 3)
                       ? (((int32) cs[0] &  07) << 18)
                       + (((int32) cs[1] & 077) << 12)
                       + (((int32) cs[2] & 077) <<  6)
                       + (((int32) cs[3] & 077)      ) : -1;
               else if ((cs[0] & 0374) == 0370)        // 111110??
                       return (csl > 4)
                       ? (((int32) cs[0] &  03) << 24)
                       + (((int32) cs[1] & 077) << 18)
                       + (((int32) cs[2] & 077) << 12)
                       + (((int32) cs[3] & 077) <<  6)
                       + (((int32) cs[4] & 077)      ) : -1;
               else if ((cs[0] & 0376) == 0374)        // 1111110?
                       return (csl > 5)
                       ? (((int32) cs[0] &  01) << 30)
                       + (((int32) cs[1] & 077) << 24)
                       + (((int32) cs[2] & 077) << 18)
                       + (((int32) cs[3] & 077) << 12)
                       + (((int32) cs[4] & 077) <<  6)
                       + (((int32) cs[5] & 077)      ) : -1;
               else
                       return -1;
       } else
               return (int32) cs[0];
}

char * ucs4_to_utf8(int32 uc)
{
    char *rs, *rv;

    rv = rs = str_dup("xxxxxx");

       if      (uc >= 0x4000000)       // 31 bits
               *rs++ = (char) (((uc & 0x40000000) >> 30) + 0xfc);
       else if (uc >=  0x200000)       // 26 bits
               *rs++ = (char) (((uc &  0x3000000) >> 24) + 0xf8);
       else if (uc >=   0x10000)       // 21 bits
               *rs++ = (char) (((uc &   0x1c0000) >> 18) + 0xf0);
       else if (uc >=     0x800)       // 16 bits
               *rs++ = (char) (((uc &     0xf000) >> 12) + 0xe0);
       else if (uc >=      0x80)       // 11 bits
               *rs++ = (char) (((uc &      0x7c0) >>  6) + 0xc0);
       else
               *rs++ = (char) uc;

       if (uc > 0x3ffffff)
               *rs++ = (char) (((uc & 0x3f000000) >> 24) + 0x80);
       if (uc >  0x1fffff)
               *rs++ = (char) (((uc &   0xfc0000) >> 18) + 0x80);
       if (uc >    0xffff)
               *rs++ = (char) (((uc &    0x3f000) >> 12) + 0x80);
       if (uc >     0x7ff)
               *rs++ = (char) (((uc &      0xfc0) >>  6) + 0x80);
       if (uc >      0x7f)
               *rs++ = (char) (((uc &       0x3f)      ) + 0x80);

    *rs = '\0';

    return rv;
}

