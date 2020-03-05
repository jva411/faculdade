package tecnicas.ui;

import tecnicas.geometria.Ponto;

public abstract class Figura {

    Ponto Origem;

    protected Figura(Ponto Origem){
        this.Origem = Origem;
    }

    public abstract void desenhar();

    public abstract double getArea();

    public void mover(Ponto p){

        Origem.mover(p.x, p.y);

    }

}