public class Monitor {
    private int saldo;

    public Monitor(int saldoInicial) {
        this.saldo = saldoInicial;
    }

    public synchronized void depositar(int valor){
        // deposita o  valro na conta
        int temp = saldo;

        try{
            Thread.sleep(1);
        } catch (InterruptedException e) {
            System.out.println("Erro");
        }

        temp += valor;
        saldo = temp;
    }

    public int getSaldo(){
        return saldo;
    }
}
