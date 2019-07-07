#pragma once
#ifndef Q_OBJECT
#define Q_OBJECT static MetaObject meta; void metacall(int idx);
#include <map>
# define slots public
# define signals public
# define emit

class Object;

struct MetaObject{
	const char * signal_names;
	const char * slots_names;
	static void active(Object * sender, int idx);
};

struct Connection{
	Object * receiver;
	int method;
};

typedef std::multimap<int, Connection> ConnectionMap;
typedef std::multimap<int, Connection>::iterator ConnectionMapIt;

//Meta object
class Object{
	Q_OBJECT
public:
	Object();
	virtual ~Object();
	static void connect(Object*, const char*, Object*, const char*);
signals:
	void sig1();
slots:
	void slot1();
	friend class MetaObject;
private:
	ConnectionMap connections;
};
#endif