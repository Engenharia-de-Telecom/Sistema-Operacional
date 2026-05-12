package lab_coordenacao_2.exercicio2;

public class ContaMonitor {

    static int saldo = 100;

    static class Depositar extends Thread {
        private int valor;

        public Depositar(int valor) {
            this.valor = valor;
        }

        @Override
        public void run() {

            // Cada thread chama essa função.
                int temp = saldo; // Passo 1: Leitura
                try {
                    // Força troca de contexto
                    Thread.sleep(1);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

                temp += valor; // Passo 2: Soma
                saldo = temp;  // Passo 3: Escrita
    }

    public static void main(String[] args) {

        Thread t1 = new Depositar(50);
        Thread t2 = new Depositar(30);

        t1.start();
        t2.start();

        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Saldo final esperado: 180");
        System.out.println("Saldo final obtido: " + saldo);
    }
}
}