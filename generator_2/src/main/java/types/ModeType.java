package types;

public enum ModeType {
    UNIFORM("uniform"),
    NORMAL("normal"),
    EXPONENTIAL("exp");

    private final String spelling;

    ModeType(String spelling) {
        this.spelling = spelling;
    }

    public String getSpelling() {
        return spelling;
    }
}
