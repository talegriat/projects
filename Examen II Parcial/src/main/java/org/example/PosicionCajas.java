package org.example;
import java.awt.Color;
import java.awt.Graphics;

public class PosicionCajas {
    int x,y;
    boolean ocupado;
    public PosicionCajas(int x,int y, boolean ocupado){
        this.x=x;
        this.y=y;
        this.ocupado=ocupado;
    }
    public PosicionCajas(boolean ocupado){
        this.ocupado=ocupado;
    }
    public void dibujar(Graphics g){
        if(ocupado){
            g.setColor(Color.GREEN);
            g.fillOval(x,y,48,48);
        }
        else{
            g.setColor(Color.RED);
            g.fillOval(x,y,48,48);
        }
    }

}
