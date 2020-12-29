/* clock.h */

/* Intel 8254-2 clock chip constants */

#define	CLOCKBASE	0x40		/* I/O base port of clock chip	*/
#define	CLOCK0		CLOCKBASE
#define	CLKCNTL		(CLOCKBASE+3)	/* chip CSW I/O port		*/


#define CLKTICKS_PER_SEC  1000	/* clock timer resolution		*/

extern	uint32	clktime;	/* current time in secs since boot	*/

//Lab2 3.1 (username:lei48, date modified: 09/25/2018)
extern	uint32	clktimemilli;	/* current time in milisecs since boot	*/

//end of Lab2 3.1 (username:lei48, date modified: 09/25/2018)


//Lab2 3.2 (username:lei48, date modified: 09/25/2018)
extern uint32 currproctime;
//end of Lab2 3.2 (username:lei48, date modified: 09/25/2018)



extern	qid16	sleepq;		/* queue for sleeping processes		*/
extern	uint32	preempt;	/* preemption counter			*/

//Lab1 4.1(username:lei48, date modified: 09/09/2018)
typedef struct xminsec {
int upmin; 
int upsec;
} xminsec_t;