package org.example;

import java.awt.*;

public class MovimientoCajas {//los personajes van a las cajas

    int x,y;
    int filay=600;
    int filax=600;
    public MovimientoCajas(int x, int y){
        this.x=x;
        this.y=y;
    }

    public void movimientoC(){
        if(y==230){
            if(x>=600){
                if(filax<=700){
                    filax+=20;
                }
                else{
                    if(filay>=300){
                        filay-=20;
                    }
                    else{
                        if(filax<=x){
                            filax+=20;
                        }
                    }

                }

            }
            else{
                if(x<=600){
                    if(filax>=500){
                        filax-=20;
                    }
                    else{
                        if(filay>=300){
                            filay-=20;
                        }
                        else{
                            if(filax>=x){
                                filax-=20;
                            }
                        }

                    }
                }

            }
        }else{
            if(filay>=500){
                filay-=20;
            }
            else{
                if(x<=600){
                    if(filax>=x){
                        filax-=20;

                    }
                }
                else{
                    if(x>=600){
                        if(filax<=x){
                            filax+=20;
                        }
                    }

                }

            }

        }

    }
    public void dibujar(Graphics g){
        g.setColor(Color.WHITE);
        g.fillOval(filax,filay,48,48);

    }
}
