package cz.muni.fi.pb162.vnitro; 
/**
 * Interface for Car
 */ 

public interface ICar extends IVehicle {
    
    /**
     * Returns boolean value depens on the state of car. 
     * Car is full if and only if every space for passengers 
     * has a passenger.
     *  
     * @return true if this car is full, false otherwise
     */
    boolean isFull();
    
    /**
     * Method empties this car - i.e. sets all places for passengers to empty.
     */
    void emptyCar();
    
    /**
     * Method tries to get on with passenger. First tries 
     * the 1st position (next to driver), then the 2nd position (behind the driver)
     * and last the 3rd position (next to the 2nd position, behind the 1st position).
     * 
     * @param passenger Passenger who wants to get on.
     * @return true if getting on is successful, false otherwise
     */
    boolean getOnPassenger(IPerson passenger);
    
    /**
     * Method tries to get on with passenger to the specified position. 
     * 1 = next to driver, 2 = behind the driver, 3 = next to the 2, behind the 1.
     * 
     * @param position Specified position where passenger wants to sit.
     * @param passenger Passenger who wants to get on.
     * @return true if getting on is successful, false otherwise
     */
    boolean getOnPassenger(int position, IPerson passenger);
    
    /**
     * @return Car with ID: <car_id>, driver: <driver>, passengers: <passenger1>, <passenger2>, <passenger3>
     */
    String toString();
    
}
