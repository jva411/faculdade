package tecnicas;

import java.lang.reflect.*;
import java.util.HashMap;

import tecnicas.geometria.*;
import tecnicas.ui.*;

public class Main {

    public static void main(String[] args){

        Ponto p = new Ponto();
        Figura f = new Quadrado(p, 5);
        f.desenhar();
        System.out.println(f.getArea());

    }

}