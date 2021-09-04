package cz.muni.fi.pb162.vnitro;

/**
 * @author Ondrej Kostik
 */
public class Car extends Vehicle implements ICar {
    private IPerson[] passengers = new IPerson[3];

    public Car(String id) {
        super(id);
    }

    @Override
    public boolean isFull() {
        return passengers[0] != null && passengers[1] != null
                && passengers[2] != null;
    }

    @Override
    public void emptyCar() {
        passengers[0] = null;
        passengers[1] = null;
        passengers[2] = null;
    }

    @Override
    public boolean getOnPassenger(IPerson passenger) {
        if (passengers[0] == null){
            return getOnPassenger(1, passenger);
        }
        if (passengers[1] == null){
            return getOnPassenger(2, passenger);
        }
        return getOnPassenger(3, passenger);
    }

    @Override
    public boolean getOnPassenger(int position, IPerson passenger) {
        if (passengers[position-1] == null){
            passengers[position-1] = passenger;
            return true;
        }
        return false;
    }

    @Override
    public String toString(){
        return String.format("Car with ID: %s, driver: %s, passengers: %s, %s,%s",
                getId(), getDriver(), passengers[0], passengers[1], passengers[2]);
    }
}
