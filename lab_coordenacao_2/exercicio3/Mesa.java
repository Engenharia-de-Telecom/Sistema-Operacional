package lab_coordenacao_2.exercicio3;

import java.util.LinkedList;
import java.util.Queue;

class Mesa {

    // Cria uma fila
    private Queue<String> pizzas = new LinkedList<>();
    private final int LIMITE = 2;

    // Monitor: Garante que só um mexe na mesa por vez
    public synchronized void colocarPizza(String nomePizza) throws InterruptedException {
        // Se a mesa NÃO estiver vazia, o cozinheiro dorme e solta o lock
        while (pizzas.size() == LIMITE) {
            System.out.println("Cozinheiro dormindo...");
            wait();
        }

        pizzas.add(nomePizza);

        System.out.println("Cozinheiro colocou a pizza de: " + nomePizza);

        // Avisa o entregador que tem pizza pronta
        notifyAll();
    }

    public synchronized String retirarPizza() throws InterruptedException {
        // Se a mesa estiver vazia, o entregador dorme e solta o lock
        while (pizzas.isEmpty()) {
            System.out.println("Motorista dormindo...");
            wait();
        }

        String pizza = pizzas.poll();
        System.out.println("Entregador levou a pizza de: " + pizza);

        // Avisa o cozinheiro que a mesa liberou
        notifyAll();
        return pizza;
    }
}