package lab_coordenacao_2.exercicio2;
import java.util.concurrent.Semaphore;

public class ContaSemafaro {

    static int saldo = 100;
    static final Semaphore semaphore = new Semaphore(1);

    static class Depositar extends Thread {
        private int valor;

        public Depositar(int valor) {
            this.valor = valor;
        }

        @Override
        public void run() {

            // Cada thread chama essa função.
            try{
                semaphore.acquire();    
                int temp = saldo; // Passo 1: Leitura
                try {
                    // Força troca de contexto
                    Thread.sleep(1);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

                temp += valor; // Passo 2: Soma
                saldo = temp;  // Passo 3: Escrita
            } catch(InterruptedException e) {
                System.out.println("Thread interrompida");
            } finally{
                semaphore.release();
            }
        
        }
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