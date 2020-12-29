/* paging.h */

//typedef unsigned int	 bsd_t;


/* Structure for a page directory entry */

typedef struct {

  unsigned int pd_pres	: 1;		/* page table present?		*/
  unsigned int pd_write : 1;		/* page is writable?		*/
  unsigned int pd_user	: 1;		/* is use level protection?	*/
  unsigned int pd_pwt	: 1;		/* write through cachine for pt?*/
  unsigned int pd_pcd	: 1;		/* cache disable for this pt?	*/
  unsigned int pd_acc	: 1;		/* page table was accessed?	*/
  unsigned int pd_mbz	: 1;		/* must be zero			*/
  unsigned int pd_fmb	: 1;		/* four MB pages?		*/
  unsigned int pd_global: 1;		/* global (ignored)		*/
  unsigned int pd_avail : 3;		/* for programmer's use		*/
  unsigned int pd_base	: 20;		/* location of page table?	*/
} pd_t;

/* Structure for a page table entry */

typedef struct {

  unsigned int pt_pres	: 1;		/* page is present?		*/
  unsigned int pt_write : 1;		/* page is writable?		*/
  unsigned int pt_user	: 1;		/* is use level protection?	*/
  unsigned int pt_pwt	: 1;		/* write through for this page? */
  unsigned int pt_pcd	: 1;		/* cache disable for this page? */
  unsigned int pt_acc	: 1;		/* page was accessed?		*/
  unsigned int pt_dirty : 1;		/* page was written?		*/
  unsigned int pt_mbz	: 1;		/* must be zero			*/
  unsigned int pt_global: 1;		/* should be zero in 586	*/
  unsigned int pt_avail : 3;		/* for programmer's use		*/
  unsigned int pt_base	: 20;		/* location of page?		*/
} pt_t;

/* Prototypes for required API calls */
//SYSCALL xmmap(int, bsd_t, int);
//SYSCALL xmunmap(int);

#define NBPG		4096	/* number of bytes per page	*/
#define FRAME0		1024	/* zero-th frame		*/
#define NFRAMES		3072	/* number of frames		*/

#define MAP_SHARED 1
#define MAP_PRIVATE 2

#define FIFO 3
#define MYPOLICY 4

#define MAX_ID		7		/* You get 8 mappings, 0 - 7 */
#define MIN_ID          0




//Lab5


#define PAGE 0
#define PAGETABLE 1
#define PAGEDIRECTORY 2
#define PAGEDIRSIZE	1024
#define PAGETABSIZE	1024
#define NUM_PAGES_FOR_PD_PT 1000
#define NUM_LOCAL_USER_PG 2072



//inverted page table
typedef struct {
	int	frame_number;
	int	virtual_page_number;
  pid32	pid;
 	bool8	used;
	int	type;
  int ref_count;
} inverted_page_table;



extern inverted_page_table ipagetab[NFRAMES];//global inverted page table
extern uint32  pf_counter;//global counter of how many times page fault happens
extern sid32	pgft_sem;//global page fault semaphore


extern void initialize_paging(void);  
extern int findfframe(void);
extern syscall vcreate (void *, uint32 , uint16 , pri16 , char *, uint32 , ...);
extern void Lab5_test1(void); 
extern void Lab5_test2(void); 
extern char  *vgetmem (uint32);
extern syscall	vfreemem(	char*,	uint32	);
extern int findfpage(void);
extern	interrupt pfisr(void);

extern	void hook_ptable_create(unsigned int );
extern	void hook_ptable_delete(unsigned int );
extern	void hook_pfault(char *);
extern	void hook_pswap_out(unsigned int , int );
extern	int get_faults(void);











