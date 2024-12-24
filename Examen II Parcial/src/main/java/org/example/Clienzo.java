package org.example;

import java.awt.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import javax.swing.*;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.List;


public class Clienzo extends JPanel implements Runnable{

    Thread hilodesimulacion;//la simulacion se acaba cuando termina el hilo

    //posicion de inicio de los clientes
    int clientesX=600;
    int clientesY=1000;
    //Array de clientes
    private final List<Movimiento> m;
    private final List<MovimientoCajas>n;

    //Array de Cajas
    private final List<PosicionCajas> tpm;
    //Fondo de la simulacion
    public ImageIcon img= new ImageIcon("D:\\UAA\\Banco.jpg");

    //tuputamadre JUAN
    BlockingQueue<Consumidor> sim=new LinkedBlockingQueue<>();
    BlockingQueue<Productor>num=new LinkedBlockingQueue<>();

    int numero=1;
    public Clienzo() {
        setPreferredSize(new Dimension(1200, 1000));
        this.setBackground(Color.GRAY);
        this.setDoubleBuffered(true);//se dibuja antes de aparecer en la pantalla, mejora el rendimiento
        m= Collections.synchronizedList(new ArrayList<>());
        tpm=Collections.synchronizedList(new ArrayList<>(1));
        n= Collections.synchronizedList(new ArrayList<>());
    }

    public void InicioSim(){
        hilodesimulacion=new Thread(this);
        hilodesimulacion.start();
    }
    boolean run=true;
   public void turnOffRun() {
        run = false;
    }
    //metodo del hilo
    public void run() {
        //Constructor
        Thread constructor= new Thread(new Constructor(num,sim,n));
        constructor.start();
        //Productor
        Thread producer = new Thread(new Productor(num,m,numero));
        producer.start();
        //Consumidores

        Thread trabajador = new Thread(new Consumidor(sim, 1, 335,230, tpm));


            Thread trabajador2=new Thread(new Consumidor(sim,2,465,230,tpm));

            Thread trabajador3=new Thread(new Consumidor(sim,3,600,230,tpm));
            Thread trabajador4=new Thread(new Consumidor(sim,4,740,230,tpm));
            Thread trabajador5=new Thread(new Consumidor(sim,5,860,230,tpm));

            Thread trabajador6=new Thread(new Consumidor(sim,6,200,350,tpm));
            Thread trabajador7=new Thread(new Consumidor(sim,7,400,350,tpm));
            Thread trabajador8=new Thread(new Consumidor(sim,8,600,350,tpm));
            Thread trabajador9=new Thread(new Consumidor(sim,9,800,350,tpm));
            Thread trabajador10=new Thread(new Consumidor(sim,10,1000,350,tpm));




        trabajador6.start();
        trabajador7.start();
        trabajador8.start();
        trabajador9.start();
        trabajador10.start();


        trabajador.start();
        trabajador2.start();
        trabajador3.start();
        trabajador4.start();
        trabajador5.start();





        long drawInterval=1000000000/60;
        long nextDrawTime=System.nanoTime()+drawInterval;
        while(run){
            try{
                for(Movimiento movimiento:m){
                    movimiento.movimientoF();

                }
                for(MovimientoCajas movimientoCajas: n){
                    movimientoCajas.movimientoC();
                }
                repaint();
                long remainingTime=nextDrawTime-System.nanoTime();
                remainingTime=remainingTime/1000000;
                Thread.sleep(remainingTime);
                nextDrawTime+=drawInterval;
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
        prinStatistics();




    }



    public void paintComponent(Graphics g){
        //clientesX= fila.getX();
        //clientesY= fila.getY();
        super.paintComponent(g);
        Graphics2D g1= (Graphics2D)g;//mejor control del 2D
        g.drawImage(img.getImage(),0,0,this);
        img.paintIcon(this,g,0,0);
        g.drawImage(img.getImage(),(int)1920,(int)1200,this);

        //g1.setColor(Color.WHITE);
        //g1.fillOval(clientesX,clientesY,48,48);
        for(Movimiento movimiento:m){
            movimiento.dibujar(g);
        }

        for(PosicionCajas posicionCajas:tpm){
            posicionCajas.dibujar(g);
        }
        for(MovimientoCajas movimientoCajas:n){
            movimientoCajas.dibujar(g);
        }



    }
}

