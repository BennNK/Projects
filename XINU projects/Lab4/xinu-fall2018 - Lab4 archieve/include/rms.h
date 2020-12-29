//RMS scheduler
//Lab3 4.1(username:lei48, date modified: 10/03/2018)



//Lab3 4.1(username:lei48, date modified: 10/03/2018)
typedef struct rmsparam 
{
uint16 rms_ct; 
uint16 rms_period;
} rmsparam_t;
//end of Lab3 4.1


//Lab3 4.1 (username:lei48, date modified: 10/12/2018)
/* in file rms_create.c */
extern	pid32	rms_create(void *, uint32, rmsparam_t* rmsptr, char *, uint32, ...);


#define	 RMSBOUND 0.5
# define RMSQUANTUM 1000
extern	uint32	preempt_rms;	/* rms preemption counter			*/

extern void rms_app(uint32 , uint32 );