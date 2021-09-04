package cz.muni.fi.pb162.exam;

import java.util.Comparator;

public class EventTypeComparator implements Comparator<HistoricalEvent> {
    @Override
    public int compare(HistoricalEvent event1, HistoricalEvent event2) {
        if (event1.getClass() == event2.getClass()){
            return event1.getDate().compareTo(event2.getDate());
        }
        return 0;
    }
}
