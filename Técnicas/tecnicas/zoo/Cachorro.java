package tecnicas.zoo;

public class Cachorro extends Animal implements Terrestre {

    public Cachorro(String Cor, String Nome, boolean IsMale){
        super(Cor, Nome, IsMale);
    }

    public void som(){
        System.out.println("Au au");
    }

    public void andar(){}

}