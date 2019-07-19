package testClasses;

import java.util.function.IntFunction;

public class MonitorTest extends DummyTestClass implements TestLockClass{
  int  counter=0;
    public MonitorTest(){};
    @Override
    public void process(){
        synchronized (this) {
            counter=f.applyAsInt(counter);
        }
    }
}
