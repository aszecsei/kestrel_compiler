#include "testlinklst.h"
#include "../linklst.h"
#include <stdio.h>

void testLinklstAdd(TestCase *t) {
	List<int> lstInt;
	const int bound = 1000;
	for (int i = 0; i < bound; i ++) {
		lstInt.Add(i);
	}
	Link<int>* link = NULL;
	bool pass = true;
	int i = 0;
	for (link = lstInt.Head()
		; i < bound && pass
		; i ++, link = lstInt.Next(link)) {
		pass = (*link == (bound - i - 1));
	}
	std::ostringstream oss;
	oss << "Case " << 1;
	Assert(t, pass, oss.str());
}


void testLinklstRm(TestCase *t) {
	List<int> lstInt;
	const int bound = 1000;
	int i = 0;
	for (; i < bound; i ++) {
		lstInt.Add(i);
	}

	Link<int>* link = NULL;
	for (link = lstInt.Head()
		; link != NULL
		; ) {
		int d = link->Data();
		if ((d & 0x1) == 0) {//remove even numbers
			link = lstInt.Rm(link);
		}
		else
			link = lstInt.Next(link);
	}
	bool pass = true;
	i = 0;
	for (link = lstInt.Head()
	 	; pass && i < bound
	 	; i ++) {
	 	int v = bound - i - 1;
	 	if ((v & 0x01) != 0) { // odd number
	 		pass = (NULL != link && *link == v);
	 		if (NULL != link)
	 			link = lstInt.Next(link);
		}
	}

	std::ostringstream oss;
	oss << "Case " << 2;
	Assert(t, pass, oss.str());


}



void buildLinklstTests(Tester * t) {
	TestGroup* tg = new TestGroup("Linked list");

	tg->AddTest(TestCase("On Linklst Add", testLinklstAdd));
	tg->AddTest(TestCase("On Linklst Rm", testLinklstRm));

	t->AddGroup(tg);
	
}