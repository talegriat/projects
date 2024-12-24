package org.example;

import java.util.List;
import java.util.Random;
import java.util.concurrent.BlockingQueue;

public class Consumidor implements Runnable{
    private BlockingQueue<Consumidor>queue;
    private final List<PosicionCajas>tpm;

    int x, y;
    boolean ocupado=true;



    int trabajador;
    int contDesc=0;



    public Consumidor(BlockingQueue<Consumidor> queue, int trabajador, int x, int y,List<PosicionCajas>tpm){
        this.queue=queue;
        this.trabajador=trabajador;
        this.x=x;
        this.y=y;
        this.tpm=tpm;

    }

    public void run(){
        try{
            tpm.add(new PosicionCajas(x,y,ocupado));
            while(true){
                queue.put(this);
                System.out.println("Se mando el Trabajador "+ trabajador);

                Thread.sleep(10000);




            }



        }catch(InterruptedException e){
            Thread.currentThread().interrupt();
        }

    }
}

