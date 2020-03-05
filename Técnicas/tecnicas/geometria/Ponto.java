package tecnicas.geometria;

public class Ponto {

    public double x, y;
    
    public Ponto(){ this(0); }
    public Ponto(double x) { this(x, x); }
    public Ponto(double x, double y){
        
        this.x = x;
        this.y = y;

    }

    public void mover(double dx, double dy){
        
        x += dx;
        y += dy;

    }

    public double distance(Ponto p){
        return Math.sqrt( Math.pow(p.x - x, 2) + Math.pow(p.y - y, 2));
    }

}