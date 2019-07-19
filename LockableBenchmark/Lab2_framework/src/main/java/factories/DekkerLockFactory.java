package factories;
import lockables.DekkerLock;
import lockables.FixnumLock;

public class DekkerLockFactory implements FixnumLockFactory{
    public FixnumLock getInstance(int n){
        return new DekkerLock(n);
    }
}
