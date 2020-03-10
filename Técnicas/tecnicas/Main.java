package tecnicas;

import tecnicas.geometria.*;
import tecnicas.ui.*;
import tecnicas.zoo.*;

public class Main {

    public static void main(String[] args){

        Ponto p = new Ponto();
        Figura f = new Quadrado(p, 5);
        f.desenhar();
        System.out.println(f.getArea());

        
        Animal[] animais = new Animal[10];
        animais[0] = new Gato("preto", "luna", false);
        animais[1] = new Cachorro("Marrom", "Chocolate", true);
        animais[2] = new Papagaio("Loro", true);

        for(int i=0; i != 3; i++) animais[i].som();

    }

}