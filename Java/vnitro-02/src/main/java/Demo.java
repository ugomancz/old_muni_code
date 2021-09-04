
import java.util.Collection;
import java.util.NoSuchElementException;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author bar
 */
public class Demo {
    public static void main(String[] args) {
        Car correctLeftOne = new Car("1B2345", CrossingSide.LEFT), 
            correctLeftTwo = new Car("1AHOJ", CrossingSide.LEFT),
            correctRightOne = new Car("2BCDE", CrossingSide.RIGHT);
        Car incorrect;
        RailwayCrossing ok = new RailwayCrossing("1234"), incorrectCrossing;
        System.err.print("Nekorektni parametry konstruktoru Car:");
        try{
            incorrect = new Car(null,CrossingSide.RIGHT);
            System.err.println(" nevyhozena vyjimka");
        }catch(IllegalArgumentException ex){
            System.err.println(" OK\nmsg: "+ex.getMessage());
        }catch(Exception ex){
            System.err.println(" vyhozena neocekavana vyjimka: "+ex);
        }
        
        System.err.print("Nekorektni parametry konstruktoru prejezdu: ");
        try{
            incorrectCrossing = new RailwayCrossing(null);
            System.err.println("Chyba -  nevyhozena pozadovana vyjimka.");
        }catch(IllegalArgumentException ex){
            System.err.println("OK\nmsg: "+ex.getMessage());
        }catch(Exception ex){
            System.err.println("Vyhozena neocekavana vyjimka "+ex);
        }
        
        System.err.println("Stav prejezdu: "+ok);
        System.err.println("Prijezd korektniho auta:");
        ok.enqueue(correctLeftOne);
        System.err.println("Stav prejezdu: "+ok);
        ok.enqueue(correctRightOne);
        System.err.println("Stav prejezdu: "+ok);
        ok.enqueue(correctLeftTwo);
        System.err.println("Stav prejezdu: "+ok);
        
        System.err.print("Prijezd auta, ktere uz na prejezdu je:");
        try{
            ok.enqueue(correctLeftTwo);
            System.err.println("Chyba - nevyhozena pozadovana vyjimka.");
        }catch(IllegalArgumentException ex){
            System.err.println("Vyjimka OK\nmsg: "+ex.getMessage());
        }catch(Exception ex){
            System.err.println("Vyhozena neocekavana vyjimka: "+ex);
        }
        
        System.out.println("Seznam vsech aut na leve strane:");
        System.out.println("Leva strana: " + ok.getWaitingCars(CrossingSide.LEFT));
        
        System.out.println("Seznam vsech aut v prave strane:");
        System.out.println("Prava strana: " + ok.getWaitingCars(CrossingSide.RIGHT));
        
        System.out.print("Odstraneni auta ze seznamu v getWaitingCars: ");
        try{
            Collection<Car> carsLeft = ok.getWaitingCars(CrossingSide.LEFT);
            carsLeft.removeAll(carsLeft);
            System.err.println("Zkontrolovat, ze se jedna o kopii ne atribut.");
        }catch(UnsupportedOperationException ex){
            System.out.println("OK");
        }
        
        System.out.println("Odjezd aut, ktera na prejezdu jsou:");
        System.out.print("Z leva:");
        ok.dequeue(CrossingSide.LEFT);
        System.out.print(ok+"\nZ leva: ");
        
        ok.dequeue(CrossingSide.LEFT);
        System.out.print(ok+"\nZ prava:");
        ok.dequeue(CrossingSide.RIGHT);
        System.out.println(ok);
        
        System.err.println("Odjezd neexistujiciho auta:");
        try{
            System.err.print("Z leva:");
            ok.dequeue(CrossingSide.LEFT);
            System.err.println("CHYBA - nevyhozena ocekavana vyjimka.");
        }catch(NoSuchElementException ex){
            System.err.println("OK\nmsg: "+ex.getMessage());
        }catch(Exception ex){
            System.err.println("Neocekavana vyjimka: "+ex);
        }
        
        try{
            System.err.print("Z prava:");
            ok.dequeue(CrossingSide.RIGHT);
            System.err.println("CHYBA - nevyhozena ocekavana vyjimka.");
        }catch(NoSuchElementException ex){
            System.err.println("OK\nmsg: "+ex.getMessage());
        }catch(Exception ex){
            System.err.println("Neocekavana vyjimka: "+ex);
        }
        
        System.out.println("Seznam vsech aut na leve strane:");
        System.out.println("Leva strana: " + ok.getWaitingCars(CrossingSide.LEFT));
        
        System.out.println("Seznam vsech aut v prave strane:");
        System.out.println("Prava strana: " + ok.getWaitingCars(CrossingSide.RIGHT));
    }
}
