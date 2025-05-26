import java.util.*;

public class SymbolTable {
    Map<String, Integer> OffsetMap = new HashMap<String, Integer>();

    public void insert(String s, int address) {
        // Controlla se l'indirizzo è già occupato da un'altra variabile
        for (Map.Entry<String, Integer> entry : OffsetMap.entrySet()) {
            if (entry.getValue() == address && !entry.getKey().equals(s)) {
                throw new IllegalArgumentException(
                    "Reference to a memory location already occupied by another variable: " + 
                    entry.getKey() + " at address " + address);
            }
        }
        OffsetMap.put(s, address);
    }

    public int lookupAddress(String s) {
        if (OffsetMap.containsKey(s))
            return OffsetMap.get(s);
        else
            return -1;
    }
}