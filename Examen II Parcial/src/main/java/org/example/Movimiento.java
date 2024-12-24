package org.example;


import java.awt.Color;
import java.awt.Graphics;
public class Movimiento {
    int x,y;
    int fila=600;

    int tx,ty;
    boolean ocupado;

    int num;


    public Movimiento(int x, int y){
        this.x=x;
        this.y=y;
    }
    public Movimiento(int tx, int ty, boolean ocupado){
        this.tx=tx;
        this.ty=ty;
    }


    public Movimiento(){}

    public int getX(){
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }

    public int getY(){
        return y;
    }

    public void dibujar(Graphics g){
        g.setColor(Color.WHITE);
        g.fillOval(x,y,48,48);

    }


    public void  movimientoF(){//Movimiento de los clientes a la fila
        if(y>=fila){
            y-=20;
        }


    }









}
