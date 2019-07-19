package lockables;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.atomic.AtomicReference;
import java.lang.UnsupportedOperationException;

public class SpinLock implements Lock{

    private AtomicReference<Thread> owner = new AtomicReference<Thread>();
    private int count = 0;
    public void lock(){
        Thread currentThread = Thread.currentThread();
        if(currentThread == owner.get()) {
            count++;
            return;
        }
        while(!owner.compareAndSet(null, currentThread)) {
            //spin,spin,spin...
        }
    }
    public boolean tryLock(long a, TimeUnit b){
        Thread currentThread = Thread.currentThread();
        if (currentThread == owner.get()) {
            count++;
            return true;
        }
        long c = System.currentTimeMillis();
        while((b.toMillis(a)+c)>System.currentTimeMillis())
            if (owner.compareAndSet(null, currentThread)) return true;
        return false;
    }
    public boolean tryLock() {
        Thread currentThread = Thread.currentThread();
        if (currentThread == owner.get()) {
            count++;
            return true;
        }
        if (owner.compareAndSet(null, currentThread)) return true;
            return false;
    }
    public void lockInterruptibly()throws InterruptedException{
        //?
    }
    public void unlock(){
        Thread currentThread = Thread.currentThread();
        if (owner.get() == currentThread) {
            if (count != 0) {
                count--;
            } else {
                if(!owner.compareAndSet(currentThread, null)); // then it can be somehow emphasised;
            }
        }
    }
    public Condition newCondition() throws UnsupportedOperationException{
        throw new UnsupportedOperationException("not yet implemented");

    }
}

