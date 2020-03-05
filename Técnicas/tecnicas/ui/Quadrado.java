package tecnicas.ui;

import tecnicas.geometria.Ponto;

public class Quadrado extends Figura {

    public double lado;

    public Quadrado(Ponto Origem, double lado){
        super(Origem);
        this.lado = lado;
    }

    public void desenhar(){

        System.out.println("Oi, eu sou um quadrado!");

    }

    public double getArea(){

        return lado * lado;

    }

}