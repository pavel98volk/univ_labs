package factories;

import lockables.FixnumLock;

public interface FixnumLockFactory {
   FixnumLock getInstance(int n);
}
