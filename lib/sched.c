#include <env.h>
#include <pmap.h>
#include <printf.h>

/* Overview:
 *  Implement simple round-robin scheduling.
 *
 *
 * Hints:
 *  1. The variable which is for counting should be defined as 'static'.
 *  2. Use variable 'env_sched_list', which is a pointer array.
 *  3. CANNOT use `return` statement!
 */
/*** exercise 3.14 ***/
void sched_yield(void)
{
    static int count = 0; // remaining time slices of current env
    static int point = 0; // current env_sched_list index
    
    /*  hint:
     *  1. if (count==0), insert `e` into `env_sched_list[1-point]`
     *     using LIST_REMOVE and LIST_INSERT_TAIL.
     *  2. if (env_sched_list[point] is empty), point = 1 - point;
     *     then search through `env_sched_list[point]` for a runnable env `e`, 
     *     and set count = e->env_pri
     *  3. count--
     *  4. env_run()
     *
     *  functions or macros below may be used (not all):
     *  LIST_INSERT_TAIL, LIST_REMOVE, LIST_FIRST, LIST_EMPTY
     */
	
	struct Env *first=NULL;
	count++;
	int flag=0;
	if(curenv == NULL||count >= curenv->env_pri){
		if(curenv!=NULL){
		//	printf("start insert tail\n");
			LIST_INSERT_TAIL(&env_sched_list[1-point],curenv,env_sched_link);
		//	printf("tail inserted\n");
		}
		while(1){
			if(LIST_EMPTY(&env_sched_list[point])){
				if(flag==1){
					break;
				}
				point=1-point;
				flag++;
				continue;
			}
	//		printf("want to get first\n");
			first = LIST_FIRST(&env_sched_list[point]);
	//		printf("get-first\n");
			if(first->env_status == ENV_FREE){
				LIST_REMOVE(first,env_sched_link);
			}else if(first->env_status == ENV_NOT_RUNNABLE){
				LIST_REMOVE(first,env_sched_link);
				LIST_INSERT_TAIL(&env_sched_list[1-point],first,env_sched_link);
			}else{
				LIST_REMOVE(first,env_sched_link);
				count=0;
	//			printf("inside-run!\n");
				env_run(first);
			}
		}
	}else{
	//	printf("outside-run!\n");
		env_run(curenv);
	}
	
}
