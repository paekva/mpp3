package generators;

public class Exponential extends Generator {
    private double lambda = 2.0;

    public Exponential(double[] params){
        generatorParams = params;
    }

    double getRandomValue(double m, double y) {
        return Math.log(1 - Math.random()) / lambda;
    }
}
