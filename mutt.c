#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <pthread.h>

#define MAX_WAIT_TIME_IN_SECONDS (4)

typedef struct thread_info_s
{
    // Used to identify a thread.
    pthread_t thread_id;
    // A condition is a synchronization device that allows threads to suspend execution and relinquish the processors until some predicate on shared data is satisfied.
    // The basic operations on conditions are: signal the condition (when the predicate becomes true), and wait for the condition, suspending the thread execution until another thread signals the condition.
    pthread_cond_t condition;
    // A mutex is a MUTual EXclusion device, and is useful for protecting shared data structures from concurrent modifications, and implementing critical sections and monitors.
    // A mutex has two possible states: unlocked (not owned by any thread), and locked (owned by one thread).
    // A mutex can never be owned by two different threads simultaneously.
    // A thread attempting to lock a mutex that is already locked by another thread is suspended until the owning thread unlocks the mutex first.
    pthread_mutex_t mutex;
} thread_info_t ;

static void *worker_thread(void *p);

int main(int argc, char *argv[])
{
    thread_info_t thread_info;
    pthread_cond_init(&thread_info.condition, NULL);
    pthread_mutex_init(&thread_info.mutex, NULL);

    const int lock_rv = pthread_mutex_lock(&thread_info.mutex);
    if (lock_rv)
    {
        perror("");
        abort();
    }

    const int create_rv = pthread_create(&(thread_info.thread_id), NULL, &worker_thread, (void *) &thread_info);
    if (create_rv)
    {
        perror("");
        abort();
    }

    struct timespec max_wait = {0, 0};
    
    const int gettime_rv = clock_gettime(CLOCK_MONOTONIC, &max_wait);
    max_wait.tv_sec += MAX_WAIT_TIME_IN_SECONDS;

    puts("wait");fflush(stdout);
    const int timed_wait_rv = pthread_cond_timedwait(&thread_info.condition, &thread_info.mutex, &max_wait);
    if (timed_wait_rv)
    {
        if (ETIMEDOUT == timed_wait_rv)
        {
            puts("ETIMEDOUT");fflush(stdout);
        }
        else
        {
            perror("");
            abort();
        }
    }
    const int unlock_rv = pthread_mutex_unlock(&(thread_info.mutex));
    puts("Done.");fflush(stdout);
    const int join_rv = pthread_join(thread_info.thread_id, NULL);
    if (join_rv)
    {
        perror("");
        abort();
    }

    return 0;
}

void *worker_thread(void *data)
{
    thread_info_t *thread_info = (thread_info_t *) data;
    const int lock_rv = pthread_mutex_lock(&(thread_info->mutex));
    int oldtype;
    const int setcanceltype_rv = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);
    puts("Worker: in");fflush(stdout);
    sleep(10);
    puts("Worker: out");fflush(stdout);
    const int signal_rv = pthread_cond_signal(&(thread_info->condition));
    const int unlock_rv = pthread_mutex_unlock(&(thread_info->mutex));
    return NULL;
}

