import java.util.Objects;

/**
 * @author Ondrej Kostik
 */
public class Car {
    private String registrationPlate = null;
    private CrossingSide crossingSide = null;

    public Car(String registrationPlate, CrossingSide crossingSide) {
        if (registrationPlate == null) {
            throw new IllegalArgumentException("Registration plate is null");
        }
        this.registrationPlate = registrationPlate;
        this.crossingSide = crossingSide;
    }

    public String getRegistrationPlate() {
        return registrationPlate;
    }

    public CrossingSide getCrossingSide() {
        return crossingSide;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Car)) return false;
        Car car = (Car) o;
        return Objects.equals(registrationPlate, car.registrationPlate);
    }

    @Override
    public int hashCode() {
        return Objects.hash(registrationPlate);
    }

    @Override
    public String toString(){
        return String.format("Car %s: %s", registrationPlate, crossingSide);
    }
}
