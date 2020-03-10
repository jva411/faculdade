package tecnicas.zoo;

public class Papagaio extends Animal implements Avoante, Terrestre {

    public Papagaio(String Nome, boolean IsMale){
        super("verde", Nome, IsMale);
    }

    public void som(){
        System.out.println(new StringBuilder(nome).append(' ').append(nome).toString());
    }

    public void voar(){}
    public void andar(){}

}