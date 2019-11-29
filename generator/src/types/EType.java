package types;

public enum EType {
    FIBONACCI (0),
    POW (1),
    BUBBLE_SORT_UINT64 (2),
    STOP (3);

    private final int index;

    EType(int index) {
        this.index = index;
    }

    public int index() {
        return index;
    }
}
