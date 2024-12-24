package org.example;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.TimeUnit;
import java.util.Random;

public class Productor implements Runnable{
    private BlockingQueue<Productor>queue;

    private final List<Movimiento>m;
    int contC;
    Random random= new Random();
    int x=600;
    int y=1500;



    boolean band;

    //Constructores
    public Productor(BlockingQueue<Productor> queue,List<Movimiento>m,int contC){
        this.queue = queue;
        this.m=m;
        this.contC=contC;

    }

    public void run(){
        //Manda a los clientes a fila y consumidor
        try{
            while(true){
                queue.put(this);
                System.out.println("Cliente "+contC);
                m.add(new Movimiento(600,1000));
                Thread.sleep(1000);
                contC++;
            }


        }catch(InterruptedException e){
            Thread.currentThread().interrupt();
        }

    }

}
