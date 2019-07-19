package testClasses;

import java.util.function.IntUnaryOperator;

public interface TestLockClass{
    void process();
    int get();
    void setFunction(IntUnaryOperator f);
    IntUnaryOperator  getFunction();
}
