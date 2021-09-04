package cz.muni.fi.pb162.vnitro;

/**
 * @author Ondrej Kostik
 */
public class Vehicle implements IVehicle {
    private String id;
    private IPerson driver;

    public Vehicle(String id) {
        this.id = id;
    }

    @Override
    public String getId() {
        return id;
    }

    @Override
    public IPerson getDriver() {
        return driver;
    }

    @Override
    public boolean getOnDriver(IPerson driver) {
        if (getDriver() != null){
            return false;
        }
        if (!driver.getHasDriveLicense()){
            return false;
        }
        this.driver = driver;
        return true;
    }
}
