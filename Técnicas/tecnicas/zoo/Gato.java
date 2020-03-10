package tecnicas.zoo;

public class Gato extends Animal implements Terrestre {

    public Gato(String Cor, String Nome, boolean IsMale){
        super(Cor, Nome, IsMale);
    }

    public void som(){
        if(isMale) System.out.println("Miau");
        else System.out.println("Nyahh");
    }

    public void andar(){}

}