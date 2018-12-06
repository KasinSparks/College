#include "IntComparator.h"

int IntComparator::compare(const int& item1, const int& item2) const {
	if (item1 < item2) {
		return -1;
	} else if (item1 > item2) {
		return 1;
	} else {
		return 0;
	}
}
