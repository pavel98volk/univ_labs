package lockables;

import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicIntegerArray;
import java.util.concurrent.locks.Condition;

public class BakeryLock extends lockables.FixnumLock {

//    List<Integer> tickets;
//    List<Boolean> entering;

    AtomicIntegerArray tickets;
    AtomicIntegerArray entering;



    //из за того что 4 ядра, планировщик вмешивается в критичеакую и дает другим, а те ждет. 4 и 5

    public BakeryLock(int n) {
        super(n);
//        tickets = new ArrayList<>(threadNum); // ticket for threads in line, n - number of threads
//        entering = new ArrayList<>(threadNum); // True when thread entering in line

        tickets = new AtomicIntegerArray(threadNum);
        entering = new AtomicIntegerArray(threadNum);

        for (int i = 0; i < threadNum; i++) {
            tickets.set(i, 0);
            entering.set(i, 0);
        }
    }

    //На входе в критическую секцию ставить номер потока, вошедшего в эту секцию, при выходе проверять совпадает ли номер, может кто паралельно вошел в критическую секцию +

    //Первоначальный алгоритм Лампорта был сделан для модели памяти с последовательной согласованностью. Сейчас же в модели памяти присутствует reordering.

    // поменять на AtomicIntegerArray(threads); +

    @Override
    public void lockInterruptibly() throws InterruptedException {
        throw new UnsupportedOperationException("Not used.");
    }

    @Override
    public void lock() {
        int pid = getId();
        entering.set(pid, 0);

        int max = 0;
        for (int i = 0; i < threadNum; i++) { max = Math.max(max, tickets.get(i)); }

        tickets.set(pid, 1 + max);
        entering.set(pid, 0);

        for (int i = 0; i < threadNum; ++i) {
            if (i != pid) {
                while (entering.get(i) == 1) {
//                    try {
//                        Thread.sleep(100);
//                    } catch (InterruptedException e) {
//                        e.printStackTrace();
//                    }
                    Thread.yield();
                } // wait while other thread picks a ticket
                while (tickets.get(i) != 0 && ( tickets.get(pid) > tickets.get(i)  ||
                        (tickets.get(pid) == tickets.get(i) && pid > i))) {
//                    try {
//                        Thread.sleep(100);
//                    } catch (InterruptedException e) {
//                        e.printStackTrace();
//                    }
                    Thread.yield();
                }
            }
        }
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
    public void unlock() { tickets.set(getId(), 0); }
    @Override
    public Condition newCondition() {
        throw new UnsupportedOperationException("Not used.");
    }
}
