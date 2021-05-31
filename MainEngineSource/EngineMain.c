#pragma once
#if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)
#define _TEX_WIN32_
#else
#define _TEX_POSIX_
#endif
//C
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
//Platform specific includes 
#if defined(_TEX_POSIX_)
#include <xcb/xcb.h>
#include <pthread.h>
#include <signal.h>
#include <sched.h>
//#include <unistd.h>
//#include <sys/time.h>
#include <errno.h>
#include <dlfcn.h>
#elif defined(_TEX_WIN32_)
#include <Windows.h>
//#include <shellapi.h>
//#include <process.h>
//#include <sys/timeb.h>
#include <windowsx.h>
#endif
//Main
#include "Extension.h"
//end

struct {
	uint64_t InitialExtensionMax;
}Config;

uint32_t EngineVersion[3] = { 1, 0, 0 };
#ifdef NDEBUG
BinaryType EngineBinType = Release;
#else
BinaryType EngineBinType = Debug;
#endif

volatile EngineUtils Utils;


/* Mutex */
#if defined(_TEX_WIN32_)
typedef struct {
	union {
		CRITICAL_SECTION cs;      /* Critical section handle (used for non-timed mutexes) */
		HANDLE mut;               /* Mutex handle (used for timed mutex) */
	} mHandle;                  /* Mutex handle */
	int mAlreadyLocked;         /* TRUE if the mutex is already locked */
	int mRecursive;             /* TRUE if the mutex is recursive */
	int mTimed;                 /* TRUE if the mutex is timed */
}mtx_t;
#else
typedef pthread_mutex_t mtx_t;
#endif

/* Condition variable */
#ifdef _TEX_WIN32_
#define _CONDITION_EVENT_ONE 0
#define _CONDITION_EVENT_ALL 1
#endif

#if defined(_TEX_WIN32_)
typedef struct {
	HANDLE mEvents[2];                  /* Signal and broadcast event HANDLEs. */
	unsigned int mWaitersCount;         /* Count of the number of waiters. */
	CRITICAL_SECTION mWaitersCountLock; /* Serialize access to mWaitersCount. */
}cnd_t;
#else
typedef pthread_cond_t cnd_t;
#endif

#ifdef _TEX_WIN32_
typedef struct {
	LONG volatile status;
	CRITICAL_SECTION lock;
} once_flag;
#define ONCE_FLAG_INIT {0,}
#else
#define once_flag pthread_once_t
#define ONCE_FLAG_INIT PTHREAD_ONCE_INIT
#endif

/*
* Added in 1.0.0
* Error Reporting Function, variant used for invalid data in structs.
* @param FunctionName, Name of the function to trace back to.
* @param ObjectName, Name of the object with invalid data.
* @param ObjectPointer, Pointer to the object with invalid data.
* @param Error, Error message.
*/
void ObjectError(const UTF8* FunctionName, const UTF8* ObjectName, void* ObjectPointer, const UTF8* Error)
{
	char buffer[512];
	snprintf(buffer, 512, "Error: %s : %s 0x%p, Encountered The Following Validation Error: %s\n", FunctionName, ObjectName, ObjectPointer, Error);
#ifdef _TEX_WIN32_
	LPWSTR Path1 = NULL;
	uint32_t size = MultiByteToWideChar(CP_UTF8, 0, buffer, -1, Path1, 0);
	Path1 = (WCHAR*)malloc(sizeof(WCHAR) * size);
	MultiByteToWideChar(CP_UTF8, 0, buffer, -1, Path1, size);

	OutputDebugString(Path1);
	free(Path1);
#endif
}
/*
* Added in 1.0.0
* Error Reporting Function, variant used for critical function errors that arent related to any input.
* @param FunctionName, Name of the function to trace back to.
* @param Error, Error message.
* @param Value, Error Code.
*/
void FunctionError(const UTF8* FunctionName, const UTF8* Error, uint64_t Value)
{
	char buffer[512];
	snprintf(buffer, 512, "Error: %s Failed With Error: %s0x%p\n", FunctionName, Error, Value);
#ifdef _TEX_WIN32_
	LPWSTR Path1 = NULL;
	uint32_t size = MultiByteToWideChar(CP_UTF8, 0, buffer, -1, Path1, 0);
	Path1 = (WCHAR*)malloc(sizeof(WCHAR) * size);
	MultiByteToWideChar(CP_UTF8, 0, buffer, -1, Path1, size);

	OutputDebugString(Path1);
	free(Path1);
#endif
}
/*
* Added in 1.0.0
* Error Reporting Function, variant used for invalid arguments in a function.
* @param FunctionName, Name of the function to trace back to.
* @param Error, Error message.
*/
void ArgsError(const UTF8* FunctionName, const UTF8* Error)
{
	char buffer[512];
	snprintf(buffer, 512, "Error: %s Invalid Argument: %s\n", FunctionName, Error);
#ifdef _TEX_WIN32_
	LPWSTR Path1 = NULL;
	uint32_t size = MultiByteToWideChar(CP_UTF8, 0, buffer, -1, Path1, 0);
	Path1 = (WCHAR*)malloc(sizeof(WCHAR) * size);
	MultiByteToWideChar(CP_UTF8, 0, buffer, -1, Path1, size);

	OutputDebugString(Path1);
	free(Path1);
#endif
}

/*
* Added in 1.0.0
* Create a mutex object.
* @param mtx A mutex object.
* @param type Bit-mask that must have one of the following six values:
*   @li @c mtx_plain for a simple non-recursive mutex
*   @li @c mtx_timed for a non-recursive mutex that supports timeout
*   @li @c mtx_plain | @c mtx_recursive (same as @c mtx_plain, but recursive)
*   @li @c mtx_timed | @c mtx_recursive (same as @c mtx_timed, but recursive)
* @return @ref thrd_success on success, or @ref thrd_error if the request could
* not be honored.
*/
TEXRESULT Create_Mutex(mtx_t* pMutex, MutexType Type)
{
#ifdef _TEX_WIN32_
	pMutex->mAlreadyLocked = FALSE;
	pMutex->mRecursive = Type & MutexType_Recursive;
	pMutex->mTimed = Type & MutexType_Timed;
	if (!pMutex->mTimed)
	{
		InitializeCriticalSection(&(pMutex->mHandle.cs));
	}
	else
	{
		pMutex->mHandle.mut = CreateMutex(NULL, FALSE, NULL);
		if (pMutex->mHandle.mut == NULL)
			return Failure;
	}
	return Success;
#else
	int ret;
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	if (Type & MutexType_Recursive)
	{
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	}
	ret = pthread_mutex_init(pMutex, &attr);
	pthread_mutexattr_destroy(&attr);
	return ret == 0 ? Success : Failure;
#endif
}
/*
* Added in 1.0.0
* Release any resources used by the given mutex.
* @param mtx A mutex object.
*/
void Destroy_Mutex(mtx_t* pMutex)
{
#ifdef _TEX_WIN32_
	if (!pMutex->mTimed)
		DeleteCriticalSection(&(pMutex->mHandle.cs));
	else
		CloseHandle(pMutex->mHandle.mut);
#else
	pthread_mutex_destroy(pMutex);
#endif
}
/*
* Added in 1.0.0
* Lock the given mutex.
* Blocks until the given mutex can be locked. If the mutex is non-recursive, and
* the calling thread already has a lock on the mutex, this call will block
* forever.
* @param mtx A mutex object.
* @return @ref thrd_success on success, or @ref thrd_error if the request could
* not be honored.
*/
TEXRESULT Lock_Mutex(mtx_t* pMutex)
{
#ifdef _TEX_WIN32_
	if (!pMutex->mTimed)
	{
		EnterCriticalSection(&(pMutex->mHandle.cs));
	}
	else
	{
		switch (WaitForSingleObject(pMutex->mHandle.mut, INFINITE))
		{
		case WAIT_OBJECT_0:
			break;
		case WAIT_ABANDONED:
		default:
			return Failure;
		}
	}

	if (!pMutex->mRecursive)
	{
		while (pMutex->mAlreadyLocked) Sleep(1); /* Simulate deadlock... */
		pMutex->mAlreadyLocked = TRUE;
	}
	return Success;
#else
	return pthread_mutex_lock(pMutex) == 0 ? Success : Failure;
#endif
}
/*
* Added in 1.0.0
* Lock the given mutex, or block until a specific point in time.
* Blocks until either the given mutex can be locked, or the specified TIME_UTC
* based time.
* @param mtx A mutex object.
* @param ts A UTC based calendar time
* @return @ref The mtx_timedlock function returns thrd_success on success, or
* thrd_timedout if the time specified was reached without acquiring the
* requested resource, or thrd_error if the request could not be honored.
*/
TEXRESULT TimedLock_Mutex(mtx_t* pMutex, const struct timespec* ts)
{
#ifdef _TEX_WIN32_
	struct timespec current_ts;
	DWORD timeoutMs;

	if (!pMutex->mTimed)
		return Failure;

	timespec_get(&current_ts, TIME_UTC);

	if ((current_ts.tv_sec > ts->tv_sec) || ((current_ts.tv_sec == ts->tv_sec) && (current_ts.tv_nsec >= ts->tv_nsec)))
	{
		timeoutMs = 0;
	}
	else
	{
		timeoutMs = (DWORD)(ts->tv_sec - current_ts.tv_sec) * 1000;
		timeoutMs += (ts->tv_nsec - current_ts.tv_nsec) / 1000000;
		timeoutMs += 1;
	}

	/* TODO: the timeout for WaitForSingleObject doesn't include time
	   while the computer is asleep. */
	switch (WaitForSingleObject(pMutex->mHandle.mut, timeoutMs))
	{
	case WAIT_OBJECT_0:
		break;
	case WAIT_TIMEOUT:
		return Timeout;
	case WAIT_ABANDONED:
	default:
		return Failure;
	}

	if (!pMutex->mRecursive)
	{
		while (pMutex->mAlreadyLocked) Sleep(1); /* Simulate deadlock... */
		pMutex->mAlreadyLocked = TRUE;
	}

	return Success;
#elif defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >= 200112L) && defined(_POSIX_THREADS) && (_POSIX_THREADS >= 200112L)
	switch (pthread_mutex_timedlock(pMutex, ts)) {
	case 0:
		return Success;
	case ETIMEDOUT:
		return Timeout;
	default:
		return Failure;
	}
#else
	int rc;
	struct timespec cur, dur;

	/* Try to acquire the lock and, if we fail, sleep for 5ms. */
	while ((rc = pthread_mutex_trylock(pMutex)) == EBUSY) {
		timespec_get(&cur, TIME_UTC);

		if ((cur.tv_sec > ts->tv_sec) || ((cur.tv_sec == ts->tv_sec) && (cur.tv_nsec >= ts->tv_nsec)))
		{
			break;
		}

		dur.tv_sec = ts->tv_sec - cur.tv_sec;
		dur.tv_nsec = ts->tv_nsec - cur.tv_nsec;
		if (dur.tv_nsec < 0)
		{
			dur.tv_sec--;
			dur.tv_nsec += 1000000000;
		}

		if ((dur.tv_sec != 0) || (dur.tv_nsec > 5000000))
		{
			dur.tv_sec = 0;
			dur.tv_nsec = 5000000;
		}

		nanosleep(&dur, NULL);
	}

	switch (rc) {
	case 0:
		return Success;
	case ETIMEDOUT:
	case EBUSY:
		return Timeout;
	default:
		return Failure;
	}
#endif
}
/*
* Added in 1.0.0
* Try to lock the given mutex.
* The specified mutex shall support either test and return or timeout. If the
* mutex is already locked, the function returns without blocking.
* @param mtx A mutex object.
* @return @ref thrd_success on success, or @ref thrd_busy if the resource
* requested is already in use, or @ref thrd_error if the request could not be
* honored.
*/
TEXRESULT TryLock_Mutex(mtx_t* pMutex)
{
#ifdef _TEX_WIN32_
	int ret;
	if (!pMutex->mTimed)
	{
		ret = TryEnterCriticalSection(&(pMutex->mHandle.cs)) ? Success : Busy;
	}
	else
	{
		ret = (WaitForSingleObject(pMutex->mHandle.mut, 0) == WAIT_OBJECT_0) ? Success : Busy;
	}

	if ((!pMutex->mRecursive) && (ret == Success))
	{
		if (pMutex->mAlreadyLocked)
		{
			LeaveCriticalSection(&(pMutex->mHandle.cs));
			ret = Busy;
		}
		else
		{
			pMutex->mAlreadyLocked = TRUE;
		}
	}
	return ret;
#else
	return (pthread_mutex_trylock(pMutex) == 0) ? Success : Failure;
#endif
}
/*
* Added in 1.0.0
* Unlock the given mutex.
* @param mtx A mutex object.
* @return @ref thrd_success on success, or @ref thrd_error if the request could
* not be honored.
*/
TEXRESULT Unlock_Mutex(mtx_t* pMutex)
{
#ifdef _TEX_WIN32_
	pMutex->mAlreadyLocked = FALSE;
	if (!pMutex->mTimed)
	{
		LeaveCriticalSection(&(pMutex->mHandle.cs));
	}
	else
	{
		if (!ReleaseMutex(pMutex->mHandle.mut))
		{
			return Failure;
		}
	}
	return Success;
#else
	return pthread_mutex_unlock(pMutex) == 0 ? Success : Failure;
#endif
}
/*
* Added in 1.0.0
* Create a condition variable object.
* @param cond A condition variable object.
* @return @ref thrd_success on success, or @ref thrd_error if the request could
* not be honored.
*/
TEXRESULT Create_Condition(cnd_t* pCondition)
{
#ifdef _TEX_WIN32_
	pCondition->mWaitersCount = 0;

	/* Init critical section */
	InitializeCriticalSection(&pCondition->mWaitersCountLock);

	/* Init events */
	pCondition->mEvents[_CONDITION_EVENT_ONE] = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (pCondition->mEvents[_CONDITION_EVENT_ONE] == NULL)
	{
		pCondition->mEvents[_CONDITION_EVENT_ALL] = NULL;
		return Failure;
	}
	pCondition->mEvents[_CONDITION_EVENT_ALL] = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (pCondition->mEvents[_CONDITION_EVENT_ALL] == NULL)
	{
		CloseHandle(pCondition->mEvents[_CONDITION_EVENT_ONE]);
		pCondition->mEvents[_CONDITION_EVENT_ONE] = NULL;
		return Failure;
	}

	return Success;
#else
	return pthread_cond_init(pCondition, NULL) == 0 ? Success : Failure;
#endif
}
/*
* Added in 1.0.0
* Release any resources used by the given condition variable.
* @param cond A condition variable object.
*/
void Destroy_Condition(cnd_t* pCondition)
{
#ifdef _TEX_WIN32_
	if (pCondition->mEvents[_CONDITION_EVENT_ONE] != NULL)
	{
		CloseHandle(pCondition->mEvents[_CONDITION_EVENT_ONE]);
	}
	if (pCondition->mEvents[_CONDITION_EVENT_ALL] != NULL)
	{
		CloseHandle(pCondition->mEvents[_CONDITION_EVENT_ALL]);
	}
	DeleteCriticalSection(&pCondition->mWaitersCountLock);
#else
	pthread_cond_destroy(pCondition);
#endif
}
/*
* Added in 1.0.0
* Signal a condition variable.
* Unblocks one of the threads that are blocked on the given condition variable
* at the time of the call. If no threads are blocked on the condition variable
* at the time of the call, the function does nothing and return success.
* @param cond A condition variable object.
* @return @ref thrd_success on success, or @ref thrd_error if the request could
* not be honored.
*/
TEXRESULT Signal_Condition(cnd_t* pCondition)
{
#ifdef _TEX_WIN32_
	int haveWaiters;

	/* Are there any waiters? */
	EnterCriticalSection(&pCondition->mWaitersCountLock);
	haveWaiters = (pCondition->mWaitersCount > 0);
	LeaveCriticalSection(&pCondition->mWaitersCountLock);

	/* If we have any waiting threads, send them a signal */
	if (haveWaiters)
	{
		if (SetEvent(pCondition->mEvents[_CONDITION_EVENT_ONE]) == 0)
		{
			return Failure;
		}
	}

	return Success;
#else
	return pthread_cond_signal(pCondition) == 0 ? Success : Failure;
#endif
}
/*
* Added in 1.0.0
* Broadcast a condition variable.
* Unblocks all of the threads that are blocked on the given condition variable
* at the time of the call. If no threads are blocked on the condition variable
* at the time of the call, the function does nothing and return success.
* @param cond A condition variable object.
* @return @ref thrd_success on success, or @ref thrd_error if the request could
* not be honored.
*/
TEXRESULT Broadcast_Condition(cnd_t* pCondition)
{
#ifdef _TEX_WIN32_
	int haveWaiters;
	/* Are there any waiters? */
	EnterCriticalSection(&pCondition->mWaitersCountLock);
	haveWaiters = (pCondition->mWaitersCount > 0);
	LeaveCriticalSection(&pCondition->mWaitersCountLock);

	/* If we have any waiting threads, send them a signal */
	if (haveWaiters)
	{
		if (SetEvent(pCondition->mEvents[_CONDITION_EVENT_ALL]) == 0)
		{
			return Failure;
		}
	}
	return Success;
#else
	return pthread_cond_broadcast(pCondition) == 0 ? Success : Failure;
#endif
}

#ifdef _TEX_WIN32_
static TEXRESULT _TimedWait_Condition_win32(cnd_t* pCondition, mtx_t* pMutex, DWORD timeout)
{
	DWORD result;
	int lastWaiter;

	//Increment number of waiters 
	EnterCriticalSection(&pCondition->mWaitersCountLock);
	++pCondition->mWaitersCount;
	LeaveCriticalSection(&pCondition->mWaitersCountLock);

	//Release the mutex while waiting for the condition (will decrease
	//   the number of waiters when done)... 
	Unlock_Mutex(pMutex);

	//Wait for either event to become signaled due to cnd_signal() or
	//  cnd_broadcast() being called
	result = WaitForMultipleObjects(2, pCondition->mEvents, FALSE, timeout);
	if (result == WAIT_TIMEOUT)
	{
		// The mutex is locked again before the function returns, even if an error occurred 
		Lock_Mutex(pMutex);
		return Timeout;
	}
	else if (result == WAIT_FAILED)
	{
		//The mutex is locked again before the function returns, even if an error occurred 
		Lock_Mutex(pMutex);
		return Failure;
	}

	// Check if we are the last waiter 
	EnterCriticalSection(&pCondition->mWaitersCountLock);
	--pCondition->mWaitersCount;
	lastWaiter = (result == (WAIT_OBJECT_0 + _CONDITION_EVENT_ALL)) &&
		(pCondition->mWaitersCount == 0);
	LeaveCriticalSection(&pCondition->mWaitersCountLock);

	// If we are the last waiter to be notified to stop waiting, reset the event 
	if (lastWaiter)
	{
		if (ResetEvent(pCondition->mEvents[_CONDITION_EVENT_ALL]) == 0)
		{
			// The mutex is locked again before the function returns, even if an error occurred 
			Lock_Mutex(pMutex);
			return Failure;
		}
	}
	// Re-acquire the mutex 
	Lock_Mutex(pMutex);

	return Success;
}
#endif

/*
* Added in 1.0.0
* Wait for a condition variable to become signaled.
* The function atomically unlocks the given mutex and endeavors to block until
* the given condition variable is signaled by a call to cnd_signal or to
* cnd_broadcast. When the calling thread becomes unblocked it locks the mutex
* before it returns.
* @param cond A condition variable object.
* @param mtx A mutex object.
* @return @ref thrd_success on success, or @ref thrd_error if the request could
* not be honored.
*/
TEXRESULT Wait_Condition(cnd_t* pCondition, mtx_t* pMutex)
{
#ifdef _TEX_WIN32_
	return _TimedWait_Condition_win32(pCondition, pMutex, INFINITE);
#else
	return pthread_cond_wait(pCondition, pMutex) == 0 ? Success : Failure;
#endif
}
/*
* Wait for a condition variable to become signaled.
* The function atomically unlocks the given mutex and endeavors to block until
* the given condition variable is signaled by a call to cnd_signal or to
* cnd_broadcast, or until after the specified time. When the calling thread
* becomes unblocked it locks the mutex before it returns.
* @param cond A condition variable object.
* @param mtx A mutex object.
* @param xt A point in time at which the request will time out (absolute time).
* @return @ref thrd_success upon success, or @ref thrd_timeout if the time
* specified in the call was reached without acquiring the requested resource, or
* @ref thrd_error if the request could not be honored.
*/
TEXRESULT TimedWait_Condition(cnd_t* pCondition, mtx_t* pMutex, const struct timespec* ts)
{
#ifdef _TEX_WIN32_
	struct timespec now;
	if (timespec_get(&now, TIME_UTC) == TIME_UTC)
	{
		unsigned long long nowInMilliseconds = now.tv_sec * 1000 + now.tv_nsec / 1000000;
		unsigned long long tsInMilliseconds = ts->tv_sec * 1000 + ts->tv_nsec / 1000000;
		DWORD delta = (tsInMilliseconds > nowInMilliseconds) ?
			(DWORD)(tsInMilliseconds - nowInMilliseconds) : 0;
		return _TimedWait_Condition_win32(pCondition, pMutex, delta);
	}
	else
		return Failure;
#else
	int ret;
	ret = pthread_cond_timedwait(pCondition, pMutex, ts);
	if (ret == ETIMEDOUT)
	{
		return Timeout;
	}
	return ret == 0 ? Success : Failure;
#endif
}

/*
//If TIME_UTC is missing, provide it and provide a wrapper for timespec_get.
#ifndef TIME_UTC
#define TIME_UTC 1
#define _TTHREAD_EMULATE_TIMESPEC_GET_

#if defined(_TTHREAD_WIN32_)
struct _tthread_timespec {
	time_t tv_sec;
	long   tv_nsec;
};
#define timespec _tthread_timespec
#endif

int _tthread_timespec_get(struct timespec* ts, int base);
#define timespec_get _tthread_timespec_get
#endif
*/
/** Information to pass to the new thread (what to run). */
typedef struct {
	thrd_start_t mFunction; /**< Pointer to the function to be executed. */
	void* mArg;            /**< Function argument for the thread function. */
} _thread_start_info;

/* Thread wrapper function. */
#ifdef _TEX_WIN32_
static DWORD WINAPI _thrd_wrapper_function(LPVOID aArg)
#else
static void* _thrd_wrapper_function(void* aArg)
#endif
{
	thrd_start_t fun;
	void* arg;
	int  res;

	/* Get thread startup information */
	_thread_start_info* ti = (_thread_start_info*)aArg;
	fun = ti->mFunction;
	arg = ti->mArg;

	/* The thread is responsible for freeing the startup information */
	free((void*)ti);

	/* Call the actual client thread function */
	res = fun(arg);

#ifdef _TEX_WIN32_
	return (DWORD)res;
#else
	return (void*)(intptr_t)res;
#endif
}
/*
* Added in 1.0.0
* Create a new thread.
* @param thr Identifier of the newly created thread.
* @param func A function pointer to the function that will be executed in
*        the new thread.
* @param arg An argument to the thread function.
* @return @ref thrd_success on success, or @ref thrd_nomem if no memory could
* be allocated for the thread requested, or @ref thrd_error if the request
* could not be honored.
* @note A thread’s identifier may be reused for a different thread once the
* original thread has exited and either been detached or joined to another
* thread.
*/
TEXRESULT Create_Thread(Thread** pThread, thrd_start_t Function, void* arg)
{
	/* Fill out the thread startup information (passed to the thread wrapper,
	   which will eventually free it) */
	_thread_start_info* ti = (_thread_start_info*)malloc(sizeof(_thread_start_info));
	if (ti == NULL)
	{
		return Out_Of_Memory_Result;
	}
	ti->mFunction = Function;
	ti->mArg = arg;

	/* Create the thread */
#ifdef _TEX_WIN32_
	*pThread = CreateThread(NULL, 0, _thrd_wrapper_function, (LPVOID)ti, 0, NULL);
#else
	if (pthread_create(pThread, NULL, _thrd_wrapper_function, (void*)ti) != 0)
	{
		*pThread = 0;
	}
#endif
	/* Did we fail to create the thread? */
	if (!*pThread)
	{
		free(ti);
		return Failure;
	}
	return Success;
}
/*
* Added in 1.0.0
* Identify the calling thread.
* @return The identifier of the calling thread.
*/
Thread* Current_Thread(void)
{
#ifdef _TEX_WIN32_
	return GetCurrentThread();
#else
	return pthread_self();
#endif
}
/*
* Added in 1.0.0
* Dispose of any resources allocated to the thread when that thread exits.
* @return thrd_success, or thrd_error on error
*/
TEXRESULT Detach_Thread(Thread* Thread)
{
#ifdef _TEX_WIN32_
	/* https://stackoverflow.com/questions/12744324/how-to-detach-a-thread-on-windows-c#answer-12746081 */
	return CloseHandle(Thread) != 0 ? Success : Failure;
#else
	return pthread_detach(Thread) == 0 ? Success : Failure;
#endif
}
/*
* Added in 1.0.0
* Compare two thread identifiers.
* The function determines if two thread identifiers refer to the same thread.
* @return Zero if the two thread identifiers refer to different threads.
* Otherwise a nonzero value is returned.
*/
TEXRESULT ThreadEqual(Thread* Thread0, Thread* Thread1)
{
#ifdef _TEX_WIN32_
	return (GetThreadId(Thread0) == GetThreadId(Thread1)) ? Success : Failure;
#else
	return (pthread_equal(Thread0, Thread1)) ? Success : Failure;
#endif
}
/*
* Added in 1.0.0
* Terminate execution of the calling thread.
* @param res Result code of the calling thread.
*/
void Exit_Thread(int res)
{
#ifdef _TEX_WIN32_
	ExitThread((DWORD)res);
#else
	pthread_exit((void*)(intptr_t)res);
#endif
}
/*
* Added in 1.0.0
* Wait for a thread to terminate.
* The function joins the given thread with the current thread by blocking
* until the other thread has terminated.
* @param thr The thread to join with.
* @param res If this pointer is not NULL, the function will store the result
*        code of the given thread in the integer pointed to by @c res.
* @return @ref thrd_success on success, or @ref thrd_error if the request could
* not be honored.
*/
TEXRESULT Join_Thread(Thread* Thread, int* res)
{
#ifdef _TEX_WIN32_
	DWORD dwRes;

	if (WaitForSingleObject(Thread, INFINITE) == WAIT_FAILED)
	{
		return Failure;
	}
	if (res != NULL)
	{
		if (GetExitCodeThread(Thread, &dwRes) != 0)
		{
			*res = (int)dwRes;
		}
		else
		{
			return Failure;
		}
	}
	CloseHandle(Thread);
#else
	void* pres;
	if (pthread_join(Thread, &pres) != 0)
	{
		return Failure;
	}
	if (res != NULL)
	{
		*res = (int)(intptr_t)pres;
	}
#endif
	return Success;
}
/*
* Added in 1.0.0
* Put the calling thread to sleep.
* Suspend execution of the calling thread.
* @param duration  Interval to sleep for
* @param remaining If non-NULL, this parameter will hold the remaining
*                  time until time_point upon return. This will
*                  typically be zero, but if the thread was woken up
*                  by a signal that is not ignored before duration was
*                  reached @c remaining will hold a positive time.
* @return 0 (zero) on successful sleep, -1 if an interrupt occurred,
*         or a negative value if the operation fails.
*/
TEXRESULT Sleep_Thread(const struct timespec* duration, struct timespec* remaining)
{
#ifdef _TEX_WIN32_
	struct timespec start;
	DWORD t;

	timespec_get(&start, TIME_UTC);

	t = SleepEx((DWORD)(duration->tv_sec * 1000 +
		duration->tv_nsec / 1000000 +
		(((duration->tv_nsec % 1000000) == 0) ? 0 : 1)),
		TRUE);

	if (t == 0) {
		return 0;
	}
	else {
		if (remaining != NULL) {
			timespec_get(remaining, TIME_UTC);
			remaining->tv_sec -= start.tv_sec;
			remaining->tv_nsec -= start.tv_nsec;
			if (remaining->tv_nsec < 0)
			{
				remaining->tv_nsec += 1000000000;
				remaining->tv_sec -= 1;
			}
		}
		return (t == WAIT_IO_COMPLETION) ? -1 : -2;
	}
#else
	int res = nanosleep(duration, remaining);
	if (res == 0) {
		return 0;
	}
	else if (errno == EINTR) {
		return -1;
	}
	else {
		return -2;
	}
#endif
}
/*
* Added in 1.0.0
* Yield execution to another thread.
* Permit other threads to run, even if the current thread would ordinarily
* continue to run.
*/
void Yield_Thread(void)
{
#ifdef _TEX_WIN32_
	Sleep(0);
#else
	sched_yield();
#endif
}
/*
#if defined(_TTHREAD_EMULATE_TIMESPEC_GET_)
int _tthread_timespec_get(struct timespec* ts, int base)
{
#ifdef _TEX_WIN32_
	struct _timeb tb;
#elif !defined(CLOCK_REALTIME)
	struct timeval tv;
#endif

	if (base != TIME_UTC)
	{
		return 0;
	}

#if defined(_TTHREAD_WIN32_)
	_ftime_s(&tb);
	ts->tv_sec = (time_t)tb.time;
	ts->tv_nsec = 1000000L * (long)tb.millitm;
#elif defined(CLOCK_REALTIME)
	base = (clock_gettime(CLOCK_REALTIME, ts) == 0) ? base : 0;
#else
	gettimeofday(&tv, NULL);
	ts->tv_sec = (time_t)tv.tv_sec;
	ts->tv_nsec = 1000L * (long)tv.tv_usec;
#endif

	return base;
}
#endif
*/

/*
* Added in 1.0.0
* Invoke a callback exactly once
* @param flag Flag used to ensure the callback is invoked exactly
*        once.
* @param func Callback to invoke.
*/
void Call_Once(once_flag* flag, void (*func)(void))
{
#ifdef _TEX_WIN32_
	while (flag->status < 3)
	{
		switch (flag->status)
		{
		case 0:
			if (InterlockedCompareExchange(&(flag->status), 1, 0) == 0) {
				InitializeCriticalSection(&(flag->lock));
				EnterCriticalSection(&(flag->lock));
				flag->status = 2;
				func();
				flag->status = 3;
				LeaveCriticalSection(&(flag->lock));
				return;
			}
			break;
		case 1:
			break;
		case 2:
			EnterCriticalSection(&(flag->lock));
			LeaveCriticalSection(&(flag->lock));
			break;
		}
	}
#else
	pthread_once(flag, func);
#endif
}

//////////////////////////////////////////
//DLL Functions
//////////////////////////////////////////

/*
* Added in 1.0.0
* @param pDLL_Handle, pointer to a handle where the result will be stored.
* @param Path, file path of the DLL to load.
*/
TEXRESULT Open_DLL(void** pDLL_Handle, const UTF8* Path)
{
#ifndef NDEBUG
	if (pDLL_Handle == NULL)
	{
		ArgsError("Open_DLL()", "pDLL_Handle == NULLPTR");
		return Invalid_Parameter | Failure;
	}
	if (Path == NULL)
	{
		ArgsError("Open_DLL()", "Path == NULLPTR");
		return Invalid_Parameter | Failure;
	}
#endif
#ifdef _TEX_WIN32_
	LPWSTR Path1 = NULL;
	uint32_t size = MultiByteToWideChar(CP_UTF8, 0, Path, -1, Path1, 0);
	Path1 = (WCHAR*)malloc(sizeof(WCHAR) * size);
	MultiByteToWideChar(CP_UTF8, 0, Path, -1, Path1, size);
	*pDLL_Handle = LoadLibraryExW(Path1, NULL, NULL);
	free((void*)Path1);
#else
	*pDLL_Handle = dlopen(Path, RTLD_NOW);
#endif

#ifndef NDEBUG
	if (*pDLL_Handle == NULL)
	{
		FunctionError("Open_DLL()", "LoadLibraryExW() Failed.", NULL);
		return Failure;
	}
#endif
	return Success;
}
/*
* Added in 1.0.0
* @param DLL_Handle, The handle of the DLL to get the function from.
* @param pFunction, Pointer to a pointer where the resulting function pointer will be stored.
* @param Name, Name of the function to get. (Note: on windows you need to __declspec(dllexport))
*/
TEXRESULT Get_ExternalFunction(void* DLL_Handle, void** pFunction, const UTF8* Name)
{
#ifndef NDEBUG
	if (DLL_Handle == NULL)
	{
		ArgsError("Get_ExternalFunction()", "DLL_Handle == NULLPTR");
		return Invalid_Parameter | Failure;
	}
	if (pFunction == NULL)
	{
		ArgsError("Get_ExternalFunction()", "pFunction == NULLPTR");
		return Invalid_Parameter | Failure;
	}
	if (Name == NULL)
	{
		ArgsError("Get_ExternalFunction()", "Name == NULLPTR");
		return Invalid_Parameter | Failure;
	}
#endif

#ifdef _TEX_WIN32_
	*pFunction = GetProcAddress((HMODULE)DLL_Handle, Name);
#else
	*pFunction = dlsym(DLL_Handle, Name);
#endif
	return Success;
}
/*
* Added in 1.0.0
* @param DLL_Handle, The handle of the DLL to close.
*/
void Close_DLL(void* DLL_Handle)
{
#ifndef NDEBUG
	if (DLL_Handle == NULL)
	{
		ArgsError("Get_ExternalFunction()", "DLL_Handle == NULLPTR");
		return;
	}
#endif

#ifdef _TEX_WIN32_
	FreeLibrary((HMODULE)DLL_Handle);
#else
	dlclose(DLL_Handle);
#endif
}

//////////////////////////////////////////
//Misc Functions
//////////////////////////////////////////

/*
* Added in 1.0.0
* Compares specified version set to engine version.
* @param MinVersion, the three version numbers of mininium compatibility.
* @param MaxVersion, the three version numbers of maxinium compatibility.
* @return Success if they are within range.
*/
TEXRESULT Check_VersionCompatibility(uint32_t MinVersion[3], uint32_t MaxVersion[3])
{
	if (MinVersion[0] <= EngineVersion[0] && MaxVersion[0] >= EngineVersion[0])
	{
		if (MinVersion[1] <= EngineVersion[1] && MaxVersion[1] >= EngineVersion[1])
		{
			if (MinVersion[2] <= EngineVersion[2] && MaxVersion[2] >= EngineVersion[2])
			{
				return Success;
			}
		}
	}
	return Failure;
}

//////////////////////////////////////////
//ExtensionData Functions
//////////////////////////////////////////

/*
* Added in 1.0.0
* Gets pointer that is an index that points to the ExtensionData in the main ExtensionDataBuffer from the Allocation.
* @param Allocation, Allocation of the extension to get pointer of.
*/
ExtensionData* Get_ExtensionDataPointer(ExtensionAllocation Allocation)
{
	return &Utils.ExtensionBuffer.Buffer[Allocation];
}
/*
* Added in 1.0.0
* when CreateInfo == NULLPTR the extensiondata will be blank.
* @param pAllocation, Pointer to a allocation to store the refrence to the newly created object.
* @param CreateInfo, Pointer to the createinfo that specifies parameters for the object.
*/
TEXRESULT Create_ExtensionData(ExtensionAllocation* pAllocation, ExtensionDataCreateInfo* CreateInfo)
{
#ifndef NDEBUG
	if (pAllocation == NULL)
	{
		ArgsError("Create_ExtensionData()", "pAllocation == NULL");
		return Invalid_Parameter | Failure;
	}
#endif
	Lock_Mutex(Utils.ExtensionBuffer.mutex);

	ExtensionData* pExtensionData = NULL;

	uint64_t reqchunks = 1;
	uint64_t resets = 0;
	uint64_t foundchunks = 0;

	while (foundchunks != reqchunks)
	{
		foundchunks = (Utils.ExtensionBuffer.Buffer[Utils.ExtensionBuffer.PrevPointer].AllocationSize == NULL) ? foundchunks + 1 : 0;

		Utils.ExtensionBuffer.PrevPointer++;
		if (Utils.ExtensionBuffer.PrevPointer > Utils.ExtensionBuffer.Max)
		{
			Utils.ExtensionBuffer.PrevPointer = 0;
			resets++;
			if (resets > 1)
			{
				FunctionError("Create_ExtensionData()", "Not Enough Space In Array, Resize Array ", NULL);
				return Resize_Array_Result | Failure;
			}
		}
	}
	uint64_t pointer = Utils.ExtensionBuffer.PrevPointer - reqchunks;


	pExtensionData = &Utils.ExtensionBuffer.Buffer[pointer];
	memset(pExtensionData, NULL, sizeof(ExtensionData) * reqchunks);

	pExtensionData->AllocationSize = reqchunks;
	pExtensionData->Allocation = pointer;

	*pAllocation = pExtensionData->Allocation;

	if (CreateInfo != NULL)
	{
		pExtensionData->Name = (char*)CopyData((void*)CreateInfo->Name);

		if (Open_DLL(&pExtensionData->handle, pExtensionData->Name) != Success)
		{
			FunctionError("Create_ExtensionData()", "Open_DLL() Failed.", NULL);
			return Failure;
		}

		void* pfunc = NULL;
		if (Get_ExternalFunction(pExtensionData->handle, &pfunc, "Initialise_Resources") != Success)
		{
			FunctionError("Create_ExtensionData()", "Get_ExternalFunction() Failed.", NULL);
			return Failure;
		}


		void(*EntryPoint)(ExtensionCreateInfo* ReturnInfo) =
			(void(*)(ExtensionCreateInfo* ReturnInfo))pfunc;

		ExtensionCreateInfo ExtenCreateInfo;
		memset(&ExtenCreateInfo, NULL, sizeof(ExtenCreateInfo));

		EntryPoint(&ExtenCreateInfo);

		pExtensionData->pFunctionsSize = ExtenCreateInfo.pFunctionsSize;
		pExtensionData->pFunctions = ExtenCreateInfo.pFunctions;

		pExtensionData->pResourcesSize = ExtenCreateInfo.pResourcesSize;
		pExtensionData->pResources = ExtenCreateInfo.pResources;


		pExtensionData->ConfigParametersSize = ExtenCreateInfo.ConfigParametersSize;
		pExtensionData->ConfigParameters = ExtenCreateInfo.ConfigParameters;


		pExtensionData->ExtensionVersion[0] = ExtenCreateInfo.ExtensionVersion[0];
		pExtensionData->ExtensionVersion[1] = ExtenCreateInfo.ExtensionVersion[1];
		pExtensionData->ExtensionVersion[2] = ExtenCreateInfo.ExtensionVersion[2];

		pExtensionData->MinRequiredVersion[0] = ExtenCreateInfo.MinRequiredVersion[0];
		pExtensionData->MinRequiredVersion[1] = ExtenCreateInfo.MinRequiredVersion[1];
		pExtensionData->MinRequiredVersion[2] = ExtenCreateInfo.MinRequiredVersion[2];

		pExtensionData->MaxRequiredVersion[0] = ExtenCreateInfo.MaxRequiredVersion[0];
		pExtensionData->MaxRequiredVersion[1] = ExtenCreateInfo.MaxRequiredVersion[1];
		pExtensionData->MaxRequiredVersion[2] = ExtenCreateInfo.MaxRequiredVersion[2];

		pExtensionData->BinType = ExtenCreateInfo.BinType;

		if (Check_VersionCompatibility(pExtensionData->MinRequiredVersion, pExtensionData->MaxRequiredVersion) == Failure)
		{
			printf("Engine Version %u.%u.%u is incompatible with Extension Version %u.%u.%u %u.%u.%u, %s\n",
				EngineVersion[0], EngineVersion[1], EngineVersion[2],
				pExtensionData->MinRequiredVersion[0], pExtensionData->MinRequiredVersion[1], pExtensionData->MinRequiredVersion[2],
				pExtensionData->MaxRequiredVersion[0], pExtensionData->MaxRequiredVersion[1], pExtensionData->MaxRequiredVersion[2],
				pExtensionData->Name);
		}

		if (pExtensionData->BinType != EngineBinType)
		{
			printf("Engine BinType is incompatible with ExtensionBintype, %s\n", pExtensionData->Name);
			return Failure;
		}
	}
	Unlock_Mutex(Utils.ExtensionBuffer.mutex);
	return Success;
}
/*
* Added in 1.0.0
* Destroys everything, including functioninfos and resourceinfos in it. 
* @param Allocation, Allocation of the extension to destroy.
*/
void Destroy_ExtensionData(ExtensionAllocation Allocation)
{
	ExtensionData* pExtensionData = Get_ExtensionDataPointer(Allocation);

	if (pExtensionData->Name != NULL)
		free((void*)pExtensionData->Name);

	for (size_t i = 0; i < pExtensionData->pFunctionsSize; i++)
	{
		if (pExtensionData->pFunctions[i]->Name != NULL)
			free(pExtensionData->pFunctions[i]->Name);
		if (pExtensionData->pFunctions[i]->Args != NULL)
			free(pExtensionData->pFunctions[i]->Args);

		free(pExtensionData->pFunctions[i]);
	}

	for (size_t i = 0; i < pExtensionData->pResourcesSize; i++)
	{
		if (pExtensionData->pResources[i]->Name != NULL)
			free(pExtensionData->pResources[i]->Name);

		free(pExtensionData->pResources[i]);
	}

	if (pExtensionData->pFunctions != NULL)
		free(pExtensionData->pFunctions);

	if (pExtensionData->pResources != NULL)
		free(pExtensionData->pResources);


	for (size_t i = 0; i < pExtensionData->ConfigParametersSize; i++)
	{
		if (pExtensionData->ConfigParameters[i].Name != NULL)
			free(pExtensionData->ConfigParameters[i].Name);

	}


	if (pExtensionData->ConfigParameters != NULL)
		free(pExtensionData->ConfigParameters);
	//end

	if (pExtensionData->handle != NULL)
		Close_DLL(pExtensionData->handle);

	memset(pExtensionData, NULL, sizeof(*pExtensionData) * pExtensionData->AllocationSize);
}

//////////////////////////////////////////
//ExtensionDataBuffer Functions
//////////////////////////////////////////

/*
* Added in 1.0.0
* Creates main ExtensionDataBuffer.
* @param InitialSize is the size in allocation chunks. (1 ExtensionData == 1 chunk).
*/
TEXRESULT Create_ExtensionDataBuffer(uint64_t InitialSize)
{
#ifndef NDEBUG
	if (InitialSize == NULL)
	{
		ArgsError("Create_ExtensionDataBuffer()", "InitialSize == NULL");
		return Invalid_Parameter | Failure;
	}
#endif
	memset(&Utils.ExtensionBuffer, NULL, sizeof(Utils.ExtensionBuffer));

	Utils.ExtensionBuffer.Buffer = (ExtensionData*)calloc(InitialSize, sizeof(*Utils.ExtensionBuffer.Buffer));
	Utils.ExtensionBuffer.Max = InitialSize;

	Create_Mutex(Utils.ExtensionBuffer.mutex, MutexType_Plain);

	return Success;
}
/*
* Added in 1.0.0
* Resizes the internal ExtensionDataBuffer
* @param NewSize is the size in allocation chunks. (1 ExtensionData == 1 chunk).
*/
TEXRESULT Resize_ExtensionDataBuffer(uint64_t NewSize)
{
#ifndef NDEBUG
	if (NewSize == NULL)
	{
		ArgsError("Resize_GameObjectBuffer()", "NewSize == NULL");
		return Invalid_Parameter;
	}
#endif
	Lock_Mutex(Utils.ExtensionBuffer.mutex);
	Resize_Array((void**)&Utils.ExtensionBuffer.Buffer, Utils.ExtensionBuffer.Max, NewSize, sizeof(*Utils.ExtensionBuffer.Buffer));
	Utils.ExtensionBuffer.Max = NewSize;
	Unlock_Mutex(Utils.ExtensionBuffer.mutex);
	return Success;
}
/*
* Added in 1.0.0
* Destroys main ExtensionDataBuffer.
*/
void Destroy_ExtensionDataBuffer()
{
	Lock_Mutex(Utils.ExtensionBuffer.mutex);

	for (size_t i = 0; i < Utils.ExtensionBuffer.Max;)
	{
		ExtensionData* pExtensionData = (ExtensionData*)&Utils.ExtensionBuffer.Buffer[i];
		if (pExtensionData->AllocationSize != NULL)
		{
			Destroy_ExtensionData(pExtensionData->Allocation);
			i += pExtensionData->AllocationSize;
		}
		else
		{
			i++;
		}
	}

	Utils.ExtensionBuffer.PrevPointer = 0;
	Utils.ExtensionBuffer.Max = 0;
	if (Utils.ExtensionBuffer.Buffer != NULL)
		free(Utils.ExtensionBuffer.Buffer);

	Destroy_Mutex(Utils.ExtensionBuffer.mutex);

	memset(&Utils.ExtensionBuffer, NULL, sizeof(Utils.ExtensionBuffer));
}

//////////////////////////////////////////
//Resolver/Linker
//////////////////////////////////////////

/*
* Added in 1.0.0
* Resolves all Symbols in the game engine. (required for function)
* compares symbols and if they match equalize their values.
*/
void Resolve_Linkages()
{
	for (size_t i = 0; i < Utils.ExtensionBuffer.Max;)
	{
		ExtensionData* pExtension = &Utils.ExtensionBuffer.Buffer[i];
		if (pExtension->AllocationSize != NULL)
		{
			for (size_t i1 = 0; i1 < pExtension->pResourcesSize; i1++)
			{
				if (*pExtension->pResources[i1]->ppResource == NULL)
				{
					for (size_t i2 = 0; i2 < Utils.Category.ExternalResourcesSize; i2++)
					{
						if (strcmp(pExtension->pResources[i1]->Name, Utils.Category.ExternalResources[i2]->Name) == 0 && *Utils.Category.ExternalResources[i2]->ppResource != NULL)
						{
							*pExtension->pResources[i1]->ppResource = *Utils.Category.ExternalResources[i2]->ppResource;
							break;
						}
					}
				}
				else
				{

				}
			}
			for (size_t i1 = 0; i1 < pExtension->pFunctionsSize; i1++)
			{
				if (*pExtension->pFunctions[i1]->ppFunction == NULL)
				{
					for (size_t i2 = 0; i2 < Utils.Category.ExternalFunctionsSize; i2++)
					{
						if (strcmp(pExtension->pFunctions[i1]->Name, Utils.Category.ExternalFunctions[i2]->Name) == 0 && *Utils.Category.ExternalFunctions[i2]->ppFunction != NULL)
						{
							*pExtension->pFunctions[i1]->ppFunction = *Utils.Category.ExternalFunctions[i2]->ppFunction;
							break;
						}
					}
				}
				else
				{

				}
			}
			i += pExtension->AllocationSize;
		}
		else
		{
			i++;
		}
	}
}


int Recreate_Categories_cmpfunc(FunctionInfo** a, FunctionInfo** b)
{
	if ((*a)->Priority < (*b)->Priority)  return -1;
	if ((*a)->Priority == (*b)->Priority)  return 0;
	if ((*a)->Priority > (*b)->Priority)  return 1;
}
/*
* Added in 1.0.0
* Resets and refills all the optimization categories. (required for function)
*/
void Recreate_Categories()
{
	free(Utils.Category.ExternalFunctions);
	free(Utils.Category.ExternalResources);

	free(Utils.Category.Construct);
	free(Utils.Category.Destruct);
	free(Utils.Category.EveryFrame);
	free(Utils.Category.Key_Input);
	free(Utils.Category.Character_Input);
	free(Utils.Category.MouseButton_Input);
	free(Utils.Category.MousePos_Input);
	free(Utils.Category.MouseEnter_Input);
	free(Utils.Category.Scroll_Input);
	free(Utils.Category.Joystick_Connect);
	free(Utils.Category.Monitor_Connect);
	free(Utils.Category.Drop_Input);
	free(Utils.Category.Window_Resize);
	free(Utils.Category.FrameBuffer_Resize);
	free(Utils.Category.Window_Refresh);
	free(Utils.Category.Window_Minimise);
	free(Utils.Category.Window_Move);
	free(Utils.Category.Window_Minimise);
	free(Utils.Category.Window_Focused);
	free(Utils.Category.Window_Close);
	free(Utils.Category.Window_Open);


#define AddToCategory(Category, CategorySize, pInfo)\
	Resize_Array((void**)&Category, CategorySize, CategorySize + 1, sizeof(*Category));\
	Category[CategorySize] = pInfo;\
	CategorySize += 1;


	for (size_t i = 0; i < Utils.ExtensionBuffer.Max;)
	{
		ExtensionData* pExtension = &Utils.ExtensionBuffer.Buffer[i];
		if (pExtension->AllocationSize != NULL)
		{
			for (size_t i1 = 0; i1 < pExtension->pFunctionsSize; i1++){
				AddToCategory(Utils.Category.ExternalFunctions, Utils.Category.ExternalFunctionsSize, pExtension->pFunctions[i1]);
			}

			for (size_t i1 = 0; i1 < pExtension->pResourcesSize; i1++){
				AddToCategory(Utils.Category.ExternalResources, Utils.Category.ExternalResourcesSize, pExtension->pResources[i1])
			}
			i += pExtension->AllocationSize;
		}
		else
		{
			i++;
		}
		
	}


	for (size_t i = 0; i < Utils.ExtensionBuffer.Max;)
	{
		ExtensionData* pExtension = &Utils.ExtensionBuffer.Buffer[i];
		if (pExtension->AllocationSize != NULL)
		{
			for (size_t i1 = 0; i1 < pExtension->pFunctionsSize; i1++)
			{
				FunctionInfo* pFunctionInfo = pExtension->pFunctions[i1];
				uint32_t flagbits = pFunctionInfo->CallFlags;
				//CALLFLAG SYSTEM VERY COOL THANK YOU AUGUST 
				if (flagbits & Construct){
					AddToCategory(Utils.Category.Construct, Utils.Category.ConstructSize, pFunctionInfo)
				}
				if (flagbits & Destruct) {
					AddToCategory(Utils.Category.Destruct, Utils.Category.DestructSize, pFunctionInfo)
				}
				if (flagbits & EveryFrame) {
					AddToCategory(Utils.Category.EveryFrame, Utils.Category.EveryFrameSize, pFunctionInfo)
				}
				if (flagbits & Key_Input) {
					AddToCategory(Utils.Category.Key_Input, Utils.Category.Key_InputSize, pFunctionInfo)
				}
				if (flagbits & Character_Input) {
					AddToCategory(Utils.Category.Character_Input, Utils.Category.Character_InputSize, pFunctionInfo)
				}
				if (flagbits & MouseButton_Input) {
					AddToCategory(Utils.Category.MouseButton_Input, Utils.Category.MouseButton_InputSize, pFunctionInfo)
				}
				if (flagbits & MousePos_Input) {
					AddToCategory(Utils.Category.MousePos_Input, Utils.Category.MousePos_InputSize, pFunctionInfo)
				}
				if (flagbits & MouseEnter_Input) {
					AddToCategory(Utils.Category.MouseEnter_Input, Utils.Category.MouseEnter_InputSize, pFunctionInfo)
				}
				if (flagbits & Scroll_Input) {
					AddToCategory(Utils.Category.Scroll_Input, Utils.Category.Scroll_InputSize, pFunctionInfo)
				}
				if (flagbits & Joystick_Connect) {
					AddToCategory(Utils.Category.Joystick_Connect, Utils.Category.Joystick_ConnectSize, pFunctionInfo)
				}
				if (flagbits & Monitor_Connect) {
					AddToCategory(Utils.Category.Monitor_Connect, Utils.Category.Monitor_ConnectSize, pFunctionInfo)
				}
				if (flagbits & Drop_Input) {
					AddToCategory(Utils.Category.Drop_Input, Utils.Category.Drop_InputSize, pFunctionInfo)
				}
				if (flagbits & Window_Resize) {
					AddToCategory(Utils.Category.Window_Resize, Utils.Category.Window_ResizeSize, pFunctionInfo)
				}
				if (flagbits & FrameBuffer_Resize) {
					AddToCategory(Utils.Category.FrameBuffer_Resize, Utils.Category.FrameBuffer_ResizeSize, pFunctionInfo)
				}
				if (flagbits & Window_Refresh) {
					AddToCategory(Utils.Category.Window_Refresh, Utils.Category.Window_RefreshSize, pFunctionInfo)
				}
				if (flagbits & Window_Move) {
					AddToCategory(Utils.Category.Window_Move, Utils.Category.Window_MoveSize, pFunctionInfo)
				}
				if (flagbits & Window_Minimise) {
					AddToCategory(Utils.Category.Window_Minimise, Utils.Category.Window_MinimiseSize, pFunctionInfo)
				}
				if (flagbits & Window_Focused) {
					AddToCategory(Utils.Category.Window_Focused, Utils.Category.Window_FocusedSize, pFunctionInfo)
				}
				if (flagbits & Window_Close) {
					AddToCategory(Utils.Category.Window_Close, Utils.Category.Window_CloseSize, pFunctionInfo)
				}
				if (flagbits & Window_Open) {
					AddToCategory(Utils.Category.Window_Open, Utils.Category.Window_OpenSize, pFunctionInfo)
				}
			}
			i += pExtension->AllocationSize;
		}
		else
		{
			i++;
		}
	}


	//reorder the optimization categories


#define sort(Category, CategorySize)\
	if (CategorySize != NULL && Category != NULL)\
		qsort(Category, CategorySize, sizeof(*Category), Recreate_Categories_cmpfunc);


	sort(Utils.Category.Construct, Utils.Category.ConstructSize);
	sort(Utils.Category.Destruct, Utils.Category.DestructSize);
	sort(Utils.Category.EveryFrame, Utils.Category.EveryFrameSize);
	sort(Utils.Category.Key_Input, Utils.Category.Key_InputSize);
	sort(Utils.Category.Character_Input, Utils.Category.Character_InputSize);
	sort(Utils.Category.MouseButton_Input, Utils.Category.MouseButton_InputSize);
	sort(Utils.Category.MousePos_Input, Utils.Category.MousePos_InputSize);
	sort(Utils.Category.MouseEnter_Input, Utils.Category.MouseEnter_InputSize);
	sort(Utils.Category.Scroll_Input, Utils.Category.Scroll_InputSize);
	sort(Utils.Category.Joystick_Connect, Utils.Category.Joystick_ConnectSize);
	sort(Utils.Category.Monitor_Connect, Utils.Category.Monitor_ConnectSize);
	sort(Utils.Category.Drop_Input, Utils.Category.Drop_InputSize);
	sort(Utils.Category.Window_Resize, Utils.Category.Window_ResizeSize);
	sort(Utils.Category.FrameBuffer_Resize, Utils.Category.FrameBuffer_ResizeSize);
	sort(Utils.Category.Window_Refresh, Utils.Category.Window_RefreshSize);
	sort(Utils.Category.Window_Move, Utils.Category.Window_MoveSize);
	sort(Utils.Category.Window_Minimise, Utils.Category.Window_MinimiseSize);
	sort(Utils.Category.Window_Focused, Utils.Category.Window_FocusedSize);
	sort(Utils.Category.Window_Close, Utils.Category.Window_CloseSize);
	sort(Utils.Category.Window_Open, Utils.Category.Window_OpenSize);
	
}
/*
* Added in 1.0.0
* Runs FunctionInfo.
* @param pFunctionInfo Pointer to FunctionInfo of the function to run.
*/
void Run_ExternalFunction(FunctionInfo* pFunctionInfo) //could cause crash on linux
{
	void* pfunction = *pFunctionInfo->ppFunction;
	TEXRESULT(*function)(ResourceInfo*) = (TEXRESULT(*)(ResourceInfo*))pfunction;
	TEXRESULT res = Success;
	if ((res = function(pFunctionInfo->Args)) != Success)
	{
		FunctionError(pFunctionInfo->Name, "Returned Non-Success. TEXRESULT == ", res);
		return;
	}
}
/*
* Added in 1.0.0
* Like Resolve_Linkages but only resolves 1 item.
* @param pReturnInfo Pointer to a FunctionInfo struct where the resolved symbol will be stored.
*/
TEXRESULT Resolve_FunctionSymbol(FunctionInfo* pReturnInfo)
{
	for (size_t i2 = 0; i2 < Utils.Category.ExternalFunctionsSize; i2++)
	{
		if (strcmp(pReturnInfo->Name, Utils.Category.ExternalFunctions[i2]->Name) == 0 && *Utils.Category.ExternalFunctions[i2]->ppFunction != NULL)
		{
			*pReturnInfo->ppFunction = *Utils.Category.ExternalFunctions[i2]->ppFunction;
			break;
		}
	}
	return Success;
}
/*
* Added in 1.0.0
* Like Resolve_Linkages but only resolves 1 item.
* @param pReturnResource Pointer to a ResourceInfo struct where the resolved symbol will be stored.
*/
TEXRESULT Resolve_ResourceSymbol(ResourceInfo* pReturnResource)
{
	for (size_t i2 = 0; i2 < Utils.Category.ExternalResourcesSize; i2++)
	{
		if (strcmp(pReturnResource->Name, Utils.Category.ExternalResources[i2]->Name) == 0 && *Utils.Category.ExternalResources[i2]->ppResource != NULL)
		{
			*pReturnResource->ppResource = *Utils.Category.ExternalResources[i2]->ppResource;
			break;
		}
	}
	return Success;
}

//////////////////////////////////////////
//Window Functions
//////////////////////////////////////////

#ifdef _WIN32
Key WindowsKeyCode_To_TriangleEngine(Window* pWindow, KeyState state, uint32_t keycode)
{
	switch (keycode)
	{
	case VK_SPACE: pWindow->STATE_KEY_SPACE = state; break;
	case VK_OEM_7: pWindow->STATE_KEY_APOSTROPHE = state; break;
	case VK_OEM_COMMA: pWindow->STATE_KEY_COMMA = state; break;
	case VK_OEM_MINUS: pWindow->STATE_KEY_MINUS = state; break;
	case VK_OEM_PERIOD: pWindow->STATE_KEY_PERIOD = state; break;
	case VK_OEM_2: pWindow->STATE_KEY_SLASH = state; break;
	case 0x30: pWindow->STATE_KEY_0 = state; break;
	case 0x31: pWindow->STATE_KEY_1 = state; break;
	case 0x32: pWindow->STATE_KEY_2 = state; break;
	case 0x33: pWindow->STATE_KEY_3 = state; break;
	case 0x34: pWindow->STATE_KEY_4 = state; break;
	case 0x35: pWindow->STATE_KEY_5 = state; break;
	case 0x36: pWindow->STATE_KEY_6 = state; break;
	case 0x37: pWindow->STATE_KEY_7 = state; break;
	case 0x38: pWindow->STATE_KEY_8 = state; break;
	case 0x39: pWindow->STATE_KEY_9 = state; break;
	case VK_OEM_1: pWindow->STATE_KEY_SEMICOLON = state; break;
	case VK_OEM_PLUS: pWindow->STATE_KEY_PLUS = state; break;
	case 0x41: pWindow->STATE_KEY_A = state; break;
	case 0x42: pWindow->STATE_KEY_B = state; break;
	case 0x43: pWindow->STATE_KEY_C = state; break;
	case 0x44: pWindow->STATE_KEY_D = state; break;
	case 0x45: pWindow->STATE_KEY_E = state; break;
	case 0x46: pWindow->STATE_KEY_F = state; break;
	case 0x47: pWindow->STATE_KEY_G = state; break;
	case 0x48: pWindow->STATE_KEY_H = state; break;
	case 0x49: pWindow->STATE_KEY_I = state; break;
	case 0x4A: pWindow->STATE_KEY_J = state; break;
	case 0x4B: pWindow->STATE_KEY_K = state; break;
	case 0x4C: pWindow->STATE_KEY_L = state; break;
	case 0x4D: pWindow->STATE_KEY_M = state; break;
	case 0x4E: pWindow->STATE_KEY_N = state; break;
	case 0x4F: pWindow->STATE_KEY_O = state; break;
	case 0x50: pWindow->STATE_KEY_P = state; break;
	case 0x51: pWindow->STATE_KEY_Q = state; break;
	case 0x52: pWindow->STATE_KEY_R = state; break;
	case 0x53: pWindow->STATE_KEY_S = state; break;
	case 0x54: pWindow->STATE_KEY_T = state; break;
	case 0x55: pWindow->STATE_KEY_U = state; break;
	case 0x56: pWindow->STATE_KEY_V = state; break;
	case 0x57: pWindow->STATE_KEY_W = state; break;
	case 0x58: pWindow->STATE_KEY_X = state; break;
	case 0x59: pWindow->STATE_KEY_Y = state; break;
	case 0x5A: pWindow->STATE_KEY_Z = state; break;
	case VK_OEM_4: pWindow->STATE_KEY_LEFT_BRACKET = state; break;
	case VK_OEM_5: pWindow->STATE_KEY_BACKSLASH = state; break;
	case VK_OEM_6: pWindow->STATE_KEY_RIGHT_BRACKET = state; break;
	case VK_OEM_3: pWindow->STATE_KEY_GRAVE_ACCENT = state; break;
	case VK_OEM_8: pWindow->STATE_KEY_WORLD_1 = state; break;
	case VK_OEM_102: pWindow->STATE_KEY_WORLD_2 = state; break;
	case VK_ESCAPE: pWindow->STATE_KEY_ESCAPE = state; break;
	case VK_RETURN: pWindow->STATE_KEY_ENTER = state; pWindow->STATE_KEY_KP_ENTER = state; break;
	case VK_TAB: pWindow->STATE_KEY_TAB = state; break;
	case VK_BACK: pWindow->STATE_KEY_BACKSPACE = state; break;
	case VK_INSERT: pWindow->STATE_KEY_INSERT = state; break;
	case VK_DELETE: pWindow->STATE_KEY_DELETE = state; break;
	case VK_RIGHT: pWindow->STATE_KEY_RIGHT = state; break;
	case VK_LEFT: pWindow->STATE_KEY_LEFT = state; break;
	case VK_DOWN: pWindow->STATE_KEY_DOWN = state; break;
	case VK_UP: pWindow->STATE_KEY_UP = state; break;
	case VK_PRIOR: pWindow->STATE_KEY_PAGE_UP = state; break;
	case VK_NEXT: pWindow->STATE_KEY_PAGE_DOWN = state; break;
	case VK_HOME: pWindow->STATE_KEY_HOME = state; break;
	case VK_END: pWindow->STATE_KEY_END = state; break;
	case VK_CAPITAL: pWindow->STATE_KEY_CAPS_LOCK = state; break;
	case VK_SCROLL: pWindow->STATE_KEY_SCROLL_LOCK = state; break;
	case VK_NUMLOCK: pWindow->STATE_KEY_NUM_LOCK = state; break;
	case VK_SNAPSHOT: pWindow->STATE_KEY_PRINT_SCREEN = state; break;
	case VK_PAUSE: pWindow->STATE_KEY_PAUSE = state; break;
	case VK_F1: pWindow->STATE_KEY_F1 = state; break;
	case VK_F2: pWindow->STATE_KEY_F2 = state; break;
	case VK_F3: pWindow->STATE_KEY_F3 = state; break;
	case VK_F4: pWindow->STATE_KEY_F4 = state; break;
	case VK_F5: pWindow->STATE_KEY_F5 = state; break;
	case VK_F6: pWindow->STATE_KEY_F6 = state; break;
	case VK_F7: pWindow->STATE_KEY_F7 = state; break;
	case VK_F8: pWindow->STATE_KEY_F8 = state; break;
	case VK_F9: pWindow->STATE_KEY_F9 = state; break;
	case VK_F10: pWindow->STATE_KEY_F10 = state; break;
	case VK_F11: pWindow->STATE_KEY_F11 = state; break;
	case VK_F12: pWindow->STATE_KEY_F12 = state; break;
	case VK_F13: pWindow->STATE_KEY_F13 = state; break;
	case VK_F14: pWindow->STATE_KEY_F14 = state; break;
	case VK_F15: pWindow->STATE_KEY_F15 = state; break;
	case VK_F16: pWindow->STATE_KEY_F16 = state; break;
	case VK_F17: pWindow->STATE_KEY_F17 = state; break;
	case VK_F18: pWindow->STATE_KEY_F18 = state; break;
	case VK_F19: pWindow->STATE_KEY_F19 = state; break;
	case VK_F20: pWindow->STATE_KEY_F20 = state; break;
	case VK_F21: pWindow->STATE_KEY_F21 = state; break;
	case VK_F22: pWindow->STATE_KEY_F22 = state; break;
	case VK_F23: pWindow->STATE_KEY_F23 = state; break;
	case VK_F24: pWindow->STATE_KEY_F24 = state; break;
	case VK_NUMPAD0: pWindow->STATE_KEY_KP_0 = state; break;
	case VK_NUMPAD1: pWindow->STATE_KEY_KP_1 = state; break;
	case VK_NUMPAD2: pWindow->STATE_KEY_KP_2 = state; break;
	case VK_NUMPAD3: pWindow->STATE_KEY_KP_3 = state; break;
	case VK_NUMPAD4: pWindow->STATE_KEY_KP_4 = state; break;
	case VK_NUMPAD5: pWindow->STATE_KEY_KP_5 = state; break;
	case VK_NUMPAD6: pWindow->STATE_KEY_KP_6 = state; break;
	case VK_NUMPAD7: pWindow->STATE_KEY_KP_7 = state; break;
	case VK_NUMPAD8: pWindow->STATE_KEY_KP_8 = state; break;
	case VK_NUMPAD9: pWindow->STATE_KEY_KP_9 = state; break;
	case VK_DECIMAL: pWindow->STATE_KEY_KP_DECIMAL = state; break;
	case VK_DIVIDE: pWindow->STATE_KEY_KP_DIVIDE = state; break;
	case VK_MULTIPLY: pWindow->STATE_KEY_KP_MULTIPLY = state; break;
	case VK_SUBTRACT: pWindow->STATE_KEY_KP_SUBTRACT = state; break;
	case VK_ADD: pWindow->STATE_KEY_KP_ADD = state; break;
	case VK_LSHIFT: pWindow->STATE_KEY_LEFT_SHIFT = state; break;
	case VK_LCONTROL: pWindow->STATE_KEY_LEFT_CONTROL = state; break;
	case VK_LMENU: pWindow->STATE_KEY_LEFT_ALT = state; break;
	case VK_LWIN: pWindow->STATE_KEY_LEFT_SUPER = state; break;
	case VK_RSHIFT: pWindow->STATE_KEY_RIGHT_SHIFT = state; break;
	case VK_RCONTROL: pWindow->STATE_KEY_RIGHT_CONTROL = state; break;
	case VK_RMENU: pWindow->STATE_KEY_RIGHT_ALT = state; break;
	case VK_RWIN: pWindow->STATE_KEY_RIGHT_SUPER = state; break;
	case VK_APPS: pWindow->STATE_KEY_MENU = state; break;

	case VK_SHIFT: pWindow->STATE_KEY_LEFT_SHIFT = state; pWindow->STATE_KEY_RIGHT_SHIFT = state; break;
	case VK_CONTROL: pWindow->STATE_KEY_LEFT_CONTROL = state; pWindow->STATE_KEY_RIGHT_CONTROL = state; break;
	case VK_MENU: pWindow->STATE_KEY_LEFT_ALT = state; pWindow->STATE_KEY_RIGHT_ALT = state; break;
	}
}

void SetValue_To_KeyState(Window* pWindow, KeyState state, Key key)
{
	switch (key)
	{
	case KEY_SPACE: pWindow->STATE_KEY_SPACE = state; break;
	case KEY_APOSTROPHE: pWindow->STATE_KEY_APOSTROPHE = state; break;
	case KEY_COMMA: pWindow->STATE_KEY_COMMA = state; break;
	case KEY_MINUS: pWindow->STATE_KEY_MINUS = state; break;
	case KEY_PERIOD: pWindow->STATE_KEY_PERIOD = state; break;
	case KEY_SLASH: pWindow->STATE_KEY_SLASH = state; break;
	case KEY_0: pWindow->STATE_KEY_0 = state; break;
	case KEY_1: pWindow->STATE_KEY_1 = state; break;
	case KEY_2: pWindow->STATE_KEY_2 = state; break;
	case KEY_3: pWindow->STATE_KEY_3 = state; break;
	case KEY_4: pWindow->STATE_KEY_4 = state; break;
	case KEY_5: pWindow->STATE_KEY_5 = state; break;
	case KEY_6: pWindow->STATE_KEY_6 = state; break;
	case KEY_7: pWindow->STATE_KEY_7 = state; break;
	case KEY_8: pWindow->STATE_KEY_8 = state; break;
	case KEY_9: pWindow->STATE_KEY_9 = state; break;
	case KEY_SEMICOLON: pWindow->STATE_KEY_SEMICOLON = state; break;
	case KEY_PLUS: pWindow->STATE_KEY_PLUS = state; break;
	case KEY_A: pWindow->STATE_KEY_A = state; break;
	case KEY_B: pWindow->STATE_KEY_B = state; break;
	case KEY_C: pWindow->STATE_KEY_C = state; break;
	case KEY_D: pWindow->STATE_KEY_D = state; break;
	case KEY_E: pWindow->STATE_KEY_E = state; break;
	case KEY_F: pWindow->STATE_KEY_F = state; break;
	case KEY_G: pWindow->STATE_KEY_G = state; break;
	case KEY_H: pWindow->STATE_KEY_H = state; break;
	case KEY_I: pWindow->STATE_KEY_I = state; break;
	case KEY_J: pWindow->STATE_KEY_J = state; break;
	case KEY_K: pWindow->STATE_KEY_K = state; break;
	case KEY_L: pWindow->STATE_KEY_L = state; break;
	case KEY_M: pWindow->STATE_KEY_M = state; break;
	case KEY_N: pWindow->STATE_KEY_N = state; break;
	case KEY_O: pWindow->STATE_KEY_O = state; break;
	case KEY_P: pWindow->STATE_KEY_P = state; break;
	case KEY_Q: pWindow->STATE_KEY_Q = state; break;
	case KEY_R: pWindow->STATE_KEY_R = state; break;
	case KEY_S: pWindow->STATE_KEY_S = state; break;
	case KEY_T: pWindow->STATE_KEY_T = state; break;
	case KEY_U: pWindow->STATE_KEY_U = state; break;
	case KEY_V: pWindow->STATE_KEY_V = state; break;
	case KEY_W: pWindow->STATE_KEY_W = state; break;
	case KEY_X: pWindow->STATE_KEY_X = state; break;
	case KEY_Y: pWindow->STATE_KEY_Y = state; break;
	case KEY_Z: pWindow->STATE_KEY_Z = state; break;
	case KEY_LEFT_BRACKET: pWindow->STATE_KEY_LEFT_BRACKET = state; break;
	case KEY_BACKSLASH: pWindow->STATE_KEY_BACKSLASH = state; break;
	case KEY_RIGHT_BRACKET: pWindow->STATE_KEY_RIGHT_BRACKET = state; break;
	case KEY_GRAVE_ACCENT: pWindow->STATE_KEY_GRAVE_ACCENT = state; break;
	case KEY_WORLD_1: pWindow->STATE_KEY_WORLD_1 = state; break;
	case KEY_WORLD_2: pWindow->STATE_KEY_WORLD_2 = state; break;
	case KEY_ESCAPE: pWindow->STATE_KEY_ESCAPE = state; break;
	case KEY_ENTER: pWindow->STATE_KEY_ENTER = state; break;
	case KEY_TAB: pWindow->STATE_KEY_TAB = state; break;
	case KEY_BACKSPACE: pWindow->STATE_KEY_BACKSPACE = state; break;
	case KEY_INSERT: pWindow->STATE_KEY_INSERT = state; break;
	case KEY_DELETE: pWindow->STATE_KEY_DELETE = state; break;
	case KEY_RIGHT: pWindow->STATE_KEY_RIGHT = state; break;
	case KEY_LEFT: pWindow->STATE_KEY_LEFT = state; break;
	case KEY_DOWN: pWindow->STATE_KEY_DOWN = state; break;
	case KEY_UP: pWindow->STATE_KEY_UP = state; break;
	case KEY_PAGE_UP: pWindow->STATE_KEY_PAGE_UP = state; break;
	case KEY_PAGE_DOWN: pWindow->STATE_KEY_PAGE_DOWN = state; break;
	case KEY_HOME: pWindow->STATE_KEY_HOME = state; break;
	case KEY_END: pWindow->STATE_KEY_END = state; break;
	case KEY_CAPS_LOCK: pWindow->STATE_KEY_CAPS_LOCK = state; break;
	case KEY_SCROLL_LOCK: pWindow->STATE_KEY_SCROLL_LOCK = state; break;
	case KEY_NUM_LOCK: pWindow->STATE_KEY_NUM_LOCK = state; break;
	case KEY_PRINT_SCREEN: pWindow->STATE_KEY_PRINT_SCREEN = state; break;
	case KEY_PAUSE: pWindow->STATE_KEY_PAUSE = state; break;
	case KEY_F1: pWindow->STATE_KEY_F1 = state; break;
	case KEY_F2: pWindow->STATE_KEY_F2 = state; break;
	case KEY_F3: pWindow->STATE_KEY_F3 = state; break;
	case KEY_F4: pWindow->STATE_KEY_F4 = state; break;
	case KEY_F5: pWindow->STATE_KEY_F5 = state; break;
	case KEY_F6: pWindow->STATE_KEY_F6 = state; break;
	case KEY_F7: pWindow->STATE_KEY_F7 = state; break;
	case KEY_F8: pWindow->STATE_KEY_F8 = state; break;
	case KEY_F9: pWindow->STATE_KEY_F9 = state; break;
	case KEY_F10: pWindow->STATE_KEY_F10 = state; break;
	case KEY_F11: pWindow->STATE_KEY_F11 = state; break;
	case KEY_F12: pWindow->STATE_KEY_F12 = state; break;
	case KEY_F13: pWindow->STATE_KEY_F13 = state; break;
	case KEY_F14: pWindow->STATE_KEY_F14 = state; break;
	case KEY_F15: pWindow->STATE_KEY_F15 = state; break;
	case KEY_F16: pWindow->STATE_KEY_F16 = state; break;
	case KEY_F17: pWindow->STATE_KEY_F17 = state; break;
	case KEY_F18: pWindow->STATE_KEY_F18 = state; break;
	case KEY_F19: pWindow->STATE_KEY_F19 = state; break;
	case KEY_F20: pWindow->STATE_KEY_F20 = state; break;
	case KEY_F21: pWindow->STATE_KEY_F21 = state; break;
	case KEY_F22: pWindow->STATE_KEY_F22 = state; break;
	case KEY_F23: pWindow->STATE_KEY_F23 = state; break;
	case KEY_F24: pWindow->STATE_KEY_F24 = state; break;
	case KEY_KP_0: pWindow->STATE_KEY_KP_0 = state; break;
	case KEY_KP_1: pWindow->STATE_KEY_KP_1 = state; break;
	case KEY_KP_2: pWindow->STATE_KEY_KP_2 = state; break;
	case KEY_KP_3: pWindow->STATE_KEY_KP_3 = state; break;
	case KEY_KP_4: pWindow->STATE_KEY_KP_4 = state; break;
	case KEY_KP_5: pWindow->STATE_KEY_KP_5 = state; break;
	case KEY_KP_6: pWindow->STATE_KEY_KP_6 = state; break;
	case KEY_KP_7: pWindow->STATE_KEY_KP_7 = state; break;
	case KEY_KP_8: pWindow->STATE_KEY_KP_8 = state; break;
	case KEY_KP_9: pWindow->STATE_KEY_KP_9 = state; break;
	case KEY_KP_DECIMAL: pWindow->STATE_KEY_KP_DECIMAL = state; break;
	case KEY_KP_DIVIDE: pWindow->STATE_KEY_KP_DIVIDE = state; break;
	case KEY_KP_MULTIPLY: pWindow->STATE_KEY_KP_MULTIPLY = state; break;
	case KEY_KP_SUBTRACT: pWindow->STATE_KEY_KP_SUBTRACT = state; break;
	case KEY_KP_ADD: pWindow->STATE_KEY_KP_ADD = state; break;
	case KEY_KP_ENTER: pWindow->STATE_KEY_KP_ENTER = state; break;
	case KEY_LEFT_SHIFT: pWindow->STATE_KEY_LEFT_SHIFT = state; break;
	case KEY_LEFT_CONTROL: pWindow->STATE_KEY_LEFT_CONTROL = state; break;
	case KEY_LEFT_ALT: pWindow->STATE_KEY_LEFT_ALT = state; break;
	case KEY_LEFT_SUPER: pWindow->STATE_KEY_LEFT_SUPER = state; break;
	case KEY_RIGHT_SHIFT: pWindow->STATE_KEY_RIGHT_SHIFT = state; break;
	case KEY_RIGHT_CONTROL: pWindow->STATE_KEY_RIGHT_CONTROL = state; break;
	case KEY_RIGHT_ALT: pWindow->STATE_KEY_RIGHT_ALT = state; break;
	case KEY_RIGHT_SUPER: pWindow->STATE_KEY_RIGHT_SUPER = state; break;
	case KEY_MENU: pWindow->STATE_KEY_MENU = state; break;
	}
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* pWindow = NULL;
	for (size_t i = 0; i < Utils.pWindowsSize; i++)
		if (Utils.pWindows[i]->Window == hwnd)
			pWindow = Utils.pWindows[i];

	switch (uMsg)
	{
	case WM_DESTROY:

		return 0;
	case WM_MOVE: // Handle window MOVING
		if (pWindow->FullScreen != true)
		{
			Utils.Window_Move_Callback_state.pWindow = pWindow;
			Utils.Window_Move_Callback_state.X_Position = LOWORD(lParam);
			Utils.Window_Move_Callback_state.Y_Position = HIWORD(lParam);
			for (size_t i = 0; i < Utils.Category.Window_MoveSize; i++)
				Run_ExternalFunction(Utils.Category.Window_Move[i]);
		}
		return 0;
	case WM_SIZE: // Handle window resizing
		if (pWindow->FullScreen != true)
		{
			Utils.Window_Resize_Callback_state.pWindow = pWindow;
			Utils.Window_Resize_Callback_state.NewWidth = LOWORD(lParam);
			Utils.Window_Resize_Callback_state.NewHeight = HIWORD(lParam);
			for (size_t i = 0; i < Utils.Category.Window_ResizeSize; i++)
				Run_ExternalFunction(Utils.Category.Window_Resize[i]);

			Utils.FrameBuffer_Resize_Callback_state.pWindow = pWindow;
			Utils.FrameBuffer_Resize_Callback_state.NewWidth = LOWORD(lParam);
			Utils.FrameBuffer_Resize_Callback_state.NewHeight = HIWORD(lParam);
			for (size_t i = 0; i < Utils.Category.FrameBuffer_ResizeSize; i++)
				Run_ExternalFunction(Utils.Category.FrameBuffer_Resize[i]);

			if (wParam == SIZE_MINIMIZED)
			{
				Utils.Window_Minimise_Callback_state.pWindow = pWindow;
				Utils.Window_Minimise_Callback_state.Iconified = true;
				for (size_t i = 0; i < Utils.Category.Window_MinimiseSize; i++)
					Run_ExternalFunction(Utils.Category.Window_Minimise[i]);
			}
			if ((wParam == SIZE_MAXIMIZED) || (wParam == SIZE_RESTORED))
			{
				Utils.Window_Minimise_Callback_state.pWindow = pWindow;
				Utils.Window_Minimise_Callback_state.Iconified = false;
				for (size_t i = 0; i < Utils.Category.Window_MinimiseSize; i++)
					Run_ExternalFunction(Utils.Category.Window_Minimise[i]);
			}
		}
		return 0;
	case WM_SETFOCUS:
		Utils.Window_Focused_Callback_state.pWindow = pWindow;
		Utils.Window_Focused_Callback_state.Focus = true;
		for (size_t i = 0; i < Utils.Category.Window_FocusedSize; i++)
			Run_ExternalFunction(Utils.Category.Window_Focused[i]);
		return 0;
	case WM_KILLFOCUS:
		Utils.Window_Focused_Callback_state.pWindow = pWindow;
		Utils.Window_Focused_Callback_state.Focus = false;
		for (size_t i = 0; i < Utils.Category.Window_FocusedSize; i++)
			Run_ExternalFunction(Utils.Category.Window_Focused[i]);
		return 0;
	case WM_CLOSE:
		Utils.Window_Close_Callback_state.pWindow = pWindow;
		for (size_t i = 0; i < Utils.Category.Window_CloseSize; i++)
			Run_ExternalFunction(Utils.Category.Window_Close[i]);
		return 0;
	case WM_KEYDOWN:
		Utils.Key_Callback_state.pWindow = pWindow;
		WindowsKeyCode_To_TriangleEngine(pWindow, KeyPress, wParam);
		Utils.Key_Callback_state.KeyCode = Utils.Key_Callback_state.KeyCode;
		Utils.Key_Callback_state.ScanCode = (lParam >> 16) & 0xff;
		Utils.Key_Callback_state.State = KeyPress;
		if (LOWORD(lParam) > 0)
			Utils.Key_Callback_state.State = KeyRepeat;
		for (size_t i = 0; i < Utils.Category.Key_InputSize; i++)
			Run_ExternalFunction(Utils.Category.Key_Input[i]);
		return 0;
	case WM_KEYUP:
		Utils.Key_Callback_state.pWindow = pWindow;
		WindowsKeyCode_To_TriangleEngine(pWindow, KeyRelease, wParam);
		Utils.Key_Callback_state.KeyCode = Utils.Key_Callback_state.KeyCode;
		Utils.Key_Callback_state.ScanCode = (lParam >> 16) & 0xff;
		Utils.Key_Callback_state.State = KeyRelease;
		for (size_t i = 0; i < Utils.Category.Key_InputSize; i++)
			Run_ExternalFunction(Utils.Category.Key_Input[i]);
		return 0;
	case WM_CHAR:
	case WM_SYSCHAR:
		if (wParam >= 0xd800 && wParam <= 0xdbff)
			pWindow->OpSys.win32.highSurrogate = (WCHAR)wParam;
		else
		{
			unsigned int codepoint = 0;
			if (wParam >= 0xdc00 && wParam <= 0xdfff)
			{
				if (pWindow->OpSys.win32.highSurrogate)
				{
					codepoint += (pWindow->OpSys.win32.highSurrogate - 0xd800) << 10;
					codepoint += (WCHAR)wParam - 0xdc00;
					codepoint += 0x10000;
				}
			}
			else
				codepoint = (WCHAR)wParam;

			pWindow->OpSys.win32.highSurrogate = 0;

			Utils.Character_Callback_state.pWindow = pWindow;
			Utils.Character_Callback_state.CodePoint = codepoint;
			for (size_t i = 0; i < Utils.Category.Character_InputSize; i++)
				Run_ExternalFunction(Utils.Category.Character_Input[i]);
		}
		//if (uMsg == WM_SYSCHAR && window->win32.keymenu)
		//	break;
		return 0;
	case WM_UNICHAR:
	{
		if (wParam == UNICODE_NOCHAR)
		{
			// WM_UNICHAR is not sent by Windows, but is sent by some
			// third-party input method engine
			// Returning TRUE here announces support for this message
			return TRUE;
		}

		Utils.Character_Callback_state.pWindow = pWindow;
		Utils.Character_Callback_state.CodePoint = wParam;
		for (size_t i = 0; i < Utils.Category.Character_InputSize; i++)
			Run_ExternalFunction(Utils.Category.Character_Input[i]);
		return 0;
	}
	case WM_MOUSEHOVER:
		Utils.MouseEnter_Callback_state.pWindow = pWindow;
		Utils.MouseEnter_Callback_state.Entered = true;
		for (size_t i = 0; i < Utils.Category.MouseEnter_InputSize; i++)
			Run_ExternalFunction(Utils.Category.MouseEnter_Input[i]);
		return 0;
	case WM_MOUSELEAVE:
		Utils.MouseEnter_Callback_state.pWindow = pWindow;
		Utils.MouseEnter_Callback_state.Entered = false;
		for (size_t i = 0; i < Utils.Category.MouseEnter_InputSize; i++)
			Run_ExternalFunction(Utils.Category.MouseEnter_Input[i]);
		return 0;
	case WM_MOUSEMOVE:
		Utils.MousePos_Callback_state.pWindow = pWindow;	
		Utils.MousePos_Callback_state.X_Position = ((uint32_t)GET_X_LPARAM(lParam));
		Utils.MousePos_Callback_state.Y_Position = ((uint32_t)GET_Y_LPARAM(lParam));
		for (size_t i = 0; i < Utils.Category.MousePos_InputSize; i++)
			Run_ExternalFunction(Utils.Category.MousePos_Input[i]);
		return 0;
	case WM_MOUSEWHEEL:
		Utils.Scroll_Callback_state.pWindow = pWindow;
		Utils.Scroll_Callback_state.Delta = ((double)(short)HIWORD(wParam)) / WHEEL_DELTA;
		Utils.Scroll_Callback_state.X_Offset = LOWORD(lParam);
		Utils.Scroll_Callback_state.Y_Offset = HIWORD(lParam);
		for (size_t i = 0; i < Utils.Category.Scroll_InputSize; i++)
			Run_ExternalFunction(Utils.Category.Scroll_Input[i]);
		return 0;
	case WM_SHOWWINDOW:
		Utils.Window_Refresh_Callback_state.pWindow = pWindow;
		for (size_t i = 0; i < Utils.Category.Window_RefreshSize; i++)
			Run_ExternalFunction(Utils.Category.Window_Refresh[i]);
		return 0;
	case WM_LBUTTONDOWN:
		Utils.MouseButton_Callback_state.pWindow = pWindow;
		Utils.MouseButton_Callback_state.Button = MOUSE_BUTTON_1;
		pWindow->STATE_MOUSE_BUTTON_1 = KeyPress;
		Utils.MouseButton_Callback_state.State = KeyPress;
		for (size_t i = 0; i < Utils.Category.MouseButton_InputSize; i++)
			Run_ExternalFunction(Utils.Category.MouseButton_Input[i]);
		return 0;
	case WM_LBUTTONUP:
		Utils.MouseButton_Callback_state.pWindow = pWindow;
		Utils.MouseButton_Callback_state.Button = MOUSE_BUTTON_1;
		pWindow->STATE_MOUSE_BUTTON_1 = KeyRelease;
		Utils.MouseButton_Callback_state.State = KeyRelease;
		for (size_t i = 0; i < Utils.Category.MouseButton_InputSize; i++)
			Run_ExternalFunction(Utils.Category.MouseButton_Input[i]);
		return 0;
	case WM_MBUTTONDOWN:
		Utils.MouseButton_Callback_state.pWindow = pWindow;
		Utils.MouseButton_Callback_state.Button = MOUSE_BUTTON_2;
		pWindow->STATE_MOUSE_BUTTON_2 = KeyPress;
		Utils.MouseButton_Callback_state.State = KeyPress;
		for (size_t i = 0; i < Utils.Category.MouseButton_InputSize; i++)
			Run_ExternalFunction(Utils.Category.MouseButton_Input[i]);
		return 0;
	case WM_MBUTTONUP:
		Utils.MouseButton_Callback_state.pWindow = pWindow;
		Utils.MouseButton_Callback_state.Button = MOUSE_BUTTON_2;
		pWindow->STATE_MOUSE_BUTTON_2 = KeyRelease;
		Utils.MouseButton_Callback_state.State = KeyRelease;
		for (size_t i = 0; i < Utils.Category.MouseButton_InputSize; i++)
			Run_ExternalFunction(Utils.Category.MouseButton_Input[i]);
		return 0;
	case WM_RBUTTONDOWN:
		Utils.MouseButton_Callback_state.pWindow = pWindow;
		Utils.MouseButton_Callback_state.Button = MOUSE_BUTTON_3;
		pWindow->STATE_MOUSE_BUTTON_3 = KeyPress;
		Utils.MouseButton_Callback_state.State = KeyPress;
		for (size_t i = 0; i < Utils.Category.MouseButton_InputSize; i++)
			Run_ExternalFunction(Utils.Category.MouseButton_Input[i]);
		return 0;
	case WM_RBUTTONUP:
		Utils.MouseButton_Callback_state.pWindow = pWindow;
		Utils.MouseButton_Callback_state.Button = MOUSE_BUTTON_3;
		pWindow->STATE_MOUSE_BUTTON_3 = KeyRelease;
		Utils.MouseButton_Callback_state.State = KeyRelease;
		for (size_t i = 0; i < Utils.Category.MouseButton_InputSize; i++)
			Run_ExternalFunction(Utils.Category.MouseButton_Input[i]);
		return 0;
	case WM_XBUTTONDOWN:
		Utils.MouseButton_Callback_state.pWindow = pWindow;
		switch (HIWORD(wParam))
		{
		case XBUTTON1:
			Utils.MouseButton_Callback_state.Button = MOUSE_BUTTON_4;
			pWindow->STATE_MOUSE_BUTTON_4 = KeyPress;
			break;
		case XBUTTON2:
			Utils.MouseButton_Callback_state.Button = MOUSE_BUTTON_5;
			pWindow->STATE_MOUSE_BUTTON_5 = KeyPress;
			break;
		}
		Utils.MouseButton_Callback_state.State = KeyPress;
		for (size_t i = 0; i < Utils.Category.MouseButton_InputSize; i++)
			Run_ExternalFunction(Utils.Category.MouseButton_Input[i]);
		return true;
	case WM_XBUTTONUP:
		Utils.MouseButton_Callback_state.pWindow = pWindow;
		switch (HIWORD(wParam))
		{
		case XBUTTON1:
			Utils.MouseButton_Callback_state.Button = MOUSE_BUTTON_4;
			pWindow->STATE_MOUSE_BUTTON_4 = KeyRelease;
			break;
		case XBUTTON2:
			Utils.MouseButton_Callback_state.Button = MOUSE_BUTTON_5;
			pWindow->STATE_MOUSE_BUTTON_5 = KeyRelease;
			break;
		}
		Utils.MouseButton_Callback_state.State = KeyRelease;
		for (size_t i = 0; i < Utils.Category.MouseButton_InputSize; i++)
			Run_ExternalFunction(Utils.Category.MouseButton_Input[i]);
		return true;
	case WM_DROPFILES:
		
		if (Utils.Drop_Callback_state.Paths != NULL)
			free(Utils.Drop_Callback_state.Paths);

		Utils.Drop_Callback_state.PathsSize = DragQueryFile(wParam, UINT32_MAX, NULL, NULL);
		Utils.Drop_Callback_state.Paths = calloc(Utils.Drop_Callback_state.PathsSize, sizeof(*Utils.Drop_Callback_state.Paths));
		for (size_t i = 0; i < Utils.Drop_Callback_state.PathsSize; i++)
		{
			uint64_t reqsize = DragQueryFile(wParam, i, NULL, NULL) + 1;
			LPWSTR lpwstr = malloc(sizeof(LPWSTR) * reqsize);
			DragQueryFile(wParam, i, lpwstr, reqsize);
			
			uint32_t MultibyteSize = WideCharToMultiByte(CP_UTF8, 0, lpwstr, -1, Utils.Drop_Callback_state.Paths[i], NULL, NULL, NULL);
			Utils.Drop_Callback_state.Paths[i] = (UTF8*)malloc(MultibyteSize);
			WideCharToMultiByte(CP_UTF8, 0, lpwstr, -1, Utils.Drop_Callback_state.Paths[i], MultibyteSize, NULL, NULL);
			//OutputDebugStringA(Utils.Drop_Callback_state.Paths[i]);
		}
		DragFinish(wParam);

		Utils.Drop_Callback_state.pWindow = pWindow;
		for (size_t i = 0; i < Utils.Category.Drop_InputSize; i++)
			Run_ExternalFunction(Utils.Category.Drop_Input[i]);
		return 0;
	case WM_GETMINMAXINFO:
		if (pWindow != NULL)
		{
			if (pWindow->FullScreen == true)
			{
				//OutputDebugStringA("MESSSAGE RECIEVED\n");
				//SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 1920, 1080, 0);
			}
		}
		return 0;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	/*
	static void Joystick_callback(int joystick, int action)
	{
		Utils.Joystick_Connect_Callback_state.Joystick = (Joystick)joystick;
		Utils.Joystick_Connect_Callback_state.Action = (ConnectionEvent)action;
		for (size_t i = 0; i < Utils.Category.Joystick_ConnectSize; i++)
			Run_ExternalFunction(Utils.Category.Joystick_Connect[i]);
	}

	static void Monitor_callback(GLFWmonitor * monitor, int action)
	{
		Utils.Monitor_Connect_Callback_state.pMonitor = monitor;
		Utils.Monitor_Connect_Callback_state.Action = (ConnectionEvent)action;
		for (size_t i = 0; i < Utils.Category.Monitor_ConnectSize; i++)
			Run_ExternalFunction(Utils.Category.Monitor_Connect[i]);
	}*/
}
#endif

//////////////////////////////////////////
//Window Functions
//////////////////////////////////////////

/*
* Added in 1.0.0
* Creates a window in the OS.
* @param Height/Width Desired value in pixels.
* @param Name will be displayed on window
*/
TEXRESULT Create_Window(Window** ppWindow, uint32_t Width, uint32_t Height, const UTF8* Name)
{
#ifndef NDEBUG
	if (ppWindow == NULL)
	{
		ArgsError("Create_Window()", "ppWindow == NULL");
		return Invalid_Parameter | Failure;
	}
#endif
	Lock_Mutex(Utils.WindowsMutex);
	Resize_Array((void**)&Utils.pWindows, Utils.pWindowsSize, Utils.pWindowsSize + 1, sizeof(*Utils.pWindows));
	Utils.pWindows[Utils.pWindowsSize] = (Window*)calloc(1, sizeof(Window));
	Window* pWindow = Utils.pWindows[Utils.pWindowsSize];
	Utils.pWindowsSize += 1;
	Unlock_Mutex(Utils.WindowsMutex);
#ifdef _WIN32
	/*
	HICON hIcon3;      // icon handle 

// Yang icon AND bitmask 

	BYTE ANDmaskIcon[] = { 0xFF, 0xFF, 0xFF, 0xFF,   // line 1 
						  0xFF, 0xFF, 0xC3, 0xFF,   // line 2 
						  0xFF, 0xFF, 0x00, 0xFF,   // line 3 
						  0xFF, 0xFE, 0x00, 0x7F,   // line 4 

						  0xFF, 0xFC, 0x00, 0x1F,   // line 5 
						  0xFF, 0xF8, 0x00, 0x0F,   // line 6 
						  0xFF, 0xF8, 0x00, 0x0F,   // line 7 
						  0xFF, 0xF0, 0x00, 0x07,   // line 8 

						  0xFF, 0xF0, 0x00, 0x03,   // line 9 
						  0xFF, 0xE0, 0x00, 0x03,   // line 10 
						  0xFF, 0xE0, 0x00, 0x01,   // line 11 
						  0xFF, 0xE0, 0x00, 0x01,   // line 12 

						  0xFF, 0xF0, 0x00, 0x01,   // line 13 
						  0xFF, 0xF0, 0x00, 0x00,   // line 14 
						  0xFF, 0xF8, 0x00, 0x00,   // line 15 
						  0xFF, 0xFC, 0x00, 0x00,   // line 16 

						  0xFF, 0xFF, 0x00, 0x00,   // line 17 
						  0xFF, 0xFF, 0x80, 0x00,   // line 18 
						  0xFF, 0xFF, 0xE0, 0x00,   // line 19 
						  0xFF, 0xFF, 0xE0, 0x01,   // line 20 

						  0xFF, 0xFF, 0xF0, 0x01,   // line 21 
						  0xFF, 0xFF, 0xF0, 0x01,   // line 22 
						  0xFF, 0xFF, 0xF0, 0x03,   // line 23 
						  0xFF, 0xFF, 0xE0, 0x03,   // line 24 

						  0xFF, 0xFF, 0xE0, 0x07,   // line 25 
						  0xFF, 0xFF, 0xC0, 0x0F,   // line 26 
						  0xFF, 0xFF, 0xC0, 0x0F,   // line 27 
						  0xFF, 0xFF, 0x80, 0x1F,   // line 28 

						  0xFF, 0xFF, 0x00, 0x7F,   // line 29 
						  0xFF, 0xFC, 0x00, 0xFF,   // line 30 
						  0xFF, 0xF8, 0x03, 0xFF,   // line 31 
						  0xFF, 0xFC, 0x3F, 0xFF };  // line 32 

	// Yang icon XOR bitmask 

	BYTE XORmaskIcon[] = { 0x00, 0x00, 0x00, 0x00,   // line 1 
						  0x00, 0x00, 0x00, 0x00,   // line 2 
						  0x00, 0x00, 0x00, 0x00,   // line 3 
						  0x00, 0x00, 0x00, 0x00,   // line 4 

						  0x00, 0x00, 0x00, 0x00,   // line 5 
						  0x00, 0x00, 0x00, 0x00,   // line 6 
						  0x00, 0x00, 0x00, 0x00,   // line 7 
						  0x00, 0x00, 0x38, 0x00,   // line 8 

						  0x00, 0x00, 0x7C, 0x00,   // line 9 
						  0x00, 0x00, 0x7C, 0x00,   // line 10 
						  0x00, 0x00, 0x7C, 0x00,   // line 11 
						  0x00, 0x00, 0x38, 0x00,   // line 12 

						  0x00, 0x00, 0x00, 0x00,   // line 13 
						  0x00, 0x00, 0x00, 0x00,   // line 14 
						  0x00, 0x00, 0x00, 0x00,   // line 15 
						  0x00, 0x00, 0x00, 0x00,   // line 16 

						  0x00, 0x00, 0x00, 0x00,   // line 17 
						  0x00, 0x00, 0x00, 0x00,   // line 18 
						  0x00, 0x00, 0x00, 0x00,   // line 19 
						  0x00, 0x00, 0x00, 0x00,   // line 20 

						  0x00, 0x00, 0x00, 0x00,   // line 21 
						  0x00, 0x00, 0x00, 0x00,   // line 22 
						  0x00, 0x00, 0x00, 0x00,   // line 23 
						  0x00, 0x00, 0x00, 0x00,   // line 24 

						  0x00, 0x00, 0x00, 0x00,   // line 25 
						  0x00, 0x00, 0x00, 0x00,   // line 26 
						  0x00, 0x00, 0x00, 0x00,   // line 27 
						  0x00, 0x00, 0x00, 0x00,   // line 28 

						  0x00, 0x00, 0x00, 0x00,   // line 29 
						  0x00, 0x00, 0x00, 0x00,   // line 30 
						  0x00, 0x00, 0x00, 0x00,   // line 31 
						  0x00, 0x00, 0x00, 0x00 };  // line 32 

	hIcon3 = CreateIcon(Utils.Instance,    // application instance  
		32,              // icon width 
		32,              // icon height 
		1,               // number of XOR planes 
		1,               // number of bits per pixel 
		ANDmaskIcon,     // AND bitmask  
		XORmaskIcon);    // XOR bitmask 
	*/

	LPWSTR Name1 = NULL;
	uint32_t Name1Size = MultiByteToWideChar(CP_UTF8, 0, Name, -1, Name1, 0);
	Name1 = (WCHAR*)malloc(sizeof(WCHAR) * Name1Size);
	MultiByteToWideChar(CP_UTF8, 0, Name, -1, Name1, Name1Size);

	WNDCLASS wc;
	memset(&wc, 0, sizeof(WNDCLASS));
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = Utils.win32.Instance;
	wc.lpszClassName = Name1;
	RegisterClass(&wc);


	pWindow->Window = CreateWindowEx(
		0,                              // Optional window styles.
		Name1,							// Window class
		Name1,							// Window text
		WS_OVERLAPPEDWINDOW,            // Window style
		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT,
		Width, Height,
		NULL,       // Parent window    
		NULL,       // Menu
		Utils.win32.Instance,  // Instance handle
		NULL        // Additional application data
	);
	free((void*)Name1);
	if (!pWindow->Window)
	{
		return Failure;
	}

	DragAcceptFiles(pWindow->Window, true);
	ShowWindow(pWindow->Window, 1);
#endif
	*ppWindow = pWindow;

	Utils.Window_Open_Callback_state.pWindow = pWindow->Window;
	for (size_t i = 0; i < Utils.Category.Window_OpenSize; i++)
	{
		Run_ExternalFunction(Utils.Category.Window_Open[i]);
	}
	return Success;
}
/*
* Added in 1.0.0
* Destroys specified window.
* @param pWindow Pointer to a window created with Create_Window().
* @param Name is the same Name of the window when created with Create_Window().
*/
TEXRESULT Destroy_Window(Window* pWindow, const UTF8* Name)
{
#ifndef NDEBUG
	if (pWindow == NULL)
	{
		ArgsError("Destroy_Window()", "pWindow == NULLPTR");
		return Invalid_Parameter | Failure;
	}
#endif
	Lock_Mutex(Utils.WindowsMutex);
	for (size_t i = 0; i < Utils.pWindowsSize; i++)
	{
		if (Utils.pWindows[i] == pWindow)
		{
#ifdef _WIN32
			DestroyWindow(Utils.pWindows[i]->Window);
			LPWSTR Name1 = NULL;
			uint32_t Name1Size = MultiByteToWideChar(CP_UTF8, 0, Name, -1, Name1, 0);
			Name1 = (WCHAR*)malloc(sizeof(WCHAR) * Name1Size);
			MultiByteToWideChar(CP_UTF8, 0, Name, -1, Name1, Name1Size);

			UnregisterClass(Name1, Utils.win32.Instance);
			free((void*)Name1);
#endif
			free(Utils.pWindows[i]);
			RemoveMember_Array((void**)&Utils.pWindows, Utils.pWindowsSize, i, sizeof(*Utils.pWindows), 1);
			Utils.pWindowsSize -= 1;
			return Success;
		}
	}
	Unlock_Mutex(Utils.WindowsMutex);
	FunctionError("Destroy_Window()", "Window Not Found, Window == ", pWindow);
	return Invalid_Parameter | Failure;
}
/*
* Added in 1.0.0
* @param pWindow Pointer to a window created with Create_Window()
* @param FullScreen is bool true == fullscreen false = windowed.
*/
TEXRESULT Set_WindowFullScreen(Window* pWindow, bool FullScreen)
{
	pWindow->FullScreen = FullScreen;
#ifdef _WIN32
	DWORD dwStyle = GetWindowLong(pWindow->Window, GWL_STYLE);
	if (pWindow->FullScreen == true)
	{
		MONITORINFO mi = { sizeof(mi) };
		if (GetWindowPlacement(pWindow->Window, &pWindow->OpSys.win32.WindowPreviousPlacement) && GetMonitorInfo(MonitorFromWindow(pWindow->Window, MONITOR_DEFAULTTOPRIMARY), &mi)) {
			SetWindowLong(pWindow->Window, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
			SetWindowPos(pWindow->Window, HWND_TOP,
				mi.rcMonitor.left, mi.rcMonitor.top,
				mi.rcMonitor.right - mi.rcMonitor.left,
				mi.rcMonitor.bottom - mi.rcMonitor.top,
				SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
		}
	}
	else
	{
		SetWindowLong(pWindow->Window, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(pWindow->Window, &pWindow->OpSys.win32.WindowPreviousPlacement);
		SetWindowPos(pWindow->Window, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
	}
#endif
}
/*
* Added in 1.0.0
* @param pWindow Pointer to a window created with Create_Window().
* @param pData pointer where data will be stored, if NULL pDataSize will be set to the required size.
* @param pDataSize will be set to the required size in bytes plus null terminator.
*/
TEXRESULT Read_ClipboardUTF8(Window* pWindow, UTF8* pData, uint64_t* pDataSize)
{
#ifdef _WIN32
	if (OpenClipboard(pWindow->Window) == 0){
		FunctionError("Read_Clipboard()", "OpenClipboard() Failed, Result == ", GetLastError());
		return (TEXRESULT)(Failure);
	}

	HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
	if (hClipboardData == NULL){
		CloseClipboard();
		FunctionError("Read_Clipboard()", "GetClipboardData() Failed, Result == ", GetLastError());
		return (TEXRESULT)(Failure);
	}

	LPWSTR string = GlobalLock(hClipboardData);
	if (string != NULL)
	{
		*pDataSize = WideCharToMultiByte(CP_UTF8, 0, string, -1, NULL, NULL, NULL, NULL);
		if (pData != NULL)
		{
			WideCharToMultiByte(CP_UTF8, 0, string, -1, pData, *pDataSize, NULL, NULL);
			pData[(*pDataSize) - 1] = '\0';
		}
	}
	GlobalUnlock(hClipboardData);


	if (CloseClipboard() == 0) {
		FunctionError("Read_Clipboard()", "CloseClipboard() Failed, Result == ", GetLastError());
		return (TEXRESULT)(Failure);
	}
#endif
}
/*
* Added in 1.0.0
* @param pWindow Pointer to a window created with Create_Window().
* @param pData is null terminated UTF8 string.
*/
TEXRESULT Write_ClipboardUTF8(Window* pWindow, UTF8* pData)
{
#ifdef _WIN32
	if (OpenClipboard(pWindow->Window) == 0){
		FunctionError("Write_Clipboard()", "OpenClipboard Failed, Result == ", GetLastError());
		return (TEXRESULT)(Failure);
	}
	if (EmptyClipboard(pWindow->Window) == 0) {
		CloseClipboard();
		FunctionError("Write_Clipboard()", "EmptyClipboard Failed, Result == ", GetLastError());
		return (TEXRESULT)(Failure);
	}

	LPWSTR string = NULL;
	uint32_t size = MultiByteToWideChar(CP_UTF8, 0, pData, -1, string, 0);

	HANDLE hglb = GlobalAlloc(GMEM_MOVEABLE, sizeof(WCHAR) * size);
	if (hglb == NULL){
		CloseClipboard();
		FunctionError("Write_Clipboard()", "GlobalAlloc Failed, Result == ", GetLastError());
		return (TEXRESULT)(Failure);
	}

	string = GlobalLock(hglb);
	MultiByteToWideChar(CP_UTF8, 0, pData, -1, string, size);
	GlobalUnlock(hglb);


	HANDLE hClipboardData = SetClipboardData(CF_UNICODETEXT, hglb);
	if (hClipboardData == NULL) {
		CloseClipboard();
		FunctionError("Write_Clipboard()", "GetClipboardData() Failed, Result == ", GetLastError());
		return (TEXRESULT)(Failure);
	}

	if (CloseClipboard() == 0) {
		FunctionError("Write_Clipboard()", "CloseClipboard Failed, Result == ", GetLastError());
		return (TEXRESULT)(Failure);
	}
#endif
}
/*
* Added in 1.0.0
* @param pWindow Pointer to a window created with Create_Window().
* @param ppMonitor is a pointer to the resulting native monitor handle.
*/
TEXRESULT Get_PrimaryMonitor(Window* pWindow, Monitor** ppMonitor)
{
#ifndef NDEBUG
	if (ppMonitor == NULL)
	{
		ArgsError("Get_Monitor()", "ppMonitor == NULLPTR");
		return Invalid_Parameter | Failure;
	}
#endif
	
#ifdef _WIN32
	*ppMonitor = MonitorFromWindow(pWindow->Window, MONITOR_DEFAULTTOPRIMARY);
#endif
	return Success;
}
/*
* Added in 1.0.0
* Returns all the videomodes of a monitor.
* @param pMonitor is a native monitor handle to return the video modes of.
* @param pMonitorInfo is the monitor info thats returned.
*/
TEXRESULT Get_MonitorInfo(MonitorInfo* pMonitorInfo, Monitor* pMonitor)
{
#ifndef NDEBUG
	if (pMonitor == NULL)
	{
		ArgsError("Get_MonitorInfo()", "pMonitor == NULLPTR");
		return Invalid_Parameter | Failure;
	}
	if (pMonitorInfo == NULL)
	{
		ArgsError("Get_MonitorInfo()", "pMonitorInfo == NULLPTR");
		return Invalid_Parameter | Failure;
	}
#endif
#ifdef _WIN32

	MONITORINFO info;
	memset(&info, 0, sizeof(info));
	info.cbSize = sizeof(info);
	GetMonitorInfo(pMonitor, &info);


	/*GetDpiForWindow();
	int size = 0;
	GLFWvidmode* vidmodes = (GLFWvidmode*)glfwGetVideoModes((GLFWmonitor*)pMonitor, &size);
	*pSize = size;

	int widthmm = 0;
	int heightmm = 0;
	glfwGetMonitorPhysicalSize((GLFWmonitor*)pMonitor, &widthmm, &heightmm);

	int xpos = 0;
	int ypos = 0;
	glfwGetMonitorPos((GLFWmonitor*)pMonitor, &xpos, &ypos);

	GLFWvidmode* activevidmode = (GLFWvidmode*)glfwGetVideoMode((GLFWmonitor*)pMonitor);


	MonitorVideoMode* MonitorVideoModes = (MonitorVideoMode*)calloc(size, sizeof(MonitorVideoMode));
	
	for (size_t i = 0; i < size; i++)
	{
		MonitorVideoModes[i].Height = vidmodes[i].height;
		MonitorVideoModes[i].Width = vidmodes[i].width;

		MonitorVideoModes[i].RedBits = vidmodes[i].redBits;
		MonitorVideoModes[i].GreenBits = vidmodes[i].greenBits;
		MonitorVideoModes[i].BlueBits = vidmodes[i].blueBits;

		MonitorVideoModes[i].RefreshRate = vidmodes[i].refreshRate;

		MonitorVideoModes[i].WidthMM = widthmm;
		MonitorVideoModes[i].HeightMM = heightmm;

		MonitorVideoModes[i].Xpos = xpos;
		MonitorVideoModes[i].Ypos = ypos;



		if (activevidmode->height == vidmodes[i].height &&
			activevidmode->width == vidmodes[i].width &&
			activevidmode->redBits == vidmodes[i].redBits &&
			activevidmode->greenBits == vidmodes[i].greenBits &&
			activevidmode->blueBits == vidmodes[i].blueBits &&
			activevidmode->refreshRate == vidmodes[i].refreshRate)
		{
			*pActiveMonitorVideoModeIndex = i;
		}
	}

	*pMonitorVideoModes = MonitorVideoModes;*/
#endif
	return Success;
}

//////////////////////////////////////////
//Control Functions
//////////////////////////////////////////

/*
* Added in 1.0.0
* Closes the game engine.
*/
void Exit_Application()
{
	Utils.ApplicationClose = true;
}
/*
* Added in 1.0.0
* Applies specified array of values to specified config parameters.
* ConfigParameterName is a symbol used to find the specified config parameter.
* pConfigParameterToApply is a pointer to the data to be applied.
* ElementsCount is how many array elements to apply to. Must not exceed the ConfigParameterInfo.ArrayElements,
  If ElementsCount == NULL pConfigParameterToApply is assumed to be null terminated and the size will be gauged this way.
* ElementArrayIndex is the index in the array where pConfigParameterToApply will start to be copied to.
  ElementsCount + ElementArrayIndex Must not exceed ConfigParameterInfo.ArrayElements.
* sizeof each element is specified in ConfigParameterInfo.ByteLength
*/
void Apply_Config(const UTF8* ConfigParameterName, void* pConfigParameterToApply, uint64_t ArrayElementsCount, uint64_t ElementArrayIndex)
{
	for (size_t i1 = 0; i1 < Utils.ExtensionBuffer.Max;)
	{
		ExtensionData* pExtensionData = (ExtensionData*)&Utils.ExtensionBuffer.Buffer[i1];
		if (pExtensionData->AllocationSize != NULL)
		{
			for (size_t i2 = 0; i2 < pExtensionData->ConfigParametersSize; i2++)
			{
				if (strcmp(ConfigParameterName, pExtensionData->ConfigParameters[i2].Name) == 0)
				{
					if (ArrayElementsCount != NULL)
					{
						memcpy((void*)((uint64_t)pExtensionData->ConfigParameters[i2].pParameter + (uint64_t)(ElementArrayIndex * pExtensionData->ConfigParameters[i2].ByteLength)),
							pConfigParameterToApply, ArrayElementsCount * pExtensionData->ConfigParameters[i2].ByteLength);
					}
					else
					{
						memcpy((void*)((uint64_t)pExtensionData->ConfigParameters[i2].pParameter + (uint64_t)(ElementArrayIndex * pExtensionData->ConfigParameters[i2].ByteLength)),
							pConfigParameterToApply, strlen(pConfigParameterToApply) * pExtensionData->ConfigParameters[i2].ByteLength);
					}
				}
			}
			i1 += pExtensionData->AllocationSize;
		}
		else
		{
			i1++;
		}
	}
}

//////////////////////////////////////////
//Main Functions
//////////////////////////////////////////

#ifdef _WIN32
HINSTANCE ghInstance = NULL;
HINSTANCE ghPrevInstance = NULL;
PWSTR gpCmdLine = NULL;
int gnCmdShow = NULL;
#endif

TEXRESULT Initialize()
{
	////////////////////////////////////////////////////////////////////////////////////////
	//Reseting
	////////////////////////////////////////////////////////////////////////////////////////
	memset(&Config, NULL, sizeof(Config));
	memset(&Utils, NULL, sizeof(Utils));

	//stupid endian test
	unsigned int x = 0x76543210;
	char* c = (char*)&x;
	if (!(*c == 0x10)) //big endian, unsupported.
		return 1;
#ifdef _WIN32
	Utils.win32.Instance = ghInstance;
	Utils.win32.PrevInstance = ghPrevInstance;
	Utils.win32.CommandShow = gnCmdShow;
	if (gpCmdLine != NULL)
	{
		LPSTR Multibyte = NULL;
		uint32_t MultibyteSize = WideCharToMultiByte(CP_UTF8, 0, gpCmdLine, -1, Multibyte, NULL, NULL, NULL);
		Multibyte = (LPSTR*)malloc(sizeof(LPSTR) * MultibyteSize);
		WideCharToMultiByte(CP_UTF8, 0, gpCmdLine, -1, Multibyte, MultibyteSize, NULL, NULL);
		Utils.win32.CommandLine = Multibyte;
	}
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	Utils.CPU.MaxThreads = sysinfo.dwNumberOfProcessors;
#else
	cpu_set_t cpuset;
	sched_getaffinity(0, sizeof(cpuset), &cpuset);
	Utils.CPU.MaxThreads = CPU_COUNT(&cpuset);
#endif


	Config.InitialExtensionMax = 1024;

	Create_Mutex(Utils.WindowsMutex, MutexType_Plain);

	Create_ExtensionDataBuffer(Config.InitialExtensionMax);

	Create_ExtensionData(&Utils.EngineExtension, NULL);

	ExtensionData* pEngineExtension = Get_ExtensionDataPointer(Utils.EngineExtension);

	ConfigParameterExport(&pEngineExtension->ConfigParameters, &pEngineExtension->ConfigParametersSize, (const UTF8*)CopyData("Engine::InitialExtensionMax"), &Config.InitialExtensionMax, 1, sizeof(Config.InitialExtensionMax));

	//resources
	ResourceExport(&pEngineExtension->pResources, &pEngineExtension->pResourcesSize, (const UTF8*)CopyData("Engine::Utils"), &EngineRes.pUtils, &Utils);

	//FUNCTIONS
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Resize_ExtensionDataBuffer"), &EngineRes.pResize_ExtensionDataBuffer, &Resize_ExtensionDataBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Get_ExtensionDataPointer"), &EngineRes.pGet_ExtensionDataPointer, &Get_ExtensionDataPointer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Create_ExtensionData"), &EngineRes.pCreate_ExtensionData, &Create_ExtensionData, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Destroy_ExtensionData"), &EngineRes.pDestroy_ExtensionData, &Destroy_ExtensionData, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Resolve_Linkages"), &EngineRes.pResolve_Linkages, &Resolve_Linkages, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Recreate_Categories"), &EngineRes.pRecreate_Categories, &Recreate_Categories, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Resolve_FunctionSymbol"), &EngineRes.pResolve_FunctionSymbol, &Resolve_FunctionSymbol, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Resolve_ResourceSymbol"), &EngineRes.pResolve_ResourceSymbol, &Resolve_ResourceSymbol, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Create_Window"), &EngineRes.pCreate_Window, &Create_Window, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Destroy_Window"), &EngineRes.pDestroy_Window, &Destroy_Window, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Set_WindowFullScreen"), &EngineRes.pSet_WindowFullScreen, &Set_WindowFullScreen, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Read_ClipboardUTF8"), &EngineRes.pRead_ClipboardUTF8, &Read_ClipboardUTF8, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Write_ClipboardUTF8"), &EngineRes.pWrite_ClipboardUTF8, &Write_ClipboardUTF8, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Get_PrimaryMonitor"), &EngineRes.pGet_PrimaryMonitor, &Get_PrimaryMonitor, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Get_MonitorInfo"), &EngineRes.pGet_MonitorInfo, &Get_MonitorInfo, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Exit_Application"), &EngineRes.pExit_Application, &Exit_Application, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Apply_Config"), &EngineRes.pApply_Config, &Apply_Config, (CallFlagBits)NULL, 0.0f, NULL, NULL);


	//Threading
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Create_Mutex"), &EngineRes.pCreate_Mutex, &Create_Mutex, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Destroy_Mutex"), &EngineRes.pDestroy_Mutex, &Destroy_Mutex, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Lock_Mutex"), &EngineRes.pLock_Mutex, &Lock_Mutex, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::TimedLock_Mutex"), &EngineRes.pTimedLock_Mutex, &TimedLock_Mutex, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::TryLock_Mutex"), &EngineRes.pTryLock_Mutex, &TryLock_Mutex, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Unlock_Mutex"), &EngineRes.pUnlock_Mutex, &Unlock_Mutex, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Create_Condition"), &EngineRes.pCreate_Condition, &Create_Condition, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Destroy_Condition"), &EngineRes.pDestroy_Condition, &Destroy_Condition, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Signal_Condition"), &EngineRes.pSignal_Condition, &Signal_Condition, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Broadcast_Condition"), &EngineRes.pBroadcast_Condition, &Broadcast_Condition, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Wait_Condition"), &EngineRes.pWait_Condition, &Wait_Condition, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::TimedWait_Condition"), &EngineRes.pTimedWait_Condition, &TimedWait_Condition, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Create_Thread"), &EngineRes.pCreate_Thread, &Create_Thread, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Current_Thread"), &EngineRes.pCurrent_Thread, &Current_Thread, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Detach_Thread"), &EngineRes.pDetach_Thread, &Detach_Thread, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::ThreadEqual"), &EngineRes.pThreadEqual, &ThreadEqual, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Exit_Thread"), &EngineRes.pExit_Thread, &Exit_Thread, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Join_Thread"), &EngineRes.pJoin_Thread, &Join_Thread, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Sleep_Thread"), &EngineRes.pSleep_Thread, &Sleep_Thread, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Yield_Thread"), &EngineRes.pYield_Thread, &Yield_Thread, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::Call_Once"), &EngineRes.pCall_Once, &Call_Once, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	//errorcallback
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::ObjectError"), &EngineRes.pObjectError, &ObjectError, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::FunctionError"), &EngineRes.pFunctionError, &FunctionError, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&pEngineExtension->pFunctions, &pEngineExtension->pFunctionsSize, (const UTF8*)CopyData("Engine::ArgsError"), &EngineRes.pArgsError, &ArgsError, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	////////////////////////////////////////////////////////////////////////////////////////
	//Init Extensions
	////////////////////////////////////////////////////////////////////////////////////////
	
	UTF8* CommandLinePointer = Utils.win32.CommandLine;
	while (*CommandLinePointer != '\0')
	{
		uint64_t it = Find_first_of(CommandLinePointer, ",");
	
		UTF8* tempstring = NULL;
		uint64_t tempstringpointer = 0;
		switch (EngineBinType)
		{
		case Debug:
			tempstring = malloc(it + 9 + 1);
			memcpy(tempstring + tempstringpointer, CommandLinePointer, it);
			tempstringpointer += it;
			memcpy(tempstring + tempstringpointer, "Debug.dll", 9);
			tempstringpointer += 9;
			break;
		case Release:
			tempstring = malloc(it + 11 + 1);
			memcpy(tempstring + tempstringpointer, CommandLinePointer, it);
			tempstringpointer += it;
			memcpy(tempstring + tempstringpointer, "Release.dll", 11);
			tempstringpointer += 11;
			break;
		}
		tempstring[tempstringpointer] = '\0';
		tempstringpointer++;
		OutputDebugStringA(tempstring);

		ExtensionDataCreateInfo CreateInfo = { NULL };
		CreateInfo.Name = tempstring;
		ExtensionAllocation Extension = NULL;
		if (Create_ExtensionData(&Extension, &CreateInfo) != Success)
		{
			Destroy_ExtensionData(Extension);
		}
		free((void*)CreateInfo.Name);	
		CommandLinePointer += it + 1;
	}
	//end
	Recreate_Categories();
	Resolve_Linkages();

	for (size_t i = 0; i < Utils.Category.ConstructSize; i++)
	{
		Run_ExternalFunction(Utils.Category.Construct[i]);
	}
	return Success;
}

TEXRESULT Destroy()
{
	for (size_t i = 0; i < Utils.Category.DestructSize; i++)
	{
		Run_ExternalFunction(Utils.Category.Destruct[i]);
	}

	Destroy_ExtensionData(Utils.EngineExtension);

	Destroy_ExtensionDataBuffer(&Utils.ExtensionBuffer);

	free(Utils.Category.ExternalFunctions);
	free(Utils.Category.ExternalResources);

	free(Utils.Category.Construct);
	free(Utils.Category.Destruct);
	free(Utils.Category.EveryFrame);
	free(Utils.Category.Key_Input);
	free(Utils.Category.Character_Input);
	free(Utils.Category.MouseButton_Input);
	free(Utils.Category.MousePos_Input);
	free(Utils.Category.MouseEnter_Input);
	free(Utils.Category.Scroll_Input);
	free(Utils.Category.Joystick_Connect);
	free(Utils.Category.Monitor_Connect);
	free(Utils.Category.Drop_Input);
	free(Utils.Category.Window_Resize);
	free(Utils.Category.FrameBuffer_Resize);
	free(Utils.Category.Window_Refresh);
	free(Utils.Category.Window_Minimise);
	free(Utils.Category.Window_Move);
	free(Utils.Category.Window_Minimise);
	free(Utils.Category.Window_Focused);
	free(Utils.Category.Window_Close);
	free(Utils.Category.Window_Open);

	Utils.pWindows = NULL;
	Utils.pWindowsSize = NULL;

	Destroy_Mutex(Utils.WindowsMutex);

	memset(&Config, NULL, sizeof(Config));
	memset(&Utils, NULL, sizeof(Utils));

	return Success;
}

#ifdef _WIN32
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow){	
	ghInstance = hInstance;
	ghPrevInstance = hPrevInstance;
	gpCmdLine = pCmdLine;
	gnCmdShow = nCmdShow;

	Initialize();
	while (Utils.ApplicationClose == false)
	{
		for (size_t i = 0; i < Utils.pWindowsSize; i++)
		{
			MSG msg;
			for (size_t i1 = 0; i1 < PeekMessage(&msg, Utils.pWindows[i]->Window, 0, 0, 0); i1++)
			{
				GetMessage(&msg, NULL, 0, 0);
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		for (size_t i = 0; i < Utils.Category.EveryFrameSize; i++)
		{
			Run_ExternalFunction(Utils.Category.EveryFrame[i]);
		}
	}
	return Destroy();
}
#endif