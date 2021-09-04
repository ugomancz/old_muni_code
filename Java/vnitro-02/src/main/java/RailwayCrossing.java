import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.NoSuchElementException;

/**
 * @author Ondrej Kostik
 */
public class RailwayCrossing {
    private String name = null;
    private List<Car> leftLine = new ArrayList<>();
    private List<Car> rightLine = new ArrayList<>();

    public RailwayCrossing(String name) {
        if (name == null) {
            throw new IllegalArgumentException("Name of RailwayCrossing cannot be null");
        }
        this.name = name;
    }

    public void enqueue(Car car) {
        if (car == null) {
            throw new IllegalArgumentException("Car doesn't exist");
        }
        if (leftLine.contains(car) || rightLine.contains(car)) {
            throw new IllegalArgumentException("Car already waiting in line");
        }
        if (car.getCrossingSide() == CrossingSide.LEFT) {
            leftLine.add(car);
            return;
        }
        rightLine.add(car);
    }

    public Car dequeue(CrossingSide side) {
        if (leftLine.isEmpty() && rightLine.isEmpty()) {
            throw new NoSuchElementException("No cars waiting at the crossing");
        }
        if (side == CrossingSide.LEFT) {
            if (!leftLine.isEmpty()) {
                return leftLine.remove(0);
            }
            return null;
        }
        if (!rightLine.isEmpty()) {
            return rightLine.remove(0);
        }
        return null;
    }

    public List<Car> getWaitingCars(CrossingSide side) {
        if (side == CrossingSide.LEFT) {
            return Collections.unmodifiableList(new ArrayList<>(leftLine));
        }
        return Collections.unmodifiableList(new ArrayList<>(rightLine));
    }

    @Override
    public String toString() {
        return String.format("%s\nLeva strana: %s\nPrava strana: %s", name, leftLine, rightLine);
    }
}
