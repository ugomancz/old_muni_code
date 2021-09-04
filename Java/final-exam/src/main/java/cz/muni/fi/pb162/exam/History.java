package cz.muni.fi.pb162.exam;

//import com.sun.source.tree.Tree;

import java.io.*;
import java.util.SortedSet;
import java.util.TreeSet;
import java.util.stream.Collectors;

public class History {
    public SortedSet<HistoricalEvent> getAllEvents() {
        return allEvents;
    }

    private SortedSet<HistoricalEvent> allEvents = new TreeSet<HistoricalEvent>();

    public SortedSet<HistoricalEvent> getAllEvents(boolean orderByType) {
        if (orderByType) {
            SortedSet<HistoricalEvent> result = new TreeSet<>(new EventTypeComparator());
            result.addAll(allEvents);
            return result;
        }
        return getAllEvents();
    }

    public SortedSet<HistoricalEvent> getEvents(boolean orderByType, boolean battles, boolean peaceTreaty, boolean other) {
        SortedSet<HistoricalEvent> result = new TreeSet<>();
        if (orderByType) {
            result = new TreeSet<>(new EventTypeComparator());
        }
        if (battles == true) {
            result.addAll(allEvents.stream()
                    .filter((x) -> (x instanceof Battle))
                    .collect(Collectors.toSet()));
        }
        if (peaceTreaty == true) {
            result.addAll(allEvents.stream()
                    .filter((x) -> (x instanceof PeaceTreaty))
                    .collect(Collectors.toSet()));
        }
        if (other == true) {
            result.addAll(allEvents.stream()
                    .filter((x) -> !(x instanceof Battle) && !(x instanceof PeaceTreaty))
                    .collect(Collectors.toSet()));
        }
        return result;
    }

    public HistoricalEvent getOldestBattle() {
        if (getAllEvents(true).first() == null) {
            return null;
        }
        HistoricalEvent oldestBattle = getEvents(true, true, false, false).first();
        if (oldestBattle instanceof Battle) {
            return oldestBattle;
        }
        return null;
    }

    public void read(File file) throws EventsException {
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(file)));
            String line = reader.readLine();
            SortedSet<HistoricalEvent> tmpEvents = new TreeSet<>();
            while (line != null) {
                addToEvents(line, tmpEvents);
                line = reader.readLine();
            }
            allEvents.addAll(tmpEvents);
        } catch (IOException ex) {
            throw new EventsException("File couldn't be loaded");
        }
    }

    private void addToEvents(String line, SortedSet tmpEvents) throws EventsException {
        String[] split = line.split(" ", 5);
        if (String.format("%s %s", split[1], split[2]).equals(Battle.battlePrefix)) {
            HistoricalEvent event = new Battle(split[0], split[3]);
            tmpEvents.add(event);
            return;
        }
        if (split.length > 3 && String.format("%s %s %s", split[1], split[2], split[3]).equals(PeaceTreaty.treatyPrefix)) {
            HistoricalEvent event = new PeaceTreaty(split[0], split[4]);
            tmpEvents.add(event);
            return;
        }
        HistoricalEvent event = new HistoricalEvent(split[0], split[1]);
        tmpEvents.add(event);
    }

    public static void write(OutputStream os, SortedSet<HistoricalEvent> events) throws EventsException {
        if (events == null) {
            throw new EventsException("Set of events is null");
        }
        try (BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(os))) {
            for (HistoricalEvent event : events) {
                writer.write(String.format("%s %s", event.getDate(), event.getDescription()));
                writer.newLine();
            }
        } catch (IOException ex) {
            throw new EventsException("Couldn't write to file");
        }
    }

    public void write(File file, SortedSet<HistoricalEvent> events) throws EventsException {
        try {
            write(new FileOutputStream(file), events);
        } catch (FileNotFoundException ex) {
            throw new EventsException("output file doesn't exist");
        }
    }
}
