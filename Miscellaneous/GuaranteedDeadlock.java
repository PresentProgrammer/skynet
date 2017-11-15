class Main {

  private static final boolean TURNED_OFF = false;

  public static void main(final String... args) {
    final Object firstLock = new Object();
    final Object secondLock = new Object();
    final CustomSemaphore semaphore = new CustomSemaphore(TURNED_OFF);
    System.out.println("See how the threads never finish...");

    synchronized (firstLock) {
      final Thread lockedThread = new Thread(new DeadlockRunnable(firstLock, secondLock, semaphore));
      lockedThread.start();
      while (semaphore.forbidToGo()) {
        Thread.yield();
      }
      synchronized (secondLock) {
        Message.finishingThread();
      }
    }
  }
}

class DeadlockRunnable implements Runnable {

  private final Object firstLock;
  private final Object secondLock;
  private final CustomSemaphore semaphore;

  DeadlockRunnable(final Object firstLock, final Object secondLock, final CustomSemaphore semaphore) {
    this.firstLock = firstLock;
    this.secondLock = secondLock;
    this.semaphore = semaphore;
  }

  @Override
  public void run() {
    synchronized (secondLock) {
      semaphore.turnOn();
      synchronized (firstLock) {
        Message.finishingThread();
      }
    }
  }
}

class Message {

  static void finishingThread() {
    System.out.println("finishing thread with name " + Thread.currentThread().getName());
  }
}

class CustomSemaphore {

  private boolean go;

  CustomSemaphore(final boolean go) {
    this.go = go;
  }

  void turnOn() {
    go = true;
  }

  boolean forbidToGo() {
    return !go;
  }
}