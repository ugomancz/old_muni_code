
package cz.muni.fi.pb162.exam;

import java.io.File;
import java.io.IOException;

/**
 *
 *
 * @author Ales  Zlamal
 */
public class Demo {
    
    public static void main(String[] args) {
        History hist = new History();
        
        try {
            hist.read(new File("none.txt"));
            System.out.println("ERROR: read() should throw EventsException on failure.");
        } catch(EventsException ex) {            
        } catch(Exception ex) {
            System.out.println("ERROR: read() should throw EventsException on failure: " + ex);
        }
        
        try {
            hist.read(new File("history.txt"));
        } catch(Exception ex) {
            System.out.println("ERROR: read() failed on correct input: " + ex);
        }
        
        try {
            System.out.println();
            System.out.println("Battles sorted by date:");
            History.write(System.out, hist.getEvents(false, true, false, false));
            
            System.out.println();
            System.out.println("Peace treaties sorted by date:");
            History.write(System.out, hist.getEvents(false, false, true, false));
            
            System.out.println();
            System.out.println("Other events sorted by date:");
            History.write(System.out, hist.getEvents(false, false, false, true));
            
            System.out.println();
            System.out.println("All events by date:");
            History.write(System.out, hist.getAllEvents(false));
            
            System.out.println();
            System.out.println("All events by type:");
            History.write(System.out, hist.getAllEvents(true));
            
            System.out.println();
            System.out.println("The oldest battle: " + hist.getOldestBattle());
        } catch(EventsException ex) {            
        }
        
        int oldSize = hist.getAllEvents(false).size();
        try {
            hist.read(new File("history-errors.txt"));
            System.out.println("ERROR: read() should throw EventsException on failure.");
        } catch (EventsException ex) {
            if (hist.getAllEvents(false).size() != oldSize) {
                System.out.println("ERROR: read() should fail atomically.");
            }
        } catch (Exception ex) {
            System.out.println("ERROR: read() should throw EventsException on failure: " + ex);
        }
    }
}
