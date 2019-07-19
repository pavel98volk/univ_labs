package lockables;



import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;

public class DekkerLock extends lockables.FixnumLock {

    public DekkerLock(int threadNum) {
        super(threadNum);
        flagFirst = false;
        flagSecond = false;
        turn = 0;
    }
    @Override
    @SuppressWarnings("CallToThreadYield")
    public void lock() {
        final long currentThreadId = getId(Thread.currentThread());
        if (currentThreadId == 0) {
            flagFirst = true;
        } else {
            flagSecond = true;
        }

        if (currentThreadId == 0) {
            while (flagSecond == true) {
                if (turn == 1 - currentThreadId) {
                    flagFirst = false;
                    while (turn == 1 - currentThreadId) {
                        Thread.yield();
                    }
                    flagFirst = true;
                }
            }
        } else {
            while (flagFirst == true) {
                if (turn == 1 - currentThreadId) {
                    flagSecond = false;
                    while (turn == 1 - currentThreadId) {
                        Thread.yield();
                    }
                    flagSecond = true;
                }
            }
        }
    }

    @Override
    public void unlock() {
        final long currentThreadId = getId(Thread.currentThread());

        turn = 1 - currentThreadId;
        if (currentThreadId == 0) {
            flagFirst = false;
        } else {
            flagSecond = false;
        }
    }

    private volatile boolean flagFirst;
    private volatile boolean flagSecond;
    private volatile long turn;

    @Override
    public void lockInterruptibly() throws InterruptedException {
        throw new UnsupportedOperationException("Not used.");
    }

    @Override
    public boolean tryLock() {
        throw new UnsupportedOperationException("Not used.");
    }

    @Override
    public boolean tryLock(long time, TimeUnit unit) throws InterruptedException {
        throw new UnsupportedOperationException("Not used.");
    }

    @Override
    public Condition newCondition() {
        throw new UnsupportedOperationException("Not used.");
    }

}
