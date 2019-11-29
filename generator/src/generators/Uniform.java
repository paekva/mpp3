package generators;

public class Uniform extends Generator {
    public Uniform(double[] params){
        generatorParams = params;
    }

    double getRandomValue(double a, double b) {
        return Math.random()*(b-a) + a;
    }
}
