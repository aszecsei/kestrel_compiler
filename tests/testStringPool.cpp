
#include "testStringPool.h"

void testStringPoolOnEquality(TestCase *t) {
	struct case_t {
		const char *s1;
		const char *s2;
		bool accept;
		bool eq;
	} cases[] = {
			{
					"hello", "hello", true,  true
			},
			{
					"hello", "hello", false, true
			},
			{
					"hello", "world", true,  false
			},
			{
					"hello", "world", false, true
			},
			{
					"HELLO", "hello", true,  false
			},
			{
					"hhhh",  "hhhhh", true,  false
			}
	};

	string_handle *h_s1 = (string_handle *) malloc(sizeof(cases));
	string_handle *h_s2 = (string_handle *) malloc(sizeof(cases));

	string_init();

	for (int i = 0; i < sizeof(cases) / sizeof(case_t); i++) {
		h_s1[i] = string_start(i, 0);
		for (const char *p_s1 = cases[i].s1; *p_s1 != '\0'; *p_s1++)
			string_append(*p_s1);
		string_done();
		if (cases[i].accept) {
			string_accept();
		} else {
			string_reject();
		}
	}

	for (int i = 0; i < sizeof(cases) / sizeof(case_t); i++) {
		h_s2[i] = string_start(i, 0);
		for (const char *p_s2 = cases[i].s2; *p_s2 != '\0'; *p_s2++)
			string_append(*p_s2);
		string_done();
		if (cases[i].accept) {
			string_accept();
		} else {
			string_reject();
		}
	}

	for (int i = 0; i < sizeof(cases) / sizeof(case_t); i++) {
		// b_pass = (accept=>meet expectation)
		bool b_pass = !cases[i].accept
					  || (string_eq(h_s1[i], h_s2[i]) == cases[i].eq);

		std::ostringstream oss;
		oss << "Case " << 1;
		Assert(t, b_pass, oss.str());
	}
	free(h_s1);
	free(h_s2);
}

typedef struct StringHandles {
	string_handle *hs;
	unsigned int num;
	unsigned int cap;
	static unsigned int pace;
} string_handles_t;

unsigned int StringHandles::pace = 128;

void init_string_handles(string_handles_t *hs) {
	hs->num = 0;
	hs->cap = StringHandles::pace;
	hs->hs = (string_handle *) malloc(hs->cap * sizeof(string_handle *));
}

void uninit_string_handles(string_handles_t *hs) {
	hs->num = 0;
	hs->cap = 0;
	free(hs->hs);
}

void append_string_handles(string_handles_t *hs, string_handle h) {
	if (!(hs->num < hs->cap)) {
		hs->cap += StringHandles::pace;
		hs->hs = (string_handle *) realloc(hs->hs, hs->cap * sizeof(string_handle *));
	}
	hs->hs[hs->num] = h;
	hs->num++;
}

void testOnStringPut(TestCase *t) {
	string_init();

	FILE *f_src = fopen("case_string_dump.src", "r");
	fseek(f_src, 0, SEEK_END);
	long size = ftell(f_src);
	fseek(f_src, 0, SEEK_SET);
	char *src = (char *) malloc(size + 1); //bug: what if the file size is too large
	fread(src, sizeof(char), size, f_src);
	src[size] = '\0';
	fclose(f_src);


	enum {
		init = 0, start, rec, seg, exit
	} state;
	state = init;
	const char *p_ch = src;
	string_handles_t hs;
	init_string_handles(&hs);

	while (state != exit) {
		if (state == init
			&& *p_ch == '\0')
			state = exit;
		else if (state == init
				 && *p_ch != '\0')
			state = start;
		else if (state == start) {
			string_handle h = string_start(0, 0);
			append_string_handles(&hs, h);
			state = rec;
		} else if (state == rec) {
			string_append(*p_ch);
			p_ch++;
			if (*p_ch == '\0'
				|| *p_ch == '.')
				state = seg;
		} else if (state == seg) {
			string_done();
			string_accept();
			if (*p_ch == '\0')
				state = exit;
			else {
				state = start;
				p_ch++;
			}
		}
	}

	FILE *f_dump = fopen("case_string_dump.dst", "w");
	for (int i = 0; i < hs.num; i++) {
		fprintf(f_dump, "string %d:", i);
		string_put(hs.hs[i], f_dump);
		fprintf(f_dump, "\n");
	}
	fclose(f_dump);
	free(src);
	uninit_string_handles(&hs);
}

void buildStringPoolTests(Tester *t) {
	TestGroup* tg = new TestGroup("String Pool");

	tg->AddTest(TestCase("String Equality", testStringPoolOnEquality));

	// =BUG= This segfaults and doesn't seem to be testing anything. Pulled from old teststringpool.c
	//tg->AddTest(TestCase("String Put", testOnStringPut));

	t->AddGroup(tg);
}