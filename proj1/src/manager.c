/**
 * @mainpage Process Simulation
 *
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "proc_structs.h"
#include "proc_syntax.h"
#include "logger.h"
#include "manager.h"

#define LOWEST_PRIORITY INT_MAX // 0 is highest, setting INT_MAX as lowest
#define NOT_MAPPED -1 // if the process is not scheduled to run, assign this to pcb->rank

static pcb_queue_t terminatedq;
static pcb_queue_t waitingq;
static pcb_queue_t readyq;
static resource_t *system_resources;

bool_t terminate();
bool_t load_new_processes(void);
void schedule_fcfs();
void schedule_rr(int quantum);
void schedule_priority();

int execute_instr(pcb_t *proc);
bool_t acquire_resource(pcb_t *proc, char *resource_name);
bool_t release_resource(pcb_t *proc, char *resource_name);

void enqueue(pcb_t *proc, pcb_queue_t *queue, int status);

/* get arguments */
int get_num_threads(int num_args, char **argv);
char *get_data(int num_args, char **argv);
int get_algo(int num_args, char **argv);
int get_time_quantum(int num_args, char **argv);
void print_args(int num_thr, char *data, int sched, int tq);
void print_queues(pcb_t *cur_pcb);

int main(int argc, char** argv) {
  int num_thr = get_num_threads(argc, argv);
  char *data = get_data(argc, argv);
  int scheduler = get_algo(argc, argv);
  int time_quantum = get_time_quantum(argc, argv);
  print_args(num_thr, data, scheduler, time_quantum);
  bool_t success = FALSE;

  if (strcmp(data,"generate") == 0) {
    #ifdef DEBUG_MNGR
    printf("****Generate processes and initialise the system\n");
    #endif
    success = init_loader_from_generator();
  } else {
    #ifdef DEBUG_MNGR
    printf("Parse process file and initialise the system: %s \n", data);
    #endif
    success = init_loader_from_files(data);
  }

  if (success) {
    init_system();
    system_resources = get_resources();
    printf("***********Scheduling processes************\n");
    schedule_processes(num_thr, scheduler, time_quantum);
    dealloc_data_structures();
  } else {
    printf("Error: no processes to schedule\n");
  }

  return EXIT_SUCCESS;
}

/**
 * @brief The linked list of loaded processes is moved to the readyqueue.
 *    The waiting and terminated queues are intialised to empty
 */
void init_system(void)
{
  readyq.first = longterm_scheduler();
  readyq.last = NULL;

  // TODO: Update the states of each process pcb added to readyq
  // TODO: Update any counters used to detect termination
  // TODO: Set readyq.last to point to the last pcb in the queue linked list
  if(readyq.first != NULL)
  {
    pcb_t *current_pcb = readyq.first;
    pcb_t *previous_pcb = NULL;

    while(current_pcb != NULL)
    {
      current_pcb->state = READY;
      previous_pcb = current_pcb;
      current_pcb = current_pcb->next;
    }

    if(previous_pcb != NULL)
      readyq.last = previous;
  }

  waitingq.last = NULL;
  waitingq.first = NULL;
  terminatedq.last = NULL;
  terminatedq.first = NULL;

  print_queues(NULL);
}

/** @brief Schedules each instruction of each process */
void schedule_processes(int num_thr, schedule_t sched_type, int quantum)
{
  switch (sched_type) {
    case PRIOR:
      schedule_priority();
      break;
    case RR:
      schedule_rr(quantum);
      break;
    case FCFS:
      schedule_fcfs();
      break;
    default:
      break;
  }
}

/** @brief Return true when there are no more processes to schedule */
bool_t terminate() {
  // TODO: implement
  return FALSE;
}

/**
 * @brief Call the longterm schedule to check for new arrivals
 * If there are new arrivals, call
 *  log_pcbs("New arrivals in ready queue", new_arrivals);
 */
bool_t load_new_processes(void) {
  pcb_t *new_arrivals = longterm_scheduler();
  // TODO: Add new arrivals to the readyq using enqueue
  // TODO: and update any counters used to detect termination
}


/** Schedules processes using FCFS scheduling */
void schedule_fcfs(void) {
  // TODO: implement

}

/** Schedules processes using the Round-Robin scheduler. */
void schedule_rr(int quantum) {
  // TODO: implement
}

/** Schedules processes using priority scheduling with preemption */
void schedule_priority(void) {
  // TODO: implement
}

/** Call the correct function to execute the next instruction of the process
 *  If there is an unknown / no instruction, call the appropriate log function:
 *    log_unknown_instr() / log_no_instr()
 *  If the instruction was to release a resource, and it was successful,
 *    wake up the first process in the waiting queue waiting for this resource
 *    and if there is a process to wake up, log it with the log_wake_up() function
 *  Update the status of the process in its pcb and return its status,
 *    so that the scheduler can act accordingly
 *
 **/
int execute_instr(pcb_t *pcb) {
    // TODO: implement
    if(pcb == NULL)
      return TERMINATED;

    if(pcb->next_instruction == NULL)
    {
      log_no_instr(pcb->process->name);
      return TERMINATED;
    }

    instr_t *current_instruction = pcb->next_instruction;
    int result = READY;

    switch (current_instruction->type)
    {
      case REQ_OP:
        if(acquire_resource(pcb, current_instr->resource_name))
        {
          result = READY;
        }
        else
        {
          result = WAITING;
        }
        break;
    }
}

/**
 * @brief Acquire a resource for a process if it is available
 *     NB: Do not remove the resource from the system_resources list
 *     Update the allocated field
 * If the resource was successfully acquired, the following log messages must be called:
 *    log_request_acquired(cur_pcb->process->name, resource_name);
 *    log_avail_resources(system_resources);
 *    log_msg("\n");
 *
 */
bool_t acquire_resource(pcb_t *cur_pcb, char *resource_name) {
  // TODO: implement
  if(cur_pcb == NULL || resource_name == NULL)
    return FALSE;

  /*Current resource in the linked list of resources*/
  resource_t *current_resource = system_resources;

  /*
   * Loop through the resource linked list, for a resource with the same name as resource_name
   * If resource with matching name is found, check if it is free
   * If it is already taken, return FALSE
   * else it is assigned to the current process, cur_pcb and return TRUE
   * if resource is never found return FALSE
   */
  while(current_resource != NULL)
  {

    if (strcmp(current_resource->name, resource_name) == 0)
    {
      if(current_resource != NULL)
        return FALSE;

      current_resource->allocated = cur_pcb;
      log_request_acquired(cur_pcb->process->name, resource_name);
      log_avail_resources(system_resources);
      log_msg("\n");

      return TRUE;
    }

    current_resource = current_resource->next;

  }

  return FALSE;
}

/**
 * @brief Execute the release instruction for the process
 *  Update the allocated field
 *  Find a process that is waiting for a resource with the same name and move it to the ready queue
 *
 * If the release was successful, the following logging function must be called
 *  log_release_released(pcb->process->name, resource_name);
 *  log_avail_resources(system_resources);
 *  log_msg("\n");
 * If the release was unsuccessful, the following logging function must be called:
 *  log_release_error(pcb->process->name, resource_name);
 *
 */
bool_t release_resource(pcb_t *proc, char *resource_name) {
  // TODO: implement
  if(proc == NULL || resource_name == NULL)
    return FALSE;
    
  /*Current resource in the linked list of resources*/
  resource_t *current_resource = system_resources;
  /*
   * Loop through the list of resources
   * Check for resource with the same name as resource_name
   * if it is found, checks if it is allocated to the proccess, proc
   * returns FALSE if it is not
   * else deallocated it and return TRUE
   * if resource is never found return FALSE
   */
  while (current_resource != NULL)
  {
    if (strcmp(current_resource->name, resource_name) == 0)
    {
      if(current_resource->allocated != proc)
        return FALSE;

      current_resource->allocated = NULL;
      log_release_released(proc->process->name, resource_name);
      log_avail_resources(system_resources);
      log_msg("\n");

      return TRUE;
    }

    current_resource = current_resource->next;
  }

  return FALSE;
}

/**
 * @brief Enqueue process <code>pcb</code> to <code>queue</code>
 * Log the enqueue operation appropriately, depending on <code>status</code>
 *   log_ready(pcb->process->name);
 *   log_request_waiting(pcb->process->name, pcb->next_instruction->resource_name);
 *   log_terminated(pcb->process->name);
 */
void enqueue(pcb_t *pcb, pcb_queue_t *queue, int status) {
  // TODO: implement
  if(pcb == NULL)
    return;

  pcb->next = NULL;
  pcb->state = status;

  if(queue->first == NULL)
  {
    queue->first = pcb;
    queue->last = pcb;
  }
  else
  {
    queue->last->next = pcb;
    queue->last = pcb;
  }


  switch(status)
  {
    case READY:
      log_ready(pcb->process->name);
      break;

    case WAITING:
      if(pcb->next_instruction != NULL)
        log_request_waiting(pcb->process->name, pcb->next_instruction->resource_name);
      break;

    case TERMINATED:
      log_terminated(pcb->process->name);
      break;

    default: break;
  }

  return;
}
/*
 * Remove a process from the front of a queue
 */
pcb_t* dequeue(pcb_queue_t *queue) {
  pcb_t *proc = NULL;

  if (queue->first != NULL)
  {
    proc = queue->first;
    queue->first = proc->next;

    if (queue->first == NULL)
      queue->last = NULL;

    proc->next = NULL;
  }

  return proc;
}
/**
 * @brief detect deadlock
 * If deadlock is detected, the following log function must be called
 *  log_deadlock_detected();
 */
struct pcb_t* detect_deadlock(void) {
  /* TODO: Implement */
  return NULL;
}

/** @brief Deallocate the queues */
void free_manager(void) {
  print_queues(NULL);

  #ifdef DEBUG_MNGR
  printf("\nFreeing the queues...\n");
  #endif
  dealloc_pcbs(readyq.first);
  dealloc_pcbs(waitingq.first);
  dealloc_pcbs(terminatedq.first);
}

/** @brief Retrieve the number of threads to create from the list of arguments */
int get_num_threads(int num_args, char **argv) {
  if (num_args > 1) return atoi(argv[1]);
  else return 1;
}

/** @brief Retrieve the name of a process file or the codename "generate" from the list of arguments */
char *get_data(int num_args, char **argv) {
  char *data_origin = "generate";
  if (num_args > 2) return argv[2];
  else return data_origin;
}

/** @brief Retrieve the scheduler algorithm type from the list of arguments */
int get_algo(int num_args, char **argv) {
  if (num_args > 3) return atoi(argv[3]);
  else return 1;
}

/** @brief Retrieve the time quantum from the list of arguments */
int get_time_quantum(int num_args, char **argv) {
  if (num_args > 4) return atoi(argv[4]);
  else return 1;
}

/** @brief Print the arguments of the program */
void print_args(int num_thr, char *data, int sched, int tq) {
  printf("Arguments: num_threads = %d, data = %s, scheduler = %s,  time quantum = %d\n", num_thr, data, (sched==0)?"priority":(sched==1)?"RR":"FCFS", tq);
}


/**
 * @brief Print the currently running process, as well as all the queued processes
 */
void print_queues(pcb_t *cur_pcb) {
  if (cur_pcb != NULL) log_running(cur_pcb, omp_get_thread_num());
  log_queue(readyq.first, "Ready");
  log_queue(waitingq.first, "Waiting");
  log_queue(terminatedq.first, "Terminated");
  log_msg("\n");
}
