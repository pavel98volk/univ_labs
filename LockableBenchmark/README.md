# LockableBenchmark
This repository provides benchmark to test Lockables and fixnumlocks

Classes:
1 benchmark package
    - Benchmark class : "class with main()"
    - SpeedTest class : handles the benchmarking process
    - TestRunnable class : is needed for multi-thread testing (in SpeedTest);
    
2 lockable package
    - SpinLock class : as it is 
    - DekkerLock class : derived from FixNumLock
    - FixNumLock class : abstract class. Represents fixnumlock concept
    - FixNumLockInterface interface: interface to implement fixNumLocks
    - BackeryLock class: var 3
    - ILamportLock class: var 5
    
3 testClasses package
    - TestLockClass: interface that specifies structure of TestLockClass. Used in SpeedTest , mostly to test monitor and atomic since they are not usual lockables.
    - DummyTestClass: implements TestLockClass interface. Contains all code, that is similar in TestLockClass es.
    - AtomicTest: extends DummyTestClass, uses atomic Integer;
    - MonitorTest: extends DummyTestClass, uses in-built synchronized;
4 general
    - Reference: used to pass object as if by reference(on reference to object). Reason to implement:  <Long>s are immutable;
    - Table: data type to represent results of benchmarking. Can be retrieved from SpeedTest as well as transformed there into String;
5 factories
    Contains interface for Fixnumlock factory and different implementations of it. Actually implementations are unused;