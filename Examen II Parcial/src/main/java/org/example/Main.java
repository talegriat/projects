package org.example;

import javax.swing.JFrame;
public class Main{
    public static void main(String[] args){
        JFrame simulacion=new JFrame();
        simulacion.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        simulacion.setResizable(false);
        simulacion.setTitle("Examen Practico - II Parcial");

        Clienzo banco=new Clienzo();
        simulacion.add(banco);
        simulacion.pack();
        banco.InicioSim();
        final Timer timer = new Timer();
        timer.scheduleAtFixedRate(new TimerTask() {
                                                    int i = 60; // Time in seconds
                                                    public void run() {
                                                                        System.out.println(i--);
                                                                        if (i < 0) {
                                                                           timer.cancel();
                                                                            banco.turnOffRun();
                                                                            }
                                                                        }
                                                    }, 0, 1000);
        simulacion.setLocationRelativeTo(null);//se centra la pantalla
        simulacion.setVisible(true);
    }
}