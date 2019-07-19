package benchmark;

import general.Reference;
import testClasses.TestLockClass;
import java .util.function.IntUnaryOperator;


// runnable to run tests in SpeedTest class;
class TestRunnable implements Runnable{
    TestLockClass lock;
    int iter;
    Reference<Long> res;
    TestRunnable(TestLockClass l, int iter , Reference<Long> result, IntUnaryOperator func ){
        this.iter=iter;
        lock=l;res=result;

        l.setFunction(func);

    }
    TestRunnable(TestLockClass l, int iter , Reference<Long> result ){
        this.iter=iter;
        lock=l;
        res=result;
    }
    void changeLock(TestLockClass l){
        l.setFunction(lock.getFunction());
        lock=l;

    }
  public void run(){
        Long startTime =System.nanoTime();
     for(int i=0;i<iter;i++){
         lock.process();
     }
      res.value+=(System.nanoTime()-startTime)/1000000;
      return;
  }
}
