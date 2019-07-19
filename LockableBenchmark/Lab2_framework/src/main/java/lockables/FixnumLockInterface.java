package lockables;

import java.util.concurrent.locks.Lock;

public interface FixnumLockInterface extends Lock {
    int getId();

    void register(Thread thread);
    void unregister(Thread thread);

    void lock();
    void unlock();

    void reset();
}
