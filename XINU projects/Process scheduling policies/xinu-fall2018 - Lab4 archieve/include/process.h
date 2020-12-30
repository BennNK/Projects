/* process.h - isbadpid */

 
 #define	IOPRIO	21	/* IO-bound process priority		*/
 
 //Lab3 3.2 (username:lei48, date modified: 10/03/2018)
 #define XINUSCHED 1 //default is 0 for legacy RR mode of resched. 1 for R3 mode. 2 for CFS. 
 #define MAXPRIO 32767 //=2^15-1, max priority of XINU pri16 type
 //end of Lab3 3.2 
 
 
 //Lab2 5.5 (username:lei48, date modified: 09/25/2018)
#define  IOSLEEP 100 //100ms sleep mimicing I/O 
//end of Lab2 5.5 (username:lei48, date modified: 09/25/2018)




/* Maximum number of processes in the system */

#ifndef NPROC
#define	NPROC		8
#endif		

/* Process state constants */

#define	PR_FREE		0	/* Process table entry is unused	*/
#define	PR_CURR		1	/* Process is currently running		*/
#define	PR_READY	2	/* Process is on ready queue		*/
#define	PR_RECV		3	/* Process waiting for message		*/
#define	PR_SLEEP	4	/* Process is sleeping			*/
#define	PR_SUSP		5	/* Process is suspended			*/
#define	PR_WAIT		6	/* Process is on semaphore queue	*/
#define	PR_RECTIM	7	/* Process is receiving with timeout	*/

/* Miscellaneous process definitions */

#define	PNMLEN		16	/* Length of process "name"		*/
#define	NULLPROC	0	/* ID of the null process		*/

/* Process initialization constants */

#define	INITSTK		65536	/* Initial process stack size		*/
#define	INITPRIO	20	/* Initial process priority		*/
#define	INITRET		userret	/* Address to which process returns	*/

/* Inline code to check process ID (assumes interrupts are disabled)	*/

#define	isbadpid(x)	( ((pid32)(x) < 0) || \
			  ((pid32)(x) >= NPROC) || \
			  (proctab[(x)].prstate == PR_FREE))

/* Number of device descriptors a process can have open */

#define NDESC		5	/* must be odd to make procent 4N bytes	*/

/* Definition of the process table (multiple of 32 bits) */





//Lab4 4 (username:lei48, date modified: 10/24/2018)
struct xsigtab {
bool8 regyes; 
int (* fnt)(); 
uint32 optarg;
};
//end of Lab4 4









struct procent {		/* Entry in the process table		*/
	uint16	prstate;	/* Process state: PR_CURR, etc.		*/
	pri16	prprio;		/* Process priority			*/
	char	*prstkptr;	/* Saved stack pointer			*/
	char	*prstkbase;	/* Base of run time stack		*/
	uint32	prstklen;	/* Stack length in bytes		*/
	char	prname[PNMLEN];	/* Process name				*/
	sid32	prsem;		/* Semaphore on which process waits	*/
	pid32	prparent;	/* ID of the creating process		*/
	umsg32	prmsg;		/* Message sent to this process		*/
	bool8	prhasmsg;	/* Nonzero iff msg is valid		*/
	int16	prdesc[NDESC];	/* Device descriptors for process	*/
 
 
  
 //Lab2 3.2 (username:lei48, date modified: 09/25/2018)
 uint32 pgrosscpu;
 //end of Lab2 3.2 (username:lei48, date modified: 09/25/2018)
 
 //Lab2 3.3 (username:lei48, date modified: 09/25/2018)
 uint32 pwaittime;
 uint32 pwaitcount;
 uint32 pstartwait;
 //end of Lab2 3.3(username:lei48, date modified: 09/25/2018)
 
 //Lab3 3.2(username:lei48, date modified: 10/03/2018)
 uint32 pvirtcpu;
 //end of Lab3 3.2
 

//Lab3 4.1(username:lei48, date modified: 10/03/2018)
bool8 prrms;
uint16 prct;
uint16 prperiod;
//end of Lab3 4.1

//Lab4 3 (username:lei48, date modified: 10/24/2018)
int * func_address;
bool8 hasfunc;
//end of Lab4 3

//Lab4 4 (username:lei48, date modified: 10/24/2018)
struct xsigtab prsig[SIGNUM];
uint32 xalarm_time;
bool8 jump_do_shandler;
//end of Lab4 4
 
};

























/* Marker for the top of a process stack (used to help detect overflow)	*/
#define	STACKMAGIC	0x0A0AAAA9

extern	struct	procent proctab[];
extern	int32	prcount;	/* Currently active processes		*/
extern	pid32	currpid;	/* Currently executing process		*/
