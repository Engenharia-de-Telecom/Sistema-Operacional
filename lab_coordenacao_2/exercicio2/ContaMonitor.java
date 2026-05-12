public class ContaMonitor {

    static class Depositar extends Thread {
        
        private Monitor monitor;
        private int valor;

        public Depositar(Monitor monitor, int valor) {
            this.monitor = monitor;
            this.valor = valor;
        }

        @Override
        public void run() {
            monitor.depositar(valor);
    }

    public static void main(String[] args) {

        Monitor monitor = new Monitor(100);

        Thread t1 = new Depositar(monitor, 50);
        Thread t2 = new Depositar(monitor, 30);

        t1.start();
        t2.start();

        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Saldo final esperado: 180");
        System.out.println("Saldo final obtido: " + monitor.getSaldo());
    }
}
}