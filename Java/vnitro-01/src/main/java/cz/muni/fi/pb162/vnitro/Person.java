package cz.muni.fi.pb162.vnitro;  

public class Person implements IPerson {

    private String name;
    private boolean hasDriveLicense;

    public Person(String name){
        this(name, false);
    }

    public Person(String name, boolean hasDriveLicense){
        this.name = name;
        this.hasDriveLicense = hasDriveLicense;
    }
    
    @Override
    public String getName() {
        return name;
    }

    @Override
    public boolean getHasDriveLicense() {
        return hasDriveLicense;
    }

    public String toString() {
        return "Person " + name + (getHasDriveLicense() ? " has" : " has't") +" drive license.";
    }

}
