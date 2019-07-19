package testClasses;
import java.util.concurrent.locks.Lock;
import java.util.function.IntFunction;
import java.util.function.IntUnaryOperator;

public class CustomTest extends DummyTestClass implements TestLockClass{
    Lock lock;

    public CustomTest(Lock l){
        super();
        lock = l;
    }
    public CustomTest(Lock l,IntUnaryOperator func){
        super(func);
        lock=l;
    }
    @Override
    public void process(){
        lock.lock();
        counter=f.applyAsInt(counter);
        lock.unlock();
    }

}
