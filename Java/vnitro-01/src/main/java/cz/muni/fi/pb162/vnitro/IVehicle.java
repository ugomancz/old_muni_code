package cz.muni.fi.pb162.vnitro; 
/**
 * Interface for Vehicle
 */ 

public interface IVehicle {

    /**
     * @return id of the vehicle
     */
    String getId();
    
    /**
     * @return driver who is in the vehicle
     */
    IPerson getDriver();
    
    /**
     * Method tries to get on with the specified driver. 
     * Driver cannot get on if here is already another 
     * driver in the car or driver has not drive license.
     * 
     * @param driver Person who wants to be a driver of this vehicle.
     * @return true if person can be driver, false otherwise
     */
    boolean getOnDriver(IPerson driver);
}
