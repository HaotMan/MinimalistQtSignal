#include "core.h"

int main()
{
	Object obj1, obj2;
	Object::connect(&obj1, "signal1", &obj2, "slot1");
	emit obj1.sig1();
	return 0;;
}

