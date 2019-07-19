package general;

import java.util.Vector;

public class Table<T>{
    public Vector<String> columnNames;
    public Vector<String> rowNames;
    public Vector<Vector<T>> values; // a[row][column];
}
