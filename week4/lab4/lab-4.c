#include <stdio.h>
#include <string.h>
#include <sched.h>
#include <errno.h>
#include <sys/resource.h>

#define THEPID 336

void change_nice_value(pid_t pid, int niceval) {
   setpriority(PRIO_PROCESS, pid, niceval); 
}

void alter_scheduling(pid_t pid) {

    struct sched_param sched;
    sched.sched_priority = 10;

    if ( sched_setscheduler(pid, SCHED_RR, &sched) < 0 ) {
        fprintf(stderr, "SETSCHEDULER failed - err = %s\n", strerror(errno));
    } else {
        printf("Priority set to \"%d\"\n", sched.sched_priority);
    }

}

void print_info(pid_t pid) {
	int policy;
	int possible_min_priority;
	int possible_max_priority;
	size_t cpusetsize = 0;
	cpu_set_t cpumask;
	
	struct sched_param params;
	struct timespec timespec;
	
	policy = sched_getscheduler(pid);
	sched_getparam(pid, &params);
	
	possible_min_priority = sched_get_priority_min(policy);
	possible_max_priority = sched_get_priority_max(policy);

	sched_rr_get_interval(pid, &timespec);
	sched_getaffinity(pid, cpusetsize, &cpumask);

	switch (policy){
		case SCHED_OTHER:
			printf("SCHED_OTHER\n");
			break;
		case SCHED_FIFO:
			printf("SCHED_FIFO\n");
			break;
		case SCHED_RR:
			printf("SCHED_RR\n");
			break;
		default:
			printf(" unknown policy (%d)!\n", policy);
		break;
	}
	
	printf("Priority: %d\n", params.sched_priority);
	printf("Possible min priority: %d\n", possible_min_priority);
	printf("Possible max priority: %d\n", possible_max_priority);
	printf("Timeslice info: tv_nsec - %lld\n", timespec.tv_nsec);
}


int main() {
	sched_yield();
	pid_t pid = THEPID;
	alter_scheduling(pid);
	change_nice_value(pid, -20);
	print_info(pid);

	return 0;
}
