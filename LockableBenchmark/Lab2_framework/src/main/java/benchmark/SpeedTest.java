package benchmark;

import java.util.Vector;
import java.util.concurrent.locks.Lock;
import java.util.function.*;

import factories.FixnumLockFactory;
import general.Reference;
import general.Table;
import lockables.FixnumLock;
import testClasses.TestLockClass;
import testClasses.*;

import java.lang.Thread;


//tip1 first type names of locks and then names of fixnumlocks;
public class SpeedTest {
    public static String genTextResult(Vector<Lock> locks, Vector<String>lockNames,Vector<FixnumLockFactory> fixnumFactories,Vector<String>fixnumNames) {
        String resString = new String();
        resString+="Problems: first lock.lock() is wierdly long,phenomonon can be seen in other places,like last unlock(). also operation changing does not work as desired yet\n";
        try{
            Table<Long> res = genTestTable( locks,lockNames ,fixnumFactories,fixnumNames);
            resString+=String.format("%-30s|","");
            for(String s:res.columnNames)
                resString+= String.format("%-15s|",s);
            resString+="\n";
            for(int i=0;i<res.values.size();i++) {
                resString += String.format("%-30s|",res.rowNames.get(i));
                for (Long l : res.values.get(i))
                    resString += String.format("%-15d|",l);
                resString+="\n";
            }
        } catch(IllegalArgumentException e){
            resString = "Exeption! Check if names size equals locks size";
        }
        return resString;
    }
    public static String genTextResult(Vector<Lock> locks, Vector<String>lockNames){
        return genTextResult(locks,lockNames,new Vector<FixnumLockFactory>(),new Vector<String>());
    }
    public static Table<Long> genTestTable(Vector<Lock> locks, Vector<String>lockNames,Vector<FixnumLockFactory> fixnumFactories,Vector<String>fixnumNames) throws IllegalArgumentException{
        if(locks.size()!=lockNames.size()) throw new IllegalArgumentException("expected different ammount of names");
        if(fixnumFactories.size()!= fixnumNames.size()) throw new IllegalArgumentException("expected different ammount of fixnumlock names");
        Table <Long> table = new Table<Long>();
        table.columnNames=new Vector<String>();
        table.values=new Vector<Vector<Long>>();
        table.rowNames=new Vector<String>();
        table.columnNames.addAll(lockNames);
        table.columnNames.add("Atomic");
        table.columnNames.add("Monitor");
        table.columnNames.addAll(fixnumNames);
        table.rowNames.add("lock time (ns)");
        table.values.add(lockTest(locks,10));
        table.values.lastElement().add(new Long(-1));//for atomic
        table.values.lastElement().add(monitorLockTest(10));//for monitor
        table.values.lastElement().addAll(fixnumLockLockTest(fixnumFactories,1));
        table.rowNames.add("unlock time (ns)");
        table.values.add(unlockTest(locks,1));
        table.values.lastElement().add(new Long(-1));//for atomic
        table.values.lastElement().add(monitorUnockTest(10));//for monitor
        table.values.lastElement().addAll(fixnumLockLockTest(fixnumFactories,10));
        Vector<TestLockClass> testClasses = generateTestClasses(locks);
        testClasses.add(new AtomicTest());
        testClasses.add(new MonitorTest());

        IntUnaryOperator f=new IntUnaryOperator() {
            @Override
            public int applyAsInt(int value) {
               return value+1;
            }
        };
        //first test with 1M iterations and small amount of threads(max thread time);
        table.rowNames.add("10 threads 10k add(1) (ms)");
        table.values.add(universalMultiThreadTest(testClasses,fixnumFactories,10,10000,f));
        //second test with 100k iterations and 100 threads(max thread time);
        table.rowNames.add("100 threads 2k add(1) (ms)");
       table.values.add(universalMultiThreadTest(testClasses,fixnumFactories,100,2000,f));


        //third test with 10 threads 10 000 iterations and consumable function(max thread time);
        f=new IntUnaryOperator() {
            int i=0;
            @Override
            public int applyAsInt(int value) {
                //System.out.println(i++);
              for(int i=0;i<2000000;i++){
                  value=value*value+3;
              }
                return value+1;
            }
        };
         table.rowNames.add("time consuming operation (ms)");
        table.values.add(universalMultiThreadTest(testClasses,fixnumFactories,10,20,f)); // to change in final
          return table;
    }
    public static Table<Long> genTestTable(Vector<Lock> locks, Vector<String>lockNames) throws IllegalArgumentException{
        return genTestTable(locks,lockNames,new Vector<FixnumLockFactory>(),new Vector<String>());
    }
    static Vector<FixnumLock> createFixnumLocks(Vector<FixnumLockFactory> f, int n){
        Vector<FixnumLock> res = new Vector<FixnumLock>(f.capacity());
          for(FixnumLockFactory fk:f)res.add(fk.getInstance(n));
          return res;
    }
    static Vector<TestLockClass> generateTestClasses(Vector<Lock> locks){
        Vector<TestLockClass> res = new Vector<TestLockClass>(locks.capacity());
        for(Lock l:locks){
            res.add(new CustomTest(l));
        }
        return res;
    }
    public static Vector<Long> lockTest(Vector<Lock> locks,int iter){
         Vector<Long> res= new Vector<Long>();
         for(Lock lock:locks) {
             res.add(new Long(0));
             for(int i =0;i<=iter;i++) {
                 long time = System.nanoTime();
                 lock.lock();
                 if(i!=0)res.set(res.size()-1, res.lastElement()+new Long(System.nanoTime() - time));
                 lock.unlock();
             }
             res.set(res.size()-1, res.lastElement()/iter);
         }
         return res;
     }
    public static Long monitorLockTest(int iter){
        Long res=new Long(0);
        long time;
        for(int i =0;i<=iter;i++) {
                 time = System.nanoTime();
                synchronized (res) {
                  if(i!=0)res += new Long(System.nanoTime() - time);
                }
        }
        res/=iter;
        return res;
    }
    public static Vector<Long> unlockTest(Vector<Lock> locks, int iter){
        Vector<Long> res= new Vector<Long>();
        long time;
        for(Lock lock:locks) {
            res.add(new Long(0));
            for(int i =0;i<=iter;i++) {
                lock.lock();
                time =System.nanoTime();
                lock.unlock();
                if(i!=0)res.set(res.size()-1, res.lastElement()+new Long(System.nanoTime() - time));
            }
            res.set(res.size()-1, res.lastElement()/iter);
        }
        return res;
    }
    public static Long monitorUnockTest(int iter){
        Long res=new Long(0);
        long time;
        for(int i =0;i<=iter;i++) {

            synchronized (res) {
                 time= System.nanoTime();
            }
           if(i!=0) res += new Long(System.nanoTime() - time);
        }
        res/=iter;
        return res;
    }
    public static Vector<Long> fixnumLockLockTest(Vector<FixnumLockFactory> factories,int iter){
        Vector<FixnumLock> locks =  createFixnumLocks(factories,1);
        Vector<Long> res= new Vector<Long>();
        for(FixnumLock lock:locks) {
            lock.register(Thread.currentThread());
        }
        Vector<Lock> l = new Vector<Lock>();l.addAll(locks);
        res = lockTest(l,iter);

        l.clear();
        locks.clear();
        return res;
    }
    public static Vector<Long> fixnumLockUnlockTest(Vector<FixnumLockFactory> factories, int iter){
        Vector<FixnumLock> locks =  createFixnumLocks(factories,1);
        Vector<Long> res= new Vector<Long>();
        for(FixnumLock lock:locks) {
            lock.register(Thread.currentThread());
        }
        Vector<Lock> l = new Vector<Lock>();l.addAll(locks);
        res = unlockTest(l,iter);
        l.clear();
        locks.clear();
        return res;
    }
    public static Vector<Long> universalMultiThreadTest(Vector<TestLockClass> rats,Vector<FixnumLockFactory> ratFactories,int threadNum,int iter,IntUnaryOperator func){
        Vector<Long> res = multiThreadTest(rats,threadNum,iter,func);
        res.addAll(fixnumLockMultiThreadTest(ratFactories,threadNum,iter,func));
        return res;
    }
    public static Vector<Long> multiThreadTest(Vector<TestLockClass> rats,int threadNum,int iter,IntUnaryOperator func){

        Vector<Reference<Long>> tempRes = new Vector<Reference<Long>>(threadNum);
        Vector<TestRunnable> runnables = new Vector<TestRunnable>();
        runnables.clear();
        Vector<Thread> threads=new Vector<Thread>();
        Vector<Long> res= new Vector<Long>(rats.capacity());
        res.setSize(rats.size());
        for(int i=0;i<threadNum;i++) {
            tempRes.add(new Reference<Long>(new Long(-1)));//to see if we missed some tests
            runnables.add(new TestRunnable(rats.get(0),iter,tempRes.get(i),func));
        }
        for(TestLockClass rat:rats) {
            threads.clear();
            //init threads for lockable
            for (int i = 0; i < threadNum; i++) {
                tempRes.get(i).value = new Long(0);
                runnables.get(i).changeLock(rat);
                threads.add(new Thread(runnables.lastElement(), "thread" + i));
            }

            res.set(rats.indexOf(rat),multiThreadTestInnerBlock(rats,threadNum,tempRes,threads));
        }

          return res;
    }
    static Long multiThreadTestInnerBlock(Vector<TestLockClass> rats,int threadNum,Vector<Reference<Long>>tempRes,Vector<Thread>threads){
            Long res=new Long(0);
            //start
            for(int i=0;i<threadNum;i++){
                threads.get(i).start();
            }
            //join

        for(int i=0;i<threadNum;i++){
            //better to kill after some time
            try {
                threads.get(i).join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            }
            //calculate fit function and store in res
            for(int i=0;i<threadNum;i++){
                // if(res.get(rats.indexOf(rat))<tempRes.get(i).value);
                res+=tempRes.get(i).value;
            }
            res/=threadNum;
        return res;
    }
    public static Vector<Long> fixnumLockMultiThreadTest(Vector<FixnumLockFactory> ratFactories,int threadNum,int iter,IntUnaryOperator func){
        if(ratFactories.size() == 0)return new Vector<Long>();
            Vector<FixnumLock> rats =  createFixnumLocks(ratFactories,threadNum);
            Vector<Reference<Long>> tempRes = new Vector<Reference<Long>>(threadNum);
            Vector<TestRunnable> runnables = new Vector<TestRunnable>();
            Vector<Thread> threads=new Vector<Thread>();
            Vector<Long> res= new Vector<Long>(rats.capacity());
            res.setSize(rats.size());
            // fixnum->lock
            Vector<Lock> temp = new Vector<Lock>();temp.addAll(rats);
            //lock->testLockClass;
            Vector<TestLockClass> testRats= generateTestClasses(temp);
            for(int i=0;i<threadNum;i++) {
                tempRes.add(new Reference<Long>(new Long(-1)));//to see if we missed some tests
                runnables.add(new TestRunnable(testRats.get(0),iter,tempRes.get(i),func));
            }
            for(TestLockClass rat:testRats) {
                threads.clear();

                //init threads for lockable
                for (int i = 0; i < threadNum; i++) {
                    tempRes.get(i).value = new Long(0);
                    runnables.get(i).changeLock(rat);
                    threads.add(new Thread(runnables.lastElement(), "thread" + i));
                     rats.get(testRats.indexOf(rat)).register(threads.lastElement());

                }
                res.set(testRats.indexOf(rat),multiThreadTestInnerBlock(testRats,threadNum,tempRes,threads));
            }

            temp.clear();
            testRats.clear();
            rats.clear();

            return res;
        }
    public static void main(String[] args) {
           Vector<testClasses.TestLockClass> tes =new Vector<>();
    }
}

//super.isAssignableFrom(child);