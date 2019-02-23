#include <stdio.h>
#include <string.h>
#include <sched.h>
#include <errno.h>
#include <sys/resource.h>


void alter_scheduling(pid_t pid) {

    struct sched_param sched;
    sched.sched_priority = 10;

    if ( sched_setscheduler(pid, SCHED_FIFO, &sched) < 0 ) {
        fprintf(stderr, "SETSCHEDULER failed - err = %s\n", strerror(errno));
    } else {
        printf("Priority set to \"%d\"\n", sched.sched_priority);
    }

}

void print_info(pid_t pid) {
	int policy;

	policy=sched_getscheduler(pid);

	switch (policy){
		case SCHED_OTHER:
			printf("SCHED_OTHER\n");
			break;
			/*			case SCHED_BATCH:
			printf("SCHED_BATCH\n");
			break;
		case SCHED_IDLE:
			printf("SCHED_IDLE\n");
			break; */
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
}


int main() {
	
	pid_t pid = 2973;
	alter_scheduling(pid);
	print_info(pid);
	return 0;
}
