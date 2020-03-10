package tecnicas.zoo;

public abstract class Animal {

    String cor, nome;
    boolean isMale;

    protected Animal(String Cor, String Nome, boolean IsMale){

        cor = Cor;
        nome = Nome;
        isMale = IsMale;

    }

    public abstract void som();

}