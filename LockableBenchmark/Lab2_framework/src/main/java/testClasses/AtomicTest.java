package testClasses;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.function.IntUnaryOperator;

public class AtomicTest extends DummyTestClass implements TestLockClass{
    AtomicInteger atomicCounter=new AtomicInteger(0);
    public AtomicTest(){};
    public AtomicTest(IntUnaryOperator func){
        f=func;
    };
    @Override
    public void process(){
        atomicCounter.getAndUpdate(f);
    }
    @Override
    public int get(){
        return atomicCounter.get();
    }

}
