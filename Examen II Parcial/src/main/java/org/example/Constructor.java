package org.example;
import java.util.List;
import java.util.Random;
import java.util.concurrent.BlockingQueue;


public class Constructor implements Runnable {//Es el consumidor como tal, recibe info de Productor y Consumidor para mandarlo a graficos
    private BlockingQueue<Productor> queue1;
    private BlockingQueue<Consumidor>queue2;
    int n1,n2;
    private final List<MovimientoCajas>m;
    public Constructor(BlockingQueue<Productor>queue1, BlockingQueue<Consumidor>queue2,List<MovimientoCajas>m){
        this.queue1= queue1;
        this.queue2=queue2;
        this.m=m;

    }
    public void run(){
        try{
            while(true){
                Productor number=queue1.take();
                //n1=queue1.size();
                Consumidor tpm=queue2.take();
                System.out.println("El cliente "+number.contC+" Va con el trabajador "+tpm.trabajador);
                m.add(new MovimientoCajas(tpm.x,tpm.y));
                //n2=queue1.size();

                Thread.sleep(1000);


            }

        }catch(InterruptedException e){
            Thread.currentThread().interrupt();
        }
    }
}
