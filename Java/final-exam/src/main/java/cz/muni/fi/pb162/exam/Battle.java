package cz.muni.fi.pb162.exam;

public class Battle extends HistoricalEvent {

    public static final String battlePrefix = "Bitva u";

    public Battle(String date, String place) {
        super(checkDate(date), checkPlace(place));
    }

    private static String checkDate(String date) {
        if (date == null) {
            throw new IllegalArgumentException("date is null");
        }
        return date;
    }

    private static String checkPlace(String place) {
        if (place == null) {
            throw new IllegalArgumentException("place is null");
        }
        return String.format("%s %s", battlePrefix, place);
    }
}
