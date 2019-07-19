package lockables;
import java.util.*;
        import java.util.concurrent.Semaphore;
        import java.util.concurrent.TimeUnit;
        import java.util.concurrent.locks.Condition;

public class ILamportLock extends FixnumLock{
    private class Pair implements Comparable{
        private Integer key, priority;      // 0 is max priority

        Pair(Integer ia, Integer ib){
            key = ia;
            priority = ib;
        }

        Pair(Pair obj){
            key = obj.key;
            priority = obj.priority;
        }

        public void setKey(Integer ikey){
            key = ikey;
        }

        public void setPrior(Integer iprior){
            priority = iprior;
        }

        @Override
        public int compareTo(Object ix){
            Pair x = (Pair)ix;
            if(this.key < x.key){
                return -1;
            }
            else if(Objects.equals(this.key, x.key)){
                return 0;
            }
            return 1;
        }
    };

    private final ArrayList<Pair> tickets = new ArrayList<>(threadNum);
    private final ArrayList<Boolean> entering = new ArrayList<>(threadNum);

    private final TreeSet<Pair>freeUsedTickets = new TreeSet<>();

    private final Integer ticketBound = 2;
    //  private final AtomicInteger maxTicket = new AtomicInteger(0);

    private final Semaphore fillCount = new Semaphore(ticketBound);

    private Boolean isInitialized = Boolean.FALSE;

    public ILamportLock(int n){
        super(n);
        synchronized(isInitialized){
            if(!isInitialized){
                for(int i = 0; i < threadNum; i++){
                    tickets.add(new Pair(-1, -1));
                    entering.add(false);
                    freeUsedTickets.add(new Pair(i,0));
                }
                isInitialized = true;
            }
        }
    }

    @Override
    public void lock(){
        Integer pid = getId();
        try{
            fillCount.acquire();
        }
        catch(InterruptedException me){

        }
        actualLock(pid);
    }

    @Override
    public void lockInterruptibly() throws InterruptedException{
        Integer pid= getId();
        fillCount.acquire();
        actualLock(pid);
    }

    @Override
    public boolean tryLock(){
        Integer pid =getId();
        Boolean result = fillCount.tryAcquire();
        if(!result){
            return false;
        }
        actualLock(pid);
        return true;
    }

    @Override
    public boolean tryLock( long time, TimeUnit unit) throws InterruptedException{
        Integer pid =getId();
        Boolean result = fillCount.tryAcquire(time, unit);
        if(!result){
            return false;
        }
        actualLock(pid);
        return true;
    }

    @Override
    public Condition newCondition() throws UnsupportedOperationException{
        throw new UnsupportedOperationException();
    }

    @Override
    public void unlock(){
        Integer pid = getId();
        Pair freeTicket = new Pair(tickets.get(pid));
        freeTicket.setPrior(freeTicket.priority + 1);
        tickets.get(pid).setKey(-1);
        tickets.get(pid).setPrior(-1);


        synchronized(freeUsedTickets){
            freeUsedTickets.add(freeTicket);
        }
        fillCount.release();

       // System.out.println("Thread #" + pid + " exited....");
    }

    private void actualLock(Integer pid){
        Pair ticket;

        entering.set(pid, true);
        synchronized(freeUsedTickets){
            ticket = freeUsedTickets.pollFirst();
        }
        entering.set(pid, false);
        tickets.set(pid, ticket);

       // System.out.println(pid + " got " + ticket.key + " with priority " + ticket.priority);

        for(int i = 0; i < threadNum; i++){
            if(i == pid){ continue; }
            while(entering.get(i)){ Thread.yield(); }
            while((tickets.get(pid).priority > tickets.get(i).priority && tickets.get(i).priority != -1)||
                    (tickets.get(i).priority.equals(tickets.get(pid).priority) && (tickets.get(i).key != -1 && tickets.get(pid).key > tickets.get(i).key)))
            { Thread.yield(); }

        }

        // System.out.println(freeUsedTickets);
    }
}