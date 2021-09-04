package cz.muni.fi.pb162.exam;

import java.util.Objects;

/**
 * @author Anonymous
 */
public class HistoricalEvent implements Comparable<HistoricalEvent> {

    private String date;
    private String desc;

    /**
     * Constructor.
     *
     * @param date Date of the event in the format YYYY-MM-DD
     * @param desc Description (what happened)
     * @throws IllegalArgumentException if the date is missing
     */
    public HistoricalEvent(String date, String desc) {
        if (date == null || !date.matches("\\d\\d\\d\\d-\\d\\d-\\d\\d")) {
            throw new IllegalArgumentException("date");
        }
        if (desc == null || desc.isEmpty()) {
            throw new IllegalArgumentException("event");
        }
        this.date = date;
        this.desc = desc;
    }

    /**
     * Returns date of the event.
     *
     * @return date
     */
    public String getDate() {
        return date;
    }

    /**
     * Returns description (what happened).
     *
     * @return description
     */
    public String getDescription() {
        return desc;
    }

    @Override
    public String toString() {
        return date + " " + desc;
    }

    public int compareTo(HistoricalEvent event) {
        if (this == event) {
            return 0;
        }
        int result = this.getDate().compareTo(event.getDate());
        if (result != 0) {
            result = this.getDescription().compareTo(event.getDescription());
        }
        return result;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        HistoricalEvent that = (HistoricalEvent) o;
        return Objects.equals(date, that.date) &&
                Objects.equals(desc, that.desc);
    }

    @Override
    public int hashCode() {
        return Objects.hash(date, desc);
    }
}
