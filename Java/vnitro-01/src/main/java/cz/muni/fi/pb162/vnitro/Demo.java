package cz.muni.fi.pb162.vnitro; 

public class Demo {

    public static void main(String[] args) {

        IPerson driver1 = new Person("Pepa", true);
        IPerson pass1 = new Person("Franta");
        IPerson pass2 = new Person("Anezka", true);
        IPerson pass3 = new Person("Karel", false);
        IPerson pass4 = new Person("Karolina");

        ICar car = new Car("2B6 7451");

        if (car.isFull()) {
            System.out.println("Car with ID " + car.getId() + " is full.");
        } else {
            System.out.println("Car with ID " + car.getId() + " has empty space(s).");
        }

        if (car.getOnDriver(pass1)) {
            System.out.println("Person " + pass1.getName() + ", was setted as a driver.");
        }

        if (car.getOnDriver(driver1)) {
            System.out.println("Person " + driver1.getName() + ", was setted as a driver.");
        }

        if (car.getOnDriver(pass3)) {
            System.out.println("Person " + pass3.getName() + ", couldn't be setted as a driver.");
        }

        car.getOnPassenger(2, pass2);
        System.out.println(car);

        car.getOnPassenger(pass1);
        car.getOnPassenger(pass3);
        if (car.getOnPassenger(pass4)) {
            System.out.println("Person " + pass4.getName() + ", couldn't be setted as a passenger.");
        }
        
        if (car.isFull()) {
            System.out.println("Car with ID " + car.getId() + " is full.");
        } else {
            System.out.println("Car with ID " + car.getId() + " has empty space(s).");
        }
        
        System.out.println(car);
        car.emptyCar();
        System.out.println(car);
    }

}
