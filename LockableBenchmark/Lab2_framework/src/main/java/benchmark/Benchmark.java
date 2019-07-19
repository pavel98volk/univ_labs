package benchmark;

import factories.FixnumLockFactory;
import lockables.*;

import java.util.Vector;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Benchmark {

    public static void main(String[] args) {
        Vector<Lock> locks= new Vector<Lock>();
       // locks.add(new SpinLock());
        locks.add(new SpinLock());
        locks.add(new ReentrantLock());
        Vector<String> names = new Vector<String>();
        names.add("SpinLock");
        names.add("ReentrantLock");
        Vector<FixnumLockFactory> fixnumFactories= new Vector<FixnumLockFactory>();
        fixnumFactories.add(new FixnumLockFactory() {
            @Override
            public FixnumLock getInstance(int n) {
                return new DekkerLock(n);
            }
        });
        fixnumFactories.add(new FixnumLockFactory() {
            @Override
            public FixnumLock getInstance(int n) {
                return new BakeryLock(n);
            }
        });
        fixnumFactories.add(new FixnumLockFactory() {
            @Override
            public FixnumLock getInstance(int n) {
                return new ILamportLock(n);
            }
        });

        Vector<String> fixnumNames = new Vector<String>();
        fixnumNames.add("Dekker Lock");
        fixnumNames.add("Bakery Lock");
        fixnumNames.add("Lamport Lock++");
       System.out.println(SpeedTest.genTextResult(locks,names,fixnumFactories,fixnumNames));
    }
}
