public enum EType {
    FIBONACCI (1),
    POW (2),
    BUBBLE_SORT_UINT64 (3),
    STOP (4);

    private final int index;

    EType(int index) {
        this.index = index;
    }

    public int index() {
        return index;
    }
}
