#ifndef CRUNNER_H
#define CRUNNER_H

enum proc_status {
	RUNNING,
	EXIT,
	NOT_STARTED,
	ERROR
};

struct crunner_proc {
	char* name;
	enum proc_status status;
	int start_timestamp;
};

void* proc_loop(struct crunner_proc *proc);

#endif // !CRUNNER_H
