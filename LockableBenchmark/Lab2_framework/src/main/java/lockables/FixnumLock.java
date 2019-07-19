package lockables;

import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Lock;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.LinkedHashSet;

/**
 * Class that can be used to derive classes for
 * mutual exclusion primitives with limited
 * number of threads
 */
public abstract class FixnumLock implements FixnumLockInterface {

    class OwnershipException extends RuntimeException {
        public OwnershipException() {
            super();
        }
        public OwnershipException(String s) {
            super(s);
        }
    }

    class OutOfThreadsNumException extends RuntimeException {
        public OutOfThreadsNumException() {
            super();
        }
        public OutOfThreadsNumException(String s) {
            super(s);
        }
    }

    private Map<Long, Long> threadIdMap;
    private Set<Long> availableLockIDs;
    private long currentLockId;
    protected final int threadNum;

    public FixnumLock(int threadNum) {
        this.threadNum = threadNum;
        currentLockId = 0;
        threadIdMap = new HashMap<>();
        availableLockIDs = new LinkedHashSet<>();
        for (long i = 0; i < threadNum; i++) {
            availableLockIDs.add(i);
        }
    }

    public long getId(Thread thread) {
        return threadIdMap.get(thread.getId());
    }
    public int getId() {
        return threadIdMap.get(Thread.currentThread().getId()).intValue();
    }

    public boolean isAuthorized(Thread thread) {
        return threadIdMap.containsKey(thread.getId());
    }

    synchronized public void register(Thread thread) throws OutOfThreadsNumException {
        if (!isAuthorized(thread)) {
            if (threadIdMap.size() < threadNum) {
                threadIdMap.put(thread.getId(), currentLockId);
                availableLockIDs.remove(currentLockId);
                if (!availableLockIDs.isEmpty()) {
                    currentLockId = availableLockIDs.iterator().next();
                }
            } else {
                throw new OutOfThreadsNumException("All allowed threads are already registered");
            }
        }
    }

    synchronized public void unregister(Thread thread) {
        if (isAuthorized(thread)) {
            long removed = threadIdMap.remove(thread.getId());
            availableLockIDs.add(removed);
            currentLockId = availableLockIDs.iterator().next();
        }
    }

    synchronized public void reset() {
        threadIdMap.clear();
        for (long i = 0; i < threadNum; i++) {
            availableLockIDs.add(i);
        }
        currentLockId = 0;
    }


    /**
     * If any ancestor want to guarantee that only authorized
     * threads can access critical region, it should call
     * wrappers (described below) for methods in Lock interface
     */

    synchronized public final void checkedLock() {
        if (isAuthorized(Thread.currentThread())) {
            lock();
        } else {
            throw new OwnershipException("Thread is not authorized");
        }
    }

    synchronized public final boolean checkedTryLock() {
        if (isAuthorized(Thread.currentThread())) {
            return tryLock();
        } else {
            throw new OwnershipException("Thread is not authorized");
        }
    }


    synchronized public final void checkedLockInterruptibly() throws InterruptedException {
        if (isAuthorized(Thread.currentThread())) {
            lockInterruptibly();
        } else {
            throw new OwnershipException("Thread is not authorized");
        }
    }


    synchronized public final boolean checkedTryLock(long time, TimeUnit unit) throws InterruptedException {
        if (isAuthorized(Thread.currentThread())) {
            return tryLock(time, unit);
        } else {
            throw new OwnershipException("Thread is not authorized");
        }
    }
}
