package testClasses;

import java.util.function.IntUnaryOperator;

public class DummyTestClass implements TestLockClass {
        int counter=0;
        IntUnaryOperator f;
        public DummyTestClass(){
            f  = new IntUnaryOperator() {
                @Override
                public int applyAsInt(int value) {
                    return value++;
                }
            };
        }
        public DummyTestClass(IntUnaryOperator func){
            f=func;

        }
        public void setFunction(IntUnaryOperator func){
            f=func;
        }
        public void process(){
            counter=f.applyAsInt(counter);
        }

    @Override
    public IntUnaryOperator getFunction() {
        return f;
    }

    public int get(){
            return counter;
        }

}
