package lab_coordenacao_2.exercicio3;

public class Pizzaria {
    public static void main(String[] args) {
        Mesa mesa = new Mesa();

        // Thread do Cozinheiro
        new Thread(() -> {
            try {
                String[] cardapio = {"Calabresa", "Mussarela", "Portuguesa", "4 Queijos"};

                int i = 0;
                while(true) {
                    String pizza = cardapio[i % cardapio.length];
                    mesa.colocarPizza(pizza);
                    i++;
                    Thread.sleep(2000); // Demora para cozinhar
                }
            } catch (InterruptedException e) {}
        }).start();

        // Thread do Entregador
        new Thread(() -> {
            try {
                while (true) {
                    mesa.retirarPizza();
                    Thread.sleep(500); // Demora para entregar
                }
            } catch (InterruptedException e) {}
        }).start();
    }
}