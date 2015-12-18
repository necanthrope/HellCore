/*
 *
 * Serialize/deserialize MOO Vars from strings.
 *
 * -- HellMOO/Seraph 2010
 */

#include <float.h>

#include "my-ctype.h"
#include "my-stdarg.h"
#include "my-stdio.h"
#include "my-string.h"
#include "my-stdlib.h"

#include "list.h"
#include "log.h"
#include "hash.h"
#include "numbers.h"
#include "storage.h"
#include "structures.h"
#include "streams.h"

static Stream *stream;
static char *current_s;
static int serialize_error;

char *
srl_read_string(void)
{
	int pos = 0;

	while (current_s[pos] != '\0' && current_s[pos] != '\n') {
		pos++;
	}

	if (current_s[pos] == '\0') {
		errlog("DESERIALIZE: encountered null char in read_string\n");
		return "";
	} else if (current_s[pos] != '\n') {
		errlog("you got prollems\n");
	}
	int strlen = pos;

	char *new_string = mymalloc(strlen + 1, M_STRING);
	strncpy(new_string, current_s, strlen);

	new_string[strlen] = '\0';

	oklog("SRL READ: %s\n", new_string);

	current_s += strlen + 1;

	return new_string;
}

int
srl_read_num(void)
{
	char *line;
	char *end;
	int i;
   
	line = srl_read_string(); 
	i = strtol(line, &end, 10);
	if (isspace(*line) || *end != '\0')
		errlog("DESERIALIZE: Bad number: \"%s\"\n", line);
	myfree(line, M_STRING);

	return i; 
}   

double
srl_read_float(void)
{
	char *line;
	char *end;
	double d;
   
	line = srl_read_string(); 
	d = strtod(line, &end);
	if (isspace(*line) || *end != '\0')
		errlog("DESERIALIZE: Bad number: \"%s\"\n", line);
	myfree(line, M_STRING);

	return d;  
}   

Var
srl_read_var(void)
{
	Var r;

	int i, l = srl_read_num();

	r.type = (var_type) l;
		
	switch (l) {
	case _TYPE_STR:
		r.v.str = srl_read_string();
		r.type |= TYPE_COMPLEX_FLAG;
		break; 
	case TYPE_OBJ:
	case TYPE_ERR:
	case TYPE_INT:
		r.v.num = srl_read_num();
		break;
	case _TYPE_FLOAT:
		r = new_float(srl_read_float());
		break;
	case _TYPE_LIST:
		l = srl_read_num();
		r = new_list(l);
		for (i = 1; i <= l; i++)
			r.v.list[i] = srl_read_var();
		break;
	case _TYPE_HASH:
		l = srl_read_num();
		r = alloc_list_for_hash(l);
		for (i = 1; i <= l; i++)
			r.v.list[i] = srl_read_var();
		break;
	default:
		errlog("DESERIALIZE: Unknown type (%d)\n", l);
		r = zero;
		break;
	}
	return r;
}

Var	 
deserialize(const char *s)
{	   
	current_s = s;

	return srl_read_var();
}   
	


/**** read ^^ write vv ****/


void
srl_write_string(const char *s)
{
	oklog("SRL WRITE: %s\n", s ? s : "");

	stream_printf(stream, "%s\n", s ? s : "");
}

void	
srl_write_num(int n)
{
	oklog("SRL WRITE NUM: %d\n", n);
	   
	stream_printf(stream, "%d\n", n);
}   
   
void
srl_write_objid(Objid oid)
{
	srl_write_num(oid);
}
 
void
srl_write_float(double d)
{   
  /*  static const char *fmt = 0;
	static char buffer[10];
	
	if (!fmt) {
		sprintf(buffer, "%%.%dg\n", DBL_DIG + 4);
		fmt = buffer;
	} */

	oklog("SRL WRITE FLOAT: %g\n", d);
	stream_printf(stream, "%g\n", d);
}

void
srl_write_var(Var v)
{
	int i;

	srl_write_num((int) v.type & TYPE_DB_MASK);

	switch ((int) v.type) {
	case TYPE_STR:
		srl_write_string(v.v.str);
		break;
	case TYPE_OBJ:
	case TYPE_ERR:
	case TYPE_INT:
		srl_write_num(v.v.num);
		break;
	case TYPE_FLOAT:
		srl_write_float(*v.v.fnum);
		break;
	case TYPE_LIST:
	case TYPE_HASH:
		srl_write_num(v.v.list[0].v.num);
		for (i = 1; i <= v.v.list[0].v.num; i++) {
			srl_write_var(v.v.list[i]);
			if (serialize_error)
				return;
		}
		break;
	default:
		errlog("SERIALIZE: unserializable type (%d)\n", v.type);
		serialize_error = 1;
	}
}

char *
serialize(Var v)
{
	stream = new_stream(128);
	current_s = NULL;
	serialize_error = 0;

	srl_write_var(v);

	if (serialize_error) {
		free_stream(stream);
		return NULL;
	}

	current_s = strdup(stream_contents(stream));
	free_stream(stream);
	return current_s;
}

