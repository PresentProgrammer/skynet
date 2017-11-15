class Main {

  public static void main(final String... args) {
    System.out.println("See how the threads never finish...");
    final Object lock = new Object();
    synchronized (lock) {
      final Thread lockedThread = new Thread(new DeadlockRunnable(lock));
      lockedThread.start();
      try {
        lockedThread.join();
      } catch (final InterruptedException e) {
        e.printStackTrace();
      }
      Message.finishingThread();
    }
  }
}

class DeadlockRunnable implements Runnable {

  private final Object lock;

  DeadlockRunnable(final Object lock) {
    this.lock = lock;
  }

  @Override
  public void run() {
    synchronized (lock) {
      Message.finishingThread();
    }
  }
}

class Message {

  static void finishingThread() {
    System.out.println("finishing thread with name " + Thread.currentThread().getName());
  }
}
















