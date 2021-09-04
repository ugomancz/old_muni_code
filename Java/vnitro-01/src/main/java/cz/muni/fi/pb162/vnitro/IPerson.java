package cz.muni.fi.pb162.vnitro; 
/**
 * Interface for Person
 */ 

public interface IPerson {

    /**
     * @return Name of the person
     */
    String getName();
    
    /**
     * @return true if this person has drive license, false otherwise
     */
    boolean getHasDriveLicense();
    
    /**
     * @return Person <name> has/hasn't drive license.
     */
    String toString();
    
}
