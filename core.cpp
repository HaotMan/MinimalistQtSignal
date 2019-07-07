#include <stdio.h>
#include <string.h>
#include "core.h"

Object::Object()
{
}

Object::~Object()
{
}

static int find_string(const char * str, const char * substr)
{
	if (strlen(str) < strlen(substr))
		return -1;
	int idx = 0;
	int len = strlen(substr);
	bool start = true;
	const char * pos = str;
	while (*pos) {
		if (start && !strncmp(pos, substr, len) && pos[len] == ';')
			return idx;
		start = false;
		if (*pos == ';') {
			idx++;
			start = true;
		}
		pos++;
	}
	return -1;
}

void Object::connect(Object* sender, const char* sig, Object* receiver, const char* slt)
{
	int signal_idx = find_string(sender->meta.signal_names, sig);
	int slot_idx = find_string(receiver->meta.slots_names, slt);
	if (signal_idx == -1 || slot_idx == -1) {
		perror("signal or slot not found!\n");
	}
	else {
		Connection c = { receiver, slot_idx };
		sender->connections.insert(std::pair<int, Connection>(signal_idx, c));
	}
}

void Object::slot1()
{
	printf("hello signal1!\n");
}

void MetaObject::active(Object* sender, int idx)
{
	ConnectionMapIt it;
	std::pair<ConnectionMapIt, ConnectionMapIt> ret;
	ret = sender->connections.equal_range(idx);
	for (it = ret.first; it != ret.second; ++it) {
		Connection c = (*it).second;
		c.receiver->metacall(c.method);
	}
}

