package lab_coordenacao_2.exercicio1;
import java.util.concurrent.Semaphore;

public class ContadorSemafaro {

    static final int NUM_THREADS = 100;
    static final int NUM_STEPS = 100000;
    static final Semaphore semaphore = new Semaphore(1);

    static int sum = 0;

    static class Worker extends Thread {
        @Override
        public void run() {
            for (int i = 0; i < NUM_STEPS; i++) {
                
                try {
                    semaphore.acquire();
                    sum += 1;
                }catch(InterruptedException e) {
                    System.out.println("Thread interrompida");
                } finally {
                    semaphore.release();
                }
            }
        }
    }

    public static void main(String[] args) {

        Thread[] threads = new Thread[NUM_THREADS]; 
        long expected = (long) NUM_THREADS * NUM_STEPS;

        // Criação das threads
        for (int i = 0; i < NUM_THREADS; i++) {
            threads[i] = new Worker();
            threads[i].start();
        }

        // Espera todas as threads terminarem
        for (int i = 0; i < NUM_THREADS; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                System.out.println("Thread interrompida");
            }
        }

        System.out.println("--- Demonstração de Condição de Corrida ---");
        System.out.println("Valor esperado (N * steps): " + expected);
        System.out.println("Valor obtido no contador:   " + sum);
        System.out.println("Diferença (Perda de dados): " + (expected - sum));
    }
}